#include "gtest/gtest.h"
#include "seededdistancetransform.h"
#include "intensityimage.h"
#include "distanceimage.h"
#include "filehandling.h"
#include "seed.h"
#include <vector>
#include "defs.h"
#include "cclattice.h"
#include "exception.h"

using namespace LatticeLib;

TEST(SeededDistanceTransform, ApproximateMBDBBUint8) {

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

    // make images
    double scaleFactor = 1;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    // read uint8 image
    char flowersRGBFile[] = "flowers.bin";
    double *flowersRGBDoubleData = readVolume(flowersRGBFile, 3 * nElements);
    for (int elementIndex = 0; elementIndex < 3 * nElements; elementIndex++) {
        flowersRGBDoubleData[elementIndex] = flowersRGBDoubleData[elementIndex];
    }
    std::cout << "read and traversed file data." << std::endl;
    uint8 *flowersRGBData = new uint8[3 * nElements];
    for (int elementIndex = 0; elementIndex < 3 * nElements; elementIndex++) {
        flowersRGBData[elementIndex] = 0;
    }
    std::cout << "allocated and traversed uint8 array." << std::endl;
    for (int elementIndex = 0; elementIndex < 3 * nElements; elementIndex++) {
        flowersRGBData[elementIndex] = uint8(flowersRGBDoubleData[elementIndex]);
    }
    std::cout << "converted data from file." << std::endl;

    uint8* flowersRData = flowersRGBData;
    uint8* flowersGData = flowersRGBData + nElements;
    uint8* flowersBData = flowersRGBData + 2 * nElements;

    IntensityImage<uint8> flowersRGB(flowersRGBData, lattice, 3, 0, 255);
    IntensityImage<uint8> flowersR(flowersRData, lattice, 1, 0, 255);
    IntensityImage<uint8> flowersG(flowersGData, lattice, 1, 0, 255);
    IntensityImage<uint8> flowersB(flowersBData, lattice, 1, 0, 255);

    PNorm norm(2);

    DistanceImage distanceTransformRGB = approximateMinimumBarrierBoundingBox(flowersRGB, seeds, norm, 26);
    DistanceImage distanceTransformR = approximateMinimumBarrierBoundingBox(flowersR, seeds, norm, 26);
    DistanceImage distanceTransformG = approximateMinimumBarrierBoundingBox(flowersG, seeds, norm, 26);
    DistanceImage distanceTransformB = approximateMinimumBarrierBoundingBox(flowersB, seeds, norm, 26);

    char flowersRGBOut[] = "flowersRGB_AMBDBB_uint8_2norm.bin";
    char flowersROut[] = "flowersR_AMBDBB_uint8_2norm.bin";
    char flowersGOut[] = "flowersG_AMBDBB_uint8_2norm.bin";
    char flowersBOut[] = "flowersB_AMBDBB_uint8_2norm.bin";

    writeVolume(flowersRGBOut, distanceTransformRGB.getData(), 3 * nElements);
    writeVolume(flowersROut, distanceTransformR.getData(), nElements);
    writeVolume(flowersGOut, distanceTransformG.getData(), nElements);
    writeVolume(flowersBOut, distanceTransformB.getData(), nElements);

    delete seedData;
    delete flowersRGBDoubleData;
    delete flowersRGBData;
}

