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
    int oldNRows = 120, oldNColumns = 10, oldNLayers = 10, nBands = 2;
    int newNRows = 24, newNColumns = 2, newNLayers = 2;
    double oldDensity = 125.0, newDensity = 1.0;
    int oldNElements = oldNRows * oldNColumns * oldNLayers;
    int newNElements = newNRows * newNColumns * oldNLayers;
    CCLattice oldLattice(oldNRows, oldNColumns, oldNLayers, oldDensity);
    CCLattice newLattice(newNRows, newNColumns, newNLayers, newDensity);

    char highResFileName[] = "testfiles/doubleband.bin";
    char lowResFileName[] = "testfiles/doubleband125.bin";
    char *highResFilePointer = highResFileName;
    char *lowResFilePointer = lowResFileName;
    double *dataHighRes = readVolume(highResFilePointer, oldNElements * nBands);
    double *dataLowRes = readVolume(lowResFilePointer, newNElements * nBands);
    Image<double> oldImage(dataHighRes, oldLattice, nBands);
    std::cout << "input image: " << std::endl;
    oldImage.printParameters();
    double data[newNElements];
    Image<double> newImage(data, newLattice, nBands);
    std::cout << "output image: " << std::endl;
    newImage.printParameters();

    ImageResampler<double> resampler;
    UniformWeight<double> weights;
    resampler.downsample(oldImage, weights, 26, newImage);
    for (int newElementIndex = 0; newElementIndex < newNElements; newElementIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(newElementIndex));
        EXPECT_NEAR(data[newElementIndex], dataLowRes[newElementIndex],EPSILONT);
    }
}
