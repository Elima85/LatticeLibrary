#ifndef CIMAGE_H
#define CIMAGE_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator> // for ostream_iterator
#include <cmath> // for cbrt and round
#include "exception.h"
#include "defs.h"
#include "priorityqueue.h"
#include "neighbor.h"
#include "lattice.h"

namespace CImage {

const double subSpelDistanceBall[] = {0.620350490899400, 0.555652269755901, 0.528145846788119, 0.506733087451325, 0.488465341540168, 0.472200234189075, 0.457351805704674, 0.443573133456330, 0.430637667609462, 0.418388186452059, 0.406710310647046, 0.395517753727524, 0.384743426499272, 0.374333786228138, 0.364245771896523, 0.354443732834114, 0.344897652005037, 0.335582559204240, 0.326476583721540, 0.317561321011888, 0.308820379142558, 0.300239505316538, 0.291806237861001, 0.283509194867229, 0.275338468809351, 0.267285098580547, 0.259340853252859, 0.251498337907495, 0.243750944387129, 0.236092477215586, 0.228517246588628, 0.221020025533428, 0.213596069832290, 0.206240924436824, 0.198950416024646, 0.191720656894714, 0.184548014514595, 0.177429087540041, 0.170360715205684, 0.163339888340089, 0.156363750911780, 0.149429598983671, 0.142534866270465, 0.135677111230972, 0.128854005489208, 0.122063323408814, 0.115302932722693, 0.108570795658118, 0.101864946865430, 0.095183483049688, 0.088524564685696, 0.081886409948481, 0.075267289099859, 0.068665519274745, 0.062079459617461, 0.055507506723747, 0.048948090348974, 0.042399669346957, 0.035860727807206, 0.029329771361217, 0.022805323630816, 0.016285922793487, 0.009770118241188, 0.003256467310422, -0.003256467310422, -0.009770118241188, -0.016285922793488, -0.022805323630817, -0.029329771361217, -0.035860727807206, -0.042399669346958, -0.048948090348974, -0.055507506723748, -0.062079459617461, -0.068665519274746, -0.075267289099859, -0.081886409948482, -0.088524564685696, -0.095183483049688, -0.101864946865430, -0.108570795658118, -0.115302932722693, -0.122063323408814, -0.128854005489208, -0.135677111230972, -0.142534866270465, -0.149429598983671, -0.156363750911781, -0.163339888340089, -0.170360715205684, -0.177429087540041, -0.184548014514595, -0.191720656894715, -0.198950416024646, -0.206240924436824, -0.213596069832290, -0.221020025533428, -0.228517246588628, -0.236092477215586, -0.243750944387129, -0.251498337907496, -0.259340853252859, -0.267285098580547, -0.275338468809351, -0.283509194867229, -0.291806237861002, -0.300239505316538, -0.308820379142559, -0.317561321011888, -0.326476583721540, -0.335582559204241, -0.344897652005037, -0.354443732834115, -0.364245771896524, -0.374333786228138, -0.384743426499272, -0.395517753727525, -0.406710310647046, -0.418388186452059, -0.430637667609462, -0.443573133456331, -0.457351805704674, -0.472200234189075, -0.488465341540169, -0.506733087451326, -0.528145846788120, -0.555652269755902, -0.620350490899443};

/**
 * A wrapper class for handling color image data represented as a 1D array of template T.
 *
 * The modality bands are stored one after another, in accordance with the file format used.
 *
 * Member 		| Comment
 * :-------		| :-------
 * data			| 1D array of spel values
 * lattice      | specifies the sampling lattice of the image
 * nBands		| \#modality bands
 *
 * Elements are accessed starting from 0, using \f$(r,c,l)\f$, or by a single index \f$i = \#rows\times\#cols\times l + \#cols\times r + c\f$.
 *//*
 *           .
 *         .
 *       .
 *     002 012 022 ...
 *   001 011 021 ...
 * 000 010 020 ...
 * 100
 * 200
 * .
 * .
 * .
 */
template <class T>
class CImage{
protected:
    /** pixel values in a 1D array */
    T *data;

    /** sampling lattice of the image, containing its dimensions */
    Lattice &lattice;

	/** \#modality bands */
	int nBands;

public:
    /**
    * Color image constructor
    *
    * Parameter     | Comment
    * :---------    | :-------
    * d             | Image data, must be of length l->nElements or more.
    * l             | Image sampling lattice, will not be deleted by the CImage destructor.
    * nB            | \#modality bands, >=1
    */
    CImage(T *d, Lattice &l, int nB) : lattice(l) {
        data = d;
        nBands = nB;
    }
	~CImage() {};

