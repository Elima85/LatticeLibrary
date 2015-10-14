#ifndef LATTICELIBRARY_SEEDEDDISTANCETRANSFORM_H
#define LATTICELIBRARY_SEEDEDDISTANCETRANSFORM_H

#include "image.h"
#include "seed.h"
#include "norm.h"
#include "priorityqueue.h"
#include <vector>
#include <cfloat>
#include <algorithm> // find
#include "vectoroperators.h"
#include "seededdistancemeasure.h"

namespace LatticeLib {

    /**
     * Class for computing seeded distance transforms of Image objects.
     */
    class SeededDistanceTransform {

    public:
        /**
         * Applies the specified distance measure to the input image, and computes the distance transform and the roots of its inverse forest.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :------   | :-------
         * inputImage           | INPUT     | Input image for the distance transform.
         * seeds                | INPUT     | %Seed points for the distance transform. Contains one vector of seed points for every label.
         * distanceMeasure      | INPUT     | Distance measure to be used for the transform.
         * neighborhoodSize     | INPUT     | The number of neighbors that count as adjacent to a spel.
         * distanceTransform    | OUTPUT    | The computed distance transform. Must have the same lattice and dimensions as the input image, and one modality band for each label.
         * roots                | OUTPUT    | The roots of the distance transform. Must have the same lattice and dimensions as the input image, and one modality band for each label.
         */
        template<class T>
        void apply(const Image<T> &inputImage, const vector<vector<Seed> > &seeds,
                   SeededDistanceMeasure<T> &distanceMeasure, int neighborhoodSize,
                   Image<double> distanceTransform, Image<int> roots) const {

            if ((inputImage.getLattice() != distanceTransform.getLattice()) ||
                (inputImage.getLattice() != roots.getLattice())) {
                throw incompatibleParametersException();
            }
            if ((distanceTransform.getNBands() != seeds.size()) || (roots.getNBands() != seeds.size())) {
                throw incompatibleParametersException();
            }

            // setup
            int nElements = inputImage.getNElements();
            int nLabels = seeds.size();
            bool *inQueue = new bool[nElements]; // so that only the "best" copy of an element is popped, and all others are skipped, until a better one is pushed.
            distanceMeasure.setup(inputImage);
            for (int labelIndex = 0; labelIndex < nLabels; labelIndex++) {
                // initialization
                for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                    inQueue[elementIndex] = false;
                }
                priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
                vector<PriorityQueueElement<T> > newQueueElements;
                distanceMeasure.initialize(inputImage, seeds, labelIndex, distanceTransform, roots, newQueueElements);
                int nNewQueueElements = newQueueElements.size();
                for (int newQueueElementIndex = 0; newQueueElementIndex < nNewQueueElements; newQueueElementIndex++) {
                    queue.push(newQueueElements[newQueueElementIndex]);
                    inQueue[newQueueElements[newQueueElementIndex].getIndex()] = true;
                }
                // wave front propagation
                while (!queue.empty()) {
                    PriorityQueueElement<T> topElement = queue.top();
                    queue.pop();
                    int poppedElementIndex = topElement.getIndex();
                    if (inQueue[poppedElementIndex]) {
                        inQueue[poppedElementIndex] = false; // so that old queue elements offering larger distances are skipped
                        distanceMeasure.update(inputImage, neighborhoodSize, poppedElementIndex, labelIndex,
                                               distanceTransform, roots, newQueueElements);
                        nNewQueueElements = newQueueElements.size();
                        for (int queueElementIndex = 0; queueElementIndex < nNewQueueElements; queueElementIndex++) {
                            queue.push(newQueueElements[queueElementIndex]);
                            inQueue[newQueueElements[queueElementIndex].getIndex()] = true;
                        }
                    }
                }
            }
            // cleanup
            distanceMeasure.clear();
        }

        /**
         * Applies the specified distance measure to the input image, and computes the distance transform and the roots of its inverse forest.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :------   | :-------
         * inputImage           | INPUT     | Input image for the distance transform.
         * seeds                | INPUT     | %Seed points for the distance transform. Contains one vector of seed points for every label.
         * distanceMeasure      | INPUT     | Distance measure to be used for the transform.
         * neighborhoodSize     | INPUT     | The number of neighbors that count as adjacent to a spel.
         * distanceTransform    | OUTPUT    | The computed distance transform. Must have the same lattice and dimensions as the input image, and one modality band for each label.
         * roots                | OUTPUT    | The roots of the distance transform. Must have the same lattice and dimensions as the input image, and one modality band for each label.
         */
        template<class T>
        void applySingleLayer(const Image<T> &inputImage, const vector<vector<Seed> > &seeds,
                              SeededDistanceMeasure<T> &distanceMeasure, int neighborhoodSize,
                              Image<double> distanceTransform, Image<int> roots) const {

            if ((inputImage.getLattice() != distanceTransform.getLattice()) ||
                (inputImage.getLattice() != roots.getLattice())) {
                throw incompatibleParametersException();
            }

            // setup
            int nElements = inputImage.getNElements();
            int nLabels = seeds.size();
            bool *inQueue = new bool[nElements];
            std::fill_n(inQueue, nElements, false);
            distanceMeasure.setup(inputImage);
            vector< vector<Seed> > allSeeds;
            vector<Seed> cumulativeSeeds;
            for (int labelIndex = 0; labelIndex < nLabels; labelIndex++){
                int nSeeds = seeds[labelIndex].size();
                for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
                    cumulativeSeeds.push_back(Seed(seeds[labelIndex][seedIndex].getElementIndex(),
                                                   seeds[labelIndex][seedIndex].getLabel()));
                }
            }
            allSeeds.push_back(cumulativeSeeds);

            apply(inputImage, allSeeds, distanceMeasure, neighborhoodSize, distanceTransform, roots);
        }
    };

}

#endif
