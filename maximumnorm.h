#ifndef MAXIMUMNORM_H
#define MAXIMUMNORM_H

#include "norm.h"
#include <vector>
#include "defs.h"

namespace LatticeLib {
/**
 * Class for computing the maximum norm of a vector.
 */
    template<class T>
    class MaximumNorm : public Norm<T> {
    public:
        /**
         * Constructor for MaximumNorm objects.
         */
        MaximumNorm() : Norm<T>() { }

        /**
         * Copy constructor for MaximumNorm objects.
         *
         * Parameter	| in/out	| Comment
         * :---------- 	| :-------	| :--------
         * n			| INPUT		| MaximumNorm object to be copied.
         */
        MaximumNorm(const MaximumNorm &n) : Norm<T>(n) { }

        /**
         * Destructor for MaximumNorm objects.
         */
        ~MaximumNorm() { };

        /**
         * Overloads Norm::compute().
         *
         * Computes the maximum norm of the input vector.
         */
        double compute(vector <T> v) const {
            double maximum = -1.0;
            int N = v.size();
            for (int i = 0; i < N; i++) {
                if (fabs(v[i]) > maximum) {
                    maximum = v[i];
                }
            }
            return maximum;
        }
    };

}

#endif //MAXIMUMNORM_H
