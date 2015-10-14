#ifndef LATTICELIBRARY_NORM_H
#define LATTICELIBRARY_NORM_H

#include <vector>
#include <cmath>
#include "defs.h"

using namespace std;

namespace LatticeLib {

	/**
	 * Base class for vector norms.
	 */
	template<class T>
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
		virtual ~Norm() {};

		/**
		 * Computes a norm of the input vector. The implementation in the base class returns -1.0.
         *
         * Parameter	| in/out	| Comment
         * :---------- 	| :-------	| :--------
         * vector		| INPUT		| Vector for which to compute a norm.
		 */
		virtual double compute(vector<T> vector) const = 0;
	};
}

#endif
