#ifndef IMAGECCTEST
#define IMAGECCTEST

#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "exception.h"
#include "label.h"
#include <cmath>
#include <vector>
#include "filehandling.h"

using namespace CImage;

/**
* Tests type CImagetypeCC aka CImageCC<uint8>.
*/
TEST(CImageCC, constructor) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = i;
    }

    // constructor
    CImageCC<double> *imCCempty = new CImageCC<double>();
    EXPECT_TRUE(imCCempty);
    EXPECT_EQ(imCCempty->getNRows(), 0);
    EXPECT_EQ(imCCempty->getNColumns(), 0);
    EXPECT_EQ(imCCempty->getNLayers(), 0);
    EXPECT_EQ(imCCempty->getNBands(), 0);
    EXPECT_NEAR(imCCempty->getScaleFactor(), 1, EPSILONT);

    CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);
    EXPECT_TRUE(imCC);

    // getters
    uint8 *imdata = imCC->getData();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < nB; j++) {
            EXPECT_EQ(imdata[i], data[i]);
        }
    }

    EXPECT_EQ(imCC->getNElements(), N);
    EXPECT_NE(imCC->getNElements(), N + 1);

    EXPECT_EQ(imCC->getNColumns(), nC);
    EXPECT_NE(imCC->getNColumns(), nC + 1);

    EXPECT_EQ(imCC->getNRows(), nR);
    EXPECT_NE(imCC->getNRows(), nR + 1);

    EXPECT_EQ(imCC->getNLayers(), nL);
    EXPECT_NE(imCC->getNLayers(), nL + 1);

    EXPECT_EQ(imCC->getNBands(), nB);
    EXPECT_NE(imCC->getNBands(), nB + 1);

    // validity of elements
    EXPECT_FALSE(imCC->isValid(-1));
    EXPECT_TRUE(imCC->isValid(0));
    EXPECT_TRUE(imCC->isValid(N - 1));
    EXPECT_FALSE(imCC->isValid(N));

    EXPECT_FALSE(imCC->isValid(0, -1));
    EXPECT_FALSE(imCC->isValid(N - 1, -1));
    EXPECT_FALSE(imCC->isValid(-1, 0));
    EXPECT_TRUE(imCC->isValid(0, 0));
    EXPECT_TRUE(imCC->isValid(N - 1, 0));
    EXPECT_FALSE(imCC->isValid(N, 0));
    EXPECT_TRUE(imCC->isValid(0, nB - 1));
    EXPECT_TRUE(imCC->isValid(N - 1, nB - 1));
    EXPECT_FALSE(imCC->isValid(0, nB));
    EXPECT_FALSE(imCC->isValid(N - 1, nB));

    EXPECT_FALSE(imCC->isValid(-1, 0, 0));
    EXPECT_FALSE(imCC->isValid(0, -1, 0));
    EXPECT_FALSE(imCC->isValid(0, 0, -1));
    EXPECT_TRUE(imCC->isValid(0, 0, 0));
    EXPECT_TRUE(imCC->isValid(nR - 1, 0, 0));
    EXPECT_TRUE(imCC->isValid(0, nC - 1, 0));
    EXPECT_TRUE(imCC->isValid(0, 0, nL - 1));
    EXPECT_FALSE(imCC->isValid(nR, 0, 0));
    EXPECT_FALSE(imCC->isValid(0, nC, 0));
    EXPECT_FALSE(imCC->isValid(0, 0, nL));

    EXPECT_FALSE(imCC->isValid(0, 0, 0, -1));
    EXPECT_FALSE(imCC->isValid(nR - 1, 0, 0, -1));
    EXPECT_FALSE(imCC->isValid(0, nC - 1, 0, -1));
    EXPECT_FALSE(imCC->isValid(0, 0, nL - 1, -1));
    EXPECT_FALSE(imCC->isValid(0, 0, 0, nB));
    EXPECT_FALSE(imCC->isValid(nR - 1, 0, 0, nB));
    EXPECT_FALSE(imCC->isValid(0, nC - 1, 0, nB));
    EXPECT_FALSE(imCC->isValid(0, 0, nL - 1, nB));
    EXPECT_TRUE(imCC->isValid(0, 0, 0, nB - 1));
    EXPECT_TRUE(imCC->isValid(nR - 1, 0, 0, nB - 1));
    EXPECT_TRUE(imCC->isValid(0, nC - 1, 0, nB - 1));
    EXPECT_TRUE(imCC->isValid(0, 0, nL - 1, nB - 1));

    // index conversion
    EXPECT_EQ(imCC->rclToIndex(0, 0, 0), 0);
    EXPECT_EQ(imCC->rclToIndex(1, 2, 3), 98);
    EXPECT_EQ(imCC->rclToIndex(nR - 1, nC - 1, nL - 1), N - 1);

    EXPECT_EQ(imCC->indexToR(0), 0);
    EXPECT_EQ(imCC->indexToC(0), 0);
    EXPECT_EQ(imCC->indexToL(0), 0);
    EXPECT_EQ(imCC->indexToR(98), 1);
    EXPECT_EQ(imCC->indexToC(98), 2);
    EXPECT_EQ(imCC->indexToL(98), 3);
    EXPECT_EQ(imCC->indexToR(N - 1), nR - 1);
    EXPECT_EQ(imCC->indexToC(N - 1), nC - 1);
    EXPECT_EQ(imCC->indexToL(N - 1), nL - 1);

    delete imCC;
}

