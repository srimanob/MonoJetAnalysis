#include "Operation.h"
#include "Histogram01.h"
#include <iostream>
#include <fstream>

#include <TH1D.h>
#include <math.h>

#include "TStyle.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TLegend.h>

#include "TTree.h"
#include "TDirectory.h"
#include "TKey.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TProfile.h"
#include "Constants.h"

#include <TLorentzVector.h>

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

using namespace std;
using namespace Operation;
using namespace Constants;

namespace Histogram01 
{
	///----------------HLT Histograms  Defination--------------------------------------------------------------------------------

	hHLTEff::hHLTEff(const std::string & fileName):
	mFileName(fileName)
	{
		fileOut = new TFile(mFileName.c_str(),"recreate");
		
		histo1D["MET_80"]       = new TH1D("MET_80"      ,"MET80"     , 50, 0, 1000);
		histo1D["MET_All"]      = new TH1D("MET_All"     ,"MET"       , 50, 0, 1000);
		histo1D["Jet1Pt_80"]    = new TH1D("Jet1Pt_80"   ,"Jet1Pt80"  , 50, 0, 1000);
		histo1D["Jet1Pt_All"]   = new TH1D("Jet1Pt_All"  ,"Jet1Pt"    , 50, 0, 1000);

		histo1D["MET_80_Eff"]       = new TH1D("MET_80_Eff"      ,"MET80"     , 50, 0, 1000);
		histo1D["Jet1Pt_80_Eff"]    = new TH1D("Jet1Pt_80_Eff"   ,"Jet1Pt80"  , 50, 0, 1000);
	}


	/// ---------------HLT Eff Histograms Filling----------------------------------------------------------------------------

	bool hHLTEff::Process(EventData & ev) 
	{
		int t = ev.MetType();
		//int njets = JetNumber(ev);
		int ixjet1= JetIndex(0, ev);
		//int ixjet2= JetIndex(1, ev);	
		double w= ev.Weight();



		if(ev.run() < 178381 )
		{
			int flg_trg80=0;
			string strtrg = ev.HLTNames();
			if (strtrg.find("HLT_CentralJet80_MET80")!=string::npos ) flg_trg80=1;
	

			if( flg_trg80==1 )  
			{
			  histo1D["Jet1Pt_80"]->Fill( ev.PFAK5JetPtCor(ixjet1) ,w );
			  histo1D["MET_80"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ),w );
			}

			histo1D["Jet1Pt_All"]->Fill( ev.PFAK5JetPtCor(ixjet1),w );
			histo1D["MET_All"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) ,w );

		}


		return true;
	}
	
	std::ostream& hHLTEff::Description(std::ostream &ostrm) 
	{
		ostrm << "  HLTEff (output in " << mFileName << "):";

		return ostrm;
	}


	hHLTEff::~hHLTEff() 
	{

		histo1D["MET_80_Eff"]->Divide( histo1D["MET_80"], histo1D["MET_All"] , 1.0, 1.0 );
		histo1D["Jet1Pt_80_Eff"]->Divide( histo1D["Jet1Pt_80"], histo1D["Jet1Pt_All"] , 1.0, 1.0 );


		fileOut->Write();
		delete fileOut;
		
	}
	
	


