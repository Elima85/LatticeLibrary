#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "image.h"
#include "intensityworkset.h"
#include "lattice.h"
#include "vectoroperators.h"
#include <cmath>
#include <stdio.h>
#include "exception.h"
#include "minimumvaluefinder.h"
#include "seed.h"
#include "priorityqueue.h"
#include "structuringelement.h"
#include "seededdistancemeasure.h"
#include "seededdistancetransform.h"
#include "seed.h"

namespace LatticeLib {

    /**
     * Class for segmenting Image data based on the result of a SeededDistanceTransform.
     */
    class Segmentation {
    public:
        /**
         * Crisp segmentation, based on a distance transform. Each modality band in the output image corresponds to a label.
         * Each element belongs to exactly one layer, in which its value is 'true'.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :-----    |:-------
         * distanceTransform    | INPUT     | Distance transform on which to base the segmentation.
         * segmentation         | OUTPUT    | Resulting segmentation. Must have the same lattice and number of modality bands as distanceTransform.
         */
        void crisp(Image<double> distanceTransform, Image<bool> segmentation) {
            if (distanceTransform.getLattice() != segmentation.getLattice()) {
                throw incompatibleParametersException();
            }
            if (distanceTransform.getNBands() != segmentation.getNBands()) {
                throw incompatibleParametersException();
            }

            int nElements = distanceTransform.getNElements();
            int nBands = distanceTransform.getNBands();
            MinimumValueFinder<double> valueFinder;
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                vector<double> distances = distanceTransform[elementIndex];
                vector<bool> labels(nBands, false);
                labels.at(valueFinder.getVectorElementIndex(distances)) = true;
                segmentation.setElement(elementIndex,labels);
            }
        }

