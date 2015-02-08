#include "gtest/gtest.h"
#include "cclattice.h"
#include "defs.h"
#include <cmath>

using namespace CImage;

TEST(CCLattice,coordinates) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor1 = 1.0;
    double scaleFactor2 = cbrt(2.5);
    
    CCLattice* lattice1 = new CCLattice(nRows, nColumns, nLayers, scaleFactor1);
    CCLattice* lattice2 = new CCLattice(nRows, nColumns, nLayers, scaleFactor2);
    
    // "1D" lattices
    CCLattice *lattice1Column1Layer = new CCLattice(nElements, 1, 1, scaleFactor1);
    CCLattice *lattice1Row1Layer = new CCLattice(1, nElements, 1, scaleFactor1);
    CCLattice *lattice1Row1Column = new CCLattice(1, 1, nElements, scaleFactor1);
    
    // "2D" lattices
    int n1 = 15;
    int n2 = 14;
    CCLattice *lattice1Layer = new CCLattice(n1, n2, 1, scaleFactor1);
    CCLattice *lattice1Column = new CCLattice(n1, 1, n2, scaleFactor1);
    CCLattice *lattice1Row = new CCLattice(1, n1, n2, scaleFactor1);
    
    vector<double> coordinates;
    
    // coordinates, unit scale
    EXPECT_NEAR(lattice1->indexToX(0), 0.5, EPSILONT);
    EXPECT_NEAR(lattice1->indexToY(0), 0.5, EPSILONT);
    EXPECT_NEAR(lattice1->indexToZ(0), 0.5, EPSILONT);
    EXPECT_NEAR(lattice1->indexToX(170), 0.5 + 2, EPSILONT);
    EXPECT_NEAR(lattice1->indexToY(170), 0.5 + 3, EPSILONT);
    EXPECT_NEAR(lattice1->indexToZ(170), 0.5 + 5, EPSILONT);
    EXPECT_NEAR(lattice1->indexToX(209), 0.5 + 5, EPSILONT);
    EXPECT_NEAR(lattice1->indexToY(209), 0.5 + 4, EPSILONT);
    EXPECT_NEAR(lattice1->indexToZ(209), 0.5 + 6, EPSILONT);
    EXPECT_NEAR(lattice1->indexToX(nElements - 1), 0.5 + nColumns - 1, EPSILONT);
    EXPECT_NEAR(lattice1->indexToY(nElements - 1), 0.5 + nRows - 1, EPSILONT);
    EXPECT_NEAR(lattice1->indexToZ(nElements - 1), 0.5 + nLayers - 1, EPSILONT);
    lattice1->getCoordinates(0, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5, EPSILONT);
    lattice1->getCoordinates(170, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5 + 2, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5 + 3, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5 + 5, EPSILONT);
    lattice1->getCoordinates(209, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5 + 5, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5 + 4, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5 + 6, EPSILONT);
    lattice1->getCoordinates(nElements - 1, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5 + nColumns - 1, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5 + nRows - 1, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5 + nLayers - 1, EPSILONT);

    EXPECT_NEAR(lattice2->indexToX(0), 0.5 * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToY(0), 0.5 * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToZ(0), 0.5 * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToX(170), (0.5 + 2) * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToY(170), (0.5 + 3) * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToZ(170), (0.5 + 5) * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToX(209), (0.5 + 5) * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToY(209), (0.5 + 4) * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToZ(209), (0.5 + 6) * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToX(nElements - 1), (0.5 + (nColumns - 1)) * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToY(nElements - 1), (0.5 + (nRows - 1)) * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->indexToZ(nElements - 1), (0.5 + (nLayers - 1)) * scaleFactor2, EPSILONT);

    EXPECT_GT(lattice2->indexToX(170) - lattice1->indexToX(170), EPSILONT);
    EXPECT_GT(lattice2->indexToY(170) - lattice1->indexToY(170), EPSILONT);
    EXPECT_GT(lattice2->indexToZ(170) - lattice1->indexToZ(170), EPSILONT);
    EXPECT_GT(lattice2->indexToX(209) - lattice1->indexToX(209), EPSILONT);
    EXPECT_GT(lattice2->indexToY(209) - lattice1->indexToY(209), EPSILONT);
    EXPECT_GT(lattice2->indexToZ(209) - lattice1->indexToZ(209), EPSILONT);
    EXPECT_GT(lattice2->indexToX(nElements - 1) - lattice1->indexToX(nElements - 1), EPSILONT);
    EXPECT_GT(lattice2->indexToY(nElements - 1) - lattice1->indexToY(nElements - 1), EPSILONT);
    EXPECT_GT(lattice2->indexToZ(nElements - 1) - lattice1->indexToZ(nElements - 1), EPSILONT);

    // width, height and depth
    EXPECT_NEAR(lattice1->getWidth(), 6, EPSILONT);
    EXPECT_NEAR(lattice1->getHeight(), 5, EPSILONT);
    EXPECT_NEAR(lattice1->getDepth(), 7, EPSILONT);
    EXPECT_NEAR(lattice2->getWidth(), scaleFactor2 * 6, EPSILONT);
    EXPECT_NEAR(lattice2->getHeight(), scaleFactor2 * 5, EPSILONT);
    EXPECT_NEAR(lattice2->getDepth(), scaleFactor2 * 7, EPSILONT);
    EXPECT_NEAR(lattice1Column1Layer->getWidth(), 1, EPSILONT);
    EXPECT_NEAR(lattice1Column1Layer->getHeight(), nElements, EPSILONT);
    EXPECT_NEAR(lattice1Column1Layer->getDepth(), 1, EPSILONT);
    EXPECT_NEAR(lattice1Row1Layer->getWidth(), nElements, EPSILONT);
    EXPECT_NEAR(lattice1Row1Layer->getHeight(), 1, EPSILONT);
    EXPECT_NEAR(lattice1Row1Layer->getDepth(), 1, EPSILONT);
    EXPECT_NEAR(lattice1Row1Column->getWidth(), 1, EPSILONT);
    EXPECT_NEAR(lattice1Row1Column->getHeight(), 1, EPSILONT);
    EXPECT_NEAR(lattice1Row1Column->getDepth(), nElements, EPSILONT);

    EXPECT_NEAR(lattice1Layer->getWidth(), n2, EPSILONT);
    EXPECT_NEAR(lattice1Layer->getHeight(), n1, EPSILONT);
    EXPECT_NEAR(lattice1Layer->getDepth(), 1, EPSILONT);

    EXPECT_NEAR(lattice1Column->getWidth(), 1, EPSILONT);
    EXPECT_NEAR(lattice1Column->getHeight(), n1, EPSILONT);
    EXPECT_NEAR(lattice1Column->getDepth(), n2, EPSILONT);

    EXPECT_NEAR(lattice1Row->getWidth(), n1, EPSILONT);
    EXPECT_NEAR(lattice1Row->getHeight(), 1, EPSILONT);
    EXPECT_NEAR(lattice1Row->getDepth(), n2, EPSILONT);
    
    delete lattice1;
    delete lattice2;
    delete lattice1Column1Layer;
    delete lattice1Row1Layer;
    delete lattice1Row1Column;
    delete lattice1Layer;
    delete lattice1Column;
    delete lattice1Row;
}

