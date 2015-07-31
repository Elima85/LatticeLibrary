#ifndef FCCLATTICE_H
#define FCCLATTICE_H

#include "lattice.h"
#include "linearinterpolation.h"
#include <cmath>

namespace LatticeLib {
#define FCCOFFSET 0.793700525984100 // 1/(2^(1/3)), distance between layers in FCC
#define FCCFACEDISTANCE 1.122462048309373 // face neighbor distance
#define FCCPOINTDISTANCE 1.587401051968199 // 2/(2^(1/3)), point neighbor distance
    const double distanceTableFCC[] = {0.714077046326529, 0.584803910742471, 0.539549351387385, 0.514827152974004,
                                         0.494182137726088, 0.474779246135581, 0.457429195670903, 0.444857955564193,
                                         0.432049156262755, 0.416457896497643, 0.406295118688379, 0.395099247457030,
                                         0.383984914266236, 0.373939520778821, 0.365127204667108, 0.354809540369391,
                                         0.344742627461438, 0.335591156334671, 0.326989274134147, 0.317776359547039,
                                         0.307758730036562, 0.297990203600959, 0.289601501302384, 0.282373570385305,
                                         0.274091628675670, 0.265677476283618, 0.257639748014919, 0.249811259480845,
                                         0.241931405009107, 0.234613601807503, 0.226629910710280, 0.218426567840259,
                                         0.210969972072138, 0.204970597016393, 0.198200540088346, 0.190695890815276,
                                         0.182793900838194, 0.175633893526011, 0.170742902343941, 0.162768805584692,
                                         0.156227685808754, 0.151008107616109, 0.145752745772041, 0.139159470809782,
                                         0.131352246116331, 0.124123023669870, 0.117882609641882, 0.112013962417163,
                                         0.105179520511002, 0.098065042076195, 0.090231585203651, 0.083009647739121,
                                         0.078744449568174, 0.068700177909267, 0.061433745479717, 0.055568374014679,
                                         0.048991541832693, 0.042445590781161, 0.034485090405223, 0.027694335480268,
                                         0.021722076617656, 0.015428180841809, 0.010236512587796, 0.003707371875781,
                                         -0.003630851925319, -0.010631573445721, -0.016410970291770, -0.023322622799315,
                                         -0.028825749810292, -0.034732814119153, -0.042002255077926, -0.048067280463827,
                                         -0.055747223920438, -0.062483286304572, -0.068408121666749, -0.074493907320462,
                                         -0.081306297387967, -0.088382396840916, -0.096162589794095, -0.104260062680029,
                                         -0.111686279510446, -0.118634581261823, -0.125211426614980, -0.131617741383244,
                                         -0.138195415529015, -0.145384226245301, -0.149171106862121, -0.155255401999289,
                                         -0.163796132921106, -0.172131726206582, -0.178992083695221, -0.186852374100716,
                                         -0.193109335183382, -0.199360097653993, -0.208887666498899, -0.216334847227242,
                                         -0.222520382851360, -0.229712301302484, -0.238404293937451, -0.246180071162991,
                                         -0.251547526818121, -0.259023433738466, -0.268319052135775, -0.277427580468557,
                                         -0.285128086314985, -0.293499153982363, -0.300869506924703, -0.309212407534078,
                                         -0.320907601467231, -0.328155731251493, -0.336715699297306, -0.345794247700394,
                                         -0.355579894093477, -0.367494153207715, -0.378436472328643, -0.387858147892052,
                                         -0.396477352246857, -0.405475042921039, -0.416825667569806, -0.431295712646092,
                                         -0.446430380869664, -0.462255639266114, -0.479204286758705, -0.494706543978469,
                                         -0.511852029543659, -0.534751990156574, -0.581183711707067,
                                         -0.719465948707445};

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
         * scale        | INPUT     | The number of lattice points per unit volume.
         */
        FCCLattice(int rows, int columns, int layers, double density);

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
            values.push_back(distanceTableFCC[bounds[0]]);
            values.push_back(distanceTableFCC[bounds[1]]);
            double scaleFactor = cbrt(1 / getDensity());
            return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
        }

        /**
         * Returns the face neighbors of the element at \f$(row,column,layer)\f$.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * rowIndex     | INPUT     | Row index.
         * columnIndex  | INPUT     | Column index.
         * layerIndex   | INPUT     | Layer index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get12Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const;

        /**
         * Returns the face neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * elementindex | INPUT     | Element index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get12Neighbors(int elementIndex, vector<Neighbor> &neighbors) const;

        /**
         * Returns the face- and edge neighbors of the element at \f$(row,column,layer)\f$.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * rowIndex     | INPUT     | Row index.
         * columnIndex  | INPUT     | Column index.
         * layerIndex   | INPUT     | Layer index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get18Neighbors(int rowIndex, int columnIndex, int layerIndex, vector<Neighbor> &neighbors) const;

        /**
         * Returns the face- and edge neighbors of the element with index \f$(index)\f$.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * elementindex | INPUT     | Element index.
         * neighbors    | OUTPUT    | Extracted neighbors.
         */
        void get18Neighbors(int elementIndex, vector<Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * rowIndex         | INPUT     | Row index.
         * columnIndex      | INPUT     | Column index.
         * layerIndex       | INPUT     | Layer index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 12: face neighbors <br> 18: face- and point neighbors
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int rowIndex, int columnIndex, int layerIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const;

        /**
         * Implements Lattice::getNeighbors().
         *
         * Parameter	    | in/out	| Comment
         * :----------	    | :-------	| :--------
         * elementindex     | INPUT     | Element index.
         * neighborhoodSize | INPUT     | Requested neighborhood size. <br> 12: face neighbors <br> 18: face- and point neighbors
         * neighbors        | OUTPUT    | Extracted neighbors.
         */
        void getNeighbors(int elementIndex, int neighborhoodSize, vector<Neighbor> &neighbors) const;
    };

}

#endif