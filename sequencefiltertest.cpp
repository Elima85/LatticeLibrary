#include "gtest/gtest.h"
#include "defs.h"
#include "filtercoefficient.h"
#include <cmath>
#include "sequencefilter.h"
#include <vector>
#include "cclattice.h"

using namespace LatticeLib;

TEST(WeightedAverageFilter, initialization) {
    int neighborhoodSize = 6;
    SequenceFilter<double> minFilter(sequenceOption::min, neighborhoodSize);
    SequenceFilter<double> maxFilter(sequenceOption::max, neighborhoodSize);
    SequenceFilter<double> medianFilter(sequenceOption::median, neighborhoodSize);
    EXPECT_EQ(minFilter.getNeighborhoodSize(), neighborhoodSize);
    EXPECT_TRUE(minFilter.getNeighborhoodSize() != neighborhoodSize - 1);
}
