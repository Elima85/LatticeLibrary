#include "gtest/gtest.h"
#include "image.h"
#include "intensityworkset.h"
#include "seededdistancemeasure.h"
#include "seededdistancetransform.h"
#include "approximateminimumbarrierdistance.h"
#include "fuzzyconnectedness.h"
#include "fuzzydistance.h"
#include "geodesicdistance.h"
#include "minimumbarrierdistance.h"
#include "seed.h"
#include <vector>
#include "defs.h"

using namespace LatticeLib;

TEST(SeededDistanceTransform, ApproximateMinimumBarrierDistance) {

    SeededDistanceTransform seededDistanceTransform;
    PNorm<double> norm(2);
    ApproximateMinimumBarrierDistance<double> distanceMeasure(norm);

}

TEST(SeededDistanceTransform, FuzzyConnectedness) {

    SeededDistanceTransform seededDistanceTransform;
    PNorm<double> norm(2);
    FuzzyConnectedness<double> distanceMeasure(norm);

}

TEST(SeededDistanceTransform, FuzzyDistance) {

    SeededDistanceTransform seededDistanceTransform;
    PNorm<double> norm(2);
    FuzzyDistance<double> distanceMeasure(norm);

}

TEST(SeededDistanceTransform, GeodesicDistance) {

    SeededDistanceTransform seededDistanceTransform;
    GeodesicDistance<double> distanceMeasure;

}

TEST(SeededDistanceTransform, MinimumBarrierDistance) {

    SeededDistanceTransform seededDistanceTransform;
    MinimumBarrierDistance<double> distanceMeasure;

}

//TEST(SeededDistanceTransform, ApproximateMBDBBUint8) {

/*
    int nRows = 321, nColumns = 481, nLayers = 1;
    int nElements = nRows * nColumns * nLayers;

    // get seeds
    char seedFile[] = "seeds.bin";
    double *seedData = readVolume(seedFile, nElements);
    vector<Seed> seeds;
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        if (seedData[elementIndex] > EPSILONT) {
            seeds.push_back(Seed(elementIndex, round(seedData[elementIndex])));
        }
    }
    uint8 *seedDataUint8 = new uint8[nElements];
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        seedDataUint8[elementIndex] = uint8(seedData[elementIndex]);
    }
    std::cout << "#seeds: " << seeds.size() << std::endl;

    // make images
    double scaleFactor = 1;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    // read uint8 image
    char flowersRGBFile[] = "flowers.bin";
    double *flowersRGBDoubleData = readVolume(flowersRGBFile, 3 * nElements);
    uint8 *flowersRGBData = new uint8[3 * nElements];
    for (int elementIndex = 0; elementIndex < 3 * nElements; elementIndex++) {
        flowersRGBData[elementIndex] = uint8(flowersRGBDoubleData[elementIndex]);
    }

    uint8* flowersRData = flowersRGBData;
    uint8* flowersGData = flowersRGBData + nElements;
    uint8* flowersBData = flowersRGBData + 2 * nElements;

    IntensityImage<uint8> flowersRGB(flowersRGBData, lattice, 3, 0, 255);
    IntensityImage<uint8> flowersR(flowersRData, lattice, 1, 0, 255);
    IntensityImage<uint8> flowersG(flowersGData, lattice, 1, 0, 255);
    IntensityImage<uint8> flowersB(flowersBData, lattice, 1, 0, 255);

    PNorm norm(2);
    PNorm *normPointer = new PNorm(2);*/

    // Old method
