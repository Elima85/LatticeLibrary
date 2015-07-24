#ifndef LATTICELIBRARY_SEQUENCEFILTER_H
#define LATTICELIBRARY_SEQUENCEFILTER_H

#include "templatefilter.h"
#include "spatialtemplate.h"
#include "vectorvaluefinder.h"
#include "neighbor.h"

namespace LatticeLib {

    /**
     * Class for sequence filters
     * ===========================
     * Objects of this class act as spatial filters, picking a specific intensity from the neighborhood of a spatial
     * element. The filter coefficients specify which elements of the neighborhood are included in the selection.
     *
     * Member 	        | Comment
     * --------	        | --------
     * neighborhoodSize	| Element neighborhood size to be used for this filter.
     * coefficients		| Template coefficients. True for the elements that are included in the selection. False or undefined for elements that are not included.
     * indexPicker      | Defines which intensity value to pick from the neighborhood of an element.
     */
    template<class intensityTemplate>
    class SequenceFilter : public TemplateFilter<bool, intensityTemplate> {

    private:
        /** Defines which intensity value to pick from the neighborhood of an element. */
        VectorValueFinder<intensityTemplate> &indexPicker;

    public:
        /**
         * Constructor for SequenceFilter objects.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * indexPicker  | INPUT     | Defines which intensity value to pick from the neighborhood of an element.
         */
        SequenceFilter(vector<FilterCoefficient<bool> > c, int nS, VectorValueFinder<intensityTemplate> &picker) : TemplateFilter<bool, intensityTemplate> (c, nS), indexPicker(picker){ }
        ~SequenceFilter() {}

        /**
         * Returns indexPicker.
         */
        VectorValueFinder<intensityTemplate>& getIndexPicker() const {
            return indexPicker;
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
        void applyToBand(Image <intensityTemplate> image, int bandIndex, double *result) const {
            if ((bandIndex < 0) || (bandIndex >= image.getNBands())) {
                // throw error or exception
            }

            int nElements = image.getNElements();
            vector<FilterCoefficient<bool> > coefficients = getCoefficients();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                // center element
                vector<intensityTemplate> intensities;
                int coefficientIndex = findCoefficient(-1);
                if (coefficientIndex > -1) {
                    if (getCoefficients()[coefficientIndex].getCoefficient()) {
                        intensities.push_back(image(elementIndex, bandIndex));
                    }
                }
                // neighbors
                vector<Neighbor> neighbors;
                image.getNeighbors(elementIndex, getNeighborhoodSize(), neighbors);
                for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                    coefficientIndex = findCoefficient(neighbors[neighborIndex].getPosition());
                    if (coefficientIndex > -1) {
                        if (getCoefficients()[coefficientIndex].getCoefficient()) {
                            intensities.push_back(image(neighbors[neighborIndex].getElementIndex(), bandIndex));
                        }
                    }
                }
                result[elementIndex] = intensities[indexPicker.getVectorElementIndex(intensities)];
            }

        }

        /**
         * Implements TemplateFilter::applyToImage().
         *
         * Parameter	| in/out	| comment
         * :---------	| :------	| :-------
         * image		| INPUT		| Input image.
         * result		| OUTPUT	| Filtered intensity values. Needs to be of a length of at least image.nElements * image.nBands.
         */
        void applyToImage(Image <intensityTemplate> image, double *result) const {
            int nElements = image.getNElements();
            int nBands = image.getNBands();
            for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                int offset = bandIndex * nElements;
                applyToBand(image, bandIndex, result + offset);
            }
        }
    };
}

#endif //LATTICELIBRARY_SEQUENCEFILTER_H
