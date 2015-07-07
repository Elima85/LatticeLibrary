#ifndef DISTANCEMEASURE_H
#define DISTANCEMEASURE_H

#include "priorityqueue.h"
#include "intensityimage.h"
#include "distanceimage.h"
#include "rootimage.h"

namespace LatticeLib {

    /**
    * Abstract class for distance measures to be used in distance transforms based on wave front propagation.
    */
    class DistanceMeasure {

    protected:
        int neighborhoodSize;

    public:
        DistanceMeasure() {
            neighborhoodSize = 0;
        }
        ~DistanceMeasure();

        /**
        * Initializes the distance measure to fit the image of application.
        */
        template<class T>
        void initialize(const IntensityImage<T> &image, int nS) {
            neighborhoodSize = nS;
        };

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
        void update(const IntensityImage<T> &image, DistanceImage &distanceTransform, RootImage &roots, int elementIndex, int labelIndex, vector<PriorityQueueElement<T> > &toQueue) {};

        /**
        * Clears up the remains of previous applications. Must be called after every application.
        */
        void clear(){
            neighborhoodSize = 0;
        };
    };
}

#endif