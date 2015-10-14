#include "gtest/gtest.h"
#include "../src/defs.h"
#include "../src/image.h"
#include "../src/cclattice.h"
#include "../src/bcclattice.h"
#include "../src/fcclattice.h"

using namespace LatticeLib;

TEST(Image,initialization) {

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

    Image<uint8> *imageCC = new Image<uint8>(data, *latticeCC, nBands);
    Image<uint8> *imageBCC = new Image<uint8>(data, *latticeBCC, nBands);
    Image<uint8> *imageFCC = new Image<uint8>(data, *latticeFCC, nBands);

    // image parameters
    EXPECT_TRUE(imageCC);
    EXPECT_EQ(latticeCC->getNRows(), imageCC->getNRows());
    EXPECT_EQ(latticeCC->getNColumns(), imageCC->getNColumns());
    EXPECT_EQ(latticeCC->getNLayers(), imageCC->getNLayers());
    EXPECT_EQ(latticeCC->getNElements(), imageCC->getNElements());
    EXPECT_EQ(latticeCC->getDensity(), imageCC->getDensity());
    EXPECT_EQ(nBands, imageCC->getNBands());
    EXPECT_EQ(long(data), long(imageCC->getData()));
    EXPECT_NE(latticeCC->getNRows(), imageCC->getNRows() + 1);
    EXPECT_NE(latticeCC->getNColumns(), imageCC->getNColumns() + 1);
    EXPECT_NE(latticeCC->getNLayers(), imageCC->getNLayers() + 1);
    EXPECT_NE(latticeCC->getNElements(), imageCC->getNElements() + 1);
    EXPECT_NE(0.0, imageCC->getDensity());
    EXPECT_NE(nBands, imageCC->getNBands() + 1);
    EXPECT_NE(0, long(imageCC->getData()));

    EXPECT_TRUE(imageBCC);
    EXPECT_EQ(latticeBCC->getNRows(), imageBCC->getNRows());
    EXPECT_EQ(latticeBCC->getNColumns(), imageBCC->getNColumns());
    EXPECT_EQ(latticeBCC->getNLayers(), imageBCC->getNLayers());
    EXPECT_EQ(latticeBCC->getNElements(), imageBCC->getNElements());
    EXPECT_EQ(latticeBCC->getDensity(), imageBCC->getDensity());
    EXPECT_EQ(nBands, imageBCC->getNBands());
    EXPECT_EQ(long(data), long(imageBCC->getData()));
    EXPECT_NE(latticeBCC->getNRows(), imageBCC->getNRows() + 1);
    EXPECT_NE(latticeBCC->getNColumns(), imageBCC->getNColumns() + 1);
    EXPECT_NE(latticeBCC->getNLayers(), imageBCC->getNLayers() + 1);
    EXPECT_NE(latticeBCC->getNElements(), imageBCC->getNElements() + 1);
    EXPECT_NE(0.0, imageBCC->getDensity());
    EXPECT_NE(nBands, imageBCC->getNBands() + 1);
    EXPECT_NE(0, long(imageBCC->getData()));

    EXPECT_TRUE(imageFCC);
    EXPECT_EQ(latticeFCC->getNRows(), imageFCC->getNRows());
    EXPECT_EQ(latticeFCC->getNColumns(), imageFCC->getNColumns());
    EXPECT_EQ(latticeFCC->getNLayers(), imageFCC->getNLayers());
    EXPECT_EQ(latticeFCC->getNElements(), imageFCC->getNElements());
    EXPECT_EQ(latticeFCC->getDensity(), imageFCC->getDensity());
    EXPECT_EQ(nBands, imageFCC->getNBands());
    EXPECT_EQ(long(data), long(imageFCC->getData()));
    EXPECT_NE(latticeFCC->getNRows(), imageFCC->getNRows() + 1);
    EXPECT_NE(latticeFCC->getNColumns(), imageFCC->getNColumns() + 1);
    EXPECT_NE(latticeFCC->getNLayers(), imageFCC->getNLayers() + 1);
    EXPECT_NE(latticeFCC->getNElements(), imageFCC->getNElements() + 1);
    EXPECT_NE(0.0, imageFCC->getDensity());
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

TEST(Image,copying) {

    int nRows = 2;
    int nColumns = 3;
    int nLayers = 4;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    uint8 data[nElements * nBands];
    for (int i = 0; i < nBands * nElements; i++) {
        data[i] = i;
    }

    Image<uint8> original(data, lattice, nBands);
    Image<uint8> copy(original);
    EXPECT_EQ(original.getNRows(), copy.getNRows());
    EXPECT_EQ(original.getNColumns(), copy.getNColumns());
    EXPECT_EQ(original.getNLayers(), copy.getNLayers());
    EXPECT_EQ(original.getNElements(), copy.getNElements());
    EXPECT_EQ(original.getDensity(), copy.getDensity());
    EXPECT_EQ(original.getNBands(), copy.getNBands());
    EXPECT_EQ(original.getData(), copy.getData());

    /*EXPECT_NE(original.getData(), copy.getData());

    uint8 *originalData = original.getData();
    uint8 *copiedData = copy.getData();
    EXPECT_EQ(originalData[0], copiedData[0]);
    EXPECT_EQ(originalData[1], copiedData[1]);
    EXPECT_EQ(originalData[2], copiedData[2]);
    EXPECT_EQ(originalData[3], copiedData[3]);
    EXPECT_EQ(originalData[4], copiedData[4]);
    EXPECT_EQ(originalData[5], copiedData[5]);
    EXPECT_EQ(originalData[6], copiedData[6]);
    EXPECT_EQ(originalData[7], copiedData[7]);
    EXPECT_EQ(originalData[8], copiedData[8]);
    EXPECT_EQ(originalData[9], copiedData[9]);
    EXPECT_EQ(originalData[10], copiedData[10]);
    EXPECT_EQ(originalData[11], copiedData[11]);
    EXPECT_EQ(originalData[12], copiedData[12]);
    EXPECT_EQ(originalData[13], copiedData[13]);
    EXPECT_EQ(originalData[14], copiedData[14]);
    EXPECT_EQ(originalData[15], copiedData[15]);
    EXPECT_EQ(originalData[16], copiedData[16]);
    EXPECT_EQ(originalData[17], copiedData[17]);
    EXPECT_EQ(originalData[18], copiedData[18]);
    EXPECT_EQ(originalData[19], copiedData[19]);
    EXPECT_EQ(originalData[20], copiedData[20]);
    EXPECT_EQ(originalData[21], copiedData[21]);
    EXPECT_EQ(originalData[22], copiedData[22]);
    EXPECT_EQ(originalData[23], copiedData[23]);
    EXPECT_EQ(originalData[24], copiedData[24]);
    EXPECT_EQ(originalData[25], copiedData[25]);
    EXPECT_EQ(originalData[26], copiedData[26]);
    EXPECT_EQ(originalData[27], copiedData[27]);
    EXPECT_EQ(originalData[28], copiedData[28]);
    EXPECT_EQ(originalData[29], copiedData[29]);
    EXPECT_EQ(originalData[30], copiedData[30]);
    EXPECT_EQ(originalData[31], copiedData[31]);
    EXPECT_EQ(originalData[32], copiedData[32]);
    EXPECT_EQ(originalData[33], copiedData[33]);
    EXPECT_EQ(originalData[34], copiedData[34]);
    EXPECT_EQ(originalData[35], copiedData[35]);
    EXPECT_EQ(originalData[36], copiedData[36]);
    EXPECT_EQ(originalData[37], copiedData[37]);
    EXPECT_EQ(originalData[38], copiedData[38]);
    EXPECT_EQ(originalData[39], copiedData[39]);
    EXPECT_EQ(originalData[40], copiedData[40]);
    EXPECT_EQ(originalData[41], copiedData[41]);
    EXPECT_EQ(originalData[42], copiedData[42]);
    EXPECT_EQ(originalData[43], copiedData[43]);
    EXPECT_EQ(originalData[44], copiedData[44]);
    EXPECT_EQ(originalData[45], copiedData[45]);
    EXPECT_EQ(originalData[46], copiedData[46]);
    EXPECT_EQ(originalData[47], copiedData[47]);
    EXPECT_EQ(originalData[48], copiedData[48]);
    EXPECT_EQ(originalData[49], copiedData[49]);
    EXPECT_EQ(originalData[50], copiedData[50]);
    EXPECT_EQ(originalData[51], copiedData[51]);
    EXPECT_EQ(originalData[52], copiedData[52]);
    EXPECT_EQ(originalData[53], copiedData[53]);
    EXPECT_EQ(originalData[54], copiedData[54]);
    EXPECT_EQ(originalData[55], copiedData[55]);
    EXPECT_EQ(originalData[56], copiedData[56]);
    EXPECT_EQ(originalData[57], copiedData[57]);
    EXPECT_EQ(originalData[58], copiedData[58]);
    EXPECT_EQ(originalData[59], copiedData[59]);
    EXPECT_EQ(originalData[60], copiedData[60]);
    EXPECT_EQ(originalData[61], copiedData[61]);
    EXPECT_EQ(originalData[62], copiedData[62]);
    EXPECT_EQ(originalData[63], copiedData[63]);
    EXPECT_EQ(originalData[64], copiedData[64]);
    EXPECT_EQ(originalData[65], copiedData[65]);
    EXPECT_EQ(originalData[66], copiedData[66]);
    EXPECT_EQ(originalData[67], copiedData[67]);
    EXPECT_EQ(originalData[68], copiedData[68]);
    EXPECT_EQ(originalData[69], copiedData[69]);
    EXPECT_EQ(originalData[70], copiedData[70]);
    EXPECT_EQ(originalData[71], copiedData[71]);*/

}