///===========================================================================================================

	

	///----------------Data MC Matching Histograms Defination -------------------------------------------------

	hDataMcMatching::hDataMcMatching(const std::string & fileName):
	mFileName(fileName)
	{
		fileOut = new TFile(mFileName.c_str(),"recreate");


		//pf noise clean for leading jet
		histo1D["PFAK5JetChaHadEngFrac"]      = new TH1D("PFAK5JetChaHadEngFrac"    , "PFAK5JetChaHadEngFrac" , 60,  0., 1.2);
		histo1D["PFAK5JetNeuHadEngFrac"]      = new TH1D("PFAK5JetNeuHadEngFrac"    , "PFAK5JetNeuHadEngFrac" , 60, -0.1, 1.1);
		histo1D["PFAK5JetChaEmEngFrac"]       = new TH1D("PFAK5JetChaEmEngFrac"     , "PFAK5JetChaEmEngFrac " , 60, -0.1, 1.1);
		histo1D["PFAK5JetNeuEmEngFrac"]       = new TH1D("PFAK5JetNeuEmEngFrac"     , "PFAK5JetNeuEmEngFrac " , 60, -0.1, 1.1);

		//pf noise clean for leading jet
		histo1D["PFAK5JetChaHadEngFrac150"]   = new TH1D("PFAK5JetChaHadEngFrac150" , "PFAK5JetChaHadEngFrac" , 60,  0., 1.2);
		histo1D["PFAK5JetNeuHadEngFrac150"]   = new TH1D("PFAK5JetNeuHadEngFrac150" , "PFAK5JetNeuHadEngFrac" , 60, -0.1, 1.1);
		histo1D["PFAK5JetChaEmEngFrac150"]    = new TH1D("PFAK5JetChaEmEngFrac150"  , "PFAK5JetChaEmEngFrac " , 60, -0.1, 1.1);
		histo1D["PFAK5JetNeuEmEngFrac150"]    = new TH1D("PFAK5JetNeuEmEngFrac150"  , "PFAK5JetNeuEmEngFrac " , 60, -0.1, 1.1);


		//pf noise clean for leading jet
		histo1D["PFAK5JetChaHadEngFrac300"]   = new TH1D("PFAK5JetChaHadEngFrac300" , "PFAK5JetChaHadEngFrac" , 60,  0., 1.2);
		histo1D["PFAK5JetNeuHadEngFrac300"]   = new TH1D("PFAK5JetNeuHadEngFrac300" , "PFAK5JetNeuHadEngFrac" , 60, -0.1, 1.1);
		histo1D["PFAK5JetChaEmEngFrac300"]    = new TH1D("PFAK5JetChaEmEngFrac300"  , "PFAK5JetChaEmEngFrac " , 60, -0.1, 1.1);
		histo1D["PFAK5JetNeuEmEngFrac300"]    = new TH1D("PFAK5JetNeuEmEngFrac300"  , "PFAK5JetNeuEmEngFrac " , 60, -0.1, 1.1);

		//pf noise clean  for second jet
		histo1D["PFAK5JetChaHadEngFrac2"]     = new TH1D("PFAK5JetChaHadEngFrac2"   , "PFAK5JetChaHadEngFrac-2" , 60,  0., 1.2);
		histo1D["PFAK5JetNeuHadEngFrac2"]     = new TH1D("PFAK5JetNeuHadEngFrac2"   , "PFAK5JetNeuHadEngFrac-2" , 60, -0.1, 1.1);
		histo1D["PFAK5JetChaEmEngFrac2"]      = new TH1D("PFAK5JetChaEmEngFrac2"    , "PFAK5JetChaEmEngFrac-2"  , 60, -0.1, 1.1);
		histo1D["PFAK5JetNeuEmEngFrac2"]      = new TH1D("PFAK5JetNeuEmEngFrac2"    , "PFAK5JetNeuEmEngFrac-2"  , 60, -0.1, 1.1);

		//PV
		histo1D["NPV"]              = new TH1D("NPV"            , "NPV "                , 25, 0, 25);
		histo1D["PVx"]              = new TH1D("PVx"            , "PV x"                , 100, -1, 1);
		histo1D["PVy"]              = new TH1D("PVy"            , "PV y"                , 200, -2, 2);
		histo1D["PVz"]              = new TH1D("PVz"            , "PV z"                , 1000, -10, 10);
		histo1D["PVR"]              = new TH1D("PVR"            , "PV R"                , 300, 0, 30);
		histo1D["PVndof"]           = new TH1D("PVndof"         , "PV ndof"             , 300, 0, 30);
		histo1D["PVchi2"]           = new TH1D("PVchi2"         , "PV chi2"             , 300, 0, 30);
		histo1D["PVntracks"]        = new TH1D("PVntracks"      , "PV nTracks"          , 70, 0, 70);
		

		//jet1 
		histo1D["Jet1Pt"]           = new TH1D("Jet1Pt"         , "Jet1Pt "             , 40, 0, 1000);
		histo1D["Jet1PtThrs"]       = new TH1D("Jet1PtThrs"     , "Jet1Pt "             , 40, 0, 1000);
		histo1D["Jet1Emf"]          = new TH1D("Jet1Emf"        , "Jet1Emf"             , 300,-1, 2);

		histo1D["Jet1Pt_1"]           = new TH1D("Jet1Pt_1"         , "Jet1Pt "             , 40, 0, 1000);
		histo1D["Jet1Pt_2"]           = new TH1D("Jet1Pt_2"         , "Jet1Pt "             , 40, 0, 1000);
		histo1D["Jet1Pt_3"]           = new TH1D("Jet1Pt_3"         , "Jet1Pt "             , 40, 0, 1000);

		histo1D["Jet1Eta_1"]          = new TH1D("Jet1Eta_1"        , "Jet1Eta "            , 36, -3.6, 3.6);
		histo1D["Jet1Eta_2"]          = new TH1D("Jet1Eta_2"        , "Jet1Eta "            , 36, -3.6, 3.6);
		histo1D["Jet1Eta_3"]          = new TH1D("Jet1Eta_3"        , "Jet1Eta "            , 36, -3.6, 3.6);



		// for overflow
		histo1D["Jet1Pt2"]          = new TH1D("Jet1Pt2"        , "Jet1Pt "             , 40, 0, 1000);
		histo1D["Jet1Pt3"]          = new TH1D("Jet1Pt3"        , "Jet1Pt "             , 39, 0, 975);

	
		histo1D["Jet1Eta"]          = new TH1D("Jet1Eta"        , "Jet1Eta "            , 36, -3.6, 3.6);
		histo1D["Jet1Phi"]          = new TH1D("Jet1Phi"        , "Jet1Phi "            , 80, -4, 4);
	
		//histo1D["Jet1Eta_uncor"]    = new TH1D("Jet1Eta_uncor"        , "Jet1Eta "            , 36, -3.6, 3.6);
		histo1D["Jet1Phi_uncor"]    = new TH1D("Jet1Phi_uncor"        , "Jet1Phi "            , 80, -4, 4);
		histo1D["Jet1Pt_uncor"]     = new TH1D("Jet1Pt_uncor"         , "Jet1Pt "             , 28, 0, 700);



		histo2D["Jet1PhivsEta"]     = new TH2D("Jet1PhivsEta"   , "Jet1Phi vs Eta"      , 40, -4, 4 , 40, -4,4);


		histo1D["CaloJet1Emf_1"]     = new TH1D("CaloJet1Emf_1"   , "CaloJet1Emf_1"      , 60, -1, 2 );
		histo1D["CaloJet1Emf_2"]     = new TH1D("CaloJet1Emf_2"   , "CaloJet1Emf_2"      , 60, -1, 2 );
		histo1D["CaloJet1Emf_3"]     = new TH1D("CaloJet1Emf_3"   , "CaloJet1Emf_3"      , 60, -1, 2 );



		histo1D["CaloJet1Eta"]      = new TH1D("CaloJet1Eta"    , "CaloJet1Eta "        , 36, -3.6, 3.6);	


		histo1D["Jet2Pt"]           = new TH1D("Jet2Pt"         , "Jet2Pt "             , 24, 0, 600);
		histo1D["Jet2Eta"]          = new TH1D("Jet2Eta"        , "Jet2Eta "            , 52, -5.2, 5.2);
		histo1D["Jet2Phi"]          = new TH1D("Jet2Phi"        , "Jet2Phi "            , 80, -4, 4);

		//Njet
		histo1D["NJet"]             = new TH1D("NJet"           , "NJet "               , 10, 0, 10);
		
		//deltaPhi
		histo1D["dPhi_MetLep_Jet1"] = new TH1D("dPhi_MetLep_Jet1", "dPhi MetLep Jet1 "   , 35, 0, 3.5);
		histo1D["dPhi_Met_Jet1"]    = new TH1D("dPhi_Met_Jet1"   , "dPhi Met Jet1 "      , 35, 0, 3.5 );
		
		histo1D["dPhi_MetLep_Jet2"] = new TH1D("dPhi_MetLep_Jet2", "dPhi MetLep Jet2 "   , 35, 0., 3.5);
		histo1D["dPhi_Met_Jet2"]    = new TH1D("dPhi_Met_Jet2"   , "dPhi Met Jet2 "      , 35, 0., 3.5);
		
		histo1D["dPhi_Jet1_Jet2"]   = new TH1D("dPhi_Jet1_Jet2"  , "dPhi Jet1 Jet2 "     , 35, 0, 3.5);
		
		//Met
		histo1D["Met"]              = new TH1D("Met"             , "MET "                ,  40, 0, 1000);
		histo1D["MetLep1"]          = new TH1D("MetLep1"         , "MET+Lep"              , 40, 0, 1000);
		histo1D["MetLep2"]          = new TH1D("MetLep2"         , "MET+Lep"              , 32, 200, 1000);

		//for overflow 
		histo1D["MetLep3"]          = new TH1D("MetLep3"         , "MET+Lep"             , 32, 200, 1000); 
		histo1D["MetLep4"]          = new TH1D("MetLep4"         , "MET+Lep"             , 31, 200, 975); 


		histo1D["MetLepPhi"]        = new TH1D("MetLepPhi"       , "MET+Lep Phi "        , 80, -4, 4);
		histo1D["MetPhi"]           = new TH1D("MetPhi"          , "MET Phi "            , 80, -4, 4);

		histo1D["MetLepThrs1"]      = new TH1D("MetLepThrs1"     , "METLep Threshold"    , 40, 0, 1000  );
		histo1D["MetLepThrs2"]      = new TH1D("MetLepThrs2"     , "METLep Threshold"    , 32, 200, 1000);
		

		histo1D["MetSumEt"]         = new TH1D("MetSumEt"        , "SumEt"               , 150, 0, 1500);

		//TIV
		histo1D["TIV"]              = new TH1D("TIV"             , "TIV "                , 70, -0.05, 0.3);
		
		//Muon ISo
		histo1D["MuonPt"]           = new TH1D("MuonPt"         , "MuonPt "               ,40, 0,400);
		histo1D["MuonPt_2"]         = new TH1D("MuonPt_2"       , "MuonPt "               ,30, 0,120);
		
		
		//PF Electron & Muon
		histo1D["PFElecPt"]         = new TH1D("PFElecPt"       , "PF ElecPt "            ,80, 0,80);
		histo1D["PFMuonPt"]         = new TH1D("PFMuonPt"       , "PF MuonPt "            ,80, 0,80);
		
		
		histo1D["NJet_met100"]      = new TH1D("NJet_met100"     , "NJet  Met>100 GeV"    , 10, 0, 10);
		histo1D["NJet_met150"]      = new TH1D("NJet_met150"     , "NJet  Met>150 GeV"    , 10, 0, 10);
		histo1D["NJet_met200"]      = new TH1D("NJet_met200"     , "NJet  Met>200 GeV"    , 10, 0, 10);
		histo1D["NJet_met250"]      = new TH1D("NJet_met250"     , "NJet  Met>250 GeV"    , 10, 0, 10);
		
		histo1D["EnergyScale"]      = new TH1D("EnergyScale"     , "Energy Scale "        , 10, 0,10);
		histo2D["UncerVsJetPt"]     = new TH2D("UncerVsJetPt"    , "Uncertinity vs JetPt" , 100, 0 ,800, 100, 0, 0.1);
		histo2D["UncerVsJetEta"]    = new TH2D("UncerVsJetEta"   , "Uncertinity vs JetEta", 100,-5 ,5  , 100, 0, 0.1);

		histo1D["GenJet1Pt"]        = new TH1D("GenJet1Pt"         , "Leading GenJet p_{T}"    , 24, 0, 600);
		histo1D["GenWPt"]           = new TH1D("GenWPt"            , "Gen W p_{T}"             , 24, 0, 600);
		histo1D["GenZPt"]           = new TH1D("GenZPt"            , "Gen Z p_{T}"             , 24, 0, 600);

		histo1D["GenJet1PtThrs"]    = new TH1D("GenJet1PtThrs"    , "Leading GenJet p_{T}"    , 24, 0, 600);
		histo1D["GenWPtThrs"]       = new TH1D("GenWPtThrs"       , "Gen W p_{T}"             , 24, 0, 600);
		histo1D["GenZPtThrs"]       = new TH1D("GenZPtThrs"       , "Gen Z p_{T}"             , 24, 0, 600);

		histo2D["GenJet1ptvsWpt"]   = new TH2D("GenJet1ptvsWpt"   , "GenJet1pt vs Wpt", 48, 0,600, 48, 0,600);
		histo2D["RecJet1ptvsWpt"]   = new TH2D("RecJet1ptvsWpt"   , "RecJet1pt vs Wpt", 48, 0,600, 48, 0,600);

		histo2D["GenJet1ptvsZpt"]   = new TH2D("GenJet1ptvsZpt"   , "GenJet1pt vs Zpt", 48, 0,600, 48, 0,600);
		histo2D["RecJet1ptvsZpt"]   = new TH2D("RecJet1ptvsZpt"   , "RecJet1pt vs Zpt", 48, 0,600, 48, 0,600);

		histo2D["METmuvsWpt"]       = new TH2D("METmuvsWpt"       , "METmu vs Wpt", 48, 0,600, 48, 0,600);
		histo2D["METmuvsZpt"]       = new TH2D("METmuvsZpt"       , "Metmu vs Wpt", 48, 0,600, 48, 0,600);

		histo1D["METoverWpt"]       = new TH1D("METoverWpt"       , "MET over  W p_{T}"   , 50, 0, 2);
		histo1D["METoverZpt"]       = new TH1D("METoverZpt"       , "MET over  Z p_{T}"   , 50, 0, 2);

		histo1D["numofPileup"]      = new TH1D("numofPileup"      , "numofPileup"   , 30, 0, 30);

		histo1D["Met_Wenu"]         = new TH1D("Met_Wenu"         , "MET W->enu"    , 32, 0, 800);
		histo1D["Met_Wmnu"]         = new TH1D("Met_Wmnu"         , "MET W->munu"    , 32, 0, 800);
		histo1D["Met_Wtnu"]         = new TH1D("Met_Wtnu"         , "MET W->tnu"    , 32, 0, 800);

		histo1D["GenElecPt"]        = new TH1D("GenElecPt"         , "Gen Elec p_{T}"     , 100, 0, 800);
		histo1D["GenMuonPt"]        = new TH1D("GenMuonPt"         , "Gen Muon p_{T}"     , 100, 0, 800);
		histo1D["GenTauPt"]         = new TH1D("GenTauPt"          , "Gen Tau p_{T}"      , 100, 0, 800);


		histo1D["PFMuonPt1"]           = new TH1D("PFMuonPt1"           , "PFMuonPt1"          , 100, 0, 800);
		histo1D["PFMuonEta1"]          = new TH1D("PFMuonEta1"          , "PFMuonEta1"         , 100, -6, 6);
		histo1D["PFMuonIso1"]          = new TH1D("PFMuonIso1"          , "PFMuonIso1"         , 100, -1, 3);
		histo1D["PFMuonisGMPT1"]       = new TH1D("PFMuonisGMPT1"       , "PFMuonisGMPT1"      , 50, 0, 50);
		histo1D["PFMuonnValidHits1"]   = new TH1D("PFMuonnValidHits1"   , "PFMuonnValidHits1"  , 100, 0, 100);
		histo1D["PFMuondxy1"]          = new TH1D("PFMuondxy1"          , "PFMuondxy1"         , 100, -1, 5);
		histo1D["PFMuondz1"]           = new TH1D("PFMuondz1"           , "PFMuondz1"          , 100, -1, 5);


		histo1D["PFMuonPt2"]           = new TH1D("PFMuonPt2"           , "PFMuonPt2"          , 100, 0, 800);
		histo1D["PFMuonEta2"]          = new TH1D("PFMuonEta2"          , "PFMuonEta2"         , 100, -6, 6);
		histo1D["PFMuonIso2"]          = new TH1D("PFMuonIso2"          , "PFMuonIso2"         , 100, -1, 3);
		histo1D["PFMuonisGMPT2"]       = new TH1D("PFMuonisGMPT2"       , "PFMuonisGMPT2"      , 50, 0, 50);
		histo1D["PFMuonnValidHits2"]   = new TH1D("PFMuonnValidHits2"   , "PFMuonnValidHits2"  , 100, 0, 100);
		histo1D["PFMuondxy2"]          = new TH1D("PFMuondxy2"          , "PFMuondxy2"         , 100, -1, 5);
		histo1D["PFMuondz2"]           = new TH1D("PFMuondz2"           , "PFMuondz2"          , 100, -1, 5);

		histo1D["CaloJetEMF"]          = new TH1D("CaloJetEMF"           , "CaloJetEMF"        , 300, -1, 2);

		histo1D["NPFTau"]           = new TH1D("NPFTau"            , "NPFTau"         , 10, 0, 10);
		histo1D["PFTauE"]          = new TH1D("PFTauE"           , "PFTauE"        , 100, 0, 500);
		histo1D["PFTauPt"]          = new TH1D("PFTauPt"           , "PFTauPt"        , 100, 0, 500);
		histo1D["PFTauPx"]          = new TH1D("PFTauPx"           , "PFTauPx"        , 100, -100, 100);
		histo1D["PFTauPy"]          = new TH1D("PFTauPy"           , "PFTauPy"        , 100, -100, 100);
		histo1D["PFTauPz"]          = new TH1D("PFTauPz"           , "PFTauPz"        , 100, -100, 100);
		histo1D["PFTauEta"]          = new TH1D("PFTauEta"           , "PFTauEta"        , 100, -5, 5);
		histo1D["PFTauPhi"]          = new TH1D("PFTauPhi"           , "PFTauPhi"        , 100, -4, 4);
		histo1D["PFTauEtaEtaMoment"]          = new TH1D("PFTauEtaEtaMoment"           , "PFTauEtaEtaMoment"        , 100, -0.01, 0.1);
		histo1D["PFTauPhiPhiMoment"]          = new TH1D("PFTauPhiPhiMoment"           , "PFTauPhiPhiMoment"        , 100, -0.01, 0.1);
		histo1D["PFTauLeadPFChargedHadrCandsignedSipt"]          = new TH1D("PFTauLeadPFChargedHadrCandsignedSipt"           , "PFTauLeadPFChargedHadrCandsignedSipt"        , 200, -1, 3);
		histo1D["PFTauIsoPFChargedHadrCandsPtSum"]          = new TH1D("PFTauIsoPFChargedHadrCandsPtSum"           , "PFTauIsoPFChargedHadrCandsPtSum"        , 100, 0, 50);
		histo1D["PFTauIsoPFGammaCandsEtSum"]          = new TH1D("PFTauIsoPFGammaCandsEtSum"           , "PFTauIsoPFGammaCandsEtSum"        , 30, 0, 15);

		histo1D["PFTauMaximumHCALPFClusterEt"]           = new TH1D("PFTauMaximumHCALPFClusterEt"            , "PFTauMaximumHCALPFClusterEt"         , 100, 0, 500);
		histo1D["PFTauEmFraction"]           = new TH1D("PFTauEmFraction"            , "PFTauEmFraction"         , 70, -0.2, 1.2);
		histo1D["PFTauHcalTotOverPLead"]           = new TH1D("PFTauHcalTotOverPLead"            , "PFTauHcalTotOverPLead"         , 100, 0, 200);
		histo1D["PFTauHcalMaxOverPLead"]           = new TH1D("PFTauHcalMaxOverPLead"            , "PFTauHcalMaxOverPLead"         , 100, 0, 200);
		histo1D["PFTauHcal3x3OverPLead"]           = new TH1D("PFTauHcal3x3OverPLead"            , "PFTauHcal3x3OverPLead"         , 50, 0, 100);
		histo1D["PFTauEcalStripSumEOverPLead"]           = new TH1D("PFTauEcalStripSumEOverPLead"            , "PFTauEcalStripSumEOverPLead"         , 75, 0, 150);
		histo1D["PFTauBremsRecoveryEOverPLead"]           = new TH1D("PFTauBremsRecoveryEOverPLead"            , "PFTauBremsRecoveryEOverPLead"         , 10, 0, 10);
		histo1D["PFTauElectronPreIDOutput"]           = new TH1D("PFTauElectronPreIDOutput"            , "PFTauElectronPreIDOutput"         , 10, 0, 10);
		histo1D["PFTauElectronPreIDDecision"]           = new TH1D("PFTauElectronPreIDDecision"            , "PFTauElectronPreIDDecision"         , 10, 0, 10);
		histo1D["PFTauMuonDecision"]           = new TH1D("PFTauMuonDecision"            , "PFTauMuonDecision"         , 10, 0, 10);




		histo1D["MetLep1_cm"]       = new TH1D("MetLep1_cm"      , "MET+Lep"              , 40, 0, 1000);
		histo1D["MetLep1_eff"]      = new TH1D("MetLep1_eff"     , "MET+Lep"              , 32, 0, 800);


		histo1D["GravitonPt"]         = new TH1D("GravitonPt"        , "GravitonPt"                 , 50, 0, 1000);
		histo1D["GravitonPt_gg"]      = new TH1D("GravitonPt_gg"     , "GravitonPt_gg"              , 50, 0, 1000);
		histo1D["GravitonPt_qg"]      = new TH1D("GravitonPt_qg"     , "GravitonPt_qg"              , 50, 0, 1000);
		histo1D["GravitonPt_qq"]      = new TH1D("GravitonPt_qq"     , "GravitonPt_qq"              , 50, 0, 1000);


		histo2D["SumETvsNPV"]         = new TH2D("SumETvsNPV"       , "SumETvsNPV"        ,1500,0,1500, 30, 0, 30);
		profile1D["SumETprNPV"]       = new TProfile("SumETprNPV"   , "<SumET> vs NPV"    ,30,0,30,0,1500);

        histo2D["PileUpETvsNPV"]      = new TH2D("PileUpETvsNPV"    , "SumETvsNPV"        ,1500,0,1500, 30, 0, 30);
		profile1D["PileUpETprNPV"]    = new TProfile("PileUpETprNPV", "<PileUpET> vs NPV"    ,30,0,30,0,1500);


		histo2D["NPVvsnpv0"]	      = new TH2D("NPVvsnpv0"    , "NPVvsnpv0"        ,50,0,50, 50, 0, 50);
		profile1D["NPVprnpv0"]	      = new TProfile("NPVprnpv0"    , "NPVprnpv0"    ,50,0,50,0,50);


		for(int i=0; i<45; i++ )
		{
			char his[100];

			sprintf(his,"PDF%d", i);

			histo1D[his]           = new TH1D(his , "PDF"  , 10, 0, 10);

		}		



	}

	///---------------------- Data MC Matching Histograms Filling -----------------------------------------------------------------

	bool hDataMcMatching::Process(EventData & ev) 	{

	  
		int t = ev.MetType();

		double w= ev.Weight();


		histo2D["SumETvsNPV"]->Fill( ev.MetSumEt(t), ev.NPV(), w );
		profile1D["SumETprNPV"]->Fill( ev.NPV() , ev.MetSumEt(t) );

		histo2D["NPVvsnpv0"]->Fill( ev.NPV() , ev.npv0() , w );
		profile1D["NPVprnpv0"]->Fill( ev.NPV() , ev.npv0()  );
		
		int njets = JetNumber(ev);
		int ixjet1= JetIndex(0, ev);
		int ixjet2= JetIndex(1, ev);	


		double  pileupET = ev.MetSumEt(t) - (ev.PFAK5JetPtCor(ixjet1)+ ev.PFAK5JetPtCor(ixjet2) );  

		histo2D["PileUpETvsNPV"]->Fill(  pileupET , ev.NPV() , w );

		profile1D["PileUpETprNPV"]->Fill( ev.NPV() , pileupET );

		histo2D["Jet1PhivsEta"]->Fill(  ev.PFAK5JetEta(ixjet1) ,ev.PFAK5JetPhi(ixjet1), w);

   
		histo1D["Jet1Phi_uncor"]->Fill( atan2( ev.PFAK5JetPy(ixjet1) ,  ev.PFAK5JetPx(ixjet1)  )  , w);
		histo1D["Jet1Pt_uncor"]->Fill(  ev.PFAK5JetPt(ixjet1) , w);




		histo1D["NPFTau"]->Fill(ev.NPFTau() );       
		histo1D["PFTauE"]->Fill(ev.PFTauE(0) );          
		histo1D["PFTauPt"]->Fill(ev.PFTauPt(0) );        
		histo1D["PFTauPx"]->Fill(ev.PFTauPx(0) );        
		histo1D["PFTauPy"]->Fill(ev.PFTauPy(0) );          
		histo1D["PFTauPz"]->Fill(ev.PFTauPz(0) );         
		histo1D["PFTauEta"]->Fill(ev.PFTauEta(0) );        
		histo1D["PFTauPhi"]->Fill(ev.PFTauPhi(0) );          
		histo1D["PFTauEtaEtaMoment"]->Fill(ev.PFTauEtaEtaMoment(0) );           
		histo1D["PFTauPhiPhiMoment"]->Fill(ev.PFTauPhiPhiMoment(0) );          
		histo1D["PFTauLeadPFChargedHadrCandsignedSipt"]->Fill(ev.PFTauLeadPFChargedHadrCandsignedSipt(0) );          
		histo1D["PFTauIsoPFChargedHadrCandsPtSum"]->Fill(ev.PFTauIsoPFChargedHadrCandsPtSum(0) );          
		histo1D["PFTauIsoPFGammaCandsEtSum"]->Fill(ev.PFTauIsoPFGammaCandsEtSum(0) );           

		histo1D["PFTauMaximumHCALPFClusterEt"]->Fill(ev.PFTauMaximumHCALPFClusterEt(0) );            
		histo1D["PFTauEmFraction"]->Fill(ev.PFTauEmFraction(0) );           
		histo1D["PFTauHcalTotOverPLead"]->Fill(ev.PFTauHcalTotOverPLead(0) );           
		histo1D["PFTauHcalMaxOverPLead"]->Fill(ev.PFTauHcalMaxOverPLead(0) );           
		histo1D["PFTauHcal3x3OverPLead"]->Fill(ev.PFTauHcal3x3OverPLead(0) );            
		histo1D["PFTauEcalStripSumEOverPLead"]->Fill(ev.PFTauEcalStripSumEOverPLead(0) );            
		histo1D["PFTauBremsRecoveryEOverPLead"]->Fill(ev.PFTauBremsRecoveryEOverPLead(0) );          
		histo1D["PFTauElectronPreIDOutput"]->Fill(ev.PFTauElectronPreIDOutput(0) );         
		histo1D["PFTauElectronPreIDDecision"]->Fill(ev.PFTauElectronPreIDDecision(0) );      
		histo1D["PFTauMuonDecision"]->Fill(ev.PFTauMuonDecision(0) );          





		float Iso = 0.0;
		Iso = (ev.PFMuonNeutralHadronIso(0) + ev.PFMuonChargedHadronIso(0) + ev.PFMuonPhotonIso(0))/ev.PFMuonPt(0);
	
		histo1D["PFMuonPt1"]->Fill( ev.PFMuonPt(0) );
		histo1D["PFMuonEta1"]->Fill( ev.PFMuonEta(0) );
		histo1D["PFMuonIso1"]->Fill( Iso );
		histo1D["PFMuonisGMPT1"]->Fill( ev.PFMuonisGMPT(0) );
		histo1D["PFMuonnValidHits1"]->Fill( ev.PFMuonnValidHits(0) );
		histo1D["PFMuondxy1"]->Fill(  ev.PFMuondxy(0) );
		histo1D["PFMuondz1"]->Fill( ev.PFMuondz(0) );

		Iso = 0.0;
		Iso = (ev.PFMuonNeutralHadronIso(1) + ev.PFMuonChargedHadronIso(1) + ev.PFMuonPhotonIso(1))/ev.PFMuonPt(1);

		histo1D["PFMuonPt2"]->Fill( ev.PFMuonPt(1) );
		histo1D["PFMuonEta2"]->Fill( ev.PFMuonPt(1) );
		histo1D["PFMuonIso2"]->Fill( Iso );
		histo1D["PFMuonisGMPT2"]->Fill( ev.PFMuonisGMPT(1) );
		histo1D["PFMuonnValidHits2"]->Fill( ev.PFMuonnValidHits(1) );
		histo1D["PFMuondxy2"]->Fill(  ev.PFMuondxy(1) );
		histo1D["PFMuondz2"]->Fill( ev.PFMuondz(1) );

		if(ev.CaloAK5JetEmf(0) >0.03 && ev.CaloAK5JetEmf(0)<0.98 ) histo1D["CaloJetEMF"]->Fill( ev.CaloAK5JetEmf(0) , w);


		
		//pf noise clean  for leading jet

		histo1D["PFAK5JetChaHadEngFrac"]->Fill( ev.PFAK5JetChaHadEngFrac(ixjet1) , w );
		histo1D["PFAK5JetNeuHadEngFrac"]->Fill( ev.PFAK5JetNeuHadEngFrac(ixjet1) , w );
		histo1D["PFAK5JetChaEmEngFrac"]->Fill( ev.PFAK5JetChaEmEngFrac(ixjet1) , w );
		histo1D["PFAK5JetNeuEmEngFrac"]->Fill( ev.PFAK5JetNeuEmEngFrac(ixjet1) , w ); 
		
		//pf noise clean for second jet
		histo1D["PFAK5JetChaHadEngFrac2"]->Fill( ev.PFAK5JetChaHadEngFrac(ixjet2) , w );
		histo1D["PFAK5JetNeuHadEngFrac2"]->Fill( ev.PFAK5JetNeuHadEngFrac(ixjet2) , w );
		histo1D["PFAK5JetChaEmEngFrac2"]->Fill( ev.PFAK5JetChaEmEngFrac(ixjet2) , w );
		histo1D["PFAK5JetNeuEmEngFrac2"]->Fill( ev.PFAK5JetNeuEmEngFrac(ixjet2) , w ); 
		

		histo1D["NPV"]->Fill( ev.NPV() , w );

		histo1D["numofPileup"]->Fill( ev.npv0() , w );

		for(int i=0; i<ev.NPV(); i++)
		{
		  histo1D["PVx"]->Fill( ev.PVx(i) , w  );
		  histo1D["PVy"]->Fill( ev.PVy(i) , w  );
		  histo1D["PVz"]->Fill( ev.PVz(i) , w  );              
		  histo1D["PVR"]->Fill( sqrt(ev.PVx(i)*ev.PVx(i) + ev.PVz(i)*ev.PVz(i) ) , w  );              
		  histo1D["PVndof"]->Fill( ev.PVndof(i) , w  );           
		  histo1D["PVchi2"]->Fill( ev.PVchi2(i) , w  );           
		  histo1D["PVntracks"]->Fill( ev.PVntracks(i) , w  );    
		}


		//jet1 cut
		histo1D["Jet1Pt"]->Fill( ev.PFAK5JetPtCor( ixjet1  ) , w ); 
		histo1D["Jet1Pt3"]->Fill( ev.PFAK5JetPtCor( ixjet1  ) , w ); 

		histo1D["Jet1Eta"]->Fill( ev.PFAK5JetEta( ixjet1 ) , w ); 
		histo1D["Jet1Emf"]->Fill( ev.CaloAK5JetEmf(0) , w );  

		histo1D["Jet1Phi"]->Fill( ev.PFAK5JetPhi(ixjet1) , w ); 

		histo1D["CaloJet1Eta"]->Fill( ev.CaloAK5JetEta(0) , w );  


		if( ev.PFAK5JetPhi(ixjet1)< -1.5 )
		{  
			histo1D["Jet1Pt_1"]->Fill( ev.PFAK5JetPtCor( ixjet1  ) , w ); 
			histo1D["Jet1Eta_1"]->Fill( ev.PFAK5JetEta( ixjet1  ) , w ); 

			histo1D["CaloJet1Emf_1"]->Fill( ev.CaloAK5JetEmf( ixjet1  ) , w );
		}

		else if( ev.PFAK5JetPhi(ixjet1) > -1.5  && ev.PFAK5JetPhi(ixjet1)< 0.5)
		{
			histo1D["Jet1Pt_2"]->Fill( ev.PFAK5JetPtCor( ixjet1  ) , w ); 
			histo1D["Jet1Eta_2"]->Fill( ev.PFAK5JetEta( ixjet1  ) , w ); 
			histo1D["CaloJet1Emf_2"]->Fill( ev.CaloAK5JetEmf( ixjet1  ) , w );
		}
        else if( ev.PFAK5JetPhi(ixjet1) > 0.5 )  
		{
			histo1D["Jet1Pt_3"]->Fill( ev.PFAK5JetPtCor( ixjet1  ) , w );
			histo1D["Jet1Eta_3"]->Fill( ev.PFAK5JetEta( ixjet1  ) , w ); 
			histo1D["CaloJet1Emf_3"]->Fill( ev.CaloAK5JetEmf( ixjet1  ) , w );
		}

		//njet
		histo1D["NJet"]->Fill( njets , w );
		
		//deltaPhi
		histo1D["dPhi_MetLep_Jet1"]->Fill( fabs( deltaPhi( ev.PFAK5JetPhi(ixjet1) , MetLepPhi( ev.MetPx(t) , ev.MetPy(t) ,ev) ) ), w );
		histo1D["dPhi_Met_Jet1"]->Fill( fabs( deltaPhi( ev.PFAK5JetPhi(ixjet1) , ev.MetPhi(t) ) ), w );
		
		if(njets==2)
		{  
			histo1D["dPhi_MetLep_Jet2"]->Fill(  fabs( deltaPhi( ev.PFAK5JetPhi(ixjet2) , MetLepPhi( ev.MetPx(t) , ev.MetPy(t) ,ev) ) ), w );

			histo1D["dPhi_Met_Jet2"]->Fill(  fabs( deltaPhi( ev.PFAK5JetPhi(ixjet2) , ev.MetPhi(t) ) ) , w );
			
			histo1D["dPhi_Jet1_Jet2"]->Fill(  fabs( deltaPhi( ev.PFAK5JetPhi(ixjet1) ,  ev.PFAK5JetPhi(ixjet2) ) ), w );

			histo1D["Jet2Pt"]->Fill( ev.PFAK5JetPtCor(ixjet2) , w ); 
			histo1D["Jet2Eta"]->Fill( ev.PFAK5JetEta(ixjet2) , w ); 
			histo1D["Jet2Phi"]->Fill( ev.PFAK5JetPhi(ixjet2) , w ); 

		}
		
		//Met
		histo1D["Met"]->Fill( ev.MetPt( t) , w );
		histo1D["MetLep1"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) , w ); 
		histo1D["MetLep2"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) , w );
		histo1D["MetLep4"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) , w );

		if(ev.MetPt(0) >95. ) histo1D["MetLep1_cm"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) , w ); 


		histo1D["MetLepPhi"]->Fill( fabs( MetLepPhi( ev.MetPx(t) , ev.MetPy(t) , ev) ), w );
		histo1D["MetPhi"]->Fill(   ev.MetPhi(t)  , w ); 

		histo1D["MetSumEt"]->Fill(   ev.MetSumEt(t)  , w ); 
		
		//TIV
		histo1D["TIV"]->Fill( ev.LowTIV()  , w );
		
		//MuonIso
		if(ev.NMuon() >0 )histo1D["MuonPt"]->Fill( ev.MuonPt(0)  , w );
		if(ev.NMuon() >0 )histo1D["MuonPt_2"]->Fill( ev.MuonPt(0)  , w );
		if(ev.NPFMuon() >0 )histo1D["PFMuonPt"]->Fill( ev.PFMuonPt(0)  , w ); 


		
		//ELectron
		if(ev.NPFElec() >0 )histo1D["PFElecPt"]->Fill( ev.PFElecPt(0)  , w ); 
		
		if( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) > 100.  ) histo1D["NJet_met100"]->Fill( njets , w );  
		if( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) > 150.  ) histo1D["NJet_met150"]->Fill( njets , w );  
		if( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) > 200.  ) histo1D["NJet_met200"]->Fill( njets , w );  
		if( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) > 250.  ) histo1D["NJet_met250"]->Fill( njets , w );  

		if(MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) > 150. && MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) < 200.)
		{
			histo1D["PFAK5JetChaHadEngFrac150"]->Fill( ev.PFAK5JetChaHadEngFrac(ixjet1) , w );
			histo1D["PFAK5JetNeuHadEngFrac150"]->Fill( ev.PFAK5JetNeuHadEngFrac(ixjet1) , w );
			histo1D["PFAK5JetChaEmEngFrac150"]->Fill( ev.PFAK5JetChaEmEngFrac(ixjet1) , w );
			histo1D["PFAK5JetNeuEmEngFrac150"]->Fill( ev.PFAK5JetNeuEmEngFrac(ixjet1) , w ); 
		}

		if(MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) > 300.)
		{
			histo1D["PFAK5JetChaHadEngFrac300"]->Fill( ev.PFAK5JetChaHadEngFrac(ixjet1) , w );
			histo1D["PFAK5JetNeuHadEngFrac300"]->Fill( ev.PFAK5JetNeuHadEngFrac(ixjet1) , w );
			histo1D["PFAK5JetChaEmEngFrac300"]->Fill( ev.PFAK5JetChaEmEngFrac(ixjet1) , w );
			histo1D["PFAK5JetNeuEmEngFrac300"]->Fill( ev.PFAK5JetNeuEmEngFrac(ixjet1) , w ); 
		}

		
		histo1D["EnergyScale"]->Fill( ev.EnergyScale()  );  


		histo2D["UncerVsJetPt"]->Fill( ev.PFAK5JetPtCor(ixjet1) ,ev.PFAK5uncer(ixjet1),  w );  
		histo2D["UncerVsJetEta"]->Fill( ev.PFAK5JetEta(ixjet1) , ev.PFAK5uncer(ixjet1), w );  


		histo1D["GenJet1Pt"] ->Fill( ev.GenAK5JetPt(0),  w );  

		double  METplusMuPt=0,METplusMuPx=ev.MetPx(t) ,METplusMuPy=ev.MetPy(t) ;
		for(int i=0; i<ev.NMuon(); i++)
		{
			METplusMuPx =  METplusMuPx+ ev.PFMuonPx(i);
			METplusMuPy =  METplusMuPy + ev.PFMuonPy(i);
		}
		METplusMuPt= sqrt( METplusMuPx*METplusMuPx + METplusMuPy*METplusMuPy );

 
		for(int i=0; i<ev.NGenPar(); i++)
		{
			if(abs(ev.GenParId(i) )==24 && ev.GenParStatus(i)==2 )
			{
				histo1D["GenWPt"]->Fill( ev.GenParPt(i), w );
				histo2D["GenJet1ptvsWpt"]->Fill( ev.GenAK5JetPt(0), ev.GenParPt(i), w );
				histo2D["RecJet1ptvsWpt"]->Fill( ev.PFAK5JetPtCor(ixjet1), ev.GenParPt(i), w );
				histo2D["METmuvsWpt"]->Fill( METplusMuPt, ev.GenParPt(i), w );   
				histo1D["METoverWpt"]->Fill( METplusMuPt/ ev.GenParPt(i), w ); 
				
			}
			if(abs(ev.GenParId(i) )==23 && ev.GenParStatus(i)==2 )
			{
				histo1D["GenZPt"]->Fill( ev.GenParPt(i), w );
				histo2D["GenJet1ptvsZpt"]->Fill( ev.GenAK5JetPt(0), ev.GenParPt(i), w );
				histo2D["RecJet1ptvsZpt"]->Fill( ev.PFAK5JetPtCor(ixjet1), ev.GenParPt(i), w );
				histo2D["METmuvsZpt"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ), ev.GenParPt(i), w );   
				histo1D["METoverZpt"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev )/ ev.GenParPt(i), w ); 
			}

			if( abs(ev.GenParId(i) )==11 && ev.GenParStatus(i)==3 )  histo1D["Met_Wenu"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) ,w );
			if( abs(ev.GenParId(i) )==13 && ev.GenParStatus(i)==3 )  histo1D["Met_Wmnu"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) ,w );
			if( abs(ev.GenParId(i) )==15 && ev.GenParStatus(i)==3 )  histo1D["Met_Wtnu"]->Fill( MetLepPt( ev.MetPx(t) , ev.MetPy(t) , ev ) ,w );


			
		}

		for(int i=0; i<ev.NGenPar(); i++)
		{
			if(abs(ev.GenParId(i) )==11 && ev.GenParStatus(i)==3 )
			{
				histo1D["GenElecPt"]->Fill( ev.GenParPt(i), w );
			}
			else if(abs(ev.GenParId(i) )==13 && ev.GenParStatus(i)==3 )
			{
				histo1D["GenMuonPt"]->Fill( ev.GenParPt(i), w );
				
			}
			else if(abs(ev.GenParId(i) )==15 && ev.GenParStatus(i)==3 )
			{
				histo1D["GenTauPt"]->Fill( ev.GenParPt(i), w );
			}
		}



		for(int i=0; i<41; i++ )
		{
			char his[100];

			sprintf(his,"PDF%d", i);

			double w = ev.PDFWeight(i) * ev.PDFWeights(0) / ev.PDFWeight(0);

			histo1D[his]->Fill( 5 , w ); 

		}	


		for(int i=0; i<ev.NGenPar(); i++)
		{
		  histo1D["GravitonPt"]->Fill( ev.GenParPt(i), w );

			if( ev.GenParMother1(i)==21 &&  ev.GenParMother2(i)==21  ) histo1D["GravitonPt_gg"]->Fill( ev.GenParPt(i), w );
					
			if( (ev.GenParMother1(i)==21 ||  ev.GenParMother2(i)==21 )  && 
				(  ( abs(ev.GenParMother1(i))>0 && abs(ev.GenParMother1(i))<9  )  ||  ( abs(ev.GenParMother2(i))>0 && abs(ev.GenParMother2(i))<9  )  ) )
			{
			  histo1D["GravitonPt_qg"]->Fill( ev.GenParPt(i) , w);
			}
			if(   ( abs(ev.GenParMother1(i))>0 && abs(ev.GenParMother1(i))<9  )  &&  ( abs(ev.GenParMother2(i))>0 && abs(ev.GenParMother2(i))<9   ) )
			{
			  histo1D["GravitonPt_qq"]->Fill( ev.GenParPt(i) , w );
			}

		
		
		
		}
		

		return true;
	}
	

	std::ostream& hDataMcMatching::Description(std::ostream &ostrm) 
	{
	  
		double a1=0, a2=0;
	  	for(int i=41; i>0; i--)
		{		

			a1=a1+histo1D["MetLep1"]->GetBinContent(i);
			histo1D["MetLepThrs1"]->SetBinContent( i , a1 );

			a2=a2+histo1D["Jet1Pt"]->GetBinContent(i);
			histo1D["Jet1PtThrs"]->SetBinContent( i , a2 );
		}

		double a5=0;
		for(int i=33; i>0; i--)
		{
			a5=a5+histo1D["MetLep2"]->GetBinContent(i);
			histo1D["MetLepThrs2"]->SetBinContent( i , a5 );

		}
		for(int i=1; i<33 ; i++)
		{	
			double a6= histo1D["MetLep4"]->GetBinContent(i);
		    histo1D["MetLep3"]->SetBinContent( i , a6 );
		}

		for(int i=1; i<41 ; i++)
		{	
			double a7= histo1D["Jet1Pt3"]->GetBinContent(i);
		    histo1D["Jet1Pt2"]->SetBinContent( i , a7 );
		}
		


		//histo1D["MetLep1_eff"]->Divide( histo1D["MetLep1_cm"], histo1D["MetLep1"] , 1.0, 1.0 ); 


		ostrm << "  DataMcMatching (output in " << mFileName << "):";
		return ostrm;
	}



	hDataMcMatching::~hDataMcMatching() 
	{	  
		fileOut->Write();
		delete fileOut;	
	}


