/*
 * typedef of a priority queue suited for our needs, borrowed from Filip Malm. Should be changed to using templates or type aliases or something, to match the CImage class.
 *
 * If there are several elements with the same priority value, FIFO is applied.
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <math.h>
#include <queue>
#include <vector>
#include "norm.h"
#include "defs.h"
using namespace std;

namespace CImage {

#define EPSILONPQ 0.0000001

/**
* Queue element containing one value.
*/
    template <class T>
    class PriorityQueueElement{
    private:
        /** element value */
        T value;

        /** element identifier*/
        long index;

    public:
        /**
        * Empty element
        */
        PriorityQueueElement() {
            value = 0.0;
            index = 0;
        }

        /**
        * Sets value to input value.
        */
        PriorityQueueElement(
                long i, T v) {
            value = v;
            index = i;
        }

        /**
        * Sets value to the input norm of the input vector.
        */
        PriorityQueueElement(long i, const vector<T> &v,
                const Norm *n) {
            value = n->compute(v);
            index = i;
        }

        T getValue()
        const {
            return value;
        }

        long

        getIndex() const {
            return index;
        }

        bool

        operator== (const
        PriorityQueueElement& rhs)
        const {
            return fabs(this->value - rhs.value) < EPSILONPQ;
        }

        bool operator!= (const PriorityQueueElement& rhs)

        const {
            return fabs(this->value - rhs.value) > EPSILONPQ;
        }
    };

    /**
    * Comparison of two queue elements.
    */
    class
    PriorityQueueElementComparison{
    public:
        template <class T>
        bool operator() (const
        PriorityQueueElement<T>& lhs, const
        PriorityQueueElement<T>&rhs) const{
            return lhs.getValue() > rhs.getValue();
        }
    };

}

// declare queue using "priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue"
// TODO: look into type aliases or something, to make some kind of typedef. This declaration is way too long. Maybe a wrapper class PriorityQueue<T> containing a private object queue?

#endif
