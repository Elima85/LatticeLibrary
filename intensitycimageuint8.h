#ifndef INTENSITYCIMAGEUINT8_H
#define INTENSITYCIMAGEUINT8_H

#include "intensitycimage.h"

namespace CImage {

    /**
    * Spatial domain image with double precision. Intensity range: [0,1]
    */
    class IntensityCImageUint8 : public IntensityCImage<uint8> {

    public:
        IntensityCImageUint8(uint8 *d, Lattice &l, int nB);

        ~IntensityCImageUint8();

        /**
        * Implements IntensityCImage::adjustIntensity().
        */
        uint8 adjustIntensity(uint8 intensity);
    };
}

#endif