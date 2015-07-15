#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "image.h"
#include "intensityworkset.h"
#include "lattice.h"
#include "vectoroperators.h"
#include <cmath>
#include <stdio.h>

namespace LatticeLib {

    /**
     * Class for segmenting Image data based on the result of a SeededDistanceTransform.
     */
    class Segmentation {
    public:
        /**
         * Crisp segmentation, based on a distance transform. Each modality band in the output image corresponds to a label.
         * Each spel belongs to exactly one layer, in which its value is 'true'.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :-----    |:-------
         * distanceTransform    | INPUT     | Distance transform on which to base the segmentation.
         * segmentation         | OUTPUT    | Resulting segmentation. Must have the same lattice and number of modality bands as distanceTransform.
         */
        void crisp(Image<double> distanceTransform, Image<bool> segmentation) {
            if (distanceTransform.getLattice() != segmentation.getLattice()) {
                // throw error
            }
            if (distanceTransform.getNBands() != segmentation.getNBands()) {
                // throw error
            }

            int nElements = distanceTransform.getNElements();
            int nBands = distanceTransform.getNBands();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                vector<double> distances = distanceTransform[elementIndex];
                vector<bool> labels(nBands, false);
                labels.at(getIndexOfMinimumValue(distances)) = true;
                segmentation.setElement(elementIndex,labels);
            }
        }

        /**
         * Fuzzy segmentation, based on a distance transform. Each modality band in the output image corresponds to a
         * label. The sum of the intensities of each spel is segmentation.maxIntensity. The intensity of a spel in a
         * band corresponds to its degree of membership, in the range [minIntensity,maxIntensity] to that label. The
         * accumulated round off error is added in favour of the last label, to make the labels sum up correctly.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :-----    |:-------
         * distanceTransform    | INPUT     | Distance transform on which to base the segmentation.
         * segmentation         | OUTPUT    | Resulting segmentation. Must have the same lattice and number of modality bands as distanceTransform.
         */
        template <class T>
        void fuzzy(Image<double> distanceTransform, IntensityWorkset<T> segmentation) {
            if (distanceTransform.getLattice() != segmentation.getImage().getLattice()) {
                // throw error
            }
            if (distanceTransform.getNBands() != segmentation.getImage().getNBands()) {
                // throw error
            }

            int nElements = distanceTransform.getNElements();
            int nLabels = distanceTransform.getNBands();
            T minCoverage = segmentation.getMinIntensity();
            T maxCoverage = segmentation.getMaxIntensity();
            T coverageRange = maxCoverage - minCoverage;
            double radius = cbrt(3/(4 * PI) * segmentation.getImage().getLattice().getScaleFactor()); // approximate the spel by a sphere
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                vector<double> distances = distanceTransform[elementIndex];
                int nearestLabel = getIndexOfMinimumValue(distances);
                double smallestDistance = distances[nearestLabel];
                vector<int> competingLabels;
                int nCompetingLabels = 0;
                vector<double> competingClaims;
                double sumOfClaims = 0.0;
                for (int labelIndex = 0; labelIndex < nLabels; labelIndex++) {
                    segmentation.getImage().setElement(elementIndex, labelIndex, minCoverage); // initialize to no label
                    double claim = radius - (distances[labelIndex] - smallestDistance);
                    if (claim > 0.0) { // part of the spel is closer to labelIndex than to nearestLabel
                        competingLabels.push_back(labelIndex);
                        competingClaims.push_back(claim);
                        sumOfClaims += claim;
                        nCompetingLabels++;
                    }
                }
                double normalizationFactor = 1/sumOfClaims;
                T accumulatedCoverage = 0;
                for (int labelIndex = 0; labelIndex < (nCompetingLabels - 1); labelIndex++) {
                    T coverage = T(minCoverage + coverageRange * normalizationFactor * competingClaims[labelIndex]);
                    segmentation.getImage().setElement(elementIndex,competingLabels[labelIndex],coverage);
                    accumulatedCoverage += (coverage - minCoverage);
                }
                // This favours the last label, as the accumulated round-off error, which may be as much as nBands, is added to its coverage value, but it's the only idea I've got right now.
                segmentation.getImage().setElement(elementIndex, competingLabels[nCompetingLabels - 1], maxCoverage - accumulatedCoverage);
            }
        }
    };
}

#endif //SEGMENTATION_H