///============================================================================================================================================




///---------------------------WZ Analysis---------------------------------------------------------------------------------------


	hWZAnalysis::hWZAnalysis(const std::string & fileName):
	mFileName(fileName)
	{
		fileOut = new TFile(mFileName.c_str(),"recreate");
		
		histo1D["NofLep"]          = new TH1D("NofLep"           , "Number of Lep"       , 10, 0, 10);
		histo1D["NofLep2"]          = new TH1D("NofLep2"           , "Number of Lep"       , 10, 0, 10);

		histo1D["NofLepSign"]      = new TH1D("NofLepSign"       , "Number of Lep Sign"  , 40, 0, 40);

			
		histo1D["WlepnuMT"]          = new TH1D("WlepnuMT"           , "Wlepnu m_{T}"                 , 50, 0, 500);
		histo1D["WlepnuMT_50_100"]   = new TH1D("WlepnuMT_50_100"    , "Wlepnu m_{T}   50<m_{T}<100"  , 40, 0, 400);
		

		histo1D["WlepnuPT"]          = new TH1D("WlepnuPT"           , "Wlepnu p_{T}"                 , 22, 350, 900);
		histo1D["WlepnuPT_50_100"]   = new TH1D("WlepnuPT_50_100"    , "Wlepnu p_{T}   50<m_{T}<100"  , 22, 350, 900);
		


		histo1D["ZleplepMT"]          = new TH1D("ZleplepMT"           , "Zleplep m_{T}"                 , 100, 0, 400);
		histo1D["ZleplepMT_81_101"]   = new TH1D("ZleplepMT_81_101"    , "Zleplep m_{T}  81<m_{T}<101"   , 100, 0, 400);
		
		histo1D["WlepnuMT_2"]        = new TH1D("WlepnuMT_2"         , "Wlepnu m_{T}"                 , 20, 0, 200);
		histo1D["WlepnuMT_50_100_2"] = new TH1D("WlepnuMT_50_100_2"  , "Wlepnu m_{T}   50<m_{T}<100"  , 20, 0, 200);
		
		histo1D["ZleplepMT_2"]        = new TH1D("ZleplepMT_2"         , "Zleplep m_{T}"                 , 50, 0, 200);
		histo1D["ZleplepMT_81_101_2"] = new TH1D("ZleplepMT_81_101_2"  , "Zleplep m_{T}  81<m_{T}<101"   , 50, 0, 200);
		histo1D["ZleplepMT_60_120"]   = new TH1D("ZleplepMT_60_120"    , "Zleplep m_{T}  60<m_{T}<120"   , 30, 60,120);

		histo1D["ZleplepPT"]          = new TH1D("ZleplepPT"           , "Zleplep p_{T}  "               , 40, 0,800);
		histo1D["ZleplepPT_60_120"]   = new TH1D("ZleplepPT_60_120"    , "Zleplep p_{T}  60<m_{T}<120"   , 40, 0,800);


		histo1D["WlepnuMT_300"]      = new TH1D("WlepnuMT_300"       , "Wlepnu m_{T}"                 , 30, 0, 300);

		histo1D["WlepnuMT_210"]      = new TH1D("WlepnuMT_210"       , "Wlepnu m_{T}"                 , 21, 0, 210);
		histo1D["WlepnuMT_310"]      = new TH1D("WlepnuMT_310"       , "Wlepnu m_{T}"                 , 31, 0, 310);
		
		
		histo1D["WlepnuMT_e"]        = new TH1D("WlepnuMT_e"         , "Wlepnu m_{T} for e"      , 80, 0, 400);
		histo1D["WlepnuMT_m"]        = new TH1D("WlepnuMT_m"         , "Wlepnu m_{T} for lep"    , 80, 0, 400);
		histo1D["WlepnuMT_t"]        = new TH1D("WlepnuMT_t"         , "Wlepnu m_{T} for tau"    , 80, 0, 400);


		histo1D["WlepnuMT_50_100_e"] = new TH1D("WlepnuMT_50_100_e"  , "Wlepnu m_{T} for e  50<m_{T}<100"      , 80, 0, 400);
		histo1D["WlepnuMT_50_100_m"] = new TH1D("WlepnuMT_50_100_m"  , "Wlepnu m_{T} for mu  50<m_{T}<100"     , 80, 0, 400);
		histo1D["WlepnuMT_50_100_t"] = new TH1D("WlepnuMT_50_100_t"  , "Wlepnu m_{T} for tau  50<m_{T}<100"    , 80, 0, 400);
		
		
		histo1D["njets_1"]          = new TH1D("njets_1"           , "NJet for  Wlepnu "                 , 10, 0, 10);
		histo1D["njets_2"]          = new TH1D("njets_2"           , "NJet for  Wlepnu  50<m_{T}<100 "   , 10, 0, 10);
		
		histo1D["njets_3"]          = new TH1D("njets_3"           , "NJet for  Zleplep "                 , 10, 0, 10);
		histo1D["njets_4"]          = new TH1D("njets_4"           , "NJet for  Zleplep  81<m_{T}<101 "   , 10, 0, 10);
		
		histo1D["dPhiJ1J2"]         = new TH1D("dPhiJ1J2"          , "dPhi(Jet1,Jet2)"    , 80, -4, 4);
		
		histo2D["dPhi1_vs_dPhi2"]   = new TH2D("dPhi1_vs_dPhi2"    , "dPhi1 vs dPhi2"     , 40, 0, 4 , 40, 0,4 ); 

		histo1D["GenElecPt"]        = new TH1D("GenElecPt"         , "Gen Elec p_{T}"     , 100, 0, 800);
		histo1D["GenMuonPt"]        = new TH1D("GenMuonPt"         , "Gen Muon p_{T}"     , 100, 0, 800);
		histo1D["GenTauPt"]         = new TH1D("GenTauPt"          , "Gen Tau p_{T}"      , 100, 0, 800);
		
		histo1D["ZleplepPFMET"]     = new TH1D("ZleplepPFMET"      , "PFMET for Z #lep #lep "      , 100, 0, 800);

		
		histo1D["METparalle"]       = new TH1D("METparalle"        , "PFMET Paralle "         , 100, -100, 100);
		histo1D["METperpendicular"] = new TH1D("METperpendicular"  , "PFMET Perpendicular"    , 100, -100, 100);
		histo1D["DPhiPFMetDiLep"]   = new TH1D("DPhiPFMetDiLep"    , "DPhi PFMET DiLep"        , 100, -4, 4);

		histo1D["PhiDiLep"]         = new TH1D("PhiDiLep"          , "Phi DiLep"            , 100, -4, 4);

		histo1D["DPhiPFMetDiLep2"]  = new TH1D("DPhiPFMetDiLep2"   , "DPhi PFMET DiLep"     , 100, -4, 4);

		histo1D["METPar1"]   = new TH1D("METPar1"     , "MET Paralelle"        , 100, -100, 100);
		histo1D["METPar2"]   = new TH1D("METPar2"     , "MET Paralelle"        , 100, -100, 100);
		histo1D["METPar3"]   = new TH1D("METPar3"     , "MET Paralelle"        , 100, -100, 100);	

		histo1D["dRPFMuonRegMuon"]   = new TH1D("dRPFMuonRegMuon"     , "dRPFMuonRegMuon"        ,700, -1, 6);	

		//hprof  = new TProfile("hprof","Profile of pz versus px",100,-4,4,0,20);

	}


	// --------------- Histograms Filling------------------------------------------------------------------------

	bool hWZAnalysis::Process(EventData & ev) 
	{

		int  t= ev.MetType(); 
	
		double w= ev.Weight();


		
		int njets= JetNumber(ev);
		int ixjet1= JetIndex(0, ev);
		int ixjet2= JetIndex(1, ev);	
		
		double dPhi1= fabs( deltaPhi( ev.PFAK5JetPhi(ixjet1), MetLepPhi( ev.MetPx(t) , ev.MetPy(t) , ev ) ) );
		double dPhi2= fabs( deltaPhi( ev.PFAK5JetPhi(ixjet2), MetLepPhi( ev.MetPx(t) , ev.MetPy(t) , ev ) ) ); 
		
		if(njets==2)
		{
			histo1D["dPhiJ1J2"]->Fill( deltaPhi( ev.PFAK5JetPhi(ixjet1) , ev.PFAK5JetPhi(ixjet2)  ) , w );
			histo2D["dPhi1_vs_dPhi2"]->Fill( dPhi1, dPhi2 , w );
		}
		
		int IsoLepIndex=0;	
		
		int isoLepPseq[20], isoLepMseq[20], isoLepPnum=0,isoLepMnum=0; //=0 for isoMuPnum,isoMuMnum 
		
		for (int i=0; i<20; i++) 
		{
			isoLepPseq[i]=0; isoLepMseq[i]=0;
		}
		
		//---------- ISoMuon index counting ---------------------------- 
		for(int i=0; i<ev.NPFLep(); i++ )
		{
		 
			if( PFLepTightCuts(ev ,i) )
			{
				IsoLepIndex++;
				
				if(ev.PFLepCharge(i)<0.0)
				{
					isoLepMseq[isoLepMnum]=i;
					isoLepMnum++;
				}

				else if(ev.PFLepCharge(i)>0.0)
				{
					isoLepPseq[isoLepPnum]=i;
					isoLepPnum++;
				}
			}
		}
		histo1D["NofLep"]->Fill(IsoLepIndex , w );
		histo1D["NofLep2"]->Fill(ev.NPFMuon() , w ); 


		//----------deltaR between PFMuon and Regular Muon-------------------------

		for(int i=0; i<ev.NPFMuon(); i++ )
		{
			for(int j=0; j<ev.NMuon(); j++ )
			{
				double dr = deltaR( ev.PFMuonEta(i), ev.PFMuonPhi(i), ev.MuonEta(j), ev.MuonPhi(j) );
				
				if( PFMuonTightCuts(ev, i) && IsIsoMuon(j, ev) ) histo1D["dRPFMuonRegMuon"]->Fill( dr );
				
			}
		}





		// ------------Wmunu identification---------------------------------------

		for(int i=0; i<ev.NGenPar(); i++)
		{
			if(abs(ev.GenParId(i) )==11 && ev.GenParStatus(i)==3 )
			{
				histo1D["GenElecPt"]->Fill( ev.GenParPt(i), w );
			}
			else if(abs(ev.GenParId(i) )==13 && ev.GenParStatus(i)==3 )
			{
			  if(ev.GenParCharge(i)==-1)histo1D["GenMuonPt"]->Fill( ev.GenParPt(i), w );
				
			}
			else if(abs(ev.GenParId(i) )==15 && ev.GenParStatus(i)==3 )
			{
				histo1D["GenTauPt"]->Fill( ev.GenParPt(i), w );
			}
		}

		double WlepnuMT=0;
		if(IsoLepIndex==1)
		{

			double MTPt=0;

			for(int i=0; i<ev.NPFLep(); i++ )
			{
				if( PFLepTightCuts(ev ,i) )
				{  
					double MTEn= ev.PFLepPt(i)+ ev.MetPt(t);
					double MTPx= ev.PFLepPx(i)+ ev.MetPx(t);
					double MTPy= ev.PFLepPy(i)+ ev.MetPy(t);

					MTPt=sqrt(MTPx*MTPx+MTPy*MTPy);
					WlepnuMT=sqrt((MTEn*MTEn)-(MTPt*MTPt));	
				}	
			} 
			
			if(WlepnuMT>0)
			{
				histo1D["WlepnuPT"]->Fill( MTPt, w );
				
				histo1D["WlepnuMT"]->Fill( WlepnuMT, w );
				histo1D["WlepnuMT_2"]->Fill( WlepnuMT, w );
				histo1D["WlepnuMT_300"]->Fill( WlepnuMT, w );
				
				histo1D["njets_1"]->Fill( njets, w );

				for(int i=0; i<ev.NGenPar(); i++)
				{
					if(abs(ev.GenParId(i) )==11 && ev.GenParStatus(i)==3 )
					{
						histo1D["WlepnuMT_e"]->Fill( WlepnuMT, w );
					}
					else if(abs(ev.GenParId(i) )==13 && ev.GenParStatus(i)==3 )
					{
						histo1D["WlepnuMT_m"]->Fill( WlepnuMT, w );
						
					}
					else if(abs(ev.GenParId(i) )==15 && ev.GenParStatus(i)==3 )
					{
						histo1D["WlepnuMT_t"]->Fill( WlepnuMT, w );
					}
				}
			}


		
			
			if( WlepnuMT>50 && WlepnuMT<100 )
			{


				histo1D["WlepnuPT_50_100"]->Fill( MTPt, w );		  
				histo1D["WlepnuMT_50_100"]->Fill( WlepnuMT, w );
				histo1D["WlepnuMT_50_100_2"]->Fill( WlepnuMT, w );
				histo1D["njets_2"]->Fill( njets, w );
						
				for(int i=0; i<ev.NGenPar(); i++)
				{
		
					if(abs(ev.GenParId(i) )==11 && ev.GenParStatus(i)==3 )
					{
						histo1D["WlepnuMT_50_100_e"]->Fill( WlepnuMT, w );
					}
					else if(abs(ev.GenParId(i) )==13 && ev.GenParStatus(i)==3 )
					{
						histo1D["WlepnuMT_50_100_m"]->Fill( WlepnuMT, w );
					}
					else if(abs(ev.GenParId(i) )==15 && ev.GenParStatus(i)==3 )
					{
						histo1D["WlepnuMT_50_100_t"]->Fill( WlepnuMT, w );
					}

				}
			}
			
		}
		
	
		
		//-------------Zmumu  identification------------------------------------
	   
		
		if( isoLepPnum==1 &&  isoLepMnum==1)
		{

			double dilepPhi =0;
			double ZleplepMT=0;
			double ZPt=0;

			for(int i=0; i<isoLepMnum ; i++ )
			{
				int ixmum=isoLepMseq[i];
				
				for(int j=0; j<isoLepPnum ; j++ )
				{  
					int ixmup=isoLepPseq[j] ;
					
					double ZEn= ev.PFLepE(ixmup)  + ev.PFLepE(ixmum) ;
					double ZPx= ev.PFLepPx(ixmup) + ev.PFLepPx(ixmum);
					double ZPy= ev.PFLepPy(ixmup) + ev.PFLepPy(ixmum);
					double ZPz= ev.PFLepPz(ixmup) + ev.PFLepPz(ixmum);
				  
					ZPt=sqrt(ZPx*ZPx + ZPy*ZPy);
				  
					ZleplepMT=sqrt((ZEn*ZEn)-(ZPt*ZPt)-(ZPz*ZPz));
					
					dilepPhi = atan2( ZPy, ZPx);
				}
			} 
			
			if(ZleplepMT>0)
			{
				histo1D["ZleplepPT"]->Fill( ZPt, w );
				histo1D["ZleplepMT"]->Fill( ZleplepMT, w );
				histo1D["ZleplepMT_2"]->Fill( ZleplepMT, w );
				histo1D["njets_3"]->Fill( njets, w );
			}
					      			
			if( ZleplepMT>81 && ZleplepMT<101 )
			{
				histo1D["ZleplepMT_81_101"]->Fill( ZleplepMT, w );
				histo1D["ZleplepMT_81_101_2"]->Fill( ZleplepMT, w );

			}
			if( ZleplepMT>60 && ZleplepMT<120 )
			{
				histo1D["ZleplepMT_60_120"]->Fill( ZleplepMT, w );
				histo1D["ZleplepPT_60_120"]->Fill( ZPt, w );

				double  METparalle = ev.MetPt(t) * cos( deltaPhi( ev.MetPhi(t), dilepPhi ) );
				double  METperpendicular = ev.MetPt(t) * sin( deltaPhi( ev.MetPhi(t), dilepPhi ) );

				histo1D["METparalle"]->Fill(  METparalle , w ); 
				histo1D["METperpendicular"] ->Fill( METperpendicular , w );
				histo1D["DPhiPFMetDiLep"]->Fill(  deltaPhi( ev.MetPhi(t), dilepPhi )  , w );

				histo1D["DPhiPFMetDiLep2"]->Fill(  ev.MetPhi(t)- dilepPhi  , w );


				histo1D["PhiDiLep"]->Fill(  dilepPhi  , w );

				if(ev.NPV()>1 && ev.NPV()<4) histo1D["METPar1"]->Fill(  METparalle , w ); 
				if(ev.NPV()>3 && ev.NPV()<9) histo1D["METPar2"]->Fill(  METparalle , w ); 
				if(ev.NPV()>8 ) histo1D["METPar3"]->Fill(  METparalle , w ); 

				histo1D["njets_4"]->Fill( njets, w );
				histo1D["ZleplepPFMET"]->Fill( ev.MetPt(t), w );

			}

			
			
		}
		
		
		return true;
	}
	
	std::ostream& hWZAnalysis::Description(std::ostream &ostrm) 
	{
		ostrm << "  WZ Analysis (output in " << mFileName << "):";
		return ostrm;
	}

	//-------------- End Job-----------------------------------------------------------------------------------
	hWZAnalysis::~hWZAnalysis() 
	{	

		for(int i=1; i<22; i++)
		{
		        double a1= histo1D["WlepnuMT_2"]->GetBinContent(i);
		        histo1D["WlepnuMT_210"]->SetBinContent( i , a1 );

		}
		for(int i=1; i<32; i++)
		{
		        double a1= histo1D["WlepnuMT_300"]->GetBinContent(i);
		        histo1D["WlepnuMT_310"]->SetBinContent( i , a1 );

		}


		fileOut->Write();
		delete fileOut;	
	}
	
	
