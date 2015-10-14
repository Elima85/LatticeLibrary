#include "gtest/gtest.h"
#include "../src/defs.h"
#include "../src/cropintensityrange.h"
#include "../src/renormalizeintensityrange.h"
#include "../src/exception.h"
#include <cmath>

using namespace LatticeLib;

TEST(DataRedistribution, cropintensitytest) {

    int size = 10;
    int intTestArray[10] = {0,1,2,3,4,5,6,7,8,9};
    double doubleTestArray[10] = {0.0,1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9};

    CropIntensityRange<int> intCropIntensities;
    CropIntensityRange<double> doubleCropIntensities;

    // T = int
    EXPECT_THROW(intCropIntensities.apply(intTestArray, size, 0, 9, 5, 4), incompatibleParametersException);
    for (int index = 0; index < size; index ++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(index, intTestArray[index]);
    }
    intCropIntensities.apply(intTestArray, size, 0, 9, -1, 10);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(index, intTestArray[index]);
    }
    intCropIntensities.apply(intTestArray, size, 0, 9, 0, 9);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(index, intTestArray[index]);
    }
    intCropIntensities.apply(intTestArray, size, 0, 9, 2, 7);
    for (int index = 0; index < 2; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(2, intTestArray[index]);
    }
    for (int index = 2; index < 7; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(index, intTestArray[index]);
    }
    for (int index = 7; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(7, intTestArray[index]);
    }
    intCropIntensities.apply(intTestArray, size, 2, 7, 5, 5);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(5, intTestArray[index]);
    }
    intCropIntensities.apply(intTestArray, size, 2, 7, 9, 10);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(9, intTestArray[index]);
    }
    intCropIntensities.apply(intTestArray, size, 9, 10, 1, 2);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(2, intTestArray[index]);
    }

    // T = double
    EXPECT_THROW(doubleCropIntensities.apply(doubleTestArray, size, 0.0, 9.9, 5.0, 4.0), incompatibleParametersException);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(1.1 * double(index), doubleTestArray[index], EPSILONT);
    }
    doubleCropIntensities.apply(doubleTestArray, size, 0.0, 9.9, -1.1, 10.1);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(1.1 * double(index), doubleTestArray[index], EPSILONT);
    }
    doubleCropIntensities.apply(doubleTestArray, size, 0.0, 9.9, 0.0 - 0.5 * EPSILONT, 9.9 + 0.5 * EPSILONT);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(1.1 * double(index), doubleTestArray[index], EPSILONT);
    }
    doubleCropIntensities.apply(doubleTestArray, size, 0.0, 9.9, 2.1, 7.8);
    for (int index = 0; index < 2; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(2.1, doubleTestArray[index], EPSILONT);
    }
    for (int index = 2; index < 8; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(1.1 * double(index), doubleTestArray[index], EPSILONT);
    }
    for (int index = 8; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(7.8, doubleTestArray[index], EPSILONT);
    }
    doubleCropIntensities.apply(doubleTestArray, size, 2.1, 7.8, 5.5, 5.5 + 0.5 * EPSILONT);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(5.5, doubleTestArray[index], EPSILONT);
    }
    doubleCropIntensities.apply(doubleTestArray, size, 5.5, 5.5 + 0.5 * EPSILONT, 9.9, 10.1);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(9.9, doubleTestArray[index], EPSILONT);
    }
    doubleCropIntensities.apply(doubleTestArray, size, 9.9, 10.1, 1.1, 2.2);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(2.2, doubleTestArray[index], EPSILONT);
    }
}

