#ifndef INTENSITYCIMAGE_H
#define INTENSITYCIMAGE_H

#include "cimage.h"

namespace CImage {

/**
* Abstract base class for spatial domain images.
*/
    template<class T>
    class IntensityCImage : public CImage<T> {

    protected:
        T minValue;
        T maxValue;

    public:
        IntensityCImage(T *d, Lattice &l, int nB, T minVal, T maxVal) : CImage<T>(d, l, nB) {
            minValue = minVal;
            maxValue = maxVal;
        }
        ~IntensityCImage() {};

        /**
        * Truncates the intensity value to fit into the range of the IntensityCImage object.
        *
        * Parameter     | Comment
        * :---------    | :-------
        * intensity     | intensity of a spatial element
        */
        template<class S>
        T adjustIntensity(S intensity) const {
            return MIN(maxValue, MAX(minValue, intensity));
        }

    };

}

#endif