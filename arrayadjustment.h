#ifndef ARRAYADJUSTMENT_H
#define ARRAYADJUSTMENT_H

namespace LatticeLib {

    /**
     * Base class for adjusting the range and distribution of array values.
     */
    class ArrayAdjustment {

    public:
        /**
         * Adjusts the range and distribution of the values in the input array. The implementation in the base class
         * does nothing.
         *
         * Parameter	| Comment
         * :-------		| :-------
         * array        | Array to be modified.
         * nElements    | Number of elements in the array.
         * value1       | Range and distribution parameter.
         * value2       | Range and distribution parameter.
         */
        template <class T>
        void apply(T* array, int nElements, T value1, T value2) const {}

    };

}

#endif //ARRAYADJUSTMENT_H
