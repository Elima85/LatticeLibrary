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

	if (argc != 10) {
		cerr << "Usage: dist inputfile [c|b|f] #rows #columns #layers #bands #neighbors areafile volumefile" << endl;
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
	nN = atoi(argv[7]);
	areaFilename = argv[8];
	volumeFilename = argv[9];
	nTot = nR * nC * nL;
	//cout << "lattice: " << lattice << "\n#rows: " << nR << "\n#columns: " << nC << "\n#layers: " << nL << "\n#bands: " << nB << "\nReading from " << infilename << " and writing to " << areaFilename << endl;

	// read volume
	double *spelsD;
	spelsD = readVolume(infilename,nTot*nB);
	uint8 *spels = new uint8[nTot];
	for (int i = 0; i < nTot; i++) {
		spels[i] = (uint8)spelsD[i];
	}

	// create image object
	Lattice* imageLattice;
	switch(lattice) {
	case 'c':
		//    	cout << "CC lattice" << endl;
		imageLattice = new CCLattice(nR, nC, nL, 1.0);
		break;
	case 'b':
		//    	cout << "BCC lattice" << endl;
		imageLattice = new BCCLattice(nR, nC, nL, 1.0);
		break;
	case 'f':
		//    	cout << "FCC lattice" << endl;
		imageLattice = new FCCLattice(nR, nC, nL, 1.0);
		break;
	default:
		cerr << "Invalid lattice. Valid options are: {c,b,f}" << endl;
		exit(1);
	}
	Image<uint8> inputImage(spels, *imageLattice, nB);
	IntensityWorkset<uint8> fuzzyObject(inputImage, 0, 127);

	ObjectSurfaceAreaFromVoronoiCellIntersection<uint8> areaApproximation;
	double area = areaApproximation.compute(fuzzyObject, 0);
	std::ofstream areaFile;
	areaFile.open(areaFilename, std::ios_base::app);
	areaFile << area << "\n";
	areaFile.close();

	ObjectVolumeFromCoverage<uint8> volumeApproximation;
	double volume = volumeApproximation.compute(fuzzyObject, 0);
	std::ofstream volumeFile;
	volumeFile.open(volumeFilename, std::ios_base::app);
	volumeFile << volume << "\n";
	volumeFile.close();

	delete imageLattice;
	delete spels;
	delete spelsD;

	return 0;
}
