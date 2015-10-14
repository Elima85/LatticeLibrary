#include "defs.h"
#include "image.h"
#include "filehandling.h"
#include "lattice.h"
#include "cclattice.h"
#include "intensityworkset.h"
#include "objectsurfaceareafromvoronoicellintersection.h"
#include "objectvolumefromcoverage.h"
#include "seededdistancemeasure.h"
#include "approximateminimumbarrierdistance.h"
#include "fuzzyconnectedness.h"
#include "fuzzydistance.h"
#include "geodesicdistance.h"
#include "minimumbarrierdistance.h"
#include "norm.h"
#include "maximumnorm.h"
#include "pnorm.h"
#include "productnorm.h"
#include "seededdistancetransform.h"
#include "seed.h"
#include "segmentation.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
using namespace LatticeLib;

int main(int argc, char *argv[]) {

    //std::cout << "Running mrisegmentation.cpp..." << std::endl;
    if (argc != 12) {
        cerr << "#arguments = " << argc << endl;
        cerr <<
        "Usage: dist mrivolume.bin seeds.bin #rows #columns #layers #bands samplingdensity [a|c|f|g|m] [m|p|*] neighborhoodSize segmentation.bin" <<
        endl;
        exit(1);
    }
    // read input parameters
    char *volumeFilename, *seedsFilename, *segmentationFilename;
    char distanceMeasureType, normType;
    int nRows, nColumns, nLayers, nBands, neighborhoodSize;
    double inputDensity, outputDensity;
    volumeFilename = argv[1];
    seedsFilename = argv[2];
    nRows = atoi(argv[3]);
    nColumns = atoi(argv[4]);
    nLayers = atoi(argv[5]);
    nBands = atoi(argv[6]);
    inputDensity = atof(argv[7]);
    distanceMeasureType = *argv[8];
    normType = *argv[9];
    neighborhoodSize = atoi(argv[10]);
    segmentationFilename = argv[11];

    int nElements = nRows * nColumns * nLayers;

    // create input image
    double *volumeData;
    volumeData = readVolume(volumeFilename, nElements * nBands);
    CCLattice lattice(nRows, nColumns, nLayers, inputDensity);
    Image<double> inputImage(volumeData, lattice, nBands);

    // extract seed points
    int nLabels = 5;
    double *seedData;
    seedData = readVolume(seedsFilename, nElements * nLabels);
    Image<double> seedImage(seedData, lattice, nLabels);
    //int nPotentialSeeds = 0;
    //for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
    //    if (fabs(seedData[elementIndex]) > EPSILONT) {
    //        nPotentialSeeds++;
    //    }
    //}
    //cout << "#Potential seedpoints: " << nPotentialSeeds << endl;
    vector<vector<Seed> > seedPoints;
    vector<Seed> tmp;
    for (int label = 0; label < nLabels; label++) {
        tmp.clear();
        for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
            if (fabs(seedImage(elementIndex, label) - 1) < EPSILONT) {
                tmp.push_back(Seed(Seed(elementIndex, label)));
            }
        }
        seedPoints.push_back(tmp);
    }
    //std::cout << "Extracted seedpoints:" << std::endl;
    //std::cout << "\tlabel 1: " << seedPoints[0].size() << std::endl;
    //std::cout << "\tlabel 2: " << seedPoints[1].size() << std::endl;
    //std::cout << "\tlabel 3: " << seedPoints[2].size() << std::endl;
    //std::cout << "\tlabel 4: " << seedPoints[3].size() << std::endl;
    //std::cout << "\tlabel 5: " << seedPoints[4].size() << std::endl;

    // distance measure
    Norm<double> *norm;
    switch (normType) {
        case 'm':
            norm = new MaximumNorm<double>;
            break;
        case 'p':
            norm = new PNorm<double>(2);
            break;
        case '*':
            norm = new ProductNorm<double>;
            break;
        default:
            exit(1);
    }
    SeededDistanceMeasure<double> *distanceMeasure;
    switch (distanceMeasureType) {
        case 'a':
            distanceMeasure = new ApproximateMinimumBarrierDistance<double>(*norm);
            break;
        case 'c':
            distanceMeasure = new FuzzyConnectedness<double>(*norm);
            break;
        case 'f':
            distanceMeasure = new FuzzyDistance<double>(*norm);
            break;
        case 'g':
            distanceMeasure = new GeodesicDistance<double>;
            break;
        case 'm':
            distanceMeasure = new MinimumBarrierDistance<double>;
            break;
        default:
            exit(1);
    }

    // distance transform
    double *distanceTransformData = new double[nElements];
    Image<double> distanceImage(distanceTransformData, lattice, 1);
    int *rootData = new int[nElements];
    Image<int> rootImage(rootData, lattice, 1);
    SeededDistanceTransform seededDistanceTransform;
    seededDistanceTransform.applySingleLayer(inputImage, seedPoints, *distanceMeasure, neighborhoodSize, distanceImage, rootImage);
    writeVolume("distancetransform.bin", distanceTransformData, nElements);

    // segmentation
    Segmentation segmentation;
    double *fuzzySegmentationData = new double[nElements * nLabels];
    //double *fuzzySegmentationData = readVolume(segmentationFilename, nElements * nLabels);
    Image<double> fuzzySegmentationImage(fuzzySegmentationData, *lattice, nLabels);
    IntensityWorkset<double> fuzzySegmentation(fuzzySegmentationImage, 0, 1);
    // save segmentation
    segmentation.fuzzy(distanceImage, neighborhoodSize, fuzzySegmentation);
    writeVolume(segmentationFilename, fuzzySegmentationData, nElements * nLabels);

    ObjectSurfaceAreaFromVoronoiCellIntersection<double> surfaceAreaComputer;
    double area;
    area = surfaceAreaComputer.compute(fuzzySegmentation, 4);
    cout << "small tomato surface area: " << area << endl;
    area = surfaceAreaComputer.compute(fuzzySegmentation, 3);
    cout << "large tomato surface area: " << area << endl;
    area = surfaceAreaComputer.compute(fuzzySegmentation, 2);
    cout << "avocado surface area: " << area << endl;
    area = surfaceAreaComputer.compute(fuzzySegmentation, 1);
    cout << "margarine surface area: " << area << endl;

    ObjectVolumeFromCoverage<double> volumeComputer;
    double volume;
    volume = volumeComputer.compute(fuzzySegmentation, 4);
    cout << "small tomato volume: " << volume << endl;
    volume = volumeComputer.compute(fuzzySegmentation, 3);
    cout << "large tomato volume: " << volume << endl;
    volume = volumeComputer.compute(fuzzySegmentation, 2);
    cout << "avocado volume: " << volume << endl;
    volume = volumeComputer.compute(fuzzySegmentation, 1);
    cout << "margarine volume: " << volume << endl;

    delete seedData;
    delete volumeData;
    delete rootData;
    delete distanceTransformData;
    delete fuzzySegmentationData;
    delete norm;
    delete distanceMeasure;

    return 0;
}

