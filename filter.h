#ifndef FILTER_H
#define FILTER_H

#include <vector>

using namespace std;

/**
 * Filter coefficient for template filters.
 *
 * Member 		| Comment
 * --------		| --------
 * index		| index of the corresponding neighbor (-1 for midpoint?)
 * coefficient	| filter coefficient for this neighbor
 *
 */
template <class S>
class FilterCoefficient{

private:
	/** index of the corresponding neighbor */
	int index;

	/** filter coefficient for this neighbor */
	S factor;

public:
	FilterCoefficient(int i, S f) {
		index = i;
		factor = f;
	}
	FilterCoefficient() {
		index = 0;
		factor = 0;
	}

	double getIndex() const {
		return index;
	}

	S getFactor() const {
		return factor;
	}

	void setIndex(int i) {
		index = i;
	}

	void setFactor(S f) {
		factor = f;
	}

	void set(int i, S f) {
		index = i;
		factor = f;
	}
};

/**
 * Abstract base class for template filters.
 *
 * Member 			| Comment
 * --------			| --------
 * neighborhoodSize	| Size of spel neighborhood to be used for this filter.
 *
 */
template <class S>
class Filter {

private:
	/** Size of spel neighborhood to be used for this filter. */
	int neighborhoodSize;

	/** #coefficients in the filter */
	int nCoeffs;

protected:

	/**
	 * Sets neighborhoodSize.
	 *
	 * Parameter	| comment
	 * :---------	| :-------
	 * nS			| new neighborhoodSize
	 */
	void setNeighborhoodSize(int nS) {
		neighborhoodSize = nS;
	}

	/**
	 * Sets nCoeffs.
	 *
	 * Parameter	| comment
	 * :---------	| :-------
	 * nC			| new nCoeffs
	 */
	void setNCoeffs(int nC) {
		nCoeffs = nC;
	}

	/**
	 * Increases nCoeffs by 1.
	 */
	void incNCoeffs() {
		nCoeffs++;
	}

	/**
	 * Decreases nCoeffs by 1.
	 */
	void decNCoeffs() {
		nCoeffs--;
	}

public:
	Filter(int nC, int nS) {
		nCoeffs = nC;
		neighborhoodSize = nS;
	}

	/**
	 * Returns neighborhoodSize.
	 */
	int getNeighborhoodSize() const {
		return neighborhoodSize;
	}

	/**
	 * Returns the coefficient vector.
	 */
	virtual vector< FilterCoefficient<S> > getCoeffs() const = 0;

	/**
	 * Returns i:th FilterCoefficient from the coefficient vector.
	 *
	 * Parameter	| comment
	 * :---------	| :-------
	 * i			| position in coefficient vector
	 */
	virtual FilterCoefficient<S> getCoeff(int i) const = 0;

	/**
	 * Finds the position of the coefficient corresponding to the neighbor with the input index. Returns -1 if this neighbor does not have a coefficient.
	 *
	 * Parameter	| comment
	 * :---------	| :-------
	 * index		| index of corresponding neighbor
	 */
	virtual int findCoeff(int index) const = 0;

	/**
	 * Returns nCoeffs.
	 */
	int getNCoeffs() const {
		return nCoeffs;
	}

	/**
	 * Adds a coefficient at the end of the coefficient vector.
	 *
	 * Parameter	| comment
	 * :---------	| :-------
	 * index		| index of corresponding neighbor
	 * coeff		| coefficient
	 */
	virtual void addCoeff(int index, S coeff) = 0;

	/**
	 * Removes the coefficient corresponding to a neighbor.
	 *
	 * Parameter	| comment
	 * :---------	| :-------
	 * index		| index of corresponding neigbhbor
	 */
	virtual void eraseCoeff(int index) = 0;

	virtual ~Filter() {};
};

#endif
