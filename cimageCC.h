#ifndef CIMAGECC_H
#define CIMAGECC_H

#include <vector>
#include <iostream>
#include "defs.h"
#include "cimage.h"
#include "exception.h"
#include <cmath> // for round and pow
#include "neighbor.h"
#include "vectoroperators.h"

using namespace std;

namespace CImage {

const double subSpelDistanceCC[] = {0.732561001953818, 0.623694421783119, 0.574117314861196, 0.545268728828970, 0.522258720698669, 0.498729324394126, 0.480707859606576, 0.463058309432147, 0.447547529277453, 0.435059717244305, 0.421979035363776, 0.408772221380592, 0.397218274081152, 0.385408831485960, 0.371034869565175, 0.361626850445366, 0.353133590283520, 0.343685342443376, 0.333243454404165, 0.323842720287171, 0.315971391870786, 0.307344650439405, 0.299684705457515, 0.293155227880055, 0.283489987533105, 0.275961397146807, 0.269506713286797, 0.263202822971670, 0.256156669785891, 0.247577626759671, 0.237204981587119, 0.228948727770187, 0.222544617218361, 0.215783286864766, 0.211576281065243, 0.205299784658052, 0.198656799902412, 0.192562684545687, 0.184012838245001, 0.177640427838295, 0.169949935772603, 0.162649713746829, 0.157511308449056, 0.152682862291989, 0.143888663346916, 0.141342404753425, 0.139786927041494, 0.126969807990735, 0.117183303909957, 0.113489756302915, 0.109829594252491, 0.103392976131273, 0.094241949207657, 0.084322184704939, 0.076215849536726, 0.069930557887927, 0.064249817114914, 0.056120996514145, 0.049036822024338, 0.042203612739737, 0.034763114688529, 0.026654768012468, 0.021932503144634, 0.014911957875909, 0.006680036195622, -0.000562761929592, -0.005652822081754, -0.012546080795956, -0.020036935176039, -0.026178879796216, -0.031401706399816, -0.040408680802843, -0.045487588557626, -0.052706370720326, -0.059001198780690, -0.062091002272227, -0.072586785229022, -0.080657236944146, -0.087066875359926, -0.092979208280686, -0.099219654384174, -0.104018785849585, -0.115523864279216, -0.126057366702486, -0.131746142667347, -0.137413735687764, -0.143218451635786, -0.149561154785262, -0.156400628587445, -0.163581385067814, -0.171102831548518, -0.182654603631760, -0.190820776326902, -0.196813913548657, -0.203724211825539, -0.206488542749684, -0.213483246723245, -0.222245239721738, -0.229778356296238, -0.236939694152633, -0.242784795433991, -0.250554916306037, -0.258950658160991, -0.266840910974776, -0.277387788493246, -0.286304451774960, -0.292445258370560, -0.299081243599725, -0.309873043142970, -0.316216427403862, -0.326610620843017, -0.336890614104287, -0.345557276431350, -0.354894374354358, -0.367061546071091, -0.379432748009766, -0.390638253836092, -0.401630286245039, -0.417097495500319, -0.430449889421386, -0.442913278930958, -0.457713438299709, -0.479274915322158, -0.508435392312227, -0.533759096776991, -0.559184238862179, -0.602187829564287, -0.729122335558677};

/**
 * CImageCC:
 * A wrapper class for handling CC image data represented as a 1D array.
 *
 *//*
 *           .
 *         .
 *       .
 *     002 012 022 ...
 *   001 011 021 ...
 * 000 010 020 ...
 * 100
 * 200   ???
 * .
 * .
 * .
 */
template <class T>
class CImageCC : public CImage<T> {

public:
	CImageCC(T *d,int nr, int nc, int nl, int nb, double ev = 1) : CImage<T>(d, nr, nc, nl, nb, ev){
	}
	CImageCC() : CImage<T>(){
	}
	~CImageCC() {}

	/**
	 * Implements CImage::indexToX()
	 */
	double indexToX(int i) const {
		return this->scaleFactor * (this->indexToC(i) + 0.5);
	}

	/**
	 * Implements CImage::indexToY()
	 */
	double indexToY(int i) const {
		return this->scaleFactor * (this->indexToR(i) + 0.5);
	}

	/**
	 * Implements CImage::indexToZ()
	 */
	double indexToZ(int i) const {
		return this->scaleFactor * (this->indexToL(i) + 0.5);
	}

	/**
	 * Implements CImage::getWidth()
	 */
	double getWidth() const {
		return this->indexToX(0) + this->indexToX(this->rclToIndex(0,this->nColumns - 1,0));
	}

	/**
	 * Implements CImage::getHeight()
	 */
	double getHeight() const {
		return this->indexToY(0) + this->indexToY(this->rclToIndex(this->nRows - 1,0,0));
	}

	/**
	 * Implements CImage::getDepth()
	 */
	double getDepth() const {
		return this->indexToZ(0) + this->indexToZ(this->rclToIndex(0,0,this->nLayers - 1));
	}

	/**
	 * Implements CImage::internalDistanceVoronoiAverage
	 */
	double internalDistanceVoronoiAverage(uint8 coverage) const {
		return subSpelDistanceCC[coverage];
	}

	/**
	 * Implements CImage::internalDistanceVoronoiAverage
	 */
	double internalDistanceVoronoiAverage(double coverage) const {
		if (coverage < 0 || coverage > 1) {
					throw outsideRangeException();
		}
		uint8 convertedCoverage = round(coverage * 255);
		return internalDistanceVoronoiAverage(convertedCoverage);
	}

	/**
	 * Returns the face neighbors of the spel at \f$(r,c,l)\f$.
	 */
	void get6Neighbors(int r, int c, int l, vector<Neighbor> &neighbors) const {
		if(!this->isValid(r,c,l)){
			throw outsideImageException();
		}
		//cout << "Inside get6Neighbors (CC)." << endl;
//		vector<Neighbor> neighbors;
//		neighbors.reserve(6);
		neighbors.clear();
		if(this->isValid(r,c+1,l)){
			neighbors.push_back(Neighbor(0,this->rclToIndex(r,c+1,l))); //,CCd001)); //right
		}
		if(this->isValid(r,c-1,l)){
			neighbors.push_back(Neighbor(1,this->rclToIndex(r,c-1,l))); //,CCd001)); // left
		}
		if(this->isValid(r+1,c,l)){
			neighbors.push_back(Neighbor(2,this->rclToIndex(r+1,c,l))); //,CCd001)); // bottom
		}
		if(this->isValid(r-1,c,l)){
			neighbors.push_back(Neighbor(3,this->rclToIndex(r-1,c,l))); //,CCd001)); // top
		}
		if(this->isValid(r,c,l-1)){
			neighbors.push_back(Neighbor(4,this->rclToIndex(r,c,l-1))); //,CCd001)); // front
		}
		if(this->isValid(r,c,l+1)){
			neighbors.push_back(Neighbor(5,this->rclToIndex(r,c,l+1))); //,CCd001)); // back
		}
//		return neighbors;
	}

