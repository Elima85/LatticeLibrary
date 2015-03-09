#include "binaryimage.h"

namespace LatticeLib {

    BinaryImage::BinaryImage(bool* d, Lattice &l, int nB) : Image<bool>(d, l, nB) {};
    BinaryImage::BinaryImage(const BinaryImage &original) : Image<bool>(original) {};
    BinaryImage::~BinaryImage(){};
}

