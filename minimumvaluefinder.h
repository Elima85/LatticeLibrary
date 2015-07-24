#ifndef LATTICELIBRARY_MINIMUMVALUEFINDER_H
#define LATTICELIBRARY_MINIMUMVALUEFINDER_H

#include "vectorvaluefinder.h"
#include <vector>
#include "defs.h"

namespace LatticeLib {
    /**
     * Class for finding the minimum value in a vector.
     */
    template<class intensityTemplate>
    class MinimumValueFinder : public VectorValueFinder<intensityTemplate> {
    public:
        /**
         * Implements VectorIndexPicker::getVectorElement().
         *
         * Returns the minimum value in the vector.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * vector       | INPUT     | Vector in which to find the element.
         */
        intensityTemplate getVectorElement(const vector<intensityTemplate> &vector) const {
            int length = vector.size();
            intensityTemplate minValue = INF;
            for (int elementIndex = 0; elementIndex < length; elementIndex++) {
                if (vector[elementIndex] < minValue) {
                    minValue = vector[elementIndex];
                }
            }
            return minValue;
        }

        /**
         * Implements VectorIndexPicker::getVectorElementIndex().
         *
         * Returns the index of the minimum value in the vector.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * vector       | INPUT     | Vector in which to find the element.
         */
        int getVectorElementIndex(const vector<intensityTemplate> &vector) const {
            int length = vector.size();
            int indexOfMinimumValue;
            double minValue = INF;
            for (int elementIndex = 0; elementIndex < length; elementIndex++) {
                if (vector[elementIndex] < minValue) {
                    minValue = vector[elementIndex];
                    indexOfMinimumValue = elementIndex;
                }
            }
            return indexOfMinimumValue;
        }
    };
}

#endif //LATTICELIBRARY_MINIMUMVALUEFINDER_H
