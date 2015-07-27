#ifndef INTENSITYWORKSET_H
#define INTENSITYWORKSET_H

#include "image.h"
#include "lattice.h"
#include "dataredistribution.h"
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
            std::cout << "fitBandIntensities: actualMin = " << actualMin << ", actualMax = " << actualMax << "\n new limits: min = " << minIntensity << ", max = " << maxIntensity << std::endl;
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
            std::cout << "fitImageIntensities: actualMin = " << actualMin << ", actualMax = " << actualMax << "\n new limits: min = " << minIntensity << ", max = " << maxIntensity << std::endl;
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

        /**
         * Approximates the distance, in the range \f$[-0.5,0.5]\f$, between the spel center and an intersecting surface.
         *
         * Parameter	| in/out    | Comment
         * :-------		| :------   | :-------
         * intensity	| INPUT     | Coverage value of the spatial element.
         * option       | INPUT     | Method of approximation. <br> linear: \f$distance = 0.5 - coverage\f$ <br> ball: The spatial element is approximated by a ball. <br> voronoi: The average relationship between distance and coverage for the particular lattice is used.
         */
        double intensityToInternalDistance(intensityTemplate intensity, distanceApproximationOption option){
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
