#ifndef BCCLATTICE_H
#define BCCLATTICE_H

#include "lattice.h"

namespace LatticeLib {

#define BCCOFFSET 0.629960524947437 // 1/(4^(1/3)), distance between layers in BCC
#define BCCHEXFACEDISTANCE 1.091123635971721 // hexagonal face neighbor distance
#define BCCSQFACEDISTANCE 1.259921049894873 // square face neighbor distance

    class BCCLattice : public Lattice {

    public:
        BCCLattice(int rows, int columns, int layers, double scale);
        BCCLattice(const BCCLattice &original);
        ~BCCLattice();

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
        void get8Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
        * Returns the face neighbors of the element with index \f$(index)\f$.
        */
        void get8Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
        * Returns the face- and edge neighbors of the element at \f$(row,column,layer)\f$.
        */
        void get14Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
        * Returns the face- and edge neighbors of the element with index \f$(index)\f$.
        */
        void get14Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
        * Implements Lattice::getNeighbors(int row, int column, int layer, int nNeighbors, vector <Neighbor> &neighbors).
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * neighborhoodSize  |           | requested neighborhood size
        *                   |           | 8: hexagonal face neighbors
        *                   |           | 14: hexagonal- and square face neighbors
        */
        void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector <Neighbor> &neighbors) const;

        /**
        * Implements Lattice::getNeighbors(int index, int nNeighbors, vector <Neighbor> &neighbors).
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * neighborhoodSize  |           | requested neighborhood size
        *                   |           | 8: hexagonal face neighbors
        *                   |           | 14: hexagonal- and square face neighbors
        */
        void getNeighbors(int index, int neighborhoodSize, vector <Neighbor> &neighbors) const;
    };
}

#endif