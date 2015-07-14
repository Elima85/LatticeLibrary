#ifndef FCCLATTICE_H
#define FCCLATTICE_H

#include "lattice.h"

namespace LatticeLib {
#define FCCOFFSET 0.793700525984100 // 1/(2^(1/3)), distance between layers in FCC
#define FCCFACEDISTANCE 1.122462048309373 // face neighbor distance
#define FCCPOINTDISTANCE 1.587401051968199 // 2/(2^(1/3)), point neighbor distance
    // TODO: const double subSpelDistanceVoronoiFCC[] = {[255 elements]};

    class FCCLattice : public Lattice {

    public:
        FCCLattice(int rows, int columns, int layers, double scale);
        FCCLattice(const FCCLattice &original);
        ~FCCLattice();

        /**
        * Implements Lattice::getWidth().
        */
        double getWidth() const;

        /**
        * Implements Lattice::getHeight().
        */
        double getHeight() const;

        /**
        * Implements Lattice::getDepth().
        */
        double getDepth() const;

        /**
        * Implements Lattice::indexToX().
        */
        double indexToX(int index) const;

        /**
        * Implements Lattice::indexToY().
        */
        double indexToY(int index) const;

        /**
        * Implements Lattice::indexToZ().
        */
        double indexToZ(int index) const;

        /**
        * Returns the face neighbors of the element at \f$(row,column,layer)\f$.
        */
        void get12Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const;

        /**
        * Returns the face neighbors of the element with index \f$(index)\f$.
        */
        void get12Neighbors(int index, vector<Neighbor> &neighbors) const;

        /**
        * Returns the face- and edge neighbors of the element at \f$(row,column,layer)\f$.
        */
        void get18Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const;

        /**
        * Returns the face- and edge neighbors of the element with index \f$(index)\f$.
        */
        void get18Neighbors(int index, vector<Neighbor> &neighbors) const;

        /**
        * Implements Lattice::getNeighbors(int row, int column, int layer, int nNeighbors, vector <Neighbor> &neighbors).
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * neighborhoodSize  |           | requested neighborhood size
        *                   |           | 12: face neighbors
        *                   |           | 18: face- and point neighbors
        */
        void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector<Neighbor> &neighbors) const;

        /**
        * Implements Lattice::getNeighbors(int index, int nNeighbors, vector <Neighbor> &neighbors).
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * neighborhoodSize  |           | requested neighborhood size
        *                   |           | 12: face neighbors
        *                   |           | 18: face- and point neighbors
        */
        void getNeighbors(int index, int neighborhoodSize, vector<Neighbor> &neighbors) const;
    };

}

#endif