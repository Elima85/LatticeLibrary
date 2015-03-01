#include "rootcimage.h"

namespace CImage {
    RootCImage::RootCImage(int *d, Lattice &l, int nB) : CImage<double>(d, l, nB) {};
    RootCImage::~RootCImage() {};
}