#ifndef MINIMUMBARRIERDISTANCE_H
#define MINIMUMBARRIERDISTANCE_H

#include "distancemeasure.h"
#include "image.h"
#include "norm.h"
#include "neighbor.h"
#include "vectoroperators.h"
#include "seed.h"

namespace LatticeLib {

/**
 * Minimum Barrier Distance
 * ==========================
 * Computes the minimum barrier distance, defined as the difference between the highest and lowest intensity value along a path. *Only takes the first modality band into account!*
 *
 * References
 * -----------
 * [Ciesielski et al. 2014] (http://www.sciencedirect.com/science/article/pii/S107731421400068X)
 */
    template<class T>
    class MinimumBarrierDistance : public DistanceMeasure {

    protected:
        /** The norm used when converting a traversed intensity span to a scalar distance value. */
        Norm &norm;

        /** The lowest intensities that have been traversed between a spatial element and the closest seed point. */
        T *pathMinimumValue;

        /** The highest intensities that have been traversed between a spatial element and the closest seed point. */
        T *pathMaximumValue;

        /** Preliminary path to each element. */
        int *preliminaryRoots;

    public:
        /**
         * Constructor for ApproximateMinimumBarrierBoundingBoxDistance objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * n            | INPUT     | The norm used when converting a traversed intensity span to a scalar distance value.
         */
        MinimumBarrierDistance(Norm &n) : DistanceMeasure() {
            norm = n;
            pathMinimumValue = NULL;
            pathMaximumValue = NULL;
        }

        /**
         * Destructor for ApproximateMinimumBarrierBoundingBoxDistance objects.
         */
        ~MinimumBarrierDistance() { }

        /**
         * Overloads DistanceMeasure::initialize().
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         */
        void initialize(const Image<T> &image) {
            if ((pathMaximumValue != NULL) || (pathMinimumValue != NULL)) {
                // TODO: Throw error or exception
            }
            int nElements = image.getNElements();
            pathMinimumValue = new T[nElements];
            pathMaximumValue = new T[nElements];
        }

        /**
         * Overloads DistanceMeasure::reset().
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         */
        void reset(const Image<T> &image, vector<Seed> seeds) {
            if ((pathMaximumValue == NULL) || (pathMinimumValue == NULL)) {
                // TODO: Throw error or exception
            }
            int nElements = image.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                pathMinimumValue[elementIndex] = -INF;
                pathMaximumValue[elementIndex] = INF;
            }
            int nSeeds = seeds.size();
            for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
                pathMinimumValue[elementIndex] = image(seeds[seedIndex].getIndex(), 0); // the spel is always part of the path between itself and the object boundary
                pathMaximumValue[elementIndex] = image(seeds[seedIndex].getIndex(), 0);
            }
        }

        /**
         * Overloads DistanceMeasure::update().
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
            int nNeighbors = neighbors.size();
            for (int neighborIndex = 0; neighborIndex < nNeighbors; neighborIndex++) {
                int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
                T minIntensity = MIN(pathMinimumValue[elementIndex], image(neighborGlobalIndex, 0));
                T maxIntensity = MAX(pathMaximumValue[elementIndex], image(neighborGlobalIndex, 0));
                T intensitySpan = maxIntensity - minIntensity;
                if (minIntensity > pathMinimumValue[neighborGlobalIndex]) {
                    pathMinimumValue[neighborGlobalIndex] = minIntensity;
                    pathMaximumValue[neighborGlobalIndex] = maxIntensity;
                    double distance = maxIntensity - minIntensity;
                    if (distance < distanceTransform[neighborGlobalIndex]) {
                        distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                        roots.setElement(neighborGlobalIndex, labelIndex, elementIndex);
                        toQueue.push_back(PriorityQueueElement<T>(neighborGlobalIndex, distance));
                    }
                }
            }

        }

        /**
         * Overloads DistanceMeasure::clear().
         */
        void clear() {
            delete pathMinimumValue;
            delete pathMaximumValue;
            pathMinimumValue = NULL;
            pathMaximumValue = NULL;
        }
    };
}

#endif //MINIMUMBARRIERDISTANCE_H
