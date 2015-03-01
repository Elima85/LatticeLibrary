#ifndef ROOTCIMAGE_H
#define ROOTCIMAGE_H

namespace CImage{

/**
* Class for root images in inverse forest transforms.
*/
    class RootCImage : public CImage<int> {
    public:
        RootCImage(int *d, Lattice &l, int nB);
        ~DistanceCImage();
    };
}

#endif