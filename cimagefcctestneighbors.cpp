#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageFCC.h"
#include "exception.h"
#include <cmath>
#include <vector>

using namespace CImage;

TEST(CImageFCC, neighbors) {

    /**
    * Tests getNeighbor(r,c,l,N). Since all other methods
    * always call getXNeighbors(r,c,l), those methods should work
    * properly if the tests pass for this method and for
    * indexTo[R,C,L]().
    */

    // image parameters
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N];
    for (int i = 0; i < N; i++) {
        data[i] = 0;
    }
    CImagetypeFCC *imFCC = new CImagetypeFCC(data, nR, nC, nL, nB);

    vector<Neighbor> neighbors;
    int nNeighbors, returnedNeighbors, correctNNeighbors;
    // neighbor indices
    // {tf,tl,tba,tr,fl,bal,bar,fr,bof,bol,boba,bor,   t,f,l,ba,r,bo}
    int FCC12ELER[12] = {99, 128, 159, 129, 104, 164, 165, 105, 111, 140, 171, 141}; // {31,55,81,56,35,85,86,36,41,65,91,66};
    int FCC12ELOR[12] = {44, 74, 104, 75, 50, 110, 111, 51, 56, 86, 116, 87}; // {37,62,87,63,42,92,93,43,47,72,97,73};
    int FCC12OLER[12] = {69, 99, 129, 100, 75, 135, 136, 76, 81, 111, 141, 112}; // {1,25,51,26,5,55,56,6,11,35,61,36};
    int FCC12OLOR[12] = {74, 103, 134, 104, 79, 139, 140, 80, 86, 115, 146, 116}; // {6,31,56,32,11,61,62,12,16,41,66,42};
    int FCC18ELER[18] = {99, 128, 159, 129, 104, 164, 165, 105, 111, 140, 171, 141, 123, 75, 134, 195, 136, 147}; // {31,55,81,56,35,85,86,36,41,65,91,66,51,11,60,111,62,71};
    int FCC18ELOR[18] = {44, 74, 104, 75, 50, 110, 111, 51, 56, 86, 116, 87, 68, 20, 79, 140, 81}; // bottom missing // {37,62,87,63,42,92,93,43,47,72,97,73,57,17,66,117,68}; // bottom missing
    int FCC18OLER[18] = {69, 99, 129, 100, 75, 135, 136, 76, 81, 111, 141, 112, 93, 45, 104, 165, 106, 117}; // {1,25,51,26,5,55,56,6,11,35,61,36,30,81,32,41}; // top and front missing
    int FCC18OLOR[18] = {74, 103, 134, 104, 79, 139, 140, 80, 86, 115, 146, 116, 98, 50, 109, 170, 111}; // bottom missing // {6,31,56,32,11,61,62,12,16,41,66,42,26,35,86,37,46}; // front missing

    // 12 neighbors
    nNeighbors = 12;
    correctNNeighbors = 3;
    imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 5;
    imFCC->getNeighbors(4, 5, 6, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imFCC->getNeighbors(3, 5, 6, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imFCC->getNeighbors(4, 5, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 8;
    imFCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imFCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imFCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    correctNNeighbors = 12;
    imFCC->getNeighbors(3, 5, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imFCC->getNeighbors(2, 3, 4, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC12ELER[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC12ELER[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC12ELER[2]);
    imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 4), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC12ELER[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC12ELER[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC12ELER[2]);

    imFCC->getNeighbors(3, 2, 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC12ELOR[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC12ELOR[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC12ELOR[2]);
    imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 2), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC12ELOR[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC12ELOR[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC12ELOR[2]);

    imFCC->getNeighbors(2, 3, 3, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC12OLER[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC12OLER[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC12OLER[2]);
    imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 3), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC12OLER[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC12OLER[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC12OLER[2]);

    imFCC->getNeighbors(3, 2, 3, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC12OLOR[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC12OLOR[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC12OLOR[2]);
    imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 3), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC12OLOR[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC12OLOR[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC12OLOR[2]);

    // 18 neighbors
    nNeighbors = 18;
    correctNNeighbors = 6;
    imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 8;
    imFCC->getNeighbors(4, 5, 6, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imFCC->getNeighbors(3, 5, 6, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imFCC->getNeighbors(4, 5, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 11;
    imFCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imFCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imFCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 15;
    imFCC->getNeighbors(3, 5, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    correctNNeighbors = 17;
    imFCC->getNeighbors(3, 2, 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC18ELOR[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC18ELOR[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC18ELOR[2]);
    imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 2), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC18ELOR[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC18ELOR[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC18ELOR[2]);

    imFCC->getNeighbors(3, 2, 3, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC18OLOR[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC18OLOR[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC18OLOR[2]);
    imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 3), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC18OLOR[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC18OLOR[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC18OLOR[2]);

    correctNNeighbors = 18;
    imFCC->getNeighbors(2, 3, 4, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC18ELER[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC18ELER[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC18ELER[2]);
    imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 4), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC18ELER[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC18ELER[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC18ELER[2]);

    imFCC->getNeighbors(2, 3, 3, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC18OLER[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC18OLER[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC18OLER[2]);
    imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 3), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), FCC18OLER[0]);
    EXPECT_EQ(neighbors[1].getIndex(), FCC18OLER[1]);
    EXPECT_EQ(neighbors[2].getIndex(), FCC18OLER[2]);

    // Exceptions
    nNeighbors = 12;
    EXPECT_THROW(imFCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 18;
    EXPECT_THROW(imFCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imFCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 6;
    EXPECT_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 8;
    EXPECT_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 14;
    EXPECT_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 26;
    EXPECT_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = -12;
    EXPECT_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 0;
    EXPECT_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 100;
    EXPECT_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);

    delete imFCC;
}