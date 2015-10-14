#ifndef LATTICELIBRARY_DATAREDISTRIBUTION_H
#define LATTICELIBRARY_DATAREDISTRIBUTION_H

namespace LatticeLib {
    /**
     * Class for changing the intensity distribution in IntensityWorkset Image objects.
     */
    template <class intensityTemplate>
    class DataRedistribution {
    public:
        /**
         * Constructor for IntensityRedistribution objects.
         */
        DataRedistribution() {}

        /**
         * Destructor for IntensityRedistribution objects.
         */
        virtual ~DataRedistribution() {}

        /**
         * Changes the intensity distribution in the specified band.
         *
         * Parameter        | in/out        | Comment
         * :---------       | :------       | :-------
         * data             | INPUT/OUTPUT  | The data distribution that is to be changed.
         * oldMinimumValue  | INPUT         | Minimum intensity for the old distribution.
         * oldMaximumValue  | INPUT         | Maximum intensity for the old distribution.
         * newMinimumValue  | INPUT         | Minimum intensity for the new distribution.
         * newMaximumValue  | INPUT         | Maximum intensity for the new distribution.
         */
        virtual void apply(intensityTemplate *data, int nElements, intensityTemplate oldMinimumValue,
                           intensityTemplate oldMaximumValue, intensityTemplate newMinimumValue,
                           intensityTemplate newMaximumValue) const = 0;
   };
}

#endif //LATTICELIBRARY_DATAREDISTRIBUTION_H
