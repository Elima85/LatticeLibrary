#ifndef LATTICELIBRARY_INTENSITYWORKSET_H
#define LATTICELIBRARY_INTENSITYWORKSET_H

#include "image.h"
#include "lattice.h"
#include "dataredistribution.h"
#include <algorithm>
#include "exception.h"
#include <stdio.h>
#include <cmath>
#include "linearinterpolation.h"

namespace LatticeLib {

/**
 * A class for spatial domain images and fuzzy segmented images, for which it is necessary to know the possible intensity range.
 *
 * Member 		| Comment
 * :-------		| :-------
 * image		| Spatial domain image or fuzzy segmentation.
 * minIntensity | The lowest possible intensity value.
 * maxIntensity	| The highest possible intensity value.
 */
    template <class intensityTemplate>
    class IntensityWorkset {

    private:
        /** %Image dimensions and data. */
        Image<intensityTemplate> &image;

        /** Minimum intensity value. */
        intensityTemplate minIntensity;

        /** Maximum intensity value. */
        intensityTemplate maxIntensity;

    public:
        /**
         * Constructor for IntensityWorkset objects. Does not adjust the image data to the specified intensity range.
         *
         * Parameter    | in/out    |Comment
         * :---------   | :------   |:-------
         * image        | INPUT     | %Image dimensions and data.
         * minVal       | INPUT     | Minimum intensity value.
         * maxVal       | INPUT     | Maximum intensity value.
         */
        IntensityWorkset(Image<intensityTemplate> &im, intensityTemplate minVal, intensityTemplate maxVal) : image(im){
            minIntensity = minVal;
            maxIntensity = maxVal;
        }

        /**
         * Constructor for IntensityWorkset objects. Adjusts the image data to the specified intensity range, using the provided IntensityRedistribution object..
         *
         * Parameter    | in/out    |Comment
         * :---------   | :------   |:-------
         * image        | INPUT     | %Image dimensions and data.
         * minVal       | INPUT     | Minimum intensity value.
         * maxVal       | INPUT     | Maximum intensity value.
         */
        IntensityWorkset(Image<intensityTemplate> &im, intensityTemplate minVal, intensityTemplate maxVal,
                         const DataRedistribution<intensityTemplate> &newDistribution) : image(im) {
            int nTotal = image.getNBands() * image.getNElements();
            intensityTemplate *data = image.getData();
            intensityTemplate oldMinVal = INF;
            intensityTemplate oldMaxVal = -INF;
            for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
                oldMinVal = MIN(oldMinVal, data[dataIndex]);
                oldMaxVal = MAX(oldMaxVal, data[dataIndex]);
            }
            newDistribution.apply(data, nTotal, oldMinVal, oldMaxVal, minVal, maxVal);
            minIntensity = minVal;
            maxIntensity = maxVal;
        }

        /**
         * Copy constructor for IntensityWorkset objects.
         *
         * Parameter    | in/out    |Comment
         * :---------   | :------   |:-------
         * original     | INPUT     | IntensityWorkset object to be copied.
         */
        IntensityWorkset(const IntensityWorkset<intensityTemplate> &original) : image(original.getImage()){
            minIntensity = original.minIntensity;
            maxIntensity = original.maxIntensity;
        }

        ~IntensityWorkset() {}; // TODO: delete data array?

        /** Returns image. */
        Image<intensityTemplate>& getImage() const {
            return image;
        }

        /** Returns minIntensity. */
        intensityTemplate getMinIntensity() const {
            return minIntensity;
        }

        /** Returns maxIntensity. */
        intensityTemplate getMaxIntensity() const {
            return maxIntensity;
        }

        /** Returns the length of the intensity range. */
        intensityTemplate getRange() const {
            return maxIntensity - minIntensity;
        }

