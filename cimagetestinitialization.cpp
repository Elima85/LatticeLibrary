#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cclattice.h"
#include "bcclattice.h"
#include "fcclattice.h"

using namespace CImage;

TEST(CImage,initialization) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice *latticeCC = new CCLattice(nRows,nColumns,nLayers, scaleFactor);
    BCCLattice *latticeBCC = new BCCLattice(nRows, nColumns, nLayers, scaleFactor);
    FCCLattice *latticeFCC = new FCCLattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    uint8 data[nElements * nBands];
    for (int i = 0; i < nBands * nElements; i++) {
        data[i] = i;
    }

    CImage<uint8> *imageCC = new CImage<uint8>(data, *latticeCC, nBands);
    CImage<uint8> *imageBCC = new CImage<uint8>(data, *latticeBCC, nBands);
    CImage<uint8> *imageFCC = new CImage<uint8>(data, *latticeFCC, nBands);

    // image parameters
    EXPECT_TRUE(imageCC);
    EXPECT_EQ(latticeCC->getNRows(), imageCC->getNRows());
    EXPECT_EQ(latticeCC->getNColumns(), imageCC->getNColumns());
    EXPECT_EQ(latticeCC->getNLayers(), imageCC->getNLayers());
    EXPECT_EQ(latticeCC->getNElements(), imageCC->getNElements());
    EXPECT_EQ(latticeCC->getScaleFactor(), imageCC->getScaleFactor());
    EXPECT_EQ(nBands, imageCC->getNBands());
    EXPECT_EQ(long(data), long(imageCC->getData()));
    EXPECT_NE(latticeCC->getNRows(), imageCC->getNRows() + 1);
    EXPECT_NE(latticeCC->getNColumns(), imageCC->getNColumns() + 1);
    EXPECT_NE(latticeCC->getNLayers(), imageCC->getNLayers() + 1);
    EXPECT_NE(latticeCC->getNElements(), imageCC->getNElements() + 1);
    EXPECT_NE(0.0, imageCC->getScaleFactor());
    EXPECT_NE(nBands, imageCC->getNBands() + 1);
    EXPECT_NE(0, long(imageCC->getData()));

    EXPECT_TRUE(imageBCC);
    EXPECT_EQ(latticeBCC->getNRows(), imageBCC->getNRows());
    EXPECT_EQ(latticeBCC->getNColumns(), imageBCC->getNColumns());
    EXPECT_EQ(latticeBCC->getNLayers(), imageBCC->getNLayers());
    EXPECT_EQ(latticeBCC->getNElements(), imageBCC->getNElements());
    EXPECT_EQ(latticeBCC->getScaleFactor(), imageBCC->getScaleFactor());
    EXPECT_EQ(nBands, imageBCC->getNBands());
    EXPECT_EQ(long(data), long(imageBCC->getData()));
    EXPECT_NE(latticeBCC->getNRows(), imageBCC->getNRows() + 1);
    EXPECT_NE(latticeBCC->getNColumns(), imageBCC->getNColumns() + 1);
    EXPECT_NE(latticeBCC->getNLayers(), imageBCC->getNLayers() + 1);
    EXPECT_NE(latticeBCC->getNElements(), imageBCC->getNElements() + 1);
    EXPECT_NE(0.0, imageBCC->getScaleFactor());
    EXPECT_NE(nBands, imageBCC->getNBands() + 1);
    EXPECT_NE(0, long(imageBCC->getData()));

    EXPECT_TRUE(imageFCC);
    EXPECT_EQ(latticeFCC->getNRows(), imageFCC->getNRows());
    EXPECT_EQ(latticeFCC->getNColumns(), imageFCC->getNColumns());
    EXPECT_EQ(latticeFCC->getNLayers(), imageFCC->getNLayers());
    EXPECT_EQ(latticeFCC->getNElements(), imageFCC->getNElements());
    EXPECT_EQ(latticeFCC->getScaleFactor(), imageFCC->getScaleFactor());
    EXPECT_EQ(nBands, imageFCC->getNBands());
    EXPECT_EQ(long(data), long(imageFCC->getData()));
    EXPECT_NE(latticeFCC->getNRows(), imageFCC->getNRows() + 1);
    EXPECT_NE(latticeFCC->getNColumns(), imageFCC->getNColumns() + 1);
    EXPECT_NE(latticeFCC->getNLayers(), imageFCC->getNLayers() + 1);
    EXPECT_NE(latticeFCC->getNElements(), imageFCC->getNElements() + 1);
    EXPECT_NE(0.0, imageFCC->getScaleFactor());
    EXPECT_NE(nBands, imageFCC->getNBands() + 1);
    EXPECT_NE(0, long(imageFCC->getData()));
    
    // index conversion
    EXPECT_EQ(latticeCC->rclToIndex(0, 0, 0), imageCC->rclToIndex(0, 0, 0));
    EXPECT_EQ(latticeCC->rclToIndex(1, 2, 3), imageCC->rclToIndex(1, 2, 3));
    EXPECT_EQ(latticeCC->rclToIndex(nRows - 1, nColumns - 1, nLayers - 1), imageCC->rclToIndex(nRows - 1, nColumns - 1, nLayers - 1));
    EXPECT_EQ(latticeCC->indexToR(0), latticeCC->indexToR(0));
    EXPECT_EQ(latticeCC->indexToC(0), latticeCC->indexToC(0));
    EXPECT_EQ(latticeCC->indexToL(0), latticeCC->indexToL(0));
    EXPECT_EQ(latticeCC->indexToR(98), latticeCC->indexToR(98));
    EXPECT_EQ(latticeCC->indexToC(98), latticeCC->indexToC(98));
    EXPECT_EQ(latticeCC->indexToL(98), latticeCC->indexToL(98));
    EXPECT_EQ(latticeCC->indexToR(nElements - 1), latticeCC->indexToR(nElements - 1));
    EXPECT_EQ(latticeCC->indexToC(nElements - 1), latticeCC->indexToC(nElements - 1));
    EXPECT_EQ(latticeCC->indexToL(nElements - 1), latticeCC->indexToL(nElements - 1));

    EXPECT_EQ(latticeBCC->rclToIndex(0, 0, 0), imageBCC->rclToIndex(0, 0, 0));
    EXPECT_EQ(latticeBCC->rclToIndex(1, 2, 3), imageBCC->rclToIndex(1, 2, 3));
    EXPECT_EQ(latticeBCC->rclToIndex(nRows - 1, nColumns - 1, nLayers - 1), imageBCC->rclToIndex(nRows - 1, nColumns - 1, nLayers - 1));
    EXPECT_EQ(latticeBCC->indexToR(0), latticeBCC->indexToR(0));
    EXPECT_EQ(latticeBCC->indexToC(0), latticeBCC->indexToC(0));
    EXPECT_EQ(latticeBCC->indexToL(0), latticeBCC->indexToL(0));
    EXPECT_EQ(latticeBCC->indexToR(98), latticeBCC->indexToR(98));
    EXPECT_EQ(latticeBCC->indexToC(98), latticeBCC->indexToC(98));
    EXPECT_EQ(latticeBCC->indexToL(98), latticeBCC->indexToL(98));
    EXPECT_EQ(latticeBCC->indexToR(nElements - 1), latticeBCC->indexToR(nElements - 1));
    EXPECT_EQ(latticeBCC->indexToC(nElements - 1), latticeBCC->indexToC(nElements - 1));
    EXPECT_EQ(latticeBCC->indexToL(nElements - 1), latticeBCC->indexToL(nElements - 1));

    EXPECT_EQ(latticeFCC->rclToIndex(0, 0, 0), imageFCC->rclToIndex(0, 0, 0));
    EXPECT_EQ(latticeFCC->rclToIndex(1, 2, 3), imageFCC->rclToIndex(1, 2, 3));
    EXPECT_EQ(latticeFCC->rclToIndex(nRows - 1, nColumns - 1, nLayers - 1), imageFCC->rclToIndex(nRows - 1, nColumns - 1, nLayers - 1));
    EXPECT_EQ(latticeFCC->indexToR(0), latticeFCC->indexToR(0));
    EXPECT_EQ(latticeFCC->indexToC(0), latticeFCC->indexToC(0));
    EXPECT_EQ(latticeFCC->indexToL(0), latticeFCC->indexToL(0));
    EXPECT_EQ(latticeFCC->indexToR(98), latticeFCC->indexToR(98));
    EXPECT_EQ(latticeFCC->indexToC(98), latticeFCC->indexToC(98));
    EXPECT_EQ(latticeFCC->indexToL(98), latticeFCC->indexToL(98));
    EXPECT_EQ(latticeFCC->indexToR(nElements - 1), latticeFCC->indexToR(nElements - 1));
    EXPECT_EQ(latticeFCC->indexToC(nElements - 1), latticeFCC->indexToC(nElements - 1));
    EXPECT_EQ(latticeFCC->indexToL(nElements - 1), latticeFCC->indexToL(nElements - 1));

    // validity of elements
    EXPECT_FALSE(imageCC->isValid(-1));
    EXPECT_TRUE(imageCC->isValid(0));
    EXPECT_TRUE(imageCC->isValid(nElements - 1));
    EXPECT_FALSE(imageCC->isValid(nElements));
    EXPECT_FALSE(imageCC->isValid(0, -1));
    EXPECT_FALSE(imageCC->isValid(nElements - 1, -1));
    EXPECT_FALSE(imageCC->isValid(-1, 0));
    EXPECT_TRUE(imageCC->isValid(0, 0));
    EXPECT_TRUE(imageCC->isValid(nElements - 1, 0));
    EXPECT_FALSE(imageCC->isValid(nElements, 0));
    EXPECT_TRUE(imageCC->isValid(0, nBands - 1));
    EXPECT_TRUE(imageCC->isValid(nElements - 1, nBands - 1));
    EXPECT_FALSE(imageCC->isValid(0, nBands));
    EXPECT_FALSE(imageCC->isValid(nElements - 1, nBands));
    EXPECT_FALSE(imageCC->isValid(-1, 0, 0));
    EXPECT_FALSE(imageCC->isValid(0, -1, 0));
    EXPECT_FALSE(imageCC->isValid(0, 0, -1));
    EXPECT_TRUE(imageCC->isValid(0, 0, 0));
    EXPECT_TRUE(imageCC->isValid(nRows - 1, 0, 0));
    EXPECT_TRUE(imageCC->isValid(0, nColumns - 1, 0));
    EXPECT_TRUE(imageCC->isValid(0, 0, nLayers - 1));
    EXPECT_FALSE(imageCC->isValid(nRows, 0, 0));
    EXPECT_FALSE(imageCC->isValid(0, nColumns, 0));
    EXPECT_FALSE(imageCC->isValid(0, 0, nLayers));
    EXPECT_FALSE(imageCC->isValid(0, 0, 0, -1));
    EXPECT_FALSE(imageCC->isValid(nRows - 1, 0, 0, -1));
    EXPECT_FALSE(imageCC->isValid(0, nColumns - 1, 0, -1));
    EXPECT_FALSE(imageCC->isValid(0, 0, nLayers - 1, -1));
    EXPECT_FALSE(imageCC->isValid(0, 0, 0, nBands));
    EXPECT_FALSE(imageCC->isValid(nRows - 1, 0, 0, nBands));
    EXPECT_FALSE(imageCC->isValid(0, nColumns - 1, 0, nBands));
    EXPECT_FALSE(imageCC->isValid(0, 0, nLayers - 1, nBands));
    EXPECT_TRUE(imageCC->isValid(0, 0, 0, nBands - 1));
    EXPECT_TRUE(imageCC->isValid(nRows - 1, 0, 0, nBands - 1));
    EXPECT_TRUE(imageCC->isValid(0, nColumns - 1, 0, nBands - 1));
    EXPECT_TRUE(imageCC->isValid(0, 0, nLayers - 1, nBands - 1));

    EXPECT_FALSE(imageBCC->isValid(-1));
    EXPECT_TRUE(imageBCC->isValid(0));
    EXPECT_TRUE(imageBCC->isValid(nElements - 1));
    EXPECT_FALSE(imageBCC->isValid(nElements));
    EXPECT_FALSE(imageBCC->isValid(0, -1));
    EXPECT_FALSE(imageBCC->isValid(nElements - 1, -1));
    EXPECT_FALSE(imageBCC->isValid(-1, 0));
    EXPECT_TRUE(imageBCC->isValid(0, 0));
    EXPECT_TRUE(imageBCC->isValid(nElements - 1, 0));
    EXPECT_FALSE(imageBCC->isValid(nElements, 0));
    EXPECT_TRUE(imageBCC->isValid(0, nBands - 1));
    EXPECT_TRUE(imageBCC->isValid(nElements - 1, nBands - 1));
    EXPECT_FALSE(imageBCC->isValid(0, nBands));
    EXPECT_FALSE(imageBCC->isValid(nElements - 1, nBands));
    EXPECT_FALSE(imageBCC->isValid(-1, 0, 0));
    EXPECT_FALSE(imageBCC->isValid(0, -1, 0));
    EXPECT_FALSE(imageBCC->isValid(0, 0, -1));
    EXPECT_TRUE(imageBCC->isValid(0, 0, 0));
    EXPECT_TRUE(imageBCC->isValid(nRows - 1, 0, 0));
    EXPECT_TRUE(imageBCC->isValid(0, nColumns - 1, 0));
    EXPECT_TRUE(imageBCC->isValid(0, 0, nLayers - 1));
    EXPECT_FALSE(imageBCC->isValid(nRows, 0, 0));
    EXPECT_FALSE(imageBCC->isValid(0, nColumns, 0));
    EXPECT_FALSE(imageBCC->isValid(0, 0, nLayers));
    EXPECT_FALSE(imageBCC->isValid(0, 0, 0, -1));
    EXPECT_FALSE(imageBCC->isValid(nRows - 1, 0, 0, -1));
    EXPECT_FALSE(imageBCC->isValid(0, nColumns - 1, 0, -1));
    EXPECT_FALSE(imageBCC->isValid(0, 0, nLayers - 1, -1));
    EXPECT_FALSE(imageBCC->isValid(0, 0, 0, nBands));
    EXPECT_FALSE(imageBCC->isValid(nRows - 1, 0, 0, nBands));
    EXPECT_FALSE(imageBCC->isValid(0, nColumns - 1, 0, nBands));
    EXPECT_FALSE(imageBCC->isValid(0, 0, nLayers - 1, nBands));
    EXPECT_TRUE(imageBCC->isValid(0, 0, 0, nBands - 1));
    EXPECT_TRUE(imageBCC->isValid(nRows - 1, 0, 0, nBands - 1));
    EXPECT_TRUE(imageBCC->isValid(0, nColumns - 1, 0, nBands - 1));
    EXPECT_TRUE(imageBCC->isValid(0, 0, nLayers - 1, nBands - 1));

    EXPECT_FALSE(imageFCC->isValid(-1));
    EXPECT_TRUE(imageFCC->isValid(0));
    EXPECT_TRUE(imageFCC->isValid(nElements - 1));
    EXPECT_FALSE(imageFCC->isValid(nElements));
    EXPECT_FALSE(imageFCC->isValid(0, -1));
    EXPECT_FALSE(imageFCC->isValid(nElements - 1, -1));
    EXPECT_FALSE(imageFCC->isValid(-1, 0));
    EXPECT_TRUE(imageFCC->isValid(0, 0));
    EXPECT_TRUE(imageFCC->isValid(nElements - 1, 0));
    EXPECT_FALSE(imageFCC->isValid(nElements, 0));
    EXPECT_TRUE(imageFCC->isValid(0, nBands - 1));
    EXPECT_TRUE(imageFCC->isValid(nElements - 1, nBands - 1));
    EXPECT_FALSE(imageFCC->isValid(0, nBands));
    EXPECT_FALSE(imageFCC->isValid(nElements - 1, nBands));
    EXPECT_FALSE(imageFCC->isValid(-1, 0, 0));
    EXPECT_FALSE(imageFCC->isValid(0, -1, 0));
    EXPECT_FALSE(imageFCC->isValid(0, 0, -1));
    EXPECT_TRUE(imageFCC->isValid(0, 0, 0));
    EXPECT_TRUE(imageFCC->isValid(nRows - 1, 0, 0));
    EXPECT_TRUE(imageFCC->isValid(0, nColumns - 1, 0));
    EXPECT_TRUE(imageFCC->isValid(0, 0, nLayers - 1));
    EXPECT_FALSE(imageFCC->isValid(nRows, 0, 0));
    EXPECT_FALSE(imageFCC->isValid(0, nColumns, 0));
    EXPECT_FALSE(imageFCC->isValid(0, 0, nLayers));
    EXPECT_FALSE(imageFCC->isValid(0, 0, 0, -1));
    EXPECT_FALSE(imageFCC->isValid(nRows - 1, 0, 0, -1));
    EXPECT_FALSE(imageFCC->isValid(0, nColumns - 1, 0, -1));
    EXPECT_FALSE(imageFCC->isValid(0, 0, nLayers - 1, -1));
    EXPECT_FALSE(imageFCC->isValid(0, 0, 0, nBands));
    EXPECT_FALSE(imageFCC->isValid(nRows - 1, 0, 0, nBands));
    EXPECT_FALSE(imageFCC->isValid(0, nColumns - 1, 0, nBands));
    EXPECT_FALSE(imageFCC->isValid(0, 0, nLayers - 1, nBands));
    EXPECT_TRUE(imageFCC->isValid(0, 0, 0, nBands - 1));
    EXPECT_TRUE(imageFCC->isValid(nRows - 1, 0, 0, nBands - 1));
    EXPECT_TRUE(imageFCC->isValid(0, nColumns - 1, 0, nBands - 1));
    EXPECT_TRUE(imageFCC->isValid(0, 0, nLayers - 1, nBands - 1));

    delete latticeCC;
    delete latticeBCC;
    delete latticeFCC;
    delete imageCC;
    delete imageBCC;
    delete imageFCC;

}