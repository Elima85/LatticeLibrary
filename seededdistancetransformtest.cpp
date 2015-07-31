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