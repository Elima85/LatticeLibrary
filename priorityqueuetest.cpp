#include "gtest/gtest.h"
#include "priorityqueue.h"
#include "pnorm.h"
#include "defs.h"

using namespace LatticeLib;

TEST(PriorityQueue, Test) {

    double values1[] = {1.1, 2.2, 3.3};
    double values2[] = {4.4, 5.5, 6.6};
    vector<double> vector1(values1, values1 + 3);
    vector<double> vector2(values2, values2 + 3);
    PNorm<double> norm1(1);
    PNorm<double> norm2(2);
    priority_queue<PriorityQueueElement<double>, vector<PriorityQueueElement<double> >, PriorityQueueElementComparison> queue;
    PriorityQueueElement<double> singleElement1(0, 1);
    PriorityQueueElement<double> singleElement2(1, 2);
    PriorityQueueElement<double> singleElement3(1, 2);
    PriorityQueueElement<double> doubleElement1(0, 2 - 1.1);
    PriorityQueueElement<double> doubleElement2(1, 4.1 - 3);
    PriorityQueueElement<double> doubleElement3(1, 4.1 - 3);
    PriorityQueueElement<double> vectorElement1(0, norm1.compute(vector1));
    PriorityQueueElement<double> vectorElement2(1, norm1.compute(vector2));
    PriorityQueueElement<double> vectorElement3(1, norm1.compute(vector2));
    PriorityQueueElement<double> vectorElement4(1, norm2.compute(vector2));

    // == operator
    EXPECT_TRUE(!(singleElement1 == singleElement2));
    EXPECT_TRUE(singleElement2 == singleElement2);
    EXPECT_TRUE(singleElement2 == singleElement3);
    EXPECT_TRUE(!(doubleElement1 == doubleElement2));
    EXPECT_TRUE(doubleElement2 == doubleElement2);
    EXPECT_TRUE(doubleElement2 == doubleElement3);
    EXPECT_TRUE(!(vectorElement1 == vectorElement2));
    EXPECT_TRUE(vectorElement2 == vectorElement2);
    EXPECT_TRUE(vectorElement2 == vectorElement3);
    EXPECT_TRUE(!(vectorElement2 == vectorElement4));

    // != operator
    EXPECT_TRUE(singleElement1 != singleElement2);
    EXPECT_TRUE(!(singleElement2 != singleElement2));
    EXPECT_TRUE(!(singleElement2 != singleElement3));
    EXPECT_TRUE(doubleElement1 != doubleElement2);
    EXPECT_TRUE(!(doubleElement2 != doubleElement2));
    EXPECT_TRUE(!(doubleElement2 != doubleElement3));
    EXPECT_TRUE(vectorElement1 != vectorElement2);
    EXPECT_TRUE(!(vectorElement2 != vectorElement2));
    EXPECT_TRUE(!(vectorElement2 != vectorElement3));
    EXPECT_TRUE(vectorElement2 != vectorElement4);

    // pop order
    queue.push(singleElement1);
    queue.push(singleElement2);
    PriorityQueueElement<double> e1 = queue.top();
    EXPECT_TRUE(e1 == singleElement1);
    queue.pop();
    queue.pop();
    queue.push(singleElement2);
    queue.push(singleElement1);
    e1 = queue.top();
    EXPECT_TRUE(e1 == singleElement1);
    queue.pop();
    queue.pop();

    queue.push(doubleElement1);
    queue.push(doubleElement2);
    e1 = queue.top();
    EXPECT_TRUE(e1 == doubleElement1);
    queue.pop();
    queue.pop();
    queue.push(doubleElement2);
    queue.push(doubleElement1);
    e1 = queue.top();
    EXPECT_TRUE(e1 == doubleElement1);
    queue.pop();
    queue.pop();

    queue.push(vectorElement1);
    queue.push(vectorElement2);
    e1 = queue.top();
    EXPECT_TRUE(e1 == vectorElement1);
    queue.pop();
    queue.pop();
    queue.push(vectorElement2);
    queue.push(vectorElement1);
    e1 = queue.top();
    EXPECT_TRUE(e1 == vectorElement1);
    queue.pop();
    queue.pop();
}

