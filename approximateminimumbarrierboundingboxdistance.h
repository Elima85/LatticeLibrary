#ifndef APPROXIMATEMINIMUMBARRIERBOUNDINGBOXDISTANCE_H
#define APPROXIMATEMINIMUMBARRIERBOUNDINGBOXDISTANCE_H

#include "distancemeasure.h"
#include "image.h"
#include "norm.h"
#include "neighbor.h"
#include "vectoroperators.h"

namespace LatticeLib {

/**
 * Vectorial Approximated Minimum Barrier Distance
 * ================================================
 * Approximates the minimum of the difference between the maximum and minimum values along a path, based on the locally optimal path ("greedy" algorithm). Uses a bounding box for handling the vectorial intensity values.
 *
 * References
 * -----------
 * [Strand et al. 2012](http://www.sciencedirect.com/science/article/pii/S1077314212001750) <br>
 * [Kårsnäs and Strand 2012](http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=6460253&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D6460253)
 */
    template<class T>
    class ApproximateMinimumBarrierBoundingBoxDistance : public DistanceMeasure {

    protected:
        /** The norm used when converting a traversed intensity span to a scalar distance value. */
        Norm &norm;

        /** The lowest intensities that have been traversed between a spatial element and the closest seed point. */
        vector<T> *pathMinimumValue;

        /** The highest intensities that have been traversed between a spatial element and the closest seed point. */
        vector<T> *pathMaximumValue;

    public:
        /**
         * Constructor for ApproximateMinimumBarrierBoundingBoxDistance objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * n            | INPUT     | The norm used when converting a traversed intensity span to a scalar distance value.
         */
        ApproximateMinimumBarrierBoundingBoxDistance(Norm &n) : DistanceMeasure() {
            norm = n;
            pathMinimumValue = NULL;
            pathMaximumValue = NULL;
        }

        /**
         * Destructor for ApproximateMinimumBarrierBoundingBoxDistance objects.
         */
        ~ApproximateMinimumBarrierBoundingBoxDistance(){}

        /**
         * Overloads DistanceMeasure::initialize().
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         * TODO: Should seeds be added here? Would it make exact MBD work?
         */
        void initialize(const Image<T> &image) {
            int nElements = image.getNElements();
            pathMinimumValue = new vector<T>[nElements];
            pathMaximumValue = new vector<T>[nElements];
        }

        /**
         * Overloads DistanceMeasure::reset().
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         */
        void reset(const Image<T> &image) {
            int nElements = image.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                pathMinimumValue[elementIndex] = image[elementIndex]; // the spel is always part of the path between itself and the object boundary
                pathMaximumValue[elementIndex] = image[elementIndex];
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
                vector<T> minIntensities = minElements(pathMinimumValue[elementIndex], image[neighborGlobalIndex]);
                vector<T> maxIntensities = maxElements(pathMaximumValue[elementIndex], image[neighborGlobalIndex]);
                vector<T> intensitySpans = maxIntensities - minIntensities;
                double distance = norm.compute(intensitySpans);
                if (distance < distanceTransform(neighborGlobalIndex, labelIndex)) {
                    distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                    roots.setElement(neighborGlobalIndex, labelIndex, elementIndex);
                    pathMinimumValue[neighborGlobalIndex] = minIntensities;
                    pathMaximumValue[neighborGlobalIndex] = maxIntensities;
                    toQueue.push_back(PriorityQueueElement<T>(neighborGlobalIndex, distance));
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

#endif