#ifndef FUZZYSEGMENTATIONCIMAGE_H
#define FUZZYSEGMENTATIONCIMAGE_H

#include "intensityimage.h"

namespace LatticeLib {

/**
* Abstract base class for fuzzy segmentations. Each modality band is a fuzzy foreground/background segmentation.
*/
    template<class T>
    class FuzzySegmentationImage : public IntensityImage<T> {

    public:
        FuzzySegmentationImage(T *d, Lattice &l, int nB, T minVal, T maxVal) : IntensityImage<T>(d, l, nB, minVal, maxVal) {};
        virtual ~FuzzySegmentationImage() {};

        /**
        * Uses the intensity value of a spel, regarded as a coverage value, to approximate the distance between the spel center and the surface that, supposedly, intersects the spel.
        *
        * Parameter	| Comment
        * :----------	| :--------
        * index   	    | spel index
        * band		    | modality band index
        * method		| Approximation method:
        * 				|	0: linear
        * 				|	1: ball
        * 				|	2: Voronoi cell average
        */
        double getApproximatedInternalDistance(int index, int band, int method) const {}

    };

}

#endif