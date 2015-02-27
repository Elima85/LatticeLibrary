#include "gtest/gtest.h"
#include "defs.h"
#include "intensitycimage.h"
#include "cclattice.h"

using namespace CImage;

TEST(IntensityCImage, initialization) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    int nTotal = nElements * nBands;
    uint8 dataUint8Full[nTotal];
    uint8 dataUint8Half[nTotal];
    double dataDouble01[nTotal];
    double dataDouble14[nTotal];
    for (int i = 0; i < nTotal; i++) {
        dataUint8Full[i] = MIN(i, 255);
        dataUint8Half[i] = MIN(i, 255);
        dataDouble01[i] = double(i)/100.0;
        dataDouble14[i] = double(i)/100.0;
    }
    IntensityCImage<uint8> *imageUint8Full = new IntensityCImage<uint8>(dataUint8Full, lattice, nBands,0,255);
    uint8* extractedDataUint8 = imageUint8Full->getData();
    int minValUint8 = INT_MAX, maxValUint8 = INT_MIN;
    for (int i = 0; i < nTotal; i++) {
        int currentVal = extractedDataUint8[i];
        if (currentVal < minValUint8) {
            minValUint8 = currentVal;
        }
        else {
            if (currentVal > maxValUint8) {
                maxValUint8 = currentVal;
            }
        }
    }
    EXPECT_GE(minValUint8, 0);
    EXPECT_LE(maxValUint8, 255);
    EXPECT_EQ(0, extractedDataUint8[0]);
    EXPECT_EQ(63, extractedDataUint8[63]);
    EXPECT_EQ(255, extractedDataUint8[255]);
    EXPECT_EQ(255, extractedDataUint8[300]);
    EXPECT_EQ(0, imageUint8Full->adjustIntensity(-3187));
    EXPECT_EQ(0, imageUint8Full->adjustIntensity(-43.78));
    EXPECT_EQ(0, imageUint8Full->adjustIntensity(0));
    EXPECT_EQ(63, imageUint8Full->adjustIntensity(63));
    EXPECT_EQ(63, imageUint8Full->adjustIntensity(63.1));
    EXPECT_EQ(63, imageUint8Full->adjustIntensity(63.9));
    EXPECT_EQ(255, imageUint8Full->adjustIntensity(255));
    EXPECT_EQ(255, imageUint8Full->adjustIntensity(47953));
    EXPECT_EQ(255, imageUint8Full->adjustIntensity(853.65));


    IntensityCImage<uint8> *imageUint8Half = new IntensityCImage<uint8>(dataUint8Half, lattice, nBands, 63, 190);
    extractedDataUint8 = imageUint8Half->getData();
    minValUint8 = INT_MAX;
    maxValUint8 = INT_MIN;
    for (int i = 0; i < nTotal; i++) {
        int currentVal = extractedDataUint8[i];
        if (currentVal < minValUint8) {
            minValUint8 = currentVal;
        }
        else {
            if (currentVal > maxValUint8) {
                maxValUint8 = currentVal;
            }
        }
    }
    EXPECT_GE(minValUint8, 63);
    EXPECT_LE(maxValUint8, 190);
    EXPECT_EQ(63, extractedDataUint8[0]);
    EXPECT_EQ(63, extractedDataUint8[63]);
    EXPECT_EQ(127, extractedDataUint8[127]);
    EXPECT_EQ(190, extractedDataUint8[190]);
    EXPECT_EQ(190, extractedDataUint8[300]);
    EXPECT_EQ(63, imageUint8Half->adjustIntensity(-3187));
    EXPECT_EQ(63, imageUint8Half->adjustIntensity(-43.78));
    EXPECT_EQ(63, imageUint8Half->adjustIntensity(0));
    EXPECT_EQ(63, imageUint8Half->adjustIntensity(63));
    EXPECT_EQ(100, imageUint8Half->adjustIntensity(100));
    EXPECT_EQ(100, imageUint8Half->adjustIntensity(100.1));
    EXPECT_EQ(100, imageUint8Half->adjustIntensity(100.9));
    EXPECT_EQ(190, imageUint8Half->adjustIntensity(190));
    EXPECT_EQ(190, imageUint8Half->adjustIntensity(255));
    EXPECT_EQ(190, imageUint8Half->adjustIntensity(853.65));

    IntensityCImage<double> *imageDouble01 = new IntensityCImage<double>(dataDouble01, lattice, nBands, 0, 1);
    double *extractedDataDouble = imageDouble01->getData();
    double minValDouble = DBL_MAX, maxValDouble = DBL_MIN;
    for (int i = 0; i < nTotal; i++) {
        double currentVal = extractedDataDouble[i];
        if (currentVal < minValDouble) {
            minValDouble = currentVal;
        }
        else {
            if (currentVal > maxValDouble) {
                maxValDouble = currentVal;
            }
        }
    }
    EXPECT_GE(minValDouble, 0);
    EXPECT_LE(maxValDouble, 1);
    EXPECT_NEAR(0, extractedDataDouble[0], EPSILONT);
    EXPECT_NEAR(0.63, extractedDataDouble[63], EPSILONT);
    EXPECT_NEAR(1, extractedDataDouble[255], EPSILONT);
    EXPECT_NEAR(1, extractedDataDouble[300], EPSILONT);
    EXPECT_NEAR(0, imageDouble01->adjustIntensity(-43.78), EPSILONT);
    EXPECT_NEAR(0, imageDouble01->adjustIntensity(0), EPSILONT);
    EXPECT_NEAR(0.63, imageDouble01->adjustIntensity(0.63), EPSILONT);
    EXPECT_NEAR(1, imageDouble01->adjustIntensity(1), EPSILONT);
    EXPECT_NEAR(1, imageDouble01->adjustIntensity(853.65), EPSILONT);

    IntensityCImage<double> *imageDouble14 = new IntensityCImage<double>(dataDouble14, lattice, nBands, 1, 4);
    extractedDataDouble = imageDouble14->getData();
    minValDouble = DBL_MAX;
    maxValDouble = DBL_MIN;
    for (int i = 0; i < nTotal; i++) {
        double currentVal = extractedDataDouble[i];
        if (currentVal < minValDouble) {
            minValDouble = currentVal;
        }
        else {
            if (currentVal > maxValDouble) {
                maxValDouble = currentVal;
            }
        }
    }
    EXPECT_GE(minValDouble, 1);
    EXPECT_LE(maxValDouble, 4);
    EXPECT_NEAR(1, extractedDataDouble[0], EPSILONT);
    EXPECT_NEAR(1, extractedDataDouble[63], EPSILONT);
    EXPECT_NEAR(1, extractedDataDouble[100], EPSILONT);
    EXPECT_NEAR(2.55, extractedDataDouble[255], EPSILONT);
    EXPECT_NEAR(3, extractedDataDouble[300], EPSILONT);
    EXPECT_NEAR(4, extractedDataDouble[400], EPSILONT);
    EXPECT_NEAR(4, extractedDataDouble[500], EPSILONT);
    EXPECT_NEAR(1, imageDouble14->adjustIntensity(-43.78), EPSILONT);
    EXPECT_NEAR(1, imageDouble14->adjustIntensity(0), EPSILONT);
    EXPECT_NEAR(1, imageDouble14->adjustIntensity(1), EPSILONT);
    EXPECT_NEAR(3.14, imageDouble14->adjustIntensity(3.14), EPSILONT);
    EXPECT_NEAR(4, imageDouble14->adjustIntensity(4), EPSILONT);
    EXPECT_NEAR(4, imageDouble14->adjustIntensity(853.65), EPSILONT);

    delete imageUint8Full;
    delete imageUint8Half;
    delete imageDouble01;
    delete imageDouble14;

}

