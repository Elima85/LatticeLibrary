#include "gtest/gtest.h"
#include "defs.h"
#include "filtercoefficient.h"
#include "spatialtemplate.h"
#include <cmath>
#include <vector>
#include "cclattice.h"
#include <stdio.h>

using namespace LatticeLib;

TEST(FilterCoefficient, initialization) {
    // constructor
    int indices[3] = {0,1,2};
    int intCoefficients[3] = {-1,0,2};
    double doubleCoefficients[3] = {-1.1,0.0,2.2};
    bool boolCoefficients[3] = {false,true,false};

    FilterCoefficient<bool> boolEmptyFilterCoefficient;
    FilterCoefficient<int> intEmptyFilterCoefficient;
    FilterCoefficient<double> doubleEmptyCoefficient;
    EXPECT_EQ(boolEmptyFilterCoefficient.getPositionIndex(),0);
    EXPECT_EQ(intEmptyFilterCoefficient.getPositionIndex(),0);
    EXPECT_EQ(doubleEmptyCoefficient.getPositionIndex(),0);
    EXPECT_EQ(boolEmptyFilterCoefficient.getCoefficient(),false);
    EXPECT_EQ(intEmptyFilterCoefficient.getCoefficient(),0);
    EXPECT_NEAR(doubleEmptyCoefficient.getCoefficient(),0.0, EPSILONT);

    vector<FilterCoefficient<bool> > boolFilterCoefficient;
    vector<FilterCoefficient<int> > intFilterCoefficient;
    vector<FilterCoefficient<double> > doubleFilterCoefficient;

    for (int i = 0; i < 3; i++) {
        boolFilterCoefficient.push_back(FilterCoefficient<bool>(indices[i], boolCoefficients[i]));
        intFilterCoefficient.push_back(FilterCoefficient<int>(indices[i], intCoefficients[i]));
        doubleFilterCoefficient.push_back(FilterCoefficient<double>(indices[i], doubleCoefficients[i]));
    }

    // getters
    for (int index = 0; index < 3; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));

        EXPECT_EQ(boolFilterCoefficient[index].getPositionIndex(), indices[index]);
        EXPECT_EQ(boolFilterCoefficient[index].getCoefficient(), boolCoefficients[index]);

        EXPECT_EQ(intFilterCoefficient[index].getPositionIndex(), indices[index]);
        EXPECT_EQ(intFilterCoefficient[index].getCoefficient(), intCoefficients[index]);

        EXPECT_NEAR(doubleFilterCoefficient[index].getCoefficient(), doubleCoefficients[index], EPSILONT);
        EXPECT_EQ(doubleFilterCoefficient[index].getPositionIndex(), indices[index]);
    }

    // setters
    int ind2[3] = {1,2,3};
    int ci2[3] = {-2,1,0};
    double cd2[3] = {0.0,2.2,1.1};
    bool cb2[3] = {true,false,true};

    for (int i = 0; i < 3; i++) {
        boolFilterCoefficient[i].setPositionIndex(ind2[i]);
        intFilterCoefficient[i].setPositionIndex(ind2[i]);
        doubleFilterCoefficient[i].setPositionIndex(ind2[i]);

        boolFilterCoefficient[i].setCoefficient(cb2[i]);
        intFilterCoefficient[i].setCoefficient(ci2[i]);
        doubleFilterCoefficient[i].setCoefficient(cd2[i]);
    }
    for (int index = 0; index < 3; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));

        EXPECT_TRUE(boolFilterCoefficient[index].getPositionIndex() != indices[index]);
        EXPECT_EQ(boolFilterCoefficient[index].getPositionIndex(), ind2[index]);
        EXPECT_EQ(boolFilterCoefficient[index].getCoefficient(), cb2[index]);
        EXPECT_TRUE(boolFilterCoefficient[index].getCoefficient() != boolCoefficients[index]);

        EXPECT_TRUE(intFilterCoefficient[index].getPositionIndex() != indices[index]);
        EXPECT_EQ(intFilterCoefficient[index].getPositionIndex(), ind2[index]);
        EXPECT_EQ(intFilterCoefficient[index].getCoefficient(), ci2[index]);
        EXPECT_TRUE(intFilterCoefficient[index].getCoefficient() != intCoefficients[index]);

        EXPECT_TRUE(doubleFilterCoefficient[index].getPositionIndex() != indices[index]);
        EXPECT_EQ(doubleFilterCoefficient[index].getPositionIndex(), ind2[index]);
        EXPECT_NEAR(doubleFilterCoefficient[index].getCoefficient(), cd2[index], EPSILONT);
        EXPECT_TRUE(fabs(doubleFilterCoefficient[index].getCoefficient() - doubleCoefficients[index]) > EPSILONT);
    }

    for (int i = 0; i < 3; i++) {
        boolFilterCoefficient[i].set(indices[i], boolCoefficients[i]);
        intFilterCoefficient[i].set(indices[i], intCoefficients[i]);
        doubleFilterCoefficient[i].set(indices[i], doubleCoefficients[i]);
    }
    for (int index = 0; index < 3; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));

        EXPECT_EQ(boolFilterCoefficient[index].getPositionIndex(), indices[index]);
        EXPECT_EQ(intFilterCoefficient[index].getPositionIndex(), indices[index]);
        EXPECT_EQ(doubleFilterCoefficient[index].getPositionIndex(), indices[index]);

        EXPECT_EQ(boolFilterCoefficient[index].getCoefficient(), boolCoefficients[index]);
        EXPECT_EQ(intFilterCoefficient[index].getCoefficient(), intCoefficients[index]);
        EXPECT_NEAR(doubleFilterCoefficient[index].getCoefficient(), doubleCoefficients[index], EPSILONT);
    }
}