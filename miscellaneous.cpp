#include "miscellaneous.h"
#include "exception.h"
#include <cmath>

namespace CImage {

    double getCost(double a, double b) {
        double c = fabs(a - b) + EPSILONC;
        //double c=b; //(a+b)/2;
        c = c / (255 + EPSILONC);
        c = pow(c, 3);
        c = c * (255 + EPSILONC);
        return c;
    }

    /*bool IS_EVEN(int i) {
        return (i % 2 == 0);
    }*/

    int lowerBound(const double *array, int size, double val) {

        if (val < array[0]) {
            throw outsideRangeException();
        }

        if (val > array[size - 1]) {
            return size - 1;
        }

        int lower, upper, guess;
        bool found = false;
        lower = 0;
        upper = size - 1;

        while ((lower <= upper) && !found) {
            guess = lower + 0.5 * (upper - lower);
            if (array[guess] <= val) {
                if (array[guess + 1] > val) {
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
}