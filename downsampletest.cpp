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

TEST(Downsample, CCtoCC) {
    int oldNRows = 11, oldNColumns = 11, oldNLayers = 1, nBands = 1;
    int newNRows = 3, newNColumns = 3, newNLayers = 1;
    double oldDensity = 125.0, newDensity = 1.0;
    int oldNElements = oldNRows * oldNColumns * oldNLayers;
    int newNElements = newNRows * newNColumns * oldNLayers;
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
    oldImage.printParameters();

    double dataLowRes[9] = {1, 6.0/15.0, 3.0/9.0, 9.0/15.0, 12.0/25.0, 7.0/15.0, 0.0, 9.0/15.0, 6.0/9.0};

    double data[newNElements];
    Image<double> newImage(data, newLattice, nBands);
    newImage.printParameters();

    ImageResampler<double> resampler;
    UniformWeight<double> weights;
    resampler.downsample(oldImage, weights, 26, newImage);
    for (int newElementIndex = 0; newElementIndex < newNElements; newElementIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(newElementIndex));
        EXPECT_NEAR(data[newElementIndex], dataLowRes[newElementIndex], EPSILONT);
    }
}

TEST(Downsample, CCtoFCC) {
    int oldNRows = 13, oldNColumns = 16, oldNLayers = 1, nBands = 1;
    int newNRows = 5, newNColumns = 3, newNLayers = 1;
    double oldDensity = 1.0, newDensity = 1.0/54.0;
    int oldNElements = oldNRows * oldNColumns * oldNLayers;
    int newNElements = newNRows * newNColumns * oldNLayers;
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
    oldImage.printParameters();

    double dataLowResMax[15] = {0.0, 12.0/13.0, 7.0/11.0, 8.0/19.0, 12.0/20.0, 7.0/14.0, 8.0/12.0, 15.0/22.0, 15.0/20.0, 14.0/19.0, 12.0/18.0, 9.0/13.0, 1.0, 4.0/12.0, 9.0/14.0};
    double dataLowResMin[15] = {0.0,  8.0/12.0, 5.0/14.0, 2.0/19.0,  5.0/18.0, 2.0/11.0, 5.0/13.0,  6.0/15.0,  8.0/18.0,  8.0/18.0,  7.0/19.0, 5.0/12.0, 1.0, 1.0/13.0, 4.0/11.0};

    double data[newNElements];
    Image<double> newImage(data, newLattice, nBands);
    newImage.printParameters();
    std::cout << "new image height = " << newImage.getHeight() << std::endl;
    std::cout << "new image width = " << newImage.getWidth() << std::endl;
    std::cout << "new image depth = " << newImage.getDepth() << std::endl;

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