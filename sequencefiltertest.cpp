#include "gtest/gtest.h"
#include "defs.h"
#include "filtercoefficient.h"
#include <cmath>
#include "sequencefilter.h"
#include "maximumvaluefinder.h"
#include "minimumvaluefinder.h"
#include <vector>
#include "cclattice.h"
#include <typeinfo> // for typeid

using namespace LatticeLib;

TEST(WeightedAverageFilter, initialization) {
    int neighborhoodSize = 6;
    vector<FilterCoefficient<bool> > filterCoefficients;
    for (int coefficientIndex = 0; coefficientIndex < 7; coefficientIndex++) {
        filterCoefficients.push_back(FilterCoefficient<bool>(coefficientIndex - 1, true));
    }
    MaximumValueFinder<double> maxFinder;
    MinimumValueFinder<double> minFinder;
    SequenceFilter<double> maxFilter(filterCoefficients, neighborhoodSize, maxFinder);
    SequenceFilter<double> minFilter(filterCoefficients, neighborhoodSize, minFinder);

    EXPECT_EQ(maxFilter.getNeighborhoodSize(), neighborhoodSize);
    EXPECT_TRUE(maxFilter.getNeighborhoodSize() != neighborhoodSize - 1);
    EXPECT_EQ(typeid(maxFinder), typeid(maxFilter.getIndexPicker()));

    EXPECT_EQ(minFilter.getNeighborhoodSize(), neighborhoodSize);
    EXPECT_TRUE(minFilter.getNeighborhoodSize() != neighborhoodSize - 1);
    EXPECT_EQ(typeid(minFinder), typeid(minFilter.getIndexPicker()));
}
