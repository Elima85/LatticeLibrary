#ifndef FILEHANDLING_H
#define FILEHANDLING_H

namespace CImage {

/*
 * Allocates and returns an array with the values read from the input file.
 *
 * Must be paired with delete[]!
 */
    double *readVolume(const char *path, int nTot);

/*
 * Writes the input array to the input file.
 */
// to be tested
    void writeVolume(const char *path, const double *values, const int nTot);
}

#endif