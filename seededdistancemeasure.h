#ifndef LATTICELIBRARY_SEEDEDDISTANCEMEASURE_H
#define LATTICELIBRARY_SEEDEDDISTANCEMEASURE_H

#include "priorityqueue.h"
#include "image.h"
#include "intensityworkset.h"
#include "seed.h"
#include <cfloat>

namespace LatticeLib {

    /**
    * Base class for distance measures to be used with SeededDistanceTransform.
    */
    template<class T>
    class SeededDistanceMeasure {

    public:
        /**
         * Allocates the resources necessary for the distance transform.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         */
        virtual void setup(const Image<T> &image) {}

        /**
         * Initializes all parameters before traversing the image.
         *
         * Parameter            | in/out  | Comment
         * :---------           | :------ | :-------
         * image                | INPUT   | Input image for the distance transform.
         * seeds                | INPUT   | Vector of seeds associated to the label that is being processed.
         * labelIndex           | INPUT   | Index of the label of the set of seed points being processed.
         * distanceTransform    | OUTPUT  | Distance transform of the image band.
         * roots                | OUTPUT  | Source elements of the propagated distance values.
         * toQueue              | OUTPUT  | Spatial elements to be put on the priority queue.
         */
        virtual void initialize(const Image<T> &image, const vector<vector <Seed> > &seeds, int labelIndex,
                        Image<double> &distanceTransform, Image<int> &roots,
                        vector<PriorityQueueElement<T> > &toQueue) {
            int nElements = image.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                // initialize background
                distanceTransform.setElement(elementIndex, labelIndex, DBL_MAX);
                roots.setElement(elementIndex, labelIndex, -1);
            }
            toQueue.clear();
            int nSeeds = seeds[labelIndex].size();
            for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
                int elementIndex = seeds[labelIndex][seedIndex].getElementIndex();
                distanceTransform.setElement(elementIndex, labelIndex, 0);
                roots.setElement(elementIndex, labelIndex, elementIndex);
                toQueue.push_back(PriorityQueueElement<T>(elementIndex, 0));
            }
        }

        /**
         * Propagates the wave front to the next spatial element.
         *
         * Parameter            | in/out        | Comment
         * :---------           | :------       | :-------
         * image                | INPUT         | Input image for the distance transform.
         * neighborhoodSize     | INPUT         | The maximum number of neighbors that count as adjacent to a spel.
         * elementIndex         | INPUT         | Index of the spatial element being processed.
         * labelIndex           | INPUT         | Index of the label of the set of seed points being processed.
         * distanceTransform    | INPUT/OUTPUT  | Distance transform of the image.
         * roots                | OUTPUT        | Source spels of the propagated distance values.
         * toQueue              | OUTPUT        | Spatial elements to be put on the priority queue.
         */
        virtual void update(const Image<T> &image, int neighborhoodSize, int elementIndex, int labelIndex,
                    Image<double> &distanceTransform, Image<int> &roots, vector<PriorityQueueElement<T> > &toQueue) {}

        /**
         * Clears and deletes the image data, in preparation for re-use for other images.
         */
        virtual void clear() {}
    };
}

#endif