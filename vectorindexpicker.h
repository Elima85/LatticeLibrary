#ifndef LATTICELIBRARY_VECTORINDEXPICKER_H
#define LATTICELIBRARY_VECTORINDEXPICKER_H

#include <vector>

namespace LatticeLib {

    /**
     * Abstract base class for finding the index of a vector element with some specific property.
     */
    template <class intensityTemplate>
    class VectorIndexPicker {
    public:
        /**
         * Constructor for VectorIndexPicker objects.
         */
        VectorIndexPicker() {}

        /**
         * Destructor for VectorIndexPicker objects.
         */
        virtual ~VectorIndexPicker() {}

        /**
         * Returns the index of a vector element with some specific property.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * vector       | INPUT     | Vector in which to find the element.
         */
        virtual int getVectorElementIndex(const vector<intensityTemplate> &vector) const = 0;
    };
}

#endif //LATTICELIBRARY_VECTORINDEXPICKER_H
