#include "gtest/gtest.h"
#include "../src/defs.h"
#include "../src/structuringelement.h"
#include "../src/cclattice.h"
#include "../src/image.h"

using namespace LatticeLib;

TEST(StructuringElement, initialization) {
    int neighborhoodSize1 = 6;
    int neighborhoodSize2 = 26;
    vector<FilterCoefficient<bool> > filterCoefficients;
    for (int coefficientIndex = 0; coefficientIndex < 7; coefficientIndex++) {
        filterCoefficients.push_back(FilterCoefficient<bool>(coefficientIndex - 1, true));
    }
    StructuringElement structuringElement1(filterCoefficients, neighborhoodSize1);
    StructuringElement structuringElement2(filterCoefficients, neighborhoodSize2);

    EXPECT_EQ(structuringElement1.getNeighborhoodSize(), neighborhoodSize1);
    EXPECT_NE(structuringElement2.getNeighborhoodSize(), neighborhoodSize1);
    EXPECT_EQ(structuringElement2.getNeighborhoodSize(), neighborhoodSize2);
    EXPECT_NE(structuringElement1.getNeighborhoodSize(), neighborhoodSize2);
}

TEST(StructuringElement, erosion) {

    int nRows = 5, nColumns = 10, nLayers = 5, nBands = 2;
    int nElements = nRows * nColumns * nLayers;
    double density = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, density);
    int imageData[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
                       0, 1, 1, 1, 0, 0, 1, 2, 1, 0,
                       0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 1, 1, 1, 0, 0, 1, 2, 1, 0,
                       0, 1, 1, 1, 0, 0, 2, 2, 2, 0,
                       0, 1, 1, 1, 0, 0, 1, 2, 1, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
                       0, 1, 1, 1, 0, 0, 1, 2, 1, 0,
                       0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 1, 1, 1, 0, 0, 2, 2, 2, 0,
                       0, 1, 2, 1, 0, 0, 2, 2, 2, 0,
                       0, 1, 1, 1, 0, 0, 2, 2, 2, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 1, 2, 1, 0, 0, 2, 2, 2, 0,
                       0, 2, 2, 2, 0, 0, 2, 2, 2, 0,
                       0, 1, 2, 1, 0, 0, 2, 2, 2, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 1, 1, 1, 0, 0, 2, 2, 2, 0,
                       0, 1, 2, 1, 0, 0, 2, 2, 2, 0,
                       0, 1, 1, 1, 0, 0, 2, 2, 2, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Image<int> image(imageData, lattice, nBands);
    int resultBandData[nElements];
    Image<int> resultBand(resultBandData, lattice, nBands);
    int resultData[nElements * nBands];
    Image<int> result(resultData, lattice, nBands);

    int result1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 1, 0, 0, 0, 0, 2, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 2, 0, 0, 0, 0, 2, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int result2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 1, 0, 0, 0, 0, 2, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 2, 0, 0, 0, 0, 2, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int neighborhoodSize1 = 26, neighborhoodSize2 = 6;
    vector<FilterCoefficient<bool> > filterCoefficients1, filterCoefficients2;
    for (int coefficientIndex = 0; coefficientIndex < 7; coefficientIndex++) {
        filterCoefficients1.push_back(FilterCoefficient<bool>(coefficientIndex - 1, true));
    }
    for (int coefficientIndex = 0; coefficientIndex < 27; coefficientIndex++) {
        filterCoefficients2.push_back(FilterCoefficient<bool>(coefficientIndex - 1, true));
    }
    StructuringElement structuringElement1(filterCoefficients1, neighborhoodSize1);
    StructuringElement structuringElement2(filterCoefficients2, neighborhoodSize2);

    structuringElement1.binaryErodeBand(image, 0, 0, resultBand);
    for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(result1[dataIndex], resultBandData[dataIndex]);
    }
    structuringElement1.binaryErodeBand(image, 1, 0, resultBand);
    for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(result1[nElements + dataIndex], resultBandData[dataIndex]);
    }
    structuringElement2.binaryErodeBand(image, 0, 0, resultBand);
    for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(result2[dataIndex], resultBandData[dataIndex]);
    }
    structuringElement2.binaryErodeBand(image, 1, 0, resultBand);
    for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(result2[nElements + dataIndex], resultBandData[dataIndex]);
    }

    structuringElement1.binaryErodeImage(image, 0, result);
    for (int dataIndex = 0; dataIndex < 2 * nElements; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(result1[dataIndex], resultData[dataIndex]);
    }
    structuringElement2.binaryErodeImage(image, 0, result);
    for (int dataIndex = 0; dataIndex < 2 * nElements; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));
        EXPECT_EQ(result2[dataIndex], resultData[dataIndex]);
    }
}