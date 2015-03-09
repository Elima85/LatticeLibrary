#ifndef NEIGHBOR_H
#define NEIGHBOR_H

namespace LatticeLib {

/**
 * Class for handling different types of spel neighbors.
 */
class Neighbor {
private:
	/** Location relative to the middle spel. */
	int positionIndex;

	/** Index of the neighbor in the image data array. */
	int imageIndex;

public:
	Neighbor(int l, int i);
	~Neighbor();

	/** Returns positionIndex, indicating the position of the neighbor relative to the middle spel. */
	int getPosition() const;

	/** Returns imageIndex, the index of the middle spel in the image data array. */
	int getIndex() const;
};

}

#endif
