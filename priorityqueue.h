/*
 * typedef of a priority queue suited for our needs, borrowed from Filip Malm. Should be changed to using templates or type aliases or something, to match the CImage class.
 *
 * If there are several elements with the same priority value, FIFO is applied.
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <math.h>
#include <queue>
#include <vector>
#include "norm.h"
#include "defs.h"
using namespace std;

namespace CImage {

#define EPSILONPQ 0.0000001

/**
 * Queue element containing one value.
 */
template <class T>
class PriorityQueueElement{
private:
	/** element value */
	T value;

	/** element identifier*/
	long index;

public:
	/**
	 * Empty element
	 */
	PriorityQueueElement() {
		value = 0.0;
		index = 0;
	}
	/**
	 * Sets value to input value.
	 */
	PriorityQueueElement(long i, T v) {
		value = v;
		index = i;
	}
	/**
	 * Sets value to the input norm of the input vector.
	 */
	PriorityQueueElement(long i, const vector<T> &v, const Norm *n) {
		value = n->compute(v);
		index = i;
	}

	T getValue() const {
		return value;
	}

	long getIndex() const {
		return index;
	}

	bool operator== (const PriorityQueueElement& rhs) const {
		return fabs(this->value - rhs.value) < EPSILONPQ;
	}

	bool operator!= (const PriorityQueueElement& rhs) const {
		return fabs(this->value - rhs.value) > EPSILONPQ;
	}
};

/**
 * Comparison of two queue elements.
 */
class PriorityQueueElementComparison{
public:
	template <class T>
	bool operator() (const PriorityQueueElement<T>& lhs, const PriorityQueueElement<T>& rhs) const{
		return lhs.getValue() > rhs.getValue();
	}
};

// declare queue using "priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue"
// TODO: look into type aliases or something, to make some kind of typedef. This declaration is way too long. Maybe a wrapper class PriorityQueue<T> containing a private object queue?
//template <class T>
//class PriorityQueue {
//private:
//	priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
//public:
//	void push(PriorityQueueElement<T> element) {
//		queue.push(element);
//	}
//
//	PriorityQueueElement<T> pop() {
//		return queue.pop();
//	}
//
//	PriorityQueueElement<T> top() const {
//		return queue.top();
//	}
//
//	bool empty() const {
//		return queue.empty();
//	}
//}


/**
 * Queue element containing one value.
 */
class Pq1Elem{
public:
	/** element value */
	double value;

	/** element identifier*/
	long index;

	Pq1Elem(long i, double v){value=v; index=i;}

	bool operator== (const Pq1Elem& rhs) const {
		return fabs(this->value - rhs.value) < EPSILONPQ;
	}

	bool operator!= (const Pq1Elem& rhs) const {
		return fabs(this->value - rhs.value) > EPSILONPQ;
	}
};

/**
 * Comparison of two queue element containing one value.
 */
class Pq1Comp{
public:
	bool operator() (const Pq1Elem& lhs, const Pq1Elem& rhs) const{
		return lhs.value > rhs.value;
	}
};

/**
 * Priority queue for elements containing one value.
 */
typedef priority_queue<Pq1Elem, vector<Pq1Elem>, Pq1Comp> Pq1;

/**
 * Queue element containing two values.
 */
class Pq2Elem{
public:
	/** larger element value */
	double maxVal;

	/** smaller element value */
	double minVal;

	/** element identifier*/
	long index;

	Pq2Elem(long i, double min, double max){maxVal = max; minVal = min; index = i;}

	bool operator== (const Pq2Elem& rhs) const {
		return (fabs(this->maxVal - rhs.maxVal) < EPSILONPQ) && (fabs(this->minVal - rhs.minVal) < EPSILONPQ);
	}

	bool operator!= (const Pq2Elem& rhs) const {
		return (fabs(this->maxVal - rhs.maxVal) > EPSILONPQ) || (fabs(this->minVal - rhs.minVal) > EPSILONPQ);
	}
};


/**
 * Comparison of two queue element containing two values.
 */
class Pq2Comp{
public:
	bool operator() (const Pq2Elem& lhs, const Pq2Elem& rhs) const{
//		if(lhs.maxVal == rhs.maxVal){ // Not necessary for strict inequality below.
//			return lhs.minVal < rhs.minVal;
//		}
		return lhs.maxVal > rhs.maxVal; // dangerous, as this may not correspond to the smallest distance.
	}
};

/**
 * Priority queue for elements containing two values.
 */
typedef priority_queue<Pq2Elem, vector<Pq2Elem>, Pq2Comp> Pq2;


/**
 * Queue element containing an array of three elements. Used for Euclidean distance vector propagation. Change name to PqEDV?
 */
class PqVElem { // TODO: Generalize to vector<T>
public:
	/** distance vector */
	double vec[3];

	/** distance */
	double length;

	/** element identifier*/
	long index;

