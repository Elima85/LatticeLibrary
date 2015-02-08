#ifndef FUZZYSEGMENTATIONCIMAGEUINT8_H
#define FUZZYSEGMENTATIONCIMAGEUINT8_H

#include "fuzzysegmentationcimage.h"

namespace CImage {

/**
* Class for fuzzy segmentations, range: [0,255]. Each modality band is a fuzzy foreground/background segmentation.
*/
    class FuzzySegmentationCImageUint8 : public FuzzySegmentationCImage<uint8> {

    public:
        FuzzySegmentationCImageUint8(uint8 *d, Lattice &l, int nB);
        // FuzzySegmentationCImageUint8(const FuzzySegmentationCImageDouble *original);
        ~FuzzySegmentationCImageUint8();

        /**
        * Truncates the intensity value to fit into the range of the IntensityCImage object.
        *
        * Parameter     | Comment
        * :---------    | :-------
        * intensity     | intensity of a spatial element
        */
        uint8 adjustIntensity(uint8 intensity) const;

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