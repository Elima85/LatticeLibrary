#ifndef CIMAGEBCC_H
#define CIMAGEBCC_H

#include <vector>
#include <iostream>
#include <cmath> // for cbrt and round
#include "cimage.h"
#include "exception.h"
#include "defs.h"
#include "neighbor.h"
#include "miscellaneous.h"
#include "vectoroperators.h"
#include "filehandling.h" // DEBUG
using namespace std;

namespace CImage {

// neighbor distances
#define BCCOFFSET 0.629960524947437 // 1/(4^(1/3)), distance between layers in BCC
#define BCCHEXFACEDISTANCE 1.091123635971721 // hexagonal face neighbor distance
#define BCCSQFACEDISTANCE 1.259921049894873 // square face neighbor distance
const double subSpelDistanceBCC[] = {0.701972775991366, 0.559384096369300, 0.523708491831535, 0.504208119337289, 0.485961099189012, 0.472741906135919, 0.458428017799460, 0.445843863595213, 0.434019197645408, 0.421854125314656, 0.410046880337088, 0.398436206179092, 0.388502787488950, 0.379144338651330, 0.368789186781820, 0.360067592029462, 0.351589510084802, 0.340956184471487, 0.329472567765149, 0.321934283205210, 0.313308029661695, 0.304521999486493, 0.295681765149159, 0.287079844458938, 0.279572841418967, 0.270861674256076, 0.258622537052800, 0.247030386296779, 0.239786630506896, 0.230416027579064, 0.222140243071163, 0.215396284206380, 0.209046622997721, 0.201292811785985, 0.194850180312712, 0.186887340378882, 0.178301036183765, 0.169774888060555, 0.160240158042547, 0.151141619183839, 0.144910123075057, 0.139387081056519, 0.132275281214361, 0.123179449447133, 0.115209909239135, 0.110282588275489, 0.105846354179058, 0.097971825318819, 0.091618971374103, 0.084055977701946, 0.077881461109973, 0.073232744286903, 0.067781308571245, 0.061551851798691, 0.053606146291214, 0.046420652020054, 0.041350100604422, 0.036400013065505, 0.029826111258516, 0.023163184058998, 0.016486093935675, 0.009027623284885, 0.000545114595576, -0.006409316162271, -0.011482052972629, -0.015909380103552, -0.021930295484404, -0.030471309324572, -0.040087312040690, -0.046264459750243, -0.049745671713369, -0.055999006275204, -0.063703031687841, -0.072133278469194, -0.080124877274717, -0.086253283696209, -0.088776416146436, -0.095688808377654, -0.104454984748970, -0.112888180402466, -0.121260312573985, -0.126321890828481, -0.131849231572847, -0.138220378699248, -0.145300216688578, -0.152684773950153, -0.159078310790973, -0.166091155853891, -0.173145831561477, -0.179553181648581, -0.186280945968988, -0.192493313638436, -0.199834267437540, -0.207937851311092, -0.215239752797464, -0.222649547807335, -0.231373128404468, -0.239614163904793, -0.247238387508153, -0.256049244942309, -0.261748975120585, -0.269512678472865, -0.278161635054214, -0.285938506381002, -0.294409262751931, -0.304112483169524, -0.313207636275675, -0.322104272848939, -0.332070852300711, -0.343230544965409, -0.352860726531219, -0.361270311111415, -0.369949001001639, -0.381124542872056, -0.390590115886440, -0.402038335648907, -0.413310900786398, -0.423543150723804, -0.436036024356762, -0.447960451557584, -0.460686204854493, -0.473981713655202, -0.487815571365090, -0.505860782414118, -0.521218530696975, -0.540411881786846, -0.581537424601552, -0.713634612236801};


/**
 * image_BCC:
 * A wrapper class for handling BCC image data represented as a 1D array.
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
class CImageBCC : public CImage<T> {

public:
	// Constructor
	CImageBCC(T *d,int nr, int nc, int nl, int nb, double ev = 1) : CImage<T>(d, nr, nc, nl, nb, ev){
	}
	CImageBCC() : CImage<T>(){
	}
	~CImageBCC() {}

	/**
	 * Implements CImage::indexToX()
	 */
	double indexToX(int i) const {
		int c,l;
		double x;
		c = this->indexToC(i);
		l = this->indexToL(i);
		//x = c * BCCFACTORX2 + (!IS_EVEN(l)) * BCCOFFSET;
		x = this->scaleFactor * ((1 + !IS_EVEN(l)) * BCCOFFSET + c * BCCSQFACEDISTANCE);
		return x;
	}

