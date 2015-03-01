#ifndef DISTANCECIMAGE_H
#define DISTANCECIMAGE_H

#include "cimage.h"
#include "crispsegmentationcimage.h"
#include "fuzzysegmentationcimage.h"
#include "seed.h"

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
        FuzzySegmentationCImage<T> fuzzyLabel(T minValue, T maxValue) const {
            int nElements = getNElements();
            T *labels = new T[nElements * nBands];
            if (labels == NULL) {
                throw allocationException();
            }
//            FuzzySegmentationCImage<T> *segmentation = new FuzzySegmentationCImage<T>(labels, lattice, nBands, minValue, maxValue);
            FuzzySegmentationCImage<T> segmentation(labels, lattice, nBands, minValue, maxValue);
            T membershipRange = maxValue - minValue;
            for (int index = 0; index < nElements; index++) {
                PNorm sum(1);
                vector<double> distances = (*this)[index];
                double sumOfDistances = sum.compute(distances);
                for (int band = 0; band < nBands; band++) {
                    // Should there be some kind of threshold value here, or something else that enables assigning 100% values to some (inner) spels?
                    segmentation.setElement(index, band, minValue + membershipRange / sumOfDistances * distances[band]);
                }
            }
            return segmentation;
        }

    };

}

#endif