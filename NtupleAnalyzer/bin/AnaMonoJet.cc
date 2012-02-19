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



	string logFileName = anaout + "/";
	logFileName += argv[1];
	logFileName += ".log";

	Manager manager(logFileName);



	string histFile = anaout + "/";
	histFile += argv[1];



	cout << "Starting to Run ........" << endl;
	

//---------------------------------------CUTS & Fill Hist--------------------------------------------------------------

	vector<int> abrun;
	vector<int> abevt;
	
	
	
	//CutAbnormalEvents  CAbnormalEvents(abrun , abevt);  manager.Add(&CAbnormalEvents);
	
	//CutHLT          CHLT(1); manager.Add(&CHLT);

 	hDataMcMatching  DataMcMatching0(histFile+"_AnaMonoJet_0.root"); manager.Add(&DataMcMatching0);
  
	CutMet CMet(200); manager.Add(&CMet);
 	hDataMcMatching  DataMcMatching1(histFile+"_AnaMonoJet_1.root"); manager.Add(&DataMcMatching1);
 

 	CutNoiseClean CNoiseClean( 0.95 , 0.98, 1,  0.01, 0.99); manager.Add(&CNoiseClean);
 	hDataMcMatching  DataMcMatching2(histFile+"_AnaMonoJet_2.root"); manager.Add(&DataMcMatching2);

	CutJet1 CJet1( 110 , 2.4,  0.02, 0.98); manager.Add(&CJet1);
 	hDataMcMatching  DataMcMatching3(histFile+"_AnaMonoJet_3.root"); manager.Add(&DataMcMatching3);
 
 	
	hHLTEff  HLTEff1(histFile+"_HLTEff1.root"); manager.Add(&HLTEff1);
 	
 
	CutNJet  CNJet(3); manager.Add(&CNJet);
	hDataMcMatching  DataMcMatching4(histFile+"_AnaMonoJet_4.root"); manager.Add(&DataMcMatching4);
 
 
 	CutDeltaPhi3  CDeltaPhi3(2.5);  manager.Add(&CDeltaPhi3);
 	hDataMcMatching  DataMcMatching5(histFile+"_AnaMonoJet_5.root"); manager.Add(&DataMcMatching5);
 

	hHLTEff  HLTEff2(histFile+"_HLTEff2.root"); manager.Add(&HLTEff2);


	//CutTIV CTIV(0.01); manager.Add(&CTIV);
	//hDataMcMatching  DataMcMatching8(histFile+"_AnaMonoJet_8.root"); manager.Add(&DataMcMatching8);


	//NoPFElec         CNoPFElec(10.);  manager.Add(&CNoPFElec);
        //hDataMcMatching  DataMcMatching7(histFile+"_AnaMonoJet_7.root"); manager.Add(&DataMcMatching7);



 	NoPFMuon        CNoPFMuon(10.);  manager.Add(&CNoPFMuon);
 	hDataMcMatching  DataMcMatching6(histFile+"_AnaMonoJet_6.root"); manager.Add(&DataMcMatching6);

 	NoPFElec         CNoPFElec(10.);  manager.Add(&CNoPFElec);
 	hDataMcMatching  DataMcMatching7(histFile+"_AnaMonoJet_7.root"); manager.Add(&DataMcMatching7);
 	

 	CutTIV CTIV(0.01); manager.Add(&CTIV);	
 	hDataMcMatching  DataMcMatching8(histFile+"_AnaMonoJet_8.root"); manager.Add(&DataMcMatching8);


	CutMet CMet2(250); manager.Add(&CMet2);
	hDataMcMatching  DataMcMatching9(histFile+"_AnaMonoJet_9.root"); manager.Add(&DataMcMatching9);


	CutMet CMet3(300); manager.Add(&CMet3);
	hDataMcMatching  DataMcMatching10(histFile+"_AnaMonoJet_10.root"); manager.Add(&DataMcMatching10);

	CutMet CMet4(350); manager.Add(&CMet4);
	hDataMcMatching  DataMcMatching11(histFile+"_AnaMonoJet_11.root"); manager.Add(&DataMcMatching11);


	CutMet CMet5(400); manager.Add(&CMet5);
	hDataMcMatching  DataMcMatching12(histFile+"_AnaMonoJet_12.root"); manager.Add(&DataMcMatching12);

	


//-------------------------------------------------------------------------------------------------------------------------

	cout << "Running over sample " << argv[1] << endl;

	
	EventData eventData(argv[1], nev, isMC); 



	// Loop over events
	manager.Run(eventData);

}
