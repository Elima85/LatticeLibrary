#ifndef LATTICELIBRARY_LINEARINTERPOLATION_H
#define LATTICELIBRARY_LINEARINTERPOLATION_H

#include "interpolation.h"
#include "exception.h"
#include <vector>
#include <stdio.h> // DEBUG

namespace LatticeLib {

    /**
     * Class for linear interpolation of a value within a series of values.
     */
    template<class positionTemplate, class intensityTemplate>
    class LinearInterpolation : public Interpolation<positionTemplate, intensityTemplate> {

    public:
        /**
         * Implements Interpolation::apply().
         *
         * Approximates the value at the specified position using linear interpolation.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :------   | :-------
         * referencePositions   | INPUT     | Coordinates of the values in the series. Must be monotonically non-decreasing and contain at least two elements.
         * referenceValues      | INPUT     | Values at the coordinates defined by referencePositions. Must be of the same length as referencePositions.
         * intermediatePosition | INPUT     | Coordinate of interpolated value. Must be within the range of referencePositions.
         */
        double apply(vector <positionTemplate> referencePositions, vector <intensityTemplate> referenceValues,
                     double intermediatePosition) const {
            //std::cout << "Inside LinearInterpolation::apply()" << std::endl;
            if ((referencePositions.size() < 2) || (referencePositions.size() != referenceValues.size())) {
                std::cout << "LinearInterpolation.apply(): #positions: " << referencePositions.size() << ", #values: " << referenceValues.size() << endl;
                throw incompatibleParametersException();
            }
            double position1, position2, value1, value2;
            double result;
            bool found = false;
            for (int positionIndex = 0; positionIndex < referencePositions.size() - 1; positionIndex++) {
                if ((referencePositions[positionIndex] <= intermediatePosition) && (referencePositions[positionIndex + 1] >= intermediatePosition)) {
                    position1 = referencePositions[positionIndex];
                    position2 = referencePositions[positionIndex + 1];
                    value1 = referenceValues[positionIndex];
                    value2 = referenceValues[positionIndex + 1];
                    found = true;
                    //std::cout << "Found value." << std::endl;
                }
            }
            if (found) {
                double inclination = (value2 - value1) / (position2 - position1);
                double subStep = intermediatePosition - position1;
                result =  value1 + subStep * inclination;
            }
            else {
                std::cout << "LinearInterpolation.apply(): " << intermediatePosition << " is not in the span [" << referencePositions[0] << ", " << referencePositions[referencePositions.size() - 1] << "]." << std::endl;
                throw incompatibleParametersException();
            }
            return result;
        }

    };

}

#endif //LATTICELIBRARY_LINEARINTERPOLATION_H
