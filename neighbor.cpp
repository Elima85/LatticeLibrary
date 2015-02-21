#include "neighbor.h"

namespace CImage {
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