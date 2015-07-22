#ifndef FILTER_H
#define FILTER_H

#include "filtercoefficient.h"
#include "image.h"
#include "neighbor.h"
#include <vector>

namespace LatticeLib {

/**
 * Spatial Template Filter
 * ========================
 * Class for template filters for image processing.
 * TODO: Should there be a parent class for Filter and StructuringElement?
 * TODO: Child classes for median, min, and max filtering, etc? Or common parent class?
 *
 * Member 			| Comment
 * --------			| --------
 * neighborhoodSize	| Element neighborhood size to be used for this filter.
 * coefficients		| Template coefficients.
 */
	template<class S>
	class Filter {

	private:
		/** Template coefficients. */
		vector<FilterCoefficient<S> > coefficients;

		/** Element neighborhood size to be used for this filter. */
		int neighborhoodSize;

	public:
		/**
		 * Constructor for Filter objects.
		 *
		 * Parameter	| in/out	| comment
		 * :---------	| :------	| :-------
		 * c			| INPUT		| Vector containing the template coefficients.
		 * nS			| INPUT		| Neighborhood size.
		 */
		Filter(vector<FilterCoefficient<S> > c, int nS) {
			coefficients = c;
			neighborhoodSize = nS;
		}

		/**
		 * Destructor for Filter objects.
		 */
		~Filter() {};

		/**
	 	 * Returns neighborhoodSize.
	 	 */
		int getNeighborhoodSize() const {
			return neighborhoodSize;
		}

		/**
	 	 * Returns the number of template coefficients.
		 */
		int getNCoefficients() const {
			return coefficients.size();
		}

		/**
		 * Returns the template coefficient vector.
		 */
		vector<FilterCoefficient<S> > getCoefficients() const {
			return coefficients;
		}

		/**
		 * Returns the requested FilterCoefficient object from the coefficient vector.
		 *
		 *
		 * Parameter		| in/out	| comment
		 * :---------		| :------	| :-------
		 * coefficientIndex	| INPUT		| Position in the template coefficient vector.
		 */
		FilterCoefficient<S> getCoefficient(int coefficientIndex) const {
			return coefficients[coefficientIndex];
		}

		/**
		 * Finds the position of the FilterCoefficient object, corresponding to the neighbor with the input position
		 * index, in the template coefficient vector. Returns -2 if this neighbor does not have a coefficient.
		 *
		 *
		 * Parameter		| in/out	| comment
		 * :---------		| :------	| :-------
		 * positionIndex	| INPUT		| Position index of corresponding neighbor.
		 */
		int findCoefficient(int positionIndex) const {
			int result = -2;
			int nCoefficients = getNCoefficients();
			for (int coefficientIndex = 0; coefficientIndex < nCoefficients; coefficientIndex++) {
				if (coefficients[coefficientIndex].getPositionIndex() == positionIndex) {
					result = coefficientIndex;
				}
			}
			return result;
		}

		/**
		 * Applies the filter to the specified modality band of the input image.
		 *
		 * Parameter	| in/out	| comment
		 * :---------	| :------	| :-------
		 * image		| INPUT		| Input image.
		 * bandIndex	| INPUT		| Index of the band to be filtered.
		 * result		| OUTPUT	| Filtered intensity values. Needs to be of a length of at least image.nElements.
		 */
		template<class T>
		void applyToBand(Image<T> image, int bandIndex, T *result) const {
			if ((bandIndex < 0) || (bandIndex >= image.getNBands())) {
				// throw error or exception
			}

			int nElements = image.getNElements();
			for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
				int neighborhoodSize = getNeighborhoodSize();
				vector<Neighbor> neighbors;
				T result = 0;
				image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
				int nFoundNeighbors = neighbors.size();
				result[elementIndex] = 0;
				for (int neighborIndex = 0; neighborIndex < nFoundNeighbors; neighborIndex++) {
					int coefficientIndex = findCoefficient(neighbors[neighborIndex].getPosition());
					if (coefficientIndex > -1) {
						result[elementIndex] += image(neighbors[neighborIndex].getIndex(), bandIndex) *
												coefficients[coefficientIndex].getCoefficient();
					}
				}
			}
		}

		/**
		 * Applies the filter to all modality bands of the input image.
		 *
		 * Parameter	| in/out	| comment
		 * :---------	| :------	| :-------
		 * image		| INPUT		| Input image.
		 * result		| OUTPUT	| Filtered intensity values. Needs to be of a length of at least image.nElements * image.nBands.
		 */
		template<class T>
		void applyToImage(Image<T> image, T *result) const {
			int nElements = image.getNElements();
			int nBands = image.getNBands();
			for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
				int offset = bandIndex * nElements;
				applyToBand(image, bandIndex, result[offset]);
			}
		}
	};
}

#endif
