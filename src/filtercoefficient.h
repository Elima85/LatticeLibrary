#ifndef LATTICELIBRARY_FILTERCOEFFICIENT_H
#define LATTICELIBRARY_FILTERCOEFFICIENT_H

namespace LatticeLib {

/**
 * Coefficient for template filters.
 *
 * Member 		| Comment
 * --------		| --------
 * index		| Position index of the element in a neighborhood. The origin element has index -1.
 * coefficient	| WeightedAverageFilter coefficient for the specified element.
 */
    template<class coefficientTemplate>
    class FilterCoefficient {

    private:
        /** Position index of the element in a neighborhood. The midpoint element has index -1. */
        int positionIndex;

        /** WeightedAverageFilter coefficient for the specified element. */
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
         * Parameter	        | in/out	| Comment
		 * :---------  	        | :-------	| :--------
         * inputPositionIndex   | INPUT     | Position index.
         * inputCoefficient     | INPUT     | Corresponding coefficient value.
         */
        FilterCoefficient(int inputPositionIndex, coefficientTemplate inputCoefficient) {
            positionIndex = inputPositionIndex;
            coefficient = inputCoefficient;
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
         * Parameter            | in/out	| Comment
		 * :----------          | :-------  | :--------
         * inputPositionIndex   | INPUT     | New position index.
         */
        void setPositionIndex(int inputPositionIndex) {
            positionIndex = inputPositionIndex;
        }

        /**
         * Sets coefficient to the input value.
         *
         * Parameter        | in/out    | Comment
		 * :----------      | :-------  | :--------
         * inputCoefficient | INPUT     | New coefficient value.
         */
        void setCoefficient(coefficientTemplate inputCoefficient) {
            coefficient = inputCoefficient;
        }

        /**
         * Sets positionIndex and coefficient to the input values.
         *
         * Parameter	        | in/out	| Comment
		 * :----------          | :-------  | :--------
         * inputPositionIndex   | INPUT     | New position index.
         * inputCoefficient     | INPUT     | New coefficient value.
         */
        void set(int inputPositionIndex, coefficientTemplate inputCoefficient) {
            positionIndex = inputPositionIndex;
            coefficient = inputCoefficient;
        }
    };
}

#endif //LATTICELIBRARY_FILTERCOEFFICIENT_H
