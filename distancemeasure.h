#ifndef DISTANCEMEASURE_H
#define DISTANCEMEASURE_H

#include "intensityworkset.h"
#include "image.h"
#include "priorityqueue.h"

namespace LatticeLib {

    /**
    * Base class for distance measures to be used with DistanceTransform.
    */
    template<class T>
    class DistanceMeasure {

    public:
        /**
         * Allocates the resources necessary for the distance transform.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         */
        virtual void setup(IntensityWorkset <T> &image) { };

        /**
         * Initializes all parameters before traversing the image.
         *
         * Parameter            | in/out        | Comment
         * :---------           | :------       | :-------
         * input                | INPUT         | Contains the image, and its intensity span, on which to perform the distance transform.
         * bandIndex            | INPUT         | Index of the band to be processed.
         * neighborhoodSize     | INPUT         | The maximum number of neighbors that count as adjacent to a spatial element.
         * distanceTransform    | INPUT/OUTPUT  | Distance transform of the image band.
         * roots                | OUTPUT        | Source elements of the propagated distance values.
         * toQueue              | OUTPUT        | Spatial elements to be put on the priority queue.
         */
        virtual void initialize(const IntensityWorkset<T> &input, int bandIndex, int neighborhoodSize,
                        Image<double> &distanceTransform, Image<int> &roots, vector <PriorityQueueElement<T> > &toQueue) { };

        /**
         * Propagates the wave front to the next spatial element.
         *
         * Parameter            | in/out        | Comment
         * :---------           | :------       | :-------
         * image                | INPUT         | Input image for the distance transform.
         * bandIndex            | INPUT         | Index of the band to be processed.
         * neighborhoodSize     | INPUT         | The maximum number of neighbors that count as adjacent to a spatial element.
         * elementIndex         | INPUT         | Index of the spatial element being processed.
         * distanceTransform    | INPUT/OUTPUT  | Distance transform of the image.
         * roots                | OUTPUT        | Source spels of the propagated distance values.
         * toQueue              | OUTPUT        | Spatial elements to be put on the priority queue.
         */
        virtual void update(const IntensityWorkset <T> &image, int bandIndex, int neighborhoodSize, int elementIndex,
                    Image <double> &distanceTransform, Image <int> &roots,
                    vector <PriorityQueueElement<T> > &toQueue) { };

        /**
         * Clears and deletes the image data, in preparation for re-use for other images.
         */
        virtual void clear() { };
    };
}

#endif //DISTANCEMEASURE_H
