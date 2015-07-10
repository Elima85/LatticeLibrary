#include "gtest/gtest.h"
#include "defs.h"
#include "segmentation.h"
#include "image.h"

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
    bool labels[nElements * nBands];
    Image<double> distanceTransform(distance, lattice, nBands);
    vector<double> defaultDistances;
    defaultDistances.push_back(0.9);
    defaultDistances.push_back(0.8);
    defaultDistances.push_back(0.7);
    for (int elementIndex = 0; elementIndex < nBands; elementIndex++) {
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

    Image<bool> labels(labels, lattice, nBands);

    Segmentation segmentation;
    segmentation(distanceTransform, labels);

    // only one label per element
    int incorrectLabels = 0;
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        int nLabels = 0;
        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
            if (labels(elementIndex,bandIndex)) {
                nLabels++;
            }
            if (nLabels != 1) {
                incorrectLabels++;
            }
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