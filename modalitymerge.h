#ifndef MODALITYMERGE_H
#define MODALITYMERGE_H

#include "image.h"
#include "vectoroperators.h"

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
        template<class T>
        void mergeAllBands(Image<T> image, blendOption option, T* result) const {
            switch (option) {
                case min:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector <T> intensities = image[elementIndex];
                        int minIndex = getIndexOfMinimumValue(intensities);
                        result[elementIndex] = intensities[minIndex];
                    }
                    break;
                case max:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector <T> intensities = image[elementIndex];
                        int maxIndex = getIndexOfMaximumValue(intensities);
                        result[elementIndex] = intensities[maxIndex];
                    }
                    break;
                case mean:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector <T> intensities = image[elementIndex];
                        result[elementIndex] = T(meanValue(intensities));
                    }
                    break;
                case sum:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector <T> intensities = image[elementIndex];
                        result[elementIndex] = T(sumOfElements(intensities));
                    }
                    break;
                default:
                    return;
                    // throw error or exception
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
        template<class T>
        void mergeBands(Image<T> image, vector<int> bandIndices, blendOption option, T *result) const {
            int nBands = bandIndices.size();
            switch (option) {
                case min:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<T> intensities;
                        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                            intensities.push_back(image(elementIndex,bandIndices[bandIndex]));
                        }
                        int minIndex = getIndexOfMinimumValue(intensities);
                        result[elementIndex] = intensities[minIndex];
                    }
                    break;
                case max:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<T> intensities;
                        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                            intensities.push_back(image(elementIndex, bandIndices[bandIndex]));
                        }
                        int maxIndex = getIndexOfMaximumValue(intensities);
                        result[elementIndex] = intensities[maxIndex];
                    }
                    break;
                case mean:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<T> intensities;
                        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                            intensities.push_back(image(elementIndex, bandIndices[bandIndex]));
                        }
                        result[elementIndex] = T(meanValue(intensities));
                    }
                    break;
                case sum:
                    for (int elementIndex = 0; elementIndex < image.getNElements(); elementIndex++) {
                        vector<T> intensities;
                        for (int bandIndex = 0; bandIndex < nBands; bandIndex++) {
                            intensities.push_back(image(elementIndex, bandIndices[bandIndex]));
                        }
                        result[elementIndex] = T(sumOfElements(intensities));
                    }
                    break;
                default:
                    // throw error or exception
                    return;
            }
        }

    };
}

#endif //MODALITYMERGE_H
