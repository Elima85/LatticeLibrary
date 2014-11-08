#ifndef IMAGEFCC_H
#define IMAGEFCC_H

#include <vector>
#include <iostream>
#include <cmath>  // for cbrt and round
#include "cimage.h"
#include "exception.h"
#include "defs.h"
#include "neighbor.h"
#include "miscellaneous.h"
#include "vectoroperators.h"
using namespace std;

namespace CImage {

// neighbor distances
#define FCCOFFSET 0.793700525984100 // 1/(2^(1/3)), distance between layers in FCC
#define FCCFACEDISTANCE 1.122462048309373 // face neighbor distance
#define FCCPOINTDISTANCE 1.587401051968199 // 2/(2^(1/3)), point neighbor distance
const double subSpelDistanceFCC[] = {0.714077046326529, 0.584803910742471, 0.539549351387385, 0.514827152974004, 0.494182137726088, 0.474779246135581, 0.457429195670903, 0.444857955564193, 0.432049156262755, 0.416457896497643, 0.406295118688379, 0.395099247457030, 0.383984914266236, 0.373939520778821, 0.365127204667108, 0.354809540369391, 0.344742627461438, 0.335591156334671, 0.326989274134147, 0.317776359547039, 0.307758730036562, 0.297990203600959, 0.289601501302384, 0.282373570385305, 0.274091628675670, 0.265677476283618, 0.257639748014919, 0.249811259480845, 0.241931405009107, 0.234613601807503, 0.226629910710280, 0.218426567840259, 0.210969972072138, 0.204970597016393, 0.198200540088346, 0.190695890815276, 0.182793900838194, 0.175633893526011, 0.170742902343941, 0.162768805584692, 0.156227685808754, 0.151008107616109, 0.145752745772041, 0.139159470809782, 0.131352246116331, 0.124123023669870, 0.117882609641882, 0.112013962417163, 0.105179520511002, 0.098065042076195, 0.090231585203651, 0.083009647739121, 0.078744449568174, 0.068700177909267, 0.061433745479717, 0.055568374014679, 0.048991541832693, 0.042445590781161, 0.034485090405223, 0.027694335480268, 0.021722076617656, 0.015428180841809, 0.010236512587796, 0.003707371875781, -0.003630851925319, -0.010631573445721, -0.016410970291770, -0.023322622799315, -0.028825749810292, -0.034732814119153, -0.042002255077926, -0.048067280463827, -0.055747223920438, -0.062483286304572, -0.068408121666749, -0.074493907320462, -0.081306297387967, -0.088382396840916, -0.096162589794095, -0.104260062680029, -0.111686279510446, -0.118634581261823, -0.125211426614980, -0.131617741383244, -0.138195415529015, -0.145384226245301, -0.149171106862121, -0.155255401999289, -0.163796132921106, -0.172131726206582, -0.178992083695221, -0.186852374100716, -0.193109335183382, -0.199360097653993, -0.208887666498899, -0.216334847227242, -0.222520382851360, -0.229712301302484, -0.238404293937451, -0.246180071162991, -0.251547526818121, -0.259023433738466, -0.268319052135775, -0.277427580468557, -0.285128086314985, -0.293499153982363, -0.300869506924703, -0.309212407534078, -0.320907601467231, -0.328155731251493, -0.336715699297306, -0.345794247700394, -0.355579894093477, -0.367494153207715, -0.378436472328643, -0.387858147892052, -0.396477352246857, -0.405475042921039, -0.416825667569806, -0.431295712646092, -0.446430380869664, -0.462255639266114, -0.479204286758705, -0.494706543978469, -0.511852029543659, -0.534751990156574, -0.581183711707067, -0.719465948707445};


/*
 * image_FCC:
 * A wrapper class for handling FCC image data represented as a 1D array.
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
class CImageFCC : public CImage<T> {

public:
	// Constructor
	CImageFCC(T *d,int nr, int nc, int nl, int nb, double ev = 1) : CImage<T>(d, nr, nc, nl, nb, ev){
	}
	CImageFCC() : CImage<T>(){
	}
	~CImageFCC() {}

	// Get coordinates
	/**
	 * Implements CImage::indexToX()
	 */
	double indexToX(int i) const {
		int r,c,l;
		double x;
		r = this->indexToR(i);
		c = this->indexToC(i);
		l = this->indexToL(i);
		//x = c * FCCPOINTDISTANCE + (1 - isEven(l+r)) * FCCOFFSET;
		x = this->scaleFactor * ((1 + !isEven(l + r)) * FCCOFFSET + c * FCCPOINTDISTANCE);
		return x;
	}

