#include "gtest/gtest.h"
#include "defs.h"
#include "filtercoefficient.h"
#include <cmath>
#include "weightedaveragefilter.h"
#include <vector>
#include "cclattice.h"

using namespace LatticeLib;

TEST(FilterCoefficient, initialization) {
    // constructor
    int indices[3] = {0,1,2};
    int intCoefficients[3] = {-1,0,2};
    double doubleCoefficients[3] = {-1.1,0.0,2.2};
    bool boolCoefficients[3] = {false,true,false};

    FilterCoefficient<bool> boolEmptyFilterCoefficient;
    FilterCoefficient<int> intEmptyFilterCoefficient;
    FilterCoefficient<double> doubleEmptyCoefficient;
    EXPECT_EQ(boolEmptyFilterCoefficient.getPositionIndex(),0);
    EXPECT_EQ(intEmptyFilterCoefficient.getPositionIndex(),0);
    EXPECT_EQ(doubleEmptyCoefficient.getPositionIndex(),0);
    EXPECT_EQ(boolEmptyFilterCoefficient.getCoefficient(),false);
    EXPECT_EQ(intEmptyFilterCoefficient.getCoefficient(),0);
    EXPECT_NEAR(doubleEmptyCoefficient.getCoefficient(),0.0, EPSILONT);

    vector<FilterCoefficient<bool> > boolFilterCoefficient;
    vector<FilterCoefficient<int> > intFilterCoefficient;
    vector<FilterCoefficient<double> > doubleFilterCoefficient;

    for (int i = 0; i < 3; i++) {
        boolFilterCoefficient.push_back(FilterCoefficient<bool>(indices[i], boolCoefficients[i]));
        intFilterCoefficient.push_back(FilterCoefficient<int>(indices[i], intCoefficients[i]));
        doubleFilterCoefficient.push_back(FilterCoefficient<double>(indices[i], doubleCoefficients[i]));
    }

    // getters
    for (int index = 0; index < 3; index++) {
        string message = "getters, index = ";
        SCOPED_TRACE(message + to_string(index));

        EXPECT_EQ(boolFilterCoefficient[index].getPositionIndex(), indices[index]);
        EXPECT_EQ(boolFilterCoefficient[index].getCoefficient(), boolCoefficients[index]);

        EXPECT_EQ(intFilterCoefficient[index].getPositionIndex(), indices[index]);
        EXPECT_EQ(intFilterCoefficient[index].getCoefficient(), intCoefficients[index]);

        EXPECT_NEAR(doubleFilterCoefficient[index].getCoefficient(), doubleCoefficients[index], EPSILONT);
        EXPECT_EQ(doubleFilterCoefficient[index].getPositionIndex(), indices[index]);
    }

    // setters
    int ind2[3] = {1,2,3};
    int ci2[3] = {-2,1,0};
    double cd2[3] = {0.0,2.2,1.1};
    bool cb2[3] = {true,false,true};

    for (int i = 0; i < 3; i++) {
        boolFilterCoefficient[i].setPositionIndex(ind2[i]);
        intFilterCoefficient[i].setPositionIndex(ind2[i]);
        doubleFilterCoefficient[i].setPositionIndex(ind2[i]);

        boolFilterCoefficient[i].setCoefficient(cb2[i]);
        intFilterCoefficient[i].setCoefficient(ci2[i]);
        doubleFilterCoefficient[i].setCoefficient(cd2[i]);
    }
    for (int index = 0; index < 3; index++) {
        string message = "single setters, index = ";
        SCOPED_TRACE(message + to_string(index));

        EXPECT_TRUE(boolFilterCoefficient[index].getPositionIndex() != indices[index]);
        EXPECT_EQ(boolFilterCoefficient[index].getPositionIndex(), ind2[index]);
        EXPECT_EQ(boolFilterCoefficient[index].getCoefficient(), cb2[index]);
        EXPECT_TRUE(boolFilterCoefficient[index].getCoefficient() != boolCoefficients[index]);

        EXPECT_TRUE(intFilterCoefficient[index].getPositionIndex() != indices[index]);
        EXPECT_EQ(intFilterCoefficient[index].getPositionIndex(), ind2[index]);
        EXPECT_EQ(intFilterCoefficient[index].getCoefficient(), ci2[index]);
        EXPECT_TRUE(intFilterCoefficient[index].getCoefficient() != intCoefficients[index]);

        EXPECT_TRUE(doubleFilterCoefficient[index].getPositionIndex() != indices[index]);
        EXPECT_EQ(doubleFilterCoefficient[index].getPositionIndex(), ind2[index]);
        EXPECT_NEAR(doubleFilterCoefficient[index].getCoefficient(), cd2[index], EPSILONT);
        EXPECT_TRUE(fabs(doubleFilterCoefficient[index].getCoefficient() - doubleCoefficients[index]) > EPSILONT);
    }

    for (int i = 0; i < 3; i++) {
        boolFilterCoefficient[i].set(indices[i], boolCoefficients[i]);
        intFilterCoefficient[i].set(indices[i], intCoefficients[i]);
        doubleFilterCoefficient[i].set(indices[i], doubleCoefficients[i]);
    }
    for (int index = 0; index < 3; index++) {
        string message = "combined setter, index = ";
        SCOPED_TRACE(message + to_string(index));

        EXPECT_EQ(boolFilterCoefficient[index].getPositionIndex(), indices[index]);
        EXPECT_EQ(intFilterCoefficient[index].getPositionIndex(), indices[index]);
        EXPECT_EQ(doubleFilterCoefficient[index].getPositionIndex(), indices[index]);

        EXPECT_EQ(boolFilterCoefficient[index].getCoefficient(), boolCoefficients[index]);
        EXPECT_EQ(intFilterCoefficient[index].getCoefficient(), intCoefficients[index]);
        EXPECT_NEAR(doubleFilterCoefficient[index].getCoefficient(), doubleCoefficients[index], EPSILONT);
    }
}

