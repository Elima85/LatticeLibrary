#ifndef SEEDEDDISTANCETRANSFORM_H
#define SEEDEDDISTANCETRANSFORM_H

#include "image.h"
#include "seed.h"
#include "norm.h"
#include "priorityqueue.h"
#include <vector>
#include <cfloat>
#include <algorithm> // find
#include "vectoroperators.h"
#include "seededdistancemeasure.h"
#include <stdio.h>

namespace LatticeLib {

    /**
     * Class for computing seeded distance transforms of Image objects.
     */
    class SeededDistanceTransform {

    public:
        /**
         * Applies the specified distance measure to the input image, and computes the distance transform and the roots of its inverse forest.
         *
         * Parameter            | in/out    | Comment
         * :---------           | :------   | :-------
         * inputImage           | INPUT     | Input image for the distance transform.
         * seeds                | INPUT     | %Seed points for the distance transform. Contains one vector of seed points for every label.
         * distanceMeasure      | INPUT     | Distance measure to be used for the transform.
         * neighborhoodSize     | INPUT     | The number of neighbors that count as adjacent to a spel.
         * distanceTransform    | OUTPUT    | The computed distance transform. Must have the same lattice and dimensions as the input image, and one modality band for each label.
         * roots                | OUTPUT    | The roots of the distance transform. Must have the same lattice and dimensions as the input image, and one modality band for each label.
         */
        template<class T>
        void apply(const Image<T> &inputImage, const vector<vector<Seed> > &seeds,
                   SeededDistanceMeasure<T> &distanceMeasure, int neighborhoodSize,
                   Image<double> distanceTransform, Image<int> roots) const {

            if ((inputImage.getLattice() != distanceTransform.getLattice()) ||
                (inputImage.getLattice() != roots.getLattice())) {
                // throw exception or error
            }
            if ((distanceTransform.getNBands() != seeds.size()) || (roots.getNBands() != seeds.size())) {
                // throw exception or error
            }

            // setup
            int nElements = inputImage.getNElements();
            int nLabels = seeds.size();
            bool *inQueue = new bool[nElements]; // so that only the "best" copy of an element is popped, and all others are skipped, until a better one is pushed.
            distanceMeasure.setup(inputImage);
            for (int labelIndex = 0; labelIndex < nLabels; labelIndex++) {
                // initialization
                for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                    inQueue[elementIndex] = false;
                }
                priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
                vector<PriorityQueueElement<T> > newQueueElements;
                distanceMeasure.initialize(inputImage, seeds, labelIndex, distanceTransform, roots, newQueueElements);
                int nNewQueueElements = newQueueElements.size();
                for (int newQueueElementIndex = 0; newQueueElementIndex < nNewQueueElements; newQueueElementIndex++) {
                    queue.push(newQueueElements[newQueueElementIndex]);
                    inQueue[newQueueElements[newQueueElementIndex].getIndex()] = true;
                }
                // wave front propagation
                while (!queue.empty()) {
                    PriorityQueueElement<T> topElement = queue.top();
                    queue.pop();
                    int poppedElementIndex = topElement.getIndex();
                    if (inQueue[poppedElementIndex]) {
                        inQueue[poppedElementIndex] = false; // so that old queue elements offering larger distances are skipped
                        distanceMeasure.update(inputImage, neighborhoodSize, poppedElementIndex, labelIndex,
                                               distanceTransform, roots, newQueueElements);
                        nNewQueueElements = newQueueElements.size();
                        for (int queueElementIndex = 0; queueElementIndex < nNewQueueElements; queueElementIndex++) {
                            queue.push(newQueueElements[queueElementIndex]);
                            inQueue[newQueueElements[queueElementIndex].getIndex()] = true;
                        }
                    }
                }
            }
            // cleanup
            distanceMeasure.clear();
        }

    };
