#include "cclattice.h"
#include "exception.h"
#include <cmath>

using namespace std;

namespace LatticeLib {

    CCLattice::CCLattice(int rows, int columns, int layers, double density) : Lattice(rows, columns, layers, density) {};
    CCLattice::CCLattice(const CCLattice &original) : Lattice(original) {};
    CCLattice::~CCLattice() {};

    double CCLattice::indexToX(int elementIndex) const {
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return scaleFactor * (this->indexToC(elementIndex) + 0.5); // scaleFactor är sidan på kuben
    }
    double CCLattice::indexToY(int elementIndex) const {
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return scaleFactor * (this->indexToR(elementIndex) + 0.5);
    }
    double CCLattice::indexToZ(int elementIndex) const {
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return scaleFactor * (this->indexToL(elementIndex) + 0.5);
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
        double scaleFactor = cbrt(1 / this->latticeDensity);
        return subSpelDistanceVoronoiCC[coverageIndex] * [function of scaleFactor];
    }*/
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
            neighbors.push_back(Neighbor(6, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex))); //,CCd011)); // bottom right
        }
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(7, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex))); //,CCd011)); // top right
        }
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(8, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 1))); //,CCd011)); // back right
        }
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(9, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 1))); //,CCd011)); // front right
        }
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(10, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex))); //,CCd011)); // bottom left
        }
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(11, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex))); //,CCd011)); // top left
        }
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(12, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 1))); //,CCd011)); // back left
        }
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(13, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 1))); //,CCd011)); // front left
        }
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(14, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 1))); //,CCd011)); // bottom back
        }
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(15, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 1))); //,CCd011)); // bottom front
        }
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(16, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 1))); //,CCd011)); // top back
        }
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(17, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 1))); //,CCd011)); // top front
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
            neighbors.push_back(Neighbor(18, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex - 1))); //,CCd111)); // bottom front right
        }
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(19, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex - 1))); //,CCd111)); // top front right
        }
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(20, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex + 1))); //,CCd111)); // top back right
        }
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(21, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex + 1))); //,CCd111)); // bottom back right
        }
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(22, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex - 1))); //,CCd111)); // bottom front left
        }
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(23, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex - 1))); //,CCd111)); // top front left
        }
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(24, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex + 1))); //,CCd111)); // top back left
        }
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(25, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex + 1))); //,CCd111)); // bottom back left
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
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex))); //,2*CCd001)); // right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex))); //,CCd012)); // left inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex + 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex - 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex - 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex - 1))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex))); //,2*CCd001)); // left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex))); //,CCd012)); // left inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex + 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex - 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex - 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex - 1))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex))); //,2*CCd001)); // bottom
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex))); //,CCd012)); // bottom inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex + 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex - 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex - 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex - 1))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex))); //,2*CCd001)); // top
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex))); //,CCd012)); // top inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex + 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex - 1))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex - 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex + 1))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex - 1))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex, layerIndex - 2))); //,2*CCd001)); // front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 2))); //,CCd012)); // front inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex - 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex - 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex - 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex - 2))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex, layerIndex + 2))); //,2*CCd001)); // back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 2))); //,CCd012)); // back inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 2))); //,CCd012));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex + 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex + 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex + 2))); //,CCd112));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex + 2))); //,CCd112));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex))); //,2*CCd011)); // bottom right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex + 1))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex - 1))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex))); //,2*CCd011)); // top right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex + 1))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex - 1))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex + 2))); //,2*CCd011)); // back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex + 2))); //,CCd122));
        }
        localNeighborIndex++;
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex + 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex - 2))); //,2*CCd011)); // front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex - 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex - 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex))); //,2*CCd011)); // bottom left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex + 1))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex - 1))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex))); //,2*CCd011)); // top left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex + 1))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex - 1))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex + 2))); //,2*CCd011)); // back left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex + 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex + 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex - 2))); //,2*CCd011)); // front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex - 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex - 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex + 2))); //,2*CCd011)); // bottom back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex + 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex + 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex - 2))); //,2*CCd011)); // bottom front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex - 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex - 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex + 2))); //,2*CCd011)); // top back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex + 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex + 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 2, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex - 2))); //,2*CCd011)); // top front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex - 2))); //,CCd122));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex - 2))); //,CCd122));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex - 2))); //,2*CCd111)); // bottom front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex - 2))); //,2*CCd111)); // top front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex + 2))); //,2*CCd111)); // top back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex + 2))); //,2*CCd111)); // bottom back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex - 2))); //,2*CCd111)); // bottom front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex - 2))); //,2*CCd111)); // top front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex + 2))); //,2*CCd111)); // top back left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex + 2))); //,2*CCd111)); // bottom back left
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
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex))); //,3*CCd001)); // right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex))); //,CCd013)); // right inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex + 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex - 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex))); //,CCd023)); // right middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex + 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex - 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex - 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex - 2))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex))); //,3*CCd001)); // left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex))); //,CCd013)); // left inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex + 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex - 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex))); //,CCd023)); // left middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex + 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex - 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex - 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex - 2))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex))); //,3*CCd001)); // bottom
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex))); //,CCd013)); // bottom inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex + 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex - 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex))); //,CCd023)); // bottom middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex + 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex - 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex - 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex - 2))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex))); //,3*CCd001)); // top
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex))); //,CCd013)); // top inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex + 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex - 1))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex + 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex - 1))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex))); //,CCd023)); // top middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex + 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex - 2))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex + 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex - 1))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex + 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex - 2))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex - 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex + 2))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex - 2))); //CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex, layerIndex - 3))); //,3*CCd001)); // front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex - 3))); //,CCd013)); // front inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex - 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex - 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex - 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex - 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex - 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex - 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex - 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex - 3))); //,CCd023)); // front middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex - 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex - 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex - 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex - 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex - 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex - 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex - 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex - 3))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex, layerIndex + 3))); //,3*CCd001)); // back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex, layerIndex + 3))); //,CCd013)); // back inner
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex, layerIndex + 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 1, layerIndex + 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 1, layerIndex + 3))); //,CCd013));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 1, layerIndex + 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 1, layerIndex + 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 1, layerIndex + 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 1, layerIndex + 3))); //,CCd113));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex, layerIndex + 3))); //,CCd023)); // back middle
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex, layerIndex + 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 2, layerIndex + 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 2, layerIndex + 3))); //,CCd023));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 1, layerIndex + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 1, layerIndex + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 2, layerIndex + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 2, layerIndex + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 1, layerIndex + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 1, layerIndex + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 2, layerIndex + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 2, layerIndex + 3))); //,CCd123));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 2, layerIndex + 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 2, layerIndex + 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 2, layerIndex + 3))); //,CCd223));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 2, layerIndex + 3))); //,CCd223));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex))); //,3*CCd011)); // bottom right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex + 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex - 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex + 2))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex - 2))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex))); //,2*CCd011)); // top right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex + 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex - 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex + 2))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex - 2))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex + 3))); //,3*CCd011)); // back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex + 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex + 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex + 3, layerIndex - 3))); //,3*CCd011)); // front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex + 3, layerIndex - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex + 3, layerIndex - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex + 3, layerIndex - 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex + 3, layerIndex - 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex))); //,3*CCd011)); // bottom left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex + 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex - 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex + 2))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex - 2))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex))); //,2*CCd011)); // top left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex + 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex + 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex - 1)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex - 1))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex + 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex + 2))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex - 2)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex - 2))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex + 3))); //,3*CCd011)); // back left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex + 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex + 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex, columnIndex - 3, layerIndex - 3))); //,3*CCd011)); // front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 1, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 1, columnIndex - 3, layerIndex - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 1, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 1, columnIndex - 3, layerIndex - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 2, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 2, columnIndex - 3, layerIndex - 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 2, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 2, columnIndex - 3, layerIndex - 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex + 3))); //,3*CCd011)); // bottom back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex + 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex + 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex, layerIndex - 3))); //,3*CCd011)); // bottom front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 1, layerIndex - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 1, layerIndex - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 2, layerIndex - 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 2, layerIndex - 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex + 3))); //,3*CCd011)); // top back
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex + 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex + 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex + 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex - 3, columnIndex, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex, layerIndex - 3))); //,3*CCd011)); // top front
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 1, layerIndex - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 1, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 1, layerIndex - 3))); //,CCd133));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 2, layerIndex - 3))); //,CCd233));
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 2, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 2, layerIndex - 3))); //,CCd233));
        }
        localNeighborIndex++;

        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex - 3))); //,3*CCd111)); // bottom front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex - 3))); //,3*CCd111)); // top front right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex + 3, layerIndex + 3))); //,3*CCd111)); // top back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex + 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex + 3, layerIndex + 3))); //,3*CCd111)); // bottom back right
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex - 3))); //,3*CCd111)); // bottom front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex - 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex - 3))); //,3*CCd111)); // top front left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex - 3, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex - 3, columnIndex - 3, layerIndex + 3))); //,3*CCd111)); // top back left
        }
        localNeighborIndex++;
        if (this->isValid(rowIndex + 3, columnIndex - 3, layerIndex + 3)) {
            neighbors.push_back(Neighbor(localNeighborIndex, this->rclToIndex(rowIndex + 3, columnIndex - 3, layerIndex + 3))); //,3*CCd111)); // bottom back left
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