	/**
	 * Returns the face neighbors of the spel with index \f$(i)\f$.
	 */
	void get6Neighbors(int i, vector<Neighbor> &neighbors) const {
//		return get6Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
		get6Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
	}

	/**
	 * Returns the face- and edge neighbors of the spel at \f$(r,c,l)\f$.
	 */
	void get18Neighbors(int r, int c, int l, vector<Neighbor> &neighbors) const {
		if(!this->isValid(r,c,l)){
			throw outsideImageException();
		}
		//cout << "Inside get18Neighbors (CC)." << endl;
//		vector<Neighbor> neighbors;
//		neighbors.reserve(18);
//		neighbors = get6Neighbors(r,c,l);
		neighbors.clear();
		get6Neighbors(r,c,l,neighbors);
		if(this->isValid(r+1,c+1,l)){
			neighbors.push_back(Neighbor(6,this->rclToIndex(r+1,c+1,l))); //,CCd011)); // bottom right
		}
		if(this->isValid(r-1,c+1,l)){
			neighbors.push_back(Neighbor(7,this->rclToIndex(r-1,c+1,l))); //,CCd011)); // top right
		}
		if(this->isValid(r,c+1,l+1)){
			neighbors.push_back(Neighbor(8,this->rclToIndex(r,c+1,l+1))); //,CCd011)); // back right
		}
		if(this->isValid(r,c+1,l-1)){
			neighbors.push_back(Neighbor(9,this->rclToIndex(r,c+1,l-1))); //,CCd011)); // front right
		}
		if(this->isValid(r+1,c-1,l)){
			neighbors.push_back(Neighbor(10,this->rclToIndex(r+1,c-1,l))); //,CCd011)); // bottom left
		}
		if(this->isValid(r-1,c-1,l)){
			neighbors.push_back(Neighbor(11,this->rclToIndex(r-1,c-1,l))); //,CCd011)); // top left
		}
		if(this->isValid(r,c-1,l+1)){
			neighbors.push_back(Neighbor(12,this->rclToIndex(r,c-1,l+1))); //,CCd011)); // back left
		}
		if(this->isValid(r,c-1,l-1)){
			neighbors.push_back(Neighbor(13,this->rclToIndex(r,c-1,l-1))); //,CCd011)); // front left
		}
		if(this->isValid(r+1,c,l+1)){
			neighbors.push_back(Neighbor(14,this->rclToIndex(r+1,c,l+1))); //,CCd011)); // bottom back
		}
		if(this->isValid(r+1,c,l-1)){
			neighbors.push_back(Neighbor(15,this->rclToIndex(r+1,c,l-1))); //,CCd011)); // bottom front
		}
		if(this->isValid(r-1,c,l+1)){
			neighbors.push_back(Neighbor(16,this->rclToIndex(r-1,c,l+1))); //,CCd011)); // top back
		}
		if(this->isValid(r-1,c,l-1)){
			neighbors.push_back(Neighbor(17,this->rclToIndex(r-1,c,l-1))); //,CCd011)); // top front
		}
//		return result;
	}

	/**
	 * Returns the face- and edge neighbors of the spel with index \f$(i)\f$.
	 */
	void get18Neighbors(int i, vector<Neighbor> &neighbors) const {
//		return get18Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
		get18Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
	}

	/**
	 * Returns the face-, edge- and point neighbors of the spel at \f$(r,c,l)\f$.
	 */
	void get26Neighbors(int r, int c, int l, vector<Neighbor> &neighbors) const {
		if(!this->isValid(r,c,l)){
			throw outsideImageException();
		}
//		cout << "Inside get26Neighbors (CC)." << endl;
//		vector<Neighbor> neighbors;
//		neighbors.reserve(26);
//		neighbors = get18Neighbors(r,c,l);
		neighbors.clear();
		get18Neighbors(r,c,l,neighbors);
		if(this->isValid(r+1,c+1,l-1)){
			neighbors.push_back(Neighbor(18,this->rclToIndex(r+1,c+1,l-1))); //,CCd111)); // bottom front right
		}
		if(this->isValid(r-1,c+1,l-1)){
			neighbors.push_back(Neighbor(19,this->rclToIndex(r-1,c+1,l-1))); //,CCd111)); // top front right
		}
		if(this->isValid(r-1,c+1,l+1)){
			neighbors.push_back(Neighbor(20,this->rclToIndex(r-1,c+1,l+1))); //,CCd111)); // top back right
		}
		if(this->isValid(r+1,c+1,l+1)){
			neighbors.push_back(Neighbor(21,this->rclToIndex(r+1,c+1,l+1))); //,CCd111)); // bottom back right
		}
		if(this->isValid(r+1,c-1,l-1)){
			neighbors.push_back(Neighbor(22,this->rclToIndex(r+1,c-1,l-1))); //,CCd111)); // bottom front left
		}
		if(this->isValid(r-1,c-1,l-1)){
			neighbors.push_back(Neighbor(23,this->rclToIndex(r-1,c-1,l-1))); //,CCd111)); // top front left
		}
		if(this->isValid(r-1,c-1,l+1)){
			neighbors.push_back(Neighbor(24,this->rclToIndex(r-1,c-1,l+1))); //,CCd111)); // top back left
		}
		if(this->isValid(r+1,c-1,l+1)){
			neighbors.push_back(Neighbor(25,this->rclToIndex(r+1,c-1,l+1))); //,CCd111)); // bottom back left
		}
	//	return result;
	}

	/**
	 * Returns the face-, edge- and point neighbors of the spel with index \f$(i)\f$.
	 */
	void get26Neighbors(int i, vector<Neighbor> &neighbors) const {
//		return get26Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
		get26Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
	}

