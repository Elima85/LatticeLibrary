#ifndef DISTANCETRANSFORM_H
#define DISTANCETRANSFORM_H

#include "cimage.h"
#include "priorityqueue.h"
#include "norm.h"
#include <vector>
#include <cfloat>

namespace CImage {

/**
 * Anti-Aliased Euclidean distance
 *
 * Computes the Euclidean distance from the background (membership value == 0)
 * voxel centers to an object (membership values in (0,1]) with a crudely approximated border.
 *
 * (Gustavson and Strand 2011, use 8 neighbors => nN = 8)
 *
 * Parameter	| in/out	| Comment
 * :----------	| :-------	| :--------
 * dt			| OUTPUT	| Distance transform of the image.
 * nN			|			| #neighbors to use.
 */
template <class T>
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
}

}

#endif
