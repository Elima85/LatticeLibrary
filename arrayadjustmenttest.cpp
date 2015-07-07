#include "gtest/gtest.h"
#include "defs.h"
#include "arrayadjustment.h"
#include "valuecropper.h"
#include "valuenormalizer.h"
#include "valuestretcher.h"
#include "exception.h"
#include <stdio.h>

using namespace LatticeLib;

TEST(ValueCropper,valuecroppertest) {

    int size = 10;
    int intTestArray[10] = {0,1,2,3,4,5,6,7,8,9};
    double doubleTestArray[10] = {0.0,1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9};

    ValueCropper cropper;

    // T = int
    EXPECT_THROW(cropper.apply(intTestArray, size,5,4), incompatibleException);
    EXPECT_EQ(0, intTestArray[0]);
    EXPECT_EQ(1, intTestArray[1]);
    EXPECT_EQ(2, intTestArray[2]);
    EXPECT_EQ(3, intTestArray[3]);
    EXPECT_EQ(4, intTestArray[4]);
    EXPECT_EQ(5, intTestArray[5]);
    EXPECT_EQ(6, intTestArray[6]);
    EXPECT_EQ(7, intTestArray[7]);
    EXPECT_EQ(8, intTestArray[8]);
    cropper.apply(intTestArray, size,-1,10);
    EXPECT_EQ(0,intTestArray[0]);
    EXPECT_EQ(1, intTestArray[1]);
    EXPECT_EQ(2, intTestArray[2]);
    EXPECT_EQ(3, intTestArray[3]);
    EXPECT_EQ(4, intTestArray[4]);
    EXPECT_EQ(5, intTestArray[5]);
    EXPECT_EQ(6, intTestArray[6]);
    EXPECT_EQ(7, intTestArray[7]);
    EXPECT_EQ(8, intTestArray[8]);
    EXPECT_EQ(9, intTestArray[9]);
    cropper.apply(intTestArray, size, 0, 9);
    EXPECT_EQ(0, intTestArray[0]);
    EXPECT_EQ(1, intTestArray[1]);
    EXPECT_EQ(2, intTestArray[2]);
    EXPECT_EQ(3, intTestArray[3]);
    EXPECT_EQ(4, intTestArray[4]);
    EXPECT_EQ(5, intTestArray[5]);
    EXPECT_EQ(6, intTestArray[6]);
    EXPECT_EQ(7, intTestArray[7]);
    EXPECT_EQ(8, intTestArray[8]);
    EXPECT_EQ(9, intTestArray[9]);
    cropper.apply(intTestArray, size, 2, 7);
    EXPECT_EQ(2, intTestArray[0]);
    EXPECT_EQ(2, intTestArray[1]);
    EXPECT_EQ(2, intTestArray[2]);
    EXPECT_EQ(3, intTestArray[3]);
    EXPECT_EQ(4, intTestArray[4]);
    EXPECT_EQ(5, intTestArray[5]);
    EXPECT_EQ(6, intTestArray[6]);
    EXPECT_EQ(7, intTestArray[7]);
    EXPECT_EQ(7, intTestArray[8]);
    EXPECT_EQ(7, intTestArray[9]);
    cropper.apply(intTestArray, size, 5, 5);
    EXPECT_EQ(5, intTestArray[0]);
    EXPECT_EQ(5, intTestArray[1]);
    EXPECT_EQ(5, intTestArray[2]);
    EXPECT_EQ(5, intTestArray[3]);
    EXPECT_EQ(5, intTestArray[4]);
    EXPECT_EQ(5, intTestArray[5]);
    EXPECT_EQ(5, intTestArray[6]);
    EXPECT_EQ(5, intTestArray[7]);
    EXPECT_EQ(5, intTestArray[8]);
    EXPECT_EQ(5, intTestArray[9]);
    cropper.apply(intTestArray, size, 9, 10);
    EXPECT_EQ(9, intTestArray[0]);
    EXPECT_EQ(9, intTestArray[1]);
    EXPECT_EQ(9, intTestArray[2]);
    EXPECT_EQ(9, intTestArray[3]);
    EXPECT_EQ(9, intTestArray[4]);
    EXPECT_EQ(9, intTestArray[5]);
    EXPECT_EQ(9, intTestArray[6]);
    EXPECT_EQ(9, intTestArray[7]);
    EXPECT_EQ(9, intTestArray[8]);
    EXPECT_EQ(9, intTestArray[9]);
    cropper.apply(intTestArray, size, 1, 2);
    EXPECT_EQ(2, intTestArray[0]);
    EXPECT_EQ(2, intTestArray[1]);
    EXPECT_EQ(2, intTestArray[2]);
    EXPECT_EQ(2, intTestArray[3]);
    EXPECT_EQ(2, intTestArray[4]);
    EXPECT_EQ(2, intTestArray[5]);
    EXPECT_EQ(2, intTestArray[6]);
    EXPECT_EQ(2, intTestArray[7]);
    EXPECT_EQ(2, intTestArray[8]);
    EXPECT_EQ(2, intTestArray[9]);

    // T = double
    EXPECT_THROW(cropper.apply(doubleTestArray, size, 5.0, 4.0), incompatibleException);
    EXPECT_NEAR(0.0, doubleTestArray[0], EPSILONT);
    EXPECT_NEAR(1.1, doubleTestArray[1], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[2], EPSILONT);
    EXPECT_NEAR(3.3, doubleTestArray[3], EPSILONT);
    EXPECT_NEAR(4.4, doubleTestArray[4], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[5], EPSILONT);
    EXPECT_NEAR(6.6, doubleTestArray[6], EPSILONT);
    EXPECT_NEAR(7.7, doubleTestArray[7], EPSILONT);
    EXPECT_NEAR(8.8, doubleTestArray[8], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[9], EPSILONT);
    cropper.apply(doubleTestArray, size, -1.1, 10.1);
    EXPECT_NEAR(0.0, doubleTestArray[0], EPSILONT);
    EXPECT_NEAR(1.1, doubleTestArray[1], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[2], EPSILONT);
    EXPECT_NEAR(3.3, doubleTestArray[3], EPSILONT);
    EXPECT_NEAR(4.4, doubleTestArray[4], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[5], EPSILONT);
    EXPECT_NEAR(6.6, doubleTestArray[6], EPSILONT);
    EXPECT_NEAR(7.7, doubleTestArray[7], EPSILONT);
    EXPECT_NEAR(8.8, doubleTestArray[8], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[9], EPSILONT);
    cropper.apply(doubleTestArray, size, 0.0 - 0.5*EPSILONT, 9.9 + 0.5 *EPSILONT);
    EXPECT_NEAR(0.0, doubleTestArray[0], EPSILONT);
    EXPECT_NEAR(1.1, doubleTestArray[1], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[2], EPSILONT);
    EXPECT_NEAR(3.3, doubleTestArray[3], EPSILONT);
    EXPECT_NEAR(4.4, doubleTestArray[4], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[5], EPSILONT);
    EXPECT_NEAR(6.6, doubleTestArray[6], EPSILONT);
    EXPECT_NEAR(7.7, doubleTestArray[7], EPSILONT);
    EXPECT_NEAR(8.8, doubleTestArray[8], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[9], EPSILONT);
    cropper.apply(doubleTestArray, size, 2.1, 7.8);
    EXPECT_NEAR(2.1, doubleTestArray[0], EPSILONT);
    EXPECT_NEAR(2.1, doubleTestArray[1], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[2], EPSILONT);
    EXPECT_NEAR(3.3, doubleTestArray[3], EPSILONT);
    EXPECT_NEAR(4.4, doubleTestArray[4], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[5], EPSILONT);
    EXPECT_NEAR(6.6, doubleTestArray[6], EPSILONT);
    EXPECT_NEAR(7.7, doubleTestArray[7], EPSILONT);
    EXPECT_NEAR(7.8, doubleTestArray[8], EPSILONT);
    EXPECT_NEAR(7.8, doubleTestArray[9], EPSILONT);
    cropper.apply(doubleTestArray, size, 5.5, 5.5 + 0.5*EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[0], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[1], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[2], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[3], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[4], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[5], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[6], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[7], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[8], EPSILONT);
    EXPECT_NEAR(5.5, doubleTestArray[9], EPSILONT);
    cropper.apply(doubleTestArray, size, 9.9, 10.1);
    EXPECT_NEAR(9.9, doubleTestArray[0], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[1], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[2], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[3], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[4], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[5], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[6], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[7], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[8], EPSILONT);
    EXPECT_NEAR(9.9, doubleTestArray[9], EPSILONT);
    cropper.apply(doubleTestArray, size, 1.1, 2.2);
    EXPECT_NEAR(2.2, doubleTestArray[0], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[1], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[2], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[3], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[4], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[5], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[6], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[7], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[8], EPSILONT);
    EXPECT_NEAR(2.2, doubleTestArray[9], EPSILONT);
}
