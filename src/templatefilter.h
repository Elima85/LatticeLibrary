#ifndef LATTICELIBRARY_TEMPLATEFILTER_H
#define LATTICELIBRARY_TEMPLATEFILTER_H

#include "spatialtemplate.h"
#include "filtercoefficient.h"
#include "image.h"
#include <vector>

namespace LatticeLib {

    /**
     * Abstract base class for spatial filters
     * ========================================
     *
     * Member 			| Comment
     * --------			| --------
     * neighborhoodSize	| Element neighborhood size to be used for this filter.
     * coefficients		| Template coefficients.
     */
    template<class coefficientTemplate, class intensityTemplate>
    class TemplateFilter : public SpatialTemplate <coefficientTemplate> {

    public:
        TemplateFilter(vector<FilterCoefficient<coefficientTemplate> > c, int nS) : SpatialTemplate<coefficientTemplate>(c, nS) {}
        virtual ~TemplateFilter() {}
        virtual void applyToBand(Image<intensityTemplate> image, int bandIndex, double *result) const = 0;
        virtual void applyToImage(Image<intensityTemplate> image, double *result) const = 0;
    };

}

#endif //LATTICELIBRARY_TEMPLATEFILTER_H