	PqVElem(long i, double x, double y, double z) {
		index = i;
		vec[0] = x;
		vec[1] = y;
		vec[2] = z;
		length = sqrt(x*x+y*y+z*z);
	}

/*	pqv_elem(long i, double v[3]) { // not tested
		index = i;
		double x = v[0];
		double y = v[1];
		double z = v[2];
		vec[0] = x;
		vec[1] = y;
		vec[2] = z;
		length = sqrt(x*x+y*y+z*z);
	}*/

	// BORDE HA VISS TOLERANS!!!
	bool operator== (const PqVElem& rhs) const {
		return (fabs(this->vec[0] - rhs.vec[0]) < EPSILONPQ) && (fabs(this->vec[1] - rhs.vec[1]) < EPSILONPQ) && (fabs(this->vec[2] - rhs.vec[2]) < EPSILONPQ);
	}

	bool operator!= (const PqVElem& rhs) const {
		return (fabs(this->vec[0] - rhs.vec[0]) > EPSILONPQ) || (fabs(this->vec[1] - rhs.vec[1]) > EPSILONPQ) || (fabs(this->vec[2] - rhs.vec[2]) > EPSILONPQ);
	}
};

/**
 * Comparison of two queue element containing a vector.
 */
class PqVComp { // TODO: Generalize to vector<T>
public:
	bool operator() (const PqVElem& lhs, const PqVElem& rhs) const{
		return lhs.length > rhs.length;
	}
};

/**
 * Priority queue for elements containing a vector.
 */
typedef priority_queue<PqVElem, vector<PqVElem>, PqVComp> PqV;  // TODO: Generalize to vector<T>


/**
 * Queue element containing two vector<T>.
 */
template <class T>
class Pq2VElem { // TODO: Change to better name.
private:
	/** maximum vector */
	vector<T> maxVec;

	/** minimum vector */
	vector<T> minVec;

	/** vector norm */
	Norm* vectorNorm;

	/** element identifier*/
	long index;

	/** norm of difference between the vectors */
	double differenceNorm;

public:
	Pq2VElem() {
		index = -1;
		vectorNorm = NULL;
	}
	Pq2VElem(long i, vector<T> v1, vector<T> v2, Norm* n) { // TODO: Make n const somehow!
		if (v1.size() != v2.size()) {
			throw dimensionMismatchException();
		}
		// check whether the values in v1 are actually larger than those in v2?
		index = i;
		maxVec = v1;
		minVec = v2;
		vectorNorm = n;
		differenceNorm = vectorNorm->compute(maxVec-minVec);
	}

	double computeNorm(vector<T> v) const {
		if (!vectorNorm) {
			throw notInitializedException();
		}
		return vectorNorm->compute(v);
	}
	vector<T> getMaxVector() const {
		return maxVec;
	}
	vector<T> getMinVector() const {
		return minVec;
	}
	long getIndex() const {
		return index;
	}

	double getDifferenceNorm() const {
		return differenceNorm;
	}

	bool operator== (const Pq2VElem<T>& rhs) const {
		if (this->maxVec.size() != rhs.maxVec.size()) {
			throw dimensionMismatchException();
		}
		double n1 = vectorNorm->compute(this->maxVec - rhs.maxVec);
		double n2 = vectorNorm->compute(this->minVec - rhs.minVec);
		double normDiff1 = fabs(vectorNorm->compute(maxVec) - rhs.vectorNorm->compute(rhs.maxVec));
		double normDiff2 = fabs(vectorNorm->compute(minVec) - rhs.vectorNorm->compute(rhs.minVec));
	//	std::cout << "n1 = " << n1 << ", n2 = " << n2 << std::endl;
		return ((n1 < EPSILONPQ) && (n2 < EPSILONPQ) && (normDiff1 < EPSILONPQ) && (normDiff2 < EPSILONPQ));
	}

	bool operator!= (const Pq2VElem<T>& rhs) const {
		if (this->maxVec.size() != rhs.maxVec.size()) {
			throw dimensionMismatchException();
		}
		double n1 = vectorNorm->compute(this->maxVec - rhs.maxVec);
		double n2 = vectorNorm->compute(this->minVec - rhs.minVec);
		double normDiff1 = fabs(vectorNorm->compute(maxVec) - rhs.vectorNorm->compute(rhs.maxVec));
		double normDiff2 = fabs(vectorNorm->compute(minVec) - rhs.vectorNorm->compute(rhs.minVec));
	//	std::cout << "n1 = " << n1 << ", n2 = " << n2 << std::endl;
		return ((n1 > EPSILONPQ) || (n2 > EPSILONPQ) || (normDiff1 > EPSILONPQ) || (normDiff2 > EPSILONPQ));
	}
};

/**
 * Comparison of two queue element containing a vector.
 */
class Pq2VComp { // TODO: Change to better name.
public:
	template <class T>
	bool operator() (const Pq2VElem<T>& lhs, const Pq2VElem<T>& rhs) const{
//		double rhsDiff = rhs.computeNorm(rhs.getMaxVector()-rhs.getMinVector());
//		double lhsDiff = lhs.computeNorm(lhs.getMaxVector()-lhs.getMinVector());
//		return lhsDiff > rhsDiff;
		return lhs.getDifferenceNorm() > rhs.getDifferenceNorm();
	}
};

}

#endif
