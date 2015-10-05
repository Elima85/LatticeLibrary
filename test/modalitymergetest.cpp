#include "gtest/gtest.h"
#include "../defs.h"
#include "../image.h"
#include "../cclattice.h"
#include "../modalitymerge.h"

using namespace LatticeLib;

TEST(ModalityMerge, totalmerge) {

    int nRows = 2, nColumns = 2, nLayers = 1, nBands = 4, nElements = 4;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    double doubleData[] = {0.1, 0.2, 0.3, 0.4, 0.2, 0.3, 0.4, 0.1, 0.3, 0.4, 0.1, 0.2, 0.4, 0.1, 0.2, 0.3};
    int intData[] = {1, 2, 3, 4, 2, 3, 4, 1, 3, 4, 1, 2, 4, 1, 2, 3};
    double doubleResultData[4];
    int intResultData[4];
    Image<double> doubleImage(doubleData, lattice, nBands);
    Image<int> intImage(intData, lattice, nBands);

    ModalityMerge modalityMerge;

    modalityMerge.mergeAllBands(doubleImage, blendOption::min, doubleResultData);
    modalityMerge.mergeAllBands(intImage, blendOption::min, intResultData);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        EXPECT_NEAR(0.1, doubleResultData[elementIndex], EPSILONT);
        EXPECT_EQ(1, intResultData[elementIndex]);
    }

    modalityMerge.mergeAllBands(doubleImage, blendOption::max, doubleResultData);
    modalityMerge.mergeAllBands(intImage, blendOption::max, intResultData);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        EXPECT_NEAR(0.4, doubleResultData[elementIndex], EPSILONT);
        EXPECT_EQ(4, intResultData[elementIndex]);
    }

    modalityMerge.mergeAllBands(doubleImage, blendOption::mean, doubleResultData);
    modalityMerge.mergeAllBands(intImage, blendOption::mean, intResultData);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        EXPECT_NEAR(0.25, doubleResultData[elementIndex], EPSILONT);
        EXPECT_EQ(2, intResultData[elementIndex]);
    }

    modalityMerge.mergeAllBands(doubleImage, blendOption::sum, doubleResultData);
    modalityMerge.mergeAllBands(intImage, blendOption::sum, intResultData);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        EXPECT_NEAR(1, doubleResultData[elementIndex], EPSILONT);
        EXPECT_EQ(10, intResultData[elementIndex]);
    }
}

TEST(ModalityMerge, partialmerge) {

    int nRows = 2, nColumns = 2, nLayers = 1, nBands = 4, nElements = 4;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    double doubleData[] = {0, 0, 0, 0, 0.1, 0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.3};
    int intData[] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
    double doubleResultData[4];
    int intResultData[4];
    Image<double> doubleImage(doubleData, lattice, nBands);
    Image<int> intImage(intData, lattice, nBands);
    vector<int> bandIndices;
    bandIndices.push_back(1);
    bandIndices.push_back(3);

    ModalityMerge modalityMerge;

    modalityMerge.mergeBands(doubleImage, bandIndices, blendOption::min, doubleResultData);
    modalityMerge.mergeBands(intImage, bandIndices, blendOption::min, intResultData);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        EXPECT_NEAR(0.1, doubleResultData[elementIndex], EPSILONT);
        EXPECT_EQ(1, intResultData[elementIndex]);
    }

    modalityMerge.mergeBands(doubleImage, bandIndices, blendOption::max, doubleResultData);
    modalityMerge.mergeBands(intImage, bandIndices, blendOption::max, intResultData);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        EXPECT_NEAR(0.3, doubleResultData[elementIndex], EPSILONT);
        EXPECT_EQ(3, intResultData[elementIndex]);
    }

    modalityMerge.mergeBands(doubleImage, bandIndices, blendOption::mean, doubleResultData);
    modalityMerge.mergeBands(intImage, bandIndices, blendOption::mean, intResultData);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        EXPECT_NEAR(0.2, doubleResultData[elementIndex], EPSILONT);
        EXPECT_EQ(2, intResultData[elementIndex]);
    }

    modalityMerge.mergeBands(doubleImage, bandIndices, blendOption::sum, doubleResultData);
    modalityMerge.mergeBands(intImage, bandIndices, blendOption::sum, intResultData);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        EXPECT_NEAR(0.4, doubleResultData[elementIndex], EPSILONT);
        EXPECT_EQ(4, intResultData[elementIndex]);
    }

}