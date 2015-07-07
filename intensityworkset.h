#ifndef INTENSITYWORKSET_H
#define INTENSITYWORKSET_H

#include "image.h"
#include "lattice.h"

namespace LatticeLib {

    enum imageIntensityAdjustmentOption {none, crop, normalize}; // for the entire image at once
    enum elementIntensityAdjustmentOption {none, crop}; // for a single element. Normalization is not possible.

/**
 * A class for spatial domain images and fuzzy segmented images, for which it is necessary to know the possible intensity range.
 *
 * Member 		| Comment
 * :-------		| :-------
 * image		| Spatial domain image or fuzzy segmentation.
 * minIntensity | The lowest possible intensity value.
 * maxIntensity	| The highest possible intensity value.
 *
 */
    template<class T>
    class IntensityWorkset {

    private:
        Image<T> &image;
        T minIntensity;
        T maxIntensity;

    public:
        /**
         * Intensity workset constructor.
         *
         * Parameter    | Comment
         * :---------   | :-------
         * d            | Image data, must be of length l->nElements or more.
         * l            | Image sampling lattice, will not be deleted by the Image destructor.
         * nB           | \#modality bands, >=1
         * minVal       | Minimum intensity value.
         * maxVal       | Maximum intensity value.
         */
        IntensityWorkset(T *d, Lattice &l, int nB, T minVal, T maxVal) {
            minIntensity = minVal;
            maxIntensity = maxVal;
            image = Image<T>(d, l, nB);
        }

        IntensityWorkset(const IntensityWorkset<T> &original) {
            minIntensity = original.minIntensity;
            maxIntensity = original.maxIntensity;
            image = Image<T>(original.image);
        }

        ~IntensityWorkset() {}; // TODO: delete data array?

        /** Returns minIntensity. */
        T getMinIntensity() {
            return minIntensity;
        }

        /** Returns maxIntensity. */
        T getMaxIntensity() {
            return maxIntensity;
        }