        /**
         * Adapts the intensity range of the specified band to that specified in the IntensityWorkset object using the input DataDistribution object.
         *
         * Parameter	    | in/out    | Comment
         * :-------		    | :------   | :-------
         * bandIndex        | INPUT     | Index of the band to be processed.
         * newDistribution  | INPUT     | Defines the new distribution of the intensity values.
         */
        void fitBandIntensities(int bandIndex, const DataRedistribution<intensityTemplate> &newDistribution) {
            int nElements = image.getNElements();
            intensityTemplate *data = image.getData() + bandIndex * nElements;
            intensityTemplate actualMin = INF;
            intensityTemplate actualMax = -INF;
            for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
                actualMin = MIN(actualMin, data[dataIndex]);
                actualMax = MAX(actualMax, data[dataIndex]);
            }
            newDistribution.apply(data, nElements, actualMin, actualMax, minIntensity, maxIntensity);
        }

        /**
         * Adapts the intensity range of the Image object to that specified in the IntensityWorkset object using the input DataDistribution object.
         *
         * Parameter	    | in/out    | Comment
         * :-------		    | :------   | :-------
         * newDistribution  | INPUT     | Defines the new distribution of the intensity values.
         */
        void fitImageIntensities(const DataRedistribution<intensityTemplate> &newDistribution) {
            int nTotal = image.getNBands() * image.getNElements();
            intensityTemplate *data = image.getData();
            intensityTemplate actualMin = INF;
            intensityTemplate actualMax = -INF;
            for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
                actualMin = MIN(actualMin, data[dataIndex]);
                actualMax = MAX(actualMax, data[dataIndex]);
            }
            newDistribution.apply(data, nTotal, actualMin, actualMax, minIntensity, maxIntensity);
        }

        /**
         * Redistributes the intensities of the specified band using the input DataDistribution object.
         *
         * Parameter	    | in/out    | Comment
         * :-------		    | :------   | :-------
         * bandIndex        | INPUT     | Index of the band to be processed.
         * newDistribution  | INPUT     | Defines the new distribution of the intensity values.
         * newMinVal	    | INPUT     | New minimum intensity
         * newMaxVal	    | INPUT     | New maximum intensity
         */
        void redistributeBandIntensities(int bandIndex, const DataRedistribution<intensityTemplate> &newDistribution,
                                         intensityTemplate newMinIntensity, intensityTemplate newMaxIntensity) {
            int nElements = image.getNElements();
            intensityTemplate *data = image.getData() + bandIndex * nElements;
            newDistribution.apply(data, nElements, minIntensity, maxIntensity, newMinIntensity, newMaxIntensity);
        }

        /**
         * Redistributes the intensities of the image using the input DataDistribution object.
         *
         * Parameter	    | in/out    | Comment
         * :-------		    | :------   | :-------
         * newDistribution  | INPUT     | Defines the new distribution of the intensity values.
         * newMinVal	    | INPUT     | New minimum intensity
         * newMaxVal	    | INPUT     | New maximum intensity
         */
        void redistributeImageIntensities(const DataRedistribution<intensityTemplate> &newDistribution,
                                         intensityTemplate newMinIntensity, intensityTemplate newMaxIntensity) {
            int nBands = image.getNBands();
            for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                redistributeBandIntensities(bandIndex, newDistribution, newMinIntensity, newMaxIntensity);
            }
        }

        /**
         * Sets the minimum intensity to the specified value, and optionally traverses and adjusts the data to the new
         * intensity range.
         *
         * Parameter	| in/out    | Comment
         * :-------		| :------   | :-------
         * newMinVal	| INPUT     | New minimum intensity
         */
        void setMinIntensity(intensityTemplate newMinIntensity) {
            minIntensity = newMinIntensity;
        }

        /**
         * Sets the minimum intensity to the specified value, and optionally traverses and adjusts the data to the new
         * intensity range.
         *
         * Parameter	| in/out    | Comment
         * :-------		| :------   | :-------
         * newMinVal	| INPUT     | New minimum intensity
         */
        void setMinIntensity(intensityTemplate newMinIntensity,
                             const DataRedistribution<intensityTemplate> &newDistribution) {
            redistributeImageIntensities(newDistribution, newMinIntensity, maxIntensity);
            setMinIntensity(newMinIntensity);
        }

        /**
         * Sets the maximum intensity to the specified value, and optionally traverses and adjusts the data to the new
         * intensity range.
         *
         * Parameter	| in/out    | Comment
         * :-------		| :------   | :-------
         * newMaxVal	| INPUT     | New maximum intensity
         */
        void setMaxIntensity(intensityTemplate newMaxIntensity) {
            maxIntensity = newMaxIntensity;
        }

        /**
         * Sets the maximum intensity to the specified value, and optionally traverses and adjusts the data to the new
         * intensity range.
         *
         * Parameter	| in/out    | Comment
         * :-------		| :------   | :-------
         * newMaxVal	| INPUT     | New maximum intensity
         */
        void setMaxIntensity(intensityTemplate newMaxIntensity,
                             const DataRedistribution<intensityTemplate> &newDistribution) {
            redistributeImageIntensities(newDistribution, minIntensity, newMaxIntensity);
            setMaxIntensity(newMaxIntensity);
        }
    };
}

#endif //LATTICELIBRARY_INTENSITYWORKSET_H
