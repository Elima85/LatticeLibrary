#include "defs.h"
#include "image.h"
#include "filehandling.h"
#include "lattice.h"
#include "cclattice.h"
#include "bcclattice.h"
#include "fcclattice.h"
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
    if (argc != 13) {
        cerr << "#arguments = " << argc << endl;
        cerr <<
        "Usage: dist mrivolume.bin seeds.bin [c|b|f] #rows #columns #layers #bands samplingdensity [a|c|f|g|m] [m|p|*] neighborhoodSize segmentation.bin" << endl;
        exit(1);
    }
    //std::cout << "Passed argument check." << std::endl;
    // read input parameters
    char *volumeFilename, *seedsFilename, *segmentationFilename;
    char latticeType, distanceMeasureType, normType;
    int nRows, nColumns, nLayers, nBands, neighborhoodSize;
    double inputDensity, outputDensity;
    volumeFilename = argv[1];
    seedsFilename = argv[2];
    latticeType = *argv[3];
    nRows = atoi(argv[4]);
    nColumns = atoi(argv[5]);
    nLayers = atoi(argv[6]);
    nBands = atoi(argv[7]);
    inputDensity = atof(argv[8]);
    distanceMeasureType = *argv[9];
    normType = *argv[10];
    neighborhoodSize = atoi(argv[11]);
    segmentationFilename = argv[12];
    //std::cout << "Read arguments." << std::endl;

    int nElements = nRows * nColumns * nLayers;

    // create input image
    double *volumeData;
    volumeData = readVolume(volumeFilename, nElements * nBands);
    Lattice *lattice;
    switch (latticeType) {
        case 'c':
            lattice = new CCLattice(nRows, nColumns, nLayers, inputDensity);
            break;
        case 'b':
            lattice = new BCCLattice(nRows, nColumns, nLayers, inputDensity);
            break;
        case 'f':
            lattice = new FCCLattice(nRows, nColumns, nLayers, inputDensity);
            break;
        default:
            exit(1);
    }
    Image<double> inputImage(volumeData, *lattice, nBands);
    //std::cout << "Created input volume:" << std::endl;
    inputImage.printParameters();

    // extract seed points
    int nLabels = 5;
    double *seedData;
    seedData = readVolume(seedsFilename, nElements * nLabels);
    //std::cout << "#data points in seedData: " << nElements * nLabels << std::endl;
    Image<double> seedImage(seedData, *lattice, nLabels);
    //int nPotentialSeeds = 0;
    //for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
    //    if (fabs(seedData[elementIndex]) > EPSILONT) {
    //        nPotentialSeeds++;
    //    }
    //}
    //cout << "#Potential seedpoints: " << nPotentialSeeds << endl;
    vector< vector<Seed> > seedPoints;
    vector<Seed> tmp;
    for (int label = 0; label < nLabels; label++) {
        tmp.clear();
        for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
            if (fabs(seedImage(elementIndex, label)-1) < EPSILONT) {
                tmp.push_back(Seed(Seed(elementIndex, label)));
            }
        }
        seedPoints.push_back(tmp);
    }
    delete seedData;
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
    //std::cout << "Initialized distance measure." << std::endl;

    // distance transform
    double *distanceTransformData = new double[nElements];
    Image<double> distanceImage(distanceTransformData, *lattice, 1);
    distanceImage.printParameters();

    int *rootData = new int[nElements];
    Image<int> rootImage(rootData, *lattice, 1);
    rootImage.printParameters();

    SeededDistanceTransform seededDistanceTransform;
    seededDistanceTransform.applySingleLayer(inputImage, seedPoints, *distanceMeasure, neighborhoodSize, distanceImage, rootImage);

    writeVolume("distancetransform.bin", distanceTransformData, nElements);
    double *rootDataDouble = new double[nElements];
    for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
        rootDataDouble[dataIndex] = double(rootData[dataIndex]);
    }

    writeVolume("roots.bin", rootDataDouble, nElements);

    //std::cout << "Finished distance transform." << std::endl;

    // segmentation
    Segmentation segmentation;
    int *crispSegmentationData = new int[nElements];
    Image<int> segmentationImage(crispSegmentationData, *lattice, 1);
    // save segmentation
    segmentation.crisp(rootImage, seedPoints, neighborhoodSize, segmentationImage);
    //std::cout << "Finished segmentation." << std::endl;
    double *segmentationData = new double[nElements];
    for (int dataIndex = 0; dataIndex < nElements; dataIndex++) {
        segmentationData[dataIndex] = double(crispSegmentationData[dataIndex]);
    }
    writeVolume(segmentationFilename, segmentationData, nElements);
    std::cout << "Finished segmentation." << std::endl;

    ObjectSurfaceAreaFromVoronoiCellIntersection<double> surfaceArea;
    //cout << "small tomato surface area: " << surfaceArea.compute(fuzzySegmentation, 5) << endl;
    //cout << "large tomato surface area: " << surfaceArea.compute(fuzzySegmentation, 4) << endl;
    //cout << "avocado surface area: " << surfaceArea.compute(fuzzySegmentation, 3) << endl;
    ObjectVolumeFromCoverage<double> volume;
    //cout << "small tomato volume: " << volume.compute(fuzzySegmentation, 5) << endl;
    //cout << "large tomato volume: " << volume.compute(fuzzySegmentation, 4) << endl;
    //cout << "avocado volume: " << volume.compute(fuzzySegmentation, 3) << endl;

    //std::ofstream volumeFile;
    //volumeFile.open(volumeFilename, std::ios_base::app);
    //volumeFile.write(reinterpret_cast<char *>(&volume), sizeof(double));
    //volumeFile.close();

    delete lattice;
    delete volumeData;
    delete distanceTransformData;
    delete segmentationData;
    delete norm;
    delete distanceMeasure;

    return 0;
}
