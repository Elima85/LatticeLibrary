#ifndef IMAGEFCCTEST
#define IMAGEFCCTEST

#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageFCC.h"
#include "exception.h"
#include "label.h"
#include <cmath>
#include <vector>



using namespace CImage;

/**
 * Tests type CImagetypeFCC aka CImageFCC<uint8>.
 */

TEST(CImageFCC, constructor) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = i;
	}

	// constructor
	CImagetypeFCC *imFCC = new CImagetypeFCC(data, nR, nC, nL, nB);
	EXPECT_TRUE(imFCC);

	// getters
	uint8* imdata = imFCC->getData();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < nB; j++) {
			EXPECT_TRUE(imdata[i] == data[i]);
		}
	}

	EXPECT_TRUE(imFCC->getNElements() == N);
	EXPECT_TRUE(imFCC->getNElements() != N + 1);

	EXPECT_TRUE(imFCC->getNColumns() == nC);
	EXPECT_TRUE(imFCC->getNColumns() != nC + 1);

	EXPECT_TRUE(imFCC->getNRows() == nR);
	EXPECT_TRUE(imFCC->getNRows() != nR + 1);

	EXPECT_TRUE(imFCC->getNLayers() == nL);
	EXPECT_TRUE(imFCC->getNLayers() != nL + 1);

	EXPECT_TRUE(imFCC->getNBands() == nB);
	EXPECT_TRUE(imFCC->getNBands() != nB + 1);

	// validity of elements
	EXPECT_TRUE(!imFCC->isValid(-1));
	EXPECT_TRUE(imFCC->isValid(0));
	EXPECT_TRUE(imFCC->isValid(N - 1));
	EXPECT_TRUE(!imFCC->isValid(N));

	EXPECT_TRUE(!imFCC->isValid(0, -1));
	EXPECT_TRUE(!imFCC->isValid(N - 1, -1));
	EXPECT_TRUE(!imFCC->isValid(-1, 0));
	EXPECT_TRUE(imFCC->isValid(0, 0));
	EXPECT_TRUE(imFCC->isValid(N - 1, 0));
	EXPECT_TRUE(!imFCC->isValid(N, 0));
	EXPECT_TRUE(imFCC->isValid(0, nB - 1));
	EXPECT_TRUE(imFCC->isValid(N - 1, nB - 1));
	EXPECT_TRUE(!imFCC->isValid(0, nB));
	EXPECT_TRUE(!imFCC->isValid(N - 1, nB));

	EXPECT_TRUE(!imFCC->isValid(-1, 0, 0));
	EXPECT_TRUE(!imFCC->isValid(0, -1, 0));
	EXPECT_TRUE(!imFCC->isValid(0, 0, -1));
	EXPECT_TRUE(imFCC->isValid(0, 0, 0));
	EXPECT_TRUE(imFCC->isValid(nR - 1, 0, 0));
	EXPECT_TRUE(imFCC->isValid(0, nC - 1, 0));
	EXPECT_TRUE(imFCC->isValid(0, 0, nL - 1));
	EXPECT_TRUE(!imFCC->isValid(nR, 0, 0));
	EXPECT_TRUE(!imFCC->isValid(0, nC, 0));
	EXPECT_TRUE(!imFCC->isValid(0, 0, nL));

	EXPECT_TRUE(!imFCC->isValid(0, 0, 0, -1));
	EXPECT_TRUE(!imFCC->isValid(nR - 1, 0, 0, -1));
	EXPECT_TRUE(!imFCC->isValid(0, nC - 1, 0, -1));
	EXPECT_TRUE(!imFCC->isValid(0, 0, nL - 1, -1));
	EXPECT_TRUE(!imFCC->isValid(0, 0, 0, nB));
	EXPECT_TRUE(!imFCC->isValid(nR - 1, 0, 0, nB));
	EXPECT_TRUE(!imFCC->isValid(0, nC - 1, 0, nB));
	EXPECT_TRUE(!imFCC->isValid(0, 0, nL - 1, nB));
	EXPECT_TRUE(imFCC->isValid(0, 0, 0, nB - 1));
	EXPECT_TRUE(imFCC->isValid(nR - 1, 0, 0, nB - 1));
	EXPECT_TRUE(imFCC->isValid(0, nC - 1, 0, nB - 1));
	EXPECT_TRUE(imFCC->isValid(0, 0, nL - 1, nB - 1));

	// index conversion
	EXPECT_TRUE(imFCC->rclToIndex(0, 0, 0) == 0);
	EXPECT_TRUE(imFCC->rclToIndex(1, 2, 3) == 98);
	EXPECT_TRUE(imFCC->rclToIndex(nR - 1, nC - 1, nL - 1) == N - 1);

	EXPECT_TRUE(imFCC->indexToR(0) == 0);
	EXPECT_TRUE(imFCC->indexToC(0) == 0);
	EXPECT_TRUE(imFCC->indexToL(0) == 0);
	EXPECT_TRUE(imFCC->indexToR(98) == 1);
	EXPECT_TRUE(imFCC->indexToC(98) == 2);
	EXPECT_TRUE(imFCC->indexToL(98) == 3);
	EXPECT_TRUE(imFCC->indexToR(N - 1) == nR - 1);
	EXPECT_TRUE(imFCC->indexToC(N - 1) == nC - 1);
	EXPECT_TRUE(imFCC->indexToL(N - 1) == nL - 1);

	delete imFCC;
}

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
	EXPECT_NEAR(imFCC->indexToX(135), FCCOFFSET + 6*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToY(135), FCCOFFSET + FCCPOINTDISTANCE, EPSILONT);
	EXPECT_NEAR(imFCC->indexToZ(135), FCCOFFSET + 2*FCCPOINTDISTANCE, EPSILONT);
	EXPECT_NEAR(imFCC->indexToX(80), FCCOFFSET + 5*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToY(80), FCCOFFSET + 3*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToZ(80), FCCOFFSET + 2*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToX(105), FCCOFFSET + 7*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToY(105), FCCOFFSET + 2*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToZ(105), FCCOFFSET + 3*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToX(110), FCCOFFSET + 4*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToY(110), FCCOFFSET + 3*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToZ(110), FCCOFFSET + 3*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToX(209), FCCOFFSET + 10*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToY(209), FCCOFFSET + 4*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC->indexToZ(209), FCCOFFSET + 6*FCCOFFSET, EPSILONT);

	imFCC->getCoordinates(0,coordinates);
	EXPECT_NEAR(coordinates[0], FCCOFFSET, EPSILONT);
	EXPECT_NEAR(coordinates[1], FCCOFFSET, EPSILONT);
	EXPECT_NEAR(coordinates[2], FCCOFFSET, EPSILONT);
	imFCC->getCoordinates(135,coordinates);
	EXPECT_NEAR(coordinates[0], FCCOFFSET + 6*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(coordinates[1], FCCOFFSET + FCCPOINTDISTANCE, EPSILONT);
	EXPECT_NEAR(coordinates[2], FCCOFFSET + 2*FCCPOINTDISTANCE, EPSILONT);
	imFCC->getCoordinates(209,coordinates);
	EXPECT_NEAR(coordinates[0], FCCOFFSET + 10*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(coordinates[1], FCCOFFSET + 4*FCCOFFSET, EPSILONT);
	EXPECT_NEAR(coordinates[2], FCCOFFSET + 6*FCCOFFSET, EPSILONT);

	EXPECT_NEAR(imFCC2->indexToX(0), factor * FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC2->indexToY(0), factor * FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC2->indexToZ(0), factor * FCCOFFSET, EPSILONT);
	EXPECT_NEAR(imFCC2->indexToX(135), factor * (FCCOFFSET + 6*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToY(135), factor * (FCCOFFSET + FCCPOINTDISTANCE), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToZ(135), factor * (FCCOFFSET + 2*FCCPOINTDISTANCE), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToX(80), factor * (FCCOFFSET + 5*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToY(80), factor * (FCCOFFSET + 3*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToZ(80), factor * (FCCOFFSET + 2*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToX(105), factor * (FCCOFFSET + 7*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToY(105), factor * (FCCOFFSET + 2*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToZ(105), factor * (FCCOFFSET + 3*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToX(110), factor * (FCCOFFSET + 4*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToY(110), factor * (FCCOFFSET + 3*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToZ(110), factor * (FCCOFFSET + 3*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToX(209), factor * (FCCOFFSET + 10*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToY(209), factor * (FCCOFFSET + 4*FCCOFFSET), EPSILONT);
	EXPECT_NEAR(imFCC2->indexToZ(209), factor * (FCCOFFSET + 6*FCCOFFSET), EPSILONT);

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
	double ft[3] = { 0, -FCCOFFSET, -FCCOFFSET };
	double fr[3] = { FCCOFFSET, 0, -FCCOFFSET };
	double fb[3] = { 0, FCCOFFSET, -FCCOFFSET };
	double fl[3] = { -FCCOFFSET, 0, -FCCOFFSET };
	double mtr[3] = { FCCOFFSET, -FCCOFFSET, 0 };
	double mbr[3] = { FCCOFFSET, FCCOFFSET, 0 };
	double mbl[3] = { -FCCOFFSET, FCCOFFSET, 0 };
	double mtl[3] = { -FCCOFFSET, -FCCOFFSET, 0 };
	double bt[3] = { 0, -FCCOFFSET, FCCOFFSET };
	double br[3] = { FCCOFFSET, 0, FCCOFFSET };
	double bb[3] = { 0, FCCOFFSET, FCCOFFSET };
	double bl[3] = { -FCCOFFSET, 0, FCCOFFSET };
	double front[3] = { 0, 0, -FCCPOINTDISTANCE };
	double top[3] = { 0, -FCCPOINTDISTANCE, 0 };
	double right[3] = { FCCPOINTDISTANCE, 0, 0 };
	double bottom[3] = { 0, FCCPOINTDISTANCE, 0 };
	double left[3] = { -FCCPOINTDISTANCE, 0, 0 };
	double back[3] = { 0, 0, FCCPOINTDISTANCE };
	imFCC->euclideanDistanceVector(82, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_TRUE(fabs(dv[i]) < EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 45, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], front[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 93, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], top[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 106, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], right[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 117, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bottom[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 104, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], left[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 165, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], back[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 69, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], ft[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 76, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fr[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 81, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fb[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 75, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fl[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 100, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], mtr[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 112, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], mbr[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 111, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], mbl[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 99, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], mtl[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 129, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bt[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 136, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], br[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 141, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bb[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 135, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bl[i], EPSILONT);
	}

	double ft2[3] = { 0, -factor * FCCOFFSET, -factor * FCCOFFSET };
	double fr2[3] = { factor * FCCOFFSET, 0, -factor * FCCOFFSET };
	double fb2[3] = { 0, factor * FCCOFFSET, -factor * FCCOFFSET };
	double fl2[3] = { -factor * FCCOFFSET, 0, -factor * FCCOFFSET };
	double mtr2[3] = { factor * FCCOFFSET, -factor * FCCOFFSET, 0 };
	double mbr2[3] = { factor * FCCOFFSET, factor * FCCOFFSET, 0 };
	double mbl2[3] = { -factor * FCCOFFSET, factor * FCCOFFSET, 0 };
	double mtl2[3] = { -factor * FCCOFFSET, -factor * FCCOFFSET, 0 };
	double bt2[3] = { 0, -factor * FCCOFFSET, factor * FCCOFFSET };
	double br2[3] = { factor * FCCOFFSET, 0, factor * FCCOFFSET };
	double bb2[3] = { 0, factor * FCCOFFSET, factor * FCCOFFSET };
	double bl2[3] = { -factor * FCCOFFSET, 0, factor * FCCOFFSET };
	double front2[3] = { 0, 0, -factor * FCCPOINTDISTANCE };
	double top2[3] = { 0, -factor * FCCPOINTDISTANCE, 0 };
	double right2[3] = { factor * FCCPOINTDISTANCE, 0, 0 };
	double bottom2[3] = { 0, factor * FCCPOINTDISTANCE, 0 };
	double left2[3] = { -factor * FCCPOINTDISTANCE, 0, 0 };
	double back2[3] = { 0, 0, factor * FCCPOINTDISTANCE };
	imFCC2->euclideanDistanceVector(82, 82, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_TRUE(fabs(dv[i]) < EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 45, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], front2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 93, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], top2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 106, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], right2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 117, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bottom2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 104, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], left2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 165, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], back2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 69, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], ft2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 76, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fr2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 81, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fb2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 75, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], fl2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 100, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], mtr2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 112, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], mbr2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 111, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], mbl2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 99, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], mtl2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 129, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bt2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 136, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], br2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 141, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bb2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 135, dv);
	for (int i = 0; i < 3; i++) {
		EXPECT_NEAR(dv[i], bl2[i], EPSILONT);
	}

	delete imFCC;
	delete imFCC2;

}

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
	int FCC12ELER[12] = { 99, 128, 159, 129, 104, 164, 165, 105, 111, 140, 171, 141 }; // {31,55,81,56,35,85,86,36,41,65,91,66};
	int FCC12ELOR[12] = { 44, 74, 104, 75, 50, 110, 111, 51, 56, 86, 116, 87 }; // {37,62,87,63,42,92,93,43,47,72,97,73};
	int FCC12OLER[12] =	{ 69, 99, 129, 100, 75, 135, 136, 76, 81, 111, 141, 112 }; // {1,25,51,26,5,55,56,6,11,35,61,36};
	int FCC12OLOR[12] = { 74, 103, 134, 104, 79, 139, 140, 80, 86, 115, 146, 116 }; // {6,31,56,32,11,61,62,12,16,41,66,42};
	int FCC18ELER[18] = { 99, 128, 159, 129, 104, 164, 165, 105, 111, 140, 171, 141, 123, 75, 134, 195, 136, 147 }; // {31,55,81,56,35,85,86,36,41,65,91,66,51,11,60,111,62,71};
	int FCC18ELOR[18] = { 44, 74, 104, 75, 50, 110, 111, 51, 56, 86, 116, 87, 68, 20, 79, 140, 81 }; // bottom missing // {37,62,87,63,42,92,93,43,47,72,97,73,57,17,66,117,68}; // bottom missing
	int FCC18OLER[18] = { 69, 99, 129, 100, 75, 135, 136, 76, 81, 111, 141, 112, 93, 45, 104, 165, 106, 117 }; // {1,25,51,26,5,55,56,6,11,35,61,36,30,81,32,41}; // top and front missing
	int FCC18OLOR[18] = { 74, 103, 134, 104, 79, 139, 140, 80, 86, 115, 146, 116, 98, 50, 109, 170, 111 }; // bottom missing // {6,31,56,32,11,61,62,12,16,41,66,42,26,35,86,37,46}; // front missing

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
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC12ELER[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 4), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC12ELER[i]);
	}

	imFCC->getNeighbors(3, 2, 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC12ELOR[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 2), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC12ELOR[i]);
	}

	imFCC->getNeighbors(2, 3, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC12OLER[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC12OLER[i]);
	}

	imFCC->getNeighbors(3, 2, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC12OLOR[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC12OLOR[i]);
	}

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
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC18ELOR[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 2), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC18ELOR[i]);
	}

	imFCC->getNeighbors(3, 2, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC18OLOR[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC18OLOR[i]);
	}

	correctNNeighbors = 18;
	imFCC->getNeighbors(2, 3, 4, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC18ELER[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 4), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC18ELER[i]);
	}

	imFCC->getNeighbors(2, 3, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC18OLER[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	EXPECT_EQ(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		EXPECT_EQ(neighbors[i].getIndex(), FCC18OLER[i]);
	}

	// Exceptions
	nNeighbors = 12;
	EXPECT_THROW(imFCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(0, nC, 0, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(0, -1, 0, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(0, 0, nL, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(0, 0, -1, nNeighbors, neighbors),	outsideImageException);
	nNeighbors = 18;
	EXPECT_THROW(imFCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(0, nC, 0, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(0, -1, 0, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(0, 0, nL, nNeighbors, neighbors),	outsideImageException);
	EXPECT_THROW(imFCC->getNeighbors(0, 0, -1, nNeighbors, neighbors),	outsideImageException);
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

#endif