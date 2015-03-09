#ifndef BINARYIMAGE_H
#define BINARYIMAGE_H

/**
* A binary image, for crisp segmentations, morphology, etc.
*/

#include "image.h"

namespace LatticeLib {

    class BinaryImage : public Image<bool> {

    public:
        BinaryImage(bool* d, Lattice &l, int nB);
        BinaryImage(const BinaryImage &original);
        ~BinaryImage();

    };

}

#endif