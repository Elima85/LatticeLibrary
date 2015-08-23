#include "gtest/gtest.h"
#include "defs.h"
#include "uniformweight.h"
#include "exception.h"
#include "cclattice.h"

using namespace LatticeLib;

TEST(WeightAssignment, UniformWeight) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);
    double data[5*6*7];

    Image<double> reference(data, lattice, 1);
    Image<double> input(data, lattice, 1);

    UniformWeight<double> uniformWeight;

    for (int elementIndex1 = 0; elementIndex1 < nElements; elementIndex1++) {
        for (int elementIndex2 = 0; elementIndex2 < nElements; elementIndex2++) {
            string message1 = "index1 = ";
            string message2 = ", index2 = ";
            SCOPED_TRACE(message1 + to_string(elementIndex1) + message2 + to_string(elementIndex2));
            EXPECT_NEAR(1.0, uniformWeight.compute(elementIndex1, reference, elementIndex2, input), EPSILONT);
        }
    }
    EXPECT_THROW(uniformWeight.compute(0, reference, nElements, input), outOfRangeException);
    EXPECT_THROW(uniformWeight.compute(nElements, reference, 0, input), outOfRangeException);
    EXPECT_THROW(uniformWeight.compute(nElements, reference, nElements, input), outOfRangeException);
}