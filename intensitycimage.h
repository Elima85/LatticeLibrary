#ifndef INTENSITYCIMAGE_H
#define INTENSITYCIMAGE_H

/**
* Abstract base class for spatial domain images.
*/

#include "cimage.h"

namespace CImage {

    class IntensityCImage : public CImage<bool> {

    public:
        IntensityCImage(bool *d, Lattice &l, int nB) {};
        ~IntensityCImage();

    };

}

#endif