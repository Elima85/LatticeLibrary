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


	if (argc != 16) {
		cerr << "#arguments = " << argc << endl;
		cerr << "Usage: dist inputfile [c|b|f] #inputrows #inputcolumns #inputlayers #inputbands inputdensity outputfile [c|b|f] #outputrows #outputcolumns #outputlayers #outputbands outputdensity neighborhoodSize" << endl;
		exit(1);
	}

	// read input parameters
	char *inputFilename, *outputFilename;
	char inputLatticeType, outputLatticeType;
	int inputNRows, inputNColumns, inputNLayers, inputNBands, outputNRows, outputNColumns, outputNLayers, outputNBands, neighborhoodSize;
	double inputDensity, outputDensity;
	inputFilename = argv[1];
	inputLatticeType = *argv[2];
	inputNRows = atoi(argv[3]);
	inputNColumns = atoi(argv[4]);
	inputNLayers = atoi(argv[5]);
	inputNBands = atoi(argv[6]);
	inputDensity = atof(argv[7]);
	outputFilename = argv[8];
	outputLatticeType = *argv[9];
	outputNRows = atoi(argv[10]);
	outputNColumns = atoi(argv[11]);
	outputNLayers = atoi(argv[12]);
	outputNBands = atoi(argv[13]);
	outputDensity = atof(argv[14]);
	neighborhoodSize = atoi(argv[15]);
	int inputNDataPoints = inputNRows * inputNColumns * inputNLayers * inputNBands;
	cout << "#input data points: " << inputNDataPoints << endl;
	int outputNDataPoints = outputNRows * outputNColumns * outputNLayers * outputNBands;

	// create input image
	double *inputIntensities;
	inputIntensities = readVolume(inputFilename, inputNDataPoints);
	int NNZ = 0;
	for (int dataIndex = 0; dataIndex < inputNDataPoints; dataIndex++) {
		if (fabs(inputIntensities[dataIndex]) > EPSILONT) {
			NNZ++;
		}
	}
	cout << "#seeds: " << NNZ << endl;
	Lattice* inputLattice;
	switch(inputLatticeType) {
	case 'c':
		inputLattice = new CCLattice(inputNRows, inputNColumns, inputNLayers, inputDensity);
		break;
	case 'b':
		inputLattice = new BCCLattice(inputNRows, inputNColumns, inputNLayers, inputDensity);
		break;
	case 'f':
		inputLattice = new FCCLattice(inputNRows, inputNColumns, inputNLayers, inputDensity);
		break;
	default:
		exit(1);
	}
	Image<double> inputImage(inputIntensities, *inputLattice, inputNBands);
	cout << "Read input image:" << endl;
	inputImage.printParameters();
	vector<double> bandSum(inputImage.getNBands(), 0.0);
	for (int elementIndex = 0; elementIndex < inputImage.getNElements(); elementIndex++) {
		bandSum = bandSum + inputImage[elementIndex];
	}
	std::cout << "Sum of band elements: ";
	printVector(bandSum);

	// create output image
	double *outputIntensities = new double[outputNDataPoints];
	Lattice *outputLattice;
	switch (outputLatticeType) {
		case 'c':
			outputLattice = new CCLattice(outputNRows, outputNColumns, outputNLayers, outputDensity);
			break;
		case 'b':
			outputLattice = new BCCLattice(outputNRows, outputNColumns, outputNLayers, outputDensity);
			break;
		case 'f':
			outputLattice = new FCCLattice(outputNRows, outputNColumns, outputNLayers, outputDensity);
			break;
		default:
			exit(1);
	}
	Image<double> outputImage(outputIntensities, *outputLattice, outputNBands);
	cout << "Allocated output image:" << endl;
	outputImage.printParameters();

	ImageResampler<double> resampler;
	UniformWeight<double> weights;
	resampler.downsample(inputImage, weights, neighborhoodSize, outputImage);

	writeVolume(outputFilename, outputIntensities, outputNRows * outputNColumns * outputNLayers * outputNBands);

	//std::ofstream volumeFile;
	//volumeFile.open(volumeFilename, std::ios_base::app);
	//volumeFile.write(reinterpret_cast<char *>(&volume), sizeof(double));
	//volumeFile.close();

	delete inputLattice;
	delete inputIntensities;
	delete outputLattice;
	delete outputIntensities;

	return 0;
}