///============================================================================================================================================


	
///---------------------------Source of W after Monojet Cuts Analysis -----------------------------------------------------------------------
	
	//----------------MuonAnalysis Histograms  Defination--------------------------------------------------------------------

	hWSourceAnalysis::hWSourceAnalysis(const std::string & fileName):
	mFileName(fileName)
	{
		fileOut = new TFile(mFileName.c_str(),"recreate");
		histo1D["WplusPT"]              = new TH1D("WplusPT"         , "WplusPT"           , 100, 0, 1000);
		histo1D["WminusPT"]             = new TH1D("WminusPT"        , "WminusPT"          , 100, 0, 1000);

		histo1D["WPT"]                  = new TH1D("WPT"             , "WPT"               , 100, 0, 1000);

		histo1D["WplusRminus"]          = new TH1D("WplusRminus"     , "WplusRminus"       , 100, 0, 1000);
				
		
		histo1D["PFMuonIsTracker"]        = new TH1D("PFMuonIsTracker"     , "WplusRminus"       , 10, 0, 10); 
		histo1D["PFMuonIsGlobal"]         = new TH1D("PFMuonIsGlobal"      , "WplusRminus"       , 10, 0, 10);
		histo1D["PFMuonCombChi2Norm"]     = new TH1D("PFMuonCombChi2Norm"  , "WplusRminus"       , 100, 0, 100);
		histo1D["PFMuonNumOfMatches"]     = new TH1D("PFMuonNumOfMatches"  , "WplusRminus"       , 100, 0, 100);
		histo1D["PFMuonTrkDxy"]           = new TH1D("PFMuonTrkDxy"        , "WplusRminus"       , 100, 0, 2);
		histo1D["PFMuonTrkValidHits"]          = new TH1D("PFMuonTrkValidHits"            , "WplusRminus"       , 100, 0, 100);
		histo1D["PFMuonTrkNumOfValidPixHits"]  = new TH1D("PFMuonTrkNumOfValidPixHits"    , "WplusRminus"       , 100, 0, 100);     
		histo1D["PFMuonStandValidHits"]        = new TH1D("PFMuonStandValidHits"          , "WplusRminus"       , 100, 0, 100);     
		histo1D["PFMuonPt"]                    = new TH1D("PFMuonPt"  , "WplusRminus"       , 100, 0, 1000);     
		histo1D["PFMuonEta"]                   = new TH1D("PFMuonEta" , "WplusRminus"       , 100, -4, 4);  
	
		histo1D["PFMuonIso"]                   = new TH1D("PFMuonIso" , "WplusRminus"       , 300, -1, 2);    
	
	}


	// ---------------MuonANalysis Histograms Filling------------------------------------------------------------------------

	bool hWSourceAnalysis::Process(EventData & ev) 
	{

		//double w= ev.Weight();
		//int  t= ev.MetType(); 
		

		for(int i=0; i<ev.NGenPar(); i++)
		{

			if(abs(ev.GenParId(i) )==24 && ev.GenParStatus(i)==3 )
			{
				histo1D["WPT"]->Fill( ev.GenParPt(i) );
			}
			if(abs(ev.GenParId(i) )==24 && ev.GenParStatus(i)==3 && ev.GenParCharge(i)==-1 )
			{
				histo1D["WminusPT"]->Fill( ev.GenParPt(i) );

			}
			if(abs(ev.GenParId(i) )==24 && ev.GenParStatus(i)==3 && ev.GenParCharge(i)== 1 )
			{
				histo1D["WplusPT"]->Fill( ev.GenParPt(i) );
			}
		}
		
		for(int i=0; i<ev.NPFMuon(); i++)
		{

			histo1D["PFMuonIsTracker"]->Fill(ev.PFMuonIsTracker(i)  );
			histo1D["PFMuonIsGlobal"]->Fill(ev.PFMuonIsGlobal(i)  );
			histo1D["PFMuonNumOfMatches"]->Fill(ev.PFMuonNumOfMatches(i)  );
			histo1D["PFMuonCombChi2Norm"]->Fill(ev.PFMuonCombChi2Norm(i)  );
			histo1D["PFMuonTrkDxy"]->Fill(ev.PFMuonTrkDxy(i)  );
			histo1D["PFMuonTrkValidHits"]->Fill(ev.PFMuonTrkValidHits(i)  );
			histo1D["PFMuonTrkNumOfValidPixHits"]->Fill(ev.PFMuonTrkNumOfValidPixHits(i) );
			histo1D["PFMuonStandValidHits"]->Fill(ev.PFMuonStandValidHits(i) );
			histo1D["PFMuonPt"]->Fill(ev.PFMuonPt(i)  );
			histo1D["PFMuonEta"]->Fill(abs( ev.PFMuonEta(i) )  );
		

					
			float Iso = 0.0;
			Iso = (ev.PFMuonNeutralHadronIso(i) + ev.PFMuonChargedHadronIso(i) + ev.PFMuonPhotonIso(i))/ev.PFMuonPt(i);
			
			histo1D["PFMuonIso"]->Fill( Iso );
		
		}
			

		return true;
	}
	
	std::ostream& hWSourceAnalysis::Description(std::ostream &ostrm) 
	{
		ostrm << "  Source of W Analysis (output in " << mFileName << "):";
		return ostrm;
	}

	//--------------MuonAnalysis End Job-----------------------------------------------------------------------------------
	hWSourceAnalysis::~hWSourceAnalysis() 
	{	
		
		histo1D["WplusRminus"]->Divide( histo1D["WplusPT"], histo1D["WminusPT"] );



		fileOut->Write();
		delete fileOut;	
	}
	
	


