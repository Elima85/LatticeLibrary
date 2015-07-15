#ifndef NORM_H
#define NORM_H

#include <vector>
#include <cmath>
#include "defs.h"

using namespace std;

namespace LatticeLib {

	/**
	 * Base class for vector norms.
	 */
	class Norm {
	public:
		/**
         * Constructor for Norm objects.
         */
		Norm() {}

		/**
         * Copy constructor for Norm objects.
         *
         * Parameter	| in/out	| Comment
         * :---------- 	| :-------	| :--------
         * n			| INPUT		| Norm object to be copied.
         */
		Norm(const Norm &n) {}

		/**
		 * Destructor for Norm objects.
		 */
		~Norm() {};

		/**
		 * Computes a norm of the input vector. The implementation in the base class returns -1.0.
         *
         * Parameter	| in/out	| Comment
         * :---------- 	| :-------	| :--------
         * v			| INPUT		| Vector for which to compute a norm.
		 */
		template <class T>
		double compute(vector<T> v) const {
			return -1.0;
		}

	};
}

#endif