TEST(CImageCC, coordinates) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = 0;
    }
    CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);
    double volume = 2.5;
    double factor = cbrt(volume);
    CImagetypeCC *imCC2 = new CImagetypeCC(data, nR, nC, nL, nB, volume);

    CImagetypeCC *imCC1C1L = new CImagetypeCC(data, N, 1, 1, 1);
    CImagetypeCC *imCC1R1L = new CImagetypeCC(data, 1, N, 1, 1);
    CImagetypeCC *imCC1R1C = new CImagetypeCC(data, 1, 1, N, 1);
    int n1 = 15, n2 = 14;
    CImagetypeCC *imCCRC = new CImagetypeCC(data, n1, n2, 1, 1);
    CImagetypeCC *imCCRL = new CImagetypeCC(data, n1, 1, n2, 1);
    CImagetypeCC *imCCCL = new CImagetypeCC(data, 1, n1, n2, 1);
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
    CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);
    double volume = 2.5;
    double factor = cbrt(volume);
    CImagetypeCC *imCC2 = new CImagetypeCC(data, nR, nC, nL, nB, volume);

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
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(fabs(dv[i]) < EPSILONT);
    }
    imCC->euclideanDistanceVector(103, 104, dv);
    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(dv[i], xyz100[i], EPSILONT);
    }
    imCC->euclideanDistanceVector(103, 109, dv);
    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(dv[i], xyz010[i], EPSILONT);
    }
    imCC->euclideanDistanceVector(73, 103, dv);
    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(dv[i], xyz001[i], EPSILONT);
    }
    imCC->euclideanDistanceVector(13, 116, dv);
    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(dv[i], xyz123[i], EPSILONT);
    }

    double xyz2100[3] = {1 * factor, 0, 0};
    double xyz2010[3] = {0, 1 * factor, 0};
    double xyz2001[3] = {0, 0, 1 * factor};
    double xyz2123[3] = {1 * factor, 2 * factor, 3 * factor};
    imCC2->euclideanDistanceVector(103, 103, dv);
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(fabs(dv[i]) < EPSILONT);
    }
    imCC2->euclideanDistanceVector(103, 104, dv);
    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(dv[i], xyz2100[i], EPSILONT);
    }
    imCC2->euclideanDistanceVector(103, 109, dv);
    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(dv[i], xyz2010[i], EPSILONT);
    }
    imCC2->euclideanDistanceVector(73, 103, dv);
    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(dv[i], xyz2001[i], EPSILONT);
    }
    imCC2->euclideanDistanceVector(13, 116, dv);
    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(dv[i], xyz2123[i], EPSILONT);
    }

    delete imCC;
    delete imCC2;

}

