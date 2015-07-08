#include "gtest/gtest.h"
#include "intensityworkset.h"
#include "defs.h"

using namespace LatticeLib;

TEST(IntensityWorkset, initialization) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    int nTotal = nElements * nBands;
    double doubleDataRef[nTotal];
    double doubleData1[nTotal];
    double doubleData2[nTotal];
    double doubleData3[nTotal];
    for (int i = 0; i < nTotal; i++) {
        doubleDataRef[i] = double(i);
        doubleData1[i] = double(i);
        doubleData2[i] = double(i);
        doubleData3[i] = double(i);
    }
    Image<double> doubleImage1(doubleData1, lattice, nBands);
    Image<double> doubleImage2(doubleData2, lattice, nBands);
    Image<double> doubleImage3(doubleData3, lattice, nBands);

    IntensityWorkset<double> doubleIW1(doubleImage1, 0.0, 1.0, none);
    IntensityWorkset<double> doubleIW2(doubleImage2, 0.0, 1.0, crop);
    IntensityWorkset<double> doubleIW3(doubleImage3, 0.0, 1.0, normalize);

    EXPECT_EQ(long(doubleIW1.getImage().getData()), long(doubleData1));
    double sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData1[dataIndex] - doubleDataRef[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);
    EXPECT_NEAR(doubleIW1.getMinIntensity(), 0.0, EPSILONT);
    EXPECT_NEAR(doubleIW1.getMaxIntensity(), 1.0, EPSILONT);


    EXPECT_EQ(long(doubleIW2.getImage().getData()), long(doubleData2));
    sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + doubleData2[dataIndex];
    }
    EXPECT_NEAR(sum, nTotal - 1, EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(0, 0), 0, EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(0, 1), 1, EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(0, 2), 1, EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(103, 0), 1, EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(103, 1), 1, EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(103, 2), 1, EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(nElements - 1, 0), 1, EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(nElements - 1, 1), 1, EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(nElements - 1, 2), 1, EPSILONT);
    EXPECT_NEAR(doubleIW2.getMinIntensity(), 0.0, EPSILONT);
    EXPECT_NEAR(doubleIW2.getMaxIntensity(), 1.0, EPSILONT);

    EXPECT_NEAR(doubleIW3.getImage()(0, 0), 0, EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(0, 1) / doubleIW3.getImage()(0, 2), doubleDataRef[nElements] / doubleDataRef[2 * nElements], EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(0, 1) - doubleDataRef[nElements]), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(0, 2) - doubleDataRef[2 * nElements]), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(103, 0) / doubleIW3.getImage()(103, 1), doubleDataRef[103] / doubleDataRef[nElements + 103], EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(103, 1) / doubleIW3.getImage()(103, 2), doubleDataRef[nElements + 103] / doubleDataRef[2 * nElements + 103], EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(103, 0) - doubleDataRef[103]), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(103, 1) - doubleDataRef[nElements + 103]), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(103, 2) - doubleDataRef[2 * nElements + 103]), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(nElements - 1, 0) / doubleIW3.getImage()(nElements - 1, 1), doubleDataRef[nElements - 1] / doubleDataRef[2 * nElements - 1], EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(nElements - 1, 0) - doubleDataRef[nElements - 1]), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(nElements - 1, 1) - doubleDataRef[2 * nElements - 1]), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(nElements - 1, 2), 1, EPSILONT);
    EXPECT_NEAR(doubleIW3.getMinIntensity(), 0.0, EPSILONT);
    EXPECT_NEAR(doubleIW3.getMaxIntensity(), 1.0, EPSILONT);

    IntensityWorkset<double> doubleIW4(doubleIW3);
    EXPECT_NEAR(doubleIW4.getImage()(0, 0), doubleIW3.getImage()(0, 0), EPSILONT);
    EXPECT_NEAR(doubleIW4.getImage()(0, 1), doubleIW3.getImage()(0, 1), EPSILONT);
    EXPECT_NEAR(doubleIW4.getImage()(0, 2), doubleIW3.getImage()(0, 2), EPSILONT);
    EXPECT_NEAR(doubleIW4.getImage()(103, 0), doubleIW3.getImage()(103, 0), EPSILONT);
    EXPECT_NEAR(doubleIW4.getImage()(103, 1), doubleIW3.getImage()(103, 1), EPSILONT);
    EXPECT_NEAR(doubleIW4.getImage()(103, 2), doubleIW3.getImage()(103, 2), EPSILONT);
    EXPECT_NEAR(doubleIW4.getImage()(nElements - 1, 0), doubleIW3.getImage()(nElements - 1, 0), EPSILONT);
    EXPECT_NEAR(doubleIW4.getImage()(nElements - 1, 1), doubleIW3.getImage()(nElements - 1, 1), EPSILONT);
    EXPECT_NEAR(doubleIW4.getImage()(nElements - 1, 2), doubleIW3.getImage()(nElements - 1, 2), EPSILONT);
    EXPECT_NEAR(doubleIW4.getMinIntensity(), doubleIW2.getMinIntensity(), EPSILONT);
    EXPECT_NEAR(doubleIW4.getMaxIntensity(), doubleIW2.getMaxIntensity(), EPSILONT);
}

