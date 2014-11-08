#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageBCC.h"
#include "exception.h"
#include <cmath>
#include <vector>


using namespace CImage;

TEST(CImageBCC, neighbors) {
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
    CImageBCC<uint8> *imBCC = new CImageBCC<uint8>(data, nR, nC, nL, nB);

    vector<Neighbor> neighbors;
    int nNeighbors, returnedNeighbors, correctNNeighbors;
    // neighbor indices
    // {tlf,trf,bolf,borf,tlba,trba,bolba,borba,   t,f,l,ba,r,bo}
    int BCC8EL[8] = {45, 46, 51, 52, 105, 106, 111, 112}; // {31,32,36,37,81,82,86,87};
    int BCC8OL[8] = {82, 83, 88, 89, 142, 143, 148, 149}; // {12,13,17,18,62,63,67,68};
    int BCC14EL[14] = {45, 46, 51, 52, 105, 106, 111, 112, 76, 22, 81, 142, 83, 88}; // {31,32,36,37,81,82,86,87,57,12,61,112,63,67};
    int BCC14OL[14] = {82, 83, 88, 89, 142, 143, 148, 149, 106, 52, 111, 172, 113, 118}; // {12,13,17,18,62,63,67,68,32,36,87,38,42};

    // 8 neighbors
    nNeighbors = 8;
    correctNNeighbors = 8;
    imBCC->getNeighbors(3, 4, 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), BCC8EL[0]);
    EXPECT_EQ(neighbors[1].getIndex(), BCC8EL[1]);
    EXPECT_EQ(neighbors[2].getIndex(), BCC8EL[2]);
    EXPECT_EQ(neighbors[3].getIndex(), BCC8EL[3]);
    EXPECT_EQ(neighbors[4].getIndex(), BCC8EL[4]);
    EXPECT_EQ(neighbors[5].getIndex(), BCC8EL[5]);
    EXPECT_EQ(neighbors[6].getIndex(), BCC8EL[6]);
    EXPECT_EQ(neighbors[7].getIndex(), BCC8EL[7]);
    imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 2), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), BCC8EL[0]);
    EXPECT_EQ(neighbors[1].getIndex(), BCC8EL[1]);
    EXPECT_EQ(neighbors[2].getIndex(), BCC8EL[2]);
    EXPECT_EQ(neighbors[3].getIndex(), BCC8EL[3]);
    EXPECT_EQ(neighbors[4].getIndex(), BCC8EL[4]);
    EXPECT_EQ(neighbors[5].getIndex(), BCC8EL[5]);
    EXPECT_EQ(neighbors[6].getIndex(), BCC8EL[6]);
    EXPECT_EQ(neighbors[7].getIndex(), BCC8EL[7]);
    imBCC->getNeighbors(3, 4, 3, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), BCC8OL[0]);
    EXPECT_EQ(neighbors[1].getIndex(), BCC8OL[1]);
    EXPECT_EQ(neighbors[2].getIndex(), BCC8OL[2]);
    EXPECT_EQ(neighbors[3].getIndex(), BCC8OL[3]);
    EXPECT_EQ(neighbors[4].getIndex(), BCC8OL[4]);
    EXPECT_EQ(neighbors[5].getIndex(), BCC8OL[5]);
    EXPECT_EQ(neighbors[6].getIndex(), BCC8OL[6]);
    EXPECT_EQ(neighbors[7].getIndex(), BCC8OL[7]);
    imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 3), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), BCC8OL[0]);
    EXPECT_EQ(neighbors[1].getIndex(), BCC8OL[1]);
    EXPECT_EQ(neighbors[2].getIndex(), BCC8OL[2]);
    EXPECT_EQ(neighbors[3].getIndex(), BCC8OL[3]);
    EXPECT_EQ(neighbors[4].getIndex(), BCC8OL[4]);
    EXPECT_EQ(neighbors[5].getIndex(), BCC8OL[5]);
    EXPECT_EQ(neighbors[6].getIndex(), BCC8OL[6]);
    EXPECT_EQ(neighbors[7].getIndex(), BCC8OL[7]);
    correctNNeighbors = 1;
    imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 2;
    imBCC->getNeighbors(4, 0, 6, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 4;
    imBCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imBCC->getNeighbors(0, 5, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imBCC->getNeighbors(4, 0, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    // 14 neighbors
    nNeighbors = 14;
    correctNNeighbors = 14;
    imBCC->getNeighbors(3, 4, 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), BCC14EL[0]);
    EXPECT_EQ(neighbors[1].getIndex(), BCC14EL[1]);
    EXPECT_EQ(neighbors[2].getIndex(), BCC14EL[2]);
    EXPECT_EQ(neighbors[3].getIndex(), BCC14EL[3]);
    EXPECT_EQ(neighbors[4].getIndex(), BCC14EL[4]);
    EXPECT_EQ(neighbors[5].getIndex(), BCC14EL[5]);
    EXPECT_EQ(neighbors[6].getIndex(), BCC14EL[6]);
    EXPECT_EQ(neighbors[7].getIndex(), BCC14EL[7]);
    EXPECT_EQ(neighbors[8].getIndex(), BCC14EL[8]);
    EXPECT_EQ(neighbors[9].getIndex(), BCC14EL[9]);
    EXPECT_EQ(neighbors[10].getIndex(), BCC14EL[10]);
    EXPECT_EQ(neighbors[11].getIndex(), BCC14EL[11]);
    EXPECT_EQ(neighbors[12].getIndex(), BCC14EL[12]);
    EXPECT_EQ(neighbors[13].getIndex(), BCC14EL[13]);
    imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 2), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), BCC14EL[0]);
    EXPECT_EQ(neighbors[1].getIndex(), BCC14EL[1]);
    EXPECT_EQ(neighbors[2].getIndex(), BCC14EL[2]);
    EXPECT_EQ(neighbors[3].getIndex(), BCC14EL[3]);
    EXPECT_EQ(neighbors[4].getIndex(), BCC14EL[4]);
    EXPECT_EQ(neighbors[5].getIndex(), BCC14EL[5]);
    EXPECT_EQ(neighbors[6].getIndex(), BCC14EL[6]);
    EXPECT_EQ(neighbors[7].getIndex(), BCC14EL[7]);
    EXPECT_EQ(neighbors[8].getIndex(), BCC14EL[8]);
    EXPECT_EQ(neighbors[9].getIndex(), BCC14EL[9]);
    EXPECT_EQ(neighbors[10].getIndex(), BCC14EL[10]);
    EXPECT_EQ(neighbors[11].getIndex(), BCC14EL[11]);
    EXPECT_EQ(neighbors[12].getIndex(), BCC14EL[12]);
    EXPECT_EQ(neighbors[13].getIndex(), BCC14EL[13]);
    imBCC->getNeighbors(3, 4, 3, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), BCC14OL[0]);
    EXPECT_EQ(neighbors[1].getIndex(), BCC14OL[1]);
    EXPECT_EQ(neighbors[2].getIndex(), BCC14OL[2]);
    EXPECT_EQ(neighbors[3].getIndex(), BCC14OL[3]);
    EXPECT_EQ(neighbors[4].getIndex(), BCC14OL[4]);
    EXPECT_EQ(neighbors[5].getIndex(), BCC14OL[5]);
    EXPECT_EQ(neighbors[6].getIndex(), BCC14OL[6]);
    EXPECT_EQ(neighbors[7].getIndex(), BCC14OL[7]);
    EXPECT_EQ(neighbors[8].getIndex(), BCC14OL[8]);
    EXPECT_EQ(neighbors[9].getIndex(), BCC14OL[9]);
    EXPECT_EQ(neighbors[10].getIndex(), BCC14OL[10]);
    EXPECT_EQ(neighbors[11].getIndex(), BCC14OL[11]);
    EXPECT_EQ(neighbors[12].getIndex(), BCC14OL[12]);
    EXPECT_EQ(neighbors[13].getIndex(), BCC14OL[13]);
    imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 3), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), BCC14OL[0]);
    EXPECT_EQ(neighbors[1].getIndex(), BCC14OL[1]);
    EXPECT_EQ(neighbors[2].getIndex(), BCC14OL[2]);
    EXPECT_EQ(neighbors[3].getIndex(), BCC14OL[3]);
    EXPECT_EQ(neighbors[4].getIndex(), BCC14OL[4]);
    EXPECT_EQ(neighbors[5].getIndex(), BCC14OL[5]);
    EXPECT_EQ(neighbors[6].getIndex(), BCC14OL[6]);
    EXPECT_EQ(neighbors[7].getIndex(), BCC14OL[7]);
    EXPECT_EQ(neighbors[8].getIndex(), BCC14OL[8]);
    EXPECT_EQ(neighbors[9].getIndex(), BCC14OL[9]);
    EXPECT_EQ(neighbors[10].getIndex(), BCC14OL[10]);
    EXPECT_EQ(neighbors[11].getIndex(), BCC14OL[11]);
    EXPECT_EQ(neighbors[12].getIndex(), BCC14OL[12]);
    EXPECT_EQ(neighbors[13].getIndex(), BCC14OL[13]);
    correctNNeighbors = 4;
    imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 5;
    imBCC->getNeighbors(4, 0, 6, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 7;
    imBCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imBCC->getNeighbors(0, 5, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imBCC->getNeighbors(4, 0, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    // Exceptions
    nNeighbors = 8;
    EXPECT_THROW(imBCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 14;
    EXPECT_THROW(imBCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imBCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 6;
    EXPECT_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 12;
    EXPECT_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 18;
    EXPECT_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 26;
    EXPECT_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = -8;
    EXPECT_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 0;
    EXPECT_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 100;
    EXPECT_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);

    delete imBCC;
}