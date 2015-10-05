#include "gtest/gtest.h"
#include "../defs.h"
#include "../bcclattice.h"
#include <cmath>

using namespace LatticeLib;

TEST(BCCLattice, areamapping) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double density2 = 2.5;
    double scaleFactor = cbrt(1/density2);
    scaleFactor = scaleFactor * scaleFactor;
    BCCLattice lattice1(nRows, nColumns, nLayers, 1.0);
    BCCLattice lattice2(nRows, nColumns, nLayers, density2);

    for (int index = 0; index < 1000; index++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(index));
        double coverage = double(index) / 1000.0;
        EXPECT_NEAR(lattice1.approximateIntersectionArea(coverage), lattice1.approximateIntersectionArea(1.0 - coverage), EPSILONT);
        EXPECT_NEAR(lattice2.approximateIntersectionArea(coverage), lattice2.approximateIntersectionArea(1.0 - coverage), EPSILONT);
        EXPECT_NEAR(lattice2.approximateIntersectionArea(coverage), lattice1.approximateIntersectionArea(coverage) * scaleFactor, EPSILONT);
    }

}