TEST(WeightedAverageFilter, initialization) {

    int positionIndices[4] = {-1,0,1,3};
    double coefficientValues[4] = {2.2,0,-1.1,16.16};
    int neighborhoodSize = 6;
    vector<FilterCoefficient<double> > filterCoefficients;
    for (int i = 0; i < 4; i++) {
        filterCoefficients.push_back(FilterCoefficient<double>(positionIndices[i], coefficientValues[i]));
    }
    WeightedAverageFilter<double> filter(filterCoefficients, neighborhoodSize);

    // getters
    for (int index = 0; index < 3; index++) {
        string message = "getCoefficients, index = ";
        SCOPED_TRACE(message + to_string(index));

        vector<FilterCoefficient<double> > extractedFilterCoefficients = filter.getCoefficients();
        EXPECT_EQ(extractedFilterCoefficients[index].getPositionIndex(), filterCoefficients[index].getPositionIndex());
        EXPECT_NEAR(extractedFilterCoefficients[index].getCoefficient(), filterCoefficients[index].getCoefficient(), EPSILONT);
    }

    for (int index = 0; index < 3; index++) {
        string message = "getCoefficient, index = ";
        SCOPED_TRACE(message + to_string(index));

        FilterCoefficient<double> c = filter.getCoefficient(index);
        EXPECT_EQ(c.getPositionIndex(), filterCoefficients[index].getPositionIndex());
        EXPECT_NEAR(c.getCoefficient(), filterCoefficients[index].getCoefficient(), EPSILONT);
    }

    EXPECT_EQ(filter.getNeighborhoodSize(), neighborhoodSize);
    EXPECT_TRUE(filter.getNeighborhoodSize() != neighborhoodSize - 1);
    EXPECT_EQ(filter.getNCoefficients(),4);
    EXPECT_TRUE(filter.getNCoefficients() != 5);

    EXPECT_EQ(filter.findCoefficient(-1),0);
    EXPECT_EQ(filter.findCoefficient(1),2);
    EXPECT_EQ(filter.findCoefficient(2),-1);
}

