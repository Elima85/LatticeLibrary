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

    EXPECT_NEAR(doubleIW1.getImage()(0, 0), doubleDataRef[0], EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(0, 1), doubleDataRef[nElements], EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(0, 2), doubleDataRef[2 * nElements], EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(103, 0), doubleDataRef[103], EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(103, 1), doubleDataRef[nElements + 103], EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(103, 2), doubleDataRef[2 * nElements + 103], EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(nElements - 1, 0), doubleDataRef[nElements-1], EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(nElements - 1, 1), doubleDataRef[2 * nElements - 1], EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(nElements - 1, 2), doubleDataRef[3 * nElements - 1], EPSILONT);
    EXPECT_NEAR(doubleIW1.getMinIntensity(), 0.0, EPSILONT);
    EXPECT_NEAR(doubleIW1.getMaxIntensity(), 1.0, EPSILONT);

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

    EXPECT_NEAR(doubleIW1.getImage()(0, 0), doubleIWCropped.getImage()(0, 0), EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(0, 1), doubleIWCropped.getImage()(0, 1), EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(0, 2), doubleIWCropped.getImage()(0, 2), EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(103, 0), doubleIWCropped.getImage()(103, 0), EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(103, 1), doubleIWCropped.getImage()(103, 1), EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(103, 2), doubleIWCropped.getImage()(103, 2), EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(nElements - 1, 0), doubleIWCropped.getImage()(nElements - 1, 0), EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(nElements - 1, 1), doubleIWCropped.getImage()(nElements - 1, 1), EPSILONT);
    EXPECT_NEAR(doubleIW1.getImage()(nElements - 1, 2), doubleIWCropped.getImage()(nElements - 1, 2), EPSILONT);

    EXPECT_NEAR(doubleIW2.getImage()(0, 0), doubleIWNormalized.getImage()(0, 0), EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(0, 1), doubleIWNormalized.getImage()(0, 1), EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(0, 2), doubleIWNormalized.getImage()(0, 2), EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(103, 0), doubleIWNormalized.getImage()(103, 0), EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(103, 1), doubleIWNormalized.getImage()(103, 1), EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(103, 2), doubleIWNormalized.getImage()(103, 2), EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(nElements - 1, 0), doubleIWNormalized.getImage()(nElements - 1, 0), EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(nElements - 1, 1), doubleIWNormalized.getImage()(nElements - 1, 1), EPSILONT);
    EXPECT_NEAR(doubleIW2.getImage()(nElements - 1, 2), doubleIWNormalized.getImage()(nElements - 1, 2), EPSILONT);

    EXPECT_NEAR(doubleIW3.getImage()(0, 0), doubleIWRef.getImage()(0, 0), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(0, 1), doubleIWNormalizedBand.getImage()(0, 0), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(0, 1) - doubleIWNormalized.getImage()(0, 1)), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(0, 1) - doubleIWRef.getImage()(0, 1)), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(0, 2), doubleIWRef.getImage()(0, 2), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(103, 0), doubleIWRef.getImage()(103, 0), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(103, 1), doubleIWNormalizedBand.getImage()(103, 0), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(103, 1) - doubleIWNormalized.getImage()(103, 1)), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(103, 1) - doubleIWRef.getImage()(103, 1)), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(103, 2), doubleIWRef.getImage()(103, 2), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(nElements - 1, 0), doubleIWRef.getImage()(nElements - 1, 0), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(nElements - 1, 1), doubleIWNormalizedBand.getImage()(nElements - 1, 0), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(nElements - 1, 1) - doubleIWNormalized.getImage()(nElements - 1, 1)), EPSILONT);
    EXPECT_GT(fabs(doubleIW3.getImage()(nElements - 1, 1) - doubleIWRef.getImage()(nElements - 1, 1)), EPSILONT);
    EXPECT_NEAR(doubleIW3.getImage()(nElements - 1, 2), doubleIWRef.getImage()(nElements - 1, 2), EPSILONT);

}

TEST(IntensityWorkset, limits) {
    
}