#ifndef GEODESICDISTANCE_H
#define GEODESICDISTANCE_H

#include "distancemeasure.h"
#include "image.h"
#include "norm.h"
#include "neighbor.h"

namespace LatticeLib {

    /**
     * Geodesic distance
     * Toivanen 1996, Ikonen 2005, Criminisi 2008
     *
     * Sample values are treated as height values, and the "walking distance" along the surface is calculated.
     * We use the 2-norm instead of approximating the Euclidean distance with the 1-norm, as we don't get integer results anyway.
     * Euclidean inter-neighbor distance is used as a weight. Borgefors1986 suggests optimal weights
     * for 2D CC, but these are not taken into account.
     */
    class GeodesicDistance : public DistanceMeasure {

    protected:
        /** The norm used when converting a traversed intensity span to a scalar distance value. */
        Norm &norm;

    public:
        GeodesicDistance(Norm &n) : DistanceMeasure() {
            norm = n;
        }

        ~GeodesicDistance();

        template<class T>
        void update(const Image<T> &image, int neighborhoodSize, int elementIndex, int labelIndex,
                    Image<double> &distanceTransform, Image<int> &roots, vector<PriorityQueueElement<T> > &toQueue) {
            toQueue.clear();
            vector<Neighbor> neighbors;
            image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
            for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
                vector<T> intensityDifference = elementIntensity - image[neighborGlobalIndex];
                distance = distanceTransform(elementIndex, labelIndex) +
                           sqrt(norm.compute(intensityDifference) * norm.compute(intensityDifference) +
                                distanceToNeighbor * distanceToNeighbor); // Not perfect... Weights are messed up if it's not the 2-norm, I think.
                if (distance<distanceTransform(neighborGlobalIndex, labelIndex)) {
                    distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                    roots.setElement(neighborGlobalIndex, labelIndex, elementIndex);
                    toQueue.push_back(PriorityQueueElement<T>(neighborGlobalIndex, distance));
                }
            }
        }
    };

}

#endif //GEODESICDISTANCE_H
