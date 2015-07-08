#ifndef VALUENORMALIZER_H
#define VALUENORMALIZER_H

#include "arrayadjustment.h"

namespace LatticeLib {

    /**
     * Class for normalizing values in a given range to [0,1].
     */
    class ValueNormalizer : public ArrayAdjustment {

    public:
        /**
         * Normalizes values in the range [minValue,maxValue] to [0,1]. Please note that if no value in the input array
         * equals minValue or maxValue, then none of the resulting values equals 0 or 1, respectively.
         * OBS! This does not work well for integers, as all values <maxValue are truncated to 0 after normalization.
         *
         * Parameter	| Comment
         * :-------		| :-------
         * array        | Array to be modified.
         * nElements    | \#elements in the array.
         * minValue     | Minimum value of input range.
         * maxValue     | Maximum value of input range.
         */
        template<class T>
        void apply(T *array, int nElements, T minValue, T maxValue) {
            if (minValue > maxValue) {
                throw incompatibleException();
            }
            T range = maxValue - minValue;
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                array[elementIndex] = (array[elementIndex] - minValue) / range;
            }
        }

    };

}

#endif //VALUENORMALIZER_H
