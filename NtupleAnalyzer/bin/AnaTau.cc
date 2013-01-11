////////////////////////////////////////////////////////////////////////////
//            nTuple Analysis Macro                                       //
////////////////////////////////////////////////////////////////////////////

#include "EventData.h"
#include "Operation.h"
#include "Histogram01.h"
#include "Histogram02.h"
#include "HistogramMET.h"
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
using namespace HistogramMET;
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
  
  CutHLT             CHLT(0);  manager.Add(&CHLT);
  CutAbnormalEvents  CAbnormalEvents(abrun , abevt);  manager.Add(&CAbnormalEvents);
  hTauAnalysis       TauAnalysis0(histFile+"_AnaHadronicTau_0.root"); manager.Add(&TauAnalysis0);   

  CutMet             CMet(200); manager.Add(&CMet);
  hTauAnalysis       TauAnalysis1(histFile+"_AnaHadronicTau_1.root"); manager.Add(&TauAnalysis1); 
  
  CutNoiseClean      CNoiseClean( 0.95 , 0.98, 1,  0.01, 0.99); manager.Add(&CNoiseClean);
  CutHLT             CHLT1(1); manager.Add(&CHLT1);
  hTauAnalysis       TauAnalysis2(histFile+"_AnaHadronicTau_2.root"); manager.Add(&TauAnalysis2);
  
  CutJet1            CJet1( 110 , 2.4,  0.02, 0.98); manager.Add(&CJet1);
  hTauAnalysis       TauAnalysis3(histFile+"_AnaHadronicTau_3.root"); manager.Add(&TauAnalysis3);
  
  CutNJet            CNJet(3); manager.Add(&CNJet);
  hTauAnalysis       TauAnalysis4(histFile+"_AnaHadronicTau_4.root"); manager.Add(&TauAnalysis4);
  
  CutDeltaPhi3       CDeltaPhi3(2.5);  manager.Add(&CDeltaPhi3);
  hTauAnalysis       TauAnalysis5(histFile+"_AnaHadronicTau_5.root"); manager.Add(&TauAnalysis5);
  
  NoPFMuon           CNoPFMuon(10., 66.);  manager.Add(&CNoPFMuon); // no cut on eta
  hTauAnalysis       TauAnalysis6(histFile+"_AnaHadronicTau_6.root"); manager.Add(&TauAnalysis6);
  
  NoPFElec           CNoPFElec(10., 66.);  manager.Add(&CNoPFElec); // no cut on eta
  hTauAnalysis       TauAnalysis7(histFile+"_AnaHadronicTau_7.root"); manager.Add(&TauAnalysis7);
  
  //CutTIV             CTIV(0.01); manager.Add(&CTIV);	
  //hTauAnalysis       TauAnalysis8(histFile+"_AnaHadronicTau_8.root"); manager.Add(&TauAnalysis8);

  //CutTau             CTau(1,1); manager.Add(&CTau);
  //hTauAnalysis       TauAnalysis8(histFile+"_AnaHadronicTau_8.root"); manager.Add(&TauAnalysis8);

  CutMet             CMet2(250); manager.Add(&CMet2);
  hTauAnalysis       TauAnalysis9(histFile+"_AnaHadronicTau_9.root"); manager.Add(&TauAnalysis9);
  
  CutMet             CMet3(300); manager.Add(&CMet3);
  hTauAnalysis       TauAnalysis10(histFile+"_AnaHadronicTau_10.root"); manager.Add(&TauAnalysis10);
  
  CutMet             CMet4(350); manager.Add(&CMet4);
  hTauAnalysis       TauAnalysis11(histFile+"_AnaHadronicTau_11.root"); manager.Add(&TauAnalysis11);
  
  CutMet             CMet5(400); manager.Add(&CMet5);
  hTauAnalysis       TauAnalysis12(histFile+"_AnaHadronicTau_12.root"); manager.Add(&TauAnalysis12);
  
  CutMet             CMet6(450); manager.Add(&CMet6);
  hTauAnalysis       TauAnalysis13(histFile+"_AnaHadronicTau_13.root"); manager.Add(&TauAnalysis13);
  
  CutMet             CMet7(500); manager.Add(&CMet7);
  hTauAnalysis       TauAnalysis14(histFile+"_AnaHadronicTau_14.root"); manager.Add(&TauAnalysis14);
  
  CutMet             CMet8(550); manager.Add(&CMet8);
  hTauAnalysis       TauAnalysis15(histFile+"_AnaHadronicTau_15.root"); manager.Add(&TauAnalysis15);
  
  //-------------------------------------------------------------------------------------------------------------------------
  
  cout << "Running over sample " << argv[1] << endl;
  
  
  EventData eventData(argv[1], nev, isMC);
  
  // Loop over events
  manager.Run(eventData);
  
}
