#ifndef FUZZYDISTANCE_H
#define FUZZYDISTANCE_H

#include "distancemeasure.h"
#include "image.h"
#include "norm.h"
#include "neighbor.h"

/**
* Fuzzy distance
* Saha 2002, (Svensson 2008)
*
* The distance between two neighbors is the average of their intensity values multiplied with the Euclidean distance between them. OBS!!! Only takes the first band into account! Use norm of average color vector?
*/
class FuzzyDistance : public DistanceMeasure {

protected:
    /** The norm used in the definition of distance. */
    Norm &norm;

public:
    FuzzyDistance(Norm &n) : DistanceMeasure() {
        norm = n;
    }
    ~FuzzyDistance();

    template<class T>
    void update(const Image <T> &image, int neighborhoodSize, int elementIndex, int labelIndex,
                Image <double> &distanceTransform, Image <int> &roots, vector <PriorityQueueElement<T>> &toQueue) {
        toQueue.clear();
        vector <Neighbor> neighbors;
        image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
        for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
            int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
            double distanceToNeighbor = image.euclideanDistance(elementIndex, neighborGlobalIndex);
            double distance = distanceTransform(elementIndex, nLabels) +
                              0.5 * norm.compute(image[neighborGlobalIndex] + image[elementIndex]) * distanceToNeighbor;
            if (distance < distanceTransform(neighborGlobalIndex, labelIndex)) {
                distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                roots.setElement(neighborGlobalIndex, labelIndex, elementIndex);
                toQueue.push_back(PriorityQueueElement<T>(neighborGlobalIndex, distance));
            }
        }
    };

};

#endif