#ifndef LATTICELIBRARY_DEFS_H
#define LATTICELIBRARY_DEFS_H

/** \mainpage LatticeLibrary
 *
 * \section intro_sec Introduction
 * LatticeLibrary is a C++ framework for general processing of 2D and 3D data organized on arbitrary lattices. The current implementation supports the Cartesian Cubic (CC), Body-Centered Cubic (BCC) and Face-Centered Cubic (FCC) lattices, and the software architecture is meant to facilitate addition of other lattices. The data is treated as an undirected mathematical graph, the connectivity of which is defined using the Lattice class, enabling the application of all implemented processing methods to data organized on any lattice. An introduction to undirected graphs can be found in, for example, [Trudeau 1994] (http://www.amazon.com/Introduction-Graph-Theory-Dover-Mathematics/dp/0486678709).
 * By introducing software for processing data organized on alternative lattices, we hope to facilitate and encourage further studies of the possible advantages of non-Cartesian lattices in a wide range of research areas.
 *
 * \subsection features Features
 * As LatticeLibrary is originally developed to study the behavior of various image processing methods applied to data sampled on the BCC and FCC lattices, most of the featured functionality is focused in this area. However, we hope that LatticeLibrary may serve as a foundation for other applications as well.
 *
 * \subsection Licence
 * LatticeLibrary is available under the [GNU Lesser General Public License v2.1] (http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html).
 *
 * \section install_sec Installation
 * \subsection req Requirements
 * - CMake 2.8.4 or later.
 * - GCC or Clang with C++11 support.
 * \subsection comp Compilation
 * CMakeLists.txt provides instructions for building a test environment.
 */

namespace LatticeLib {

    typedef unsigned char uint8;

    #define EPSILON 0.0000001 // tolerance for comparisons
    #define EPSILONT 0.0000001 // tolerance for testing
    #define INF 10000000.0
    #define PI 3.141592653589793
    #define MIN(a, b) (a < b ? a : b)
    #define MAX(a, b) (a > b ? a : b)
    #define IS_EVEN(a) ((a) % 2 == 0)

}
#endif
