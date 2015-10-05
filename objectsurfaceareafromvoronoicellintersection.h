#ifndef LATTICELIBRARY_AREAOFVORONOICELLINTERSECTION_H
#define LATTICELIBRARY_AREAOFVORONOICELLINTERSECTION_H

#include "intensityworkset.h"
#include "objectsurfacearea.h"
#include "exception.h"

namespace LatticeLib {

    /**
     * Class for computing the surface area of a segmented object, stored as a modality band in an IntensityWorkset object. The intersecting surface is assumed to be locally planar. The coverage values of the elements are mapped to the average area of a planar surface dividing the element accordingly.
     */
    template<class intensityTemplate>
    class ObjectSurfaceAreaFromVoronoiCellIntersection : public ObjectSurfaceArea<intensityTemplate> {
    public:
        /**
         * Implements ObjectSurfaceArea::compute().
         *
         * The intersecting surface is assumed to be locally planar. The coverage values of the elements are mapped to the average area of a planar surface dividing the element accordingly.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :------   | :-------
         * inputImage           | INPUT     | %Image containing the specified element.
         * labelIndex           | INPUT     | Label (band) index for the specified element.
         */
        double compute(IntensityWorkset<intensityTemplate> &inputImage, int labelIndex) const {
            int nElements = inputImage.getImage().getNElements();
            int start = labelIndex * nElements;
            int stop = start + nElements;
            intensityTemplate *data = inputImage.getImage().getData();
            double minValue = inputImage.getMinIntensity();
            double maxValue = inputImage.getMaxIntensity();
            double range = inputImage.getRange();
            double approximatedArea = 0.0;
            for (int dataIndex = start; dataIndex < stop; dataIndex++) {
                double intensity = data[dataIndex];
                double coverage = (intensity - minValue) / range;
                if (coverage > 0 && coverage < 1) {
                    approximatedArea = approximatedArea + inputImage.getImage().getLattice().approximateIntersectionArea(coverage);
                }
            }
            return approximatedArea;
        }
    };
}

#endif //LATTICELIBRARY_AREAOFVORONOICELLINTERSECTION_H
