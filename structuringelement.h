#ifndef LATTICELIBRARY_STRUCTURINGELEMENT_H
#define LATTICELIBRARY_STRUCTURINGELEMENT_H

#include "filtercoefficient.h"
#include "spatialtemplate.h"
#include "image.h"

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
		StructuringElement(vector<FilterCoefficient<bool> > c, int nS) : SpatialTemplate<bool> (c, nS) {}

		/**
		 * Destructor for StructuringElement objects.
		 */
		~StructuringElement() { };

		//TODO: binaryErodeBand, binaryDilateBand, binaryOpenBand, binaryCloseBand

		/**
		 * Erodes a binary image, one band at a time, (treating intensity values greater than 0 as 1) using the
		 * provided structuring element.
		 *
		 * coefficient value	| meaning
		 * :-----------------	| :-------
		 * true					| Required to be >0.
		 * false				| Required to be ==0, to a precision defined in defs.h.
		 * not defined			| No requirements.
		 *
		 * Parameter	| in/out	| Comment
		 * :----------	| :-------	| :--------
		 * image		| INPUT		| Image to be eroded.
	 	 * result		| OUTPUT	| Intensity values after erosion. Needs to be of a length of at least image.nElements * image.nBands.
		 */
		template<class T>
		void binaryErode(Image<intensityTemplate> image, intensityTemplate *result) const {

			int nNeighbors = getNeighborhoodSize();
			vector<Neighbor> neighbors;
			T *data = image.getData();
			int nBands = image.getNBands();
			int nElements = image.getNElements();
			int localNNeighbors, nID, position, start;
			bool fit = true;
			T newVal;

			for (int b = 0; b < nBands; b++) {
				start = b * nElements; // start of modality band b
				for (int i = 0; i < nElements; i++) {
					// get neighbors
					image.getNeighbors(start + i, nNeighbors, neighbors);
					localNNeighbors = neighbors.size();

					// compute new value
					// center spel
					position = findCoeff(-1);
					if (position != -1) {
						if ((getCoeff(position).getFactor() != (data[start + i] > 0))) {
							fit = false;
						}
					}
					// neighbors
					for (int n = 0; n < localNNeighbors; n++) {
						nID = neighbors[n].getLocation();
						position = findCoeff(nID);
						if (position != -1) {
							if ((getCoeff(position).getFactor() != (data[start + neighbors[n].getIndex()] > 0))) {
								fit = false;
							}
						}
					}
					if (fit) {
						result[start + i] = 1;
					}
					else {
						result[start + i] = 0;
					}
				}
			}
		}

		/**
		 * Dilates a binary image, one band at a time, (treating intensity values greater than 0 as 1) using the
		 * provided structuring element.
		 *
		 * Template fitting:
		 *
		 * coefficient value	| location	| meaning
		 * :-----------------	| :--------	| :-------
		 * true					| main		| Required to be >0.
		 * false				| main		| Required to be ==0.
		 * true					| other		| Set to 1 if main element fits.
		 * false				| other		| No effect.
		 * not defined			| other		| No effect.
		 *
		 * Parameter	| in/out	| Comment
		 * :----------	| :-------	| :--------
		 * filter		| INPUT		| Structuring element.
		 * result		| OUTPUT	| Intensity values after dilation. Needs to be of a length of at least image.nElements * image.nBands.
		 */
		template<class T>
		void binaryDilate(Image<intensityTemplate> image, intensityTemplate *result) const {

			// Memset result to 0!!!
			int nNeighbors = filter.getNeighborhoodSize();
			int locNNeighbors, nID, position;
			vector<Neighbor> neighbors;
			vector<FilterCoefficient<bool> > coeffs = filter.getCoeffs();
			bool fit = true;

			int start;
			for (int b = 0; b < nBands; b++) {
				start = b * nElements; // start of modality band b
				for (int i = 0; i < nElements; i++) {
					// get neighbors
					this->getNeighbors(start + i, nNeighbors, neighbors);
					locNNeighbors = neighbors.size();

					// compute new value
					// center spel
					position = filter.findCoeff(-1);
					if (position != -1) {
						fit = (filter.getCoeff(position).getFactor() == (data[start + i] > 0));
					}
					// neighbors
					if (fit) {
						for (int n = 0; n < locNNeighbors; n++) {
							nID = neighbors[n].getLocation();
							position = filter.findCoeff(nID);
							if (position != -1) {
								if (filter.getCoeff(position).getFactor()) {
									result[start + i] = 1;
								}
							}
						}
					}
				}
			}
		}

		/**
		 * Opens the image, one band at a time, using the provided structuring element, by applying erosion followed by
		 * dilation.
		 *
		 * Parameter	| in/out	| Comment
		 * :----------	| :-------	| :--------
		 * filter		| INPUT		| Structuring element.
		 * result		| OUTPUT	| Intensity values after opening. Needs to be of a length of at least image.nElements * image.nBands.
		 */
		template<class T>
		void binaryOpen(Image<intensityTemplate> image, intensityTemplate *result) const {

			// erosion
			T erosion[this->getNElements() * this->getNBands()];
			this->binaryErode(filter, erosion); // Does this really work? erosion is on stack!

			// dilation
			// Memset result to 0!!!
			int nNeighbors = filter.getNeighborhoodSize();
			int locNNeighbors, nID, position;
			vector<Neighbor> neighbors;
			vector<FilterCoefficient<bool> > coeffs = filter.getCoeffs();
			bool fit = true;

			int start;
			for (int b = 0; b < nBands; b++) {
				start = b * nElements; // start of modality band b
				for (int i = 0; i < nElements; i++) {
					// get neighbors
					this->getNeighbors(start + i, nNeighbors, neighbors);
					locNNeighbors = neighbors.size();

					// compute new value
					// center spel
					position = filter.findCoeff(-1);
					if (position != -1) {
						fit = (filter.getCoeff(position).getFactor() == (erosion[start + i] > 0));
					}
					// neighbors
					if (fit) {
						for (int n = 0; n < locNNeighbors; n++) {
							nID = neighbors[n].getLocation();
							position = filter.findCoeff(nID);
							if (position != -1) {
								if (filter.getCoeff(position).getFactor()) {
									result[start + neighbors[n].getIndex()] = 1;
								}
							}
						}
					}
				}
			}
		}

		/**
		 * Closes the image, one band at a time, using the provided structuring element, by applying dilation followed
		 * by erosion.
		 *
		 * Parameter	| in/out	| Comment
		 * :----------	| :-------	| :--------
		 * filter		| INPUT		| Structuring element.
		 * result		| OUTPUT	| Intensity values after closing. Needs to be of a length of at least image.nElements * image.nBands.
		 */
		template<class T>
		void binaryClose(Image<intensityTemplate> image, intensityTemplate *result) const {

			// dilation
			T dilation[this->getNElements() * this->getNBands()];
			this->binaryDilate(filter, dilation); // Does this really work? dilation is on stack!

			// erosion
			int nNeighbors = filter.getNeighborhoodSize();
			int locNNeighbors, nID, position;
			vector<Neighbor> neighbors;
			vector<FilterCoefficient<bool> > coeffs = filter.getCoeffs();
			T newVal;
			bool fit = true;

			int start;
			for (int b = 0; b < nBands; b++) {
				start = b * nElements; // start of modality band b
				for (int i = 0; i < nElements; i++) {
					// get neighbors
					this->getNeighbors(start + i, nNeighbors, neighbors);
					locNNeighbors = neighbors.size();

					// compute new value
					// center spel
					position = filter.findCoeff(-1);
					if (position != -1) {
						fit = (filter.getCoeff(position).getFactor() == (dilation[start + i] > 0));
					}
					// neighbors
					for (int n = 0; n < locNNeighbors; n++) {
						nID = neighbors[n].getLocation();
						position = filter.findCoeff(nID);
						if (position != -1) {
							fit = (filter.getCoeff(position).getFactor() ==
								   (dilation[start + neighbors[n].getIndex()] > 0));
						}
					}
					if (fit) {
						result[start + i] = 1;
					}
					else {
						result[start + i] = 0;
					}
				}
			}
		}
	};// TODO: Test!

}

#endif
