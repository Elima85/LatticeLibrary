#ifndef TEST_H
#define TEST_H

#define EPSILONT 0.000001 // tolerance for testing

#define BOOST_TEST_MODULE dist_test

#include "priorityqueue.h"
#include "neighbor.h"
#include "defs.h"
#include "cimage.h"
#include "cimageCC.h"
#include "cimageBCC.h"
#include "cimageFCC.h"
#include "exception.h"
#include "norm.h"
//#include "filter.h"
#include "label.h"
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <vector>

using namespace CImage;

int add(int i, int j){
 return i + j;
 }

BOOST_AUTO_TEST_CASE(universeInOrder){
BOOST_CHECK(add(2, 2) == 4);
}

BOOST_AUTO_TEST_SUITE(Priorityqueue_test)

BOOST_AUTO_TEST_CASE(PriorityQueueTest) {

	double values1[] = {1.1,2.2,3.3};
	double values2[] = {4.4,5.5,6.6};
    vector<double> vector1(values1,values1 + 3);
	vector<double> vector2(values2,values2 + 3);
	PNorm *norm1 = new PNorm(1);
	PNorm *norm2 = new PNorm(2);
	priority_queue<PriorityQueueElement<double>, vector<PriorityQueueElement<double> >, PriorityQueueElementComparison> queue;
	PriorityQueueElement<double> singleElement1(0,1);
	PriorityQueueElement<double> singleElement2(1,2);
	PriorityQueueElement<double> singleElement3(1,2);
	PriorityQueueElement<double> doubleElement1(0,2-1.1);
	PriorityQueueElement<double> doubleElement2(1,4.1-3);
	PriorityQueueElement<double> doubleElement3(1,4.1-3);
	PriorityQueueElement<double> vectorElement1(0,vector1,norm1);
	PriorityQueueElement<double> vectorElement2(1,vector2,norm1);
	PriorityQueueElement<double> vectorElement3(1,vector2,norm1);
	PriorityQueueElement<double> vectorElement4(1,vector2,norm2);

	// == operator
	BOOST_CHECK(!(singleElement1 == singleElement2));
	BOOST_CHECK(singleElement2 == singleElement2);
	BOOST_CHECK(singleElement2 == singleElement3);
	BOOST_CHECK(!(doubleElement1 == doubleElement2));
	BOOST_CHECK(doubleElement2 == doubleElement2);
	BOOST_CHECK(doubleElement2 == doubleElement3);
	BOOST_CHECK(!(vectorElement1 == vectorElement2));
	BOOST_CHECK(vectorElement2 == vectorElement2);
	BOOST_CHECK(vectorElement2 == vectorElement3);
	BOOST_CHECK(!(vectorElement2 == vectorElement4));

	// != operator
	BOOST_CHECK(singleElement1 != singleElement2);
	BOOST_CHECK(!(singleElement2 != singleElement2));
	BOOST_CHECK(!(singleElement2 != singleElement3));
	BOOST_CHECK(doubleElement1 != doubleElement2);
	BOOST_CHECK(!(doubleElement2 != doubleElement2));
	BOOST_CHECK(!(doubleElement2 != doubleElement3));
	BOOST_CHECK(vectorElement1 != vectorElement2);
	BOOST_CHECK(!(vectorElement2 != vectorElement2));
	BOOST_CHECK(!(vectorElement2 != vectorElement3));
	BOOST_CHECK(vectorElement2 != vectorElement4);

	// pop order
	queue.push(singleElement1);
	queue.push(singleElement2);
	PriorityQueueElement<double> e1 = queue.top();
	BOOST_CHECK(e1 == singleElement1);
	queue.pop();
	queue.pop();
	queue.push(singleElement2);
	queue.push(singleElement1);
	e1 = queue.top();
	BOOST_CHECK(e1 == singleElement1);
	queue.pop();
	queue.pop();

	queue.push(doubleElement1);
	queue.push(doubleElement2);
	e1 = queue.top();
	BOOST_CHECK(e1 == doubleElement1);
	queue.pop();
	queue.pop();
	queue.push(doubleElement2);
	queue.push(doubleElement1);
	e1 = queue.top();
	BOOST_CHECK(e1 == doubleElement1);
	queue.pop();
	queue.pop();

	queue.push(vectorElement1);
	queue.push(vectorElement2);
	e1 = queue.top();
	BOOST_CHECK(e1 == vectorElement1);
	queue.pop();
	queue.pop();
	queue.push(vectorElement2);
	queue.push(vectorElement1);
	e1 = queue.top();
	BOOST_CHECK(e1 == vectorElement1);
	queue.pop();
	queue.pop();


}

BOOST_AUTO_TEST_CASE(Pq1Test) {

	Pq1 q;
	Pq1Elem elem1 = Pq1Elem(0, 1);
	Pq1Elem elem2 = Pq1Elem(1, 2);
	Pq1Elem elem3 = Pq1Elem(1, 2);

	// == operator
	BOOST_CHECK(!(elem1 == elem2));
	BOOST_CHECK(elem2 == elem3);

	// != operator
	BOOST_CHECK(elem1 != elem2);
	BOOST_CHECK(!(elem2 != elem3));

	// pop order
	q.push(elem1);
	q.push(elem2);
	Pq1Elem e1 = q.top();
	BOOST_CHECK(e1 == elem1);
	q.pop();
	q.pop();

	q.push(elem2);
	q.push(elem1);
	e1 = q.top();
	BOOST_CHECK(e1 == elem1);
	q.pop();
	q.pop();
}

BOOST_AUTO_TEST_CASE(Pq2Test) {

	Pq2 q;
	Pq2Elem elem1 = Pq2Elem(0, 1, 2);
	Pq2Elem elem2 = Pq2Elem(1, 3, 4);
	Pq2Elem elem3 = Pq2Elem(1, 3, 4);

	// == operator
	BOOST_CHECK(!(elem1 == elem2));
	BOOST_CHECK(elem2 == elem3);

	// != operator
	BOOST_CHECK(elem1 != elem2);
	BOOST_CHECK(!(elem2 != elem3));

	// pop order
	q.push(elem1);
	q.push(elem2);
	Pq2Elem e1 = q.top();
	BOOST_CHECK(e1 == elem1);
	q.pop();
	q.pop();

	q.push(elem2);
	q.push(elem1);
	e1 = q.top();
	BOOST_CHECK(e1 == elem1);
	q.pop();
	q.pop();
}

BOOST_AUTO_TEST_CASE(PqVTest) {

	PqV q;
	PqVElem elem1 = PqVElem(0, 1, 1, 1);
	PqVElem elem2 = PqVElem(1, 2, 2, 2);
	PqVElem elem3 = PqVElem(1, 2, 2, 2);

	// == operator
	BOOST_CHECK(!(elem1 == elem2));
	BOOST_CHECK(elem2 == elem2);
	BOOST_CHECK(elem2 == elem3);

	// != operator
	BOOST_CHECK(elem1 != elem2);
	BOOST_CHECK(!(elem2 != elem2));
	BOOST_CHECK(!(elem2 != elem3));

	// pop order
	q.push(elem1);
	q.push(elem2);
	PqVElem e1 = q.top();
	BOOST_CHECK(e1 == elem1);
	q.pop();
	q.pop();

	q.push(elem2);
	q.push(elem1);
	e1 = q.top();
	BOOST_CHECK(e1 == elem1);
	q.pop();
	q.pop();
}

