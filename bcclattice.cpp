#include "bcclattice.h"
#include "defs.h"
#include "exception.h"
#include <cmath>
#include "linearinterpolation.h"
#include <stdio.h> // DEBUG
#include "pnorm.h"
#include <vector>
#include "vectoroperators.h"

using namespace std;

namespace LatticeLib {

    BCCLattice::BCCLattice(int rows, int columns, int layers, double density) : Lattice(rows, columns, layers, density) {};
    BCCLattice::BCCLattice(const BCCLattice &original) : Lattice(original) {};
    BCCLattice::~BCCLattice() {};

    double BCCLattice::indexToX(int elementIndex) const {
        int c, l;
        double x;
        double scaleFactor = cbrt(1 / this->latticeDensity);
        c = this->indexToC(elementIndex);
        l = this->indexToL(elementIndex);
        x = scaleFactor * ((!IS_EVEN(l)) * BCCOFFSET + c * BCCSQFACEDISTANCE);
        return x;
    }
    double BCCLattice::indexToY(int elementIndex) const {
        int r, l;
        double y;
        double scaleFactor = cbrt(1 / this->latticeDensity);
        r = this->indexToR(elementIndex);
        l = this->indexToL(elementIndex);
        y = scaleFactor * ((!IS_EVEN(l)) * BCCOFFSET + r * BCCSQFACEDISTANCE);
        return y;
    }
    double BCCLattice::indexToZ(int elementIndex) const {
        int l = this->indexToL(elementIndex);
        double scaleFactor = cbrt(1 / this->latticeDensity);
        double z = scaleFactor * (l) * BCCOFFSET;
        return z;
    }
    int BCCLattice::coordinatesToIndex(vector<double> coordinates) const {
        if (coordinates.size() != 3) {
            throw incompatibleParametersException();
        }
        double scaleFactor = cbrt(1 / this->latticeDensity);
        int prelColumnIndex = MAX(0, MIN(this->nColumns - 1, round(coordinates[0] / (scaleFactor * BCCSQFACEDISTANCE))));
        int prelRowIndex = MAX(0, MIN(this->nRows - 1, round(coordinates[1] / (scaleFactor * BCCSQFACEDISTANCE))));
        int prelLayerIndex = MAX(0, MIN(this->nLayers - 1, round(coordinates[2] / (scaleFactor * BCCOFFSET))));
        int prelIndex = this->rclToIndex(prelRowIndex, prelColumnIndex, prelLayerIndex);
        vector<double> potentialCoordinates;
        this->getCoordinates(prelIndex, potentialCoordinates);
        PNorm<double> norm(2);
        double smallestDistance = norm.compute(coordinates - potentialCoordinates);
        vector<Neighbor> neighbors;
        this->getNeighbors(prelIndex, 14, neighbors);
        for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
            this->getCoordinates(neighbors[neighborIndex].getElementIndex(), potentialCoordinates);
            double prelDistance = norm.compute(coordinates - potentialCoordinates);
            if (prelDistance < smallestDistance) {
                smallestDistance = prelDistance;
                prelIndex = neighbors[neighborIndex].getElementIndex();
            }
        }
        return prelIndex;
    }
    double BCCLattice::getElementWidth() const {
        return BCCSQFACEDISTANCE * cbrt(1 / this->latticeDensity);
    }
    double BCCLattice::getElementHeight() const {
        return BCCSQFACEDISTANCE * cbrt(1 / this->latticeDensity);
    }
    double BCCLattice::getElementDepth() const {
        return BCCSQFACEDISTANCE * cbrt(1 / this->latticeDensity);
    }
    double BCCLattice::getWidth() const {
        return (this->nColumns * BCCSQFACEDISTANCE + (this->nLayers > 1) * BCCOFFSET) * cbrt(1 / this->latticeDensity);
    }
    double BCCLattice::getHeight() const {
        return (this->nRows * BCCSQFACEDISTANCE + (this->nLayers > 1) * BCCOFFSET) * cbrt(1 / this->latticeDensity);
    }
    double BCCLattice::getDepth() const {
        return (this->nLayers + 1) * BCCOFFSET * cbrt(1 / this->latticeDensity);
    }
    double BCCLattice::approximateDistanceToElementCenter(double coverage) const {
        //std::cout << "Inside BCCLattice::approximateDistanceToElementCenter()." << std::endl; // DEBUG
        LinearInterpolation<int, double> interpolation;
        double coveragePosition = coverage * 127;
        vector<int> bounds;
        bounds.push_back(floor(coveragePosition));
        bounds.push_back(ceil(coveragePosition));
        vector<double> values;
        values.push_back(distanceTableBCC[bounds[0]]);
        values.push_back(distanceTableBCC[bounds[1]]);
        double scaleFactor = cbrt(1 / getDensity());
        return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
    }
    double BCCLattice::approximateIntersectionArea(double coverage) const {
        double coveragePosition = coverage * 255;
        vector<int> bounds;
        bounds.push_back(floor(coveragePosition));
        bounds.push_back(ceil(coveragePosition));
        vector<double> values;
        values.push_back(surfaceAreaTableBCC[bounds[0]]);
        values.push_back(surfaceAreaTableBCC[bounds[1]]);
        double scaleFactor = cbrt(1 / getDensity());
        scaleFactor = scaleFactor * scaleFactor;
        LinearInterpolation<int, double> interpolation;
        return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
    }
    void BCCLattice::get8Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        neighbors.clear();
        if (IS_EVEN(layerIndex)) {
            if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex - 1)) {
                neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex - 1))); // top left front
            }
            if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
                neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); // top right front
            }
            if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 1)) {
                neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 1))); // bottom left front
            }
            if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); // bottom right front
            }
            if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex + 1)) {
                neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex + 1))); // top left back
            }
            if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
                neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); // top right back
            }
            if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 1)) {
                neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 1))); // bottom left back
            }
            if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); // bottom right back
            }
        }
        else { // offset layers
            if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); // top left front
            }
            if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 1)) {
                neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 1))); // top right front
            }
            if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
                neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); // bottom left front
            }
            if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex - 1)) {
                neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex - 1))); // bottom right front
            }
            if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); // top left back
            }
            if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 1)) {
                neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 1))); // top right back
            }
            if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
                neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); // bottom left back
            }
            if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex + 1)) {
                neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex + 1))); // bottom right back
            }
        }
    }
    void BCCLattice::get8Neighbors(int elementIndex, vector<Neighbor> &neighbors) const {
        get8Neighbors(this->indexToR(elementIndex), this->indexToC(elementIndex), this->indexToL(elementIndex), neighbors);
    }
    void BCCLattice::get14Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        neighbors.clear();
        get8Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); // top
        }
        if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); // front
        }
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); // left
        }
        if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); // back
        }
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); // right
        }
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); // bottom
        }
    }
    void BCCLattice::get14Neighbors(int elementIndex, vector<Neighbor> &neighbors) const {
        get14Neighbors(this->indexToR(elementIndex), this->indexToC(elementIndex), this->indexToL(elementIndex), neighbors);
    }
    void BCCLattice::getNeighbors(int rowIndex, int columnIndex, int layerIndex, int neighborhoodSize, vector <Neighbor> &neighbors) const {
        switch (neighborhoodSize) {
            case 8:
                get8Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
                break;
            case 14:
                get14Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
                break;
            default:
                throw incompatibleParametersException();
        }
    }
    void BCCLattice::getNeighbors(int elementIndex, int neighborhoodSize, vector <Neighbor> &neighbors) const {
        switch (neighborhoodSize) {
            case 8:
                get8Neighbors(elementIndex, neighbors);
                break;
            case 14:
                get14Neighbors(elementIndex, neighbors);
                break;
            default:
                throw incompatibleParametersException();
        }
    }
}