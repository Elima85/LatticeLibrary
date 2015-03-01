#ifndef INTENSITYCIMAGE_H
#define INTENSITYCIMAGE_H

#include "cimage.h"

namespace CImage {

/**
* Abstract base class for spatial domain images.
*/
    template<class T>
    class IntensityCImage : public CImage<T> {

    protected:
        T minValue;
        T maxValue;

    public:
        IntensityCImage(T *d, Lattice &l, int nB, T minVal, T maxVal) : CImage<T>(d, l, nB) {
            minValue = minVal;
            maxValue = maxVal;
            for (int intensityIndex = 0; intensityIndex < this->getNElements() * nB; intensityIndex++) {
                this->data[intensityIndex] = MIN(this->maxValue, MAX(this->minValue, this->data[intensityIndex]));
            }
        }
        IntensityCImage(const IntensityCImage &original) : CImage<T>(original) {
            minValue = original.minValue;
            maxValue = original.maxValue;
        }
        ~IntensityCImage() {};

        /**
        * Sets the intensity of element[index] to the value within the image intensity range that is closest to the specified intensity.
        *
        * Parameter		| Comment
        * :----------   | :--------
        * index			| element index
        * band			| band index
        * intensity		| new intensity valuse
        */
        template<class S>
        void setElement(int index, int band, S intensity) {
            if (!this->isValid(index, band)) {
                throw outsideImageException();
            }
            this->data[band * this->lattice.getNElements() + index] = this->adjustIntensity(intensity);
        }

        /**
        * Sets the intensity of element(r,c,l) to the value within the image intensity range that is closest to the specified intensity.
        *
        * Parameter		| Comment
        * :----------	| :--------
        * row			| row index
        * column		| column index
        * layer			| layer index
        * band			| band index
        * intensity		| new intensity valuse
        */
        template<class S>
        void setElement(int row, int column, int layer, int band, S intensity) {
            int index = this->rclToIndex(row, column, layer);
            this->setElement(index, band, intensity);
        }

        /**
        * Sets the intensity of element [index] to the value within the image intensity range that is closest to the specified intensity.
        *
        * Parameter		    | Comment
        * :----------   	| :--------
        * index			    | element index
        * intensityValues	| intensity values for each band
        */
        template <class S>
        void setElement(int index, vector<S> intensityValues) {
            if (!this->isValid(index)) {
                throw outsideImageException();
            }
            if (intensityValues.size() != this->nBands) {
                throw dimensionMismatchException();
            }
            for (int band = 0; band < this->nBands; band++) {
                this->data[band * this->lattice.getNElements() + index] = this->adjustIntensity(intensityValues[band]);
            }
        }

        /**
        * Sets the intensity of element (r,c,l) to the value within the image intensity range that is closest to the specified intensity.
        *
        * Parameter		    | Comment
        * :----------		| :--------
        * row				| row index
        * column			| column index
        * layer			    | layer index
        * intensityValues	| intensity values for each band
        */
        template<class S>
        void setElement(int row, int column, int layer, vector<S> intensityValues) {
            int index = this->rclToIndex(row, column, layer);
            this->setElement(index, intensityValues);
        }

        /**
        * Truncates the intensity value to fit into the range of the IntensityCImage object.
        *
        * Parameter     | Comment
        * :---------    | :-------
        * intensity     | intensity of a spatial element
        */
        template<class S>
        T adjustIntensity(S intensity) const { // TODO: Needs something for rounding S to T.
            return MIN(maxValue, MAX(minValue, intensity));
        }

    };

}

#endif