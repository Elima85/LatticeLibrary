#ifndef FILTERCOEFFICIENT_H
#define FILTERCOEFFICIENT_H

namespace LatticeLib {

/**
 * Filter coefficient for template filters.
 *
 * Member 		| Comment
 * --------		| --------
 * index		| index of the corresponding neighbor (-1 for midpoint?)
 * coefficient	| filter coefficient for this neighbor
 *
 */
    template<class S>
    class FilterCoefficient {

    private:
        /** index of the corresponding neighbor */
        int positionIndex;

        /** filter coefficient for this neighbor */
        S coefficient;

    public:
        FilterCoefficient(int i, S f) {
            index = i;
            factor = f;
        }

        FilterCoefficient() {
            index = 0;
            factor = 0;
        }

        double getIndex() const {
            return positionIndex;
        }

        S getCoefficient() const {
            return coefficient;
        }

        void setIndex(int i) {
            positionIndex = i;
        }

        void setCoefficient(S c) {
            coefficient = c;
        }

        void set(int i, S c) {
            positionIndex = i;
            coefficient = c;
        }
    };
}

#endif //FILTERCOEFFICIENT_H
