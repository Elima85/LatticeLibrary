#ifndef LATTICELIBRARY_MAXIMUMVALUEFINDER_H
#define LATTICELIBRARY_MAXIMUMVALUEFINDER_H

#include "vectorindexpicker.h"
#include <vector>
#include "defs.h"

namespace LatticeLib {
    /**
     * Class for finding the index of the maximum value in a vector.
     */
    template<class intensityTemplate>
    class MaximumValueFinder : public VectorIndexPicker<intensityTemplate> {
    public:
        /**
         * Implements VectorIndexPicker::getVectorElementIndex().
         *
         * Returns the index of the maximum value in the vector.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * vector       | INPUT     | Vector in which to find the element.
         */
        int getVectorElementIndex(const vector<intensityTemplate> &vector) const {
            int length = vector.size();
            int indexOfMaximumValue;
            double minValue = -INF;
            for (int elementIndex = 0; elementIndex < length; elementIndex++) {
                if (vector[elementIndex] < minValue) {
                    minValue = vector[elementIndex];
                    indexOfMaximumValue = elementIndex;
                }
            }
            return indexOfMaximumValue;
        }
    };
}

#endif //LATTICELIBRARY_MAXIMUMVALUEFINDER_H
