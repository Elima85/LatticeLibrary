#include "gtest/gtest.h"
#include "../defs.h"
#include "../segmentation.h"
#include "../image.h"
#include "../intensityworkset.h"
#include "../cclattice.h"
#include "filehandling.h"
#include "../vectoroperators.h"

using namespace LatticeLib;

TEST(Segmentation, crisp) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    double distance[nElements * nBands];
    bool labelValues[nElements * nBands];
    Image<double> distanceTransform(distance, lattice, nBands);
    vector<double> defaultDistances;
    defaultDistances.push_back(9.9);
    defaultDistances.push_back(8.8);
    defaultDistances.push_back(7.7);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        distanceTransform.setElement(elementIndex, defaultDistances); // default: label 2
    }
    distanceTransform.setElement(2, 2, 3, 0, 0.0); // midpoint: label 0
    distanceTransform.setElement(2, 3, 3, 0, 0.0);
    for (int columnIndex = 0; columnIndex < nColumns; columnIndex++) { // roof and floor: label 1
        for (int layerIndex = 0; layerIndex < nLayers; layerIndex++) {
            distanceTransform.setElement(0, columnIndex, layerIndex, 1, 0.0);
            distanceTransform.setElement(4, columnIndex, layerIndex, 1, 0.0);
        }
    }

    Image<bool> labels(labelValues, lattice, nBands);

    Segmentation segmentation;
    segmentation.crisp(distanceTransform, labels);

    int nLabels[] = {0,0,0};
    int totalNLabels = 0;
    for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
        for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
            if (labels(elementIndex, bandIndex)) {
                nLabels[bandIndex]++;
                totalNLabels++;
            }
        }
    }
    EXPECT_EQ(210, totalNLabels);
    EXPECT_EQ(2, nLabels[0]);
    EXPECT_EQ(84, nLabels[1]);
    EXPECT_EQ(124, nLabels[2]);

    // only one label per element
    int incorrectLabels = 0;
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        int nCurrentLabels = 0;
        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
            if (labels(elementIndex,bandIndex)) {
                nCurrentLabels++;
            }
        }
        if (nCurrentLabels != 1) {
            incorrectLabels++;
        }
    }
    EXPECT_EQ(0, incorrectLabels);

    // correct labels?
    EXPECT_EQ(1, labels(2, 2, 3, 0));
    EXPECT_EQ(1, labels(2, 3, 3, 0));
    int labelSum = 0;
    for (int columnIndex = 0; columnIndex < nColumns; columnIndex++) { // roof and floor: label 1
        for (int layerIndex = 0; layerIndex < nLayers; layerIndex++) {
            labelSum += labels(0, columnIndex, layerIndex, 1);
            labelSum += labels(4, columnIndex, layerIndex, 1);
        }
    }
    EXPECT_EQ(84, labelSum);
}

TEST(Segmentation, CrispAMBD) {

    int nRows = 321;
    int nColumns = 481;
    int nLayers = 1;
    int nElements = nRows * nColumns * nLayers;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    int nBands = 3;
    int nTotal = nElements * nBands;

    char inputFilename[] = "test/AMBDflowersRGB26.bin";
    char *inputFilenamePointer = inputFilename;
    double *distanceTransformData = readVolume(inputFilenamePointer, nTotal);
    Image<double> distanceTransformImage(distanceTransformData, lattice, nBands);
    bool segmentationData[nTotal];
    Image<bool> segmentationImage(segmentationData, lattice, nBands);
    double doubleSegmentationData[nTotal];

    Segmentation segmentation;
    segmentation.crisp(distanceTransformImage, segmentationImage);
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        if (segmentationData[dataIndex]) {
            doubleSegmentationData[dataIndex] = 1.0;
        }
        else {
            doubleSegmentationData[dataIndex] = 0.0;
        }
    }
    char newFilename[] = "test/AMBDflowersRGB26segmentation.bin";
    writeVolume(newFilename, doubleSegmentationData, nTotal);

    delete distanceTransformData;
}

TEST(Segmentation, FuzzyAMBD) {

    int nRows = 321;
    int nColumns = 481;
    int nLayers = 1;
    int nElements = nRows * nColumns * nLayers;
    CCLattice lattice(nRows, nColumns, nLayers, 1.0);
    int nBands = 3;
    int nLabels = 3;

    char inputFilename[] = "test/AMBDflowersRGB26.bin";
    char *inputFilenamePointer = inputFilename;
    double *distanceTransformData = readVolume(inputFilenamePointer, nElements * nLabels);
    Image<double> distanceTransformImage(distanceTransformData, lattice, nLabels);
    double segmentationData[nElements * nLabels];
    Image<double> segmentationImage(segmentationData, lattice, nLabels);
    IntensityWorkset<double> fuzzySegmentation(segmentationImage, 0.0, 1.0);

    Segmentation segmentation;
    segmentation.fuzzy(distanceTransformImage, 6, fuzzySegmentation);

    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(elementIndex));
        EXPECT_NEAR(sumOfElements(segmentationImage[elementIndex]), 1.0, EPSILONT);
    }

    char newFilename[] = "test/fuzzyAMBDflowersRGB26segmentation.bin";
    writeVolume(newFilename, segmentationData, nElements * nLabels);

    delete distanceTransformData;
}