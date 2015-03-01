#include "gtest/gtest.h"
#include "cclattice.h"
#include "distancecimage.h"
#include "crispsegmentationcimage.h"
#include "fuzzysegmentationcimage.h"
#include "defs.h"

using namespace CImage;

TEST(DistanceCImage, crisplabel) {

    int nRows = 4;
    int nColumns = 4;
    int nLayers = 4;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    double dataDouble[nElements * nBands];

    DistanceCImage distanceImage(dataDouble, lattice, nBands);

    //std::cout << "First band: " << std::endl;
    int band = 0;
    double xRef = 4;
    double yRef = 0;
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        for (int columnIndex = 0; columnIndex < nColumns; columnIndex++) {
            for (int layerIndex = 0; layerIndex < nLayers; layerIndex++) {
                double xDiff = fabs(xRef - distanceImage.indexToX(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex)));
                double yDiff = fabs(yRef - distanceImage.indexToY(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex)));
                double intensity = sqrt(xDiff * xDiff + yDiff * yDiff);
                distanceImage.setElement(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex), band, intensity);
                //std::cout << "intensity at (" << rowIndex << "," << columnIndex << "," << layerIndex << "," << band << "): " << intensity << std::endl;
            }
        }
    }
    //std::cout << "Second band: " << std::endl;
    band = 1;
    xRef = 0;
    yRef = 4;
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        for (int columnIndex = 0; columnIndex < nColumns; columnIndex++) {
            for (int layerIndex = 0; layerIndex < nLayers; layerIndex++) {
                double xDiff = fabs(xRef - distanceImage.indexToX(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex)));
                double yDiff = fabs(yRef - distanceImage.indexToY(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex)));
                double intensity = sqrt(xDiff * xDiff + yDiff * yDiff);
                distanceImage.setElement(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex), band, intensity);
                //std::cout << "intensity at (" << rowIndex << "," << columnIndex << "," << layerIndex << "," << band << "): " << intensity << std::endl;
            }
        }
    }
    //std::cout << "Third band: " << std::endl;
    band = 2;
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        for (int columnIndex = 0; columnIndex < nColumns; columnIndex++) {
            for (int layerIndex = 0; layerIndex < nLayers; layerIndex++) {
                double factor = 0.5 * fabs(columnIndex - rowIndex);
                double intensity = factor * sqrt(2);
                distanceImage.setElement(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex), band, intensity);
                //std::cout << "intensity at (" << rowIndex << "," << columnIndex << "," << layerIndex << "," << band << "): " << intensity << std::endl;
            }
        }
    }

    CrispSegmentationCImage segmentation = distanceImage.crispLabel();

    EXPECT_EQ(distanceImage.getNRows(), segmentation.getNRows());
    EXPECT_EQ(distanceImage.getNColumns(), segmentation.getNColumns());
    EXPECT_EQ(distanceImage.getNLayers(), segmentation.getNLayers());
    EXPECT_EQ(distanceImage.getNBands(), segmentation.getNBands());
    EXPECT_EQ(distanceImage.getNElements(), segmentation.getNElements());
    EXPECT_NEAR(distanceImage.getScaleFactor(), segmentation.getScaleFactor(), EPSILONT);
    EXPECT_NEAR(distanceImage.getWidth(), segmentation.getWidth(), EPSILONT);
    EXPECT_NEAR(distanceImage.getHeight(), segmentation.getHeight(), EPSILONT);
    EXPECT_NEAR(distanceImage.getDepth(), segmentation.getDepth(), EPSILONT);

    EXPECT_FALSE(segmentation(0, 0, 0, 0));
    EXPECT_FALSE(segmentation(0, 1, 0, 0));
    EXPECT_FALSE(segmentation(0, 2, 0, 0));
    EXPECT_TRUE(segmentation(0, 3, 0, 0));
    EXPECT_FALSE(segmentation(0, 0, 1, 0));
    EXPECT_FALSE(segmentation(0, 1, 1, 0));
    EXPECT_FALSE(segmentation(0, 2, 1, 0));
    EXPECT_TRUE(segmentation(0, 3, 1, 0));
    EXPECT_FALSE(segmentation(0, 0, 2, 0));
    EXPECT_FALSE(segmentation(0, 1, 2, 0));
    EXPECT_FALSE(segmentation(0, 2, 2, 0));
    EXPECT_TRUE(segmentation(0, 3, 2, 0));
    EXPECT_FALSE(segmentation(0, 0, 3, 0));
    EXPECT_FALSE(segmentation(0, 1, 3, 0));
    EXPECT_FALSE(segmentation(0, 2, 3, 0));
    EXPECT_TRUE(segmentation(0, 3, 3, 0));

    EXPECT_FALSE(segmentation(1, 0, 0, 0));
    EXPECT_FALSE(segmentation(1, 1, 0, 0));
    EXPECT_FALSE(segmentation(1, 2, 0, 0));
    EXPECT_FALSE(segmentation(1, 3, 0, 0));
    EXPECT_FALSE(segmentation(1, 0, 1, 0));
    EXPECT_FALSE(segmentation(1, 1, 1, 0));
    EXPECT_FALSE(segmentation(1, 2, 1, 0));
    EXPECT_FALSE(segmentation(1, 3, 1, 0));
    EXPECT_FALSE(segmentation(1, 0, 2, 0));
    EXPECT_FALSE(segmentation(1, 1, 2, 0));
    EXPECT_FALSE(segmentation(1, 2, 2, 0));
    EXPECT_FALSE(segmentation(1, 3, 2, 0));
    EXPECT_FALSE(segmentation(1, 0, 3, 0));
    EXPECT_FALSE(segmentation(1, 1, 3, 0));
    EXPECT_FALSE(segmentation(1, 2, 3, 0));
    EXPECT_FALSE(segmentation(1, 3, 3, 0));

    EXPECT_FALSE(segmentation(2, 0, 0, 0));
    EXPECT_FALSE(segmentation(2, 1, 0, 0));
    EXPECT_FALSE(segmentation(2, 2, 0, 0));
    EXPECT_FALSE(segmentation(2, 3, 0, 0));
    EXPECT_FALSE(segmentation(2, 0, 1, 0));
    EXPECT_FALSE(segmentation(2, 1, 1, 0));
    EXPECT_FALSE(segmentation(2, 2, 1, 0));
    EXPECT_FALSE(segmentation(2, 3, 1, 0));
    EXPECT_FALSE(segmentation(2, 0, 2, 0));
    EXPECT_FALSE(segmentation(2, 1, 2, 0));
    EXPECT_FALSE(segmentation(2, 2, 2, 0));
    EXPECT_FALSE(segmentation(2, 3, 2, 0));
    EXPECT_FALSE(segmentation(2, 0, 3, 0));
    EXPECT_FALSE(segmentation(2, 1, 3, 0));
    EXPECT_FALSE(segmentation(2, 2, 3, 0));
    EXPECT_FALSE(segmentation(2, 3, 3, 0));

    EXPECT_FALSE(segmentation(3, 0, 0, 0));
    EXPECT_FALSE(segmentation(3, 1, 0, 0));
    EXPECT_FALSE(segmentation(3, 2, 0, 0));
    EXPECT_FALSE(segmentation(3, 3, 0, 0));
    EXPECT_FALSE(segmentation(3, 0, 1, 0));
    EXPECT_FALSE(segmentation(3, 1, 1, 0));
    EXPECT_FALSE(segmentation(3, 2, 1, 0));
    EXPECT_FALSE(segmentation(3, 3, 1, 0));
    EXPECT_FALSE(segmentation(3, 0, 2, 0));
    EXPECT_FALSE(segmentation(3, 1, 2, 0));
    EXPECT_FALSE(segmentation(3, 2, 2, 0));
    EXPECT_FALSE(segmentation(3, 3, 2, 0));
    EXPECT_FALSE(segmentation(3, 0, 3, 0));
    EXPECT_FALSE(segmentation(3, 1, 3, 0));
    EXPECT_FALSE(segmentation(3, 2, 3, 0));
    EXPECT_FALSE(segmentation(3, 3, 3, 0));


    EXPECT_FALSE(segmentation(0, 0, 0, 1));
    EXPECT_FALSE(segmentation(0, 1, 0, 1));
    EXPECT_FALSE(segmentation(0, 2, 0, 1));
    EXPECT_FALSE(segmentation(0, 3, 0, 1));
    EXPECT_FALSE(segmentation(0, 0, 1, 1));
    EXPECT_FALSE(segmentation(0, 1, 1, 1));
    EXPECT_FALSE(segmentation(0, 2, 1, 1));
    EXPECT_FALSE(segmentation(0, 3, 1, 1));
    EXPECT_FALSE(segmentation(0, 0, 2, 1));
    EXPECT_FALSE(segmentation(0, 1, 2, 1));
    EXPECT_FALSE(segmentation(0, 2, 2, 1));
    EXPECT_FALSE(segmentation(0, 3, 2, 1));
    EXPECT_FALSE(segmentation(0, 0, 3, 1));
    EXPECT_FALSE(segmentation(0, 1, 3, 1));
    EXPECT_FALSE(segmentation(0, 2, 3, 1));
    EXPECT_FALSE(segmentation(0, 3, 3, 1));

    EXPECT_FALSE(segmentation(1, 0, 0, 1));
    EXPECT_FALSE(segmentation(1, 1, 0, 1));
    EXPECT_FALSE(segmentation(1, 2, 0, 1));
    EXPECT_FALSE(segmentation(1, 3, 0, 1));
    EXPECT_FALSE(segmentation(1, 0, 1, 1));
    EXPECT_FALSE(segmentation(1, 1, 1, 1));
    EXPECT_FALSE(segmentation(1, 2, 1, 1));
    EXPECT_FALSE(segmentation(1, 3, 1, 1));
    EXPECT_FALSE(segmentation(1, 0, 2, 1));
    EXPECT_FALSE(segmentation(1, 1, 2, 1));
    EXPECT_FALSE(segmentation(1, 2, 2, 1));
    EXPECT_FALSE(segmentation(1, 3, 2, 1));
    EXPECT_FALSE(segmentation(1, 0, 3, 1));
    EXPECT_FALSE(segmentation(1, 1, 3, 1));
    EXPECT_FALSE(segmentation(1, 2, 3, 1));
    EXPECT_FALSE(segmentation(1, 3, 3, 1));

    EXPECT_FALSE(segmentation(2, 0, 0, 1));
    EXPECT_FALSE(segmentation(2, 1, 0, 1));
    EXPECT_FALSE(segmentation(2, 2, 0, 1));
    EXPECT_FALSE(segmentation(2, 3, 0, 1));
    EXPECT_FALSE(segmentation(2, 0, 1, 1));
    EXPECT_FALSE(segmentation(2, 1, 1, 1));
    EXPECT_FALSE(segmentation(2, 2, 1, 1));
    EXPECT_FALSE(segmentation(2, 3, 1, 1));
    EXPECT_FALSE(segmentation(2, 0, 2, 1));
    EXPECT_FALSE(segmentation(2, 1, 2, 1));
    EXPECT_FALSE(segmentation(2, 2, 2, 1));
    EXPECT_FALSE(segmentation(2, 3, 2, 1));
    EXPECT_FALSE(segmentation(2, 0, 3, 1));
    EXPECT_FALSE(segmentation(2, 1, 3, 1));
    EXPECT_FALSE(segmentation(2, 2, 3, 1));
    EXPECT_FALSE(segmentation(2, 3, 3, 1));

    EXPECT_TRUE(segmentation(3, 0, 0, 1));
    EXPECT_FALSE(segmentation(3, 1, 0, 1));
    EXPECT_FALSE(segmentation(3, 2, 0, 1));
    EXPECT_FALSE(segmentation(3, 3, 0, 1));
    EXPECT_TRUE(segmentation(3, 0, 1, 1));
    EXPECT_FALSE(segmentation(3, 1, 1, 1));
    EXPECT_FALSE(segmentation(3, 2, 1, 1));
    EXPECT_FALSE(segmentation(3, 3, 1, 1));
    EXPECT_TRUE(segmentation(3, 0, 2, 1));
    EXPECT_FALSE(segmentation(3, 1, 2, 1));
    EXPECT_FALSE(segmentation(3, 2, 2, 1));
    EXPECT_FALSE(segmentation(3, 3, 2, 1));
    EXPECT_TRUE(segmentation(3, 0, 3, 1));
    EXPECT_FALSE(segmentation(3, 1, 3, 1));
    EXPECT_FALSE(segmentation(3, 2, 3, 1));
    EXPECT_FALSE(segmentation(3, 3, 3, 1));


    EXPECT_TRUE(segmentation(0, 0, 0, 2));
    EXPECT_TRUE(segmentation(0, 1, 0, 2));
    EXPECT_TRUE(segmentation(0, 2, 0, 2));
    EXPECT_FALSE(segmentation(0, 3, 0, 2));
    EXPECT_TRUE(segmentation(0, 0, 1, 2));
    EXPECT_TRUE(segmentation(0, 1, 1, 2));
    EXPECT_TRUE(segmentation(0, 2, 1, 2));
    EXPECT_FALSE(segmentation(0, 3, 1, 2));
    EXPECT_TRUE(segmentation(0, 0, 2, 2));
    EXPECT_TRUE(segmentation(0, 1, 2, 2));
    EXPECT_TRUE(segmentation(0, 2, 2, 2));
    EXPECT_FALSE(segmentation(0, 3, 2, 2));
    EXPECT_TRUE(segmentation(0, 0, 3, 2));
    EXPECT_TRUE(segmentation(0, 1, 3, 2));
    EXPECT_TRUE(segmentation(0, 2, 3, 2));
    EXPECT_FALSE(segmentation(0, 3, 3, 2));

    EXPECT_TRUE(segmentation(1, 0, 0, 2));
    EXPECT_TRUE(segmentation(1, 1, 0, 2));
    EXPECT_TRUE(segmentation(1, 2, 0, 2));
    EXPECT_TRUE(segmentation(1, 3, 0, 2));
    EXPECT_TRUE(segmentation(1, 0, 1, 2));
    EXPECT_TRUE(segmentation(1, 1, 1, 2));
    EXPECT_TRUE(segmentation(1, 2, 1, 2));
    EXPECT_TRUE(segmentation(1, 3, 1, 2));
    EXPECT_TRUE(segmentation(1, 0, 2, 2));
    EXPECT_TRUE(segmentation(1, 1, 2, 2));
    EXPECT_TRUE(segmentation(1, 2, 2, 2));
    EXPECT_TRUE(segmentation(1, 3, 2, 2));
    EXPECT_TRUE(segmentation(1, 0, 3, 2));
    EXPECT_TRUE(segmentation(1, 1, 3, 2));
    EXPECT_TRUE(segmentation(1, 2, 3, 2));
    EXPECT_TRUE(segmentation(1, 3, 3, 2));

    EXPECT_TRUE(segmentation(2, 0, 0, 2));
    EXPECT_TRUE(segmentation(2, 1, 0, 2));
    EXPECT_TRUE(segmentation(2, 2, 0, 2));
    EXPECT_TRUE(segmentation(2, 3, 0, 2));
    EXPECT_TRUE(segmentation(2, 0, 1, 2));
    EXPECT_TRUE(segmentation(2, 1, 1, 2));
    EXPECT_TRUE(segmentation(2, 2, 1, 2));
    EXPECT_TRUE(segmentation(2, 3, 1, 2));
    EXPECT_TRUE(segmentation(2, 0, 2, 2));
    EXPECT_TRUE(segmentation(2, 1, 2, 2));
    EXPECT_TRUE(segmentation(2, 2, 2, 2));
    EXPECT_TRUE(segmentation(2, 3, 2, 2));
    EXPECT_TRUE(segmentation(2, 0, 3, 2));
    EXPECT_TRUE(segmentation(2, 1, 3, 2));
    EXPECT_TRUE(segmentation(2, 2, 3, 2));
    EXPECT_TRUE(segmentation(2, 3, 3, 2));

    EXPECT_FALSE(segmentation(3, 0, 0, 2));
    EXPECT_TRUE(segmentation(3, 1, 0, 2));
    EXPECT_TRUE(segmentation(3, 2, 0, 2));
    EXPECT_TRUE(segmentation(3, 3, 0, 2));
    EXPECT_FALSE(segmentation(3, 0, 1, 2));
    EXPECT_TRUE(segmentation(3, 1, 1, 2));
    EXPECT_TRUE(segmentation(3, 2, 1, 2));
    EXPECT_TRUE(segmentation(3, 3, 1, 2));
    EXPECT_FALSE(segmentation(3, 0, 2, 2));
    EXPECT_TRUE(segmentation(3, 1, 2, 2));
    EXPECT_TRUE(segmentation(3, 2, 2, 2));
    EXPECT_TRUE(segmentation(3, 3, 2, 2));
    EXPECT_FALSE(segmentation(3, 0, 3, 2));
    EXPECT_TRUE(segmentation(3, 1, 3, 2));
    EXPECT_TRUE(segmentation(3, 2, 3, 2));
    EXPECT_TRUE(segmentation(3, 3, 3, 2));

    delete segmentation.getData();

}