	/**
	 * Returns the neighbors within a \f5\times5\times5\f cube with its center at \f$(r,c,l)\f$.
	 */
	void get124Neighbors(int r, int c, int l, vector<Neighbor> &neighbors) const {
		if(!this->isValid(r,c,l)){
			throw outsideImageException();
		}
//		vector<Neighbor> result;
//		neighbors.reserve(124);
//		neighbors = get26Neighbors(r,c,l);
		get26Neighbors(r,c,l,neighbors);
		int i = 26;
		if(this->isValid(r,c+2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+2,l))); //,2*CCd001)); // right
		}
		i++;
		if(this->isValid(r+1,c+2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+2,l))); //,CCd012)); // left inner
		}
		i++;
		if(this->isValid(r-1,c+2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+2,l))); //,CCd012));
		}
		i++;
		if(this->isValid(r,c+2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+2,l+1))); //,CCd012));
		}
		i++;
		if(this->isValid(r,c+2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+2,l-1))); //,CCd012));
		}
		i++;
		if(this->isValid(r+1,c+2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+2,l+1))); //,CCd112));
		}
		i++;
		if(this->isValid(r+1,c+2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+2,l-1))); //,CCd112));
		}
		i++;
		if(this->isValid(r-1,c+2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+2,l+1))); //,CCd112));
		}
		i++;
		if(this->isValid(r-1,c+2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+2,l-1))); //,CCd112));
		}
		i++;

		if(this->isValid(r,c-2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-2,l))); //,2*CCd001)); // left
		}
		i++;
		if(this->isValid(r+1,c-2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-2,l))); //,CCd012)); // left inner
		}
		i++;
		if(this->isValid(r-1,c-2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-2,l))); //,CCd012));
		}
		i++;
		if(this->isValid(r,c-2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-2,l+1))); //,CCd012));
		}
		i++;
		if(this->isValid(r,c-2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-2,l-1))); //,CCd012));
		}
		i++;
		if(this->isValid(r+1,c-2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-2,l+1))); //,CCd112));
		}
		i++;
		if(this->isValid(r+1,c-2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-2,l-1))); //,CCd112));
		}
		i++;
		if(this->isValid(r-1,c-2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-2,l+1))); //,CCd112));
		}
		i++;
		if(this->isValid(r-1,c-2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-2,l-1))); //,CCd112));
		}
		i++;

		if(this->isValid(r+2,c,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c,l))); //,2*CCd001)); // bottom
		}
		i++;
		if(this->isValid(r+2,c+1,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+1,l))); //,CCd012)); // bottom inner
		}
		i++;
		if(this->isValid(r+2,c-1,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-1,l))); //,CCd012));
		}
		i++;
		if(this->isValid(r+2,c,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c,l+1))); //,CCd012));
		}
		i++;
		if(this->isValid(r+2,c,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c,l-1))); //,CCd012));
		}
		i++;
		if(this->isValid(r+2,c+1,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+1,l+1))); //,CCd112));
		}
		i++;
		if(this->isValid(r+2,c+1,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+1,l-1))); //,CCd112));
		}
		i++;
		if(this->isValid(r+2,c-1,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-1,l+1))); //,CCd112));
		}
		i++;
		if(this->isValid(r+2,c-1,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-1,l-1))); //,CCd112));
		}
		i++;

		if(this->isValid(r-2,c,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c,l))); //,2*CCd001)); // top
		}
		i++;
		if(this->isValid(r-2,c+1,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+1,l))); //,CCd012)); // top inner
		}
		i++;
		if(this->isValid(r-2,c-1,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-1,l))); //,CCd012));
		}
		i++;
		if(this->isValid(r-2,c,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c,l+1))); //,CCd012));
		}
		i++;
		if(this->isValid(r-2,c,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c,l-1))); //,CCd012));
		}
		i++;
		if(this->isValid(r-2,c+1,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+1,l+1))); //,CCd112));
		}
		i++;
		if(this->isValid(r-2,c+1,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+1,l-1))); //,CCd112));
		}
		i++;
		if(this->isValid(r-2,c-1,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-1,l+1))); //,CCd112));
		}
		i++;
		if(this->isValid(r-2,c-1,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-1,l-1))); //,CCd112));
		}
		i++;

		if(this->isValid(r,c,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c,l-2))); //,2*CCd001)); // front
		}
		i++;
		if(this->isValid(r+1,c,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c,l-2))); //,CCd012)); // front inner
		}
		i++;
		if(this->isValid(r-1,c,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c,l-2))); //,CCd012));
		}
		i++;
		if(this->isValid(r,c+1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+1,l-2))); //,CCd012));
		}
		i++;
		if(this->isValid(r,c-1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-1,l-2))); //,CCd012));
		}
		i++;
		if(this->isValid(r+1,c+1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+1,l-2))); //,CCd112));
		}
		i++;
		if(this->isValid(r+1,c-1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-1,l-2))); //,CCd112));
		}
		i++;
		if(this->isValid(r-1,c+1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+1,l-2))); //,CCd112));
		}
		i++;
		if(this->isValid(r-1,c-1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-1,l-2))); //,CCd112));
		}
		i++;

		if(this->isValid(r,c,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c,l+2))); //,2*CCd001)); // back
		}
		i++;
		if(this->isValid(r+1,c,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c,l+2))); //,CCd012)); // back inner
		}
		i++;
		if(this->isValid(r-1,c,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c,l+2))); //,CCd012));
		}
		i++;
		if(this->isValid(r,c+1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+1,l+2))); //,CCd012));
		}
		i++;
		if(this->isValid(r,c-1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-1,l+2))); //,CCd012));
		}
		i++;
		if(this->isValid(r+1,c+1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+1,l+2))); //,CCd112));
		}
		i++;
		if(this->isValid(r+1,c-1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-1,l+2))); //,CCd112));
		}
		i++;
		if(this->isValid(r-1,c+1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+1,l+2))); //,CCd112));
		}
		i++;
		if(this->isValid(r-1,c-1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-1,l+2))); //,CCd112));
		}
		i++;

		if(this->isValid(r+2,c+2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+2,l))); //,2*CCd011)); // bottom right
		}
		i++;
		if(this->isValid(r+2,c+2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+2,l+1))); //,CCd122));
		}
		i++;
		if(this->isValid(r+2,c+2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+2,l-1))); //,CCd122));
		}
		i++;

		if(this->isValid(r-2,c+2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+2,l))); //,2*CCd011)); // top right
		}
		i++;
		if(this->isValid(r-2,c+2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+2,l+1))); //,CCd122));
		}
		i++;
		if(this->isValid(r-2,c+2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+2,l-1))); //,CCd122));
		}
		i++;

		if(this->isValid(r,c+2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+2,l+2))); //,2*CCd011)); // back right
		}
		i++;
		if(this->isValid(r+1,c+2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+2,l+2))); //,CCd122));
		}
		i++;
		i++;
		if(this->isValid(r-1,c+2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+2,l+2))); //,CCd122));
		}
		i++;

		if(this->isValid(r,c+2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+2,l-2))); //,2*CCd011)); // front right
		}
		i++;
		if(this->isValid(r+1,c+2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+2,l-2))); //,CCd122));
		}
		i++;
		if(this->isValid(r-1,c+2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+2,l-2))); //,CCd122));
		}
		i++;

		if(this->isValid(r+2,c-2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-2,l))); //,2*CCd011)); // bottom left
		}
		i++;
		if(this->isValid(r+2,c-2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-2,l+1))); //,CCd122));
		}
		i++;
		if(this->isValid(r+2,c-2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-2,l-1))); //,CCd122));
		}
		i++;

		if(this->isValid(r-2,c-2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-2,l))); //,2*CCd011)); // top left
		}
		i++;
		if(this->isValid(r-2,c-2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-2,l+1))); //,CCd122));
		}
		i++;
		if(this->isValid(r-2,c-2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-2,l-1))); //,CCd122));
		}
		i++;

		if(this->isValid(r,c-2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-2,l+2))); //,2*CCd011)); // back left
		}
		i++;
		if(this->isValid(r+1,c-2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-2,l+2))); //,CCd122));
		}
		i++;
		if(this->isValid(r-1,c-2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-2,l+2))); //,CCd122));
		}
		i++;

		if(this->isValid(r,c-2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-2,l-2))); //,2*CCd011)); // front left
		}
		i++;
		if(this->isValid(r+1,c-2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-2,l-2))); //,CCd122));
		}
		i++;
		if(this->isValid(r-1,c-2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-2,l-2))); //,CCd122));
		}
		i++;

		if(this->isValid(r+2,c,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c,l+2))); //,2*CCd011)); // bottom back
		}
		i++;
		if(this->isValid(r+2,c+1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+1,l+2))); //,CCd122));
		}
		i++;
		if(this->isValid(r+2,c-1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-1,l+2))); //,CCd122));
		}
		i++;

		if(this->isValid(r+2,c,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c,l-2))); //,2*CCd011)); // bottom front
		}
		i++;
		if(this->isValid(r+2,c-1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+1,l-2))); //,CCd122));
		}
		i++;
		if(this->isValid(r+2,c+1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-1,l-2))); //,CCd122));
		}
		i++;

		if(this->isValid(r-2,c,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c,l+2))); //,2*CCd011)); // top back
		}
		i++;
		if(this->isValid(r-2,c+1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+1,l+2))); //,CCd122));
		}
		i++;
		if(this->isValid(r-2,c-1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-1,l+2))); //,CCd122));
		}
		i++;

		if(this->isValid(r-2,c,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c,l-2))); //,2*CCd011)); // top front
		}
		i++;
		if(this->isValid(r-2,c+1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+1,l-2))); //,CCd122));
		}
		i++;
		if(this->isValid(r-2,c-1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-1,l-2))); //,CCd122));
		}
		i++;

		if(this->isValid(r+2,c+2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+2,l-2))); //,2*CCd111)); // bottom front right
		}
		i++;
		if(this->isValid(r-2,c+2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+2,l-2))); //,2*CCd111)); // top front right
		}
		i++;
		if(this->isValid(r-2,c+2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+2,l+2))); //,2*CCd111)); // top back right
		}
		i++;
		if(this->isValid(r+2,c+2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+2,l+2))); //,2*CCd111)); // bottom back right
		}
		i++;
		if(this->isValid(r+2,c-2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-2,l-2))); //,2*CCd111)); // bottom front left
		}
		i++;
		if(this->isValid(r-2,c-2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-2,l-2))); //,2*CCd111)); // top front left
		}
		i++;
		if(this->isValid(r-2,c-2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-2,l+2))); //,2*CCd111)); // top back left
		}
		i++;
		if(this->isValid(r+2,c-2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-2,l+2))); //,2*CCd111)); // bottom back left
		}