	/**
	 * Implements CImage::indexToY()
	 */
	double indexToY(int i) const {
		int r;
		double y;
		r = this->indexToR(i);
		//y = r * FCCOFFSET;
		y = this->scaleFactor * ((r + 1) * FCCOFFSET);
		return y;
	}

	/**
	 * Implements CImage::indexToZ()
	 */
	double indexToZ(int i) const {
		int l = this->indexToL(i);
		//double z = l * FCCOFFSET;
		double z = this->scaleFactor * ((l + 1) * FCCOFFSET);
		return z;
	}

	/**
	 * Implements CImage::getWidth()
	 */
	double getWidth() const {
		return (1 + ((this->nRows > 1) || (this->nLayers > 1))) * this->indexToX(0) + this->indexToX(this->rclToIndex(0, this->nColumns - 1, 0));
	}

	/**
	 * Implements CImage::getHeight()
	 */
	double getHeight() const {
		return this->indexToY(this->rclToIndex(this->nRows - 1, 0, 0)) + this->indexToY(0);
	}

	/**
	 * Implements CImage::getDepth()
	 */
	double getDepth() const {
		return this->indexToZ(0) + indexToZ(this->rclToIndex(0,0,this->nLayers - 1));
	}

	/**
	 * Implements CImage::internalDistanceVoronoiAverage
	 */
	double internalDistanceVoronoiAverage(uint8 coverage) const {
		return subSpelDistanceFCC[coverage];
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
//	vector<Neighbor> get12Neighbors(int r, int c, int l) const {
	void get12Neighbors(int r, int c, int l, vector<Neighbor> &neighbors) const {
		if(!this->isValid(r,c,l)){
			throw outsideImageException();
		}
//		vector<Neighbor> result;
//		result.reserve(12);
		neighbors.clear();
		if((l%2)!=1){
			if ((r%2)!=1){
				if(this->isValid(r-1,c,l-1)){
					neighbors.push_back(Neighbor(0,this->rclToIndex(r-1,c,l-1))); //,FCCD1)); // top front
				}
				if(this->isValid(r-1,c-1,l)){
					neighbors.push_back(Neighbor(1,this->rclToIndex(r-1,c-1,l))); //,FCCD1)); // top left
				}
				if(this->isValid(r-1,c,l+1)){
					neighbors.push_back(Neighbor(2,this->rclToIndex(r-1,c,l+1))); //,FCCD1)); // top back
				}
				if(this->isValid(r-1,c,l)){
					neighbors.push_back(Neighbor(3,this->rclToIndex(r-1,c,l))); //,FCCD1)); // top right
				}
				if(this->isValid(r,c-1,l-1)){
					neighbors.push_back(Neighbor(4,this->rclToIndex(r,c-1,l-1))); //,FCCD1)); // front left
				}
				if(this->isValid(r,c-1,l+1)){
					neighbors.push_back(Neighbor(5,this->rclToIndex(r,c-1,l+1))); //,FCCD1)); // back left
				}
				if(this->isValid(r,c,l+1)){
					neighbors.push_back(Neighbor(6,this->rclToIndex(r,c,l+1))); //,FCCD1)); // back right
				}
				if(this->isValid(r,c,l-1)){
					neighbors.push_back(Neighbor(7,this->rclToIndex(r,c,l-1))); //,FCCD1)); // front right
				}
				if(this->isValid(r+1,c,l-1)){
					neighbors.push_back(Neighbor(8,this->rclToIndex(r+1,c,l-1))); //,FCCD1)); // bottom front
				}
				if(this->isValid(r+1,c-1,l)){
					neighbors.push_back(Neighbor(9,this->rclToIndex(r+1,c-1,l))); //,FCCD1)); // bottom left
				}
				if(this->isValid(r+1,c,l+1)){
					neighbors.push_back(Neighbor(10,this->rclToIndex(r+1,c,l+1))); //,FCCD1)); // bottom back
				}
				if(this->isValid(r+1,c,l)){
					neighbors.push_back(Neighbor(11,this->rclToIndex(r+1,c,l))); //,FCCD1)); // bottom right
				}
			}
			else { //offset row
				if(this->isValid(r-1,c,l-1)){
					neighbors.push_back(Neighbor(0,this->rclToIndex(r-1,c,l-1))); //,FCCD1)); // top front
				}
				if(this->isValid(r-1,c,l)){
					neighbors.push_back(Neighbor(1,this->rclToIndex(r-1,c,l))); //,FCCD1)); // top left
				}
				if(this->isValid(r-1,c,l+1)){
					neighbors.push_back(Neighbor(2,this->rclToIndex(r-1,c,l+1))); //,FCCD1)); // top back
				}
				if(this->isValid(r-1,c+1,l)){
					neighbors.push_back(Neighbor(3,this->rclToIndex(r-1,c+1,l))); //,FCCD1)); // top right
				}
				if(this->isValid(r,c,l-1)){
					neighbors.push_back(Neighbor(4,this->rclToIndex(r,c,l-1))); //,FCCD1)); // front left
				}
				if(this->isValid(r,c,l+1)){
					neighbors.push_back(Neighbor(5,this->rclToIndex(r,c,l+1))); //,FCCD1)); // back left
				}
				if(this->isValid(r,c+1,l+1)){
					neighbors.push_back(Neighbor(6,this->rclToIndex(r,c+1,l+1))); //,FCCD1)); // back right
				}
				if(this->isValid(r,c+1,l-1)){
					neighbors.push_back(Neighbor(7,this->rclToIndex(r,c+1,l-1))); //,FCCD1)); // front right
				}
				if(this->isValid(r+1,c,l-1)){
					neighbors.push_back(Neighbor(8,this->rclToIndex(r+1,c,l-1))); //,FCCD1)); // bottom front
				}
				if(this->isValid(r+1,c,l)){
					neighbors.push_back(Neighbor(9,this->rclToIndex(r+1,c,l))); //,FCCD1)); // bottom left
				}
				if(this->isValid(r+1,c,l+1)){
					neighbors.push_back(Neighbor(10,this->rclToIndex(r+1,c,l+1))); //,FCCD1)); // bottom back
				}
				if(this->isValid(r+1,c+1,l)){
					neighbors.push_back(Neighbor(11,this->rclToIndex(r+1,c+1,l))); //,FCCD1)); // bottom right
				}
			}
		}
		else { // offset layer
			if ((r%2)==1){ //aligned row
				if(this->isValid(r-1,c,l-1)){
					neighbors.push_back(Neighbor(0,this->rclToIndex(r-1,c,l-1))); //,FCCD1)); // top front
				}
				if(this->isValid(r-1,c-1,l)){
					neighbors.push_back(Neighbor(1,this->rclToIndex(r-1,c-1,l))); //,FCCD1)); // top left
				}
				if(this->isValid(r-1,c,l+1)){
					neighbors.push_back(Neighbor(2,this->rclToIndex(r-1,c,l+1))); //,FCCD1)); // top back
				}
				if(this->isValid(r-1,c,l)){
					neighbors.push_back(Neighbor(3,this->rclToIndex(r-1,c,l))); //,FCCD1)); // top right
				}
				if(this->isValid(r,c-1,l-1)){
					neighbors.push_back(Neighbor(4,this->rclToIndex(r,c-1,l-1))); //,FCCD1)); // front left
				}
				if(this->isValid(r,c-1,l+1)){
					neighbors.push_back(Neighbor(5,this->rclToIndex(r,c-1,l+1))); //,FCCD1)); // back left
				}
				if(this->isValid(r,c,l+1)){
					neighbors.push_back(Neighbor(6,this->rclToIndex(r,c,l+1))); //,FCCD1)); // back right
				}
				if(this->isValid(r,c,l-1)){
					neighbors.push_back(Neighbor(7,this->rclToIndex(r,c,l-1))); //,FCCD1)); // front right
				}
				if(this->isValid(r+1,c,l-1)){
					neighbors.push_back(Neighbor(8,this->rclToIndex(r+1,c,l-1))); //,FCCD1)); // bottom front
				}
				if(this->isValid(r+1,c-1,l)){
					neighbors.push_back(Neighbor(9,this->rclToIndex(r+1,c-1,l))); //,FCCD1)); // bottom left
				}
				if(this->isValid(r+1,c,l+1)){
					neighbors.push_back(Neighbor(10,this->rclToIndex(r+1,c,l+1))); //,FCCD1)); // bottom back
				}
				if(this->isValid(r+1,c,l)){
					neighbors.push_back(Neighbor(11,this->rclToIndex(r+1,c,l))); //,FCCD1)); // bottom right
				}
			}
			else { //offset row
				if(this->isValid(r-1,c,l-1)){
					neighbors.push_back(Neighbor(0,this->rclToIndex(r-1,c,l-1))); //,FCCD1)); // top front
				}
				if(this->isValid(r-1,c,l)){
					neighbors.push_back(Neighbor(1,this->rclToIndex(r-1,c,l))); //,FCCD1)); // top left
				}
				if(this->isValid(r-1,c,l+1)){
					neighbors.push_back(Neighbor(2,this->rclToIndex(r-1,c,l+1))); //,FCCD1)); // top back
				}
				if(this->isValid(r-1,c+1,l)){
					neighbors.push_back(Neighbor(3,this->rclToIndex(r-1,c+1,l))); //,FCCD1)); // top right
				}
				if(this->isValid(r,c,l-1)){
					neighbors.push_back(Neighbor(4,this->rclToIndex(r,c,l-1))); //,FCCD1)); // front left
				}
				if(this->isValid(r,c,l+1)){
					neighbors.push_back(Neighbor(5,this->rclToIndex(r,c,l+1))); //,FCCD1)); // back left
				}
				if(this->isValid(r,c+1,l+1)){
					neighbors.push_back(Neighbor(6,this->rclToIndex(r,c+1,l+1))); //,FCCD1)); // back right
				}
				if(this->isValid(r,c+1,l-1)){
					neighbors.push_back(Neighbor(7,this->rclToIndex(r,c+1,l-1))); //,FCCD1)); // front right
				}
				if(this->isValid(r+1,c,l-1)){
					neighbors.push_back(Neighbor(8,this->rclToIndex(r+1,c,l-1))); //,FCCD1)); // bottom front
				}
				if(this->isValid(r+1,c,l)){
					neighbors.push_back(Neighbor(9,this->rclToIndex(r+1,c,l))); //,FCCD1)); // bottom left
				}
				if(this->isValid(r+1,c,l+1)){
					neighbors.push_back(Neighbor(10,this->rclToIndex(r+1,c,l+1))); //,FCCD1)); // bottom back
				}
				if(this->isValid(r+1,c+1,l)){
					neighbors.push_back(Neighbor(11,this->rclToIndex(r+1,c+1,l))); //,FCCD1)); // bottom right
				}
			}
		}
//		return neighbors;
	}

	/**
	 * Returns the face neighbors of the spel with index \f$(i)\f$.
	 */
//	vector<Neighbor> get12Neighbors(int i) const {
	void get12Neighbors(int i, vector<Neighbor> &neighbors) const {
		get12Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
//		return get12Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
	}

	/**
	 * Returns the face- and point neighbors of the spel at \f$(r,c,l)\f$.
	 */
//	vector<Neighbor> get18Neighbors(int r, int c, int l) const {
	void get18Neighbors(int r, int c, int l, vector<Neighbor> &neighbors) const {
		if(!this->isValid(r,c,l)){
			throw outsideImageException();
		}
//		vector<Neighbor> result;
//		result.reserve(18);
//		result = get12Neighbors(r,c,l);
		neighbors.clear();
		get12Neighbors(r,c,l,neighbors);
		if((l%2)!=1){
			if ((r%2)!=1){
				if(this->isValid(r-2,c,l)){
					neighbors.push_back(Neighbor(12,this->rclToIndex(r-2,c,l))); //,FCCD2)); // top
				}
				if(this->isValid(r,c,l-2)){
					neighbors.push_back(Neighbor(13,this->rclToIndex(r,c,l-2))); //,FCCD2)); // front
				}
				if(this->isValid(r,c-1,l)){
					neighbors.push_back(Neighbor(14,this->rclToIndex(r,c-1,l))); //,FCCD2)); // left
				}
				if(this->isValid(r,c,l+2)){
					neighbors.push_back(Neighbor(15,this->rclToIndex(r,c,l+2))); //,FCCD2)); // back
				}
				if(this->isValid(r,c+1,l)){
					neighbors.push_back(Neighbor(16,this->rclToIndex(r,c+1,l))); //,FCCD2)); // right
				}
				if(this->isValid(r+2,c,l)){
					neighbors.push_back(Neighbor(17,this->rclToIndex(r+2,c,l))); //,FCCD2)); // bottom
				}
			}
			else { //offset row
				if(this->isValid(r-2,c,l)){
					neighbors.push_back(Neighbor(12,this->rclToIndex(r-2,c,l))); //,FCCD2)); // top
				}
				if(this->isValid(r,c,l-2)){
					neighbors.push_back(Neighbor(13,this->rclToIndex(r,c,l-2))); //,FCCD2)); // front
				}
				if(this->isValid(r,c-1,l)){
					neighbors.push_back(Neighbor(14,this->rclToIndex(r,c-1,l))); //,FCCD2)); // left
				}
				if(this->isValid(r,c,l+2)){
					neighbors.push_back(Neighbor(15,this->rclToIndex(r,c,l+2))); //,FCCD2)); // back
				}
				if(this->isValid(r,c+1,l)){
					neighbors.push_back(Neighbor(16,this->rclToIndex(r,c+1,l))); //,FCCD2)); // right
				}
				if(this->isValid(r+2,c,l)){
					neighbors.push_back(Neighbor(17,this->rclToIndex(r+2,c,l))); //,FCCD2)); // bottom
				}
			}
		}
		else{ // offset layer
			if ((r%2)==1){ //aligned row
				if(this->isValid(r-2,c,l)){
					neighbors.push_back(Neighbor(12,this->rclToIndex(r-2,c,l))); //,FCCD2)); // top
				}
				if(this->isValid(r,c,l-2)){
					neighbors.push_back(Neighbor(13,this->rclToIndex(r,c,l-2))); //,FCCD2)); // front
				}
				if(this->isValid(r,c-1,l)){
					neighbors.push_back(Neighbor(14,this->rclToIndex(r,c-1,l))); //,FCCD2)); // left
				}
				if(this->isValid(r,c,l+2)){
					neighbors.push_back(Neighbor(15,this->rclToIndex(r,c,l+2))); //,FCCD2)); // back
				}
				if(this->isValid(r,c+1,l)){
					neighbors.push_back(Neighbor(16,this->rclToIndex(r,c+1,l))); //,FCCD2)); // right
				}
				if(this->isValid(r+2,c,l)){
					neighbors.push_back(Neighbor(17,this->rclToIndex(r+2,c,l))); //,FCCD2)); // bottom
				}
			}
			else { //offset row
				if(this->isValid(r-2,c,l)){
					neighbors.push_back(Neighbor(12,this->rclToIndex(r-2,c,l))); //,FCCD2)); // top
				}
				if(this->isValid(r,c,l-2)){
					neighbors.push_back(Neighbor(13,this->rclToIndex(r,c,l-2))); //,FCCD2)); // front
				}
				if(this->isValid(r,c-1,l)){
					neighbors.push_back(Neighbor(14,this->rclToIndex(r,c-1,l))); //,FCCD2)); // left
				}
				if(this->isValid(r,c,l+2)){
					neighbors.push_back(Neighbor(15,this->rclToIndex(r,c,l+2))); //,FCCD2)); // back
				}
				if(this->isValid(r,c+1,l)){
					neighbors.push_back(Neighbor(16,this->rclToIndex(r,c+1,l))); //,FCCD2)); // right
				}
				if(this->isValid(r+2,c,l)){
					neighbors.push_back(Neighbor(17,this->rclToIndex(r+2,c,l))); //,FCCD2)); // bottom
				}
			}
		}
//		return neighbors;
	}

	/**
	 * Returns the face- and point neighbors of the spel with index \f$(i)\f$.
	 */
//	vector<Neighbor> get18Neighbors(int i) const {
	void get18Neighbors(int i, vector<Neighbor> &neighbors) const {
		get18Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
//		return get18Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i));
	}

	/**
	 * Returns the specified neighborhood of the spel at \f$(r,c,l)\f$:
	 *
	 * N  | neighbors
	 * -: | :---------
	 * 12 | face
	 * 18 | face, point
	 */
//	vector<Neighbor> getNeighbors(int r, int c, int l, int N) const {
	void getNeighbors(int r, int c, int l, int N, vector<Neighbor> &neighbors) const {
		switch (N){
		case 12:
//			return get12Neighbors(r, c, l);
			get12Neighbors(r, c, l, neighbors);
			break;
		case 18:
//			return get18Neighbors(r, c, l);
			get18Neighbors(r, c, l, neighbors);
			break;
		default:
			throw nNeighborsException();
		}
	}

	/**
	 * Returns the specified neighborhood of the spel with index \f$(i)\f$:
	 *
	 * N  | neighbors
	 * -: | :---------
	 * 12 | face
	 * 18 | face, point
	 */
//	vector<Neighbor> getNeighbors(int i, int N) const {
	void getNeighbors(int i, int N, vector<Neighbor> &neighbors) const {
		switch (N){
		case 12:
//			return get12Neighbors(i);
			get12Neighbors(i,neighbors);
			break;
		case 18:
//			return get18Neighbors(i);
			get18Neighbors(i,neighbors);
			break;
		default:
			throw nNeighborsException();
		}
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
	 * i			|			| center spel index
	 * nN			| 			| neighborhood size
	 * padding		|			| Flag to determine type of padding
	 * 				|			|	0: zero padding
	 * 				|			|	1: nearest neighbor
	 * 				|			|	2: mirror
	 * neighbors	| IN/OUT	| vector of existing neighbors, to be padded
	 */
/*	void padNeighborhood(int i, int nSize, int padding, vector<Neighbor> &neighbors) {

		if (!this->isValid(i)){
			throw outsideImageException();
		}

		if ((nSize != 12) && (nSize != 18)) {
			throw outsideRangeException();
		}

		int nPresent = neighbors.size();
		int current = 0;
		int substitute;

		switch (padding) {
		case 0: // zero padding
			break;
		case 1: // nearest neighbor
			for (int n = 0; n < nSize; n++) {
				if (neighbors[n].getLocation() == current) { // neighbor is present
					current++;
				}
				else { // neighbor is missing
					// find proper index
					neighbors.insert(neighbors.begin() + current,Neighbor(current, substitute, 0));
				}
			}
			break;
		case 2: // mirror
			for (int n = 0; n < nSize; n++) {
				if (neighbors[n].getLocation() == current) { // neighbor is present
					current++;
				}
				else { // neighbor is missing
					// find proper index
					neighbors.insert(neighbors.begin() + current,Neighbor(current, substitute, 0));
				}
			}
			break;
		default:
			throw outsideRangeException();
		}
	}*/
};

typedef CImageFCC<uint8> CImagetypeFCC;

}

#endif
