#ifndef IMAGECCTEST
#define IMAGECCTEST

#include "gtest/gtest.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "exception.h"
#include "label.h"
#include <cmath>
#include <vector>
#include "filehandling.h"

using namespace CImage;

/**
* Tests type CImagetypeCC aka CImageCC<uint8>.
*/
TEST(CImageCC, constructor) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = i;
    }

    // constructor
    CImageCC<double> *imCCempty = new CImageCC<double>();
    EXPECT_TRUE(imCCempty);
    EXPECT_EQ(imCCempty->getNRows(), 0);
    EXPECT_EQ(imCCempty->getNColumns(), 0);
    EXPECT_EQ(imCCempty->getNLayers(), 0);
    EXPECT_EQ(imCCempty->getNBands(), 0);
    EXPECT_NEAR(imCCempty->getScaleFactor(), 1, EPSILONT);

    CImageCC<uint8> *imCC = new CImageCC<uint8>(data, nR, nC, nL, nB);
    EXPECT_TRUE(imCC);

    uint8 *imdata = imCC->getData();
    EXPECT_NEAR(imdata[0], data[0], EPSILONT);
    EXPECT_NEAR(imdata[1], data[1], EPSILONT);
    EXPECT_NEAR(imdata[2], data[2], EPSILONT);
    EXPECT_NEAR(imdata[3], data[3], EPSILONT);
    EXPECT_NEAR(imdata[4], data[4], EPSILONT);
    EXPECT_NEAR(imdata[5], data[5], EPSILONT);
    EXPECT_NEAR(imdata[6], data[6], EPSILONT);
    EXPECT_NEAR(imdata[7], data[7], EPSILONT);
    EXPECT_NEAR(imdata[8], data[8], EPSILONT);
    EXPECT_NEAR(imdata[9], data[9], EPSILONT);
    EXPECT_NEAR(imdata[10], data[10], EPSILONT);
    EXPECT_NEAR(imdata[11], data[11], EPSILONT);
    EXPECT_NEAR(imdata[12], data[12], EPSILONT);
    EXPECT_NEAR(imdata[13], data[13], EPSILONT);
    EXPECT_NEAR(imdata[14], data[14], EPSILONT);
    EXPECT_NEAR(imdata[15], data[15], EPSILONT);
    EXPECT_NEAR(imdata[16], data[16], EPSILONT);
    EXPECT_NEAR(imdata[17], data[17], EPSILONT);
    EXPECT_NEAR(imdata[18], data[18], EPSILONT);
    EXPECT_NEAR(imdata[19], data[19], EPSILONT);
    EXPECT_NEAR(imdata[20], data[20], EPSILONT);
    EXPECT_NEAR(imdata[21], data[21], EPSILONT);
    EXPECT_NEAR(imdata[22], data[22], EPSILONT);
    EXPECT_NEAR(imdata[23], data[23], EPSILONT);
    EXPECT_NEAR(imdata[24], data[24], EPSILONT);
    EXPECT_NEAR(imdata[25], data[25], EPSILONT);
    EXPECT_NEAR(imdata[26], data[26], EPSILONT);
    EXPECT_NEAR(imdata[27], data[27], EPSILONT);
    EXPECT_NEAR(imdata[28], data[28], EPSILONT);
    EXPECT_NEAR(imdata[29], data[29], EPSILONT);
    EXPECT_NEAR(imdata[30], data[30], EPSILONT);
    EXPECT_NEAR(imdata[31], data[31], EPSILONT);
    EXPECT_NEAR(imdata[32], data[32], EPSILONT);
    EXPECT_NEAR(imdata[33], data[33], EPSILONT);
    EXPECT_NEAR(imdata[34], data[34], EPSILONT);
    EXPECT_NEAR(imdata[35], data[35], EPSILONT);
    EXPECT_NEAR(imdata[36], data[36], EPSILONT);
    EXPECT_NEAR(imdata[37], data[37], EPSILONT);
    EXPECT_NEAR(imdata[38], data[38], EPSILONT);
    EXPECT_NEAR(imdata[39], data[39], EPSILONT);
    EXPECT_NEAR(imdata[40], data[40], EPSILONT);
    EXPECT_NEAR(imdata[41], data[41], EPSILONT);
    EXPECT_NEAR(imdata[42], data[42], EPSILONT);
    EXPECT_NEAR(imdata[43], data[43], EPSILONT);
    EXPECT_NEAR(imdata[44], data[44], EPSILONT);
    EXPECT_NEAR(imdata[45], data[45], EPSILONT);
    EXPECT_NEAR(imdata[46], data[46], EPSILONT);
    EXPECT_NEAR(imdata[47], data[47], EPSILONT);
    EXPECT_NEAR(imdata[48], data[48], EPSILONT);
    EXPECT_NEAR(imdata[49], data[49], EPSILONT);
    EXPECT_NEAR(imdata[50], data[50], EPSILONT);
    EXPECT_NEAR(imdata[51], data[51], EPSILONT);
    EXPECT_NEAR(imdata[52], data[52], EPSILONT);
    EXPECT_NEAR(imdata[53], data[53], EPSILONT);
    EXPECT_NEAR(imdata[54], data[54], EPSILONT);
    EXPECT_NEAR(imdata[55], data[55], EPSILONT);
    EXPECT_NEAR(imdata[56], data[56], EPSILONT);
    EXPECT_NEAR(imdata[57], data[57], EPSILONT);
    EXPECT_NEAR(imdata[58], data[58], EPSILONT);
    EXPECT_NEAR(imdata[59], data[59], EPSILONT);
    EXPECT_NEAR(imdata[60], data[60], EPSILONT);
    EXPECT_NEAR(imdata[61], data[61], EPSILONT);
    EXPECT_NEAR(imdata[62], data[62], EPSILONT);
    EXPECT_NEAR(imdata[63], data[63], EPSILONT);
    EXPECT_NEAR(imdata[64], data[64], EPSILONT);
    EXPECT_NEAR(imdata[65], data[65], EPSILONT);
    EXPECT_NEAR(imdata[66], data[66], EPSILONT);
    EXPECT_NEAR(imdata[67], data[67], EPSILONT);
    EXPECT_NEAR(imdata[68], data[68], EPSILONT);
    EXPECT_NEAR(imdata[69], data[69], EPSILONT);
    EXPECT_NEAR(imdata[70], data[70], EPSILONT);
    EXPECT_NEAR(imdata[71], data[71], EPSILONT);
    EXPECT_NEAR(imdata[72], data[72], EPSILONT);
    EXPECT_NEAR(imdata[73], data[73], EPSILONT);
    EXPECT_NEAR(imdata[74], data[74], EPSILONT);
    EXPECT_NEAR(imdata[75], data[75], EPSILONT);
    EXPECT_NEAR(imdata[76], data[76], EPSILONT);
    EXPECT_NEAR(imdata[77], data[77], EPSILONT);
    EXPECT_NEAR(imdata[78], data[78], EPSILONT);
    EXPECT_NEAR(imdata[79], data[79], EPSILONT);
    EXPECT_NEAR(imdata[80], data[80], EPSILONT);
    EXPECT_NEAR(imdata[81], data[81], EPSILONT);
    EXPECT_NEAR(imdata[82], data[82], EPSILONT);
    EXPECT_NEAR(imdata[83], data[83], EPSILONT);
    EXPECT_NEAR(imdata[84], data[84], EPSILONT);
    EXPECT_NEAR(imdata[85], data[85], EPSILONT);
    EXPECT_NEAR(imdata[86], data[86], EPSILONT);
    EXPECT_NEAR(imdata[87], data[87], EPSILONT);
    EXPECT_NEAR(imdata[88], data[88], EPSILONT);
    EXPECT_NEAR(imdata[89], data[89], EPSILONT);
    EXPECT_NEAR(imdata[90], data[90], EPSILONT);
    EXPECT_NEAR(imdata[91], data[91], EPSILONT);
    EXPECT_NEAR(imdata[92], data[92], EPSILONT);
    EXPECT_NEAR(imdata[93], data[93], EPSILONT);
    EXPECT_NEAR(imdata[94], data[94], EPSILONT);
    EXPECT_NEAR(imdata[95], data[95], EPSILONT);
    EXPECT_NEAR(imdata[96], data[96], EPSILONT);
    EXPECT_NEAR(imdata[97], data[97], EPSILONT);
    EXPECT_NEAR(imdata[98], data[98], EPSILONT);
    EXPECT_NEAR(imdata[99], data[99], EPSILONT);
    EXPECT_NEAR(imdata[100], data[100], EPSILONT);
    EXPECT_NEAR(imdata[101], data[101], EPSILONT);
    EXPECT_NEAR(imdata[102], data[102], EPSILONT);
    EXPECT_NEAR(imdata[103], data[103], EPSILONT);
    EXPECT_NEAR(imdata[104], data[104], EPSILONT);
    EXPECT_NEAR(imdata[105], data[105], EPSILONT);
    EXPECT_NEAR(imdata[106], data[106], EPSILONT);
    EXPECT_NEAR(imdata[107], data[107], EPSILONT);
    EXPECT_NEAR(imdata[108], data[108], EPSILONT);
    EXPECT_NEAR(imdata[109], data[109], EPSILONT);
    EXPECT_NEAR(imdata[110], data[110], EPSILONT);
    EXPECT_NEAR(imdata[111], data[111], EPSILONT);
    EXPECT_NEAR(imdata[112], data[112], EPSILONT);
    EXPECT_NEAR(imdata[113], data[113], EPSILONT);
    EXPECT_NEAR(imdata[114], data[114], EPSILONT);
    EXPECT_NEAR(imdata[115], data[115], EPSILONT);
    EXPECT_NEAR(imdata[116], data[116], EPSILONT);
    EXPECT_NEAR(imdata[117], data[117], EPSILONT);
    EXPECT_NEAR(imdata[118], data[118], EPSILONT);
    EXPECT_NEAR(imdata[119], data[119], EPSILONT);
    EXPECT_NEAR(imdata[120], data[120], EPSILONT);
    EXPECT_NEAR(imdata[121], data[121], EPSILONT);
    EXPECT_NEAR(imdata[122], data[122], EPSILONT);
    EXPECT_NEAR(imdata[123], data[123], EPSILONT);
    EXPECT_NEAR(imdata[124], data[124], EPSILONT);
    EXPECT_NEAR(imdata[125], data[125], EPSILONT);
    EXPECT_NEAR(imdata[126], data[126], EPSILONT);
    EXPECT_NEAR(imdata[127], data[127], EPSILONT);
    EXPECT_NEAR(imdata[128], data[128], EPSILONT);
    EXPECT_NEAR(imdata[129], data[129], EPSILONT);
    EXPECT_NEAR(imdata[130], data[130], EPSILONT);
    EXPECT_NEAR(imdata[131], data[131], EPSILONT);
    EXPECT_NEAR(imdata[132], data[132], EPSILONT);
    EXPECT_NEAR(imdata[133], data[133], EPSILONT);
    EXPECT_NEAR(imdata[134], data[134], EPSILONT);
    EXPECT_NEAR(imdata[135], data[135], EPSILONT);
    EXPECT_NEAR(imdata[136], data[136], EPSILONT);
    EXPECT_NEAR(imdata[137], data[137], EPSILONT);
    EXPECT_NEAR(imdata[138], data[138], EPSILONT);
    EXPECT_NEAR(imdata[139], data[139], EPSILONT);
    EXPECT_NEAR(imdata[140], data[140], EPSILONT);
    EXPECT_NEAR(imdata[141], data[141], EPSILONT);
    EXPECT_NEAR(imdata[142], data[142], EPSILONT);
    EXPECT_NEAR(imdata[143], data[143], EPSILONT);
    EXPECT_NEAR(imdata[144], data[144], EPSILONT);
    EXPECT_NEAR(imdata[145], data[145], EPSILONT);
    EXPECT_NEAR(imdata[146], data[146], EPSILONT);
    EXPECT_NEAR(imdata[147], data[147], EPSILONT);
    EXPECT_NEAR(imdata[148], data[148], EPSILONT);
    EXPECT_NEAR(imdata[149], data[149], EPSILONT);
    EXPECT_NEAR(imdata[150], data[150], EPSILONT);
    EXPECT_NEAR(imdata[151], data[151], EPSILONT);
    EXPECT_NEAR(imdata[152], data[152], EPSILONT);
    EXPECT_NEAR(imdata[153], data[153], EPSILONT);
    EXPECT_NEAR(imdata[154], data[154], EPSILONT);
    EXPECT_NEAR(imdata[155], data[155], EPSILONT);
    EXPECT_NEAR(imdata[156], data[156], EPSILONT);
    EXPECT_NEAR(imdata[157], data[157], EPSILONT);
    EXPECT_NEAR(imdata[158], data[158], EPSILONT);
    EXPECT_NEAR(imdata[159], data[159], EPSILONT);
    EXPECT_NEAR(imdata[160], data[160], EPSILONT);
    EXPECT_NEAR(imdata[161], data[161], EPSILONT);
    EXPECT_NEAR(imdata[162], data[162], EPSILONT);
    EXPECT_NEAR(imdata[163], data[163], EPSILONT);
    EXPECT_NEAR(imdata[164], data[164], EPSILONT);
    EXPECT_NEAR(imdata[165], data[165], EPSILONT);
    EXPECT_NEAR(imdata[166], data[166], EPSILONT);
    EXPECT_NEAR(imdata[167], data[167], EPSILONT);
    EXPECT_NEAR(imdata[168], data[168], EPSILONT);
    EXPECT_NEAR(imdata[169], data[169], EPSILONT);
    EXPECT_NEAR(imdata[170], data[170], EPSILONT);
    EXPECT_NEAR(imdata[171], data[171], EPSILONT);
    EXPECT_NEAR(imdata[172], data[172], EPSILONT);
    EXPECT_NEAR(imdata[173], data[173], EPSILONT);
    EXPECT_NEAR(imdata[174], data[174], EPSILONT);
    EXPECT_NEAR(imdata[175], data[175], EPSILONT);
    EXPECT_NEAR(imdata[176], data[176], EPSILONT);
    EXPECT_NEAR(imdata[177], data[177], EPSILONT);
    EXPECT_NEAR(imdata[178], data[178], EPSILONT);
    EXPECT_NEAR(imdata[179], data[179], EPSILONT);
    EXPECT_NEAR(imdata[180], data[180], EPSILONT);
    EXPECT_NEAR(imdata[181], data[181], EPSILONT);
    EXPECT_NEAR(imdata[182], data[182], EPSILONT);
    EXPECT_NEAR(imdata[183], data[183], EPSILONT);
    EXPECT_NEAR(imdata[184], data[184], EPSILONT);
    EXPECT_NEAR(imdata[185], data[185], EPSILONT);
    EXPECT_NEAR(imdata[186], data[186], EPSILONT);
    EXPECT_NEAR(imdata[187], data[187], EPSILONT);
    EXPECT_NEAR(imdata[188], data[188], EPSILONT);
    EXPECT_NEAR(imdata[189], data[189], EPSILONT);
    EXPECT_NEAR(imdata[190], data[190], EPSILONT);
    EXPECT_NEAR(imdata[191], data[191], EPSILONT);
    EXPECT_NEAR(imdata[192], data[192], EPSILONT);
    EXPECT_NEAR(imdata[193], data[193], EPSILONT);
    EXPECT_NEAR(imdata[194], data[194], EPSILONT);
    EXPECT_NEAR(imdata[195], data[195], EPSILONT);
    EXPECT_NEAR(imdata[196], data[196], EPSILONT);
    EXPECT_NEAR(imdata[197], data[197], EPSILONT);
    EXPECT_NEAR(imdata[198], data[198], EPSILONT);
    EXPECT_NEAR(imdata[199], data[199], EPSILONT);
    EXPECT_NEAR(imdata[200], data[200], EPSILONT);
    EXPECT_NEAR(imdata[201], data[201], EPSILONT);
    EXPECT_NEAR(imdata[202], data[202], EPSILONT);
    EXPECT_NEAR(imdata[203], data[203], EPSILONT);
    EXPECT_NEAR(imdata[204], data[204], EPSILONT);
    EXPECT_NEAR(imdata[205], data[205], EPSILONT);
    EXPECT_NEAR(imdata[206], data[206], EPSILONT);
    EXPECT_NEAR(imdata[207], data[207], EPSILONT);
    EXPECT_NEAR(imdata[208], data[208], EPSILONT);
    EXPECT_NEAR(imdata[209], data[209], EPSILONT);

    EXPECT_NEAR(imdata[210], data[210], EPSILONT);
    EXPECT_NEAR(imdata[211], data[211], EPSILONT);
    EXPECT_NEAR(imdata[212], data[212], EPSILONT);
    EXPECT_NEAR(imdata[213], data[213], EPSILONT);
    EXPECT_NEAR(imdata[214], data[214], EPSILONT);
    EXPECT_NEAR(imdata[215], data[215], EPSILONT);
    EXPECT_NEAR(imdata[216], data[216], EPSILONT);
    EXPECT_NEAR(imdata[217], data[217], EPSILONT);
    EXPECT_NEAR(imdata[218], data[218], EPSILONT);
    EXPECT_NEAR(imdata[219], data[219], EPSILONT);
    EXPECT_NEAR(imdata[220], data[220], EPSILONT);
    EXPECT_NEAR(imdata[221], data[221], EPSILONT);
    EXPECT_NEAR(imdata[222], data[222], EPSILONT);
    EXPECT_NEAR(imdata[223], data[223], EPSILONT);
    EXPECT_NEAR(imdata[224], data[224], EPSILONT);
    EXPECT_NEAR(imdata[225], data[225], EPSILONT);
    EXPECT_NEAR(imdata[226], data[226], EPSILONT);
    EXPECT_NEAR(imdata[227], data[227], EPSILONT);
    EXPECT_NEAR(imdata[228], data[228], EPSILONT);
    EXPECT_NEAR(imdata[229], data[229], EPSILONT);
    EXPECT_NEAR(imdata[230], data[230], EPSILONT);
    EXPECT_NEAR(imdata[231], data[231], EPSILONT);
    EXPECT_NEAR(imdata[232], data[232], EPSILONT);
    EXPECT_NEAR(imdata[233], data[233], EPSILONT);
    EXPECT_NEAR(imdata[234], data[234], EPSILONT);
    EXPECT_NEAR(imdata[235], data[235], EPSILONT);
    EXPECT_NEAR(imdata[236], data[236], EPSILONT);
    EXPECT_NEAR(imdata[237], data[237], EPSILONT);
    EXPECT_NEAR(imdata[238], data[238], EPSILONT);
    EXPECT_NEAR(imdata[239], data[239], EPSILONT);
    EXPECT_NEAR(imdata[240], data[240], EPSILONT);
    EXPECT_NEAR(imdata[241], data[241], EPSILONT);
    EXPECT_NEAR(imdata[242], data[242], EPSILONT);
    EXPECT_NEAR(imdata[243], data[243], EPSILONT);
    EXPECT_NEAR(imdata[244], data[244], EPSILONT);
    EXPECT_NEAR(imdata[245], data[245], EPSILONT);
    EXPECT_NEAR(imdata[246], data[246], EPSILONT);
    EXPECT_NEAR(imdata[247], data[247], EPSILONT);
    EXPECT_NEAR(imdata[248], data[248], EPSILONT);
    EXPECT_NEAR(imdata[249], data[249], EPSILONT);
    EXPECT_NEAR(imdata[250], data[250], EPSILONT);
    EXPECT_NEAR(imdata[251], data[251], EPSILONT);
    EXPECT_NEAR(imdata[252], data[252], EPSILONT);
    EXPECT_NEAR(imdata[253], data[253], EPSILONT);
    EXPECT_NEAR(imdata[254], data[254], EPSILONT);
    EXPECT_NEAR(imdata[255], data[255], EPSILONT);
    EXPECT_NEAR(imdata[256], data[256], EPSILONT);
    EXPECT_NEAR(imdata[257], data[257], EPSILONT);
    EXPECT_NEAR(imdata[258], data[258], EPSILONT);
    EXPECT_NEAR(imdata[259], data[259], EPSILONT);
    EXPECT_NEAR(imdata[260], data[260], EPSILONT);
    EXPECT_NEAR(imdata[261], data[261], EPSILONT);
    EXPECT_NEAR(imdata[262], data[262], EPSILONT);
    EXPECT_NEAR(imdata[263], data[263], EPSILONT);
    EXPECT_NEAR(imdata[264], data[264], EPSILONT);
    EXPECT_NEAR(imdata[265], data[265], EPSILONT);
    EXPECT_NEAR(imdata[266], data[266], EPSILONT);
    EXPECT_NEAR(imdata[267], data[267], EPSILONT);
    EXPECT_NEAR(imdata[268], data[268], EPSILONT);
    EXPECT_NEAR(imdata[269], data[269], EPSILONT);
    EXPECT_NEAR(imdata[270], data[270], EPSILONT);
    EXPECT_NEAR(imdata[271], data[271], EPSILONT);
    EXPECT_NEAR(imdata[272], data[272], EPSILONT);
    EXPECT_NEAR(imdata[273], data[273], EPSILONT);
    EXPECT_NEAR(imdata[274], data[274], EPSILONT);
    EXPECT_NEAR(imdata[275], data[275], EPSILONT);
    EXPECT_NEAR(imdata[276], data[276], EPSILONT);
    EXPECT_NEAR(imdata[277], data[277], EPSILONT);
    EXPECT_NEAR(imdata[278], data[278], EPSILONT);
    EXPECT_NEAR(imdata[279], data[279], EPSILONT);
    EXPECT_NEAR(imdata[280], data[280], EPSILONT);
    EXPECT_NEAR(imdata[281], data[281], EPSILONT);
    EXPECT_NEAR(imdata[282], data[282], EPSILONT);
    EXPECT_NEAR(imdata[283], data[283], EPSILONT);
    EXPECT_NEAR(imdata[284], data[284], EPSILONT);
    EXPECT_NEAR(imdata[285], data[285], EPSILONT);
    EXPECT_NEAR(imdata[286], data[286], EPSILONT);
    EXPECT_NEAR(imdata[287], data[287], EPSILONT);
    EXPECT_NEAR(imdata[288], data[288], EPSILONT);
    EXPECT_NEAR(imdata[289], data[289], EPSILONT);
    EXPECT_NEAR(imdata[290], data[290], EPSILONT);
    EXPECT_NEAR(imdata[291], data[291], EPSILONT);
    EXPECT_NEAR(imdata[292], data[292], EPSILONT);
    EXPECT_NEAR(imdata[293], data[293], EPSILONT);
    EXPECT_NEAR(imdata[294], data[294], EPSILONT);
    EXPECT_NEAR(imdata[295], data[295], EPSILONT);
    EXPECT_NEAR(imdata[296], data[296], EPSILONT);
    EXPECT_NEAR(imdata[297], data[297], EPSILONT);
    EXPECT_NEAR(imdata[298], data[298], EPSILONT);
    EXPECT_NEAR(imdata[299], data[299], EPSILONT);
    EXPECT_NEAR(imdata[300], data[300], EPSILONT);
    EXPECT_NEAR(imdata[301], data[301], EPSILONT);
    EXPECT_NEAR(imdata[302], data[302], EPSILONT);
    EXPECT_NEAR(imdata[303], data[303], EPSILONT);
    EXPECT_NEAR(imdata[304], data[304], EPSILONT);
    EXPECT_NEAR(imdata[305], data[305], EPSILONT);
    EXPECT_NEAR(imdata[306], data[306], EPSILONT);
    EXPECT_NEAR(imdata[307], data[307], EPSILONT);
    EXPECT_NEAR(imdata[308], data[308], EPSILONT);
    EXPECT_NEAR(imdata[309], data[309], EPSILONT);
    EXPECT_NEAR(imdata[310], data[310], EPSILONT);
    EXPECT_NEAR(imdata[311], data[311], EPSILONT);
    EXPECT_NEAR(imdata[312], data[312], EPSILONT);
    EXPECT_NEAR(imdata[313], data[313], EPSILONT);
    EXPECT_NEAR(imdata[314], data[314], EPSILONT);
    EXPECT_NEAR(imdata[315], data[315], EPSILONT);
    EXPECT_NEAR(imdata[316], data[316], EPSILONT);
    EXPECT_NEAR(imdata[317], data[317], EPSILONT);
    EXPECT_NEAR(imdata[318], data[318], EPSILONT);
    EXPECT_NEAR(imdata[319], data[319], EPSILONT);
    EXPECT_NEAR(imdata[320], data[320], EPSILONT);
    EXPECT_NEAR(imdata[321], data[321], EPSILONT);
    EXPECT_NEAR(imdata[322], data[322], EPSILONT);
    EXPECT_NEAR(imdata[323], data[323], EPSILONT);
    EXPECT_NEAR(imdata[324], data[324], EPSILONT);
    EXPECT_NEAR(imdata[325], data[325], EPSILONT);
    EXPECT_NEAR(imdata[326], data[326], EPSILONT);
    EXPECT_NEAR(imdata[327], data[327], EPSILONT);
    EXPECT_NEAR(imdata[328], data[328], EPSILONT);
    EXPECT_NEAR(imdata[329], data[329], EPSILONT);
    EXPECT_NEAR(imdata[330], data[330], EPSILONT);
    EXPECT_NEAR(imdata[331], data[331], EPSILONT);
    EXPECT_NEAR(imdata[332], data[332], EPSILONT);
    EXPECT_NEAR(imdata[333], data[333], EPSILONT);
    EXPECT_NEAR(imdata[334], data[334], EPSILONT);
    EXPECT_NEAR(imdata[335], data[335], EPSILONT);
    EXPECT_NEAR(imdata[336], data[336], EPSILONT);
    EXPECT_NEAR(imdata[337], data[337], EPSILONT);
    EXPECT_NEAR(imdata[338], data[338], EPSILONT);
    EXPECT_NEAR(imdata[339], data[339], EPSILONT);
    EXPECT_NEAR(imdata[340], data[340], EPSILONT);
    EXPECT_NEAR(imdata[341], data[341], EPSILONT);
    EXPECT_NEAR(imdata[342], data[342], EPSILONT);
    EXPECT_NEAR(imdata[343], data[343], EPSILONT);
    EXPECT_NEAR(imdata[344], data[344], EPSILONT);
    EXPECT_NEAR(imdata[345], data[345], EPSILONT);
    EXPECT_NEAR(imdata[346], data[346], EPSILONT);
    EXPECT_NEAR(imdata[347], data[347], EPSILONT);
    EXPECT_NEAR(imdata[348], data[348], EPSILONT);
    EXPECT_NEAR(imdata[349], data[349], EPSILONT);
    EXPECT_NEAR(imdata[350], data[350], EPSILONT);
    EXPECT_NEAR(imdata[351], data[351], EPSILONT);
    EXPECT_NEAR(imdata[352], data[352], EPSILONT);
    EXPECT_NEAR(imdata[353], data[353], EPSILONT);
    EXPECT_NEAR(imdata[354], data[354], EPSILONT);
    EXPECT_NEAR(imdata[355], data[355], EPSILONT);
    EXPECT_NEAR(imdata[356], data[356], EPSILONT);
    EXPECT_NEAR(imdata[357], data[357], EPSILONT);
    EXPECT_NEAR(imdata[358], data[358], EPSILONT);
    EXPECT_NEAR(imdata[359], data[359], EPSILONT);
    EXPECT_NEAR(imdata[360], data[360], EPSILONT);
    EXPECT_NEAR(imdata[361], data[361], EPSILONT);
    EXPECT_NEAR(imdata[362], data[362], EPSILONT);
    EXPECT_NEAR(imdata[363], data[363], EPSILONT);
    EXPECT_NEAR(imdata[364], data[364], EPSILONT);
    EXPECT_NEAR(imdata[365], data[365], EPSILONT);
    EXPECT_NEAR(imdata[366], data[366], EPSILONT);
    EXPECT_NEAR(imdata[367], data[367], EPSILONT);
    EXPECT_NEAR(imdata[368], data[368], EPSILONT);
    EXPECT_NEAR(imdata[369], data[369], EPSILONT);
    EXPECT_NEAR(imdata[370], data[370], EPSILONT);
    EXPECT_NEAR(imdata[371], data[371], EPSILONT);
    EXPECT_NEAR(imdata[372], data[372], EPSILONT);
    EXPECT_NEAR(imdata[373], data[373], EPSILONT);
    EXPECT_NEAR(imdata[374], data[374], EPSILONT);
    EXPECT_NEAR(imdata[375], data[375], EPSILONT);
    EXPECT_NEAR(imdata[376], data[376], EPSILONT);
    EXPECT_NEAR(imdata[377], data[377], EPSILONT);
    EXPECT_NEAR(imdata[378], data[378], EPSILONT);
    EXPECT_NEAR(imdata[379], data[379], EPSILONT);
    EXPECT_NEAR(imdata[380], data[380], EPSILONT);
    EXPECT_NEAR(imdata[381], data[381], EPSILONT);
    EXPECT_NEAR(imdata[382], data[382], EPSILONT);
    EXPECT_NEAR(imdata[383], data[383], EPSILONT);
    EXPECT_NEAR(imdata[384], data[384], EPSILONT);
    EXPECT_NEAR(imdata[385], data[385], EPSILONT);
    EXPECT_NEAR(imdata[386], data[386], EPSILONT);
    EXPECT_NEAR(imdata[387], data[387], EPSILONT);
    EXPECT_NEAR(imdata[388], data[388], EPSILONT);
    EXPECT_NEAR(imdata[389], data[389], EPSILONT);
    EXPECT_NEAR(imdata[390], data[390], EPSILONT);
    EXPECT_NEAR(imdata[391], data[391], EPSILONT);
    EXPECT_NEAR(imdata[392], data[392], EPSILONT);
    EXPECT_NEAR(imdata[393], data[393], EPSILONT);
    EXPECT_NEAR(imdata[394], data[394], EPSILONT);
    EXPECT_NEAR(imdata[395], data[395], EPSILONT);
    EXPECT_NEAR(imdata[396], data[396], EPSILONT);
    EXPECT_NEAR(imdata[397], data[397], EPSILONT);
    EXPECT_NEAR(imdata[398], data[398], EPSILONT);
    EXPECT_NEAR(imdata[399], data[399], EPSILONT);
    EXPECT_NEAR(imdata[400], data[400], EPSILONT);
    EXPECT_NEAR(imdata[401], data[401], EPSILONT);
    EXPECT_NEAR(imdata[402], data[402], EPSILONT);
    EXPECT_NEAR(imdata[403], data[403], EPSILONT);
    EXPECT_NEAR(imdata[404], data[404], EPSILONT);
    EXPECT_NEAR(imdata[405], data[405], EPSILONT);
    EXPECT_NEAR(imdata[406], data[406], EPSILONT);
    EXPECT_NEAR(imdata[407], data[407], EPSILONT);
    EXPECT_NEAR(imdata[408], data[408], EPSILONT);
    EXPECT_NEAR(imdata[409], data[409], EPSILONT);
    EXPECT_NEAR(imdata[410], data[410], EPSILONT);
    EXPECT_NEAR(imdata[411], data[411], EPSILONT);
    EXPECT_NEAR(imdata[412], data[412], EPSILONT);
    EXPECT_NEAR(imdata[413], data[413], EPSILONT);
    EXPECT_NEAR(imdata[414], data[414], EPSILONT);
    EXPECT_NEAR(imdata[415], data[415], EPSILONT);
    EXPECT_NEAR(imdata[416], data[416], EPSILONT);
    EXPECT_NEAR(imdata[417], data[417], EPSILONT);
    EXPECT_NEAR(imdata[418], data[418], EPSILONT);
    EXPECT_NEAR(imdata[419], data[419], EPSILONT);

    EXPECT_NEAR(imdata[420], data[420], EPSILONT);
    EXPECT_NEAR(imdata[421], data[421], EPSILONT);
    EXPECT_NEAR(imdata[422], data[422], EPSILONT);
    EXPECT_NEAR(imdata[423], data[423], EPSILONT);
    EXPECT_NEAR(imdata[424], data[424], EPSILONT);
    EXPECT_NEAR(imdata[425], data[425], EPSILONT);
    EXPECT_NEAR(imdata[426], data[426], EPSILONT);
    EXPECT_NEAR(imdata[427], data[427], EPSILONT);
    EXPECT_NEAR(imdata[428], data[428], EPSILONT);
    EXPECT_NEAR(imdata[429], data[429], EPSILONT);
    EXPECT_NEAR(imdata[430], data[430], EPSILONT);
    EXPECT_NEAR(imdata[431], data[431], EPSILONT);
    EXPECT_NEAR(imdata[432], data[432], EPSILONT);
    EXPECT_NEAR(imdata[433], data[433], EPSILONT);
    EXPECT_NEAR(imdata[434], data[434], EPSILONT);
    EXPECT_NEAR(imdata[435], data[435], EPSILONT);
    EXPECT_NEAR(imdata[436], data[436], EPSILONT);
    EXPECT_NEAR(imdata[437], data[437], EPSILONT);
    EXPECT_NEAR(imdata[438], data[438], EPSILONT);
    EXPECT_NEAR(imdata[439], data[439], EPSILONT);
    EXPECT_NEAR(imdata[440], data[440], EPSILONT);
    EXPECT_NEAR(imdata[441], data[441], EPSILONT);
    EXPECT_NEAR(imdata[442], data[442], EPSILONT);
    EXPECT_NEAR(imdata[443], data[443], EPSILONT);
    EXPECT_NEAR(imdata[444], data[444], EPSILONT);
    EXPECT_NEAR(imdata[445], data[445], EPSILONT);
    EXPECT_NEAR(imdata[446], data[446], EPSILONT);
    EXPECT_NEAR(imdata[447], data[447], EPSILONT);
    EXPECT_NEAR(imdata[448], data[448], EPSILONT);
    EXPECT_NEAR(imdata[449], data[449], EPSILONT);
    EXPECT_NEAR(imdata[450], data[450], EPSILONT);
    EXPECT_NEAR(imdata[451], data[451], EPSILONT);
    EXPECT_NEAR(imdata[452], data[452], EPSILONT);
    EXPECT_NEAR(imdata[453], data[453], EPSILONT);
    EXPECT_NEAR(imdata[454], data[454], EPSILONT);
    EXPECT_NEAR(imdata[455], data[455], EPSILONT);
    EXPECT_NEAR(imdata[456], data[456], EPSILONT);
    EXPECT_NEAR(imdata[457], data[457], EPSILONT);
    EXPECT_NEAR(imdata[458], data[458], EPSILONT);
    EXPECT_NEAR(imdata[459], data[459], EPSILONT);
    EXPECT_NEAR(imdata[460], data[460], EPSILONT);
    EXPECT_NEAR(imdata[461], data[461], EPSILONT);
    EXPECT_NEAR(imdata[462], data[462], EPSILONT);
    EXPECT_NEAR(imdata[463], data[463], EPSILONT);
    EXPECT_NEAR(imdata[464], data[464], EPSILONT);
    EXPECT_NEAR(imdata[465], data[465], EPSILONT);
    EXPECT_NEAR(imdata[466], data[466], EPSILONT);
    EXPECT_NEAR(imdata[467], data[467], EPSILONT);
    EXPECT_NEAR(imdata[468], data[468], EPSILONT);
    EXPECT_NEAR(imdata[469], data[469], EPSILONT);
    EXPECT_NEAR(imdata[470], data[470], EPSILONT);
    EXPECT_NEAR(imdata[471], data[471], EPSILONT);
    EXPECT_NEAR(imdata[472], data[472], EPSILONT);
    EXPECT_NEAR(imdata[473], data[473], EPSILONT);
    EXPECT_NEAR(imdata[474], data[474], EPSILONT);
    EXPECT_NEAR(imdata[475], data[475], EPSILONT);
    EXPECT_NEAR(imdata[476], data[476], EPSILONT);
    EXPECT_NEAR(imdata[477], data[477], EPSILONT);
    EXPECT_NEAR(imdata[478], data[478], EPSILONT);
    EXPECT_NEAR(imdata[479], data[479], EPSILONT);
    EXPECT_NEAR(imdata[480], data[480], EPSILONT);
    EXPECT_NEAR(imdata[481], data[481], EPSILONT);
    EXPECT_NEAR(imdata[482], data[482], EPSILONT);
    EXPECT_NEAR(imdata[483], data[483], EPSILONT);
    EXPECT_NEAR(imdata[484], data[484], EPSILONT);
    EXPECT_NEAR(imdata[485], data[485], EPSILONT);
    EXPECT_NEAR(imdata[486], data[486], EPSILONT);
    EXPECT_NEAR(imdata[487], data[487], EPSILONT);
    EXPECT_NEAR(imdata[488], data[488], EPSILONT);
    EXPECT_NEAR(imdata[489], data[489], EPSILONT);
    EXPECT_NEAR(imdata[490], data[490], EPSILONT);
    EXPECT_NEAR(imdata[491], data[491], EPSILONT);
    EXPECT_NEAR(imdata[492], data[492], EPSILONT);
    EXPECT_NEAR(imdata[493], data[493], EPSILONT);
    EXPECT_NEAR(imdata[494], data[494], EPSILONT);
    EXPECT_NEAR(imdata[495], data[495], EPSILONT);
    EXPECT_NEAR(imdata[496], data[496], EPSILONT);
    EXPECT_NEAR(imdata[497], data[497], EPSILONT);
    EXPECT_NEAR(imdata[498], data[498], EPSILONT);
    EXPECT_NEAR(imdata[499], data[499], EPSILONT);
    EXPECT_NEAR(imdata[500], data[500], EPSILONT);
    EXPECT_NEAR(imdata[501], data[501], EPSILONT);
    EXPECT_NEAR(imdata[502], data[502], EPSILONT);
    EXPECT_NEAR(imdata[503], data[503], EPSILONT);
    EXPECT_NEAR(imdata[504], data[504], EPSILONT);
    EXPECT_NEAR(imdata[505], data[505], EPSILONT);
    EXPECT_NEAR(imdata[506], data[506], EPSILONT);
    EXPECT_NEAR(imdata[507], data[507], EPSILONT);
    EXPECT_NEAR(imdata[508], data[508], EPSILONT);
    EXPECT_NEAR(imdata[509], data[509], EPSILONT);
    EXPECT_NEAR(imdata[510], data[510], EPSILONT);
    EXPECT_NEAR(imdata[511], data[511], EPSILONT);
    EXPECT_NEAR(imdata[512], data[512], EPSILONT);
    EXPECT_NEAR(imdata[513], data[513], EPSILONT);
    EXPECT_NEAR(imdata[514], data[514], EPSILONT);
    EXPECT_NEAR(imdata[515], data[515], EPSILONT);
    EXPECT_NEAR(imdata[516], data[516], EPSILONT);
    EXPECT_NEAR(imdata[517], data[517], EPSILONT);
    EXPECT_NEAR(imdata[518], data[518], EPSILONT);
    EXPECT_NEAR(imdata[519], data[519], EPSILONT);
    EXPECT_NEAR(imdata[520], data[520], EPSILONT);
    EXPECT_NEAR(imdata[521], data[521], EPSILONT);
    EXPECT_NEAR(imdata[522], data[522], EPSILONT);
    EXPECT_NEAR(imdata[523], data[523], EPSILONT);
    EXPECT_NEAR(imdata[524], data[524], EPSILONT);
    EXPECT_NEAR(imdata[525], data[525], EPSILONT);
    EXPECT_NEAR(imdata[526], data[526], EPSILONT);
    EXPECT_NEAR(imdata[527], data[527], EPSILONT);
    EXPECT_NEAR(imdata[528], data[528], EPSILONT);
    EXPECT_NEAR(imdata[529], data[529], EPSILONT);
    EXPECT_NEAR(imdata[530], data[530], EPSILONT);
    EXPECT_NEAR(imdata[531], data[531], EPSILONT);
    EXPECT_NEAR(imdata[532], data[532], EPSILONT);
    EXPECT_NEAR(imdata[533], data[533], EPSILONT);
    EXPECT_NEAR(imdata[534], data[534], EPSILONT);
    EXPECT_NEAR(imdata[535], data[535], EPSILONT);
    EXPECT_NEAR(imdata[536], data[536], EPSILONT);
    EXPECT_NEAR(imdata[537], data[537], EPSILONT);
    EXPECT_NEAR(imdata[538], data[538], EPSILONT);
    EXPECT_NEAR(imdata[539], data[539], EPSILONT);
    EXPECT_NEAR(imdata[540], data[540], EPSILONT);
    EXPECT_NEAR(imdata[541], data[541], EPSILONT);
    EXPECT_NEAR(imdata[542], data[542], EPSILONT);
    EXPECT_NEAR(imdata[543], data[543], EPSILONT);
    EXPECT_NEAR(imdata[544], data[544], EPSILONT);
    EXPECT_NEAR(imdata[545], data[545], EPSILONT);
    EXPECT_NEAR(imdata[546], data[546], EPSILONT);
    EXPECT_NEAR(imdata[547], data[547], EPSILONT);
    EXPECT_NEAR(imdata[548], data[548], EPSILONT);
    EXPECT_NEAR(imdata[549], data[549], EPSILONT);
    EXPECT_NEAR(imdata[550], data[550], EPSILONT);
    EXPECT_NEAR(imdata[551], data[551], EPSILONT);
    EXPECT_NEAR(imdata[552], data[552], EPSILONT);
    EXPECT_NEAR(imdata[553], data[553], EPSILONT);
    EXPECT_NEAR(imdata[554], data[554], EPSILONT);
    EXPECT_NEAR(imdata[555], data[555], EPSILONT);
    EXPECT_NEAR(imdata[556], data[556], EPSILONT);
    EXPECT_NEAR(imdata[557], data[557], EPSILONT);
    EXPECT_NEAR(imdata[558], data[558], EPSILONT);
    EXPECT_NEAR(imdata[559], data[559], EPSILONT);
    EXPECT_NEAR(imdata[560], data[560], EPSILONT);
    EXPECT_NEAR(imdata[561], data[561], EPSILONT);
    EXPECT_NEAR(imdata[562], data[562], EPSILONT);
    EXPECT_NEAR(imdata[563], data[563], EPSILONT);
    EXPECT_NEAR(imdata[564], data[564], EPSILONT);
    EXPECT_NEAR(imdata[565], data[565], EPSILONT);
    EXPECT_NEAR(imdata[566], data[566], EPSILONT);
    EXPECT_NEAR(imdata[567], data[567], EPSILONT);
    EXPECT_NEAR(imdata[568], data[568], EPSILONT);
    EXPECT_NEAR(imdata[569], data[569], EPSILONT);
    EXPECT_NEAR(imdata[570], data[570], EPSILONT);
    EXPECT_NEAR(imdata[571], data[571], EPSILONT);
    EXPECT_NEAR(imdata[572], data[572], EPSILONT);
    EXPECT_NEAR(imdata[573], data[573], EPSILONT);
    EXPECT_NEAR(imdata[574], data[574], EPSILONT);
    EXPECT_NEAR(imdata[575], data[575], EPSILONT);
    EXPECT_NEAR(imdata[576], data[576], EPSILONT);
    EXPECT_NEAR(imdata[577], data[577], EPSILONT);
    EXPECT_NEAR(imdata[578], data[578], EPSILONT);
    EXPECT_NEAR(imdata[579], data[579], EPSILONT);
    EXPECT_NEAR(imdata[580], data[580], EPSILONT);
    EXPECT_NEAR(imdata[581], data[581], EPSILONT);
    EXPECT_NEAR(imdata[582], data[582], EPSILONT);
    EXPECT_NEAR(imdata[583], data[583], EPSILONT);
    EXPECT_NEAR(imdata[584], data[584], EPSILONT);
    EXPECT_NEAR(imdata[585], data[585], EPSILONT);
    EXPECT_NEAR(imdata[586], data[586], EPSILONT);
    EXPECT_NEAR(imdata[587], data[587], EPSILONT);
    EXPECT_NEAR(imdata[588], data[588], EPSILONT);
    EXPECT_NEAR(imdata[589], data[589], EPSILONT);
    EXPECT_NEAR(imdata[590], data[590], EPSILONT);
    EXPECT_NEAR(imdata[591], data[591], EPSILONT);
    EXPECT_NEAR(imdata[592], data[592], EPSILONT);
    EXPECT_NEAR(imdata[593], data[593], EPSILONT);
    EXPECT_NEAR(imdata[594], data[594], EPSILONT);
    EXPECT_NEAR(imdata[595], data[595], EPSILONT);
    EXPECT_NEAR(imdata[596], data[596], EPSILONT);
    EXPECT_NEAR(imdata[597], data[597], EPSILONT);
    EXPECT_NEAR(imdata[598], data[598], EPSILONT);
    EXPECT_NEAR(imdata[599], data[599], EPSILONT);
    EXPECT_NEAR(imdata[600], data[600], EPSILONT);
    EXPECT_NEAR(imdata[601], data[601], EPSILONT);
    EXPECT_NEAR(imdata[602], data[602], EPSILONT);
    EXPECT_NEAR(imdata[603], data[603], EPSILONT);
    EXPECT_NEAR(imdata[604], data[604], EPSILONT);
    EXPECT_NEAR(imdata[605], data[605], EPSILONT);
    EXPECT_NEAR(imdata[606], data[606], EPSILONT);
    EXPECT_NEAR(imdata[607], data[607], EPSILONT);
    EXPECT_NEAR(imdata[608], data[608], EPSILONT);
    EXPECT_NEAR(imdata[609], data[609], EPSILONT);
    EXPECT_NEAR(imdata[610], data[610], EPSILONT);
    EXPECT_NEAR(imdata[611], data[611], EPSILONT);
    EXPECT_NEAR(imdata[612], data[612], EPSILONT);
    EXPECT_NEAR(imdata[613], data[613], EPSILONT);
    EXPECT_NEAR(imdata[614], data[614], EPSILONT);
    EXPECT_NEAR(imdata[615], data[615], EPSILONT);
    EXPECT_NEAR(imdata[616], data[616], EPSILONT);
    EXPECT_NEAR(imdata[617], data[617], EPSILONT);
    EXPECT_NEAR(imdata[618], data[618], EPSILONT);
    EXPECT_NEAR(imdata[619], data[619], EPSILONT);
    EXPECT_NEAR(imdata[620], data[620], EPSILONT);
    EXPECT_NEAR(imdata[621], data[621], EPSILONT);
    EXPECT_NEAR(imdata[622], data[622], EPSILONT);
    EXPECT_NEAR(imdata[623], data[623], EPSILONT);
    EXPECT_NEAR(imdata[624], data[624], EPSILONT);
    EXPECT_NEAR(imdata[625], data[625], EPSILONT);
    EXPECT_NEAR(imdata[626], data[626], EPSILONT);
    EXPECT_NEAR(imdata[627], data[627], EPSILONT);
    EXPECT_NEAR(imdata[628], data[628], EPSILONT);
    EXPECT_NEAR(imdata[629], data[629], EPSILONT);

    EXPECT_EQ(imCC->getNElements(), N);
    EXPECT_NE(imCC->getNElements(), N + 1);

    EXPECT_EQ(imCC->getNColumns(), nC);
    EXPECT_NE(imCC->getNColumns(), nC + 1);

    EXPECT_EQ(imCC->getNRows(), nR);
    EXPECT_NE(imCC->getNRows(), nR + 1);

    EXPECT_EQ(imCC->getNLayers(), nL);
    EXPECT_NE(imCC->getNLayers(), nL + 1);

    EXPECT_EQ(imCC->getNBands(), nB);
    EXPECT_NE(imCC->getNBands(), nB + 1);

    // validity of elements
    EXPECT_FALSE(imCC->isValid(-1));
    EXPECT_TRUE(imCC->isValid(0));
    EXPECT_TRUE(imCC->isValid(N - 1));
    EXPECT_FALSE(imCC->isValid(N));

    EXPECT_FALSE(imCC->isValid(0, -1));
    EXPECT_FALSE(imCC->isValid(N - 1, -1));
    EXPECT_FALSE(imCC->isValid(-1, 0));
    EXPECT_TRUE(imCC->isValid(0, 0));
    EXPECT_TRUE(imCC->isValid(N - 1, 0));
    EXPECT_FALSE(imCC->isValid(N, 0));
    EXPECT_TRUE(imCC->isValid(0, nB - 1));
    EXPECT_TRUE(imCC->isValid(N - 1, nB - 1));
    EXPECT_FALSE(imCC->isValid(0, nB));
    EXPECT_FALSE(imCC->isValid(N - 1, nB));

    EXPECT_FALSE(imCC->isValid(-1, 0, 0));
    EXPECT_FALSE(imCC->isValid(0, -1, 0));
    EXPECT_FALSE(imCC->isValid(0, 0, -1));
    EXPECT_TRUE(imCC->isValid(0, 0, 0));
    EXPECT_TRUE(imCC->isValid(nR - 1, 0, 0));
    EXPECT_TRUE(imCC->isValid(0, nC - 1, 0));
    EXPECT_TRUE(imCC->isValid(0, 0, nL - 1));
    EXPECT_FALSE(imCC->isValid(nR, 0, 0));
    EXPECT_FALSE(imCC->isValid(0, nC, 0));
    EXPECT_FALSE(imCC->isValid(0, 0, nL));

    EXPECT_FALSE(imCC->isValid(0, 0, 0, -1));
    EXPECT_FALSE(imCC->isValid(nR - 1, 0, 0, -1));
    EXPECT_FALSE(imCC->isValid(0, nC - 1, 0, -1));
    EXPECT_FALSE(imCC->isValid(0, 0, nL - 1, -1));
    EXPECT_FALSE(imCC->isValid(0, 0, 0, nB));
    EXPECT_FALSE(imCC->isValid(nR - 1, 0, 0, nB));
    EXPECT_FALSE(imCC->isValid(0, nC - 1, 0, nB));
    EXPECT_FALSE(imCC->isValid(0, 0, nL - 1, nB));
    EXPECT_TRUE(imCC->isValid(0, 0, 0, nB - 1));
    EXPECT_TRUE(imCC->isValid(nR - 1, 0, 0, nB - 1));
    EXPECT_TRUE(imCC->isValid(0, nC - 1, 0, nB - 1));
    EXPECT_TRUE(imCC->isValid(0, 0, nL - 1, nB - 1));

    // index conversion
    EXPECT_EQ(imCC->rclToIndex(0, 0, 0), 0);
    EXPECT_EQ(imCC->rclToIndex(1, 2, 3), 98);
    EXPECT_EQ(imCC->rclToIndex(nR - 1, nC - 1, nL - 1), N - 1);

    EXPECT_EQ(imCC->indexToR(0), 0);
    EXPECT_EQ(imCC->indexToC(0), 0);
    EXPECT_EQ(imCC->indexToL(0), 0);
    EXPECT_EQ(imCC->indexToR(98), 1);
    EXPECT_EQ(imCC->indexToC(98), 2);
    EXPECT_EQ(imCC->indexToL(98), 3);
    EXPECT_EQ(imCC->indexToR(N - 1), nR - 1);
    EXPECT_EQ(imCC->indexToC(N - 1), nC - 1);
    EXPECT_EQ(imCC->indexToL(N - 1), nL - 1);

    delete imCC;
}