	// Getters
	/**
	 * Returns the number of spatial elements in the image.
	 */
	int getNElements() const{
		return lattice.getNElements();
	}

	/*
	 * Returns the number of rows in the image.
	 */
	int getNColumns() const{
		return lattice.getNColumns();
	}

	/**
	 * Returns the number of columns in the image.
	 */
	int getNRows() const{
		return lattice.getNRows();
	}

	/**
	 * Returns the number of layers in a 3D image.
	 */
	int getNLayers() const{
		return lattice.getNLayers();
	}

	/**
	 * Returns the number of modality bands of the image.
	 */
	int getNBands() const{
		return nBands;
	}

    /**
    * Returns the lattice scale factor.
    */
    double getScaleFactor() const {
        return lattice.getScaleFactor();
    }

	/**
	 * Returns a pointer to the data array of the image.
	 */
	T* getData() const{
		return data;
	}

    /**
    * Prints the parameters of the image.
    */
    void printParameters() const {
        cout << "#rows: " << lattice.getNRows() << endl;
        cout << "#columns: " << lattice.getNColumns() << endl;
        cout << "#layers: " << lattice.getNLayers() << endl;
        cout << "#modality bands: " << nBands << endl;
        cout << "scale factor: " << lattice.getScaleFactor() << endl;
        cout << "data array: " << data << endl;
    }

	/**
	 * Returns the width of the image in distance units.
	 */
    double getWidth() const {
        return lattice.getWidth();
    }

	/**
	 * Returns the height of the image in distance units.
	 */
	double getHeight() const {
        return lattice.getHeight();
    }

	/**
	 * Returns the depth of the image in distance units.
	 */
    double getDepth() const {
        return lattice.getDepth();
    }

	/**
	 * Checks whether a spel is inside the image.
	 */
	bool isValid(int index, int band = 0) const{
		//return((index >= 0 && index < lattice.getNElements()) && (band >= 0 && band < nBands));
        return (lattice.isValid(index) && (band >= 0 && band < nBands));
	}

	/**
	 * Checks whether a spel is inside the image.
	 */
	bool isValid(int row, int column, int layer, int band = 0) const{
		//return((row >= 0 && row < lattice.getNRows()) && (column >= 0 && column < lattice.getNColumns()) && (layer >= 0 && layer < lattice.getNLayers()) && (band >= 0 && band < nBands));
        return (lattice.isValid(row, column, layer) && (band >= 0 && band < nBands));
	}

	/**
	 * Converts the row-, column-, and layer indices of a spatial element to its index in the data array.
	 */
	int rclToIndex(int row, int column, int layer) const{
		if(!this->isValid(row, column, layer)){
			throw outsideImageException();
		}
		return(lattice.getNRows() * lattice.getNColumns() * layer + lattice.getNColumns() * row + column);
	}

	/**
	 * Converts the index of a spatial element to its column index.
	 */
	int indexToC(int index) const{
		if(!this->isValid(index)){
			throw outsideImageException();
		}
		return (index % (lattice.getNRows() * lattice.getNColumns())) % lattice.getNColumns();
	}

	/**
	 * Converts the index of a spatial element to its row index.
	 */
	int indexToR(int index) const{
		if(!this->isValid(index)){
			throw outsideImageException();
		}
		return (index % (lattice.getNRows() * lattice.getNColumns())) / lattice.getNColumns();
	}

	/**
	 * Converts the index of a spatial element to its layer index.
	 */
	int indexToL(int index) const{
		if(!this->isValid(index)){
			throw outsideImageException();
		}
		return index / (lattice.getNRows() * lattice.getNColumns());
	}

	/**
	 * Converts the index of a spatial element to its x-coordinate.
	 */
    double indexToX(int index) const {
        return lattice.indexToX(index);
    }

	/**
	 * Converts the index of a spatial element to its y-coordinate.
	 */
	double indexToY(int index) const {
        return lattice.indexToY(index);
    }

	/**
	 * Converts the index of a spatial element to its z-coordinate.
	 */
	double indexToZ(int index) const {
        return lattice.indexToZ(index);
    }

	/**
	 * Uses indexTo[X,Y,Z](i) to compute the coordinates of the spatial element with index i.
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * i			| 			| index of spatial element
	 * coordinates	| OUTPUT	| coordinates of the spatial elements
	 */
	void getCoordinates(int index, vector<double> &coordinates) const {
        lattice.getCoordinates(index,coordinates);
	}

