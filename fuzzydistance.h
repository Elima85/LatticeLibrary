#ifndef FUZZYDISTANCE_H
#define FUZZYDISTANCE_H

#include "distancemeasure.h"
#include "image.h"
#include "norm.h"
#include "neighbor.h"
#include <cfloat> // DBL_MAX

namespace LatticeLib {

/**
 * Fuzzy Distance
 * ===============
 * The distance between two neighbors is the average of their intensity values multiplied with the Euclidean distance
 * between them. *Only takes the first modality band into account!*
 *
 * References
 * -----------
 * [Saha et al. 2002](http://www.sciencedirect.com/science/article/pii/S1077314202909744) <br>
 * [Svensson 2008](http://www.sciencedirect.com/science/article/pii/S0167865508000226)
 */
    template<class T>
    class FuzzyDistance : public SeededDistanceMeasure<T> {

    protected:
        /** The norm used in the definition of distance. */
        Norm<T> &norm;

    public:
        /**
         * Constructor for FuzzyDistance objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * n            | INPUT     | The norm used in the definition of distance.
         */
        FuzzyDistance(Norm<T> &n) : SeededDistanceMeasure<T>(), norm(n) {
            norm = n;
        }

        /**
         * Destructor for FuzzyDistance objects.
         */
        ~FuzzyDistance() {}

        /**
         * Overloads SeededDistanceMeasure::update().
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
        void update(const Image <T> &image, int neighborhoodSize, int elementIndex, int labelIndex,
                    Image <double> &distanceTransform, Image <int> &roots, vector <PriorityQueueElement<T>> &toQueue) {
            toQueue.clear();
            vector <Neighbor> neighbors;
            image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
            for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                int neighborGlobalIndex = neighbors[neighborIndex].getElementIndex();
                double distanceToNeighbor = image.euclideanDistance(elementIndex, neighborGlobalIndex);
                double distance = distanceTransform(elementIndex, labelIndex) +
                                  0.5 * norm.compute(image[neighborGlobalIndex] + image[elementIndex]) * distanceToNeighbor;
                if (distance < distanceTransform(neighborGlobalIndex, labelIndex)) {
                    distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                    roots.setElement(neighborGlobalIndex, labelIndex, elementIndex);
                    toQueue.push_back(PriorityQueueElement<T>(neighborGlobalIndex, distance));
                }
            }
        }

    };
}

#endif