TEST(CImageCC, neighbors) {
    /**
    * Tests getNeighbor(r,c,l,N) and getNeighbor(i,N). Since these
    * always call getXNeighbors(r,c,l), those methods should work
    * properly if the tests pass.
    */

    // image parameters
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N];
    for (int i = 0; i < N * nB; i++) {
        data[i] = 0;
    }
    CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);

    vector<Neighbor> neighbors;
    int nNeighbors, returnedNeighbors, correctNNeighbors;
    // neighbor indices
    //{r,l,bo,t,f,ba,   bor,tr,bar,fr,bol,tl,bal,fl,boba,bof,tba,tf,   bofr,tfr,tbar,bobar,bofl,tfl,tbal,bobal}
    int CC6[6] = {171, 169, 176, 164, 140, 200};    // {63,61,67,57,37,87};
    int CC18[18] = {171, 169, 176, 164, 140, 200, 177, 165, 201, 141, 175, 163, 199, 139, 206, 146, 194, 134};    // {63,61,67,57,37,87,68,58,88,38,66,56,86,36,92,42,82,32};
    int CC26[26] = {171, 169, 176, 164, 140, 200, 177, 165, 201, 141, 175, 163, 199, 139, 206, 146, 194, 134, 147, 135, 195, 207, 145, 133, 193, 205};// {63,61,67,57,37,87,68,58,88,38,66,56,86,36,92,42,82,32,43,33,83,93,41,31,81,91};

    // 6 neighbors
    nNeighbors = 6;
    correctNNeighbors = 6;
    imCC->getNeighbors(3, 2, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    for (int i = 0; i < returnedNeighbors; i++) {
        EXPECT_EQ(neighbors[i].getIndex(), CC6[i]);
    }
    imCC->getNeighbors(imCC->rclToIndex(3, 2, 5), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    for (int i = 0; i < returnedNeighbors; i++) {
        EXPECT_EQ(neighbors[i].getIndex(), CC6[i]);
    }

    correctNNeighbors = 3;
    imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 4;
    imCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 5;
    imCC->getNeighbors(0, 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 2, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 1, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 2, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    // 18 neighbors
    nNeighbors = 18;
    correctNNeighbors = 18;
    imCC->getNeighbors(3, 2, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    for (int i = 0; i < returnedNeighbors; i++) {
        EXPECT_EQ(neighbors[i].getIndex(), CC18[i]);
    }
    imCC->getNeighbors(imCC->rclToIndex(3, 2, 5), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    for (int i = 0; i < returnedNeighbors; i++) {
        EXPECT_EQ(neighbors[i].getIndex(), CC18[i]);
    }

    correctNNeighbors = 6;
    imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 9;
    imCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 13;
    imCC->getNeighbors(0, 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 2, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 1, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 2, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    // 26 neighbors
    nNeighbors = 26;
    correctNNeighbors = 26;
    imCC->getNeighbors(3, 2, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    for (int i = 0; i < returnedNeighbors; i++) {
        EXPECT_EQ(neighbors[i].getIndex(), CC26[i]);
    }
    imCC->getNeighbors(imCC->rclToIndex(3, 2, 5), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    for (int i = 0; i < returnedNeighbors; i++) {
        EXPECT_EQ(neighbors[i].getIndex(), CC26[i]);
    }
    correctNNeighbors = 7;
    imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 11;
    imCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 17;
    imCC->getNeighbors(0, 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 2, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 1, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 2, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    // Exceptions
    nNeighbors = 6;
    EXPECT_THROW(imCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 18;
    EXPECT_THROW(imCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 26;
    EXPECT_THROW(imCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 8;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 12;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 14;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    // nNeighbors = 18 is valid for both CC and FCC.
    nNeighbors = -6;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 0;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 100;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);

    delete imCC;

}

TEST(CImageCC, operators) {

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

    int index;
    double returnedVal;
    vector<double> returnedElem;

    // []-operator
    index = 0;
    returnedElem = (*imCC)[index];
    EXPECT_EQ(returnedElem.size(), nB);
    for (int i = 0; i < nB; i++) {
        EXPECT_NEAR(returnedElem[i], 10 * i + 1, EPSILONT);
    }
    index = 14;
    returnedElem = (*imCC)[index];
    EXPECT_EQ(returnedElem.size(), nB);
    for (int i = 0; i < nB; i++) {
        EXPECT_NEAR(returnedElem[i], 10 * i + 5, EPSILONT);
    }
    index = 10;
    returnedElem = (*imCC)[index];
    EXPECT_EQ(returnedElem.size(), nB);
    for (int i = 0; i < nB; i++) {
        EXPECT_NEAR(returnedElem[i], 10 * i + 6, EPSILONT);
    }
    index = N - 1;
    returnedElem = (*imCC)[index];
    EXPECT_EQ(returnedElem.size(), nB);
    for (int i = 0; i < nB; i++) {
        EXPECT_NEAR(returnedElem[i], 10 * i + 3, EPSILONT);
    }

    // ()-operator
    returnedVal = (*imCC)(0, 0, 0, 0);
    EXPECT_NEAR(returnedVal, 1, EPSILONT);
    returnedVal = (*imCC)(0, 1, 2, 3);
    EXPECT_NEAR(returnedVal, 34, EPSILONT);
    returnedVal = (*imCC)(nR - 1, nC - 1, nL - 1, nB - 1);
    EXPECT_NEAR(returnedVal, 43, EPSILONT);

    /*
	returnedVal = (*imCC)(imCC->rclToIndex(0, 0, 0), 0);
	EXPECT_NEAR(returnedVal, 1, EPSILONT);
	returnedVal = (*imCC)(imCC->rclToIndex(0, 1, 2), 3);
	EXPECT_NEAR(returnedVal, 34, EPSILONT);
	returnedVal = (*imCC)(imCC->rclToIndex(nR - 1, nC - 1, nL - 1), nB - 1);
	EXPECT_NEAR(returnedVal, 43, EPSILONT);
    */

    // Exceptions
    EXPECT_THROW((*imCC)[-1], outsideImageException);
    EXPECT_THROW((*imCC)[N], outsideImageException);

    EXPECT_THROW((*imCC)(-1, 0, 0, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, -1, 0, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, 0, -1, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, 0, 0, -1), outsideImageException);
    EXPECT_THROW((*imCC)(nR, 0, 0, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, nC, 0, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, 0, nL, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, 0, 0, nB), outsideImageException);

    delete imCC;
}

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

    for (int index = 0; index > N; index++) {
        originalIntensity = (*imCC)[index];
        imCC->setElement(index, intensities0);
        for (int i = 0; i < nB; i++) {
            EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), i), 0, EPSILONT);
        }
        imCC->setElement(index, intensitiesRight);
        for (int i = 0; i < nB; i++) {
            EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), i), intensitiesRight[i], EPSILONT);
        }
        imCC->setElement(index, originalIntensity);
        for (int i = 0; i < nB; i++) {
            EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), i), originalIntensity[i], EPSILONT);
        }
    }

    double *newData = imCC->getData();
    for (int i = 0; i < N * nB; i++) {
        EXPECT_NEAR(data[i], newData[i], EPSILONT);
    }

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
	CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);

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