	/**
	 * Implements CImage::indexToY()
	 */
	double indexToY(int i) const {
		int r,l;
		double y;
		r = this->indexToR(i);
		l = this->indexToL(i);
		//y = r * BCCFACTORX2 + (!IS_EVEN(l)) * BCCOFFSET;
		y = this->scaleFactor * ((1 + !IS_EVEN(l)) * BCCOFFSET + r * BCCSQFACEDISTANCE);
		return y;
	}

	/**
	 * Implements CImage::indexToZ()
	 */
	double indexToZ(int i) const {
		int l = this->indexToL(i);
		//double z = l*BCCOFFSET;
		double z = this->scaleFactor * (1 + l) * BCCOFFSET;
		return z;
	}

	/**
	 * Implements CImage::getWidth()
	 */
	double getWidth() const {
		return this->indexToX(0) + this->indexToX(this->rclToIndex(0,this->nColumns - 1, (this->nLayers > 1)));
	}

	/**
	 * Implements CImage::getHeight()
	 */
	double getHeight() const {
		return this->indexToY(0) + this->indexToY(this->rclToIndex(this->nRows - 1, 0, (this->nLayers > 1)));
	}

	/**
	 * Implements CImage::getDepth()
	 */
	double getDepth() const {
		return this->indexToZ(0) + this->indexToZ(this->nElements - 1);
	}

