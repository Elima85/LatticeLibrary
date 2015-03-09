#include "crispsegmentationimage.h"

namespace LatticeLib {

    CrispSegmentationImage::CrispSegmentationImage(bool *d, Lattice &l, int nB) : BinaryImage(d, l, nB) {};
    CrispSegmentationImage::~CrispSegmentationImage() {};
}

