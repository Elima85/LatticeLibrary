#ifndef VALUESTRETCHER_H
#define VALUESTRETCHER_H

#include "arrayadjustment.h"

namespace LatticeLib {

    /**
     * Class for stretching (or compressing) array values in the range [0,1] to the given range.
     */
    class ValueStretcher : public ArrayAdjustment {

    public:
        /**
         * Stretches (or compresses) the range of the array values from [0,1] to [minValue,maxValue].
         *
         * Parameter	| Comment
         * :-------		| :-------
         * array        | Array to be modified.
         * nElements    | \#elements in the array.
         * minValue     | Minimum value of output range.
         * maxValue     | Maximum value of output range.
         */
        template<class T>
        void apply(T *array, int nElements, T minValue, T maxValue) {
            T range = maxValue - minValue;
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                array[elementIndex] = array[elementIndex] * range + minValue;
            }
        }

    };

}

#endif //VALUESTRETCHER_H
