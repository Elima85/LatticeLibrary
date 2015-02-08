#ifndef INTENSITYCIMAGE_H
#define INTENSITYCIMAGE_H

#include "cimage.h"

namespace CImage {

/**
* Abstract base class for spatial domain images.
*/
    template<class T>
    class IntensityCImage : public CImage<T> {

    public:
        IntensityCImage(T *d, Lattice &l, int nB) : CImage<T>(d, l, nB) {};
        virtual ~IntensityCImage() {};

        /**
        * Truncates the intensity value to fit into the range of the IntensityCImage object.
        *
        * Parameter     | Comment
        * :---------    | :-------
        * intensity     | intensity of a spatial element
        */
        virtual T adjustIntensity(T intensity) const = 0;

    };

}

#endif