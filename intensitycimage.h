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
        ~IntensityCImage() {};

        /**
        * Sets the intensity of element [index] to the specified intensity.
        *
        * Parameter		| Comment
        * :----------   | :--------
        * index			| element index
        * band			| band index
        * intensity		| new intensity valuse
        */
        void setElement(int index, int band, T intensity) { // TODO: Test!!
            if (!this->isValid(index, band)) {
                throw outsideImageException();
            }
            this->data[band * this->lattice.getNElements() + index] = this->adjustIntensity(intensity);
        }

        /**
        * Sets the intensity of element [index] to the specified intensity.
        *
        * Parameter		    | Comment
        * :----------   	| :--------
        * index			    | element index
        * intensityValues	| intensity values for each band
        */
        template<class S>
        void setElement(int index, vector<T> intensityValues) { // TODO: Test!!
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