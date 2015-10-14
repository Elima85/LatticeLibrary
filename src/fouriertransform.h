#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

namespace LatticeLib {

    /**
    * Computes the Fourier transform of the input image.
    *
    * Parameter			    | Comment
    * :----------		    | :--------
    * spatialDomainImage	| Spatial domain image.
    *
    * Returns
    * :-------
    * A frequency domain image that is the Fourier transform of the input image.
    */
    // TODO: What types can FFTW handle? Can T be a template, or should it be defined?
    // TODO: Depending on the above, the implementation may have to be moved to a cpp-file.
    template <class T>
    void fourierTransform(Image<T> &spatialDomainImage, Image<complex> &frequencyDomainImage) {
        // TODO: Allocate and fill frequencyValues with data obtained through Fourier transform.
        // TODO: Add the abstract method int* rearrangeForFFT() to the Lattice class and implement for CCLattice, BCCLattice and FCCLattice.
        // TODO: Create a Lattice object for the frequency domain image.
    }

    /**
    * Computes the inverse Fourier transform of the input image.
    *
    * Parameter			    | Comment
    * :----------		    | :--------
    * frequencyDomainImage	| Frequency domain image.
    *
    * Returns
    * :-------
    * A spatial domain image that is the inverse Fourier transform of the input image.
    */
    // TODO: What types can FFTW handle? What type should T be for the output?
    // TODO: Depending on the above, the implementation may have to be moved to a cpp-file.
    void inverseFourierTransform(Image<complex> &frequencyDomainImage, Image<double> &spatialDomainImage) {
        // TODO: Allocate and fill spatialValues with data obtained through inverse Fourier transform.
        // TODO: Add the abstract method int* rearrangeForIFFT() to the Lattice class and implement for CCLattice, BCCLattice and FCCLattice.
        // TODO: Create a Lattice object for the spatial domain image.
    }

}

#endif