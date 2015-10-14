#ifndef LATTICELIBRARY_STRUCTURINGELEMENT_H
#define LATTICELIBRARY_STRUCTURINGELEMENT_H

#include "filtercoefficient.h"
#include "spatialtemplate.h"
#include "image.h"
#include <cmath>

namespace LatticeLib {

/**
 * Structuring Element
 * ====================
 * Structuring element for morphological operations.
 *
 * Member 			| Comment
 * --------			| --------
 * neighborhoodSize	| Element neighborhood size to be used for this filter.
 * coefficients		| Template coefficients.
 */
	class StructuringElement : public SpatialTemplate<bool> {

	public:
		/**
		 * Constructor for StructuringElement objects.
		 *
		 * Parameter	| in/out	| comment
		 * :---------	| :------	| :-------
		 * c			| INPUT		| Vector containing the template coefficients.
		 * nS			| INPUT		| Neighborhood size.
		 */
		StructuringElement(vector<FilterCoefficient<bool> > c, int nS) : SpatialTemplate<bool>(c, nS) { }

		/**
		 * Destructor for StructuringElement objects.
		 */
		~StructuringElement() { };

		/**
		 * Erodes the specified band of an image, using the provided structuring element.
		 *
		 * coefficient value	| meaning
		 * :-----------------	| :-------
		 * true					| Required to be foreground.
		 * false				| Required to be background.
		 * not defined			| No requirements.
		 *
		 * Parameter			| in/out	| Comment
		 * :----------			| :-------	| :--------
		 * image				| INPUT		| Image to be eroded.
		 * bandIndex			| INPUT		| Index of the band to dilate.
		 * backgroundIntensity	| INPUT		| Elements of this intensity are regarded as belonging to the background.
	 	 * result				| OUTPUT	| Result image. Needs to be of the same dimensions as the input image.
		 */
		template<class intensityTemplate>
		void binaryErodeBand(Image<intensityTemplate> image, int bandIndex, intensityTemplate backgroundIntensity,
							 Image<intensityTemplate> result) const {
			if (image.getLattice() != result.getLattice()) {
				throw incompatibleParametersException();
			}

			int nNeighbors = getNeighborhoodSize();
			int nElements = image.getNElements();
			for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
				int position = findCoefficient(-1);
				bool fit = true;
				if (position != -1) {
					// check if the origin element fits
					if ((getCoefficient(position).getCoefficient()) ==
						(fabs(image(elementIndex, bandIndex) - backgroundIntensity) > EPSILON)) {
						vector<Neighbor> neighbors;
						image.getNeighbors(elementIndex, nNeighbors, neighbors);
						int localNNeighbors = neighbors.size();
						// check if the neighbor elements fit
						for (int neighborIndex = 0; neighborIndex < localNNeighbors; neighborIndex++) {
							int neighborPosition = neighbors[neighborIndex].getPosition();
							position = findCoefficient(neighborPosition);
							if (position != -1) {
								if ((getCoefficient(position).getCoefficient()) !=
										(fabs(image(neighbors[neighborIndex].getElementIndex(), bandIndex) -
										 image(elementIndex, bandIndex)) < EPSILON)) {
									fit = false;
								}
							}
						}
					}
					else {
						fit = false;
					}
					if (fit) { // set to the same value as the input element
						result.setElement(elementIndex, 0, image(elementIndex, bandIndex));
					}
					else { // set to background
						result.setElement(elementIndex, 0, backgroundIntensity);
					}
				}
			}
		}

