#ifndef LATTICELIBRARY_RENORMALIZEINTENSITYRANGE_H
#define LATTICELIBRARY_RENORMALIZEINTENSITYRANGE_H

#include "dataredistribution.h"
#include "exception.h"

namespace LatticeLib {
    /**
     * Class for cropping the intensity range of IntensityWorkset Image objects.
     */
    template<class intensityTemplate>
    class RenormalizeIntensityRange : public DataRedistribution<intensityTemplate> {
    public:
        /**
         * Constructor for CropIntensityRange objects.
         */
        RenormalizeIntensityRange() : DataRedistribution<intensityTemplate>() { }

        /**
         * Destructor for CropIntensityRange objects.
         */
        ~RenormalizeIntensityRange() { }

        /**
         * Implements DataRedistribution::apply().
         *
         * Normalizes the range of the input data to [newMinValue,newMaxValue]. _Does not work well for integer values, due to round-off errors._
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
            double oldRange = oldMaximumValue - oldMinimumValue;
            double newRange = newMaximumValue - newMinimumValue;
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                data[elementIndex] = intensityTemplate((double(data[elementIndex] - oldMinimumValue)/oldRange) * newRange + newMinimumValue);
            }
        }

    };
}
#endif //LATTICELIBRARY_RENORMALIZEINTENSITYRANGE_H