BOOST_AUTO_TEST_CASE(Pq2VTest) {

	double minVals1[] = {-1.1,0.5,-0.1,-0.6,0.9};
	double minVals2[] = {-2.1,1.5,-1.1,-1.6,1.9};
	double maxVals1[] = {-0.9,2.4,5.2,8.2,3.1};
	double maxVals2[] = {0.9,3.2,8.6,4.3,5.1};
	vector<double> minVec1, minVec2, maxVec1, maxVec2, shortVec;
	minVec1.assign(minVals1, minVals1+5);
	minVec2.assign(minVals2, minVals2+5);
	maxVec1.assign(maxVals1, maxVals1+5);
	maxVec2.assign(maxVals2, maxVals2+5);
	shortVec.assign(minVals1, minVals1+4);

	PNorm* norm1 = new PNorm(1);
	PNorm* norm2 = new PNorm(2);

//	Pq2V q;
	priority_queue<Pq2VElem<double>, vector< Pq2VElem<double> >, Pq2VComp> q;
	Pq2VElem<double> elem1 = Pq2VElem<double>(0,maxVec1,minVec1,norm1);
	Pq2VElem<double> elem2 = Pq2VElem<double>(1,maxVec2,minVec2,norm1);
	Pq2VElem<double> elem3 = Pq2VElem<double>(2,maxVec2,minVec2,norm1);
	Pq2VElem<double> elem4 = Pq2VElem<double>(3,maxVec1,minVec1,norm2);
	Pq2VElem<double> dummyElement;

	// constructor and getters
	BOOST_CHECK_THROW(Pq2VElem<double>(4,maxVec1,shortVec,norm1),dimensionMismatchException);
	BOOST_CHECK_EQUAL(elem1.getIndex(),0);
	BOOST_CHECK(elem1.getIndex() != 1);
	BOOST_CHECK_EQUAL(elem4.getIndex(),3);
	BOOST_CHECK(elem4.getIndex() != 2);
	vector<double> min1 = elem1.getMinVector();
	vector<double> max1 = elem1.getMaxVector();
	vector<double> min2 = elem2.getMinVector();
	vector<double> max2 = elem2.getMaxVector();
	for (int i = 0; i < 5; i++) {
		BOOST_CHECK_CLOSE_FRACTION(min1[i], minVals1[i],EPSILONT);
		BOOST_CHECK_CLOSE_FRACTION(max1[i], maxVals1[i],EPSILONT);
		BOOST_CHECK_CLOSE_FRACTION(min2[i], minVals2[i],EPSILONT);
		BOOST_CHECK_CLOSE_FRACTION(max2[i], maxVals2[i],EPSILONT);
		BOOST_CHECK(fabs(min1[i] - minVals2[i]) > EPSILONT);
		BOOST_CHECK(fabs(max1[i] - maxVals2[i]) > EPSILONT);
		BOOST_CHECK(fabs(min2[i] - minVals1[i]) > EPSILONT);
		BOOST_CHECK(fabs(max2[i] - maxVals1[i]) > EPSILONT);
	}

	// norm
	BOOST_CHECK_CLOSE_FRACTION(elem1.computeNorm(elem1.getMinVector()), norm1->compute(minVec1), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(elem4.computeNorm(elem4.getMinVector()), norm2->compute(minVec1), EPSILONT);
	BOOST_CHECK(fabs(elem1.computeNorm(elem1.getMinVector()) - norm2->compute(minVec1)) > EPSILONT);

	// == operator
	BOOST_CHECK(elem1 == elem1);
	BOOST_CHECK(elem2 == elem3);
	BOOST_CHECK(!(elem1 == elem4));
	BOOST_CHECK(!(elem1 == elem2));

	// != operator
	BOOST_CHECK(!(elem1 != elem1));
	BOOST_CHECK(!(elem2 != elem3));
	BOOST_CHECK(elem1 != elem4);
	BOOST_CHECK(elem1 != elem2);

	// pop order
	q.push(elem1);
	q.push(elem2);
	Pq2VElem<double> e1 = q.top();
	BOOST_CHECK(e1 == elem1);
	q.pop();
	q.pop();

	q.push(elem2);
	q.push(elem1);
	e1 = q.top();
	BOOST_CHECK(e1 == elem1);
	q.pop();
	q.pop();

	// exceptions
	BOOST_CHECK_THROW(dummyElement.computeNorm(vector<double>(2,3)),notInitializedException);

	delete norm1;
	delete norm2;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Neighbor_test)

BOOST_AUTO_TEST_CASE(NeighborTest) {

	int location1 = 0;
	int location2 = 1;
	int index1 = 1;
	int index2 = 2;
	//double distance1 = 0.1;
	//double distance2 = 0.2;

	Neighbor n1 = Neighbor(location1, index1); //, distance1);
	Neighbor n2 = Neighbor(location2, index2); //, distance2);

	// constructor and getters
	BOOST_CHECK(n1.getLocation() == location1);
	BOOST_CHECK(n1.getIndex() == index1);
	//BOOST_CHECK(n1.getDistance() == distance1);
	BOOST_CHECK(n1.getLocation() != location2);
	BOOST_CHECK(n1.getIndex() != index2);
	//BOOST_CHECK(n1.getDistance() != distance2);

	BOOST_CHECK(n2.getLocation() == location2);
	BOOST_CHECK(n2.getIndex() == index2);
	//BOOST_CHECK(n2.getDistance() == distance2);
	BOOST_CHECK(n2.getLocation() != location1);
	BOOST_CHECK(n2.getIndex() != index1);
	//BOOST_CHECK(n2.getDistance() != distance1);

	// setter
//	n1.set(index2, distance2);
//	BOOST_CHECK(n1.getIndex() == index2);
//	BOOST_CHECK(n1.getDistance() == distance2);
//	BOOST_CHECK(n1.getIndex() != index1);
//	BOOST_CHECK(n1.getDistance() != distance1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Norm_test)

BOOST_AUTO_TEST_CASE(PNormTest) {
	int intVals[] = {0,1,2,3,4,5};
	vector<int> intVector;
	intVector.assign(intVals, intVals + 6);

	double doubleVals[] = {0.0,1.1,2.2,3.3,4.4};
	vector<double> doubleVector;
	doubleVector.assign(doubleVals, doubleVals + 5);

	vector<double> zeroVector;
	zeroVector.assign(3,0.0);

	PNorm norm1(1);
	PNorm norm2(2);
	PNorm norm5(5);
	PNorm norm1Copy(&norm1);
	PNorm norm5Copy(&norm5);

	// constructor and getter
	BOOST_CHECK_EQUAL(norm1.getP(),1);
	BOOST_CHECK_EQUAL(norm2.getP(),2);
	BOOST_CHECK_EQUAL(norm5.getP(),5);
	BOOST_CHECK(norm1.getP() != 2);
	BOOST_CHECK(norm2.getP() != 3);
	BOOST_CHECK(norm5.getP() != 1);
	BOOST_CHECK_EQUAL(norm1Copy.getP(),1);
	BOOST_CHECK_EQUAL(norm5Copy.getP(),5);
	BOOST_CHECK(norm1Copy.getP() != 2);
	BOOST_CHECK(norm5Copy.getP() != 1);

	// compute
	BOOST_CHECK_CLOSE_FRACTION(norm1.compute(zeroVector),0.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm1.compute(intVector),15.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm1.compute(doubleVector),11.0,EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(norm2.compute(zeroVector),0.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm2.compute(intVector),7.4161984871,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm2.compute(doubleVector),6.02494813256,EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(norm5.compute(zeroVector),0.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm5.compute(intVector),5.36022049567,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm5.compute(doubleVector),4.61510254893,EPSILONT);
}

BOOST_AUTO_TEST_CASE(ProductNormTest) {
	int intVals[] = {0,1,2,3,4,5};
	vector<int> intVector1, intVector2;
	intVector1.assign(intVals, intVals + 6);
	intVector2.assign(intVals + 1, intVals + 6);

	double doubleVals[] = {0.0,1.1,2.2,3.3,4.4};
	vector<double> doubleVector1, doubleVector2;
	doubleVector1.assign(doubleVals, doubleVals + 5);
	doubleVector2.assign(doubleVals + 1, doubleVals + 5);

	vector<double> zeroVector;
	zeroVector.assign(3,0.0);

	ProductNorm norm;
	ProductNorm normCopy(&norm);

	// compute
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(zeroVector),0.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(intVector1),0.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(intVector2),120.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(doubleVector1),0.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(doubleVector2),35.1384,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(intVector1),normCopy.compute(intVector1),EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(doubleVector1),normCopy.compute(doubleVector1),EPSILONT);

}

BOOST_AUTO_TEST_CASE(MaximumNormTest) {

	int intVals[] = {0,1,4,5,2,3};
	vector<int> intVector;
	intVector.assign(intVals, intVals + 6);

	double doubleVals[] = {0.0,3.3,4.4,1.1,2.2};
	vector<double> doubleVector;
	doubleVector.assign(doubleVals, doubleVals + 5);

	vector<double> zeroVector;
	zeroVector.assign(3,0.0);

	MaximumNorm norm;
	MaximumNorm normCopy(&norm);

	// compute
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(zeroVector),0.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(intVector),5.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(doubleVector),4.4,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(intVector),normCopy.compute(intVector),EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(norm.compute(doubleVector),normCopy.compute(doubleVector),EPSILONT);

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(files_test)

BOOST_AUTO_TEST_CASE(readTest) {
	int nR = 2, nC = 3, nL = 4, nB = 5;
	int nTot = nR*nC*nL;
	char filename[] = "testimage2345.bin";
	char* filenamepointer = filename;
	double* fromFile = readVolume(filenamepointer, nTot*nB);
	double referenceData[] = 	{1,2,3,4,5,6,2,3,4,5,6,1,3,4,5,6,1,2,4,5,6,1,2,3,
								11,12,13,14,15,16,12,13,14,15,16,11,13,14,15,16,11,12,14,15,16,11,12,13,
								21,22,23,24,25,26,22,23,24,25,26,21,23,24,25,26,21,22,24,25,26,21,22,23,
								31,32,33,34,35,36,32,33,34,35,36,31,33,34,35,36,31,32,34,35,36,31,32,33,
								41,42,43,44,45,46,42,43,44,45,46,41,43,44,45,46,41,42,44,45,46,41,42,43};
	for (int i = 0; i < nTot*nB; i++) {
		BOOST_CHECK_CLOSE_FRACTION(fromFile[i],referenceData[i],EPSILONT);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Filter_test)

BOOST_AUTO_TEST_CASE(FilterCoefficientTest) {
// // constructor
// int ind[3] = {0,1,2};
// int ci[3] = {-1,0,2};
// double cd[3] = {-1.1,0.0,2.2};
// bool cb[3] = {false,true,false};
//
// FilterCoefficient<bool> fcbempty;
// FilterCoefficient<int> fciempty;
// FilterCoefficient<double> fcdempty;
// BOOST_CHECK_EQUAL(fcbempty.getIndex(),0);
// BOOST_CHECK_EQUAL(fciempty.getIndex(),0);
// BOOST_CHECK_EQUAL(fcdempty.getIndex(),0);
// BOOST_CHECK_EQUAL(fcbempty.getFactor(),false);
// BOOST_CHECK_EQUAL(fciempty.getFactor(),0);
// BOOST_CHECK_CLOSE_FRACTION(fcdempty.getFactor(),0.0,EPSILONT);
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
// BOOST_CHECK_EQUAL(fcb[i].getIndex(), ind[i]);
// BOOST_CHECK_EQUAL(fci[i].getIndex(), ind[i]);
// BOOST_CHECK_EQUAL(fcd[i].getIndex(), ind[i]);
//
// BOOST_CHECK_EQUAL(fcb[i].getFactor(), cb[i]);
// BOOST_CHECK_EQUAL(fci[i].getFactor(), ci[i]);
// BOOST_CHECK_CLOSE_FRACTION(fcd[i].getFactor(), cd[i],EPSILONT);
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
// BOOST_CHECK(fcb[i].getIndex() != ind[i]);
// BOOST_CHECK(fci[i].getIndex() != ind[i]);
// BOOST_CHECK(fcd[i].getIndex() != ind[i]);
// BOOST_CHECK_EQUAL(fcb[i].getIndex(), ind2[i]);
// BOOST_CHECK_EQUAL(fci[i].getIndex(), ind2[i]);
// BOOST_CHECK_EQUAL(fcd[i].getIndex(), ind2[i]);
//
// BOOST_CHECK_EQUAL(fcb[i].getFactor(), cb2[i]);
// BOOST_CHECK_EQUAL(fci[i].getFactor(), ci2[i]);
// BOOST_CHECK_CLOSE_FRACTION(fcd[i].getFactor(), cd2[i],EPSILONT);
// BOOST_CHECK(fcb[i].getFactor() != cb[i]);
// BOOST_CHECK(fci[i].getFactor() != ci[i]);
// BOOST_CHECK(fabs(fcd[i].getFactor() - cd[i]) > EPSILONT);
// }
//
// for (int i = 0; i < 3; i++) {
// fcb[i].set(ind[i],cb[i]);
// fci[i].set(ind[i],ci[i]);
// fcd[i].set(ind[i],cd[i]);
// }
// for (int i = 0; i < 3; i++) {
// BOOST_CHECK_EQUAL(fcb[i].getIndex(), ind[i]);
// BOOST_CHECK_EQUAL(fci[i].getIndex(), ind[i]);
// BOOST_CHECK_EQUAL(fcd[i].getIndex(), ind[i]);
//
// BOOST_CHECK_EQUAL(fcb[i].getFactor(), cb[i]);
// BOOST_CHECK_EQUAL(fci[i].getFactor(), ci[i]);
// BOOST_CHECK_CLOSE_FRACTION(fcd[i].getFactor(), cd[i],EPSILONT);
// }
// }
//
// BOOST_AUTO_TEST_CASE(StructuringElementTest) {
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
// BOOST_CHECK_EQUAL(coeffs2[i].getIndex(),coeffs[i].getIndex());
// BOOST_CHECK_EQUAL(coeffs2[i].getFactor(),coeffs[i].getFactor());
// }
//
// FilterCoefficient<bool> c = FilterCoefficient<bool>(0,false);
// for (int i = 0; i < 3; i++) {
// c = se.getCoeff(i);
// BOOST_CHECK_EQUAL(c.getIndex(),coeffs[i].getIndex());
// BOOST_CHECK_EQUAL(c.getFactor(),coeffs[i].getFactor());
// }
//
// BOOST_CHECK_EQUAL(se.getNeighborhoodSize(),nSize);
// BOOST_CHECK(se.getNeighborhoodSize() != nSize - 1);
// BOOST_CHECK_EQUAL(se.getNCoeffs(),4);
// BOOST_CHECK(se.getNCoeffs() != 5);
//
// BOOST_CHECK_EQUAL(se.findCoeff(-1),0);
// BOOST_CHECK_EQUAL(se.findCoeff(1),2);
// BOOST_CHECK_EQUAL(se.findCoeff(2),-1);
//
// se.addCoeff(2,true);
// BOOST_CHECK_EQUAL(se.getCoeff(se.findCoeff(2)).getIndex(), 2);
// BOOST_CHECK_EQUAL(se.getCoeff(se.findCoeff(2)).getFactor(), true);
// BOOST_CHECK_EQUAL(se.getNCoeffs(),5);
//
// se.eraseCoeff(1);
// BOOST_CHECK_EQUAL(se.findCoeff(1),-1);
// BOOST_CHECK_EQUAL(se.getNCoeffs(),4);
// se.eraseCoeff(6);
// BOOST_CHECK_EQUAL(se.getNCoeffs(),4);
//
}

BOOST_AUTO_TEST_CASE(IntFilterTest) {
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
// BOOST_CHECK_EQUAL(coeffs2[i].getIndex(),coeffs[i].getIndex());
// BOOST_CHECK_EQUAL(coeffs2[i].getFactor(),coeffs[i].getFactor());
// }
//
// FilterCoefficient<int> c = FilterCoefficient<int>(0,0);
// for (int i = 0; i < 3; i++) {
// c = filter.getCoeff(i);
// BOOST_CHECK_EQUAL(c.getIndex(),coeffs[i].getIndex());
// BOOST_CHECK_EQUAL(c.getFactor(),coeffs[i].getFactor());
// }
//
// BOOST_CHECK_EQUAL(filter.getNeighborhoodSize(),nSize);
// BOOST_CHECK(filter.getNeighborhoodSize() != nSize - 1);
// BOOST_CHECK_EQUAL(filter.getNCoeffs(),4);
// BOOST_CHECK(filter.getNCoeffs() != 5);
//
// BOOST_CHECK_EQUAL(filter.findCoeff(-1),0);
// BOOST_CHECK_EQUAL(filter.findCoeff(1),2);
// BOOST_CHECK_EQUAL(filter.findCoeff(2),-1);
//
// filter.addCoeff(2,-4);
// BOOST_CHECK_EQUAL(filter.getCoeff(filter.findCoeff(2)).getIndex(), 2);
// BOOST_CHECK_EQUAL(filter.getCoeff(filter.findCoeff(2)).getFactor(), -4);
// BOOST_CHECK_EQUAL(filter.getNCoeffs(),5);
//
// filter.eraseCoeff(1);
// BOOST_CHECK_EQUAL(filter.findCoeff(1),-1);
// BOOST_CHECK_EQUAL(filter.getNCoeffs(),4);
// filter.eraseCoeff(6);
// BOOST_CHECK_EQUAL(filter.getNCoeffs(),4);
//
}

BOOST_AUTO_TEST_CASE(DoubleFilterTest) {
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
// BOOST_CHECK_EQUAL(coeffs2[i].getIndex(),coeffs[i].getIndex());
// BOOST_CHECK_CLOSE_FRACTION(coeffs2[i].getFactor(),coeffs[i].getFactor(),EPSILONT);
// }
//
// FilterCoefficient<double> c = FilterCoefficient<double>(0,0.0);
// for (int i = 0; i < 3; i++) {
// c = filter.getCoeff(i);
// BOOST_CHECK_EQUAL(c.getIndex(),coeffs[i].getIndex());
// BOOST_CHECK_CLOSE_FRACTION(c.getFactor(),coeffs[i].getFactor(),EPSILONT);
// }
//
// BOOST_CHECK_EQUAL(filter.getNeighborhoodSize(),nSize);
// BOOST_CHECK(filter.getNeighborhoodSize() != nSize - 1);
// BOOST_CHECK_EQUAL(filter.getNCoeffs(),4);
// BOOST_CHECK(filter.getNCoeffs() != 5);
//
// BOOST_CHECK_EQUAL(filter.findCoeff(-1),0);
// BOOST_CHECK_EQUAL(filter.findCoeff(1),2);
// BOOST_CHECK_EQUAL(filter.findCoeff(2),-1);
//
// filter.addCoeff(2,-4.5);
// BOOST_CHECK_EQUAL(filter.getCoeff(filter.findCoeff(2)).getIndex(), 2);
// BOOST_CHECK_CLOSE_FRACTION(filter.getCoeff(filter.findCoeff(2)).getFactor(),-4.5,EPSILONT);
// BOOST_CHECK_EQUAL(filter.getNCoeffs(),5);
//
// filter.eraseCoeff(1);
// BOOST_CHECK_EQUAL(filter.findCoeff(1),-1);
// BOOST_CHECK_EQUAL(filter.getNCoeffs(),4);
// filter.eraseCoeff(6);
// BOOST_CHECK_EQUAL(filter.getNCoeffs(),4);
//
}

BOOST_AUTO_TEST_SUITE_END()

/**
 * bool isEven(int)
 * int length() (of vector)
 * int lowerBound(double*,int,double)
 * vector<T> element-wise operators, tested for int and double.
 */
BOOST_AUTO_TEST_SUITE(misc_test)

BOOST_AUTO_TEST_CASE(isEvenTest) {
	BOOST_CHECK(isEven(0));
	BOOST_CHECK(!isEven(1));
	BOOST_CHECK(isEven(2));
	BOOST_CHECK(!isEven(3));
	BOOST_CHECK(isEven(4));
	BOOST_CHECK(!isEven(5));
	BOOST_CHECK(isEven(6));
	BOOST_CHECK(!isEven(7));
	BOOST_CHECK(isEven(8));
	BOOST_CHECK(!isEven(9));
	BOOST_CHECK(isEven(10));
}

BOOST_AUTO_TEST_CASE(lengthTest) {

	double vec[3] = { 1, 0, 0 };

	BOOST_CHECK_CLOSE_FRACTION(length(vec), 1, EPSILONT);
	vec[0] = -1;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 1, EPSILONT);
	vec[0] = 0;
	vec[1] = 1;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 1, EPSILONT);
	vec[1] = -1;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 1, EPSILONT);
	vec[1] = 0;
	vec[2] = 1;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 1, EPSILONT);
	vec[2] = -1;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 1, EPSILONT);

	vec[0] = 1;
	vec[1] = 2;
	vec[2] = 3;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 3.74165738677, EPSILONT);
	vec[0] = 2;
	vec[1] = 3;
	vec[2] = 1;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 3.74165738677, EPSILONT);
	vec[0] = -1;
	vec[1] = 2;
	vec[2] = 3;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 3.74165738677, EPSILONT);
	vec[0] = 1;
	vec[1] = -2;
	vec[2] = 3;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 3.74165738677, EPSILONT);
	vec[0] = 1;
	vec[1] = 2;
	vec[2] = -3;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 3.74165738677, EPSILONT);
	vec[0] = -1;
	vec[1] = -2;
	vec[2] = -3;
	BOOST_CHECK_CLOSE_FRACTION(length(vec), 3.74165738677, EPSILONT);
}

