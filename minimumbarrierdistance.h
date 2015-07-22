#ifndef MINIMUMBARRIERDISTANCE_H
#define MINIMUMBARRIERDISTANCE_H

#include "distancemeasure.h"
#include "image.h"
#include "neighbor.h"
#include "vectoroperators.h"
#include "seed.h"
#include <cfloat> // DBL_MAX

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
    class MinimumBarrierDistance : public SeededDistanceMeasure<T> {

    protected:

        /** The lowest intensities that have been traversed between a spatial element and the closest seed point. */
        T *pathMinimumValue;

        /** The highest intensities that have been traversed between a spatial element and the closest seed point. */
        T *pathMaximumValue;

        /** Preliminary path to each element. */
        int *preliminaryRoots;

    public:
        /**
         * Constructor for ApproximateMinimumBarrierBoundingBoxDistance objects.
         */
        MinimumBarrierDistance() : SeededDistanceMeasure<T>() {
            pathMinimumValue = NULL;
            pathMaximumValue = NULL;
        }

        /**
         * Destructor for ApproximateMinimumBarrierBoundingBoxDistance objects.
         */
        ~MinimumBarrierDistance() { }

        /**
         * Overloads SeededDistanceMeasure::initialize().
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         */
        void setup(const Image<T> &image) {
            if ((pathMaximumValue != NULL) || (pathMinimumValue != NULL)) {
                // TODO: Throw error or exception
            }
            int nElements = image.getNElements();
            pathMinimumValue = new T[nElements];
            pathMaximumValue = new T[nElements];
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
                // TODO: Throw error or exception
            }
            int nElements = image.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                pathMinimumValue[elementIndex] = -INF;
                pathMaximumValue[elementIndex] = INF;
                // initialize background
                distanceTransform.setElement(elementIndex, labelIndex, DBL_MAX);
                roots.setElement(elementIndex, labelIndex, -1);
            }
            toQueue.clear();
            int nSeeds = seeds[labelIndex].size();
            for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
                int elementIndex = seeds[labelIndex][seedIndex].getIndex();
                pathMinimumValue[elementIndex] = image(elementIndex, 0); // the spel is always part of the path between itself and the object boundary
                pathMaximumValue[elementIndex] = image(elementIndex, 0);
                distanceTransform.setElement(elementIndex, labelIndex, 0);
                roots.setElement(elementIndex, labelIndex, elementIndex);
                toQueue.push_back(PriorityQueueElement<T>(elementIndex, 0));
            }
        }

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
                int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
                T minIntensity = MIN(pathMinimumValue[elementIndex], image(neighborGlobalIndex, 0));
                T maxIntensity = MAX(pathMaximumValue[elementIndex], image(neighborGlobalIndex, 0));
                T intensitySpan = maxIntensity - minIntensity;
                if (minIntensity > pathMinimumValue[neighborGlobalIndex]) {
                    pathMinimumValue[neighborGlobalIndex] = minIntensity;
                    pathMaximumValue[neighborGlobalIndex] = maxIntensity;
                    double distance = maxIntensity - minIntensity;
                    if (distance < distanceTransform(neighborGlobalIndex, labelIndex)) {
                        distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                        roots.setElement(neighborGlobalIndex, labelIndex, elementIndex);
                        toQueue.push_back(PriorityQueueElement<T>(neighborGlobalIndex, distance));
                    }
                }
            }

        }

        /**
         * Overloads SeededDistanceMeasure::clear().
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