	/**
	 * Computes the Euclidean distance to another spatial element.
	 */
	double euclideanDistance(int index1, int index2) const {
        return lattice.euclideanDistance(index1, index2);
	}

	/**
	 * Computes the Euclidean distance vector pointing from point i to point j.
	 */
	void euclideanDistanceVector(int index1, int index2, vector<double> &distanceVector) const {
        lattice.euclideanDistanceVector(index1, index2, distanceVector);
	}

	/**
	 * Approximates the distance, in the range \f$[-0.5,0.5]\f$, between the spel center and an intersecting surface using
	 * \f$ distance = 0.5 - coverage\f$.
	 *
	 * Parameter	| Comment
	 * :----------	| :--------
	 * coverage		| 1 means total coverage, 0 means no coverage.
	 */
	double internalDistanceLinear(double coverage) const {
		if (coverage < 0 || coverage > 1) {
			throw outsideRangeException();
		}
		return 0.5 - coverage;
	}
	double internalDistanceLinear(uint8 coverage) const {
		double convertedCoverage = coverage/255.0;
		return internalDistanceLinear(convertedCoverage);
	}

	/**
	 * Approximates the distance, in the range \f$[-0.620,0.620]\f$, between the spel center and an intersecting surface by assuming a spherical spel.
	 *
	 * Parameter	| Comment
	 * :----------	| :--------
	 * coverage		| 1 means total coverage, 0 means no coverage.
	 */
	double internalDistanceBall(uint8 coverage) const {
		cout << "coverage and index: " << int(coverage) << endl;
		return subSpelDistanceBall[coverage];
	}
	double internalDistanceBall(double coverage) const {
		if (coverage < 0 || coverage > 1) {
					throw outsideRangeException();
		}
		uint8 convertedCoverage = round(coverage * 255); // should be 127 or something, or we need to remake the arrays.
		return internalDistanceBall(convertedCoverage);
	}

	/**
	 * Approximates the distance using the average of the Voronoi cell.
	 *
	 * Parameter	| Comment
	 * :----------	| :--------
	 * coverage		| 1 means total coverage, 0 means no coverage.
	 */
	//virtual double internalDistanceVoronoiAverage(uint8 coverage) const = 0;
	//virtual double internalDistanceVoronoiAverage(double coverage) const = 0;

	/*
	 * Uses the intensity value of a spel, regarded as a coverage value, to approximate the distance between the spel center and the surface that, supposedly, intersects the spel.
	 *
	 * Parameter	| Comment
	 * :----------	| :--------
	 * i			| spel index
	 * b			| modality band index
	 * method		| Approximation method:
	 * 				|	0: linear
	 * 				|	1: ball
	 * 				|	2: Voronoi cell average
	 */
	/*double approximatedInternalDistance(int index, int band, int method) const {

		if (!isValid(index, band)) {
			throw outsideImageException();
		}

		T intensity = (*this)(index, band);
		switch(method) {
		case 0:
			return internalDistanceLinear(intensity);
			break;
		case 1:
			return internalDistanceBall(intensity);
			break;
		case 2:
			return internalDistanceVoronoiAverage(intensity);
			break;
		default:
			throw outsideRangeException();
		}
	}*/

	// Operators
	T& operator()(int row, int column, int layer, int band = 0) const {
		if(!this->isValid(row, column, layer, band)){
			throw outsideImageException();
		}
		return this->data[band * this->lattice.getNElements() + this->rclToIndex(row, column, layer)];
	}

	T& operator()(int index, int band) const {
		if(!this->isValid(index, band)){
			throw outsideImageException();
		}
		return this->data[band * lattice.getNElements() + index];
	}

	vector<T> operator[](int index) const {
		if(!this->isValid(index)){
			throw outsideImageException();
		}
		vector<T> intensityValues;
		for (int band = 0; band < this->nBands; band++) {
			intensityValues.push_back(this->data[band * this->lattice.getNElements() + index]);
		}
		return intensityValues;
	}

    /**
    * Sets the intensity of element [index] to the specified intensity.
    *
    * Parameter		    | Comment
    * :----------   	| :--------
    * index			    | element index
    * intensityValues	| intensity values for each band
    */
    void setElement(int index, vector<T> intensityValues) {
        if (!this->isValid(index)) {
            throw outsideImageException();
        }
        if (intensityValues.size() != nBands) {
            throw dimensionMismatchException();
        }
        for (int band = 0; band < this->nBands; band++) {
            data[band * lattice.getNElements() + index] = intensityValues[band];
        }
    }

