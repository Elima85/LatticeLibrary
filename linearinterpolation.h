#ifndef LATTICELIBRARY_LINEARINTERPOLATION_H
#define LATTICELIBRARY_LINEARINTERPOLATION_H

#include "interpolation.h"
#include "exception.h"
#include <vector>

namespace LatticeLib {

    template<class positionTemplate, class intensityTemplate>
    class LinearInterpolation : public Interpolation<positionTemplate, intensityTemplate> {

    public:
        double apply(vector <positionTemplate> referencePositions, vector <intensityTemplate> referenceValues,
                     double intermediatePosition) {
            if ((referencePositions.size() < 2) || (referencePositions.size() != referenceValues.size())) {
                throw incompatibleParametersException();
            }
            positionTemplate position1, position2, value1, value2;
            double result;
            bool found = false;
            for (int positionIndex = 0; positionIndex < referencePositions.size() - 1; positionIndex++) {
                if ((referencePositions[positionIndex] < intermediatePosition) && (referencePositions[positionIndex + 1] > intermediatePosition)) {
                    position1 = referencePositions[positionIndex];
                    position2 = referencePositions[positionIndex + 1];
                    value1 = referenceValues[positionIndex];
                    value2 = referenceValues[positionIndex + 1];
                    found = true;
                }
            }
            if (found) {
                double inclination = (value2 - value1) / (position2 - position1);
                double subStep = intermediatePosition - position1;
                result =  value1 + subStep * inclination;
            }
            else {
                throw incompatibleParametersException();
            }
            return result;
        }

    };

}

#endif //LATTICELIBRARY_LINEARINTERPOLATION_H