/*
* Approximated vectorial minimum barrier distance
* Strand et al. 2012, Kårsnäs and Strand 2012
*
* Approximates the minimum of the difference between the maximum and minimum values along a path, based on the locally optimal path ("greedy" algorithm).
* Is the other approximation (min(max)-max(min)) valid for VMBD? Can min(max) and max(min) be computed for each band by itself? (probably not)
*
* Parameter			| Comment
* :----------		| :--------
* image				| Input image
* seeds				| indices and labels of seedpoints
* norm				| The norm used in the definition of distance.
* neighborhoodSize  | #neighbors to use.
*/
/*    template<class T>
    DistanceImage approximateMinimumBarrierBoundingBox(const IntensityImage<T> &image, const vector<Seed> seeds, Norm &norm, int neighborhoodSize) { // TODO: Make norm const somehow!

        // initialization
        int nElements = image.getNElements();
        int nSeeds = seeds.size();
        int nLabels = 0;
        vector<int> listOfLabels;
        for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
            int label = seeds[seedIndex].getLabel();
            bool newLabel = true;
            for (int labelIndex = 0; labelIndex < listOfLabels.size(); labelIndex++) {
                if (listOfLabels[labelIndex] == label) {
                    newLabel = false;
                }
            }
            if (newLabel) {
                nLabels++;
                listOfLabels.push_back(label);
                //std::cout << "label: " << label << std::endl;
            }
        }
        //std::cout << "#labels: " << listOfLabels.size() << std::endl;
        double *distanceValues = new double[nElements * nLabels];
        DistanceImage distanceTransform(distanceValues, image.getLattice(), nLabels);
        std::cout << "#rows: " << distanceTransform.getNRows() << "\n#columns: " << distanceTransform.getNColumns() << "\n#layers: " << distanceTransform.getNLayers() << "\n#bands: " << distanceTransform.getNBands() << std::endl;


        // Every layer represents the distance from seed points of one class
        vector<T> *pathMin = new vector<T>[nElements];
        vector<T> *pathMax = new vector<T>[nElements];
        bool *inQueue = new bool[nElements]; // so that only the "best" copy of an element is popped, and all others are skipped, until a better one is pushed.
        for (int labelIndex = 0; labelIndex < nLabels; labelIndex++) {

            // initialize background
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                pathMin[elementIndex] = image[elementIndex]; // the spel is always part of the path between itself and the object boundary
                pathMax[elementIndex] = image[elementIndex];
                distanceTransform.setElement(elementIndex, labelIndex, DBL_MAX);
                inQueue[elementIndex] = false;
            }

            // initialize seed points and put them on queue
            priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
            int currentLabel = listOfLabels[labelIndex];
            std::cout << "current label: " << currentLabel << std::endl;
            for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
                if (seeds[seedIndex].getLabel() == currentLabel) {
                    int elementIndex = seeds[seedIndex].getElementIndex();
                    distanceTransform.setElement(elementIndex, labelIndex, 0);
                    queue.push(PriorityQueueElement<T>(elementIndex, 0));
                    inQueue[elementIndex] = true;
                }
            }

            // wave front propagation
            vector<Neighbor> neighbors;
            while (!queue.empty()) {
                PriorityQueueElement<T> topElement = queue.top();
                queue.pop();
                int currentIndex = topElement.getIndex();
                if (inQueue[currentIndex]) {
                    inQueue[currentIndex] = false; // so that old queue elements offering larger distances are skipped
                    image.getNeighbors(currentIndex, neighborhoodSize, neighbors);
                    for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                        int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
                        vector<T> minIntensities = minElements(pathMin[currentIndex], image[neighborGlobalIndex]);
                        vector<T> maxIntensities = maxElements(pathMax[currentIndex], image[neighborGlobalIndex]);
                        vector<T> intensitySpans = maxIntensities - minIntensities;
                        double distance = norm.compute(intensitySpans);
                        if (distance < distanceTransform(neighborGlobalIndex, labelIndex)) {
                            distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                            pathMin[neighborGlobalIndex] = minIntensities;
                            pathMax[neighborGlobalIndex] = maxIntensities;
                            queue.push(PriorityQueueElement<T>(neighborGlobalIndex, pathMax[neighborGlobalIndex] - pathMin[neighborGlobalIndex], norm));
                            inQueue[neighborGlobalIndex] = true;
                        }
                    }
                }
            }
        }

        delete[] inQueue;
        delete[] pathMin;
        delete[] pathMax;

        return distanceTransform;
    }*/

