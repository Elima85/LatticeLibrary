#ifndef NEIGHBORTEST
#define NEIGHBORTEST

#include "gtest/gtest.h"
#include "neighbor.h"
#include "defs.h"

using namespace LatticeLib;

TEST(Neighbor, Neighbor) {

    int location1 = 0;
    int location2 = 1;
    int index1 = 1;
    int index2 = 2;
    //double distance1 = 0.1;
    //double distance2 = 0.2;

    Neighbor n1 = Neighbor(location1, index1); //, distance1);
    Neighbor n2 = Neighbor(location2, index2); //, distance2);

    // constructor and getters
    EXPECT_EQ(n1.getPosition(), location1);
    EXPECT_EQ(n1.getIndex(), index1);
    EXPECT_NE(n1.getPosition(), location2);
    EXPECT_NE(n1.getIndex(), index2);

    EXPECT_EQ(n2.getPosition(), location2);
    EXPECT_EQ(n2.getIndex(), index2);
    EXPECT_NE(n2.getPosition(), location1);
    EXPECT_NE(n2.getIndex(), index1);

    // setter
//	n1.set(index2, distance2);
//	EXPECT_TRUE(n1.getIndex() == index2);
//	EXPECT_TRUE(n1.getIndex() != index1);
}

#endif