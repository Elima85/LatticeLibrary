#include "fcclattice.h"
#include "defs.h"
#include "miscellaneous.h"
#include "exception.h"

using namespace std;

namespace CImage {

    FCCLattice::FCCLattice(int rows, int columns, int layers, double scale) : Lattice(rows, columns, layers, scale) {};
    FCCLattice::FCCLattice(const FCCLattice &original) : Lattice(original) {};
    FCCLattice::~FCCLattice() {};

    double FCCLattice::indexToX(int index) const {
        int row, column, layer;
        double x;
        row = this->indexToR(index);
        column = this->indexToC(index);
        layer = this->indexToL(index);
        x = this->scaleFactor * ((1 + !IS_EVEN(layer + row)) * FCCOFFSET + column * FCCPOINTDISTANCE);
        return x;
    }
    double FCCLattice::indexToY(int index) const {
        int row;
        double y;
        row = this->indexToR(index);
        y = this->scaleFactor * ((row + 1) * FCCOFFSET);
        return y;
    }
    double FCCLattice::indexToZ(int index) const {
        int layer = this->indexToL(index);
        double z = this->scaleFactor * ((layer + 1) * FCCOFFSET);
        return z;
    }
    double FCCLattice::getWidth() const {
        return (1 + ((this->nRows > 1) || (this->nLayers > 1))) * this->indexToX(0) + this->indexToX(this->rclToIndex(0, this->nColumns - 1, 0));
    }
    double FCCLattice::getHeight() const {
        return this->indexToY(this->rclToIndex(this->nRows - 1, 0, 0)) + this->indexToY(0);
    }
    double FCCLattice::getDepth() const {
        return this->indexToZ(0) + indexToZ(this->rclToIndex(0, 0, this->nLayers - 1));
    }
    void FCCLattice::get12Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideRangeException();
        }
        neighbors.clear();
        if ((layer % 2) != 1) {
            if ((row % 2) != 1) {
                if (this->isValid(row - 1, column, layer - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(row - 1, column, layer - 1))); //,FCCD1)); // top front
                }
                if (this->isValid(row - 1, column - 1, layer)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(row - 1, column - 1, layer))); //,FCCD1)); // top left
                }
                if (this->isValid(row - 1, column, layer + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(row - 1, column, layer + 1))); //,FCCD1)); // top back
                }
                if (this->isValid(row - 1, column, layer)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(row - 1, column, layer))); //,FCCD1)); // top right
                }
                if (this->isValid(row, column - 1, layer - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(row, column - 1, layer - 1))); //,FCCD1)); // front left
                }
                if (this->isValid(row, column - 1, layer + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(row, column - 1, layer + 1))); //,FCCD1)); // back left
                }
                if (this->isValid(row, column, layer + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(row, column, layer + 1))); //,FCCD1)); // back right
                }
                if (this->isValid(row, column, layer - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(row, column, layer - 1))); //,FCCD1)); // front right
                }
                if (this->isValid(row + 1, column, layer - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(row + 1, column, layer - 1))); //,FCCD1)); // bottom front
                }
                if (this->isValid(row + 1, column - 1, layer)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(row + 1, column - 1, layer))); //,FCCD1)); // bottom left
                }
                if (this->isValid(row + 1, column, layer + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(row + 1, column, layer + 1))); //,FCCD1)); // bottom back
                }
                if (this->isValid(row + 1, column, layer)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(row + 1, column, layer))); //,FCCD1)); // bottom right
                }
            }
            else { //offset row
                if (this->isValid(row - 1, column, layer - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(row - 1, column, layer - 1))); //,FCCD1)); // top front
                }
                if (this->isValid(row - 1, column, layer)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(row - 1, column, layer))); //,FCCD1)); // top left
                }
                if (this->isValid(row - 1, column, layer + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(row - 1, column, layer + 1))); //,FCCD1)); // top back
                }
                if (this->isValid(row - 1, column + 1, layer)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(row - 1, column + 1, layer))); //,FCCD1)); // top right
                }
                if (this->isValid(row, column, layer - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(row, column, layer - 1))); //,FCCD1)); // front left
                }
                if (this->isValid(row, column, layer + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(row, column, layer + 1))); //,FCCD1)); // back left
                }
                if (this->isValid(row, column + 1, layer + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(row, column + 1, layer + 1))); //,FCCD1)); // back right
                }
                if (this->isValid(row, column + 1, layer - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(row, column + 1, layer - 1))); //,FCCD1)); // front right
                }
                if (this->isValid(row + 1, column, layer - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(row + 1, column, layer - 1))); //,FCCD1)); // bottom front
                }
                if (this->isValid(row + 1, column, layer)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(row + 1, column, layer))); //,FCCD1)); // bottom left
                }
                if (this->isValid(row + 1, column, layer + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(row + 1, column, layer + 1))); //,FCCD1)); // bottom back
                }
                if (this->isValid(row + 1, column + 1, layer)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(row + 1, column + 1, layer))); //,FCCD1)); // bottom right
                }
            }
        }
        else { // offset layer
            if ((row % 2) == 1) { //aligned row
                if (this->isValid(row - 1, column, layer - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(row - 1, column, layer - 1))); //,FCCD1)); // top front
                }
                if (this->isValid(row - 1, column - 1, layer)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(row - 1, column - 1, layer))); //,FCCD1)); // top left
                }
                if (this->isValid(row - 1, column, layer + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(row - 1, column, layer + 1))); //,FCCD1)); // top back
                }
                if (this->isValid(row - 1, column, layer)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(row - 1, column, layer))); //,FCCD1)); // top right
                }
                if (this->isValid(row, column - 1, layer - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(row, column - 1, layer - 1))); //,FCCD1)); // front left
                }
                if (this->isValid(row, column - 1, layer + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(row, column - 1, layer + 1))); //,FCCD1)); // back left
                }
                if (this->isValid(row, column, layer + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(row, column, layer + 1))); //,FCCD1)); // back right
                }
                if (this->isValid(row, column, layer - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(row, column, layer - 1))); //,FCCD1)); // front right
                }
                if (this->isValid(row + 1, column, layer - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(row + 1, column, layer - 1))); //,FCCD1)); // bottom front
                }
                if (this->isValid(row + 1, column - 1, layer)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(row + 1, column - 1, layer))); //,FCCD1)); // bottom left
                }
                if (this->isValid(row + 1, column, layer + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(row + 1, column, layer + 1))); //,FCCD1)); // bottom back
                }
                if (this->isValid(row + 1, column, layer)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(row + 1, column, layer))); //,FCCD1)); // bottom right
                }
            }
            else { //offset row
                if (this->isValid(row - 1, column, layer - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(row - 1, column, layer - 1))); //,FCCD1)); // top front
                }
                if (this->isValid(row - 1, column, layer)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(row - 1, column, layer))); //,FCCD1)); // top left
                }
                if (this->isValid(row - 1, column, layer + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(row - 1, column, layer + 1))); //,FCCD1)); // top back
                }
                if (this->isValid(row - 1, column + 1, layer)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(row - 1, column + 1, layer))); //,FCCD1)); // top right
                }
                if (this->isValid(row, column, layer - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(row, column, layer - 1))); //,FCCD1)); // front left
                }
                if (this->isValid(row, column, layer + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(row, column, layer + 1))); //,FCCD1)); // back left
                }
                if (this->isValid(row, column + 1, layer + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(row, column + 1, layer + 1))); //,FCCD1)); // back right
                }
                if (this->isValid(row, column + 1, layer - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(row, column + 1, layer - 1))); //,FCCD1)); // front right
                }
                if (this->isValid(row + 1, column, layer - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(row + 1, column, layer - 1))); //,FCCD1)); // bottom front
                }
                if (this->isValid(row + 1, column, layer)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(row + 1, column, layer))); //,FCCD1)); // bottom left
                }
                if (this->isValid(row + 1, column, layer + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(row + 1, column, layer + 1))); //,FCCD1)); // bottom back
                }
                if (this->isValid(row + 1, column + 1, layer)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(row + 1, column + 1, layer))); //,FCCD1)); // bottom right
                }
            }
        }
    }
    void FCCLattice::get12Neighbors(int index, vector<Neighbor> &neighbors) const {
        get12Neighbors(this->indexToR(index), this->indexToC(index), this->indexToL(index), neighbors);
    }
    void FCCLattice::get18Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideRangeException();
        }
        neighbors.clear();
        get12Neighbors(row, column, layer, neighbors);
        if ((layer % 2) != 1) {
            if ((row % 2) != 1) {
                if (this->isValid(row - 2, column, layer)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(row - 2, column, layer))); //,FCCD2)); // top
                }
                if (this->isValid(row, column, layer - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(row, column, layer - 2))); //,FCCD2)); // front
                }
                if (this->isValid(row, column - 1, layer)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(row, column - 1, layer))); //,FCCD2)); // left
                }
                if (this->isValid(row, column, layer + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(row, column, layer + 2))); //,FCCD2)); // back
                }
                if (this->isValid(row, column + 1, layer)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(row, column + 1, layer))); //,FCCD2)); // right
                }
                if (this->isValid(row + 2, column, layer)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(row + 2, column, layer))); //,FCCD2)); // bottom
                }
            }
            else { //offset row
                if (this->isValid(row - 2, column, layer)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(row - 2, column, layer))); //,FCCD2)); // top
                }
                if (this->isValid(row, column, layer - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(row, column, layer - 2))); //,FCCD2)); // front
                }
                if (this->isValid(row, column - 1, layer)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(row, column - 1, layer))); //,FCCD2)); // left
                }
                if (this->isValid(row, column, layer + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(row, column, layer + 2))); //,FCCD2)); // back
                }
                if (this->isValid(row, column + 1, layer)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(row, column + 1, layer))); //,FCCD2)); // right
                }
                if (this->isValid(row + 2, column, layer)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(row + 2, column, layer))); //,FCCD2)); // bottom
                }
            }
        }
        else { // offset layer
            if ((row % 2) == 1) { //aligned row
                if (this->isValid(row - 2, column, layer)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(row - 2, column, layer))); //,FCCD2)); // top
                }
                if (this->isValid(row, column, layer - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(row, column, layer - 2))); //,FCCD2)); // front
                }
                if (this->isValid(row, column - 1, layer)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(row, column - 1, layer))); //,FCCD2)); // left
                }
                if (this->isValid(row, column, layer + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(row, column, layer + 2))); //,FCCD2)); // back
                }
                if (this->isValid(row, column + 1, layer)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(row, column + 1, layer))); //,FCCD2)); // right
                }
                if (this->isValid(row + 2, column, layer)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(row + 2, column, layer))); //,FCCD2)); // bottom
                }
            }
            else { //offset row
                if (this->isValid(row - 2, column, layer)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(row - 2, column, layer))); //,FCCD2)); // top
                }
                if (this->isValid(row, column, layer - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(row, column, layer - 2))); //,FCCD2)); // front
                }
                if (this->isValid(row, column - 1, layer)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(row, column - 1, layer))); //,FCCD2)); // left
                }
                if (this->isValid(row, column, layer + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(row, column, layer + 2))); //,FCCD2)); // back
                }
                if (this->isValid(row, column + 1, layer)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(row, column + 1, layer))); //,FCCD2)); // right
                }
                if (this->isValid(row + 2, column, layer)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(row + 2, column, layer))); //,FCCD2)); // bottom
                }
            }
        }
    }
    void FCCLattice::get18Neighbors(int index, vector<Neighbor> &neighbors) const {
        get18Neighbors(this->indexToR(index), this->indexToC(index), this->indexToL(index), neighbors);
    }
    void FCCLattice::getNeighbors(int row, int column, int layer, int nNeighbors, vector<Neighbor> &neighbors) const {
        switch (nNeighbors) {
            case 12:
                get12Neighbors(row, column, layer, neighbors);
                break;
            case 18:
                get18Neighbors(row, column, layer, neighbors);
                break;
            default:
                throw neighborhoodSizeException();
        }
    }
    void FCCLattice::getNeighbors(int index, int nNeighbors, vector<Neighbor> &neighbors) const {
        switch (nNeighbors) {
            case 12:
                get12Neighbors(index, neighbors);
                break;
            case 18:
                get18Neighbors(index, neighbors);
                break;
            default:
                throw neighborhoodSizeException();
        }
    }
}