BOOST_AUTO_TEST_CASE(lowerBoundTest) {

	double numbers[10] = { 0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
	int length = 10;

	BOOST_CHECK(lowerBound(numbers, length, 0) == 0);
	BOOST_CHECK(lowerBound(numbers, length, 10) == 9);
	BOOST_CHECK(lowerBound(numbers, length, 5) == 4);
	BOOST_CHECK(lowerBound(numbers, length, 7.7) == 7);

	BOOST_CHECK_THROW(lowerBound(numbers, length, -1), outsideRangeException);
}

BOOST_AUTO_TEST_CASE(vectorTOperatorTest) {

	// T = int
	int intVals[] = {-2,-1,0,3,4};
	int intNegVals[] = {2,1,0,-3,-4};
	int intMinVals[] = {-2,-1,0,-3,-4};
	int intMaxVals[] = {2,1,0,3,4};
	vector<int> intVector1, intVector2, intNegVector;
	intVector1.assign(intVals, intVals + 5);
	intVector2.assign(intVals, intVals + 5);
	intNegVector.assign(intNegVals, intNegVals + 5);
	vector<int> intVector3 = intVector1 + intNegVector;
	vector<int> intVector4 = intVector3 - intVector1;
	vector<int> intVector5(intVals, intVals + 4);
	vector<int> intVector6 = intVector1 - intVector1;
	vector<int> intMinVector(intMinVals, intMinVals + 5);
	vector<int> intMaxVector(intMaxVals, intMaxVals + 5);
	vector<int> intVector7 = minElements(intVector1,intNegVector);
	vector<int> intVector8 = maxElements(intVector1,intNegVector);
	vector<double> multiplicationResult;
	BOOST_CHECK(intVector1 == intVector2);
	BOOST_CHECK(intVector1 != intNegVector);
	BOOST_CHECK(-intVector1 == intNegVector);
	BOOST_CHECK(intVector1 == -intNegVector);
	for (int i = 0; i < 5; i++) {
		BOOST_CHECK_EQUAL(intVector3[i], 0);
		BOOST_CHECK_EQUAL(intVector4[i], intNegVector[i]);
		BOOST_CHECK_EQUAL(intVector6[i], 0);
		BOOST_CHECK_EQUAL(intVector7[i], intMinVector[i]);
		BOOST_CHECK_EQUAL(intVector8[i], intMaxVector[i]);
	}
	multiplicationResult = 0 * intVector1;
	for (int i = 0; i < 5; i++) {
		BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[i],0,EPSILONT);
	}
	multiplicationResult = 1 * intVector1;
	for (int i = 0; i < 5; i++) {
		BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[i],intVals[i],EPSILONT);
	}
	multiplicationResult = -1 * intVector1;
	for (int i = 0; i < 5; i++) {
		BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[i],intNegVals[i],EPSILONT);
	}
	multiplicationResult = 0.5 * intVector1;
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[0],-1,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[1],-0.5,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[2],0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[3],1.5,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[4],2,EPSILONT);
	BOOST_CHECK_THROW(intVector1 + intVector5,dimensionMismatchException);
	BOOST_CHECK_THROW(intVector1 - intVector5,dimensionMismatchException);
	BOOST_CHECK_THROW(minElements(intVector1,intVector5),dimensionMismatchException);
	BOOST_CHECK_THROW(maxElements(intVector1,intVector5),dimensionMismatchException);

	// T = double
	double doubleVals[] = {-2.2,-1.1,0,3.3,4.4};
	double doubleNegVals[] = {2.2,1.1,0,-3.3,-4.4};
	double doubleMinVals[] = {-2.2,-1.1,0,-3.3,-4.4};
	double doubleMaxVals[] = {2.2,1.1,0,3.3,4.4};
	vector<double> doubleVector1, doubleVector2, doubleNegVector;
	doubleVector1.assign(doubleVals, doubleVals + 5);
	doubleVector2.assign(doubleVals, doubleVals + 5);
	doubleNegVector.assign(doubleNegVals, doubleNegVals + 5);
	vector<double> doubleVector3 = doubleVector1 + doubleNegVector;
	vector<double> doubleVector4 = doubleVector3 - doubleVector1;
	vector<double> doubleVector5(doubleVals, doubleVals + 4);
	vector<double> doubleVector6 = doubleVector1 - doubleVector1;
	vector<double> doubleMinVector(doubleMinVals,doubleMinVals + 5);
	vector<double> doubleMaxVector(doubleMaxVals,doubleMaxVals + 5);
	vector<double> doubleVector7 = minElements(doubleVector1,doubleNegVector);
	vector<double> doubleVector8 = maxElements(doubleVector1,doubleNegVector);
	BOOST_CHECK(doubleVector1 == doubleVector2);
	BOOST_CHECK(doubleVector1 != doubleNegVector);
	BOOST_CHECK(-doubleVector1 == doubleNegVector);
	BOOST_CHECK(doubleVector1 == -doubleNegVector);
	for (int i = 0; i < 5; i++) {
		BOOST_CHECK_CLOSE_FRACTION(doubleVector3[i],0,EPSILONT);
		BOOST_CHECK_CLOSE_FRACTION(doubleVector4[i],doubleNegVector[i],EPSILONT);
		BOOST_CHECK_CLOSE_FRACTION(doubleVector6[i],0,EPSILONT);
		BOOST_CHECK_CLOSE_FRACTION(doubleVector7[i],doubleMinVector[i],EPSILONT);
		BOOST_CHECK_CLOSE_FRACTION(doubleVector8[i],doubleMaxVector[i],EPSILONT);
	}
	multiplicationResult = 0 * doubleVector1;
	for (int i = 0; i < 5; i++) {
		BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[i],0,EPSILONT);
	}
	multiplicationResult = 1 * doubleVector1;
	for (int i = 0; i < 5; i++) {
		BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[i],doubleVals[i],EPSILONT);
	}
	multiplicationResult = -1 * doubleVector1;
	for (int i = 0; i < 5; i++) {
		BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[i],doubleNegVals[i],EPSILONT);
	}
	multiplicationResult = 0.5 * doubleVector1;
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[0],-1.1,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[1],-0.55,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[2],0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[3],1.65,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(multiplicationResult[4],2.2,EPSILONT);

	BOOST_CHECK_THROW(doubleVector1 + doubleVector5, dimensionMismatchException);
	BOOST_CHECK_THROW(doubleVector1 - doubleVector5, dimensionMismatchException);
	BOOST_CHECK_THROW(minElements(doubleVector1,doubleVector5),dimensionMismatchException);
	BOOST_CHECK_THROW(maxElements(doubleVector1,doubleVector5),dimensionMismatchException);

}

BOOST_AUTO_TEST_SUITE_END()

/**
 * Tests type CImagetypeCC aka CImageCC<uint8>.
 */
BOOST_AUTO_TEST_SUITE(CImagetypeCC_test)

BOOST_AUTO_TEST_CASE(constructorTest) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = i;
	}

	// constructor
	CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);
	BOOST_CHECK(imCC);

	// getters
	uint8* imdata = imCC->getData();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < nB; j++) {
			BOOST_CHECK(imdata[i] == data[i]);
		}
	}

	BOOST_CHECK(imCC->getNElements() == N);
	BOOST_CHECK(imCC->getNElements() != N + 1);

	BOOST_CHECK(imCC->getNColumns() == nC);
	BOOST_CHECK(imCC->getNColumns() != nC + 1);

	BOOST_CHECK(imCC->getNRows() == nR);
	BOOST_CHECK(imCC->getNRows() != nR + 1);

	BOOST_CHECK(imCC->getNLayers() == nL);
	BOOST_CHECK(imCC->getNLayers() != nL + 1);

	BOOST_CHECK(imCC->getNBands() == nB);
	BOOST_CHECK(imCC->getNBands() != nB + 1);

	// validity of elements
	BOOST_CHECK(!imCC->isValid(-1));
	BOOST_CHECK(imCC->isValid(0));
	BOOST_CHECK(imCC->isValid(N - 1));
	BOOST_CHECK(!imCC->isValid(N));

	BOOST_CHECK(!imCC->isValid(0, -1));
	BOOST_CHECK(!imCC->isValid(N - 1, -1));
	BOOST_CHECK(!imCC->isValid(-1, 0));
	BOOST_CHECK(imCC->isValid(0, 0));
	BOOST_CHECK(imCC->isValid(N - 1, 0));
	BOOST_CHECK(!imCC->isValid(N, 0));
	BOOST_CHECK(imCC->isValid(0, nB - 1));
	BOOST_CHECK(imCC->isValid(N - 1, nB - 1));
	BOOST_CHECK(!imCC->isValid(0, nB));
	BOOST_CHECK(!imCC->isValid(N - 1, nB));

	BOOST_CHECK(!imCC->isValid(-1, 0, 0));
	BOOST_CHECK(!imCC->isValid(0, -1, 0));
	BOOST_CHECK(!imCC->isValid(0, 0, -1));
	BOOST_CHECK(imCC->isValid(0, 0, 0));
	BOOST_CHECK(imCC->isValid(nR - 1, 0, 0));
	BOOST_CHECK(imCC->isValid(0, nC - 1, 0));
	BOOST_CHECK(imCC->isValid(0, 0, nL - 1));
	BOOST_CHECK(!imCC->isValid(nR, 0, 0));
	BOOST_CHECK(!imCC->isValid(0, nC, 0));
	BOOST_CHECK(!imCC->isValid(0, 0, nL));

	BOOST_CHECK(!imCC->isValid(0, 0, 0, -1));
	BOOST_CHECK(!imCC->isValid(nR - 1, 0, 0, -1));
	BOOST_CHECK(!imCC->isValid(0, nC - 1, 0, -1));
	BOOST_CHECK(!imCC->isValid(0, 0, nL - 1, -1));
	BOOST_CHECK(!imCC->isValid(0, 0, 0, nB));
	BOOST_CHECK(!imCC->isValid(nR - 1, 0, 0, nB));
	BOOST_CHECK(!imCC->isValid(0, nC - 1, 0, nB));
	BOOST_CHECK(!imCC->isValid(0, 0, nL - 1, nB));
	BOOST_CHECK(imCC->isValid(0, 0, 0, nB - 1));
	BOOST_CHECK(imCC->isValid(nR - 1, 0, 0, nB - 1));
	BOOST_CHECK(imCC->isValid(0, nC - 1, 0, nB - 1));
	BOOST_CHECK(imCC->isValid(0, 0, nL - 1, nB - 1));

	// index conversion
	BOOST_CHECK(imCC->rclToIndex(0, 0, 0) == 0);
	BOOST_CHECK(imCC->rclToIndex(1, 2, 3) == 98);
	BOOST_CHECK(imCC->rclToIndex(nR - 1, nC - 1, nL - 1) == N - 1);

	BOOST_CHECK(imCC->indexToR(0) == 0);
	BOOST_CHECK(imCC->indexToC(0) == 0);
	BOOST_CHECK(imCC->indexToL(0) == 0);
	BOOST_CHECK(imCC->indexToR(98) == 1);
	BOOST_CHECK(imCC->indexToC(98) == 2);
	BOOST_CHECK(imCC->indexToL(98) == 3);
	BOOST_CHECK(imCC->indexToR(N - 1) == nR - 1);
	BOOST_CHECK(imCC->indexToC(N - 1) == nC - 1);
	BOOST_CHECK(imCC->indexToL(N - 1) == nL - 1);

	delete imCC;
}

