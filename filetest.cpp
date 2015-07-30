#include "gtest/gtest.h"
#include "filehandling.h"
#include "defs.h"

using namespace LatticeLib;
using std::string;
using std::to_string;

TEST(Files, readVolume) {
    int nR = 2, nC = 3, nL = 4, nB = 5;
    int nElements = nR * nC * nL;
    int nTotal = nB * nElements;
    char filename[] = "testimage2345.bin";
    char *filenamepointer = filename;
    double *fromFile = readVolume(filenamepointer, nTotal);
    double referenceData[] = {
            1, 2, 3,
            4, 5, 6,

            2, 3, 4,
            5, 6, 1,

            3, 4, 5,
            6, 1, 2,

            4, 5, 6,
            1, 2, 3,


            11, 12, 13,
            14, 15, 16,

            12, 13, 14,
            15, 16, 11,

            13, 14, 15,
            16, 11, 12,

            14, 15, 16,
            11, 12, 13,


            21, 22, 23,
            24, 25, 26,

            22, 23, 24,
            25, 26, 21,

            23, 24, 25,
            26, 21, 22,

            24, 25, 26,
            21, 22, 23,


            31, 32, 33,
            34, 35, 36,

            32, 33, 34,
            35, 36, 31,

            33, 34, 35,
            36, 31, 32,

            34, 35, 36,
            31, 32, 33,


            41, 42, 43,
            44, 45, 46,

            42, 43, 44,
            45, 46, 41,

            43, 44, 45,
            46, 41, 42,

            44, 45, 46,
            41, 42, 43
    };

    for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
        string message = "index = ";
        SCOPED_TRACE(message + to_string(dataIndex));

        EXPECT_NEAR(fromFile[dataIndex], referenceData[dataIndex], EPSILONT);
    }
    delete fromFile;
}