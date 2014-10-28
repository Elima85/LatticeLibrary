#ifndef SCALARFILTER_H
#define SCALARFILTER_H

#include "filter.h"

/**
 * Base class for weighted average template filters.
 *
 * Member 	| Comment
 * --------	| --------
 * nCoeffs	| #coefficients in the filter
 */
template <class S>
class ScalarFilter : public Filter<S> {

private:

public:
	ScalarFilter(int nC, int nS) : Filter<S>(nC, nS) {
	}
	virtual ~ScalarFilter() {};
	virtual vector< FilterCoefficient<S> > getCoeffs() const = 0;
	virtual FilterCoefficient<S> getCoeff(int i) const = 0;
	virtual int findCoeff(int index) const = 0;
	virtual void addCoeff(int index, S coeff) = 0;
	virtual void eraseCoeff(int index) = 0;
};

/**
 * Template filter with integer coefficients.
 *
 * Member 		| Comment
 * --------		| --------
 * coefficients	| filter coefficients
 *
 */
class IntFilter : public ScalarFilter<int> {
private:
	/** filter coefficients */
	vector< FilterCoefficient<int> > coefficients;

public:
	IntFilter(vector< FilterCoefficient<int> > c, int n) : ScalarFilter<int>(c.size(), n) {
		coefficients = c;
	}
	~IntFilter() {}

	vector< FilterCoefficient<int> > getCoeffs() const {
		return coefficients;
	}

	FilterCoefficient<int> getCoeff(int i) const {
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

	void addCoeff(int index, int coeff) {
		coefficients.push_back(FilterCoefficient<int>(index,coeff));
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
};

/**
 * Template filter with double coefficients.
 *
 * Member 		| Comment
 * --------		| --------
 * coefficients	| filter coefficients
 *
 */
class DoubleFilter : public ScalarFilter<double> {
private:
	/** filter coefficients */
	vector< FilterCoefficient<double> > coefficients;

public:
	DoubleFilter(vector< FilterCoefficient<double> > c, int n) : ScalarFilter<double>(c.size(), n) {
		coefficients = c;
	}
	~DoubleFilter() {}

	vector< FilterCoefficient<double> > getCoeffs() const {
		return coefficients;
	}

	FilterCoefficient<double> getCoeff(int i) const {
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

	void addCoeff(int index, double coeff) {
		coefficients.push_back(FilterCoefficient<double>(index,coeff));
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
};




#endif
