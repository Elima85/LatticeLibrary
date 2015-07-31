#ifndef LATTICELIBRARY_LINEARDISTANCETOCENTER_H
#define LATTICELIBRARY_LINEARDISTANCETOCENTER_H

#include "intensityworkset.h"

namespace LatticeLib {
    /**
     * Class for linear approximation of the distance, in the range \f$[-0.5,0.5]\f$, between an element center and the intersecting surface of a fuzzy object.
     */
    template<class intensityTemplate>
    class LinearDistanceToCenter : public DistanceToElementCenter {

    public:
        /**
         * Implements DistanceToElementCenter::compute().
         *
         * Approximates the distance, in the range \f$[-0.5,0.5]\f$, between an element center and the intersecting surface of a fuzzy object by \f$distance = 0.5 - coverage\f$.
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
            double scaleFactor = cbrt(1 / inputImage.getImage().getDensity());
            return (0.5 - coverage) * scaleFactor;
        }

    };
}

#endif //LATTICELIBRARY_LINEARDISTANCETOCENTER_H
