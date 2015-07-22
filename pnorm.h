#ifndef PNORM_H
#define PNORM_H

#include "norm.h"
#include <vector>
#include <cmath>

namespace LatticeLib {

/**
 * Class for computing the p-norm of a vector, defined as \f$((\sum_i v[i]^p)^\frac{1}{p})\f$. City-block distance is obtained through p = 1, Euclidean distance for p = 2, etc.
 *
 * Member 	| Comment
 * :-------	| :-------
 * p		| Defines the order of the norm.
 */
    template<class T>
    class PNorm : public Norm<T> {
    private:
        /** Defines the order of the norm. */
        double p;

    public:
        /**
         * Constructor for PNorm objects.
         *
         * Parameter	| in/out	| Comment
         * :---------- 	| :-------	| :--------
         * p			| INPUT		| Defines the order of the norm.
         */
        PNorm(double pval) : Norm<T>() {
            p = pval;
        }

        /**
         * Copy constructor for PNorm objects.
         *
         * Parameter	| in/out	| Comment
         * :---------- 	| :-------	| :--------
         * n			| INPUT		| PNorm object to be copied.
         */
        PNorm(const PNorm &n) : Norm<T>(n) {
            p = n.getP();
        }

        /**
         * Destructor for PNorm objects.
         */
        ~PNorm() { }

        /**
         * Returns p.
         */
        double getP() const {
            return p;
        }

        /**
         * Overloads Norm::compute().
         *
         * Computes the p-norm of the input vector.
         *
         * Parameter	| in/out	| Comment
         * :---------- 	| :-------	| :--------
         * v			| INPUT		| Vector for which to compute the norm.
         */
        double compute(vector<T> v) const {
            double sum = 0.0;
            int N = v.size();
            for (int i = 0; i < N; i++) {
                sum = sum + pow(fabs(v[i]), p);
            }
            return pow(sum, 1 / p);
        }
    };
}

#endif //PNORM_H
