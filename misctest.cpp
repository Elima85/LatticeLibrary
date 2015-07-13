#include "gtest/gtest.h"
#include "miscellaneous.h"
#include "defs.h"
#include "vectoroperators.h"
#include "exception.h"
#include <cmath>

using namespace LatticeLib;

/**
* bool IS_EVEN(int)
* int lowerBound(double*,int,double)
* vector<T> element-wise operators, tested for int and double.
*/

TEST(Miscellaneous, IS_EVEN) {
    EXPECT_TRUE(IS_EVEN(0));
    EXPECT_FALSE(IS_EVEN(1));
    EXPECT_TRUE(IS_EVEN(2));
    EXPECT_FALSE(IS_EVEN(3));
    EXPECT_TRUE(IS_EVEN(4));
    EXPECT_FALSE(IS_EVEN(5));
    EXPECT_TRUE(IS_EVEN(6));
    EXPECT_FALSE(IS_EVEN(7));
    EXPECT_TRUE(IS_EVEN(8));
    EXPECT_FALSE(IS_EVEN(9));
    EXPECT_TRUE(IS_EVEN(10));
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
    double accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(intVector3[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(intVector6[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(intVector4[i] - intNegVector[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(intVector7[i] - intMinVector[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(intVector8[i] - intMaxVector[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);

    multiplicationResult = 0 * intVector1;
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(multiplicationResult[i]);
    }
    EXPECT_NEAR(accumulatedError, 0, EPSILONT);

    multiplicationResult = 1 * intVector1;
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(multiplicationResult[i] - intVals[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);

    multiplicationResult = -1 * intVector1;
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(multiplicationResult[i] - intNegVals[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);

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

    EXPECT_EQ(getIndexOfMinimumValue(intVector1),0);
    EXPECT_EQ(getIndexOfMinimumValue(intNegVector), 4);
    EXPECT_EQ(getIndexOfMinimumValue(intMinVector), 4);
    EXPECT_EQ(getIndexOfMinimumValue(intMaxVector), 2);

    EXPECT_EQ(getIndexOfMaximumValue(intVector1), 4);
    EXPECT_EQ(getIndexOfMaximumValue(intNegVector), 0);
    EXPECT_EQ(getIndexOfMaximumValue(intMinVector), 2);
    EXPECT_EQ(getIndexOfMaximumValue(intMaxVector), 4);

    EXPECT_EQ(sumOfElements(intVector1), 4);
    EXPECT_EQ(sumOfElements(intNegVector), -4);
    EXPECT_EQ(sumOfElements(intMinVector), -10);
    EXPECT_EQ(sumOfElements(intMaxVector), 10);

    EXPECT_NEAR(meanValue(intVector1), 0.8, EPSILONT);
    EXPECT_NEAR(meanValue(intNegVector), -0.8, EPSILONT);
    EXPECT_NEAR(meanValue(intMinVector), -2, EPSILONT);
    EXPECT_NEAR(meanValue(intMaxVector), 2, EPSILONT);

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
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(doubleVector3[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(doubleVector6[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(doubleVector4[i] - doubleNegVector[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(doubleVector7[i] - doubleMinVector[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(doubleVector8[i] - doubleMaxVector[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);

    multiplicationResult = 0 * doubleVector1;
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(multiplicationResult[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);

    multiplicationResult = 1 * doubleVector1;
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(multiplicationResult[i] - doubleVals[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);

    multiplicationResult = -1 * doubleVector1;
    accumulatedError = 0.0;
    for (int i = 0; i < 5; i++) {
        accumulatedError += fabs(multiplicationResult[i] - doubleNegVals[i]);
    }
    EXPECT_NEAR(accumulatedError, 0.0, EPSILONT);

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

    EXPECT_EQ(getIndexOfMinimumValue(doubleVector1), 0);
    EXPECT_EQ(getIndexOfMinimumValue(doubleNegVector), 4);
    EXPECT_EQ(getIndexOfMinimumValue(doubleMinVector), 4);
    EXPECT_EQ(getIndexOfMinimumValue(doubleMaxVector), 2);

    EXPECT_EQ(getIndexOfMaximumValue(doubleVector1), 4);
    EXPECT_EQ(getIndexOfMaximumValue(doubleNegVector), 0);
    EXPECT_EQ(getIndexOfMaximumValue(doubleMinVector), 2);
    EXPECT_EQ(getIndexOfMaximumValue(doubleMaxVector), 4);

    EXPECT_NEAR(sumOfElements(doubleVector1), 4.4, EPSILONT);
    EXPECT_NEAR(sumOfElements(doubleNegVector), -4.4, EPSILONT);
    EXPECT_NEAR(sumOfElements(doubleMinVector), -11, EPSILONT);
    EXPECT_NEAR(sumOfElements(doubleMaxVector), 11, EPSILONT);

    EXPECT_NEAR(meanValue(doubleVector1), 4.4/5, EPSILONT);
    EXPECT_NEAR(meanValue(doubleNegVector), -4.4/5, EPSILONT);
    EXPECT_NEAR(meanValue(doubleMinVector), -11.0/5.0, EPSILONT);
    EXPECT_NEAR(meanValue(doubleMaxVector), 11.0/5.0, EPSILONT);

}