#ifndef INTENSITYWORKSET_H
#define INTENSITYWORKSET_H

#include "image.h"
#include "lattice.h"
#include "cclattice.h"
#include "valuecropper.h"
#include "valuenormalizer.h"
#include "valuedenormalizer.h"
#include <algorithm>
#include "exception.h"
#include <stdio.h>

namespace LatticeLib {

    enum imageIntensityAdjustmentOption {none, crop, normalize}; // for the entire image at once
    //enum elementIntensityAdjustmentOption {none, crop}; // for a single element. Normalization is not possible.

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
    template <class T>
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
        IntensityWorkset(Image<T> &im, T minVal, T maxVal, imageIntensityAdjustmentOption option) : image(im){
            switch (option) {
                case none:
                    break;
                case crop: {
                    T* data = im.getData();
                    int nElements = im.getLattice().getNElements() * im.getNBands();
                    ValueCropper cropper;
                    cropper.apply(data, nElements, minVal, maxVal);
                    break;
                }
                case normalize:{
                    T *data = im.getData();
                    int nElements = im.getLattice().getNElements() * im.getNBands();
                    ValueNormalizer normalizer;
                    ValueDenormalizer denormalizer;
                    T currentMinVal = *std::min_element(data, data + nElements);

                    T currentMaxVal = *std::max_element(data, data + nElements);
                    normalizer.apply(data, nElements, currentMinVal, currentMaxVal);
                    denormalizer.apply(data, nElements, minVal, maxVal);
                    break;
                }
                default:
                    throw invalidArgumentException();
            }
            minIntensity = minVal;
            maxIntensity = maxVal;
        }

        IntensityWorkset(const IntensityWorkset<T> &original) : image(original.getImage()){
            minIntensity = original.minIntensity;
            maxIntensity = original.maxIntensity;
        }

        ~IntensityWorkset() {}; // TODO: delete data array?

        /** Returns image. */
        Image<T>& getImage() const {
            return image;
        }

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
            cropper.apply(image.getData(), nBands * nElements, minIntensity, maxIntensity);
        }

        /**
         * Normalizes the image, so that it's maximum intensity is maxIntensity, and it's lowest intensity is
         * minIntensity. Preserves the intensity relationship between the modality bands.
         */
        void normalizeIntensities() {
            int nElements = image.getNElements();
            int nBands = image.getNBands();
            int nTotal = nBands * nElements;
            T* data = image.getData();
            ValueNormalizer normalizer;
            ValueDenormalizer denormalizer;
            T currentMinVal = *std::min_element(data, data + nTotal);
            T currentMaxVal = *std::max_element(data, data + nTotal);
            //std::cout << "minVal: " << currentMinVal << ", maxVal: " << currentMaxVal << std::endl;
            normalizer.apply(data, nTotal, currentMinVal, currentMaxVal);
            denormalizer.apply(data, nTotal, minIntensity, maxIntensity);
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
            T *data = image.getData();
            ValueNormalizer normalizer;
            ValueDenormalizer denormalizer;
            T currentMinVal = *std::min_element(data + start, data + stop);
            T currentMaxVal = *std::max_element(data + start, data + stop);
            //std::cout << "minVal: " << currentMinVal << ", maxVal: " << currentMaxVal << std::endl;
            normalizer.apply(data + start, nElements, currentMinVal, currentMaxVal);
            denormalizer.apply(data + start, nElements, minIntensity, maxIntensity);
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
        void setMinIntensity(T newMinVal, imageIntensityAdjustmentOption option) {
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
                    throw invalidArgumentException();
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
        void setMaxIntensity(T newMaxVal, imageIntensityAdjustmentOption option) {
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
                    throw invalidArgumentException();
            }
        }
    };
}

#endif //INTENSITYWORKSET_H
