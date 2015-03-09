#ifndef INVERSEFORESTTRANSFORM_H
#define INVERSEFORESTTRANSFORM_H

#include "intensityimage.h"
#include "distanceimage.h"
#include "rootimage.h"
#include "distancemeasure.h"

namespace LatticeLib {

    template <class T>
    class InverseForestTransform {

    public:
        IntensityImage<T> &image;
        DistanceImage distanceTransform;
        RootImage roots;

        InverseForestTransform(IntensityImage<T> &input, int nLabels) {
            image = input;
            double *distanceValues = new double(image.getNElements() * nLabels);
            distanceTransform(distanceValues, image.getLattice(), nLabels);
            int *rootValues = new int(image.getNElements() * nLabels);
            roots(rootValues, image.getLattice(), nLabels);
        }
        ~InverseForestTransform();

        compute(DistanceMeasure *distanceMeasure, int neighborhoodSize);
    };
}

#endif