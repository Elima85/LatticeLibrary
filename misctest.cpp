#ifndef MISCTEST
#define MISCTEST

#include "gtest/gtest.h"
#include "miscellaneous.h"
#include "defs.h"
#include "vectoroperators.h"

using namespace CImage;

/**
* bool isEven(int)
* int length() (of vector)
* int lowerBound(double*,int,double)
* vector<T> element-wise operators, tested for int and double.
*/

TEST(Miscellaneous, isEven) {
    EXPECT_TRUE(isEven(0));
    EXPECT_FALSE(isEven(1));
    EXPECT_TRUE(isEven(2));
    EXPECT_FALSE(isEven(3));
    EXPECT_TRUE(isEven(4));
    EXPECT_FALSE(isEven(5));
    EXPECT_TRUE(isEven(6));
    EXPECT_FALSE(isEven(7));
    EXPECT_TRUE(isEven(8));
    EXPECT_FALSE(isEven(9));
    EXPECT_TRUE(isEven(10));
}

TEST(Miscellaneous, lowerBound) {

    double numbers[10] = {0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    int length = 10;

    EXPECT_EQ(lowerBound(numbers, length, 0), 0);
    EXPECT_EQ(lowerBound(numbers, length, 10), 9);
    EXPECT_EQ(lowerBound(numbers, length, 5), 4);
    EXPECT_EQ(lowerBound(numbers, length, 7.7), 7);

    EXPECT_THROW(lowerBound(numbers, length, -1), outsideRangeException);
}

TEST(Miscellaneous, vectorTOperators) {

    // T = int
    int intVals[] = {-2, -1, 0, 3, 4};
    int intNegVals[] = {2, 1, 0, -3, -4};
    int intMinVals[] = {-2, -1, 0, -3, -4};
    int intMaxVals[] = {2, 1, 0, 3, 4};
    vector<int> intVector1, intVector2, intNegVector;
    intVector1.assign(intVals, intVals + 5);
    intVector2.assign(intVals, intVals + 5);
    intNegVector.assign(intNegVals, intNegVals + 5);
    vector<int> intVector3 = intVector1 + intNegVector;
    vector<int> intVector4 = intVector3 - intVector1;
    vector<int> intVector5(intVals, intVals + 4);
    vector<int> intVector6 = intVector1 - intVector1;
    vector<int> intMinVector(intMinVals, intMinVals + 5);
    vector<int> intMaxVector(intMaxVals, intMaxVals + 5);
    vector<int> intVector7 = minElements(intVector1, intNegVector);
    vector<int> intVector8 = maxElements(intVector1, intNegVector);
    vector<double> multiplicationResult;
    EXPECT_TRUE(intVector1 == intVector2);
    EXPECT_TRUE(intVector1 != intNegVector);
    EXPECT_TRUE(-intVector1 == intNegVector);
    EXPECT_TRUE(intVector1 == -intNegVector);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(intVector3[i], 0);
        EXPECT_EQ(intVector4[i], intNegVector[i]);
        EXPECT_EQ(intVector6[i], 0);
        EXPECT_EQ(intVector7[i], intMinVector[i]);
        EXPECT_EQ(intVector8[i], intMaxVector[i]);
    }
    multiplicationResult = 0 * intVector1;
    EXPECT_NEAR(multiplicationResult[0], 0, EPSILONT);
    EXPECT_NEAR(multiplicationResult[1], 0, EPSILONT);
    EXPECT_NEAR(multiplicationResult[2], 0, EPSILONT);
    EXPECT_NEAR(multiplicationResult[3], 0, EPSILONT);
    EXPECT_NEAR(multiplicationResult[4], 0, EPSILONT);
    multiplicationResult = 1 * intVector1;
    for (int i = 0; i < 5; i++) {
        EXPECT_NEAR(multiplicationResult[i], intVals[i], EPSILONT);
    }
    multiplicationResult = -1 * intVector1;
    for (int i = 0; i < 5; i++) {
        EXPECT_NEAR(multiplicationResult[i], intNegVals[i], EPSILONT);
    }
    multiplicationResult = 0.5 * intVector1;
    EXPECT_NEAR(multiplicationResult[0], -1, EPSILONT);
    EXPECT_NEAR(multiplicationResult[1], -0.5, EPSILONT);
    EXPECT_NEAR(multiplicationResult[2], 0, EPSILONT);
    EXPECT_NEAR(multiplicationResult[3], 1.5, EPSILONT);
    EXPECT_NEAR(multiplicationResult[4], 2, EPSILONT);
    EXPECT_THROW(intVector1 + intVector5, dimensionMismatchException);
    EXPECT_THROW(intVector1 - intVector5, dimensionMismatchException);
    EXPECT_THROW(minElements(intVector1, intVector5), dimensionMismatchException);
    EXPECT_THROW(maxElements(intVector1, intVector5), dimensionMismatchException);

    // T = double
    double doubleVals[] = {-2.2, -1.1, 0, 3.3, 4.4};
    double doubleNegVals[] = {2.2, 1.1, 0, -3.3, -4.4};
    double doubleMinVals[] = {-2.2, -1.1, 0, -3.3, -4.4};
    double doubleMaxVals[] = {2.2, 1.1, 0, 3.3, 4.4};
    vector<double> doubleVector1, doubleVector2, doubleNegVector;
    doubleVector1.assign(doubleVals, doubleVals + 5);
    doubleVector2.assign(doubleVals, doubleVals + 5);
    doubleNegVector.assign(doubleNegVals, doubleNegVals + 5);
    vector<double> doubleVector3 = doubleVector1 + doubleNegVector;
    vector<double> doubleVector4 = doubleVector3 - doubleVector1;
    vector<double> doubleVector5(doubleVals, doubleVals + 4);
    vector<double> doubleVector6 = doubleVector1 - doubleVector1;
    vector<double> doubleMinVector(doubleMinVals, doubleMinVals + 5);
    vector<double> doubleMaxVector(doubleMaxVals, doubleMaxVals + 5);
    vector<double> doubleVector7 = minElements(doubleVector1, doubleNegVector);
    vector<double> doubleVector8 = maxElements(doubleVector1, doubleNegVector);
    EXPECT_TRUE(doubleVector1 == doubleVector2);
    EXPECT_TRUE(doubleVector1 != doubleNegVector);
    EXPECT_TRUE(-doubleVector1 == doubleNegVector);
    EXPECT_TRUE(doubleVector1 == -doubleNegVector);
    for (int i = 0; i < 5; i++) {
        EXPECT_NEAR(doubleVector3[i], 0, EPSILONT);
        EXPECT_NEAR(doubleVector4[i], doubleNegVector[i], EPSILONT);
        EXPECT_NEAR(doubleVector6[i], 0, EPSILONT);
        EXPECT_NEAR(doubleVector7[i], doubleMinVector[i], EPSILONT);
        EXPECT_NEAR(doubleVector8[i], doubleMaxVector[i], EPSILONT);
    }
    multiplicationResult = 0 * doubleVector1;
    for (int i = 0; i < 5; i++) {
        EXPECT_NEAR(multiplicationResult[i], 0, EPSILONT);
    }
    multiplicationResult = 1 * doubleVector1;
    for (int i = 0; i < 5; i++) {
        EXPECT_NEAR(multiplicationResult[i], doubleVals[i], EPSILONT);
    }
    multiplicationResult = -1 * doubleVector1;
    for (int i = 0; i < 5; i++) {
        EXPECT_NEAR(multiplicationResult[i], doubleNegVals[i], EPSILONT);
    }
    multiplicationResult = 0.5 * doubleVector1;
    EXPECT_NEAR(multiplicationResult[0], -1.1, EPSILONT);
    EXPECT_NEAR(multiplicationResult[1], -0.55, EPSILONT);
    EXPECT_NEAR(multiplicationResult[2], 0, EPSILONT);
    EXPECT_NEAR(multiplicationResult[3], 1.65, EPSILONT);
    EXPECT_NEAR(multiplicationResult[4], 2.2, EPSILONT);

    EXPECT_THROW(doubleVector1 + doubleVector5, dimensionMismatchException);
    EXPECT_THROW(doubleVector1 - doubleVector5, dimensionMismatchException);
    EXPECT_THROW(minElements(doubleVector1, doubleVector5), dimensionMismatchException);
    EXPECT_THROW(maxElements(doubleVector1, doubleVector5), dimensionMismatchException);

}

#endif