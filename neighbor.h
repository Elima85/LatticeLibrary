#ifndef NEIGHBOR_H
#define NEIGHBOR_H

namespace LatticeLib {

	// TODO: Neighborhood class? Would facilitate padding.

/**
 * Class for representing neighbors of lattice elements.
 *
 * Member			| Comment
 * :-------			| :-------
 * positionIndex	| Location relative to the middle spel.
 * elementIndex		| Global index of the element.
 */
	class Neighbor {
	private:
		/** Location relative to the middle spel. */
		int positionIndex;

		/** Global index of the element. */
		int elementIndex;

	public:
		/**
         * Constructor for Neighbor objects.
         *
         * Parameter    | in/out	| Comment
         * :----------  | :-------	| :--------
         * position		| INPUT		| Location relative to the middle spel.
         * index		| INPUT		| Global index of the element.
         */
		Neighbor(int position, int index);

		/**
         * Destructor for Neighbor objects.
         */
		~Neighbor();

		/** Returns positionIndex. */
		int getPosition() const;

		/** Returns elementIndex. */
		int getIndex() const;
	};

}

#endif
