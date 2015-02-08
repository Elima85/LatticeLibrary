#ifndef NORM_H
#define NORM_H

#include <vector>
#include <tgmath.h>
#include "defs.h"
#include <iostream> // for polish debugging

using namespace std;

namespace CImage {

class Norm { // zero-norm, sort of.
public:
	Norm() {}
	Norm(const Norm* n) {}
	virtual ~Norm() {};

	virtual double compute(vector<double> v) const = 0;
	virtual double compute(vector<int> v) const = 0;
	virtual double compute(vector<uint8> v) const = 0;
	// what I really want, but it's not allowed, and I don't have time for a nice fix:
	//template <class T> double compute(vector<T> v) const  = 0;

}; // Norm


/**
 * p-norm class, for city-block distance, Euclidean distance, etc.
 */
class PNorm : public Norm {
private:
	double p; // for pow(double base, double exponent)

public:
	PNorm(double pval) : Norm() {
		p = pval;
	}
	PNorm(const PNorm* n) : Norm(n) {
		p = n->getP();
	}
	~PNorm() {}

	double getP() const {
		return p;
	}

	template <class T>
	double computeT(vector<T> v) const {
		double sum = 0.0;
		int N = v.size();
		for (int i = 0; i < N; i++) {
			sum = sum + pow(fabs(v[i]),p);
		}
		return pow(sum,1/p);
	}
	double compute(vector<double> v) const {
		return computeT(v);
	}
	double compute(vector<int> v) const {
		return computeT(v);
	}
	double compute(vector<uint8> v) const {
		return computeT(v);
	}
};

/**
 * Product of all vector elements. Not really a norm, as it doesn't fulfill the mathematical requirements.
 */
class ProductNorm : public Norm {
public:
	ProductNorm() : Norm() {}
	ProductNorm(const ProductNorm* n) : Norm(n) {}
	~ProductNorm() {};

	template <class T>
	double computeT(vector<T> v) const {
		double product = 1.0;
		int N = v.size();
		for (int i = 0; i < N; i++) {
			product = product * fabs(v[i]);
		}
		return product;
	}
	double compute(vector<double> v) const {
		return computeT(v);
	}
	double compute(vector<int> v) const {
		return computeT(v);
	}
	double compute(vector<uint8> v) const {
		return computeT(v);
	}
};

/**
 * Element with largest magnitude.
 */
class MaximumNorm : public Norm {
public:
	MaximumNorm() : Norm() {}
	MaximumNorm(const MaximumNorm* n) : Norm(n) {}
	~MaximumNorm() {};

	template <class T>
	double computeT(vector<T> v) const {
		double maximum = -1.0;
		int N = v.size();
		for (int i = 0; i < N; i++) {
			if (fabs(v[i]) > maximum) {
				maximum = v[i];
			}
		}
		return maximum;
	}
	double compute(vector<double> v) const {
		return computeT(v);
	}
	double compute(vector<int> v) const {
		return computeT(v);
	}
	double compute(vector<uint8> v) const {
		return computeT(v);
	}
};

} // CImage

#endif
