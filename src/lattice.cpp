#include "lattice.h"
#include "exception.h"
#include <cmath> // for cbrt and round
#include <typeinfo> // for typeid
#include "defs.h"

namespace LatticeLib {
    Lattice::Lattice(int rows, int columns, int layers, double density) {
        nLayers = layers;
        nColumns = columns;
        nRows = rows;
        latticeDensity = density;
    }
    Lattice::Lattice(const Lattice &original) {
        nLayers = original.nLayers;
        nColumns = original.nColumns;
        nRows = original.nRows;
        latticeDensity = original.latticeDensity;
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
    double Lattice::getDensity() const {
        return latticeDensity;
    }
    bool Lattice::isValid(int elementIndex) const {
        return ((elementIndex >= 0 && elementIndex < nColumns * nRows * nLayers));
    }
    bool Lattice::isValid(int rowIndex, int columnIndex, int layerIndex) const {
        return ((rowIndex >= 0 && rowIndex < nRows) && (columnIndex >= 0 && columnIndex < nColumns) && (layerIndex >= 0 && layerIndex < nLayers));
    }
    int Lattice::rclToIndex(int rowIndex, int columnIndex, int layerIndex) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        return (nRows * nColumns * layerIndex + nColumns * rowIndex + columnIndex);
    }
    int Lattice::indexToC(int elementIndex) const {
        if (!this->isValid(elementIndex)) {
            throw outOfRangeException();
        }
        return (elementIndex % (nRows * nColumns)) % nColumns;
    }
    int Lattice::indexToR(int elementIndex) const {
        if (!this->isValid(elementIndex)) {
            throw outOfRangeException();
        }
        return (elementIndex % (nRows * nColumns)) / nColumns;
    }
    int Lattice::indexToL(int elementIndex) const {
        if (!this->isValid(elementIndex)) {
            throw outOfRangeException();
        }
        return elementIndex / (nRows * nColumns);
    }
    void Lattice::getCoordinates(int elementIndex, vector<double> &coordinates) const {
        coordinates.clear();
        coordinates.push_back(this->indexToX(elementIndex));
        coordinates.push_back(this->indexToY(elementIndex));
        coordinates.push_back(this->indexToZ(elementIndex));
    }
    double Lattice::euclideanDistance(int elementIndex1, int elementIndex2) const {
        double xDistance, yDistance, zDistance;
        xDistance = this->indexToX(elementIndex1) - this->indexToX(elementIndex2);
        yDistance = this->indexToY(elementIndex1) - this->indexToY(elementIndex2);
        zDistance = this->indexToZ(elementIndex1) - this->indexToZ(elementIndex2);
        return sqrt(xDistance * xDistance + yDistance * yDistance + zDistance * zDistance);
    }
    void Lattice::euclideanDistanceVector(int elementIndex1, int elementIndex2, vector<double> &distanceVector) const {
        distanceVector.clear();
        distanceVector.push_back(this->indexToX(elementIndex2) - this->indexToX(elementIndex1));
        distanceVector.push_back(this->indexToY(elementIndex2) - this->indexToY(elementIndex1));
        distanceVector.push_back(this->indexToZ(elementIndex2) - this->indexToZ(elementIndex1));
    }
    bool Lattice::operator==(const Lattice &rhs) const {
        return (typeid(*this) == typeid(rhs) && nColumns == rhs.getNColumns() && nRows == rhs.getNRows() && nLayers == rhs.getNLayers() && latticeDensity ==
                                                                                                                                           rhs.getDensity());
    }
    bool Lattice::operator!=(const Lattice &rhs) const {
        return !((*this)==rhs);
    }
}
