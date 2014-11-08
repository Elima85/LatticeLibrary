#ifndef IMAGEBCCTEST
#define IMAGEBCCTEST

#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageBCC.h"
#include "exception.h"
#include "label.h"
#include <cmath>
#include <vector>


using namespace CImage;

/**
 * Tests type CImagetypeBCC aka CImageBCC<uint8>.
 */

TEST(CImageBCC, constructor) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = i;
	}

	// constructor
	CImagetypeBCC *imBCC = new CImagetypeBCC(data, nR, nC, nL, nB);
	EXPECT_TRUE(imBCC);

	// getters
	uint8* imdata = imBCC->getData();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < nB; j++) {
			EXPECT_TRUE(imdata[i] == data[i]);
		}
	}

	EXPECT_TRUE(imBCC->getNElements() == N);
	EXPECT_TRUE(imBCC->getNElements() != N + 1);

	EXPECT_TRUE(imBCC->getNColumns() == nC);
	EXPECT_TRUE(imBCC->getNColumns() != nC + 1);

	EXPECT_TRUE(imBCC->getNRows() == nR);
	EXPECT_TRUE(imBCC->getNRows() != nR + 1);

	EXPECT_TRUE(imBCC->getNLayers() == nL);
	EXPECT_TRUE(imBCC->getNLayers() != nL + 1);

	EXPECT_TRUE(imBCC->getNBands() == nB);
	EXPECT_TRUE(imBCC->getNBands() != nB + 1);

	// validity of elements
	EXPECT_TRUE(!imBCC->isValid(-1));
	EXPECT_TRUE(imBCC->isValid(0));
	EXPECT_TRUE(imBCC->isValid(N - 1));
	EXPECT_TRUE(!imBCC->isValid(N));

	EXPECT_TRUE(!imBCC->isValid(0, -1));
	EXPECT_TRUE(!imBCC->isValid(N - 1, -1));
	EXPECT_TRUE(!imBCC->isValid(-1, 0));
	EXPECT_TRUE(imBCC->isValid(0, 0));
	EXPECT_TRUE(imBCC->isValid(N - 1, 0));
	EXPECT_TRUE(!imBCC->isValid(N, 0));
	EXPECT_TRUE(imBCC->isValid(0, nB - 1));
	EXPECT_TRUE(imBCC->isValid(N - 1, nB - 1));
	EXPECT_TRUE(!imBCC->isValid(0, nB));
	EXPECT_TRUE(!imBCC->isValid(N - 1, nB));

	EXPECT_TRUE(!imBCC->isValid(-1, 0, 0));
	EXPECT_TRUE(!imBCC->isValid(0, -1, 0));
	EXPECT_TRUE(!imBCC->isValid(0, 0, -1));
	EXPECT_TRUE(imBCC->isValid(0, 0, 0));
	EXPECT_TRUE(imBCC->isValid(nR - 1, 0, 0));
	EXPECT_TRUE(imBCC->isValid(0, nC - 1, 0));
	EXPECT_TRUE(imBCC->isValid(0, 0, nL - 1));
	EXPECT_TRUE(!imBCC->isValid(nR, 0, 0));
	EXPECT_TRUE(!imBCC->isValid(0, nC, 0));
	EXPECT_TRUE(!imBCC->isValid(0, 0, nL));

	EXPECT_TRUE(!imBCC->isValid(0, 0, 0, -1));
	EXPECT_TRUE(!imBCC->isValid(nR - 1, 0, 0, -1));
	EXPECT_TRUE(!imBCC->isValid(0, nC - 1, 0, -1));
	EXPECT_TRUE(!imBCC->isValid(0, 0, nL - 1, -1));
	EXPECT_TRUE(!imBCC->isValid(0, 0, 0, nB));
	EXPECT_TRUE(!imBCC->isValid(nR - 1, 0, 0, nB));
	EXPECT_TRUE(!imBCC->isValid(0, nC - 1, 0, nB));
	EXPECT_TRUE(!imBCC->isValid(0, 0, nL - 1, nB));
	EXPECT_TRUE(imBCC->isValid(0, 0, 0, nB - 1));
	EXPECT_TRUE(imBCC->isValid(nR - 1, 0, 0, nB - 1));
	EXPECT_TRUE(imBCC->isValid(0, nC - 1, 0, nB - 1));
	EXPECT_TRUE(imBCC->isValid(0, 0, nL - 1, nB - 1));

	// index conversion
	EXPECT_TRUE(imBCC->rclToIndex(0, 0, 0) == 0);
	EXPECT_TRUE(imBCC->rclToIndex(1, 2, 3) == 98);
	EXPECT_TRUE(imBCC->rclToIndex(nR - 1, nC - 1, nL - 1) == N - 1);

	EXPECT_TRUE(imBCC->indexToR(0) == 0);
	EXPECT_TRUE(imBCC->indexToC(0) == 0);
	EXPECT_TRUE(imBCC->indexToL(0) == 0);
	EXPECT_TRUE(imBCC->indexToR(98) == 1);
	EXPECT_TRUE(imBCC->indexToC(98) == 2);
	EXPECT_TRUE(imBCC->indexToL(98) == 3);
	EXPECT_TRUE(imBCC->indexToR(N - 1) == nR - 1);
	EXPECT_TRUE(imBCC->indexToC(N - 1) == nC - 1);
	EXPECT_TRUE(imBCC->indexToL(N - 1) == nL - 1);

	delete imBCC;
}

