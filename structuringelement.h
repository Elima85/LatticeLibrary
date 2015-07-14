#ifndef STRUCTURINGELEMENT_H
#define STRUCTURINGELEMENT_H

#include "filtercoefficient.h"
#include "image.h"

namespace LatticeLib {

/**
 * Structuring element for morphological operations.
 *
 * Member 			| Comment
 * --------			| --------
 * coefficients		| filter coefficients
 * neighborhoodSize	| Size of spel neighborhood to be used for this filter.
 */
	class StructuringElement {

	private:
		/**
	 * Filter coefficients.
	 *
	 * coefficient	| meaning
	 * :-----------	| :-------
	 * true			| required to be >0
	 * false		| required to be ==0, to a precision defined in defs.h.
	 * not defined	| no requirements
	 */
		vector<FilterCoefficient<bool> > coefficients;

		/** Size of spel neighborhood to be used for this filter. */
		int neighborhoodSize;


	public:
		StructuringElement(vector<FilterCoefficient<S> > c, int nS) {
			coefficients = c;
			neighborhoodSize = nS;
		}

		~StructuringElement() { };

		/**
	 * NOT TESTED!!!
	 * Erodes a binary image (treats >0 as 1) using the provided structuring element.
	 *
	 * Template fitting:
	 *
	 * coefficient	| meaning
	 * :-----------	| :-------
	 * true			| required to be >0
	 * false		| required to be ==0
	 * not defined	| no requirements
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * image		|			| image to be eroded
	 * result		| OUTPUT	| Values of eroded image, nBands*nElements elements.
	 */
		template<class T>
		void binaryErode(Image<T> image, T *result) const {

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
	 * NOT TESTED!!!
	 * Dilates a binary image (treats >0 as 1) using the provided structuring element.
	 *
	 * Template fitting:
	 *
	 * coefficient	| index		| meaning
	 * :-----------	| :--------	| :-------
	 * true			|�center	| required to be >0
	 * false		| center	| required to be ==0
	 * true			|�other		| set to 1 if center element fits
	 * false		| other		| no effect
	 * not defined	| other		| no effect
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * filter		|			| Structuring element.
	 * result		| OUTPUT	| Values of dilated image.
	 */
		template<class T>
		void binaryDilate(Image<T> image, T *result) const {

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
	 * NOT TESTED!!!
	 * Opens the image using the provided structuring element. (erosion, dilation)
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * filter		|			| Structuring element.
	 * result		| OUTPUT	| Values of opened image.
	 */
		template<class T>
		void binaryOpen(Image<T> image, T *result) const {

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
	 * NOT TESTED!!!
	 * Closes the image using the provided structuring element.
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * filter		|			| Structuring element.
	 * nN			|			| #neighbors to use.
	 * result		| OUTPUT	| Values of closed image.
	 */
		template<class T>
		void binaryClose(Image<T> image, T *result) const {

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
	};

}


#endif
