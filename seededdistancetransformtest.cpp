#include "gtest/gtest.h"
#include "image.h"
#include "cclattice.h"
#include "intensityworkset.h"
#include "seededdistancemeasure.h"
#include "seededdistancetransform.h"
#include "approximateminimumbarrierdistance.h"
#include "fuzzyconnectedness.h"
#include "fuzzydistance.h"
#include "geodesicdistance.h"
#include "minimumbarrierdistance.h"
#include "filehandling.h"
#include "seed.h"
#include <vector>
#include "defs.h"

using namespace LatticeLib;

#ifdef AMBDTEST
TEST(SeededDistanceTransform, ApproximateMinimumBarrierDistanceRGB) {

    int nRows = 321;
    int nColumns = 481;
    int nLayers = 1;
    int nElements = nRows * nColumns * nLayers;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    int nBands = 3;
    int nTotal = nElements * nBands;

    char inputFilename[] = "flowersRGB.bin";
    char *inputFilenamePointer = inputFilename;
    double *imageData = readVolume(inputFilenamePointer, nTotal);
    Image<double> inputImage(imageData, lattice, nBands);

    double distanceTransformData[nTotal];
    Image<double> distanceTransformImage(distanceTransformData, lattice, nBands);
    int rootData[nTotal];
    Image<int> rootImage(rootData, lattice, nBands);

    vector<vector<Seed> > seeds;
    vector<Seed> tmp;
    // background
    tmp.clear();
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, 0, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, nColumns - 1, 0), 0));
    }
    for (int columnIndex = 0; columnIndex < nRows; columnIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(0, columnIndex, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(nRows - 1, columnIndex, 0), 0));
    }
    seeds.push_back(tmp);
    // center
    tmp.clear();
    for (int rowIndex = 136; rowIndex < 148; rowIndex++) {
        for (int columnIndex = 112; columnIndex < 166; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    for (int rowIndex = 150; rowIndex < 204; rowIndex++) {
        for (int columnIndex = 298; columnIndex < 308; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    seeds.push_back(tmp);
    // petals 1: rows 82-87, 189-194, columns 79-84, 177-182
    tmp.clear();
    for (int rowIndex = 82; rowIndex < 87; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 87; rowIndex < 189; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 84; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 177; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 189; rowIndex < 194; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    // petals 2: rows 122-127, 230-235, columns 253-258, 366-371
    for (int rowIndex = 122; rowIndex < 127; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 127; rowIndex < 230; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 258; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 366; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 230; rowIndex < 235; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    seeds.push_back(tmp);

    PNorm<double> norm(2);
    ApproximateMinimumBarrierDistance<double> distanceMeasure(norm);
    SeededDistanceTransform seededDistanceTransform;
    seededDistanceTransform.apply(inputImage, seeds, distanceMeasure, 26, distanceTransformImage, rootImage);
    char newFilename[] = "AMBDflowersRGB26.bin";
    writeVolume(newFilename, distanceTransformImage.getData(), nTotal);

    delete imageData;
}
#endif

#ifdef FCTEST
TEST(SeededDistanceTransform, FuzzyConnectednessRGB) {

    int nRows = 321;
    int nColumns = 481;
    int nLayers = 1;
    int nElements = nRows * nColumns * nLayers;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    int nBands = 3;
    int nTotal = nElements * nBands;

    char inputFilename[] = "flowersRGB.bin";
    char *inputFilenamePointer = inputFilename;
    double *imageData = readVolume(inputFilenamePointer, nTotal);
    Image<double> inputImage(imageData, lattice, nBands);

    double distanceTransformData[nTotal];
    Image<double> distanceTransformImage(distanceTransformData, lattice, nBands);
    int rootData[nTotal];
    Image<int> rootImage(rootData, lattice, nBands);

    vector<vector<Seed> > seeds;
    vector<Seed> tmp;
    // background
    tmp.clear();
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, 0, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, nColumns - 1, 0), 0));
    }
    for (int columnIndex = 0; columnIndex < nRows; columnIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(0, columnIndex, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(nRows - 1, columnIndex, 0), 0));
    }
    seeds.push_back(tmp);
    // center
    tmp.clear();
    for (int rowIndex = 136; rowIndex < 148; rowIndex++) {
        for (int columnIndex = 112; columnIndex < 166; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    for (int rowIndex = 150; rowIndex < 204; rowIndex++) {
        for (int columnIndex = 298; columnIndex < 308; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    seeds.push_back(tmp);
    // petals 1: rows 82-87, 189-194, columns 79-84, 177-182
    tmp.clear();
    for (int rowIndex = 82; rowIndex < 87; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 87; rowIndex < 189; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 84; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 177; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 189; rowIndex < 194; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    // petals 2: rows 122-127, 230-235, columns 253-258, 366-371
    for (int rowIndex = 122; rowIndex < 127; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 127; rowIndex < 230; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 258; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 366; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 230; rowIndex < 235; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    seeds.push_back(tmp);

    SeededDistanceTransform seededDistanceTransform;
    PNorm<double> norm(2);
    FuzzyConnectedness<double> distanceMeasure(norm);
    seededDistanceTransform.apply(inputImage, seeds, distanceMeasure, 26, distanceTransformImage, rootImage);
    char newFilename[] = "FCflowersRGB26.bin";
    writeVolume(newFilename, distanceTransformImage.getData(), nTotal);

    delete imageData;

}
#endif

#ifdef FDTEST
TEST(SeededDistanceTransform, FuzzyDistance) {

    int nRows = 321;
    int nColumns = 481;
    int nLayers = 1;
    int nElements = nRows * nColumns * nLayers;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    int nBands = 3;
    int nTotal = nElements * nBands;

    char inputFilename[] = "flowersRGB.bin";
    char *inputFilenamePointer = inputFilename;
    double *imageData = readVolume(inputFilenamePointer, nTotal);
    Image<double> inputImage(imageData, lattice, nBands);

    double distanceTransformData[nTotal];
    Image<double> distanceTransformImage(distanceTransformData, lattice, nBands);
    int rootData[nTotal];
    Image<int> rootImage(rootData, lattice, nBands);

    vector<vector<Seed> > seeds;
    vector<Seed> tmp;
    // background
    tmp.clear();
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, 0, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, nColumns - 1, 0), 0));
    }
    for (int columnIndex = 0; columnIndex < nRows; columnIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(0, columnIndex, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(nRows - 1, columnIndex, 0), 0));
    }
    seeds.push_back(tmp);
    // center
    tmp.clear();
    for (int rowIndex = 136; rowIndex < 148; rowIndex++) {
        for (int columnIndex = 112; columnIndex < 166; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    for (int rowIndex = 150; rowIndex < 204; rowIndex++) {
        for (int columnIndex = 298; columnIndex < 308; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    seeds.push_back(tmp);
    // petals 1: rows 82-87, 189-194, columns 79-84, 177-182
    tmp.clear();
    for (int rowIndex = 82; rowIndex < 87; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 87; rowIndex < 189; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 84; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 177; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 189; rowIndex < 194; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    // petals 2: rows 122-127, 230-235, columns 253-258, 366-371
    for (int rowIndex = 122; rowIndex < 127; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 127; rowIndex < 230; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 258; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 366; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 230; rowIndex < 235; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    seeds.push_back(tmp);

    SeededDistanceTransform seededDistanceTransform;
    PNorm<double> norm(2);
    FuzzyDistance<double> distanceMeasure(norm);
    seededDistanceTransform.apply(inputImage, seeds, distanceMeasure, 26, distanceTransformImage, rootImage);
    char newFilename[] = "FDflowersRGB26.bin";
    writeVolume(newFilename, distanceTransformImage.getData(), nTotal);

    delete imageData;

}
#endif

#ifdef GDTEST
TEST(SeededDistanceTransform, GeodesicDistance) {

    int nRows = 321;
    int nColumns = 481;
    int nLayers = 1;
    int nElements = nRows * nColumns * nLayers;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    int nBands = 3;
    int nTotal = nElements * nBands;

    char inputFilename[] = "flowersRGB.bin";
    char *inputFilenamePointer = inputFilename;
    double *imageData = readVolume(inputFilenamePointer, nTotal);
    Image<double> inputImage(imageData, lattice, nBands);

    double distanceTransformData[nTotal];
    Image<double> distanceTransformImage(distanceTransformData, lattice, nBands);
    int rootData[nTotal];
    Image<int> rootImage(rootData, lattice, nBands);

    vector<vector<Seed> > seeds;
    vector<Seed> tmp;
    // background
    tmp.clear();
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, 0, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, nColumns - 1, 0), 0));
    }
    for (int columnIndex = 0; columnIndex < nRows; columnIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(0, columnIndex, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(nRows - 1, columnIndex, 0), 0));
    }
    seeds.push_back(tmp);
    // center
    tmp.clear();
    for (int rowIndex = 136; rowIndex < 148; rowIndex++) {
        for (int columnIndex = 112; columnIndex < 166; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    for (int rowIndex = 150; rowIndex < 204; rowIndex++) {
        for (int columnIndex = 298; columnIndex < 308; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    seeds.push_back(tmp);
    // petals 1: rows 82-87, 189-194, columns 79-84, 177-182
    tmp.clear();
    for (int rowIndex = 82; rowIndex < 87; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 87; rowIndex < 189; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 84; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 177; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 189; rowIndex < 194; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    // petals 2: rows 122-127, 230-235, columns 253-258, 366-371
    for (int rowIndex = 122; rowIndex < 127; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 127; rowIndex < 230; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 258; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 366; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 230; rowIndex < 235; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    seeds.push_back(tmp);

    SeededDistanceTransform seededDistanceTransform;
    GeodesicDistance<double> distanceMeasure;
    seededDistanceTransform.apply(inputImage, seeds, distanceMeasure, 26, distanceTransformImage, rootImage);
    char newFilename[] = "GDflowersRGB26.bin";
    writeVolume(newFilename, distanceTransformImage.getData(), nTotal);

    delete imageData;

}
#endif

#define MBDTEST
#ifdef MBDTEST
TEST(SeededDistanceTransform, MinimumBarrierDistance) {

    int nRows = 321;
    int nColumns = 481;
    int nLayers = 1;
    int nElements = nRows * nColumns * nLayers;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    int nBands = 3;
    int nTotal = nElements * nBands;

    char inputFilename[] = "flowersRGB.bin";
    char *inputFilenamePointer = inputFilename;
    double *imageData = readVolume(inputFilenamePointer, nTotal);
    Image<double> inputImage(imageData, lattice, nBands);

    double distanceTransformData[nTotal];
    Image<double> distanceTransformImage(distanceTransformData, lattice, nBands);
    int rootData[nTotal];
    Image<int> rootImage(rootData, lattice, nBands);

    vector<vector<Seed> > seeds;
    vector<Seed> tmp;
    // background
    tmp.clear();
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, 0, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, nColumns - 1, 0), 0));
    }
    for (int columnIndex = 0; columnIndex < nRows; columnIndex++) {
        tmp.push_back(Seed(inputImage.rclToIndex(0, columnIndex, 0), 0));
        tmp.push_back(Seed(inputImage.rclToIndex(nRows - 1, columnIndex, 0), 0));
    }
    seeds.push_back(tmp);
    // center
    tmp.clear();
    for (int rowIndex = 136; rowIndex < 148; rowIndex++) {
        for (int columnIndex = 112; columnIndex < 166; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    for (int rowIndex = 150; rowIndex < 204; rowIndex++) {
        for (int columnIndex = 298; columnIndex < 308; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 1));
        }
    }
    seeds.push_back(tmp);
    // petals 1: rows 82-87, 189-194, columns 79-84, 177-182
    tmp.clear();
    for (int rowIndex = 82; rowIndex < 87; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 87; rowIndex < 189; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 84; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 177; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 189; rowIndex < 194; rowIndex++) {
        for (int columnIndex = 79; columnIndex < 182; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    // petals 2: rows 122-127, 230-235, columns 253-258, 366-371
    for (int rowIndex = 122; rowIndex < 127; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 127; rowIndex < 230; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 258; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
        for (int columnIndex = 366; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    for (int rowIndex = 230; rowIndex < 235; rowIndex++) {
        for (int columnIndex = 253; columnIndex < 371; columnIndex++) {
            tmp.push_back(Seed(inputImage.rclToIndex(rowIndex, columnIndex, 0), 2));
        }
    }
    seeds.push_back(tmp);

    SeededDistanceTransform seededDistanceTransform;
    MinimumBarrierDistance<double> distanceMeasure;
    seededDistanceTransform.apply(inputImage, seeds, distanceMeasure, 26, distanceTransformImage, rootImage);
    char newFilename[] = "MBDflowersRGB26.bin";
    writeVolume(newFilename, distanceTransformImage.getData(), nTotal);

    delete imageData;

}
#endif

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

