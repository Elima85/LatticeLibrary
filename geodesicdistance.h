#ifndef LATTICELIBRARY_GEODESICDISTANCE_H
#define LATTICELIBRARY_GEODESICDISTANCE_H

#include "distancemeasure.h"
#include "image.h"
#include "neighbor.h"
#include <cfloat> // DBL_MAX

namespace LatticeLib {

    /**
     * Geodesic Distance
     * ==================
     *
     * Sample values are treated as height values, and the "walking distance" along the surface is calculated.
     * We use the 2-norm instead of approximating the Euclidean distance with the 1-norm, that was used in the original
     * paper, as we don't get the benefits of integer results anyway. Euclidean inter-neighbor distance is used as a
     * weight. [Borgefors 1986](http://www.sciencedirect.com/science/article/pii/S0734189X86800470) suggests optimal
     * weights for 2D Cartesian lattices, but these are not taken into account. *Only takes the first modality band
     * into account!*
     *
     * References
     * -----------
     * [Toivanen 1996](http://www.sciencedirect.com/science/article/pii/0167865596000104) <br>
     * [Ikonen 2005](http://link.springer.com/chapter/10.1007/978-3-540-31965-8_22) <br>
     * [Criminisi et al. 2008](http://link.springer.com/chapter/10.1007/978-3-540-88682-2_9)
     */
    template<class T>
    class GeodesicDistance : public SeededDistanceMeasure<T> {

    protected:

    public:
        /**
         * Constructor for GeodesicDistance objects.
         */
        GeodesicDistance() : SeededDistanceMeasure<T>(){}

        /**
         * Destructor for GeodesicDistance objects.
         */
        ~GeodesicDistance() {}

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
        void update(const Image<T> &image, int neighborhoodSize, int elementIndex, int labelIndex,
                    Image<double> &distanceTransform, Image<int> &roots, vector<PriorityQueueElement<T> > &toQueue) {
            toQueue.clear();
            vector<Neighbor> neighbors;
            image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
            T elementIntensity = image(elementIndex, 0);
            for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                int neighborGlobalIndex = neighbors[neighborIndex].getElementIndex();
                T intensityDifference = elementIntensity - image(neighborGlobalIndex, 0);
                double distanceToNeighbor = image.euclideanDistance(elementIndex, neighborGlobalIndex);
                double distance = distanceTransform(elementIndex, labelIndex) +
                           sqrt(intensityDifference * intensityDifference + distanceToNeighbor * distanceToNeighbor);
                if (distance < distanceTransform(neighborGlobalIndex, labelIndex)) {
                    distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                    roots.setElement(neighborGlobalIndex, labelIndex, elementIndex);
                    toQueue.push_back(PriorityQueueElement<T>(neighborGlobalIndex, distance));
                }
            }
        }
    };

}

#endif //LATTICELIBRARY_GEODESICDISTANCE_H
