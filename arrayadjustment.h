#ifndef ARRAYADJUSTMENT_H
#define ARRAYADJUSTMENT_H

namespace LatticeLib {

    /**
     * Parent class for adjusting the range and distribution of array values.
     *
     * If not for the templates, this class would have been an abstract base class. It's not meant to be used.
     */
    class ArrayAdjustment {

    public:
        /**
         * Adjusts the range and distribution of the values in the input array.
         * As this class would have been an abstract class, if not for the templates, the implementation here does nothing.
         *
         * Parameter	| Comment
         * :-------		| :-------
         * array        | Array to be modified.
         * nElements    | \#elements in the array.
         * value1       | Range and distribution parameter.
         * value2       | Range and distribution parameter.
         */
        template <class T>
        void apply(T* array, int nElements, T value1, T value2) const {}

    };

}

#endif //ARRAYADJUSTMENT_H
