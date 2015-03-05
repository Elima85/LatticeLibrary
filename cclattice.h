#ifndef CCLATTICE_H
#define CCLATTICE_H

#include "lattice.h"

namespace CImage {

    class CCLattice : public Lattice {

    public:
        CCLattice(int rows, int columns, int layers, double scale);
        CCLattice(const CCLattice &original);
        ~CCLattice();

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
        void get6Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
        * Returns the face neighbors of the element with index \f$(index)\f$.
        */
        void get6Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
        * Returns the face- and edge neighbors of the element at \f$(row,column,layer)\f$.
        */
        void get18Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
        * Returns the face- and edge neighbors of the element with index \f$(index)\f$.
        */
        void get18Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
        * Returns the within a \f3\times3\times3\f cube with its center at \f$(row,column,layer)\f$.
        */
        void get26Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
        * Returns the face-, edge- and point neighbors of the element with index \f$(index)\f$.
        */
        void get26Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
        * Returns the neighbors within a \f5\times5\times5\f cube with its center at \f$(row,column,layer)\f$.
        */
        void get124Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
        * Returns the neighbors within a \f5\times5\times5\f cube with its center at element \f$(index)\f$.
        */
        void get124Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
        * Returns the neighbors within a \f7\times7\times7\f cube with its center at \f$(row,column,layer)\f$.
        */
        void get342Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
        * Returns the neighbors within a \f5\times5\times5\f cube with its center at element \f$(index)\f$.
        */
        void get342Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
        * Implements Lattice::getNeighbors(int row, int column, int layer, int nNeighbors, vector <Neighbor> &neighbors).
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * neighborhoodSize  |           | requested neighborhood size
        *                   |           | 6: face neighbors
        *                   |           | 18: face- and edge neighbors
        *                   |           | 26: 3*3*3 neighborhood
        *                   |           | 124: 5*5*5 neighborhood
        *                   |           | 342: 7*7*7 neighborhood
        */
        void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector <Neighbor> &neighbors) const;

        /**
        * Implements Lattice::getNeighbors(int index, int nNeighbors, vector <Neighbor> &neighbors).
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * neighborhoodSize  |           | requested neighborhood size
        *                   |           | 6: face neighbors
        *                   |           | 18: face- and edge neighbors
        *                   |           | 26: 3*3*3 neighborhood
        *                   |           | 124: 5*5*5 neighborhood
        *                   |           | 342: 7*7*7 neighborhood
        */
        void getNeighbors(int index, int neighborhoodSize, vector <Neighbor> &neighbors) const;
    };
}

#endif