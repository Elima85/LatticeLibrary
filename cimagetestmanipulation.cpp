#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cclattice.h"

using namespace CImage;

TEST(CImage, manipulation) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice latticeCC(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    uint8 data[nElements * nBands];
    for (int i = 0; i < nBands * nElements; i++) {
        data[i] = 0;
    }
    CImage<uint8> *imageCC = new CImage<uint8>(data, latticeCC, nBands);

    uint8 newValues[] = {11, 22, 33};
    vector<uint8> newIntensityValues(newValues, newValues + 3);

    int elementIndex = 42;
    vector<uint8> currentIntensityValues = (*imageCC)[elementIndex];
    EXPECT_EQ(currentIntensityValues[0], 0);
    EXPECT_EQ(currentIntensityValues[1], 0);
    EXPECT_EQ(currentIntensityValues[2], 0);
    imageCC->setElement(elementIndex, newIntensityValues);
    currentIntensityValues = (*imageCC)[elementIndex];
    EXPECT_EQ(currentIntensityValues[0], newIntensityValues[0]);
    EXPECT_EQ(currentIntensityValues[1], newIntensityValues[1]);
    EXPECT_EQ(currentIntensityValues[2], newIntensityValues[2]);

    elementIndex = 43;
    currentIntensityValues = (*imageCC)[elementIndex];
    EXPECT_EQ(currentIntensityValues[0], 0);
    EXPECT_EQ(currentIntensityValues[1], 0);
    EXPECT_EQ(currentIntensityValues[2], 0);
    imageCC->setElement(imageCC->indexToR(elementIndex), imageCC->indexToC(elementIndex), imageCC->indexToL(elementIndex), newIntensityValues);
    currentIntensityValues = (*imageCC)[elementIndex];
    EXPECT_EQ(currentIntensityValues[0], newIntensityValues[0]);
    EXPECT_EQ(currentIntensityValues[1], newIntensityValues[1]);
    EXPECT_EQ(currentIntensityValues[2], newIntensityValues[2]);

    elementIndex = 44;
    currentIntensityValues = (*imageCC)[elementIndex];
    EXPECT_EQ(currentIntensityValues[0], 0);
    EXPECT_EQ(currentIntensityValues[1], 0);
    EXPECT_EQ(currentIntensityValues[2], 0);
    imageCC->setElement(elementIndex, 0, newIntensityValues[0]);
    imageCC->setElement(elementIndex, 1, newIntensityValues[1]);
    imageCC->setElement(elementIndex, 2, newIntensityValues[2]);
    currentIntensityValues = (*imageCC)[elementIndex];
    EXPECT_EQ(currentIntensityValues[0], newIntensityValues[0]);
    EXPECT_EQ(currentIntensityValues[1], newIntensityValues[1]);
    EXPECT_EQ(currentIntensityValues[2], newIntensityValues[2]);

    elementIndex = 45;
    currentIntensityValues = (*imageCC)[elementIndex];
    EXPECT_EQ(currentIntensityValues[0], 0);
    EXPECT_EQ(currentIntensityValues[1], 0);
    EXPECT_EQ(currentIntensityValues[2], 0);
    imageCC->setElement(imageCC->indexToR(elementIndex), imageCC->indexToC(elementIndex), imageCC->indexToL(elementIndex), 0, newIntensityValues[0]);
    imageCC->setElement(imageCC->indexToR(elementIndex), imageCC->indexToC(elementIndex), imageCC->indexToL(elementIndex), 1, newIntensityValues[1]);
    imageCC->setElement(imageCC->indexToR(elementIndex), imageCC->indexToC(elementIndex), imageCC->indexToL(elementIndex), 2, newIntensityValues[2]);
    currentIntensityValues = (*imageCC)[elementIndex];
    EXPECT_EQ(currentIntensityValues[0], newIntensityValues[0]);
    EXPECT_EQ(currentIntensityValues[1], newIntensityValues[1]);
    EXPECT_EQ(currentIntensityValues[2], newIntensityValues[2]);

    delete imageCC;
}