#include "gtest/gtest.h"
#include "bcclattice.h"
#include "defs.h"

using namespace CImage;

TEST(BCCLattice, initialization) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor1 = 1.0;
    double scaleFactor2 = 2.5;

    BCCLattice lattice1(nRows, nColumns, nLayers, scaleFactor1);
    BCCLattice lattice2(nRows, nColumns, nLayers, scaleFactor2);
    BCCLattice lattice3(lattice2);

    EXPECT_EQ(lattice1.getNRows(), nRows);
    EXPECT_NE(lattice1.getNRows(), nRows + 1);
    EXPECT_EQ(lattice1.getNColumns(), nColumns);
    EXPECT_NE(lattice1.getNColumns(), nColumns + 1);
    EXPECT_EQ(lattice1.getNLayers(), nLayers);
    EXPECT_NE(lattice1.getNLayers(), nLayers + 1);
    EXPECT_EQ(lattice1.getNElements(), nElements);
    EXPECT_NE(lattice1.getNElements(), nElements + 1);
    EXPECT_NEAR(lattice1.getScaleFactor(), scaleFactor1, EPSILONT);

    EXPECT_EQ(lattice2.getNRows(), nRows);
    EXPECT_NE(lattice2.getNRows(), nRows + 1);
    EXPECT_EQ(lattice2.getNColumns(), nColumns);
    EXPECT_NE(lattice2.getNColumns(), nColumns + 1);
    EXPECT_EQ(lattice2.getNLayers(), nLayers);
    EXPECT_NE(lattice2.getNLayers(), nLayers + 1);
    EXPECT_EQ(lattice2.getNElements(), nElements);
    EXPECT_NE(lattice2.getNElements(), nElements + 1);
    EXPECT_NEAR(lattice2.getScaleFactor(), scaleFactor2, EPSILONT);

    // copy constructor
    EXPECT_EQ(lattice2.getNRows(), lattice3.getNRows());
    EXPECT_EQ(lattice2.getNColumns(), lattice3.getNColumns());
    EXPECT_EQ(lattice2.getNLayers(), lattice3.getNLayers());
    EXPECT_EQ(lattice2.getNElements(), lattice3.getNElements());
    EXPECT_EQ(lattice2.getScaleFactor(), lattice3.getScaleFactor());
    EXPECT_NE(lattice1.getScaleFactor(), lattice3.getScaleFactor());

    // validity of elements
    EXPECT_FALSE(lattice1.isValid(-1));
    EXPECT_TRUE(lattice1.isValid(0));
    EXPECT_TRUE(lattice1.isValid(nElements - 1));
    EXPECT_FALSE(lattice1.isValid(nElements));
    EXPECT_FALSE(lattice1.isValid(-1, 0, 0));
    EXPECT_FALSE(lattice1.isValid(0, -1, 0));
    EXPECT_FALSE(lattice1.isValid(0, 0, -1));
    EXPECT_TRUE(lattice1.isValid(0, 0, 0));
    EXPECT_TRUE(lattice1.isValid(nRows - 1, 0, 0));
    EXPECT_TRUE(lattice1.isValid(0, nColumns - 1, 0));
    EXPECT_TRUE(lattice1.isValid(0, 0, nLayers - 1));
    EXPECT_FALSE(lattice1.isValid(nRows, 0, 0));
    EXPECT_FALSE(lattice1.isValid(0, nColumns, 0));
    EXPECT_FALSE(lattice1.isValid(0, 0, nLayers));

    // index conversion
    EXPECT_EQ(lattice1.rclToIndex(0, 0, 0), 0);
    EXPECT_EQ(lattice1.rclToIndex(1, 2, 3), 98);
    EXPECT_EQ(lattice1.rclToIndex(nRows - 1, nColumns - 1, nLayers - 1), nElements - 1);
    EXPECT_EQ(lattice1.indexToR(0), 0);
    EXPECT_EQ(lattice1.indexToC(0), 0);
    EXPECT_EQ(lattice1.indexToL(0), 0);
    EXPECT_EQ(lattice1.indexToR(98), 1);
    EXPECT_EQ(lattice1.indexToC(98), 2);
    EXPECT_EQ(lattice1.indexToL(98), 3);
    EXPECT_EQ(lattice1.indexToR(nElements - 1), nRows - 1);
    EXPECT_EQ(lattice1.indexToC(nElements - 1), nColumns - 1);
    EXPECT_EQ(lattice1.indexToL(nElements - 1), nLayers - 1);
}