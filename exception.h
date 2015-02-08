#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>
using namespace std;

namespace CImage {

/**
* Exception thrown when trying to access a spel that is not within the image.
*/
    struct outsideImageException : public exception {
        const char* what () const throw () {
            return "Spatial element is not within the image.";
        }
    };

/**
* Exception thrown when trying to use a neighborhood that is not defined for the image sampling lattice.
*/
    struct neighborhoodSizeException : public exception {
        const char* what () const throw () {
            return "Incorrect neighborhood size for this type of image.";
        }
    };

/**
* Exception thrown when an index or a searched-for value is outside of the searchable range.
*/
    struct outsideRangeException : public exception {
        const char* what () const throw () {
            return "Input value is outside of the defined range.";
        }
    };

/**
* Exception thrown at null pointer input. NOT TESTED!!!
*/
    struct nullPointerException : public exception {
        const char* what () const throw () {
            return "Input pointer is NULL.";
        }
    };

/**
* Exception thrown when allocation fails. NOT TESTED!!!
*/
    struct allocationException : public exception {
        const char* what () const throw () {
            return "Allocation failed.";
        }
    };

/**
* Exception thrown when a file is not opened. NOT TESTED!!!
*/
    struct fileException : public exception {
        const char* what () const throw () {
            return "File could not be opened.";
        }
    };

/**
* Exception thrown when argument dimensions do not match. NOT TESTED!!!
*/
    struct dimensionMismatchException : public exception {
        const char* what () const throw () {
            return "Dimensions do not match.";
        }
    };

/**
* Exception thrown when an object is not properly initialized for usage in the called function or method. NOT TESTED!!!
*/
    struct notInitializedException : public exception {
        const char* what () const throw () {
            return "Calling object is not initialized.";
        }
    };

    /**
    * Exception thrown when the input image is too small to be downsampled to the desired resolution. NOT TESTED!!!
    */
    struct downsampleException : public exception {
        const char* what() const throw() {
            return "Input image cannot be downsampled to this resolution.";
        }
    };

}

#endif
