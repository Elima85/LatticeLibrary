#include <cstdio>
#include "exception.h"
#include "filehandling.h"
#include "defs.h"

namespace CImage {

    double *readVolume(const char *path, int nTot) {

        FILE *f = fopen(path, "r");
        if (f == NULL) {
            throw fileException();
        }
        double *vol = new double[nTot];
        if (!vol) {
            throw allocationException();
        }

        int r, rTot = 0;
        while (!feof(f) && (r = fread(vol + rTot, sizeof(double), MIN(2048, nTot - rTot), f)) > 0)
            rTot += r;
        fclose(f);
        return vol;
    }

    void writeVolume(const char *path, const double *values, const int nTot) {
        FILE *f = fopen(path, "wb");
        if (f == NULL) {
            throw fileException();
        }
        fwrite(values, sizeof(double), nTot, f);
        fclose(f);
    }
}