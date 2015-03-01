#ifndef BINARYCIMAGE_H
#define BINARYCIMAGE_H

/**
* A binary image, for crisp segmentations, morphology, etc.
*/

#include "cimage.h"

namespace CImage {

    class BinaryCImage : public CImage<bool> {

    public:
        BinaryCImage(bool* d, Lattice &l, int nB);
        BinaryCImage(const BinaryCImage &original);
        ~BinaryCImage();

    };

}

#endif