#ifndef PRODUCTNORM_H
#define PRODUCTNORM_H

#include "norm.h"
#include <vector>

using namespace std;

namespace LatticeLib {
/**
 * Class for computing the product of all vector elements. *This is not a norm accordning to the mathematical definition.*
 */
    class ProductNorm : public Norm {
    public:
        /**
         * Constructor for ProductNorm objects.
         */
        ProductNorm() : Norm() { }

        /**
         * Copy constructor for ProductNorm objects.
         *
         * Parameter	| in/out	| Comment
         * :---------- 	| :-------	| :--------
         * n			| INPUT		| ProductNorm object to be copied.
         */
        ProductNorm(const ProductNorm &n) : Norm(n) { }

        /**
         * Destructor for ProductNorm objects.
         */
        ~ProductNorm() { };

        /**
         * Overloads Norm::compute().
         *
         * Computes the product of all vector elements.
         */
        template<class T>
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
