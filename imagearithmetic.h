#ifndef IMAGEARITHMETIC_H
#define IMAGEARITHMETIC_H

#include "image.h"
#include "vectoroperators.h"

namespace LatticeLib {

    class ImageArithmetic {

    public:

        /**
         * Adds the intensity values of two images.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image1		| INPUT		| First term of the addition.
         * image2		| INPUT		| Second term of the addition. Needs to have a Lattice identical to that of image1.
         * result		| OUTPUT	| Result of addition. Needs to have a Lattice identical to that of image1.
         */
        template<class T, class S>
        void add(Image<T> image1, Image <S> image2, Image<T> result) {
            if ((image1.getLattice() != image2.getLattice()) || (image1.getLattice() != result.getLattice())) {
                // throw error or exception
            }
            if ((image1.getNBands() != image2.getNBands()) || (image1.getNBands() != result.getNBands())) {
                // throw error or exception
            }
            int nElements = image1.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                result.setElement(elementIndex, image1[elementIndex] + image2[elementIndex]);
            }
        }

        /**
         * Subtracts the intensity values of one image from the other.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image1		| INPUT		| First term of the subtraction.
         * image2		| INPUT		| Second term of the subtraction. Needs to have a Lattice identical to that of image1.
         * result		| OUTPUT	| Result of addition. Needs to have a Lattice identical to that of image1.
         */
        template<class T, class S>
        void subtract(Image<T> image1, Image<S> image2, Image<T> result) {
            if ((image1.getLattice() != image2.getLattice()) || (image1.getLattice() != result.getLattice())) {
                // throw error or exception
            }
            if ((image1.getNBands() != image2.getNBands()) || (image1.getNBands() != result.getNBands())) {
                // throw error or exception
            }
            int nElements = image1.getNElements();
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                result.setElement(elementIndex, image1[elementIndex] - image2[elementIndex]);
            }
        }

        /**
         * Scales the intensity values of the input image by the input factor.
         *
         * Parameter	| in/out	| Comment
         * :----------	| :-------	| :--------
         * image        | INPUT     | Image to be scaled.
         * factor		| INPUT		| Scale factor with which to multiply the intensity values.
         * result		| OUTPUT	| Result of the multiplication. Needs to have a Lattice identical to that of image1.
         */
        template<class T, class S>
        void scale(Image<T> image, S factor, Image<T> result) {
            int nTotal = image.getNBands() * image.getNElements();
            T *dataIn = image.getData();
            T *dataOut = result.getData();
            for (int dataIndex = 0; dataIndex < nTotal; dataIndex++) {
                dataOut[dataIndex] = T(factor * dataIn[dataIndex]);
            }
        }
    };
}

#endif //IMAGEARITHMETIC_H
