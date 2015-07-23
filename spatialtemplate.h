#ifndef LATTICELIBRARY_SPATIALTEMPLATE_H
#define LATTICELIBRARY_SPATIALTEMPLATE_H

#include "filtercoefficient.h"
#include <vector>
using std::vector; // TODO: Why do I need this here?!

namespace LatticeLib {
    /**
     * Base class for spatial templates
     * =================================
     * Classes derived from this class may be used as, for example, template filters or structuring elements in image processing.
     *
     * Member 			| Comment
     * --------			| --------
     * neighborhoodSize	| Element neighborhood size to be used for this filter.
     * coefficients		| Template coefficients.
     */
    template<class coefficientTemplate>
    class SpatialTemplate {

    protected:
        /** Template coefficients. */
        vector <FilterCoefficient<coefficientTemplate> > coefficients;

        /** Element neighborhood size to be used for this filter. */
        int neighborhoodSize;

    public:

        /**
         * Constructor for WeightedAverageFilter objects. The FilterCoefficient vector is left empty.
         *
         * Parameter	| in/out	| comment
         * :---------	| :------	| :-------
         * nS			| INPUT		| Neighborhood size.
         */
        SpatialTemplate(int nS) {
            neighborhoodSize = nS;
        }

        /**
         * Constructor for WeightedAverageFilter objects.
         *
         * Parameter	| in/out	| comment
         * :---------	| :------	| :-------
         * c			| INPUT		| Vector containing the template coefficients.
         * nS			| INPUT		| Neighborhood size.
         */
        SpatialTemplate(vector<FilterCoefficient<coefficientTemplate> > c, int nS) {
            coefficients = c;
            neighborhoodSize = nS;
        }

        /**
         * Destructor for WeightedAverageFilter objects.
         */
        virtual ~SpatialTemplate() { };

        /**
          * Returns neighborhoodSize.
          */
        int getNeighborhoodSize() const {
            return neighborhoodSize;
        }

        /**
          * Returns the number of template coefficients.
         */
        int getNCoefficients() const {
            return coefficients.size();
        }

        /**
         * Returns the template coefficient vector.
         */
        vector <FilterCoefficient<coefficientTemplate> > getCoefficients() const {
            return coefficients;
        }

        /**
         * Returns the requested FilterCoefficient object from the coefficient vector.
         *
         *
         * Parameter		| in/out	| comment
         * :---------		| :------	| :-------
         * coefficientIndex	| INPUT		| Position in the template coefficient vector.
         */
        FilterCoefficient<coefficientTemplate> getCoefficient(int coefficientIndex) const {
            return coefficients[coefficientIndex];
        }

        /**
         * Finds the position of the FilterCoefficient object, corresponding to the neighbor with the input position
         * index, in the template coefficient vector. Returns -1 if this neighbor does not have a coefficient.
         *
         * Parameter		| in/out	| comment
         * :---------		| :------	| :-------
         * positionIndex	| INPUT		| Position index of corresponding neighbor.
         */
        int findCoefficient(int positionIndex) const {
            int result = -1;
            int nCoefficients = getNCoefficients();
            for (int coefficientIndex = 0; coefficientIndex < nCoefficients; coefficientIndex++) {
                if (coefficients[coefficientIndex].getPositionIndex() == positionIndex) {
                    result = coefficientIndex;
                }
            }
            return result;
        }

    };
}

#endif //LATTICELIBRARY_SPATIALTEMPLATE_H
