#ifndef VECTOROPERATORS_H
#define VECTOROPERATORS_H

#include <vector>
#include "exception.h"
#include "defs.h"

namespace LatticeLib {

    template<class T>
    vector <T> operator+(const vector <T> &v1, const vector <T> &v2) {
        int length = v1.size();
        if (length != v2.size()) {
            throw dimensionMismatchException();
        }
        vector <T> result;
        for (int i = 0; i < length; i++) {
            result.push_back(v1[i] + v2[i]);
        }
        return result;
    }

    template<class T>
    vector <T> operator-(const vector <T> &v1, const vector <T> &v2) {
        int length = v1.size();
        if (length != v2.size()) {
            throw dimensionMismatchException();
        }
        vector <T> result;
        for (int i = 0; i < length; i++) {
            result.push_back(v1[i] - v2[i]);
        }
        return result;
    }

    template<class T>
    vector <T> operator-(const vector <T> &v) {
        vector <T> result;
        int length = v.size();
        for (int i = 0; i < length; i++) {
            result.push_back(-v[i]);
        }
        return result;
    }

    template<class T>
    vector<double> operator*(double d, const vector <T> &v) {
        vector<double> result;
        int length = v.size();
        for (int i = 0; i < length; i++) {
            result.push_back(d * v[i]);
        }
        return result;
    }

    template<class T>
    vector <T> minElements(vector <T> v1, vector <T> v2) {
        int length = v1.size();
        if (length != v2.size()) {
            throw dimensionMismatchException();
        }
        vector <T> result;
        for (int i = 0; i < length; i++) {
            result.push_back(MIN(v1[i], v2[i]));
        }
        return result;
    }

    template<class T>
    vector <T> maxElements(vector <T> v1, vector <T> v2) {
        int length = v1.size();
        if (length != v2.size()) {
            throw dimensionMismatchException();
        }
        vector <T> result;
        for (int i = 0; i < length; i++) {
            result.push_back(MAX(v1[i], v2[i]));
        }
        return result;
    }

    template<class T>
    int getIndexOfMinumumValue(vector<T> v) {
        int length = v.size();
        int index;
        double minValue = INF;
        for (int i = 0; i < length; i++) {
            if (v[i] < minValue) {
                minValue = v[i];
                index = i;
            }
        }
        return index;
    }

    template<class T>
    T sumOfElements(vector<T> v) {
        int length = v.size();
        T sum = 0;
        for (int i = 0; i < length; i++) {
            sum += v[i];
        }
        return sum;
    }

    template<class T>
    void printVector(vector<T> v) {
        int nElements = v.size();
        cout << "(" << v[0];
        for (int i = 1; i < nElements; i++){
            cout << ", " << v[i];
        }
        cout << ")" << endl;
    }
}
#endif