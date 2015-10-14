#ifndef LATTICELIBRARY_INTERPOLATION_H
#define LATTICELIBRARY_INTERPOLATION_H

#include <vector>
using std::vector;

namespace LatticeLib {

    /**
     * Class for interpolating a value within a series of values.
     */
    template <class positionTemplate, class intensityTemplate>
    class Interpolation {

    public:
        /**
         * Approximates the value at the specified position based on the values around it.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :------   | :-------
         * referencePositions   | INPUT     | Coordinates of the values in the series. Must be monotonically non-decreasing.
         * referenceValues      | INPUT     | Values at the coordinates defined by referencePositions. Must be of the same length as referencePositions.
         * intermediatePosition | INPUT     | Coordinate of interpolated value. Must be within the range of referencePositions.
         */
        virtual double apply(vector<positionTemplate> referencePositions, vector<intensityTemplate> referenceValues,
                             double intermediatePosition) const = 0;

    };

}

#endif //LATTICELIBRARY_INTERPOLATION_H