/*    uint8 *segmentationRGB = new uint8[3 * nElements];
    uint8 *segmentationR = new uint8[3 * nElements];
    uint8 *segmentationG = new uint8[3 * nElements];
    uint8 *segmentationB = new uint8[3 * nElements];
    double *dtRGB = new double[3 * nElements];
    double *dtR = new double[3 * nElements];
    double *dtG = new double[3 * nElements];
    double *dtB = new double[3 * nElements];
    approximateMinimumBarrierBoundingBox(&flowersRGB, seedDataUint8, normPointer, 26, segmentationRGB, dtRGB);
    approximateMinimumBarrierBoundingBox(&flowersR, seedDataUint8, normPointer, 26, segmentationR, dtR);
    approximateMinimumBarrierBoundingBox(&flowersG, seedDataUint8, normPointer, 26, segmentationG, dtG);
    approximateMinimumBarrierBoundingBox(&flowersB, seedDataUint8, normPointer, 26, segmentationB, dtB);
    char flowersRGBdtOld[] = "flowersRGB_AMBDBBdtOld_uint8_2norm.bin";
    char flowersRdtOld[] = "flowersR_AMBDBBdtOld_uint8_2norm.bin";
    char flowersGdtOld[] = "flowersG_AMBDBBdtOld_uint8_2norm.bin";
    char flowersBdtOld[] = "flowersB_AMBDBBdtOld_uint8_2norm.bin";
    char flowersRGBsegmOld[] = "flowersRGB_AMBDBBsegmOld_uint8_2norm.bin";
    char flowersRsegmOld[] = "flowersR_AMBDBBsegmOld_uint8_2norm.bin";
    char flowersGsegmOld[] = "flowersG_AMBDBBsegmOld_uint8_2norm.bin";
    char flowersBsegmOld[] = "flowersB_AMBDBBsegmOld_uint8_2norm.bin";
    writeVolume(flowersRGBdtOld, dtRGB, nElements);
    writeVolume(flowersRdtOld, dtR, nElements);
    writeVolume(flowersGdtOld, dtG, nElements);
    writeVolume(flowersBdtOld, dtB, nElements);
    double *tmp = new double[nElements];
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        tmp[elementIndex] = double(segmentationRGB[elementIndex]);
    }
    writeVolume(flowersRGBsegmOld, tmp, nElements);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        tmp[elementIndex] = double(segmentationR[elementIndex]);
    }
    writeVolume(flowersRsegmOld, tmp, nElements);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        tmp[elementIndex] = double(segmentationG[elementIndex]);
    }
    writeVolume(flowersGsegmOld, tmp, nElements);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        tmp[elementIndex] = double(segmentationB[elementIndex]);
    }
    writeVolume(flowersBsegmOld, tmp, nElements);
    delete tmp;
    delete dtRGB;
    delete dtR;
    delete dtG;
    delete dtB;
    delete segmentationRGB;
    delete segmentationR;
    delete segmentationG;
    delete segmentationB;
    delete normPointer;*/

    // New method
    /*DistanceImage distanceTransformRGB = approximateMinimumBarrierBoundingBox(flowersRGB, seeds, norm, 26);
    DistanceImage distanceTransformR = approximateMinimumBarrierBoundingBox(flowersR, seeds, norm, 26);
    DistanceImage distanceTransformG = approximateMinimumBarrierBoundingBox(flowersG, seeds, norm, 26);
    DistanceImage distanceTransformB = approximateMinimumBarrierBoundingBox(flowersB, seeds, norm, 26);

    char flowersRGBOut[] = "flowersRGB_AMBDBB_uint8_2norm.bin";
    char flowersROut[] = "flowersR_AMBDBB_uint8_2norm.bin";
    char flowersGOut[] = "flowersG_AMBDBB_uint8_2norm.bin";
    char flowersBOut[] = "flowersB_AMBDBB_uint8_2norm.bin";

    writeVolume(flowersRGBOut, distanceTransformRGB.getData(), 2 * nElements);
    writeVolume(flowersROut, distanceTransformR.getData(), 2 * nElements);
    writeVolume(flowersGOut, distanceTransformG.getData(), 2 * nElements);
    writeVolume(flowersBOut, distanceTransformB.getData(), 2 * nElements);

    delete seedData;
    delete flowersRGBDoubleData;
    delete flowersRGBData;*/
//}

