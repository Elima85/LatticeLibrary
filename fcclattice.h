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

        /**
         * Constructor for FCCLattice objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * rows         | INPUT     | Number of rows.
         * columns      | INPUT     | Number of columns.
         * layers       | INPUT     | Number of layers.
         * scale        | INPUT     | Distance scale factor. TODO: Figure out how this works!!
         */
        FCCLattice(int rows, int columns, int layers, double scale);

        /**
         * Copy constructor for FCCLattice objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * original     | INPUT     | Object to be copied.
         */
        FCCLattice(const FCCLattice &original);

        /**
         * Destructor for BCCLattice objects.
         */
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
        void get12Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const;

        /**
         * Returns the face neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get12Neighbors(int index, vector<Neighbor> &neighbors) const;

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
        void get18Neighbors(int row, int column, int layer, vector<Neighbor> &neighbors) const;

        /**
         * Returns the face- and edge neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void get18Neighbors(int index, vector<Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * row              | INPUT     | Row index.
         * column           | INPUT     | Column index.
         * layer            | INPUT     | Layer index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 12: face neighbors <br> 18: face- and point neighbors
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector<Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * index            | INPUT     | Element index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 12: face neighbors <br> 18: face- and point neighbors
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int index, int neighborhoodSize, vector<Neighbor> &neighbors) const;
    };

}

#endif