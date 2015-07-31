#include "gtest/gtest.h"
#include "linearinterpolation.h"
#include "defs.h"
#include "exception.h"
#include <vector>

using namespace LatticeLib;
using std::vector;

TEST(Interpolation, linearinterpolation) {

    LinearInterpolation<int,int> interpolation;

    vector<int> intPositions;
    vector<int> intValues;

    for (int vectorIndex = 0; vectorIndex < 5; vectorIndex++) {
        intPositions.push_back(vectorIndex);
        intValues.push_back(vectorIndex * 10);
    }

    double result;
    result = interpolation.apply(intPositions, intValues, 2.5);
    EXPECT_NEAR(25, result, EPSILONT);
    EXPECT_THROW(interpolation.apply(intPositions, intValues, -1.0), incompatibleParametersException);
    EXPECT_THROW(interpolation.apply(intPositions, intValues, 5.2), incompatibleParametersException);
    EXPECT_THROW(interpolation.apply(intPositions, vector<int>(intValues.begin(), intValues.end() - 1), 3), incompatibleParametersException);
}