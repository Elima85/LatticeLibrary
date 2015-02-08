#include "intensitycimagedouble.h"
#include "exception.h"

namespace CImage {

    IntensityCImageDouble::IntensityCImageDouble(double *d, Lattice &l, int nB) : IntensityCImage<double>(d, l, nB) {
        int nElements = getNElements();
        for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
            if ((data[elementIndex] < 0) || (data[elementIndex] > 1)) {
                throw outsideRangeException();
            }
        }
    };
    IntensityCImageDouble::~IntensityCImageDouble() {};

    double IntensityCImageDouble::adjustIntensity(double intensity) const {
        return MIN(1, MAX(0, intensity));
    }

}
