#ifndef MODALITYMERGE_H
#define MODALITYMERGE_H

#include "image.h"
#include "vectoroperators.h"
#include "minimumvaluefinder.h"
#include "maximumvaluefinder.h"
#include <stdio.h>

namespace LatticeLib {

    enum blendOption {min, max, mean, sum};

    /**
     * Class for merging image modality bands.
     */
    class ModalityMerge { // TODO: Test!

    public:

        /**
         * Blends all modality bands into a single band, and returns the result in the form of an array.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image        | INPUT     | Image containing the modality bands to be merged.
         * option		| INPUT		| Decides how to merge the modality bands into one <br> blendOption::min: minimum value is kept <br> blendOption::max: maximum value is kept <br> blendOption::mean: returns the mean intensity for each element <br> blendOption::sum: returns the sum of the intensities for each element
         * result		| OUTPUT	| Blended values. Needs to be of length >= nElements.
         */
        template<class intensityTemplate>
        void mergeAllBands(Image<intensityTemplate> image, blendOption option, intensityTemplate* result) const {
            switch (option) {
                case min:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<intensityTemplate> intensities = image[elementIndex];
                        MinimumValueFinder<intensityTemplate> valueFinder;
                        int minIndex = valueFinder.getVectorElementIndex(intensities);
                        result[elementIndex] = intensities[minIndex];
                    }
                    break;
                case max:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<intensityTemplate> intensities = image[elementIndex];
                        MaximumValueFinder<intensityTemplate> valueFinder;
                        int maxIndex = valueFinder.getVectorElementIndex(intensities);
                        result[elementIndex] = intensities[maxIndex];
                    }
                    break;
                case mean:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector <intensityTemplate> intensities = image[elementIndex];
                        result[elementIndex] = intensityTemplate(meanValue(intensities));
                    }
                    break;
                case sum:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector <intensityTemplate> intensities = image[elementIndex];
                        result[elementIndex] = intensityTemplate(sumOfElements(intensities));
                    }
                    break;
                default:
                    throw incompatibleParametersException();
            }
        }

        /**
         * Blends the specified modality bands into a single band, and returns the result in the form of an array.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image        | INPUT     | Image containing the modality bands to be merged.
         * bandIndices  | INPUT     | Indices of the bands to be merged.
         * option		| INPUT		| Decides how to merge the modality bands into one <br> blendOption::min: minimum value is kept <br> blendOption::max: maximum value is kept <br> blendOption::mean: returns the mean intensity for each element <br> blendOption::sum: returns the sum of the intensities for each element
         * result		| OUTPUT	| Blended values. Needs to be of length >= nElements.
         */
        template<class intensityTemplate>
        void mergeBands(Image<intensityTemplate> image, vector<int> bandIndices, blendOption option, intensityTemplate *result) const {
            int nBands = bandIndices.size();
            switch (option) {
                case min:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<intensityTemplate> intensities;
                        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                            intensities.push_back(image(elementIndex,bandIndices[bandIndex]));
                        }
                        MinimumValueFinder<intensityTemplate> valueFinder;
                        int minIndex = valueFinder.getVectorElementIndex(intensities);
                        result[elementIndex] = intensities[minIndex];
                    }
                    break;
                case max:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<intensityTemplate> intensities;
                        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                            intensities.push_back(image(elementIndex, bandIndices[bandIndex]));
                        }
                        MaximumValueFinder<intensityTemplate> valueFinder;
                        int maxIndex = valueFinder.getVectorElementIndex(intensities);
                        result[elementIndex] = intensities[maxIndex];
                    }
                    break;
                case mean:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<intensityTemplate> intensities;
                        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                            intensities.push_back(image(elementIndex, bandIndices[bandIndex]));
                        }
                        result[elementIndex] = intensityTemplate(meanValue(intensities));
                    }
                    break;
                case sum:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<intensityTemplate> intensities;
                        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                            intensities.push_back(image(elementIndex, bandIndices[bandIndex]));
                        }
                        result[elementIndex] = intensityTemplate(sumOfElements(intensities));
                    }
                    break;
                default:
                    throw incompatibleParametersException();
            }
        }

    };
}

#endif //MODALITYMERGE_H
