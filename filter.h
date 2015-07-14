#ifndef FILTER_H
#define FILTER_H

#include "filtercoefficient.h
#include "image.h"
#include "neighbor.h"

namespace LatticeLib {

/**
 * Class for template filters.
 *
 * Member 			| Comment
 * --------			| --------
 * neighborhoodSize	| Size of spel neighborhood to be used for this filter.
 * coefficients		| Filter coefficients.
 */
	template<class S>
	class Filter {

	private:
		/** Filter coefficients. */
		vector<FilterCoefficient<S> > coefficients;

		/** Size of spel neighborhood to be used for this filter. */
		int neighborhoodSize;

	public:
		Filter(vector<FilterCoefficient<S> > c, int nS) {
			coefficients = c;
			neighborhoodSize = nS;
		}

		~Filter() {};

		/**
	 	 * Returns neighborhoodSize.
	 	 */
		int getNeighborhoodSize() const {
			return neighborhoodSize;
		}

		/**
	 	 * Returns the number of filter coefficients.
		 */
		int getNCoefficients() const {
			return coefficients.size();
		}

		/**
		 * Returns the coefficient vector.
		 */
		vector<FilterCoefficient<S> > getCoeffs() const {
			return coefficients;
		}

		/**
		 * Returns i:th FilterCoefficient from the coefficient vector.
		 *
		 * Parameter		| comment
		 * :---------		| :-------
		 * coefficientIndex	| position in coefficient vector
		 */
		FilterCoefficient<S> getCoefficient(int coefficientIndex) const {
			return coefficients[coefficientIndex];
		}

		/**
		 * Finds the position of the coefficient corresponding to the neighbor with the input index. Returns -1 if this neighbor does not have a coefficient.
		 *
		 * Parameter		| comment
		 * :---------		| :-------
		 * positionIndex	| Position index of corresponding neighbor.
		 */
		int findCoefficient(int positionIndex) const {
			int result = -1;
			int nCoefficients = getNCoefficients();
			for (int coefficientIndex = 0; coefficientIndex < nCoefficients; coefficientIndex++) {
				if (coefficients[coefficientIndex].getIndex() == positionIndex) {
					result = coefficientIndex;
				}
			}
			return result;
		}

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
