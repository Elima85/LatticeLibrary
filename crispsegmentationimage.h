#ifndef CRISPSEGMENTATIONIMAGE_H
#define CRISPSEGMENTATIONIMAGE_H

#include "binaryimage.h"

namespace LatticeLib {

    class CrispSegmentationImage : public BinaryImage {

    public:
        CrispSegmentationImage(bool *d, Lattice &l, int nB);
        ~CrispSegmentationImage();

    };
}

#endif