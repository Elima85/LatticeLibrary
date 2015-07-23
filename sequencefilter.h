#ifndef LATTICELIBRARY_SEQUENCEFILTER_H
#define LATTICELIBRARY_SEQUENCEFILTER_H

#include "templatefilter.h"
#include "spatialtemplate.h"

namespace LatticeLib {

    /**
     * Class for sequence filters
     * ===========================
     * Objects of this class act as spatial filters based on sorting the spatial elements according to intensity value.
     *
     * Member 	| Comment
     * --------	| --------
     * sequence | Defines which intensity value to pick, after sorting the spatial elements according to intensity. <br> sequenceOption::min: Lowest intensity. <br> sequenceOption::max: Highest intensity. <br> sequenceOption::median: Median intensity.
     */
    enum sequenceOption {min, max, median};

    template<class intensityTemplate>
    class SequenceFilter : public TemplateFilter<bool, intensityTemplate> {

    private:
        /** Defines the filter functionality*/
        sequenceOption sequence; // TODO: Or should this be an ElementPicker object or something? A class for choosing an element from a vector?

    public:
        /**
         * Constructor for SequenceFilter objects.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * sequence     | INPUT     | Defines which intensity value to pick, after sorting the spatial elements according to intensity. <br> sequenceOption::min: Lowest intensity. <br> sequenceOption::max: Highest intensity. <br> sequenceOption::median: Median intensity.
         */
        SequenceFilter(sequenceOption s, int nS) : TemplateFilter<bool, intensityTemplate> (nS) {
            sequence = s;
        }
        ~SequenceFilter() {}

        /**
         * Returns the sequence option of the filter.
         */
        sequenceOption getSequenceOption() const {
            return sequence;
        }

        /**
          * Gives access to SpatialTemplate::getNeighborhoodSize().
          */
        int getNeighborhoodSize() const {
            return SpatialTemplate<bool>::getNeighborhoodSize();
        }

        /**
          * Gives access to SpatialTemplate::getNCoefficients().
         */
        int getNCoefficients() const {
            return SpatialTemplate<bool>::getNCoefficients();
        }

        /**
          * Gives access to SpatialTemplate::getCoefficients().
         */
        vector <FilterCoefficient<bool>> getCoefficients() const {
            return SpatialTemplate<bool>::getCoefficients();
        }

        /**
          * Gives access to SpatialTemplate::getCoefficient().
         *
         *
         * Parameter		| in/out	| comment
         * :---------		| :------	| :-------
         * coefficientIndex	| INPUT		| Position in the template coefficient vector.
         */
        FilterCoefficient <bool> getCoefficient(int coefficientIndex) const {
            return SpatialTemplate<bool>::getCoefficient(coefficientIndex);
        }

        /**
          * Gives access to SpatialTemplate::findCoefficient().
         *
         * Parameter		| in/out	| comment
         * :---------		| :------	| :-------
         * positionIndex	| INPUT		| Position index of corresponding neighbor.
         */
        int findCoefficient(int positionIndex) const {
            return SpatialTemplate<bool>::findCoefficient(positionIndex);
        }

        /**
         * Implements TemplateFilter::applyToBand().
         *
         * Parameter	| in/out	| comment
         * :---------	| :------	| :-------
         * image		| INPUT		| Input image.
         * bandIndex	| INPUT		| Index of the band to be filtered.
         * result		| OUTPUT	| Filtered intensity values. Needs to be of a length of at least image.nElements.
         */
        void applyToBand(Image <intensityTemplate> image, int bandIndex, double *result) const { }

        /**
         * Implements TemplateFilter::applyToImage().
         *
         * Parameter	| in/out	| comment
         * :---------	| :------	| :-------
         * image		| INPUT		| Input image.
         * result		| OUTPUT	| Filtered intensity values. Needs to be of a length of at least image.nElements * image.nBands.
         */
        void applyToImage(Image <intensityTemplate> image, double *result) const { }
    };
}

#endif //LATTICELIBRARY_SEQUENCEFILTER_H