TEST(DataRedistribution, normalizationtest) {

    int size = 10;
    int intTestArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double doubleTestArray1[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    double doubleTestArray2[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    double doubleTestArray3[10] = {-10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0};
    double doubleTestArray4[10] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5};
    float floatTestArray1[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    float floatTestArray2[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    float floatTestArray3[10] = {-10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0};
    float floatTestArray4[10] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5};

    RenormalizeIntensityRange<double> doubleRenormalizeIntensity;
    RenormalizeIntensityRange<float> floatRenormalizeIntensity;
    RenormalizeIntensityRange<int> intRenormalizeIntensity;

    // T = int
    EXPECT_THROW(intRenormalizeIntensity.apply(intTestArray, size, 1, 10, 10, 1), incompatibleParametersException);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(index + 1, intTestArray[index]);
    }
    intRenormalizeIntensity.apply(intTestArray, size, 1, 10, 0, 10);
    EXPECT_EQ(0, intTestArray[0]);
    for (int index = 1; index < size - 1; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_EQ(index, intTestArray[index]);
    }
    EXPECT_EQ(10, intTestArray[9]);

    // T = double
    EXPECT_THROW(doubleRenormalizeIntensity.apply(doubleTestArray1, size, 1, 10, 10.0, 1.0), incompatibleParametersException);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(index + 1, doubleTestArray1[index], EPSILONT);
    }
    doubleRenormalizeIntensity.apply(doubleTestArray1, size, 0, 10, 0, 1.0);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(0.1 * double(index + 1), doubleTestArray1[index], EPSILONT);
    }
    doubleRenormalizeIntensity.apply(doubleTestArray2, size, 1, 15, 0, 1.0);
    EXPECT_NEAR(0.0, doubleTestArray2[0], EPSILONT);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GT(doubleTestArray2[index], doubleTestArray2[index - 1]);
    }
    EXPECT_GT(1, doubleTestArray2[9]);
    doubleRenormalizeIntensity.apply(doubleTestArray3, size, -10.0, 0.0, 0, 1.0);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(0.1 * double(index + 1), doubleTestArray1[index], EPSILONT);
    }
    doubleRenormalizeIntensity.apply(doubleTestArray4, size, 0.0, 10.0, 0, 1.0);
    EXPECT_GT(doubleTestArray4[0], 0.0);
    for (int index = 1; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GT(doubleTestArray4[index], doubleTestArray4[index - 1]);
    }
    EXPECT_GT(1, doubleTestArray4[9]);
    for (int index = 1; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GT(doubleTestArray4[index], doubleTestArray4[index - 1]);
        EXPECT_NEAR(doubleTestArray4[index] / doubleTestArray4[index - 1], double(1 + 0.5 * index) / double(0.5 + 0.5 * index), EPSILONT);
    }

    // T = float (10 * EPSILONT, because of lower precision)
    EXPECT_THROW(floatRenormalizeIntensity.apply(floatTestArray1, size, float(1), float(10), float(10.0), float(1.0)), incompatibleParametersException);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(index + 1, floatTestArray1[index], 10 * EPSILONT);
    }
    floatRenormalizeIntensity.apply(floatTestArray1, size, float(0), float(10), float(0), float(1.0));
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(0.1 * double(index + 1), floatTestArray1[index], 10 * EPSILONT);
    }
    floatRenormalizeIntensity.apply(floatTestArray2, size, float(1), float(15), float(0), float(1.0));
    EXPECT_NEAR(0.0, floatTestArray2[0], 10 * EPSILONT);
    for (int index = 1; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GT(floatTestArray2[index], floatTestArray2[index - 1]);
    }
    EXPECT_GT(1, floatTestArray2[9]);
    floatRenormalizeIntensity.apply(floatTestArray3, size, float(-10.0), float(0.0), float(0), float(1.0));
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(0.1 * double(index + 1), floatTestArray1[index], 10 * EPSILONT);
    }
    floatRenormalizeIntensity.apply(floatTestArray4, size, float(0.0), float(10.0), float(0), float(1.0));
    EXPECT_GT(floatTestArray4[0], 0.0);
    for (int index = 1; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GT(floatTestArray4[index], floatTestArray4[index - 1]);
    }
    EXPECT_GT(1, floatTestArray4[9]);
    for (int index = 1; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GT(floatTestArray4[index], floatTestArray4[index - 1]);
        EXPECT_NEAR(floatTestArray4[index] / floatTestArray4[index - 1], double(1 + 0.5 * index) / double(0.5 + 0.5 * index), 10 * EPSILONT);
    }

}

TEST(DataRedistribution, denormalizationtest) {

    int size = 10;
    double doubleTestArray1[10] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    double doubleTestArray2[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    double doubleTestArray3[10] = {-10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0};
    float floatTestArray1[10] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    float floatTestArray2[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    float floatTestArray3[10] = {-10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0};

    RenormalizeIntensityRange<double> doubleRenormalizeIntensity;
    RenormalizeIntensityRange<float> floatRenormalizeIntensity;

    // T = double
    EXPECT_THROW(doubleRenormalizeIntensity.apply(doubleTestArray1, size, 0, 1, 10.0, 1.0), incompatibleParametersException);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(0.1 * double(index), doubleTestArray1[index], EPSILONT);
    }
    doubleRenormalizeIntensity.apply(doubleTestArray2, size, -3, 14, 0, 1);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GE(fabs(doubleTestArray2[index] - (index + 1)), EPSILONT);
    }
    doubleRenormalizeIntensity.apply(doubleTestArray2, size, 0, 1, -3, 14);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(doubleTestArray2[index], index + 1, EPSILONT);
    }
    doubleRenormalizeIntensity.apply(doubleTestArray3, size, -3, 14, 0, 1);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GE(fabs(doubleTestArray3[index] + (10.0 - index)), EPSILONT);
    }
    doubleRenormalizeIntensity.apply(doubleTestArray3, size, 0, 1, -3, 14);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(doubleTestArray3[index], (-10.0 + index), EPSILONT);
    }

    // T = float (10 * EPSILONT, because of lower precision)
    EXPECT_THROW(floatRenormalizeIntensity.apply(floatTestArray1, size, float(0), float(1), float(10.0), float(1.0)),
                 incompatibleParametersException);
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(0.1 * float(index), floatTestArray1[index], 10 * EPSILONT);
    }
    floatRenormalizeIntensity.apply(floatTestArray2, size, float(-3), float(14), float(0), float(1));
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GE(fabs(floatTestArray2[index] - (index + 1)), 10 * EPSILONT);
    }
    floatRenormalizeIntensity.apply(floatTestArray2, size, float(0), float(1), float(-3), float(14));
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(floatTestArray2[index], index + 1, 10 * EPSILONT);
    }
    floatRenormalizeIntensity.apply(floatTestArray3, size, float(-3), float(14), float(0), float(1));
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_GE(fabs(floatTestArray3[index] + (10.0 - index)), 10 * EPSILONT);
    }
    floatRenormalizeIntensity.apply(floatTestArray3, size, float(0), float(1), float(-3), float(14));
    for (int index = 0; index < size; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        EXPECT_NEAR(floatTestArray3[index], (-10.0 + index), 10 * EPSILONT);
    }

}