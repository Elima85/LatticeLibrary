#ifndef PADDING_H
#define PADDING_H

#include <vector>
#include "cimage.h"
#include "neighbor.h"

using namespace std;

class Padding {

public:
	Padding() {}
	virtual ~Padding() {};
	template <class T> virtual void padNeighborhood(CImage<T> *image, int centerIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const = 0;
};

class ZeroPadding : public Padding {

public:
	ZeroPadding() : Padding() {}
	~ZeroPadding() {}

	template <class T>
	void padNeighborhood(CImage<T> *image, int centerIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const {

	}
};

class NearestNeighborPadding : public Padding {

public:
	NearestNeighborPadding() : Padding() {}
	~NearestNeighborPadding() {}

	template <class T>
	void padNeighborhood(CImage<T> *image, int centerIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const {

	}
};

class MirrorPadding : public Padding {

public:
	MirrorPadding() : Padding() {}
	~MirrorPadding() {}

	template <class T>
	void padNeighborhood(CImage<T> *image, int centerIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const {

	}
};

#endif
