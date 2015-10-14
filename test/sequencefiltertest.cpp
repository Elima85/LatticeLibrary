#include "gtest/gtest.h"
#include "../src/defs.h"
#include "../src/filtercoefficient.h"
#include <cmath>
#include "../src/sequencefilter.h"
#include "../src/maximumvaluefinder.h"
#include "../src/minimumvaluefinder.h"
#include "../src/medianvaluefinder.h"
#include <vector>
#include "../src/cclattice.h"
#include <typeinfo> // for typeid

using namespace LatticeLib;

TEST(SequenceFilter, initialization) {
    int neighborhoodSize = 6;
    vector<FilterCoefficient<bool> > filterCoefficients;
    for (int coefficientIndex = 0; coefficientIndex < 7; coefficientIndex++) {
        filterCoefficients.push_back(FilterCoefficient<bool>(coefficientIndex - 1, true));
    }
    MaximumValueFinder<double> maxFinder;
    MinimumValueFinder<double> minFinder;
    MedianValueFinder<double> medianFinder;
    SequenceFilter<double> maxFilter(filterCoefficients, neighborhoodSize, maxFinder);
    SequenceFilter<double> minFilter(filterCoefficients, neighborhoodSize, minFinder);
    SequenceFilter<double> medianFilter(filterCoefficients, neighborhoodSize, medianFinder);

    EXPECT_EQ(maxFilter.getNeighborhoodSize(), neighborhoodSize);
    EXPECT_TRUE(maxFilter.getNeighborhoodSize() != neighborhoodSize - 1);
    EXPECT_EQ(typeid(maxFinder), typeid(maxFilter.getIndexPicker()));

    EXPECT_EQ(minFilter.getNeighborhoodSize(), neighborhoodSize);
    EXPECT_TRUE(minFilter.getNeighborhoodSize() != neighborhoodSize - 1);
    EXPECT_EQ(typeid(minFinder), typeid(minFilter.getIndexPicker()));

    EXPECT_EQ(medianFilter.getNeighborhoodSize(), neighborhoodSize);
    EXPECT_TRUE(medianFilter.getNeighborhoodSize() != neighborhoodSize - 1);
    EXPECT_EQ(typeid(medianFinder), typeid(medianFilter.getIndexPicker()));
}
