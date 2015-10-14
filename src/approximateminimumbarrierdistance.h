#ifndef LATTICELIBRARY_APPROXIMATEMINIMUMBARRIERDISTANCE_H
#define LATTICELIBRARY_APPROXIMATEMINIMUMBARRIERDISTANCE_H

#include "seededdistancemeasure.h"
#include "image.h"
#include "pnorm.h"
#include "neighbor.h"
#include "vectoroperators.h"
#include "seed.h"
#include <cfloat> // DBL_MAX
#include <cmath>
#include <vector>

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
    class ApproximateMinimumBarrierDistance : public SeededDistanceMeasure<T> {

    protected:
        /** The norm used when converting a traversed intensity span to a scalar distance value. */
        Norm<T> &norm;

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
        ApproximateMinimumBarrierDistance(Norm<T> &n) : SeededDistanceMeasure<T>(), norm(n) {
            pathMinimumValue = NULL;
            pathMaximumValue = NULL;
        }

        /**
         * Destructor for ApproximateMinimumBarrierBoundingBoxDistance objects.
         */
        ~ApproximateMinimumBarrierDistance(){}

        /**
         * Overloads SeededDistanceMeasure::initialize().
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         */
        void setup(const Image<T> &image) {
            if ((pathMaximumValue != NULL) || (pathMinimumValue != NULL)) {
                // TODO: Throw error or exception?
            }
            int nElements = image.getNElements();
            pathMinimumValue = new vector<T>[nElements];
            pathMaximumValue = new vector<T>[nElements];
        }

        /**
         * Overloads SeededDistanceMeasure::initialize().
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
        void initialize(const Image<T> &image, const vector<vector<Seed> > &seeds, int labelIndex,
                        Image<double> &distanceTransform, Image<int> &roots, vector<PriorityQueueElement<T> > &toQueue) {
            if ((pathMaximumValue == NULL) || (pathMinimumValue == NULL)) {
                // TODO: Throw error or exception?
            }
            int nElements = image.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                pathMinimumValue[elementIndex] = image[elementIndex]; // the spel is always part of the path between itself and the object boundary
                pathMaximumValue[elementIndex] = image[elementIndex];
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
        };

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
            int nNeighbors = neighbors.size();
            for (int neighborIndex = 0; neighborIndex < nNeighbors; neighborIndex++) {
                int neighborGlobalIndex = neighbors[neighborIndex].getElementIndex();
                vector<T> minIntensities = minElements(pathMinimumValue[elementIndex], image[neighborGlobalIndex]);
                vector<T> maxIntensities = maxElements(pathMaximumValue[elementIndex], image[neighborGlobalIndex]);
                vector<T> intensitySpans = maxIntensities - minIntensities;
                double distance = norm.compute(intensitySpans);
                if (distanceTransform(neighborGlobalIndex, labelIndex) - distance > DBL_EPSILON) {
                    distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                    roots.setElement(neighborGlobalIndex, labelIndex, elementIndex);
                    pathMinimumValue[neighborGlobalIndex] = minIntensities;
                    pathMaximumValue[neighborGlobalIndex] = maxIntensities;
                    toQueue.push_back(PriorityQueueElement<T>(neighborGlobalIndex, distance));
                }
            }
        }

        /**
         * Overloads SeededDistanceMeasure::clear().
         */
        void clear() {
            delete[] pathMinimumValue;
            delete[] pathMaximumValue;
            pathMinimumValue = NULL;
            pathMaximumValue = NULL;
        }
    };
}

#endif