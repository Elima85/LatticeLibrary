#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "exception.h"
#include <cmath>
#include <vector>

using namespace CImage;

TEST(CImageCC, coordinates) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = 0;
    }
    CImageCC<uint8> *imCC = new CImageCC<uint8>(data, nR, nC, nL, nB);
    double volume = 2.5;
    double factor = cbrt(volume);
    CImageCC<uint8> *imCC2 = new CImageCC<uint8>(data, nR, nC, nL, nB, volume);

    CImageCC<uint8> *imCC1C1L = new CImageCC<uint8>(data, N, 1, 1, 1);
    CImageCC<uint8> *imCC1R1L = new CImageCC<uint8>(data, 1, N, 1, 1);
    CImageCC<uint8> *imCC1R1C = new CImageCC<uint8>(data, 1, 1, N, 1);
    int n1 = 15, n2 = 14;
    CImageCC<uint8> *imCCRC = new CImageCC<uint8>(data, n1, n2, 1, 1);
    CImageCC<uint8> *imCCRL = new CImageCC<uint8>(data, n1, 1, n2, 1);
    CImageCC<uint8> *imCCCL = new CImageCC<uint8>(data, 1, n1, n2, 1);
    vector<double> coordinates;

    // spel coordinates
    EXPECT_NEAR(imCC->indexToX(0), 0.5, EPSILONT);
    EXPECT_NEAR(imCC->indexToY(0), 0.5, EPSILONT);
    EXPECT_NEAR(imCC->indexToZ(0), 0.5, EPSILONT);
    EXPECT_NEAR(imCC->indexToX(170), 0.5 + 2, EPSILONT);
    EXPECT_NEAR(imCC->indexToY(170), 0.5 + 3, EPSILONT);
    EXPECT_NEAR(imCC->indexToZ(170), 0.5 + 5, EPSILONT);
    EXPECT_NEAR(imCC->indexToX(209), 0.5 + 5, EPSILONT);
    EXPECT_NEAR(imCC->indexToY(209), 0.5 + 4, EPSILONT);
    EXPECT_NEAR(imCC->indexToZ(209), 0.5 + 6, EPSILONT);
    EXPECT_NEAR(imCC->indexToX(N - 1), 0.5 + nC - 1, EPSILONT);
    EXPECT_NEAR(imCC->indexToY(N - 1), 0.5 + nR - 1, EPSILONT);
    EXPECT_NEAR(imCC->indexToZ(N - 1), 0.5 + nL - 1, EPSILONT);

    imCC->getCoordinates(0, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5, EPSILONT);
    imCC->getCoordinates(170, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5 + 2, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5 + 3, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5 + 5, EPSILONT);
    imCC->getCoordinates(209, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5 + 5, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5 + 4, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5 + 6, EPSILONT);
    imCC->getCoordinates(N - 1, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5 + nC - 1, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5 + nR - 1, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5 + nL - 1, EPSILONT);

    EXPECT_NEAR(imCC2->indexToX(0), 0.5 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToY(0), 0.5 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToZ(0), 0.5 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToX(170), (0.5 + 2) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToY(170), (0.5 + 3) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToZ(170), (0.5 + 5) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToX(209), (0.5 + 5) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToY(209), (0.5 + 4) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToZ(209), (0.5 + 6) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToX(N - 1), (0.5 + (nC - 1)) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToY(N - 1), (0.5 + (nR - 1)) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToZ(N - 1), (0.5 + (nL - 1)) * factor, EPSILONT);

    EXPECT_GT(imCC2->indexToX(170) - imCC->indexToX(170), EPSILONT);
    EXPECT_GT(imCC2->indexToY(170) - imCC->indexToY(170), EPSILONT);
    EXPECT_GT(imCC2->indexToZ(170) - imCC->indexToZ(170), EPSILONT);
    EXPECT_GT(imCC2->indexToX(209) - imCC->indexToX(209), EPSILONT);
    EXPECT_GT(imCC2->indexToY(209) - imCC->indexToY(209), EPSILONT);
    EXPECT_GT(imCC2->indexToZ(209) - imCC->indexToZ(209), EPSILONT);
    EXPECT_GT(imCC2->indexToX(N - 1) - imCC->indexToX(N - 1), EPSILONT);
    EXPECT_GT(imCC2->indexToY(N - 1) - imCC->indexToY(N - 1), EPSILONT);
    EXPECT_GT(imCC2->indexToZ(N - 1) - imCC->indexToZ(N - 1), EPSILONT);

    // width, height and depth
    EXPECT_NEAR(imCC->getWidth(), 6, EPSILONT);
    EXPECT_NEAR(imCC->getHeight(), 5, EPSILONT);
    EXPECT_NEAR(imCC->getDepth(), 7, EPSILONT);
    EXPECT_NEAR(imCC2->getWidth(), factor * 6, EPSILONT);
    EXPECT_NEAR(imCC2->getHeight(), factor * 5, EPSILONT);
    EXPECT_NEAR(imCC2->getDepth(), factor * 7, EPSILONT);
    EXPECT_NEAR(imCC1C1L->getWidth(), 1, EPSILONT);
    EXPECT_NEAR(imCC1C1L->getHeight(), N, EPSILONT);
    EXPECT_NEAR(imCC1C1L->getDepth(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1L->getWidth(), N, EPSILONT);
    EXPECT_NEAR(imCC1R1L->getHeight(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1L->getDepth(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1C->getWidth(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1C->getHeight(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1C->getDepth(), N, EPSILONT);

    EXPECT_NEAR(imCCRC->getWidth(), n2, EPSILONT);
    EXPECT_NEAR(imCCRC->getHeight(), n1, EPSILONT);
    EXPECT_NEAR(imCCRC->getDepth(), 1, EPSILONT);

    EXPECT_NEAR(imCCRL->getWidth(), 1, EPSILONT);
    EXPECT_NEAR(imCCRL->getHeight(), n1, EPSILONT);
    EXPECT_NEAR(imCCRL->getDepth(), n2, EPSILONT);

    EXPECT_NEAR(imCCCL->getWidth(), n1, EPSILONT);
    EXPECT_NEAR(imCCCL->getHeight(), 1, EPSILONT);
    EXPECT_NEAR(imCCCL->getDepth(), n2, EPSILONT);

    delete imCC;
    delete imCC2;
    delete imCC1C1L;
    delete imCC1R1L;
    delete imCC1R1C;
    delete imCCCL;
    delete imCCRL;
    delete imCCRC;
}

TEST(CImageCC, distances) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = 0;
    }
    CImageCC<uint8> *imCC = new CImageCC<uint8>(data, nR, nC, nL, nB);
    double volume = 2.5;
    double factor = cbrt(volume);
    CImageCC<uint8> *imCC2 = new CImageCC<uint8>(data, nR, nC, nL, nB, volume);

    // distance between spels
    EXPECT_NEAR(imCC->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 104), 1, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 104), imCC->euclideanDistance(104, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 97), 1, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 97), imCC->euclideanDistance(97, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 73), 1, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 73), imCC->euclideanDistance(73, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 110), 1.41421356237, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 110), imCC->euclideanDistance(110, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 98), 1.41421356237, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 98), imCC->euclideanDistance(98, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 67), 1.41421356237, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 67), imCC->euclideanDistance(67, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 79), 1.41421356237, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 79), imCC->euclideanDistance(79, 103), EPSILONT);

    EXPECT_NEAR(imCC2->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 104), 1 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 104), imCC2->euclideanDistance(104, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 97), 1 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 97), imCC2->euclideanDistance(97, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 73), 1 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 73), imCC2->euclideanDistance(73, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 110), sqrt(factor * factor * 2), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 110), imCC2->euclideanDistance(110, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 98), sqrt(factor * factor * 2), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 98), imCC2->euclideanDistance(98, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 67), sqrt(factor * factor * 2), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 67), imCC2->euclideanDistance(67, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 79), sqrt(factor * factor * 2), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 79), imCC2->euclideanDistance(79, 103), EPSILONT);

    vector<double> dv;
    double xyz100[3] = {1, 0, 0};
    double xyz010[3] = {0, 1, 0};
    double xyz001[3] = {0, 0, 1};
    double xyz123[3] = {1, 2, 3};
    imCC->euclideanDistanceVector(103, 103, dv);
    EXPECT_TRUE(fabs(dv[0]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[1]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[2]) < EPSILONT);
    imCC->euclideanDistanceVector(103, 104, dv);
    EXPECT_NEAR(dv[0], xyz100[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz100[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz100[2], EPSILONT);
    imCC->euclideanDistanceVector(103, 109, dv);
    EXPECT_NEAR(dv[0], xyz010[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz010[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz010[2], EPSILONT);
    imCC->euclideanDistanceVector(73, 103, dv);
    EXPECT_NEAR(dv[0], xyz001[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz001[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz001[2], EPSILONT);
    imCC->euclideanDistanceVector(13, 116, dv);
    EXPECT_NEAR(dv[0], xyz123[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz123[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz123[2], EPSILONT);

    double xyz2100[3] = {1 * factor, 0, 0};
    double xyz2010[3] = {0, 1 * factor, 0};
    double xyz2001[3] = {0, 0, 1 * factor};
    double xyz2123[3] = {1 * factor, 2 * factor, 3 * factor};
    imCC2->euclideanDistanceVector(103, 103, dv);
    EXPECT_TRUE(fabs(dv[0]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[1]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[2]) < EPSILONT);
    imCC2->euclideanDistanceVector(103, 104, dv);
    EXPECT_NEAR(dv[0], xyz2100[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz2100[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz2100[2], EPSILONT);
    imCC2->euclideanDistanceVector(103, 109, dv);
    EXPECT_NEAR(dv[0], xyz2010[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz2010[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz2010[2], EPSILONT);
    imCC2->euclideanDistanceVector(73, 103, dv);
    EXPECT_NEAR(dv[0], xyz2001[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz2001[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz2001[2], EPSILONT);
    imCC2->euclideanDistanceVector(13, 116, dv);
    EXPECT_NEAR(dv[0], xyz2123[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz2123[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz2123[2], EPSILONT);

    delete imCC;
    delete imCC2;

}