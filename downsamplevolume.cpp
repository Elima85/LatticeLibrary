#include "defs.h"
#include "image.h"
#include "filehandling.h"
#include "lattice.h"
#include "cclattice.h"
#include "bcclattice.h"
#include "fcclattice.h"
#include "intensityworkset.h"
#include "objectvolumefromcoverage.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string.h>
#include "imageresampler.h"
#include "uniformweight.h"

using namespace std;
using namespace LatticeLib;

int main(int argc, char *argv[]) {


    if (argc != 17) {
        cerr << "#arguments = " << argc << endl;
        cerr <<
        "Usage: dist inputfile inputlatticetype #inputrows #inputcolumns #inputlayers #inputbands inputdensity " <<
                "outputlatticetype #outputrows #outputcolumns #outputlayers #outputbands outputdensity " <<
                "lowResNeighborhoodSize ouputvolumefile resultfile" << endl;
        exit(1);
    }

    // read input parameters
    char *highResDataFilename, *volumeFilename, *resultFilename;
    char highResLatticeType, lowResLatticeType;
    int highResNRows, highResNColumns, highResNLayers, highResNBands, lowResNRows, lowResNColumns, lowResNLayers, lowResNBands, lowResNeighborhoodSize;
    double highResDensity, lowResDensity;
    highResDataFilename = argv[1];
    highResLatticeType = *argv[2];
    highResNRows = atoi(argv[3]);
    highResNColumns = atoi(argv[4]);
    highResNLayers = atoi(argv[5]);
    highResNBands = atoi(argv[6]);
    highResDensity = atof(argv[7]);
    lowResLatticeType = *argv[8];
    lowResNRows = atoi(argv[9]);
    lowResNColumns = atoi(argv[10]);
    lowResNLayers = atoi(argv[11]);
    lowResNBands = atoi(argv[12]);
    lowResDensity = atof(argv[13]);
    lowResNeighborhoodSize = atoi(argv[14]);
    volumeFilename = argv[15];
    resultFilename = argv[16];
    int highResNDataPoints = highResNRows * highResNColumns * highResNLayers * highResNBands;
    int lowResNDataPoints = lowResNRows * lowResNColumns * lowResNLayers * lowResNBands;

    // create input image
    double *highResData;
    highResData = readVolume(highResDataFilename, highResNDataPoints);
    int NNZ = 0;
    for (int dataIndex = 0; dataIndex < highResNDataPoints; dataIndex++) {
        if (fabs(highResData[dataIndex]) > EPSILONT) {
            NNZ++;
        }
    }
    cout << "#nz elements: " << NNZ << endl;
    Lattice *highResLattice;
    switch (highResLatticeType) {
        case 'c':
            highResLattice = new CCLattice(highResNRows, highResNColumns, highResNLayers, highResDensity);
            break;
        case 'b':
            highResLattice = new BCCLattice(highResNRows, highResNColumns, highResNLayers, highResDensity);
            break;
        case 'f':
            highResLattice = new FCCLattice(highResNRows, highResNColumns, highResNLayers, highResDensity);
            break;
        default:
            exit(1);
    }
    Image<double> highResImage(highResData, *highResLattice, highResNBands);
    cout << "Read input image:" << endl;
    highResImage.printParameters();
    //vector<double> bandSum(highResImage.getNBands(), 0.0);
    //for (int elementIndex = 0; elementIndex < highResImage.getNElements(); elementIndex++) {
    //    bandSum = bandSum + highResImage[elementIndex];
    //}
    //std::cout << "Sum of band elements: ";
    //printVector(bandSum);

    // create output image
    double *lowResIntensities = new double[lowResNDataPoints];
    Lattice *lowResLattice;
    switch (lowResLatticeType) {
        case 'c':
            lowResLattice = new CCLattice(lowResNRows, lowResNColumns, lowResNLayers, lowResDensity);
            break;
        case 'b':
            lowResLattice = new BCCLattice(lowResNRows, lowResNColumns, lowResNLayers, lowResDensity);
            break;
        case 'f':
            lowResLattice = new FCCLattice(lowResNRows, lowResNColumns, lowResNLayers, lowResDensity);
            break;
        default:
            exit(1);
    }
    Image<double> lowResImage(lowResIntensities, *lowResLattice, lowResNBands);
    cout << "Allocated output image:" << endl;
    lowResImage.printParameters();

    ImageResampler<double> resampler;
    UniformWeight<double> weights;
    resampler.downsample(highResImage, weights, lowResNeighborhoodSize, lowResImage);
    writeVolume(volumeFilename, lowResIntensities, lowResNDataPoints);
    IntensityWorkset<double> lowResFuzzySegmentation(lowResImage, 0, 1);

    ObjectVolumeFromCoverage<double> volumeComputer;
    double volume = volumeComputer.compute(lowResFuzzySegmentation, 0);

    std::ofstream resultFile;
    resultFile.open(resultFilename, std::ios_base::app);
    resultFile.write(reinterpret_cast<char *>(&volume), sizeof(double));
    resultFile.close();

    delete highResLattice;
    delete highResData;
    delete lowResLattice;
    delete lowResIntensities;

    return 0;
}
