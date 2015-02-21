#ifndef DISTANCECIMAGE_H
#define DISTANCECIMAGE_H

#include "cimage.h"

namespace CImage {

/**
* Class for distance transforms of images.
*/
    class DistanceCImage : public CImage<double> {

    public:
        DistanceCImage(double *d, Lattice &l, int nB);
        ~DistanceCImage();

    };

}

#endif