#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "exception.h"
#include "defs.h"
#include "neighbor.h"
#include "lattice.h"

namespace LatticeLib {

/**
 * A class for handling multimodal image data of up to three dimensions represented as a row-major array, with modality
 * bands stored consecutively. Because of the template implementation, the image intensity values may be of
 * any type.
 *
 * Member 		| Comment
 * :-------		| :-------
 * data			| Array of intensity values.
 * lattice      | Specifies the sampling lattice of the image, and contains its dimensions.
 * nBands		| Number of modality bands.
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
		/** Array of intensity values. */
		T *data;

		/** Specifies the sampling lattice of the image, and contains its dimensions. */
		Lattice &lattice;

		/** Number of modality bands. */
		int nBands;

	public:
		/**
         * Constructor for Image objects.
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	|:-------
         * d			| INPUT		| %Image data, must be of length lattice.nElements or more.
         * l			| INPUT		| %Image sampling lattice.
         * nB			| INPUT		| Number of modality bands, must be at least 1.
         */
		Image(T *d, Lattice &l, int nB) : lattice(l) {
			data = d;
			nBands = nB;
		}

		/**
         * Copy constructor for Image objects. The resulting object shares the data array of the input object.
         *
         * Parameter     | in/out	| Comment
         * :---------    | :------	| :-------
         * original      | INPUT	| Image object to be copied.
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

		/**
         * Wrapper for Lattice::getNElements();
         *
         * Returns the number of spatial elements in the image.
         */
		int getNElements() const{
			return lattice.getNElements();
		}

		/**
         * Wrapper for Lattice::getNRows();
         *
         * Returns the number of rows in the image.
         */
		int getNColumns() const{
			return lattice.getNColumns();
		}

		/**
         * Wrapper for Lattice::getNColumns();
         *
         * Returns the number of columns in the image.
         */
		int getNRows() const{
			return lattice.getNRows();
		}

		/**
         * Wrapper for Lattice::getNLayers();
         *
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
         * Wrapper for Lattice::getScaleFactor();
         *
         * Returns the lattice scale factor.
         */
		double getScaleFactor() const {
			return lattice.getDensity();
		}

		/**
         * Returns a pointer to the data array of the image.
         */
		T* getData() const {
			return data;
		}

		/**
		 * Returns a pointer to the beginning of the requested band of in the data array of the image.
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * bandIndex	| INPUT		| Index of the requested band.
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
         * Wrapper for Lattice::getWidth().
         */
		double getWidth() const {
			return lattice.getWidth();
		}

		/**
         * Wrapper for Lattice::getHeight().
         */
		double getHeight() const {
			return lattice.getHeight();
		}

		/**
         * Wrapper for Lattice::getDepth().
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
			cout << "scale factor: " << lattice.getDensity() << endl;
			cout << "data array: " << data << endl;
		}

		/**
         * Checks whether a spatial element is part of the image.
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         * bandIndex	| INPUT		| Index of the band of interest.
         */
		bool isValid(int elementIndex, int bandIndex = 0) const{
			return (lattice.isValid(elementIndex) && (bandIndex >= 0 && bandIndex < nBands));
		}

		/**
         * Checks whether a spel is inside the image.
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * rowIndex		| INPUT		| Row index of the element of interest.
         * columnIndex	| INPUT		| Column index of the element of interest.
         * layerIndex	| INPUT		| Layer index of the element of interest.
         * bandIndex	| INPUT		| Index of the band of interest.
         */
		bool isValid(int rowIndex, int columnIndex, int layerIndex, int bandIndex = 0) const{
			return (lattice.isValid(rowIndex, columnIndex, layerIndex) && (bandIndex >= 0 && bandIndex < nBands));
		}

		/**
         * Wrapper for Lattice::rclToIndex(int row, int column, int layer).
         */
		int rclToIndex(int rowIndex, int columnIndex, int layerIndex) const{
			return lattice.rclToIndex(rowIndex, columnIndex, layerIndex);
		}

