#ifndef BCCLATTICE_H
#define BCCLATTICE_H

#include "lattice.h"

namespace LatticeLib {

#define BCCOFFSET 0.629960524947437 // 1/(4^(1/3)), distance between layers in BCC
#define BCCHEXFACEDISTANCE 1.091123635971721 // hexagonal face neighbor distance
#define BCCSQFACEDISTANCE 1.259921049894873 // (\cbrt(2)) square face neighbor distance ( = 2 * BCCOFFSET)
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
         * scale        | INPUT     | The number of lattice points per unit volume.
         */
        BCCLattice(int rows, int columns, int layers, double density);

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
        void get8Neighbors(int rowIndex, int columnIndex, int layerIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * elementindex | INPUT     | Element index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get8Neighbors(int elementIndex, vector <Neighbor> &neighbors) const;

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
        void get14Neighbors(int rowIndex, int columnIndex, int layerIndex, vector <Neighbor> &neighbors) const;

        /**
         * Returns the face- and edge neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * elementindex | INPUT     | Element index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get14Neighbors(int elementIndex, vector <Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * rowIndex         | INPUT     | Row index.
         * columnIndex      | INPUT     | Column index.
         * layerIndex       | INPUT     | Layer index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 8: hexagonal face neighbors <br> 14: hexagonal- and square face neighbors
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int rowIndex, int columnIndex, int layerIndex, int neighborhoodSize, vector <Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * elementIndex     | INPUT     | Element index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 8: hexagonal face neighbors <br> 14: hexagonal- and square face neighbors
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int elementIndex, int neighborhoodSize, vector <Neighbor> &neighbors) const;
    };
}

#endif