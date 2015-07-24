#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>
using namespace std;

namespace LatticeLib {

/**
* Exception thrown when attempting to access something outside of the specified limits.
*/
    struct outOfRangeException : public exception {
        const char *what() const throw() {
            return "The input value is outside of the specified range.";
        }
    };

/**
* Exception thrown when the parameters given to a function or method are not compatible.
*/
    struct incompatibleParametersException : public exception {
        const char *what() const throw() {
            return "The input parameters do not fulfill the requirements.";
        }
    };

}

#endif
