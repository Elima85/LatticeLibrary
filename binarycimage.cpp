#include "binarycimage.h"

namespace CImage{

    BinaryCImage::BinaryCImage(bool* d, Lattice &l, int nB) : CImage<bool>(d, l, nB) {};
    BinaryCImage::~BinaryCImage(){};
}

