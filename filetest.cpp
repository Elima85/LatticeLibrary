#ifndef FILETEST
#define FILETEST

#include "gtest/gtest.h"
#include "filehandling.h"
#include "defs.h"

using namespace CImage;

TEST(Files, readVolume) {
    int nR = 2, nC = 3, nL = 4, nB = 5;
    int nTot = nR * nC * nL;
    char filename[] = "testimage2345.bin";
    char *filenamepointer = filename;
    double *fromFile = readVolume(filenamepointer, nTot * nB);
    double referenceData[] = {1, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 1, 3, 4, 5, 6, 1, 2, 4, 5, 6, 1, 2, 3,
            11, 12, 13, 14, 15, 16, 12, 13, 14, 15, 16, 11, 13, 14, 15, 16, 11, 12, 14, 15, 16, 11, 12, 13,
            21, 22, 23, 24, 25, 26, 22, 23, 24, 25, 26, 21, 23, 24, 25, 26, 21, 22, 24, 25, 26, 21, 22, 23,
            31, 32, 33, 34, 35, 36, 32, 33, 34, 35, 36, 31, 33, 34, 35, 36, 31, 32, 34, 35, 36, 31, 32, 33,
            41, 42, 43, 44, 45, 46, 42, 43, 44, 45, 46, 41, 43, 44, 45, 46, 41, 42, 44, 45, 46, 41, 42, 43};

    EXPECT_NEAR(fromFile[0], referenceData[0], EPSILONT);
    EXPECT_NEAR(fromFile[1], referenceData[1], EPSILONT);
    EXPECT_NEAR(fromFile[2], referenceData[2], EPSILONT);
    EXPECT_NEAR(fromFile[3], referenceData[3], EPSILONT);
    EXPECT_NEAR(fromFile[4], referenceData[4], EPSILONT);
    EXPECT_NEAR(fromFile[5], referenceData[5], EPSILONT);
    EXPECT_NEAR(fromFile[6], referenceData[6], EPSILONT);
    EXPECT_NEAR(fromFile[7], referenceData[7], EPSILONT);
    EXPECT_NEAR(fromFile[8], referenceData[8], EPSILONT);
    EXPECT_NEAR(fromFile[9], referenceData[9], EPSILONT);
    EXPECT_NEAR(fromFile[10], referenceData[10], EPSILONT);
    EXPECT_NEAR(fromFile[11], referenceData[11], EPSILONT);
    EXPECT_NEAR(fromFile[12], referenceData[12], EPSILONT);
    EXPECT_NEAR(fromFile[13], referenceData[13], EPSILONT);
    EXPECT_NEAR(fromFile[14], referenceData[14], EPSILONT);
    EXPECT_NEAR(fromFile[15], referenceData[15], EPSILONT);
    EXPECT_NEAR(fromFile[16], referenceData[16], EPSILONT);
    EXPECT_NEAR(fromFile[17], referenceData[17], EPSILONT);
    EXPECT_NEAR(fromFile[18], referenceData[18], EPSILONT);
    EXPECT_NEAR(fromFile[19], referenceData[19], EPSILONT);
    EXPECT_NEAR(fromFile[20], referenceData[20], EPSILONT);
    EXPECT_NEAR(fromFile[21], referenceData[21], EPSILONT);
    EXPECT_NEAR(fromFile[22], referenceData[22], EPSILONT);
    EXPECT_NEAR(fromFile[23], referenceData[23], EPSILONT);
    EXPECT_NEAR(fromFile[24], referenceData[24], EPSILONT);
    EXPECT_NEAR(fromFile[25], referenceData[25], EPSILONT);
    EXPECT_NEAR(fromFile[26], referenceData[26], EPSILONT);
    EXPECT_NEAR(fromFile[27], referenceData[27], EPSILONT);
    EXPECT_NEAR(fromFile[28], referenceData[28], EPSILONT);
    EXPECT_NEAR(fromFile[29], referenceData[29], EPSILONT);
    EXPECT_NEAR(fromFile[30], referenceData[30], EPSILONT);
    EXPECT_NEAR(fromFile[31], referenceData[31], EPSILONT);
    EXPECT_NEAR(fromFile[32], referenceData[32], EPSILONT);
    EXPECT_NEAR(fromFile[33], referenceData[33], EPSILONT);
    EXPECT_NEAR(fromFile[34], referenceData[34], EPSILONT);
    EXPECT_NEAR(fromFile[35], referenceData[35], EPSILONT);
    EXPECT_NEAR(fromFile[36], referenceData[36], EPSILONT);
    EXPECT_NEAR(fromFile[37], referenceData[37], EPSILONT);
    EXPECT_NEAR(fromFile[38], referenceData[38], EPSILONT);
    EXPECT_NEAR(fromFile[39], referenceData[39], EPSILONT);
    EXPECT_NEAR(fromFile[40], referenceData[40], EPSILONT);
    EXPECT_NEAR(fromFile[41], referenceData[41], EPSILONT);
    EXPECT_NEAR(fromFile[42], referenceData[42], EPSILONT);
    EXPECT_NEAR(fromFile[43], referenceData[43], EPSILONT);
    EXPECT_NEAR(fromFile[44], referenceData[44], EPSILONT);
    EXPECT_NEAR(fromFile[45], referenceData[45], EPSILONT);
    EXPECT_NEAR(fromFile[46], referenceData[46], EPSILONT);
    EXPECT_NEAR(fromFile[47], referenceData[47], EPSILONT);
    EXPECT_NEAR(fromFile[48], referenceData[48], EPSILONT);
    EXPECT_NEAR(fromFile[49], referenceData[49], EPSILONT);
    EXPECT_NEAR(fromFile[50], referenceData[50], EPSILONT);
    EXPECT_NEAR(fromFile[51], referenceData[51], EPSILONT);
    EXPECT_NEAR(fromFile[52], referenceData[52], EPSILONT);
    EXPECT_NEAR(fromFile[53], referenceData[53], EPSILONT);
    EXPECT_NEAR(fromFile[54], referenceData[54], EPSILONT);
    EXPECT_NEAR(fromFile[55], referenceData[55], EPSILONT);
    EXPECT_NEAR(fromFile[56], referenceData[56], EPSILONT);
    EXPECT_NEAR(fromFile[57], referenceData[57], EPSILONT);
    EXPECT_NEAR(fromFile[58], referenceData[58], EPSILONT);
    EXPECT_NEAR(fromFile[59], referenceData[59], EPSILONT);
    EXPECT_NEAR(fromFile[60], referenceData[60], EPSILONT);
    EXPECT_NEAR(fromFile[61], referenceData[61], EPSILONT);
    EXPECT_NEAR(fromFile[62], referenceData[62], EPSILONT);
    EXPECT_NEAR(fromFile[63], referenceData[63], EPSILONT);
    EXPECT_NEAR(fromFile[64], referenceData[64], EPSILONT);
    EXPECT_NEAR(fromFile[65], referenceData[65], EPSILONT);
    EXPECT_NEAR(fromFile[66], referenceData[66], EPSILONT);
    EXPECT_NEAR(fromFile[67], referenceData[67], EPSILONT);
    EXPECT_NEAR(fromFile[68], referenceData[68], EPSILONT);
    EXPECT_NEAR(fromFile[69], referenceData[69], EPSILONT);
    EXPECT_NEAR(fromFile[70], referenceData[70], EPSILONT);
    EXPECT_NEAR(fromFile[71], referenceData[71], EPSILONT);
    EXPECT_NEAR(fromFile[72], referenceData[72], EPSILONT);
    EXPECT_NEAR(fromFile[73], referenceData[73], EPSILONT);
    EXPECT_NEAR(fromFile[74], referenceData[74], EPSILONT);
    EXPECT_NEAR(fromFile[75], referenceData[75], EPSILONT);
    EXPECT_NEAR(fromFile[76], referenceData[76], EPSILONT);
    EXPECT_NEAR(fromFile[77], referenceData[77], EPSILONT);
    EXPECT_NEAR(fromFile[78], referenceData[78], EPSILONT);
    EXPECT_NEAR(fromFile[79], referenceData[79], EPSILONT);
    EXPECT_NEAR(fromFile[80], referenceData[80], EPSILONT);
    EXPECT_NEAR(fromFile[81], referenceData[81], EPSILONT);
    EXPECT_NEAR(fromFile[82], referenceData[82], EPSILONT);
    EXPECT_NEAR(fromFile[83], referenceData[83], EPSILONT);
    EXPECT_NEAR(fromFile[84], referenceData[84], EPSILONT);
    EXPECT_NEAR(fromFile[85], referenceData[85], EPSILONT);
    EXPECT_NEAR(fromFile[86], referenceData[86], EPSILONT);
    EXPECT_NEAR(fromFile[87], referenceData[87], EPSILONT);
    EXPECT_NEAR(fromFile[88], referenceData[88], EPSILONT);
    EXPECT_NEAR(fromFile[89], referenceData[89], EPSILONT);
    EXPECT_NEAR(fromFile[90], referenceData[90], EPSILONT);
    EXPECT_NEAR(fromFile[91], referenceData[91], EPSILONT);
    EXPECT_NEAR(fromFile[92], referenceData[92], EPSILONT);
    EXPECT_NEAR(fromFile[93], referenceData[93], EPSILONT);
    EXPECT_NEAR(fromFile[94], referenceData[94], EPSILONT);
    EXPECT_NEAR(fromFile[95], referenceData[95], EPSILONT);
    EXPECT_NEAR(fromFile[96], referenceData[96], EPSILONT);
    EXPECT_NEAR(fromFile[97], referenceData[97], EPSILONT);
    EXPECT_NEAR(fromFile[98], referenceData[98], EPSILONT);
    EXPECT_NEAR(fromFile[99], referenceData[99], EPSILONT);
    EXPECT_NEAR(fromFile[100], referenceData[100], EPSILONT);
    EXPECT_NEAR(fromFile[101], referenceData[101], EPSILONT);
    EXPECT_NEAR(fromFile[102], referenceData[102], EPSILONT);
    EXPECT_NEAR(fromFile[103], referenceData[103], EPSILONT);
    EXPECT_NEAR(fromFile[104], referenceData[104], EPSILONT);
    EXPECT_NEAR(fromFile[105], referenceData[105], EPSILONT);
    EXPECT_NEAR(fromFile[106], referenceData[106], EPSILONT);
    EXPECT_NEAR(fromFile[107], referenceData[107], EPSILONT);
    EXPECT_NEAR(fromFile[108], referenceData[108], EPSILONT);
    EXPECT_NEAR(fromFile[109], referenceData[109], EPSILONT);
    EXPECT_NEAR(fromFile[110], referenceData[110], EPSILONT);
    EXPECT_NEAR(fromFile[111], referenceData[111], EPSILONT);
    EXPECT_NEAR(fromFile[112], referenceData[112], EPSILONT);
    EXPECT_NEAR(fromFile[113], referenceData[113], EPSILONT);
    EXPECT_NEAR(fromFile[114], referenceData[114], EPSILONT);
    EXPECT_NEAR(fromFile[115], referenceData[115], EPSILONT);
    EXPECT_NEAR(fromFile[116], referenceData[116], EPSILONT);
    EXPECT_NEAR(fromFile[117], referenceData[117], EPSILONT);
    EXPECT_NEAR(fromFile[118], referenceData[118], EPSILONT);
    EXPECT_NEAR(fromFile[119], referenceData[119], EPSILONT);
}

#endif