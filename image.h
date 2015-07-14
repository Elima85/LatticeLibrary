#ifndef IMAGE_H
#define IMAGE_H

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
#include "vectoroperators.h"

namespace LatticeLib {

/**
 * A class for handling color image data represented as a 1D array of template T.
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
	class Image {
	protected:
		/** pixel values in a 1D array */
		T *data;

		/** sampling lattice of the image, containing its dimensions */
		Lattice &lattice;

		/** \#modality bands */
		int nBands;

	public:
		/**
        * Color image constructor.
        *
        * Parameter     | Comment
        * :---------    | :-------
        * d             | Image data, must be of length l->nElements or more.
        * l             | Image sampling lattice, will not be deleted by the Image destructor.
        * nB            | \#modality bands, >=1
        */
		Image(T *d, Lattice &l, int nB) : lattice(l) {
			data = d;
			nBands = nB;
		}

		/**
        * Color image copy constructor. The copy receives its own data array.
        */
		Image(const Image<T> &original) : lattice(original.getLattice()) {
			nBands = original.nBands;
			int nTotal = nBands * original.getNElements();
			data = original.data;
			//data = new T[nTotal];
			//for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
			//	data[dataIndex] = original.data[dataIndex];
			//}
		}
		~Image() {}; // TODO: Should this delete the data array?

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
		T* getData() const {
			return data;
		}

		/**
		 * Returns a pointer to the beginning of the requested band of in the data array of the image.
		 */
		T* getBand(int bandIndex) const {
			return data + bandIndex * getNElements();
		}

		/**
		 * Returns the image sampling lattice.
		 */
		Lattice& getLattice() const {
			return lattice;
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
         * Checks whether a spel is inside the image.
         */
		bool isValid(int index, int band = 0) const{
			return (lattice.isValid(index) && (band >= 0 && band < nBands));
		}

		/**
         * Checks whether a spel is inside the image.
         */
		bool isValid(int row, int column, int layer, int band = 0) const{
			return (lattice.isValid(row, column, layer) && (band >= 0 && band < nBands));
		}

		/**
         * Converts the row-, column-, and layer indices of a spatial element to its index in the data array.
         */
		int rclToIndex(int row, int column, int layer) const{
//			if(!this->isValid(row, column, layer)){
//				throw outsideImageException();
//			}
//			return(lattice.getNRows() * lattice.getNColumns() * layer + lattice.getNColumns() * row + column);
			return lattice.rclToIndex(row, column, layer);
		}

		/**
         * Converts the index of a spatial element to its column index.
         */
		int indexToC(int index) const{
//			if(!this->isValid(index)){
//				throw outsideImageException();
//			}
//			return (index % (lattice.getNRows() * lattice.getNColumns())) % lattice.getNColumns();
			return lattice.indexToC(index);
		}

		/**
         * Converts the index of a spatial element to its row index.
         */
		int indexToR(int index) const{
//			if(!this->isValid(index)){
//				throw outsideImageException();
//			}
//			return (index % (lattice.getNRows() * lattice.getNColumns())) / lattice.getNColumns();
			return lattice.indexToR(index);
		}

		/**
         * Converts the index of a spatial element to its layer index.
         */
		int indexToL(int index) const{
//			if(!this->isValid(index)){
//				throw outsideImageException();
//			}
//			return index / (lattice.getNRows() * lattice.getNColumns());
			return lattice.indexToL(index);
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
        * Parameter		| Comment
        * :----------   | :--------
        * index			| element index
        * band			| band index
        * intensity		| new intensity valuse
        */
		template<class S>
		void setElement(int index, int band, S intensity) {
			if (!this->isValid(index, band)) {
				throw outsideImageException();
			}
			data[band * lattice.getNElements() + index] = T(intensity);
		}

		/**
        * Sets the intensity of element (r,c,l) to the specified intensity.
        *
        * Parameter		| Comment
        * :----------	| :--------
        * row			| row index
        * column		| column index
        * layer			| layer index
        * band			| band index
        * intensity		| new intensity valuse
        */
		template<class S>
		void setElement(int row, int column, int layer, int band, S intensity) {
			int index = rclToIndex(row, column, layer);
			this->setElement(index, band, intensity);
		}

		/**
        * Sets the intensity of element [index] to the specified intensity.
        *
        * Parameter		    | Comment
        * :----------   	| :--------
        * index			    | element index
        * intensityValues	| intensity values for each band
        */
		template<class S>
		void setElement(int index, vector<S> intensityValues) {
			if (!this->isValid(index)) {
				throw outsideImageException();
			}
			if (intensityValues.size() != nBands) {
				throw dimensionMismatchException();
			}
			for (int band = 0; band < this->nBands; band++) {
				data[band * lattice.getNElements() + index] = T(intensityValues[band]);
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
		template<class S>
		void setElement(int row, int column, int layer, vector<S> intensityValues) {
			int index = rclToIndex(row, column, layer);
			this->setElement(index, intensityValues);
		}

		/**
         * Returns the neighbors of a spatial element.
         */
		void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector<Neighbor> &neighbors) const {
			lattice.getNeighbors(row, column, layer, neighborhoodSize, neighbors);
		}

		/**
         * Returns the neighbors of a spatial element.
         */
		void getNeighbors(int index, int neighborhoodSize, vector<Neighbor> &neighbors) const  {
			lattice.getNeighbors(index, neighborhoodSize, neighbors);
		}
	};

}
#endif
