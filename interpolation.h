#ifndef LATTICELIBRARY_INTERPOLATION_H
#define LATTICELIBRARY_INTERPOLATION_H

#include <vector>
using std::vector;

namespace LatticeLib {

    template <class positionTemplate, class intensityTemplate>
    class Interpolation {

    public:
        virtual double apply(vector<positionTemplate> referencePositions, vector<intensityTemplate> referenceValues,
                             double intermediatePosition) = 0;

    };

}

#endif //LATTICELIBRARY_INTERPOLATION_H
