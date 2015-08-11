#include "fcclattice.h"
#include "defs.h"
#include "exception.h"
#include <cmath>
#include "linearinterpolation.h"

using namespace std;

namespace LatticeLib {

    FCCLattice::FCCLattice(int rows, int columns, int layers, double density) : Lattice(rows, columns, layers, density) {};
    FCCLattice::FCCLattice(const FCCLattice &original) : Lattice(original) {};
    FCCLattice::~FCCLattice() {};

    double FCCLattice::indexToX(int elementIndex) const {
        int row, column, layer;
        double x;
        double scaleFactor = cbrt(1 / this->latticeDensity);
        row = this->indexToR(elementIndex);
        column = this->indexToC(elementIndex);
        layer = this->indexToL(elementIndex);
        x = scaleFactor * ((1 + !IS_EVEN(layer + row)) * FCCOFFSET + column * FCCPOINTDISTANCE);
        return x;
    }
    double FCCLattice::indexToY(int elementIndex) const {
        int row;
        double y;
        double scaleFactor = cbrt(1 / this->latticeDensity);
        row = this->indexToR(elementIndex);
        y = scaleFactor * ((row + 1) * FCCOFFSET);
        return y;
    }
    double FCCLattice::indexToZ(int elementIndex) const {
        int layer = this->indexToL(elementIndex);
        double scaleFactor = cbrt(1 / this->latticeDensity);
        double z = scaleFactor * ((layer + 1) * FCCOFFSET);
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
    double FCCLattice::approximateDistanceToElementCenter(double coverage) const {
        LinearInterpolation<int, double> interpolation;
        double coveragePosition = coverage * 128;
        vector<int> bounds;
        bounds.push_back(floor(coveragePosition));
        bounds.push_back(ceil(coveragePosition));
        vector<double> values;
        values.push_back(distanceTableFCC[bounds[0]]);
        values.push_back(distanceTableFCC[bounds[1]]);
        double scaleFactor = cbrt(1 / getDensity());
        return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
    }
    double FCCLattice::approximateIntersectionArea(double coverage) const {
        LinearInterpolation<int, double> interpolation;
        double coveragePosition = coverage * 128;
        vector<int> bounds;
        bounds.push_back(floor(coveragePosition));
        bounds.push_back(ceil(coveragePosition));
        vector<double> values;
        values.push_back(surfaceAreaTableFCC[bounds[0]]);
        values.push_back(surfaceAreaTableFCC[bounds[1]]);
        double scaleFactor = cbrt(1 / getDensity());
        scaleFactor *= scaleFactor;
        return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
    }
    void FCCLattice::get12Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        neighbors.clear();
        if ((layerIndex % 2) != 1) {
            if ((rowIndex % 2) != 1) {
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); //,FCCD1)); // top front
                }
                if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex))); //,FCCD1)); // top left
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); //,FCCD1)); // top back
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); //,FCCD1)); // top right
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 1))); //,FCCD1)); // front left
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 1))); //,FCCD1)); // back left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); //,FCCD1)); // back right
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); //,FCCD1)); // front right
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); //,FCCD1)); // bottom front
                }
                if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex))); //,FCCD1)); // bottom left
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); //,FCCD1)); // bottom back
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); //,FCCD1)); // bottom right
                }
            }
            else { //offset row
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); //,FCCD1)); // top front
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); //,FCCD1)); // top left
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); //,FCCD1)); // top back
                }
                if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex))); //,FCCD1)); // top right
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); //,FCCD1)); // front left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); //,FCCD1)); // back left
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 1))); //,FCCD1)); // back right
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 1))); //,FCCD1)); // front right
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); //,FCCD1)); // bottom front
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); //,FCCD1)); // bottom left
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); //,FCCD1)); // bottom back
                }
                if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex))); //,FCCD1)); // bottom right
                }
            }
        }
        else { // offset layer
            if ((rowIndex % 2) == 1) { //aligned row
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); //,FCCD1)); // top front
                }
                if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex))); //,FCCD1)); // top left
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); //,FCCD1)); // top back
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); //,FCCD1)); // top right
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 1))); //,FCCD1)); // front left
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 1))); //,FCCD1)); // back left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); //,FCCD1)); // back right
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); //,FCCD1)); // front right
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); //,FCCD1)); // bottom front
                }
                if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex))); //,FCCD1)); // bottom left
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); //,FCCD1)); // bottom back
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); //,FCCD1)); // bottom right
                }
            }
            else { //offset row
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); //,FCCD1)); // top front
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); //,FCCD1)); // top left
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); //,FCCD1)); // top back
                }
                if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex))); //,FCCD1)); // top right
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); //,FCCD1)); // front left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); //,FCCD1)); // back left
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 1))); //,FCCD1)); // back right
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 1))); //,FCCD1)); // front right
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); //,FCCD1)); // bottom front
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); //,FCCD1)); // bottom left
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); //,FCCD1)); // bottom back
                }
                if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex))); //,FCCD1)); // bottom right
                }
            }
        }
    }
    void FCCLattice::get12Neighbors(int elementIndex, vector<Neighbor> &neighbors) const {
        get12Neighbors(this->indexToR(elementIndex), this->indexToC(elementIndex), this->indexToL(elementIndex), neighbors);
    }
    void FCCLattice::get18Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        neighbors.clear();
        get12Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
        if ((layerIndex % 2) != 1) {
            if ((rowIndex % 2) != 1) {
                if (this->isValid(rowIndex - 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); //,FCCD2)); // top
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); //,FCCD2)); // front
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); //,FCCD2)); // left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); //,FCCD2)); // back
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); //,FCCD2)); // right
                }
                if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); //,FCCD2)); // bottom
                }
            }
            else { //offset row
                if (this->isValid(rowIndex - 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); //,FCCD2)); // top
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); //,FCCD2)); // front
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); //,FCCD2)); // left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); //,FCCD2)); // back
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); //,FCCD2)); // right
                }
                if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); //,FCCD2)); // bottom
                }
            }
        }
        else { // offset layer
            if ((rowIndex % 2) == 1) { //aligned row
                if (this->isValid(rowIndex - 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); //,FCCD2)); // top
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); //,FCCD2)); // front
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); //,FCCD2)); // left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); //,FCCD2)); // back
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); //,FCCD2)); // right
                }
                if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); //,FCCD2)); // bottom
                }
            }
            else { //offset row
                if (this->isValid(rowIndex - 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); //,FCCD2)); // top
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); //,FCCD2)); // front
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); //,FCCD2)); // left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); //,FCCD2)); // back
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); //,FCCD2)); // right
                }
                if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); //,FCCD2)); // bottom
                }
            }
        }
    }
    void FCCLattice::get18Neighbors(int elementIndex, vector<Neighbor> &neighbors) const {
        get18Neighbors(this->indexToR(elementIndex), this->indexToC(elementIndex), this->indexToL(elementIndex), neighbors);
    }
    void FCCLattice::getNeighbors(int rowIndex, int columnIndex, int layerIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const {
        switch (neighborhoodSize) {
            case 12:
                get12Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
                break;
            case 18:
                get18Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
                break;
            default:
                throw incompatibleParametersException();
        }
    }
    void FCCLattice::getNeighbors(int elementIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const {
        switch (neighborhoodSize) {
            case 12:
                get12Neighbors(elementIndex, neighbors);
                break;
            case 18:
                get18Neighbors(elementIndex, neighbors);
                break;
            default:
                throw incompatibleParametersException();
        }
    }
}