#include "gtest/gtest.h"
#include "defs.h"
#include "image.h"
#include "cclattice.h"
#include "bcclattice.h"
#include "fcclattice.h"
#include "imageresampler.h"
#include "uniformweight.h"
#include "filehandling.h"
#include <cmath>

using namespace LatticeLib;

TEST(Downsample, CCto2DCC) {
    int oldNRows = 11, oldNColumns = 11, oldNLayers = 1, nBands = 1;
    int newNRows = 3, newNColumns = 3, newNLayers = 1;
    double oldDensity = 125.0, newDensity = 1.0;
    int oldNElements = oldNRows * oldNColumns * oldNLayers;
    int newNElements = newNRows * newNColumns * newNLayers;
    CCLattice oldLattice(oldNRows, oldNColumns, oldNLayers, oldDensity);
    CCLattice newLattice(newNRows, newNColumns, newNLayers, newDensity);

    double dataHighRes[121];
    for (int rowIndex = 0; rowIndex < 6; rowIndex++){
        for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
        for (int columnIndex = 5; columnIndex < 10; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
    }
    for (int rowIndex = 0; rowIndex < 6; rowIndex++) {
        dataHighRes[oldLattice.rclToIndex(rowIndex, 10, 0)] = 1.0;
    }
    for (int rowIndex = 6; rowIndex < 11; rowIndex++) {
        for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
        for (int columnIndex = 5; columnIndex < 10; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
    }
    for (int rowIndex = 6; rowIndex < 11; rowIndex++) {
        dataHighRes[oldLattice.rclToIndex(rowIndex, 10, 0)] = 0.0;
    }
    Image<double> oldImage(dataHighRes, oldLattice, nBands);
    //oldImage.printParameters();

    double dataLowRes[9] = {1, 6.0/15.0, 3.0/9.0, 9.0/15.0, 12.0/25.0, 7.0/15.0, 0.0, 9.0/15.0, 6.0/9.0};

    double data[newNElements];
    Image<double> newImage(data, newLattice, nBands);
    //newImage.printParameters();

    ImageResampler<double> resampler;
    UniformWeight<double> weights;
    resampler.downsample(oldImage, weights, 26, newImage);
    for (int newElementIndex = 0; newElementIndex < newNElements; newElementIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(newElementIndex));
        EXPECT_NEAR(data[newElementIndex], dataLowRes[newElementIndex], EPSILONT);
    }
}

TEST(Downsample, CCto3DCC) {
    int oldNRows = 11, oldNColumns = 11, oldNLayers = 6, nBands = 1;
    int newNRows = 3, newNColumns = 3, newNLayers = 2;
    double oldDensity = 125.0, newDensity = 1.0;
    int oldNElements = oldNRows * oldNColumns * oldNLayers;
    int newNElements = newNRows * newNColumns * newNLayers;
    CCLattice oldLattice(oldNRows, oldNColumns, oldNLayers, oldDensity);
    CCLattice newLattice(newNRows, newNColumns, newNLayers, newDensity);

    double dataHighRes[oldNElements];
    for (int layerIndex = 0; layerIndex < 3; layerIndex++) {
        for (int rowIndex = 0; rowIndex < 6; rowIndex++) {
            for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
                dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, layerIndex)] = 1.0;
            }
            for (int columnIndex = 5; columnIndex < 10; columnIndex++) {
                dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, layerIndex)] = 0.0;
            }
        }
        for (int rowIndex = 0; rowIndex < 6; rowIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, 10, layerIndex)] = 1.0;
        }
        for (int rowIndex = 6; rowIndex < 11; rowIndex++) {
            for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
                dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, layerIndex)] = 0.0;
            }
            for (int columnIndex = 5; columnIndex < 10; columnIndex++) {
                dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, layerIndex)] = 1.0;
            }
        }
        for (int rowIndex = 6; rowIndex < 11; rowIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, 10, layerIndex)] = 0.0;
        }
    }
    for (int layerIndex = 3; layerIndex < 6; layerIndex++) {
        for (int rowIndex = 0; rowIndex < 6; rowIndex++) {
            for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
                dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, layerIndex)] = 0.0;
            }
            for (int columnIndex = 5; columnIndex < 10; columnIndex++) {
                dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, layerIndex)] = 1.0;
            }
        }
        for (int rowIndex = 0; rowIndex < 6; rowIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, 10, layerIndex)] = 0.0;
        }
        for (int rowIndex = 6; rowIndex < 11; rowIndex++) {
            for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
                dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, layerIndex)] = 1.0;
            }
            for (int columnIndex = 5; columnIndex < 10; columnIndex++) {
                dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, layerIndex)] = 0.0;
            }
        }
        for (int rowIndex = 6; rowIndex < 11; rowIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, 10, layerIndex)] = 1.0;
        }
    }
    Image<double> oldImage(dataHighRes, oldLattice, nBands);
    //oldImage.printParameters();

    double dataLowRes[18] = {1, 6.0 / 15.0, 3.0 / 9.0, 9.0 / 15.0, 12.0 / 25.0, 7.0 / 15.0, 0.0, 9.0 / 15.0, 6.0 / 9.0,
                             0, 9.0 / 15.0, 6.0 / 9.0, 6.0 / 15.0, 13.0 / 25.0, 8.0 / 15.0, 1.0, 6.0 / 15.0, 3.0 / 9.0};

    double data[newNElements];
    Image<double> newImage(data, newLattice, nBands);
    //newImage.printParameters();

    ImageResampler<double> resampler;
    UniformWeight<double> weights;
    resampler.downsample(oldImage, weights, 26, newImage);
    for (int newElementIndex = 0; newElementIndex < newNElements; newElementIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(newElementIndex));
        EXPECT_NEAR(data[newElementIndex], dataLowRes[newElementIndex], EPSILONT);
    }
}

