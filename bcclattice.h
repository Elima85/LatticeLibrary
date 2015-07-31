#ifndef BCCLATTICE_H
#define BCCLATTICE_H

#include "lattice.h"
#include "linearinterpolation.h"
#include <cmath>

namespace LatticeLib {

#define BCCOFFSET 0.629960524947437 // 1/(4^(1/3)), distance between layers in BCC
#define BCCHEXFACEDISTANCE 1.091123635971721 // hexagonal face neighbor distance
#define BCCSQFACEDISTANCE 1.259921049894873 // (\cbrt(2)) square face neighbor distance ( = 2 * BCCOFFSET)
    const double distanceTableBCC[] = {0.701972775991366, 0.559384096369300, 0.523708491831535, 0.504208119337289,
                                         0.485961099189012, 0.472741906135919, 0.458428017799460, 0.445843863595213,
                                         0.434019197645408, 0.421854125314656, 0.410046880337088, 0.398436206179092,
                                         0.388502787488950, 0.379144338651330, 0.368789186781820, 0.360067592029462,
                                         0.351589510084802, 0.340956184471487, 0.329472567765149, 0.321934283205210,
                                         0.313308029661695, 0.304521999486493, 0.295681765149159, 0.287079844458938,
                                         0.279572841418967, 0.270861674256076, 0.258622537052800, 0.247030386296779,
                                         0.239786630506896, 0.230416027579064, 0.222140243071163, 0.215396284206380,
                                         0.209046622997721, 0.201292811785985, 0.194850180312712, 0.186887340378882,
                                         0.178301036183765, 0.169774888060555, 0.160240158042547, 0.151141619183839,
                                         0.144910123075057, 0.139387081056519, 0.132275281214361, 0.123179449447133,
                                         0.115209909239135, 0.110282588275489, 0.105846354179058, 0.097971825318819,
                                         0.091618971374103, 0.084055977701946, 0.077881461109973, 0.073232744286903,
                                         0.067781308571245, 0.061551851798691, 0.053606146291214, 0.046420652020054,
                                         0.041350100604422, 0.036400013065505, 0.029826111258516, 0.023163184058998,
                                         0.016486093935675, 0.009027623284885, 0.000545114595576, -0.006409316162271,
                                         -0.011482052972629, -0.015909380103552, -0.021930295484404, -0.030471309324572,
                                         -0.040087312040690, -0.046264459750243, -0.049745671713369, -0.055999006275204,
                                         -0.063703031687841, -0.072133278469194, -0.080124877274717, -0.086253283696209,
                                         -0.088776416146436, -0.095688808377654, -0.104454984748970, -0.112888180402466,
                                         -0.121260312573985, -0.126321890828481, -0.131849231572847, -0.138220378699248,
                                         -0.145300216688578, -0.152684773950153, -0.159078310790973, -0.166091155853891,
                                         -0.173145831561477, -0.179553181648581, -0.186280945968988, -0.192493313638436,
                                         -0.199834267437540, -0.207937851311092, -0.215239752797464, -0.222649547807335,
                                         -0.231373128404468, -0.239614163904793, -0.247238387508153, -0.256049244942309,
                                         -0.261748975120585, -0.269512678472865, -0.278161635054214, -0.285938506381002,
                                         -0.294409262751931, -0.304112483169524, -0.313207636275675, -0.322104272848939,
                                         -0.332070852300711, -0.343230544965409, -0.352860726531219, -0.361270311111415,
                                         -0.369949001001639, -0.381124542872056, -0.390590115886440, -0.402038335648907,
                                         -0.413310900786398, -0.423543150723804, -0.436036024356762, -0.447960451557584,
                                         -0.460686204854493, -0.473981713655202, -0.487815571365090, -0.505860782414118,
                                         -0.521218530696975, -0.540411881786846, -0.581537424601552, -0.713634612236801};

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
         * Approximates the distance from the element center to an edge intersecting the element based on the coverage value of the element.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * coverage     | INPUT     | Element coverage value.
         */
        double approximateDistanceToElementCenter(double coverage) const {
            LinearInterpolation<int, double> interpolation;
            double coveragePosition = coverage * 128;
            vector<int> bounds;
            bounds.push_back(floor(coveragePosition));
            bounds.push_back(ceil(coveragePosition));
            vector<double> values;
            values.push_back(distanceTableBCC[bounds[0]]);
            values.push_back(distanceTableBCC[bounds[1]]);
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