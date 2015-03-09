#ifndef SEED_H
#define SEED_H

namespace LatticeLib {

    /**
    * Class for segmentation seeds.
    */
    class Seed {
    private:
        /** Index of the seed spel in the image data array. */
        int index;

        /** Label for the seeded region. */
        int label;

    public:
        Seed(int i, int l);
        ~Seed();

        /** Returns the index of the seed spel. */
        int getIndex() const;

        /** Returns the label of the seed spel. */
        int getLabel() const;
    };
}

#endif