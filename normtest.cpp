#ifndef NORMTEST
#define NORMTEST

#include "gtest/gtest.h"
#include "norm.h"
#include "defs.h"
#include "pnorm.h"
#include "productnorm.h"
#include "maximumnorm.h"

using namespace LatticeLib;

TEST(Norm, PNorm) {
    int intVals[] = {0, 1, 2, 3, 4, 5};
    vector<int> intVector;
    intVector.assign(intVals, intVals + 6);

    double doubleVals[] = {0.0, 1.1, 2.2, 3.3, 4.4};
    vector<double> doubleVector;
    doubleVector.assign(doubleVals, doubleVals + 5);

    vector<double> zeroVector;
    zeroVector.assign(3, 0.0);

    PNorm norm1(1);
    PNorm norm2(2);
    PNorm norm5(5);
    PNorm norm1Copy(norm1);
    PNorm norm5Copy(norm5);

    // constructor and getter
    EXPECT_EQ(norm1.getP(), 1);
    EXPECT_EQ(norm2.getP(), 2);
    EXPECT_EQ(norm5.getP(), 5);
    EXPECT_NE(norm1.getP(), 2);
    EXPECT_NE(norm2.getP(), 3);
    EXPECT_NE(norm5.getP(), 1);
    EXPECT_EQ(norm1Copy.getP(), 1);
    EXPECT_EQ(norm5Copy.getP(), 5);
    EXPECT_NE(norm1Copy.getP(), 2);
    EXPECT_NE(norm5Copy.getP(), 1);

    // compute
    EXPECT_NEAR(norm1.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(norm1.compute(intVector), 15.0, EPSILONT);
    EXPECT_NEAR(norm1.compute(doubleVector), 11.0, EPSILONT);

    EXPECT_NEAR(norm2.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(norm2.compute(intVector), 7.4161984871, EPSILONT);
    EXPECT_NEAR(norm2.compute(doubleVector), 6.02494813256, EPSILONT);

    EXPECT_NEAR(norm5.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(norm5.compute(intVector), 5.36022049567, EPSILONT);
    EXPECT_NEAR(norm5.compute(doubleVector), 4.61510254893, EPSILONT);
}

TEST(Norm, ProductNorm) {
    int intVals[] = {0, 1, 2, 3, 4, 5};
    vector<int> intVector1, intVector2;
    intVector1.assign(intVals, intVals + 6);
    intVector2.assign(intVals + 1, intVals + 6);

    double doubleVals[] = {0.0, 1.1, 2.2, 3.3, 4.4};
    vector<double> doubleVector1, doubleVector2;
    doubleVector1.assign(doubleVals, doubleVals + 5);
    doubleVector2.assign(doubleVals + 1, doubleVals + 5);

    vector<double> zeroVector;
    zeroVector.assign(3, 0.0);

    ProductNorm norm;
    ProductNorm normCopy(norm);

    // compute
    EXPECT_NEAR(norm.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(norm.compute(intVector1), 0.0, EPSILONT);
    EXPECT_NEAR(norm.compute(intVector2), 120.0, EPSILONT);
    EXPECT_NEAR(norm.compute(doubleVector1), 0.0, EPSILONT);
    EXPECT_NEAR(norm.compute(doubleVector2), 35.1384, EPSILONT);
    EXPECT_NEAR(norm.compute(intVector1), normCopy.compute(intVector1), EPSILONT);
    EXPECT_NEAR(norm.compute(doubleVector1), normCopy.compute(doubleVector1), EPSILONT);

}

TEST(Norm, MaximumNorm) {

    int intVals[] = {0, 1, 4, 5, 2, 3};
    vector<int> intVector;
    intVector.assign(intVals, intVals + 6);

    double doubleVals[] = {0.0, 3.3, 4.4, 1.1, 2.2};
    vector<double> doubleVector;
    doubleVector.assign(doubleVals, doubleVals + 5);

    vector<double> zeroVector;
    zeroVector.assign(3, 0.0);

    MaximumNorm norm;
    MaximumNorm normCopy(norm);

    // compute
    EXPECT_NEAR(norm.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(norm.compute(intVector), 5.0, EPSILONT);
    EXPECT_NEAR(norm.compute(doubleVector), 4.4, EPSILONT);
    EXPECT_NEAR(norm.compute(intVector), normCopy.compute(intVector), EPSILONT);
    EXPECT_NEAR(norm.compute(doubleVector), normCopy.compute(doubleVector), EPSILONT);

}


#endif