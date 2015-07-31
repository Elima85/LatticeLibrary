#ifndef LATTICELIBRARY_COVERAGETODISTANCE_H
#define LATTICELIBRARY_COVERAGETODISTANCE_H

#include "intensityworkset.h"

namespace LatticeLib {
    /**
     * Class for converting the intensity value of an element in an IntensityWorkset to the distance, in the range \f$[-0.5,0.5]\f$, between the element center and the surface of a fuzzy segmented object that intersects the Voronoi cell of that element.
     */
    template <class intensityTemplate>
    class DistanceToElementCenter {

    public:
        /**
         * Approximates the distance, in the range \f$[-0.5,0.5]\f$, between the center of the specified element and the surface of a fuzzy segmented object that intersects the Voronoi cell of that element.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * inputImage   | INPUT     | %Image containing the specified element.
         * elementIndex | INPUT     | Element for which to compute the distance.
         * labelIndex   | INPUT     | Label (band) index for the specified element.
         */
        virtual double compute(IntensityWorkset<intensityTemplate> inputImage, int elementIndex, int labelIndex) const = 0;

    };
}

#endif //LATTICELIBRARY_COVERAGETODISTANCE_H
