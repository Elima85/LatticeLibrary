#include "gtest/gtest.h"
#include "defs.h"
#include "image.h"
#include "cclattice.h"
#include "imagearithmetic.h"
#include <cmath>

using namespace LatticeLib;

TEST(ImageArithmetic, addition) {

    int nRows = 2, nColumns = 2, nLayers = 1, nBands = 4, nTotal = 16;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    double doubleUnitData[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    double doubleIncreasingData[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
    double doubleResultData[16];
    int intUnitData[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int intIncreasingData[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int intResultData[16];
    Image<double> doubleUnitImage(doubleUnitData, lattice, nBands);
    Image<double> doubleIncreasingImage(doubleIncreasingData, lattice, nBands);
    Image<double> doubleResultImage(doubleResultData, lattice, nBands);
    Image<int> intUnitImage(intUnitData, lattice, nBands);
    Image<int> intIncreasingImage(intIncreasingData, lattice, nBands);
    Image<int> intResultImage(intResultData, lattice, nBands);

    ImageArithmetic imageArithmetic;

    imageArithmetic.add(doubleUnitImage, doubleIncreasingImage, doubleResultImage);
    imageArithmetic.add(intUnitImage, intIncreasingImage, intResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "T T addition, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_NEAR(doubleResultData[dataIndex], doubleUnitData[dataIndex] + doubleIncreasingData[dataIndex], EPSILONT);
        EXPECT_EQ(intResultData[dataIndex], intUnitData[dataIndex] + intIncreasingData[dataIndex]);
    }

    imageArithmetic.add(doubleIncreasingImage, intUnitImage, doubleResultImage);
    imageArithmetic.add(intUnitImage, doubleIncreasingImage, intResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "T S addition, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_NEAR(doubleResultData[dataIndex], doubleUnitData[dataIndex] + doubleIncreasingData[dataIndex], EPSILONT);
    }
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "T S addition, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        if ((dataIndex == 0) || (dataIndex == 10)) {
            EXPECT_NEAR(doubleResultData[dataIndex], intResultData[dataIndex], EPSILONT);
        }
        else {
            EXPECT_GT(fabs(doubleResultData[dataIndex] - intResultData[dataIndex]), EPSILONT);
        }
    }
    for (int dataIndex = 0; dataIndex < 10; dataIndex++) {
        string message = "T S addition, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(intResultData[dataIndex], 1);
    }
    for (int dataIndex = 10; dataIndex < nTotal; dataIndex++) {
        string message = "T S addition, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(intResultData[dataIndex], 2);
    }
}

TEST(ImageArithmetic, subtraction) {

    int nRows = 2, nColumns = 2, nLayers = 1, nBands = 4, nTotal = 16;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    double doubleUnitData[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    double doubleIncreasingData[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
    double doubleResultData[16];
    int intUnitData[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int intIncreasingData[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int intResultData[16];
    Image<double> doubleUnitImage(doubleUnitData, lattice, nBands);
    Image<double> doubleIncreasingImage(doubleIncreasingData, lattice, nBands);
    Image<double> doubleResultImage(doubleResultData, lattice, nBands);
    Image<int> intUnitImage(intUnitData, lattice, nBands);
    Image<int> intIncreasingImage(intIncreasingData, lattice, nBands);
    Image<int> intResultImage(intResultData, lattice, nBands);

    ImageArithmetic imageArithmetic;

    imageArithmetic.subtract(doubleUnitImage, doubleIncreasingImage, doubleResultImage);
    imageArithmetic.subtract(intUnitImage, intIncreasingImage, intResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "T T subtraction, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_NEAR(doubleResultData[dataIndex], doubleUnitData[dataIndex] - doubleIncreasingData[dataIndex], EPSILONT);
        EXPECT_EQ(intResultData[dataIndex], intUnitData[dataIndex] - intIncreasingData[dataIndex]);
    }

    imageArithmetic.subtract(doubleIncreasingImage, intUnitImage, doubleResultImage);
    imageArithmetic.subtract(intUnitImage, doubleIncreasingImage, intResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "T S subtraction, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_NEAR(doubleResultData[dataIndex], doubleIncreasingData[dataIndex] - doubleUnitData[dataIndex], EPSILONT);
    }
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "T S subtraction, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        if (dataIndex == 10) {
            EXPECT_NEAR(doubleResultData[dataIndex], intResultData[dataIndex], EPSILONT);
        }
        else {
            EXPECT_GT(fabs(doubleResultData[dataIndex] - intResultData[dataIndex]), EPSILONT);
        }
    }
    for (int dataIndex = 0; dataIndex < 10; dataIndex++) {
        string message = "T S subtraction, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(intResultData[dataIndex], 1);
    }
    for (int dataIndex = 10; dataIndex < nTotal; dataIndex++) {
        string message = "T S subtraction, index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(intResultData[dataIndex], 0);
    }
}

TEST(ImageArithmetic, scaling) {

    int nRows = 2, nColumns = 2, nLayers = 1, nBands = 4, nTotal = 16;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    double doubleData[] = {0, 0, 0, 0, 0.1, 0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.3};
    int intData[] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
    double doubleResultData[16];
    int intResultData[16];
    Image<double> doubleImage(doubleData, lattice, nBands);
    Image<double> doubleResultImage(doubleResultData, lattice, nBands);
    Image<int> intImage(intData, lattice, nBands);
    Image<int> intResultImage(intResultData, lattice, nBands);

    ImageArithmetic imageArithmetic;

    imageArithmetic.scale(doubleImage, 1, doubleResultImage);
    imageArithmetic.scale(intImage, 1.0, intResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_NEAR(doubleResultData[dataIndex], doubleData[dataIndex], EPSILONT);
        EXPECT_EQ(intResultData[dataIndex], intData[dataIndex]);
    }

    imageArithmetic.scale(doubleImage, 10, doubleResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_NEAR(doubleResultData[dataIndex], intData[dataIndex], EPSILONT);
    }
    imageArithmetic.scale(doubleImage, 0, doubleResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_NEAR(doubleResultData[dataIndex], 0.0, EPSILONT);
    }
    imageArithmetic.scale(doubleImage, 2.5, doubleResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_NEAR(doubleResultData[dataIndex], 2.5 * doubleData[dataIndex], EPSILONT);
    }

    imageArithmetic.scale(intImage, 1.3, intResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(intData[dataIndex], intResultData[dataIndex]);
    }
    imageArithmetic.scale(intImage, 0.3, intResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(0, intResultData[dataIndex]);
    }
    imageArithmetic.scale(intImage, 3, intResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(3 * intData[dataIndex], intResultData[dataIndex]);
    }
    imageArithmetic.scale(intImage, 0, intResultImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(0, intResultData[dataIndex]);
    }

}
