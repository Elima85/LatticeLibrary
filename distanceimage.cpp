#include "distanceimage.h"
#include "crispsegmentationimage.h"
#include "exception.h"
#include "vectoroperators.h"
#include "norm.h"

namespace LatticeLib {

    DistanceImage::DistanceImage(double *d, Lattice &l, int nB) : Image<double>(d, l, nB) {};
    DistanceImage::~DistanceImage() {};

    CrispSegmentationImage DistanceImage::crispLabel() const {
        int nElements = getNElements();
        bool *labels = new bool[nElements * nBands];
        if (labels == NULL) {
            throw allocationException();
        }
        CrispSegmentationImage segmentation(labels, lattice, nBands);
        for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
            int label = getIndexOfMinumumValue((*this)[elementIndex]);
            for (int bandIndex = 0; bandIndex < this->nBands; bandIndex++) {
                if (bandIndex == label) {
                    segmentation.setElement(elementIndex, bandIndex, true);
                }
                else {
                    segmentation.setElement(elementIndex, bandIndex, false);
                }
            }
        }
        return segmentation;
    }

}