//		return neighbors;
	}

	/**
	 * Returns the neighbors within a \f5\times5\times5\f cube with its center at \f$(r,c,l)\f$.
	 */
	void get124Neighbors(int i, vector<Neighbor> &neighbors) const {
//		return get124Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
		get124Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
	}

	/**
	 * Returns the neighbors within a \f7\times7\times7\f cube with its center at \f$(r,c,l)\f$.
	 */
	void get342Neighbors(int r, int c, int l, vector<Neighbor> &neighbors) const {
		if(!this->isValid(r,c,l)){
			throw outsideImageException();
		}
//		vector<Neighbor> result;
//		neighbors.reserve(342);
//		neighbors = get124Neighbors(r,c,l);
		get124Neighbors(r,c,l,neighbors);
		int i = 124;
		if(this->isValid(r,c+3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+3,l))); //,3*CCd001)); // right
		}
		i++;
		if(this->isValid(r+1,c+3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+3,l))); //,CCd013)); // right inner
		}
		i++;
		if(this->isValid(r-1,c+3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+3,l))); //,CCd013));
		}
		i++;
		if(this->isValid(r,c+3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+3,l+1))); //,CCd013));
		}
		i++;
		if(this->isValid(r,c+3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+3,l-1))); //,CCd013));
		}
		i++;
		if(this->isValid(r+1,c+3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+3,l+1))); //,CCd113));
		}
		i++;
		if(this->isValid(r+1,c+3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+3,l-1))); //,CCd113));
		}
		i++;
		if(this->isValid(r-1,c+3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+3,l+1))); //,CCd113));
		}
		i++;
		if(this->isValid(r-1,c+3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+3,l-1))); //,CCd113));
		}
		i++;
		if(this->isValid(r+2,c+3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+3,l))); //,CCd023)); // right middle
		}
		i++;
		if(this->isValid(r-2,c+3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+3,l))); //,CCd023));
		}
		i++;
		if(this->isValid(r,c+3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+3,l+2))); //,CCd023));
		}
		i++;
		if(this->isValid(r,c+3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+3,l-2))); //,CCd023));
		}
		i++;
		if(this->isValid(r+2,c+3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+3,l+1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-2,c+3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+3,l+1))); //,CCd123));
		}
		i++;
		if(this->isValid(r+1,c+3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+3,l+2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+1,c+3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+3,l-2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+2,c+3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+3,l-1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-2,c+3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+3,l-1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-1,c+3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+3,l+2))); //,CCd123));
		}
		i++;
		if(this->isValid(r-1,c+3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+3,l-2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+2,c+3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+3,l+2))); //,CCd223));
		}
		i++;
		if(this->isValid(r+2,c+3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+3,l-2))); //,CCd223));
		}
		i++;
		if(this->isValid(r-2,c+3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+3,l+2))); //,CCd223));
		}
		i++;
		if(this->isValid(r-2,c+3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+3,l-2))); //,CCd223));
		}
		i++;

		if(this->isValid(r,c-3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-3,l))); //,3*CCd001)); // left
		}
		i++;
		if(this->isValid(r+1,c-3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-3,l))); //,CCd013)); // left inner
		}
		i++;
		if(this->isValid(r-1,c-3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-3,l))); //,CCd013));
		}
		i++;
		if(this->isValid(r,c-3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-3,l+1))); //,CCd013));
		}
		i++;
		if(this->isValid(r,c-3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-3,l-1))); //,CCd013));
		}
		i++;
		if(this->isValid(r+1,c-3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-3,l+1))); //,CCd113));
		}
		i++;
		if(this->isValid(r+1,c-3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-3,l-1))); //,CCd113));
		}
		i++;
		if(this->isValid(r-1,c-3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-3,l+1))); //,CCd113));
		}
		i++;
		if(this->isValid(r-1,c-3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-3,l-1))); //,CCd113));
		}
		i++;
		if(this->isValid(r+2,c-3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-3,l))); //,CCd023)); // left middle
		}
		i++;
		if(this->isValid(r-2,c-3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-3,l))); //,CCd023));
		}
		i++;
		if(this->isValid(r,c-3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-3,l+2))); //,CCd023));
		}
		i++;
		if(this->isValid(r,c-3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-3,l-2))); //,CCd023));
		}
		i++;
		if(this->isValid(r+2,c-3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-3,l+1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-2,c-3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-3,l+1))); //,CCd123));
		}
		i++;
		if(this->isValid(r+1,c-3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-3,l+2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+1,c-3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-3,l-2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+2,c-3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-3,l-1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-2,c-3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-3,l-1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-1,c-3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-3,l+2))); //,CCd123));
		}
		i++;
		if(this->isValid(r-1,c-3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-3,l-2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+2,c-3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-3,l+2))); //,CCd223));
		}
		i++;
		if(this->isValid(r+2,c-3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-3,l-2))); //,CCd223));
		}
		i++;
		if(this->isValid(r-2,c-3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-3,l+2))); //,CCd223));
		}
		i++;
		if(this->isValid(r-2,c-3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-3,l-2))); //,CCd223));
		}
		i++;

		if(this->isValid(r+3,c,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c,l))); //,3*CCd001)); // bottom
		}
		i++;
		if(this->isValid(r+3,c+1,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+1,l))); //,CCd013)); // bottom inner
		}
		i++;
		if(this->isValid(r+3,c-1,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-1,l))); //,CCd013));
		}
		i++;
		if(this->isValid(r+3,c,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c,l+1))); //,CCd013));
		}
		i++;
		if(this->isValid(r+3,c,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c,l-1))); //,CCd013));
		}
		i++;
		if(this->isValid(r+3,c+1,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+1,l+1))); //,CCd113));
		}
		i++;
		if(this->isValid(r+3,c+1,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+1,l-1))); //,CCd113));
		}
		i++;
		if(this->isValid(r+3,c-1,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-1,l+1))); //,CCd113));
		}
		i++;
		if(this->isValid(r+3,c-1,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-1,l-1))); //,CCd113));
		}
		i++;
		if(this->isValid(r+3,c+2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+2,l))); //,CCd023)); // bottom middle
		}
		i++;
		if(this->isValid(r+3,c-2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-2,l))); //,CCd023));
		}
		i++;
		if(this->isValid(r+3,c,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c,l+2))); //,CCd023));
		}
		i++;
		if(this->isValid(r+3,c,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c,l-2))); //,CCd023));
		}
		i++;
		if(this->isValid(r+3,c+2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+2,l+1))); //,CCd123));
		}
		i++;
		if(this->isValid(r+3,c-2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-2,l+1))); //,CCd123));
		}
		i++;
		if(this->isValid(r+3,c+1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+1,l+2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+3,c+1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+1,l-2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+3,c+2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+2,l-1))); //,CCd123));
		}
		i++;
		if(this->isValid(r+3,c-2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-2,l-1))); //,CCd123));
		}
		i++;
		if(this->isValid(r+3,c-1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-1,l+2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+3,c-1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-1,l-2))); //,CCd123));
		}
		i++;
		if(this->isValid(r+3,c+2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+2,l+2))); //,CCd223));
		}
		i++;
		if(this->isValid(r+3,c+2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+2,l-2))); //,CCd223));
		}
		i++;
		if(this->isValid(r+3,c-2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-2,l+2))); //,CCd223));
		}
		i++;
		if(this->isValid(r+3,c-2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-2,l-2))); //,CCd223));
		}
		i++;

		if(this->isValid(r-3,c,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c,l))); //,3*CCd001)); // top
		}
		i++;
		if(this->isValid(r-3,c+1,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+1,l))); //,CCd013)); // top inner
		}
		i++;
		if(this->isValid(r-3,c-1,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-1,l))); //,CCd013));
		}
		i++;
		if(this->isValid(r-3,c,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c,l+1))); //,CCd013));
		}
		i++;
		if(this->isValid(r-3,c,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c,l-1))); //,CCd013));
		}
		i++;
		if(this->isValid(r-3,c+1,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+1,l+1))); //,CCd113));
		}
		i++;
		if(this->isValid(r-3,c+1,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+1,l-1))); //,CCd113));
		}
		i++;
		if(this->isValid(r-3,c-1,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-1,l+1))); //,CCd113));
		}
		i++;
		if(this->isValid(r-3,c-1,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-1,l-1))); //,CCd113));
		}
		i++;
		if(this->isValid(r-3,c+2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+2,l))); //,CCd023)); // top middle
		}
		i++;
		if(this->isValid(r-3,c-2,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-2,l))); //,CCd023));
		}
		i++;
		if(this->isValid(r-3,c,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c,l+2))); //,CCd023));
		}
		i++;
		if(this->isValid(r-3,c,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c,l-2))); //,CCd023));
		}
		i++;
		if(this->isValid(r-3,c+2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+2,l+1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-3,c-2,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-2,l+1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-3,c+1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+1,l+2))); //,CCd123));
		}
		i++;
		if(this->isValid(r-3,c+1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+1,l-2))); //,CCd123));
		}
		i++;
		if(this->isValid(r-3,c+2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+2,l-1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-3,c-2,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-2,l-1))); //,CCd123));
		}
		i++;
		if(this->isValid(r-3,c-1,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-1,l+2))); //,CCd123));
		}
		i++;
		if(this->isValid(r-3,c-1,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-1,l-2))); //,CCd123));
		}
		i++;
		if(this->isValid(r-3,c+2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+2,l+2))); //,CCd223));
		}
		i++;
		if(this->isValid(r-3,c+2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+2,l-2))); //,CCd223));
		}
		i++;
		if(this->isValid(r-3,c-2,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-2,l+2))); //,CCd223));
		}
		i++;
		if(this->isValid(r-3,c-2,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-2,l-2))); //CCd223));
		}
		i++;

		if(this->isValid(r,c,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c,l-3))); //,3*CCd001)); // front
		}
		i++;
		if(this->isValid(r+1,c,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c,l-3))); //,CCd013)); // front inner
		}
		i++;
		if(this->isValid(r-1,c,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c,l-3))); //,CCd013));
		}
		i++;
		if(this->isValid(r,c+1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+1,l-3))); //,CCd013));
		}
		i++;
		if(this->isValid(r,c-1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-1,l-3))); //,CCd013));
		}
		i++;
		if(this->isValid(r+1,c+1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+1,l-3))); //,CCd113));
		}
		i++;
		if(this->isValid(r+1,c-1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-1,l-3))); //,CCd113));
		}
		i++;
		if(this->isValid(r-1,c+1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+1,l-3))); //,CCd113));
		}
		i++;
		if(this->isValid(r-1,c-1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-1,l-3))); //,CCd113));
		}
		i++;
		if(this->isValid(r+2,c,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c,l-3))); //,CCd023)); // front middle
		}
		i++;
		if(this->isValid(r-2,c,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c,l-3))); //,CCd023));
		}
		i++;
		if(this->isValid(r,c+2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+2,l-3))); //,CCd023));
		}
		i++;
		if(this->isValid(r,c-2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-2,l-3))); //,CCd023));
		}
		i++;
		if(this->isValid(r+2,c+1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+1,l-3))); //,CCd123));
		}
		i++;
		if(this->isValid(r-2,c+1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+1,l-3))); //,CCd123));
		}
		i++;
		if(this->isValid(r+1,c+2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+2,l-3))); //,CCd123));
		}
		i++;
		if(this->isValid(r+1,c-2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-2,l-3))); //,CCd123));
		}
		i++;
		if(this->isValid(r+2,c-1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-1,l-3))); //,CCd123));
		}
		i++;
		if(this->isValid(r-2,c-1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-1,l-3))); //,CCd123));
		}
		i++;
		if(this->isValid(r-1,c+2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+2,l-3))); //,CCd123));
		}
		i++;
		if(this->isValid(r-1,c-2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-2,l-3))); //,CCd123));
		}
		i++;
		if(this->isValid(r+2,c+2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+2,l-3))); //,CCd223));
		}
		i++;
		if(this->isValid(r+2,c-2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-2,l-3))); //,CCd223));
		}
		i++;
		if(this->isValid(r-2,c+2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+2,l-3))); //,CCd223));
		}
		i++;
		if(this->isValid(r-2,c-2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-2,l-3))); //,CCd223));
		}
		i++;

		if(this->isValid(r,c,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c,l+3))); //,3*CCd001)); // back
		}
		i++;
		if(this->isValid(r+1,c,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c,l+3))); //,CCd013)); // back inner
		}
		i++;
		if(this->isValid(r-1,c,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c,l+3))); //,CCd013));
		}
		i++;
		if(this->isValid(r,c+1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+1,l+3))); //,CCd013));
		}
		i++;
		if(this->isValid(r,c-1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-1,l+3))); //,CCd013));
		}
		i++;
		if(this->isValid(r+1,c+1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+1,l+3))); //,CCd113));
		}
		i++;
		if(this->isValid(r+1,c-1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-1,l+3))); //,CCd113));
		}
		i++;
		if(this->isValid(r-1,c+1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+1,l+3))); //,CCd113));
		}
		i++;
		if(this->isValid(r-1,c-1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-1,l+3))); //,CCd113));
		}
		i++;
		if(this->isValid(r+2,c,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c,l+3))); //,CCd023)); // back middle
		}
		i++;
		if(this->isValid(r-2,c,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c,l+3))); //,CCd023));
		}
		i++;
		if(this->isValid(r,c+2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+2,l+3))); //,CCd023));
		}
		i++;
		if(this->isValid(r,c-2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-2,l+3))); //,CCd023));
		}
		i++;
		if(this->isValid(r+2,c+1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+1,l+3))); //,CCd123));
		}
		i++;
		if(this->isValid(r-2,c+1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+1,l+3))); //,CCd123));
		}
		i++;
		if(this->isValid(r+1,c+2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+2,l+3))); //,CCd123));
		}
		i++;
		if(this->isValid(r+1,c-2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-2,l+3))); //,CCd123));
		}
		i++;
		if(this->isValid(r+2,c-1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-1,l+3))); //,CCd123));
		}
		i++;
		if(this->isValid(r-2,c-1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-1,l+3))); //,CCd123));
		}
		i++;
		if(this->isValid(r-1,c+2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+2,l+3))); //,CCd123));
		}
		i++;
		if(this->isValid(r-1,c-2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-2,l+3))); //,CCd123));
		}
		i++;
		if(this->isValid(r+2,c+2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+2,l+3))); //,CCd223));
		}
		i++;
		if(this->isValid(r+2,c-2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-2,l+3))); //,CCd223));
		}
		i++;
		if(this->isValid(r-2,c+2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+2,l+3))); //,CCd223));
		}
		i++;
		if(this->isValid(r-2,c-2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-2,l+3))); //,CCd223));
		}
		i++;

		if(this->isValid(r+3,c+3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+3,l))); //,3*CCd011)); // bottom right
		}
		i++;
		if(this->isValid(r+3,c+3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+3,l+1))); //,CCd133));
		}
		i++;
		if(this->isValid(r+3,c+3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+3,l-1))); //,CCd133));
		}
		i++;
		if(this->isValid(r+3,c+3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+3,l+2))); //,CCd233));
		}
		i++;
		if(this->isValid(r+3,c+3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+3,l-2))); //,CCd233));
		}
		i++;

		if(this->isValid(r-3,c+3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+3,l))); //,2*CCd011)); // top right
		}
		i++;
		if(this->isValid(r-3,c+3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+3,l+1))); //,CCd133));
		}
		i++;
		if(this->isValid(r-3,c+3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+3,l-1))); //,CCd133));
		}
		i++;
		if(this->isValid(r-3,c+3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+3,l+2))); //,CCd233));
		}
		i++;
		if(this->isValid(r-3,c+3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+3,l-2))); //,CCd233));
		}
		i++;

		if(this->isValid(r,c+3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+3,l+3))); //,3*CCd011)); // back right
		}
		i++;
		if(this->isValid(r+1,c+3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+3,l+3))); //,CCd133));
		}
		i++;
		if(this->isValid(r-1,c+3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+3,l+3))); //,CCd133));
		}
		i++;
		if(this->isValid(r+2,c+3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+3,l+3))); //,CCd233));
		}
		i++;
		if(this->isValid(r-2,c+3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+3,l+3))); //,CCd233));
		}
		i++;

		if(this->isValid(r,c+3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c+3,l-3))); //,3*CCd011)); // front right
		}
		i++;
		if(this->isValid(r+1,c+3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c+3,l-3))); //,CCd133));
		}
		i++;
		if(this->isValid(r-1,c+3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c+3,l-3))); //,CCd133));
		}
		i++;
		if(this->isValid(r+2,c+3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c+3,l-3))); //,CCd233));
		}
		i++;
		if(this->isValid(r-2,c+3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c+3,l-3))); //,CCd233));
		}
		i++;

		if(this->isValid(r+3,c-3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-3,l))); //,3*CCd011)); // bottom left
		}
		i++;
		if(this->isValid(r+3,c-3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-3,l+1))); //,CCd133));
		}
		i++;
		if(this->isValid(r+3,c-3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-3,l-1))); //,CCd133));
		}
		i++;
		if(this->isValid(r+3,c-3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-3,l+2))); //,CCd233));
		}
		i++;
		if(this->isValid(r+3,c-3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-3,l-2))); //,CCd233));
		}
		i++;

		if(this->isValid(r-3,c-3,l)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-3,l))); //,2*CCd011)); // top left
		}
		i++;
		if(this->isValid(r-3,c-3,l+1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-3,l+1))); //,CCd133));
		}
		i++;
		if(this->isValid(r-3,c-3,l-1)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-3,l-1))); //,CCd133));
		}
		i++;
		if(this->isValid(r-3,c-3,l+2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-3,l+2))); //,CCd233));
		}
		i++;
		if(this->isValid(r-3,c-3,l-2)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-3,l-2))); //,CCd233));
		}
		i++;

		if(this->isValid(r,c-3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-3,l+3))); //,3*CCd011)); // back left
		}
		i++;
		if(this->isValid(r+1,c-3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-3,l+3))); //,CCd133));
		}
		i++;
		if(this->isValid(r-1,c-3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-3,l+3))); //,CCd133));
		}
		i++;
		if(this->isValid(r+2,c-3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-3,l+3))); //,CCd233));
		}
		i++;
		if(this->isValid(r-2,c-3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-3,l+3))); //,CCd233));
		}
		i++;

		if(this->isValid(r,c-3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r,c-3,l-3))); //,3*CCd011)); // front left
		}
		i++;
		if(this->isValid(r+1,c-3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+1,c-3,l-3))); //,CCd133));
		}
		i++;
		if(this->isValid(r-1,c-3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-1,c-3,l-3))); //,CCd133));
		}
		i++;
		if(this->isValid(r+2,c-3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+2,c-3,l-3))); //,CCd233));
		}
		i++;
		if(this->isValid(r-2,c-3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-2,c-3,l-3))); //,CCd233));
		}
		i++;

		if(this->isValid(r+3,c,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c,l+3))); //,3*CCd011)); // bottom back
		}
		i++;
		if(this->isValid(r+3,c+1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+1,l+3))); //,CCd133));
		}
		i++;
		if(this->isValid(r+3,c-1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-1,l+3))); //,CCd133));
		}
		i++;
		if(this->isValid(r+3,c+2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+2,l+3))); //,CCd233));
		}
		i++;
		if(this->isValid(r+3,c-2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-2,l+3))); //,CCd233));
		}
		i++;

		if(this->isValid(r+3,c,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c,l-3))); //,3*CCd011)); // bottom front
		}
		i++;
		if(this->isValid(r+3,c+1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+1,l-3))); //,CCd133));
		}
		i++;
		if(this->isValid(r+3,c-1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-1,l-3))); //,CCd133));
		}
		i++;
		if(this->isValid(r+3,c+2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+2,l-3))); //,CCd233));
		}
		i++;
		if(this->isValid(r+3,c-2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-2,l-3))); //,CCd233));
		}
		i++;

		if(this->isValid(r-3,c,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c,l+3))); //,3*CCd011)); // top back
		}
		i++;
		if(this->isValid(r-3,c+1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+1,l+3))); //,CCd133));
		}
		i++;
		if(this->isValid(r-3,c-1,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-1,l+3))); //,CCd133));
		}
		i++;
		if(this->isValid(r-3,c+2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+2,l+3))); //,CCd233));
		}
		i++;
		if(this->isValid(r-3,c-2,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-2,l+3))); //,CCd233));
		}
		i++;

		if(this->isValid(r-3,c,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c,l-3))); //,3*CCd011)); // top front
		}
		i++;
		if(this->isValid(r-3,c+1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+1,l-3))); //,CCd133));
		}
		i++;
		if(this->isValid(r-3,c-1,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-1,l-3))); //,CCd133));
		}
		i++;
		if(this->isValid(r-3,c+2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+2,l-3))); //,CCd233));
		}
		i++;
		if(this->isValid(r-3,c-2,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-2,l-3))); //,CCd233));
		}
		i++;

		if(this->isValid(r+3,c+3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+3,l-3))); //,3*CCd111)); // bottom front right
		}
		i++;
		if(this->isValid(r-3,c+3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+3,l-3))); //,3*CCd111)); // top front right
		}
		i++;
		if(this->isValid(r-3,c+3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c+3,l+3))); //,3*CCd111)); // top back right
		}
		i++;
		if(this->isValid(r+3,c+3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c+3,l+3))); //,3*CCd111)); // bottom back right
		}
		i++;
		if(this->isValid(r+3,c-3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-3,l-3))); //,3*CCd111)); // bottom front left
		}
		i++;
		if(this->isValid(r-3,c-3,l-3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-3,l-3))); //,3*CCd111)); // top front left
		}
		i++;
		if(this->isValid(r-3,c-3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r-3,c-3,l+3))); //,3*CCd111)); // top back left
		}
		i++;
		if(this->isValid(r+3,c-3,l+3)){
			neighbors.push_back(Neighbor(i,this->rclToIndex(r+3,c-3,l+3))); //,3*CCd111)); // bottom back left
		}

