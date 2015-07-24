#ifndef LATTICELIBRARY_VECTORVALUEFINDER_H
#define LATTICELIBRARY_VECTORVALUEFINDER_H

#include <vector>

namespace LatticeLib {

    /**
     * Abstract base class for finding a vector element with some specific property.
     */
    template <class intensityTemplate>
    class VectorValueFinder {
    public:
        /**
         * Constructor for VectorIndexPicker objects.
         */
        VectorValueFinder() {}

        /**
         * Destructor for VectorIndexPicker objects.
         */
        virtual ~VectorValueFinder() {}

        /**
         * Returns the value of the vector element with some specific property.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * vector       | INPUT     | Vector in which to find the element.
         */
        virtual intensityTemplate getVectorElement(const vector<intensityTemplate> &vector) const = 0;

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

#endif //LATTICELIBRARY_VECTORVALUEFINDER_H
