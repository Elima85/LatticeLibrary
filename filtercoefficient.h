#ifndef FILTERCOEFFICIENT_H
#define FILTERCOEFFICIENT_H

namespace LatticeLib {

/**
 * Coefficient for template filters.
 *
 * Member 		| Comment
 * --------		| --------
 * index		| Position index of the element in a neighborhood. The midpoint element has index -1.
 * coefficient	| %Filter coefficient for the specified element.
 */
    template<class S>
    class FilterCoefficient {

    private:
        /** Position index of the element in a neighborhood. The midpoint element has index -1. */
        int positionIndex;

        /** %Filter coefficient for the specified element. */
        S coefficient;

    public:
        /**
         * Default constructor for FilterCoefficient objects.
         */
        FilterCoefficient() {
            positionIndex = 0;
            coefficient = 0;
        }

        /**
         * Constructor for FilterCoefficient objects.
         *
         * Parameter	| in/out	| Comment
		 * :---------  	| :-------	| :--------
         * i            | INPUT     | Position index.
         * c            | INPUT     | Corresponding coefficient value.
         */
        FilterCoefficient(int i, S c) {
            positionIndex = i;
            coefficient = c;
        }

        /**
         * Returns positionIndex.
         */
        double getIndex() const {
            return positionIndex;
        }

        /**
         * Returns coefficient.
         */
        S getCoefficient() const {
            return coefficient;
        }

        /**
         * Sets positionIndex to the input value.
         *
         * Parameter    | in/out	| Comment
		 * :----------  | :-------  | :--------
         * i            | INPUT     | New position index.
         */
        void setPositionIndex(int i) {
            positionIndex = i;
        }

        /**
         * Sets coefficient to the input value.
         *
         * Parameter    | in/out    | Comment
		 * :----------  | :-------  | :--------
         * c            | INPUT     | New coefficient value.
         */
        void setCoefficient(S c) {
            coefficient = c;
        }

        /**
         * Sets positionIndex and coefficient to the input values.
         *
         * Parameter	| in/out	| Comment
		 * :----------  | :-------  | :--------
         * i            | INPUT     | New position index.
         * c            | INPUT     | New coefficient value.
         */
        void set(int i, S c) {
            positionIndex = i;
            coefficient = c;
        }
    };
}

#endif //FILTERCOEFFICIENT_H
