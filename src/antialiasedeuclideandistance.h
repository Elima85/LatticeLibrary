#ifndef LATTICELIBRARY_AAEDISTANCETRANSFORM_H
#define LATTICELIBRARY_AAEDISTANCETRANSFORM_H

#include "distancemeasure.h"
#include "image.h"
#include "intensityworkset.h"
#include "priorityqueue.h"
#include "pnorm.h"
#include <vector>
#include <cfloat> // DBL_MAX
#include "distancetovoronoicellcenter.h"

namespace LatticeLib {

	/**
	 * Anti-Aliased Euclidean distance
	 * ================================
	 * Computes the Euclidean distance from the background voxel centers to image objects, the borders of which are
	 * approximated from the element intensity, interpreted as the element coverage value.
	 *
	 * minIntensity is interpreted as 100% background, maxIntensity is interpreted as 100% object, and values in
	 * between as part background and object. Each modality band represents one class of objects.
	 *
	 * References
	 * -----------
	 * [Gustavson and Strand 2011] (http://www.sciencedirect.com/science/article/pii/S0167865510002953)<br>
	 * [Linnér and Strand 2014] (http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=6976896&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D6976896)
	 */
	template<class T>
	class AntiAliasedEuclideanDistance : public DistanceMeasure<T> { // TODO: Test!

	private:
		/** Index of the closest edge element to each spatial element in the image. */
		int* originalRoots;

	public:

		AntiAliasedEuclideanDistance() : DistanceMeasure<T>() {
			originalRoots = NULL;
		}

		~AntiAliasedEuclideanDistance() {}

		/**
		 * Overloads DistanceMeasure::setup().
		 */
		void setup(IntensityWorkset<T> &input) {
			originalRoots = new int[input.getImage().getNElements()];
		}

		/**
		 * Overloads DistanceMeasure::initialize().
		 */
		void initialize(const IntensityWorkset<T> &input, int bandIndex, int neighborhoodSize,
						Image<double> &distanceTransform, Image<int> &roots, vector<PriorityQueueElement<T> > &toQueue) {
			toQueue.clear();
			T minIntensity = input.getMinIntensity();
			T maxIntensity = input.getMaxIntensity();
			T intensityRange = maxIntensity - minIntensity;
			Image<T> image = input.getImage();
			int nElements = image.getNElements();
			DistanceToVoronoiCellCenter subElementDistance;
			for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
				if (image(elementIndex, bandIndex) > 0) {
					if (image(elementIndex, bandIndex) == 1) { // object element
						roots.setElement(elementIndex, bandIndex) = elementIndex;
						originalRoots[elementIndex] = elementIndex;
						distanceTransform.setElement(elementIndex, bandIndex) = 0.0;
						// Put neighbors of edge voxels on queue.
						vector<Neighbor> neighbors;
						image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
						bool closeToEdge = false;
						for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
							if (image(neighbors[neighborIndex].getIndex(), bandIndex) != 1) {
								closeToEdge = true;
							}
						}
						if (closeToEdge) {
							toQueue.push_back(PriorityQueueElement<T>(elementIndex, 0));
						}
					}
					else { // edge element
						roots.setElement(elementIndex, bandIndex) = elementIndex;
						originalRoots[elementIndex] = elementIndex;
						double coverage = (image(elementIndex, bandIndex) - minIntensity)/ intensityRange;
						distanceTransform.setElement(elementIndex, bandIndex) = subElementDistance.compute(input, elementIndex, bandIndex);
						toQueue.push_back(PriorityQueueElement<T>(elementIndex, distanceTransform(elementIndex, bandIndex)));
					}
				}
				else { // background element
					distanceTransform(elementIndex, bandIndex) = DBL_MAX;
					originalRoots[elementIndex] = -1;
					roots(elementIndex, bandIndex) = -1;
				}
			}
		}

		/**
		 * Overloads DistanceMeasure::update().
		 */
		void update(const IntensityWorkset<T> &input, int bandIndex, int neighborhoodSize, int elementIndex,
					Image<double> &distanceTransform, Image<int> &roots,
					vector<PriorityQueueElement<T> > &toQueue) {
			toQueue.clear();
			vector<Neighbor> neighbors;
			input.getImage().getNeighbors(elementIndex, neighborhoodSize, neighbors);
			int nNeighbors = neighbors.size();
			for (int neighborIndex = 0; neighborIndex < nNeighbors; neighborIndex++) {
				int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
				double distance = input.getImage().euclideanDistance(elementIndex, neighborGlobalIndex) + distanceTransform(originalRoots[elementIndex],bandIndex);
				if (distanceTransform(neighborGlobalIndex, labelIndex) - distance > DBL_EPSILON) {
					distanceTransform.setElement(neighborGlobalIndex, bandIndex, distance);
					roots.setElement(neighborGlobalIndex, bandIndex, elementIndex);
					originalRoots[neighborGlobalIndex] = originalRoots[elementIndex];
					toQueue.push_back(PriorityQueueElement<T>(neighborGlobalIndex, distance));
				}
			}
		}

		/**
		 * Overloads DistanceMeasure::clear().
		 */
		void clear() {
			delete originalRoots;
		}
	};

#endif
