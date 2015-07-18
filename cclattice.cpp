#include "cclattice.h"
#include "exception.h"
#include <cmath>

using namespace std;

namespace LatticeLib {

    CCLattice::CCLattice(int rows, int columns, int layers, double scale) : Lattice(rows, columns, layers, scale) {};
    CCLattice::CCLattice(const CCLattice &original) : Lattice(original) {};
    CCLattice::~CCLattice() {};

    double CCLattice::indexToX(int index) const {
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return scaleFactor * (this->indexToC(index) + 0.5); // scaleFactor är sidan på kuben
    }
    double CCLattice::indexToY(int index) const {
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return scaleFactor * (this->indexToR(index) + 0.5);
    }
    double CCLattice::indexToZ(int index) const {
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return scaleFactor * (this->indexToL(index) + 0.5);
    }
    double CCLattice::getWidth() const {
        return this->indexToX(0) + this->indexToX(this->rclToIndex(0, this->nColumns - 1, 0));
    }
    double CCLattice::getHeight() const {
        return this->indexToY(0) + this->indexToY(this->rclToIndex(this->nRows - 1, 0, 0));
    }
    double CCLattice::getDepth() const {
        return this->indexToZ(0) + this->indexToZ(this->rclToIndex(0, 0, this->nLayers - 1));
    }

