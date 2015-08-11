#ifndef LATTICELIBRARY_OBJECTSURFACEAREA_H
#define LATTICELIBRARY_OBJECTSURFACEAREA_H

#include "intensityworkset.h"

namespace LatticeLib {
    /**
     * Abstract base class for computing the surface area of a segmented object, stored as a modality band in an IntensityWorkset object.
     */
    template<class intensityTemplate>
    class ObjectSurfaceArea {

    public:
        /**
         * Approximates the surface area of a segmented object, stored as a modality band in an IntensityWorkset object.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :------   | :-------
         * inputImage           | INPUT     | %Image containing the specified element.
         * labelIndex           | INPUT     | Label (band) index for the specified element.
         */
        virtual double compute(IntensityWorkset<intensityTemplate> inputImage, int labelIndex) const = 0;

    };
}

#endif //LATTICELIBRARY_OBJECTSURFACEAREA_H
