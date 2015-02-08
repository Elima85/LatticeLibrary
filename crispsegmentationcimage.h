#ifndef CRISPSEGMENTATIONCIMAGE_H
#define CRISPSEGMENTATIONCIMAGE_H

#include "binarycimage.h"

namespace CImage {

    class CrispSegmentationCImage : public BinaryCImage {

    public:
        CrispSegmentationCImage(bool *d, Lattice &l, int nB);
        ~CrispSegmentationCImage();

    };
}

#endif