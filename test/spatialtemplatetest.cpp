#include "gtest/gtest.h"
#include "../defs.h"
#include "../filtercoefficient.h"
#include "../spatialtemplate.h"
#include <vector>

using namespace LatticeLib;
using std::string;
using std::to_string; // TODO: Why do I need this?!

TEST(SpatialTemplate, initialization) {

    int positionIndices[4] = {-1, 0, 1, 3};
    double coefficientValues[4] = {2.2, 0, -1.1, 16.16};
    int neighborhoodSize = 6;
    vector <FilterCoefficient<double>> filterCoefficients;
    for (int i = 0;i < 4; i++) {
        filterCoefficients.push_back(FilterCoefficient<double>(positionIndices[i], coefficientValues[i]));
    }
    SpatialTemplate <double> filter(filterCoefficients, neighborhoodSize);

    // getters
    for ( int index = 0; index < 3; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));

        vector <FilterCoefficient<double>> extractedFilterCoefficients = filter.getCoefficients();
        EXPECT_EQ(extractedFilterCoefficients[index].getPositionIndex(), filterCoefficients[index].getPositionIndex());
        EXPECT_NEAR(extractedFilterCoefficients[index].getCoefficient(), filterCoefficients[index].getCoefficient(), EPSILONT);
    }

    for (int index = 0;index < 3; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));

        FilterCoefficient <double> c = filter.getCoefficient(index);
        EXPECT_EQ(c.getPositionIndex(), filterCoefficients[index].getPositionIndex());
        EXPECT_NEAR(c.getCoefficient(), filterCoefficients[index].getCoefficient(), EPSILONT);
    }

    EXPECT_EQ(filter.getNeighborhoodSize(), neighborhoodSize);
    EXPECT_TRUE(filter.getNeighborhoodSize() != neighborhoodSize - 1);
    EXPECT_EQ(filter.getNCoefficients(),4);
    EXPECT_TRUE(filter.getNCoefficients() != 5);

    EXPECT_EQ(filter.findCoefficient(-1), 0);
    EXPECT_EQ(filter.findCoefficient(1), 2);
    EXPECT_EQ(filter.findCoefficient(2), -1);
}