//		return neighbors;
	}

	/**
	 * Returns the neighbors within a \f5\times5\times5\f cube with its center at \f$(r,c,l)\f$.
	 */
	void get342Neighbors(int i, vector<Neighbor> &neighbors) const {
//		return get342Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
		get342Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
	}

	/**
	 * Returns the specified neighborhood of the spel at \f$(r,c,l)\f$:
	 *
	 * N  | neighbors
	 * -: | :---------
	 * 6  | face
	 * 18 | face, edge
	 * 26 | face, edge, point
	 */
	void getNeighbors(int r, int c, int l, int N, vector<Neighbor> &neighbors) const {
		//		cout << "Inside getNeighbors (CC)." << endl;
		switch (N){
		case 6:
//			return get6Neighbors(r, c, l);
			get6Neighbors(r, c, l, neighbors);
			break;
		case 18:
//			return get18Neighbors(r, c, l);
			get18Neighbors(r, c, l, neighbors);
			break;
		case 26:
//			return get26Neighbors(r, c, l);
			get26Neighbors(r, c, l, neighbors);
			break;
		case 124:
//			return get124Neighbors(r, c, l);
			get124Neighbors(r, c, l, neighbors);
			break;
		case 342:
//			return get342Neighbors(r, c, l);
			get342Neighbors(r, c, l, neighbors);
			break;
		default:
			throw nNeighborsException();
		}
	}

	/**
	 * Returns the specified neighborhood of the spel with index \f$(i)\f$:
	 *
	 * N   | neighbors
	 * --: | :---------
	 * 6   | face
	 * 18  | face, edge
	 * 26  | face, edge, point
	 * 124 | 5*5*5
	 * 342 | 7*7*7
	 */
	void getNeighbors(int i, int N, vector<Neighbor> &neighbors) const {
		//		cout << "Inside getNeighbors (CC)." << endl;
		switch (N){
		case 6:
			//			return get6Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
			get6Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
			break;
		case 18:
			//	return get18Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
			get18Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
			break;
		case 26:
			//	return get26Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
			get26Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
			break;
		case 124:
			//	return get124Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
			get124Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
			break;
		case 342:
			//	return get342Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
			get342Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
			break;
		default:
			throw nNeighborsException();
		}
	}

	/**
	 * Implements CImage::downsample(const CImage<T>* original, double newSpelVolume, T* data)
	 */
	T* downsample(const CImage<T>* original, double newSpelVolume) {

		// high resolution image parameters
		double oldWidth = original->getWidth();
		double oldHeight = original->getHeight();
		double oldDepth = original->getDepth();
		int oldNElements = original->getNElements();
		int nBands = original->getNBands();

		// low resolution image parameters
		double newScaleFactor = cbrt(newSpelVolume);
		int newNRows = floor(oldHeight/newScaleFactor);
		int newNColumns = floor(oldWidth/newScaleFactor);
		int newNLayers = floor(oldDepth/newScaleFactor);
		int newNElements = newNRows * newNColumns * newNLayers;
		this->nRows = newNRows;
		this->nColumns = newNColumns;
		this->nLayers = newNLayers;
		this->nElements = newNElements;
		this->nBands = nBands;
        this->scaleFactor = newScaleFactor;
		this->data = new T[newNElements * nBands];
        if(!this->data) {
            throw nullPointerException();
        }
        double newWidth = this->getWidth();
		double newHeight = this->getHeight();
		double newDepth = this->getDepth();

		vector<Neighbor> neighbors;
		int nNeighbors, nSubSpels;
		vector<double> newIntensity, newLocation, oldLocation, neighborLocation;
		vector< vector<double> > newNeighborLocations;
		double squaredDistanceToCurrent, squaredDistanceToNeighbor, volumeFactor;
		bool inside;
		for (int newE = 0; newE < newNElements; newE++) {
			nSubSpels = 0;
			newIntensity.assign(nBands,0.0);
			this->getCoordinates(newE,newLocation);
			this->getNeighbors(newE, 6, neighbors); // enough, since the six closest neighbors define the Voronoi cell
			nNeighbors = neighbors.size();
			newNeighborLocations.clear();
			for (int n = 0; n < nNeighbors; n++) {
				this->getCoordinates(neighbors[n].getIndex(),neighborLocation);
				newNeighborLocations.push_back(neighborLocation);
			}
			for (int oldE = 0; oldE < oldNElements; oldE++) { // Should be optimized to some search area!!
				original->getCoordinates(oldE,oldLocation);
				squaredDistanceToCurrent = 0;
				for (int i = 0; i < 3; i++) {
					squaredDistanceToCurrent = squaredDistanceToCurrent + (newLocation[i] - oldLocation[i]) * (newLocation[i] - oldLocation[i]);
				}
				inside = true;
				for (int n = 0; (n < nNeighbors) && inside; n++) {
                    squaredDistanceToNeighbor = 0;
					for (int i = 0; i < 3; i++) {
						squaredDistanceToNeighbor = squaredDistanceToNeighbor + (newNeighborLocations[n][i] - oldLocation[i]) * (newNeighborLocations[n][i] - oldLocation[i]);
					}
					if (squaredDistanceToNeighbor < squaredDistanceToCurrent) {
						inside = false;
					}
				}
				if (inside) {
					newIntensity = newIntensity + (*original)[oldE];
					nSubSpels++;
				}
			}
            volumeFactor = 1.0 / double(nSubSpels);
			this->setElement(newE, (volumeFactor * newIntensity));
		}
        return this->data;
	}

	/**
	 * Pads the input vector with values for the missing neighbors by adding
	 * dummy neighbors. The dummy neighbor contains the index of a nearby spel
	 * (for example another neighbor) with an intensity value that may
	 * substitute the missing value, based on the input flag. Zero padding
	 * does not add any dummy neighbors, and is supported only to provide a
	 * convenient interface for the calling function.
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * index		|			| center spel index
	 * nN			| 			| neighborhood size
	 * padding		|			| Flag to determine type of padding
	 * 				|			|	0: zero padding
	 * 				|			|	1: nearest neighbor
	 * 				|			|	2: mirror
	 * neighbors	| IN/OUT	| vector of existing neighbors, to be padded
	 */
