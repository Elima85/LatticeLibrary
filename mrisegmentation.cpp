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


    if (argc != 13) {
        cerr << "#arguments = " << argc << endl;
        cerr <<
        "Usage: dist mrivolume.bin seeds.bin [c|b|f] #rows #columns #layers #bands samplingdensity [a|c|f|g|m] [m|p|*] neighborhoodSize segmentation.bin" << endl;
        exit(1);
    }

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
    int nElements = nRows * nColumns * nLayers;
    int nDataPoints = nElements * nBands;

    // create input image
    double *volumeData;
    volumeData = readVolume(volumeFilename, nDataPoints);
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
    cout << "Created input volume:" << endl;
    //inputImage.printParameters();

    // extract seed points
    int nLabels = 5;
    double *seedData;
    seedData = readVolume(seedsFilename, nElements * nLabels);
    cout << "#data points in seedData: " << nElements * nLabels << endl;
    Image<double> seedImage(seedData, *lattice, nLabels);
    int nPotentialSeeds = 0;
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        if (fabs(seedData[elementIndex]) > EPSILONT) {
            nPotentialSeeds++;
        }
    }
    cout << "#Potential seedpoints: " << nPotentialSeeds << endl;
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
    cout << "Extracted seedpoints:" << endl;
    cout << "\tlabel 1: " << seedPoints[0].size() << endl;
    cout << "\tlabel 2: " << seedPoints[1].size() << endl;
    cout << "\tlabel 3: " << seedPoints[2].size() << endl;
    cout << "\tlabel 4: " << seedPoints[3].size() << endl;
    cout << "\tlabel 5: " << seedPoints[4].size() << endl;

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
    cout << "Initialized distance measure." << endl;

    // distance transform
    double *distanceTransformData = new double[nElements * nLabels];
    Image<double> distanceImage(distanceTransformData, *lattice, nLabels);
    distanceImage.printParameters();
    int *rootData = new int[nElements * nLabels];
    Image<int> rootImage(rootData, *lattice, nLabels);
    rootImage.printParameters();
    SeededDistanceTransform seededDistanceTransform;
    seededDistanceTransform.apply(inputImage, seedPoints, *distanceMeasure, neighborhoodSize, distanceImage, rootImage);
    delete rootData;
    for (int dataIndex = 0; dataIndex < nElements * nLabels; dataIndex++) {
        double tmp = distanceTransformData[dataIndex];
        distanceTransformData[dataIndex] = 0.0;
        distanceTransformData[dataIndex] = tmp;
    }
    vector<double> bandSum(nLabels, 0.0);
    for (int elementIndex = 0; elementIndex < nElements; elementIndex++) {
        bandSum = bandSum + distanceImage[elementIndex];
    }
    std::cout << "Sum of distances: ";
    printVector(bandSum);
    std::cout << "saving " << nElements * nLabels << " elements..." << std::endl;
    writeVolume("distancetransform.bin", distanceTransformData, nElements * nLabels);
    //writeVolume(outputFilename, outputIntensities, outputNRows * outputNColumns * outputNLayers * outputNBands);
    cout << "Finished distance transform:" << endl;
    distanceImage.printParameters();

    // segmentation
    Segmentation segmentation;
    double *segmentationData = new double[nElements * nLabels];
    //bool *crispSegmentationData = new bool[nElements * nLabels];
    //Image<bool> segmentationImage(crispSegmentationData, *lattice, nLabels);
    //segmentation.crisp(distanceImage, segmentationImage);
    Image<double> segmentationImage(segmentationData, *lattice, nLabels);
    IntensityWorkset<double> fuzzySegmentation(segmentationImage, 0.0, 1.0);
    segmentation.fuzzy(distanceImage, 0.01, fuzzySegmentation);
    //for (int dataIndex = 0; dataIndex < nElements * nLabels; dataIndex++) {
    //    segmentationData[dataIndex] = double(crispSegmentationData[dataIndex]);
    //}
    writeVolume(segmentationFilename, segmentationData, nElements * nLabels);
    cout << "Finished segmentation:" << endl;
    //fuzzySegmentation.getImage().printParameters();

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