	/**
	 * Implements CImage::internalDistanceVoronoiAverage
	 */
	double internalDistanceVoronoiAverage(uint8 coverage) const {
		return subSpelDistanceBCC[coverage];
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
	 * Returns the hexagonal face neighbors of the spel at \f$(r,c,l)\f$.
	 */
	void get8Neighbors(int r, int c, int l, vector<Neighbor> &neighbors) const {
		if(!this->isValid(r,c,l)){
			throw outsideImageException();
		}
		neighbors.clear();
		if(IS_EVEN(l)){
			if(this->isValid(r-1,c-1,l-1)){
				neighbors.push_back(Neighbor(0,this->rclToIndex(r-1,c-1,l-1))); // top left front
			}
			if(this->isValid(r-1,c,l-1)){
				neighbors.push_back(Neighbor(1,this->rclToIndex(r-1,c,l-1))); // top right front
			}
			if(this->isValid(r,c-1,l-1)){
				neighbors.push_back(Neighbor(2,this->rclToIndex(r,c-1,l-1))); // bottom left front
			}
			if(this->isValid(r,c,l-1)){
				neighbors.push_back(Neighbor(3,this->rclToIndex(r,c,l-1))); // bottom right front
			}
			if(this->isValid(r-1,c-1,l+1)){
				neighbors.push_back(Neighbor(4,this->rclToIndex(r-1,c-1,l+1))); // top left back
			}
			if(this->isValid(r-1,c,l+1)){
				neighbors.push_back(Neighbor(5,this->rclToIndex(r-1,c,l+1))); // top right back
			}
			if(this->isValid(r,c-1,l+1)){
				neighbors.push_back(Neighbor(6,this->rclToIndex(r,c-1,l+1))); // bottom left back
			}
			if(this->isValid(r,c,l+1)){
				neighbors.push_back(Neighbor(7,this->rclToIndex(r,c,l+1))); // bottom right back
			}
		}
		else{ // offset layers
			if(this->isValid(r,c,l-1)){
				neighbors.push_back(Neighbor(0,this->rclToIndex(r,c,l-1))); // top left front
			}
			if(this->isValid(r,c+1,l-1)){
				neighbors.push_back(Neighbor(1,this->rclToIndex(r,c+1,l-1))); // top right front
			}
			if(this->isValid(r+1,c,l-1)){
				neighbors.push_back(Neighbor(2,this->rclToIndex(r+1,c,l-1))); // bottom left front
			}
			if(this->isValid(r+1,c+1,l-1)){
				neighbors.push_back(Neighbor(3,this->rclToIndex(r+1,c+1,l-1))); // bottom right front
			}
			if(this->isValid(r,c,l+1)){
				neighbors.push_back(Neighbor(4,this->rclToIndex(r,c,l+1))); // top left back
			}
			if(this->isValid(r,c+1,l+1)){
				neighbors.push_back(Neighbor(5,this->rclToIndex(r,c+1,l+1))); // top right back
			}
			if(this->isValid(r+1,c,l+1)){
				neighbors.push_back(Neighbor(6,this->rclToIndex(r+1,c,l+1))); // bottom left back
			}
			if(this->isValid(r+1,c+1,l+1)){
				neighbors.push_back(Neighbor(7,this->rclToIndex(r+1,c+1,l+1))); // bottom right back
			}
		}
	}

	/**
	 * Returns the face neighbors of the spel with index \f$(i)\f$.
	 */
	void get8Neighbors(int i, vector<Neighbor> &neighbors) const {
		get8Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
	}

	/**
	 * Returns the hexagonal and square face neighbors of the spel at \f$(r,c,l)\f$.
	 */
	void get14Neighbors(int r, int c, int l, vector<Neighbor> &neighbors) const {
		if(!this->isValid(r,c,l)){
			throw outsideImageException();
        }
        neighbors.clear();
        get8Neighbors(r,c,l,neighbors);
        if(this->isValid(r-1,c,l)){
            neighbors.push_back(Neighbor(8,this->rclToIndex(r-1,c,l))); // top
        }
        if(this->isValid(r,c,l-2)){
            neighbors.push_back(Neighbor(9,this->rclToIndex(r,c,l-2))); // front
        }
        if(this->isValid(r,c-1,l)){
            neighbors.push_back(Neighbor(10,this->rclToIndex(r,c-1,l))); // left
        }
        if(this->isValid(r,c,l+2)){
            neighbors.push_back(Neighbor(11,this->rclToIndex(r,c,l+2))); // back
        }
        if(this->isValid(r,c+1,l)){
            neighbors.push_back(Neighbor(12,this->rclToIndex(r,c+1,l))); // right
        }
        if(this->isValid(r+1,c,l)){
            neighbors.push_back(Neighbor(13,this->rclToIndex(r+1,c,l))); // bottom
        }
	}

	/**
	 * Returns the hexagonal and square face neighbors of the spel with index \f$(i)\f$.
	 */
	void get14Neighbors(int i, vector<Neighbor> &neighbors) const {
		get14Neighbors(this->indexToR(i), this->indexToC(i), this->indexToL(i), neighbors);
	}

	/**
	 * Returns the specified neighborhood of the spel at \f$(r,c,l)\f$:
	 *
	 * N  | neighbors
	 * -: | :---------
	 * 8  | hexagonal face
	 * 14 | hexagonal face, square face
	 */
	void getNeighbors(int r, int c, int l, int N, vector<Neighbor> &neighbors) const {
		switch (N){
		case 8:
			get8Neighbors(r, c, l, neighbors);
			break;
		case 14:
			get14Neighbors(r, c, l, neighbors);
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
	 * 8  | hexagonal face
	 * 14 | hexagonal face, square face
	 */
	void getNeighbors(int i, int N, vector<Neighbor> &neighbors) const {
		switch (N){
		case 8:
			get8Neighbors(i,neighbors);
			break;
		case 14:
			get14Neighbors(i,neighbors);
			break;
		default:
			throw nNeighborsException();
		}
	}

    /**
    * Implements CImage::downsample(const CImage<T>* original, double newSpelVolume, T* data)
    */
    T *downsample(const CImage<T> *original, double newSpelVolume) {

        // high resolution image parameters
        double oldWidth = original->getWidth();
        double oldHeight = original->getHeight();
        double oldDepth = original->getDepth();
        int oldNElements = original->getNElements();
        int nBands = original->getNBands();

//        cout << "old #rows: " << original->getNRows() << endl; // DEBUG
//        cout << "old #columns: " << original->getNColumns() << endl; // DEBUG
//        cout << "old #layers: " << original->getNLayers() << endl; // DEBUG

        // low resolution image parameters
        double newScaleFactor = cbrt(newSpelVolume);
        if((oldDepth < newScaleFactor * (BCCSQFACEDISTANCE + BCCOFFSET)) || (oldWidth < newScaleFactor * (BCCSQFACEDISTANCE + BCCOFFSET)) || (oldHeight < newScaleFactor * (BCCSQFACEDISTANCE + BCCOFFSET))){
            // Must have more than two layers, columns and rows to be a BCC lattice.
            throw downsampleException();
        }
        // get dimensions
        int newNRows = (int) floor((oldHeight - newScaleFactor * BCCOFFSET) / (newScaleFactor * BCCSQFACEDISTANCE));
        int newNColumns = (int) floor((oldWidth - newScaleFactor * BCCOFFSET) / (newScaleFactor * BCCSQFACEDISTANCE));
        int newNLayers = (int) floor((oldDepth - newScaleFactor * BCCOFFSET) / (newScaleFactor * BCCOFFSET));
        int newNElements = newNRows * newNColumns * newNLayers;
        this->nRows = newNRows;
        this->nColumns = newNColumns;
        this->nLayers = newNLayers;
        this->nElements = newNElements;
        this->nBands = nBands;
        this->scaleFactor = newScaleFactor;
        this->data = new T[newNElements * nBands];
        if (!this->data) {
            throw nullPointerException();
        }
        double newWidth = this->getWidth();
        double newHeight = this->getHeight();
        double newDepth = this->getDepth();

//        cout << "new #rows: " << this->getNRows() << endl; // DEBUG
//        cout << "new #columns: " << this->getNColumns() << endl; // DEBUG
//        cout << "new #layers: " << this->getNLayers() << endl; // DEBUG

        vector<Neighbor> newNeighbors;
        int nNeighbors, nSubSpels;
//        int minR, maxR, minC, maxC, minL, maxL; // DEBUG
//        double *voronoiCells = new double[oldNElements]; // DEBUG
//        for (int i = 0; i < oldNElements; i++) { // DEBUG
//            voronoiCells[i] = 0; // DEBUG
//        } // DEBUG
        vector<double> newIntensity, newCoordinates, oldCoordinates, neighborCoordinates;
        vector<vector<double> > newNeighborCoordinates;
        double squaredDistanceToCurrent, squaredDistanceToNeighbor, volumeFactor, squaredRadius = pow(1.1 * this->scaleFactor * BCCOFFSET * sqrt(1.25),2);
        bool inside;
        for (int newIndex = 0; newIndex < newNElements; newIndex++) {
            cout << "Element index: " << newIndex << endl; // DEBUG
            nSubSpels = 0;
//            minR = 10000; // DEBUG
//            maxR = 0; // DEBUG
//            minC = 10000; // DEBUG
//            maxC = 0; // DEBUG
//            minL = 10000; // DEBUG
//            maxL = 0; // DEBUG
            newIntensity.assign(nBands, 0.0);
            this->getCoordinates(newIndex, newCoordinates);
//            cout << "new element location: " << endl; // DEBUG
//            printVector(newCoordinates); // DEBUG
            this->getNeighbors(newIndex, 14, newNeighbors);
            nNeighbors = newNeighbors.size();
//            cout << "#neighbors: " << nNeighbors << endl; // DEBUG
//            for (int n = 0; n < nNeighbors; n++) { // DEBUG
//                cout <<"\t" << newNeighbors[n].getIndex() << endl; // DEBUG
//            } // DEBUG
            newNeighborCoordinates.clear();
//            cout << "neighbors: " << endl; // DEBUG
            for (int n = 0; n < nNeighbors; n++) {
                this->getCoordinates(newNeighbors[n].getIndex(), neighborCoordinates);
                newNeighborCoordinates.push_back(neighborCoordinates);
//                printVector(newNeighborCoordinates[n]); // DEBUG
            }
            for (int oldIndex = 0; oldIndex < oldNElements; oldIndex++) { // Should be optimized to some search area!! Check if squaredDistanceToCurrent is less than some regionOfInterest, e.g. (scaleFactor*BCCOFFSET)^2?
                original->getCoordinates(oldIndex, oldCoordinates);
                squaredDistanceToCurrent = 0;
                for (int i = 0; i < 3; i++) {
                    squaredDistanceToCurrent = squaredDistanceToCurrent + pow(newCoordinates[i] - oldCoordinates[i],2);
                }
                if (squaredDistanceToCurrent < squaredRadius) {
                    inside = true;
                    for (int n = 0; n < nNeighbors; n++) {
                        squaredDistanceToNeighbor = 0;
                        for (int i = 0; i < 3; i++) {
                            squaredDistanceToNeighbor = squaredDistanceToNeighbor + pow(newNeighborCoordinates[n][i] - oldCoordinates[i], 2);
                        }
                        if (squaredDistanceToNeighbor < squaredDistanceToCurrent) {
                            inside = false;
                            break;
                        }
                    }

                    if (inside) {
//                        voronoiCells[oldIndex] = newIndex; // DEBUG
                        newIntensity = newIntensity + (*original)[oldIndex];
                        nSubSpels++;
//                    minR = MIN(minR, original->indexToR(oldIndex)); // DEBUG
//                    maxR = MAX(maxR, original->indexToR(oldIndex)); // DEBUG
//                    minC = MIN(minC, original->indexToC(oldIndex)); // DEBUG
//                    maxC = MAX(maxC, original->indexToC(oldIndex)); // DEBUG
//                    minL = MIN(minL, original->indexToL(oldIndex)); // DEBUG
//                    maxL = MAX(maxL, original->indexToL(oldIndex)); // DEBUG
                    }
                }
            }
//            cout << "range of R: [" << minR << "," << maxR << "]" << endl; //DEBUG
//            cout << "range of C: [" << minC << "," << maxC << "]" << endl; //DEBUG
//            cout << "range of L: [" << minL << "," << maxL << "]" << endl; //DEBUG
//            cout << "#subSpels: " << nSubSpels << endl; // DEBUG
//            cout << "accumulated intensity: " << endl; // DEBUG
//            printVector(newIntensity); // DEBUG
            volumeFactor = 1.0 / double(nSubSpels);
            this->setElement(newIndex, (volumeFactor * newIntensity));
            cout << "new intensity:" << endl; // DEBUG
            printVector((*this)[newIndex]); // DEBUG
        }
//        char filename[] = "voronoiCells.bin"; // DEBUG
//        char *filepointer = filename; // DEBUG
//        writeVolume(filepointer, voronoiCells, oldNElements); // DEBUG
//        delete[] voronoiCells; // DEBUG
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
	 * i			|			| center spel index
	 * nN			| 			| neighborhood size
	 * padding		|			| Flag to determine type of padding
	 * 				|			|	0: zero padding
	 * 				|			|	1: nearest neighbor
	 * 				|			|	2: mirror
	 * neighbors	| IN/OUT	| vector of existing neighbors, to be padded
	 */
	void padNeighborhood(int i, int nSize, int padding, vector<Neighbor> &neighbors) {
/*
		if (!this->isValid(i)){
			throw outsideImageException();
		}

		if ((nSize != 8) && (nSize != 14)) {
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
				if (neighbors[n].getPosition() == current) { // neighbor is present
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
		}*/
	}
};

typedef CImageBCC<uint8> CImagetypeBCC;

}

#endif