BOOST_AUTO_TEST_CASE(coordinateTest) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = 0;
	}
	CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);
	double volume = 2.5;
	double factor = cbrt(volume);
	CImagetypeCC *imCC2 = new CImagetypeCC(data, nR, nC, nL, nB, volume);

	CImagetypeCC *imCC1C1L = new CImagetypeCC(data, N, 1, 1, 1);
	CImagetypeCC *imCC1R1L = new CImagetypeCC(data, 1, N, 1, 1);
	CImagetypeCC *imCC1R1C = new CImagetypeCC(data, 1, 1, N, 1);
	int n1 = 15, n2 = 14;
	CImagetypeCC *imCCRC = new CImagetypeCC(data, n1, n2, 1, 1);
	CImagetypeCC *imCCRL = new CImagetypeCC(data, n1, 1, n2, 1);
	CImagetypeCC *imCCCL = new CImagetypeCC(data, 1, n1, n2, 1);
	vector<double> coordinates;

	// spel coordinates
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToX(0), 0.5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToY(0), 0.5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToZ(0), 0.5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToX(170), 0.5 + 2, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToY(170), 0.5 + 3, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToZ(170), 0.5 + 5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToX(209), 0.5 + 5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToY(209), 0.5 + 4, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToZ(209), 0.5 + 6, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToX(N - 1), 0.5 + nC - 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToY(N - 1), 0.5 + nR - 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->indexToZ(N - 1), 0.5 + nL - 1, EPSILONT);

	imCC->getCoordinates(0,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], 0.5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], 0.5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], 0.5, EPSILONT);
	imCC->getCoordinates(170,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], 0.5 + 2, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], 0.5 + 3, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], 0.5 + 5, EPSILONT);
	imCC->getCoordinates(209,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], 0.5 + 5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], 0.5 + 4, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], 0.5 + 6, EPSILONT);
	imCC->getCoordinates(N - 1,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], 0.5 + nC - 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], 0.5 + nR - 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], 0.5 + nL - 1, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToX(0), 0.5 * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToY(0), 0.5 * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToZ(0), 0.5 * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToX(170), (0.5 + 2) * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToY(170), (0.5 + 3) * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToZ(170), (0.5 + 5) * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToX(209), (0.5 + 5) * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToY(209), (0.5 + 4) * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToZ(209), (0.5 + 6) * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToX(N - 1), (0.5 + (nC - 1)) * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToY(N - 1), (0.5 + (nR - 1)) * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->indexToZ(N - 1), (0.5 + (nL - 1)) * factor, EPSILONT);

	BOOST_CHECK(imCC2->indexToX(170) - imCC->indexToX(170) > EPSILONT);
	BOOST_CHECK(imCC2->indexToY(170) - imCC->indexToY(170) > EPSILONT);
	BOOST_CHECK(imCC2->indexToZ(170) - imCC->indexToZ(170) > EPSILONT);
	BOOST_CHECK(imCC2->indexToX(209) - imCC->indexToX(209) > EPSILONT);
	BOOST_CHECK(imCC2->indexToY(209) - imCC->indexToY(209) > EPSILONT);
	BOOST_CHECK(imCC2->indexToZ(209) - imCC->indexToZ(209) > EPSILONT);
	BOOST_CHECK(imCC2->indexToX(N - 1) - imCC->indexToX(N - 1) > EPSILONT);
	BOOST_CHECK(imCC2->indexToY(N - 1) - imCC->indexToY(N - 1) > EPSILONT);
	BOOST_CHECK(imCC2->indexToZ(N - 1) - imCC->indexToZ(N - 1) > EPSILONT);

	// width, height and depth
	BOOST_CHECK_CLOSE_FRACTION(imCC->getWidth(), 6, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->getHeight(), 5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->getDepth(), 7, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->getWidth(), factor * 6, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->getHeight(), factor * 5, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->getDepth(), factor * 7, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC1C1L->getWidth(), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC1C1L->getHeight(), N, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC1C1L->getDepth(), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC1R1L->getWidth(), N, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC1R1L->getHeight(), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC1R1L->getDepth(), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC1R1C->getWidth(), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC1R1C->getHeight(), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC1R1C->getDepth(), N, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imCCRC->getWidth(), n2, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCRC->getHeight(), n1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCRC->getDepth(), 1, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imCCRL->getWidth(), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCRL->getHeight(), n1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCRL->getDepth(), n2, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imCCCL->getWidth(), n1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCCL->getHeight(), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCCL->getDepth(), n2, EPSILONT);

	delete imCC;
	delete imCC2;
	delete imCC1C1L;
	delete imCC1R1L;
	delete imCC1R1C;
	delete imCCCL;
	delete imCCRL;
	delete imCCRC;
}

BOOST_AUTO_TEST_CASE(distanceTest) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = 0;
	}
	CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);
	double volume = 2.5;
	double factor = cbrt(volume);
	CImagetypeCC *imCC2 = new CImagetypeCC(data, nR, nC, nL, nB, volume);

	// distance between spels
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(0, 0), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(170, 170), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 104), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 104), imCC->euclideanDistance(104, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 97), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 97), imCC->euclideanDistance(97, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 73), 1, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 73), imCC->euclideanDistance(73, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 110), 1.41421356237, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 110), imCC->euclideanDistance(110, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 98), 1.41421356237, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 98), imCC->euclideanDistance(98, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 67), 1.41421356237, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 67), imCC->euclideanDistance(67, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 79), 1.41421356237, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC->euclideanDistance(103, 79), imCC->euclideanDistance(79, 103), EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(0, 0), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(170, 170), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 104), 1 * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 104), imCC2->euclideanDistance(104, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 97), 1 * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 97), imCC2->euclideanDistance(97, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 73), 1 * factor, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 73), imCC2->euclideanDistance(73, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 110), sqrt(factor * factor * 2), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 110), imCC2->euclideanDistance(110, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 98), sqrt(factor * factor * 2), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 98), imCC2->euclideanDistance(98, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 67), sqrt(factor * factor * 2), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 67), imCC2->euclideanDistance(67, 103), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 79), sqrt(factor * factor * 2), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCC2->euclideanDistance(103, 79), imCC2->euclideanDistance(79, 103), EPSILONT);

	vector<double> dv;
	double xyz100[3] = { 1, 0, 0 };
	double xyz010[3] = { 0, 1, 0 };
	double xyz001[3] = { 0, 0, 1 };
	double xyz123[3] = { 1, 2, 3 };
	imCC->euclideanDistanceVector(103, 103, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK(fabs(dv[i]) < EPSILONT);
	}
	imCC->euclideanDistanceVector(103, 104, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], xyz100[i], EPSILONT);
	}
	imCC->euclideanDistanceVector(103, 109, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], xyz010[i], EPSILONT);
	}
	imCC->euclideanDistanceVector(73, 103, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], xyz001[i], EPSILONT);
	}
	imCC->euclideanDistanceVector(13, 116, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], xyz123[i], EPSILONT);
	}

	double xyz2100[3] = { 1 * factor, 0, 0 };
	double xyz2010[3] = { 0, 1 * factor, 0 };
	double xyz2001[3] = { 0, 0, 1 * factor };
	double xyz2123[3] = { 1 * factor, 2 * factor, 3 * factor };
	imCC2->euclideanDistanceVector(103, 103, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK(fabs(dv[i]) < EPSILONT);
	}
	imCC2->euclideanDistanceVector(103, 104, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], xyz2100[i], EPSILONT);
	}
	imCC2->euclideanDistanceVector(103, 109, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], xyz2010[i], EPSILONT);
	}
	imCC2->euclideanDistanceVector(73, 103, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], xyz2001[i], EPSILONT);
	}
	imCC2->euclideanDistanceVector(13, 116, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], xyz2123[i], EPSILONT);
	}

	delete imCC;
	delete imCC2;

}

BOOST_AUTO_TEST_CASE(neighborTest) {
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
	CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);

	vector<Neighbor> neighbors;
	int nNeighbors, returnedNeighbors, correctNNeighbors;
	// neighbor indices
	//{r,l,bo,t,f,ba,   bor,tr,bar,fr,bol,tl,bal,fl,boba,bof,tba,tf,   bofr,tfr,tbar,bobar,bofl,tfl,tbal,bobal}
	int CC6[6] = { 171, 169, 176, 164, 140, 200 };	// {63,61,67,57,37,87};
	int CC18[18] = { 171, 169, 176, 164, 140, 200, 177, 165, 201, 141, 175, 163, 199, 139, 206, 146, 194, 134 };	// {63,61,67,57,37,87,68,58,88,38,66,56,86,36,92,42,82,32};
	int CC26[26] = { 171, 169, 176, 164, 140, 200, 177, 165, 201, 141, 175, 163, 199, 139, 206, 146, 194, 134, 147, 135, 195, 207, 145, 133, 193, 205 };// {63,61,67,57,37,87,68,58,88,38,66,56,86,36,92,42,82,32,43,33,83,93,41,31,81,91};

	// 6 neighbors
	nNeighbors = 6;
	correctNNeighbors = 6;
	imCC->getNeighbors(3, 2, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), CC6[i]);
	}
	imCC->getNeighbors(imCC->rclToIndex(3, 2, 5), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), CC6[i]);
	}

	correctNNeighbors = 3;
	imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 0, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 0, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 4;
	imCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 5;
	imCC->getNeighbors(0, 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 2, nL - 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 2, nC - 1, nL - 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 2, nC - 2, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);

	// 18 neighbors
	nNeighbors = 18;
	correctNNeighbors = 18;
	imCC->getNeighbors(3, 2, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), CC18[i]);
	}
	imCC->getNeighbors(imCC->rclToIndex(3, 2, 5), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), CC18[i]);
	}

	correctNNeighbors = 6;
	imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 0, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 0, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 9;
	imCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 13;
	imCC->getNeighbors(0, 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 2, nL - 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 2, nC - 1, nL - 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 2, nC - 2, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);

	// 26 neighbors
	nNeighbors = 26;
	correctNNeighbors = 26;
	imCC->getNeighbors(3, 2, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), CC26[i]);
	}
	imCC->getNeighbors(imCC->rclToIndex(3, 2, 5), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), CC26[i]);
	}
	correctNNeighbors = 7;
	imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 0, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 0, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 11;
	imCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(0, nC - 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, nC - 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 17;
	imCC->getNeighbors(0, 1, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(1, 1, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 1, nC - 2, nL - 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 2, nC - 1, nL - 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imCC->getNeighbors(nR - 2, nC - 2, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);

	// Exceptions
	nNeighbors = 6;
	BOOST_CHECK_THROW(imCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, nC, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, -1, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, nL, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, -1, nNeighbors, neighbors),outsideImageException);
	nNeighbors = 18;
	BOOST_CHECK_THROW(imCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, nC, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, -1, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, nL, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, -1, nNeighbors, neighbors),outsideImageException);
	nNeighbors = 26;
	BOOST_CHECK_THROW(imCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, nC, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, -1, 0, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, nL, nNeighbors, neighbors),outsideImageException);
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, -1, nNeighbors, neighbors),outsideImageException);
	nNeighbors = 8;
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors),nNeighborsException);
	nNeighbors = 12;
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors),nNeighborsException);
	nNeighbors = 14;
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors),nNeighborsException);
	// nNeighbors = 18 is valid for both CC and FCC.
	nNeighbors = -6;
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors),nNeighborsException);
	nNeighbors = 0;
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors),nNeighborsException);
	nNeighbors = 100;
	BOOST_CHECK_THROW(imCC->getNeighbors(0, 0, 0, nNeighbors, neighbors),nNeighborsException);

	delete imCC;

}