///============================================================================================================================================

void  OutputEPS( map<string,TH1D*> histos_ , string dirName)
{


  std::map<std::string, TH1D*>::iterator histo1Diter;

  char dir[150],str[255], rm[255];
  sprintf(dir,"%s_eps" , dirName.c_str() );
  sprintf(str,"mkdir %s",dir);
  sprintf(rm,"rm -rf  %s",dir);
  system(rm);
  system(str);
  gROOT->Reset();
  gROOT->SetBatch(true);
  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetOptStat(1111);


  for(histo1Diter = histos_.begin(); histo1Diter != histos_.end(); histo1Diter++)
    {

      TCanvas *can=new TCanvas("MonoJet","MonoJet",0,0,550,410);
      can->cd();
      can->SetLogy();
      //TPaveStats *ptstats;
      //ptstats = new TPaveStats(0.75,0.8,0.99,1.0,"brNDC");

      //histo1Diter->second->GetListOfFunctions()->Add(ptstats);

      //ptstats->SetParent( histo1Diter->second->GetListOfFunctions());

      histo1Diter->second->Draw();

      histo1Diter->second->SetStats(1);

      //ptstats->SetOptStat(1111);


      std::string filename = dir;
      filename += '/';
      filename +=  histo1Diter->first;

      filename  += ".eps";
      can->SaveAs( filename.c_str() );
      
    }

}
	
	
	


}