TEST(CImageCC, segmentations) {

}

TEST(CImageCC, distanceTransforms) {

    // sub-spel precision term
/*
	int nR = 4, nC = 6, nL = 5;
	int N = nR * nC * nL;
	double dataD[] = 	{0,0,0,0,0,0,
						0,0,0,0,0,0,
						0,0,0,0,0,0,
						0,0,0,0,0,0,

						0,0.5,0.5,0.5,0.5,0,
						0,0.5,0.7,0.7,0.5,0,
						0,0.5,0.7,0.7,0.5,0,
						0,0.5,0.5,0.5,0.5,0,

						0,0.2,0.2,0.2,0.2,0,
						0,0.3,1,  1,  0.1,0,
						0,0.3,1,  1,  0.1,0,
						0,0.3,0.3,0.3,0.3,0,

						0,0.1,0.1,0.1, 0.1,0,
						0,0.2,  1,  1,0.01,0,
						0,0.2,  1,  1,0.01,0,
						0,0.4,0.4,0.2, 0.1,0,

						0,0,0,0,0,0,
						0,0,0,0,0,0,
						0,0,0,0,0,0,
						0,0,0,0,0,0};
	uint8 dataU[N];
	for(int i = 0; i < N; i++) {
		dataU[i] = round(dataD[i] * 255);
	}

	CImageCC<double> *imCCD = new CImageCC<double>(dataD,nR,nC,nL,1);
	CImageCC<uint8> *imCCU = new CImageCC<uint8>(dataU,nR,nC,nL,1);

	EXPECT_NEAR(imCCD->internalDistanceLinear(0.0),0.5, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(0.5),0.0, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(1.0),-0.5, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(uint8(0)),0.5, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(uint8(127)),0.00196078431, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(uint8(255)),-0.5, EPSILONT);
	EXPECT_THROW(imCCD->internalDistanceLinear(-0.1),outsideRangeException);
	EXPECT_THROW(imCCD->internalDistanceLinear(1.1),outsideRangeException);

	EXPECT_NEAR(imCCD->internalDistanceBall(uint8(0)),0.620350490899400, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(uint8(15)),0.344897652005037, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(uint8(255)),-0.620350490899443, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(0.0),0.620350490899400, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(0.51),imCCD->internalDistanceBall(uint8(128)), EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(1.0),-0.620350490899443, EPSILONT);
	EXPECT_THROW(imCCD->internalDistanceBall(-0.1),outsideRangeException);
	EXPECT_THROW(imCCD->internalDistanceBall(1.1),outsideRangeException);

	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(uint8(0)),0.732561001953818, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(uint8(15)),0.361626850445366, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(uint8(255)),-0.729122335558677, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(0.0),0.732561001953818, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(0.51),imCCD->internalDistanceVoronoiAverage(uint8(128)), EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(1.0),-0.729122335558677, EPSILONT);
	EXPECT_THROW(imCCD->internalDistanceVoronoiAverage(-0.1),outsideRangeException);
	EXPECT_THROW(imCCD->internalDistanceVoronoiAverage(1.1),outsideRangeException);

	EXPECT_THROW(imCCD->approximatedInternalDistance(-1,0,1),outsideImageException);
	EXPECT_THROW(imCCU->approximatedInternalDistance(-1,0,1),outsideImageException);
	EXPECT_THROW(imCCD->approximatedInternalDistance(N,0,1),outsideImageException);
	EXPECT_THROW(imCCU->approximatedInternalDistance(N,0,1),outsideImageException);
	EXPECT_THROW(imCCD->approximatedInternalDistance(1,0,-1),outsideRangeException);
	EXPECT_THROW(imCCU->approximatedInternalDistance(1,0,-1),outsideRangeException);
	EXPECT_THROW(imCCD->approximatedInternalDistance(1,0,3),outsideRangeException);
	EXPECT_THROW(imCCU->approximatedInternalDistance(1,0,3),outsideRangeException);*/

}