void padNeighborhood(int index, int nSize, int padding, vector<Neighbor> &neighbors) {
/*
		if (!this->isValid(index)){
			throw outsideImageException();
		}

		if ((nSize != 6) && (nSize != 18) && (nSize != 26)) {
			throw outsideRangeException();
		}

		if (getNLayers() == 1) {
			//padNeighborhood2D(index, nSize, padding, neighbors);
		}

		int nPresent = neighbors.size();
		int currentLoc = 0;
		int substituteIndex, r, c, l, substituteLoc;

		switch (padding) {
		case 0: // zero padding
			break;
		case 1: // nearest neighbor
			// This does not work for 2D-images!!!
			for (int n = 0; n < nSize; n++) {
				if (neighbors[n].getLocation() == currentLoc) { // neighbor is present
					currentLoc++;
				}
				else { // neighbor is missing
					// find proper index
					substituteLoc = mirrorCC[currentLoc];
					substituteIndex = -1;
					for (int p = 0; p < nPresent; p++) {
						if (neighbors[p].getLocation() == substituteLoc) {
							substituteIndex = neighbors[p].getIndex();
						}
					}
					if (substituteIndex != -1) {
						neighbors.insert(neighbors.begin() + currentLoc,Neighbor(currentLoc, substituteIndex, 0));
					}
					else {
						// This should not happen. Throw something.
					}
				}
			}
			break;
		case 2: // mirror
			for (int n = 0; n < nSize; n++) {
				if (neighbors[n].getLocation() == currentLoc) { // neighbor is present
					currentLoc++;
				}
				else { // neighbor is missing
					// find proper index
					neighbors.insert(neighbors.begin() + currentLoc,Neighbor(currentLoc, substituteIndex, 0));
				}
			}
			break;
		default:
			throw outsideRangeException();
		}
		*/
	}



};

typedef CImageCC<uint8> CImagetypeCC;

}

#endif
