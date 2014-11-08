#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "exception.h"
#include <cmath>
#include <vector>

using namespace CImage;

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