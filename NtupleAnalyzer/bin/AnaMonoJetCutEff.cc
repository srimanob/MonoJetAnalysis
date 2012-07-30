////////////////////////////////////////////////////////////////////////////
//            nTuple Analysis Macro                                       //
////////////////////////////////////////////////////////////////////////////

#include "EventData.h"
#include "Operation.h"
#include "Histogram01.h"
#include "Histogram02.h"
#include "Constants.h"

// ROOT includes
#include <TStyle.h>
#include <TROOT.h>

// std includes
#include <fstream>
#include <string>

using namespace Operation;
using namespace Histogram01;
using namespace Histogram02;
using namespace Constants;
using namespace std;


int main(int argc, char ** argv) 
{
	if ( argc < 5 ) 
	{
		cerr << "Program need more than this parameter " << endl;
		cerr << "Example:  Analysis  sampleName(ex:wjets or met or ...)   maxEvents  cutNumber  isMC(0 or 1)  Analyis" << endl;
		return 1;
	}
	string anaout = Constants::outputDir; 
	anaout += "results/";
	anaout += argv[5];


	int nev;
	if ( argc >= 5 ) sscanf ( argv[2], "%d", &nev );
	else nev = 100000000;
	
	
	int  sel;
	sscanf(argv[3], "%d", &sel);
	string selName = argv[3];
	

	int  isMC;
	sscanf(argv[4], "%d", &isMC);


	std::string logFileName = anaout + "/";
	logFileName += argv[1];
	logFileName += ".log";


	Manager manager(logFileName);


	string histFile = anaout + "/";
	histFile += argv[1];


	cout << "Starting to Run ........" << endl;


//---------------------------------------CUTS & Fill Hist--------------------------------------------------------------


	vector<int> abrun;
	vector<int> abevt;
	
	
	//CutAbnormalEvents  CAbnormalEvents(abrun , abevt);            
	CutNoiseClean      CNoiseClean( 0.95 , 0.98, 1,  0.01, 0.99);
 
	//CutHLT             CHLT(0);
	CutJet1            CJet1( 110 , 2.4,  0.02, 0.98); 
	CutNJet            CNJet(3);
	CutDeltaPhi3       CDeltaPhi3(2.5); 
	CutMet             CMet(200,1);
	CutTIV             CTIV(0.01);
	NoPFMuon           CNoPFMuon(10.);
	NoPFElec           CNoPFElec(10.);

	//manager.Add(&CAbnormalEvents);
	if(sel!=1) manager.Add(&CNoiseClean);
	
	//if(sel!=1) manager.Add(&CHLT);
	if(sel!=2) manager.Add(&CJet1);
	if(sel!=3) manager.Add(&CNJet); 
	if(sel!=4) manager.Add(&CDeltaPhi3);
	if(sel!=5) manager.Add(&CMet );
	if(sel!=6) manager.Add(&CTIV );
	if(sel!=7) manager.Add(&CNoPFMuon);
	if(sel!=8) manager.Add(&CNoPFElec);

      
	
	hDataMcMatching  DataMcMatching(histFile+"_AnaMonoJetCutEff_" +selName + ".root");   manager.Add(&DataMcMatching);


//-------------------------------------------------------------------------------------------------------------------------

	cout << "Running over sample " << argv[1] << endl;

 
	EventData eventData(argv[1], nev, isMC); 




	// Loop over events
	manager.Run(eventData);

}
