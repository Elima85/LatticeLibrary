#ifndef LATTICELIBRARY_PRIORITYQUEUE_H
#define LATTICELIBRARY_PRIORITYQUEUE_H

#include <cmath>
#include <queue>
#include "defs.h"

namespace LatticeLib {

#define EPSILONPQ 0.0000001

/**
 * Class for a priority queue element.
 *
 * Member 	| Comment
 * :-------	| :-------
 * value    | Value of the element.
 * index    | Element identifier.
 */
    template <class T>
    class PriorityQueueElement{
    private:
        /** Value of the element. */
        T value;

        /** Element identifier.*/
        long index;

    public:
        /**
        * Constructor for empty PriorityQueueElement objects.
        */
        PriorityQueueElement() {
            value = 0.0;
            index = 0;
        }

        /**
         * Constructor for PriorityQueueElement objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * i            | INPUT     | Value of the element.
         * v            | INPUT     | Element identifier.
         */
        PriorityQueueElement(long i, T v) {
            value = v;
            index = i;
        }

        /** Returns value. */
        T getValue() const {
            return value;
        }

        /** Returns index. */
        long getIndex() const {
            return index;
        }

        /**
         * Returns true if the difference in value between the two elements is less than the tolerance specified by EPSILONPQ.
         */
        bool operator== (const PriorityQueueElement& rhs) const {
            return fabs(this->value - rhs.value) < EPSILONPQ;
        }

        /**
         * Returns true if the difference in value between the two elements is greater than the tolerance specified by EPSILONPQ.
         */
        bool operator!= (const PriorityQueueElement& rhs) const {
            return fabs(this->value - rhs.value) > EPSILONPQ;
        }
    };

    /**
    * Class for comparing two PriorityQueueElements.
    */
    class PriorityQueueElementComparison{
    public:
        /**
         * Returns true if the first specified PriorityQueueElement has a larger value than the second one.
         */
        template <class T>
        bool operator() (const PriorityQueueElement<T>& lhs, const PriorityQueueElement<T>&rhs) const{
            return lhs.getValue() > rhs.getValue();
        }
    };

}

// declare queue using "priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue"
#endif
