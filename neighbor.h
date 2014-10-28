#ifndef NEIGHBOR_H
#define NEIGHBOR_H

namespace CImage {

/**
 * Class for handling different types of spel neighbors.
 */
class Neighbor {
private:
	/** Location relative to the middle spel. */
	int location;

	/** Index of the neighbor in the image data array. */
	int index;

	/** Euclidean distance to this neighbor. */
	double distance;

public:
	Neighbor(int l, int i) {//, double d) {
		location = l;
		index = i;
		//distance = d; // not good for maintainability
	}

	int getLocation() const {
		return location;
	}

	int getIndex() const {
		return index;
	}

//	double getDistance() const {
//		return distance;
//	}

//	void set(int i, double d) {
//		index = i;
//		distance = d;
//	}
};

}

#endif
