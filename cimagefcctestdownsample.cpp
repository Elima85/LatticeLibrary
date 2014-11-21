#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "cimageFCC.h"
#include "exception.h"
#include "filehandling.h"

using namespace CImage;

TEST(CImageFCC, downsample) {

    int nRHighRes = 350, nCHighRes = 450, nLHighRes = 350;
    int nTotHighRes = nRHighRes * nCHighRes * nLHighRes;
    double volumeFactor = 0.01;

    char fileName1[] = "FCChighresX.bin";
    char *filePointer1 = fileName1;
    double *data1 = readVolume(filePointer1, nTotHighRes);
    EXPECT_TRUE(data1);
    CImageCC<double> *HighRes1 = new CImageCC<double>(data1, nRHighRes, nCHighRes, nLHighRes, 1, pow(volumeFactor * FCCPOINTDISTANCE, 3) + 0.000000001 * EPSILONT);
    double gt1[] = {1, 0.5, 1, 0,  1, 0, 1, 0.5};

    CImageFCC<double> *imFCCLowRes1 = new CImageFCC<double>();
    double *downsampledData1 = imFCCLowRes1->downsample(HighRes1, 1);
    EXPECT_TRUE(downsampledData1);

    cout << "Old width: " << HighRes1->getWidth() << endl;
    cout << "Old height: " << HighRes1->getHeight() << endl;
    cout << "Old depth: " << HighRes1->getDepth() << endl;
    cout << "New width: " << imFCCLowRes1->getWidth() << endl;
    cout << "New height: " << imFCCLowRes1->getHeight() << endl;
    cout << "New depth: " << imFCCLowRes1->getDepth() << endl;
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
    delete imFCCLowRes1;
    delete HighRes1;
    delete[] data1;
    delete[] downsampledData1;

    CImageFCC<double> *imFCCLowRes2 = new CImageFCC<double>();
    char fileName2[] = "FCChighresY.bin";
    char *filePointer2 = fileName2;
    double *data2 = readVolume(filePointer2, nTotHighRes);
    EXPECT_TRUE(data2);
    cout << "Read second file." << endl;
    CImageCC<double> *HighRes2 = new CImageCC<double>(data2, nRHighRes, nCHighRes, nLHighRes, 1, pow(volumeFactor * FCCPOINTDISTANCE, 3) + 0.000000001 * EPSILONT);
    double gt2[] = {1, 1, 0.5, 0.5, 1, 1, 0.5, 0.5};
    double *downsampledData2 = imFCCLowRes2->downsample(HighRes2, 1);
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
    delete imFCCLowRes2;
    delete[] downsampledData2;
    delete[] data2;

    CImageFCC<double> *imFCCLowRes3 = new CImageFCC<double>();
    char fileName3[] = "FCChighresZ.bin";
    char *filePointer3 = fileName3;double *data3 = readVolume(filePointer3, nTotHighRes);
    EXPECT_TRUE(data3);
    cout << "Read third file." << endl;
    CImageCC<double> *HighRes3 = new CImageCC<double>(data3, nRHighRes, nCHighRes, nLHighRes, 1, pow(volumeFactor * FCCPOINTDISTANCE, 3) + 0.000000001 * EPSILONT);
    double gt3[] = {1, 1, 1, 1, 0.5, 0.5, 0.5, 0.5};
    double *downsampledData3 = imFCCLowRes3->downsample(HighRes3, 1);
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
    delete imFCCLowRes3;
    delete[] downsampledData3;
    delete[] data3;

    CImageFCC<double> *imFCCLowRes4 = new CImageFCC<double>();
    char fileName4[] = "FCChighresdoubleband.bin";
    char *filePointer4 = fileName4;
    double *data4 = readVolume(filePointer4, 2 * nTotHighRes);
    EXPECT_TRUE(data4);
    cout << "Read fourth file." << endl;
    CImageCC<double> *HighRes4 = new CImageCC<double>(data4, nRHighRes, nCHighRes, nLHighRes, 2, pow(volumeFactor * FCCPOINTDISTANCE, 3) + 0.000000001 * EPSILONT);
    double gt4[] = {0.5, 0, 0.5, 0,  0, 0, 1, 0,   0.5, 0.5, 1, 1,  0, 0, 0.5, 0.5};
    doube *downsampledData4 = imFCCLowRes4->downsample(HighRes4, 1);
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
    delete imFCCLowRes4;
    delete[] downsampledData4;
    delete[] data4;

    CImageFCC<double> *imFCCVeryLowRes = new CImageFCC<double>();
    EXPECT_THROW(imFCCVeryLowRes->downsample(HighRes1, 1000), downsampleException);
    delete imFCCVeryLowRes;

}