TEST(CImageCC, downsample) {

    //cout << "Inside TEST(CImageCC, downsample)" << endl;

    int nRHighRes = 120, nCHighRes = 10, nLHighRes = 10, nBHighRes = 2;
    int nRLowRes = 24, nCLowRes = 2, nLLowRes = 2, nBLowRes = 2;
    int nTotHighRes = nRHighRes * nCHighRes * nLHighRes;
    int nTotLowRes = nRLowRes * nCLowRes * nLHighRes;
//    char filename[] = "y10x10.bin";
    char highResFileName[] = "doubleband.bin";
    char lowResFileName[] = "doubleband125.bin";
//    char *filenamepointer = filename;
    char *highResFilePointer = highResFileName;
    char *lowResFilePointer = lowResFileName;
    double *dataHighRes = readVolume(highResFilePointer, nTotHighRes * nBHighRes);
    double *dataLowRes = readVolume(lowResFilePointer, nTotLowRes * nBLowRes);
    CImageCC<double> *imCCHighRes = new CImageCC<double>(dataHighRes, nRHighRes, nCHighRes, nLHighRes, nBHighRes, 1);

//    double groundTruth1000[12] = {1, 0.99, 0.89, 0.79, 0.69, 0.59, 0.49, 0.39, 0.29, 0.19, 0.09, 0};
//    double groundTruth125[96] = {125, 125, 125, 125, 125, 125, 120, 125, 100, 125, 95, 125, 75, 125, 70, 125, 50, 125, 45, 125, 25, 125, 20, 125, 0, 125, 0, 120, 0, 100, 0, 95, 0, 75, 0, 70, 0, 50, 0, 45, 0, 25, 0, 20, 0, 0, 0, 0, 125, 125, 125, 125, 125, 125, 120, 125, 100, 125, 95, 125, 75, 125, 70, 125, 50, 125, 45, 125, 25, 125, 20, 125, 0, 125, 0, 120, 0, 100, 0, 95, 0, 75, 0, 70, 0, 50, 0, 45, 0, 25, 0, 20, 0, 0, 0, 0};
//    for (int i = 0; i < 96; i++) {
//        groundTruth125[i] = groundTruth125[i] / 125.0;
//    }

    CImageCC<double> *imCCLowRes125 = new CImageCC<double>();
//    CImageCC<double> *imCCLowRes1000 = new CImageCC<double>();
    double *downsampledData = NULL; // *dataLowRes1000 = NULL;

    //cout << "pointer to downsampledData: " << downsampledData << endl;
    //cout << "pointer to dataLowRes1000: " << dataLowRes1000 << endl;

    downsampledData = imCCLowRes125->downsample(imCCHighRes, 125);
//    dataLowRes1000 = imCCLowRes1000->downsample(imCCHighRes, 1000);

    //cout << "pointer to downsampledData: " << downsampledData << endl;
    //cout << "pointer to dataLowRes1000: " << dataLowRes1000 << endl;

    EXPECT_TRUE(downsampledData);
    EXPECT_NEAR(dataLowRes[0], downsampledData[0], EPSILONT);
    EXPECT_NEAR(dataLowRes[1], downsampledData[1], EPSILONT);
    EXPECT_NEAR(dataLowRes[2], downsampledData[2], EPSILONT);
    EXPECT_NEAR(dataLowRes[3], downsampledData[3], EPSILONT);
    EXPECT_NEAR(dataLowRes[4], downsampledData[4], EPSILONT);
    EXPECT_NEAR(dataLowRes[5], downsampledData[5], EPSILONT);
    EXPECT_NEAR(dataLowRes[6], downsampledData[6], EPSILONT);
    EXPECT_NEAR(dataLowRes[7], downsampledData[7], EPSILONT);
    EXPECT_NEAR(dataLowRes[8], downsampledData[8], EPSILONT);
    EXPECT_NEAR(dataLowRes[9], downsampledData[9], EPSILONT);
    EXPECT_NEAR(dataLowRes[10], downsampledData[10], EPSILONT);
    EXPECT_NEAR(dataLowRes[11], downsampledData[11], EPSILONT);
    EXPECT_NEAR(dataLowRes[12], downsampledData[12], EPSILONT);
    EXPECT_NEAR(dataLowRes[13], downsampledData[13], EPSILONT);
    EXPECT_NEAR(dataLowRes[14], downsampledData[14], EPSILONT);
    EXPECT_NEAR(dataLowRes[15], downsampledData[15], EPSILONT);
    EXPECT_NEAR(dataLowRes[16], downsampledData[16], EPSILONT);
    EXPECT_NEAR(dataLowRes[17], downsampledData[17], EPSILONT);
    EXPECT_NEAR(dataLowRes[18], downsampledData[18], EPSILONT);
    EXPECT_NEAR(dataLowRes[19], downsampledData[19], EPSILONT);
    EXPECT_NEAR(dataLowRes[20], downsampledData[20], EPSILONT);
    EXPECT_NEAR(dataLowRes[21], downsampledData[21], EPSILONT);
    EXPECT_NEAR(dataLowRes[22], downsampledData[22], EPSILONT);
    EXPECT_NEAR(dataLowRes[23], downsampledData[23], EPSILONT);
    EXPECT_NEAR(dataLowRes[24], downsampledData[24], EPSILONT);
    EXPECT_NEAR(dataLowRes[25], downsampledData[25], EPSILONT);
    EXPECT_NEAR(dataLowRes[26], downsampledData[26], EPSILONT);
    EXPECT_NEAR(dataLowRes[27], downsampledData[27], EPSILONT);
    EXPECT_NEAR(dataLowRes[28], downsampledData[28], EPSILONT);
    EXPECT_NEAR(dataLowRes[29], downsampledData[29], EPSILONT);
    EXPECT_NEAR(dataLowRes[30], downsampledData[30], EPSILONT);
    EXPECT_NEAR(dataLowRes[31], downsampledData[31], EPSILONT);
    EXPECT_NEAR(dataLowRes[32], downsampledData[32], EPSILONT);
    EXPECT_NEAR(dataLowRes[33], downsampledData[33], EPSILONT);
    EXPECT_NEAR(dataLowRes[34], downsampledData[34], EPSILONT);
    EXPECT_NEAR(dataLowRes[35], downsampledData[35], EPSILONT);
    EXPECT_NEAR(dataLowRes[36], downsampledData[36], EPSILONT);
    EXPECT_NEAR(dataLowRes[37], downsampledData[37], EPSILONT);
    EXPECT_NEAR(dataLowRes[38], downsampledData[38], EPSILONT);
    EXPECT_NEAR(dataLowRes[39], downsampledData[39], EPSILONT);
    EXPECT_NEAR(dataLowRes[40], downsampledData[40], EPSILONT);
    EXPECT_NEAR(dataLowRes[41], downsampledData[41], EPSILONT);
    EXPECT_NEAR(dataLowRes[42], downsampledData[42], EPSILONT);
    EXPECT_NEAR(dataLowRes[43], downsampledData[43], EPSILONT);
    EXPECT_NEAR(dataLowRes[44], downsampledData[44], EPSILONT);
    EXPECT_NEAR(dataLowRes[45], downsampledData[45], EPSILONT);
    EXPECT_NEAR(dataLowRes[46], downsampledData[46], EPSILONT);
    EXPECT_NEAR(dataLowRes[47], downsampledData[47], EPSILONT);
    EXPECT_NEAR(dataLowRes[48], downsampledData[48], EPSILONT);
    EXPECT_NEAR(dataLowRes[49], downsampledData[49], EPSILONT);
    EXPECT_NEAR(dataLowRes[50], downsampledData[50], EPSILONT);
    EXPECT_NEAR(dataLowRes[51], downsampledData[51], EPSILONT);
    EXPECT_NEAR(dataLowRes[52], downsampledData[52], EPSILONT);
    EXPECT_NEAR(dataLowRes[53], downsampledData[53], EPSILONT);
    EXPECT_NEAR(dataLowRes[54], downsampledData[54], EPSILONT);
    EXPECT_NEAR(dataLowRes[55], downsampledData[55], EPSILONT);
    EXPECT_NEAR(dataLowRes[56], downsampledData[56], EPSILONT);
    EXPECT_NEAR(dataLowRes[57], downsampledData[57], EPSILONT);
    EXPECT_NEAR(dataLowRes[58], downsampledData[58], EPSILONT);
    EXPECT_NEAR(dataLowRes[59], downsampledData[59], EPSILONT);
    EXPECT_NEAR(dataLowRes[60], downsampledData[60], EPSILONT);
    EXPECT_NEAR(dataLowRes[61], downsampledData[61], EPSILONT);
    EXPECT_NEAR(dataLowRes[62], downsampledData[62], EPSILONT);
    EXPECT_NEAR(dataLowRes[63], downsampledData[63], EPSILONT);
    EXPECT_NEAR(dataLowRes[64], downsampledData[64], EPSILONT);
    EXPECT_NEAR(dataLowRes[65], downsampledData[65], EPSILONT);
    EXPECT_NEAR(dataLowRes[66], downsampledData[66], EPSILONT);
    EXPECT_NEAR(dataLowRes[67], downsampledData[67], EPSILONT);
    EXPECT_NEAR(dataLowRes[68], downsampledData[68], EPSILONT);
    EXPECT_NEAR(dataLowRes[69], downsampledData[69], EPSILONT);
    EXPECT_NEAR(dataLowRes[70], downsampledData[70], EPSILONT);
    EXPECT_NEAR(dataLowRes[71], downsampledData[71], EPSILONT);
    EXPECT_NEAR(dataLowRes[72], downsampledData[72], EPSILONT);
    EXPECT_NEAR(dataLowRes[73], downsampledData[73], EPSILONT);
    EXPECT_NEAR(dataLowRes[74], downsampledData[74], EPSILONT);
    EXPECT_NEAR(dataLowRes[75], downsampledData[75], EPSILONT);
    EXPECT_NEAR(dataLowRes[76], downsampledData[76], EPSILONT);
    EXPECT_NEAR(dataLowRes[77], downsampledData[77], EPSILONT);
    EXPECT_NEAR(dataLowRes[78], downsampledData[78], EPSILONT);
    EXPECT_NEAR(dataLowRes[79], downsampledData[79], EPSILONT);
    EXPECT_NEAR(dataLowRes[80], downsampledData[80], EPSILONT);
    EXPECT_NEAR(dataLowRes[81], downsampledData[81], EPSILONT);
    EXPECT_NEAR(dataLowRes[82], downsampledData[82], EPSILONT);
    EXPECT_NEAR(dataLowRes[83], downsampledData[83], EPSILONT);
    EXPECT_NEAR(dataLowRes[84], downsampledData[84], EPSILONT);
    EXPECT_NEAR(dataLowRes[85], downsampledData[85], EPSILONT);
    EXPECT_NEAR(dataLowRes[86], downsampledData[86], EPSILONT);
    EXPECT_NEAR(dataLowRes[87], downsampledData[87], EPSILONT);
    EXPECT_NEAR(dataLowRes[88], downsampledData[88], EPSILONT);
    EXPECT_NEAR(dataLowRes[89], downsampledData[89], EPSILONT);
    EXPECT_NEAR(dataLowRes[90], downsampledData[90], EPSILONT);
    EXPECT_NEAR(dataLowRes[91], downsampledData[91], EPSILONT);
    EXPECT_NEAR(dataLowRes[92], downsampledData[92], EPSILONT);
    EXPECT_NEAR(dataLowRes[93], downsampledData[93], EPSILONT);
    EXPECT_NEAR(dataLowRes[94], downsampledData[94], EPSILONT);
    EXPECT_NEAR(dataLowRes[95], downsampledData[95], EPSILONT);

    EXPECT_NEAR(dataLowRes[96], downsampledData[96], EPSILONT);
    EXPECT_NEAR(dataLowRes[97], downsampledData[97], EPSILONT);
    EXPECT_NEAR(dataLowRes[98], downsampledData[98], EPSILONT);
    EXPECT_NEAR(dataLowRes[99], downsampledData[99], EPSILONT);
    EXPECT_NEAR(dataLowRes[100], downsampledData[100], EPSILONT);
    EXPECT_NEAR(dataLowRes[101], downsampledData[101], EPSILONT);
    EXPECT_NEAR(dataLowRes[102], downsampledData[102], EPSILONT);
    EXPECT_NEAR(dataLowRes[103], downsampledData[103], EPSILONT);
    EXPECT_NEAR(dataLowRes[104], downsampledData[104], EPSILONT);
    EXPECT_NEAR(dataLowRes[105], downsampledData[105], EPSILONT);
    EXPECT_NEAR(dataLowRes[106], downsampledData[106], EPSILONT);
    EXPECT_NEAR(dataLowRes[107], downsampledData[107], EPSILONT);
    EXPECT_NEAR(dataLowRes[108], downsampledData[108], EPSILONT);
    EXPECT_NEAR(dataLowRes[109], downsampledData[109], EPSILONT);
    EXPECT_NEAR(dataLowRes[110], downsampledData[110], EPSILONT);
    EXPECT_NEAR(dataLowRes[111], downsampledData[111], EPSILONT);
    EXPECT_NEAR(dataLowRes[112], downsampledData[112], EPSILONT);
    EXPECT_NEAR(dataLowRes[113], downsampledData[113], EPSILONT);
    EXPECT_NEAR(dataLowRes[114], downsampledData[114], EPSILONT);
    EXPECT_NEAR(dataLowRes[115], downsampledData[115], EPSILONT);
    EXPECT_NEAR(dataLowRes[116], downsampledData[116], EPSILONT);
    EXPECT_NEAR(dataLowRes[117], downsampledData[117], EPSILONT);
    EXPECT_NEAR(dataLowRes[118], downsampledData[118], EPSILONT);
    EXPECT_NEAR(dataLowRes[119], downsampledData[119], EPSILONT);
    EXPECT_NEAR(dataLowRes[120], downsampledData[120], EPSILONT);
    EXPECT_NEAR(dataLowRes[121], downsampledData[121], EPSILONT);
    EXPECT_NEAR(dataLowRes[122], downsampledData[122], EPSILONT);
    EXPECT_NEAR(dataLowRes[123], downsampledData[123], EPSILONT);
    EXPECT_NEAR(dataLowRes[124], downsampledData[124], EPSILONT);
    EXPECT_NEAR(dataLowRes[125], downsampledData[125], EPSILONT);
    EXPECT_NEAR(dataLowRes[126], downsampledData[126], EPSILONT);
    EXPECT_NEAR(dataLowRes[127], downsampledData[127], EPSILONT);
    EXPECT_NEAR(dataLowRes[128], downsampledData[128], EPSILONT);
    EXPECT_NEAR(dataLowRes[129], downsampledData[129], EPSILONT);
    EXPECT_NEAR(dataLowRes[130], downsampledData[130], EPSILONT);
    EXPECT_NEAR(dataLowRes[131], downsampledData[131], EPSILONT);
    EXPECT_NEAR(dataLowRes[132], downsampledData[132], EPSILONT);
    EXPECT_NEAR(dataLowRes[133], downsampledData[133], EPSILONT);
    EXPECT_NEAR(dataLowRes[134], downsampledData[134], EPSILONT);
    EXPECT_NEAR(dataLowRes[135], downsampledData[135], EPSILONT);
    EXPECT_NEAR(dataLowRes[136], downsampledData[136], EPSILONT);
    EXPECT_NEAR(dataLowRes[137], downsampledData[137], EPSILONT);
    EXPECT_NEAR(dataLowRes[138], downsampledData[138], EPSILONT);
    EXPECT_NEAR(dataLowRes[139], downsampledData[139], EPSILONT);
    EXPECT_NEAR(dataLowRes[140], downsampledData[140], EPSILONT);
    EXPECT_NEAR(dataLowRes[141], downsampledData[141], EPSILONT);
    EXPECT_NEAR(dataLowRes[142], downsampledData[142], EPSILONT);
    EXPECT_NEAR(dataLowRes[143], downsampledData[143], EPSILONT);
    EXPECT_NEAR(dataLowRes[144], downsampledData[144], EPSILONT);
    EXPECT_NEAR(dataLowRes[145], downsampledData[145], EPSILONT);
    EXPECT_NEAR(dataLowRes[146], downsampledData[146], EPSILONT);
    EXPECT_NEAR(dataLowRes[147], downsampledData[147], EPSILONT);
    EXPECT_NEAR(dataLowRes[148], downsampledData[148], EPSILONT);
    EXPECT_NEAR(dataLowRes[149], downsampledData[149], EPSILONT);
    EXPECT_NEAR(dataLowRes[150], downsampledData[150], EPSILONT);
    EXPECT_NEAR(dataLowRes[151], downsampledData[151], EPSILONT);
    EXPECT_NEAR(dataLowRes[152], downsampledData[152], EPSILONT);
    EXPECT_NEAR(dataLowRes[153], downsampledData[153], EPSILONT);
    EXPECT_NEAR(dataLowRes[154], downsampledData[154], EPSILONT);
    EXPECT_NEAR(dataLowRes[155], downsampledData[155], EPSILONT);
    EXPECT_NEAR(dataLowRes[156], downsampledData[156], EPSILONT);
    EXPECT_NEAR(dataLowRes[157], downsampledData[157], EPSILONT);
    EXPECT_NEAR(dataLowRes[158], downsampledData[158], EPSILONT);
    EXPECT_NEAR(dataLowRes[159], downsampledData[159], EPSILONT);
    EXPECT_NEAR(dataLowRes[160], downsampledData[160], EPSILONT);
    EXPECT_NEAR(dataLowRes[161], downsampledData[161], EPSILONT);
    EXPECT_NEAR(dataLowRes[162], downsampledData[162], EPSILONT);
    EXPECT_NEAR(dataLowRes[163], downsampledData[163], EPSILONT);
    EXPECT_NEAR(dataLowRes[164], downsampledData[164], EPSILONT);
    EXPECT_NEAR(dataLowRes[165], downsampledData[165], EPSILONT);
    EXPECT_NEAR(dataLowRes[166], downsampledData[166], EPSILONT);
    EXPECT_NEAR(dataLowRes[167], downsampledData[167], EPSILONT);
    EXPECT_NEAR(dataLowRes[168], downsampledData[168], EPSILONT);
    EXPECT_NEAR(dataLowRes[169], downsampledData[169], EPSILONT);
    EXPECT_NEAR(dataLowRes[170], downsampledData[170], EPSILONT);
    EXPECT_NEAR(dataLowRes[171], downsampledData[171], EPSILONT);
    EXPECT_NEAR(dataLowRes[172], downsampledData[172], EPSILONT);
    EXPECT_NEAR(dataLowRes[173], downsampledData[173], EPSILONT);
    EXPECT_NEAR(dataLowRes[174], downsampledData[174], EPSILONT);
    EXPECT_NEAR(dataLowRes[175], downsampledData[175], EPSILONT);
    EXPECT_NEAR(dataLowRes[176], downsampledData[176], EPSILONT);
    EXPECT_NEAR(dataLowRes[177], downsampledData[177], EPSILONT);
    EXPECT_NEAR(dataLowRes[178], downsampledData[178], EPSILONT);
    EXPECT_NEAR(dataLowRes[179], downsampledData[179], EPSILONT);
    EXPECT_NEAR(dataLowRes[180], downsampledData[180], EPSILONT);
    EXPECT_NEAR(dataLowRes[181], downsampledData[181], EPSILONT);
    EXPECT_NEAR(dataLowRes[182], downsampledData[182], EPSILONT);
    EXPECT_NEAR(dataLowRes[183], downsampledData[183], EPSILONT);
    EXPECT_NEAR(dataLowRes[184], downsampledData[184], EPSILONT);
    EXPECT_NEAR(dataLowRes[185], downsampledData[185], EPSILONT);
    EXPECT_NEAR(dataLowRes[186], downsampledData[186], EPSILONT);
    EXPECT_NEAR(dataLowRes[187], downsampledData[187], EPSILONT);
    EXPECT_NEAR(dataLowRes[188], downsampledData[188], EPSILONT);
    EXPECT_NEAR(dataLowRes[189], downsampledData[189], EPSILONT);
    EXPECT_NEAR(dataLowRes[190], downsampledData[190], EPSILONT);
    EXPECT_NEAR(dataLowRes[191], downsampledData[191], EPSILONT);

    delete imCCHighRes;
    delete imCCLowRes125;
    delete[] dataLowRes;
    delete[] dataHighRes;
    delete[] downsampledData;

}

#endif