BOOST_AUTO_TEST_CASE(operatorTest) {

	int nR = 2, nC = 3, nL = 4, nB = 5;
	int N = nR * nC * nL;
	double data[] = {1,2,3,4,5,6,
					2,3,4,5,6,1,
					3,4,5,6,1,2,
					4,5,6,1,2,3,

					11,12,13,14,15,16,
					12,13,14,15,16,11,
					13,14,15,16,11,12,
					14,15,16,11,12,13,

					21,22,23,24,25,26,
					22,23,24,25,26,21,
					23,24,25,26,21,22,
					24,25,26,21,22,23,

					31,32,33,34,35,36,
					32,33,34,35,36,31,
					33,34,35,36,31,32,
					34,35,36,31,32,33,

					41,42,43,44,45,46,
					42,43,44,45,46,41,
					43,44,45,46,41,42,
					44,45,46,41,42,43};

	CImageCC<double> *imCC = new CImageCC<double>(data, nR, nC, nL, nB);

	int index;
	double returnedVal;
	vector<double> returnedElem;

	// []-operator
	index = 0;
	returnedElem = (*imCC)[index];
	BOOST_CHECK(returnedElem.size() == nB);
	for (int i = 0; i < nB; i++) {
		BOOST_CHECK_CLOSE_FRACTION(returnedElem[i], 10*i + 1, EPSILONT);
	}
	index = 14;
	returnedElem = (*imCC)[index];
	BOOST_CHECK(returnedElem.size() == nB);
	for (int i = 0; i < nB; i++) {
		BOOST_CHECK_CLOSE_FRACTION(returnedElem[i], 10*i + 5, EPSILONT);
	}
	index = 10;
	returnedElem = (*imCC)[index];
	BOOST_CHECK(returnedElem.size() == nB);
	for (int i = 0; i < nB; i++) {
		BOOST_CHECK_CLOSE_FRACTION(returnedElem[i], 10*i + 6, EPSILONT);
	}
	index = N - 1;
	returnedElem = (*imCC)[index];
	BOOST_CHECK(returnedElem.size() == nB);
	for (int i = 0; i < nB; i++) {
		BOOST_CHECK_CLOSE_FRACTION(returnedElem[i], 10*i + 3, EPSILONT);
	}

	// ()-operator
	returnedVal = (*imCC)(0, 0, 0, 0);
	BOOST_CHECK_CLOSE_FRACTION(returnedVal, 1, EPSILONT);
	returnedVal = (*imCC)(0, 1, 2, 3);
	BOOST_CHECK_CLOSE_FRACTION(returnedVal, 34, EPSILONT);
	returnedVal = (*imCC)(nR - 1, nC - 1, nL - 1, nB - 1);
	BOOST_CHECK_CLOSE_FRACTION(returnedVal, 43, EPSILONT);

	returnedVal = (*imCC)(imCC->rclToIndex(0, 0, 0), 0);
	BOOST_CHECK_CLOSE_FRACTION(returnedVal, 1, EPSILONT);
	returnedVal = (*imCC)(imCC->rclToIndex(0, 1, 2), 3);
	BOOST_CHECK_CLOSE_FRACTION(returnedVal, 34, EPSILONT);
	returnedVal = (*imCC)(imCC->rclToIndex(nR - 1, nC - 1, nL - 1), nB - 1);
	BOOST_CHECK_CLOSE_FRACTION(returnedVal, 43, EPSILONT);

	// Exceptions
	BOOST_CHECK_THROW((*imCC)[-1], outsideImageException);
	BOOST_CHECK_THROW((*imCC)[N], outsideImageException);

	BOOST_CHECK_THROW((*imCC)(-1, 0, 0, 0), outsideImageException);
	BOOST_CHECK_THROW((*imCC)(0, -1, 0, 0), outsideImageException);
	BOOST_CHECK_THROW((*imCC)(0, 0, -1, 0), outsideImageException);
	BOOST_CHECK_THROW((*imCC)(0, 0, 0, -1), outsideImageException);
	BOOST_CHECK_THROW((*imCC)(nR, 0, 0, 0), outsideImageException);
	BOOST_CHECK_THROW((*imCC)(0, nC, 0, 0), outsideImageException);
	BOOST_CHECK_THROW((*imCC)(0, 0, nL, 0), outsideImageException);
	BOOST_CHECK_THROW((*imCC)(0, 0, 0, nB), outsideImageException);

	delete imCC;
}

BOOST_AUTO_TEST_CASE(bandTest) {

	int nR = 2, nC = 3, nL = 4, nB = 5;
	int N = nR * nC * nL;
	double data[] = {1,2,3,4,5,6,
					2,3,4,5,6,1,
					3,4,5,6,1,2,
					4,5,6,1,2,3,

					11,12,13,14,15,16,
					12,13,14,15,16,11,
					13,14,15,16,11,12,
					14,15,16,11,12,13,

					21,22,23,24,25,26,
					22,23,24,25,26,21,
					23,24,25,26,21,22,
					24,25,26,21,22,23,

					31,32,33,34,35,36,
					32,33,34,35,36,31,
					33,34,35,36,31,32,
					34,35,36,31,32,33,

					41,42,43,44,45,46,
					42,43,44,45,46,41,
					43,44,45,46,41,42,
					44,45,46,41,42,43};

	CImageCC<double> *imCC = new CImageCC<double>(data, nR, nC, nL, nB);

	// setElement
	double intensities[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
	vector<double> intensities0(nB,0.0);
	vector<double> intensitiesRight, intensitiesShort, intensitiesLong;
	intensitiesShort.assign(intensities, intensities + 4);
	intensitiesRight.assign(intensities, intensities + 5);
	intensitiesLong.assign(intensities, intensities + 6);

	BOOST_CHECK_THROW(imCC->setElement(-1,intensitiesRight),outsideImageException);
	BOOST_CHECK_THROW(imCC->setElement(N,intensitiesRight),outsideImageException);
	BOOST_CHECK_THROW(imCC->setElement(1,intensitiesShort),dimensionMismatchException);
	BOOST_CHECK_THROW(imCC->setElement(1,intensitiesLong),dimensionMismatchException);

	BOOST_CHECK_THROW(imCC->setElement(-1,1,1,intensitiesRight),outsideImageException);
	BOOST_CHECK_THROW(imCC->setElement(1,-1,1,intensitiesRight),outsideImageException);
	BOOST_CHECK_THROW(imCC->setElement(1,1,-1,intensitiesRight),outsideImageException);
	BOOST_CHECK_THROW(imCC->setElement(1,intensitiesShort),dimensionMismatchException);
	BOOST_CHECK_THROW(imCC->setElement(1,intensitiesLong),dimensionMismatchException);


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
	CImagetypeCC *imCC = new CImagetypeCC(data, nR, nC, nL, nB);

	// extract band
	BOOST_CHECK_THROW(imCC->getBand(-1, resultInt), outsideImageException);
	BOOST_CHECK_THROW(imCC->getBand(nB, resultInt), outsideImageException);

	for (int band = 0; band < nB; band++) {
		imCC->getBand(band, resultInt);
		for (int i = 0; i < N; i++) {
			BOOST_CHECK(resultInt[i] == data[band * N + i]);
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
		BOOST_CHECK_EQUAL(resultInt[i], 0);
	}

	// max
	imCC->blend(1, resultInt);
	for (int i = 0; i < N; i++) {
		BOOST_CHECK_EQUAL(resultInt[i], 2);
	}

	// mean
	imCC->blend(2, resultDouble);
	for (int i = 0; i < N; i++) {
		BOOST_CHECK_CLOSE_FRACTION(resultDouble[i], 1.0, EPSILONT);
	}

	BOOST_CHECK_THROW(imCC->blend(-1, resultInt), outsideRangeException);
	BOOST_CHECK_THROW(imCC->blend(2, resultInt), outsideRangeException);
	BOOST_CHECK_THROW(imCC->blend(-1, resultDouble), outsideRangeException);
	BOOST_CHECK_THROW(imCC->blend(0, resultDouble), outsideRangeException);
	BOOST_CHECK_THROW(imCC->blend(3, resultDouble), outsideRangeException);

	delete imCC;
*/
}

BOOST_AUTO_TEST_CASE(segmentationTest) {

}

BOOST_AUTO_TEST_CASE(distanceTransformTest) {

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

	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceLinear(0.0),0.5,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceLinear(0.5),0.0,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceLinear(1.0),-0.5,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceLinear(uint8(0)),0.5,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceLinear(uint8(127)),0.00196078431,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceLinear(uint8(255)),-0.5,EPSILONT);
	BOOST_CHECK_THROW(imCCD->internalDistanceLinear(-0.1),outsideRangeException);
	BOOST_CHECK_THROW(imCCD->internalDistanceLinear(1.1),outsideRangeException);

	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceBall(uint8(0)),0.620350490899400,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceBall(uint8(15)),0.344897652005037,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceBall(uint8(255)),-0.620350490899443,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceBall(0.0),0.620350490899400,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceBall(0.51),imCCD->internalDistanceBall(uint8(128)),EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceBall(1.0),-0.620350490899443,EPSILONT);
	BOOST_CHECK_THROW(imCCD->internalDistanceBall(-0.1),outsideRangeException);
	BOOST_CHECK_THROW(imCCD->internalDistanceBall(1.1),outsideRangeException);

	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceVoronoiAverage(uint8(0)),0.732561001953818,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceVoronoiAverage(uint8(15)),0.361626850445366,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceVoronoiAverage(uint8(255)),-0.729122335558677,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceVoronoiAverage(0.0),0.732561001953818,EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceVoronoiAverage(0.51),imCCD->internalDistanceVoronoiAverage(uint8(128)),EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imCCD->internalDistanceVoronoiAverage(1.0),-0.729122335558677,EPSILONT);
	BOOST_CHECK_THROW(imCCD->internalDistanceVoronoiAverage(-0.1),outsideRangeException);
	BOOST_CHECK_THROW(imCCD->internalDistanceVoronoiAverage(1.1),outsideRangeException);

	BOOST_CHECK_THROW(imCCD->approximatedInternalDistance(-1,0,1),outsideImageException);
	BOOST_CHECK_THROW(imCCU->approximatedInternalDistance(-1,0,1),outsideImageException);
	BOOST_CHECK_THROW(imCCD->approximatedInternalDistance(N,0,1),outsideImageException);
	BOOST_CHECK_THROW(imCCU->approximatedInternalDistance(N,0,1),outsideImageException);
	BOOST_CHECK_THROW(imCCD->approximatedInternalDistance(1,0,-1),outsideRangeException);
	BOOST_CHECK_THROW(imCCU->approximatedInternalDistance(1,0,-1),outsideRangeException);
	BOOST_CHECK_THROW(imCCD->approximatedInternalDistance(1,0,3),outsideRangeException);
	BOOST_CHECK_THROW(imCCU->approximatedInternalDistance(1,0,3),outsideRangeException);*/

}

BOOST_AUTO_TEST_SUITE_END()

/**
 * Tests type CImagetypeBCC aka CImageBCC<uint8>.
 */
BOOST_AUTO_TEST_SUITE(CImagetypeBCC_test)

BOOST_AUTO_TEST_CASE(constructorTest) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = i;
	}

	// constructor
	CImagetypeBCC *imBCC = new CImagetypeBCC(data, nR, nC, nL, nB);
	BOOST_CHECK(imBCC);

	// getters
	uint8* imdata = imBCC->getData();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < nB; j++) {
			BOOST_CHECK(imdata[i] == data[i]);
		}
	}

	BOOST_CHECK(imBCC->getNElements() == N);
	BOOST_CHECK(imBCC->getNElements() != N + 1);

	BOOST_CHECK(imBCC->getNColumns() == nC);
	BOOST_CHECK(imBCC->getNColumns() != nC + 1);

	BOOST_CHECK(imBCC->getNRows() == nR);
	BOOST_CHECK(imBCC->getNRows() != nR + 1);

	BOOST_CHECK(imBCC->getNLayers() == nL);
	BOOST_CHECK(imBCC->getNLayers() != nL + 1);

	BOOST_CHECK(imBCC->getNBands() == nB);
	BOOST_CHECK(imBCC->getNBands() != nB + 1);

	// validity of elements
	BOOST_CHECK(!imBCC->isValid(-1));
	BOOST_CHECK(imBCC->isValid(0));
	BOOST_CHECK(imBCC->isValid(N - 1));
	BOOST_CHECK(!imBCC->isValid(N));

	BOOST_CHECK(!imBCC->isValid(0, -1));
	BOOST_CHECK(!imBCC->isValid(N - 1, -1));
	BOOST_CHECK(!imBCC->isValid(-1, 0));
	BOOST_CHECK(imBCC->isValid(0, 0));
	BOOST_CHECK(imBCC->isValid(N - 1, 0));
	BOOST_CHECK(!imBCC->isValid(N, 0));
	BOOST_CHECK(imBCC->isValid(0, nB - 1));
	BOOST_CHECK(imBCC->isValid(N - 1, nB - 1));
	BOOST_CHECK(!imBCC->isValid(0, nB));
	BOOST_CHECK(!imBCC->isValid(N - 1, nB));

	BOOST_CHECK(!imBCC->isValid(-1, 0, 0));
	BOOST_CHECK(!imBCC->isValid(0, -1, 0));
	BOOST_CHECK(!imBCC->isValid(0, 0, -1));
	BOOST_CHECK(imBCC->isValid(0, 0, 0));
	BOOST_CHECK(imBCC->isValid(nR - 1, 0, 0));
	BOOST_CHECK(imBCC->isValid(0, nC - 1, 0));
	BOOST_CHECK(imBCC->isValid(0, 0, nL - 1));
	BOOST_CHECK(!imBCC->isValid(nR, 0, 0));
	BOOST_CHECK(!imBCC->isValid(0, nC, 0));
	BOOST_CHECK(!imBCC->isValid(0, 0, nL));

	BOOST_CHECK(!imBCC->isValid(0, 0, 0, -1));
	BOOST_CHECK(!imBCC->isValid(nR - 1, 0, 0, -1));
	BOOST_CHECK(!imBCC->isValid(0, nC - 1, 0, -1));
	BOOST_CHECK(!imBCC->isValid(0, 0, nL - 1, -1));
	BOOST_CHECK(!imBCC->isValid(0, 0, 0, nB));
	BOOST_CHECK(!imBCC->isValid(nR - 1, 0, 0, nB));
	BOOST_CHECK(!imBCC->isValid(0, nC - 1, 0, nB));
	BOOST_CHECK(!imBCC->isValid(0, 0, nL - 1, nB));
	BOOST_CHECK(imBCC->isValid(0, 0, 0, nB - 1));
	BOOST_CHECK(imBCC->isValid(nR - 1, 0, 0, nB - 1));
	BOOST_CHECK(imBCC->isValid(0, nC - 1, 0, nB - 1));
	BOOST_CHECK(imBCC->isValid(0, 0, nL - 1, nB - 1));

	// index conversion
	BOOST_CHECK(imBCC->rclToIndex(0, 0, 0) == 0);
	BOOST_CHECK(imBCC->rclToIndex(1, 2, 3) == 98);
	BOOST_CHECK(imBCC->rclToIndex(nR - 1, nC - 1, nL - 1) == N - 1);

	BOOST_CHECK(imBCC->indexToR(0) == 0);
	BOOST_CHECK(imBCC->indexToC(0) == 0);
	BOOST_CHECK(imBCC->indexToL(0) == 0);
	BOOST_CHECK(imBCC->indexToR(98) == 1);
	BOOST_CHECK(imBCC->indexToC(98) == 2);
	BOOST_CHECK(imBCC->indexToL(98) == 3);
	BOOST_CHECK(imBCC->indexToR(N - 1) == nR - 1);
	BOOST_CHECK(imBCC->indexToC(N - 1) == nC - 1);
	BOOST_CHECK(imBCC->indexToL(N - 1) == nL - 1);

	delete imBCC;
}

