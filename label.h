#ifndef LABEL_H
#define LABEL_H

#include "image.h"
#include "crispsegmentationimage.h"
#include "distanceimage.h"
#include "intensityimage.h"
#include "priorityqueue.h"
#include <vector>
#include "vectoroperators.h"
#include <cfloat>

namespace LatticeLib {

/**
 * Approximated vectorial minimum barrier distance
 * Strand et al. 2012, Kårsnäs and Strand 2012
 *
 * Approximates the minimum of the difference between the maximum and minimum values along a path, based on the locally optimal path ("greedy" algorithm).
 * Is the other approximation (min(max)-max(min)) valid for VMBD? Can min(max) and max(min) be computed for each band by itself? (probably not)
 *
 * Parameter			| in/out	| Comment
 * :----------			| :-------	| :--------
 * image				|			| Input image
 * seeds				|			| Data array where seed elements contain their label and the rest are 0. !!!! CrispSegmentationImage?
 * labels				| OUTPUT	| Segmented data array, where each element contains its label. !!!! CrispSegmentationImage or something
 * distanceTransform	| OUTPUT	| Distance transform of the image. !!!! "DistanceMapCImage"?
 * norm					|			| The norm used in the definition of distance.
 * neighborhoodSize		|			| #neighbors to use.
 */
template <class T>
void approximateMinimumBarrierBoundingBox(const IntensityImage<T> *image, const uint8* seeds, Norm* norm, int neighborhoodSize, uint8* labels, double* distanceTransform) { // TODO: Make norm const somehow!

	if (!image || !seeds || !labels || !distanceTransform || !norm) {
		throw nullPointerException();
	}

	int nElements = image->getNElements();
	bool* inQueue = new bool[nElements]; // so that only the "best" copy of an element is popped, and all others are skipped, until a better one is pushed.
	vector<T>* pathMin = new vector<T>[nElements];
	vector<T>* pathMax = new vector<T>[nElements];
	priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;

	// initialization
	for(int i = 0; i < nElements; i++){
		pathMin[i] = (*image)[i]; // the spel is always part of the path between itself and the object boundary
		pathMax[i] = (*image)[i];
		labels[i] = seeds[i];
		if(seeds[i] > 0){ // seed points
			distanceTransform[i] = 0;
			queue.push(PriorityQueueElement<T>(i,0));
			inQueue[i] = true;
		}
		else {
			distanceTransform[i] = DBL_MAX;
			inQueue[i] = false;
		}
	}

	// wave front propagation
	int iterations = 0; // debugging
	int neighborIndex, currentIndex;
	double distance;
	vector<T> intensitySpans, minIntensities, maxIntensities;
	vector<Neighbor> neighbors;
	PriorityQueueElement<T> topElement;
	while(!queue.empty()){ // while there are still spels in the wave front
		topElement = queue.top();
		queue.pop();
		currentIndex = topElement.getIndex();
		if(inQueue[currentIndex]){
			inQueue[currentIndex] = false; // so that old queue elements offering larger distances are skipped
			image->getNeighbors(currentIndex, neighborhoodSize,neighbors);
			for(uint8 i = 0; i < neighbors.size(); i++){ // propagate distance to neighbors
				neighborIndex = neighbors[i].getIndex();
				minIntensities = minElements(pathMin[currentIndex],(*image)[neighborIndex]);
				maxIntensities = maxElements(pathMax[currentIndex],(*image)[neighborIndex]);
				intensitySpans = maxIntensities - minIntensities;
				distance = norm->compute(intensitySpans);
				if(distance < distanceTransform[neighborIndex] || (distance == distanceTransform[neighborIndex] && labels[currentIndex] < labels[neighborIndex])){ // low label favorization is not present in Robin's or Andreas' implementations
					distanceTransform[neighborIndex] = distance;
					pathMin[neighborIndex] = minIntensities;
					pathMax[neighborIndex] = maxIntensities;
					labels[neighborIndex] = labels[currentIndex];
					queue.push(PriorityQueueElement<T>(neighborIndex,norm->compute(pathMax[neighborIndex] - pathMin[neighborIndex])));
					inQueue[neighborIndex] = true;
				}
			}
		}
		iterations++;
	}

	delete[] inQueue;
	delete[] pathMin;
	delete[] pathMax;
}


/**
 * Fuzzy connectedness distance transform
 * Udupa 1996, Udupa 2003
 *
 * Maximizes the weakest link, defined as the difference in value between two neighbors along the path. OBS!!! Only takes the first band into account! Use norm of color difference vector?
 * Should an inter-neighbor Euclidian distance be used a factor, to consider different kinds of neighbors and lattices? Ask Punam Saha about fuzzy adjacency.
 *
 * Parameter			| in/out	| Comment
 * :----------			| :-------	| :--------
 * image				|			| Input image
 * seeds				|			| Data array where seed elements contain their label and the rest are 0.
 * labels				| OUTPUT	| Segmented data array, where each element contains its label.
 * distanceTransform	| OUTPUT	| Distance transform of the image.
 * neighborhoodSize		|			| #neighbors to use.
 */
template <class T>
void fuzzyConnectedness(const IntensityImage<T> *image, const uint8* seeds, Norm* norm, int neighborhoodSize, uint8* labels, double* distanceTransform) {

	if (!image || !seeds || !labels || !distanceTransform) {
		throw nullPointerException();
	}

	int nElements = image->getNElements();
	bool* inQueue = new bool[nElements];
	priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
	for(int i = 0; i < nElements; i++){
		distanceTransform[i] = DBL_MAX;
		if(seeds[i] > 0){
			distanceTransform[i] = 0;
			queue.push(PriorityQueueElement<T>(i,0));
			inQueue[i] = true;
			labels[i] = seeds[i];
		}
		else {
			inQueue[i] = false;
		}
	}

	int neighborIndex, currentIndex;
	double distance;
	vector<Neighbor> neighbors;
	PriorityQueueElement<T> topElement;
	while(!queue.empty()){
		topElement = queue.top();
		queue.pop();
		currentIndex = topElement.getIndex();
		if(inQueue[currentIndex]){
			inQueue[currentIndex] = false;
			image->getNeighbors(currentIndex, neighborhoodSize,neighbors);
			for(uint8 i = 0; i < neighbors.size(); i++){
				neighborIndex = neighbors[i].getIndex();
				distance = MAX(distanceTransform[currentIndex], norm->compute((*image)[neighborIndex] - (*image)[currentIndex]));  // if the current link is not weaker, the distance does not change.
//				distance = MAX(distanceTransform[currentIndex], fabs((*image)(neighborIndex,0) - (*image)(currentIndex,0))); // if the current link is not weaker, the distance does not change. TODO: Use norm for color?
				if(distance < distanceTransform[neighborIndex] || (distance == distanceTransform[neighborIndex] && labels[currentIndex] < labels[neighborIndex])){
					distanceTransform[neighborIndex] = distance;
					labels[neighborIndex] = labels[currentIndex];
					queue.push(PriorityQueueElement<T>(neighborIndex,distance));
					inQueue[neighborIndex] = true;
				}
			}
		}
	}
	delete[] inQueue;
}


/**
 * Fuzzy distance
 * Saha 2002, (Svensson 2008)
 *
 * The distance between two neighbors is the average of their intensity values multiplied with the Euclidean distance between them. OBS!!! Only takes the first band into account! Use norm of average color vector?
 *
 * Parameter			| in/out	| Comment
 * :----------			| :-------	| :--------
 * image				|			| Input image
 * seeds				|			| Data array where seed elements contain their label and the rest are 0.
 * labels				| OUTPUT	| Segmented data array, where each element contains its label.
 * distanceTransform	| OUTPUT	| Distance transform of the image.
 * neighborhoodSize		|			| #neighbors to use.
 */
template <class T>
void fuzzyDistance(const IntensityImage<T> *image, const uint8* seeds, Norm* norm, int neighborhoodSize, uint8* labels, double* distanceTransform) {

	if (!image || !seeds || !labels || !distanceTransform) {
		throw nullPointerException();
	}

	int nElements = image->getNElements();
	bool* inQueue = new bool[nElements];
	priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
	for(int i = 0; i < nElements; i++){
		distanceTransform[i] = DBL_MAX;
		inQueue[i] = false;
		labels[i] = seeds[i];
		if(seeds[i] > 0){
			distanceTransform[i] = 0;
			queue.push(PriorityQueueElement<T>(i,0));
			inQueue[i] = true;
		}
	}

	int currentIndex, neighborIndex, distanceToNeighbor;
	double distance;
	vector<Neighbor> neighbors;
	PriorityQueueElement<T> topElement;
	while(!queue.empty()){
		topElement = queue.top();
		queue.pop();
		currentIndex = topElement.getIndex();
		if(inQueue[currentIndex]){
			inQueue[currentIndex] = false;
			image->getNeighbors(currentIndex, neighborhoodSize,neighbors);
			for(uint8 i = 0; i < neighbors.size(); i++){
				neighborIndex = neighbors[i].getIndex();
				//distanceToNeighbor = neighbors[i].getDistance();
				distanceToNeighbor = image->euclideanDistance(currentIndex, neighborIndex);
				distance = distanceTransform[currentIndex] + 0.5 * norm->compute((*image)[neighborIndex] + (*image)[currentIndex]) * distanceToNeighbor;
//				distance = distanceTransform[currentIndex] + 0.5 * fabs((*image)(neighborIndex,0) + (*image)(currentIndex,0)) * distanceToNeighbor; // vector to scalar!
				if(distance < distanceTransform[neighborIndex] || (distance == distanceTransform[neighborIndex] && labels[currentIndex] < labels[neighborIndex])){
					distanceTransform[neighborIndex] = distance;
					labels[neighborIndex] = labels[currentIndex];
					queue.push(PriorityQueueElement<T>(neighborIndex,distance));
					inQueue[neighborIndex] = true;
				}
			}
		}
	}
	delete[] inQueue;
}


/**
 * Geodesic distance
 * Toivanen 1996, Ikonen 2005, Criminisi 2008
 *
 * Sample values are treated as height values, and the "walking distance" along the surface is calculated.
 * We use the 2-norm instead of approximating the Euclidean distance with the 1-norm, as we don't get integer results anyway.
 * Euclidean inter-neighbor distance is used as a weight. Borgefors1986 suggests optimal weights
 * for 2D CC, but these are not taken into account.
 *
 * Parameter			| in/out	| Comment
 * :----------			| :-------	| :--------
 * image				|			| Input image
 * seeds				|			| Data array where seed elements contain their label and the rest are 0.
 * labels				| OUTPUT	| Segmented data array, where each element contains its label.
 * distanceTransform	| OUTPUT	| Distance transform of the image.
 * neighborhoodSize		|			| #neighbors to use.
 */
template <class T>
void geodesicDistance(const IntensityImage<T> *image, const uint8* seeds, Norm* norm, int neighborhoodSize, uint8* labels, double* distanceTransform) {

	if (!image || !seeds || !labels || !distanceTransform) {
		throw nullPointerException();
	}

	int nElements = image->getNElements();
	bool* inQueue = new bool[nElements];
	priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;

	for(int i = 0; i < nElements; i++){
		distanceTransform[i] = DBL_MAX;
		inQueue[i] = false;
		labels[i] = seeds[i];
		if(seeds[i] > 0){
			distanceTransform[i] = 0;
			queue.push(PriorityQueueElement<T>(i,0));
			inQueue[i] = true;
		}
	}

	int currentIndex, neighborIndex, distanceToNeighbor;
	vector<T> currentIntensity, intensityDifference;
//	T currentIntensity, intensityDifference; // vector to scalar!
	double distance;
	vector<Neighbor> neighbors;
	PriorityQueueElement<T> topElement;
	while(!queue.empty()) {
		topElement = queue.top();
		queue.pop();
		currentIndex = topElement.getIndex();
		if(inQueue[currentIndex]) {
			inQueue[currentIndex] = false;
			currentIntensity = (*image)[currentIndex];
//			currentIntensity = (*image)(currentIndex,0);
			image->getNeighbors(currentIndex, neighborhoodSize,neighbors);
			for(uint8 i = 0; i < neighbors.size(); i++){
				neighborIndex = neighbors[i].getIndex();
				//distanceToNeighbor = neighbors[i].getDistance();
				distanceToNeighbor = image->euclideanDistance(currentIndex, neighborIndex);
				intensityDifference = currentIntensity - (*image)[neighborIndex];
				distance = distanceTransform[currentIndex] + sqrt(norm->compute(intensityDifference) * norm->compute(intensityDifference) + distanceToNeighbor * distanceToNeighbor); // Not perfect... Weights are messed up if it's not the 2-norm, I think.
//				intensityDifference = currentIntensity - (*image)(neighborIndex,0);
//				distance = distanceTransform[currentIndex] + sqrt(intensityDifference * intensityDifference + distanceToNeighbor * distanceToNeighbor);
				if(distance < distanceTransform[neighborIndex] || (distance == distanceTransform[neighborIndex] && labels[currentIndex] < labels[neighborIndex])){
					distanceTransform[neighborIndex] = distance;
					labels[neighborIndex] = labels[currentIndex];
					queue.push(PriorityQueueElement<T>(neighborIndex,distance));
					inQueue[neighborIndex] = true;
				}
			}
		}
	}
	delete[] inQueue;
}

}

#endif
