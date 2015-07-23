#include "seed.h"

namespace LatticeLib {
    Seed::Seed(int i, int l) {
        elementIndex = i;
        label = l;
    }
    Seed::~Seed() {}
    int Seed::getElementIndex() const {
        return elementIndex;
    }
    int Seed::getLabel() const {
        return label;
    }
}