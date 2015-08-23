#ifndef LATTICELIBRARY_IMAGERESAMPLER_H
#define LATTICELIBRARY_IMAGERESAMPLER_H

#include "image.h"
#include "exception.h"
#include "weightassignment.h"
#include <vector>
#include "vectoroperators.h"
#include "neighbor.h"
#include "pnorm.h"

namespace LatticeLib {
    template<class intensityTemplate>
    /**
     * Class for resampling image data from one lattice to another.
     *
     * The origins of the input and output images are aligned. If the input image is smaller than the output image,
     * only the existing elements of the input image are used, and elements of the output image that do not contain any
     * input image elements are set to zero intensity. If the output image is smaller than the input image, only part
     * of the input image is used.
     */
    class ImageResampler {
    public:
        /**
         * Resamples the input image to a lattice of lower resolution. The intensity values are computed as a weighted
         * average of the high resolution spatial elements inside of the Voronoi region of each low resolution spatial
         * element.
         *
         * Parameter		| in/out	| Comment
         * :---------		| :------	| :-------
         * inputImage       | INPUT     | Input high resolution image.
         * weightAssignment | INPUT     | Assigns weights to the high resolution elements in the downsampling process.
         * neighborhoodSize | INPUT     | Neighborhood size to use for Voronoi region definition.
         * outputImage      | OUTPUT    | Output low resolution image.
         */
        void downsample(Image<intensityTemplate> inputImage, const WeightAssignment<intensityTemplate> &weightAssignment,
                        int neighborhoodSize, Image<intensityTemplate> outputImage) const {
            if ((inputImage.getLattice().getDensity() < outputImage.getLattice().getDensity()) || (inputImage.getNBands() != outputImage.getNBands())) {
                throw incompatibleParametersException();
            }
            int newNRows = outputImage.getNRows();
            int newNColumns = outputImage.getNColumns();
            int newNLayers = outputImage.getNLayers();
            double oldElementWidth, oldElementHeight, oldElementDepth, newElementWidth, newElementHeight, newElementDepth;
            vector<double> coordinates1, coordinates2;
            // compute half column step length
            if (newNColumns > 1) {
                outputImage.getCoordinates(outputImage.rclToIndex(0, 0, 0), coordinates1);
                outputImage.getCoordinates(outputImage.rclToIndex(0, 1, 0), coordinates2);
                newElementWidth = fabs(coordinates1[0] - coordinates2[0]);
            }
            else {
                newElementWidth = outputImage.getWidth();
            }
            if (inputImage.getNColumns() > 1) {
                inputImage.getCoordinates(inputImage.rclToIndex(0, 0, 0), coordinates1);
                inputImage.getCoordinates(inputImage.rclToIndex(0, 1, 0), coordinates2);
                oldElementWidth = fabs(coordinates1[0] - coordinates2[0]);
            }
            else {
                oldElementWidth = inputImage.getWidth();
            }
            double columnHalfChunk = ceil(0.5 * newElementWidth / oldElementWidth);

            // compute half row step length
            if (newNRows > 1) {
                outputImage.getCoordinates(outputImage.rclToIndex(0, 0, 0), coordinates1);
                outputImage.getCoordinates(outputImage.rclToIndex(1, 0, 0), coordinates2);
                newElementHeight = fabs(coordinates1[1] - coordinates2[1]);
            }
            else {
                newElementHeight = outputImage.getHeight();
            }
            if (inputImage.getNRows() > 1) {
                inputImage.getCoordinates(inputImage.rclToIndex(0, 0, 0), coordinates1);
                inputImage.getCoordinates(inputImage.rclToIndex(1, 0, 0), coordinates2);
                oldElementHeight = fabs(coordinates1[1] - coordinates2[1]);
            }
            else {
                oldElementHeight = inputImage.getHeight();
            }
            double rowHalfChunk = ceil(0.5 * newElementHeight / oldElementHeight);

            // compute half layer step length
            if (newNLayers > 1) {
                outputImage.getCoordinates(outputImage.rclToIndex(0, 0, 0), coordinates1);
                outputImage.getCoordinates(outputImage.rclToIndex(0, 0, 1), coordinates2);
                newElementDepth = fabs(coordinates1[2] - coordinates2[2]);
            }
            else {
                newElementDepth = outputImage.getDepth();
            }
            if (inputImage.getNLayers() > 1) {
                inputImage.getCoordinates(inputImage.rclToIndex(0, 0, 0), coordinates1);
                inputImage.getCoordinates(inputImage.rclToIndex(0, 0, 1), coordinates2);
                oldElementDepth = fabs(coordinates1[2] - coordinates2[2]);
            }
            else {
                oldElementDepth = inputImage.getDepth();
            }
            double layerHalfChunk = ceil(0.5 * newElementDepth / oldElementDepth);

            for (int newRowIndex = 0; newRowIndex < newNRows; newRowIndex++) {
                for (int newColumnIndex = 0; newColumnIndex < newNColumns; newColumnIndex++) {
                    for (int newLayerIndex = 0; newLayerIndex < newNLayers; newLayerIndex++) {
                        int newElementIndex = outputImage.rclToIndex(newRowIndex, newColumnIndex, newLayerIndex);
                        // compute position of new element
                        vector<double> newElementPosition;
                        outputImage.getCoordinates(newElementIndex, newElementPosition);
                        // compute positions of the neighbors of the new element
                        vector<Neighbor> newElementNeighbors;
                        outputImage.getNeighbors(newElementIndex, neighborhoodSize, newElementNeighbors);
                        vector< vector<double> > newNeighborPositions;
                        int actualNeighborhoodSize = newElementNeighbors.size();
                        for (int newNeighborIndex = 0; newNeighborIndex < actualNeighborhoodSize; newNeighborIndex++) {
                            vector<double> neighborPosition;
                            outputImage.getCoordinates(newElementNeighbors[newNeighborIndex].getElementIndex(), neighborPosition);
                            newNeighborPositions.push_back(neighborPosition);
                        }
                        // find closest element in input image
                        int closestOldElement;
                        // extract box containing the Voronoi region of the new element
                        int oldRowIndexStart = inputImage.indexToR(closestOldElement) - rowHalfChunk;
                        int oldRowIndexStop = inputImage.indexToR(closestOldElement) + rowHalfChunk;
                        int oldColumnIndexStart = inputImage.indexToC(closestOldElement) - columnHalfChunk;
                        int oldColumnIndexStop = inputImage.indexToC(closestOldElement) + columnHalfChunk;
                        int oldLayerIndexStart = inputImage.indexToL(closestOldElement) - layerHalfChunk;
                        int oldLayerIndexStop = inputImage.indexToL(closestOldElement) + layerHalfChunk;
                        int nOldElementsInNewVoronoiRegion = 0;
                        int nBands = inputImage.getNBands();
                        vector<double> accumulatedIntensity(nBands,0.0);
                        for (int oldRowIndex = oldRowIndexStart; oldRowIndex < oldRowIndexStop; oldRowIndex++) {
                            for (int oldColumnIndex = oldColumnIndexStart; oldColumnIndex < oldColumnIndexStop; oldColumnIndex++) {
                                for (int oldLayerIndex = oldLayerIndexStart; oldLayerIndex < oldColumnIndexStop; oldLayerIndex++) {
                                    // check if the potential old element exists
                                    if (inputImage.getLattice().isValid(oldRowIndex, oldColumnIndex, oldLayerIndex)) {
                                        int oldElementIndex = inputImage.rclToIndex(oldRowIndex, oldColumnIndex, oldLayerIndex);
                                        // compute distance to new element
                                        vector<double> oldElementPosition;
                                        inputImage.getCoordinates(oldElementIndex, oldElementPosition);
                                        PNorm<double> norm(2);
                                        double distanceToNewElement = norm.compute(
                                                newElementPosition - oldElementPosition);
                                        // see if the old element is inside of the Voronoi region of the new element
                                        bool insideVoronoiRegion = true;
                                        for (int newNeighborIndex = 0; newNeighborIndex < actualNeighborhoodSize; newNeighborIndex++) {
                                            if (norm.compute(oldElementPosition - newNeighborPositions[newNeighborIndex]) < distanceToNewElement) {
                                                insideVoronoiRegion = false;
                                            }
                                        }
                                        if (insideVoronoiRegion) {
                                            double weight = weightAssignment.compute(newElementIndex, outputImage, oldElementIndex, inputImage);
                                            accumulatedIntensity = accumulatedIntensity + weight * inputImage[oldElementIndex];
                                            nOldElementsInNewVoronoiRegion++;
                                        }
                                    }
                                }
                            }
                        }
                        // set new element intensity
                        outputImage.setElement(newElementIndex, 1 / double(nOldElementsInNewVoronoiRegion) * accumulatedIntensity);
                    }
                }
            }
        }
    };
}

#endif //LATTICELIBRARY_IMAGERESAMPLER_H
