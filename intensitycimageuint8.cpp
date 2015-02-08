#include "intensitycimageuint8.h"
#include "exception.h"

namespace CImage {

    IntensityCImageUint8::IntensityCImageUint8(uint8 *d, Lattice &l, int nB) : IntensityCImage<uint8>(d, l, nB) {};
    IntensityCImageUint8::~IntensityCImageUint8() {};

    /**
    * Implements IntensityCImage::adjustIntensity().
    */
    uint8 IntensityCImageUint8::adjustIntensity(uint8 intensity) const {
        return intensity; // The intensity range is the same as the type range, so nothing needs to be done.
    }

}
