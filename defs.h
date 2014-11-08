#ifndef CIMAGEDEFS_H
#define CIMAGEDEFS_H

namespace CImage {

typedef unsigned char uint8;

// general definitions
#define EPSILONT 0.0000001 // tolerance for testing
#define INF 10000000.0
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

// CC definitions
const int mirrorCC[] = {1, 0, 3, 2, 5, 4, 11, 10, 13, 12,  7,  6,  9,  8, 17, 16, 15, 14, 24, 25, 22, 23, 20, 21, 18, 19};
                      //0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25
const int nearestCC[] = {-1, -1, -1, -1, -1, -1};
					   // 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25

const int mirrorBCC[] = {7, 6, 5, 4, 3, 2, 1, 0, 13, 11, 12,  9, 10,  8};
					   //0, 1, 2, 3, 4, 5, 6, 7,  8,  9, 10, 11, 12, 13

const int mirrorFCC[] = {10, 11, 8, 9, 6, 7, 4, 5, 2, 3,  0,  1, 17, 15, 16, 13, 14, 12};
					   // 0,  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17

}
#endif
