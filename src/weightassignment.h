#ifndef LATTICELIBRARY_WEIGHTASSIGNMENT_H
#define LATTICELIBRARY_WEIGHTASSIGNMENT_H

#include "image.h"

namespace LatticeLib {

    /**
     * Abstract base class for assigning weights to spatial elements of Image objects, to be used in computations of weighted averages.
     */
    template <class intensityTemplate>
    class WeightAssignment {
    public:
        /**
         * Computes a weight for a spatial element of an Image object, based on the characteristics of that Image and a
         * reference Image object.
         *
         * Parameter		        | in/out	| Comment
         * :---------		        | :------	| :-------
         * referenceElementIndex    | INPUT     | Index of the reference element for the weight computation.
         * referenceImage           | INPUT     | Image to which the reference element belongs.
         * inputElementIndex        | INPUT     | Index of the element that is to be assigned a weight.
         * inputImage               | INPUT     | Image to which the element to be weighted belongs.
         */
        virtual double compute(int referenceElementIndex, Image<intensityTemplate> referenceImage, int inputElementIndex, Image<intensityTemplate> inputImage) const = 0;
    };
}

#endif //LATTICELIBRARY_WEIGHTASSIGNMENT_H