TEST(CImageCC, coordinates) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = 0;
    }
    CImageCC<uint8> *imCC = new CImageCC<uint8>(data, nR, nC, nL, nB);
    double volume = 2.5;
    double factor = cbrt(volume);
    CImageCC<uint8> *imCC2 = new CImageCC<uint8>(data, nR, nC, nL, nB, volume);

    CImageCC<uint8> *imCC1C1L = new CImageCC<uint8>(data, N, 1, 1, 1);
    CImageCC<uint8> *imCC1R1L = new CImageCC<uint8>(data, 1, N, 1, 1);
    CImageCC<uint8> *imCC1R1C = new CImageCC<uint8>(data, 1, 1, N, 1);
    int n1 = 15, n2 = 14;
    CImageCC<uint8> *imCCRC = new CImageCC<uint8>(data, n1, n2, 1, 1);
    CImageCC<uint8> *imCCRL = new CImageCC<uint8>(data, n1, 1, n2, 1);
    CImageCC<uint8> *imCCCL = new CImageCC<uint8>(data, 1, n1, n2, 1);
    vector<double> coordinates;

    // spel coordinates
    EXPECT_NEAR(imCC->indexToX(0), 0.5, EPSILONT);
    EXPECT_NEAR(imCC->indexToY(0), 0.5, EPSILONT);
    EXPECT_NEAR(imCC->indexToZ(0), 0.5, EPSILONT);
    EXPECT_NEAR(imCC->indexToX(170), 0.5 + 2, EPSILONT);
    EXPECT_NEAR(imCC->indexToY(170), 0.5 + 3, EPSILONT);
    EXPECT_NEAR(imCC->indexToZ(170), 0.5 + 5, EPSILONT);
    EXPECT_NEAR(imCC->indexToX(209), 0.5 + 5, EPSILONT);
    EXPECT_NEAR(imCC->indexToY(209), 0.5 + 4, EPSILONT);
    EXPECT_NEAR(imCC->indexToZ(209), 0.5 + 6, EPSILONT);
    EXPECT_NEAR(imCC->indexToX(N - 1), 0.5 + nC - 1, EPSILONT);
    EXPECT_NEAR(imCC->indexToY(N - 1), 0.5 + nR - 1, EPSILONT);
    EXPECT_NEAR(imCC->indexToZ(N - 1), 0.5 + nL - 1, EPSILONT);

    imCC->getCoordinates(0, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5, EPSILONT);
    imCC->getCoordinates(170, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5 + 2, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5 + 3, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5 + 5, EPSILONT);
    imCC->getCoordinates(209, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5 + 5, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5 + 4, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5 + 6, EPSILONT);
    imCC->getCoordinates(N - 1, coordinates);
    EXPECT_NEAR(coordinates[0], 0.5 + nC - 1, EPSILONT);
    EXPECT_NEAR(coordinates[1], 0.5 + nR - 1, EPSILONT);
    EXPECT_NEAR(coordinates[2], 0.5 + nL - 1, EPSILONT);

    EXPECT_NEAR(imCC2->indexToX(0), 0.5 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToY(0), 0.5 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToZ(0), 0.5 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToX(170), (0.5 + 2) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToY(170), (0.5 + 3) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToZ(170), (0.5 + 5) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToX(209), (0.5 + 5) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToY(209), (0.5 + 4) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToZ(209), (0.5 + 6) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToX(N - 1), (0.5 + (nC - 1)) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToY(N - 1), (0.5 + (nR - 1)) * factor, EPSILONT);
    EXPECT_NEAR(imCC2->indexToZ(N - 1), (0.5 + (nL - 1)) * factor, EPSILONT);

    EXPECT_GT(imCC2->indexToX(170) - imCC->indexToX(170), EPSILONT);
    EXPECT_GT(imCC2->indexToY(170) - imCC->indexToY(170), EPSILONT);
    EXPECT_GT(imCC2->indexToZ(170) - imCC->indexToZ(170), EPSILONT);
    EXPECT_GT(imCC2->indexToX(209) - imCC->indexToX(209), EPSILONT);
    EXPECT_GT(imCC2->indexToY(209) - imCC->indexToY(209), EPSILONT);
    EXPECT_GT(imCC2->indexToZ(209) - imCC->indexToZ(209), EPSILONT);
    EXPECT_GT(imCC2->indexToX(N - 1) - imCC->indexToX(N - 1), EPSILONT);
    EXPECT_GT(imCC2->indexToY(N - 1) - imCC->indexToY(N - 1), EPSILONT);
    EXPECT_GT(imCC2->indexToZ(N - 1) - imCC->indexToZ(N - 1), EPSILONT);

    // width, height and depth
    EXPECT_NEAR(imCC->getWidth(), 6, EPSILONT);
    EXPECT_NEAR(imCC->getHeight(), 5, EPSILONT);
    EXPECT_NEAR(imCC->getDepth(), 7, EPSILONT);
    EXPECT_NEAR(imCC2->getWidth(), factor * 6, EPSILONT);
    EXPECT_NEAR(imCC2->getHeight(), factor * 5, EPSILONT);
    EXPECT_NEAR(imCC2->getDepth(), factor * 7, EPSILONT);
    EXPECT_NEAR(imCC1C1L->getWidth(), 1, EPSILONT);
    EXPECT_NEAR(imCC1C1L->getHeight(), N, EPSILONT);
    EXPECT_NEAR(imCC1C1L->getDepth(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1L->getWidth(), N, EPSILONT);
    EXPECT_NEAR(imCC1R1L->getHeight(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1L->getDepth(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1C->getWidth(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1C->getHeight(), 1, EPSILONT);
    EXPECT_NEAR(imCC1R1C->getDepth(), N, EPSILONT);

    EXPECT_NEAR(imCCRC->getWidth(), n2, EPSILONT);
    EXPECT_NEAR(imCCRC->getHeight(), n1, EPSILONT);
    EXPECT_NEAR(imCCRC->getDepth(), 1, EPSILONT);

    EXPECT_NEAR(imCCRL->getWidth(), 1, EPSILONT);
    EXPECT_NEAR(imCCRL->getHeight(), n1, EPSILONT);
    EXPECT_NEAR(imCCRL->getDepth(), n2, EPSILONT);

    EXPECT_NEAR(imCCCL->getWidth(), n1, EPSILONT);
    EXPECT_NEAR(imCCCL->getHeight(), 1, EPSILONT);
    EXPECT_NEAR(imCCCL->getDepth(), n2, EPSILONT);

    delete imCC;
    delete imCC2;
    delete imCC1C1L;
    delete imCC1R1L;
    delete imCC1R1C;
    delete imCCCL;
    delete imCCRL;
    delete imCCRC;
}

TEST(CImageCC, distances) {

    // set up image
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N * nB];
    for (int i = 0; i < nB * N; i++) {
        data[i] = 0;
    }
    CImageCC<uint8> *imCC = new CImageCC<uint8>(data, nR, nC, nL, nB);
    double volume = 2.5;
    double factor = cbrt(volume);
    CImageCC<uint8> *imCC2 = new CImageCC<uint8>(data, nR, nC, nL, nB, volume);

    // distance between spels
    EXPECT_NEAR(imCC->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 104), 1, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 104), imCC->euclideanDistance(104, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 97), 1, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 97), imCC->euclideanDistance(97, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 73), 1, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 73), imCC->euclideanDistance(73, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 110), 1.41421356237, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 110), imCC->euclideanDistance(110, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 98), 1.41421356237, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 98), imCC->euclideanDistance(98, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 67), 1.41421356237, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 67), imCC->euclideanDistance(67, 103), EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 79), 1.41421356237, EPSILONT);
    EXPECT_NEAR(imCC->euclideanDistance(103, 79), imCC->euclideanDistance(79, 103), EPSILONT);

    EXPECT_NEAR(imCC2->euclideanDistance(0, 0), 0, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(170, 170), 0, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 104), 1 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 104), imCC2->euclideanDistance(104, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 97), 1 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 97), imCC2->euclideanDistance(97, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 73), 1 * factor, EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 73), imCC2->euclideanDistance(73, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 110), sqrt(factor * factor * 2), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 110), imCC2->euclideanDistance(110, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 98), sqrt(factor * factor * 2), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 98), imCC2->euclideanDistance(98, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 67), sqrt(factor * factor * 2), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 67), imCC2->euclideanDistance(67, 103), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 79), sqrt(factor * factor * 2), EPSILONT);
    EXPECT_NEAR(imCC2->euclideanDistance(103, 79), imCC2->euclideanDistance(79, 103), EPSILONT);

    vector<double> dv;
    double xyz100[3] = {1, 0, 0};
    double xyz010[3] = {0, 1, 0};
    double xyz001[3] = {0, 0, 1};
    double xyz123[3] = {1, 2, 3};
    imCC->euclideanDistanceVector(103, 103, dv);
    EXPECT_TRUE(fabs(dv[0]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[1]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[2]) < EPSILONT);
    imCC->euclideanDistanceVector(103, 104, dv);
    EXPECT_NEAR(dv[0], xyz100[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz100[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz100[2], EPSILONT);
    imCC->euclideanDistanceVector(103, 109, dv);
    EXPECT_NEAR(dv[0], xyz010[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz010[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz010[2], EPSILONT);
    imCC->euclideanDistanceVector(73, 103, dv);
    EXPECT_NEAR(dv[0], xyz001[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz001[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz001[2], EPSILONT);
    imCC->euclideanDistanceVector(13, 116, dv);
    EXPECT_NEAR(dv[0], xyz123[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz123[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz123[2], EPSILONT);

    double xyz2100[3] = {1 * factor, 0, 0};
    double xyz2010[3] = {0, 1 * factor, 0};
    double xyz2001[3] = {0, 0, 1 * factor};
    double xyz2123[3] = {1 * factor, 2 * factor, 3 * factor};
    imCC2->euclideanDistanceVector(103, 103, dv);
    EXPECT_TRUE(fabs(dv[0]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[1]) < EPSILONT);
    EXPECT_TRUE(fabs(dv[2]) < EPSILONT);
    imCC2->euclideanDistanceVector(103, 104, dv);
    EXPECT_NEAR(dv[0], xyz2100[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz2100[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz2100[2], EPSILONT);
    imCC2->euclideanDistanceVector(103, 109, dv);
    EXPECT_NEAR(dv[0], xyz2010[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz2010[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz2010[2], EPSILONT);
    imCC2->euclideanDistanceVector(73, 103, dv);
    EXPECT_NEAR(dv[0], xyz2001[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz2001[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz2001[2], EPSILONT);
    imCC2->euclideanDistanceVector(13, 116, dv);
    EXPECT_NEAR(dv[0], xyz2123[0], EPSILONT);
    EXPECT_NEAR(dv[1], xyz2123[1], EPSILONT);
    EXPECT_NEAR(dv[2], xyz2123[2], EPSILONT);

    delete imCC;
    delete imCC2;

}

TEST(CImageCC, neighbors) {
    /**
    * Tests getNeighbor(r,c,l,N) and getNeighbor(i,N). Since these
    * always call getXNeighbors(r,c,l), those methods should work
    * properly if the tests pass.
    */

    // image parameters
    int nR = 5, nC = 6, nL = 7, nB = 3;
    int N = nR * nC * nL;
    uint8 data[N];
    for (int i = 0; i < N * nB; i++) {
        data[i] = 0;
    }
    CImageCC<uint8> *imCC = new CImageCC<uint8>(data, nR, nC, nL, nB);

    vector<Neighbor> neighbors;
    int nNeighbors, returnedNeighbors, correctNNeighbors;
    // neighbor indices
    //{r,l,bo,t,f,ba,   bor,tr,bar,fr,bol,tl,bal,fl,boba,bof,tba,tf,   bofr,tfr,tbar,bobar,bofl,tfl,tbal,bobal}
    int CC6[6] = {171, 169, 176, 164, 140, 200};    // {63,61,67,57,37,87};
    int CC18[18] = {171, 169, 176, 164, 140, 200, 177, 165, 201, 141, 175, 163, 199, 139, 206, 146, 194, 134};    // {63,61,67,57,37,87,68,58,88,38,66,56,86,36,92,42,82,32};
    int CC26[26] = {171, 169, 176, 164, 140, 200, 177, 165, 201, 141, 175, 163, 199, 139, 206, 146, 194, 134, 147, 135, 195, 207, 145, 133, 193, 205};// {63,61,67,57,37,87,68,58,88,38,66,56,86,36,92,42,82,32,43,33,83,93,41,31,81,91};

    // 6 neighbors
    nNeighbors = 6;
    correctNNeighbors = 6;
    imCC->getNeighbors(3, 2, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), CC6[0]);
    EXPECT_EQ(neighbors[1].getIndex(), CC6[1]);
    EXPECT_EQ(neighbors[2].getIndex(), CC6[2]);
    EXPECT_EQ(neighbors[3].getIndex(), CC6[3]);
    EXPECT_EQ(neighbors[4].getIndex(), CC6[4]);
    EXPECT_EQ(neighbors[5].getIndex(), CC6[5]);
    imCC->getNeighbors(imCC->rclToIndex(3, 2, 5), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), CC6[0]);
    EXPECT_EQ(neighbors[1].getIndex(), CC6[1]);
    EXPECT_EQ(neighbors[2].getIndex(), CC6[2]);
    EXPECT_EQ(neighbors[3].getIndex(), CC6[3]);
    EXPECT_EQ(neighbors[4].getIndex(), CC6[4]);
    EXPECT_EQ(neighbors[5].getIndex(), CC6[5]);

    correctNNeighbors = 3;
    imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 4;
    imCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 5;
    imCC->getNeighbors(0, 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 2, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 1, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 2, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    // 18 neighbors
    nNeighbors = 18;
    correctNNeighbors = 18;
    imCC->getNeighbors(3, 2, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), CC18[0]);
    EXPECT_EQ(neighbors[1].getIndex(), CC18[1]);
    EXPECT_EQ(neighbors[2].getIndex(), CC18[2]);
    EXPECT_EQ(neighbors[3].getIndex(), CC18[3]);
    EXPECT_EQ(neighbors[4].getIndex(), CC18[4]);
    EXPECT_EQ(neighbors[5].getIndex(), CC18[5]);
    EXPECT_EQ(neighbors[6].getIndex(), CC18[6]);
    EXPECT_EQ(neighbors[7].getIndex(), CC18[7]);
    EXPECT_EQ(neighbors[8].getIndex(), CC18[8]);
    EXPECT_EQ(neighbors[9].getIndex(), CC18[9]);
    EXPECT_EQ(neighbors[10].getIndex(), CC18[10]);
    EXPECT_EQ(neighbors[11].getIndex(), CC18[11]);
    EXPECT_EQ(neighbors[12].getIndex(), CC18[12]);
    EXPECT_EQ(neighbors[13].getIndex(), CC18[13]);
    EXPECT_EQ(neighbors[14].getIndex(), CC18[14]);
    EXPECT_EQ(neighbors[15].getIndex(), CC18[15]);
    EXPECT_EQ(neighbors[16].getIndex(), CC18[16]);
    EXPECT_EQ(neighbors[17].getIndex(), CC18[17]);
    imCC->getNeighbors(imCC->rclToIndex(3, 2, 5), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), CC18[0]);
    EXPECT_EQ(neighbors[1].getIndex(), CC18[1]);
    EXPECT_EQ(neighbors[2].getIndex(), CC18[2]);
    EXPECT_EQ(neighbors[3].getIndex(), CC18[3]);
    EXPECT_EQ(neighbors[4].getIndex(), CC18[4]);
    EXPECT_EQ(neighbors[5].getIndex(), CC18[5]);
    EXPECT_EQ(neighbors[6].getIndex(), CC18[6]);
    EXPECT_EQ(neighbors[7].getIndex(), CC18[7]);
    EXPECT_EQ(neighbors[8].getIndex(), CC18[8]);
    EXPECT_EQ(neighbors[9].getIndex(), CC18[9]);
    EXPECT_EQ(neighbors[10].getIndex(), CC18[10]);
    EXPECT_EQ(neighbors[11].getIndex(), CC18[11]);
    EXPECT_EQ(neighbors[12].getIndex(), CC18[12]);
    EXPECT_EQ(neighbors[13].getIndex(), CC18[13]);
    EXPECT_EQ(neighbors[14].getIndex(), CC18[14]);
    EXPECT_EQ(neighbors[15].getIndex(), CC18[15]);
    EXPECT_EQ(neighbors[16].getIndex(), CC18[16]);
    EXPECT_EQ(neighbors[17].getIndex(), CC18[17]);

    correctNNeighbors = 6;
    imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 9;
    imCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 13;
    imCC->getNeighbors(0, 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 2, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 1, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 2, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    // 26 neighbors
    nNeighbors = 26;
    correctNNeighbors = 26;
    imCC->getNeighbors(3, 2, 5, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), CC26[0]);
    EXPECT_EQ(neighbors[1].getIndex(), CC26[1]);
    EXPECT_EQ(neighbors[2].getIndex(), CC26[2]);
    EXPECT_EQ(neighbors[3].getIndex(), CC26[3]);
    EXPECT_EQ(neighbors[4].getIndex(), CC26[4]);
    EXPECT_EQ(neighbors[5].getIndex(), CC26[5]);
    EXPECT_EQ(neighbors[6].getIndex(), CC26[6]);
    EXPECT_EQ(neighbors[7].getIndex(), CC26[7]);
    EXPECT_EQ(neighbors[8].getIndex(), CC26[8]);
    EXPECT_EQ(neighbors[9].getIndex(), CC26[9]);
    EXPECT_EQ(neighbors[10].getIndex(), CC26[10]);
    EXPECT_EQ(neighbors[11].getIndex(), CC26[11]);
    EXPECT_EQ(neighbors[12].getIndex(), CC26[12]);
    EXPECT_EQ(neighbors[13].getIndex(), CC26[13]);
    EXPECT_EQ(neighbors[14].getIndex(), CC26[14]);
    EXPECT_EQ(neighbors[15].getIndex(), CC26[15]);
    EXPECT_EQ(neighbors[16].getIndex(), CC26[16]);
    EXPECT_EQ(neighbors[17].getIndex(), CC26[17]);
    EXPECT_EQ(neighbors[18].getIndex(), CC26[18]);
    EXPECT_EQ(neighbors[19].getIndex(), CC26[19]);
    EXPECT_EQ(neighbors[20].getIndex(), CC26[20]);
    EXPECT_EQ(neighbors[21].getIndex(), CC26[21]);
    EXPECT_EQ(neighbors[22].getIndex(), CC26[22]);
    EXPECT_EQ(neighbors[23].getIndex(), CC26[23]);
    EXPECT_EQ(neighbors[24].getIndex(), CC26[24]);
    EXPECT_EQ(neighbors[25].getIndex(), CC26[25]);
    imCC->getNeighbors(imCC->rclToIndex(3, 2, 5), nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    EXPECT_EQ(neighbors[0].getIndex(), CC26[0]);
    EXPECT_EQ(neighbors[1].getIndex(), CC26[1]);
    EXPECT_EQ(neighbors[2].getIndex(), CC26[2]);
    EXPECT_EQ(neighbors[3].getIndex(), CC26[3]);
    EXPECT_EQ(neighbors[4].getIndex(), CC26[4]);
    EXPECT_EQ(neighbors[5].getIndex(), CC26[5]);
    EXPECT_EQ(neighbors[6].getIndex(), CC26[6]);
    EXPECT_EQ(neighbors[7].getIndex(), CC26[7]);
    EXPECT_EQ(neighbors[8].getIndex(), CC26[8]);
    EXPECT_EQ(neighbors[9].getIndex(), CC26[9]);
    EXPECT_EQ(neighbors[10].getIndex(), CC26[10]);
    EXPECT_EQ(neighbors[11].getIndex(), CC26[11]);
    EXPECT_EQ(neighbors[12].getIndex(), CC26[12]);
    EXPECT_EQ(neighbors[13].getIndex(), CC26[13]);
    EXPECT_EQ(neighbors[14].getIndex(), CC26[14]);
    EXPECT_EQ(neighbors[15].getIndex(), CC26[15]);
    EXPECT_EQ(neighbors[16].getIndex(), CC26[16]);
    EXPECT_EQ(neighbors[17].getIndex(), CC26[17]);
    EXPECT_EQ(neighbors[18].getIndex(), CC26[18]);
    EXPECT_EQ(neighbors[19].getIndex(), CC26[19]);
    EXPECT_EQ(neighbors[20].getIndex(), CC26[20]);
    EXPECT_EQ(neighbors[21].getIndex(), CC26[21]);
    EXPECT_EQ(neighbors[22].getIndex(), CC26[22]);
    EXPECT_EQ(neighbors[23].getIndex(), CC26[23]);
    EXPECT_EQ(neighbors[24].getIndex(), CC26[24]);
    EXPECT_EQ(neighbors[25].getIndex(), CC26[25]);
    correctNNeighbors = 7;
    imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 0, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 11;
    imCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, 1, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    correctNNeighbors = 17;
    imCC->getNeighbors(0, 1, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(1, 1, 0, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 1, nC - 2, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 1, nL - 2, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);
    imCC->getNeighbors(nR - 2, nC - 2, nL - 1, nNeighbors, neighbors);
    returnedNeighbors = neighbors.size();
    EXPECT_EQ(returnedNeighbors, correctNNeighbors);

    // Exceptions
    nNeighbors = 6;
    EXPECT_THROW(imCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 18;
    EXPECT_THROW(imCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 26;
    EXPECT_THROW(imCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
    EXPECT_THROW(imCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
    nNeighbors = 8;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 12;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 14;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    // nNeighbors = 18 is valid for both CC and FCC.
    nNeighbors = -6;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 0;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
    nNeighbors = 100;
    EXPECT_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);

    delete imCC;

}

TEST(CImageCC, operators) {

    int nR = 2, nC = 3, nL = 4, nB = 5;
    int N = nR * nC * nL;
    double data[] = {1, 2, 3, 4, 5, 6,
            2, 3, 4, 5, 6, 1,
            3, 4, 5, 6, 1, 2,
            4, 5, 6, 1, 2, 3,

            11, 12, 13, 14, 15, 16,
            12, 13, 14, 15, 16, 11,
            13, 14, 15, 16, 11, 12,
            14, 15, 16, 11, 12, 13,

            21, 22, 23, 24, 25, 26,
            22, 23, 24, 25, 26, 21,
            23, 24, 25, 26, 21, 22,
            24, 25, 26, 21, 22, 23,

            31, 32, 33, 34, 35, 36,
            32, 33, 34, 35, 36, 31,
            33, 34, 35, 36, 31, 32,
            34, 35, 36, 31, 32, 33,

            41, 42, 43, 44, 45, 46,
            42, 43, 44, 45, 46, 41,
            43, 44, 45, 46, 41, 42,
            44, 45, 46, 41, 42, 43};

    CImageCC<double> *imCC = new CImageCC<double>(data, nR, nC, nL, nB);

    int index;
    double returnedVal;
    vector<double> returnedElem;

    // []-operator
    index = 0;
    returnedElem = (*imCC)[index];
    EXPECT_EQ(returnedElem.size(), nB);
    EXPECT_NEAR(returnedElem[0], 10 * 0 + 1, EPSILONT);
    EXPECT_NEAR(returnedElem[1], 10 * 1 + 1, EPSILONT);
    EXPECT_NEAR(returnedElem[2], 10 * 2 + 1, EPSILONT);
    EXPECT_NEAR(returnedElem[3], 10 * 3 + 1, EPSILONT);
    EXPECT_NEAR(returnedElem[4], 10 * 4 + 1, EPSILONT);
    index = 14;
    returnedElem = (*imCC)[index];
    EXPECT_EQ(returnedElem.size(), nB);
    EXPECT_NEAR(returnedElem[0], 10 * 0 + 5, EPSILONT);
    EXPECT_NEAR(returnedElem[1], 10 * 1 + 5, EPSILONT);
    EXPECT_NEAR(returnedElem[2], 10 * 2 + 5, EPSILONT);
    EXPECT_NEAR(returnedElem[3], 10 * 3 + 5, EPSILONT);
    EXPECT_NEAR(returnedElem[4], 10 * 4 + 5, EPSILONT);
    index = 10;
    returnedElem = (*imCC)[index];
    EXPECT_EQ(returnedElem.size(), nB);
    EXPECT_NEAR(returnedElem[0], 10 * 0 + 6, EPSILONT);
    EXPECT_NEAR(returnedElem[1], 10 * 1 + 6, EPSILONT);
    EXPECT_NEAR(returnedElem[2], 10 * 2 + 6, EPSILONT);
    EXPECT_NEAR(returnedElem[3], 10 * 3 + 6, EPSILONT);
    EXPECT_NEAR(returnedElem[4], 10 * 4 + 6, EPSILONT);
    index = N - 1;
    returnedElem = (*imCC)[index];
    EXPECT_EQ(returnedElem.size(), nB);
    EXPECT_NEAR(returnedElem[0], 10 * 0 + 3, EPSILONT);
    EXPECT_NEAR(returnedElem[1], 10 * 1 + 3, EPSILONT);
    EXPECT_NEAR(returnedElem[2], 10 * 2 + 3, EPSILONT);
    EXPECT_NEAR(returnedElem[3], 10 * 3 + 3, EPSILONT);
    EXPECT_NEAR(returnedElem[4], 10 * 4 + 3, EPSILONT);

    // ()-operator
    returnedVal = (*imCC)(0, 0, 0, 0);
    EXPECT_NEAR(returnedVal, 1, EPSILONT);
    returnedVal = (*imCC)(0, 1, 2, 3);
    EXPECT_NEAR(returnedVal, 34, EPSILONT);
    returnedVal = (*imCC)(nR - 1, nC - 1, nL - 1, nB - 1);
    EXPECT_NEAR(returnedVal, 43, EPSILONT);

    /*
	returnedVal = (*imCC)(imCC->rclToIndex(0, 0, 0), 0);
	EXPECT_NEAR(returnedVal, 1, EPSILONT);
	returnedVal = (*imCC)(imCC->rclToIndex(0, 1, 2), 3);
	EXPECT_NEAR(returnedVal, 34, EPSILONT);
	returnedVal = (*imCC)(imCC->rclToIndex(nR - 1, nC - 1, nL - 1), nB - 1);
	EXPECT_NEAR(returnedVal, 43, EPSILONT);
    */

    // Exceptions
    EXPECT_THROW((*imCC)[-1], outsideImageException);
    EXPECT_THROW((*imCC)[N], outsideImageException);

    EXPECT_THROW((*imCC)(-1, 0, 0, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, -1, 0, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, 0, -1, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, 0, 0, -1), outsideImageException);
    EXPECT_THROW((*imCC)(nR, 0, 0, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, nC, 0, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, 0, nL, 0), outsideImageException);
    EXPECT_THROW((*imCC)(0, 0, 0, nB), outsideImageException);

    delete imCC;
}

TEST(CImageCC, bands) {

    int nR = 2, nC = 3, nL = 4, nB = 5;
    int N = nR * nC * nL;
    double data[] = {1, 2, 3, 4, 5, 6,
            2, 3, 4, 5, 6, 1,
            3, 4, 5, 6, 1, 2,
            4, 5, 6, 1, 2, 3,

            11, 12, 13, 14, 15, 16,
            12, 13, 14, 15, 16, 11,
            13, 14, 15, 16, 11, 12,
            14, 15, 16, 11, 12, 13,

            21, 22, 23, 24, 25, 26,
            22, 23, 24, 25, 26, 21,
            23, 24, 25, 26, 21, 22,
            24, 25, 26, 21, 22, 23,

            31, 32, 33, 34, 35, 36,
            32, 33, 34, 35, 36, 31,
            33, 34, 35, 36, 31, 32,
            34, 35, 36, 31, 32, 33,

            41, 42, 43, 44, 45, 46,
            42, 43, 44, 45, 46, 41,
            43, 44, 45, 46, 41, 42,
            44, 45, 46, 41, 42, 43};

    CImageCC<double> *imCC = new CImageCC<double>(data, nR, nC, nL, nB);

    // setElement
    double intensities[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    vector<double> intensities0(nB, 0.0);
    vector<double> intensitiesRight, intensitiesShort, intensitiesLong, originalIntensity;
    intensitiesShort.assign(intensities, intensities + 4);
    intensitiesRight.assign(intensities, intensities + 5);
    intensitiesLong.assign(intensities, intensities + 6);

    int index = 0;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 1;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 2;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 3;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 4;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 5;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 6;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 7;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 8;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 9;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 10;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 11;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 12;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 13;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 14;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 15;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 16;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 17;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 18;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 19;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 20;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 21;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 22;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);
    index = 23;
    originalIntensity = (*imCC)[index];
    imCC->setElement(index, intensities0);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), 0, EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), 0, EPSILONT);
    imCC->setElement(index, intensitiesRight);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), intensitiesRight[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), intensitiesRight[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), intensitiesRight[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), intensitiesRight[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), intensitiesRight[4], EPSILONT);
    imCC->setElement(index, originalIntensity);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 0), originalIntensity[0], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 1), originalIntensity[1], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 2), originalIntensity[2], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 3), originalIntensity[3], EPSILONT);
    EXPECT_NEAR((*imCC)(imCC->indexToR(index), imCC->indexToC(index), imCC->indexToL(index), 4), originalIntensity[4], EPSILONT);

    double *newData = imCC->getData();
    EXPECT_NEAR(data[0], newData[0], EPSILONT);
    EXPECT_NEAR(data[1], newData[1], EPSILONT);
    EXPECT_NEAR(data[2], newData[2], EPSILONT);
    EXPECT_NEAR(data[3], newData[3], EPSILONT);
    EXPECT_NEAR(data[4], newData[4], EPSILONT);
    EXPECT_NEAR(data[5], newData[5], EPSILONT);
    EXPECT_NEAR(data[6], newData[6], EPSILONT);
    EXPECT_NEAR(data[7], newData[7], EPSILONT);
    EXPECT_NEAR(data[8], newData[8], EPSILONT);
    EXPECT_NEAR(data[9], newData[9], EPSILONT);
    EXPECT_NEAR(data[10], newData[10], EPSILONT);
    EXPECT_NEAR(data[11], newData[11], EPSILONT);
    EXPECT_NEAR(data[12], newData[12], EPSILONT);
    EXPECT_NEAR(data[13], newData[13], EPSILONT);
    EXPECT_NEAR(data[14], newData[14], EPSILONT);
    EXPECT_NEAR(data[15], newData[15], EPSILONT);
    EXPECT_NEAR(data[16], newData[16], EPSILONT);
    EXPECT_NEAR(data[17], newData[17], EPSILONT);
    EXPECT_NEAR(data[18], newData[18], EPSILONT);
    EXPECT_NEAR(data[19], newData[19], EPSILONT);
    EXPECT_NEAR(data[20], newData[20], EPSILONT);
    EXPECT_NEAR(data[21], newData[21], EPSILONT);
    EXPECT_NEAR(data[22], newData[22], EPSILONT);
    EXPECT_NEAR(data[23], newData[23], EPSILONT);

    EXPECT_NEAR(data[24], newData[24], EPSILONT);
    EXPECT_NEAR(data[25], newData[25], EPSILONT);
    EXPECT_NEAR(data[26], newData[26], EPSILONT);
    EXPECT_NEAR(data[27], newData[27], EPSILONT);
    EXPECT_NEAR(data[28], newData[28], EPSILONT);
    EXPECT_NEAR(data[29], newData[29], EPSILONT);
    EXPECT_NEAR(data[30], newData[30], EPSILONT);
    EXPECT_NEAR(data[31], newData[31], EPSILONT);
    EXPECT_NEAR(data[32], newData[32], EPSILONT);
    EXPECT_NEAR(data[33], newData[33], EPSILONT);
    EXPECT_NEAR(data[34], newData[34], EPSILONT);
    EXPECT_NEAR(data[35], newData[35], EPSILONT);
    EXPECT_NEAR(data[36], newData[36], EPSILONT);
    EXPECT_NEAR(data[37], newData[37], EPSILONT);
    EXPECT_NEAR(data[38], newData[38], EPSILONT);
    EXPECT_NEAR(data[39], newData[39], EPSILONT);
    EXPECT_NEAR(data[40], newData[40], EPSILONT);
    EXPECT_NEAR(data[41], newData[41], EPSILONT);
    EXPECT_NEAR(data[42], newData[42], EPSILONT);
    EXPECT_NEAR(data[43], newData[43], EPSILONT);
    EXPECT_NEAR(data[44], newData[44], EPSILONT);
    EXPECT_NEAR(data[45], newData[45], EPSILONT);
    EXPECT_NEAR(data[46], newData[46], EPSILONT);
    EXPECT_NEAR(data[47], newData[47], EPSILONT);

    EXPECT_NEAR(data[48], newData[48], EPSILONT);
    EXPECT_NEAR(data[49], newData[49], EPSILONT);
    EXPECT_NEAR(data[50], newData[50], EPSILONT);
    EXPECT_NEAR(data[51], newData[51], EPSILONT);
    EXPECT_NEAR(data[52], newData[52], EPSILONT);
    EXPECT_NEAR(data[53], newData[53], EPSILONT);
    EXPECT_NEAR(data[54], newData[54], EPSILONT);
    EXPECT_NEAR(data[55], newData[55], EPSILONT);
    EXPECT_NEAR(data[56], newData[56], EPSILONT);
    EXPECT_NEAR(data[57], newData[57], EPSILONT);
    EXPECT_NEAR(data[58], newData[58], EPSILONT);
    EXPECT_NEAR(data[59], newData[59], EPSILONT);
    EXPECT_NEAR(data[60], newData[60], EPSILONT);
    EXPECT_NEAR(data[61], newData[61], EPSILONT);
    EXPECT_NEAR(data[62], newData[62], EPSILONT);
    EXPECT_NEAR(data[63], newData[63], EPSILONT);
    EXPECT_NEAR(data[64], newData[64], EPSILONT);
    EXPECT_NEAR(data[65], newData[65], EPSILONT);
    EXPECT_NEAR(data[66], newData[66], EPSILONT);
    EXPECT_NEAR(data[67], newData[67], EPSILONT);
    EXPECT_NEAR(data[68], newData[68], EPSILONT);
    EXPECT_NEAR(data[69], newData[69], EPSILONT);
    EXPECT_NEAR(data[70], newData[70], EPSILONT);
    EXPECT_NEAR(data[71], newData[71], EPSILONT);

    EXPECT_NEAR(data[72], newData[72], EPSILONT);
    EXPECT_NEAR(data[73], newData[73], EPSILONT);
    EXPECT_NEAR(data[74], newData[74], EPSILONT);
    EXPECT_NEAR(data[75], newData[75], EPSILONT);
    EXPECT_NEAR(data[76], newData[76], EPSILONT);
    EXPECT_NEAR(data[77], newData[77], EPSILONT);
    EXPECT_NEAR(data[78], newData[78], EPSILONT);
    EXPECT_NEAR(data[79], newData[79], EPSILONT);
    EXPECT_NEAR(data[80], newData[80], EPSILONT);
    EXPECT_NEAR(data[81], newData[81], EPSILONT);
    EXPECT_NEAR(data[82], newData[82], EPSILONT);
    EXPECT_NEAR(data[83], newData[83], EPSILONT);
    EXPECT_NEAR(data[84], newData[84], EPSILONT);
    EXPECT_NEAR(data[85], newData[85], EPSILONT);
    EXPECT_NEAR(data[86], newData[86], EPSILONT);
    EXPECT_NEAR(data[87], newData[87], EPSILONT);
    EXPECT_NEAR(data[88], newData[88], EPSILONT);
    EXPECT_NEAR(data[89], newData[89], EPSILONT);
    EXPECT_NEAR(data[90], newData[90], EPSILONT);
    EXPECT_NEAR(data[91], newData[91], EPSILONT);
    EXPECT_NEAR(data[92], newData[92], EPSILONT);
    EXPECT_NEAR(data[93], newData[93], EPSILONT);
    EXPECT_NEAR(data[94], newData[94], EPSILONT);
    EXPECT_NEAR(data[95], newData[95], EPSILONT);

    EXPECT_NEAR(data[96], newData[96], EPSILONT);
    EXPECT_NEAR(data[97], newData[97], EPSILONT);
    EXPECT_NEAR(data[98], newData[98], EPSILONT);
    EXPECT_NEAR(data[99], newData[99], EPSILONT);
    EXPECT_NEAR(data[100], newData[100], EPSILONT);
    EXPECT_NEAR(data[101], newData[101], EPSILONT);
    EXPECT_NEAR(data[102], newData[102], EPSILONT);
    EXPECT_NEAR(data[103], newData[103], EPSILONT);
    EXPECT_NEAR(data[104], newData[104], EPSILONT);
    EXPECT_NEAR(data[105], newData[105], EPSILONT);
    EXPECT_NEAR(data[106], newData[106], EPSILONT);
    EXPECT_NEAR(data[107], newData[107], EPSILONT);
    EXPECT_NEAR(data[108], newData[108], EPSILONT);
    EXPECT_NEAR(data[109], newData[109], EPSILONT);
    EXPECT_NEAR(data[110], newData[110], EPSILONT);
    EXPECT_NEAR(data[111], newData[111], EPSILONT);
    EXPECT_NEAR(data[112], newData[112], EPSILONT);
    EXPECT_NEAR(data[113], newData[113], EPSILONT);
    EXPECT_NEAR(data[114], newData[114], EPSILONT);
    EXPECT_NEAR(data[115], newData[115], EPSILONT);
    EXPECT_NEAR(data[116], newData[116], EPSILONT);
    EXPECT_NEAR(data[117], newData[117], EPSILONT);
    EXPECT_NEAR(data[118], newData[118], EPSILONT);
    EXPECT_NEAR(data[119], newData[119], EPSILONT);

    EXPECT_THROW(imCC->setElement(-1, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(N, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(1, intensitiesShort), dimensionMismatchException);
    EXPECT_THROW(imCC->setElement(1, intensitiesLong), dimensionMismatchException);

    EXPECT_THROW(imCC->setElement(-1, 1, 1, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(1, -1, 1, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(1, 1, -1, intensitiesRight), outsideImageException);
    EXPECT_THROW(imCC->setElement(1, intensitiesShort), dimensionMismatchException);
    EXPECT_THROW(imCC->setElement(1, intensitiesLong), dimensionMismatchException);


/*
	// image parameters
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	uint8 resultInt[N * nB];
	double resultDouble[N * nB];
	for (uint8 b = 0; b < nB; b++) {
		for (int i = 0; i < N; i++) {
			data[b * N + i] = b;
		}
	}
	CImageCC<uint8> *imCC = new CImageCC<uint8>(data, nR, nC, nL, nB);

	// extract band
	EXPECT_THROW(imCC->getBand(-1, resultInt), outsideImageException);
	EXPECT_THROW(imCC->getBand(nB, resultInt), outsideImageException);

	for (int band = 0; band < nB; band++) {
		imCC->getBand(band, resultInt);
		for (int i = 0; i < N; i++) {
			EXPECT_TRUE(resultInt[i] == data[band * N + i]);
		}
	}

	// blend bands
	for (int b = 0; b < nB; b++) {
		for (int i = 0; i < N; i++) {
			data[b * N + i] = (i + b) % 3; // imCC is updated automatically, as it points to data.
		}
	}

	// min
	imCC->blend(0, resultInt);
	for (int i = 0; i < N; i++) {
		EXPECT_EQ(resultInt[i], 0);
	}

	// max
	imCC->blend(1, resultInt);
	for (int i = 0; i < N; i++) {
		EXPECT_EQ(resultInt[i], 2);
	}

	// mean
	imCC->blend(2, resultDouble);
	for (int i = 0; i < N; i++) {
		EXPECT_NEAR(resultDouble[i], 1.0, EPSILONT);
	}

	EXPECT_THROW(imCC->blend(-1, resultInt), outsideRangeException);
	EXPECT_THROW(imCC->blend(2, resultInt), outsideRangeException);
	EXPECT_THROW(imCC->blend(-1, resultDouble), outsideRangeException);
	EXPECT_THROW(imCC->blend(0, resultDouble), outsideRangeException);
	EXPECT_THROW(imCC->blend(3, resultDouble), outsideRangeException);

	delete imCC;
*/
}

TEST(CImageCC, distanceTransforms) {

    // sub-spel precision term
/*
	int nR = 4, nC = 6, nL = 5;
	int N = nR * nC * nL;
	double dataD[] = 	{0,0,0,0,0,0,
						0,0,0,0,0,0,
						0,0,0,0,0,0,
						0,0,0,0,0,0,

						0,0.5,0.5,0.5,0.5,0,
						0,0.5,0.7,0.7,0.5,0,
						0,0.5,0.7,0.7,0.5,0,
						0,0.5,0.5,0.5,0.5,0,

						0,0.2,0.2,0.2,0.2,0,
						0,0.3,1,  1,  0.1,0,
						0,0.3,1,  1,  0.1,0,
						0,0.3,0.3,0.3,0.3,0,

						0,0.1,0.1,0.1, 0.1,0,
						0,0.2,  1,  1,0.01,0,
						0,0.2,  1,  1,0.01,0,
						0,0.4,0.4,0.2, 0.1,0,

						0,0,0,0,0,0,
						0,0,0,0,0,0,
						0,0,0,0,0,0,
						0,0,0,0,0,0};
	uint8 dataU[N];
	for(int i = 0; i < N; i++) {
		dataU[i] = round(dataD[i] * 255);
	}

	CImageCC<double> *imCCD = new CImageCC<double>(dataD,nR,nC,nL,1);
	CImageCC<uint8> *imCCU = new CImageCC<uint8>(dataU,nR,nC,nL,1);

	EXPECT_NEAR(imCCD->internalDistanceLinear(0.0),0.5, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(0.5),0.0, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(1.0),-0.5, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(uint8(0)),0.5, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(uint8(127)),0.00196078431, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceLinear(uint8(255)),-0.5, EPSILONT);
	EXPECT_THROW(imCCD->internalDistanceLinear(-0.1),outsideRangeException);
	EXPECT_THROW(imCCD->internalDistanceLinear(1.1),outsideRangeException);

	EXPECT_NEAR(imCCD->internalDistanceBall(uint8(0)),0.620350490899400, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(uint8(15)),0.344897652005037, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(uint8(255)),-0.620350490899443, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(0.0),0.620350490899400, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(0.51),imCCD->internalDistanceBall(uint8(128)), EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceBall(1.0),-0.620350490899443, EPSILONT);
	EXPECT_THROW(imCCD->internalDistanceBall(-0.1),outsideRangeException);
	EXPECT_THROW(imCCD->internalDistanceBall(1.1),outsideRangeException);

	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(uint8(0)),0.732561001953818, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(uint8(15)),0.361626850445366, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(uint8(255)),-0.729122335558677, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(0.0),0.732561001953818, EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(0.51),imCCD->internalDistanceVoronoiAverage(uint8(128)), EPSILONT);
	EXPECT_NEAR(imCCD->internalDistanceVoronoiAverage(1.0),-0.729122335558677, EPSILONT);
	EXPECT_THROW(imCCD->internalDistanceVoronoiAverage(-0.1),outsideRangeException);
	EXPECT_THROW(imCCD->internalDistanceVoronoiAverage(1.1),outsideRangeException);

	EXPECT_THROW(imCCD->approximatedInternalDistance(-1,0,1),outsideImageException);
	EXPECT_THROW(imCCU->approximatedInternalDistance(-1,0,1),outsideImageException);
	EXPECT_THROW(imCCD->approximatedInternalDistance(N,0,1),outsideImageException);
	EXPECT_THROW(imCCU->approximatedInternalDistance(N,0,1),outsideImageException);
	EXPECT_THROW(imCCD->approximatedInternalDistance(1,0,-1),outsideRangeException);
	EXPECT_THROW(imCCU->approximatedInternalDistance(1,0,-1),outsideRangeException);
	EXPECT_THROW(imCCD->approximatedInternalDistance(1,0,3),outsideRangeException);
	EXPECT_THROW(imCCU->approximatedInternalDistance(1,0,3),outsideRangeException);*/

}

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

#endif