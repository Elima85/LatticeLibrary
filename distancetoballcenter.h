#ifndef LATTICELIBRARY_DISTANCETOBALLCENTER_H
#define LATTICELIBRARY_DISTANCETOBALLCENTER_H

#include "intensityworkset.h"
#include "linearinterpolation.h

namespace LatticeLib {

    const double distanceTable[] = {0.620350490899400, 0.555652269755901, 0.528145846788119, 0.506733087451325,
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
                                    -0.003256467310422, -0.009770118241188, -0.016285922793488, -0.022805323630817,
                                    -0.029329771361217, -0.035860727807206, -0.042399669346958, -0.048948090348974,
                                    -0.055507506723748, -0.062079459617461, -0.068665519274746, -0.075267289099859,
                                    -0.081886409948482, -0.088524564685696, -0.095183483049688, -0.101864946865430,
                                    -0.108570795658118, -0.115302932722693, -0.122063323408814, -0.128854005489208,
                                    -0.135677111230972, -0.142534866270465, -0.149429598983671, -0.156363750911781,
                                    -0.163339888340089, -0.170360715205684, -0.177429087540041, -0.184548014514595,
                                    -0.191720656894715, -0.198950416024646, -0.206240924436824, -0.213596069832290,
                                    -0.221020025533428, -0.228517246588628, -0.236092477215586, -0.243750944387129,
                                    -0.251498337907496, -0.259340853252859, -0.267285098580547, -0.275338468809351,
                                    -0.283509194867229, -0.291806237861002, -0.300239505316538, -0.308820379142559,
                                    -0.317561321011888, -0.326476583721540, -0.335582559204241, -0.344897652005037,
                                    -0.354443732834115, -0.364245771896524, -0.374333786228138, -0.384743426499272,
                                    -0.395517753727525, -0.406710310647046, -0.418388186452059, -0.430637667609462,
                                    -0.443573133456331, -0.457351805704674, -0.472200234189075, -0.488465341540169,
                                    -0.506733087451326, -0.528145846788120, -0.555652269755902, -0.620350490899443};
    /**
     * Class for approximation of the distance, in the range \f$[-0.5,0.5]\f$, between an element center and the intersecting surface of a fuzzy object, under the assumption that the element is spherical.
     */
    template<class intensityTemplate>
    class DistanceToBallCenter : public DistanceToElementCenter {

    public:
        /**
         * Implements DistanceToElementCenter::compute().
         *
         * Approximates the distance, in the range \f$[-0.5,0.5]\f$, between an element center and the intersecting surface of a fuzzy object by assuming the element is spherical.
         *
         * Parameter    | in/out    | Comment
         * :---------   | :------   | :-------
         * inputImage   | INPUT     | %Image containing the specified element.
         * elementIndex | INPUT     | Element for which to compute the distance.
         * labelIndex   | INPUT     | Label (band) index for the specified element.
         */
        double compute(IntensityWorkset<intensityTemplate> inputImage, int elementIndex, int labelIndex) const {
            double minValue = inputImage.getMinIntensity();
            double maxValue = inputImage.getMaxIntensity();
            double range = maxIntensity - minIntensity;
            intensityTemplate intensity = MIN(maxValue, MAX(minValue, inputImage.getImage()(elementIndex, labelIndex)));
            double coverage = (double(intensity) - minValue) / range;
            LinearInterpolation<int, double> interpolation;
            double coveragePosition = coverage * 128;
            vector<int> bounds;
            bounds.push_back(floor(coveragePosition));
            bounds.push_back(ceil(coveragePosition));
            vector<double> values(distanceTable + bounds[0], distanceTable + bounds[1]);
            double scaleFactor = cbrt(1 / inputImage.getImage().getDensity());
            return interpolation.apply(bounds, values, coveragePosition) * scaleFactor;
        }

    };
}

#endif //LATTICELIBRARY_DISTANCETOBALLCENTER_H
