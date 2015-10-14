#ifndef LATTICELIBRARY_DISTANCETOVORONOICELLCENTER_H
#define LATTICELIBRARY_DISTANCETOVORONOICELLCENTER_H

#include "intensityworkset.h"

namespace LatticeLib {
    /**
     * Class for approximation of the distance, in the range \f$[-0.5,0.5]\f$, between an element center and the intersecting surface of a fuzzy object, using the characteristics of the Lattice Voronoi cell.
     */
    template<class intensityTemplate>
    class LinearDistanceToCenter : public DistanceToElementCenter {

    public:
        /**
         * Implements DistanceToElementCenter::compute().
         *
         * Approximates the distance, in the range \f$[-0.5,0.5]\f$, between an element center and the intersecting surface of a fuzzy object, using the characteristics of the Lattice Voronoi cell.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * inputImage   | INPUT     | %Image containing the specified element.
         * elementIndex | INPUT     | Element for which to compute the distance.
         * labelIndex   | INPUT     | Label (band) index for the specified element.
         */
        double compute(IntensityWorkset<intensityTemplate> inputImage, int elementIndex, int labelIndex) const {
            double minValue = inputImage.getMinIntensity();
            double maxValue = inputImage.getMaxIntensity();
            double range = maxIntensity - minIntensity;
            intensityTemplate intensity = MIN(maxValue, MAX(minValue, inputImage.getImage()(elementIndex, labelIndex)));
            double coverage = (double(intensity) - minValue) / range;
            return inputImage.getImage().getLattice().approximateDistanceToElementCenter(coverage);
        }

    };
}

#endif //LATTICELIBRARY_DISTANCETOVORONOICELLCENTER_H
