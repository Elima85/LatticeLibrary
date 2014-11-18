/*
#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "cimageBCC.h"
#include "exception.h"
#include "filehandling.h"

using namespace CImage;

TEST(CImageBCC, downsample) { // may need a 6 layer image, so that all neighbors exist for the 8 middle spels.

    int nRHighRes = 450, nCHighRes = 450, nLHighRes = 350;
    int nTotHighRes = nRHighRes * nCHighRes * nLHighRes;
    char fileName1[] = "BCCveryhighresX.bin";
    char fileName2[] = "BCCveryhighresY.bin";
    char fileName3[] = "BCCveryhighresZ.bin";
    char fileName4[] = "BCCveryhighresdoubleband.bin";
    char *filePointer1 = fileName1;
    char *filePointer2 = fileName2;
    char *filePointer3 = fileName3;
    char *filePointer4 = fileName4;
    double *data1 = readVolume(filePointer1, nTotHighRes);
    double *data2 = readVolume(filePointer2, nTotHighRes);
    double *data3 = readVolume(filePointer3, nTotHighRes);
    double *data4 = readVolume(filePointer4, 2 * nTotHighRes);
    CImageCC<double> *HighRes1 = new CImageCC<double>(data1, nRHighRes, nCHighRes, nLHighRes, 1, pow(0.01 * BCCSQFACEDISTANCE, 3) + 0.000000001 * EPSILONT);
    CImageCC<double> *HighRes2 = new CImageCC<double>(data2, nRHighRes, nCHighRes, nLHighRes, 1, pow(0.01 * BCCSQFACEDISTANCE, 3) + 0.000000001 * EPSILONT);
    CImageCC<double> *HighRes3 = new CImageCC<double>(data3, nRHighRes, nCHighRes, nLHighRes, 1, pow(0.01 * BCCSQFACEDISTANCE, 3) + 0.000000001 * EPSILONT);
    CImageCC<double> *HighRes4 = new CImageCC<double>(data4, nRHighRes, nCHighRes, nLHighRes, 2, pow(0.01 * BCCSQFACEDISTANCE, 3) + 0.000000001 * EPSILONT);

    double gt1[] = {1, 1, 1, 1,  1, 0.5, 1, 0.5};
    double gt2[] = {1, 1, 1, 1,  1, 1, 0.5, 0.5};
    double gt3[] = {1, 1, 1, 1,  0.5, 0.5, 0.5, 0.5};
    double gt4[] = {0.5, 0, 1, 0.5,  0.5, 0, 1, 0.5,   0.5, 0.5, 1, 1,  0.5, 0.5, 1, 1};

    CImageBCC<double> *imBCCLowRes1 = new CImageBCC<double>();
    CImageBCC<double> *imBCCLowRes2 = new CImageBCC<double>();
    CImageBCC<double> *imBCCLowRes3 = new CImageBCC<double>();
    CImageBCC<double> *imBCCLowRes4 = new CImageBCC<double>();
    CImageBCC<double> *imBCCVeryLowRes = new CImageBCC<double>();

    double *downsampledData1, *downsampledData2, *downsampledData3, *downsampledData4;

    downsampledData1 = imBCCLowRes1->downsample(HighRes1, 1);
    cout << "Old width: " << HighRes1->getWidth() << endl;
    cout << "Old height: " << HighRes1->getHeight() << endl;
    cout << "Old depth: " << HighRes1->getDepth() << endl;
    cout << "New width: " << imBCCLowRes1->getWidth() << endl;
    cout << "New height: " << imBCCLowRes1->getHeight() << endl;
    cout << "New depth: " << imBCCLowRes1->getDepth() << endl;
    EXPECT_TRUE(downsampledData1);
    EXPECT_EQ(downsampledData1, imBCCLowRes1->getData());
    EXPECT_EQ(4, imBCCLowRes1->getNRows());
    EXPECT_EQ(4, imBCCLowRes1->getNColumns());
    EXPECT_EQ(6, imBCCLowRes1->getNLayers());
    EXPECT_EQ(1, imBCCLowRes1->getNBands());
    EXPECT_NEAR(gt1[0], downsampledData1[37], EPSILONT);
    EXPECT_NEAR(gt1[1], downsampledData1[38], EPSILONT);
    EXPECT_NEAR(gt1[2], downsampledData1[41], EPSILONT);
    EXPECT_NEAR(gt1[3], downsampledData1[42], EPSILONT);
    EXPECT_NEAR(gt1[4], downsampledData1[53], EPSILONT);
    EXPECT_NEAR(gt1[5], downsampledData1[54], EPSILONT);
    EXPECT_NEAR(gt1[6], downsampledData1[57], EPSILONT);
    EXPECT_NEAR(gt1[7], downsampledData1[58], EPSILONT);

    downsampledData2 = imBCCLowRes2->downsample(HighRes2, 1);
    EXPECT_TRUE(downsampledData2);
    EXPECT_EQ(downsampledData2, imBCCLowRes2->getData());
    EXPECT_EQ(4, imBCCLowRes2->getNRows());
    EXPECT_EQ(4, imBCCLowRes2->getNColumns());
    EXPECT_EQ(6, imBCCLowRes2->getNLayers());
    EXPECT_EQ(1, imBCCLowRes2->getNBands());
    EXPECT_NEAR(gt2[0], downsampledData2[37], EPSILONT);
    EXPECT_NEAR(gt2[1], downsampledData2[38], EPSILONT);
    EXPECT_NEAR(gt2[2], downsampledData2[41], EPSILONT);
    EXPECT_NEAR(gt2[3], downsampledData2[42], EPSILONT);
    EXPECT_NEAR(gt2[4], downsampledData2[53], EPSILONT);
    EXPECT_NEAR(gt2[5], downsampledData2[54], EPSILONT);
    EXPECT_NEAR(gt2[6], downsampledData2[57], EPSILONT);
    EXPECT_NEAR(gt2[7], downsampledData2[58], EPSILONT);

    downsampledData3 = imBCCLowRes3->downsample(HighRes3, 1);
    EXPECT_TRUE(downsampledData3);
    EXPECT_EQ(downsampledData3, imBCCLowRes3->getData());
    EXPECT_EQ(4, imBCCLowRes3->getNRows());
    EXPECT_EQ(4, imBCCLowRes3->getNColumns());
    EXPECT_EQ(6, imBCCLowRes3->getNLayers());
    EXPECT_EQ(1, imBCCLowRes3->getNBands());
    EXPECT_NEAR(gt3[0], downsampledData3[37], EPSILONT);
    EXPECT_NEAR(gt3[1], downsampledData3[38], EPSILONT);
    EXPECT_NEAR(gt3[2], downsampledData3[41], EPSILONT);
    EXPECT_NEAR(gt3[3], downsampledData3[42], EPSILONT);
    EXPECT_NEAR(gt3[4], downsampledData3[53], EPSILONT);
    EXPECT_NEAR(gt3[5], downsampledData3[54], EPSILONT);
    EXPECT_NEAR(gt3[6], downsampledData3[57], EPSILONT);
    EXPECT_NEAR(gt3[7], downsampledData3[58], EPSILONT);

    downsampledData4 = imBCCLowRes4->downsample(HighRes4, 1);
    EXPECT_TRUE(downsampledData4);
    EXPECT_EQ(downsampledData4, imBCCLowRes4->getData());
    EXPECT_EQ(4, imBCCLowRes4->getNRows());
    EXPECT_EQ(4, imBCCLowRes4->getNColumns());
    EXPECT_EQ(6, imBCCLowRes4->getNLayers());
    EXPECT_EQ(2, imBCCLowRes4->getNBands());
    EXPECT_NEAR(gt4[0], downsampledData4[37], EPSILONT);
    EXPECT_NEAR(gt4[1], downsampledData4[38], EPSILONT);
    EXPECT_NEAR(gt4[2], downsampledData4[41], EPSILONT);
    EXPECT_NEAR(gt4[3], downsampledData4[42], EPSILONT);
    EXPECT_NEAR(gt4[4], downsampledData4[53], EPSILONT);
    EXPECT_NEAR(gt4[5], downsampledData4[54], EPSILONT);
    EXPECT_NEAR(gt4[6], downsampledData4[57], EPSILONT);
    EXPECT_NEAR(gt4[7], downsampledData4[58], EPSILONT);

    EXPECT_NEAR(gt4[8], downsampledData4[37 + 96], EPSILONT);
    EXPECT_NEAR(gt4[9], downsampledData4[38 + 96], EPSILONT);
    EXPECT_NEAR(gt4[10], downsampledData4[41 + 96], EPSILONT);
    EXPECT_NEAR(gt4[11], downsampledData4[42 + 96], EPSILONT);
    EXPECT_NEAR(gt4[12], downsampledData4[53 + 96], EPSILONT);
    EXPECT_NEAR(gt4[13], downsampledData4[54 + 96], EPSILONT);
    EXPECT_NEAR(gt4[14], downsampledData4[57 + 96], EPSILONT);
    EXPECT_NEAR(gt4[15], downsampledData4[58 + 96], EPSILONT);

    EXPECT_THROW(imBCCVeryLowRes->downsample(HighRes1, 100), downsampleException);

    delete HighRes1;
    delete HighRes2;
    delete HighRes3;
    delete HighRes4;
    delete imBCCLowRes1;
    delete imBCCLowRes2;
    delete imBCCLowRes3;
    delete imBCCLowRes4;
    delete imBCCVeryLowRes;
    delete[] data1;
    delete[] data2;
    delete[] data3;
    delete[] data4;
    delete[] downsampledData1;
    delete[] downsampledData2;
    delete[] downsampledData3;
    delete[] downsampledData4;

}*/
