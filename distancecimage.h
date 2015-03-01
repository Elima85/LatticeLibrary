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
        CrispSegmentationCImage crispLabel() const;

        /**
        * NOT WORKING!!!! Distance 0 leads to nan membership. Don't know how to solve memberships for object "inner" spels.
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
            FuzzySegmentationCImage<T> segmentation(labels, lattice, nBands, minValue, maxValue);
            T membershipRange = maxValue - minValue;
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                PNorm sum(1);
                vector<double> distances = (*this)[elementIndex];
                vector<double> invertedDistances;
                for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                    invertedDistances.push_back(1/(distances[bandIndex])); // TODO
                }
                double sumOfDistances = sum.compute(invertedDistances);
                for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                    // Should there be some kind of threshold value here, or something else that enables assigning 100% values to some (inner) spels?
                    segmentation.setElement(elementIndex, bandIndex, minValue + membershipRange / sumOfDistances * invertedDistances[bandIndex]);
                }
                //std::cout << "Membership of spel [" << elementIndex << "]: (" << labels[elementIndex] << "," << labels[nElements + elementIndex] << "," << labels[2*nElements + elementIndex] << ")" << std::endl;
            }
            return segmentation;
        }

    };

}

#endif