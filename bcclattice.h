#ifndef BCCLATTICE_H
#define BCCLATTICE_H

#include "lattice.h"

namespace LatticeLib {

#define BCCOFFSET 0.629960524947437 // 1/(4^(1/3)), distance between layers in BCC
#define BCCHEXFACEDISTANCE 1.091123635971721 // hexagonal face neighbor distance
#define BCCSQFACEDISTANCE 1.259921049894873 // square face neighbor distance
    // TODO: const double subSpelDistanceVoronoiBCC[] = {[255 elements]};

    class BCCLattice : public Lattice {

    public:

        /**
         * Constructor for BCCLattice objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * rows         | INPUT     | Number of rows.
         * columns      | INPUT     | Number of columns.
         * layers       | INPUT     | Number of layers.
         * scale        | INPUT     | Distance scale factor. TODO: Figure out how this works!!
         */
        BCCLattice(int rows, int columns, int layers, double scale);

        /**
         * Copy constructor for BCCLattice objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * original     | INPUT     | Object to be copied.
         */
        BCCLattice(const BCCLattice &original);

        /**
         * Destructor for BCCLattice objects.
         */
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
        void get8Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get8Neighbors(int index, vector <Neighbor> &neighbors) const;

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
        void get14Neighbors(int row, int column, int layer, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face- and edge neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get14Neighbors(int index, vector <Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * row              | INPUT     | Row index.
         * column           | INPUT     | Column index.
         * layer            | INPUT     | Layer index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 8: hexagonal face neighbors <br> 14: hexagonal- and square face neighbors
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector <Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 8: hexagonal face neighbors <br> 14: hexagonal- and square face neighbors
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int index, int neighborhoodSize, vector <Neighbor> &neighbors) const;
    };
}

#endif