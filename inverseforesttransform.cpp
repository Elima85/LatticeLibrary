#include "inverseforesttransform.h"

namespace LatticeLib {
    InverseForestTransform::InverseForestTransform(DistanceImage dT, RootImage r) {
        distanceTransform = dT;
        roots = r;
    }
    InverseForestTransform::~InverseForestTransform() {
        delete distanceTransform;
        delete roots;
    }
}