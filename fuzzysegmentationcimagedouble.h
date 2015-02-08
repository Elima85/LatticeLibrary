#ifndef FUZZYSEGMENTATIONCIMAGEDOUBLE_H
#define FUZZYSEGMENTATIONCIMAGEDOUBLE_H

#include "fuzzysegmentationcimage.h"

namespace CImage {

/**
* Class for fuzzy segmentations, range: [0,1]. Each modality band is a fuzzy foreground/background segmentation.
*/
    class FuzzySegmentationCImageDouble : public FuzzySegmentationCImage<double> {

    public:
        FuzzySegmentationCImageDouble(double *d, Lattice &l, int nB);
        // FuzzySegmentationCImageDouble(const FuzzySegmentationCImageUint8 *original);
        ~FuzzySegmentationCImageDouble();

        /**
        * Truncates the intensity value to fit into the range of the IntensityCImage object.
        *
        * Parameter     | Comment
        * :---------    | :-------
        * intensity     | intensity of a spatial element
        */
        double adjustIntensity(double intensity) const;

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
        double getApproximatedInternalDistance(int index, int band, int method) const;

    };

}

#endif