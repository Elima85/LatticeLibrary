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
         * density      | INPUT     | The number of lattice points per unit volume.
         */
        CCLattice(int rows, int columns, int layers, double density);

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
        double indexToX(int elementIndex) const;

        /**
         * Implements Lattice::indexToY().
         */
        double indexToY(int elementIndex) const;

        /**
         * Implements Lattice::indexToZ().
         */
        double indexToZ(int elementIndex) const;

        /*
         * Implements Lattice::coverageToInternalDistance().
         */
        // TODO: double coverageToInternalDistance(double coverage) const;

        /**
         * Returns the face neighbors of the element at \f$(row,column,layer)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * rowIndex     | INPUT     | Row index.
         * columnIndex  | INPUT     | Column index.
         * layerIndex   | INPUT     | Layer index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get6Neighbors(int rowIndex, int columnIndex, int layerIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * elementIndex | INPUT     | Element index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get6Neighbors(int elementIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face- and edge neighbors of the element at \f$(row,column,layer)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * rowIndex     | INPUT     | Row index.
         * columnIndex  | INPUT     | Column index.
         * layerIndex   | INPUT     | Layer index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get18Neighbors(int rowIndex, int columnIndex, int layerIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face- and edge neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * elementIndex | INPUT     | Element index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get18Neighbors(int elementIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face-, edge- and node neighbors of the element with index \f$(row,column,layer)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * rowIndex     | INPUT     | Row index.
         * columnIndex  | INPUT     | Column index.
         * layerIndex   | INPUT     | Layer index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get26Neighbors(int rowIndex, int columnIndex, int layerIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face-, edge- and point neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * elementIndex | INPUT     | Element index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get26Neighbors(int elementIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the neighbors within a \f5\times5\times5\f cube with its center at \f$(row,column,layer)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * rowIndex     | INPUT     | Row index.
         * columnIndex  | INPUT     | Column index.
         * layerIndex   | INPUT     | Layer index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get124Neighbors(int rowIndex, int columnIndex, int layerIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the neighbors within a \f5\times5\times5\f cube with its center at element \f$(index)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * elementIndex | INPUT     | Element index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get124Neighbors(int elementIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the neighbors within a \f7\times7\times7\f cube with its center at \f$(row,column,layer)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * rowIndex     | INPUT     | Row index.
         * columnIndex  | INPUT     | Column index.
         * layerIndex   | INPUT     | Layer index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get342Neighbors(int rowIndex, int columnIndex, int layerIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the neighbors within a \f7\times5\times7\f cube with its center at element \f$(index)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * elementIndex | INPUT     | Element index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get342Neighbors(int elementIndex, vector <Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * rowIndex         | INPUT     | Row index.
         * columnIndex      | INPUT     | Column index.
         * layerIndex       | INPUT     | Layer index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 6: face neighbors <br> 18: face- and edge neighbors <br> 26: 3*3*3 neighborhood <br> 124: 5*5*5 neighborhood <br> 342: 7*7*7 neighborhood
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int rowIndex, int columnIndex, int layerIndex, int neighborhoodSize, vector <Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * elementIndex     | INPUT     | Element index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 6: face neighbors <br> 18: face- and edge neighbors <br> 26: 3*3*3 neighborhood <br> 124: 5*5*5 neighborhood <br> 342: 7*7*7 neighborhood
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int elementIndex, int neighborhoodSize, vector <Neighbor> &neighbors) const;
    };
}

#endif