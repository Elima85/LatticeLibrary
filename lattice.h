#ifndef LATTICELIBRARY_LATTICE_H
#define LATTICELIBRARY_LATTICE_H

#include "neighbor.h"
#include <vector>

using namespace std;

namespace LatticeLib {

/**
 * Base class for a graph-based representation of a sampling lattice, to be used as a foundation for different applications.
 *
 * The lattice point with index 0 is placed in the origin, which is in the upper left front corner.
 *
 * Member 		| Comment
 * :-------		| :-------
 * nColumns		| Number of rows of the lattice.
 * nRows	    | Number of columns of the lattice.
 * nLayers		| Number of layers of the lattice.
 * nElements    | total number of elements of the lattice.
 * density      | The number of lattice points per unit volume.
 */
    class Lattice {

    protected:
        /** Number of columns. */
        int nColumns;

        /** Number of rows. */
        int nRows;

        /** Number of layers. */
        int nLayers;

        /** The number of lattice points per unit volume. */
        double latticeDensity;

    public:

        /**
         * Constructor for Lattice objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * rows         | INPUT     | Number of rows.
         * columns      | INPUT     | Number of columns.
         * layers       | INPUT     | Number of layers.
         * density      | INPUT     | The number of lattice points per unit volume.
         */
        Lattice(int rows, int columns, int layers, double density);


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
        * Returns the lattice density.
        */
        double getDensity() const;

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
         * elementIndex | INPUT     | Element index.
        */
        bool isValid(int elementIndex) const;

        /**
        * Checks whether an element is within the span of the lattice.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * rowIndex     | INPUT     | Row index.
         * columnIndex  | INPUT     | Column index.
         * layerIndex   | INPUT     | Layer index.
        */
        bool isValid(int rowIndex, int columnIndex, int layerIndex) const;

        /**
         * Converts the row-, column-, and layer indices of an element to its element index.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * rowIndex     | INPUT     | Row index.
         * columnIndex  | INPUT     | Column index.
         * layerIndex   | INPUT     | Layer index.
         */
        int rclToIndex(int rowIndex, int columnIndex, int layerIndex) const;

        /**
        * Converts the index of an element to its column index.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * elementIndex | INPUT     | Element index.
        */
        int indexToC(int elementIndex) const;

        /**
        * Converts the index of an element to its row index.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * elementIndex | INPUT     | Element index.
        */
        int indexToR(int elementIndex) const;

        /**
        * Converts the index of an element to its layer index.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * elementIndex | INPUT     | Element index.
        */
        int indexToL(int elementIndex) const;

        /**
        * Converts the index of an element to its x-coordinate.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * elementIndex | INPUT     | Element index.
        */
        virtual double indexToX(int elementIndex) const = 0;

        /**
        * Converts the index of an element to its y-coordinate.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * elementIndex | INPUT     | Element index.
        */
        virtual double indexToY(int elementIndex) const = 0;

        /**
         * Converts the index of an element to its z-coordinate.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * elementIndex | INPUT     | Element index.
         */
        virtual double indexToZ(int elementIndex) const = 0;

        /**
         * Returns the index of the element closest to the specified point.
         *
         * Parameter    | in/out	| Comment
         * :----------	| :-------	| :--------
         * coordinates	| INPUT 	| coordinates of the spatial elements
         */
        virtual int coordinatesToIndex(vector<double> coordinates) const = 0;

        /**
        * Uses indexTo[X,Y,Z](i) to compute the coordinates of an element based on its index.
        *
        * Parameter	    | in/out	| Comment
        * :----------	| :-------	| :--------
        * elementIndex  | INPUT 	| index of element
        * coordinates	| OUTPUT	| coordinates of the spatial element
        */
        void getCoordinates(int elementIndex, vector<double> &coordinates) const;

        /**
        * Computes the Euclidean distance between two elements.
         *
         * Parameter        | in/out	| Comment
         * :----------      | :-------	| :--------
         * elementIndex1    | INPUT     | Index of the first element.
         * elementIndex2    | INPUT     | Index of the second element.
        */
        double euclideanDistance(int elementIndex1, int elementIndex2) const;

        /**
        * Computes the Euclidean distance vector from element index1 to element index2.
         *
         * Parameter        | in/out	| Comment
         * :----------      | :-------	| :--------
         * elementIndex1    | INPUT     | Index of the first element.
         * elementIndex2    | INPUT     | Index of the second element.
         * distanceVector   | OUTPUT    | Vector pointing from element index1 to element index2.
        */
        void euclideanDistanceVector(int elementIndex1, int elementIndex2, vector<double> &distanceVector) const;

        /**
         * Approximates the distance from the element center to an edge intersecting the element based on the coverage value of the element.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * coverage     | INPUT     | Element coverage value.
         */
        virtual double approximateDistanceToElementCenter(double coverage) const = 0;

        /**
         * Approximates the area of the intersection between the element and a planar surface based on the coverage value of the element.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * coverage     | INPUT     | Element coverage value.
         */
        virtual double approximateIntersectionArea(double coverage) const = 0;

        /**
        * Returns the neighbors of an element.
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * rowIndex	        | INPUT		| row of the element
        * columnIndex       | INPUT     | column of the element
        * layerIndex        | INPUT     | layer of the element
        * neighborhoodSize  | INPUT     | requested neighborhood size
        * neighbors         | OUTPUT    | vector of neighbor objects, containing the global and local index of each neighbor.
        */
        virtual void getNeighbors(int rowIndex, int columnIndex, int layerIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const = 0;

        /**
        * Returns the neighbors of an element.
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * elementIndex      | INPUT		| index of the element
        * neighborhoodSize  | INPUT     | requested neighborhood size
        * neighbors         | OUTPUT    | vector of neighbor objects, containing the global and local index of each neighbor.
        */
        virtual void getNeighbors(int elementIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const = 0;

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