BOOST_AUTO_TEST_CASE(coordinateTest) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = 0;
	}
	CImagetypeBCC *imBCC = new CImagetypeBCC(data, nR, nC, nL, nB);
	double volume = 2.5;
	CImagetypeBCC *imBCC2 = new CImagetypeBCC(data, nR, nC, nL, nB, volume);
	double factor = cbrt(volume);

	CImagetypeBCC *imBCC1C1L = new CImagetypeBCC(data, N, 1, 1, 1);
	CImagetypeBCC *imBCC1R1L = new CImagetypeBCC(data, 1, N, 1, 1);
	CImagetypeBCC *imBCC1R1C = new CImagetypeBCC(data, 1, 1, N, 1);
	int n1 = 15, n2 = 14;
	CImagetypeBCC *imBCCRC = new CImagetypeBCC(data, n1, n2, 1, 1);
	CImagetypeBCC *imBCCRL = new CImagetypeBCC(data, n1, 1, n2, 1);
	CImagetypeBCC *imBCCCL = new CImagetypeBCC(data, 1, n1, n2, 1);
	vector<double> coordinates;

	// spel coordinates
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToX(0), BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToY(0), BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToZ(0), BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToX(82), BCCOFFSET + 4*BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToY(82), BCCOFFSET + 3*BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToZ(82), BCCOFFSET + BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToX(112), BCCOFFSET + 9*BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToY(112), BCCOFFSET + 7*BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToZ(112), BCCOFFSET + 3*BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToX(209), BCCOFFSET + 5*BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToY(209), BCCOFFSET + 4*BCCSQFACEDISTANCE, EPSILONT); // !!!!!!
	BOOST_CHECK_CLOSE_FRACTION(imBCC->indexToZ(209), BCCOFFSET + 3*BCCSQFACEDISTANCE, EPSILONT);

	imBCC->getCoordinates(0,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], BCCOFFSET, EPSILONT);
	imBCC->getCoordinates(82,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], BCCOFFSET + 4*BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], BCCOFFSET + 3*BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], BCCOFFSET + BCCSQFACEDISTANCE, EPSILONT);
	imBCC->getCoordinates(112,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], BCCOFFSET + 9*BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], BCCOFFSET + 7*BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], BCCOFFSET + 3*BCCOFFSET, EPSILONT);
	imBCC->getCoordinates(209,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], BCCOFFSET + 5*BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], BCCOFFSET + 4*BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], BCCOFFSET + 3*BCCSQFACEDISTANCE, EPSILONT);


	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToX(0), factor * (BCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToY(0), factor * (BCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToZ(0), factor * (BCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToX(82), factor * (BCCOFFSET + 4*BCCSQFACEDISTANCE), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToY(82), factor * (BCCOFFSET + 3*BCCSQFACEDISTANCE), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToZ(82), factor * (BCCOFFSET + BCCSQFACEDISTANCE), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToX(112), factor * (BCCOFFSET + 9*BCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToY(112), factor * (BCCOFFSET + 7*BCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToZ(112), factor * (BCCOFFSET + 3*BCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToX(209), factor * (BCCOFFSET + 5*BCCSQFACEDISTANCE), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToY(209), factor * (BCCOFFSET + 4*BCCSQFACEDISTANCE), EPSILONT); // !!!!!!
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->indexToZ(209), factor * (BCCOFFSET + 3*BCCSQFACEDISTANCE), EPSILONT);

	// width, height and depth
	BOOST_CHECK_CLOSE_FRACTION(imBCC->getWidth(), 6.5 * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->getHeight(), 5.5 * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->getDepth(), 4 * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->getWidth(), factor * 6.5 * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->getHeight(), factor * 5.5 * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->getDepth(), factor * 4 * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC1C1L->getWidth(), BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC1C1L->getHeight(), N * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC1C1L->getDepth(), BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC1R1L->getWidth(), N * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC1R1L->getHeight(), BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC1R1L->getDepth(), BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC1R1C->getWidth(), BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC1R1C->getHeight(), BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC1R1C->getDepth(), (N + 1) * BCCOFFSET, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imBCCRC->getWidth(), n2 * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCCRC->getHeight(), n1 * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCCRC->getDepth(), BCCSQFACEDISTANCE, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imBCCRL->getWidth(), BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCCRL->getHeight(), n1 * BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCCRL->getDepth(), (n2 + 1) * BCCOFFSET, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imBCCCL->getWidth(), n1 * BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCCCL->getHeight(), BCCSQFACEDISTANCE + BCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCCCL->getDepth(), (n2 + 1) * BCCOFFSET, EPSILONT);

	delete imBCC;
	delete imBCC2;
	delete imBCC1C1L;
	delete imBCC1R1L;
	delete imBCC1R1C;
	delete imBCCCL;
	delete imBCCRL;
	delete imBCCRC;
}

BOOST_AUTO_TEST_CASE(distanceTest) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = 0;
	}
	CImagetypeBCC *imBCC = new CImagetypeBCC(data, nR, nC, nL, nB);
	double volume = 2.5;
	CImagetypeBCC *imBCC2 = new CImagetypeBCC(data, nR, nC, nL, nB, volume);
	double factor = cbrt(volume);

	// distance between spels
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(0, 0), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(170, 170), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 45), BCCHEXFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 45), imBCC->euclideanDistance(45, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 46), BCCHEXFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 46), imBCC->euclideanDistance(46, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 51), BCCHEXFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 51), imBCC->euclideanDistance(51, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 52), BCCHEXFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 52), imBCC->euclideanDistance(52, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 22), BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 22), imBCC->euclideanDistance(22, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 76), BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 76), imBCC->euclideanDistance(76, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 83), BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC->euclideanDistance(82, 83), imBCC->euclideanDistance(83, 82), EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(0, 0), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(170, 170), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 45), factor * BCCHEXFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 45), imBCC2->euclideanDistance(45, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 46), factor * BCCHEXFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 46), imBCC2->euclideanDistance(46, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 51), factor * BCCHEXFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 51), imBCC2->euclideanDistance(51, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 52), factor * BCCHEXFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 52), imBCC2->euclideanDistance(52, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 22), factor * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 22), imBCC2->euclideanDistance(22, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 76), factor * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 76), imBCC2->euclideanDistance(76, 82), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 83), factor * BCCSQFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imBCC2->euclideanDistance(82, 83), imBCC2->euclideanDistance(83, 82), EPSILONT);

	vector<double> dv;
	double right[3] = { BCCSQFACEDISTANCE, 0, 0 };
	double bottom[3] = { 0, BCCSQFACEDISTANCE, 0 };
	double back[3] = { 0, 0, BCCSQFACEDISTANCE };
	double left[3] = { -BCCSQFACEDISTANCE, 0, 0 };
	double top[3] = { 0, -BCCSQFACEDISTANCE, 0 };
	double front[3] = { 0, 0, -BCCSQFACEDISTANCE };
	double ftl[3] = { -BCCOFFSET, -BCCOFFSET, -BCCOFFSET };
	double ftr[3] = { BCCOFFSET, -BCCOFFSET, -BCCOFFSET };
	double fbl[3] = { -BCCOFFSET, BCCOFFSET, -BCCOFFSET };
	double fbr[3] = { BCCOFFSET, BCCOFFSET, -BCCOFFSET };
	double btl[3] = { -BCCOFFSET, -BCCOFFSET, BCCOFFSET };
	double btr[3] = { BCCOFFSET, -BCCOFFSET, BCCOFFSET };
	double bbl[3] = { -BCCOFFSET, BCCOFFSET, BCCOFFSET };
	double bbr[3] = { BCCOFFSET, BCCOFFSET, BCCOFFSET };
	imBCC->euclideanDistanceVector(82, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK(fabs(dv[i]) < EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 83, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], right[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 88, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bottom[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(22, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], back[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(83, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], left[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(88, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], top[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 22, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], front[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 45, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], ftl[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 46, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], ftr[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 51, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fbl[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 52, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fbr[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 105, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], btl[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 106, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], btr[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 111, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bbl[i], EPSILONT);
	}
	imBCC->euclideanDistanceVector(82, 112, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bbr[i], EPSILONT);
	}

	double right2[3] = { factor * BCCSQFACEDISTANCE, 0, 0 };
	double bottom2[3] = { 0, factor * BCCSQFACEDISTANCE, 0 };
	double back2[3] = { 0, 0, factor * BCCSQFACEDISTANCE };
	double left2[3] = { -factor * BCCSQFACEDISTANCE, 0, 0 };
	double top2[3] = { 0, -factor * BCCSQFACEDISTANCE, 0 };
	double front2[3] = { 0, 0, -factor * BCCSQFACEDISTANCE };
	double ftl2[3] = { -factor * BCCOFFSET, -factor * BCCOFFSET, -factor * BCCOFFSET };
	double ftr2[3] = { factor * BCCOFFSET, -factor * BCCOFFSET, -factor * BCCOFFSET };
	double fbl2[3] = { -factor * BCCOFFSET, factor * BCCOFFSET, -factor * BCCOFFSET };
	double fbr2[3] = { factor * BCCOFFSET, factor * BCCOFFSET, -factor * BCCOFFSET };
	double btl2[3] = { -factor * BCCOFFSET, -factor * BCCOFFSET, factor * BCCOFFSET };
	double btr2[3] = { factor * BCCOFFSET, -factor * BCCOFFSET, factor * BCCOFFSET };
	double bbl2[3] = { -factor * BCCOFFSET, factor * BCCOFFSET, factor * BCCOFFSET };
	double bbr2[3] = { factor * BCCOFFSET, factor * BCCOFFSET, factor * BCCOFFSET };
	imBCC2->euclideanDistanceVector(82, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK(fabs(dv[i]) < EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 83, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], right2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 88, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bottom2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(22, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], back2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(83, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], left2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(88, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], top2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 22, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], front2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 45, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], ftl2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 46, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], ftr2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 51, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fbl2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 52, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fbr2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 105, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], btl2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 106, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], btr2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 111, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bbl2[i], EPSILONT);
	}
	imBCC2->euclideanDistanceVector(82, 112, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bbr2[i], EPSILONT);
	}

	delete imBCC;
	delete imBCC2;
}

