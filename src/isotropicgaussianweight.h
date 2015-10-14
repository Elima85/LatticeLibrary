#ifndef LATTICELIBRARY_ISOTROPICGAUSSIANWEIGHT_H
#define LATTICELIBRARY_ISOTROPICGAUSSIANWEIGHT_H

#include "image.h"
#include "weightassignment.h"
#include <vector>
#include <math.h> // exp
#include "pnorm.h"

namespace LatticeLib {

    /**
     * Class for Gaussian weighting, using a Gaussian distribution with the specified standard deviation,
     * centered at the reference spatial element.
     */
    template<class intensityTemplate>
    class IsotropicGaussianWeight : public WeightAssignment<intensityTemplate> { // TODO: Test!
    private:
        /** Standard deviation of the Gaussian distribution. */
        double standardDeviation;

    public:

        /**
         * Constructor for GaussianWeight objects.
         *
         * Parameter    | Comment
         * :---------   | :-------
         * stdDev       | Standard deviation of the distribution.
         */
        IsotropicGaussianWeight(double stdDev) : WeightAssignment<intensityTemplate>() {
            standardDeviation = stdDev;
        }

        /**
         * Returns the standard deviation of the Gaussian distribution.
         */
        double getStandardDeviation() {
            return standardDeviation;
        }

        /**
         * Sets the standard deviation of the Gaussian distribution.
         *
         * Parameter    | in/out	| Comment
         * :---------   | :------	| :-------
         * s            | INPUT     | New standard deviation of the distribution.
         */
        void setStandardDeviation(doube stdDev) {
            standardDeviation = stdDev;
        }

        /**
         * Implements WeightAssignment.compute().
         *
         * Computes a weight for the input spatial element based on its distance to the reference spatial element and
         * the specified Gaussian distribution.
         *
         * Parameter		        | in/out	| Comment
         * :---------		        | :------	| :-------
         * referenceElementIndex    | INPUT     | Index of the reference element for the weight computation.
         * referenceImage           | INPUT     | Image to which the reference element belongs.
         * inputElementIndex        | INPUT     | Index of the element that is to be assigned a weight.
         * inputImage               | INPUT     | Image to which the element to be weighted belongs.
         */
        double compute(int referenceElementIndex, Image<intensityTemplate> referenceImage,
                       int inputElementIndex, Image<intensityTemplate> inputImage) const {
            vector<double> referenceCoordinates;
            referenceImage.getCoordinates(referenceElementIndex, referenceCoordinates);
            vector<double> inputCoordinates;
            inputImage.getCoordinates(inputElementIndex, inputCoordinates);
            PNorm norm(2);
            double distance = norm(referenceCoordinates - inputCoordinates);
            return 1/(standardDeviation * sqrt(2 * PI)) * exp(distance * distance/(2 * standardDeviation * standardDeviation));
        }
    };
}

#endif //LATTICELIBRARY_ISOTROPICGAUSSIANWEIGHT_H
