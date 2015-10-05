#ifndef LATTICELIBRARY_SEGMENTATION_H
#define LATTICELIBRARY_SEGMENTATION_H

#include "image.h"
#include "intensityworkset.h"
#include "lattice.h"
#include "vectoroperators.h"
#include <cmath>
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
                        double neighborPrimaryDistance = distanceTransform(neighbors[neighborIndex].getElementIndex(),
                                                                           neighborLabel);
                        double neighborSecondaryDistance = distanceTransform(neighbors[neighborIndex].getElementIndex(),
                                                                             elementLabel);
                        double elementSecondaryDistance = distanceTransform(elementIndex, neighborLabel);
                        double cutLocation = (elementSecondaryDistance - elementPrimaryDistance) /
                                (elementSecondaryDistance - elementPrimaryDistance +
                                        neighborSecondaryDistance - neighborPrimaryDistance);
                        edgeCoverage = MIN(cutLocation, 0.5);
                    }
                    coverage[elementLabel] = coverage[elementLabel] + edgeCoverage;
                    coverage[neighborLabel] = coverage[neighborLabel] + (0.5 - edgeCoverage);
                }
                coverage = (1.0 / (0.5 * double(neighbors.size()))) * coverage;
                coverage = coverageRange * coverage;
                coverage = coverage + vector<double>(nLabels, minCoverage);
                fuzzySegmentation.getImage().setElement(elementIndex, coverage);
            }
            delete crispSegmentationData;
        }

    };
}

#endif //LATTICELIBRARY_SEGMENTATION_H
