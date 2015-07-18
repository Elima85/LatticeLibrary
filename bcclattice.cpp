#include "bcclattice.h"
#include "defs.h"
#include "exception.h"
#include <cmath>

using namespace std;

namespace LatticeLib {

    BCCLattice::BCCLattice(int rows, int columns, int layers, double density) : Lattice(rows, columns, layers, density) {};
    BCCLattice::BCCLattice(const BCCLattice &original) : Lattice(original) {};
    BCCLattice::~BCCLattice() {};

    double BCCLattice::indexToX(int index) const {
        int c, l;
        double x;
        double scaleFactor = cbrt(1 / this->latticeDensity);
        c = this->indexToC(index);
        l = this->indexToL(index);
        x = scaleFactor * ((1 + !IS_EVEN(l)) * BCCOFFSET + c * BCCSQFACEDISTANCE);
        return x;
    }
    double BCCLattice::indexToY(int index) const {
        int r, l;
        double y;
        double scaleFactor = cbrt(1 / this->latticeDensity);
        r = this->indexToR(index);
        l = this->indexToL(index);
        y = scaleFactor * ((1 + !IS_EVEN(l)) * BCCOFFSET + r * BCCSQFACEDISTANCE);
        return y;
    }
    double BCCLattice::indexToZ(int index) const {
        int l = this->indexToL(index);
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

    /* TODO: double coverageToInternalDistance(double coverage) const {
        coverageIndex = round(coverage * 255);
        double scaleFactor = this->latticeDensity; // TODO: Find correct scaleFactor!
        return subSpelDistanceVoronoiBCC[coverageIndex] * [function of scaleFactor];
    }*/
    void BCCLattice::get8Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideRangeException();
        }
        neighbors.clear();
        if (IS_EVEN(layer)) {
            if (this->isValid(row - 1, column - 1, layer - 1)) {
                neighbors.push_back(Neighbor(0, this->rclToIndex(row - 1, column - 1, layer - 1))); // top left front
            }
            if (this->isValid(row - 1, column, layer - 1)) {
                neighbors.push_back(Neighbor(1, this->rclToIndex(row - 1, column, layer - 1))); // top right front
            }
            if (this->isValid(row, column - 1, layer - 1)) {
                neighbors.push_back(Neighbor(2, this->rclToIndex(row, column - 1, layer - 1))); // bottom left front
            }
            if (this->isValid(row, column, layer - 1)) {
                neighbors.push_back(Neighbor(3, this->rclToIndex(row, column, layer - 1))); // bottom right front
            }
            if (this->isValid(row - 1, column - 1, layer + 1)) {
                neighbors.push_back(Neighbor(4, this->rclToIndex(row - 1, column - 1, layer + 1))); // top left back
            }
            if (this->isValid(row - 1, column, layer + 1)) {
                neighbors.push_back(Neighbor(5, this->rclToIndex(row - 1, column, layer + 1))); // top right back
            }
            if (this->isValid(row, column - 1, layer + 1)) {
                neighbors.push_back(Neighbor(6, this->rclToIndex(row, column - 1, layer + 1))); // bottom left back
            }
            if (this->isValid(row, column, layer + 1)) {
                neighbors.push_back(Neighbor(7, this->rclToIndex(row, column, layer + 1))); // bottom right back
            }
        }
        else { // offset layers
            if (this->isValid(row, column, layer - 1)) {
                neighbors.push_back(Neighbor(0, this->rclToIndex(row, column, layer - 1))); // top left front
            }
            if (this->isValid(row, column + 1, layer - 1)) {
                neighbors.push_back(Neighbor(1, this->rclToIndex(row, column + 1, layer - 1))); // top right front
            }
            if (this->isValid(row + 1, column, layer - 1)) {
                neighbors.push_back(Neighbor(2, this->rclToIndex(row + 1, column, layer - 1))); // bottom left front
            }
            if (this->isValid(row + 1, column + 1, layer - 1)) {
                neighbors.push_back(Neighbor(3, this->rclToIndex(row + 1, column + 1, layer - 1))); // bottom right front
            }
            if (this->isValid(row, column, layer + 1)) {
                neighbors.push_back(Neighbor(4, this->rclToIndex(row, column, layer + 1))); // top left back
            }
            if (this->isValid(row, column + 1, layer + 1)) {
                neighbors.push_back(Neighbor(5, this->rclToIndex(row, column + 1, layer + 1))); // top right back
            }
            if (this->isValid(row + 1, column, layer + 1)) {
                neighbors.push_back(Neighbor(6, this->rclToIndex(row + 1, column, layer + 1))); // bottom left back
            }
            if (this->isValid(row + 1, column + 1, layer + 1)) {
                neighbors.push_back(Neighbor(7, this->rclToIndex(row + 1, column + 1, layer + 1))); // bottom right back
            }
        }
    }
    void BCCLattice::get8Neighbors(int index, vector<Neighbor> &neighbors) const {
        get8Neighbors(this->indexToR(index), this->indexToC(index), this->indexToL(index), neighbors);
    }
    void BCCLattice::get14Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideRangeException();
        }
        neighbors.clear();
        get8Neighbors(row, column, layer, neighbors);
        if (this->isValid(row - 1, column, layer)) {
            neighbors.push_back(Neighbor(8, this->rclToIndex(row - 1, column, layer))); // top
        }
        if (this->isValid(row, column, layer - 2)) {
            neighbors.push_back(Neighbor(9, this->rclToIndex(row, column, layer - 2))); // front
        }
        if (this->isValid(row, column - 1, layer)) {
            neighbors.push_back(Neighbor(10, this->rclToIndex(row, column - 1, layer))); // left
        }
        if (this->isValid(row, column, layer + 2)) {
            neighbors.push_back(Neighbor(11, this->rclToIndex(row, column, layer + 2))); // back
        }
        if (this->isValid(row, column + 1, layer)) {
            neighbors.push_back(Neighbor(12, this->rclToIndex(row, column + 1, layer))); // right
        }
        if (this->isValid(row + 1, column, layer)) {
            neighbors.push_back(Neighbor(13, this->rclToIndex(row + 1, column, layer))); // bottom
        }
    }
    void BCCLattice::get14Neighbors(int index, vector<Neighbor> &neighbors) const {
        get14Neighbors(this->indexToR(index), this->indexToC(index), this->indexToL(index), neighbors);
    }
    void BCCLattice::getNeighbors(int row, int column, int layer, int neighborhoodSize, vector <Neighbor> &neighbors) const {
        switch (neighborhoodSize) {
            case 8:
                get8Neighbors(row, column, layer, neighbors);
                break;
            case 14:
                get14Neighbors(row, column, layer, neighbors);
                break;
            default:
                throw neighborhoodSizeException();
        }
    }
    void BCCLattice::getNeighbors(int index, int neighborhoodSize, vector <Neighbor> &neighbors) const {
        switch (neighborhoodSize) {
            case 8:
                get8Neighbors(index, neighbors);
                break;
            case 14:
                get14Neighbors(index, neighbors);
                break;
            default:
                throw neighborhoodSizeException();
        }
    }
}