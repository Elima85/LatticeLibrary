#ifndef FUZZYCONNECTEDNESS_H
#define FUZZYCONNECTEDNESS_H

#include "distancemeasure.h"
#include "image.h"
#include "norm.h"
#include "neighbor.h"
#include <cfloat> // DBL_MAX

namespace LatticeLib {

    /**
     * Fuzzy connectedness
     * ====================
     * Maximizes the weakest link, defined as the difference in value between two neighbors along the path. *Only takes the first modality band into account!*
     * TODO: Should an inter-neighbor Euclidean distance be used a factor, to consider different kinds of neighbors and lattices? Ask Punam Saha about fuzzy adjacency.
     *
     * References
     * ------------
     * [Udupa and Samarasekera 1996](http://www.sciencedirect.com/science/article/pii/S1077316996900210) <br>
     * [Udupa and Saha 2003](http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=1232198&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D1232198)
     */
    template<class T>
    class FuzzyConnectedness : public SeededDistanceMeasure<T> {

    protected:
        /** The norm used in the definition of distance. */
        Norm<T> &norm;

    public:
        /**
         * Constructor for FuzzyConnectedness objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * n            | INPUT     | The norm used in the definition of distance.
         */
        FuzzyConnectedness(Norm<T> &n) : SeededDistanceMeasure<T>(), norm(n) {}

        /**
         * Destructor for FuzzyConnectedness objects.
         */
        ~FuzzyConnectedness() {};

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
                    Image<double> &distanceTransform, Image<int> &roots, vector <PriorityQueueElement<T> > &toQueue) {
            toQueue.clear();
            vector<Neighbor> neighbors;
            image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
            for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
                double distance = MAX(distanceTransform(elementIndex, labelIndex), norm.compute(image[neighborGlobalIndex] - image[elementIndex]));  // if the current link is not weaker, the distance does not change.
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