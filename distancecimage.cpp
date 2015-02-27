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

}
