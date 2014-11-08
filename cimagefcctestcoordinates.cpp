#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageFCC.h"
#include "exception.h"
#include <cmath>
#include <vector>

using namespace CImage;

TEST(CImageFCC, coordinates) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = 0;
    }
    CImagetypeFCC *imFCC = new CImagetypeFCC(data, nR, nC, nL, nB);
    double volume = 2.5;
    double factor = cbrt(volume);
    CImagetypeFCC *imFCC2 = new CImagetypeFCC(data, nR, nC, nL, nB, volume);
    vector<double> coordinates;

    // spel coordinates
    EXPECT_NEAR(imFCC->indexToX(0), FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToY(0), FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToZ(0), FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToX(135), FCCOFFSET + 6 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToY(135), FCCOFFSET + FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->indexToZ(135), FCCOFFSET + 2 * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->indexToX(80), FCCOFFSET + 5 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToY(80), FCCOFFSET + 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToZ(80), FCCOFFSET + 2 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToX(105), FCCOFFSET + 7 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToY(105), FCCOFFSET + 2 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToZ(105), FCCOFFSET + 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToX(110), FCCOFFSET + 4 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToY(110), FCCOFFSET + 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToZ(110), FCCOFFSET + 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToX(209), FCCOFFSET + 10 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToY(209), FCCOFFSET + 4 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->indexToZ(209), FCCOFFSET + 6 * FCCOFFSET, EPSILONT);

    imFCC->getCoordinates(0, coordinates);
    EXPECT_NEAR(coordinates[0], FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[1], FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[2], FCCOFFSET, EPSILONT);
    imFCC->getCoordinates(135, coordinates);
    EXPECT_NEAR(coordinates[0], FCCOFFSET + 6 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[1], FCCOFFSET + FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(coordinates[2], FCCOFFSET + 2 * FCCPOINTDISTANCE, EPSILONT);
    imFCC->getCoordinates(209, coordinates);
    EXPECT_NEAR(coordinates[0], FCCOFFSET + 10 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[1], FCCOFFSET + 4 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(coordinates[2], FCCOFFSET + 6 * FCCOFFSET, EPSILONT);

    EXPECT_NEAR(imFCC2->indexToX(0), factor * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC2->indexToY(0), factor * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC2->indexToZ(0), factor * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC2->indexToX(135), factor * (FCCOFFSET + 6 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToY(135), factor * (FCCOFFSET + FCCPOINTDISTANCE), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToZ(135), factor * (FCCOFFSET + 2 * FCCPOINTDISTANCE), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToX(80), factor * (FCCOFFSET + 5 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToY(80), factor * (FCCOFFSET + 3 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToZ(80), factor * (FCCOFFSET + 2 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToX(105), factor * (FCCOFFSET + 7 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToY(105), factor * (FCCOFFSET + 2 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToZ(105), factor * (FCCOFFSET + 3 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToX(110), factor * (FCCOFFSET + 4 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToY(110), factor * (FCCOFFSET + 3 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToZ(110), factor * (FCCOFFSET + 3 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToX(209), factor * (FCCOFFSET + 10 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToY(209), factor * (FCCOFFSET + 4 * FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->indexToZ(209), factor * (FCCOFFSET + 6 * FCCOFFSET), EPSILONT);

    CImagetypeFCC *imFCC1C1L = new CImagetypeFCC(data, N, 1, 1, 1);
    CImagetypeFCC *imFCC1R1L = new CImagetypeFCC(data, 1, N, 1, 1);
    CImagetypeFCC *imFCC1R1C = new CImagetypeFCC(data, 1, 1, N, 1);
    int n1 = 15, n2 = 14;
    CImagetypeFCC *imFCCRC = new CImagetypeFCC(data, n1, n2, 1, 1);
    CImagetypeFCC *imFCCRL = new CImagetypeFCC(data, n1, 1, n2, 1);
    CImagetypeFCC *imFCCCL = new CImagetypeFCC(data, 1, n1, n2, 1);

    // width, height and depth
    EXPECT_NEAR(imFCC->getWidth(), 6 * FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC->getHeight(), 3 * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->getDepth(), (7 + 1) * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC2->getWidth(), factor * (6 * FCCPOINTDISTANCE + FCCOFFSET), EPSILONT);
    EXPECT_NEAR(imFCC2->getHeight(), factor * (3 * FCCPOINTDISTANCE), EPSILONT);
    EXPECT_NEAR(imFCC2->getDepth(), factor * (7 + 1) * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC1C1L->getWidth(), 3 * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC1C1L->getHeight(), (N + 1) * FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC1C1L->getDepth(), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC1R1L->getWidth(), N * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC1R1L->getHeight(), FCCPOINTDISTANCE, EPSILONT); //!!
    EXPECT_NEAR(imFCC1R1L->getDepth(), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC1R1C->getWidth(), FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCC1R1C->getHeight(), FCCPOINTDISTANCE, EPSILONT); //!!
    EXPECT_NEAR(imFCC1R1C->getDepth(), (N + 1) * FCCOFFSET, EPSILONT);

    EXPECT_NEAR(imFCCRC->getWidth(), n2 * FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCCRC->getHeight(), (n1 + 1) * FCCOFFSET, EPSILONT); //!!
    EXPECT_NEAR(imFCCRC->getDepth(), FCCPOINTDISTANCE, EPSILONT);

    EXPECT_NEAR(imFCCRL->getWidth(), FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCCRL->getHeight(), (n1 + 1) * FCCOFFSET, EPSILONT); //!!
    EXPECT_NEAR(imFCCRL->getDepth(), (n2 + 1) * FCCOFFSET, EPSILONT);

    EXPECT_NEAR(imFCCCL->getWidth(), n1 * FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
    EXPECT_NEAR(imFCCCL->getHeight(), FCCPOINTDISTANCE, EPSILONT); //!!
    EXPECT_NEAR(imFCCCL->getDepth(), (n2 + 1) * FCCOFFSET, EPSILONT);

    delete imFCC;
    delete imFCC2;
    delete imFCC1C1L;
    delete imFCC1R1L;
    delete imFCC1R1C;
    delete imFCCCL;
    delete imFCCRL;
    delete imFCCRC;
}

TEST(CImageFCC, distances) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = 0;
    }
    CImagetypeFCC *imFCC = new CImagetypeFCC(data, nR, nC, nL, nB);
    double volume = 2.5;
    double factor = cbrt(volume);
    CImagetypeFCC *imFCC2 = new CImagetypeFCC(data, nR, nC, nL, nB, volume);

    // distance between spels
    EXPECT_NEAR(imFCC->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 69), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 69), imFCC->euclideanDistance(69, 105), EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 75), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 75), imFCC->euclideanDistance(75, 105), EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 76), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 76), imFCC->euclideanDistance(76, 105), EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 81), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 81), imFCC->euclideanDistance(81, 105), EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 99), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 99), imFCC->euclideanDistance(99, 105), EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 100), FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 100), imFCC->euclideanDistance(100, 105), EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 45), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 45), imFCC->euclideanDistance(45, 105), EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 93), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 93), imFCC->euclideanDistance(93, 105), EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 104), FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC->euclideanDistance(105, 104), imFCC->euclideanDistance(104, 105), EPSILONT);

    EXPECT_NEAR(imFCC2->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 69), factor * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 69), imFCC2->euclideanDistance(69, 105), EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 75), factor * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 75), imFCC2->euclideanDistance(75, 105), EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 76), factor * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 76), imFCC2->euclideanDistance(76, 105), EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 81), factor * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 81), imFCC2->euclideanDistance(81, 105), EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 99), factor * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 99), imFCC2->euclideanDistance(99, 105), EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 100), factor * FCCFACEDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 100), imFCC2->euclideanDistance(100, 105), EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 45), factor * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 45), imFCC2->euclideanDistance(45, 105), EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 93), factor * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 93), imFCC2->euclideanDistance(93, 105), EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 104), factor * FCCPOINTDISTANCE, EPSILONT);
    EXPECT_NEAR(imFCC2->euclideanDistance(105, 104), imFCC2->euclideanDistance(104, 105), EPSILONT);

    vector<double> dv;
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
    imFCC->euclideanDistanceVector(82, 82, dv);
    EXPECT_TRUE(fabs(dv[0]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[1]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[2]) < EPSILONT);
    imFCC->euclideanDistanceVector(105, 45, dv);
    EXPECT_NEAR(dv[0], front[0], EPSILONT);
    EXPECT_NEAR(dv[1], front[1], EPSILONT);
    EXPECT_NEAR(dv[2], front[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 93, dv);
    EXPECT_NEAR(dv[0], top[0], EPSILONT);
    EXPECT_NEAR(dv[1], top[1], EPSILONT);
    EXPECT_NEAR(dv[2], top[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 106, dv);
    EXPECT_NEAR(dv[0], right[0], EPSILONT);
    EXPECT_NEAR(dv[1], right[1], EPSILONT);
    EXPECT_NEAR(dv[2], right[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 117, dv);
    EXPECT_NEAR(dv[0], bottom[0], EPSILONT);
    EXPECT_NEAR(dv[1], bottom[1], EPSILONT);
    EXPECT_NEAR(dv[2], bottom[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 104, dv);
    EXPECT_NEAR(dv[0], left[0], EPSILONT);
    EXPECT_NEAR(dv[1], left[1], EPSILONT);
    EXPECT_NEAR(dv[2], left[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 165, dv);
    EXPECT_NEAR(dv[0], back[0], EPSILONT);
    EXPECT_NEAR(dv[1], back[1], EPSILONT);
    EXPECT_NEAR(dv[2], back[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 69, dv);
    EXPECT_NEAR(dv[0], ft[0], EPSILONT);
    EXPECT_NEAR(dv[1], ft[1], EPSILONT);
    EXPECT_NEAR(dv[2], ft[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 76, dv);
    EXPECT_NEAR(dv[0], fr[0], EPSILONT);
    EXPECT_NEAR(dv[1], fr[1], EPSILONT);
    EXPECT_NEAR(dv[2], fr[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 81, dv);
    EXPECT_NEAR(dv[0], fb[0], EPSILONT);
    EXPECT_NEAR(dv[1], fb[1], EPSILONT);
    EXPECT_NEAR(dv[2], fb[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 75, dv);
    EXPECT_NEAR(dv[0], fl[0], EPSILONT);
    EXPECT_NEAR(dv[1], fl[1], EPSILONT);
    EXPECT_NEAR(dv[2], fl[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 100, dv);
    EXPECT_NEAR(dv[0], mtr[0], EPSILONT);
    EXPECT_NEAR(dv[1], mtr[1], EPSILONT);
    EXPECT_NEAR(dv[2], mtr[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 112, dv);
    EXPECT_NEAR(dv[0], mbr[0], EPSILONT);
    EXPECT_NEAR(dv[1], mbr[1], EPSILONT);
    EXPECT_NEAR(dv[2], mbr[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 111, dv);
    EXPECT_NEAR(dv[0], mbl[0], EPSILONT);
    EXPECT_NEAR(dv[1], mbl[1], EPSILONT);
    EXPECT_NEAR(dv[2], mbl[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 99, dv);
    EXPECT_NEAR(dv[0], mtl[0], EPSILONT);
    EXPECT_NEAR(dv[1], mtl[1], EPSILONT);
    EXPECT_NEAR(dv[2], mtl[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 129, dv);
    EXPECT_NEAR(dv[0], bt[0], EPSILONT);
    EXPECT_NEAR(dv[1], bt[1], EPSILONT);
    EXPECT_NEAR(dv[2], bt[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 136, dv);
    EXPECT_NEAR(dv[0], br[0], EPSILONT);
    EXPECT_NEAR(dv[1], br[1], EPSILONT);
    EXPECT_NEAR(dv[2], br[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 141, dv);
    EXPECT_NEAR(dv[0], bb[0], EPSILONT);
    EXPECT_NEAR(dv[1], bb[1], EPSILONT);
    EXPECT_NEAR(dv[2], bb[2], EPSILONT);
    imFCC->euclideanDistanceVector(105, 135, dv);
    EXPECT_NEAR(dv[0], bl[0], EPSILONT);
    EXPECT_NEAR(dv[1], bl[1], EPSILONT);
    EXPECT_NEAR(dv[2], bl[2], EPSILONT);

    double ft2[3] = {0, -factor * FCCOFFSET, -factor * FCCOFFSET};
    double fr2[3] = {factor * FCCOFFSET, 0, -factor * FCCOFFSET};
    double fb2[3] = {0, factor * FCCOFFSET, -factor * FCCOFFSET};
    double fl2[3] = {-factor * FCCOFFSET, 0, -factor * FCCOFFSET};
    double mtr2[3] = {factor * FCCOFFSET, -factor * FCCOFFSET, 0};
    double mbr2[3] = {factor * FCCOFFSET, factor * FCCOFFSET, 0};
    double mbl2[3] = {-factor * FCCOFFSET, factor * FCCOFFSET, 0};
    double mtl2[3] = {-factor * FCCOFFSET, -factor * FCCOFFSET, 0};
    double bt2[3] = {0, -factor * FCCOFFSET, factor * FCCOFFSET};
    double br2[3] = {factor * FCCOFFSET, 0, factor * FCCOFFSET};
    double bb2[3] = {0, factor * FCCOFFSET, factor * FCCOFFSET};
    double bl2[3] = {-factor * FCCOFFSET, 0, factor * FCCOFFSET};
    double front2[3] = {0, 0, -factor * FCCPOINTDISTANCE};
    double top2[3] = {0, -factor * FCCPOINTDISTANCE, 0};
    double right2[3] = {factor * FCCPOINTDISTANCE, 0, 0};
    double bottom2[3] = {0, factor * FCCPOINTDISTANCE, 0};
    double left2[3] = {-factor * FCCPOINTDISTANCE, 0, 0};
    double back2[3] = {0, 0, factor * FCCPOINTDISTANCE};
    imFCC2->euclideanDistanceVector(82, 82, dv);
    EXPECT_TRUE(fabs(dv[0]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[1]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[2]) < EPSILONT);
    imFCC2->euclideanDistanceVector(105, 45, dv);
    EXPECT_NEAR(dv[0], front2[0], EPSILONT);
    EXPECT_NEAR(dv[1], front2[1], EPSILONT);
    EXPECT_NEAR(dv[2], front2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 93, dv);
    EXPECT_NEAR(dv[0], top2[0], EPSILONT);
    EXPECT_NEAR(dv[1], top2[1], EPSILONT);
    EXPECT_NEAR(dv[2], top2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 106, dv);
    EXPECT_NEAR(dv[0], right2[0], EPSILONT);
    EXPECT_NEAR(dv[1], right2[1], EPSILONT);
    EXPECT_NEAR(dv[2], right2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 117, dv);
    EXPECT_NEAR(dv[0], bottom2[0], EPSILONT);
    EXPECT_NEAR(dv[1], bottom2[1], EPSILONT);
    EXPECT_NEAR(dv[2], bottom2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 104, dv);
    EXPECT_NEAR(dv[0], left2[0], EPSILONT);
    EXPECT_NEAR(dv[1], left2[1], EPSILONT);
    EXPECT_NEAR(dv[2], left2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 165, dv);
    EXPECT_NEAR(dv[0], back2[0], EPSILONT);
    EXPECT_NEAR(dv[1], back2[1], EPSILONT);
    EXPECT_NEAR(dv[2], back2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 69, dv);
    EXPECT_NEAR(dv[0], ft2[0], EPSILONT);
    EXPECT_NEAR(dv[1], ft2[1], EPSILONT);
    EXPECT_NEAR(dv[2], ft2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 76, dv);
    EXPECT_NEAR(dv[0], fr2[0], EPSILONT);
    EXPECT_NEAR(dv[1], fr2[1], EPSILONT);
    EXPECT_NEAR(dv[2], fr2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 81, dv);
    EXPECT_NEAR(dv[0], fb2[0], EPSILONT);
    EXPECT_NEAR(dv[1], fb2[1], EPSILONT);
    EXPECT_NEAR(dv[2], fb2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 75, dv);
    EXPECT_NEAR(dv[0], fl2[0], EPSILONT);
    EXPECT_NEAR(dv[1], fl2[1], EPSILONT);
    EXPECT_NEAR(dv[2], fl2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 100, dv);
    EXPECT_NEAR(dv[0], mtr2[0], EPSILONT);
    EXPECT_NEAR(dv[1], mtr2[1], EPSILONT);
    EXPECT_NEAR(dv[2], mtr2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 112, dv);
    EXPECT_NEAR(dv[0], mbr2[0], EPSILONT);
    EXPECT_NEAR(dv[1], mbr2[1], EPSILONT);
    EXPECT_NEAR(dv[2], mbr2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 111, dv);
    EXPECT_NEAR(dv[0], mbl2[0], EPSILONT);
    EXPECT_NEAR(dv[1], mbl2[1], EPSILONT);
    EXPECT_NEAR(dv[2], mbl2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 99, dv);
    EXPECT_NEAR(dv[0], mtl2[0], EPSILONT);
    EXPECT_NEAR(dv[1], mtl2[1], EPSILONT);
    EXPECT_NEAR(dv[2], mtl2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 129, dv);
    EXPECT_NEAR(dv[0], bt2[0], EPSILONT);
    EXPECT_NEAR(dv[1], bt2[1], EPSILONT);
    EXPECT_NEAR(dv[2], bt2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 136, dv);
    EXPECT_NEAR(dv[0], br2[0], EPSILONT);
    EXPECT_NEAR(dv[1], br2[1], EPSILONT);
    EXPECT_NEAR(dv[2], br2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 141, dv);
    EXPECT_NEAR(dv[0], bb2[0], EPSILONT);
    EXPECT_NEAR(dv[1], bb2[1], EPSILONT);
    EXPECT_NEAR(dv[2], bb2[2], EPSILONT);
    imFCC2->euclideanDistanceVector(105, 135, dv);
    EXPECT_NEAR(dv[0], bl2[0], EPSILONT);
    EXPECT_NEAR(dv[1], bl2[1], EPSILONT);
    EXPECT_NEAR(dv[2], bl2[2], EPSILONT);

    delete imFCC;
    delete imFCC2;

}