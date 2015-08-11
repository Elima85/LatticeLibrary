#ifndef LATTICELIBRARY_OBJECTVOLUMEFROMCOVERAGE_H
#define LATTICELIBRARY_OBJECTVOLUMEFROMCOVERAGE_H

#include "intensityworkset.h"
#include "objectvolume.h"

namespace LatticeLib {
    /**
     * Class for computing the volume of a segmented object, stored as a modality band in an IntensityWorkset object.
     */
    template<class intensityTemplate>
    class ObjectVolumeFromCoverage: public ObjectVolume<intensityTemplate> {

    public:
        /**
         * Implements ObjectVolume::compute().
         *
         * Approximates the volume of a segmented object, stored as a modality band in an IntensityWorkset object.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * inputImage   | INPUT     | %Image containing the specified element.
         * labelIndex   | INPUT     | Label (band) index for the specified element.
         */
        double compute(IntensityWorkset<intensityTemplate> inputImage, int labelIndex) const {
            int nElements = inputImage.getImage().getNElements();
            int start = labelIndex * nElements;
            int stop = start + nElements;
            intensityTemplate *data = inputImage.getImage().getData();
            double minValue = inputImage.getMinIntensity();
            double maxValue = inputImage.getMaxIntensity();
            double range = maxValue - minValue;
            double approximatedVolume = 0;
            for (int dataIndex = start; dataIndex < stop; dataIndex++) {
                intensityTemplate intensity = MIN(maxValue, MAX(minValue, data[dataIndex]));
                double coverage = (double(intensity) - minValue) / range;
                approximatedVolume += coverage;
            }
            approximatedVolume /= inputImage.getImage().getLattice().getDensity();
            return approximatedVolume;
        }

    };
}

#endif //LATTICELIBRARY_OBJECTVOLUMEFROMCOVERAGE_H
