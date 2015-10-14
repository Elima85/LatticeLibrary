#include "cclattice.h"
#include "exception.h"
#include <cmath>
#include "linearinterpolation.h"
#include "defs.h"
#include <vector>

using namespace std;

namespace LatticeLib {

    CCLattice::CCLattice(int rows, int columns, int layers, double density) : Lattice(rows, columns, layers, density) {};
    CCLattice::CCLattice(const CCLattice &original) : Lattice(original) {};
    CCLattice::~CCLattice() {};

    double CCLattice::indexToX(int elementIndex) const {
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return scaleFactor * this->indexToC(elementIndex);
    }
    double CCLattice::indexToY(int elementIndex) const {
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return scaleFactor * this->indexToR(elementIndex);
    }
    double CCLattice::indexToZ(int elementIndex) const {
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return scaleFactor * this->indexToL(elementIndex);
    }
    int CCLattice::coordinatesToIndex(vector<double> coordinates) const {
        if (coordinates.size() != 3) {
            throw incompatibleParametersException();
        }
        double scaleFactor = cbrt(1 / this->latticeDensity);
        int columnIndex = MAX(0, MIN(this->nColumns - 1, round(coordinates[0] / scaleFactor)));
        int rowIndex = MAX(0, MIN(this->nRows - 1, round(coordinates[1] / scaleFactor)));
        int layerIndex = MAX(0, MIN(this->nLayers - 1, round(coordinates[2] / scaleFactor)));
        return this->rclToIndex(rowIndex, columnIndex, layerIndex);
    }
    double CCLattice::getElementWidth() const {
        return cbrt(1 / this->latticeDensity);
    }
    double CCLattice::getElementHeight() const {
        return cbrt(1 / this->latticeDensity);
    }
    double CCLattice::getElementDepth() const {
        return cbrt(1 / this->latticeDensity);
    }
    double CCLattice::getWidth() const {
        return this->nColumns * cbrt(1 / this->latticeDensity);
    }
    double CCLattice::getHeight() const {
        return this->nRows * cbrt(1 / this->latticeDensity);
    }
    double CCLattice::getDepth() const {
        return this->nLayers * cbrt(1 / this->latticeDensity);
    }
    double CCLattice::approximateDistanceToElementCenter(double coverage) const {
        LinearInterpolation<int, double> interpolation;
        double coveragePosition = coverage * 127;
        vector<int> bounds;
        bounds.push_back(floor(coveragePosition));
        bounds.push_back(ceil(coveragePosition));
        vector<double> values;
        values.push_back(distanceTableCC[bounds[0]]);
        values.push_back(distanceTableCC[bounds[1]]);
        double scaleFactor = cbrt(1 / getDensity());
        return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
    }
    double CCLattice::approximateIntersectionArea(double coverage) const {
        LinearInterpolation<int, double> interpolation;
        double coveragePosition = coverage * 255;
        vector<int> bounds;
        bounds.push_back(floor(coveragePosition));
        bounds.push_back(ceil(coveragePosition));
        vector<double> values;
        values.push_back(surfaceAreaTableCC[bounds[0]]);
        values.push_back(surfaceAreaTableCC[bounds[1]]);
        double scaleFactor = cbrt(1 / getDensity());
        scaleFactor *= scaleFactor;
        return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
    }
    void CCLattice::get6Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        neighbors.clear();
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(0, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex))); //right
        }
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(1, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex))); // left
        }
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(2, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex))); // bottom
        }
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(3, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex))); // top
        }
        if (this->isValid(rowIndex, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(4, this->rclToIndex(rowIndex, columnIndex, layerIndex - 1))); // front
        }
        if (this->isValid(rowIndex, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(5, this->rclToIndex(rowIndex, columnIndex, layerIndex + 1))); // back
        }
    }
    void CCLattice::get6Neighbors(int elementIndex, vector <Neighbor> &neighbors) const {
        get6Neighbors(this->indexToR(elementIndex), this->indexToC(elementIndex), this->indexToL(elementIndex), neighbors);
    }
    void CCLattice::get18Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        neighbors.clear();
        get6Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex))); // bottom right
        }
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex))); // top right
        }
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 1))); // back right
        }
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 1))); // front right
        }
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex))); // bottom left
        }
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex))); // top left
        }
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 1))); // back left
        }
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 1))); // front left
        }
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); // bottom back
        }
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); // bottom front
        }
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); // top back
        }
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); // top front
        }
    }
    void CCLattice::get18Neighbors(int elementIndex, vector <Neighbor> &neighbors) const {
        get18Neighbors(this->indexToR(elementIndex), this->indexToC(elementIndex), this->indexToL(elementIndex), neighbors);
    }
    void CCLattice::get26Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        neighbors.clear();
        get18Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(18, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex - 1))); // bottom front right
        }
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(19, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex - 1))); // top front right
        }
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(20, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex + 1))); // top back right
        }
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(21, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex + 1))); // bottom back right
        }
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(22, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex - 1))); // bottom front left
        }
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(23, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex - 1))); // top front left
        }
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(24, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex + 1))); // top back left
        }
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(25, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex + 1))); // bottom back left
        }
    }
    void CCLattice::get26Neighbors(int elementIndex, vector <Neighbor> &neighbors) const {
        get26Neighbors(this->indexToR(elementIndex), this->indexToC(elementIndex), this->indexToL(elementIndex), neighbors);
    }
    void CCLattice::get124Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        get26Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
        int localNeighborIndex = 26;
        if (this->isValid(rowIndex, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex))); // right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex))); // left inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex - 1)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex))); // left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex))); // left inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex - 1)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); // bottom
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex))); // bottom inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex - 1)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); // top
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex))); // top inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex - 1)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); // front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 2))); // front inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); // back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 2))); // back inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex + 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex))); // bottom right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex - 1)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex))); // top right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex - 1)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex + 2))); // back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex + 2)));
        }
        localNeighborIndex++;
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex + 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex - 2))); // front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex))); // bottom left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex - 1)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex))); // top left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex - 1)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex + 2))); // back left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex + 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex - 2))); // front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex + 2))); // bottom back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex + 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex - 2))); // bottom front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex + 2))); // top back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex + 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex - 2))); // top front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex - 2))); // bottom front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex - 2))); // top front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex + 2))); // top back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex + 2))); // bottom back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex - 2))); // bottom front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex - 2))); // top front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex + 2))); // top back left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex + 2))); // bottom back left
        }
    }
    void CCLattice::get124Neighbors(int elementIndex, vector <Neighbor> &neighbors) const {
        get124Neighbors(this->indexToR(elementIndex), this->indexToC(elementIndex), this->indexToL(elementIndex), neighbors);
    }
    void CCLattice::get342Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const {
        if (!this->isValid(rowIndex, columnIndex, layerIndex)) {
            throw outOfRangeException();
        }
        get124Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
        int localNeighborIndex = 124;
        if (this->isValid(rowIndex, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex))); // right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex))); // right inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex))); // right middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex))); // left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex))); // left inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex))); // left middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex))); // bottom
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex))); // bottom inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex))); // bottom middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex))); // top
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex))); // top inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex))); // top middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex - 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex, layerIndex - 3))); // front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 3))); // front inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex - 3))); // front middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex - 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex, layerIndex + 3))); // back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 3))); // back inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex + 3))); // back middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex + 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex))); // bottom right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex))); // top right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex + 3))); // back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex + 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex - 3))); // front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex - 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex))); // bottom left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex))); // top left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex + 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex - 1)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex + 2)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex - 2)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex + 3))); // back left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex + 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex - 3))); // front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex - 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex + 3))); // bottom back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex + 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex - 3))); // bottom front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex - 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex + 3))); // top back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex + 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex + 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex - 3))); // top front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex - 3)));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex - 3)));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex - 3))); // bottom front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex - 3))); // top front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex + 3))); // top back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex + 3))); // bottom back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex - 3))); // bottom front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex - 3))); // top front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex + 3))); // top back left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex + 3))); // bottom back left
        }

//		return neighbors;
    }
    void CCLattice::get342Neighbors(int elementIndex, vector <Neighbor> &neighbors) const {
        get342Neighbors(this->indexToR(elementIndex), this->indexToC(elementIndex), this->indexToL(elementIndex), neighbors);
    }
    void CCLattice::getNeighbors(int rowIndex, int columnIndex, int layerIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const {
        switch (neighborhoodSize){
            case 6:
                get6Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
                break;
            case 18:
                get18Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
                break;
            case 26:
                get26Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
                break;
            case 124:
                get124Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
                break;
            case 342:
                get342Neighbors(rowIndex, columnIndex, layerIndex, neighbors);
                break;
            default:
                throw incompatibleParametersException();
        }
    }
    void CCLattice::getNeighbors(int elementIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const {
        getNeighbors(indexToR(elementIndex), indexToC(elementIndex), indexToL(elementIndex),neighborhoodSize,neighbors);
    }

}