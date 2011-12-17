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

// Define the output directory

int main(int argc, char ** argv) 
{
	if ( argc < 3 ) 
	{
		cerr << "Program need more than this parameter " << endl;
		cerr << "Example:   Analysis  sampleName(ex:wjets or met or ...)   maxEvents   isMC(0 or 1)" << endl;
		return 1;
	}

	string anaout = Constants::outputDir; 
	anaout += "results/";
	anaout += argv[4];


	int nev;
	if ( argc >= 3 ) sscanf ( argv[2], "%d", &nev );
	else nev = 100000000;
	

	int  isMC;
	sscanf(argv[3], "%d", &isMC);


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
	
	//hWSourceAnalysis WSourceAnalysis(histFile+"_WSource.root"); manager.Add(&WSourceAnalysis);
	

	hDataMcMatching  DataMcMatching0(histFile+"_AnaMuon_0.root"); manager.Add(&DataMcMatching0);

	CutMet CMet(200); manager.Add(&CMet);
	hDataMcMatching  DataMcMatching1(histFile+"_AnaMuon_1.root"); manager.Add(&DataMcMatching1);

	CutNoiseClean CNoiseClean( 0.95 , 0.98, 1,  0.01, 0.99); manager.Add(&CNoiseClean);
	hDataMcMatching  DataMcMatching2(histFile+"_AnaMuon_2.root"); manager.Add(&DataMcMatching2);

	hWZAnalysis      WZAnalysis1(histFile+"_WZAnalysis_1.root"); manager.Add(&WZAnalysis1); ///-------------

	CutJet1 CJet1( 110 , 2.4,  0.02, 0.98); manager.Add(&CJet1);
	hDataMcMatching  DataMcMatching3(histFile+"_AnaMuon_3.root"); manager.Add(&DataMcMatching3);


	CutNJet  CNJet(3); manager.Add(&CNJet);
	hDataMcMatching  DataMcMatching4(histFile+"_AnaMuon_4.root"); manager.Add(&DataMcMatching4);


 	CutDeltaPhi3  CDeltaPhi3(2.5);  manager.Add(&CDeltaPhi3);
 	hDataMcMatching  DataMcMatching5(histFile+"_AnaMuon_5.root"); manager.Add(&DataMcMatching5);


 	hWZAnalysis      WZAnalysis2(histFile+"_WZAnalysis_2.root"); manager.Add(&WZAnalysis2);///-------------


 	hWSourceAnalysis  WSourceAnalysis(histFile+"_hWSourceAnalysis.root"); manager.Add(&WSourceAnalysis);///-------------


	PFLepIso        CPFLepIso(20.);  manager.Add( &CPFLepIso );	
 	//IsoMuon    CIsoMuon(20.);  manager.Add( &CIsoMuon );

	hDataMcMatching  DataMcMatching6(histFile+"_AnaMuon_6.root"); manager.Add(&DataMcMatching6);

	//hWZAnalysis      WZAnalysis3(histFile+"_WZAnalysis_3.root"); manager.Add(&WZAnalysis3);///-------------

	
	CutMet CMet2(250); manager.Add(&CMet2);
	hDataMcMatching  DataMcMatching7(histFile+"_AnaMuon_7.root"); manager.Add(&DataMcMatching7);


	hWZAnalysis      WZAnalysis3(histFile+"_WZAnalysis_3.root"); manager.Add(&WZAnalysis3);///-------------


	CutMet CMet3(300); manager.Add(&CMet3);
	hDataMcMatching  DataMcMatching8(histFile+"_AnaMuon_8.root"); manager.Add(&DataMcMatching8);


	hWZAnalysis      WZAnalysis4(histFile+"_WZAnalysis_4.root"); manager.Add(&WZAnalysis4);///-------------


	CutMet CMet4(350); manager.Add(&CMet4);
	hDataMcMatching  DataMcMatching9(histFile+"_AnaMuon_9.root"); manager.Add(&DataMcMatching9);

	hWZAnalysis      WZAnalysis5(histFile+"_WZAnalysis_5.root"); manager.Add(&WZAnalysis5);///-------------


	CutMet CMet5(400); manager.Add(&CMet5);
 	hDataMcMatching  DataMcMatching10(histFile+"_AnaMuon_10.root"); manager.Add(&DataMcMatching10);

	hWZAnalysis      WZAnalysis6(histFile+"_WZAnalysis_6.root"); manager.Add(&WZAnalysis6);///-------------



//-------------------------------------------------------------------------------------------------------------------------

	cout << "Running over sample " << argv[1] << endl;

	
	EventData eventData(argv[1], nev, isMC); 



	// Loop over events
	manager.Run(eventData);

}
