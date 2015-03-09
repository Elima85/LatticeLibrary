#ifndef FUZZYCONNECTEDNESS_H
#define FUZZYCONNECTEDNESS_H

namespace LatticeLib {

    /**
    * Fuzzy connectedness distance transform
    * Udupa 1996, Udupa 2003
    *
    * Maximizes the weakest link, defined as the difference in value between two neighbors along the path. OBS!!! Only takes the first band into account! Use norm of color difference vector?
    * Should an inter-neighbor Euclidian distance be used a factor, to consider different kinds of neighbors and lattices? Ask Punam Saha about fuzzy adjacency.
    */
    class FuzzyConnectedness : public DistanceMeasure {

    protected:
        /** The norm used when converting a traversed intensity span to a scalar distance value. */
        Norm &norm;

    public:
        FuzzyConnectedness(Norm &n) : DistanceMeasure() {
            norm = n;
        }
        ~FuzzyConnectedness();

        template<class T>
        void initialize(const IntensityCImage <T> &image, int nS) {
            neighborhoodSize = nS;
        }

        template<class T>
        void update(const IntensityCImage <T> &image, DistanceCImage &distanceTransform, RootCImage &roots, int elementIndex, int labelIndex, vector <PriorityQueueElement<T>> &toQueue) {
            toQueue.clear();
            vector <Neighbor> neighbors;
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
        void clear() {
            neighborhoodSize = 0;
        }
    }
}

#endif