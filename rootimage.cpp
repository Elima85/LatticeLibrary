#include "rootcimage.h"

namespace LatticeLib {
    RootImage::RootImage(int *d, Lattice &l, int nB) : Image<double>(d, l, nB) {};
    RootImage::~RootImage() {};
}