        /**
         * Crisp segmentation, based on a seeded distance transform.
         *
         * Parameter        | in/out    | Comment
         * :---------       | :-----    |:-------
         * roots            | INPUT     | Roots of the seeded distance transform, on which to base the segmentation.
         * seeds            | INPUT     | Seeds used for the distance transform.
         * neighborhoodSize | INPUT     | Neighborhood size used for the distance transform.
         * segmentation     | OUTPUT    | The resulting segmentation is placed in the first modality band. Must have the same lattice as roots.
         */
        void crisp(Image<int> roots, vector< vector<Seed> >seeds, int neighborhoodSize, Image<int> segmentation) {
            if ((roots.getNBands() != 1) || (segmentation.getNBands() != 1)) {
                throw incompatibleParametersException();
            }
            // initialization
            priority_queue<PriorityQueueElement<int>, vector<PriorityQueueElement<int> >, PriorityQueueElementComparison> queue;
            int nLabels = seeds.size();
            for (int labelIndex = 0; labelIndex < nLabels; labelIndex++) {
                int nSeeds = seeds[labelIndex].size();
                for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
                    int elementIndex = seeds[labelIndex][seedIndex].getElementIndex();
                    int label = seeds[labelIndex][seedIndex].getLabel();
                    segmentation.setElement(elementIndex, 0, label);
                    queue.push(PriorityQueueElement<int>(elementIndex, label));
                }
            }
            // label propagation
            while(!queue.empty()) {
                PriorityQueueElement<int> topElement = queue.top();
                queue.pop();
                int poppedElementIndex = topElement.getIndex();
                int poppedElementLabel = topElement.getValue();
                vector<Neighbor> neighbors;
                segmentation.getNeighbors(poppedElementIndex,neighborhoodSize, neighbors);
                int nNeighbors = neighbors.size();
                for (int neighborIndex = 0; neighborIndex < nNeighbors; neighborIndex++) {
                    int neighborElement = neighbors[neighborIndex].getElementIndex();
                    if (roots(neighborElement, 0) == poppedElementIndex) {
                        segmentation.setElement(neighborElement, 0, poppedElementLabel);
                        queue.push(PriorityQueueElement<int>(neighborElement, poppedElementLabel));
                    }
                }
            }
        }

        template <class intensityTemplate, class membershipTemplate>
        void fuzzy(Image<intensityTemplate> inputImage, Image<double> distanceTransform, StructuringElement structuringElement, IntensityWorkset<membershipTemplate> fuzzySegmentation) {

            if ((inputImage.getLattice() != distanceTransform.getLattice()) || (inputImage.getLattice() != fuzzySegmentation.getImage().getLattice())) {
                throw incompatibleParametersException();
            }
            if (distanceTransform.getNBands() != fuzzySegmentation.getImage().getNBands()) {
                throw incompatibleParametersException();
            }

            int nElements = inputImage.getNElements();
            int nLabels = distanceTransform.getNBands();

            // create crisp segmentation
            bool *crispSegmentationData = new bool[nElements * nLabels];
            Image<bool> crispSegmentation(crispSegmentationData, inputImage.getLattice(), nLabels);
            crisp(distanceTransform, crispSegmentation);

            // create space between segmented regions
            bool *erodedSegmentationData = new bool[nElements];
            Image<bool> erodedCrispSegmentation(erodedSegmentationData, crispSegmentation.getLattice(), 1);
            structuringElement.binaryErodeImage(crispSegmentation, false, erodedCrispSegmentation);

            // fill in the gaps
            membershipTemplate minMembership = fuzzySegmentation.getMinIntensity();
            membershipTemplate maxMembership = fuzzySegmentation.getMaxIntensity();
            membershipTemplate membershipRange = fuzzySegmentation.getRange();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                vector<bool> crispMembership = erodedCrispSegmentation[elementIndex];
                vector<bool>::iterator labelIterator = find(crispMembership.begin(), crispMembership.end(), true);
                if (labelIterator != crispMembership.end()) {
                    vector<membershipTemplate> membership(nLabels, minMembership);
                    int labelIndex = labelIterator - crispMembership.begin();
                    membership[labelIndex] = maxMembership;
                    fuzzySegmentation.getImage().setElement(elementIndex, membership);
                }
                else {
                    // find which regions are close
                    // find shortest distance to the sets of seedpoints of those regions
                    // compute claims of closest regionss
                }
            }
        }

        template<class intensityTemplate>
        void fuzzify(Image<bool> segmentation, StructuringElement structuringElement,
                     const SeededDistanceMeasure<int> &distanceMeasure,
                     IntensityWorkset<intensityTemplate> fuzzySegmentation) {

        }

        /**
         * Fuzzy segmentation, based on a distance transform. Each modality band in the output image corresponds to a
         * label. The sum of the intensities of each spatial element is segmentation.maxIntensity. The intensity of a
         * spatial element in a band corresponds to its degree of membership, in the range [minIntensity,maxIntensity]
         * to that label.
         *
         * Some simplifications are made; The shape of the spatial elements is approximated by a sphere, and the
         * competing seed points are assumed to be evenly distributed around each spatial element. The accumulated
         * round-off error is added in favour of the lowest label, to make the labels sum up correctly. This behavior
         * is most prominent for, for example, integer types, for which the round-off error may be relatively large.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :-----    |:-------
         * distanceTransform    | INPUT     | Distance transform on which to base the segmentation.
         * tolerance            | INPUT     | The maximum difference in distance that results in a fuzzy segmentation.
         * segmentation         | OUTPUT    | Resulting segmentation. Must have the same lattice and number of modality bands as distanceTransform.

         */
        template <class T>
        void fuzzy(Image<double> distanceTransform, double tolerance, IntensityWorkset<T> segmentation) {
            if (distanceTransform.getLattice() != segmentation.getImage().getLattice()) {
                throw incompatibleParametersException();
            }
            if (distanceTransform.getNBands() != segmentation.getImage().getNBands()) {
                throw incompatibleParametersException();
            }

            int nElements = distanceTransform.getNElements();
            int nLabels = distanceTransform.getNBands();
            T minCoverage = segmentation.getMinIntensity();
            T maxCoverage = segmentation.getMaxIntensity();
            T coverageRange = maxCoverage - minCoverage;
            double scaleFactor = cbrt(1 / segmentation.getImage().getLattice().getDensity());
            double radius = cbrt(3/(4 * PI)) * scaleFactor; // approximate the element by a sphere
            MinimumValueFinder<double> valueFinder;
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                vector<double> distances = distanceTransform[elementIndex];
                int nearestLabel = valueFinder.getVectorElementIndex(distances);
                double smallestDistance = distances[nearestLabel];
                vector<int> competingLabels;
                int nCompetingLabels = 0;
                vector<double> competingClaims;
                double sumOfClaims = 0.0;
                for (int labelIndex = 0; labelIndex < nLabels; labelIndex++) {
                    segmentation.getImage().setElement(elementIndex, labelIndex, minCoverage); // setup to no label
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
                for (int labelIndex = 1; labelIndex < (nCompetingLabels); labelIndex++) { // First element gets special treatment, see below.
                    T coverage = T(minCoverage + coverageRange * normalizationFactor * competingClaims[labelIndex]);
                    segmentation.getImage().setElement(elementIndex,competingLabels[labelIndex],coverage);
                    accumulatedCoverage += (coverage - minCoverage);
                }
                // This favours the first, and lowest, label, as the accumulated round-off error, which may be as much as nBands, is added to its coverage value, but it's the only idea I've got right now. The practise of favouring the lowest element was inspired by F. Malmberg, who uses this method to make the segmentations deterministic.
                segmentation.getImage().setElement(elementIndex, competingLabels[0], maxCoverage - accumulatedCoverage);
            }
        }
    };
}

#endif //SEGMENTATION_H
