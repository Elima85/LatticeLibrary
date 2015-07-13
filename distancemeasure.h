#ifndef DISTANCEMEASURE_H
#define DISTANCEMEASURE_H

#include "priorityqueue.h"
#include "image.h"
#include "intensityworkset.h"

namespace LatticeLib {

    /**
    * Abstract class for distance measures to be used in distance transforms based on wave front propagation.
    */
    class DistanceMeasure {

    public:
        /**
         * Allocates the resources necessary for the distance transform.
         */
        template <class T>
        void initialize(Image<T> &image) {}

        /**
         * Resets all parameters before traversing the image.
         */
        template<class T>
        void reset(const Image<T> &image) { };

        /**
         * Propagates the wave front to the next spatial element.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :------   | :-------
         * image                | in        | input image
         * neighborhoodSize     | in        | The maximum number of neighbors that count as adjacent to a spel.
         * elementIndex         | in        | index of the current spatial element
         * labelIndex           | in        | index of the current object label
         * distanceTransform    | in/out    | distance transform of the image
         * roots                | out       | roots in the inverse forest transform
         * toQueue              | out       | spatial elements to be put on the priority queue
         *
         */
        template<class T>
        void update(const Image<T> &image, int neighborhoodSize, int elementIndex, int labelIndex,
                    Image<double> &distanceTransform, Image<int> &roots, vector<PriorityQueueElement<T> > &toQueue) {};

        /**
         * Clears and deletes the image data.
         */
        void clear() {};
    };
}

#endif