TEST(WeightedAverageFilter, application) {

    int nRows = 5, nColumns = 5, nLayers = 1;
    double density = 1.0;
    CCLattice lattice(nRows, nColumns, nLayers, density);
    int nBands = 3;
    double doubleIntensities[75] =     {0, 1, 0, 1, 0,
                                        1, 0, 1, 0, 1,
                                        0, 1, 0, 1, 0,
                                        1, 0, 1, 0, 1,
                                        0, 1, 0, 1, 0,

                                        0, 1, 0, 1, 0,
                                        0, 1, 0, 1, 0,
                                        0, 1, 0, 1, 0,
                                        0, 1, 0, 1, 0,
                                        0, 1, 0, 1, 0,

                                        1, 1, 1, 1, 1,
                                        1, 1, 1, 1, 1,
                                        1, 1, 1, 1, 1,
                                        1, 1, 1, 1, 1,
                                        1, 1, 1, 1, 1};
    Image<double> image(doubleIntensities, lattice, nBands);

    vector<FilterCoefficient<double> > coefficients1;
    coefficients1.push_back(FilterCoefficient<double>(-1, 1));
    coefficients1.push_back(FilterCoefficient<double>(0, 1));
    coefficients1.push_back(FilterCoefficient<double>(1, 1));
    coefficients1.push_back(FilterCoefficient<double>(2, 1));
    coefficients1.push_back(FilterCoefficient<double>(3, 1));
    coefficients1.push_back(FilterCoefficient<double>(4, 1));
    coefficients1.push_back(FilterCoefficient<double>(5, 1));
    WeightedAverageFilter<double> filter1(coefficients1, 6);
    double result[75];
    filter1.applyToImage(image, result);
    int bandIndex = 0;
    for (int rowIndex = 1; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 1; columnIndex < 3; columnIndex++) {
            int elementIndex = 25 * bandIndex + 5 * rowIndex + columnIndex;
            string message = "filter1, index = ";
            SCOPED_TRACE(message + to_string(elementIndex));
            if (IS_EVEN(elementIndex)) {
                EXPECT_NEAR(result[elementIndex], 4.0 / 5.0, EPSILONT);
            }
            else {
                EXPECT_NEAR(result[elementIndex], 1.0 / 5.0, EPSILONT);
            }
        }
    }
    bandIndex = 1;
    for (int rowIndex = 1; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 1; columnIndex < 3; columnIndex++) {
            int elementIndex = 25 * bandIndex + 5 * rowIndex + columnIndex;
            string message = "filter1, index = ";
            SCOPED_TRACE(message + to_string(elementIndex));
            if (IS_EVEN(columnIndex)) {
                EXPECT_NEAR(result[elementIndex], 2.0 / 5.0, EPSILONT);
            }
            else {
                EXPECT_NEAR(result[elementIndex], 3.0 / 5.0, EPSILONT);
            }
        }
    }
    bandIndex = 2;
    for (int rowIndex = 1; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 1; columnIndex < 3; columnIndex++) {
            int elementIndex = 25 * bandIndex + 5 * rowIndex + columnIndex;
            string message = "filter1, index = ";
            SCOPED_TRACE(message + to_string(elementIndex));
            EXPECT_NEAR(result[elementIndex], 1.0, EPSILONT);
        }
    }

    vector<FilterCoefficient<double> > coefficients2;
    coefficients2.push_back(FilterCoefficient<double>(-1, 0));
    coefficients2.push_back(FilterCoefficient<double>(0, 1));
    coefficients2.push_back(FilterCoefficient<double>(1, 1));
    coefficients2.push_back(FilterCoefficient<double>(2, 1));
    coefficients2.push_back(FilterCoefficient<double>(3, 1));
    coefficients2.push_back(FilterCoefficient<double>(4, 1));
    coefficients2.push_back(FilterCoefficient<double>(5, 1));
    coefficients2.push_back(FilterCoefficient<double>(6, 0));
    coefficients2.push_back(FilterCoefficient<double>(7, 0));
    coefficients2.push_back(FilterCoefficient<double>(8, 0));
    coefficients2.push_back(FilterCoefficient<double>(9, 0));
    coefficients2.push_back(FilterCoefficient<double>(10, 0));
    coefficients2.push_back(FilterCoefficient<double>(11, 0));
    coefficients2.push_back(FilterCoefficient<double>(12, 0));
    coefficients2.push_back(FilterCoefficient<double>(13, 0));
    coefficients2.push_back(FilterCoefficient<double>(14, 0));
    coefficients2.push_back(FilterCoefficient<double>(15, 0));
    coefficients2.push_back(FilterCoefficient<double>(16, 0));
    coefficients2.push_back(FilterCoefficient<double>(17, 0));
    WeightedAverageFilter<double> filter2(coefficients2, 18);
    filter2.applyToImage(image, result);
    bandIndex = 0;
    for (int rowIndex = 1; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 1; columnIndex < 3; columnIndex++) {
            int elementIndex = 25 * bandIndex + 5 * rowIndex + columnIndex;
            string message = "filter2, index = ";
            SCOPED_TRACE(message + to_string(elementIndex));
            EXPECT_NEAR(result[elementIndex], IS_EVEN(elementIndex), EPSILONT);
        }
    }
    bandIndex = 1;
    for (int rowIndex = 1; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 1; columnIndex < 3; columnIndex++) {
            int elementIndex = 25 * bandIndex + 5 * rowIndex + columnIndex;
            string message = "filter2, index = ";
            SCOPED_TRACE(message + to_string(elementIndex));
            EXPECT_NEAR(result[elementIndex], 2.0 / 4.0, EPSILONT);
        }
    }
    bandIndex = 2;
    for (int rowIndex = 1; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 1; columnIndex < 3; columnIndex++) {
            int elementIndex = 25 * bandIndex + 5 * rowIndex + columnIndex;
            string message = "filter2, index = ";
            SCOPED_TRACE(message + to_string(elementIndex));
            EXPECT_NEAR(result[elementIndex], 1.0, EPSILONT);
        }
    }


    vector<FilterCoefficient<double> > coefficients3;
    coefficients3.push_back(FilterCoefficient<double>(-1, 1));
    coefficients3.push_back(FilterCoefficient<double>(0, 1));
    coefficients3.push_back(FilterCoefficient<double>(1, 1));
    coefficients3.push_back(FilterCoefficient<double>(2, 1));
    coefficients3.push_back(FilterCoefficient<double>(3, 1));
    coefficients3.push_back(FilterCoefficient<double>(4, 1));
    coefficients3.push_back(FilterCoefficient<double>(5, 1));
    coefficients3.push_back(FilterCoefficient<double>(6, 1));
    coefficients3.push_back(FilterCoefficient<double>(7, 1));
    coefficients3.push_back(FilterCoefficient<double>(8, 1));
    coefficients3.push_back(FilterCoefficient<double>(9, 1));
    coefficients3.push_back(FilterCoefficient<double>(10, 1));
    coefficients3.push_back(FilterCoefficient<double>(11, 1));
    coefficients3.push_back(FilterCoefficient<double>(12, 1));
    coefficients3.push_back(FilterCoefficient<double>(13, 1));
    coefficients3.push_back(FilterCoefficient<double>(14, 1));
    coefficients3.push_back(FilterCoefficient<double>(15, 1));
    coefficients3.push_back(FilterCoefficient<double>(16, 1));
    coefficients3.push_back(FilterCoefficient<double>(17, 1));
    WeightedAverageFilter<double> filter3(coefficients3, 18);
    filter3.applyToImage(image, result);
    bandIndex = 0;
    for (int rowIndex = 1; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 1; columnIndex < 3; columnIndex++) {
            int elementIndex = 25 * bandIndex + 5 * rowIndex + columnIndex;
            string message = "filter3, index = ";
            SCOPED_TRACE(message + to_string(elementIndex));
            if (IS_EVEN(elementIndex)) {
                EXPECT_NEAR(result[elementIndex], 4.0 / 9.0, EPSILONT);
            }
            else {
                EXPECT_NEAR(result[elementIndex], 5.0 / 9.0, EPSILONT);
            }
        }
    }
    bandIndex = 1;
    for (int rowIndex = 1; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 1; columnIndex < 3; columnIndex++) {
            int elementIndex = 25 * bandIndex + 5 * rowIndex + columnIndex;
            string message = "filter3, index = ";
            SCOPED_TRACE(message + to_string(elementIndex));
            if (IS_EVEN(columnIndex)) {
                EXPECT_NEAR(result[elementIndex], 6.0 / 9.0, EPSILONT);
            }
            else {
                EXPECT_NEAR(result[elementIndex], 3.0 / 9.0, EPSILONT);
            }
        }
    }
    bandIndex = 2;
    for (int rowIndex = 1; rowIndex < 3; rowIndex++) {
        for (int columnIndex = 1; columnIndex < 3; columnIndex++) {
            int elementIndex = 25 * bandIndex + 5 * rowIndex + columnIndex;
            string message = "filter3, index = ";
            SCOPED_TRACE(message + to_string(elementIndex));
            EXPECT_NEAR(result[elementIndex], 1.0, EPSILONT);
        }
    }


}