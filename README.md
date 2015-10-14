# LatticeLibrary

## Introduction
LatticeLibrary is a C++ framework for general processing of 2D and 3D data organized on arbitrary lattices. The current implementation supports the Cartesian Cubic (CC), Body-Centered Cubic (BCC) and Face-Centered Cubic (FCC) lattices, and the software architecture is meant to facilitate addition of other lattices. The data is treated as an undirected mathematical graph, the connectivity of which is defined using the Lattice class, enabling the application of all implemented processing methods to data organized on any lattice. An introduction to undirected graphs can be found in, for example, [Trudeau, 1994] (http://www.amazon.com/Introduction-Graph-Theory-Dover-Mathematics/dp/0486678709).
By introducing software for processing data organized on alternative lattices, we hope to facilitate and encourage further studies of the possible advantages of non-Cartesian lattices in a wide range of research areas.

### Features
As LatticeLibrary is originally developed to study the behavior of various image processing methods applied to data sampled on the BCC and FCC lattices, most of the featured functionality is focused in this area. However, we hope that LatticeLibrary may serve as a foundation for other applications as well. Currently, LatticeLibrary features the following functionality:
 * Basic image arithmetic, for example addition and subtraction of images.
 * Spatial template filtering, that can be used for weighted average filters (for example, mean, Gaussian and Laplacian filters), as well as sequence based filters (for example, maximum, minimum, and median filters).
 * Seeded intensity-weighted distance transforms:
     * Minimum barrier distance [Ciesielski et al., 2014](http://www.sciencedirect.com/science/article/pii/S107731421400068X).
     * Approximate vectorial minimum barrier distance [Strand et al., 2013](http://www.sciencedirect.com/science/article/pii/S1077314212001750), [Kårsnäs et al., 2012](http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=6460253&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D6460253).
     * Fuzzy connectedness [Udupa and Samarasekara, 1996](http://www.sciencedirect.com/science/article/pii/S1077316996900210), [Udupa and Saha, 2003](http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=1232198&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D1232198).
     * Fuzzy distance transform [Saha et al., 2002](http://www.sciencedirect.com/science/article/pii/S1077314202909744), [Svensson, 2008](http://www.sciencedirect.com/science/article/pii/S0167865508000226).
     * Geodesic distance transform[Toivanen, 1996](http://www.sciencedirect.com/science/article/pii/0167865596000104), [Ikonen, 2005](http://link.springer.com/chapter/10.1007/978-3-540-31965-8_22#page-1), [Criminisi et al., 2008](http://link.springer.com/chapter/10.1007/978-3-540-88682-2_9).
 * Crisp segmentation of the output from seeded intensity-weighted distance transforms.
 * Fuzzy segmentation [Malmberg et al., 2011](http://www.sciencedirect.com/science/article/pii/S0304397510006687) of the output from seeded intensity-weighted distance transforms.
 * Anti-aliased Euclidean distance transform [Gustavson and Strand, 2011](http://www.sciencedirect.com/science/article/pii/S0167865510002953), [Linnér and Strand, 2014a](http://ieeexplore.ieee.org/xpl/articleDetails.jsp?arnumber=6976896), [Linnér and Strand, 2014b](http://link.springer.com/chapter/10.1007%2F978-3-319-09955-2_8#page-1). Applicable to, for example, fuzzy segmented images.
 * Binary erosion and dilation.

### Licence
LatticeLibrary is available under the [GNU Lesser General Public License v2.1] (http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html).

## Building
### Requirements
 * CMake 2.8.4 or later.
 * GCC or Clang with C++11 support.

### Build instructions
Create and enter build directory.
```bash
mkdir build
cd build
```
Download GoogleTest.
```bash
git submodule update --init --recursive
```
Call CMake and make
```bash
cmake ..
make release
```

### Running tests
Run tests.
```bash
make testing
cd ..
build/src/testing
```
