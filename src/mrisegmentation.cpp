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
    if (argc != 15) {
        cerr << "#arguments = " << argc << endl;
        cerr <<
        "Usage: segment mrivolume.bin seeds.bin [c|b|f] #rows #columns #layers #bands samplingdensity [a|c|f|g|m] [m|p|*] neighborhoodSize segmentation.bin areafile.bin volumefile.bin" << endl;
        exit(1);
    }
    // read input parameters
    char *inputFilename, *seedsFilename, *segmentationFilename, *areaFilename, *volumeFilename;
    char latticeType, distanceMeasureType, normType;
    int nRows, nColumns, nLayers, nBands, neighborhoodSize;
    double inputDensity, outputDensity;
    inputFilename = argv[1];
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
    areaFilename = argv[13];
    volumeFilename = argv[14];

    int nElements = nRows * nColumns * nLayers;

    // create input image
    double *volumeData;
    volumeData = readVolume(inputFilename, nElements * nBands);
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

    // extract seed points
    int nLabels = 5;
    double *seedData;
    seedData = readVolume(seedsFilename, nElements * nLabels);
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
    double *distanceTransformData = new double[nElements * nLabels];
    Image<double> distanceImage(distanceTransformData, *lattice, nLabels);
    int *rootData = new int[nElements * nLabels];
    Image<int> rootImage(rootData, *lattice, nLabels);
    SeededDistanceTransform seededDistanceTransform;
    seededDistanceTransform.apply(inputImage, seedPoints, *distanceMeasure, neighborhoodSize, distanceImage, rootImage);
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
    std::ofstream areaFile;
    areaFile.open(areaFilename, std::ios_base::app);
    double area;
    area = surfaceAreaComputer.compute(fuzzySegmentation, 4);
    areaFile.write(reinterpret_cast<char *>(&area), sizeof(double));
    cout << "small tomato surface area: " << area << endl;
    area = surfaceAreaComputer.compute(fuzzySegmentation, 3);
    areaFile.write(reinterpret_cast<char *>(&area), sizeof(double));
    cout << "large tomato surface area: " << area << endl;
    area = surfaceAreaComputer.compute(fuzzySegmentation, 2);
    areaFile.write(reinterpret_cast<char *>(&area), sizeof(double));
    cout << "avocado surface area: " << area << endl;
    area = surfaceAreaComputer.compute(fuzzySegmentation, 1);
    areaFile.write(reinterpret_cast<char *>(&area), sizeof(double));
    cout << "margarine surface area: " << area << endl;
    areaFile.close();

    ObjectVolumeFromCoverage<double> volumeComputer;
    std::ofstream volumeFile;
    volumeFile.open(volumeFilename, std::ios_base::app);
    double volume;
    volume = volumeComputer.compute(fuzzySegmentation, 4);
    volumeFile.write(reinterpret_cast<char *>(&volume), sizeof(double));
    cout << "small tomato volume: " << volume << endl;
    volume = volumeComputer.compute(fuzzySegmentation, 3);
    volumeFile.write(reinterpret_cast<char *>(&volume), sizeof(double));
    cout << "large tomato volume: " << volume << endl;
    volume = volumeComputer.compute(fuzzySegmentation, 2);
    volumeFile.write(reinterpret_cast<char *>(&volume), sizeof(double));
    cout << "avocado volume: " << volume << endl;
    volume = volumeComputer.compute(fuzzySegmentation, 1);
    volumeFile.write(reinterpret_cast<char *>(&volume), sizeof(double));
    cout << "margarine volume: " << volume << endl;
    volumeFile.close();

    delete lattice;
    delete seedData;
    delete volumeData;
    delete rootData;
    delete distanceTransformData;
    delete fuzzySegmentationData;
    delete norm;
    delete distanceMeasure;

    return 0;
}
