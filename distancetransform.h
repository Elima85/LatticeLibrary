#ifndef DISTANCETRANSFORM_H
#define DISTANCETRANSFORM_H

#include "intensityworkset.h"
#include "image.h"
#include "distancemeasure.h"


namespace LatticeLib {

    class DistanceTransform {

    public:
        template<class T>
        void apply(const IntensityWorkset<T> &inputImage, DistanceMeasure &distanceMeasure,
                         int neighborhoodSize, Image <double> distanceTransform, Image <int> roots) const {

            if ((inputImage.getImage().getLattice() != distanceTransform.getLattice()) ||
                (inputImage.getImage().getLattice() != roots.getLattice())) {
                // throw exception or error
            }

            if ((inputImage.getImage().getNBands() != distanceTransform.getNBands()) ||
                (inputImage.getImage().getNBands() != roots.getNBands())) {
                // throw exception or error
            }

            for (int bandIndex = 0; bandIndex < inputImage.getImage().getNBands(); bandIndex++) {
                // initialization
                int nElements = image.getNElements();
                bool *inQueue = new bool[nElements]; // so that only the "best" copy of an element is popped, and all others are skipped, until a better one is pushed.
                distanceMeasure.setup(inputImage);
                vector<PriorityQueueElement<T> > newQueueElements;
                distanceMeasure.initialize(inputImage, bandIndex, distanceTransform, roots, newQueueElements);
                priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
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
                        distanceMeasure.update(inputImage, bandIndex, neighborhoodSize, poppedElementIndex,
                                               distanceTransform, roots, newQueueElements);
                        nNewQueueElements = newQueueElements.size();
                        for (int queueElementIndex = 0; queueElementIndex < nNewQueueElements; queueElementIndex++) {
                            queue.push(newQueueElements[queueElementIndex]);
                            inQueue[newQueueElements[queueElementIndex].getIndex()] = true;
                        }
                    }
                }
            }
            distanceMeasure.clear();
        }
    };
}

#endif //DISTANCETRANSFORM_H
