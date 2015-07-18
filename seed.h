#ifndef SEED_H
#define SEED_H

namespace LatticeLib {

    /**
     * Class for seeds for application of SeededDistanceTransform.
     *
     * Member 		| Comment
     * :-------		| :-------
     * elementIndex | Index of the seed spel in the image data array.
     * label        | Label for the seeded region.
     */
    class Seed {
    private:
        /** Index of the seed spel in the image data array. */
        int elementIndex;

        /** Label for the seeded region. */
        int label;

    public:
        /**
         * Constructor for Seed objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * i            | INPUT     | Index of the seed spel in the image data array.
         * l            | INPUT     | Label for the seeded region.
         */
        Seed(int i, int l);
        ~Seed();

        /** Returns the index of the seed spel. */ // TODO: Rename to getElementIndex()
        int getIndex() const;

        /** Returns the label of the seed spel. */
        int getLabel() const;
    };
}

#endif