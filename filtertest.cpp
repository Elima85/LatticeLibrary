#ifndef FILTERTEST
#define FILTERTEST


#include "gtest/gtest.h"
#include "defs.h"
//#include "filter.h"

using namespace CImage;

TEST(Filter, FilterCoefficient) {
// // constructor
// int ind[3] = {0,1,2};
// int ci[3] = {-1,0,2};
// double cd[3] = {-1.1,0.0,2.2};
// bool cb[3] = {false,true,false};
//
// FilterCoefficient<bool> fcbempty;
// FilterCoefficient<int> fciempty;
// FilterCoefficient<double> fcdempty;
// EXPECT_EQ(fcbempty.getIndex(),0);
// EXPECT_EQ(fciempty.getIndex(),0);
// EXPECT_EQ(fcdempty.getIndex(),0);
// EXPECT_EQ(fcbempty.getFactor(),false);
// EXPECT_EQ(fciempty.getFactor(),0);
// EXPECT_NEAR(fcdempty.getFactor(),0.0, EPSILONT);
//
// vector<FilterCoefficient<bool> > fcb;
// vector<FilterCoefficient<int> > fci;
// vector<FilterCoefficient<double> > fcd;
//
// for (int i = 0; i < 3; i++) {
// fcb.push_back(FilterCoefficient<bool>(ind[i],cb[i]));
// fci.push_back(FilterCoefficient<int>(ind[i],ci[i]));
// fcd.push_back(FilterCoefficient<double>(ind[i],cd[i]));
// }
//
// // getters
// for (int i = 0; i < 3; i++) {
// EXPECT_EQ(fcb[i].getIndex(), ind[i]);
// EXPECT_EQ(fci[i].getIndex(), ind[i]);
// EXPECT_EQ(fcd[i].getIndex(), ind[i]);
//
// EXPECT_EQ(fcb[i].getFactor(), cb[i]);
// EXPECT_EQ(fci[i].getFactor(), ci[i]);
// EXPECT_NEAR(fcd[i].getFactor(), cd[i], EPSILONT);
// }
//
// // setters
// int ind2[3] = {1,2,3};
// int ci2[3] = {-2,1,0};
// double cd2[3] = {0.0,2.2,1.1};
// bool cb2[3] = {true,false,true};
//
// for (int i = 0; i < 3; i++) {
// fcb[i].setIndex(ind2[i]);
// fci[i].setIndex(ind2[i]);
// fcd[i].setIndex(ind2[i]);
//
// fcb[i].setFactor(cb2[i]);
// fci[i].setFactor(ci2[i]);
// fcd[i].setFactor(cd2[i]);
// }
// for (int i = 0; i < 3; i++) {
// EXPECT_TRUE(fcb[i].getIndex() != ind[i]);
// EXPECT_TRUE(fci[i].getIndex() != ind[i]);
// EXPECT_TRUE(fcd[i].getIndex() != ind[i]);
// EXPECT_EQ(fcb[i].getIndex(), ind2[i]);
// EXPECT_EQ(fci[i].getIndex(), ind2[i]);
// EXPECT_EQ(fcd[i].getIndex(), ind2[i]);
//
// EXPECT_EQ(fcb[i].getFactor(), cb2[i]);
// EXPECT_EQ(fci[i].getFactor(), ci2[i]);
// EXPECT_NEAR(fcd[i].getFactor(), cd2[i], EPSILONT);
// EXPECT_TRUE(fcb[i].getFactor() != cb[i]);
// EXPECT_TRUE(fci[i].getFactor() != ci[i]);
// EXPECT_TRUE(fabs(fcd[i].getFactor() - cd[i]) > EPSILONT);
// }
//
// for (int i = 0; i < 3; i++) {
// fcb[i].set(ind[i],cb[i]);
// fci[i].set(ind[i],ci[i]);
// fcd[i].set(ind[i],cd[i]);
// }
// for (int i = 0; i < 3; i++) {
// EXPECT_EQ(fcb[i].getIndex(), ind[i]);
// EXPECT_EQ(fci[i].getIndex(), ind[i]);
// EXPECT_EQ(fcd[i].getIndex(), ind[i]);
//
// EXPECT_EQ(fcb[i].getFactor(), cb[i]);
// EXPECT_EQ(fci[i].getFactor(), ci[i]);
// EXPECT_NEAR(fcd[i].getFactor(), cd[i], EPSILONT);
// }
}

TEST(Filter, StructuringElement) {
//
// int inds[4] = {-1,0,1,3};
// bool vals[4] = {true,false,true,false};
// int nSize = 6;
// vector<FilterCoefficient<bool> > coeffs;
// for (int i = 0; i < 4; i++) {
// coeffs.push_back(FilterCoefficient<bool>(inds[i],vals[i]));
// }
// StructuringElement se = StructuringElement(coeffs,nSize);
//
// // getters
// vector<FilterCoefficient<bool> > coeffs2;
// coeffs2 = se.getCoeffs();
// for (int i = 0; i < 3; i++) {
// EXPECT_EQ(coeffs2[i].getIndex(),coeffs[i].getIndex());
// EXPECT_EQ(coeffs2[i].getFactor(),coeffs[i].getFactor());
// }
//
// FilterCoefficient<bool> c = FilterCoefficient<bool>(0,false);
// for (int i = 0; i < 3; i++) {
// c = se.getCoeff(i);
// EXPECT_EQ(c.getIndex(),coeffs[i].getIndex());
// EXPECT_EQ(c.getFactor(),coeffs[i].getFactor());
// }
//
// EXPECT_EQ(se.getNeighborhoodSize(),nSize);
// EXPECT_TRUE(se.getNeighborhoodSize() != nSize - 1);
// EXPECT_EQ(se.getNCoeffs(),4);
// EXPECT_TRUE(se.getNCoeffs() != 5);
//
// EXPECT_EQ(se.findCoeff(-1),0);
// EXPECT_EQ(se.findCoeff(1),2);
// EXPECT_EQ(se.findCoeff(2),-1);
//
// se.addCoeff(2,true);
// EXPECT_EQ(se.getCoeff(se.findCoeff(2)).getIndex(), 2);
// EXPECT_EQ(se.getCoeff(se.findCoeff(2)).getFactor(), true);
// EXPECT_EQ(se.getNCoeffs(),5);
//
// se.eraseCoeff(1);
// EXPECT_EQ(se.findCoeff(1),-1);
// EXPECT_EQ(se.getNCoeffs(),4);
// se.eraseCoeff(6);
// EXPECT_EQ(se.getNCoeffs(),4);
//
}