TEST(Downsample, CCto2DFCC) {
    int oldNRows = 13, oldNColumns = 16, oldNLayers = 1, nBands = 1;
    int newNRows = 5, newNColumns = 3, newNLayers = 1;
    double oldDensity = 1.0, newDensity = 1.0/54.0;
    int oldNElements = oldNRows * oldNColumns * oldNLayers;
    int newNElements = newNRows * newNColumns * newNLayers;
    CCLattice oldLattice(oldNRows, oldNColumns, oldNLayers, oldDensity);
    FCCLattice newLattice(newNRows, newNColumns, newNLayers, newDensity);

    double dataHighRes[208];
    for (int rowIndex = 0; rowIndex < 5; rowIndex++) {
        for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
        for (int columnIndex = 5; columnIndex < 9; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
        for (int columnIndex = 9; columnIndex < 12; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
        for (int columnIndex = 12; columnIndex < 14; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
        for (int columnIndex = 14; columnIndex < 16; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
    }
    for (int rowIndex = 5; rowIndex < 7; rowIndex++) {
        for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
        for (int columnIndex = 5; columnIndex < 9; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
        for (int columnIndex = 9; columnIndex < 12; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
        for (int columnIndex = 12; columnIndex < 14; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
        for (int columnIndex = 14; columnIndex < 16; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
    }
    for (int rowIndex = 7; rowIndex < 9; rowIndex++) {
        for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
        for (int columnIndex = 5; columnIndex < 9; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
        for (int columnIndex = 9; columnIndex < 12; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
        for (int columnIndex = 12; columnIndex < 14; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
        for (int columnIndex = 14; columnIndex < 16; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
    }
    for (int rowIndex = 9; rowIndex < 13; rowIndex++) {
        for (int columnIndex = 0; columnIndex < 5; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
        for (int columnIndex = 5; columnIndex < 9; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
        for (int columnIndex = 9; columnIndex < 12; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
        for (int columnIndex = 12; columnIndex < 14; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 0.0;
        }
        for (int columnIndex = 14; columnIndex < 16; columnIndex++) {
            dataHighRes[oldLattice.rclToIndex(rowIndex, columnIndex, 0)] = 1.0;
        }
    }
    Image<double> oldImage(dataHighRes, oldLattice, nBands);
    //oldImage.printParameters();

    double dataLowResMax[15] = {0.0, 12.0/13.0, 7.0/11.0, 8.0/19.0, 12.0/20.0, 7.0/14.0, 8.0/12.0, 15.0/22.0, 15.0/20.0, 14.0/19.0, 12.0/18.0, 9.0/13.0, 1.0, 4.0/12.0, 9.0/14.0};
    double dataLowResMin[15] = {0.0,  8.0/12.0, 5.0/14.0, 2.0/19.0,  5.0/18.0, 2.0/11.0, 5.0/13.0,  6.0/15.0,  8.0/18.0,  8.0/18.0,  7.0/19.0, 5.0/12.0, 1.0, 1.0/13.0, 4.0/11.0};

    double data[newNElements];
    Image<double> newImage(data, newLattice, nBands);
    //newImage.printParameters();
    //std::cout << "new image height = " << newImage.getHeight() << std::endl;
    //std::cout << "new image width = " << newImage.getWidth() << std::endl;
    //std::cout << "new image depth = " << newImage.getDepth() << std::endl;

    ImageResampler<double> resampler;
    UniformWeight<double> weights;
    resampler.downsample(oldImage, weights, 18, newImage);
    for (int newElementIndex = 0; newElementIndex < newNElements; newElementIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(newElementIndex));
        EXPECT_LE(data[newElementIndex], dataLowResMax[newElementIndex]);
        EXPECT_GE(data[newElementIndex], dataLowResMin[newElementIndex]);
    }
}

TEST(Downsample, CCto3DFCC) {
    int oldNRows = 7, oldNColumns = 10, oldNLayers = 4, nBands = 1;
    int newNRows = 3, newNColumns = 2, newNLayers = 2;
    double oldDensity = 1.0, newDensity = 1.0 / 54.0;
    int oldNElements = oldNRows * oldNColumns * oldNLayers;
    int newNElements = newNRows * newNColumns * newNLayers;
    CCLattice oldLattice(oldNRows, oldNColumns, oldNLayers, oldDensity);
    FCCLattice newLattice(newNRows, newNColumns, newNLayers, newDensity);

    double dataHighRes[280];
    for (int dataIndex = 0; dataIndex < oldNElements; dataIndex++) {
        dataHighRes[dataIndex] = 0.0;
    }
    for (int columnIndex = 0; columnIndex < oldNColumns; columnIndex++) {
        dataHighRes[3 * oldNColumns + columnIndex] = 1.0;
    }
    Image<double> oldImage(dataHighRes, oldLattice, nBands);
    //oldImage.printParameters();

    double data[newNElements];
    Image<double> newImage(data, newLattice, nBands);
    //newImage.printParameters();

    ImageResampler<double> resampler;
    UniformWeight<double> weights;
    resampler.downsample(oldImage, weights, 18, newImage);
    for (int newElementIndex = 0; newElementIndex < newNElements; newElementIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(newElementIndex));
        EXPECT_GE(data[2], data[newElementIndex]);
        if (newElementIndex != 2) {
            EXPECT_NE(data[2], data[newElementIndex]);
            EXPECT_GE(data[3], data[newElementIndex]);
        }
        EXPECT_LE(data[6], data[newElementIndex]);
        EXPECT_LE(data[7], data[newElementIndex]);
        EXPECT_LE(data[10], data[newElementIndex]);
        EXPECT_LE(data[11], data[newElementIndex]);
    }

    for (int dataIndex = 0; dataIndex < oldNElements; dataIndex++) {
        dataHighRes[dataIndex] = 0.0;
    }
    for (int columnIndex = 0; columnIndex < oldNColumns; columnIndex++) {
        dataHighRes[oldLattice.rclToIndex(3, columnIndex, 3)] = 1.0;
    }
    resampler.downsample(oldImage, weights, 18, newImage);
    for (int newElementIndex = 0; newElementIndex < newNElements; newElementIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(newElementIndex));
        EXPECT_GE(data[9], data[newElementIndex]);
        if (newElementIndex != 9) {
            EXPECT_NE(data[9], data[newElementIndex]);
            EXPECT_GE(data[8], data[newElementIndex]);
        }
        EXPECT_LE(data[0], data[newElementIndex]);
        EXPECT_LE(data[1], data[newElementIndex]);
        EXPECT_LE(data[4], data[newElementIndex]);
        EXPECT_LE(data[5], data[newElementIndex]);
    }
}