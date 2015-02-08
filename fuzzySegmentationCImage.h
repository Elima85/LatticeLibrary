#ifndef FUZZYSEGMENTATIONCIMAGE_H
#define FUZZYSEGMENTATIONCIMAGE_H

#include "intensitycimage.h"

namespace CImage {

/**
* Abstract base class for fuzzy segmentations. Each modality band is a fuzzy foreground/background segmentation.
*/
    template<class T>
    class FuzzySegmentationCImage : public IntensityCImage<T> {

    public:
        FuzzySegmentationCImage(T *d, Lattice &l, int nB) : IntensityCImage<T>(d, l, nB) {};
        virtual ~FuzzySegmentationCImage() {};

        /**
        * Truncates the intensity value to fit into the range of the IntensityCImage object.
        *
        * Parameter     | Comment
        * :---------    | :-------
        * intensity     | intensity of a spatial element
        */
        virtual T adjustIntensity(T intensity) const = 0;

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
        virtual double getApproximatedInternalDistance(int index, int band, int method) const = 0;

    };

}

#endif