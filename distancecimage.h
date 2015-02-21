#ifndef DISTANCECIMAGE_H
#define DISTANCECIMAGE_H

#include "cimage.h"
#include "crispsegmentationcimage.h"
#include "fuzzysegmentationcimage.h"

namespace CImage {

/**
* Class for distance transforms of images.
*/
    class DistanceCImage : public CImage<double> {

    public:
        DistanceCImage(double *d, Lattice &l, int nB);
        ~DistanceCImage();

        /**
        * Produces a crisp segmentation based on the distance transform.
        */
        CrispSegmentationCImage* crispLabel() const;

        /**
        * Produces a fuzzy segmentation based on the distance transform.
        *
        * Parameter     | Comment
        * :---------    | :-------
        * minValue      | value corresponding to 0% membership of a labelled class
        * maxValue      | value corresponding to 100% membership of a labelled class
        */
        template<class T>
        FuzzySegmentationCImage<T>* fuzzyLabel(T minValue, T maxValue) const;

    };

}

#endif