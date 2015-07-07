#ifndef INVERSEFORESTTRANSFORM_H
#define INVERSEFORESTTRANSFORM_H

#include "distanceimage.h"
#include "rootimage.h"

namespace LatticeLib {

    class InverseForestTransform {

    public:
        DistanceImage distanceTransform;
        RootImage roots;

        InverseForestTransform(DistanceImage dT, RootImage r);
        ~InverseForestTransform();
    };
}

#endif