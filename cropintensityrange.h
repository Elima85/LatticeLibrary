#ifndef LATTICELIBRARY_CROPINTENSITYRANGE_H
#define LATTICELIBRARY_CROPINTENSITYRANGE_H

#include "dataredistribution.h"
#include "exception.h"

namespace LatticeLib {
    /**
     * Class for cropping the intensity range of IntensityWorkset Image objects.
     */
    template <class intensityTemplate>
    class CropIntensityRange : public DataRedistribution<intensityTemplate> {
    public:
        /**
         * Constructor for CropIntensityRange objects.
         */
        CropIntensityRange() : DataRedistribution<intensityTemplate>(){ }

        /**
         * Destructor for CropIntensityRange objects.
         */
        ~CropIntensityRange() { }

        /**
         * Implements DataReistribution::applyToBand().
         *
         * Truncates the range of the input data to [newMinValue,newMaxValue].
         *
         * Parameter        | in/out        | Comment
         * :---------       | :------       | :-------
         * data             | INPUT/OUTPUT  | The data distribution that is to be changed.
         * oldMinimumValue  | INPUT         | Minimum intensity for the old distribution.
         * oldMaximumValue  | INPUT         | Maximum intensity for the old distribution.
         * newMinimumValue  | INPUT         | Minimum intensity for the new distribution.
         * newMaximumValue  | INPUT         | Maximum intensity for the new distribution.
         */
        void apply(intensityTemplate *data, int nElements, intensityTemplate oldMinimumValue,
                           intensityTemplate oldMaximumValue, intensityTemplate newMinimumValue,
                           intensityTemplate newMaximumValue) const {
            if (newMinimumValue > newMaximumValue) {
                throw incompatibleParametersException();
            }
            if ((newMinimumValue > oldMinimumValue) || (newMaximumValue < oldMaximumValue)) {
                for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                    data[elementIndex] = MIN(newMaximumValue, MAX(newMinimumValue, data[elementIndex]));
                }
            }
        }
    };
}

#endif //LATTICELIBRARY_CROPINTENSITYRANGE_H
