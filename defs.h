#ifndef LATTICELIBRARY_DEFS_H
#define LATTICELIBRARY_DEFS_H

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
