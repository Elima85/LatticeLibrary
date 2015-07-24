#include "defs.h"
#include "string.h"
#include "image.h"
//#include "label.h"
//#include "priorityqueue.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

using namespace LatticeLib;

//
//int main(int argc, char *argv[]){
//	return 0;
//}

/*int wtfmain(int argc, char *argv[]) {


	int nR = 5, nC = 5, nL = 5;
	int N = nR*nC*nL;
	uint8 data[N];
	for (int i = 0; i < N; i++){
		data[i] = 0;
	}

	imagetypeBCC *imBCC = new imagetypeBCC(data, nR, nC, nL);
	vector<Neighbor> neighBCC;
	neighBCC = imBCC->get_neighbors(2,2,2,14);
	cout << "BCC center: " << imBCC->index2x(imBCC->rcl2index(2,2,2)) << ","<< imBCC->index2y(imBCC->rcl2index(2,2,2)) << ","<< imBCC->index2z(imBCC->rcl2index(2,2,2)) << ")" << endl;
	for (size_t i = 0; i < neighBCC.size(); i++){
		cout << "BCC n" << i << ": (" << imBCC->index2x(neighBCC[i].getElementIndex()) << ","<< imBCC->index2y(neighBCC[i].getIndex()) << ","<< imBCC->index2z(neighBCC[i].getIndex()) << ")" << endl;
	}

	return 0;
}*/

int main(int argc, char *argv[]) {
/*
	if (argc != 11) {
		cerr << "Usage: dist inputfile [c|b|f] #rows #columns #layers #bands #neighbors outputfile seedfile method" << endl;
		exit(1);
	}

	// read input parameters
	char lattice;
	int nR,nC,nL,nB,nN,nTot, method;
	char *infilename,*outfilename,*seedfilename;
	infilename = argv[1];
	lattice = *argv[2];
	nR = atoi(argv[3]);
	nC = atoi(argv[4]);
	nL = atoi(argv[5]);
	nB = atoi(argv[6]);
	nN = atoi(argv[7]);
	outfilename = argv[8];
	seedfilename = argv[9];
	method = atoi(argv[10]);
	nTot = nR * nC * nL;
	//cout << "lattice: " << lattice << "\n#rows: " << nR << "\n#columns: " << nC << "\n#layers: " << nL << "\n#bands: " << nB << "\nReading from " << infilename << " and writing to " << outfilename << endl;

	// read volume
	double *spelsD;
	spelsD = readVolume(infilename,nTot*nB);
	uint8 *spels = new uint8[nTot];
	for (int i = 0; i < nTot; i++) {
		spels[i] = (uint8)spelsD[i];
	}

	// create image object
    ::Image::Image<double> *input;
	switch(lattice) {
	case 'c':
		//    	cout << "CC lattice" << endl;
		input = new CImageCC<double>(spelsD, nR, nC, nL, nB);
		break;
	case 'b':
		//    	cout << "BCC lattice" << endl;
		input = new CImageBCC<double>(spelsD, nR, nC, nL, nB);
		break;
	case 'f':
		//    	cout << "FCC lattice" << endl;
		input = new CImageFCC<double>(spelsD, nR, nC, nL, nB);
		break;
	default:
		cerr << "Invalid lattice. Valid options are: {c,b,f}" << endl;
		exit(1);
	}

//	PNorm *norm = new PNorm(1); // only red band active
//	PNorm *norm = new PNorm(2); // only red band active
//	ProductNorm *norm = new ProductNorm(); // always differences of 64, 248, 247, except in the very beginning
	MaximumNorm *norm = new MaximumNorm(); // only red band active

	uint8 *seeds;
	double *seedsD;
	seedsD = readVolume(seedfilename,nTot*nB);
	seeds = new uint8[nTot];
	for (int i = 0; i < nTot; i++) {
		seeds[i] = (uint8)seedsD[i];
	}
//	seeds[0] = 1;
//	seeds[5050] = 2;
//	seeds[9999] = 3;

	uint8 *labels;
	labels = new uint8[nTot];

	double *dt;
	dt = new double[nTot];
	for (int i = 0; i < nTot; i++) {
		dt[i] = 0.0;
	}
	cout << "Entering distance transform..." << endl;
	switch(method) {
	case 1:
		approximateMinimumBarrierBoundingBox(input, seeds, norm, nN, labels, dt);
		break;
	case 2:
		fuzzyConnectedness(input, seeds, norm, nN, labels, dt);
		break;
	case 3:
		fuzzyDistance(input, seeds, norm, nN, labels, dt);
		break;
	case 4:
		geodesicDistance(input, seeds, norm, nN, labels, dt);
		break;
	default:
		cout << method << " is not a valid transform method." << endl;
	}
	cout << "Transform done." << endl;

	double *labelsD = new double[nTot];
	for (int i = 0; i < nTot; i++) {
		labelsD[i] = (double) labels[i];
		if (labels[i] == 0) {
			cout << "Element " << i << " doesn't have a label!" << endl;
		}
	}
	writeVolume(outfilename,labelsD,nTot);

	// clean up?
	delete[] spels;
	delete[] spelsD;
	delete[] dt;
	delete[] labels;
	delete[] labelsD;
	delete[] seeds;
	delete[] seedsD;
	delete input;
	delete norm;
*/
	return 0;
}
