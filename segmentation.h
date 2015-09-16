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
#include "weightedaveragefilter.h"
#include "maximumvaluefinder.h"

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
         * Crisp segmentation, based on a seeded distance transform. Each element is assigned the label of the seed point within the shortest distance.
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
            //std::cout << "Inside crisp segmentation." << std::endl;
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
            //std::cout << "Initialized queue." << std::endl;
            // label propagation
            while(!queue.empty()) {
                PriorityQueueElement<int> topElement = queue.top();
                queue.pop();
                int poppedElementIndex = topElement.getIndex();
                //std::cout << "Popped element " << poppedElementIndex << std::endl;
                int poppedElementLabel = segmentation(poppedElementIndex, 0);
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

        /**
         * Fuzzy segmentation, based on a seeded distance transform.
         * Based on [Malmberg et al. 2011](http://www.sciencedirect.com/science/article/pii/S0304397510006687).
         *
         * Parameter            | in/out    | Comment
         * :---------           | :-----    |:-------
         * distanceTransform    | INPUT     | Distance transform on which to base the segmentation.
         * neighborhoodSize     | INPUT     | Neighborhood size used for computing vertex coverage. Use of only face neighbors is recommended.
         * fuzzySegmentation    | OUTPUT    | Resulting segmentation. Must have the same lattice and number of modality bands as distanceTransform.
         */
        template<class membershipTemplate>
        void fuzzy(Image<double> distanceTransform,
                   int neighborhoodSize,
                   IntensityWorkset<membershipTemplate> fuzzySegmentation) {

            if ((distanceTransform.getLattice() != fuzzySegmentation.getImage().getLattice()) ||
                distanceTransform.getNBands() != distanceTransform.getNBands()) {
                throw incompatibleParametersException();
            }
            int nLabels = distanceTransform.getNBands();
            int nElements = distanceTransform.getNElements();

            bool *crispSegmentationData = new bool[nElements * nLabels];
            Image<bool> crispSegmentation(crispSegmentationData, distanceTransform.getLattice(), nLabels);
            crisp(distanceTransform, crispSegmentation);

            membershipTemplate minCoverage = fuzzySegmentation.getMinIntensity();
            membershipTemplate maxCoverage = fuzzySegmentation.getMaxIntensity();
            membershipTemplate coverageRange = fuzzySegmentation.getRange();
            MaximumValueFinder<bool> crispMembershipFinder;
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                int elementLabel = crispMembershipFinder.getVectorElementIndex(crispSegmentation[elementIndex]);
                double elementPrimaryDistance = distanceTransform(elementIndex, elementLabel);
                vector<Neighbor> neighbors;
                distanceTransform.getNeighbors(elementIndex, neighborhoodSize, neighbors);
                vector<double> coverage(nLabels, 0.0);
                for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                    double edgeCoverage = 0.5;
                    int neighborLabel = crispMembershipFinder.getVectorElementIndex(crispSegmentation[neighbors[neighborIndex].getElementIndex()]);
                    if (elementLabel != neighborLabel) {
                        //std::cout << "found edge element: " << elementIndex << std::endl;
                        double neighborPrimaryDistance = distanceTransform(neighbors[neighborIndex].getElementIndex(),
                                                                           neighborLabel);
                        double neighborSecondaryDistance = distanceTransform(neighbors[neighborIndex].getElementIndex(),
                                                                             elementLabel);
                        double elementSecondaryDistance = distanceTransform(elementIndex, neighborLabel);
                        //double a = elementPrimaryDistance * 1.0 + elementSecondaryDistance * 0;
                        //double b = neighborPrimaryDistance * 1.0 + neighborSecondaryDistance * 0;
                        //double c = neighborPrimaryDistance * 0 + neighborSecondaryDistance * 1.0;
                        //double d = elementPrimaryDistance * 0 + elementSecondaryDistance * 1.0;
                        //std::cout << "factors: a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << std::endl;
                        //double cutLocation = (a - d) / (a - d + c - b);
                        double cutLocation = (elementSecondaryDistance - elementPrimaryDistance) /
                                (elementSecondaryDistance - elementPrimaryDistance +
                                        neighborSecondaryDistance - neighborPrimaryDistance);
                        //std::cout << "\tcut location: " << cutLocation << std::endl;
                        edgeCoverage = MIN(cutLocation, 0.5);
                    }
                    //std::cout << "\tcomputed edge coverage: " << edgeCoverage << std::endl;
                    coverage[elementLabel] = coverage[elementLabel] + edgeCoverage;
                    coverage[neighborLabel] = coverage[neighborLabel] + (0.5 - edgeCoverage);
                }
                coverage = (1.0 / (0.5 * double(neighbors.size()))) * coverage;
                //std::cout << "\tcomputed coverage: ";
                //printVector(coverage);
                coverage = coverageRange * coverage;
                coverage = coverage + vector<double>(nLabels, minCoverage);
                //std::cout << "\tassigned coverage: ";
                //printVector(coverage);
                fuzzySegmentation.getImage().setElement(elementIndex, coverage);
            }
            delete crispSegmentationData;
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
        /*template <class T>
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
        }*/
    };
}

#endif //SEGMENTATION_H