TEST(DistanceCImage, fuzzylabel) {

    int nRows = 4;
    int nColumns = 4;
    int nLayers = 4;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    double dataDouble[nElements * nBands];

    DistanceCImage distanceImage(dataDouble, lattice, nBands);

    int band = 0;
    double xRef = 4;
    double yRef = 0;
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        for (int columnIndex = 0; columnIndex < nColumns; columnIndex++) {
            for (int layerIndex = 0; layerIndex < nLayers; layerIndex++) {
                double xDiff = fabs(xRef - distanceImage.indexToX(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex)));
                double yDiff = fabs(yRef - distanceImage.indexToY(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex)));
                double intensity = sqrt(xDiff * xDiff + yDiff * yDiff);
                distanceImage.setElement(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex), band, intensity);
            }
        }
    }
    band = 1;
    xRef = 0;
    yRef = 4;
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        for (int columnIndex = 0; columnIndex < nColumns; columnIndex++) {
            for (int layerIndex = 0; layerIndex < nLayers; layerIndex++) {
                double xDiff = fabs(xRef - distanceImage.indexToX(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex)));
                double yDiff = fabs(yRef - distanceImage.indexToY(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex)));
                double intensity = sqrt(xDiff * xDiff + yDiff * yDiff);
                distanceImage.setElement(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex), band, intensity);
            }
        }
    }
    band = 2;
    for (int rowIndex = 0; rowIndex < nRows; rowIndex++) {
        for (int columnIndex = 0; columnIndex < nColumns; columnIndex++) {
            for (int layerIndex = 0; layerIndex < nLayers; layerIndex++) {
                double factor = 0.5 * fabs(columnIndex - rowIndex);
                double intensity = factor * sqrt(2);
                distanceImage.setElement(distanceImage.rclToIndex(rowIndex, columnIndex, layerIndex), band, intensity);
            }
        }
    }

    FuzzySegmentationCImage<double> segmentation = distanceImage.fuzzyLabel(0.0,1.0);

    EXPECT_EQ(distanceImage.getNRows(), segmentation.getNRows());
    EXPECT_EQ(distanceImage.getNColumns(), segmentation.getNColumns());
    EXPECT_EQ(distanceImage.getNLayers(), segmentation.getNLayers());
    EXPECT_EQ(distanceImage.getNBands(), segmentation.getNBands());
    EXPECT_EQ(distanceImage.getNElements(), segmentation.getNElements());
    EXPECT_NEAR(distanceImage.getScaleFactor(), segmentation.getScaleFactor(), EPSILONT);
    EXPECT_NEAR(distanceImage.getWidth(), segmentation.getWidth(), EPSILONT);
    EXPECT_NEAR(distanceImage.getHeight(), segmentation.getHeight(), EPSILONT);
    EXPECT_NEAR(distanceImage.getDepth(), segmentation.getDepth(), EPSILONT);

    std::cout << "returned segmented data array: " << segmentation.getData() << std::endl;

    delete segmentation.getData();
}