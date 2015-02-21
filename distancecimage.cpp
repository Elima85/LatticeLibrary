#include "distancecimage.h"
#include "crispsegmentationcimage.h"
#include "fuzzysegmentationcimage.h"
#include "exception.h"
#include "vectoroperators.h"
#include "norm.h"

namespace CImage {

    DistanceCImage::DistanceCImage(double *d, Lattice &l, int nB) : CImage<double>(d, l, nB) {};
    DistanceCImage::~DistanceCImage() {};

    CrispSegmentationCImage* DistanceCImage::crispLabel() const {
        int nElements = getNElements();
        bool *labels = new bool[nElements * nBands];
        if (labels == NULL) {
            throw allocationException();
        }
        CrispSegmentationCImage *segmentation = new CrispSegmentationCImage(labels, lattice, nBands);
        for (int index = 0; index < nElements; index++) {
            segmentation->setElement(index, getIndexOfMinumumValue((*this)[index]), true);
        }
        return segmentation;
    }
    template<class T> FuzzySegmentationCImage<T>* DistanceCImage::fuzzyLabel(T minValue, T maxValue) const {
        int nElements = getNElements();
        T *labels = new T[nElements * nBands];
        if (labels == NULL) {
            throw allocationException();
        }
        FuzzySegmentationCImage<T> *segmentation = new FuzzySegmentationCImage<T>(labels, lattice, nBands, minValue, maxValue);
        T membershipRange = maxValue - minValue;
        for (int index = 0; index < nElements; index++) {
            PNorm sum(1);
            vector<double> distances = (*this)[index];
            double sumOfDistances = sum.compute(distances);
            for (int band = 0; band < nBands; band++) {
                segmentation->setElement(index,band,minValue + membershipRange/sumOfDistances * distances[band]);
            }
        }
        return segmentation;
    }

}
