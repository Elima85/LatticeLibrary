#ifndef CCLATTICE_H
#define CCLATTICE_H

#include "lattice.h"

namespace LatticeLib {
    // TODO: const double subSpelDistanceVoronoiCC[] = {[255 elements]};

    class CCLattice : public Lattice {

    public:

        /**
         * Constructor for CCLattice objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * rows         | INPUT     | Number of rows.
         * columns      | INPUT     | Number of columns.
         * layers       | INPUT     | Number of layers.
         * scale        | INPUT     | Distance scale factor. TODO: Figure out how this works!!
         */
        CCLattice(int rows, int columns, int layers, double scale);

        /**
         * Copy constructor for CCLattice objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * original     | INPUT     | Object to be copied.
         */
        CCLattice(const CCLattice &original);

        /**
         * Destructor for CCLattice objects.
         */
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

        /*
         * Implements Lattice::coverageToInternalDistance().
         */
        // TODO: double coverageToInternalDistance(double coverage) const;

        /**
         * Returns the face neighbors of the element at \f$(row,column,layer)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * row              | INPUT     | Row index.
         * column           | INPUT     | Column index.
         * layer            | INPUT     | Layer index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get6Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get6Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face- and edge neighbors of the element at \f$(row,column,layer)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * row              | INPUT     | Row index.
         * column           | INPUT     | Column index.
         * layer            | INPUT     | Layer index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get18Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face- and edge neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get18Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face-, edge- and node neighbors of the element with index \f$(row,column,layer)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * row              | INPUT     | Row index.
         * column           | INPUT     | Column index.
         * layer            | INPUT     | Layer index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get26Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face-, edge- and point neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get26Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
         * Returns the neighbors within a \f5\times5\times5\f cube with its center at \f$(row,column,layer)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * row              | INPUT     | Row index.
         * column           | INPUT     | Column index.
         * layer            | INPUT     | Layer index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get124Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
         * Returns the neighbors within a \f5\times5\times5\f cube with its center at element \f$(index)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get124Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
         * Returns the neighbors within a \f7\times7\times7\f cube with its center at \f$(row,column,layer)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * row              | INPUT     | Row index.
         * column           | INPUT     | Column index.
         * layer            | INPUT     | Layer index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get342Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
         * Returns the neighbors within a \f7\times5\times7\f cube with its center at element \f$(index)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get342Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * row              | INPUT     | Row index.
         * column           | INPUT     | Column index.
         * layer            | INPUT     | Layer index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 6: face neighbors <br> 18: face- and edge neighbors <br> 26: 3*3*3 neighborhood <br> 124: 5*5*5 neighborhood <br> 342: 7*7*7 neighborhood
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector <Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 6: face neighbors <br> 18: face- and edge neighbors <br> 26: 3*3*3 neighborhood <br> 124: 5*5*5 neighborhood <br> 342: 7*7*7 neighborhood
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int index, int neighborhoodSize, vector <Neighbor> &neighbors) const;
    };
}

#endif