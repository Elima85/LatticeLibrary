#ifndef APPROXIMATEMINIMUMBARRIERBOUNDINGBOXDISTANCE_H
#define APPROXIMATEMINIMUMBARRIERBOUNDINGBOXDISTANCE_H

#include "distancemeasure.h"
#include "norm.h"
#include "neighbor.h"
#include "vectoroperators.h"

namespace LatticeLib {

/**
* Approximated vectorial minimum barrier distance
* Strand et al. 2012, Kårsnäs and Strand 2012
*
* Approximates the minimum of the difference between the maximum and minimum values along a path, based on the locally optimal path ("greedy" algorithm).
* Is the other approximation (min(max)-max(min)) valid for VMBD? Can min(max) and max(min) be computed for each band by itself? (probably not)
*/
    template<class T>
    class ApproximateMinimumBarrierBoundingBoxDistance : public DistanceMeasure {

    protected:
        /** The norm used when converting a traversed intensity span to a scalar distance value. */
        Norm &norm;

        /** The lowest intensities that have been traversed between a spatial element and the closest seedpoint. */
        vector<T> *pathMinimumValue;

        /** The highest intensities that have been traversed between a spatial element and the closest seedpoint. */
        vector<T> *pathMaximumValue;

    public:
        ApproximateMinimumBarrierBoundingBoxDistance(Norm &n) : DistanceMeasure() {
            norm = n;
            pathMinimumValue = NULL;
            pathMaximumValue = NULL;
        }
        ~ApproximateMinimumBarrierBoundingBoxDistance(){}

        template <class T>
        void initialize(const IntensityImage<T> &image, int nS) {
            neighborhoodSize = nS;
            int nElements = image.getNElements();
            int nBands = image.getNBands();
            vector<T> *pathMinimumValue = new vector<T>[nElements];
            vector<T> *pathMaximumValue = new vector<T>[nElements];
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                pathMinimumValue[elementIndex] = image[elementIndex]; // the spel is always part of the path between itself and the object boundary
                pathMaximumValue[elementIndex] = image[elementIndex];
            }
        }

        template<class T>
        void update(DistanceImage &distanceTransform, const IntensityImage<T> &image, RootImage &roots, int elementIndex, int labelIndex, vector<PriorityQueueElement<T> > &toQueue){
            toQueue.clear();
            vector<Neighbor> neighbors;
            image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
            for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
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

        void clear() {
            neighborhoodSize = 0;
            delete pathMinimumValue;
            delete pathMaximumValue;
            pathMinimumValue = NULL;
            pathMaximumValue = NULL;
        }
    };
}

#endif