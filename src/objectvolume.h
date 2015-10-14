#ifndef LATTICELIBRARY_OBJECTVOLUME_H
#define LATTICELIBRARY_OBJECTVOLUME_H

#include "intensityworkset.h"

namespace LatticeLib {
    /**
     * Class for computing the volume of a segmented object, stored as a modality band in an IntensityWorkset object.
     */
    template<class intensityTemplate>
    class ObjectVolume {

    public:
        /**
         * Approximates the volume of a segmented object, stored as a modality band in an IntensityWorkset object.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * inputImage   | INPUT     | %Image containing the specified element.
         * labelIndex   | INPUT     | Label (band) index for the specified element.
         */
        virtual double compute(IntensityWorkset<intensityTemplate> inputImage, int labelIndex) const = 0;

    };
}

#endif //LATTICELIBRARY_OBJECTVOLUME_H
