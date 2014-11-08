#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "exception.h"
#include <cmath>
#include <vector>

using namespace CImage;

TEST(CImageCC, bands) {

    int nR = 2, nC = 3, nL = 4, nB = 5;
    int N = nR * nC * nL;
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

    CImageCC<double> *imCC = new CImageCC<double>(data, nR, nC, nL, nB);

    // setElement
    double intensities[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    vector<double> intensities0(nB, 0.0);
    vector<double> intensitiesRight, intensitiesShort, intensitiesLong, originalIntensity;
    intensitiesShort.assign(intensities, intensities + 4);
    intensitiesRight.assign(intensities, intensities + 5);
    intensitiesLong.assign(intensities, intensities + 6);

    int index = 0;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 1;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 2;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 3;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 4;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 5;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 6;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 7;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 8;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 9;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 10;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 11;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 12;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 13;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 14;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 15;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 16;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 17;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 18;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 19;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 20;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 21;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 22;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 23;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);

    double *newData = imCC->getData();
    EXPECT_NEAR(data[0], newData[0], EPSILONT);
    EXPECT_NEAR(data[1], newData[1], EPSILONT);
    EXPECT_NEAR(data[2], newData[2], EPSILONT);
    EXPECT_NEAR(data[3], newData[3], EPSILONT);
    EXPECT_NEAR(data[4], newData[4], EPSILONT);
    EXPECT_NEAR(data[5], newData[5], EPSILONT);
    EXPECT_NEAR(data[6], newData[6], EPSILONT);
    EXPECT_NEAR(data[7], newData[7], EPSILONT);
    EXPECT_NEAR(data[8], newData[8], EPSILONT);
    EXPECT_NEAR(data[9], newData[9], EPSILONT);
    EXPECT_NEAR(data[10], newData[10], EPSILONT);
    EXPECT_NEAR(data[11], newData[11], EPSILONT);
    EXPECT_NEAR(data[12], newData[12], EPSILONT);
    EXPECT_NEAR(data[13], newData[13], EPSILONT);
    EXPECT_NEAR(data[14], newData[14], EPSILONT);
    EXPECT_NEAR(data[15], newData[15], EPSILONT);
    EXPECT_NEAR(data[16], newData[16], EPSILONT);
    EXPECT_NEAR(data[17], newData[17], EPSILONT);
    EXPECT_NEAR(data[18], newData[18], EPSILONT);
    EXPECT_NEAR(data[19], newData[19], EPSILONT);
    EXPECT_NEAR(data[20], newData[20], EPSILONT);
    EXPECT_NEAR(data[21], newData[21], EPSILONT);
    EXPECT_NEAR(data[22], newData[22], EPSILONT);
    EXPECT_NEAR(data[23], newData[23], EPSILONT);

    EXPECT_NEAR(data[24], newData[24], EPSILONT);
    EXPECT_NEAR(data[25], newData[25], EPSILONT);
    EXPECT_NEAR(data[26], newData[26], EPSILONT);
    EXPECT_NEAR(data[27], newData[27], EPSILONT);
    EXPECT_NEAR(data[28], newData[28], EPSILONT);
    EXPECT_NEAR(data[29], newData[29], EPSILONT);
    EXPECT_NEAR(data[30], newData[30], EPSILONT);
    EXPECT_NEAR(data[31], newData[31], EPSILONT);
    EXPECT_NEAR(data[32], newData[32], EPSILONT);
    EXPECT_NEAR(data[33], newData[33], EPSILONT);
    EXPECT_NEAR(data[34], newData[34], EPSILONT);
    EXPECT_NEAR(data[35], newData[35], EPSILONT);
    EXPECT_NEAR(data[36], newData[36], EPSILONT);
    EXPECT_NEAR(data[37], newData[37], EPSILONT);
    EXPECT_NEAR(data[38], newData[38], EPSILONT);
    EXPECT_NEAR(data[39], newData[39], EPSILONT);
    EXPECT_NEAR(data[40], newData[40], EPSILONT);
    EXPECT_NEAR(data[41], newData[41], EPSILONT);
    EXPECT_NEAR(data[42], newData[42], EPSILONT);
    EXPECT_NEAR(data[43], newData[43], EPSILONT);
    EXPECT_NEAR(data[44], newData[44], EPSILONT);
    EXPECT_NEAR(data[45], newData[45], EPSILONT);
    EXPECT_NEAR(data[46], newData[46], EPSILONT);
    EXPECT_NEAR(data[47], newData[47], EPSILONT);

    EXPECT_NEAR(data[48], newData[48], EPSILONT);
    EXPECT_NEAR(data[49], newData[49], EPSILONT);
    EXPECT_NEAR(data[50], newData[50], EPSILONT);
    EXPECT_NEAR(data[51], newData[51], EPSILONT);
    EXPECT_NEAR(data[52], newData[52], EPSILONT);
    EXPECT_NEAR(data[53], newData[53], EPSILONT);
    EXPECT_NEAR(data[54], newData[54], EPSILONT);
    EXPECT_NEAR(data[55], newData[55], EPSILONT);
    EXPECT_NEAR(data[56], newData[56], EPSILONT);
    EXPECT_NEAR(data[57], newData[57], EPSILONT);
    EXPECT_NEAR(data[58], newData[58], EPSILONT);
    EXPECT_NEAR(data[59], newData[59], EPSILONT);
    EXPECT_NEAR(data[60], newData[60], EPSILONT);
    EXPECT_NEAR(data[61], newData[61], EPSILONT);
    EXPECT_NEAR(data[62], newData[62], EPSILONT);
    EXPECT_NEAR(data[63], newData[63], EPSILONT);
    EXPECT_NEAR(data[64], newData[64], EPSILONT);
    EXPECT_NEAR(data[65], newData[65], EPSILONT);
    EXPECT_NEAR(data[66], newData[66], EPSILONT);
    EXPECT_NEAR(data[67], newData[67], EPSILONT);
    EXPECT_NEAR(data[68], newData[68], EPSILONT);
    EXPECT_NEAR(data[69], newData[69], EPSILONT);
    EXPECT_NEAR(data[70], newData[70], EPSILONT);
    EXPECT_NEAR(data[71], newData[71], EPSILONT);

    EXPECT_NEAR(data[72], newData[72], EPSILONT);
    EXPECT_NEAR(data[73], newData[73], EPSILONT);
    EXPECT_NEAR(data[74], newData[74], EPSILONT);
    EXPECT_NEAR(data[75], newData[75], EPSILONT);
    EXPECT_NEAR(data[76], newData[76], EPSILONT);
    EXPECT_NEAR(data[77], newData[77], EPSILONT);
    EXPECT_NEAR(data[78], newData[78], EPSILONT);
    EXPECT_NEAR(data[79], newData[79], EPSILONT);
    EXPECT_NEAR(data[80], newData[80], EPSILONT);
    EXPECT_NEAR(data[81], newData[81], EPSILONT);
    EXPECT_NEAR(data[82], newData[82], EPSILONT);
    EXPECT_NEAR(data[83], newData[83], EPSILONT);
    EXPECT_NEAR(data[84], newData[84], EPSILONT);
    EXPECT_NEAR(data[85], newData[85], EPSILONT);
    EXPECT_NEAR(data[86], newData[86], EPSILONT);
    EXPECT_NEAR(data[87], newData[87], EPSILONT);
    EXPECT_NEAR(data[88], newData[88], EPSILONT);
    EXPECT_NEAR(data[89], newData[89], EPSILONT);
    EXPECT_NEAR(data[90], newData[90], EPSILONT);
    EXPECT_NEAR(data[91], newData[91], EPSILONT);
    EXPECT_NEAR(data[92], newData[92], EPSILONT);
    EXPECT_NEAR(data[93], newData[93], EPSILONT);
    EXPECT_NEAR(data[94], newData[94], EPSILONT);
    EXPECT_NEAR(data[95], newData[95], EPSILONT);

    EXPECT_NEAR(data[96], newData[96], EPSILONT);
    EXPECT_NEAR(data[97], newData[97], EPSILONT);
    EXPECT_NEAR(data[98], newData[98], EPSILONT);
    EXPECT_NEAR(data[99], newData[99], EPSILONT);
    EXPECT_NEAR(data[100], newData[100], EPSILONT);
    EXPECT_NEAR(data[101], newData[101], EPSILONT);
    EXPECT_NEAR(data[102], newData[102], EPSILONT);
    EXPECT_NEAR(data[103], newData[103], EPSILONT);
    EXPECT_NEAR(data[104], newData[104], EPSILONT);
    EXPECT_NEAR(data[105], newData[105], EPSILONT);
    EXPECT_NEAR(data[106], newData[106], EPSILONT);
    EXPECT_NEAR(data[107], newData[107], EPSILONT);
    EXPECT_NEAR(data[108], newData[108], EPSILONT);
    EXPECT_NEAR(data[109], newData[109], EPSILONT);
    EXPECT_NEAR(data[110], newData[110], EPSILONT);
    EXPECT_NEAR(data[111], newData[111], EPSILONT);
    EXPECT_NEAR(data[112], newData[112], EPSILONT);
    EXPECT_NEAR(data[113], newData[113], EPSILONT);
    EXPECT_NEAR(data[114], newData[114], EPSILONT);
    EXPECT_NEAR(data[115], newData[115], EPSILONT);
    EXPECT_NEAR(data[116], newData[116], EPSILONT);
    EXPECT_NEAR(data[117], newData[117], EPSILONT);
    EXPECT_NEAR(data[118], newData[118], EPSILONT);
    EXPECT_NEAR(data[119], newData[119], EPSILONT);

    EXPECT_THROW(imCC->setElement(-1, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(N, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(1, intensitiesShort), dimensionMismatchException);
    EXPECT_THROW(imCC->setElement(1, intensitiesLong), dimensionMismatchException);

    EXPECT_THROW(imCC->setElement(-1, 1, 1, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(1, -1, 1, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(1, 1, -1, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(1, intensitiesShort), dimensionMismatchException);
    EXPECT_THROW(imCC->setElement(1, intensitiesLong), dimensionMismatchException);


/*
	// image parameters
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	uint8 resultInt[N * nB];
	double resultDouble[N * nB];
	for (uint8 b = 0; b < nB; b++) {
		for (int i = 0; i < N; i++) {
			data[b * N + i] = b;
		}
	}
	CImageCC<uint8> *imCC = new CImageCC<uint8>(data, nR, nC, nL, nB);

	// extract band
	EXPECT_THROW(imCC->getBand(-1, resultInt), outsideImageException);
	EXPECT_THROW(imCC->getBand(nB, resultInt), outsideImageException);

	for (int band = 0; band < nB; band++) {
		imCC->getBand(band, resultInt);
		for (int i = 0; i < N; i++) {
			EXPECT_TRUE(resultInt[i] == data[band * N + i]);
		}
	}

	// blend bands
	for (int b = 0; b < nB; b++) {
		for (int i = 0; i < N; i++) {
			data[b * N + i] = (i + b) % 3; // imCC is updated automatically, as it points to data.
		}
	}

	// min
	imCC->blend(0, resultInt);
	for (int i = 0; i < N; i++) {
		EXPECT_EQ(resultInt[i], 0);
	}

	// max
	imCC->blend(1, resultInt);
	for (int i = 0; i < N; i++) {
		EXPECT_EQ(resultInt[i], 2);
	}

	// mean
	imCC->blend(2, resultDouble);
	for (int i = 0; i < N; i++) {
		EXPECT_NEAR(resultDouble[i], 1.0, EPSILONT);
	}

	EXPECT_THROW(imCC->blend(-1, resultInt), outsideRangeException);
	EXPECT_THROW(imCC->blend(2, resultInt), outsideRangeException);
	EXPECT_THROW(imCC->blend(-1, resultDouble), outsideRangeException);
	EXPECT_THROW(imCC->blend(0, resultDouble), outsideRangeException);
	EXPECT_THROW(imCC->blend(3, resultDouble), outsideRangeException);

	delete imCC;
*/
}