		/**
         * Wrapper for Lattice::indexToC().
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         */
		int indexToC(int elementIndex) const{
			return lattice.indexToC(elementIndex);
		}

		/**
         * Wrapper for Lattice::indexToR().
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         */
		int indexToR(int elementIndex) const{
			return lattice.indexToR(elementIndex);
		}

		/**
         * Wrapper for Lattice::indexToL().
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         */
		int indexToL(int elementIndex) const{
			return lattice.indexToL(elementIndex);
		}

		/**
         * Wrapper for Lattice::indexToX().
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         */
		double indexToX(int elementIndex) const {
			return lattice.indexToX(elementIndex);
		}

		/**
         * Wrapper for Lattice::indexToY().
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         */
		double indexToY(int elementIndex) const {
			return lattice.indexToY(elementIndex);
		}

		/**
         * Wrapper for Lattice::indexToZ().
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         */
		double indexToZ(int elementIndex) const {
			return lattice.indexToZ(elementIndex);
		}

		/**
         * Wrapper for Lattice::getCoordinates().
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         * coordinates	| OUTPUT	| Coordinates of the element.
         */
		void getCoordinates(int elementIndex, vector<double> &coordinates) const {
			lattice.getCoordinates(elementIndex,coordinates);
		}

		/**
         * Wrapper for Lattice::euclideanDistance().
         *
         * Parameter		| in/out	| Comment
         * :---------		| :------	| :-------
         * elementIndex1	| INPUT		| Index of the first element of interest.
         * elementIndex2	| INPUT		| Index of the second element of interest.
         */
		double euclideanDistance(int elementIndex1, int elementIndex2) const {
			return lattice.euclideanDistance(elementIndex1, elementIndex2);
		}

		/**
         * Wrapper for Lattice::euclideanDistanceVector().
         *
         * Parameter		| in/out	| Comment
         * :---------		| :------	| :-------
         * elementIndex1	| INPUT		| Index of the first element of interest.
         * elementIndex2	| INPUT		| Index of the second element of interest.
         * distanceVector	| OUTPUT	| Vector representing the distance and direction from the first element to the second.
         */
		void euclideanDistanceVector(int elementIndex1, int elementIndex2, vector<double> &distanceVector) const {
			lattice.euclideanDistanceVector(elementIndex1, elementIndex2, distanceVector);
		}

		/**
         * Sets the intensity of the specified to the specified intensity.
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         * bandIndex	| INPUT		| Index of the band of interest.
         * intensity	| INPUT		| New intensity value.
         */
		template<class S>
		void setElement(int elementIndex, int bandIndex, S intensity) {
			if (!this->isValid(elementIndex, bandIndex)) {
				throw outsideImageException();
			}
			data[bandIndex * lattice.getNElements() + elementIndex] = T(intensity);
		}

		/**
         * Sets the intensity of the specified to the specified intensity.
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * rowIndex		| INPUT		| Row index of the element of interest.
         * columnIndex	| INPUT		| Column index of the element of interest.
         * layerIndex	| INPUT		| Layer index of the element of interest.
         * bandIndex	| INPUT		| Index of the band of interest.
         * intensity	| INPUT		| New intensity value.
         */
		template<class S>
		void setElement(int rowIndex, int columnIndex, int layerIndex, int bandIndex, S intensity) {
			int index = rclToIndex(rowIndex, columnIndex, layerIndex);
			this->setElement(index, bandIndex, intensity);
		}

		/**
         * Sets the intensity of the specified to the specified intensity.
         *
         * Parameter		| in/out	| Comment
         * :---------		| :------	| :-------
         * elementIndex		| INPUT		| Index of the element of interest.
         * intensityValues	| OUTPUT	| New intensity values for each modality band.
         */
		template<class S>
		void setElement(int elementIndex, vector<S> intensityValues) {
			if (!this->isValid(elementIndex)) {
				throw outsideImageException();
			}
			if (intensityValues.size() != nBands) {
				throw dimensionMismatchException();
			}
			for (int band = 0; band < this->nBands; band++) {
				data[band * lattice.getNElements() + elementIndex] = T(intensityValues[band]);
			}
		}

