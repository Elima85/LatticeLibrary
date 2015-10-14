#include "gtest/gtest.h"
#include "../src/defs.h"
#include "../src/image.h"
#include "../src/cclattice.h"
#include "../src/exception.h"
#include <cmath>
#include <vector>

using namespace LatticeLib;

TEST(Image, bands) {

    int nRows = 2, nColumns = 3, nLayers = 4, nBands = 5;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice *lattice = new CCLattice(nRows, nColumns, nLayers, scaleFactor);
    double data[] = {1, 2, 3, 4, 5, 6,
            2, 3, 4, 5, 6, 1,
            3, 4, 5, 6, 1, 2,
            4, 5, 6, 1, 2, 3,

            11, 12, 13, 14, 15, 16,
            12, 13, 14, 15, 16, 11,
            13, 14, 15, 16, 11, 12,
            14, 15, 16, 11, 12, 13,

            21, 22, 23, 24, 25, 26,
            22, 23, 24, 25, 26, 21,
            23, 24, 25, 26, 21, 22,
            24, 25, 26, 21, 22, 23,

            31, 32, 33, 34, 35, 36,
            32, 33, 34, 35, 36, 31,
            33, 34, 35, 36, 31, 32,
            34, 35, 36, 31, 32, 33,

            41, 42, 43, 44, 45, 46,
            42, 43, 44, 45, 46, 41,
            43, 44, 45, 46, 41, 42,
            44, 45, 46, 41, 42, 43};

    Image<double> *image = new Image<double>(data, *lattice, nBands);// setElement
    double intensities[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    vector<double> intensities0(nBands, 0.0);
    vector<double> intensitiesRight, intensitiesShort, intensitiesLong, originalIntensity;
    intensitiesShort.assign(intensities, intensities + 4);
    intensitiesRight.assign(intensities, intensities + 5);
    intensitiesLong.assign(intensities, intensities + 6);

    int index = 0;
    originalIntensity = (*image)[index];
    image->setElement(index, intensities0);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 4), 0, EPSILONT);
    image->setElement(index, intensitiesRight);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    image->setElement(index, originalIntensity);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 4), originalIntensity[4], EPSILONT);

    index = 10;
    originalIntensity = (*image)[index];
    image->setElement(index, intensities0);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 4), 0, EPSILONT);
    image->setElement(index, intensitiesRight);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    image->setElement(index, originalIntensity);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 4), originalIntensity[4], EPSILONT);

    index = nElements - 1;
    originalIntensity = (*image)[index];
    image->setElement(index, intensities0);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 4), 0, EPSILONT);
    image->setElement(index, intensitiesRight);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    image->setElement(index, originalIntensity);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*image)(image->indexToR(index), image->indexToC(index), image->indexToL(index), 4), originalIntensity[4], EPSILONT);


    EXPECT_THROW(image->setElement(-1, intensitiesRight), outOfRangeException);
    EXPECT_THROW(image->setElement(nElements, intensitiesRight), outOfRangeException);
    EXPECT_THROW(image->setElement(1, intensitiesShort), incompatibleParametersException);
    EXPECT_THROW(image->setElement(1, intensitiesLong), incompatibleParametersException);

    EXPECT_THROW(image->setElement(-1, 1, 1, intensitiesRight), outOfRangeException);
    EXPECT_THROW(image->setElement(1, -1, 1, intensitiesRight), outOfRangeException);
    EXPECT_THROW(image->setElement(1, 1, -1, intensitiesRight), outOfRangeException);
    EXPECT_THROW(image->setElement(1, intensitiesShort), incompatibleParametersException);
    EXPECT_THROW(image->setElement(1, intensitiesLong), incompatibleParametersException);

    delete lattice;
    delete image;

}