#ifndef DISTANCEMEASURE_H
#define DISTANCEMEASURE_H

#include "priorityqueue.h"
#include "intensitycimage.h"
#include "distancecimage.h"
#include "rootcimage.h"

namespace CImage {

    /**
    * Abstract class for distance measures to be used in distance transforms based on wave front propagation.
    */
    class DistanceMeasure {

    protected:
        int neighborhoodSize;

    public:
        DistanceMeasure();
        ~DistanceMeasure();

        /**
        * Initializes the distance measure to fit the image of application.
        */
        template<class T>
        void initialize(const IntensityCImage<T> &image, int neighborhoodSize) = 0;

        /**
        * Propagates the wave front to the next spatial element.
        *
        * Parameter         | in/out    | Comment
        * :---------        | :------   | :-------
        * image             | in        | input image
        * distanceTransform | in/out    | distance transform of the image
        * roots             | out       | roots in the inverse forest transform
        * elementIndex      | in        | index of the current spatial element
        * labelIndex        | in        | index of the current object label
        * toQueue           | out       | spatial elements to be put on the priority queue
        *
        */
        template<class T>
        void update(const IntensityCImage<T> &image, DistanceCImage &distanceTransform, RootCImage &roots, int elementIndex, int labelIndex, vector<PriorityQueueElement<T> > &toQueue) = 0;

        /**
        * Clears up the remains of previous applications. Must be called after every application.
        */
        void clear() = 0;
    };
}

#endif