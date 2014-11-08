#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageBCC.h"
#include "exception.h"
#include <cmath>
#include <vector>

using namespace CImage;

TEST(CImageBCC, coordinates) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = 0;
    }
    CImageBCC<uint8> *imBCC = new CImageBCC<uint8>(data, nR, nC, nL, nB);
    double volume = 2.5;
    CImageBCC<uint8> *imBCC2 = new CImageBCC<uint8>(data, nR, nC, nL, nB, volume);
    double factor = cbrt(volume);

    CImageBCC<uint8> *imBCC1C1L = new CImageBCC<uint8>(data, N, 1, 1, 1);
    CImageBCC<uint8> *imBCC1R1L = new CImageBCC<uint8>(data, 1, N, 1, 1);
    CImageBCC<uint8> *imBCC1R1C = new CImageBCC<uint8>(data, 1, 1, N, 1);
    int n1 = 15, n2 = 14;
    CImageBCC<uint8> *imBCCRC = new CImageBCC<uint8>(data, n1, n2, 1, 1);
    CImageBCC<uint8> *imBCCRL = new CImageBCC<uint8>(data, n1, 1, n2, 1);
    CImageBCC<uint8> *imBCCCL = new CImageBCC<uint8>(data, 1, n1, n2, 1);
    vector<double> coordinates;

    // spel coordinates
    EXPECT_NEAR(imBCC->indexToX(0), BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCC->indexToY(0), BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCC->indexToZ(0), BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCC->indexToX(82), BCCOFFSET + 4 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->indexToY(82), BCCOFFSET + 3 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->indexToZ(82), BCCOFFSET + BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->indexToX(112), BCCOFFSET + 9 * BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCC->indexToY(112), BCCOFFSET + 7 * BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCC->indexToZ(112), BCCOFFSET + 3 * BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCC->indexToX(209), BCCOFFSET + 5 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->indexToY(209), BCCOFFSET + 4 * BCCSQFACEDISTANCE, EPSILONT); // !!!!!!
    EXPECT_NEAR(imBCC->indexToZ(209), BCCOFFSET + 3 * BCCSQFACEDISTANCE, EPSILONT);

    imBCC->getCoordinates(0, coordinates);
    EXPECT_NEAR(coordinates[0], BCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[1], BCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[2], BCCOFFSET, EPSILONT);
    imBCC->getCoordinates(82, coordinates);
    EXPECT_NEAR(coordinates[0], BCCOFFSET + 4 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(coordinates[1], BCCOFFSET + 3 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(coordinates[2], BCCOFFSET + BCCSQFACEDISTANCE, EPSILONT);
    imBCC->getCoordinates(112, coordinates);
    EXPECT_NEAR(coordinates[0], BCCOFFSET + 9 * BCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[1], BCCOFFSET + 7 * BCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[2], BCCOFFSET + 3 * BCCOFFSET, EPSILONT);
    imBCC->getCoordinates(209, coordinates);
    EXPECT_NEAR(coordinates[0], BCCOFFSET + 5 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(coordinates[1], BCCOFFSET + 4 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(coordinates[2], BCCOFFSET + 3 * BCCSQFACEDISTANCE, EPSILONT);


    EXPECT_NEAR(imBCC2->indexToX(0), factor * (BCCOFFSET), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToY(0), factor * (BCCOFFSET), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToZ(0), factor * (BCCOFFSET), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToX(82), factor * (BCCOFFSET + 4 * BCCSQFACEDISTANCE), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToY(82), factor * (BCCOFFSET + 3 * BCCSQFACEDISTANCE), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToZ(82), factor * (BCCOFFSET + BCCSQFACEDISTANCE), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToX(112), factor * (BCCOFFSET + 9 * BCCOFFSET), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToY(112), factor * (BCCOFFSET + 7 * BCCOFFSET), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToZ(112), factor * (BCCOFFSET + 3 * BCCOFFSET), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToX(209), factor * (BCCOFFSET + 5 * BCCSQFACEDISTANCE), EPSILONT);
    EXPECT_NEAR(imBCC2->indexToY(209), factor * (BCCOFFSET + 4 * BCCSQFACEDISTANCE), EPSILONT); // !!!!!!
    EXPECT_NEAR(imBCC2->indexToZ(209), factor * (BCCOFFSET + 3 * BCCSQFACEDISTANCE), EPSILONT);

    // width, height and depth
    EXPECT_NEAR(imBCC->getWidth(), 6.5 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->getHeight(), 5.5 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->getDepth(), 4 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->getWidth(), factor * 6.5 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->getHeight(), factor * 5.5 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->getDepth(), factor * 4 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC1C1L->getWidth(), BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC1C1L->getHeight(), N * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC1C1L->getDepth(), BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC1R1L->getWidth(), N * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC1R1L->getHeight(), BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC1R1L->getDepth(), BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC1R1C->getWidth(), BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCC1R1C->getHeight(), BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCC1R1C->getDepth(), (N + 1) * BCCOFFSET, EPSILONT);

    EXPECT_NEAR(imBCCRC->getWidth(), n2 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCCRC->getHeight(), n1 * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCCRC->getDepth(), BCCSQFACEDISTANCE, EPSILONT);

    EXPECT_NEAR(imBCCRL->getWidth(), BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCCRL->getHeight(), n1 * BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCCRL->getDepth(), (n2 + 1) * BCCOFFSET, EPSILONT);

    EXPECT_NEAR(imBCCCL->getWidth(), n1 * BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCCCL->getHeight(), BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
    EXPECT_NEAR(imBCCCL->getDepth(), (n2 + 1) * BCCOFFSET, EPSILONT);

    delete imBCC;
    delete imBCC2;
    delete imBCC1C1L;
    delete imBCC1R1L;
    delete imBCC1R1C;
    delete imBCCCL;
    delete imBCCRL;
    delete imBCCRC;
}

TEST(CImageBCC, distances) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = 0;
    }
    CImageBCC<uint8> *imBCC = new CImageBCC<uint8>(data, nR, nC, nL, nB);
    double volume = 2.5;
    CImageBCC<uint8> *imBCC2 = new CImageBCC<uint8>(data, nR, nC, nL, nB, volume);
    double factor = cbrt(volume);

    // distance between spels
    EXPECT_NEAR(imBCC->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 45), BCCHEXFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 45), imBCC->euclideanDistance(45, 82), EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 46), BCCHEXFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 46), imBCC->euclideanDistance(46, 82), EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 51), BCCHEXFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 51), imBCC->euclideanDistance(51, 82), EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 52), BCCHEXFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 52), imBCC->euclideanDistance(52, 82), EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 22), BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 22), imBCC->euclideanDistance(22, 82), EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 76), BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 76), imBCC->euclideanDistance(76, 82), EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 83), BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC->euclideanDistance(82, 83), imBCC->euclideanDistance(83, 82), EPSILONT);

    EXPECT_NEAR(imBCC2->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 45), factor * BCCHEXFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 45), imBCC2->euclideanDistance(45, 82), EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 46), factor * BCCHEXFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 46), imBCC2->euclideanDistance(46, 82), EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 51), factor * BCCHEXFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 51), imBCC2->euclideanDistance(51, 82), EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 52), factor * BCCHEXFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 52), imBCC2->euclideanDistance(52, 82), EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 22), factor * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 22), imBCC2->euclideanDistance(22, 82), EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 76), factor * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 76), imBCC2->euclideanDistance(76, 82), EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 83), factor * BCCSQFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imBCC2->euclideanDistance(82, 83), imBCC2->euclideanDistance(83, 82), EPSILONT);

    vector<double> dv;
    double right[3] = {BCCSQFACEDISTANCE, 0, 0};
    double bottom[3] = {0, BCCSQFACEDISTANCE, 0};
    double back[3] = {0, 0, BCCSQFACEDISTANCE};
    double left[3] = {-BCCSQFACEDISTANCE, 0, 0};
    double top[3] = {0, -BCCSQFACEDISTANCE, 0};
    double front[3] = {0, 0, -BCCSQFACEDISTANCE};
    double ftl[3] = {-BCCOFFSET, -BCCOFFSET, -BCCOFFSET};
    double ftr[3] = {BCCOFFSET, -BCCOFFSET, -BCCOFFSET};
    double fbl[3] = {-BCCOFFSET, BCCOFFSET, -BCCOFFSET};
    double fbr[3] = {BCCOFFSET, BCCOFFSET, -BCCOFFSET};
    double btl[3] = {-BCCOFFSET, -BCCOFFSET, BCCOFFSET};
    double btr[3] = {BCCOFFSET, -BCCOFFSET, BCCOFFSET};
    double bbl[3] = {-BCCOFFSET, BCCOFFSET, BCCOFFSET};
    double bbr[3] = {BCCOFFSET, BCCOFFSET, BCCOFFSET};
    imBCC->euclideanDistanceVector(82, 82, dv);
    EXPECT_TRUE(fabs(dv[0]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[1]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[2]) < EPSILONT);
    imBCC->euclideanDistanceVector(82, 83, dv);
    EXPECT_NEAR(dv[0], right[0], EPSILONT);
    EXPECT_NEAR(dv[1], right[1], EPSILONT);
    EXPECT_NEAR(dv[2], right[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 88, dv);
    EXPECT_NEAR(dv[0], bottom[0], EPSILONT);
    EXPECT_NEAR(dv[1], bottom[1], EPSILONT);
    EXPECT_NEAR(dv[2], bottom[2], EPSILONT);
    imBCC->euclideanDistanceVector(22, 82, dv);
    EXPECT_NEAR(dv[0], back[0], EPSILONT);
    EXPECT_NEAR(dv[1], back[1], EPSILONT);
    EXPECT_NEAR(dv[2], back[2], EPSILONT);
    imBCC->euclideanDistanceVector(83, 82, dv);
    EXPECT_NEAR(dv[0], left[0], EPSILONT);
    EXPECT_NEAR(dv[1], left[1], EPSILONT);
    EXPECT_NEAR(dv[2], left[2], EPSILONT);
    imBCC->euclideanDistanceVector(88, 82, dv);
    EXPECT_NEAR(dv[0], top[0], EPSILONT);
    EXPECT_NEAR(dv[1], top[1], EPSILONT);
    EXPECT_NEAR(dv[2], top[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 22, dv);
    EXPECT_NEAR(dv[0], front[0], EPSILONT);
    EXPECT_NEAR(dv[1], front[1], EPSILONT);
    EXPECT_NEAR(dv[2], front[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 45, dv);
    EXPECT_NEAR(dv[0], ftl[0], EPSILONT);
    EXPECT_NEAR(dv[1], ftl[1], EPSILONT);
    EXPECT_NEAR(dv[2], ftl[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 46, dv);
    EXPECT_NEAR(dv[0], ftr[0], EPSILONT);
    EXPECT_NEAR(dv[1], ftr[1], EPSILONT);
    EXPECT_NEAR(dv[2], ftr[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 51, dv);
    EXPECT_NEAR(dv[0], fbl[0], EPSILONT);
    EXPECT_NEAR(dv[1], fbl[1], EPSILONT);
    EXPECT_NEAR(dv[2], fbl[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 52, dv);
    EXPECT_NEAR(dv[0], fbr[0], EPSILONT);
    EXPECT_NEAR(dv[1], fbr[1], EPSILONT);
    EXPECT_NEAR(dv[2], fbr[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 105, dv);
    EXPECT_NEAR(dv[0], btl[0], EPSILONT);
    EXPECT_NEAR(dv[1], btl[1], EPSILONT);
    EXPECT_NEAR(dv[2], btl[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 106, dv);
    EXPECT_NEAR(dv[0], btr[0], EPSILONT);
    EXPECT_NEAR(dv[1], btr[1], EPSILONT);
    EXPECT_NEAR(dv[2], btr[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 111, dv);
    EXPECT_NEAR(dv[0], bbl[0], EPSILONT);
    EXPECT_NEAR(dv[1], bbl[1], EPSILONT);
    EXPECT_NEAR(dv[2], bbl[2], EPSILONT);
    imBCC->euclideanDistanceVector(82, 112, dv);
    EXPECT_NEAR(dv[0], bbr[0], EPSILONT);
    EXPECT_NEAR(dv[1], bbr[1], EPSILONT);
    EXPECT_NEAR(dv[2], bbr[2], EPSILONT);

    double right2[3] = {factor * BCCSQFACEDISTANCE, 0, 0};
    double bottom2[3] = {0, factor * BCCSQFACEDISTANCE, 0};
    double back2[3] = {0, 0, factor * BCCSQFACEDISTANCE};
    double left2[3] = {-factor * BCCSQFACEDISTANCE, 0, 0};
    double top2[3] = {0, -factor * BCCSQFACEDISTANCE, 0};
    double front2[3] = {0, 0, -factor * BCCSQFACEDISTANCE};
    double ftl2[3] = {-factor * BCCOFFSET, -factor * BCCOFFSET, -factor * BCCOFFSET};
    double ftr2[3] = {factor * BCCOFFSET, -factor * BCCOFFSET, -factor * BCCOFFSET};
    double fbl2[3] = {-factor * BCCOFFSET, factor * BCCOFFSET, -factor * BCCOFFSET};
    double fbr2[3] = {factor * BCCOFFSET, factor * BCCOFFSET, -factor * BCCOFFSET};
    double btl2[3] = {-factor * BCCOFFSET, -factor * BCCOFFSET, factor * BCCOFFSET};
    double btr2[3] = {factor * BCCOFFSET, -factor * BCCOFFSET, factor * BCCOFFSET};
    double bbl2[3] = {-factor * BCCOFFSET, factor * BCCOFFSET, factor * BCCOFFSET};
    double bbr2[3] = {factor * BCCOFFSET, factor * BCCOFFSET, factor * BCCOFFSET};
    imBCC2->euclideanDistanceVector(82, 82, dv);
    EXPECT_TRUE(fabs(dv[0]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[1]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[2]) < EPSILONT);
    imBCC2->euclideanDistanceVector(82, 83, dv);
    EXPECT_NEAR(dv[0], right2[0], EPSILONT);
    EXPECT_NEAR(dv[1], right2[1], EPSILONT);
    EXPECT_NEAR(dv[2], right2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 88, dv);
    EXPECT_NEAR(dv[0], bottom2[0], EPSILONT);
    EXPECT_NEAR(dv[1], bottom2[1], EPSILONT);
    EXPECT_NEAR(dv[2], bottom2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(22, 82, dv);
    EXPECT_NEAR(dv[0], back2[0], EPSILONT);
    EXPECT_NEAR(dv[1], back2[1], EPSILONT);
    EXPECT_NEAR(dv[2], back2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(83, 82, dv);
    EXPECT_NEAR(dv[0], left2[0], EPSILONT);
    EXPECT_NEAR(dv[1], left2[1], EPSILONT);
    EXPECT_NEAR(dv[2], left2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(88, 82, dv);
    EXPECT_NEAR(dv[0], top2[0], EPSILONT);
    EXPECT_NEAR(dv[1], top2[1], EPSILONT);
    EXPECT_NEAR(dv[2], top2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 22, dv);
    EXPECT_NEAR(dv[0], front2[0], EPSILONT);
    EXPECT_NEAR(dv[1], front2[1], EPSILONT);
    EXPECT_NEAR(dv[2], front2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 45, dv);
    EXPECT_NEAR(dv[0], ftl2[0], EPSILONT);
    EXPECT_NEAR(dv[1], ftl2[1], EPSILONT);
    EXPECT_NEAR(dv[2], ftl2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 46, dv);
    EXPECT_NEAR(dv[0], ftr2[0], EPSILONT);
    EXPECT_NEAR(dv[1], ftr2[1], EPSILONT);
    EXPECT_NEAR(dv[2], ftr2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 51, dv);
    EXPECT_NEAR(dv[0], fbl2[0], EPSILONT);
    EXPECT_NEAR(dv[1], fbl2[1], EPSILONT);
    EXPECT_NEAR(dv[2], fbl2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 52, dv);
    EXPECT_NEAR(dv[0], fbr2[0], EPSILONT);
    EXPECT_NEAR(dv[1], fbr2[1], EPSILONT);
    EXPECT_NEAR(dv[2], fbr2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 105, dv);
    EXPECT_NEAR(dv[0], btl2[0], EPSILONT);
    EXPECT_NEAR(dv[1], btl2[1], EPSILONT);
    EXPECT_NEAR(dv[2], btl2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 106, dv);
    EXPECT_NEAR(dv[0], btr2[0], EPSILONT);
    EXPECT_NEAR(dv[1], btr2[1], EPSILONT);
    EXPECT_NEAR(dv[2], btr2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 111, dv);
    EXPECT_NEAR(dv[0], bbl2[0], EPSILONT);
    EXPECT_NEAR(dv[1], bbl2[1], EPSILONT);
    EXPECT_NEAR(dv[2], bbl2[2], EPSILONT);
    imBCC2->euclideanDistanceVector(82, 112, dv);
    EXPECT_NEAR(dv[0], bbr2[0], EPSILONT);
    EXPECT_NEAR(dv[1], bbr2[1], EPSILONT);
    EXPECT_NEAR(dv[2], bbr2[2], EPSILONT);

    delete imBCC;
    delete imBCC2;
}