TEST(IntensityCImage, manipulation) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    int nTotal = nElements * nBands;
    uint8 dataUint8[nTotal];
    double dataDouble[nTotal];
    for (int i = 0; i < nTotal; i++) {
        dataUint8[i] = 0;
        dataDouble[i] = 0;
    }

    IntensityCImage<uint8> *imageUint8 = new IntensityCImage<uint8>(dataUint8, lattice, nBands, 0, 255);
    uint8 newValuesUint8[] = {11, 22, 33};
    vector<uint8> newIntensityValuesUint8(newValuesUint8, newValuesUint8 + 3);

    int elementIndex = 42;
    vector<uint8> currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], 0);
    EXPECT_EQ(currentIntensityValuesUint8[1], 0);
    EXPECT_EQ(currentIntensityValuesUint8[2], 0);
    imageUint8->setElement(elementIndex, newIntensityValuesUint8);
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], newIntensityValuesUint8[0]);
    EXPECT_EQ(currentIntensityValuesUint8[1], newIntensityValuesUint8[1]);
    EXPECT_EQ(currentIntensityValuesUint8[2], newIntensityValuesUint8[2]);

    elementIndex = 43;
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], 0);
    EXPECT_EQ(currentIntensityValuesUint8[1], 0);
    EXPECT_EQ(currentIntensityValuesUint8[2], 0);
    imageUint8->setElement(imageUint8->indexToR(elementIndex), imageUint8->indexToC(elementIndex), imageUint8->indexToL(elementIndex), newIntensityValuesUint8);
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], newIntensityValuesUint8[0]);
    EXPECT_EQ(currentIntensityValuesUint8[1], newIntensityValuesUint8[1]);
    EXPECT_EQ(currentIntensityValuesUint8[2], newIntensityValuesUint8[2]);

    elementIndex = 44;
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], 0);
    EXPECT_EQ(currentIntensityValuesUint8[1], 0);
    EXPECT_EQ(currentIntensityValuesUint8[2], 0);
    imageUint8->setElement(elementIndex, 0, newIntensityValuesUint8[0]);
    imageUint8->setElement(elementIndex, 1, newIntensityValuesUint8[1]);
    imageUint8->setElement(elementIndex, 2, newIntensityValuesUint8[2]);
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], newIntensityValuesUint8[0]);
    EXPECT_EQ(currentIntensityValuesUint8[1], newIntensityValuesUint8[1]);
    EXPECT_EQ(currentIntensityValuesUint8[2], newIntensityValuesUint8[2]);

    elementIndex = 45;
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], 0);
    EXPECT_EQ(currentIntensityValuesUint8[1], 0);
    EXPECT_EQ(currentIntensityValuesUint8[2], 0);
    imageUint8->setElement(imageUint8->indexToR(elementIndex), imageUint8->indexToC(elementIndex), imageUint8->indexToL(elementIndex), 0, newIntensityValuesUint8[0]);
    imageUint8->setElement(imageUint8->indexToR(elementIndex), imageUint8->indexToC(elementIndex), imageUint8->indexToL(elementIndex), 1, newIntensityValuesUint8[1]);
    imageUint8->setElement(imageUint8->indexToR(elementIndex), imageUint8->indexToC(elementIndex), imageUint8->indexToL(elementIndex), 2, newIntensityValuesUint8[2]);
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], newIntensityValuesUint8[0]);
    EXPECT_EQ(currentIntensityValuesUint8[1], newIntensityValuesUint8[1]);
    EXPECT_EQ(currentIntensityValuesUint8[2], newIntensityValuesUint8[2]);

    elementIndex = 46;
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], 0);
    EXPECT_EQ(currentIntensityValuesUint8[1], 0);
    EXPECT_EQ(currentIntensityValuesUint8[2], 0);
    imageUint8->setElement(elementIndex, 0, -11);
    imageUint8->setElement(elementIndex, 1, 22);
    imageUint8->setElement(elementIndex, 2, 333);
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], 0);
    EXPECT_EQ(currentIntensityValuesUint8[1], 22);
    EXPECT_EQ(currentIntensityValuesUint8[2], 255);

    elementIndex = 47;
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], 0);
    EXPECT_EQ(currentIntensityValuesUint8[1], 0);
    EXPECT_EQ(currentIntensityValuesUint8[2], 0);
    imageUint8->setElement(imageUint8->indexToR(elementIndex), imageUint8->indexToC(elementIndex), imageUint8->indexToL(elementIndex), 0, -11);
    imageUint8->setElement(imageUint8->indexToR(elementIndex), imageUint8->indexToC(elementIndex), imageUint8->indexToL(elementIndex), 1, 22);
    imageUint8->setElement(imageUint8->indexToR(elementIndex), imageUint8->indexToC(elementIndex), imageUint8->indexToL(elementIndex), 2, 333);
    currentIntensityValuesUint8 = (*imageUint8)[elementIndex];
    EXPECT_EQ(currentIntensityValuesUint8[0], 0);
    EXPECT_EQ(currentIntensityValuesUint8[1], 22);
    EXPECT_EQ(currentIntensityValuesUint8[2], 255);



    IntensityCImage<double> *imageDouble = new IntensityCImage<double>(dataDouble, lattice, nBands, 0, 1);
    double newValuesDouble[] = {0.11, 0.22, 0.33};
    vector<double> newIntensityValuesDouble(newValuesDouble, newValuesDouble + 3);

    elementIndex = 42;
    vector<double> currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], 0, EPSILONT);
    imageDouble->setElement(elementIndex, newIntensityValuesDouble);
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], newIntensityValuesDouble[0], EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], newIntensityValuesDouble[1], EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], newIntensityValuesDouble[2], EPSILONT);

    elementIndex = 43;
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], 0, EPSILONT);
    imageDouble->setElement(imageDouble->indexToR(elementIndex), imageDouble->indexToC(elementIndex), imageDouble->indexToL(elementIndex), newIntensityValuesDouble);
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], newIntensityValuesDouble[0], EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], newIntensityValuesDouble[1], EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], newIntensityValuesDouble[2], EPSILONT);

    elementIndex = 44;
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], 0, EPSILONT);
    imageDouble->setElement(elementIndex, 0, newIntensityValuesDouble[0]);
    imageDouble->setElement(elementIndex, 1, newIntensityValuesDouble[1]);
    imageDouble->setElement(elementIndex, 2, newIntensityValuesDouble[2]);
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], newIntensityValuesDouble[0], EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], newIntensityValuesDouble[1], EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], newIntensityValuesDouble[2], EPSILONT);

    elementIndex = 45;
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], 0, EPSILONT);
    imageDouble->setElement(imageDouble->indexToR(elementIndex), imageDouble->indexToC(elementIndex), imageDouble->indexToL(elementIndex), 0, newIntensityValuesDouble[0]);
    imageDouble->setElement(imageDouble->indexToR(elementIndex), imageDouble->indexToC(elementIndex), imageDouble->indexToL(elementIndex), 1, newIntensityValuesDouble[1]);
    imageDouble->setElement(imageDouble->indexToR(elementIndex), imageDouble->indexToC(elementIndex), imageDouble->indexToL(elementIndex), 2, newIntensityValuesDouble[2]);
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], newIntensityValuesDouble[0], EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], newIntensityValuesDouble[1], EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], newIntensityValuesDouble[2], EPSILONT);

    elementIndex = 46;
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], 0, EPSILONT);
    imageDouble->setElement(elementIndex, 0, -0.11);
    imageDouble->setElement(elementIndex, 1, 0.22);
    imageDouble->setElement(elementIndex, 2, 3.33);
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], 0.22, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], 1, EPSILONT);

    elementIndex = 47;
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], 0, EPSILONT);
    imageDouble->setElement(imageDouble->indexToR(elementIndex), imageDouble->indexToC(elementIndex), imageDouble->indexToL(elementIndex), 0, -0.11);
    imageDouble->setElement(imageDouble->indexToR(elementIndex), imageDouble->indexToC(elementIndex), imageDouble->indexToL(elementIndex), 1, 0.22);
    imageDouble->setElement(imageDouble->indexToR(elementIndex), imageDouble->indexToC(elementIndex), imageDouble->indexToL(elementIndex), 2, 3.33);
    currentIntensityValuesDouble = (*imageDouble)[elementIndex];
    EXPECT_NEAR(currentIntensityValuesDouble[0], 0, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[1], 0.22, EPSILONT);
    EXPECT_NEAR(currentIntensityValuesDouble[2], 1, EPSILONT);


    delete imageUint8;
    delete imageDouble;

}