TEST(CCLattice,distances) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor1 = 1.0;
    double scaleFactor2 = cbrt(2.5);
    CCLattice *lattice1 = new CCLattice(nRows, nColumns, nLayers, scaleFactor1);
    CCLattice *lattice2 = new CCLattice(nRows, nColumns, nLayers, scaleFactor2);

    // distance between spels
    EXPECT_NEAR(lattice1->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(nElements - 1, nElements - 1), 0, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 104), 1, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 104), lattice1->euclideanDistance(104, 103), EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 97), 1, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 97), lattice1->euclideanDistance(97, 103), EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 73), 1, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 73), lattice1->euclideanDistance(73, 103), EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 110), 1.41421356237, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 110), lattice1->euclideanDistance(110, 103), EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 98), 1.41421356237, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 98), lattice1->euclideanDistance(98, 103), EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 67), 1.41421356237, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 67), lattice1->euclideanDistance(67, 103), EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 79), 1.41421356237, EPSILONT);
    EXPECT_NEAR(lattice1->euclideanDistance(103, 79), lattice1->euclideanDistance(79, 103), EPSILONT);

    EXPECT_NEAR(lattice2->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(nElements - 1, nElements - 1), 0, EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 104), 1 * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 104), lattice2->euclideanDistance(104, 103), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 97), 1 * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 97), lattice2->euclideanDistance(97, 103), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 73), 1 * scaleFactor2, EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 73), lattice2->euclideanDistance(73, 103), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 110), sqrt(scaleFactor2 * scaleFactor2 * 2), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 110), lattice2->euclideanDistance(110, 103), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 98), sqrt(scaleFactor2 * scaleFactor2 * 2), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 98), lattice2->euclideanDistance(98, 103), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 67), sqrt(scaleFactor2 * scaleFactor2 * 2), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 67), lattice2->euclideanDistance(67, 103), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 79), sqrt(scaleFactor2 * scaleFactor2 * 2), EPSILONT);
    EXPECT_NEAR(lattice2->euclideanDistance(103, 79), lattice2->euclideanDistance(79, 103), EPSILONT);

    vector<double> distanceVector;
    double xyz100[3] = {1, 0, 0};
    double xyz010[3] = {0, 1, 0};
    double xyz001[3] = {0, 0, 1};
    double xyz123[3] = {1, 2, 3};
    lattice1->euclideanDistanceVector(103, 103, distanceVector);
    EXPECT_TRUE(fabs(distanceVector[0]) < EPSILONT);
    EXPECT_TRUE(fabs(distanceVector[1]) < EPSILONT);
    EXPECT_TRUE(fabs(distanceVector[2]) < EPSILONT);
    lattice1->euclideanDistanceVector(103, 104, distanceVector);
    EXPECT_NEAR(distanceVector[0], xyz100[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], xyz100[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], xyz100[2], EPSILONT);
    lattice1->euclideanDistanceVector(103, 109, distanceVector);
    EXPECT_NEAR(distanceVector[0], xyz010[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], xyz010[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], xyz010[2], EPSILONT);
    lattice1->euclideanDistanceVector(73, 103, distanceVector);
    EXPECT_NEAR(distanceVector[0], xyz001[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], xyz001[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], xyz001[2], EPSILONT);
    lattice1->euclideanDistanceVector(13, 116, distanceVector);
    EXPECT_NEAR(distanceVector[0], xyz123[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], xyz123[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], xyz123[2], EPSILONT);

    double xyz2100[3] = {1 * scaleFactor2, 0, 0};
    double xyz2010[3] = {0, 1 * scaleFactor2, 0};
    double xyz2001[3] = {0, 0, 1 * scaleFactor2};
    double xyz2123[3] = {1 * scaleFactor2, 2 * scaleFactor2, 3 * scaleFactor2};
    lattice2->euclideanDistanceVector(103, 103, distanceVector);
    EXPECT_TRUE(fabs(distanceVector[0]) < EPSILONT);
    EXPECT_TRUE(fabs(distanceVector[1]) < EPSILONT);
    EXPECT_TRUE(fabs(distanceVector[2]) < EPSILONT);
    lattice2->euclideanDistanceVector(103, 104, distanceVector);
    EXPECT_NEAR(distanceVector[0], xyz2100[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], xyz2100[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], xyz2100[2], EPSILONT);
    lattice2->euclideanDistanceVector(103, 109, distanceVector);
    EXPECT_NEAR(distanceVector[0], xyz2010[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], xyz2010[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], xyz2010[2], EPSILONT);
    lattice2->euclideanDistanceVector(73, 103, distanceVector);
    EXPECT_NEAR(distanceVector[0], xyz2001[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], xyz2001[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], xyz2001[2], EPSILONT);
    lattice2->euclideanDistanceVector(13, 116, distanceVector);
    EXPECT_NEAR(distanceVector[0], xyz2123[0], EPSILONT);
    EXPECT_NEAR(distanceVector[1], xyz2123[1], EPSILONT);
    EXPECT_NEAR(distanceVector[2], xyz2123[2], EPSILONT);
    
    delete lattice1;
    delete lattice2;
    
}