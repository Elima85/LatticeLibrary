#ifndef LATTICELIBRARY_MEDIANVALUEFINDER_H
#define LATTICELIBRARY_MEDIANVALUEFINDER_H

#include "vectorvaluefinder.h"
#include <vector>
#include "defs.h"

namespace LatticeLib {
    /**
     * Class for finding the median value in a vector.
     */
    template<class intensityTemplate>
    class MedianValueFinder : public VectorValueFinder<intensityTemplate> {
    public:
        /**
         * Implements VectorIndexPicker::getVectorElement().
         *
         * Returns the median value of the vector.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * vector       | INPUT     | Vector in which to find the element.
         */
        intensityTemplate getVectorElement(const vector<intensityTemplate> &vector) const {
            double median;
            std::vector<intensityTemplate> sortedVector(vector);
            int size = sortedVector.size();
            sort(sortedVector.begin(), sortedVector.end());
            if (IS_EVEN(size)) {
                median = intensityTemplate(double(sortedVector[size / 2 - 1] + sortedVector[size / 2]) * 0.5);
            }
            else {
                median = intensityTemplate(sortedVector[(size - 1) / 2 + 1]);
            }
            return intensityTemplate(median);
        }

        /**
         * Implements VectorIndexPicker::getVectorElement().
         *
         * Returns the index of the vector element with the value closest to the median value of the vector.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * vector       | INPUT     | Vector in which to find the element.
         */
        int getVectorElementIndex(const vector <intensityTemplate> &vector) const {
            intensityTemplate median = getVectorElement(vector);
            int medianIndex;
            double differenceFromMedian = INF;
            for (int vectorElementIndex = 0; vectorElementIndex < vector.size(); vectorElementIndex++) {
                if (fabs(median - vector[vectorElementIndex]) < differenceFromMedian) {
                    medianIndex = vectorElementIndex;
                    differenceFromMedian = fabs(median - vector[vectorElementIndex]);
                }
            }
            return medianIndex;
        }
    };
}

#endif //LATTICELIBRARY_MEDIANVALUEFINDER_H
