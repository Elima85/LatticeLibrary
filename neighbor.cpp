#include "neighbor.h"

namespace LatticeLib {
    Neighbor::Neighbor(int position, int index) {
        positionIndex = position;
        elementIndex = index;
    }
    Neighbor::~Neighbor() {}
    int Neighbor::getPosition() const {
        return positionIndex;
    }
    int Neighbor::getIndex() const {
        return elementIndex;
    }
}