TEST(IntensityWorkset, normalization) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    int nBands = 3;
    int nTotal = nElements * nBands;
    double doubleData1[nTotal];
    double doubleData2[nTotal];
    double doubleData3[nTotal];
    double doubleData4[nTotal];
    double doubleData5[nTotal];
    double doubleData6[nTotal];
    double doubleData7[nElements];
    for (int i = 0; i < nTotal; i++) {
        doubleData1[i] = double(i);
        doubleData2[i] = double(i);
        doubleData3[i] = double(i);
        doubleData4[i] = double(i);
        doubleData5[i] = double(i);
        doubleData6[i] = double(i);
    }
    for (int i = 0; i < nElements; i++) {
        doubleData7[i] = double(i + nElements);
    }
    Image<double> doubleImage1(doubleData1, lattice, nBands);
    Image<double> doubleImage2(doubleData2, lattice, nBands);
    Image<double> doubleImage3(doubleData3, lattice, nBands);
    Image<double> doubleImage4(doubleData4, lattice, nBands);
    Image<double> doubleImage5(doubleData5, lattice, nBands);
    Image<double> doubleImage6(doubleData6, lattice, nBands);
    Image<double> doubleImage7(doubleData7, lattice, 1);

    IntensityWorkset<double> doubleIW1(doubleImage1, 0.0, 10.0, none);
    IntensityWorkset<double> doubleIW2(doubleImage2, 0.0, 10.0, none);
    IntensityWorkset<double> doubleIW3(doubleImage3, 0.0, 10.0, none);
    IntensityWorkset<double> doubleIWCropped(doubleImage4, 0.0, 10.0, crop);
    IntensityWorkset<double> doubleIWNormalized(doubleImage5, 0.0, 10.0, normalize);
    IntensityWorkset<double> doubleIWRef(doubleImage6, 0.0, 10.0, none);
    IntensityWorkset<double> doubleIWNormalizedBand(doubleImage7, 0.0, 10.0, normalize);

    doubleIW1.cropIntensities();
    doubleIW2.normalizeIntensities();
    doubleIW3.normalizeBand(1);

    EXPECT_EQ(long(doubleIW1.getImage().getData()), long(doubleData1));
    EXPECT_EQ(long(doubleIWCropped.getImage().getData()), long(doubleData4));
    double sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData1[dataIndex] - doubleData4[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

    EXPECT_EQ(long(doubleIW2.getImage().getData()), long(doubleData2));
    EXPECT_EQ(long(doubleIWNormalized.getImage().getData()), long(doubleData5));
    sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData2[dataIndex] - doubleData5[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

    EXPECT_EQ(long(doubleIW3.getImage().getData()), long(doubleData3));
    EXPECT_EQ(long(doubleIWRef.getImage().getData()), long(doubleData6));
    EXPECT_EQ(long(doubleIWNormalizedBand.getImage().getData()), long(doubleData7));
    // first band
    sum = 0;
    for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
        sum = sum + fabs(doubleData3[dataIndex] - doubleData6[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);
    // second band
    sum = 0;
    for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
        sum = sum + fabs(doubleData3[nElements + dataIndex] - doubleData7[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);
    sum = 0;
    for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
        sum = sum + fabs(doubleData3[nElements + dataIndex] - doubleData5[dataIndex]);
    }
    EXPECT_GT(sum, EPSILONT);
    // third band
    sum = 0;
    for (int dataIndex = 2 * nElements; dataIndex < 3 * nElements; dataIndex++) {
        sum = sum + fabs(doubleData3[dataIndex] - doubleData6[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

}

TEST(IntensityWorkset, limits) {

    int nRows = 5;
    int nColumns = 6;
    int nLayers = 7;
    int nElements = nRows * nColumns * nLayers;
    double scaleFactor = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, scaleFactor);

    double minVal = 0.0;
    double minValLow = -2.0;
    double minValHigh = 3.0;
    double maxVal = 10.0;
    double maxValLow = 5.0;
    double maxValHigh = 20.0;

    int nBands = 3;
    int nTotal = nElements * nBands;
    double doubleData1[nTotal];
    double doubleData2[nTotal];
    double doubleData3[nTotal];
    double doubleData4[nTotal];
    double doubleData5[nTotal];
    double doubleData6[nTotal];
    double doubleData7[nTotal];
    double doubleData8[nTotal];
    double doubleData9[nTotal];
    for (int i = 0; i < nTotal; i++) {
        double value = double(i % int(maxVal + 1.0));
        doubleData1[i] = value;
        doubleData2[i] = value;
        doubleData3[i] = value;
        doubleData4[i] = value;
        doubleData5[i] = value;
        doubleData6[i] = value;
        doubleData7[i] = value;
        doubleData8[i] = value;
        doubleData9[i] = value;
    }

    Image<double> doubleImage1(doubleData1, lattice, nBands);
    Image<double> doubleImage2(doubleData2, lattice, nBands);
    Image<double> doubleImage3(doubleData3, lattice, nBands);
    Image<double> doubleImage4(doubleData4, lattice, nBands);
    Image<double> doubleImage5(doubleData5, lattice, nBands);
    Image<double> doubleImage6(doubleData6, lattice, nBands);
    Image<double> doubleImage7(doubleData7, lattice, nBands);
    Image<double> doubleImage8(doubleData8, lattice, nBands);
    Image<double> doubleImage9(doubleData9, lattice, nBands);

    // Crop
    IntensityWorkset<double> doubleIW1(doubleImage1, minVal, maxVal, none);
    IntensityWorkset<double> doubleIWRef(doubleImage3, minVal, maxVal, none); // untouched
    IntensityWorkset<double> doubleIWCroppedHighHigh(doubleImage4, minValHigh, maxVal, crop); // cropped, minValHigh, maxVal
    IntensityWorkset<double> doubleIWCroppedHighLow(doubleImage5, minValHigh, maxValLow, crop); // cropped, minValHigh, maxValLow

    doubleIW1.setMinIntensity(minValLow,crop);
    EXPECT_NEAR(doubleIW1.getMinIntensity(), minValLow, EPSILONT);
    EXPECT_NEAR(doubleIW1.getMaxIntensity(), maxVal, EPSILONT);
    double sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData1[dataIndex] - doubleData3[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

    doubleIW1.setMaxIntensity(maxValHigh, crop);
    EXPECT_NEAR(doubleIW1.getMinIntensity(), minValLow, EPSILONT);
    EXPECT_NEAR(doubleIW1.getMaxIntensity(), maxValHigh, EPSILONT);
    sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData1[dataIndex] - doubleData3[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

    doubleIW1.setMinIntensity(minValHigh, crop);
    EXPECT_NEAR(doubleIW1.getMinIntensity(), minValHigh, EPSILONT);
    EXPECT_NEAR(doubleIW1.getMaxIntensity(), maxValHigh, EPSILONT);
    sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData1[dataIndex] - doubleData4[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

    doubleIW1.setMaxIntensity(maxValLow, crop);
    EXPECT_NEAR(doubleIW1.getMinIntensity(), minValHigh, EPSILONT);
    EXPECT_NEAR(doubleIW1.getMaxIntensity(), maxValLow, EPSILONT);
    sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData1[dataIndex] - doubleData5[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

    // normalize
    IntensityWorkset<double> doubleIW2(doubleImage2, minVal, maxVal, none);
    IntensityWorkset<double> doubleIWNormalizedLowNormal(doubleImage6, minValLow, maxVal, normalize); // normalized, minValLow, maxVal
    IntensityWorkset<double> doubleIWNormalizedLowHigh(doubleImage7, minValLow, maxValHigh, normalize); // normalized, minValLow, maxValHigh
    IntensityWorkset<double> doubleIWNormalizedHighHigh(doubleImage8, minValHigh, maxValHigh, normalize); // normalized, minValHigh, maxValHigh
    IntensityWorkset<double> doubleIWNormalizedHighLow(doubleImage9, minValHigh, maxValLow, normalize); // normalized, minValHigh, maxValLow

    doubleIW2.setMinIntensity(minValLow, normalize);
    EXPECT_NEAR(doubleIW2.getMinIntensity(), minValLow, EPSILONT);
    EXPECT_NEAR(doubleIW2.getMaxIntensity(), maxVal, EPSILONT);
    sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData2[dataIndex] - doubleData6[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

    doubleIW2.setMaxIntensity(maxValHigh, normalize);
    EXPECT_NEAR(doubleIW2.getMinIntensity(), minValLow, EPSILONT);
    EXPECT_NEAR(doubleIW2.getMaxIntensity(), maxValHigh, EPSILONT);
    sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData2[dataIndex] - doubleData7[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

    doubleIW2.setMinIntensity(minValHigh, normalize);
    EXPECT_NEAR(doubleIW2.getMinIntensity(), minValHigh, EPSILONT);
    EXPECT_NEAR(doubleIW2.getMaxIntensity(), maxValHigh, EPSILONT);
    sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData2[dataIndex] - doubleData8[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);

    doubleIW2.setMaxIntensity(maxValLow, normalize);
    EXPECT_NEAR(doubleIW2.getMinIntensity(), minValHigh, EPSILONT);
    EXPECT_NEAR(doubleIW2.getMaxIntensity(), maxValLow, EPSILONT);
    sum = 0;
    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        sum = sum + fabs(doubleData2[dataIndex] - doubleData9[dataIndex]);
    }
    EXPECT_LT(sum, EPSILONT);
}