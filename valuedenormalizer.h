#ifndef VALUEDENORMALIZER_H
#define VALUEDENORMALIZER_H

#include "arrayadjustment.h"

namespace LatticeLib {

    /**
     * Class for stretching or compressing array values in the range [0,1] to the given range.
     */
    class ValueDenormalizer : public ArrayAdjustment {

    public:
        /**
         * Overloads ArrayAdjustment::apply().
         *
         * Stretches or compresses the range of the array values from [0,1] to [minValue,maxValue]. Please note that
         * if no value in the input array equals 0 or 1, then none of the resulting values equals minValue or maxValue,
         * respectively.
         *
         * Parameter	| Comment
         * :-------		| :-------
         * array        | Array to be modified.
         * nElements    | Number of elements in the array.
         * minValue     | Minimum value of output range.
         * maxValue     | Maximum value of output range.
         */
        template<class T>
        void apply(T *array, int nElements, T minValue, T maxValue) const {
            if (minValue > maxValue) {
                throw incompatibleException();
            }
            T range = maxValue - minValue;
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                array[elementIndex] = array[elementIndex] * range + minValue;
            }
        }

    };

}

#endif //VALUEDENORMALIZER_H
