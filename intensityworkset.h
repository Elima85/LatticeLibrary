#ifndef INTENSITYWORKSET_H
#define INTENSITYWORKSET_H

#include "image.h"
#include "lattice.h"
#include "valuecropper.h"
#include "valuenormalizer.h"
#include "valuedenormalizer.h"
#include <algorithm>
#include "exception.h"
#include <stdio.h>
#include <cmath>

namespace LatticeLib {

    const double subSpelDistanceBall[] = {0.620350490899400, 0.555652269755901, 0.528145846788119, 0.506733087451325,
                                          0.488465341540168, 0.472200234189075, 0.457351805704674, 0.443573133456330,
                                          0.430637667609462, 0.418388186452059, 0.406710310647046, 0.395517753727524,
                                          0.384743426499272, 0.374333786228138, 0.364245771896523, 0.354443732834114,
                                          0.344897652005037, 0.335582559204240, 0.326476583721540, 0.317561321011888,
                                          0.308820379142558, 0.300239505316538, 0.291806237861001, 0.283509194867229,
                                          0.275338468809351, 0.267285098580547, 0.259340853252859, 0.251498337907495,
                                          0.243750944387129, 0.236092477215586, 0.228517246588628, 0.221020025533428,
                                          0.213596069832290, 0.206240924436824, 0.198950416024646, 0.191720656894714,
                                          0.184548014514595, 0.177429087540041, 0.170360715205684, 0.163339888340089,
                                          0.156363750911780, 0.149429598983671, 0.142534866270465, 0.135677111230972,
                                          0.128854005489208, 0.122063323408814, 0.115302932722693, 0.108570795658118,
                                          0.101864946865430, 0.095183483049688, 0.088524564685696, 0.081886409948481,
                                          0.075267289099859, 0.068665519274745, 0.062079459617461, 0.055507506723747,
                                          0.048948090348974, 0.042399669346957, 0.035860727807206, 0.029329771361217,
                                          0.022805323630816, 0.016285922793487, 0.009770118241188, 0.003256467310422,
                                          -0.003256467310422, -0.009770118241188, -0.016285922793488,
                                          -0.022805323630817, -0.029329771361217, -0.035860727807206,
                                          -0.042399669346958, -0.048948090348974, -0.055507506723748,
                                          -0.062079459617461, -0.068665519274746, -0.075267289099859,
                                          -0.081886409948482, -0.088524564685696, -0.095183483049688,
                                          -0.101864946865430, -0.108570795658118, -0.115302932722693,
                                          -0.122063323408814, -0.128854005489208, -0.135677111230972,
                                          -0.142534866270465, -0.149429598983671, -0.156363750911781,
                                          -0.163339888340089, -0.170360715205684, -0.177429087540041,
                                          -0.184548014514595, -0.191720656894715, -0.198950416024646,
                                          -0.206240924436824, -0.213596069832290, -0.221020025533428,
                                          -0.228517246588628, -0.236092477215586, -0.243750944387129,
                                          -0.251498337907496, -0.259340853252859, -0.267285098580547,
                                          -0.275338468809351, -0.283509194867229, -0.291806237861002,
                                          -0.300239505316538, -0.308820379142559, -0.317561321011888,
                                          -0.326476583721540, -0.335582559204241, -0.344897652005037,
                                          -0.354443732834115, -0.364245771896524, -0.374333786228138,
                                          -0.384743426499272, -0.395517753727525, -0.406710310647046,
                                          -0.418388186452059, -0.430637667609462, -0.443573133456331,
                                          -0.457351805704674, -0.472200234189075, -0.488465341540169,
                                          -0.506733087451326, -0.528145846788120, -0.555652269755902,
                                          -0.620350490899443}; // TODO: 255 elements or interpolation

    enum imageIntensityAdjustmentOption {none, crop, normalize}; // for the entire image at once
    enum distanceApproximationOption {linear, ball, voronoi};

/**
 * A class for spatial domain images and fuzzy segmented images, for which it is necessary to know the possible intensity range.
 *
 * Member 		| Comment
 * :-------		| :-------
 * image		| Spatial domain image or fuzzy segmentation.
 * minIntensity | The lowest possible intensity value.
 * maxIntensity	| The highest possible intensity value.
 */
    template <class T>
    class IntensityWorkset {

