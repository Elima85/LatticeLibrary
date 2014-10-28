#ifndef GALETNAMN_H
#define GALETNAMN_H

#include <math.h>
#include "stdint.h"
#include <cstdio>
#include "exception.h"
#include <vector>

namespace CImage {

typedef unsigned char uint8;

// general definitions
#define EPSILONC 1 // cost epsilon
#define MAXINT 4294967295
#define EPSILOND 0.0000001 // tolerance for distance transforms
#define EPSILONI 0.0000001 // intensity epsilon
#define INF 10000000.0
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

// CC definitions
const int mirrorCC[] = {1, 0, 3, 2, 5, 4, 11, 10, 13, 12,  7,  6,  9,  8, 17, 16, 15, 14, 24, 25, 22, 23, 20, 21, 18, 19};
                      //0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25
const int nearestCC[] = {-1, -1, -1, -1, -1, -1};
					   // 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25

const int mirrorBCC[] = {7, 6, 5, 4, 3, 2, 1, 0, 13, 11, 12,  9, 10,  8};
					   //0, 1, 2, 3, 4, 5, 6, 7,  8,  9, 10, 11, 12, 13

const int mirrorFCC[] = {10, 11, 8, 9, 6, 7, 4, 5, 2, 3,  0,  1, 17, 15, 16, 13, 14, 12};
					   // 0,  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17

/**
 * Element-wise addition for vectors.
 */
template <class T>
vector<T> operator+ (const vector<T> &v1, const vector<T> &v2) {
	int length = v1.size();
	if (length != v2.size()) {
		throw dimensionMismatchException();
	}
	vector<T> result;
	for (int i = 0; i < length; i++) {
		result.push_back(v1[i] + v2[i]);
	}
	return result;
}

/**
 * Element-wise subtraction for vectors.
 */
template <class T>
vector<T> operator- (const vector<T> &v1, const vector<T> &v2) {
	int length = v1.size();
	if (length != v2.size()) {
		throw dimensionMismatchException();
	}
	vector<T> result;
	for (int i = 0; i < length; i++) {
		result.push_back(v1[i] - v2[i]);
	}
	return result;
}

/**
 * Unary minus for vectors.
 */
template <class T>
vector<T> operator-(const vector<T> &v) {
	vector<T> result;
	int length = v.size();
	for (int i = 0; i < length; i++) {
		result.push_back(-v[i]);
	}
	return result;
}

/**
 * Multiplication of constant and vector.
 */
template <class T>
vector<double> operator* (double d, const vector<T> &v) {
	vector<double> result;
	int length = v.size();
	for (int i = 0; i < length; i++) {
		result.push_back(d * v[i]);
	}
	return result;
}

/**
 * Returns a vector where result[i] = min(v1[i],v2[i]).
 */
template <class T>
vector<T> minElements(vector<T> v1, vector<T> v2) {
	int length = v1.size();
	if (length != v2.size()) {
		throw dimensionMismatchException();
	}
	vector<T> result;
	for (int i = 0; i < length; i++) {
		result.push_back(MIN(v1[i],v2[i]));
	}
	return result;
}

/**
 * Returns a vector where result[i] = max(v1[i],v2[i]).
 */
template <class T>
vector<T> maxElements(vector<T> v1, vector<T> v2) {
	int length = v1.size();
	if (length != v2.size()) {
		throw dimensionMismatchException();
	}
	vector<T> result;
	for (int i = 0; i < length; i++) {
		result.push_back(MAX(v1[i],v2[i]));
	}
	return result;
}

// to be tested
double getCost(double a, double b){
	double c = fabs(a-b)+EPSILONC;
	//double c=b; //(a+b)/2;
	c=c/(255+EPSILONC);
	c=pow(c,3);
	c=c*(255+EPSILONC);
	return c;
}

bool isEven(int i) {
	return (i % 2 == 0);
}

double length(double vec[3]){ // replace with p-norm?
	return sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
}

/**
 * Binary search algorithm, only values >= 0.
 */
int lowerBound(const double *array, int size, double val) {

	if (val < array[0]) {
		throw outsideRangeException();
	}

	if (val > array[size-1]) {
		return size-1;
	}

	int lower, upper, guess;
	bool found = false;
	lower = 0;
	upper = size-1;

	while ((lower <= upper) && !found) {
		guess = lower + 0.5*(upper-lower);
		if (array[guess] <= val) {
			if (array[guess+1] > val) {
				found = true;
			}
			else {
				lower = guess;
			}
		}
		else {
			upper = guess;
		}
	}
	return guess;
}

/*
 * Allocates and returns an array with the values read from the input file.
 *
 * Must be paired with delete[]!
 */
// to be tested
double* readVolume(const char *path, int nTot) {

	FILE *f = fopen(path, "r");
	if (f == NULL) {
		throw fileException();
	}
	double *vol = new double[nTot];
	if (!vol) {
		throw allocationException();
	}

	int r, rTot = 0;
	while (!feof( f ) && (r = fread(vol + rTot, sizeof(double), MIN(2048,nTot-rTot), f)) > 0)
		rTot += r;
	fclose(f);
	return vol;
}

/*
 * Writes the input array to the input file.
 */
// to be tested
void writeVolume(const char *path, const double *values, const int nTot)
{
	FILE *f = fopen(path, "wb");
	if (f == NULL) {
		throw fileException();
	}
	fwrite(values,sizeof(double),nTot,f);
	fclose(f);
}

}
#endif
