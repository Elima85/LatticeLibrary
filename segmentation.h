#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "image.h"
#include "lattice.h"
#include "vectoroperators.h"
#include <cmath>

namespace LatticeLib {

    class Segmentation {

    /**
     * Crisp segmentation, based on a distance transform. Each modality band in the output image corresponds to a label.
     * Each spel belongs to exactly one layer, in which its value is 'true'.
     *
     * Parameter            | in/out    | Comment
     * :---------           | :-----    |:-------
     * distanceTransform    | in        | Distance transform on which to base the segmentation.
     * segmentation         | out       | Resulting segmentation. Must have the same lattice and number of modality
     *                      |           | bands as distanceTransform.
     */
    public:
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
                vector<T> distances = distanceTransform[elementIndex];
                for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                    segmentation.setElement(elementIndex, bandIndex, false);
                }
                segmentation.setElement(elementIndex,getIndexOfMinumumValue(distances),true);
            }
        }

        /**
         * Fuzzy segmentation, based on a distance transform. Each modality band in the output image corresponds to a
         * label. The sum of the intensities of each spel is segmentation.maxIntensity. The intensity of a spel in a
         * band corresponds to its degree of membership, in the range [minIntensity,maxIntensity] to that label.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :-----    |:-------
         * distanceTransform    | in        | Distance transform on which to base the segmentation.
         * segmentation         | out       | Resulting segmentation. Must have the same lattice and number of modality
         *                      |           | bands as distanceTransform.
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
            T coverageRange = segmentation.getMaxIntensity() - segmentation.getMinIntensity();
            double radius = cbrt(3/(4 * PI) * segmentation.getImage().getLattice().getScaleFactor()); // approximate the spel by a sphere
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                vector <T> distances = distanceTransform[elementIndex];
                int nearestLabel = distances.getIndexOfMinimumValue();
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
                vector<double> coverage = minCoverage + coverageRange * (normalizationFactor * competingClaims);
                for (int labelIndex = 0; labelIndex < nCompetingLabels; labelIndex++) {
                    segmentation.getImage().setElement(elementIndex,competingLabels[labelIndex],coverage[labelIndex]);
                }
            }
        }
    };
}

#endif //SEGMENTATION_H