/*
* Fuzzy connectedness distance transform
* Udupa 1996, Udupa 2003
*
* Maximizes the weakest link, defined as the difference in value between two neighbors along the path. OBS!!! Only takes the first band into account! Use norm of color difference vector?
* Should an inter-neighbor Euclidian distance be used a factor, to consider different kinds of neighbors and lattices? Ask Punam Saha about fuzzy adjacency.
*
* Parameter			| Comment
* :----------		| :--------
* image				| Input image
* seeds				| indices and labels of seedpoints
* norm				| The norm used in the definition of distance.
* neighborhoodSize  | #neighbors to use.
*/
/*    template<class T>
    DistanceImage fuzzyConnectedness(const IntensityImage<T> &image, const vector<Seed> seeds, Norm &norm, int neighborhoodSize) {

        // initialization
        int nElements = image.getNElements();
        int nSeeds = seeds.size();
        int nLabels = 0;
        vector<int> listOfLabels;
        for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
            int label = seeds[seedIndex].getLabel();
            if (find(listOfLabels.begin(), listOfLabels.end(), label) != listOfLabels.end()) {
                nLabels++;
                listOfLabels.push_back(label);
            }
        }
        double *distanceValues = new double[nElements * nLabels];
        DistanceImage distanceTransform(distanceValues, image.getLattice(), nLabels);

        // Every layer represents the distance from seed points of one class
        bool *inQueue = new bool[nElements];
        for (int labelIndex = 0; labelIndex < nLabels; labelIndex++) {

            // initialize background
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                distanceTransform.setElement(elementIndex, labelIndex, DBL_MAX);
                inQueue[elementIndex] = false;
            }

            // initialize seed points and put them on queue
            priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
            int currentLabel = listOfLabels[labelIndex];
            for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
                if (seeds[seedIndex].getLabel() == currentLabel) {
                    int elementIndex = seeds[seedIndex].getElementIndex();
                    distanceTransform.setElement(elementIndex, labelIndex, 0);
                    queue.push(PriorityQueueElement<T>(elementIndex, 0));
                    inQueue[elementIndex] = true;
                }
            }

            // wave front propagation
            vector<Neighbor> neighbors;
            while (!queue.empty()) {
                PriorityQueueElement<T> topElement = queue.top();
                queue.pop();
                int elementIndex = topElement.getIndex();
                if (inQueue[elementIndex]) {
                    inQueue[elementIndex] = false;
                    image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
                    for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                        int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
                        double distance = MAX(distanceTransform(elementIndex,labelIndex), norm.compute(image[neighborGlobalIndex] - image[elementIndex]));  // if the current link is not weaker, the distance does not change.
                        if (distance < distanceTransform(neighborGlobalIndex,labelIndex)) {
                            distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                            queue.push(PriorityQueueElement<T>(neighborGlobalIndex, distance));
                            inQueue[neighborGlobalIndex] = true;
                        }
                    }
                }
            }
        }
        delete[] inQueue;
        return distanceTransform;
    }*/

/*
* Fuzzy distance
* Saha 2002, (Svensson 2008)
*
* The distance between two neighbors is the average of their intensity values multiplied with the Euclidean distance between them. OBS!!! Only takes the first band into account! Use norm of average color vector?
*
* Parameter			| Comment
* :----------		| :--------
* image				| Input image
* seeds				| indices and labels of seedpoints
* norm				| The norm used in the definition of distance.
* neighborhoodSize  | #neighbors to use.
*/
/*    template<class T>
    DistanceImage fuzzyDistance(const IntensityImage<T> &image, const vector<Seed> seeds, Norm &norm, int neighborhoodSize) {

        // initialization
        int nElements = image.getNElements();
        int nSeeds = seeds.size();
        int nLabels = 0;
        vector<int> listOfLabels;
        for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
            int label = seeds[seedIndex].getLabel();
            if (find(listOfLabels.begin(), listOfLabels.end(), label) != listOfLabels.end()) {
                nLabels++;
                listOfLabels.push_back(label);
            }
        }
        double *distanceValues = new double[nElements * nLabels];
        DistanceImage distanceTransform(distanceValues, image.getLattice(), nLabels);

        // Every layer represents the distance from seed points of one class
        bool *inQueue = new bool[nElements];
        for (int labelIndex = 0; labelIndex < nLabels; labelIndex++) {

            // initialize background
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                distanceTransform.setElement(elementIndex, labelIndex, DBL_MAX);
                inQueue[elementIndex] = false;
            }

            // initialize seed points and put them on queue
            priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
            int currentLabel = listOfLabels[labelIndex];
            for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
                if (seeds[seedIndex].getLabel() == currentLabel) {
                    int elementIndex = seeds[seedIndex].getElementIndex();
                    distanceTransform.setElement(elementIndex, labelIndex, 0);
                    queue.push(PriorityQueueElement<T>(elementIndex, 0));
                    inQueue[elementIndex] = true;
                }
            }

            // wave front propagation
            vector<Neighbor> neighbors;
            while (!queue.empty()) {
                PriorityQueueElement<T> topElement = queue.top();
                queue.pop();
                int elementIndex = topElement.getIndex();
                if (inQueue[elementIndex]) {
                    inQueue[elementIndex] = false;
                    image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
                    for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                        int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
                        double distanceToNeighbor = image.euclideanDistance(elementIndex, neighborGlobalIndex);
                        double distance = distanceTransform(elementIndex, nLabels) + 0.5 * norm.compute(image[neighborGlobalIndex] + image[elementIndex]) * distanceToNeighbor;
//				distance = distanceTransform[currentIndex] + 0.5 * fabs(image(neighborIndex,0) + image(currentIndex,0)) * distanceToNeighbor; // vector to scalar!
                        if (distance < distanceTransform(neighborGlobalIndex, labelIndex)) {
                            distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                            queue.push(PriorityQueueElement<T>(neighborGlobalIndex, distance));
                            inQueue[neighborGlobalIndex] = true;
                        }
                    }
                }
            }
        }
        delete[] inQueue;
        return distanceTransform;
    }*/