		/**
		 * Erodes an image, one band at a time, using the provided structuring element.
		 *
		 * coefficient value	| meaning
		 * :-----------------	| :-------
		 * true					| Required to be foreground.
		 * false				| Required to be background.
		 * not defined			| No requirements.
		 *
		 * Parameter			| in/out	| Comment
		 * :----------			| :-------	| :--------
		 * image				| INPUT		| Image to be eroded.
		 * backgroundIntensity	| INPUT		| Elements of this intensity are regarded as belonging to the background.
	 	 * result				| OUTPUT	| Result image. Needs to be of the same dimensions as the input image.
		 */
		template<class intensityTemplate>
		void binaryErodeImage(Image<intensityTemplate> image, intensityTemplate backgroundIntensity,
							 Image<intensityTemplate> result) const {
			if ((image.getNBands() != result.getNBands()) || image.getLattice() != result.getLattice()) {
				throw incompatibleParametersException();
			}
			//std::cout << "Inside binaryErodeImage." << std::endl;
			int nNeighbors = getNeighborhoodSize();
			int nElements = image.getNElements();
			int nBands = image.getNBands();
			for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
				//std::cout << "eroding band " << bandIndex << std::endl;
				intensityTemplate *outputBandData = result.getBand(bandIndex);
				Image<intensityTemplate> resultBand(outputBandData, image.getLattice(), 1);
				binaryErodeBand(image, bandIndex, backgroundIntensity, resultBand);
			}
		}

		/**
		 * Dilates the specified band of an image, using the provided structuring element.
		 *
		 * Template fitting:
		 *
		 * coefficient value	| location	| meaning
		 * :-----------------	| :--------	| :-------
		 * true					| origin	| Required to be in foreground.
		 * false				| origin	| Required to be in background.
		 * true					| other		| Set to the same intensity as the origin element, if the origin element fits.
		 * false				| other		| No effect.
		 * not defined			| other		| No effect.
		 *
		 * Parameter			| in/out	| Comment
		 * :----------			| :-------	| :--------
		 * filter				| INPUT		| Structuring element.
		 * backgroundIntensity	| INPUT		| Elements of this intensity are regarded as belonging to the background.
		 * bandIndex			| INPUT		| Index of the band to dilate.
	 	 * result				| OUTPUT	| Result image. Needs to be of the same dimensions as the input image.
		 */
		template<class intensityTemplate>
		void binaryDilateBand(Image<intensityTemplate> image, intensityTemplate backgroundIntensity, int bandIndex,
							  Image<intensityTemplate> result) const {
			if ((image.getNBands() != result.getNBands()) || image.getLattice() != result.getLattice()) {
				throw incompatibleParametersException();
			}

			int nNeighbors = getNeighborhoodSize();
			int nBands = image.getNBands();
			int nElements = image.getNElements();
			for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
				int position = findCoefficient(-1);
				bool fit = true;
				if (position != -1) {
					// check if the origin element fits
					if ((getCoefficient(position).getCoefficient()) !=
						(fabs(image(elementIndex, bandIndex) - backgroundIntensity) > EPSILON)) {
						fit = false;
					}
					if (fit) { // spread element intensity to specified neighbors
						vector<Neighbor> neighbors;
						image.getNeighbors(elementIndex, nNeighbors, neighbors);
						int localNNeighbors = neighbors.size();
						for (int neighborIndex = 0; neighborIndex < localNNeighbors; neighborIndex++) {
							int neighborPosition = neighbors[neighborIndex].getPosition();
							position = findCoefficient(neighborPosition);
							if (position != -1) {
								if (getCoefficient(position).getCoefficient()) {
									result.setElement(elementIndex, bandIndex, image(elementIndex, bandIndex));
								}
							}
						}
					}
				}
			}
		}

		/**
		 * Dilates an image, one band at a time, using the provided structuring element.
		 *
		 * Template fitting:
		 *
		 * coefficient value	| location	| meaning
		 * :-----------------	| :--------	| :-------
		 * true					| origin	| Required to be in foreground.
		 * false				| origin	| Required to be in background.
		 * true					| other		| Set to the same intensity as the origin element, if the origin element fits.
		 * false				| other		| No effect.
		 * not defined			| other		| No effect.
		 *
		 * Parameter			| in/out	| Comment
		 * :----------			| :-------	| :--------
		 * image				| INPUT		| Image to be eroded.
		 * backgroundIntensity	| INPUT		| Elements of this intensity are regarded as belonging to the background.
	 	 * result				| OUTPUT	| Result image. Needs to be of the same dimensions as the input image.
		 */
		template<class intensityTemplate>
		void binaryDilateImage(Image<intensityTemplate> image, intensityTemplate backgroundIntensity,
							  Image<intensityTemplate> result) const {
			if ((image.getNBands() != result.getNBands()) || image.getLattice() != result.getLattice()) {
				throw incompatibleParametersException();
			}
			int nNeighbors = getNeighborhoodSize();
			int nElements = image.getNElements();
			int nBands = image.getNBands();
			for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
				intensityTemplate *inputBandData = image.getBand(bandIndex);
				intensityTemplate *outputBandData = result.getBand(bandIndex);
				Image<intensityTemplate> imageBand(inputBandData, image.getLattice(), 1);
				Image<intensityTemplate> resultBand(outputBandData, image.getLattice(), 1);
				binaryDilateBand(imageBand, backgroundIntensity, bandIndex, resultBand);
			}
		}
	};
}

#endif
