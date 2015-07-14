#ifndef IMAGEARITHMETICS_H
#define IMAGEARITHMETICS_H

#include "image.h"

namespace LatticeLib {

    class ImageArithmetics {

    public:

        /**
         * Adds the intensity values of two images.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image1		| INPUT		| First term of the addition.
         * image2		| INPUT		| Second term of the addition.
         * result		| OUTPUT	| Result of addition. Needs to be of length >= nElements.
         */
        template<class T, class S>
        void add(Image<T> image1, Image <S> image2, T *result) {
            if (image1.getLattice() != image2.getLattice()) {
                // throw error or exception
            }
            if (image1.getNBands() != image2.getNBands()) {
                // throw error or exception
            }
            int nTotal = image1.getNBands() * image1.getNElements();
            T *data1 = image1.getData();
            T *data2 = image2.getData();
            for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
                result[dataIndex] = T(data1[dataIndex] + data2[dataIndex]);
            }
        } // TODO: test!

        /**
         * Adds the intensity values of two bands of two images.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image1		| INPUT		| First term of the addition.
         * bandIndex1	| INPUT		| Index of the desired band of the first image.
         * image2		| INPUT		| Second term of the addition.
         * bandIndex2	| INPUT		| Index of the desired band of the second image.
         * result		| OUTPUT	| Result of addition. Needs to be of length >= nElements.
         */
        template<class T, class S>
        void addBands(Image<T> image1, int bandIndex1, Image <S> image2, int bandIndex2, T *result) {
            if (image1.getLattice() != image2.getLattice()) {
                // throw error or exception
            }
            int nElements = image1.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                result[elementIndex] = T(image1.(elementIndex, bandIndex1) + image2(elementIndex, bandIndex2));
            }
        } // TODO: test!

        /**
         * Subtracts the intensity values of one image from the other.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image1		| INPUT		| First term of the subtraction.
         * image2		| INPUT		| Second term of the subtraction.
         * result		| OUTPUT	| Result of addition. Needs to be of length >= nElements.
         */
        template<class T, class S>
        void subtract(Image <T> image1, Image <S> image2, T *result) {
            if (image1.getLattice() != image2.getLattice()) {
                // throw error or exception
            }
            if (image1.getNBands() != image2.getNBands()) {
                // throw error or exception
            }
            int nTotal = image1.getNBands() * image1.getNElements();
            T *data1 = image1.getData();
            T *data2 = image2.getData();
            for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
                result[dataIndex] = T(data1[dataIndex] - data2[dataIndex]);
            }
        } // TODO: test!

        /**
         * Subtracts the intensity values of two bands of two images.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image1		| INPUT		| First term of the subtraction.
         * bandIndex1	| INPUT		| Index of the desired band of the first image.
         * image2		| INPUT		| Second term of the subtraction.
         * bandIndex2	| INPUT		| Index of the desired band of the second image.
         * result		| OUTPUT	| Result of subtraction. Needs to be of length >= nElements.
         */
        template<class T, class S>
        void subtractBands(Image <T> image1, int bandIndex1, Image <S> image2, int bandIndex2, T *result) {
            if (image1.getLattice() != image2.getLattice()) {
                // throw error or exception
            }
            int nElements = image1.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                result[elementIndex] = T(image1(elementIndex, bandIndex1) - image2(elementIndex, bandIndex2));
            }
        } // TODO: test!

        /**
         * Scales the intensity values of the input image by the input factor.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image        | INPUT     | Image to be scaled.
         * factor		| INPUT		| Scale factor with which to multiply the intensity values.
         * result		| OUTPUT	| Result of the multiplication. Needs to be of length >= nElements.
         */
        template<class T, class S>
        void scale(Image<T> image, S factor, T *result) {
            int nTotal = image.getNBands() * image.getNElements();
            T *data = image.getData();
            for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
                result[dataIndex] = T(factor * data[dataIndex]);
            }
        } // TODO: test!
    };
}

#endif //IMAGEARITHMETICS_H
