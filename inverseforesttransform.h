#ifndef INVERSEFORESTTRANSFORM_H
#define INVERSEFORESTTRANSFORM_H

#include "intensitycimage.h"
#include "distancecimage.h"
#include "rootcimage.h"
#include "distancemeasure.h"

namespace CImage {

    template <class T>
    class InverseForestTransform {

    public:
        IntensityCImage<T> &image;
        DistanceCImage distanceTransform;
        RootCImage roots;

        InverseForestTransform(IntensityCImage<T> &input, int nLabels) {
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