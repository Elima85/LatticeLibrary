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
        for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
            int label = getIndexOfMinumumValue((*this)[elementIndex]);
            for (int bandIndex = 0; bandIndex < this->nBands; bandIndex++) {
                if (bandIndex == label) {
                    segmentation->setElement(elementIndex, bandIndex, true);
                }
                else {
                    segmentation->setElement(elementIndex, bandIndex, false);
                }
            }
        }
        return segmentation;
    }

}
