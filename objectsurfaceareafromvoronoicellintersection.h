#ifndef LATTICELIBRARY_AREAOFVORONOICELLINTERSECTION_H
#define LATTICELIBRARY_AREAOFVORONOICELLINTERSECTION_H

#include "intensityworkset.h"
#include "objectsurfacearea.h"
#include "exception.h"
#include <stdio.h> // DEBUG
#include "defs.h" // DEBUG
#include <cmath> // DEBUG
#include <fstream> // DEBUG

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
            cout << "inputImage: min = " << int(inputImage.getMinIntensity()) << ", max = " << int(inputImage.getMaxIntensity()) << ", data = " << long(inputImage.getImage().getData()) << ", density = " << inputImage.getImage().getLattice().getDensity() << endl; // DEBUG
            int nElements = inputImage.getImage().getNElements();
            int start = labelIndex * nElements;
            int stop = start + nElements;
            intensityTemplate *data = inputImage.getImage().getData();
            double minValue = inputImage.getMinIntensity();
            double maxValue = inputImage.getMaxIntensity();
            double range = maxValue - minValue;
            //if (fabs(range) < EPSILONT) { // DEBUG
            //    std::cout << "Range is too small." << std::endl; // DEBUG
            //} // DEBUG
            double approximatedArea = 0.0;
            std::cout << "Traversing image data..." << std::endl; // DEBUG
            for (int dataIndex = start; dataIndex < stop; dataIndex++) {
                double intensity = MIN(maxValue, MAX(minValue, data[dataIndex]));
                double coverage = (intensity - minValue) / range;
                //if (coverage < 0 || coverage > 1) { // DEBUG
                //    std::cout << "coverage out of bounds for dataIndex = " << dataIndex << std::endl; // DEBUG
                //} // DEBUG
                if (coverage > 0 && coverage < 1) {
                    approximatedArea = approximatedArea + inputImage.getImage().getLattice().approximateIntersectionArea(coverage);
                    //std::cout << "index: " << dataIndex << ", intensity: " << intensity << ", coverage: " << coverage << ", area: " << inputImage.getImage().getLattice().approximateIntersectionArea(coverage) << std::endl;
                }
            }
            //std::cout << "\t computed area: " << approximatedArea << std::endl;
            return approximatedArea;
        }
    };
}

#endif //LATTICELIBRARY_AREAOFVORONOICELLINTERSECTION_H
