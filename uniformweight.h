#ifndef LATTICELIBRARY_UNIFORMWEIGHT_H
#define LATTICELIBRARY_UNIFORMWEIGHT_H

#include "image.h"
#include "weightassignment.h"
#include "exception.h"
#include "lattice.h"

namespace LatticeLib {

    /**
     * Class for plain average weighting.
     */
    template<class intensityTemplate>
    class UniformWeight: public WeightAssignment<intensityTemplate> {
    public:
        /**
         * Implements WeightAssignment.compute().
         *
         * Returns 1.0. Meant to be used for plain average.
         *
         * Parameter		        | in/out	| Comment
         * :---------		        | :------	| :-------
         * referenceElementIndex    | INPUT     | Index of the reference element for the weight computation.
         * referenceImage           | INPUT     | Image to which the reference element belongs.
         * inputElementIndex        | INPUT     | Index of the element that is to be assigned a weight.
         * inputImage               | INPUT     | Image to which the element to be weighted belongs.
         */
        double compute(int referenceElementIndex, Image<intensityTemplate> referenceImage,
                               int inputElementIndex, Image<intensityTemplate> inputImage) const {
            if (!referenceImage.getLattice().isValid(referenceElementIndex) || !inputImage.getLattice().isValid(inputElementIndex)) {
                throw outOfRangeException();
            }
            return 1.0;
        }
    };
}

#endif //LATTICELIBRARY_UNIFORMWEIGHT_H
