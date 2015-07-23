#ifndef AAEDISTANCETRANSFORM_H
#define AAEDISTANCETRANSFORM_H

#include "distancemeasure.h"
#include "image.h"
#include "intensityworkset.h"
#include "priorityqueue.h"
#include "pnorm.h"
#include <vector>
#include <cfloat> // DBL_MAX

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
	class AntiAliasedEuclideanDistance : public DistanceMeasure<T> { // TODO: Implement Lattice::coverageToInternalDistance()! Test!

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
			for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
				if (image(elementIndex, bandIndex) > 0) {
					if (image(elementIndex, bandIndex) == 1) {// object element
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
						distanceTransform.setElement(elementIndex, bandIndex) = image.getLattice().coverageToInternalDistance(coverage);
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
				if (distance < distanceTransform(neighborGlobalIndex, labelIndex)) {
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

/*	template <class T>
	void antiAliasedEuclideanDistanceTransform(const CImage<T> *image, int nNeighbors, double* distanceTransform) {

		if (!distanceTransform || !image) {
			throw nullPointerException();
		}

		int nElements = image->getNElements();
		int nBands = image->getNBands();
		bool* inQueue = new bool[nElements];
		double* subSpelDistance = new double[nElements]; // distance within the nearest edge voxel
		vector<double>* distanceVector = new vector<double>[nElements]; // Would it be faster to propagate the indices of the edge spels and compute the distance from that?
		int* closestObjectSpel = new int[nElements];
		if ((!inQueue) || (!subSpelDistance) || (!distanceVector)){
			throw allocationException();
		}

		priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
		vector<Neighbor> neighbors;
		PNorm norm = PNorm(2);
		int start;

		// Consider each band as a separate segmentation
		for(int b = 0; b < nBands; b++) {
			start = b * nElements;

			// initialization
			for(int i = 0; i < nElements; i++){
				if((*image)(i,b) > 0){
					if ((*image)(i,b) == 1) {
						// Completely inside of the object, does not need to be processed further.
						distanceVector[i] = vector<double>(3,0.0);
						closestObjectSpel[i] = i;
						distanceTransform[start + i] = 0;
						subSpelDistance[i] = 0;
						inQueue[i] = false;
						// Put neighbors of border voxels on queue.
						image->getNeighbors(i,nNeighbors,neighbors);
						for(int j = 0; j < neighbors.size(); j++){
							if ((*image)[neighbors[j].getIndex()][b] != 1) {
								inQueue[i] = true;
							}
						}
						if (inQueue[i]) {
							queue.push(PriorityQueueElement<T>(i, norm.compute(distanceVector[i])));
						}
					}
					else {
						// edge spel
						distanceVector[i] = vector<double>(3,0.0);
						closestObjectSpel[i] = i;
						distanceTransform[start + i] = this->cov2d((*image)[i],2);
						subSpelDistance[i] = distanceTransform[start + i];
						queue.push(PqVElem(i, distanceVector[3*i + 0], distanceVector[3*i + 1], distanceVector[3*i + 2]));
						inQueue[i] = true;
					}
				}
				else {
					distanceVector[3*i + 0] = INF;
					distanceVector[3*i + 1] = INF;
					distanceVector[3*i + 2] = INF;
					distanceTransform[i] = INF;
					subSpelDistance[i] = INF;
					inQueue[i] = false;
				}
			}

			int ei,neighborIndex;
			double newDt;
			double newDi[3];
			double neighborLocation[3];
			int spelCount = 0;
			while(!queue.empty() && spelCount < 2*nElements){
				PqVElem e = queue.top();
				queue.pop();
				ei = e.index;
				if(inQueue[ei]){
					inQueue[ei] = false;
					neighbors = this->getNeighbors(ei,nNeighbors);
					for(size_t i = 0; i < neighbors.size(); i++){
						neighborIndex = neighbors[i].getIndex();
						this->edistv(ei,neighborIndex,neighborLocation); // neighborLocation becomes vector pointing to neighbor
						newDi[0] = distanceVector[3*ei + 0] + neighborLocation[0]; // should it be distanceVector[neighborIndex]?
						newDi[1] = distanceVector[3*ei + 1] + neighborLocation[1];
						newDi[2] = distanceVector[3*ei + 2] + neighborLocation[2];
						newDt = length(newDi) + subSpelDistance[ei];
						if ((newDt < distanceTransform[neighborIndex]) && (fabs(newDt - distanceTransform[neighborIndex]) > EPSILOND)) {
							distanceTransform[neighborIndex] = newDt;
							subSpelDistance[neighborIndex] = subSpelDistance[ei];
							distanceVector[3*neighborIndex + 0] = newDi[0];
							distanceVector[3*neighborIndex + 1] = newDi[1];
							distanceVector[3*neighborIndex + 2] = newDi[2];
							queue.push(PqVElem(neighborIndex, distanceVector[3*neighborIndex + 0], distanceVector[3*neighborIndex + 1], distanceVector[3*neighborIndex + 2]));
							inQueue[neighborIndex] = true;
						}
					}
				}
				spelCount++;
			}
		}
		delete[] inQueue;
		delete[] subSpelDistance;
		delete[] distanceVector;
		delete[] closestObjectSpel;
	}*/

}

#endif
