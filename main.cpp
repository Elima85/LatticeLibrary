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
using namespace std;

using namespace LatticeLib;

int main(int argc, char *argv[]) {

	if (argc != 9) {
		cerr << "Usage: dist inputfile [c|b|f] #rows #columns #layers #bands  areafile volumefile" << endl;
		exit(1);
	}

	// read input parameters
	char lattice;
	int nR,nC,nL,nB,nN,nTot;
	char *infilename,*areaFilename,*volumeFilename;
	infilename = argv[1];
	lattice = *argv[2];
	nR = atoi(argv[3]);
	nC = atoi(argv[4]);
	nL = atoi(argv[5]);
	nB = atoi(argv[6]);
	areaFilename = argv[7];
	volumeFilename = argv[8];
	nTot = nR * nC * nL;
	//cout << "lattice: " << lattice << "\n#rows: " << nR << "\n#columns: " << nC << "\n#layers: " << nL << "\n#bands: " << nB << "\nReading from " << infilename << " and writing to " << areaFilename << " and " << volumeFilename << endl;
	cout << infilename << endl;

	// read volume
	double *spels;
	spels = readVolume(infilename,nTot*nB);

	// create image object
	Lattice* imageLattice;
	switch(lattice) {
	case 'c':
		//cout << "CC lattice" << endl;
		imageLattice = new CCLattice(nR, nC, nL, 1.0);
		break;
	case 'b':
		//cout << "BCC lattice" << endl;
		imageLattice = new BCCLattice(nR, nC, nL, 1.0);
		break;
	case 'f':
		//cout << "FCC lattice" << endl;
		imageLattice = new FCCLattice(nR, nC, nL, 1.0);
		break;
	default:
		//cerr << "Invalid lattice. Valid options are: {c,b,f}" << endl;
		exit(1);
	}
	Image<double> inputImage(spels, *imageLattice, nB);
	IntensityWorkset<double> fuzzyObject(inputImage, 0.0, 1.0);
	//cout << "fuzzyObject: min = " << double(fuzzyObject.getMinIntensity()) << ", max = " << double(fuzzyObject.getMaxIntensity()) << ", data = " << long(fuzzyObject.getImage().getData()) << endl; // DEBUG

	ObjectSurfaceAreaFromVoronoiCellIntersection<double> areaApproximation;
	//cout << "computing area... " << endl; // DEBUG
	double area = areaApproximation.compute(fuzzyObject, 0);
	//cout << "area: " << area; // DEBUG
	std::ofstream areaFile;
	areaFile.open(areaFilename, std::ios_base::app);
	areaFile.write(reinterpret_cast<char*>(&area), sizeof(double));
	//areaFile << area << "\n";
	areaFile.close();

	ObjectVolumeFromCoverage<double> volumeApproximation;
	double volume = volumeApproximation.compute(fuzzyObject, 0);
	std::ofstream volumeFile;
	volumeFile.open(volumeFilename, std::ios_base::app);
	//volumeFile << volume << "\n";
	volumeFile.write(reinterpret_cast<char *>(&volume), sizeof(double));
	volumeFile.close();
	//cout << " and volume... " << volume << endl; // DEBUG
	//cout << "done!" << endl; // DEBUG

	delete imageLattice;
	delete spels;

	return 0;
}