        /**
         * Crops the intensity values, so that all values fit in the specified intensity range.
         */
        void cropIntensities() {
            int nElements = image.getNElements();
            int nBands = image.getNBands();
            for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                    image.setElement(elementIndex, bandIndex, MIN(maxIntensity, MAX(minIntensity, d[intensityIndex])));
                }
            }
        }

        /**
         * Normalizes the image, so that it's maximum intensity is maxIntensity, and it's lowest intensity is
         * minIntensity. Preserves the intensity relationship between the modality bands.
         */
        void normalizeIntensities() {
            T actualMinIntensity = INF;
            T actualMaxIntensity = -INF;
            int nElements = image.getNElements();
            int nBands = image.getNBands();
            for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                    if (image(elementIndex, bandIndex) < actualMinIntensity) {
                        actualMinIntensity = image(elementIndex, bandIndex);
                    }
                    if (image(elementIndex, bandIndex) >
                        actualMaxIntensity) { // else if would leave actualMaxIntensity uninitialized if all spels are of equal intensity.
                        actualMaxIntensity = image(elementIndex, bandIndex);
                    }
                }
            }
            T actualRange = actualMaxIntensity - actualMinIntensity; // check if actualRange > EPSILON
            T range = maxIntensity - minIntensity;
            if (actualRange > EPSILON) {
                if (range > EPSILON) {
                    for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                        for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                            image.setElement(elementIndex, bandIndex,
                                             (((image(elementIndex, bandIndex) - actualMinIntensity) /
                                               actualRange) * range) + minIntensity);
                        }
                    }
                }
            }
            else { // The image is completely flat.
                if (range > EPSILON) {
                    if (actualMinIntensity > minIntensity) {
                        if (actualMaxIntensity <
                            maxIntensity) { // The image is already within the target range. Do nothing.
                        }
                        else { // The image is at the maximum of the target range.
                            for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                                for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                                    image.setElement(elementIndex, bandIndex, maxIntensity);
                                }
                            }
                        }
                    }
                    else { // The image is at the minimum of the target range.
                        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                                image.setElement(elementIndex, bandIndex, minIntensity);
                            }
                        }
                    }
                }
                else { // The target range is infinitely narrow. Just assign its value to every element.
                    for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                        for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                            image.setElement(elementIndex, bandIndex, minIntensity);
                        }
                    }
                }
            }
        }

        /**
         * Normalizes the specified modality band of the image, so that it's maximum intensity is maxIntensity, and
         * it's lowest intensity is minIntensity. The other modality bands are left untouched.
         *
         * Parameter	| Comment
         * :-------		| :-------
         * bandIndex	| Index of the band to be normalized.
         *
         */
        void normalizeBand(int bandIndex) {
            T actualMinIntensity = INF;
            T actualMaxIntensity = -INF;
            int nElements = image.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                if (image(elementIndex, bandIndex) < actualMinIntensity) {
                    actualMinIntensity = image(elementIndex, bandIndex);
                }
                if (image(elementIndex, bandIndex) >
                    actualMaxIntensity) { // else if would leave actualMaxIntensity uninitialized if all spels are of equal intensity.
                    actualMaxIntensity = image(elementIndex, bandIndex);
                }
            }
            T actualRange = actualMaxIntensity - actualMinIntensity; // check if actualRange > EPSILON
            T range = maxIntensity - minIntensity;
            if (actualRange > EPSILON) {
                if (range > EPSILON) {
                    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                        image.setElement(elementIndex, bandIndex,
                                         (((image(elementIndex, bandIndex) - actualMinIntensity) /
                                           actualRange) * range) + minIntensity);
                    }
                }
            }
            else { // The image is completely flat.
                if (range > EPSILON) {
                    if (actualMinIntensity > minIntensity) {
                        if (actualMaxIntensity <
                            maxIntensity) { // The image is already within the target range. Do nothing.
                        }
                        else { // The image is at the maximum of the target range.
                            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                                image.setElement(elementIndex, bandIndex, maxIntensity);
                            }
                        }
                    }
                    else { // The image is at the minimum of the target range.
                        for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                            image.setElement(elementIndex, bandIndex, minIntensity);
                        }
                    }
                }
                else { // The target range is infinitely narrow. Just assign its value to every element.
                    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                        image.setElement(elementIndex, bandIndex, minIntensity);
                    }
                }
            }
        }

        /**
         * Sets the minimum intensity to the specified value, and optionally traverses and adjusts the data to the new
         * intensity range.
         *
         * Parameter	| Comment
         * :-------		| :-------
         * newMinVal	| New minimum intensity
         * option       | One of the following:
         *              |   none:         Do nothing. The user is responsible for all intensity values being within range.
         *              |   crop:         Values outside of the range are cropped to the range limits.
         *              |   normalize:    All intensity values are normalized to the new range.
         *
         */
        void setMinIntensity(T newMinVal, intensityAdjustmentOption option) {
            switch (option) {
                case none:
                    minIntensity = newMinVal;
                    break;
                case crop:
                    minIntensity = newMinVal;
                    cropIntensities();
                    break;
                case normalize:
                    minIntensity = newMinVal;
                    normalizeIntensities();
                    break;
                default:
                    // TODO: error?
            }
        }

        /**
         * Sets the maximum intensity to the specified value, and optionally traverses and adjusts the data to the new
         * intensity range.
         *
         * Parameter	| Comment
         * :-------		| :-------
         * newMaxVal	| New maximum intensity
         * option       | One of the following:
         *              |   none:         Do nothing. The user is responsible for all intensity values being within range.
         *              |   crop:         Values outside of the range are cropped to the range limits.
         *              |   normalize:    All intensity values are normalized to the new range.
         *
         */
        void setMaxIntensity(T newMaxVal, intensityAdjustmentOption option) {
            switch (option) {
                case none:
                    maxIntensity = newMaxVal;
                    break;
                case crop:
                    maxIntensity = newMaxVal;
                    cropIntensities();
                    break;
                case normalize:
                    maxIntensity = newMaxVal;
                    normalizeIntensities();
                    break;
                default:
                    // TODO: error?
            }
        }

        /**
        * Truncates the intensity value to fit into the range of the IntensityImage object.
        *
        * Parameter     | Comment
        * :---------    | :-------
        * intensity     | intensity of a spatial element
        */
        template<class S>
        T adjustIntensity(S intensity) const { // TODO: Needs something for rounding S to T.
            return MIN(maxIntensity, MAX(minIntensity, intensity));
        }
    };
}

#endif //INTENSITYWORKSET_H