TEST(CImageBCC, coordinates) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = 0;
	}
	CImagetypeBCC *imBCC = new CImagetypeBCC(data, nR, nC, nL, nB);
	double volume = 2.5;
	CImagetypeBCC *imBCC2 = new CImagetypeBCC(data, nR, nC, nL, nB, volume);
	double factor = cbrt(volume);

	CImagetypeBCC *imBCC1C1L = new CImagetypeBCC(data, N, 1, 1, 1);
	CImagetypeBCC *imBCC1R1L = new CImagetypeBCC(data, 1, N, 1, 1);
	CImagetypeBCC *imBCC1R1C = new CImagetypeBCC(data, 1, 1, N, 1);
	int n1 = 15, n2 = 14;
	CImagetypeBCC *imBCCRC = new CImagetypeBCC(data, n1, n2, 1, 1);
	CImagetypeBCC *imBCCRL = new CImagetypeBCC(data, n1, 1, n2, 1);
	CImagetypeBCC *imBCCCL = new CImagetypeBCC(data, 1, n1, n2, 1);
	vector<double> coordinates;

	// spel coordinates
	EXPECT_NEAR(imBCC->indexToX(0), BCCOFFSET, EPSILONT);
	EXPECT_NEAR(imBCC->indexToY(0), BCCOFFSET, EPSILONT);
	EXPECT_NEAR(imBCC->indexToZ(0), BCCOFFSET, EPSILONT);
	EXPECT_NEAR(imBCC->indexToX(82), BCCOFFSET + 4*BCCSQFACEDISTANCE, EPSILONT);
	EXPECT_NEAR(imBCC->indexToY(82), BCCOFFSET + 3*BCCSQFACEDISTANCE, EPSILONT);
	EXPECT_NEAR(imBCC->indexToZ(82), BCCOFFSET + BCCSQFACEDISTANCE, EPSILONT);
	EXPECT_NEAR(imBCC->indexToX(112), BCCOFFSET + 9*BCCOFFSET, EPSILONT);
	EXPECT_NEAR(imBCC->indexToY(112), BCCOFFSET + 7*BCCOFFSET, EPSILONT);
	EXPECT_NEAR(imBCC->indexToZ(112), BCCOFFSET + 3*BCCOFFSET, EPSILONT);
	EXPECT_NEAR(imBCC->indexToX(209), BCCOFFSET + 5*BCCSQFACEDISTANCE, EPSILONT);
	EXPECT_NEAR(imBCC->indexToY(209), BCCOFFSET + 4*BCCSQFACEDISTANCE, EPSILONT); // !!!!!!
	EXPECT_NEAR(imBCC->indexToZ(209), BCCOFFSET + 3*BCCSQFACEDISTANCE, EPSILONT);

	imBCC->getCoordinates(0,coordinates);
	EXPECT_NEAR(coordinates[0], BCCOFFSET, EPSILONT);
	EXPECT_NEAR(coordinates[1], BCCOFFSET, EPSILONT);
	EXPECT_NEAR(coordinates[2], BCCOFFSET, EPSILONT);
	imBCC->getCoordinates(82,coordinates);
	EXPECT_NEAR(coordinates[0], BCCOFFSET + 4*BCCSQFACEDISTANCE, EPSILONT);
	EXPECT_NEAR(coordinates[1], BCCOFFSET + 3*BCCSQFACEDISTANCE, EPSILONT);
	EXPECT_NEAR(coordinates[2], BCCOFFSET + BCCSQFACEDISTANCE, EPSILONT);
	imBCC->getCoordinates(112,coordinates);
	EXPECT_NEAR(coordinates[0], BCCOFFSET + 9*BCCOFFSET, EPSILONT);
	EXPECT_NEAR(coordinates[1], BCCOFFSET + 7*BCCOFFSET, EPSILONT);
	EXPECT_NEAR(coordinates[2], BCCOFFSET + 3*BCCOFFSET, EPSILONT);
	imBCC->getCoordinates(209,coordinates);
	EXPECT_NEAR(coordinates[0], BCCOFFSET + 5*BCCSQFACEDISTANCE, EPSILONT);
	EXPECT_NEAR(coordinates[1], BCCOFFSET + 4*BCCSQFACEDISTANCE, EPSILONT);
	EXPECT_NEAR(coordinates[2], BCCOFFSET + 3*BCCSQFACEDISTANCE, EPSILONT);


	EXPECT_NEAR(imBCC2->indexToX(0), factor * (BCCOFFSET), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToY(0), factor * (BCCOFFSET), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToZ(0), factor * (BCCOFFSET), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToX(82), factor * (BCCOFFSET + 4*BCCSQFACEDISTANCE), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToY(82), factor * (BCCOFFSET + 3*BCCSQFACEDISTANCE), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToZ(82), factor * (BCCOFFSET + BCCSQFACEDISTANCE), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToX(112), factor * (BCCOFFSET + 9*BCCOFFSET), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToY(112), factor * (BCCOFFSET + 7*BCCOFFSET), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToZ(112), factor * (BCCOFFSET + 3*BCCOFFSET), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToX(209), factor * (BCCOFFSET + 5*BCCSQFACEDISTANCE), EPSILONT);
	EXPECT_NEAR(imBCC2->indexToY(209), factor * (BCCOFFSET + 4*BCCSQFACEDISTANCE), EPSILONT); // !!!!!!
	EXPECT_NEAR(imBCC2->indexToZ(209), factor * (BCCOFFSET + 3*BCCSQFACEDISTANCE), EPSILONT);

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
	CImagetypeBCC *imBCC = new CImagetypeBCC(data, nR, nC, nL, nB);
	double volume = 2.5;
	CImagetypeBCC *imBCC2 = new CImagetypeBCC(data, nR, nC, nL, nB, volume);
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
	double right[3] = { BCCSQFACEDISTANCE, 0, 0 };
	double bottom[3] = { 0, BCCSQFACEDISTANCE, 0 };
	double back[3] = { 0, 0, BCCSQFACEDISTANCE };
	double left[3] = { -BCCSQFACEDISTANCE, 0, 0 };
	double top[3] = { 0, -BCCSQFACEDISTANCE, 0 };
	double front[3] = { 0, 0, -BCCSQFACEDISTANCE };
	double ftl[3] = { -BCCOFFSET, -BCCOFFSET, -BCCOFFSET };
	double ftr[3] = { BCCOFFSET, -BCCOFFSET, -BCCOFFSET };
	double fbl[3] = { -BCCOFFSET, BCCOFFSET, -BCCOFFSET };
	double fbr[3] = { BCCOFFSET, BCCOFFSET, -BCCOFFSET };
	double btl[3] = { -BCCOFFSET, -BCCOFFSET, BCCOFFSET };
	double btr[3] = { BCCOFFSET, -BCCOFFSET, BCCOFFSET };
	double bbl[3] = { -BCCOFFSET, BCCOFFSET, BCCOFFSET };
	double bbr[3] = { BCCOFFSET, BCCOFFSET, BCCOFFSET };
	imBCC->euclideanDistanceVector(82, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_TRUE(fabs(dv[i]) < EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 83, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], right[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 88, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bottom[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(22, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], back[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(83, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], left[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(88, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], top[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 22, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], front[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 45, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], ftl[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 46, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], ftr[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 51, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fbl[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 52, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fbr[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 105, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], btl[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 106, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], btr[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 111, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bbl[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 112, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bbr[i], EPSILONT);
	}

	double right2[3] = { factor * BCCSQFACEDISTANCE, 0, 0 };
	double bottom2[3] = { 0, factor * BCCSQFACEDISTANCE, 0 };
	double back2[3] = { 0, 0, factor * BCCSQFACEDISTANCE };
	double left2[3] = { -factor * BCCSQFACEDISTANCE, 0, 0 };
	double top2[3] = { 0, -factor * BCCSQFACEDISTANCE, 0 };
	double front2[3] = { 0, 0, -factor * BCCSQFACEDISTANCE };
	double ftl2[3] = { -factor * BCCOFFSET, -factor * BCCOFFSET, -factor * BCCOFFSET };
	double ftr2[3] = { factor * BCCOFFSET, -factor * BCCOFFSET, -factor * BCCOFFSET };
	double fbl2[3] = { -factor * BCCOFFSET, factor * BCCOFFSET, -factor * BCCOFFSET };
	double fbr2[3] = { factor * BCCOFFSET, factor * BCCOFFSET, -factor * BCCOFFSET };
	double btl2[3] = { -factor * BCCOFFSET, -factor * BCCOFFSET, factor * BCCOFFSET };
	double btr2[3] = { factor * BCCOFFSET, -factor * BCCOFFSET, factor * BCCOFFSET };
	double bbl2[3] = { -factor * BCCOFFSET, factor * BCCOFFSET, factor * BCCOFFSET };
	double bbr2[3] = { factor * BCCOFFSET, factor * BCCOFFSET, factor * BCCOFFSET };
	imBCC2->euclideanDistanceVector(82, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_TRUE(fabs(dv[i]) < EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 83, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], right2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 88, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bottom2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(22, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], back2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(83, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], left2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(88, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], top2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 22, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], front2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 45, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], ftl2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 46, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], ftr2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 51, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fbl2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 52, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fbr2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 105, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], btl2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 106, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], btr2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 111, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bbl2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 112, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bbr2[i], EPSILONT);
	}

	delete imBCC;
	delete imBCC2;
}

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
	CImagetypeBCC *imBCC = new CImagetypeBCC(data, nR, nC, nL, nB);

	vector<Neighbor> neighbors;
	int nNeighbors, returnedNeighbors, correctNNeighbors;
	// neighbor indices
	// {tlf,trf,bolf,borf,tlba,trba,bolba,borba,   t,f,l,ba,r,bo}
	int BCC8EL[8] = { 45, 46, 51, 52, 105, 106, 111, 112 }; // {31,32,36,37,81,82,86,87};
	int BCC8OL[8] = { 82, 83, 88, 89, 142, 143, 148, 149 }; // {12,13,17,18,62,63,67,68};
	int BCC14EL[14] = { 45, 46, 51, 52, 105, 106, 111, 112, 76, 22, 81, 142, 83, 88 }; // {31,32,36,37,81,82,86,87,57,12,61,112,63,67};
	int BCC14OL[14] = { 82, 83, 88, 89, 142, 143, 148, 149, 106, 52, 111, 172, 113, 118 }; // {12,13,17,18,62,63,67,68,32,36,87,38,42};

	// 8 neighbors
	nNeighbors = 8;
	correctNNeighbors = 8;
	imBCC->getNeighbors(3, 4, 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_TRUE(neighbors[i].getIndex() == BCC8EL[i]);
	}
	imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 2), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_TRUE(neighbors[i].getIndex() == BCC8EL[i]);
	}
	imBCC->getNeighbors(3, 4, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_TRUE(neighbors[i].getIndex() == BCC8OL[i]);
	}
	imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_TRUE(neighbors[i].getIndex() == BCC8OL[i]);
	}
	correctNNeighbors = 1;
	imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	correctNNeighbors = 2;
	imBCC->getNeighbors(4, 0, 6, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	correctNNeighbors = 4;
	imBCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	imBCC->getNeighbors(0, 5, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	imBCC->getNeighbors(4, 0, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);

	// 14 neighbors
	nNeighbors = 14;
	correctNNeighbors = 14;
	imBCC->getNeighbors(3, 4, 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_TRUE(neighbors[i].getIndex() == BCC14EL[i]);
	}
	imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 2), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_TRUE(neighbors[i].getIndex() == BCC14EL[i]);
	}
	imBCC->getNeighbors(3, 4, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_TRUE(neighbors[i].getIndex() == BCC14OL[i]);
	}
	imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_TRUE(neighbors[i].getIndex() == BCC14OL[i]);
	}
	correctNNeighbors = 4;
	imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	correctNNeighbors = 5;
	imBCC->getNeighbors(4, 0, 6, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	correctNNeighbors = 7;
	imBCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	imBCC->getNeighbors(0, 5, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);
	imBCC->getNeighbors(4, 0, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_TRUE(returnedNeighbors == correctNNeighbors);

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

TEST(CImageBCC, segmentations){

 }

TEST(CImageBCC, distanceTransforms){

}

#endif