BOOST_AUTO_TEST_CASE(neighborTest) {
	/**
	 * Tests getNeighbor(r,c,l,N). Since all other methods
	 * always call getXNeighbors(r,c,l), those methods should work
	 * properly if the tests pass for this method and for
	 * indexTo[R,C,L]().
	 */

	// image parameters
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N];
	for (int i = 0; i < N; i++) {
		data[i] = 0;
	}
	CImagetypeBCC *imBCC = new CImagetypeBCC(data, nR, nC, nL, nB);

	vector<Neighbor> neighbors;
	int nNeighbors, returnedNeighbors, correctNNeighbors;
	// neighbor indices
	// {tlf,trf,bolf,borf,tlba,trba,bolba,borba,   t,f,l,ba,r,bo}
	int BCC8EL[8] = { 45, 46, 51, 52, 105, 106, 111, 112 }; // {31,32,36,37,81,82,86,87};
	int BCC8OL[8] = { 82, 83, 88, 89, 142, 143, 148, 149 }; // {12,13,17,18,62,63,67,68};
	int BCC14EL[14] = { 45, 46, 51, 52, 105, 106, 111, 112, 76, 22, 81, 142, 83, 88 }; // {31,32,36,37,81,82,86,87,57,12,61,112,63,67};
	int BCC14OL[14] = { 82, 83, 88, 89, 142, 143, 148, 149, 106, 52, 111, 172, 113, 118 }; // {12,13,17,18,62,63,67,68,32,36,87,38,42};

	// 8 neighbors
	nNeighbors = 8;
	correctNNeighbors = 8;
	imBCC->getNeighbors(3, 4, 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK(neighbors[i].getIndex() == BCC8EL[i]);
	}
	imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 2), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK(neighbors[i].getIndex() == BCC8EL[i]);
	}
	imBCC->getNeighbors(3, 4, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK(neighbors[i].getIndex() == BCC8OL[i]);
	}
	imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK(neighbors[i].getIndex() == BCC8OL[i]);
	}
	correctNNeighbors = 1;
	imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	correctNNeighbors = 2;
	imBCC->getNeighbors(4, 0, 6, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	correctNNeighbors = 4;
	imBCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	imBCC->getNeighbors(0, 5, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	imBCC->getNeighbors(4, 0, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);

	// 14 neighbors
	nNeighbors = 14;
	correctNNeighbors = 14;
	imBCC->getNeighbors(3, 4, 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK(neighbors[i].getIndex() == BCC14EL[i]);
	}
	imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 2), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK(neighbors[i].getIndex() == BCC14EL[i]);
	}
	imBCC->getNeighbors(3, 4, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK(neighbors[i].getIndex() == BCC14OL[i]);
	}
	imBCC->getNeighbors(imBCC->rclToIndex(3, 4, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK(neighbors[i].getIndex() == BCC14OL[i]);
	}
	correctNNeighbors = 4;
	imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	correctNNeighbors = 5;
	imBCC->getNeighbors(4, 0, 6, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	correctNNeighbors = 7;
	imBCC->getNeighbors(nR - 1, nC - 1, nL - 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	imBCC->getNeighbors(0, 5, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);
	imBCC->getNeighbors(4, 0, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK(returnedNeighbors == correctNNeighbors);

	// Exceptions
	nNeighbors = 8;
	BOOST_CHECK_THROW(imBCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
	nNeighbors = 14;
	BOOST_CHECK_THROW(imBCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, nC, 0, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, -1, 0, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, nL, nNeighbors, neighbors), outsideImageException);
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, -1, nNeighbors, neighbors), outsideImageException);
	nNeighbors = 6;
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 12;
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 18;
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 26;
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = -8;
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 0;
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 100;
	BOOST_CHECK_THROW(imBCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);

	delete imBCC;
}

 BOOST_AUTO_TEST_CASE(filterTest){

 }

 BOOST_AUTO_TEST_CASE(segmentationTest){

 }

 BOOST_AUTO_TEST_CASE(distanceTransformTest){

 }

 BOOST_AUTO_TEST_SUITE_END()

/**
 * Tests type CImagetypeFCC aka CImageFCC<uint8>.
 */
BOOST_AUTO_TEST_SUITE(CImagetypeFCC_test)

BOOST_AUTO_TEST_CASE(constructorTest) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = i;
	}

	// constructor
	CImagetypeFCC *imFCC = new CImagetypeFCC(data, nR, nC, nL, nB);
	BOOST_CHECK(imFCC);

	// getters
	uint8* imdata = imFCC->getData();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < nB; j++) {
			BOOST_CHECK(imdata[i] == data[i]);
		}
	}

	BOOST_CHECK(imFCC->getNElements() == N);
	BOOST_CHECK(imFCC->getNElements() != N + 1);

	BOOST_CHECK(imFCC->getNColumns() == nC);
	BOOST_CHECK(imFCC->getNColumns() != nC + 1);

	BOOST_CHECK(imFCC->getNRows() == nR);
	BOOST_CHECK(imFCC->getNRows() != nR + 1);

	BOOST_CHECK(imFCC->getNLayers() == nL);
	BOOST_CHECK(imFCC->getNLayers() != nL + 1);

	BOOST_CHECK(imFCC->getNBands() == nB);
	BOOST_CHECK(imFCC->getNBands() != nB + 1);

	// validity of elements
	BOOST_CHECK(!imFCC->isValid(-1));
	BOOST_CHECK(imFCC->isValid(0));
	BOOST_CHECK(imFCC->isValid(N - 1));
	BOOST_CHECK(!imFCC->isValid(N));

	BOOST_CHECK(!imFCC->isValid(0, -1));
	BOOST_CHECK(!imFCC->isValid(N - 1, -1));
	BOOST_CHECK(!imFCC->isValid(-1, 0));
	BOOST_CHECK(imFCC->isValid(0, 0));
	BOOST_CHECK(imFCC->isValid(N - 1, 0));
	BOOST_CHECK(!imFCC->isValid(N, 0));
	BOOST_CHECK(imFCC->isValid(0, nB - 1));
	BOOST_CHECK(imFCC->isValid(N - 1, nB - 1));
	BOOST_CHECK(!imFCC->isValid(0, nB));
	BOOST_CHECK(!imFCC->isValid(N - 1, nB));

	BOOST_CHECK(!imFCC->isValid(-1, 0, 0));
	BOOST_CHECK(!imFCC->isValid(0, -1, 0));
	BOOST_CHECK(!imFCC->isValid(0, 0, -1));
	BOOST_CHECK(imFCC->isValid(0, 0, 0));
	BOOST_CHECK(imFCC->isValid(nR - 1, 0, 0));
	BOOST_CHECK(imFCC->isValid(0, nC - 1, 0));
	BOOST_CHECK(imFCC->isValid(0, 0, nL - 1));
	BOOST_CHECK(!imFCC->isValid(nR, 0, 0));
	BOOST_CHECK(!imFCC->isValid(0, nC, 0));
	BOOST_CHECK(!imFCC->isValid(0, 0, nL));

	BOOST_CHECK(!imFCC->isValid(0, 0, 0, -1));
	BOOST_CHECK(!imFCC->isValid(nR - 1, 0, 0, -1));
	BOOST_CHECK(!imFCC->isValid(0, nC - 1, 0, -1));
	BOOST_CHECK(!imFCC->isValid(0, 0, nL - 1, -1));
	BOOST_CHECK(!imFCC->isValid(0, 0, 0, nB));
	BOOST_CHECK(!imFCC->isValid(nR - 1, 0, 0, nB));
	BOOST_CHECK(!imFCC->isValid(0, nC - 1, 0, nB));
	BOOST_CHECK(!imFCC->isValid(0, 0, nL - 1, nB));
	BOOST_CHECK(imFCC->isValid(0, 0, 0, nB - 1));
	BOOST_CHECK(imFCC->isValid(nR - 1, 0, 0, nB - 1));
	BOOST_CHECK(imFCC->isValid(0, nC - 1, 0, nB - 1));
	BOOST_CHECK(imFCC->isValid(0, 0, nL - 1, nB - 1));

	// index conversion
	BOOST_CHECK(imFCC->rclToIndex(0, 0, 0) == 0);
	BOOST_CHECK(imFCC->rclToIndex(1, 2, 3) == 98);
	BOOST_CHECK(imFCC->rclToIndex(nR - 1, nC - 1, nL - 1) == N - 1);

	BOOST_CHECK(imFCC->indexToR(0) == 0);
	BOOST_CHECK(imFCC->indexToC(0) == 0);
	BOOST_CHECK(imFCC->indexToL(0) == 0);
	BOOST_CHECK(imFCC->indexToR(98) == 1);
	BOOST_CHECK(imFCC->indexToC(98) == 2);
	BOOST_CHECK(imFCC->indexToL(98) == 3);
	BOOST_CHECK(imFCC->indexToR(N - 1) == nR - 1);
	BOOST_CHECK(imFCC->indexToC(N - 1) == nC - 1);
	BOOST_CHECK(imFCC->indexToL(N - 1) == nL - 1);

	delete imFCC;
}