/*
* Geodesic distance
* Toivanen 1996, Ikonen 2005, Criminisi 2008
*
* Sample values are treated as height values, and the "walking distance" along the surface is calculated.
* We use the 2-norm instead of approximating the Euclidean distance with the 1-norm, as we don't get integer results anyway.
* Euclidean inter-neighbor distance is used as a weight. Borgefors1986 suggests optimal weights
* for 2D CC, but these are not taken into account.
*
* Parameter			| Comment
* :----------		| :--------
* image				| Input image
* seeds				| indices and labels of seedpoints
* norm				| The norm used in the definition of distance.
* neighborhoodSize  | #neighbors to use.
*/
/*    template<class T>
    DistanceImage geodesicDistance(const IntensityImage<T> &image, const vector<Seed> seeds, Norm &norm, int neighborhoodSize) {

        // initialization
        int nElements = image.getNElements();
        int nSeeds = seeds.size();
        int nLabels = 0;
        vector<int> listOfLabels;
        for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
            int label = seeds[seedIndex].getLabel();
            if (find(listOfLabels.begin(), listOfLabels.end(), label) != listOfLabels.end()) {
                nLabels++;
                listOfLabels.push_back(label);
            }
        }
        double *distanceValues = new double[nElements * nLabels];
        DistanceImage distanceTransform(distanceValues, image.getLattice(), nLabels);

        bool *inQueue = new bool[nElements];
        for (int labelIndex = 0; labelIndex < nLabels; labelIndex++) {

            // initialize background
            for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
                distanceTransform.setElement(elementIndex, labelIndex, DBL_MAX);
                inQueue[elementIndex] = false;
            }

            // initialize seed points and put them on queue
            priority_queue<PriorityQueueElement<T>, vector<PriorityQueueElement<T> >, PriorityQueueElementComparison> queue;
            int currentLabel = listOfLabels[labelIndex];
            for (int seedIndex = 0; seedIndex < nSeeds; seedIndex++) {
                if (seeds[seedIndex].getLabel() == currentLabel) {
                    int elementIndex = seeds[seedIndex].getElementIndex();
                    distanceTransform.setElement(elementIndex, labelIndex, 0);
                    queue.push(PriorityQueueElement<T>(elementIndex, 0));
                    inQueue[elementIndex] = true;
                }
            }

            // wave front propagation
            double distance;
            vector<Neighbor> neighbors;
            while (!queue.empty()) {
                PriorityQueueElement<T> topElement = queue.top();
                queue.pop();
                int elementIndex = topElement.getIndex();
                if (inQueue[elementIndex]) {
                    inQueue[elementIndex] = false;
                    vector<T> elementIntensity = image[elementIndex];
                    image.getNeighbors(elementIndex, neighborhoodSize, neighbors);
                    for (int neighborIndex = 0; neighborIndex < neighbors.size(); neighborIndex++) {
                        int neighborGlobalIndex = neighbors[neighborIndex].getIndex();
                        double distanceToNeighbor = image.euclideanDistance(elementIndex, neighborGlobalIndex);
                        vector<T> intensityDifference = elementIntensity - image[neighborGlobalIndex];
                        distance = distanceTransform(elementIndex, labelIndex) + sqrt(norm.compute(intensityDifference) * norm.compute(intensityDifference) + distanceToNeighbor * distanceToNeighbor); // Not perfect... Weights are messed up if it's not the 2-norm, I think.
//				intensityDifference = currentIntensity - image(neighborIndex,0);
//				distance = distanceTransform[currentIndex] + sqrt(intensityDifference * intensityDifference + distanceToNeighbor * distanceToNeighbor);
                        if (distance < distanceTransform(neighborGlobalIndex, nLabels)) {
                            distanceTransform.setElement(neighborGlobalIndex, labelIndex, distance);
                            queue.push(PriorityQueueElement<T>(neighborGlobalIndex, distance));
                            inQueue[neighborGlobalIndex] = true;
                        }
                    }
                }
            }
        }
        delete[] inQueue;
        return distanceTransform;
    }*/

}

#endif
