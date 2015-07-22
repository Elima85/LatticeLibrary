#ifndef PRODUCTNORM_H
#define PRODUCTNORM_H

#include "norm.h"
#include <vector>

using namespace std;

namespace LatticeLib {
/**
 * Class for computing the product of all vector elements. *This is not a norm accordning to the mathematical definition.*
 */
    template<class T>
    class ProductNorm : public Norm<T> {
    public:
        /**
         * Constructor for ProductNorm objects.
         */
        ProductNorm() : Norm<T>() { }

        /**
         * Copy constructor for ProductNorm objects.
         *
         * Parameter	| in/out	| Comment
         * :---------- 	| :-------	| :--------
         * n			| INPUT		| ProductNorm object to be copied.
         */
        ProductNorm(const ProductNorm &n) : Norm<T>(n) { }

        /**
         * Destructor for ProductNorm objects.
         */
        ~ProductNorm() { };

        /**
         * Overloads Norm::compute().
         *
         * Computes the product of all vector elements.
         */
        double compute(vector<T> v) const {
            double product = 1.0;
            int N = v.size();
            for (int i = 0; i < N; i++) {
                product = product * fabs(v[i]);
            }
            return product;
        }
    };
}

#endif //PRODUCTNORM_H
