#ifndef STRUCTURINGELEMENT_H
#define STRUCTURINGELEMENT_H

#include "filter.h"
#include "cimage.h"

/**
 * Structuring element for morphological operations.
 *
 * Member 		| Comment
 * --------		| --------
 * coefficients	| filter coefficients
 */
class StructuringElement : public Filter<bool> {

private:
	/** filter coefficients */
	vector< FilterCoefficient<bool> > coefficients;


public:
	// Constructor
	StructuringElement(vector< FilterCoefficient<bool> > c, int n) : Filter<bool>(c.size(),n) {
		coefficients = c;
	}

	vector< FilterCoefficient<bool> > getCoeffs() const {
		return coefficients;
	}

	FilterCoefficient<bool> getCoeff(int i) const{
		return coefficients[i];
	}

	int findCoeff(int index) const {
		int result = -1;
		int nC = this->getNCoeffs();
		for (int i = 0; i < nC; i++) {
			if (coefficients[i].getIndex() == index) {
				result = i;
			}
		}
		return result;
	}

	void addCoeff(int index, bool coeff) {
		coefficients.push_back(FilterCoefficient<bool>(index,coeff));
		this->incNCoeffs();
	}

	void eraseCoeff(int index) {
		int nC = this->getNCoeffs();
		for (int i = 0; i < nC; i++) {
			if (coefficients[i].getIndex() == index) {
				coefficients.erase(coefficients.begin() + i);
				this->decNCoeffs();
			}
		}
	}

	~StructuringElement() {}

	/**
	 * NOT TESTED!!!
	 * Erodes a binary image (treats >0 as 1) using the provided structuring element.
	 *
	 * Template fitting:
	 *
	 * coefficient	| meaning
	 * :-----------	| :-------
	 * true			|Êrequired to be >0
	 * false		| required to be ==0
	 * not defined	| no requirements
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * image		|			| image to be eroded
	 * result		| OUTPUT	| Values of eroded image, nBands*nElements elements.
	 */
	template <class T>
	void binaryErode(CImage<T> image, T* result) const {

		int nNeighbors = getNeighborhoodSize();
		vector<Neighbor> neighbors;
		T* data = image.getData();
		int nBands = image.getNBands();
		int nElements = image.getNElements();
		int localNNeighbors, nID, position, start;
		bool fit = true;
		T newVal;

		for (int b = 0; b < nBands; b++) {
			start = b * nElements; // start of modality band b
			for (int i = 0; i < nElements; i++) {
				// get neighbors
				image.getNeighbors(start + i,nNeighbors,neighbors);
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
	 * true			|Êcenter	| required to be >0
	 * false		| center	| required to be ==0
	 * true			|Êother		| set to 1 if center element fits
	 * false		| other		| no effect
	 * not defined	| other		| no effect
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * filter		|			| Structuring element.
	 * result		| OUTPUT	| Values of dilated image.
	 */
	void binaryDilate(StructuringElement filter, T* result) const {

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
				this->getNeighbors(start + i,nNeighbors,neighbors);
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
	void binaryOpen(StructuringElement filter, T* result) const {

		// erosion
		T erosion[this->getNElements()*this->getNBands()];
		this->binaryErode(filter,erosion); // Does this really work? erosion is on stack!

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
				this->getNeighbors(start + i,nNeighbors,neighbors);
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
	void binaryClose(StructuringElement filter, int nN, T* result) const {

		// dilation
		T dilation[this->getNElements()*this->getNBands()];
		this->binaryDilate(filter,dilation); // Does this really work? dilation is on stack!

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
				this->getNeighbors(start + i,nNeighbors,neighbors);
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
						fit = (filter.getCoeff(position).getFactor() == (dilation[start + neighbors[n].getIndex()] > 0));
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




#endif