    /* TODO: double coverageToInternalDistance(double coverage) const {
        coverageIndex = round(coverage * 255);
        double scaleFactor = this->latticeDensity; // TODO: Find correct scaleFactor!
        return subSpelDistanceVoronoiCC[coverageIndex] * [function of scaleFactor];
    }*/
    void CCLattice::get6Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideRangeException();
        }
        neighbors.clear();
        if (this->isValid(row, column + 1, layer)) {
            neighbors.push_back(Neighbor(0, this->rclToIndex(row, column + 1, layer))); //right
        }
        if (this->isValid(row, column - 1, layer)) {
            neighbors.push_back(Neighbor(1, this->rclToIndex(row, column - 1, layer))); // left
        }
        if (this->isValid(row + 1, column, layer)) {
            neighbors.push_back(Neighbor(2, this->rclToIndex(row + 1, column, layer))); // bottom
        }
        if (this->isValid(row - 1, column, layer)) {
            neighbors.push_back(Neighbor(3, this->rclToIndex(row - 1, column, layer))); // top
        }
        if (this->isValid(row, column, layer - 1)) {
            neighbors.push_back(Neighbor(4, this->rclToIndex(row, column, layer - 1))); // front
        }
        if (this->isValid(row, column, layer + 1)) {
            neighbors.push_back(Neighbor(5, this->rclToIndex(row, column, layer + 1))); // back
        }
    }
    void CCLattice::get6Neighbors(int index, vector <Neighbor> &neighbors) const {
        get6Neighbors(this->indexToR(index), this->indexToC(index), this->indexToL(index), neighbors);
    }
    void CCLattice::get18Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideRangeException();
        }
        neighbors.clear();
        get6Neighbors(row, column, layer, neighbors);
        if (this->isValid(row + 1, column + 1, layer)) {
            neighbors.push_back(Neighbor(6, this->rclToIndex(row + 1, column + 1, layer))); //,CCd011)); // bottom right
        }
        if (this->isValid(row - 1, column + 1, layer)) {
            neighbors.push_back(Neighbor(7, this->rclToIndex(row - 1, column + 1, layer))); //,CCd011)); // top right
        }
        if (this->isValid(row, column + 1, layer + 1)) {
            neighbors.push_back(Neighbor(8, this->rclToIndex(row, column + 1, layer + 1))); //,CCd011)); // back right
        }
        if (this->isValid(row, column + 1, layer - 1)) {
            neighbors.push_back(Neighbor(9, this->rclToIndex(row, column + 1, layer - 1))); //,CCd011)); // front right
        }
        if (this->isValid(row + 1, column - 1, layer)) {
            neighbors.push_back(Neighbor(10, this->rclToIndex(row + 1, column - 1, layer))); //,CCd011)); // bottom left
        }
        if (this->isValid(row - 1, column - 1, layer)) {
            neighbors.push_back(Neighbor(11, this->rclToIndex(row - 1, column - 1, layer))); //,CCd011)); // top left
        }
        if (this->isValid(row, column - 1, layer + 1)) {
            neighbors.push_back(Neighbor(12, this->rclToIndex(row, column - 1, layer + 1))); //,CCd011)); // back left
        }
        if (this->isValid(row, column - 1, layer - 1)) {
            neighbors.push_back(Neighbor(13, this->rclToIndex(row, column - 1, layer - 1))); //,CCd011)); // front left
        }
        if (this->isValid(row + 1, column, layer + 1)) {
            neighbors.push_back(Neighbor(14, this->rclToIndex(row + 1, column, layer + 1))); //,CCd011)); // bottom back
        }
        if (this->isValid(row + 1, column, layer - 1)) {
            neighbors.push_back(Neighbor(15, this->rclToIndex(row + 1, column, layer - 1))); //,CCd011)); // bottom front
        }
        if (this->isValid(row - 1, column, layer + 1)) {
            neighbors.push_back(Neighbor(16, this->rclToIndex(row - 1, column, layer + 1))); //,CCd011)); // top back
        }
        if (this->isValid(row - 1, column, layer - 1)) {
            neighbors.push_back(Neighbor(17, this->rclToIndex(row - 1, column, layer - 1))); //,CCd011)); // top front
        }
    }
    void CCLattice::get18Neighbors(int index, vector <Neighbor> &neighbors) const {
        get18Neighbors(this->indexToR(index), this->indexToC(index), this->indexToL(index), neighbors);
    }
    void CCLattice::get26Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideRangeException();
        }
        neighbors.clear();
        get18Neighbors(row, column, layer, neighbors);
        if (this->isValid(row + 1, column + 1, layer - 1)) {
            neighbors.push_back(Neighbor(18, this->rclToIndex(row + 1, column + 1, layer - 1))); //,CCd111)); // bottom front right
        }
        if (this->isValid(row - 1, column + 1, layer - 1)) {
            neighbors.push_back(Neighbor(19, this->rclToIndex(row - 1, column + 1, layer - 1))); //,CCd111)); // top front right
        }
        if (this->isValid(row - 1, column + 1, layer + 1)) {
            neighbors.push_back(Neighbor(20, this->rclToIndex(row - 1, column + 1, layer + 1))); //,CCd111)); // top back right
        }
        if (this->isValid(row + 1, column + 1, layer + 1)) {
            neighbors.push_back(Neighbor(21, this->rclToIndex(row + 1, column + 1, layer + 1))); //,CCd111)); // bottom back right
        }
        if (this->isValid(row + 1, column - 1, layer - 1)) {
            neighbors.push_back(Neighbor(22, this->rclToIndex(row + 1, column - 1, layer - 1))); //,CCd111)); // bottom front left
        }
        if (this->isValid(row - 1, column - 1, layer - 1)) {
            neighbors.push_back(Neighbor(23, this->rclToIndex(row - 1, column - 1, layer - 1))); //,CCd111)); // top front left
        }
        if (this->isValid(row - 1, column - 1, layer + 1)) {
            neighbors.push_back(Neighbor(24, this->rclToIndex(row - 1, column - 1, layer + 1))); //,CCd111)); // top back left
        }
        if (this->isValid(row + 1, column - 1, layer + 1)) {
            neighbors.push_back(Neighbor(25, this->rclToIndex(row + 1, column - 1, layer + 1))); //,CCd111)); // bottom back left
        }
    }
    void CCLattice::get26Neighbors(int index, vector <Neighbor> &neighbors) const {
        get26Neighbors(this->indexToR(index), this->indexToC(index), this->indexToL(index), neighbors);
    }
    void CCLattice::get124Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideRangeException();
        }
        get26Neighbors(row, column, layer, neighbors);
        int localNeighborIndex = 26;
        if (this->isValid(row, column + 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 2, layer))); //,2*CCd001)); // right
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 2, layer))); //,CCd012)); // left inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 2, layer))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 2, layer + 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 2, layer - 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 2, layer + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 2, layer - 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 2, layer + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 2, layer - 1))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(row, column - 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 2, layer))); //,2*CCd001)); // left
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 2, layer))); //,CCd012)); // left inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 2, layer))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 2, layer + 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 2, layer - 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 2, layer + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 2, layer - 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 2, layer + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 2, layer - 1))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(row + 2, column, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column, layer))); //,2*CCd001)); // bottom
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 1, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 1, layer))); //,CCd012)); // bottom inner
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 1, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 1, layer))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column, layer + 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column, layer - 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 1, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 1, layer + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 1, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 1, layer - 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 1, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 1, layer + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 1, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 1, layer - 1))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(row - 2, column, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column, layer))); //,2*CCd001)); // top
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 1, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 1, layer))); //,CCd012)); // top inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 1, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 1, layer))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column, layer + 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column, layer - 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 1, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 1, layer + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 1, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 1, layer - 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 1, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 1, layer + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 1, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 1, layer - 1))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(row, column, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column, layer - 2))); //,2*CCd001)); // front
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column, layer - 2))); //,CCd012)); // front inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column, layer - 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 1, layer - 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 1, layer - 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 1, layer - 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 1, layer - 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 1, layer - 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 1, layer - 2))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(row, column, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column, layer + 2))); //,2*CCd001)); // back
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column, layer + 2))); //,CCd012)); // back inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column, layer + 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 1, layer + 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 1, layer + 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 1, layer + 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 1, layer + 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 1, layer + 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 1, layer + 2))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(row + 2, column + 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 2, layer))); //,2*CCd011)); // bottom right
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 2, layer + 1))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 2, layer - 1))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row - 2, column + 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 2, layer))); //,2*CCd011)); // top right
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 2, layer + 1))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 2, layer - 1))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row, column + 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 2, layer + 2))); //,2*CCd011)); // back right
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 2, layer + 2))); //,CCd122));
        }
        localNeighborIndex++;
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 2, layer + 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row, column + 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 2, layer - 2))); //,2*CCd011)); // front right
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 2, layer - 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 2, layer - 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row + 2, column - 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 2, layer))); //,2*CCd011)); // bottom left
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 2, layer + 1))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 2, layer - 1))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row - 2, column - 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 2, layer))); //,2*CCd011)); // top left
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 2, layer + 1))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 2, layer - 1))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row, column - 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 2, layer + 2))); //,2*CCd011)); // back left
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 2, layer + 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 2, layer + 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row, column - 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 2, layer - 2))); //,2*CCd011)); // front left
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 2, layer - 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 2, layer - 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row + 2, column, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column, layer + 2))); //,2*CCd011)); // bottom back
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 1, layer + 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 1, layer + 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row + 2, column, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column, layer - 2))); //,2*CCd011)); // bottom front
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 1, layer - 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 1, layer - 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row - 2, column, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column, layer + 2))); //,2*CCd011)); // top back
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 1, layer + 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 1, layer + 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row - 2, column, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column, layer - 2))); //,2*CCd011)); // top front
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 1, layer - 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 1, layer - 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(row + 2, column + 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 2, layer - 2))); //,2*CCd111)); // bottom front right
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 2, layer - 2))); //,2*CCd111)); // top front right
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 2, layer + 2))); //,2*CCd111)); // top back right
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 2, layer + 2))); //,2*CCd111)); // bottom back right
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 2, layer - 2))); //,2*CCd111)); // bottom front left
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 2, layer - 2))); //,2*CCd111)); // top front left
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 2, layer + 2))); //,2*CCd111)); // top back left
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 2, layer + 2))); //,2*CCd111)); // bottom back left
        }
    }
    void CCLattice::get124Neighbors(int index, vector <Neighbor> &neighbors) const {
        get124Neighbors(this->indexToR(index), this->indexToC(index), this->indexToL(index), neighbors);
    }
    void CCLattice::get342Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const {
        if (!this->isValid(row, column, layer)) {
            throw outsideRangeException();
        }
        get124Neighbors(row, column, layer, neighbors);
        int localNeighborIndex = 124;
        if (this->isValid(row, column + 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 3, layer))); //,3*CCd001)); // right
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 3, layer))); //,CCd013)); // right inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 3, layer))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 3, layer + 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 3, layer - 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 3, layer + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 3, layer - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 3, layer + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 3, layer - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 3, layer))); //,CCd023)); // right middle
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 3, layer))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 3, layer + 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 3, layer - 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 3, layer + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 3, layer + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 3, layer + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 3, layer - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 3, layer - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 3, layer - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 3, layer + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 3, layer - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 3, layer + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 3, layer - 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 3, layer + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 3, layer - 2))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(row, column - 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 3, layer))); //,3*CCd001)); // left
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 3, layer))); //,CCd013)); // left inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 3, layer))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 3, layer + 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 3, layer - 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 3, layer + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 3, layer - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 3, layer + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 3, layer - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 3, layer))); //,CCd023)); // left middle
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 3, layer))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 3, layer + 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 3, layer - 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 3, layer + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 3, layer + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 3, layer + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 3, layer - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 3, layer - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 3, layer - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 3, layer + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 3, layer - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 3, layer + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 3, layer - 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 3, layer + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 3, layer - 2))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(row + 3, column, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column, layer))); //,3*CCd001)); // bottom
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 1, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 1, layer))); //,CCd013)); // bottom inner
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 1, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 1, layer))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column, layer + 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column, layer - 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 1, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 1, layer + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 1, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 1, layer - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 1, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 1, layer + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 1, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 1, layer - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 2, layer))); //,CCd023)); // bottom middle
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 2, layer))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column, layer + 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column, layer - 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 2, layer + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 2, layer + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 1, layer + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 1, layer - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 2, layer - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 2, layer - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 1, layer + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 1, layer - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 2, layer + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 2, layer - 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 2, layer + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 2, layer - 2))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(row - 3, column, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column, layer))); //,3*CCd001)); // top
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 1, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 1, layer))); //,CCd013)); // top inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 1, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 1, layer))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column, layer + 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column, layer - 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 1, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 1, layer + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 1, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 1, layer - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 1, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 1, layer + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 1, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 1, layer - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 2, layer))); //,CCd023)); // top middle
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 2, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 2, layer))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column, layer + 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column, layer - 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 2, layer + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 2, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 2, layer + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 1, layer + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 1, layer - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 2, layer - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 2, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 2, layer - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 1, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 1, layer + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 1, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 1, layer - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 2, layer + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 2, layer - 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 2, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 2, layer + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 2, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 2, layer - 2))); //CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(row, column, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column, layer - 3))); //,3*CCd001)); // front
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column, layer - 3))); //,CCd013)); // front inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column, layer - 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 1, layer - 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 1, layer - 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 1, layer - 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 1, layer - 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 1, layer - 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 1, layer - 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column, layer - 3))); //,CCd023)); // front middle
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column, layer - 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 2, layer - 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 2, layer - 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 1, layer - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 1, layer - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 2, layer - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 2, layer - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 1, layer - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 1, layer - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 2, layer - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 2, layer - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 2, layer - 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 2, layer - 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 2, layer - 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 2, layer - 3))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(row, column, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column, layer + 3))); //,3*CCd001)); // back
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column, layer + 3))); //,CCd013)); // back inner
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column, layer + 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 1, layer + 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 1, layer + 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 1, layer + 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 1, layer + 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 1, layer + 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 1, layer + 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column, layer + 3))); //,CCd023)); // back middle
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column, layer + 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row, column + 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 2, layer + 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row, column - 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 2, layer + 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 1, layer + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 1, layer + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 2, layer + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 2, layer + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 1, layer + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 1, layer + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 2, layer + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 2, layer + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 2, layer + 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 2, layer + 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 2, layer + 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 2, layer + 3))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(row + 3, column + 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 3, layer))); //,3*CCd011)); // bottom right
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 3, layer + 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 3, layer - 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 3, layer + 2))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 3, layer - 2))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row - 3, column + 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 3, layer))); //,2*CCd011)); // top right
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 3, layer + 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 3, layer - 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 3, layer + 2))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 3, layer - 2))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row, column + 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 3, layer + 3))); //,3*CCd011)); // back right
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 3, layer + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 3, layer + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 3, layer + 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 3, layer + 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row, column + 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column + 3, layer - 3))); //,3*CCd011)); // front right
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column + 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column + 3, layer - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column + 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column + 3, layer - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column + 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column + 3, layer - 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column + 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column + 3, layer - 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row + 3, column - 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 3, layer))); //,3*CCd011)); // bottom left
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 3, layer + 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 3, layer - 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 3, layer + 2))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 3, layer - 2))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row - 3, column - 3, layer)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 3, layer))); //,2*CCd011)); // top left
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 3, layer + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 3, layer + 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 3, layer - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 3, layer - 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 3, layer + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 3, layer + 2))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 3, layer - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 3, layer - 2))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row, column - 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 3, layer + 3))); //,3*CCd011)); // back left
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 3, layer + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 3, layer + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 3, layer + 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 3, layer + 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row, column - 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row, column - 3, layer - 3))); //,3*CCd011)); // front left
        }
        localNeighborIndex++;
        if (this->isValid(row + 1, column - 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 1, column - 3, layer - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 1, column - 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 1, column - 3, layer - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 2, column - 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 2, column - 3, layer - 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row - 2, column - 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 2, column - 3, layer - 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row + 3, column, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column, layer + 3))); //,3*CCd011)); // bottom back
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 1, layer + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 1, layer + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 2, layer + 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 2, layer + 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row + 3, column, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column, layer - 3))); //,3*CCd011)); // bottom front
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 1, layer - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 1, layer - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 2, layer - 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 2, layer - 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row - 3, column, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column, layer + 3))); //,3*CCd011)); // top back
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 1, layer + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 1, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 1, layer + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 2, layer + 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 2, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 2, layer + 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row - 3, column, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column, layer - 3))); //,3*CCd011)); // top front
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 1, layer - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 1, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 1, layer - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 2, layer - 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 2, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 2, layer - 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(row + 3, column + 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 3, layer - 3))); //,3*CCd111)); // bottom front right
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 3, layer - 3))); //,3*CCd111)); // top front right
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column + 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column + 3, layer + 3))); //,3*CCd111)); // top back right
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column + 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column + 3, layer + 3))); //,3*CCd111)); // bottom back right
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 3, layer - 3))); //,3*CCd111)); // bottom front left
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 3, layer - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 3, layer - 3))); //,3*CCd111)); // top front left
        }
        localNeighborIndex++;
        if (this->isValid(row - 3, column - 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row - 3, column - 3, layer + 3))); //,3*CCd111)); // top back left
        }
        localNeighborIndex++;
        if (this->isValid(row + 3, column - 3, layer + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(row + 3, column - 3, layer + 3))); //,3*CCd111)); // bottom back left
        }

//		return neighbors;
    }
    void CCLattice::get342Neighbors(int index, vector <Neighbor> &neighbors) const {
        get342Neighbors(this->indexToR(index), this->indexToC(index), this->indexToL(index), neighbors);
    }
    void CCLattice::getNeighbors(int row, int column, int layer, int neighborhoodSize, vector<Neighbor> &neighbors) const {
        switch (neighborhoodSize){
            case 6:
                get6Neighbors(row, column, layer, neighbors);
                break;
            case 18:
                get18Neighbors(row, column, layer, neighbors);
                break;
            case 26:
                get26Neighbors(row, column, layer, neighbors);
                break;
            case 124:
                get124Neighbors(row, column, layer, neighbors);
                break;
            case 342:
                get342Neighbors(row, column, layer, neighbors);
                break;
            default:
                throw neighborhoodSizeException();
        }
    }
    void CCLattice::getNeighbors(int index, int neighborhoodSize, vector<Neighbor> &neighbors) const {
        getNeighbors(indexToR(index), indexToC(index), indexToL(index),neighborhoodSize,neighbors);
    }

}