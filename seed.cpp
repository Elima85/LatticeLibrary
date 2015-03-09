#include "seed.h"

namespace LatticeLib {
    Seed::Seed(int i, int l) {
        index = i;
        label = l;
    }
    Seed::~Seed() {}
    int Seed::getIndex() const {
        return index;
    }
    int Seed::getLabel() const {
        return label;
    }
}