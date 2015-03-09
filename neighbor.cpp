#include "neighbor.h"

namespace LatticeLib {
    Neighbor::Neighbor(int l, int i) {
        positionIndex = l;
        imageIndex = i;
    }
    Neighbor::~Neighbor() {}
    int Neighbor::getPosition() const {
        return positionIndex;
    }
    int Neighbor::getIndex() const {
        return imageIndex;
    }
}