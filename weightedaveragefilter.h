#ifndef LATTICELIBRARY_WEIGHTEDAVERAGEFILTER_H
#define LATTICELIBRARY_WEIGHTEDAVERAGEFILTER_H

#include "filtercoefficient.h"
#include "image.h"
#include "neighbor.h"
#include "templatefilter.h"
#include "spatialtemplate.h"
#include <vector>
#include <stdio.h>

namespace LatticeLib {

/**
 * Spatial weighted average filter
 * ================================
 * Class for spatial weighted average filters for image processing, such as mean filters, Laplace filters, etc.
 *
 * Member 			| Comment
 * --------			| --------
 * neighborhoodSize	| Element neighborhood size to be used for this filter.
 * coefficients		| Template coefficients.
 */
	template<class coefficientTemplate, class intensityTemplate>
	class WeightedAverageFilter : public TemplateFilter<coefficientTemplate, intensityTemplate> {

	public:
		/**
		 * Constructor for WeightedAverageFilter objects.
		 *
		 * Parameter	| in/out	| comment
		 * :---------	| :------	| :-------
		 * c			| INPUT		| Vector containing the template coefficients.
		 * nS			| INPUT		| Neighborhood size.
		 */
		WeightedAverageFilter(vector<FilterCoefficient<coefficientTemplate> > c, int nS) : TemplateFilter<coefficientTemplate,intensityTemplate>(c, nS) {}

		/**
		 * Destructor for WeightedAverageFilter objects.
		 */
		~WeightedAverageFilter() {};

		/**
	 	 * Gives access to SpatialTemplate::getNeighborhoodSize().
	 	 */
		int getNeighborhoodSize() const {
			return SpatialTemplate<coefficientTemplate>::getNeighborhoodSize();
		}

		/**
	 	 * Gives access to SpatialTemplate::getNCoefficients().
		 */
		int getNCoefficients() const {
			return SpatialTemplate<coefficientTemplate>::getNCoefficients();
		}

		/**
	 	 * Gives access to SpatialTemplate::getCoefficients().
		 */
		vector<FilterCoefficient<coefficientTemplate> > getCoefficients() const {
			return SpatialTemplate<coefficientTemplate>::getCoefficients();
		}

		/**
	 	 * Gives access to SpatialTemplate::getCoefficient().
		 *
		 *
		 * Parameter		| in/out	| comment
		 * :---------		| :------	| :-------
		 * coefficientIndex	| INPUT		| Position in the template coefficient vector.
		 */
		FilterCoefficient<coefficientTemplate> getCoefficient(int coefficientIndex) const {
			return SpatialTemplate<coefficientTemplate>::getCoefficient(coefficientIndex);
		}

		/**
	 	 * Gives access to SpatialTemplate::findCoefficient().
		 *
		 * Parameter		| in/out	| comment
		 * :---------		| :------	| :-------
		 * positionIndex	| INPUT		| Position index of corresponding neighbor.
		 */
		int findCoefficient(int positionIndex) const {
			return SpatialTemplate<coefficientTemplate>::findCoefficient(positionIndex);
		}

		/**
		 * Implements TemplateFilter::applyToBand().
		 *
		 * Parameter	| in/out	| comment
		 * :---------	| :------	| :-------
		 * image		| INPUT		| Input image.
		 * bandIndex	| INPUT		| Index of the band to be filtered.
		 * result		| OUTPUT	| Filtered intensity values. Needs to be of a length of at least image.nElements.
		 */
		void applyToBand(Image<intensityTemplate> image, int bandIndex, double *result) const {
			if ((bandIndex < 0) || (bandIndex >= image.getNBands())) {
				// throw error or exception
			}

			int nElements = image.getNElements();
			vector<FilterCoefficient<coefficientTemplate> > coefficients = getCoefficients();
			for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
				double filterCoefficientSum = 0;
				// center element
				int coefficientIndex = findCoefficient(-1);
				if (coefficientIndex > -1) {
					result[elementIndex] = image(elementIndex, bandIndex) * coefficients[coefficientIndex].getCoefficient();
					filterCoefficientSum += coefficients[coefficientIndex].getCoefficient();
				}
				// neighbors
				int neighborhoodSize = getNeighborhoodSize();
				vector<Neighbor> neighbors;
				image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
				int nFoundNeighbors = neighbors.size();
				for (int neighborIndex = 0; neighborIndex < nFoundNeighbors; neighborIndex++) {
					coefficientIndex = findCoefficient(neighbors[neighborIndex].getPosition());
					if (coefficientIndex > -1) {
						result[elementIndex] += image(neighbors[neighborIndex].getIndex(), bandIndex) *
												coefficients[coefficientIndex].getCoefficient();
						filterCoefficientSum += coefficients[coefficientIndex].getCoefficient();
					}
				}
				// normalization
				result[elementIndex] = result[elementIndex] / filterCoefficientSum;
			}
		}

		/**
		 * Implements TemplateFilter::applyToImage().
		 *
		 * Parameter	| in/out	| comment
		 * :---------	| :------	| :-------
		 * image		| INPUT		| Input image.
		 * result		| OUTPUT	| Filtered intensity values. Needs to be of a length of at least image.nElements * image.nBands.
		 */
		void applyToImage(Image<intensityTemplate> image, double *result) const {
			int nElements = image.getNElements();
			int nBands = image.getNBands();
			for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
				int offset = bandIndex * nElements;
				applyToBand(image, bandIndex, result + offset);
			}
		}
	};
}

#endif
