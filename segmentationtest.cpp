#include "gtest/gtest.h"
#include "defs.h"
#include "segmentation.h"
#include "image.h"
#include "intensityworkset.h"
#include <stdio.h>
#include "cclattice.h"

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

TEST(Segmentation, fuzzy) {

    int nRows = 5;
    int nColumns = 5;
    int nLayers = 1;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 4;
    double distance[100] = { 2,          1,          0,          1,          2,
                             sqrt(5),    sqrt(2),    1,          sqrt(2),    sqrt(5),
                             sqrt(8),    sqrt(5),    2,          sqrt(5),    sqrt(8),
                             sqrt(13),   sqrt(10),   3,          sqrt(10),   sqrt(13),
                             sqrt(20),   sqrt(17),   4,          sqrt(17),   sqrt(20),

                             2,          sqrt(5),    sqrt(8),    sqrt(13),   sqrt(20),
                             1,          sqrt(2),    sqrt(5),    sqrt(10),   sqrt(17),
                             0,          1,          2,          3,          4,
                             1,          sqrt(2),    sqrt(5),    sqrt(10),   sqrt(17),
                             2,          sqrt(5),    sqrt(8),    sqrt(13),   sqrt(20),

                             sqrt(20),   sqrt(17),   4,          sqrt(17),   sqrt(20),
                             sqrt(13),   sqrt(10),   3,          sqrt(10),   sqrt(13),
                             sqrt(8),    sqrt(5),    2,          sqrt(5),    sqrt(8),
                             sqrt(5),    sqrt(2),    1,          sqrt(2),    sqrt(5),
                             2,          1,          0,          1,          2,

                             sqrt(20),   sqrt(13),   sqrt(8),    sqrt(5),    2,
                             sqrt(17),   sqrt(10),   sqrt(5),    sqrt(2),    1,
                             4,          3,          2,          1,          0,
                             sqrt(17),   sqrt(10),   sqrt(5),    sqrt(2),    1,
                             sqrt(20),   sqrt(13),   sqrt(8),    sqrt(5),    2};
    Image<double> distanceTransform(distance, lattice, nBands);

    uint8 uint8LabelValues[nElements * nBands];
    int intLabelValues[nElements * nBands];
    double doubleLabelValues[nElements * nBands];
    Image<uint8> uint8Labels(uint8LabelValues, lattice, nBands);
    Image<int> intLabels(intLabelValues, lattice, nBands);
    Image<double> doubleLabels(doubleLabelValues, lattice, nBands);
    IntensityWorkset<uint8> uint8FuzzyLabels(uint8Labels, 0, 255, none);
    IntensityWorkset<int> intFuzzyLabels(intLabels, 14, 92, none);
    IntensityWorkset<double> doubleFuzzyLabels(doubleLabels, 0.0, 1.0, none);


    Segmentation segmentation;
    segmentation.fuzzy(distanceTransform, uint8FuzzyLabels);
    segmentation.fuzzy(distanceTransform, intFuzzyLabels);
    segmentation.fuzzy(distanceTransform, doubleFuzzyLabels);

    int uint8LabelSum = 0, intLabelSum = 0;
    double doubleLabelSum = 0.0;
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        std::cout << std::endl;
        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
            uint8LabelSum += uint8FuzzyLabels.getImage()(elementIndex,bandIndex);
            intLabelSum += (intFuzzyLabels.getImage()(elementIndex, bandIndex) - 14);
            doubleLabelSum += doubleFuzzyLabels.getImage()(elementIndex, bandIndex);
        }

    }
    EXPECT_EQ(nElements * 255, uint8LabelSum);
    EXPECT_EQ(nElements * (92 - 14), intLabelSum);
    EXPECT_NEAR(nElements, doubleLabelSum, EPSILONT);

    EXPECT_NEAR(1, doubleFuzzyLabels.getImage()(1, 0), EPSILONT);
    EXPECT_NEAR(1, doubleFuzzyLabels.getImage()(2, 0), EPSILONT);
    EXPECT_NEAR(1, doubleFuzzyLabels.getImage()(3, 0), EPSILONT);
    EXPECT_NEAR(1, doubleFuzzyLabels.getImage()(7, 0), EPSILONT);
}
