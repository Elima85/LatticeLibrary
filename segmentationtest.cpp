#include "gtest/gtest.h"
#include "defs.h"
#include "segmentation.h"
#include "image.h"
#include <stdio.h>

using namespace LatticeLib;

TEST(Segmentation,crisp) {

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