    private:
        /** %Image dimensions and data. */
        Image<T> &image;

        /** Minimum intensity value. */
        T minIntensity;

        /** Maximum intensity value. */
        T maxIntensity;

    public:
        /**
         * Constructor for IntensityWorkset objects.
         *
         * Parameter    | in/out    |Comment
         * :---------   | :------   |:-------
         * image        | INPUT     | %Image dimensions and data.
         * minVal       | INPUT     | Minimum intensity value.
         * maxVal       | INPUT     | Maximum intensity value.
         * option       | INPUT     | Intensity adjustment of the input data.<br> none: No adjustment. <br> crop: Crop all values outside of the specified range. <br> normalize: Stretch or compress the image data to the specified range. _This does not work well for integer intensities. Please see ValueNormalizer::apply()._
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

        /**
         * Copy constructor for IntensityWorkset objects.
         *
         * Parameter    | in/out    |Comment
         * :---------   | :------   |:-------
         * original     | INPUT     | IntensityWorkset object to be copied.
         */
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

        /** Returns the length of the intensity range. */
        T getRange() const {
            return maxIntensity - minIntensity;
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
         * _This does not work well for integer intensities. Please see ValueNormalizer::apply()._
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
         * _This does not work well for integer intensities. Please see ValueNormalizer::apply()._
         *
         * Parameter	| in/out    | Comment
         * :-------		| :------   | :-------
         * bandIndex	| INPUT     | Index of the band to be normalized.
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
         * Parameter	| in/out    | Comment
         * :-------		| :------   | :-------
         * newMinVal	| INPUT     | New minimum intensity
         * option       | INPUT     | Intensity adjustment of the input data.<br> none: No adjustment. <br> crop: Crop all values outside of the specified range. <br> normalize: Stretch or compress the image data to the specified range. _This does not work well for integer intensities. Please see ValueNormalizer::apply()._
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
                    throw invalidArgumentException(); // TODO: other exception?
            }
        }

        /**
         * Sets the maximum intensity to the specified value, and optionally traverses and adjusts the data to the new
         * intensity range.
         *
         * Parameter	| in/out    | Comment
         * :-------		| :------   | :-------
         * newMaxVal	| INPUT     | New maximum intensity
         * option       | INPUT     | Intensity adjustment of the input data.<br> none: No adjustment. <br> crop: Crop all values outside of the specified range. <br> normalize: Stretch or compress the image data to the specified range. _This does not work well for integer intensities. Please see ValueNormalizer::apply()._
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

        /**
         * Approximates the distance, in the range \f$[-0.5,0.5]\f$, between the spel center and an intersecting surface.
         *
         * Parameter	| in/out    | Comment
         * :-------		| :------   | :-------
         * intensity	| INPUT     | Coverage value of the spatial element.
         * option       | INPUT     | Method of approximation. <br> linear: \f$distance = 0.5 - coverage\f$ <br> ball: The spatial element is approximated by a ball. <br> voronoi: The average relationship between distance and coverage for the particular lattice is used.
         */
        double intensityToInternalDistance(T intensity, distanceApproximationOption option){
            intensity = MIN(maxIntensity, MAX(minIntensity, intensity));
            double minValue = minIntensity;
            double range = maxIntensity - minIntensity;
            double coverage = (double(intensity) - minValue)/range;
            double result;
            switch (option) {
                case linear:
                    result = 0.5 - coverage; // TODO: * scaleFactor
                    break;
                case ball: {
                    int coverageIndex = round(coverage * 255);
                    result = subSpelDistanceBall[coverageIndex]; // TODO: * scaleFactor
                    break;
                }
                case voronoi: {
                    // TODO: result = image.getLattice().coverageToInternalDistance(coverage);
                    break;
                }
                default:
                    // TODO: throw error or exception
                    result = 0;
            }
            return result;
        }
    };
}

#endif //INTENSITYWORKSET_H
