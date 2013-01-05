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
	//GenParExist CGenParExist(13);     manager.Add(&CGenParExist);
	
	CutHLT             CHLT(0);                                       manager.Add(&CHLT);
	CutAbnormalEvents  CAbnormalEvents(abrun , abevt);                manager.Add(&CAbnormalEvents);
	hDataMcMatching    DataMcMatching0(histFile+"_AnaMuon_0.root");   manager.Add(&DataMcMatching0);

	CutMet             CMet(200);                                     manager.Add(&CMet);
	hDataMcMatching    DataMcMatching1(histFile+"_AnaMuon_1.root");   manager.Add(&DataMcMatching1);
	
	CutNoiseClean      CNoiseClean( 0.95 , 0.98, 1,  0.01, 0.99);     manager.Add(&CNoiseClean);
	CutHLT             CHLT1(1);                                      manager.Add(&CHLT1);
	hDataMcMatching    DataMcMatching2(histFile+"_AnaMuon_2.root");   manager.Add(&DataMcMatching2);
	hWZAnalysis        WZAnalysis0(histFile+"_WZAnalysis_0.root");    manager.Add(&WZAnalysis0); ///-------------
	hTauAnalysis       TauAnalysis0(histFile+"_TauAnalysis_0.root");  manager.Add(&TauAnalysis0);///-------------
	
	CutJet1            CJet1( 110 , 2.4,  0.02, 0.98);                manager.Add(&CJet1);
	hDataMcMatching    DataMcMatching3(histFile+"_AnaMuon_3.root");   manager.Add(&DataMcMatching3);

	CutNJet            CNJet(3);                                      manager.Add(&CNJet);
	hDataMcMatching    DataMcMatching4(histFile+"_AnaMuon_4.root");   manager.Add(&DataMcMatching4);

 	CutDeltaPhi3       CDeltaPhi3(2.5);                               manager.Add(&CDeltaPhi3);
 	hDataMcMatching    DataMcMatching5(histFile+"_AnaMuon_5.root");   manager.Add(&DataMcMatching5);
 	hWZAnalysis        WZAnalysis1(histFile+"_WZAnalysis_1.root");    manager.Add(&WZAnalysis1);///-------------
	hTauAnalysis       TauAnalysis1(histFile+"_TauAnalysis_1.root");  manager.Add(&TauAnalysis1);///-------------
 	hWSourceAnalysis   WSourceAnalysis(histFile+"_hWSourceAnalysis.root"); manager.Add(&WSourceAnalysis);///-------------

	//PFLepIso           CPFLepIso(20.);                                manager.Add( &CPFLepIso );	
	//WsignSelection     CWsignSelection(1.0);                          manager.Add( & CWsignSelection );
	hDataMcMatching    DataMcMatching6(histFile+"_AnaMuon_6.root");   manager.Add(&DataMcMatching6);
	hWZAnalysis        WZAnalysis2(histFile+"_WZAnalysis_2.root");    manager.Add(&WZAnalysis2);///-------------
	hTauAnalysis       TauAnalysis2(histFile+"_TauAnalysis_2.root");  manager.Add(&TauAnalysis2);///-------------

	//CutTIV             CTIV(0.01);                                    manager.Add(&CTIV);

	CutMet             CMet2(250);                                    manager.Add(&CMet2);
	hDataMcMatching    DataMcMatching7(histFile+"_AnaMuon_7.root");   manager.Add(&DataMcMatching7);
	hWZAnalysis        WZAnalysis3(histFile+"_WZAnalysis_3.root");    manager.Add(&WZAnalysis3);///-------------
	hTauAnalysis       TauAnalysis3(histFile+"_TauAnalysis_3.root");  manager.Add(&TauAnalysis3);///-------------

	CutMet             CMet3(300);                                    manager.Add(&CMet3);
	hDataMcMatching    DataMcMatching8(histFile+"_AnaMuon_8.root");   manager.Add(&DataMcMatching8);
	hWZAnalysis        WZAnalysis4(histFile+"_WZAnalysis_4.root");    manager.Add(&WZAnalysis4);///-------------
	hTauAnalysis       TauAnalysis4(histFile+"_TauAnalysis_4.root");  manager.Add(&TauAnalysis4);///-------------

	CutMet             CMet4(350);                                    manager.Add(&CMet4);
	hDataMcMatching    DataMcMatching9(histFile+"_AnaMuon_9.root");   manager.Add(&DataMcMatching9);
	hWZAnalysis        WZAnalysis5(histFile+"_WZAnalysis_5.root");    manager.Add(&WZAnalysis5);///-------------
	hTauAnalysis       TauAnalysis5(histFile+"_TauAnalysis_5.root");  manager.Add(&TauAnalysis5);///-------------

	CutMet             CMet5(400);                                    manager.Add(&CMet5);
 	hDataMcMatching    DataMcMatching10(histFile+"_AnaMuon_10.root"); manager.Add(&DataMcMatching10);
	hWZAnalysis        WZAnalysis6(histFile+"_WZAnalysis_6.root");    manager.Add(&WZAnalysis6);///-------------
	hTauAnalysis       TauAnalysis6(histFile+"_TauAnalysis_6.root");  manager.Add(&TauAnalysis6);///-------------

        CutMet             CMet6(450);                                    manager.Add(&CMet6);
        hWZAnalysis        WZAnalysis7(histFile+"_WZAnalysis_7.root");    manager.Add(&WZAnalysis7);///-------------
	hTauAnalysis       TauAnalysis7(histFile+"_TauAnalysis_7.root");  manager.Add(&TauAnalysis7);///-------------

        CutMet             CMet7(500);                                    manager.Add(&CMet7);
        hWZAnalysis        WZAnalysis8(histFile+"_WZAnalysis_8.root");    manager.Add(&WZAnalysis8);///-------------
	hTauAnalysis       TauAnalysis8(histFile+"_TauAnalysis_8.root");  manager.Add(&TauAnalysis8);///-------------

        CutMet             CMet8(550);                                    manager.Add(&CMet8);
        hWZAnalysis        WZAnalysis9(histFile+"_WZAnalysis_9.root");    manager.Add(&WZAnalysis9);///-------------
	hTauAnalysis       TauAnalysis9(histFile+"_TauAnalysis_9.root");  manager.Add(&TauAnalysis9);///-------------



//-------------------------------------------------------------------------------------------------------------------------

	cout << "Running over sample " << argv[1] << endl;

	
	EventData eventData(argv[1], nev, isMC); 



	// Loop over events
	manager.Run(eventData);

}