	/**
	 * Sets the intensity of element (r,c,l) to the specified intensity.
	 *
	 * Parameter		| Comment
	 * :----------		| :--------
	 * row				| row index
	 * column			| column index
	 * layer			| layer index
	 * intensityValues	| intensity values for each band
	 */
	void setElement(int row, int column, int layer, vector<T> intensityValues) {
		int index = rclToIndex(row, column, layer);
		this->setElement(index, intensityValues);
	}

	/**
	 * Returns the neighbors of a spatial element.
	 */
    void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector<Neighbor> &neighbors) {
        lattice.getNeighbors(row, column, layer, neighborhoodSize, neighbors);
    }

	/**
	 * Returns the neighbors of a spatial element.
	 */
    void getNeighbors(int index, int neighborhoodSize, vector<Neighbor> &neighbors) const  {
        lattice.getNeighbors(index, neighborhoodSize, neighbors);
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
//	virtual void padNeighborhood(int i, int nSize, int padding, vector<Neighbor> &neighbors) = 0;

	/**
	 * Extracts one modality band from the image.
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * index		|			| Index of the band to be extracted.
	 * result		| OUTPUT	| extracted values
	 */
	void getBand(int band, T* result) const {
		if (!(band >= 0 && band < nBands)) {
			throw outsideImageException();
		}
		for (int index = 0; index < lattice.getNElements(); index++) {
			result[index] = data[band * lattice.getNElements() + index];
		}
	}

	/**
	 * Blends all modality bands into a single band.
	 * min/max
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * flag			|			| Decides how to blend the modality bands into one
	 * 				|			| 	0: minimum val is kept
	 * 				|			| 	1: maximum val is kept
	 * result		| OUTPUT	| blended values
	 */
	void blend(int flag, T* result) const {
		T val;
		switch(flag) {
		case 0: // min
			for (int i = 0; i < lattice.getNElements(); i++) {
				val = T(INF);
				for (int b = 0; b < nBands; b++) {
					val = min(val, data[b * lattice.getNElements() + i]);
				}
				result[i] = val;
			}
			break;
		case 1: // max
			for (int i = 0; i < lattice.getNElements(); i++) {
				val = T(-INF);
				for (int b = 0; b < nBands; b++) {
					val = max(val, data[b * lattice.getNElements() + i]);
				}
				result[i] = val;
			}
			break;
		default:
			throw outsideRangeException();
		}
	}
	/**
	 * Blends all modality bands into a single band.
	 * mean
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * flag			|			| Decides how to blend the modality bands into one
	 * 				|			| 	2: computes mean value of all color bands
	 * result		| OUTPUT	| blended values
	 */
	/*
	void blend(int flag, double* result) const {
		double val;
		switch(flag) {
		case 2: // mean
			for (int i = 0; i < lattice.getNElements(); i++) {
				val = 0.0;
				for (int b = 0; b < nBands; b++) {
					val = val + double(data[b * lattice.getNElements() + i]);
				}
				result[i] = val/double(nBands);
			}
			break;
		default:
			throw outsideRangeException();
		}
	}
	*/

	/**
	 * Filters the image using the supplied filter, which may be, for example,
	 * an integer or double coefficient filter.
	 *
	 * Parameter	| in/out	| Comment
	 * :----------	| :-------	| :--------
	 * filter		|			| filter to apply on the image
	 * nN			|			| #neighbors to use.
	 * padding		|			| defines filter behavior for edge spels
	 * result		| OUTPUT	| filtered image
	 */
	// Fixa en padding-metod, som tar en grannskapsvektor och fyller p� den med v�rden f�r grannarna som fattas.
//	void filter(ScalarFilter<S> filter, int nN, int padding, T* result) const {
//
//	}

	/**
	 * Downsamples the input image using spatial elements of the specified volume. Has many imperfections.
	 *
	 * Parameter		| in/out	| Comment
	 * :----------		| :-------	| :--------
	 * original			|			| input image
	 * newSpelVolume	|			| volume of a spel in the downsampled image
	 * data				| OUTPUT	| Pointer to the data array of the resulting image, as the CImage destructor does not delete it.
	 */
	//virtual T* downsample(const CImage<T>* original, double newSpelVolume) = 0;

};

}
#endif
