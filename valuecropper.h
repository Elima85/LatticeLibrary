#ifndef VALUECROPPER_H
#define VALUECROPPER_H

#include "arrayadjustment.h"
#include "exception.h"

namespace LatticeLib {

    /**
     * Class for cropping the values of array entries, so that they fit into a defined range.
     */
    class ValueCropper : public ArrayAdjustment {

    public:
        /**
         * Crops the values of the array entries, so that they are in the range [minValue,maxValue].
         *
         * Parameter	| Comment
         * :-------		| :-------
         * array        | Array to be modified.
         * nElements    | \#elements in the array.
         * minValue     | Minimum limit for the array elements.
         * maxValue     | Maximum limit for the array elements.
         */
        template<class T>
        void apply(T* array, int nElements, T minValue, T maxValue) const {
            if (minValue > maxValue) {
                throw incompatibleException();
            }
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                array[elementIndex] = MIN(maxValue, MAX(minValue, array[elementIndex]));
            }
        }

    };

}

#endif //VALUECROPPER_H
