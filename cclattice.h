#ifndef CCLATTICE_H
#define CCLATTICE_H

#include "lattice.h"
#include "linearinterpolation.h"
#include <cmath>

namespace LatticeLib {
    const double distanceTableCC[] = {0.732561001953818, 0.623694421783119, 0.574117314861196, 0.545268728828970,
                                        0.522258720698669, 0.498729324394126, 0.480707859606576, 0.463058309432147,
                                        0.447547529277453, 0.435059717244305, 0.421979035363776, 0.408772221380592,
                                        0.397218274081152, 0.385408831485960, 0.371034869565175, 0.361626850445366,
                                        0.353133590283520, 0.343685342443376, 0.333243454404165, 0.323842720287171,
                                        0.315971391870786, 0.307344650439405, 0.299684705457515, 0.293155227880055,
                                        0.283489987533105, 0.275961397146807, 0.269506713286797, 0.263202822971670,
                                        0.256156669785891, 0.247577626759671, 0.237204981587119, 0.228948727770187,
                                        0.222544617218361, 0.215783286864766, 0.211576281065243, 0.205299784658052,
                                        0.198656799902412, 0.192562684545687, 0.184012838245001, 0.177640427838295,
                                        0.169949935772603, 0.162649713746829, 0.157511308449056, 0.152682862291989,
                                        0.143888663346916, 0.141342404753425, 0.139786927041494, 0.126969807990735,
                                        0.117183303909957, 0.113489756302915, 0.109829594252491, 0.103392976131273,
                                        0.094241949207657, 0.084322184704939, 0.076215849536726, 0.069930557887927,
                                        0.064249817114914, 0.056120996514145, 0.049036822024338, 0.042203612739737,
                                        0.034763114688529, 0.026654768012468, 0.021932503144634, 0.014911957875909,
                                        0.006680036195622, -0.000562761929592, -0.005652822081754, -0.012546080795956,
                                        -0.020036935176039, -0.026178879796216, -0.031401706399816, -0.040408680802843,
                                        -0.045487588557626, -0.052706370720326, -0.059001198780690, -0.062091002272227,
                                        -0.072586785229022, -0.080657236944146, -0.087066875359926, -0.092979208280686,
                                        -0.099219654384174, -0.104018785849585, -0.115523864279216, -0.126057366702486,
                                        -0.131746142667347, -0.137413735687764, -0.143218451635786, -0.149561154785262,
                                        -0.156400628587445, -0.163581385067814, -0.171102831548518, -0.182654603631760,
                                        -0.190820776326902, -0.196813913548657, -0.203724211825539, -0.206488542749684,
                                        -0.213483246723245, -0.222245239721738, -0.229778356296238, -0.236939694152633,
                                        -0.242784795433991, -0.250554916306037, -0.258950658160991, -0.266840910974776,
                                        -0.277387788493246, -0.286304451774960, -0.292445258370560, -0.299081243599725,
                                        -0.309873043142970, -0.316216427403862, -0.326610620843017, -0.336890614104287,
                                        -0.345557276431350, -0.354894374354358, -0.367061546071091, -0.379432748009766,
                                        -0.390638253836092, -0.401630286245039, -0.417097495500319, -0.430449889421386,
                                        -0.442913278930958, -0.457713438299709, -0.479274915322158, -0.508435392312227,
                                        -0.533759096776991, -0.559184238862179, -0.602187829564287, -0.729122335558677};

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
         * Approximates the distance from the element center to an edge intersecting the element based on the coverage value of the element.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * coverage     | INPUT     | Element coverage value.
         */
        double approximateDistanceToElementCenter(double coverage) const {
            LinearInterpolation <int, double> interpolation;
            double coveragePosition = coverage * 128;
            vector<int> bounds;
            bounds.push_back(floor(coveragePosition));
            bounds.push_back(ceil(coveragePosition));
            vector<double> values;
            values.push_back(distanceTableCC[bounds[0]]);
            values.push_back(distanceTableCC[bounds[1]]);
            double scaleFactor = cbrt(1 / getDensity());
            return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
        }

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