		/**
         * Sets the intensity of the specified to the specified intensity.
         *
         * Parameter		| in/out	| Comment
         * :---------		| :------	| :-------
         * rowIndex			| INPUT		| Row index of the element of interest.
         * columnIndex		| INPUT		| Column index of the element of interest.
         * layerIndex		| INPUT		| Layer index of the element of interest.
         * intensityValues	| OUTPUT	| New intensity values for each modality band.
         */
		template<class S>
		void setElement(int rowIndex, int columnIndex, int layerIndex, vector<S> intensityValues) {
			int index = rclToIndex(rowIndex, columnIndex, layerIndex);
			this->setElement(index, intensityValues);
		}

		/**
         * Wrapper for Lattice::getNeighbors().
         *
         * Parameter		| in/out	| Comment
         * :---------		| :------	| :-------
         * rowIndex			| INPUT		| Row index of the element of interest.
         * columnIndex		| INPUT		| Column index of the element of interest.
         * layerIndex		| INPUT		| Layer index of the element of interest.
         * neighborhoodSize	| INPUT		| Size of the requested neighborhood.
         * neighbors		| OUTPUT	| Extracted neighbors.
         */
		void getNeighbors(int rowIndex, int columnIndex, int layerIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const {
			lattice.getNeighbors(rowIndex, columnIndex, layerIndex, neighborhoodSize, neighbors);
		}

		/**
         * Wrapper for Lattice::getNeighbors().
         *
         * Parameter		| in/out	| Comment
         * :---------		| :------	| :-------
         * elementIndex		| INPUT		| Index of the element of interest.
         * neighborhoodSize	| INPUT		| Size of the requested neighborhood.
         * neighbors		| OUTPUT	| Extracted neighbors.
         */
		void getNeighbors(int elementIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const  {
			lattice.getNeighbors(elementIndex, neighborhoodSize, neighbors);
		}

		/**
		 * Returns the value of the requested spel in the requested band.
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * rowIndex		| INPUT		| Row index of the element of interest.
         * columnIndex	| INPUT		| Column index of the element of interest.
         * layerIndex	| INPUT		| Layer index of the element of interest.
         * bandIndex	| INPUT		| Index of the band of interest.
		 */
		T &operator()(int rowIndex, int columnIndex, int layerIndex, int bandIndex = 0) const {
			if (!this->isValid(rowIndex, columnIndex, layerIndex, bandIndex)) {
				throw outsideImageException();
			}
			return this->data[bandIndex * this->lattice.getNElements() + this->rclToIndex(rowIndex, columnIndex, layerIndex)];
		}

		/**
		 * Returns the value of the requested spel in the requested band.
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
         * bandIndex	| INPUT		| Index of the band of interest.
		 */
		T &operator()(int elementIndex, int bandIndex) const {
			if (!this->isValid(elementIndex, bandIndex)) {
				throw outsideImageException();
			}
			return this->data[bandIndex * lattice.getNElements() + elementIndex];
		}

		/**
		 * Returns the value in each band of the requested spel.
         *
         * Parameter	| in/out	| Comment
         * :---------	| :------	| :-------
         * elementIndex	| INPUT		| Index of the element of interest.
		 */
		vector<T> operator[](int elementIndex) const {
			if (!this->isValid(elementIndex)) {
				throw outsideImageException();
			}
			vector<T> intensityValues;
			for (int band = 0; band < this->nBands; band++) {
				intensityValues.push_back(this->data[band * this->lattice.getNElements() + elementIndex]);
			}
			return intensityValues;
		}
	};

}
#endif
