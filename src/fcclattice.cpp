#include "fcclattice.h"
#include "defs.h"
#include "exception.h"
#include <cmath>
#include "linearinterpolation.h"
#include "pnorm.h"
#include <vector>
#include "vectoroperators.h"

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
        x = scaleFactor * ((!IS_EVEN(layer + row)) * FCCOFFSET + column * FCCPOINTDISTANCE);
        return x;
    }
    double FCCLattice::indexToY(int elementIndex) const {
        int row;
        double y;
        double scaleFactor = cbrt(1 / this->latticeDensity);
        row = this->indexToR(elementIndex);
        y = scaleFactor * ((row) * FCCOFFSET);
        return y;
    }
    double FCCLattice::indexToZ(int elementIndex) const {
        int layer = this->indexToL(elementIndex);
        double scaleFactor = cbrt(1 / this->latticeDensity);
        double z = scaleFactor * ((layer) * FCCOFFSET);
        return z;
    }
    int FCCLattice::coordinatesToIndex(vector<double> coordinates) const {
        if (coordinates.size() != 3) {
            throw incompatibleParametersException();
        }
        double scaleFactor = cbrt(1 / this->latticeDensity);
        int prelColumnIndex = MAX(0, MIN(this->nColumns - 1, round(coordinates[0] / (scaleFactor * FCCPOINTDISTANCE))));
        int prelRowIndex = MAX(0, MIN(this->nRows - 1, round(coordinates[1] / (scaleFactor * FCCPOINTDISTANCE))));
        int prelLayerIndex = MAX(0, MIN(this->nLayers - 1, round(coordinates[2] / (scaleFactor * FCCOFFSET))));
        int prelIndex = this->rclToIndex(prelRowIndex, prelColumnIndex, prelLayerIndex);
        vector<double> potentialCoordinates;
        this->getCoordinates(prelIndex, potentialCoordinates);
        PNorm<double> norm(2);
        double smallestDistance = norm.compute(coordinates - potentialCoordinates);
        vector<Neighbor> neighbors;
        this->getNeighbors(prelIndex, 12, neighbors);
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
    double FCCLattice::getElementWidth() const {
        return FCCPOINTDISTANCE * cbrt(1 / this->latticeDensity);
    }
    double FCCLattice::getElementHeight() const {
        return FCCPOINTDISTANCE * cbrt(1 / this->latticeDensity);
    }
    double FCCLattice::getElementDepth() const {
        return FCCPOINTDISTANCE * cbrt(1 / this->latticeDensity);
    }
    double FCCLattice::getWidth() const {
        return (this->nColumns * FCCPOINTDISTANCE + ((this->nLayers > 1) || (this->nRows > 1)) * FCCOFFSET) * cbrt(1.0 / this->latticeDensity);
        //return (1 + ((this->nRows > 1) || (this->nLayers > 1))) * this->indexToX(0) + this->indexToX(this->rclToIndex(0, this->nColumns - 1, 0));
    }
    double FCCLattice::getHeight() const {
        return (this->nRows + 1) * FCCOFFSET * cbrt(1 / this->latticeDensity);
        //return this->indexToY(this->rclToIndex(this->nRows - 1, 0, 0)) + this->indexToY(0);
    }
    double FCCLattice::getDepth() const {
        return ((this->nLayers + 1) * FCCOFFSET) * cbrt(1 / this->latticeDensity);
        //return this->indexToZ(0) + indexToZ(this->rclToIndex(0, 0, this->nLayers - 1));
    }
    double FCCLattice::approximateDistanceToElementCenter(double coverage) const {
        LinearInterpolation<int, double> interpolation;
        double coveragePosition = coverage * 127;
        vector<int> bounds;
        bounds.push_back(floor(coveragePosition));
        bounds.push_back(ceil(coveragePosition));
        vector<double> values;
        values.push_back(distanceTableFCC[bounds[0]]); // ball-based approximation may be better.
        values.push_back(distanceTableFCC[bounds[1]]);
        double scaleFactor = cbrt(1 / getDensity());
        return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
    }
    double FCCLattice::approximateIntersectionArea(double coverage) const {
        LinearInterpolation<int, double> interpolation;
        double coveragePosition = coverage * 255;
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
                    neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); // top front
                }
                if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex))); // top left
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); // top back
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); // top right
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 1))); // front left
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 1))); // back left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); // back right
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); // front right
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); // bottom front
                }
                if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex))); // bottom left
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); // bottom back
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); // bottom right
                }
            }
            else { //offset row
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); // top front
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); // top left
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); // top back
                }
                if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex))); // top right
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); // front left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); // back left
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 1))); // back right
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 1))); // front right
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); // bottom front
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); // bottom left
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); // bottom back
                }
                if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex))); // bottom right
                }
            }
        }
        else { // offset layer
            if ((rowIndex % 2) == 1) { //aligned row
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); // top front
                }
                if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex))); // top left
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); // top back
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); // top right
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 1))); // front left
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 1))); // back left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); // back right
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); // front right
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); // bottom front
                }
                if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex))); // bottom left
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); // bottom back
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); // bottom right
                }
            }
            else { //offset row
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); // top front
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); // top left
                }
                if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); // top back
                }
                if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex))); // top right
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); // front left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); // back left
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 1))); // back right
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 1))); // front right
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
                    neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); // bottom front
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); // bottom left
                }
                if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
                    neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); // bottom back
                }
                if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex))); // bottom right
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
                    neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); // top
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); // front
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); // left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); // back
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); // right
                }
                if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); // bottom
                }
            }
            else { //offset row
                if (this->isValid(rowIndex - 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); // top
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); // front
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); // left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); // back
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); // right
                }
                if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); // bottom
                }
            }
        }
        else { // offset layer
            if ((rowIndex % 2) == 1) { //aligned row
                if (this->isValid(rowIndex - 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); // top
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); // front
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); // left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); // back
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); // right
                }
                if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); // bottom
                }
            }
            else { //offset row
                if (this->isValid(rowIndex - 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); // top
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
                    neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); // front
                }
                if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
                    neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); // left
                }
                if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
                    neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); // back
                }
                if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
                    neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); // right
                }
                if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
                    neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); // bottom
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