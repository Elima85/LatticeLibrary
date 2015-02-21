#ifndef LATTICE_H
#define LATTICE_H

#include "neighbor.h"
#include <vector>

using namespace std;

namespace CImage {

/**
* A graph-based representation of a sampling lattice.
*
* Member 		| Comment
* :-------		| :-------
* nColumns		| #rows of the lattice
* nRows		    | #columns of the lattice
* nLayers		| #layers of the lattice
* nElements	    | total #elements of the lattice
* scaleFactor	| Determines the scaling of the lattice. Default is one sample/unit volume.
*/
    class Lattice {

    protected:
        /** \#columns */
        int nColumns;

        /** \#rows */
        int nRows;

        /** \#layers */
        int nLayers;

        /** \#elements */
        int nElements;

        /** Determines the density of the lattice. */
        double scaleFactor;

    public:
        Lattice(int nr, int nc, int nl, double sf);
        Lattice(const Lattice &original);
        virtual ~Lattice() {}; // is this a definition that should be in the cpp-file instead?

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
        * Checks whether an element is inside the lattice.
        */
        bool isValid(int index) const;

        /**
        * Checks whether an element is inside the lattice.
        */
        bool isValid(int row, int column, int layer) const;

        /**
        * Converts the row-, column-, and layer indices of an element to its index in the data array.
        */
        int rclToIndex(int row, int column, int layer) const;

        /**
        * Converts the index of an element to its column index.
        */
        int indexToC(int index) const;

        /**
        * Converts the index of an element to its row index.
        */
        int indexToR(int index) const;

        /**
        * Converts the index of an element to its layer index.
        */
        int indexToL(int index) const;

        /**
        * Converts the index of an element to its x-coordinate.
        */
        virtual double indexToX(int index) const = 0;

        /**
        * Converts the index of an element to its y-coordinate.
        */
        virtual double indexToY(int index) const = 0;

        /**
        * Converts the index of an element to its z-coordinate.
        */
        virtual double indexToZ(int index) const = 0;

        /**
        * Uses indexTo[X,Y,Z](i) to compute the coordinates of the element with index i.
        *
        * Parameter	    | in/out	| Comment
        * :----------	| :-------	| :--------
        * index		    | 			| index of element
        * coordinates	| OUTPUT	| coordinates of the spatial elements
        */
        void getCoordinates(int index, vector<double> &coordinates) const;

        /**
        * Computes the Euclidean distance between two elements.
        */
        double euclideanDistance(int index1, int index2) const;

        /**
        * Computes the Euclidean distance vector pointing from element i to element j.
        */
        void euclideanDistanceVector(int index1, int index2, vector<double> &distanceVector) const;

        /**
        * Returns the neighbors of an element.
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * row		        | 			| row of the element
        * column	        |           | column of the element
        * layer             |           | layer of the element
        * neighborhoodSize  |           | requested neighborhood size
        * neighbors         | OUTPUT    | vector of neighbor objects, containing the global and local index of each neighbor.
        */
        virtual void getNeighbors(int row, int column, int layer, int neighborhoodSize, vector<Neighbor> &neighbors) const = 0;

        /**
        * Returns the neighbors of an element.
        *
        * Parameter	        | in/out	| Comment
        * :----------	    | :-------	| :--------
        * index		        | 			| index of the element
        * neighborhoodSize  |           | requested neighborhood size
        * neighbors         | OUTPUT    | vector of neighbor objects, containing the global and local index of each neighbor.
        */
        virtual void getNeighbors(int index, int neighborhoodSize, vector<Neighbor> &neighbors) const = 0;

        /**
        *
        */
        //virtual double coverageToAverageDistance(uint8 coverage) const = 0;

        /**
        *
        */
        //virtual double coverageToAverageDistance(double coverage) const = 0;

    };

}

#endif