BOOST_AUTO_TEST_CASE(coordinateTest) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = 0;
	}
	CImagetypeFCC *imFCC = new CImagetypeFCC(data, nR, nC, nL, nB);
	double volume = 2.5;
	double factor = cbrt(volume);
	CImagetypeFCC *imFCC2 = new CImagetypeFCC(data, nR, nC, nL, nB, volume);
	vector<double> coordinates;

	// spel coordinates
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToX(0), FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToY(0), FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToZ(0), FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToX(135), FCCOFFSET + 6*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToY(135), FCCOFFSET + FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToZ(135), FCCOFFSET + 2*FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToX(80), FCCOFFSET + 5*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToY(80), FCCOFFSET + 3*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToZ(80), FCCOFFSET + 2*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToX(105), FCCOFFSET + 7*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToY(105), FCCOFFSET + 2*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToZ(105), FCCOFFSET + 3*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToX(110), FCCOFFSET + 4*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToY(110), FCCOFFSET + 3*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToZ(110), FCCOFFSET + 3*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToX(209), FCCOFFSET + 10*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToY(209), FCCOFFSET + 4*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->indexToZ(209), FCCOFFSET + 6*FCCOFFSET, EPSILONT);

	imFCC->getCoordinates(0,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], FCCOFFSET, EPSILONT);
	imFCC->getCoordinates(135,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], FCCOFFSET + 6*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], FCCOFFSET + FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], FCCOFFSET + 2*FCCPOINTDISTANCE, EPSILONT);
	imFCC->getCoordinates(209,coordinates);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[0], FCCOFFSET + 10*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[1], FCCOFFSET + 4*FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(coordinates[2], FCCOFFSET + 6*FCCOFFSET, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToX(0), factor * FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToY(0), factor * FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToZ(0), factor * FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToX(135), factor * (FCCOFFSET + 6*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToY(135), factor * (FCCOFFSET + FCCPOINTDISTANCE), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToZ(135), factor * (FCCOFFSET + 2*FCCPOINTDISTANCE), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToX(80), factor * (FCCOFFSET + 5*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToY(80), factor * (FCCOFFSET + 3*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToZ(80), factor * (FCCOFFSET + 2*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToX(105), factor * (FCCOFFSET + 7*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToY(105), factor * (FCCOFFSET + 2*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToZ(105), factor * (FCCOFFSET + 3*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToX(110), factor * (FCCOFFSET + 4*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToY(110), factor * (FCCOFFSET + 3*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToZ(110), factor * (FCCOFFSET + 3*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToX(209), factor * (FCCOFFSET + 10*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToY(209), factor * (FCCOFFSET + 4*FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->indexToZ(209), factor * (FCCOFFSET + 6*FCCOFFSET), EPSILONT);

	CImagetypeFCC *imFCC1C1L = new CImagetypeFCC(data, N, 1, 1, 1);
	CImagetypeFCC *imFCC1R1L = new CImagetypeFCC(data, 1, N, 1, 1);
	CImagetypeFCC *imFCC1R1C = new CImagetypeFCC(data, 1, 1, N, 1);
	int n1 = 15, n2 = 14;
	CImagetypeFCC *imFCCRC = new CImagetypeFCC(data, n1, n2, 1, 1);
	CImagetypeFCC *imFCCRL = new CImagetypeFCC(data, n1, 1, n2, 1);
	CImagetypeFCC *imFCCCL = new CImagetypeFCC(data, 1, n1, n2, 1);

	// width, height and depth
	BOOST_CHECK_CLOSE_FRACTION(imFCC->getWidth(), 6 * FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->getHeight(), 3 * FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->getDepth(), (7 + 1) * FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->getWidth(), factor * (6 * FCCPOINTDISTANCE + FCCOFFSET), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->getHeight(), factor * (3 * FCCPOINTDISTANCE), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->getDepth(), factor * (7 + 1) * FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC1C1L->getWidth(), 3 * FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC1C1L->getHeight(), (N + 1) * FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC1C1L->getDepth(), FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC1R1L->getWidth(), N * FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC1R1L->getHeight(), FCCPOINTDISTANCE, EPSILONT); //!!
	BOOST_CHECK_CLOSE_FRACTION(imFCC1R1L->getDepth(), FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC1R1C->getWidth(), FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC1R1C->getHeight(), FCCPOINTDISTANCE, EPSILONT); //!!
	BOOST_CHECK_CLOSE_FRACTION(imFCC1R1C->getDepth(), (N + 1) * FCCOFFSET, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imFCCRC->getWidth(), n2 * FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCCRC->getHeight(), (n1 + 1) * FCCOFFSET, EPSILONT); //!!
	BOOST_CHECK_CLOSE_FRACTION(imFCCRC->getDepth(), FCCPOINTDISTANCE, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imFCCRL->getWidth(), FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCCRL->getHeight(), (n1 + 1) * FCCOFFSET, EPSILONT); //!!
	BOOST_CHECK_CLOSE_FRACTION(imFCCRL->getDepth(), (n2 + 1) * FCCOFFSET, EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imFCCCL->getWidth(), n1 * FCCPOINTDISTANCE + FCCOFFSET, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCCCL->getHeight(), FCCPOINTDISTANCE, EPSILONT); //!!
	BOOST_CHECK_CLOSE_FRACTION(imFCCCL->getDepth(), (n2 + 1) * FCCOFFSET, EPSILONT);

	delete imFCC;
	delete imFCC2;
	delete imFCC1C1L;
	delete imFCC1R1L;
	delete imFCC1R1C;
	delete imFCCCL;
	delete imFCCRL;
	delete imFCCRC;
}

BOOST_AUTO_TEST_CASE(distanceTest) {

	// set up image
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N * nB];
	for (int i = 0; i < nB * N; i++) {
		data[i] = 0;
	}
	CImagetypeFCC *imFCC = new CImagetypeFCC(data, nR, nC, nL, nB);
	double volume = 2.5;
	double factor = cbrt(volume);
	CImagetypeFCC *imFCC2 = new CImagetypeFCC(data, nR, nC, nL, nB, volume);

	// distance between spels
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(0, 0), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(170, 170), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 69), FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 69), imFCC->euclideanDistance(69, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 75), FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 75), imFCC->euclideanDistance(75, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 76), FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 76), imFCC->euclideanDistance(76, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 81), FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 81), imFCC->euclideanDistance(81, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 99), FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 99), imFCC->euclideanDistance(99, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 100), FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 100), imFCC->euclideanDistance(100, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 45), FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 45), imFCC->euclideanDistance(45, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 93), FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 93), imFCC->euclideanDistance(93, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 104), FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC->euclideanDistance(105, 104), imFCC->euclideanDistance(104, 105), EPSILONT);

	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(0, 0), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(170, 170), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(N - 1, N - 1), 0, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 69), factor * FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 69), imFCC2->euclideanDistance(69, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 75), factor * FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 75), imFCC2->euclideanDistance(75, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 76), factor * FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 76), imFCC2->euclideanDistance(76, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 81), factor * FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 81), imFCC2->euclideanDistance(81, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 99), factor * FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 99), imFCC2->euclideanDistance(99, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 100), factor * FCCFACEDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 100), imFCC2->euclideanDistance(100, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 45), factor * FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 45), imFCC2->euclideanDistance(45, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 93), factor * FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 93), imFCC2->euclideanDistance(93, 105), EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 104), factor * FCCPOINTDISTANCE, EPSILONT);
	BOOST_CHECK_CLOSE_FRACTION(imFCC2->euclideanDistance(105, 104), imFCC2->euclideanDistance(104, 105), EPSILONT);

	vector<double> dv;
	double ft[3] = { 0, -FCCOFFSET, -FCCOFFSET };
	double fr[3] = { FCCOFFSET, 0, -FCCOFFSET };
	double fb[3] = { 0, FCCOFFSET, -FCCOFFSET };
	double fl[3] = { -FCCOFFSET, 0, -FCCOFFSET };
	double mtr[3] = { FCCOFFSET, -FCCOFFSET, 0 };
	double mbr[3] = { FCCOFFSET, FCCOFFSET, 0 };
	double mbl[3] = { -FCCOFFSET, FCCOFFSET, 0 };
	double mtl[3] = { -FCCOFFSET, -FCCOFFSET, 0 };
	double bt[3] = { 0, -FCCOFFSET, FCCOFFSET };
	double br[3] = { FCCOFFSET, 0, FCCOFFSET };
	double bb[3] = { 0, FCCOFFSET, FCCOFFSET };
	double bl[3] = { -FCCOFFSET, 0, FCCOFFSET };
	double front[3] = { 0, 0, -FCCPOINTDISTANCE };
	double top[3] = { 0, -FCCPOINTDISTANCE, 0 };
	double right[3] = { FCCPOINTDISTANCE, 0, 0 };
	double bottom[3] = { 0, FCCPOINTDISTANCE, 0 };
	double left[3] = { -FCCPOINTDISTANCE, 0, 0 };
	double back[3] = { 0, 0, FCCPOINTDISTANCE };
	imFCC->euclideanDistanceVector(82, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK(fabs(dv[i]) < EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 45, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], front[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 93, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], top[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 106, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], right[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 117, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bottom[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 104, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], left[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 165, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], back[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 69, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], ft[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 76, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fr[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 81, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fb[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 75, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fl[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 100, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], mtr[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 112, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], mbr[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 111, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], mbl[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 99, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], mtl[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 129, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bt[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 136, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], br[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 141, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bb[i], EPSILONT);
	}
	imFCC->euclideanDistanceVector(105, 135, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bl[i], EPSILONT);
	}

	double ft2[3] = { 0, -factor * FCCOFFSET, -factor * FCCOFFSET };
	double fr2[3] = { factor * FCCOFFSET, 0, -factor * FCCOFFSET };
	double fb2[3] = { 0, factor * FCCOFFSET, -factor * FCCOFFSET };
	double fl2[3] = { -factor * FCCOFFSET, 0, -factor * FCCOFFSET };
	double mtr2[3] = { factor * FCCOFFSET, -factor * FCCOFFSET, 0 };
	double mbr2[3] = { factor * FCCOFFSET, factor * FCCOFFSET, 0 };
	double mbl2[3] = { -factor * FCCOFFSET, factor * FCCOFFSET, 0 };
	double mtl2[3] = { -factor * FCCOFFSET, -factor * FCCOFFSET, 0 };
	double bt2[3] = { 0, -factor * FCCOFFSET, factor * FCCOFFSET };
	double br2[3] = { factor * FCCOFFSET, 0, factor * FCCOFFSET };
	double bb2[3] = { 0, factor * FCCOFFSET, factor * FCCOFFSET };
	double bl2[3] = { -factor * FCCOFFSET, 0, factor * FCCOFFSET };
	double front2[3] = { 0, 0, -factor * FCCPOINTDISTANCE };
	double top2[3] = { 0, -factor * FCCPOINTDISTANCE, 0 };
	double right2[3] = { factor * FCCPOINTDISTANCE, 0, 0 };
	double bottom2[3] = { 0, factor * FCCPOINTDISTANCE, 0 };
	double left2[3] = { -factor * FCCPOINTDISTANCE, 0, 0 };
	double back2[3] = { 0, 0, factor * FCCPOINTDISTANCE };
	imFCC2->euclideanDistanceVector(82, 82, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK(fabs(dv[i]) < EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 45, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], front2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 93, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], top2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 106, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], right2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 117, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bottom2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 104, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], left2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 165, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], back2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 69, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], ft2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 76, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fr2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 81, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fb2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 75, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], fl2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 100, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], mtr2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 112, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], mbr2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 111, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], mbl2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 99, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], mtl2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 129, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bt2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 136, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], br2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 141, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bb2[i], EPSILONT);
	}
	imFCC2->euclideanDistanceVector(105, 135, dv);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_CLOSE_FRACTION(dv[i], bl2[i], EPSILONT);
	}

	delete imFCC;
	delete imFCC2;

}

BOOST_AUTO_TEST_CASE(neighborTest) {

	/**
	 * Tests getNeighbor(r,c,l,N). Since all other methods
	 * always call getXNeighbors(r,c,l), those methods should work
	 * properly if the tests pass for this method and for
	 * indexTo[R,C,L]().
	 */

	// image parameters
	int nR = 5, nC = 6, nL = 7, nB = 3;
	int N = nR * nC * nL;
	uint8 data[N];
	for (int i = 0; i < N; i++) {
		data[i] = 0;
	}
	CImagetypeFCC *imFCC = new CImagetypeFCC(data, nR, nC, nL, nB);

	vector<Neighbor> neighbors;
	int nNeighbors, returnedNeighbors, correctNNeighbors;
	// neighbor indices
	// {tf,tl,tba,tr,fl,bal,bar,fr,bof,bol,boba,bor,   t,f,l,ba,r,bo}
	int FCC12ELER[12] = { 99, 128, 159, 129, 104, 164, 165, 105, 111, 140, 171, 141 }; // {31,55,81,56,35,85,86,36,41,65,91,66};
	int FCC12ELOR[12] = { 44, 74, 104, 75, 50, 110, 111, 51, 56, 86, 116, 87 }; // {37,62,87,63,42,92,93,43,47,72,97,73};
	int FCC12OLER[12] =	{ 69, 99, 129, 100, 75, 135, 136, 76, 81, 111, 141, 112 }; // {1,25,51,26,5,55,56,6,11,35,61,36};
	int FCC12OLOR[12] = { 74, 103, 134, 104, 79, 139, 140, 80, 86, 115, 146, 116 }; // {6,31,56,32,11,61,62,12,16,41,66,42};
	int FCC18ELER[18] = { 99, 128, 159, 129, 104, 164, 165, 105, 111, 140, 171, 141, 123, 75, 134, 195, 136, 147 }; // {31,55,81,56,35,85,86,36,41,65,91,66,51,11,60,111,62,71};
	int FCC18ELOR[18] = { 44, 74, 104, 75, 50, 110, 111, 51, 56, 86, 116, 87, 68, 20, 79, 140, 81 }; // bottom missing // {37,62,87,63,42,92,93,43,47,72,97,73,57,17,66,117,68}; // bottom missing
	int FCC18OLER[18] = { 69, 99, 129, 100, 75, 135, 136, 76, 81, 111, 141, 112, 93, 45, 104, 165, 106, 117 }; // {1,25,51,26,5,55,56,6,11,35,61,36,30,81,32,41}; // top and front missing
	int FCC18OLOR[18] = { 74, 103, 134, 104, 79, 139, 140, 80, 86, 115, 146, 116, 98, 50, 109, 170, 111 }; // bottom missing // {6,31,56,32,11,61,62,12,16,41,66,42,26,35,86,37,46}; // front missing

	// 12 neighbors
	nNeighbors = 12;
	correctNNeighbors = 3;
	imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 5;
	imFCC->getNeighbors(4, 5, 6, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imFCC->getNeighbors(3, 5, 6, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imFCC->getNeighbors(4, 5, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 8;
	imFCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imFCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imFCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);

	correctNNeighbors = 12;
	imFCC->getNeighbors(3, 5, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imFCC->getNeighbors(2, 3, 4, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC12ELER[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 4), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC12ELER[i]);
	}

	imFCC->getNeighbors(3, 2, 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC12ELOR[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 2), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC12ELOR[i]);
	}

	imFCC->getNeighbors(2, 3, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC12OLER[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC12OLER[i]);
	}

	imFCC->getNeighbors(3, 2, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC12OLOR[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC12OLOR[i]);
	}

	// 18 neighbors
	nNeighbors = 18;
	correctNNeighbors = 6;
	imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 8;
	imFCC->getNeighbors(4, 5, 6, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imFCC->getNeighbors(3, 5, 6, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imFCC->getNeighbors(4, 5, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 11;
	imFCC->getNeighbors(1, 0, 0, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imFCC->getNeighbors(0, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	imFCC->getNeighbors(1, 0, 1, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	correctNNeighbors = 15;
	imFCC->getNeighbors(3, 5, 5, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);

	correctNNeighbors = 17;
	imFCC->getNeighbors(3, 2, 2, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC18ELOR[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 2), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC18ELOR[i]);
	}

	imFCC->getNeighbors(3, 2, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC18OLOR[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(3, 2, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC18OLOR[i]);
	}

	correctNNeighbors = 18;
	imFCC->getNeighbors(2, 3, 4, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC18ELER[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 4), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC18ELER[i]);
	}

	imFCC->getNeighbors(2, 3, 3, nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC18OLER[i]);
	}
	imFCC->getNeighbors(imFCC->rclToIndex(2, 3, 3), nNeighbors, neighbors);
	returnedNeighbors = neighbors.size();
	BOOST_CHECK_EQUAL(returnedNeighbors, correctNNeighbors);
	for (int i = 0; i < returnedNeighbors; i++) {
		BOOST_CHECK_EQUAL(neighbors[i].getIndex(), FCC18OLER[i]);
	}

	// Exceptions
	nNeighbors = 12;
	BOOST_CHECK_THROW(imFCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, nC, 0, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, -1, 0, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, nL, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, -1, nNeighbors, neighbors),	outsideImageException);
	nNeighbors = 18;
	BOOST_CHECK_THROW(imFCC->getNeighbors(nR, 0, 0, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(-1, 0, 0, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, nC, 0, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, -1, 0, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, nL, nNeighbors, neighbors),	outsideImageException);
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, -1, nNeighbors, neighbors),	outsideImageException);
	nNeighbors = 6;
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 8;
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 14;
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 26;
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = -12;
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 0;
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);
	nNeighbors = 100;
	BOOST_CHECK_THROW(imFCC->getNeighbors(0, 0, 0, nNeighbors, neighbors), nNeighborsException);

	delete imFCC;
}

BOOST_AUTO_TEST_SUITE_END()

#endif
