#include "distancecimage.h"
#include "exception.h"

namespace CImage {

    DistanceCImage::DistanceCImage(double *d, Lattice &l, int nB) : CImage<double>(d, l, nB) {};
    DistanceCImage::~DistanceCImage() {};

}
