#ifndef NORMTEST
#define NORMTEST

#include "gtest/gtest.h"
#include "../norm.h"
#include "../defs.h"
#include "../pnorm.h"
#include "../productnorm.h"
#include "../maximumnorm.h"

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

    PNorm<double> doubleNorm1(1);
    PNorm<double> doubleNorm2(2);
    PNorm<double> doubleNorm5(5);
    PNorm<double> doubleNorm1Copy(doubleNorm1);
    PNorm<double> doubleNorm5Copy(doubleNorm5);
    PNorm<int> intNorm1(1);
    PNorm<int> intNorm2(2);
    PNorm<int> intNorm5(5);

    // constructor and getter
    EXPECT_EQ(doubleNorm1.getP(), 1);
    EXPECT_EQ(doubleNorm2.getP(), 2);
    EXPECT_EQ(doubleNorm5.getP(), 5);
    EXPECT_NE(doubleNorm1.getP(), 2);
    EXPECT_NE(doubleNorm2.getP(), 3);
    EXPECT_NE(doubleNorm5.getP(), 1);
    EXPECT_EQ(doubleNorm1Copy.getP(), 1);
    EXPECT_EQ(doubleNorm5Copy.getP(), 5);
    EXPECT_NE(doubleNorm1Copy.getP(), 2);
    EXPECT_NE(doubleNorm5Copy.getP(), 1);

    // compute
    EXPECT_NEAR(doubleNorm1.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(intNorm1.compute(intVector), 15.0, EPSILONT);
    EXPECT_NEAR(doubleNorm1.compute(doubleVector), 11.0, EPSILONT);

    EXPECT_NEAR(doubleNorm2.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(intNorm2.compute(intVector), 7.4161984871, EPSILONT);
    EXPECT_NEAR(doubleNorm2.compute(doubleVector), 6.02494813256, EPSILONT);

    EXPECT_NEAR(doubleNorm5.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(intNorm5.compute(intVector), 5.36022049567, EPSILONT);
    EXPECT_NEAR(doubleNorm5.compute(doubleVector), 4.61510254893, EPSILONT);
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

    ProductNorm<double> doubleNorm;
    ProductNorm<double> doubleNormCopy(doubleNorm);
    ProductNorm<int> intNorm;
    ProductNorm<int> intNormCopy(intNorm);

    // compute
    EXPECT_NEAR(doubleNorm.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(intNorm.compute(intVector1), 0.0, EPSILONT);
    EXPECT_NEAR(intNorm.compute(intVector2), 120.0, EPSILONT);
    EXPECT_NEAR(doubleNorm.compute(doubleVector1), 0.0, EPSILONT);
    EXPECT_NEAR(doubleNorm.compute(doubleVector2), 35.1384, EPSILONT);
    EXPECT_NEAR(intNorm.compute(intVector1), intNorm.compute(intVector1), EPSILONT);
    EXPECT_NEAR(doubleNorm.compute(doubleVector1), doubleNormCopy.compute(doubleVector1), EPSILONT);

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

    MaximumNorm<double> doubleNorm;
    MaximumNorm<double> doubleNormCopy(doubleNorm);
    MaximumNorm<int> intNorm;
    MaximumNorm<int> intNormCopy(intNorm);

    // compute
    EXPECT_NEAR(doubleNorm.compute(zeroVector), 0.0, EPSILONT);
    EXPECT_NEAR(intNorm.compute(intVector), 5.0, EPSILONT);
    EXPECT_NEAR(doubleNorm.compute(doubleVector), 4.4, EPSILONT);
    EXPECT_NEAR(intNorm.compute(intVector), intNorm.compute(intVector), EPSILONT);
    EXPECT_NEAR(doubleNorm.compute(doubleVector), doubleNormCopy.compute(doubleVector), EPSILONT);

}


#endif