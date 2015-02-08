#ifndef INTENSITYCIMAGEDOUBLE_H
#define INTENSITYCIMAGEDOUBLE_H

#include "intensitycimage.h"
#include "intensitycimageuint8.h"

namespace CImage {

    /**
    * Spatial domain image with double precision. Intensity range: [0,1]
    */
    class IntensityCImageDouble : public IntensityCImage<double> {

    public:
        IntensityCImageDouble(double* d, Lattice &l, int nB);
        /**
        * To enable switching to a higher precision format.
        */
        //IntensityCImageDouble(const IntensityCImageUint8 *original);
        ~IntensityCImageDouble();

        /**
        * Implements IntensityCImage::adjustIntensity().
        */
        double adjustIntensity(double intensity) const;
    };
}

#endif