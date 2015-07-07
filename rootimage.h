#ifndef ROOTIMAGE_H
#define ROOTIMAGE_H

namespace LatticeLib {

/**
* Class for root images in inverse forest transforms.
*/
    class RootImage : public Image<int> {
    public:
        RootImage(int *d, Lattice &l, int nB);
        ~RootImage();
    };
}

#endif