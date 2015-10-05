#ifndef LATTICELIBRARY_CCLATTICE_H
#define LATTICELIBRARY_CCLATTICE_H

#include "lattice.h"

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

    const double surfaceAreaTableCC[] = {0, 0.086282546915059, 0.142747874132873, 0.186681193748981, 0.224503160947247,
                                         0.260279897126464, 0.294689911671602, 0.324900429988785, 0.353408321054462,
                                         0.379075176808474, 0.402784190101668, 0.425193773004387, 0.446705167169553,
                                         0.467542874916364, 0.494409193164560, 0.519280849128530, 0.541876584034199,
                                         0.563043526974491, 0.583239717628629, 0.602198312599792, 0.620962317250418,
                                         0.638966466653342, 0.655814673179948, 0.672705330998640, 0.687852036666179,
                                         0.702973886114577, 0.716784564614640, 0.730417632231915, 0.744020940558507,
                                         0.756396103992636, 0.769179819365003, 0.781063094222025, 0.793348613232633,
                                         0.805004260613198, 0.816380426744302, 0.827385455018609, 0.838411434515594,
                                         0.848578012923104, 0.859111452065815, 0.868571347463134, 0.878021772342081,
                                         0.887543999256658, 0.896462091082193, 0.905616124691865, 0.914292040133489,
                                         0.922773903270102, 0.931362515580305, 0.939376895588081, 0.947089010301685,
                                         0.955345182324297, 0.962379435700296, 0.969982510630157, 0.976945416892412,
                                         0.983906516268904, 0.990924763837273, 0.997503279379578, 1.004118676321133,
                                         1.010331984771550, 1.016792754333133, 1.022559356659813, 1.028547632263286,
                                         1.034347097709737, 1.039591640529596, 1.045252871052492, 1.050593334687173,
                                         1.055198683876490, 1.060613330558535, 1.065449400567071, 1.069966730612421,
                                         1.074820011532678, 1.078956646822374, 1.083415446237701, 1.087638505936859,
                                         1.091760247216225, 1.095649273532701, 1.099762436530215, 1.103166581270538,
                                         1.106896210276216, 1.110170810387363, 1.113554807347082, 1.116875875092926,
                                         1.119904807610826, 1.123174224987284, 1.126017165530898, 1.129212203324038,
                                         1.131929641853993, 1.134236900507937, 1.136936297987588, 1.139764131425315,
                                         1.141864044566793, 1.143536644153429, 1.145862880333492, 1.148537392478870,
                                         1.149785576525385, 1.151287934263153, 1.153699812721307, 1.154574400984647,
                                         1.156025910475379, 1.157467247928337, 1.158744406883927, 1.159847456268074,
                                         1.161081309419742, 1.162074121375801, 1.163667138317685, 1.164225705228560,
                                         1.165258201468969, 1.166758486799366, 1.167785378189319, 1.168289007223496,
                                         1.168419560354888, 1.169957417710073, 1.169864302308399, 1.170328527266554,
                                         1.170751497939120, 1.171308190464854, 1.171801059319674, 1.172226028512612,
                                         1.172714569028369, 1.172483139996698, 1.173140613630635, 1.173566551785727,
                                         1.173680230238339, 1.173587258714718, 1.174911561658152, 1.175229704605294,
                                         1.174927769644450, 1.175329588700438, 1.175629034173856, 1.175629034173856,
                                         1.175329588700438, 1.174927769644450, 1.175229704605294, 1.174911561658152,
                                         1.173587258714718, 1.173680230238339, 1.173566551785727, 1.173140613630635,
                                         1.172483139996697, 1.172714569028369, 1.172226028512612, 1.171801059319674,
                                         1.171308190464854, 1.170751497939120, 1.170328527266554, 1.169864302308399,
                                         1.169957417710073, 1.168419560354888, 1.168289007223496, 1.167785378189320,
                                         1.166758486799366, 1.165258201468969, 1.164225705228560, 1.163667138317685,
                                         1.162074121375802, 1.161081309419742, 1.159847456268074, 1.158744406883928,
                                         1.157467247928337, 1.156025910475379, 1.154574400984647, 1.153699812721307,
                                         1.151287934263153, 1.149785576525385, 1.148537392478870, 1.145862880333492,
                                         1.143536644153429, 1.141864044566793, 1.139764131425315, 1.136936297987588,
                                         1.134236900507937, 1.131929641853993, 1.129212203324038, 1.126017165530898,
                                         1.123174224987284, 1.119904807610827, 1.116875875092926, 1.113554807347082,
                                         1.110170810387363, 1.106896210276216, 1.103166581270538, 1.099762436530215,
                                         1.095649273532700, 1.091760247216225, 1.087638505936859, 1.083415446237701,
                                         1.078956646822374, 1.074820011532677, 1.069966730612420, 1.065449400567071,
                                         1.060613330558535, 1.055198683876490, 1.050593334687173, 1.045252871052492,
                                         1.039591640529596, 1.034347097709737, 1.028547632263286, 1.022559356659813,
                                         1.016792754333133, 1.010331984771551, 1.004118676321134, 0.997503279379578,
                                         0.990924763837273, 0.983906516268905, 0.976945416892412, 0.969982510630158,
                                         0.962379435700297, 0.955345182324298, 0.947089010301685, 0.939376895588082,
                                         0.931362515580305, 0.922773903270102, 0.914292040133489, 0.905616124691865,
                                         0.896462091082193, 0.887543999256658, 0.878021772342081, 0.868571347463135,
                                         0.859111452065815, 0.848578012923104, 0.838411434515594, 0.827385455018609,
                                         0.816380426744302, 0.805004260613198, 0.793348613232633, 0.781063094222026,
                                         0.769179819365003, 0.756396103992636, 0.744020940558507, 0.730417632231915,
                                         0.716784564614640, 0.702973886114577, 0.687852036666179, 0.672705330998640,
                                         0.655814673179948, 0.638966466653342, 0.620962317250418, 0.602198312599792,
                                         0.583239717628629, 0.563043526974491, 0.541876584034199, 0.519280849128530,
                                         0.494409193164560, 0.467542874916365, 0.446705167169553, 0.425193773004387,
                                         0.402784190101668, 0.379075176808474, 0.353408321054462, 0.324900429988785,
                                         0.294689911671602, 0.260279897126464, 0.224503160947247, 0.186681193748981,
                                         0.142747874132873, 0.086282546915059, 0};

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
        * Implements Lattice::getElementWidth().
        */
        double getElementWidth() const;

        /**
        * Implements Lattice::getElementHeight().
        */
        double getElementHeight() const;

        /**
        * Implements Lattice::getElementDepth().
        */
        double getElementDepth() const;

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

        /**
         * Implements Lattice::coordinatesToIndex();
         *
         * Parameter    | in/out	| Comment
         * :----------	| :-------	| :--------
         * coordinates	| INPUT 	| coordinates of the spatial elements
         */
        int coordinatesToIndex(vector<double> coordinates) const;

        /**
         * Implements Lattice::approximateDistanceToElementCenter().
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * coverage     | INPUT     | Element coverage value.
         */
        double approximateDistanceToElementCenter(double coverage) const;

        /**
         * Implements Lattice::approximateIntersectionArea().
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * coverage     | INPUT     | Element coverage value.
         */
        double approximateIntersectionArea(double coverage) const;

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