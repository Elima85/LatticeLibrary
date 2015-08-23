#include "bcclattice.h"
#include "defs.h"
#include "exception.h"
#include <cmath>
#include "linearinterpolation.h"
#include <stdio.h> // DEBUG

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
        x = scaleFactor * ((1 + !IS_EVEN(l)) * BCCOFFSET + c * BCCSQFACEDISTANCE);
        return x;
    }
    double BCCLattice::indexToY(int elementIndex) const {
        int r, l;
        double y;
        double scaleFactor = cbrt(1 / this->latticeDensity);
        r = this->indexToR(elementIndex);
        l = this->indexToL(elementIndex);
        y = scaleFactor * ((1 + !IS_EVEN(l)) * BCCOFFSET + r * BCCSQFACEDISTANCE);
        return y;
    }
    double BCCLattice::indexToZ(int elementIndex) const {
        int l = this->indexToL(elementIndex);
        double scaleFactor = cbrt(1 / this->latticeDensity);
        double z = scaleFactor * (1 + l) * BCCOFFSET;
        return z;
    }
    double BCCLattice::getWidth() const {
        return this->indexToX(0) + this->indexToX(this->rclToIndex(0, this->nColumns - 1, (this->nLayers > 1)));
    }
    double BCCLattice::getHeight() const {
        return this->indexToY(0) + this->indexToY(this->rclToIndex(this->nRows - 1, 0, (this->nLayers > 1)));
    }
    double BCCLattice::getDepth() const {
        return this->indexToZ(0) + this->indexToZ(this->getNElements() - 1);
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
        //std::cout << "Inside BCCLattice::approximateIntersectionArea()." << std::endl; // DEBUG
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
        //std::cout << "coverage: " << coverage << ", index: " << coveragePosition << ", lower bound: " << values[0] << ", upper bound: " << values[1] << std::endl;
        //std::cout << "interpolated value: " << interpolation.apply(bounds, values, coveragePosition) << std::endl;
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