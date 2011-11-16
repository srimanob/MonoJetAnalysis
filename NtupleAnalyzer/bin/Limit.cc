// ROOT includes
#include <TStyle.h>
#include <TROOT.h>

// std includes
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include "TH1D.h"

#include <TString.h>
#include <TFile.h>
#include <math.h>
#include <Python.h>



using namespace std;


const std::string outputDir = "";

int main(int argc, char ** argv)
{

	if ( argc < 7 ) {
		cerr << "Insufficient arguments: [histogram name] [options] [dataset1] [dataset2...]" << endl;
		return 1;
	}

 

}

