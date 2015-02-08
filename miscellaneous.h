#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#define EPSILONC 0.0000001

namespace CImage {

// to be tested
    double getCost(double a, double b);

    /**
    * Returns true if the input value is even.
    */
    //bool IS_EVEN(int i);

/**
* Binary search algorithm, only values >= 0.
*/
    int lowerBound(const double *array, int size, double val);
}

#endif