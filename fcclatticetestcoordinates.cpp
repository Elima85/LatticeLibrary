#include "gtest/gtest.h"
#include "fcclattice.h"
#include "defs.h"
#include <cmath>

using namespace LatticeLib;

TEST(FCCLattice,coordinates) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor1 = 1.0;
    double scaleFactor2 = cbrt(2.5);

    FCCLattice lattice1(nRows, nColumns, nLayers, scaleFactor1);
    FCCLattice lattice2(nRows, nColumns, nLayers, scaleFactor2);

    // "1D" lattices
    FCCLattice lattice1Column1Layer(nElements, 1, 1, scaleFactor1);
    FCCLattice lattice1Row1Layer(1, nElements, 1, scaleFactor1);
    FCCLattice lattice1Row1Column(1, 1, nElements, scaleFactor1);

    // "2D" lattices
    int n1 = 15;
    int n2 = 14;
    FCCLattice lattice1Layer(n1, n2, 1, scaleFactor1);
    FCCLattice lattice1Column(n1, 1, n2, scaleFactor1);
    FCCLattice lattice1Row(1, n1, n2, scaleFactor1);

    vector<double> coordinates;

    // spel coordinates
    EXPECT_NEAR(lattice1.indexToX(0), FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToY(0), FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToZ(0), FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToX(135), FCCOFFSET + 6 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToY(135), FCCOFFSET + FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.indexToZ(135), FCCOFFSET + 2 * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.indexToX(80), FCCOFFSET + 5 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToY(80), FCCOFFSET + 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToZ(80), FCCOFFSET + 2 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToX(105), FCCOFFSET + 7 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToY(105), FCCOFFSET + 2 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToZ(105), FCCOFFSET + 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToX(110), FCCOFFSET + 4 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToY(110), FCCOFFSET + 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToZ(110), FCCOFFSET + 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToX(209), FCCOFFSET + 10 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToY(209), FCCOFFSET + 4 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.indexToZ(209), FCCOFFSET + 6 * FCCOFFSET, EPSILONT);

    lattice1.getCoordinates(0, coordinates);
    EXPECT_NEAR(coordinates[0], FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[1], FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[2], FCCOFFSET, EPSILONT);
    lattice1.getCoordinates(135, coordinates);
    EXPECT_NEAR(coordinates[0], FCCOFFSET + 6 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[1], FCCOFFSET + FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(coordinates[2], FCCOFFSET + 2 * FCCPOINTDISTANCE, EPSILONT);
    lattice1.getCoordinates(209, coordinates);
    EXPECT_NEAR(coordinates[0], FCCOFFSET + 10 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[1], FCCOFFSET + 4 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[2], FCCOFFSET + 6 * FCCOFFSET, EPSILONT);

    EXPECT_NEAR(lattice2.indexToX(0), scaleFactor2 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice2.indexToY(0), scaleFactor2 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice2.indexToZ(0), scaleFactor2 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice2.indexToX(135), scaleFactor2 * (FCCOFFSET + 6 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToY(135), scaleFactor2 * (FCCOFFSET + FCCPOINTDISTANCE), EPSILONT);
    EXPECT_NEAR(lattice2.indexToZ(135), scaleFactor2 * (FCCOFFSET + 2 * FCCPOINTDISTANCE), EPSILONT);
    EXPECT_NEAR(lattice2.indexToX(80), scaleFactor2 * (FCCOFFSET + 5 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToY(80), scaleFactor2 * (FCCOFFSET + 3 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToZ(80), scaleFactor2 * (FCCOFFSET + 2 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToX(105), scaleFactor2 * (FCCOFFSET + 7 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToY(105), scaleFactor2 * (FCCOFFSET + 2 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToZ(105), scaleFactor2 * (FCCOFFSET + 3 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToX(110), scaleFactor2 * (FCCOFFSET + 4 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToY(110), scaleFactor2 * (FCCOFFSET + 3 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToZ(110), scaleFactor2 * (FCCOFFSET + 3 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToX(209), scaleFactor2 * (FCCOFFSET + 10 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToY(209), scaleFactor2 * (FCCOFFSET + 4 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.indexToZ(209), scaleFactor2 * (FCCOFFSET + 6 * FCCOFFSET), EPSILONT);

    // width, height and depth
    EXPECT_NEAR(lattice1.getWidth(), 6 * FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1.getHeight(), 3 * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.getDepth(), (7 + 1) * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice2.getWidth(), scaleFactor2 * (6 * FCCPOINTDISTANCE + FCCOFFSET), EPSILONT);
    EXPECT_NEAR(lattice2.getHeight(), scaleFactor2 * (3 * FCCPOINTDISTANCE), EPSILONT);
    EXPECT_NEAR(lattice2.getDepth(), scaleFactor2 * (7 + 1) * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1Column1Layer.getWidth(), 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1Column1Layer.getHeight(), (nElements + 1) * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1Column1Layer.getDepth(), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1Row1Layer.getWidth(), nElements * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1Row1Layer.getHeight(), FCCPOINTDISTANCE, EPSILONT); //!!
    EXPECT_NEAR(lattice1Row1Layer.getDepth(), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1Row1Column.getWidth(), FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1Row1Column.getHeight(), FCCPOINTDISTANCE, EPSILONT); //!!
    EXPECT_NEAR(lattice1Row1Column.getDepth(), (nElements + 1) * FCCOFFSET, EPSILONT);

    EXPECT_NEAR(lattice1Layer.getWidth(), n2 * FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1Layer.getHeight(), (n1 + 1) * FCCOFFSET, EPSILONT); //!!
    EXPECT_NEAR(lattice1Layer.getDepth(), FCCPOINTDISTANCE, EPSILONT);

    EXPECT_NEAR(lattice1Column.getWidth(), FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1Column.getHeight(), (n1 + 1) * FCCOFFSET, EPSILONT); //!!
    EXPECT_NEAR(lattice1Column.getDepth(), (n2 + 1) * FCCOFFSET, EPSILONT);

    EXPECT_NEAR(lattice1Row.getWidth(), n1 * FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(lattice1Row.getHeight(), FCCPOINTDISTANCE, EPSILONT); //!!
    EXPECT_NEAR(lattice1Row.getDepth(), (n2 + 1) * FCCOFFSET, EPSILONT);
}

TEST(FCCLattice,distances) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor1 = 1.0;
    double scaleFactor2 = cbrt(2.5);
    FCCLattice lattice1(nRows, nColumns, nLayers, scaleFactor1);
    FCCLattice lattice2(nRows, nColumns, nLayers, scaleFactor2);

    // distance between spels
    EXPECT_NEAR(lattice1.euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(nElements- 1, nElements- 1), 0, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 69), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 69), lattice1.euclideanDistance(69, 105), EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 75), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 75), lattice1.euclideanDistance(75, 105), EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 76), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 76), lattice1.euclideanDistance(76, 105), EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 81), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 81), lattice1.euclideanDistance(81, 105), EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 99), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 99), lattice1.euclideanDistance(99, 105), EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 100), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 100), lattice1.euclideanDistance(100, 105), EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 45), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 45), lattice1.euclideanDistance(45, 105), EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 93), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 93), lattice1.euclideanDistance(93, 105), EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 104), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice1.euclideanDistance(105, 104), lattice1.euclideanDistance(104, 105), EPSILONT);

    EXPECT_NEAR(lattice2.euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(nElements- 1, nElements- 1), 0, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 69), scaleFactor2 * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 69), lattice2.euclideanDistance(69, 105), EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 75), scaleFactor2 * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 75), lattice2.euclideanDistance(75, 105), EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 76), scaleFactor2 * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 76), lattice2.euclideanDistance(76, 105), EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 81), scaleFactor2 * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 81), lattice2.euclideanDistance(81, 105), EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 99), scaleFactor2 * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 99), lattice2.euclideanDistance(99, 105), EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 100), scaleFactor2 * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 100), lattice2.euclideanDistance(100, 105), EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 45), scaleFactor2 * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 45), lattice2.euclideanDistance(45, 105), EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 93), scaleFactor2 * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 93), lattice2.euclideanDistance(93, 105), EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 104), scaleFactor2 * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(lattice2.euclideanDistance(105, 104), lattice2.euclideanDistance(104, 105), EPSILONT);

    vector<double> distanceVector;
    double ft[3] = {0, -FCCOFFSET, -FCCOFFSET};
    double fr[3] = {FCCOFFSET, 0, -FCCOFFSET};
    double fb[3] = {0, FCCOFFSET, -FCCOFFSET};
    double fl[3] = {-FCCOFFSET, 0, -FCCOFFSET};
    double mtr[3] = {FCCOFFSET, -FCCOFFSET, 0};
    double mbr[3] = {FCCOFFSET, FCCOFFSET, 0};
    double mbl[3] = {-FCCOFFSET, FCCOFFSET, 0};
    double mtl[3] = {-FCCOFFSET, -FCCOFFSET, 0};
    double bt[3] = {0, -FCCOFFSET, FCCOFFSET};
    double br[3] = {FCCOFFSET, 0, FCCOFFSET};
    double bb[3] = {0, FCCOFFSET, FCCOFFSET};
    double bl[3] = {-FCCOFFSET, 0, FCCOFFSET};
    double front[3] = {0, 0, -FCCPOINTDISTANCE};
    double top[3] = {0, -FCCPOINTDISTANCE, 0};
    double right[3] = {FCCPOINTDISTANCE, 0, 0};
    double bottom[3] = {0, FCCPOINTDISTANCE, 0};
    double left[3] = {-FCCPOINTDISTANCE, 0, 0};
    double back[3] = {0, 0, FCCPOINTDISTANCE};
    lattice1.euclideanDistanceVector(82, 82, distanceVector);
    EXPECT_TRUE(fabs(distanceVector[0]) < EPSILONT);
    EXPECT_TRUE(fabs(distanceVector[1]) < EPSILONT);
    EXPECT_TRUE(fabs(distanceVector[2]) < EPSILONT);
    lattice1.euclideanDistanceVector(105, 45, distanceVector);
    EXPECT_NEAR(distanceVector[0], front[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], front[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], front[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 93, distanceVector);
    EXPECT_NEAR(distanceVector[0], top[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], top[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], top[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 106, distanceVector);
    EXPECT_NEAR(distanceVector[0], right[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], right[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], right[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 117, distanceVector);
    EXPECT_NEAR(distanceVector[0], bottom[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], bottom[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], bottom[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 104, distanceVector);
    EXPECT_NEAR(distanceVector[0], left[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], left[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], left[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 165, distanceVector);
    EXPECT_NEAR(distanceVector[0], back[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], back[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], back[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 69, distanceVector);
    EXPECT_NEAR(distanceVector[0], ft[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], ft[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], ft[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 76, distanceVector);
    EXPECT_NEAR(distanceVector[0], fr[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], fr[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], fr[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 81, distanceVector);
    EXPECT_NEAR(distanceVector[0], fb[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], fb[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], fb[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 75, distanceVector);
    EXPECT_NEAR(distanceVector[0], fl[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], fl[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], fl[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 100, distanceVector);
    EXPECT_NEAR(distanceVector[0], mtr[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], mtr[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], mtr[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 112, distanceVector);
    EXPECT_NEAR(distanceVector[0], mbr[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], mbr[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], mbr[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 111, distanceVector);
    EXPECT_NEAR(distanceVector[0], mbl[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], mbl[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], mbl[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 99, distanceVector);
    EXPECT_NEAR(distanceVector[0], mtl[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], mtl[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], mtl[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 129, distanceVector);
    EXPECT_NEAR(distanceVector[0], bt[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], bt[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], bt[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 136, distanceVector);
    EXPECT_NEAR(distanceVector[0], br[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], br[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], br[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 141, distanceVector);
    EXPECT_NEAR(distanceVector[0], bb[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], bb[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], bb[2], EPSILONT);
    lattice1.euclideanDistanceVector(105, 135, distanceVector);
    EXPECT_NEAR(distanceVector[0], bl[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], bl[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], bl[2], EPSILONT);

    double ft2[3] = {0, -scaleFactor2 * FCCOFFSET, -scaleFactor2 * FCCOFFSET};
    double fr2[3] = {scaleFactor2 * FCCOFFSET, 0, -scaleFactor2 * FCCOFFSET};
    double fb2[3] = {0, scaleFactor2 * FCCOFFSET, -scaleFactor2 * FCCOFFSET};
    double fl2[3] = {-scaleFactor2 * FCCOFFSET, 0, -scaleFactor2 * FCCOFFSET};
    double mtr2[3] = {scaleFactor2 * FCCOFFSET, -scaleFactor2 * FCCOFFSET, 0};
    double mbr2[3] = {scaleFactor2 * FCCOFFSET, scaleFactor2 * FCCOFFSET, 0};
    double mbl2[3] = {-scaleFactor2 * FCCOFFSET, scaleFactor2 * FCCOFFSET, 0};
    double mtl2[3] = {-scaleFactor2 * FCCOFFSET, -scaleFactor2 * FCCOFFSET, 0};
    double bt2[3] = {0, -scaleFactor2 * FCCOFFSET, scaleFactor2 * FCCOFFSET};
    double br2[3] = {scaleFactor2 * FCCOFFSET, 0, scaleFactor2 * FCCOFFSET};
    double bb2[3] = {0, scaleFactor2 * FCCOFFSET, scaleFactor2 * FCCOFFSET};
    double bl2[3] = {-scaleFactor2 * FCCOFFSET, 0, scaleFactor2 * FCCOFFSET};
    double front2[3] = {0, 0, -scaleFactor2 * FCCPOINTDISTANCE};
    double top2[3] = {0, -scaleFactor2 * FCCPOINTDISTANCE, 0};
    double right2[3] = {scaleFactor2 * FCCPOINTDISTANCE, 0, 0};
    double bottom2[3] = {0, scaleFactor2 * FCCPOINTDISTANCE, 0};
    double left2[3] = {-scaleFactor2 * FCCPOINTDISTANCE, 0, 0};
    double back2[3] = {0, 0, scaleFactor2 * FCCPOINTDISTANCE};
    lattice2.euclideanDistanceVector(82, 82, distanceVector);
    EXPECT_TRUE(fabs(distanceVector[0]) < EPSILONT);
    EXPECT_TRUE(fabs(distanceVector[1]) < EPSILONT);
    EXPECT_TRUE(fabs(distanceVector[2]) < EPSILONT);
    lattice2.euclideanDistanceVector(105, 45, distanceVector);
    EXPECT_NEAR(distanceVector[0], front2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], front2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], front2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 93, distanceVector);
    EXPECT_NEAR(distanceVector[0], top2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], top2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], top2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 106, distanceVector);
    EXPECT_NEAR(distanceVector[0], right2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], right2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], right2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 117, distanceVector);
    EXPECT_NEAR(distanceVector[0], bottom2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], bottom2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], bottom2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 104, distanceVector);
    EXPECT_NEAR(distanceVector[0], left2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], left2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], left2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 165, distanceVector);
    EXPECT_NEAR(distanceVector[0], back2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], back2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], back2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 69, distanceVector);
    EXPECT_NEAR(distanceVector[0], ft2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], ft2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], ft2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 76, distanceVector);
    EXPECT_NEAR(distanceVector[0], fr2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], fr2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], fr2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 81, distanceVector);
    EXPECT_NEAR(distanceVector[0], fb2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], fb2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], fb2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 75, distanceVector);
    EXPECT_NEAR(distanceVector[0], fl2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], fl2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], fl2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 100, distanceVector);
    EXPECT_NEAR(distanceVector[0], mtr2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], mtr2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], mtr2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 112, distanceVector);
    EXPECT_NEAR(distanceVector[0], mbr2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], mbr2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], mbr2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 111, distanceVector);
    EXPECT_NEAR(distanceVector[0], mbl2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], mbl2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], mbl2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 99, distanceVector);
    EXPECT_NEAR(distanceVector[0], mtl2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], mtl2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], mtl2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 129, distanceVector);
    EXPECT_NEAR(distanceVector[0], bt2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], bt2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], bt2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 136, distanceVector);
    EXPECT_NEAR(distanceVector[0], br2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], br2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], br2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 141, distanceVector);
    EXPECT_NEAR(distanceVector[0], bb2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], bb2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], bb2[2], EPSILONT);
    lattice2.euclideanDistanceVector(105, 135, distanceVector);
    EXPECT_NEAR(distanceVector[0], bl2[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], bl2[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], bl2[2], EPSILONT);
}