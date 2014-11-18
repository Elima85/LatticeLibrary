#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "cimageFCC.h"
#include "exception.h"
#include "filehandling.h"

using namespace CImage;

TEST(CImageFCC, downsample) {

    double gt1[] = {1, 0.5, 1, 0,  1, 0, 1, 0.5};
    double gt2[] = {1, 1, 0.5, 0.5, 1, 1, 0.5, 0.5};
    double gt3[] = {1, 1, 1, 1, 0.5, 0.5, 0.5, 0.5};
    double gt4[] = {0.5, 0, 0.5, 0,  0, 0, 1, 0,   0.5, 0.5, 1, 1,  0, 0, 0.5, 0.5};

    CImageFCC<double> *imFCCLowRes1 = new CImageFCC<double>();
    CImageFCC<double> *imFCCLowRes2 = new CImageFCC<double>();
    CImageFCC<double> *imFCCLowRes3 = new CImageFCC<double>();
    CImageFCC<double> *imFCCLowRes4 = new CImageFCC<double>();
    CImageFCC<double> *imFCCVeryLowRes = new CImageFCC<double>();

    int nRHighRes = 700, nCHighRes = 900, nLHighRes = 700;
    int nTotHighRes = nRHighRes * nCHighRes * nLHighRes;
    char fileName1[] = "FCCveryhighresX.bin";
    char fileName2[] = "FCCveryhighresY.bin";
    char fileName3[] = "FCCveryhighresZ.bin";
    char fileName4[] = "FCCveryhighdoubleband.bin";
    char *filePointer1 = fileName1;
    char *filePointer2 = fileName2;
    char *filePointer3 = fileName3;
    char *filePointer4 = fileName4;
    double *downsampledData1, *downsampledData2, *downsampledData3, *downsampledData4;

    double *data1 = readVolume(filePointer1, nTotHighRes);
    EXPECT_TRUE(data1);
    cout << "Read first file." << endl;
    CImageCC<double> *HighRes1 = new CImageCC<double>(data1, nRHighRes, nCHighRes, nLHighRes, 1, pow(0.005 * FCCPOINTDISTANCE, 3) + 0.000000001 * EPSILONT);
    downsampledData1 = imFCCLowRes1->downsample(HighRes1, 1);
    cout << "Old width: " << HighRes1->getWidth() << endl;
    cout << "Old height: " << HighRes1->getHeight() << endl;
    cout << "Old depth: " << HighRes1->getDepth() << endl;
    cout << "New width: " << imFCCLowRes1->getWidth() << endl;
    cout << "New height: " << imFCCLowRes1->getHeight() << endl;
    cout << "New depth: " << imFCCLowRes1->getDepth() << endl;
    EXPECT_TRUE(downsampledData1);
    EXPECT_EQ(downsampledData1, imFCCLowRes1->getData());
    EXPECT_EQ(6, imFCCLowRes1->getNRows());
    EXPECT_EQ(4, imFCCLowRes1->getNColumns());
    EXPECT_EQ(6, imFCCLowRes1->getNLayers());
    EXPECT_EQ(1, imFCCLowRes1->getNBands());
    EXPECT_NEAR(gt1[0], downsampledData1[57], EPSILONT);
    EXPECT_NEAR(gt1[1], downsampledData1[58], EPSILONT);
    EXPECT_NEAR(gt1[2], downsampledData1[61], EPSILONT);
    EXPECT_NEAR(gt1[3], downsampledData1[62], EPSILONT);
    EXPECT_NEAR(gt1[4], downsampledData1[81], EPSILONT);
    EXPECT_NEAR(gt1[5], downsampledData1[82], EPSILONT);
    EXPECT_NEAR(gt1[6], downsampledData1[85], EPSILONT);
    EXPECT_NEAR(gt1[7], downsampledData1[86], EPSILONT);
    delete HighRes1;
    delete[] data1;

    double *data2 = readVolume(filePointer2, nTotHighRes);
    EXPECT_TRUE(data2);
    cout << "Read second file." << endl;
    CImageCC<double> *HighRes2 = new CImageCC<double>(data2, nRHighRes, nCHighRes, nLHighRes, 1, pow(0.005 * FCCPOINTDISTANCE, 3) + 0.000000001 * EPSILONT);
    downsampledData2 = imFCCLowRes2->downsample(HighRes2, 1);
    EXPECT_TRUE(downsampledData2);
    EXPECT_EQ(downsampledData2, imFCCLowRes2->getData());
    EXPECT_EQ(6, imFCCLowRes2->getNRows());
    EXPECT_EQ(4, imFCCLowRes2->getNColumns());
    EXPECT_EQ(6, imFCCLowRes2->getNLayers());
    EXPECT_EQ(1, imFCCLowRes2->getNBands());
    EXPECT_NEAR(gt2[0], downsampledData2[57], EPSILONT);
    EXPECT_NEAR(gt2[1], downsampledData2[58], EPSILONT);
    EXPECT_NEAR(gt2[2], downsampledData2[61], EPSILONT);
    EXPECT_NEAR(gt2[3], downsampledData2[62], EPSILONT);
    EXPECT_NEAR(gt2[4], downsampledData2[81], EPSILONT);
    EXPECT_NEAR(gt2[5], downsampledData2[82], EPSILONT);
    EXPECT_NEAR(gt2[6], downsampledData2[85], EPSILONT);
    EXPECT_NEAR(gt2[7], downsampledData2[86], EPSILONT);
    delete HighRes2;
    delete[] data2;

    double *data3 = readVolume(filePointer3, nTotHighRes);
    EXPECT_TRUE(data3);
    cout << "Read third file." << endl;
    CImageCC<double> *HighRes3 = new CImageCC<double>(data3, nRHighRes, nCHighRes, nLHighRes, 1, pow(0.005 * FCCPOINTDISTANCE, 3) + 0.000000001 * EPSILONT);
    downsampledData3 = imFCCLowRes3->downsample(HighRes3, 1);
    EXPECT_TRUE(downsampledData3);
    EXPECT_EQ(downsampledData3, imFCCLowRes3->getData());
    EXPECT_EQ(6, imFCCLowRes3->getNRows());
    EXPECT_EQ(4, imFCCLowRes3->getNColumns());
    EXPECT_EQ(6, imFCCLowRes3->getNLayers());
    EXPECT_EQ(1, imFCCLowRes3->getNBands());
    EXPECT_NEAR(gt3[0], downsampledData3[57], EPSILONT);
    EXPECT_NEAR(gt3[1], downsampledData3[58], EPSILONT);
    EXPECT_NEAR(gt3[2], downsampledData3[61], EPSILONT);
    EXPECT_NEAR(gt3[3], downsampledData3[62], EPSILONT);
    EXPECT_NEAR(gt3[4], downsampledData3[81], EPSILONT);
    EXPECT_NEAR(gt3[5], downsampledData3[82], EPSILONT);
    EXPECT_NEAR(gt3[6], downsampledData3[85], EPSILONT);
    EXPECT_NEAR(gt3[7], downsampledData3[86], EPSILONT);
    delete HighRes3;
    delete[] data3;

    double *data4 = readVolume(filePointer4, 2 * nTotHighRes);
    EXPECT_TRUE(data4);
    cout << "Read fourth file." << endl;
    CImageCC<double> *HighRes4 = new CImageCC<double>(data4, nRHighRes, nCHighRes, nLHighRes, 2, pow(0.005 * FCCPOINTDISTANCE, 3) + 0.000000001 * EPSILONT);
    downsampledData4 = imFCCLowRes4->downsample(HighRes4, 1);
    EXPECT_TRUE(downsampledData4);
    EXPECT_EQ(downsampledData4, imFCCLowRes4->getData());
    EXPECT_EQ(6, imFCCLowRes4->getNRows());
    EXPECT_EQ(4, imFCCLowRes4->getNColumns());
    EXPECT_EQ(6, imFCCLowRes4->getNLayers());
    EXPECT_EQ(2, imFCCLowRes4->getNBands());
    EXPECT_NEAR(gt4[0], downsampledData4[57], EPSILONT);
    EXPECT_NEAR(gt4[1], downsampledData4[58], EPSILONT);
    EXPECT_NEAR(gt4[2], downsampledData4[61], EPSILONT);
    EXPECT_NEAR(gt4[3], downsampledData4[62], EPSILONT);
    EXPECT_NEAR(gt4[4], downsampledData4[81], EPSILONT);
    EXPECT_NEAR(gt4[5], downsampledData4[82], EPSILONT);
    EXPECT_NEAR(gt4[6], downsampledData4[85], EPSILONT);
    EXPECT_NEAR(gt4[7], downsampledData4[86], EPSILONT);

    EXPECT_NEAR(gt4[8], downsampledData4[57 + 144], EPSILONT);
    EXPECT_NEAR(gt4[9], downsampledData4[58 + 144], EPSILONT);
    EXPECT_NEAR(gt4[10], downsampledData4[61 + 144], EPSILONT);
    EXPECT_NEAR(gt4[11], downsampledData4[62 + 144], EPSILONT);
    EXPECT_NEAR(gt4[12], downsampledData4[81 + 144], EPSILONT);
    EXPECT_NEAR(gt4[13], downsampledData4[82 + 144], EPSILONT);
    EXPECT_NEAR(gt4[14], downsampledData4[85 + 144], EPSILONT);
    EXPECT_NEAR(gt4[15], downsampledData4[86 + 144], EPSILONT);
    delete HighRes4;
    delete[] data4;

    EXPECT_THROW(imFCCVeryLowRes->downsample(HighRes1, 100), downsampleException);

    delete imFCCLowRes1;
    delete imFCCLowRes2;
    delete imFCCLowRes3;
    delete imFCCLowRes4;
    delete imFCCVeryLowRes;
    delete[] downsampledData1;
    delete[] downsampledData2;
    delete[] downsampledData3;
    delete[] downsampledData4;

}