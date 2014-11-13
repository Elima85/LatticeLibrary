#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "exception.h"
#include "filehandling.h"

using namespace CImage;

TEST(CImageCC, downsample) {

    //cout << "Inside TEST(CImageCC, downsample)" << endl;

    int nRHighRes = 120, nCHighRes = 10, nLHighRes = 10, nBHighRes = 2;
    int nRLowRes = 24, nCLowRes = 2, nLLowRes = 2, nBLowRes = 2;
    int nTotHighRes = nRHighRes * nCHighRes * nLHighRes;
    int nTotLowRes = nRLowRes * nCLowRes * nLHighRes;
//    char filename[] = "y10x10.bin";
    char highResFileName[] = "doubleband.bin";
    char lowResFileName[] = "doubleband125.bin";
//    char *filenamepointer = filename;
    char *highResFilePointer = highResFileName;
    char *lowResFilePointer = lowResFileName;
    double *dataHighRes = readVolume(highResFilePointer, nTotHighRes * nBHighRes);
    double *dataLowRes = readVolume(lowResFilePointer, nTotLowRes * nBLowRes);
    CImageCC<double> *imCCHighRes = new CImageCC<double>(dataHighRes, nRHighRes, nCHighRes, nLHighRes, nBHighRes, 1);

//    double groundTruth1000[12] = {1, 0.99, 0.89, 0.79, 0.69, 0.59, 0.49, 0.39, 0.29, 0.19, 0.09, 0};
//    double groundTruth125[96] = {125, 125, 125, 125, 125, 125, 120, 125, 100, 125, 95, 125, 75, 125, 70, 125, 50, 125, 45, 125, 25, 125, 20, 125, 0, 125, 0, 120, 0, 100, 0, 95, 0, 75, 0, 70, 0, 50, 0, 45, 0, 25, 0, 20, 0, 0, 0, 0, 125, 125, 125, 125, 125, 125, 120, 125, 100, 125, 95, 125, 75, 125, 70, 125, 50, 125, 45, 125, 25, 125, 20, 125, 0, 125, 0, 120, 0, 100, 0, 95, 0, 75, 0, 70, 0, 50, 0, 45, 0, 25, 0, 20, 0, 0, 0, 0};
//    for (int i = 0; i < 96; i++) {
//        groundTruth125[i] = groundTruth125[i] / 125.0;
//    }

    CImageCC<double> *imCCLowRes125 = new CImageCC<double>();
//    CImageCC<double> *imCCLowRes1000 = new CImageCC<double>();
    double *downsampledData = NULL; // *dataLowRes1000 = NULL;

    //cout << "pointer to downsampledData: " << downsampledData << endl;
    //cout << "pointer to dataLowRes1000: " << dataLowRes1000 << endl;

    downsampledData = imCCLowRes125->downsample(imCCHighRes, 125);
//    dataLowRes1000 = imCCLowRes1000->downsample(imCCHighRes, 1000);

    //cout << "pointer to downsampledData: " << downsampledData << endl;
    //cout << "pointer to dataLowRes1000: " << dataLowRes1000 << endl;

    EXPECT_TRUE(downsampledData);
    EXPECT_NEAR(dataLowRes[0], downsampledData[0], EPSILONT);
    EXPECT_NEAR(dataLowRes[1], downsampledData[1], EPSILONT);
    EXPECT_NEAR(dataLowRes[2], downsampledData[2], EPSILONT);
    EXPECT_NEAR(dataLowRes[3], downsampledData[3], EPSILONT);
    EXPECT_NEAR(dataLowRes[4], downsampledData[4], EPSILONT);
    EXPECT_NEAR(dataLowRes[5], downsampledData[5], EPSILONT);
    EXPECT_NEAR(dataLowRes[6], downsampledData[6], EPSILONT);
    EXPECT_NEAR(dataLowRes[7], downsampledData[7], EPSILONT);
    EXPECT_NEAR(dataLowRes[8], downsampledData[8], EPSILONT);
    EXPECT_NEAR(dataLowRes[9], downsampledData[9], EPSILONT);
    EXPECT_NEAR(dataLowRes[10], downsampledData[10], EPSILONT);
    EXPECT_NEAR(dataLowRes[11], downsampledData[11], EPSILONT);
    EXPECT_NEAR(dataLowRes[12], downsampledData[12], EPSILONT);
    EXPECT_NEAR(dataLowRes[13], downsampledData[13], EPSILONT);
    EXPECT_NEAR(dataLowRes[14], downsampledData[14], EPSILONT);
    EXPECT_NEAR(dataLowRes[15], downsampledData[15], EPSILONT);
    EXPECT_NEAR(dataLowRes[16], downsampledData[16], EPSILONT);
    EXPECT_NEAR(dataLowRes[17], downsampledData[17], EPSILONT);
    EXPECT_NEAR(dataLowRes[18], downsampledData[18], EPSILONT);
    EXPECT_NEAR(dataLowRes[19], downsampledData[19], EPSILONT);
    EXPECT_NEAR(dataLowRes[20], downsampledData[20], EPSILONT);
    EXPECT_NEAR(dataLowRes[21], downsampledData[21], EPSILONT);
    EXPECT_NEAR(dataLowRes[22], downsampledData[22], EPSILONT);
    EXPECT_NEAR(dataLowRes[23], downsampledData[23], EPSILONT);
    EXPECT_NEAR(dataLowRes[24], downsampledData[24], EPSILONT);
    EXPECT_NEAR(dataLowRes[25], downsampledData[25], EPSILONT);
    EXPECT_NEAR(dataLowRes[26], downsampledData[26], EPSILONT);
    EXPECT_NEAR(dataLowRes[27], downsampledData[27], EPSILONT);
    EXPECT_NEAR(dataLowRes[28], downsampledData[28], EPSILONT);
    EXPECT_NEAR(dataLowRes[29], downsampledData[29], EPSILONT);
    EXPECT_NEAR(dataLowRes[30], downsampledData[30], EPSILONT);
    EXPECT_NEAR(dataLowRes[31], downsampledData[31], EPSILONT);
    EXPECT_NEAR(dataLowRes[32], downsampledData[32], EPSILONT);
    EXPECT_NEAR(dataLowRes[33], downsampledData[33], EPSILONT);
    EXPECT_NEAR(dataLowRes[34], downsampledData[34], EPSILONT);
    EXPECT_NEAR(dataLowRes[35], downsampledData[35], EPSILONT);
    EXPECT_NEAR(dataLowRes[36], downsampledData[36], EPSILONT);
    EXPECT_NEAR(dataLowRes[37], downsampledData[37], EPSILONT);
    EXPECT_NEAR(dataLowRes[38], downsampledData[38], EPSILONT);
    EXPECT_NEAR(dataLowRes[39], downsampledData[39], EPSILONT);
    EXPECT_NEAR(dataLowRes[40], downsampledData[40], EPSILONT);
    EXPECT_NEAR(dataLowRes[41], downsampledData[41], EPSILONT);
    EXPECT_NEAR(dataLowRes[42], downsampledData[42], EPSILONT);
    EXPECT_NEAR(dataLowRes[43], downsampledData[43], EPSILONT);
    EXPECT_NEAR(dataLowRes[44], downsampledData[44], EPSILONT);
    EXPECT_NEAR(dataLowRes[45], downsampledData[45], EPSILONT);
    EXPECT_NEAR(dataLowRes[46], downsampledData[46], EPSILONT);
    EXPECT_NEAR(dataLowRes[47], downsampledData[47], EPSILONT);
    EXPECT_NEAR(dataLowRes[48], downsampledData[48], EPSILONT);
    EXPECT_NEAR(dataLowRes[49], downsampledData[49], EPSILONT);
    EXPECT_NEAR(dataLowRes[50], downsampledData[50], EPSILONT);
    EXPECT_NEAR(dataLowRes[51], downsampledData[51], EPSILONT);
    EXPECT_NEAR(dataLowRes[52], downsampledData[52], EPSILONT);
    EXPECT_NEAR(dataLowRes[53], downsampledData[53], EPSILONT);
    EXPECT_NEAR(dataLowRes[54], downsampledData[54], EPSILONT);
    EXPECT_NEAR(dataLowRes[55], downsampledData[55], EPSILONT);
    EXPECT_NEAR(dataLowRes[56], downsampledData[56], EPSILONT);
    EXPECT_NEAR(dataLowRes[57], downsampledData[57], EPSILONT);
    EXPECT_NEAR(dataLowRes[58], downsampledData[58], EPSILONT);
    EXPECT_NEAR(dataLowRes[59], downsampledData[59], EPSILONT);
    EXPECT_NEAR(dataLowRes[60], downsampledData[60], EPSILONT);
    EXPECT_NEAR(dataLowRes[61], downsampledData[61], EPSILONT);
    EXPECT_NEAR(dataLowRes[62], downsampledData[62], EPSILONT);
    EXPECT_NEAR(dataLowRes[63], downsampledData[63], EPSILONT);
    EXPECT_NEAR(dataLowRes[64], downsampledData[64], EPSILONT);
    EXPECT_NEAR(dataLowRes[65], downsampledData[65], EPSILONT);
    EXPECT_NEAR(dataLowRes[66], downsampledData[66], EPSILONT);
    EXPECT_NEAR(dataLowRes[67], downsampledData[67], EPSILONT);
    EXPECT_NEAR(dataLowRes[68], downsampledData[68], EPSILONT);
    EXPECT_NEAR(dataLowRes[69], downsampledData[69], EPSILONT);
    EXPECT_NEAR(dataLowRes[70], downsampledData[70], EPSILONT);
    EXPECT_NEAR(dataLowRes[71], downsampledData[71], EPSILONT);
    EXPECT_NEAR(dataLowRes[72], downsampledData[72], EPSILONT);
    EXPECT_NEAR(dataLowRes[73], downsampledData[73], EPSILONT);
    EXPECT_NEAR(dataLowRes[74], downsampledData[74], EPSILONT);
    EXPECT_NEAR(dataLowRes[75], downsampledData[75], EPSILONT);
    EXPECT_NEAR(dataLowRes[76], downsampledData[76], EPSILONT);
    EXPECT_NEAR(dataLowRes[77], downsampledData[77], EPSILONT);
    EXPECT_NEAR(dataLowRes[78], downsampledData[78], EPSILONT);
    EXPECT_NEAR(dataLowRes[79], downsampledData[79], EPSILONT);
    EXPECT_NEAR(dataLowRes[80], downsampledData[80], EPSILONT);
    EXPECT_NEAR(dataLowRes[81], downsampledData[81], EPSILONT);
    EXPECT_NEAR(dataLowRes[82], downsampledData[82], EPSILONT);
    EXPECT_NEAR(dataLowRes[83], downsampledData[83], EPSILONT);
    EXPECT_NEAR(dataLowRes[84], downsampledData[84], EPSILONT);
    EXPECT_NEAR(dataLowRes[85], downsampledData[85], EPSILONT);
    EXPECT_NEAR(dataLowRes[86], downsampledData[86], EPSILONT);
    EXPECT_NEAR(dataLowRes[87], downsampledData[87], EPSILONT);
    EXPECT_NEAR(dataLowRes[88], downsampledData[88], EPSILONT);
    EXPECT_NEAR(dataLowRes[89], downsampledData[89], EPSILONT);
    EXPECT_NEAR(dataLowRes[90], downsampledData[90], EPSILONT);
    EXPECT_NEAR(dataLowRes[91], downsampledData[91], EPSILONT);
    EXPECT_NEAR(dataLowRes[92], downsampledData[92], EPSILONT);
    EXPECT_NEAR(dataLowRes[93], downsampledData[93], EPSILONT);
    EXPECT_NEAR(dataLowRes[94], downsampledData[94], EPSILONT);
    EXPECT_NEAR(dataLowRes[95], downsampledData[95], EPSILONT);

    EXPECT_NEAR(dataLowRes[96], downsampledData[96], EPSILONT);
    EXPECT_NEAR(dataLowRes[97], downsampledData[97], EPSILONT);
    EXPECT_NEAR(dataLowRes[98], downsampledData[98], EPSILONT);
    EXPECT_NEAR(dataLowRes[99], downsampledData[99], EPSILONT);
    EXPECT_NEAR(dataLowRes[100], downsampledData[100], EPSILONT);
    EXPECT_NEAR(dataLowRes[101], downsampledData[101], EPSILONT);
    EXPECT_NEAR(dataLowRes[102], downsampledData[102], EPSILONT);
    EXPECT_NEAR(dataLowRes[103], downsampledData[103], EPSILONT);
    EXPECT_NEAR(dataLowRes[104], downsampledData[104], EPSILONT);
    EXPECT_NEAR(dataLowRes[105], downsampledData[105], EPSILONT);
    EXPECT_NEAR(dataLowRes[106], downsampledData[106], EPSILONT);
    EXPECT_NEAR(dataLowRes[107], downsampledData[107], EPSILONT);
    EXPECT_NEAR(dataLowRes[108], downsampledData[108], EPSILONT);
    EXPECT_NEAR(dataLowRes[109], downsampledData[109], EPSILONT);
    EXPECT_NEAR(dataLowRes[110], downsampledData[110], EPSILONT);
    EXPECT_NEAR(dataLowRes[111], downsampledData[111], EPSILONT);
    EXPECT_NEAR(dataLowRes[112], downsampledData[112], EPSILONT);
    EXPECT_NEAR(dataLowRes[113], downsampledData[113], EPSILONT);
    EXPECT_NEAR(dataLowRes[114], downsampledData[114], EPSILONT);
    EXPECT_NEAR(dataLowRes[115], downsampledData[115], EPSILONT);
    EXPECT_NEAR(dataLowRes[116], downsampledData[116], EPSILONT);
    EXPECT_NEAR(dataLowRes[117], downsampledData[117], EPSILONT);
    EXPECT_NEAR(dataLowRes[118], downsampledData[118], EPSILONT);
    EXPECT_NEAR(dataLowRes[119], downsampledData[119], EPSILONT);
    EXPECT_NEAR(dataLowRes[120], downsampledData[120], EPSILONT);
    EXPECT_NEAR(dataLowRes[121], downsampledData[121], EPSILONT);
    EXPECT_NEAR(dataLowRes[122], downsampledData[122], EPSILONT);
    EXPECT_NEAR(dataLowRes[123], downsampledData[123], EPSILONT);
    EXPECT_NEAR(dataLowRes[124], downsampledData[124], EPSILONT);
    EXPECT_NEAR(dataLowRes[125], downsampledData[125], EPSILONT);
    EXPECT_NEAR(dataLowRes[126], downsampledData[126], EPSILONT);
    EXPECT_NEAR(dataLowRes[127], downsampledData[127], EPSILONT);
    EXPECT_NEAR(dataLowRes[128], downsampledData[128], EPSILONT);
    EXPECT_NEAR(dataLowRes[129], downsampledData[129], EPSILONT);
    EXPECT_NEAR(dataLowRes[130], downsampledData[130], EPSILONT);
    EXPECT_NEAR(dataLowRes[131], downsampledData[131], EPSILONT);
    EXPECT_NEAR(dataLowRes[132], downsampledData[132], EPSILONT);
    EXPECT_NEAR(dataLowRes[133], downsampledData[133], EPSILONT);
    EXPECT_NEAR(dataLowRes[134], downsampledData[134], EPSILONT);
    EXPECT_NEAR(dataLowRes[135], downsampledData[135], EPSILONT);
    EXPECT_NEAR(dataLowRes[136], downsampledData[136], EPSILONT);
    EXPECT_NEAR(dataLowRes[137], downsampledData[137], EPSILONT);
    EXPECT_NEAR(dataLowRes[138], downsampledData[138], EPSILONT);
    EXPECT_NEAR(dataLowRes[139], downsampledData[139], EPSILONT);
    EXPECT_NEAR(dataLowRes[140], downsampledData[140], EPSILONT);
    EXPECT_NEAR(dataLowRes[141], downsampledData[141], EPSILONT);
    EXPECT_NEAR(dataLowRes[142], downsampledData[142], EPSILONT);
    EXPECT_NEAR(dataLowRes[143], downsampledData[143], EPSILONT);
    EXPECT_NEAR(dataLowRes[144], downsampledData[144], EPSILONT);
    EXPECT_NEAR(dataLowRes[145], downsampledData[145], EPSILONT);
    EXPECT_NEAR(dataLowRes[146], downsampledData[146], EPSILONT);
    EXPECT_NEAR(dataLowRes[147], downsampledData[147], EPSILONT);
    EXPECT_NEAR(dataLowRes[148], downsampledData[148], EPSILONT);
    EXPECT_NEAR(dataLowRes[149], downsampledData[149], EPSILONT);
    EXPECT_NEAR(dataLowRes[150], downsampledData[150], EPSILONT);
    EXPECT_NEAR(dataLowRes[151], downsampledData[151], EPSILONT);
    EXPECT_NEAR(dataLowRes[152], downsampledData[152], EPSILONT);
    EXPECT_NEAR(dataLowRes[153], downsampledData[153], EPSILONT);
    EXPECT_NEAR(dataLowRes[154], downsampledData[154], EPSILONT);
    EXPECT_NEAR(dataLowRes[155], downsampledData[155], EPSILONT);
    EXPECT_NEAR(dataLowRes[156], downsampledData[156], EPSILONT);
    EXPECT_NEAR(dataLowRes[157], downsampledData[157], EPSILONT);
    EXPECT_NEAR(dataLowRes[158], downsampledData[158], EPSILONT);
    EXPECT_NEAR(dataLowRes[159], downsampledData[159], EPSILONT);
    EXPECT_NEAR(dataLowRes[160], downsampledData[160], EPSILONT);
    EXPECT_NEAR(dataLowRes[161], downsampledData[161], EPSILONT);
    EXPECT_NEAR(dataLowRes[162], downsampledData[162], EPSILONT);
    EXPECT_NEAR(dataLowRes[163], downsampledData[163], EPSILONT);
    EXPECT_NEAR(dataLowRes[164], downsampledData[164], EPSILONT);
    EXPECT_NEAR(dataLowRes[165], downsampledData[165], EPSILONT);
    EXPECT_NEAR(dataLowRes[166], downsampledData[166], EPSILONT);
    EXPECT_NEAR(dataLowRes[167], downsampledData[167], EPSILONT);
    EXPECT_NEAR(dataLowRes[168], downsampledData[168], EPSILONT);
    EXPECT_NEAR(dataLowRes[169], downsampledData[169], EPSILONT);
    EXPECT_NEAR(dataLowRes[170], downsampledData[170], EPSILONT);
    EXPECT_NEAR(dataLowRes[171], downsampledData[171], EPSILONT);
    EXPECT_NEAR(dataLowRes[172], downsampledData[172], EPSILONT);
    EXPECT_NEAR(dataLowRes[173], downsampledData[173], EPSILONT);
    EXPECT_NEAR(dataLowRes[174], downsampledData[174], EPSILONT);
    EXPECT_NEAR(dataLowRes[175], downsampledData[175], EPSILONT);
    EXPECT_NEAR(dataLowRes[176], downsampledData[176], EPSILONT);
    EXPECT_NEAR(dataLowRes[177], downsampledData[177], EPSILONT);
    EXPECT_NEAR(dataLowRes[178], downsampledData[178], EPSILONT);
    EXPECT_NEAR(dataLowRes[179], downsampledData[179], EPSILONT);
    EXPECT_NEAR(dataLowRes[180], downsampledData[180], EPSILONT);
    EXPECT_NEAR(dataLowRes[181], downsampledData[181], EPSILONT);
    EXPECT_NEAR(dataLowRes[182], downsampledData[182], EPSILONT);
    EXPECT_NEAR(dataLowRes[183], downsampledData[183], EPSILONT);
    EXPECT_NEAR(dataLowRes[184], downsampledData[184], EPSILONT);
    EXPECT_NEAR(dataLowRes[185], downsampledData[185], EPSILONT);
    EXPECT_NEAR(dataLowRes[186], downsampledData[186], EPSILONT);
    EXPECT_NEAR(dataLowRes[187], downsampledData[187], EPSILONT);
    EXPECT_NEAR(dataLowRes[188], downsampledData[188], EPSILONT);
    EXPECT_NEAR(dataLowRes[189], downsampledData[189], EPSILONT);
    EXPECT_NEAR(dataLowRes[190], downsampledData[190], EPSILONT);
    EXPECT_NEAR(dataLowRes[191], downsampledData[191], EPSILONT);

    delete imCCHighRes;
    delete imCCLowRes125;
    delete[] dataLowRes;
    delete[] dataHighRes;
    delete[] downsampledData;

}