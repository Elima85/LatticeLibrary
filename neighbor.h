#ifndef NEIGHBOR_H
#define NEIGHBOR_H

namespace CImage {

/**
 * Class for handling different types of spel neighbors.
 */
class Neighbor {
private:
	/** Location relative to the middle spel. */
	int position;

	/** Index of the neighbor in the image data array. */
	int index;

public:
	Neighbor(int l, int i) {//, double d) {
		position = l;
		index = i;
		//distance = d; // not good for maintainability
	}

	int getPosition() const {
		return position;
	}

	int getIndex() const {
		return index;
	}
};

}

#endif
