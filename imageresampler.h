#ifndef LATTICELIBRARY_IMAGERESAMPLER_H
#define LATTICELIBRARY_IMAGERESAMPLER_H

#include "image.h"
#include "exception.h"

namespace LatticeLib {
    template<class intensityTemplate>
    /**
     * Class for resampling image data from one lattice to another.
     *
     * The origins of the input and output images are aligned. If the input image is smaller than the output image,
     * zero-padding is added. If the output image is smaller than the input image, only part of the input image is used.
     */
    class ImageResampler {
    public:
        /**
         * Resamples the input image to a lattice of lower resolution. The intensity values of the low resolution
         * spatial elements are computed as a weighted average of the high resolution spatial elements.
         *
         * Parameter		| in/out	| Comment
         * :---------		| :------	| :-------
         * inputImage       | INPUT     | Input high resolution image.
         *                  | INPUT     | Assigns weights to the high resolution elements in the downsampling process.
         * outputImage      | OUTPUT    | Output low resolution image.
         */
        void downsample(Image<intensityTemplate> inputImage, Image<intensityTemplate> outputImage) const {
            if (inputImage.getLattice().getDensity() < outputImage.getLattice().getDensity()) {
                throw incompatibleParametersException();
            }
        }
    };
}

#endif //LATTICELIBRARY_IMAGERESAMPLER_H
