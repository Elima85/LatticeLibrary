#ifndef INTENSITYWORKSET_H
#define INTENSITYWORKSET_H

#include "image.h"
#include "lattice.h"
#include "valuecropper.h"
#include "valuenormalizer.h"
#include "valuedenormalizer.h"
#include <algorithm>

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
        IntensityWorkset(T *d, Lattice &l, int nB, T minVal, T maxVal, imageIntensityAdjustmentOption option) {
            switch(option) {
                case none:
                    break;
                case crop:
                    ValueCropper cropper;
                    int nElements = l.getNElements() * nB;
                    cropper.apply(d, nElements, minVal, maxVal);
                    break;
                case normalize:
                    int nElements = l.getNElements() * nB;
                    ValueNormalizer normalizer;
                    ValueDenormalizer denormalizer;
                    T currentMinVal = d[std::min_element(d, d + nElements)];
                    T currentMaxVal = d[std::max_element(d, d + nElements)];
                    normalizer.apply(d, nElements, currentMinVal, currentMaxVal);
                    denormalizer.apply(d, nElements, MinVal, MaxVal);
                    break;
                default:
                    //TODO: error?
            }
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
        T getMinIntensity() const {
            return minIntensity;
        }

        /** Returns maxIntensity. */
        T getMaxIntensity() const {
            return maxIntensity;
        }

        /**
         * Crops the intensity values, so that all values fit in the specified intensity range.
         */
        void cropIntensities() {
            int nElements = image.getNElements();
            int nBands = image.getNBands();
            ValueCropper cropper;
            cropper.apply(d, nBands * nElements, minVal, maxVal);
        }

        /**
         * Normalizes the image, so that it's maximum intensity is maxIntensity, and it's lowest intensity is
         * minIntensity. Preserves the intensity relationship between the modality bands.
         */
        void normalizeIntensities() {
            int nElements = image.getNElements();
            int nBands = image.getNBands();
            int nTotal = nBands * nElements;
            ValueNormalizer normalizer;
            ValueDenormalizer denormalizer;
            T currentMinVal = d[std::min_element(d, d + nTotal)];
            T currentMaxVal = d[std::max_element(d, d + nTotal)];
            normalizer.apply(d, nTotal, currentMinVal, currentMaxVal);
            denormalizer.apply(d, nTotal, MinVal, MaxVal);
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
            int nElements = image.getNElements();
            int start = bandIndex * nElements;
            int stop = start + nElements;
            ValueNormalizer normalizer;
            ValueDenormalizer denormalizer;
            T currentMinVal = d[std::min_element(d + start, d + stop)];
            T currentMaxVal = d[std::max_element(d + start, d + stop)];
            normalizer.apply(d + start, nElements, currentMinVal, currentMaxVal);
            denormalizer.apply(d + start, nElements, MinVal, MaxVal);
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
    };
}

#endif //INTENSITYWORKSET_H
