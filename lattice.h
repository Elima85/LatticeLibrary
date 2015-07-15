#ifndef LATTICE_H
#define LATTICE_H

#include "neighbor.h"
#include <vector>

using namespace std;

namespace LatticeLib {

    //TODO: index -> elementIndex, row -> rowIndex, etc...

/**
* A graph-based representation of a sampling lattice, to be used as a foundation for different applications.
*
* Member 		| Comment
* :-------		| :-------
* nColumns		| Number of rows of the lattice.
* nRows		    | Number of columns of the lattice.
* nLayers		| Number of layers of the lattice.
* nElements	    | total number of elements of the lattice.
* scaleFactor	| Determines the scaling of the lattice. Default is one sample/unit volume. TODO: Doesn't seem right... Figure out how it works!
*/
    class Lattice {

    protected:
        /** Number of columns. */
        int nColumns;

        /** Number of rows. */
        int nRows;

        /** Number of layers. */
        int nLayers;

        /** Determines the density of the lattice. // TODO: Figure out and explain more. */
        double scaleFactor;

    public:

        /**
         * Constructor for Lattice objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * rows         | INPUT     | Number of rows.
         * columns      | INPUT     | Number of columns.
         * layers       | INPUT     | Number of layers.
         * scale        | INPUT     | Distance scale factor. TODO: Figure out how this works!!
         */
        Lattice(int rows, int columns, int layers, double scale);


        /**
         * Copy constructor for Lattice objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * original     | INPUT     | Object to be copied.
         */
        Lattice(const Lattice &original);

        /**
         * Destructor for Lattice objects.
         */
        virtual ~Lattice();

        /**
        * Returns the number of spatial elements of the lattice.
        */
        int getNElements() const;

        /*
         * Returns the number of rows of the lattice.
         */
        int getNColumns() const;

        /**
        * Returns the number of columns of the lattice.
        */
        int getNRows() const;

        /**
        * Returns the number of layers of the lattice.
        */
        int getNLayers() const;

        /**
        * Returns the lattice scale factor.
        */
        double getScaleFactor() const;

        /**
        * Returns the width of the lattice in distance units.
        */
        virtual double getWidth() const = 0;

        /**
        * Returns the height of the lattice in distance units.
        */
        virtual double getHeight() const = 0;

        /**
        * Returns the depth of the lattice in distance units.
        */
        virtual double getDepth() const = 0;

        /**
        * Checks whether an element is within the span of the lattice.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * index        | INPUT     | Element index.
        */
        bool isValid(int index) const;

        /**
        * Checks whether an element is within the span of the lattice.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * row          | INPUT     | Row index.
         * column       | INPUT     | Column index.
         * layer        | INPUT     | Layer index.
        */
        bool isValid(int row, int column, int layer) const;

        /**
         * Converts the row-, column-, and layer indices of an element to its element index.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * row          | INPUT     | Row index.
         * column       | INPUT     | Column index.
         * layer        | INPUT     | Layer index.
         */
        int rclToIndex(int row, int column, int layer) const;

        /**
        * Converts the index of an element to its column index.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * index        | INPUT     | Element index.
        */
        int indexToC(int index) const;

        /**
        * Converts the index of an element to its row index.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * index        | INPUT     | Element index.
        */
        int indexToR(int index) const;

        /**
        * Converts the index of an element to its layer index.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * index        | INPUT     | Element index.
        */
        int indexToL(int index) const;

        /**
        * Converts the index of an element to its x-coordinate.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * index        | INPUT     | Element index.
        */
        virtual double indexToX(int index) const = 0;

        /**
        * Converts the index of an element to its y-coordinate.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * index        | INPUT     | Element index.
        */
        virtual double indexToY(int index) const = 0;

        /**
        * Converts the index of an element to its z-coordinate.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * index        | INPUT     | Element index.
        */
        virtual double indexToZ(int index) const = 0;

        /**
        * Uses indexTo[X,Y,Z](i) to compute the coordinates of an element based on its index.
        *
        * Parameter	    | in/out	| Comment
        * :----------	| :-------	| :--------
        * index		    | INPUT 	| index of element
        * coordinates	| OUTPUT	| coordinates of the spatial elements
        */
        void getCoordinates(int index, vector<double> &coordinates) const;

        /**
        * Computes the Euclidean distance between two elements.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * index1       | INPUT     | First element index.
         * index2       | INPUT     | Second element index.
        */
        double euclideanDistance(int index1, int index2) const;

        /**
        * Computes the Euclidean distance vector from element index1 to element index2.
         *
         * Parameter        | in/out	| Comment
         * :----------      | :-------	| :--------
         * index1           | INPUT     | First element index.
         * index2           | INPUT     | Second element index.
         * distanceVector   | OUTPUT    | Vector pointing from element index1 to element index2.
        */
        void euclideanDistanceVector(int index1, int index2, vector<double> &distanceVector) const;

        /*
         * Approximates the distance from the spel center to an edge within the spel based on the coverage value of the spel.
         */
        // TODO: virtual double coverageToInternalDistance(double coverage) const = 0;

        /**
        * Returns the neighbors of an element.
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * row		        | INPUT		| row of the element
        * column	        | INPUT     | column of the element
        * layer             | INPUT     | layer of the element
        * neighborhoodSize  | INPUT     | requested neighborhood size
        * neighbors         | OUTPUT    | vector of neighbor objects, containing the global and local index of each neighbor.
        */
        virtual void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector<Neighbor> &neighbors) const = 0;

        /**
        * Returns the neighbors of an element.
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * index		        | INPUT		| index of the element
        * neighborhoodSize  | INPUT     | requested neighborhood size
        * neighbors         | OUTPUT    | vector of neighbor objects, containing the global and local index of each neighbor.
        */
        virtual void getNeighbors(int index, int neighborhoodSize, vector<Neighbor> &neighbors) const = 0;

        /**
         * Compares the type and members of two Lattice objects, and returns true if all are equal.
         */
        bool operator==(const Lattice& rhs) const;

        /**
         * Compares the type and members of two Lattice objects, and returns false if all are equal.
         */
        bool operator!=(const Lattice &rhs) const;

    };

}

#endif