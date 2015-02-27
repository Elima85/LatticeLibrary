#include "gtest/gtest.h"
#include "seededdistancetransform.h"
#include "intensitycimage.h"
#include "distancecimage.h"
#include "filehandling.h"
#include "seed.h"
#include <vector>
#include "defs.h"
#include "cclattice.h"
#include "bcclattice.h"
#include "fcclattice.h"
#include "exception.h"

using namespace CImage;

TEST(SeededDistanceTransform, ApproximateMBDBB) {

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
    delete seedData;
    seedData = NULL;
    std::cout << "extracted seeds." << std::endl;

    // make images
    double scaleFactor = 1;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    char flowersRGBUint8File[] = "flowers.bin";
    double *flowersRGBUint8DoubleData = readVolume(flowersRGBUint8File, 3 * nElements);
    std::cout << "read uint8 file: " << (void*) flowersRGBUint8DoubleData<< std::endl;
    uint8 *flowersRGBUint8Data = new(std::nothrow) uint8(3 * nRows * nColumns * nLayers);
    for (int elementIndex = 0; elementIndex < 3 * nElements; elementIndex++) {
        flowersRGBUint8Data[elementIndex] = uint8(flowersRGBUint8DoubleData[elementIndex]);
    }
    delete flowersRGBUint8DoubleData;
    flowersRGBUint8DoubleData = NULL;

    std::cout << "converted doubles to uint8: " << (void*) flowersRGBUint8Data << std::endl;
    char flowersRGBDoubleFile[] = "flowersDouble.bin";
    double *flowersRGBDoubleData = readVolume(flowersRGBDoubleFile, 3 * nElements);
    std::cout << "read double file: " << (void*) flowersRGBDoubleData << std::endl;
    double *flowersRData = flowersRGBDoubleData;
    std::cout << "initialized red band: " << (void *) flowersRData << std::endl;
    double *flowersGData = flowersRGBDoubleData + nElements;
    std::cout << "initialized green band: " << (void *) flowersGData << std::endl;
    double *flowersBData = flowersRGBDoubleData + 2*nElements;
    std::cout << "initialized blue band: " << (void*) flowersBData << std::endl;
    IntensityCImage<uint8> *flowersRGBUint8 = new IntensityCImage<uint8>(flowersRGBUint8Data,lattice, 3, 0, 255);
    std::cout << "initialized uint8 image: " << (void*) flowersRGBUint8 << std::endl;
    IntensityCImage<double> *flowersRGBDouble = new IntensityCImage<double>(flowersRGBDoubleData, lattice, 3, 0, 1);
    std::cout << "initialized double image: " << (void*) flowersRGBDouble << std::endl;
    IntensityCImage<double> *flowersRDouble = new IntensityCImage<double>(flowersRData, lattice, 1, 0, 1);
    std::cout << "initialized red image: " << (void*) flowersRDouble << std::endl;
    IntensityCImage<double> *flowersGDouble = new IntensityCImage<double>(flowersGData, lattice, 1, 0, 1);
    std::cout << "initialized green image" << (void*) flowersGDouble << std::endl;
    IntensityCImage<double> *flowersBDouble = new IntensityCImage<double>(flowersBData, lattice, 1, 0, 1);
    std::cout << "initialized blue image" << (void*) flowersBDouble << std::endl;


    // segment


    // save image

    delete flowersRGBUint8;
    delete flowersRGBDouble;
    delete flowersRDouble;
    delete flowersGDouble;
    delete flowersBDouble;
    delete flowersRGBDoubleData;
    delete flowersRGBUint8Data;
    std::cout << "end of seededdistancetransform.h" << std::endl;

}

