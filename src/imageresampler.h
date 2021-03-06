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
    /**
     * Class for resampling image data from one lattice to another.
     *
     * The origins of the input and output images are aligned. If the input image is smaller than the output image,
     * only the existing elements of the input image are used, and elements of the output image that do not contain any
     * input image elements are set to zero intensity. If the output image is smaller than the input image, only part
     * of the input image is used.
     */
    template<class intensityTemplate>
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

            vector<double> bandSum(inputImage.getNBands(), 0.0);
            for (int elementIndex = 0; elementIndex < inputImage.getNElements(); elementIndex++) {
                bandSum = bandSum + inputImage[elementIndex];
            }

            double newElementWidth = outputImage.getLattice().getElementWidth();
            double oldElementWidth = inputImage.getLattice().getElementWidth();
            double columnHalfChunk = ceil(0.5 * newElementWidth / oldElementWidth);
            double newElementHeight = outputImage.getLattice().getElementHeight();
            double oldElementHeight = inputImage.getLattice().getElementHeight();
            double rowHalfChunk = ceil(0.5 * newElementHeight / oldElementHeight);
            double newElementDepth = outputImage.getLattice().getElementDepth();
            double oldElementDepth = inputImage.getLattice().getElementDepth();
            double layerHalfChunk = ceil(0.5 * newElementDepth / oldElementDepth);

            for (int newLayerIndex = 0; newLayerIndex < newNLayers; newLayerIndex++) {
                for (int newRowIndex = 0; newRowIndex < newNRows; newRowIndex++) {
                    for (int newColumnIndex = 0; newColumnIndex < newNColumns; newColumnIndex++) {
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
                        int closestOldElement = inputImage.getLattice().coordinatesToIndex(newElementPosition);
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
                                for (int oldLayerIndex = oldLayerIndexStart; oldLayerIndex < oldLayerIndexStop; oldLayerIndex++) {
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
                        outputImage.setElement(newElementIndex, 1 / MAX(double(nOldElementsInNewVoronoiRegion),1.0) * accumulatedIntensity);
                    }
                }
            }
        }
    };
}

#endif //LATTICELIBRARY_IMAGERESAMPLER_H
