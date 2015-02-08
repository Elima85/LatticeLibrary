#include "fuzzysegmentationcimageuint8.h"

namespace CImage {
    FuzzySegmentationCImageUint8::FuzzySegmentationCImageUint8(double *d, const Lattice &l, int nB) : FuzzySegmentationCImage<uint8>(d, l, nB) {};
    FuzzySegmentationCImageUint8::~FuzzySegmentationCImageUint8();

    double FuzzySegmentationCImageUint8::adjustIntensity(double intensity) const {
        return MIN(1, MAX(0, intensity));
    }
    double FuzzySegmentationCImageUint8::getApproximatedInternalDistance(int index, int band, int method) const {
        if (!isValid(index, band)) {
            throw outsideImageException();
        }
        uint8 intensity = (*this)(index, band);
        switch (method) {
            case 0:
                return 0;//lattice.internalDistanceLinear(intensityIndex);
                break;
            case 1:
                return 0;//lattice.internalDistanceBall(intensityIndex);
                break;
            case 2:
                return 0;//lattice.internalDistanceVoronoiAverage(intensityIndex);
                break;
            default:
                throw outsideRangeException();
        }
    }

}

#endif