TEST(Filter, IntFilter) {
//
// int inds[4] = {-1,0,1,3};
// int vals[4] = {2,0,-1,16};
// int nSize = 6;
// vector<FilterCoefficient<int> > coeffs;
// for (int i = 0; i < 4; i++) {
// coeffs.push_back(FilterCoefficient<int>(inds[i],vals[i]));
// }
// IntFilter filter = IntFilter(coeffs,nSize);
//
// // getters
// vector<FilterCoefficient<int> > coeffs2;
// coeffs2 = filter.getCoeffs();
// for (int i = 0; i < 3; i++) {
// EXPECT_EQ(coeffs2[i].getIndex(),coeffs[i].getIndex());
// EXPECT_EQ(coeffs2[i].getFactor(),coeffs[i].getFactor());
// }
//
// FilterCoefficient<int> c = FilterCoefficient<int>(0,0);
// for (int i = 0; i < 3; i++) {
// c = filter.getCoeff(i);
// EXPECT_EQ(c.getIndex(),coeffs[i].getIndex());
// EXPECT_EQ(c.getFactor(),coeffs[i].getFactor());
// }
//
// EXPECT_EQ(filter.getNeighborhoodSize(),nSize);
// EXPECT_TRUE(filter.getNeighborhoodSize() != nSize - 1);
// EXPECT_EQ(filter.getNCoeffs(),4);
// EXPECT_TRUE(filter.getNCoeffs() != 5);
//
// EXPECT_EQ(filter.findCoeff(-1),0);
// EXPECT_EQ(filter.findCoeff(1),2);
// EXPECT_EQ(filter.findCoeff(2),-1);
//
// filter.addCoeff(2,-4);
// EXPECT_EQ(filter.getCoeff(filter.findCoeff(2)).getIndex(), 2);
// EXPECT_EQ(filter.getCoeff(filter.findCoeff(2)).getFactor(), -4);
// EXPECT_EQ(filter.getNCoeffs(),5);
//
// filter.eraseCoeff(1);
// EXPECT_EQ(filter.findCoeff(1),-1);
// EXPECT_EQ(filter.getNCoeffs(),4);
// filter.eraseCoeff(6);
// EXPECT_EQ(filter.getNCoeffs(),4);
//
}

TEST(Filter, DoubleFilter) {
//
// int inds[4] = {-1,0,1,3};
// double vals[4] = {2.2,0,-1.1,16.16};
// int nSize = 6;
// vector<FilterCoefficient<double> > coeffs;
// for (int i = 0; i < 4; i++) {
// coeffs.push_back(FilterCoefficient<double>(inds[i],vals[i]));
// }
// DoubleFilter filter = DoubleFilter(coeffs,nSize);
//
// // getters
// vector<FilterCoefficient<double> > coeffs2;
// coeffs2 = filter.getCoeffs();
// for (int i = 0; i < 3; i++) {
// EXPECT_EQ(coeffs2[i].getIndex(),coeffs[i].getIndex());
// EXPECT_NEAR(coeffs2[i].getFactor(),coeffs[i].getFactor(), EPSILONT);
// }
//
// FilterCoefficient<double> c = FilterCoefficient<double>(0,0.0);
// for (int i = 0; i < 3; i++) {
// c = filter.getCoeff(i);
// EXPECT_EQ(c.getIndex(),coeffs[i].getIndex());
// EXPECT_NEAR(c.getFactor(),coeffs[i].getFactor(), EPSILONT);
// }
//
// EXPECT_EQ(filter.getNeighborhoodSize(),nSize);
// EXPECT_TRUE(filter.getNeighborhoodSize() != nSize - 1);
// EXPECT_EQ(filter.getNCoeffs(),4);
// EXPECT_TRUE(filter.getNCoeffs() != 5);
//
// EXPECT_EQ(filter.findCoeff(-1),0);
// EXPECT_EQ(filter.findCoeff(1),2);
// EXPECT_EQ(filter.findCoeff(2),-1);
//
// filter.addCoeff(2,-4.5);
// EXPECT_EQ(filter.getCoeff(filter.findCoeff(2)).getIndex(), 2);
// EXPECT_NEAR(filter.getCoeff(filter.findCoeff(2)).getFactor(),-4.5, EPSILONT);
// EXPECT_EQ(filter.getNCoeffs(),5);
//
// filter.eraseCoeff(1);
// EXPECT_EQ(filter.findCoeff(1),-1);
// EXPECT_EQ(filter.getNCoeffs(),4);
// filter.eraseCoeff(6);
// EXPECT_EQ(filter.getNCoeffs(),4);
//
}

#endif