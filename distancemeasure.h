#ifndef DISTANCEMEASURE_H
#define DISTANCEMEASURE_H

#include "priorityqueue.h"
#include "image.h"
#include "intensityworkset.h"
#include "seed.h"

namespace LatticeLib {

    /**
    * Base class for distance measures to be used in distance transforms based on wave front propagation.
    */
    class DistanceMeasure {

    public:
        /**
         * Allocates the resources necessary for the distance transform.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         */
        template <class T>
        void setup(Image<T> &image) {}

        /**
         * Resets all parameters before traversing the image.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * image        | INPUT     | Input image for the distance transform.
         */
        template<class T>
        void initialize(const Image<T> &image, vector<Seed> seeds) { };

        /**
         * Propagates the wave front to the next spatial element.
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
        template<class T>
        void update(const Image<T> &image, int neighborhoodSize, int elementIndex, int labelIndex,
                    Image<double> &distanceTransform, Image<int> &roots, vector<PriorityQueueElement<T> > &toQueue) {};

        /**
         * Clears and deletes the image data, in preparation for re-use for other images.
         */
        void clear() {};
    };
}

#endif