#ifndef FILTERCOEFFICIENT_H
#define FILTERCOEFFICIENT_H

namespace LatticeLib {

/**
 * Coefficient for template filters.
 *
 * Member 		| Comment
 * --------		| --------
 * index		| Position index of the element in a neighborhood. The origin element has index -1.
 * coefficient	| %WeightedAverageFilter coefficient for the specified element.
 */
    template<class coefficientTemplate>
    class FilterCoefficient {

    private:
        /** Position index of the element in a neighborhood. The midpoint element has index -1. */
        int positionIndex;

        /** %WeightedAverageFilter coefficient for the specified element. */
        coefficientTemplate coefficient;

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
        FilterCoefficient(int i, coefficientTemplate c) {
            positionIndex = i;
            coefficient = c;
        }

        /**
         * Returns positionIndex.
         */
        double getPositionIndex() const {
            return positionIndex;
        }

        /**
         * Returns coefficient.
         */
        coefficientTemplate getCoefficient() const {
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
        void setCoefficient(coefficientTemplate c) {
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
        void set(int i, coefficientTemplate c) {
            positionIndex = i;
            coefficient = c;
        }
    };
}

#endif //FILTERCOEFFICIENT_H
