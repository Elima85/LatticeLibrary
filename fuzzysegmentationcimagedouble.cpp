#include "fuzzysegmentationcimagedouble.h"

namespace CImage {

    FuzzySegmentationCImageDouble::FuzzySegmentationCImageDouble(double *d, Lattice &l, int nB) : FuzzySegmentationCImage<double>(d,l,nB){};
    FuzzySegmentationCImageDouble::~FuzzySegmentationCImageDouble() {};

    double FuzzySegmentationCImageDouble::adjustIntensity(double intensity) const {
        return MIN(1, MAX(0, intensity));
    }
    double FuzzySegmentationCImageDouble::getApproximatedInternalDistance(int index, int band, int method) const {
        if (!isValid(index, band)) {
            throw outsideImageException();
        }

        double intensity = (*this)(index, band);
        int intensityIndex = floor(intensity * 256);
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