#include "lattice.h"
#include "exception.h"
#include <cmath> // for cbrt and round
#include <typeinfo> // for typeid
#include "defs.h"

namespace LatticeLib {
    Lattice::Lattice(int rows, int columns, int layers, double scale) {
        nLayers = layers;
        nColumns = columns;
        nRows = rows;
        scaleFactor = scale;
    }
    Lattice::Lattice(const Lattice &original) {
        nLayers = original.nLayers;
        nColumns = original.nColumns;
        nRows = original.nRows;
        scaleFactor = original.scaleFactor;
    }
    Lattice::~Lattice() {}

    int Lattice::getNElements() const {
        return nColumns * nRows * nLayers;
    }
    int Lattice::getNColumns() const {
        return nColumns;
    }
    int Lattice::getNRows() const {
        return nRows;
    }
    int Lattice::getNLayers() const {
        return nLayers;
    }
    double Lattice::getScaleFactor() const {
        return scaleFactor;
    }
    bool Lattice::isValid(int index) const {
        return ((index >= 0 && index < nColumns * nRows * nLayers));
    }
    bool Lattice::isValid(int row, int column, int layer) const {
        return ((row >= 0 && row < nRows) && (column >= 0 && column < nColumns) && (layer >= 0 && layer < nLayers));
    }
    int Lattice::rclToIndex(int row, int column, int layer) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideImageException();
        }
        return (nRows * nColumns * layer + nColumns * row + column);
    }
    int Lattice::indexToC(int index) const {
        if (!this->isValid(index)) {
            throw outsideImageException();
        }
        return (index % (nRows * nColumns)) % nColumns;
    }
    int Lattice::indexToR(int index) const {
        if (!this->isValid(index)) {
            throw outsideImageException();
        }
        return (index % (nRows * nColumns)) / nColumns;
    }
    int Lattice::indexToL(int index) const {
        if (!this->isValid(index)) {
            throw outsideImageException();
        }
        return index / (nRows * nColumns);
    }
    void Lattice::getCoordinates(int index, vector<double> &coordinates) const {
        coordinates.clear();
        coordinates.push_back(this->indexToX(index));
        coordinates.push_back(this->indexToY(index));
        coordinates.push_back(this->indexToZ(index));
    }
    double Lattice::euclideanDistance(int index1, int index2) const {
        double xDistance, yDistance, zDistance;
        xDistance = this->indexToX(index1) - this->indexToX(index2);
        yDistance = this->indexToY(index1) - this->indexToY(index2);
        zDistance = this->indexToZ(index1) - this->indexToZ(index2);
        return sqrt(xDistance * xDistance + yDistance * yDistance + zDistance * zDistance);
    }
    void Lattice::euclideanDistanceVector(int index1, int index2, vector<double> &distanceVector) const {
        distanceVector.clear();
        distanceVector.push_back(this->indexToX(index2) - this->indexToX(index1));
        distanceVector.push_back(this->indexToY(index2) - this->indexToY(index1));
        distanceVector.push_back(this->indexToZ(index2) - this->indexToZ(index1));
    }
    bool Lattice::operator==(const Lattice &rhs) const {
        return (typeid(*this) == typeid(rhs) && nColumns == rhs.getNColumns() && nRows == rhs.getNRows() && nLayers == rhs.getNLayers() && scaleFactor == rhs.getScaleFactor());
    }
    bool Lattice::operator!=(const Lattice &rhs) const {
        return !((*this)==rhs);
    }
}
