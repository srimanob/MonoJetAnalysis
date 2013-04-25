// C++
//
// Package:    NtupleAnalyzer
// Class:      NtupleAnalyzer
// 

////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            //
//         Original Author:  Mehmet Vergili                                                   //
//               Created:   30 May 2010                                                       //
//                           MonoJet Analysis  ntuple producer                                //
////////////////////////////////////////////////////////////////////////////////////////////////

#include "NtupleAnalyzer.h"

#define TIVMAX     10000
#define MAXMUON    30
#define MAXTAU     50
#define MAXELEC    30
#define MAXJET     30
#define MAXPHOT    30
#define MAXGENPAR  1000

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "CMGTools/External/interface/PileupJetIdentifier.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "MonoJetAnalysis/NtupleAnalyzer/interface/ElectronEffectiveArea.h"

using namespace edm;
using namespace reco;
using namespace std;

class NtupleAnalyzer : public edm::EDAnalyzer 
{
public:
  explicit NtupleAnalyzer(const edm::ParameterSet&);
  ~NtupleAnalyzer();
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  void FirstValue();
  
  /// ----------member data ---------------------------
  Service<TFileService> fs;
  TTree *mtree; 
  map<string,TH1D*> histo1D;
  map<string,TH2D*> histo2D;
  
  ///
  InputTag TriggerTag;
  double   JetPtCutTag;
  double   JetEtaCutTag;
  double   WeightTag;
  bool     isMCTag;
  double   isSignalTag;
  double   triggerUsed;
  
  ///HLT  L1, L1Tech
  int     nHLT;
  int     nL1;
  int     nL1T;
  int     nNoiseFlag; 
  int     HLTArray[500];
  int     L1Array[128];
  int     L1TArray[64];
  int     HLTArray2[100];
  int     HLTPreScale[500];
  int     HLTPreScale2[100];
  int     NoiseFlag[20]; 
  char    trgnm[15000];
  TriggerNames trgnm_, trgnm2_;
  int     nhlt;

  ///Rho
  double  mfastJetRho;
  
  ///Run event Lumi BX
  int     mRun;
  int     mLumi;
  int     mBX;
  int     mnpvm1;
  int     mnpv0;
  int     mnpvp1;
  long    mEvent;
  
  ///Noise Flags
  int     flg_hnoise;
  int     flg_hfbadhit;
  int     flg_ecalspike;
  int     mbeamHaloLoose;
  int     mbeamHaloTight;
  double  mSumTrackPt;
 
  ///------------------------Generator Information------------------------------------------------------
  ///Gen Particle 	
  int     mNGenPar;
  int     mGenParIndex[MAXGENPAR]; 
  int     mGenParId[MAXGENPAR]; 
  int     mGenParStatus[MAXGENPAR]; 
  int     mGenParMother[MAXGENPAR]; 
  int     mGenParCharge[MAXGENPAR];
  int     mGenParDoughterOf[MAXGENPAR]; 
  int     mGenParMother1[MAXGENPAR]; 
  int     mGenParMother2[MAXGENPAR];
  //
  double  mGenParE[MAXGENPAR];
  double  mGenParPt[MAXGENPAR]; 
  double  mGenParPx[MAXGENPAR]; 
  double  mGenParPy[MAXGENPAR]; 
  double  mGenParPz[MAXGENPAR]; 
  double  mGenParEta[MAXGENPAR]; 
  double  mGenParPhi[MAXGENPAR]; 
  double  mGenParMass[MAXGENPAR];
  //
  double  mGenScale;
  double  mPdfscale;
  double  mPdfx1; 
  double  mPdfx2; 
  double  mPdfpdf1;
  double  mPdfpdf2; 
  double  mPdfWeights[150];
  double  mPdfWeights1[150];
  //
  int     mPdff1; 
  int     mPdff2;	
  int     mNPdfWeights;
  int     mNPdfWeights1;
  //
  int     mWTauDecayMode;
  int     mWTauN;
  int     mWTauDecayId[MAXGENPAR];  
  int     mWTauDecayStatus[MAXGENPAR]; 
  double  mWTauDecayPt[MAXGENPAR]; 
  double  mWTauDecayEta[MAXGENPAR];
  double  mWTauDecayPhi[MAXGENPAR];
  double  mWTauDecayMass[MAXGENPAR];
  
  ///------------------------Calo AK5 Jets------------------------------------------------------
  double  mCaloAK5JetE[MAXJET];
  double  mCaloAK5JetPt[MAXJET];
  double  mCaloAK5JetPx[MAXJET];
  double  mCaloAK5JetPy[MAXJET];
  double  mCaloAK5JetPz[MAXJET]; 
  double  mCaloAK5JetEta[MAXJET];
  double  mCaloAK5JetPhi[MAXJET];
  double  mCaloAK5JetEmf[MAXJET];
  double  mCaloAK5JetfHPD[MAXJET];
  double  mCaloAK5JetfRBX[MAXJET];
  double  mCaloAK5JetN90Hits[MAXJET];
  int     mNCaloAK5Jets;  
  int     mCaloAK5JetN90[MAXJET]; 
  int     mCaloAK5JetNtrkCalo[MAXJET]; 
  int     mCaloAK5JetNtrkVtx[MAXJET];
  double  mCaloAK5JetSigEta[MAXJET];
  double  mCaloAK5JetSigPhi[MAXJET];
  double  mCaloAK5JetIDEmf[MAXJET];
  double  mCaloAK5JetECor[MAXJET];
  double  mCaloAK5JetPtCor[MAXJET];
  double  mCaloAK5JetPxCor[MAXJET];
  double  mCaloAK5JetPyCor[MAXJET];
  double  mCaloAK5JetPzCor[MAXJET]; 
  double  mCaloAK5TrackPt[MAXJET];	
  double  mCaloAK5JetBtagTkCountHighEff[MAXJET]; 
  double  mCaloAK5JetBTagSimpleSecVtx[MAXJET];
  double  mCaloAK5JetBTagCombSecVtx[MAXJET]; 
  int     mCaloAK5JetIDLOOSE[MAXJET]; 
  int     mCaloAK5JetIDTIGHT[MAXJET];
  
  ///--------------PF AK5Jets-------------------------------------------
  int     mNPFAK5Jets;
  int     mPFAK5JetN90[MAXJET];
  int     mPFAK5JetNtrkPF[MAXJET];
  int     mPFAK5JetNtrkVtx[MAXJET];
  double  mPFAK5JetE[MAXJET];
  double  mPFAK5JetPt[MAXJET];
  double  mPFAK5JetPx[MAXJET];
  double  mPFAK5JetPy[MAXJET];
  double  mPFAK5JetPz[MAXJET];
  double  mPFAK5JetEta[MAXJET];
  double  mPFAK5JetPhi[MAXJET];
  double  mPFAK5JetfHPD[MAXJET];
  double  mPFAK5JetfRBX[MAXJET];
  double  mPFAK5JetN90Hits[MAXJET];
  double  mPFAK5JetSigEta[MAXJET];
  double  mPFAK5JetSigPhi[MAXJET];
  double  mPFAK5JetIDEmf[MAXJET];
  double  mPFAK5JetECor[MAXJET];
  double  mPFAK5JetPtCor[MAXJET];
  double  mPFAK5JetPxCor[MAXJET];
  double  mPFAK5JetPyCor[MAXJET];
  double  mPFAK5JetPzCor[MAXJET];
  //
  double  mPFAK5JetBtagTkCountHighEff[MAXJET];
  double  mPFAK5JetBtagTkCountHighPur[MAXJET];
  double  mPFAK5JetBtagJetProbability[MAXJET];
  double  mPFAK5JetBtagJetBProbability[MAXJET];
  double  mPFAK5JetBTagSimpleSecVtx[MAXJET];
  double  mPFAK5JetBTagCombSecVtx[MAXJET];
  double  mPFAK5JetBTagCombSecVtxMVA[MAXJET];   
  //
  double  mPFAK5uncer[MAXJET];
  double  mPFAK5JetNeuEmEngFrac[MAXJET];
  double  mPFAK5JetChaEmEngFrac[MAXJET];
  double  mPFAK5JetChaHadEngFrac[MAXJET];
  double  mPFAK5JetNeuHadEngFrac[MAXJET];
  double  mPFAK5JetChaMuEng[MAXJET];
  double  mPFAK5JetMuonEng[MAXJET];
  double  mPFAK5JetPhotEng[MAXJET];
  double  mPFAK5JetElecEng[MAXJET];		
  int     mPFAK5JetNumOfChaMu[MAXJET];
  int     mPFAK5JetNumOfMuon[MAXJET];
  int     mPFAK5JetNumOfPhot[MAXJET];
  int     mPFAK5JetNumOfElec[MAXJET];		
  int     mPFAK5JetNumOfNeu[MAXJET];
  int     mPFAK5JetNumOfCha[MAXJET];
  int     mPFAK5JetNumOfNeuHad[MAXJET];
  int     mPFAK5JetNumOfChaHad[MAXJET];
  int     mPFAK5JetNumOfDaughters[MAXJET];
  int     mPFAK5JetIDLOOSE[MAXJET];
  int     mPFAK5JetIDTIGHT[MAXJET];
  int     mPFAK5JetPUFullJetId[MAXJET];
  
  ///Gen AK5 Jets
  double  mGenAK5JetE[MAXJET];
  double  mGenAK5JetPt[MAXJET];
  double  mGenAK5JetPx[MAXJET];
  double  mGenAK5JetPy[MAXJET];
  double  mGenAK5JetPz[MAXJET];
  double  mGenAK5JetEta[MAXJET];
  double  mGenAK5JetPhi[MAXJET];
  double  mGenAK5JetEmEnergy[MAXJET];
  double  mGenAK5JetHadEnergy[MAXJET];		
  int     mNGenAK5Jets; 
  
  ///--------------METS-------------------------------------------
  int     mNMet;
  double  mMetPt[30];
  double  mMetPhi[30];
  double  mMetSumEt[30];
  double  mMetPx[30];
  double  mMetPy[30];
  double  mMetSign[30];
  
  ///--------------MHT-------------------------------------------
  double  mMHTPt;
  double  mMHTPhi;
  double  mMHTPx;
  double  mMHTPy;
  double  mMHTSign;
  
  
  ///------------MUONS-------------------------------------------
  int     mNMuon;
  double  mMuonPt[MAXMUON];
  double  mMuonEt[MAXMUON];
  double  mMuonE[MAXMUON];
  double  mMuonPx[MAXMUON];
  double  mMuonPy[MAXMUON];
  double  mMuonPz[MAXMUON];
  double  mMuonEta[MAXMUON];
  double  mMuonPhi[MAXMUON];
  double  mMuonCharge[MAXMUON];  			  
  int	  mMuonIsGlobal[MAXMUON];
  int	  mMuonIsStandAlone[MAXMUON];
  int	  mMuonIsTracker[MAXMUON];			  
  double  mMuonSumPtDR03[MAXMUON];
  double  mMuonSumPtDR05[MAXMUON];
  double  mMuonEmEtDR03[MAXMUON];
  double  mMuonHadEtDR03[MAXMUON];
  int     mMuonNumOfMatches[MAXMUON];
  
  // comb muon	
  double  mMuonCombChi2Norm[MAXMUON];  
  int	  mMuonCombValidHits[MAXMUON];  
  int	  mMuonCombLostHits[MAXMUON];
  double  mMuonCombPt[MAXMUON]; 
  double  mMuonCombPz[MAXMUON]; 
  double  mMuonCombP[MAXMUON]; 
  double  mMuonCombEta[MAXMUON]; 
  double  mMuonCombPhi[MAXMUON]; 
  double  mMuonCombChi2[MAXMUON]; 
  double  mMuonCombCharge[MAXMUON]; 
  double  mMuonCombQOverPError[MAXMUON]; 
  double  mMuonCombNdof[MAXMUON]; 
  double  mMuonCombVx[MAXMUON]; 
  double  mMuonCombVy[MAXMUON]; 
  double  mMuonCombVz[MAXMUON]; 
  double  mMuonCombD0[MAXMUON]; 
  double  mMuonCombDz[MAXMUON]; 
  
  // standalone muon	
  double  mMuonStandChi2Norm[MAXMUON];
  int	  mMuonStandValidHits[MAXMUON];
  int	  mMuonStandLostHits[MAXMUON];
  double  mMuonStandPt[MAXMUON];
  double  mMuonStandPz[MAXMUON];
  double  mMuonStandP[MAXMUON];
  double  mMuonStandEta[MAXMUON];
  double  mMuonStandPhi[MAXMUON];
  double  mMuonStandChi2[MAXMUON];
  double  mMuonStandCharge[MAXMUON];
  double  mMuonStandQOverPError[MAXMUON];
  
  // track muon	
  double  mMuonTrkChi2Norm[MAXMUON]; 
  int	  mMuonTrkValidHits[MAXMUON];
  int	  mMuonTrkLostHits[MAXMUON];
  double  mMuonTrkPt[MAXMUON]; 
  double  mMuonTrkPz[MAXMUON]; 
  double  mMuonTrkP[MAXMUON]; 
  double  mMuonTrkEta[MAXMUON]; 
  double  mMuonTrkPhi[MAXMUON]; 
  double  mMuonTrkChi2[MAXMUON]; 
  double  mMuonTrkCharge[MAXMUON]; 
  double  mMuonTrkQOverPError[MAXMUON]; 
  double  mMuonTrkDxy[MAXMUON]; 
  int     mMuonTrkNumOfValidPixHits[MAXMUON];
  
  
  ///------------PF MUONS-------------------------------------------
  int     mNPFMuon;
  double  mPFMuonPt[MAXMUON];               
  double  mPFMuonEt[MAXMUON];               
  double  mPFMuonE[MAXMUON];                
  double  mPFMuonPx[MAXMUON];               
  double  mPFMuonPy[MAXMUON];               
  double  mPFMuonPz[MAXMUON];               
  double  mPFMuonEta[MAXMUON];              
  double  mPFMuonPhi[MAXMUON];              
  int     mPFMuonCharge[MAXMUON];           
  //
  int     mPFMuonIsGlobal[MAXMUON];         
  int     mPFMuonIsStandAlone[MAXMUON];     
  int     mPFMuonIsTracker[MAXMUON];        
  //
  double  mPFMuonChargedHadronIso[MAXMUON]; 
  double  mPFMuonPhotonIso[MAXMUON];        
  double  mPFMuonNeutralHadronIso[MAXMUON]; 
  int     mPFMuonisGMPT[MAXMUON];           
  int     mPFMuonNumOfMatches[MAXMUON];
  double  mPFMuonR04ChargedHadronPt[MAXMUON];
  double  mPFMuonR04NeutralHadronEt[MAXMUON];
  double  mPFMuonR04PhotonEt[MAXMUON];
  double  mPFMuonR04PUPt[MAXMUON];
  
  //
  double  mPFMuoninnertrackPt[MAXMUON];     
  int     mPFMuonnValidHits[MAXMUON];       
  int     mPFMuonnValidPixelHits[MAXMUON];  
  double  mPFMuondxy[MAXMUON];
  double  mPFMuondz[MAXMUON];     
  //
  double  mPFMuonCombChi2Norm[MAXMUON];
  int     mPFMuonCombValidHits[MAXMUON];
  int     mPFMuonCombLostHits[MAXMUON];    
  double  mPFMuonCombPt[MAXMUON];          
  double  mPFMuonCombPz[MAXMUON];          
  double  mPFMuonCombP[MAXMUON];           
  double  mPFMuonCombEta[MAXMUON];         
  double  mPFMuonCombPhi[MAXMUON];         
  double  mPFMuonCombChi2[MAXMUON];        
  double  mPFMuonCombCharge[MAXMUON];      
  double  mPFMuonCombQOverPError[MAXMUON]; 	
  double  mPFMuonCombNdof[MAXMUON];        
  double  mPFMuonCombVx[MAXMUON];          
  double  mPFMuonCombVy[MAXMUON];          
  double  mPFMuonCombVz[MAXMUON];          
  double  mPFMuonCombD0[MAXMUON];          
  double  mPFMuonCombDz[MAXMUON];          
  //
  double  mPFMuonStandChi2Norm[MAXMUON];   
  int     mPFMuonStandValidHits[MAXMUON];  
  int     mPFMuonStandLostHits[MAXMUON];   
  double  mPFMuonStandPt[MAXMUON];         
  double  mPFMuonStandPz[MAXMUON];         
  double  mPFMuonStandP[MAXMUON];          
  double  mPFMuonStandEta[MAXMUON];        
  double  mPFMuonStandPhi[MAXMUON];        
  double  mPFMuonStandChi2[MAXMUON];       
  double  mPFMuonStandCharge[MAXMUON];     
  double  mPFMuonStandQOverPError[MAXMUON];
  //
  double  mPFMuonTrkChi2Norm[MAXMUON];    
  int     mPFMuonTrkValidHits[MAXMUON];   
  int     mPFMuonTrkLostHits[MAXMUON];    
  double  mPFMuonTrkPt[MAXMUON];          
  double  mPFMuonTrkPz[MAXMUON];          
  double  mPFMuonTrkP[MAXMUON];           
  double  mPFMuonTrkEta[MAXMUON];         
  double  mPFMuonTrkPhi[MAXMUON];         
  double  mPFMuonTrkChi2[MAXMUON];        
  double  mPFMuonTrkCharge[MAXMUON];      
  double  mPFMuonTrkQOverPError[MAXMUON]; 
  double  mPFMuonTrkDxy[MAXMUON];         
  double  mPFMuonTrkNumOfValidPixHits[MAXMUON];
  	
  
  ///--------------Electron-------------------------------------------
  int     mElecEcalDrivenSeed[MAXELEC];        
  int     mElecID80[MAXELEC];            
  int     mElecID95[MAXELEC];   
  int     mElecdB[MAXELEC];              
  int     mElecIsEB[MAXELEC]; 
  int     mElecCharge[MAXELEC];   
  int     mElecNumOfValidHits[MAXELEC];  
  int     mElecInnerNumOfHits[MAXELEC];  
  int     mNElec;
  //
  double  mElecE[MAXELEC];               
  double  mElecPt[MAXELEC];              
  double  mElecPx[MAXELEC];              
  double  mElecPy[MAXELEC];              
  double  mElecPz[MAXELEC];              
  double  mElecEta[MAXELEC];             
  double  mElecPhi[MAXELEC];             
  double  mElecdr03HcalTowerSumEt[MAXELEC]; 
  double  mElecdr03EcalRecHitSumEt[MAXELEC]; 
  double  mElecdr03TkSumPt[MAXELEC];     
  double  mElecdist[MAXELEC];            
  double  mElecdcot[MAXELEC];            
  double  mElecNormChi2[MAXELEC];        
  double  mElecdxy[MAXELEC];             
  double  mElecdz[MAXELEC];                         
  double  mElecfbrem[MAXELEC];           
  double  mElecDEtaSuTrAtVtx[MAXELEC];   
  double  mElecDPhiSuTrAtVtx[MAXELEC];   
  double  mElecHadronicOverEm[MAXELEC];
  double  mElecHcalOverEcal[MAXELEC];    
  double  mElecSuperClusOverP[MAXELEC];  
  double  mElecetaeta[MAXELEC];          
  double  mElecietaieta[MAXELEC];  
  
  ///--------------PF Electron-------------------------------------------
  int     mNPFElec;
  int     mPFElecCharge[MAXELEC]; 
  int     mPFElecIsEB[MAXELEC];  
  //
  double  mPFElecE[MAXELEC];           
  double  mPFElecPt[MAXELEC];          
  double  mPFElecPx[MAXELEC];          
  double  mPFElecPy[MAXELEC];          
  double  mPFElecPz[MAXELEC];          
  double  mPFElecEta[MAXELEC];         
  double  mPFElecPhi[MAXELEC];         
  double  mPFElecCharHadIso[MAXELEC];  
  double  mPFElecPhoIso[MAXELEC];      
  double  mPFElecNeuHadIso[MAXELEC];   
  double  mPFElecMva[MAXELEC]; 
  double  mPFElecEffArea[MAXELEC];
  //
  double  mPFElecdxy[MAXELEC];         
  double  mPFElecdz[MAXELEC];          
  double  mPFElecHadOverEm[MAXELEC];   
  double  mPFElecHcalOverEm[MAXELEC];  
  double  mPFElecSupClusOverP[MAXELEC];
  double  mPFElecInnerHits[MAXELEC];   
  double  mPFElecConvDist[MAXELEC];    
  double  mPFElecConvDcot[MAXELEC];
  //
  int     mPFElecEcalDrivenSeed[MAXELEC]; 
  int     mPFElecdB[MAXELEC];  
  int     mPFElecNumOfValidHits[MAXELEC];  
  double  mPFElecdr03HcalTowerSumEt[MAXELEC]; 
  double  mPFElecdr03EcalRecHitSumEt[MAXELEC]; 
  double  mPFElecdr03TkSumPt[MAXELEC]; 
  double  mPFElecNormChi2[MAXELEC];    
  double  mPFElecfbrem[MAXELEC];           
  double  mPFElecDEtaSuTrAtVtx[MAXELEC];   
  double  mPFElecDPhiSuTrAtVtx[MAXELEC];   
  double  mPFElecHadronicOverEm[MAXELEC];
  double  mPFElecHcalOverEcal[MAXELEC];    
  double  mPFElecSuperClusOverP[MAXELEC];  
  double  mPFElecetaeta[MAXELEC];          
  double  mPFElecietaieta[MAXELEC];  
  //
  int     mPFeidLoose[MAXELEC];              
  int     mPFeidRobustHighEnergy[MAXELEC];   
  int     mPFeidRobustLoose[MAXELEC];        
  int     mPFeidRobustTight[MAXELEC];        
  int     mPFeidTight[MAXELEC];              
  int     mPFevspi[MAXELEC];                 
  int     mPFevsmu[MAXELEC];                 
  
  ///-------------Taus--------------------------------------------------
  int     mNTau;
  int     mTauCharge[MAXTAU];
  double  mTauE[MAXTAU]; 
  double  mTauPt[MAXTAU]; 
  double  mTauPx[MAXTAU]; 
  double  mTauPy[MAXTAU]; 
  double  mTauPz[MAXTAU]; 
  double  mTauEta[MAXTAU]; 
  double  mTauPhi[MAXTAU];
  double  mTauEtaEtaMoment[MAXTAU]; 
  double  mTauPhiPhiMoment[MAXTAU]; 
  double  mTauEtaPhiMoment[MAXTAU]; 			
  double  mTauLeadPFChargedHadrCandsignedSipt[MAXTAU];
  double  mTauIsoPFChargedHadrCandsPtSum[MAXTAU];
  double  mTauIsoPFGammaCandsEtSum[MAXTAU];      
  double  mTauMaximumHCALPFClusterEt[MAXTAU];    
  double  mTauEmFraction[MAXTAU];                
  double  mTauHcalTotOverPLead[MAXTAU];          
  double  mTauHcalMaxOverPLead[MAXTAU];          
  double  mTauHcal3x3OverPLead[MAXTAU];          
  double  mTauEcalStripSumEOverPLead[MAXTAU];    
  double  mTauBremsRecoveryEOverPLead[MAXTAU];         
  double  mTauElectronPreIDOutput[MAXTAU];       
  double  mTauElectronPreIDDecision[MAXTAU];     
  double  mTauCaloComp[MAXTAU];                  
  double  mTauSegComp[MAXTAU];                   
  double  mTauMuonDecision[MAXTAU]; 
  //
  double  mTausignalPFChargedHadrCands[MAXTAU];
  double  mTausignalPFGammaCands[MAXTAU];
  //
  double  mTauDisAgainstElectronDeadECAL[MAXTAU];
  double  mTauDisAgainstElectronLoose[MAXTAU];
  double  mTauDisAgainstElectronLooseMVA2[MAXTAU];
  double  mTauDisAgainstElectronLooseMVA3[MAXTAU];
  double  mTauDisAgainstElectronMVA[MAXTAU];
  double  mTauDisAgainstElectronMVA2category[MAXTAU];
  double  mTauDisAgainstElectronMVA2raw[MAXTAU];
  double  mTauDisAgainstElectronMVA3category[MAXTAU];
  double  mTauDisAgainstElectronMVA3raw[MAXTAU];
  double  mTauDisAgainstElectronMedium[MAXTAU];
  double  mTauDisAgainstElectronMediumMVA2[MAXTAU];
  double  mTauDisAgainstElectronMediumMVA3[MAXTAU];
  double  mTauDisAgainstElectronTight[MAXTAU];
  double  mTauDisAgainstElectronTightMVA2[MAXTAU];
  double  mTauDisAgainstElectronTightMVA3[MAXTAU];
  double  mTauDisAgainstElectronVLooseMVA2[MAXTAU];
  double  mTauDisAgainstElectronVTightMVA3[MAXTAU];
  double  mTauDisAgainstMuonLoose[MAXTAU];
  double  mTauDisAgainstMuonLoose2[MAXTAU];
  double  mTauDisAgainstMuonMedium[MAXTAU];
  double  mTauDisAgainstMuonMedium2[MAXTAU];
  double  mTauDisAgainstMuonTight[MAXTAU];
  double  mTauDisAgainstMuonTight2[MAXTAU];
  double  mTauDisByCombinedIsolationDeltaBetaCorrRaw[MAXTAU];
  double  mTauDisByCombinedIsolationDeltaBetaCorrRaw3Hits[MAXTAU];
  double  mTauDisByIsolationMVA2raw[MAXTAU];
  double  mTauDisByIsolationMVAraw[MAXTAU];
  double  mTauDisByLooseCombinedIsolationDeltaBetaCorr[MAXTAU];
  double  mTauDisByLooseCombinedIsolationDeltaBetaCorr3Hits[MAXTAU];
  double  mTauDisByLooseIsolationMVA[MAXTAU];
  double  mTauDisByLooseIsolationMVA2[MAXTAU];
  double  mTauDisByMediumCombinedIsolationDeltaBetaCorr[MAXTAU];
  double  mTauDisByMediumCombinedIsolationDeltaBetaCorr3Hits[MAXTAU];
  double  mTauDisByMediumIsolationMVA[MAXTAU];
  double  mTauDisByMediumIsolationMVA2[MAXTAU];
  double  mTauDisByTightCombinedIsolationDeltaBetaCorr[MAXTAU];
  double  mTauDisByTightCombinedIsolationDeltaBetaCorr3Hits[MAXTAU];
  double  mTauDisByTightIsolationMVA[MAXTAU];
  double  mTauDisByTightIsolationMVA2[MAXTAU];
  double  mTauDisByVLooseCombinedIsolationDeltaBetaCorr[MAXTAU];
  double  mTauDisDecayModeFinding[MAXTAU];
  //
  double  mTauJetPt[MAXTAU];
  double  mTauJetEta[MAXTAU];
  double  mTauJetPhi[MAXTAU];
  
  ///---------------PF Tau-----------------------------------------------	
  int     mNPFTau;
  int     mPFTauCharge[MAXTAU];
  double  mPFTauE[MAXTAU]; 
  double  mPFTauPt[MAXTAU]; 
  double  mPFTauPx[MAXTAU]; 
  double  mPFTauPy[MAXTAU]; 
  double  mPFTauPz[MAXTAU]; 
  double  mPFTauEta[MAXTAU]; 
  double  mPFTauPhi[MAXTAU];
  double  mPFTauEtaEtaMoment[MAXTAU]; 
  double  mPFTauPhiPhiMoment[MAXTAU]; 
  double  mPFTauEtaPhiMoment[MAXTAU]; 			
  double  mPFTauLeadPFChargedHadrCandsignedSipt[MAXTAU];
  double  mPFTauIsoPFChargedHadrCandsPtSum[MAXTAU];
  double  mPFTauIsoPFGammaCandsEtSum[MAXTAU];      
  double  mPFTauMaximumHCALPFClusterEt[MAXTAU];    
  double  mPFTauEmFraction[MAXTAU];                
  double  mPFTauHcalTotOverPLead[MAXTAU];          
  double  mPFTauHcalMaxOverPLead[MAXTAU];          
  double  mPFTauHcal3x3OverPLead[MAXTAU];          
  double  mPFTauEcalStripSumEOverPLead[MAXTAU];    
  double  mPFTauBremsRecoveryEOverPLead[MAXTAU];         
  double  mPFTauElectronPreIDOutput[MAXTAU];       
  double  mPFTauElectronPreIDDecision[MAXTAU];     
  double  mPFTauCaloComp[MAXTAU];                  
  double  mPFTauSegComp[MAXTAU];                   
  double  mPFTauMuonDecision[MAXTAU]; 
  //
  double  mPFTausignalPFChargedHadrCands[MAXTAU];
  double  mPFTausignalPFGammaCands[MAXTAU];
  //
  double  mPFTauDisAgainstElectronDeadECAL[MAXTAU];
  double  mPFTauDisAgainstElectronLoose[MAXTAU];
  double  mPFTauDisAgainstElectronLooseMVA2[MAXTAU];
  double  mPFTauDisAgainstElectronLooseMVA3[MAXTAU];
  double  mPFTauDisAgainstElectronMVA[MAXTAU];
  double  mPFTauDisAgainstElectronMVA2category[MAXTAU];
  double  mPFTauDisAgainstElectronMVA2raw[MAXTAU];
  double  mPFTauDisAgainstElectronMVA3category[MAXTAU];
  double  mPFTauDisAgainstElectronMVA3raw[MAXTAU];
  double  mPFTauDisAgainstElectronMedium[MAXTAU];
  double  mPFTauDisAgainstElectronMediumMVA2[MAXTAU];
  double  mPFTauDisAgainstElectronMediumMVA3[MAXTAU];
  double  mPFTauDisAgainstElectronTight[MAXTAU];
  double  mPFTauDisAgainstElectronTightMVA2[MAXTAU];
  double  mPFTauDisAgainstElectronTightMVA3[MAXTAU];
  double  mPFTauDisAgainstElectronVLooseMVA2[MAXTAU];
  double  mPFTauDisAgainstElectronVTightMVA3[MAXTAU];
  double  mPFTauDisAgainstMuonLoose[MAXTAU];
  double  mPFTauDisAgainstMuonLoose2[MAXTAU];
  double  mPFTauDisAgainstMuonMedium[MAXTAU];
  double  mPFTauDisAgainstMuonMedium2[MAXTAU];
  double  mPFTauDisAgainstMuonTight[MAXTAU];
  double  mPFTauDisAgainstMuonTight2[MAXTAU];
  double  mPFTauDisByCombinedIsolationDeltaBetaCorrRaw[MAXTAU];
  double  mPFTauDisByCombinedIsolationDeltaBetaCorrRaw3Hits[MAXTAU];
  double  mPFTauDisByIsolationMVA2raw[MAXTAU];
  double  mPFTauDisByIsolationMVAraw[MAXTAU];
  double  mPFTauDisByLooseCombinedIsolationDeltaBetaCorr[MAXTAU];
  double  mPFTauDisByLooseCombinedIsolationDeltaBetaCorr3Hits[MAXTAU];
  double  mPFTauDisByLooseIsolation[MAXTAU];
  double  mPFTauDisByLooseIsolationDeltaBetaCorr[MAXTAU];
  double  mPFTauDisByLooseIsolationMVA[MAXTAU];
  double  mPFTauDisByLooseIsolationMVA2[MAXTAU];
  double  mPFTauDisByMediumCombinedIsolationDeltaBetaCorr[MAXTAU];
  double  mPFTauDisByMediumCombinedIsolationDeltaBetaCorr3Hits[MAXTAU];
  double  mPFTauDisByMediumIsolation[MAXTAU];
  double  mPFTauDisByMediumIsolationDeltaBetaCorr[MAXTAU];
  double  mPFTauDisByMediumIsolationMVA[MAXTAU];
  double  mPFTauDisByMediumIsolationMVA2[MAXTAU];
  double  mPFTauDisByTightCombinedIsolationDeltaBetaCorr[MAXTAU];
  double  mPFTauDisByTightCombinedIsolationDeltaBetaCorr3Hits[MAXTAU];
  double  mPFTauDisByTightIsolation[MAXTAU];
  double  mPFTauDisByTightIsolationDeltaBetaCorr[MAXTAU];
  double  mPFTauDisByTightIsolationMVA[MAXTAU];
  double  mPFTauDisByTightIsolationMVA2[MAXTAU];
  double  mPFTauDisByVLooseCombinedIsolationDeltaBetaCorr[MAXTAU];
  double  mPFTauDisByVLooseIsolation[MAXTAU];
  double  mPFTauDisByVLooseIsolationDeltaBetaCorr[MAXTAU];
  double  mPFTauDisDecayModeFinding[MAXTAU];
  //
  double  mPFTauJetPt[MAXTAU];
  double  mPFTauJetEta[MAXTAU];
  double  mPFTauJetPhi[MAXTAU];
  
  ///------------Photons------------------------------------------------	
  int     mNPhot;
  double  mPhotE[MAXPHOT];
  double  mPhotPt[MAXPHOT]; 
  double  mPhotPx[MAXPHOT]; 
  double  mPhotPy[MAXPHOT]; 
  double  mPhotPz[MAXPHOT]; 
  double  mPhotEta[MAXPHOT]; 
  double  mPhotPhi[MAXPHOT];
  double  mPhotE1x5[MAXPHOT]; 
  double  mPhotE2x5[MAXPHOT]; 
  double  mPhotE5x5[MAXPHOT]; 
  double  mPhotSigEta[MAXPHOT];
  double  mPhotSigPhi[MAXPHOT];
  double  mPhotEcalIso04[MAXPHOT]; 
  double  mPhotHcalIso04[MAXPHOT]; 
  double  mPhotTrackIso04[MAXPHOT]; 
  double  mPhotHasPixSeed[MAXPHOT];
  int     mPhotIsPhot[MAXPHOT];
  
  ///------------Primary Vertices------------------------------------------------
  double  mPVx[200];
  double  mPVy[200];
  double  mPVz[200];
  double  mPVchi2[200];
  double  mPVndof[200]; 
  int	  mPVntracks[200];
  int     mNPV;
  
  ///------------TIV------------------------------------------------
  float   TIV[TIVMAX];
  int     tivN;
  double  tiv_ltrack_thr_;
  double  tiv_strack_thr_;
  double  tiv_cone_;
  double  tiv_inner_cone_;
  double  tiv_dz_thr_;
  double  tiv_dxy_thr_;
  float   TIV_pt[TIVMAX];
  float   TIV_eta[TIVMAX];
  float   TIV_phi[TIVMAX];
  float   TIV_px[TIVMAX];
  float   TIV_py[TIVMAX];
  float   TIV_pz[TIVMAX];
  float   TIV_dxy[TIVMAX];
  float   TIV_dsz[TIVMAX];
  float   TIV_dR[TIVMAX];
  float   TIV_dz[TIVMAX];
  float   TIV_d0[TIVMAX];
  float   TIV_dxy_corr[TIVMAX];
  float   TIV_dsz_corr[TIVMAX];
  float   TIV_dz_corr[TIVMAX];
  float   TIV_d0_corr[TIVMAX];
  //
  int     TIV_lead[TIVMAX];
  //
  float   LowTIV;
  
  ///------------Input Collections------------------------------------------------
  edm::InputTag Tracks_;
  edm::InputTag PFElectronTag_; 
  edm::InputTag PFMuonTag_; 
  edm::InputTag PFTauTag_;  
  edm::InputTag TauTag_;  
  edm::InputTag PFJetTag_;  
  edm::InputTag PFMETTag_;
  
  int     DEBUG;
  
  ///------------CaloTowers------------------------------------------------
  //double CaloTowerEt[30];
  //double CaloTowerPhi[30]; 
  double  mCaloTowerdEx;
  double  mCaloTowerdEy;
};


NtupleAnalyzer::NtupleAnalyzer(const edm::ParameterSet& iConfig)
{
  mtree        = fs->make<TTree>("ntuple","ntuple");
  WeightTag    = iConfig.getParameter<double>("weight");
  
  TriggerTag   = iConfig.getParameter<string>("TriggerTag");
  JetPtCutTag  = iConfig.getParameter<double>("jetPtCut");
  JetEtaCutTag = iConfig.getParameter<double>("jetEtaCut");
  
  isMCTag      = iConfig.getParameter<bool>("isMC");
  isSignalTag  = iConfig.getParameter<double>("isSignal");
  
  triggerUsed  = iConfig.getParameter<double>("triggerUsed");
  
  ///TIV
  tiv_ltrack_thr_ = iConfig.getParameter<double>("TIV_ltrack_thr");
  tiv_strack_thr_ = iConfig.getParameter<double>("TIV_strack_thr");
  tiv_dz_thr_     = iConfig.getParameter<double>("TIV_dz_thr");
  tiv_dxy_thr_    = iConfig.getParameter<double>("TIV_dxy_thr");
  tiv_cone_       = iConfig.getParameter<double>("TIV_cone_thr");
  tiv_inner_cone_ = iConfig.getParameter<double>("TIV_inner_cone_thr");
  Tracks_         = iConfig.getUntrackedParameter<edm::InputTag>("Tracks");

  //PFCollection
  PFElectronTag_  = iConfig.getUntrackedParameter<edm::InputTag>("PFElectronTag");
  PFMuonTag_      = iConfig.getUntrackedParameter<edm::InputTag>("PFMuonTag");
  PFTauTag_       = iConfig.getUntrackedParameter<edm::InputTag>("PFTauTag");
  TauTag_         = iConfig.getUntrackedParameter<edm::InputTag>("TauTag");
  PFJetTag_       = iConfig.getUntrackedParameter<edm::InputTag>("PFJetTag");
  PFMETTag_       = iConfig.getUntrackedParameter<edm::InputTag>("PFMETTag");
  
  DEBUG=0;
}


NtupleAnalyzer::~NtupleAnalyzer()
{

}



// ------------ method called to for each event  ------------

void NtupleAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  ///--------------------------------------------------------------------------
  /// Check isMCTag
  ///--------------------------------------------------------------------------
  bool isMCTagCheck = !iEvent.eventAuxiliary().isRealData();
  if(isMCTag!=isMCTagCheck){
    cout<<"Wrong isMCTag! The GlobalTag is maybe wrong. Please check!"<<endl;
    return;
  }
  
  
  ///-------------------------------------------------------------------------- 
  /// Run  Event Lumi Bx
  ///--------------------------------------------------------------------------
  mRun   = iEvent.id().run();
  mEvent = iEvent.id().event();
  mLumi  = iEvent.luminosityBlock();
  mBX    = iEvent.bunchCrossing();
  
  
  ///--------------------------------------------------------------------------
  /// Prefilter
  ///--------------------------------------------------------------------------
  /*
    Handle< View<pat::MET> > PFMetHand2;
    iEvent.getByLabel("patMETsAK5Calo",PFMetHand2);
    const View<pat::MET> & pfmets2 = *PFMetHand2;
    if(pfmets2[0].uncorrectedPt(pat::MET::uncorrALL)< 60) return;
  */
  //if(mEvent!=128062935) return;
  
  
  ///-------------------------------------------------------------------------- 
  /// Store trigger information & Filter
  ///--------------------------------------------------------------------------
  Handle<TriggerResults> hltTriggerResultHandle;
  iEvent.getByLabel( TriggerTag , hltTriggerResultHandle);
  trgnm_ = iEvent.triggerNames(*hltTriggerResultHandle);
  const TriggerResults &Hlt = *hltTriggerResultHandle;
  char tmpnm1[3000],tmpnm2[3000];
  nhlt=0;
  if(&Hlt){
    //cout <<Hlt.size()<<endl;
    //cout <<"---------------------------------"<<endl;
    nhlt = Hlt.size();
    //trgnm_.init(Hlt);
    
    for (int itrig = 0; itrig != nhlt; ++itrig){
      string trigName=trgnm_.triggerName(itrig);
      bool accept = Hlt.accept(itrig);
      if(accept && trigName.find("HLT")!=string::npos){
	sprintf(tmpnm1,"%s",tmpnm2);
	sprintf(tmpnm2,"%s%s",tmpnm1,trigName.c_str());
      }    
      //cout <<itrig<<" "<<trigName<<" "<<accept<<endl;
    }
    //cout <<trgnm<<endl;
    //string strtrg = trgnm;
  }
  
  int flg_trg=0;
  string strtrg = tmpnm2;
  
  if(triggerUsed==1){
    if(strtrg.find("HLT_MET120_HBHENoiseCleaned_v")!=string::npos) flg_trg=1;
    if(strtrg.find("HLT_MonoCentralPFJet80_PFMETnoMu")!=string::npos) flg_trg=1;
  }
  else if(triggerUsed==2){
    if(strtrg.find("HLT_IsoMu24_eta2p1_v")!=string::npos) flg_trg=1;
    if(strtrg.find("HLT_Mu40_eta2p1_v")!=string::npos) flg_trg=1;
  }
  else if(triggerUsed==3){
    if(strtrg.find("HLT_Mu17_Mu8_v")!=string::npos) flg_trg=1;
  }
  else if(triggerUsed==4){
    if(strtrg.find("HLT_Ele27_WP80_v")!=string::npos) flg_trg=1;
  }
  else if(triggerUsed==5){
    if(strtrg.find("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v")!=string::npos) flg_trg=1;
  }
  else if(triggerUsed==6){
    if(strtrg.find("HLT_Physics_v")!=string::npos) flg_trg=1;
  }
  else if(triggerUsed==99){ //no trigger
    flg_trg=1;
  }
  else{
    if(strtrg.find("HLT_MET120_HBHENoiseCleaned_v")!=string::npos) flg_trg=1;
    if(strtrg.find("HLT_MonoCentralPFJet80_PFMETnoMu")!=string::npos) flg_trg=1;
  }
  
  if (flg_trg==0) return; 
  sprintf(trgnm,"TRG%s", tmpnm2);

  
  ///-------------------------------------------------------------------------- 
  ///
  ///--------------------------------------------------------------------------
  int hltCount=0;
  if(!hltTriggerResultHandle.isValid()){
    cout << "invalid handle for HLT TriggerResults" << std::endl;
  } 
  else{
    //HLTNames.init(*hltTriggerResultHandle);
    string tempnames;  
    hltCount = hltTriggerResultHandle->size();
    for(int i = 0 ; i < hltCount ; i++){
      //tempnames += HLTNames.triggerName(i) + "  ";
      HLTArray[i] = hltTriggerResultHandle->accept(i);
      
      //cout << i << "  " <<trgnm_.triggerName(i) << "  " << hltTriggerResultHandle->accept(i) << endl;
    }  
    nHLT = hltCount;
  }
	
  
  ///-------------------------------------------------------------------------- 
  /// NoiseFlag
  ///--------------------------------------------------------------------------
  //TriggerNames myTrigName;
  Handle<TriggerResults> myTrig;
  iEvent.getByLabel("TriggerResults", myTrig );
  //iEvent.getByLabel(edm::InputTag("TriggerResults","","PAT"), myTrig );
  
  int hltCount2 = myTrig->size();
  for(int i = 0 ; i < hltCount2; i++){
    //cout << i << "  " <<  myTrig->accept(i)  << endl;
    NoiseFlag[i] = myTrig->accept(i);
  }
  nNoiseFlag = hltCount2;
  
  
  ///-------------------------------------------------------------------------- 
  /// Shuichi's correction Method for PFMET Phi
  ///--------------------------------------------------------------------------
  /*
  //calo towers
  Handle<CaloTowerCollection> calo_h;
  iEvent.getByLabel("towerMaker", calo_h);
  const CaloTowerCollection *towers = calo_h.failedToGet () ? 0 :&*calo_h;
  
  //if (towers) { // object is available 
  
  reco::Particle::Point  vertex_=reco::Jet::Point(-0.4,0.5,0); 
  
  // double sum_et = 0.0;
  // double sum_ex = 0.0;
  // double sum_ey = 0.0;
  // double sum_ez = 0.0;
  double dEx=0.0;
  double dEy=0.0;
  
  int cti=0;
  
  for (CaloTowerCollection::const_iterator kal=towers->begin(); kal!=towers->end(); kal++){	
    // double eta   = kal->eta();
    double phi   = kal->phi();
    double theta = kal->theta();
    double e     = kal->energy();
    double et    = e*sin(theta);
    
    // double etEM    = (kal->emEnergy())*sin(theta);
    // double etHad   = (kal->hadEnergy())*sin(theta);
    
    math::PtEtaPhiMLorentzVector ct(kal->p4(vertex_));
    if(et>0.3){
      // sum_ez += e*cos(theta);
      // sum_et += et;
      // sum_ex += et*cos(phi);
      // sum_ey += et*sin(phi);
      
      // sum_ex += ct.px();
      // sum_ey += ct.py();
      
      dEx=dEx+(ct.px()-et*cos(phi));
      dEy=dEy+(ct.py()-et*sin(phi));
      
    }
    cti++;
  }   // loop over calo towers.
  
  //    double metPt=sqrt(sum_ex*sum_ex+sum_ey*sum_ey);
  //    double metPhi=atan2(-sum_ey,-sum_ex);
  
  // correct pfMET
  //double ptx=(pfmet->pt())*cos(pfmet->phi()) - dEx;
  //double pty=(pfmet->pt())*sin(pfmet->phi()) - dEy;
  
  //double newPfMetPt=sqrt(ptx*ptx+pty*pty);
  //double phi=atan2(pty,ptx);
  
  //histo1D["newPfMetPhi"]->Fill(phi);
  //histo1D["newPfMetPt"]->Fill(newPfMetPt);
  
  mCaloTowerdEx = dEx;
  mCaloTowerdEy = dEy;
  
  //}
  
  //cout  <<  mRun  <<  "   " << mLumi  <<  "   " <<   mEvent  << endl; 
  */

  
  ///-------------------------------------------------------------------------- 
  /// PileUP Summury
  ///--------------------------------------------------------------------------
  if(isMCTag){
    Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);
    
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    
    int nm1 = -1; int n0 = -1; int np1 = -1;
    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI){
      int BX = PVI->getBunchCrossing();
      
      if(BX == -1){ 
	nm1 = PVI->getPU_NumInteractions();
      }
      if(BX == 0){ 
	n0 = PVI->getPU_NumInteractions();
      }
      if(BX == 1){ 
	np1 = PVI->getPU_NumInteractions();
      }
    }
    //double MyWeight3D = LumiWeights_.weight3D( nm1,n0,np1);
    mnpvm1 = nm1; 
    mnpv0  = n0;
    mnpvp1 = np1;
  }

  
  ///-------------------------------------------------------------------------- 
  /// Rho
  ///--------------------------------------------------------------------------
  edm::Handle<double> rho;
  const edm::InputTag eventrho("kt6PFJets", "rho");
  iEvent.getByLabel(eventrho,rho);
  mfastJetRho = *rho;
  
  
  ///-------------------------------------------------------------------------- 
  /// AK5CaloJet
  ///--------------------------------------------------------------------------
  edm::Handle<edm::View<pat::Jet> > JetHand;
  iEvent.getByLabel("cleanPatJetsAK5Calo" ,JetHand);
  int jeti=0;
  /*
  for(unsigned int ind=0; ind<(*JetHand).size() && ind<MAXJET; ind++){ 
  
  const pat::Jet& jet2 = (*JetHand)[ind];
  const pat::Jet& jet =  (*JetHand)[ind].correctedJet("Uncorrected");
  
  if( jet2.pt() < JetPtCutTag ) continue;
  
  /// default scale factor: Raw & L1 & L2 & L3
  /// http://cmslxr.fnal.gov/lxr/source/DataFormats/PatCandidates/interface/JetCorrFactors.h
  
  JetIDSelectionFunctor jetIDFunctorLoose(JetIDSelectionFunctor::PURE09, JetIDSelectionFunctor::LOOSE);
  JetIDSelectionFunctor jetIDFunctorTight(JetIDSelectionFunctor::PURE09, JetIDSelectionFunctor::TIGHT);
  
  mCaloAK5JetIDLOOSE[jeti] = jetIDFunctorLoose(jet2);
  mCaloAK5JetIDTIGHT[jeti] = jetIDFunctorTight(jet2);
  
  mCaloAK5JetPt[jeti]      =  jet.pt();
  mCaloAK5JetPx [jeti]     =  jet.momentum().X();
  mCaloAK5JetPy [jeti]     =  jet.momentum().Y();
  mCaloAK5JetPz [jeti]     =  jet.momentum().Z();
  mCaloAK5JetE [jeti]      =  jet.energy();
  
  mCaloAK5JetEta[jeti]     =  jet2.eta();
  mCaloAK5JetPhi[jeti]     =  jet2.phi();
  mCaloAK5JetEmf [jeti]    =  jet2.emEnergyFraction();
  mCaloAK5JetN90 [jeti]    =  jet2.n90();
  
  mCaloAK5JetN90Hits[jeti] =  jet2.jetID().n90Hits ;
  mCaloAK5JetfHPD [jeti]   =  jet2.jetID().fHPD ;
  mCaloAK5JetfRBX [jeti]   =  jet2.jetID().fRBX ;
  mCaloAK5JetIDEmf[jeti]   =  jet2.jetID().restrictedEMF;
  
  mCaloAK5JetSigEta[jeti]  =  jet2.etaetaMoment();
  mCaloAK5JetSigPhi[jeti]  =  jet2.phiphiMoment();
  
  mCaloAK5JetPtCor[jeti]      =  jet2.pt();
  mCaloAK5JetPxCor [jeti]     =  jet2.momentum().X();
  mCaloAK5JetPyCor [jeti]     =  jet2.momentum().Y();
  mCaloAK5JetPzCor [jeti]     =  jet2.momentum().Z();
  mCaloAK5JetECor [jeti]      =  jet2.energy();
  
  mCaloAK5JetBtagTkCountHighEff[jeti] = jet.bDiscriminator("trackCountingHighEffBJetTags");
  mCaloAK5JetBTagSimpleSecVtx[jeti]   = jet.bDiscriminator("simpleSecondaryVertexBJetTags");
  mCaloAK5JetBTagCombSecVtx[jeti]     = jet.bDiscriminator("combinedSecondaryVertexBJetTags");
  
  const reco::TrackRefVector &tracks = jet.associatedTracks();
  double ptsum = 0;
  for (size_t i = 0; i < tracks.size(); ++i){
  ptsum += tracks[i]->pt();
  }
  mCaloAK5TrackPt[jeti] = ptsum; 
  
  if(isMCTag){
  if(jet.genJet()!= 0){
  mGenAK5JetPt[jeti]=jet.genJet()->pt();
  mGenAK5JetE[jeti]=jet.genJet()->energy();
  mGenAK5JetPx[jeti]=jet.genJet()->momentum().X();
  mGenAK5JetPy[jeti]=jet.genJet()->momentum().Y();
  mGenAK5JetPz[jeti]=jet.genJet()->momentum().z();
  mGenAK5JetEta[jeti]=jet.genJet()->eta();
  mGenAK5JetPhi[jeti]=jet.genJet()->phi();
  mGenAK5JetEmEnergy[jeti]=jet.genJet()->emEnergy();
  mGenAK5JetHadEnergy[jeti]=jet.genJet()->emEnergy();
  }
  else {
  mGenAK5JetPt[jeti]       =-999;
  mGenAK5JetE[jeti]        =-999;
  mGenAK5JetPx[jeti]       =-999;
  mGenAK5JetPy[jeti]       =-999;
  mGenAK5JetPz[jeti]       =-999;
  mGenAK5JetEta[jeti]      =-999;
  mGenAK5JetPhi[jeti]      =-999;
  mGenAK5JetEmEnergy[jeti] =-999;
  mGenAK5JetHadEnergy[jeti]=-999;
  }
  }
  
  jeti++;
  }
  */
  mNCaloAK5Jets = jeti;
  
  
  ///-------------------------------------------------------------------------- 
  /// AK5PFJet
  ///--------------------------------------------------------------------------
  //iEvent.getByLabel("cleanPatJetsAK5PF" ,JetHand);
  iEvent.getByLabel(PFJetTag_,JetHand);
  jeti=0;
  edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get("AK5PF",JetCorParColl);
  JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
  JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(JetCorPar); 
  
  //edm::Handle<edm::ValueMap<float> > puJetIdMVA;
  //iEvent.getByLabel("puJetMva:fullDiscriminant",puJetIdMVA);
  
  edm::Handle<edm::ValueMap<int> > puJetIdFlag;
  iEvent.getByLabel(edm::InputTag("puJetMva","fullId","PAT"),puJetIdFlag);
  int idflag;
  
  for(unsigned int ind=0; ind<(*JetHand).size() && ind<MAXJET; ind++){
    const pat::Jet& jet2 = (*JetHand)[ind];
    const pat::Jet& jet = (*JetHand)[ind].correctedJet("Uncorrected");
    
    if( jet2.pt() < JetPtCutTag ) continue;
    
    /// default scale factor: Raw & L1 & L2 & L3
    /// http://cmslxr.fnal.gov/lxr/source/DataFormats/PatCandidates/interface/JetCorrFactors.h
    
    PFJetIDSelectionFunctor pfjetIDFunctorLoose(PFJetIDSelectionFunctor::FIRSTDATA, PFJetIDSelectionFunctor::LOOSE);
    PFJetIDSelectionFunctor pfjetIDFunctorTight(PFJetIDSelectionFunctor::FIRSTDATA, PFJetIDSelectionFunctor::TIGHT);
    
    mPFAK5JetIDLOOSE[jeti]              = pfjetIDFunctorLoose(jet2);
    mPFAK5JetIDTIGHT[jeti]              = pfjetIDFunctorTight(jet2); 
    
    mPFAK5JetPUFullJetId[jeti] = 0;
    idflag = (*puJetIdFlag)[(JetHand->refAt(ind))];
    if( PileupJetIdentifier::passJetId(idflag, PileupJetIdentifier::kLoose  )) mPFAK5JetPUFullJetId[jeti] = 1;
    if( PileupJetIdentifier::passJetId(idflag, PileupJetIdentifier::kMedium )) mPFAK5JetPUFullJetId[jeti] = 2;
    if( PileupJetIdentifier::passJetId(idflag, PileupJetIdentifier::kTight  )) mPFAK5JetPUFullJetId[jeti] = 3;
    
    mPFAK5JetPt[jeti]                   = jet.pt();
    mPFAK5JetPx[jeti]                   = jet.momentum().X();
    mPFAK5JetPy[jeti]                   = jet.momentum().Y();
    mPFAK5JetPz[jeti]                   = jet.momentum().Z();
    mPFAK5JetE[jeti]                    = jet.energy();
    
    mPFAK5JetEta[jeti]                  = jet2.eta();
    mPFAK5JetPhi[jeti]                  = jet2.phi();		
    mPFAK5JetN90[jeti]                  = jet2.n90();
    mPFAK5JetNumOfDaughters[jeti]       = jet2.numberOfDaughters();
    
    ///use uncorrected jet for jetID
    mPFAK5JetN90Hits[jeti]              = jet.jetID().n90Hits ;
    mPFAK5JetfHPD[jeti]                 = jet.jetID().fHPD ;
    mPFAK5JetfRBX[jeti]                 = jet.jetID().fRBX ;
    mPFAK5JetIDEmf[jeti]                = jet.jetID().restrictedEMF;
    
    mPFAK5JetSigEta[jeti]               = jet2.etaetaMoment();
    mPFAK5JetSigPhi[jeti]               = jet2.phiphiMoment();
    mPFAK5JetPtCor[jeti]                = jet2.pt();
    mPFAK5JetPxCor[jeti]                = jet2.momentum().X();
    mPFAK5JetPyCor[jeti]                = jet2.momentum().Y();
    mPFAK5JetPzCor[jeti]                = jet2.momentum().Z();
    mPFAK5JetECor[jeti]                 = jet2.energy();
    
    mPFAK5JetNeuEmEngFrac[jeti]         = jet2.neutralEmEnergyFraction();
    mPFAK5JetChaEmEngFrac[jeti]         = jet2.chargedEmEnergyFraction();
    mPFAK5JetChaHadEngFrac[jeti]        = jet2.chargedHadronEnergyFraction();
    mPFAK5JetNeuHadEngFrac[jeti]        = jet2.neutralHadronEnergyFraction();
    
    mPFAK5JetChaMuEng[jeti]             = jet2.chargedMuEnergy();
    
    mPFAK5JetMuonEng[jeti]              = jet2.muonEnergy();
    mPFAK5JetPhotEng[jeti]              = jet2.photonEnergy();
    mPFAK5JetElecEng[jeti]              = jet2.electronEnergy();
    mPFAK5JetNumOfPhot[jeti]            = jet2.photonMultiplicity();
    mPFAK5JetNumOfElec[jeti]            = jet2.electronMultiplicity();
    mPFAK5JetNumOfNeuHad[jeti]          = jet2.neutralHadronMultiplicity();
    mPFAK5JetNumOfChaHad[jeti]          = jet2.chargedHadronMultiplicity();
    
    mPFAK5JetNumOfMuon[jeti]            = jet2.muonMultiplicity();
    mPFAK5JetNumOfChaMu[jeti]           = jet2.chargedMultiplicity();
    
    mPFAK5JetNumOfNeu[jeti]             = jet2.neutralMultiplicity();
    mPFAK5JetNumOfCha[jeti]             = jet2.chargedMultiplicity();
    
    mPFAK5JetBtagTkCountHighEff[jeti]   = jet.bDiscriminator("trackCountingHighEffBJetTags");
    mPFAK5JetBtagTkCountHighPur[jeti]   = jet.bDiscriminator("trackCountingHighPurBJetTags");
    mPFAK5JetBtagJetProbability[jeti]   = jet.bDiscriminator("jetProbabilityBJetTags");
    mPFAK5JetBtagJetBProbability[jeti]  = jet.bDiscriminator("jetBProbabilityBJetTags");
    mPFAK5JetBTagSimpleSecVtx[jeti]     = jet.bDiscriminator("simpleSecondaryVertexBJetTags");
    mPFAK5JetBTagCombSecVtx[jeti]       = jet.bDiscriminator("combinedSecondaryVertexBJetTags");
    mPFAK5JetBTagCombSecVtxMVA[jeti]    = jet.bDiscriminator("combinedSecondaryVertexMVABJetTags");  
   
    ///-----------Jets Uncertanity --------------------------------------------------------
    if(isMCTag){
      jecUnc->setJetEta(jet2.eta() ); // Give rapidity of jet you want tainty on
      jecUnc->setJetPt( jet2.pt() );// Also give the corrected pt of the jet you want the uncertainty on
      // The following function gives the relative uncertainty in the jet Pt.
      // i.e. ptCorSmeared = (1 +- uncer) * ptCor  
      mPFAK5uncer[jeti] =    jecUnc->getUncertainty(true); 
      // In principle, boolean controls if uncertainty on +ve or -ve side is returned (asymmetric errors) but not yet implemented.
    }
    else{
      mPFAK5uncer[jeti]=0.;
    }
			
    jeti++;
  }
  mNPFAK5Jets = jeti;
  
  
  ///-------------------------------------------------------------------------- 
  /// CaloMET
  ///--------------------------------------------------------------------------
  for(int i=0; i<30; i++){
    mMetPt[i]=0; 
    mMetPhi[i]=0; 
    mMetSumEt[i]=0; 
    mMetPx[i]=0; 
    mMetPy[i]=0; 
    mMetSign[i]=0;
  }
  Handle<View<pat::MET> > CaloMetHand;
  iEvent.getByLabel("patMETsAK5Calo",CaloMetHand);
  const View<pat::MET> & mets = *CaloMetHand;
  
  mNMet=30;
  
  // 0=full corr	1=uncorrNone  2=uncorrALL 3=uncorrJES  4=uncorrMUON  5=TAU
  
  mMetPt[0]    = mets[0].et();
  mMetPhi[0]   = mets[0].phi();
  mMetPx[0]    = mets[0].px();
  mMetPy[0]    = mets[0].py();
  mMetSumEt[0] = mets[0].sumEt();
  
  mMetPt[1]    = mets[0].uncorrectedPt(pat::MET::uncorrNONE); 
  mMetPhi[1]   = mets[0].uncorrectedPhi(pat::MET::uncorrNONE); 
  mMetPx[1]    = mets[0].corEx(pat::MET::uncorrNONE); 
  mMetPy[1]    = mets[0].corEy(pat::MET::uncorrNONE); 
  mMetSumEt[1] = mets[0].corSumEt(pat::MET::uncorrNONE); 
  
  mMetPt[2]    = mets[0].uncorrectedPt(pat::MET::uncorrALL); 
  mMetPhi[2]   = mets[0].uncorrectedPhi(pat::MET::uncorrALL); 
  mMetPx[2]    = mets[0].corEx(pat::MET::uncorrALL); 
  mMetPy[2]    = mets[0].corEy(pat::MET::uncorrALL); 
  mMetSumEt[2] = mets[0].corSumEt(pat::MET::uncorrALL); 
  
  mMetPt[3]    = mets[0].uncorrectedPt(pat::MET::uncorrJES); 
  mMetPhi[3]   = mets[0].uncorrectedPhi(pat::MET::uncorrJES); 
  mMetPx[3]    = mets[0].corEx(pat::MET::uncorrJES); 
  mMetPy[3]    = mets[0].corEy(pat::MET::uncorrJES); 
  mMetSumEt[3] = mets[0].corSumEt(pat::MET::uncorrJES); 
  
  mMetPt[4]    = mets[0].uncorrectedPt(pat::MET::uncorrMUON); 
  mMetPhi[4]   = mets[0].uncorrectedPhi(pat::MET::uncorrMUON); 
  mMetPx[4]    = mets[0].corEx(pat::MET::uncorrMUON); 
  mMetPy[4]    = mets[0].corEy(pat::MET::uncorrMUON); 
  mMetSumEt[4] = mets[0].corSumEt(pat::MET::uncorrMUON); 
  
  mMetPt[5]    = mets[0].uncorrectedPt(pat::MET::uncorrTAU); 
  mMetPhi[5]   = mets[0].uncorrectedPhi(pat::MET::uncorrTAU); 
  mMetPx[5]    = mets[0].corEx(pat::MET::uncorrTAU); 
  mMetPy[5]    = mets[0].corEy(pat::MET::uncorrTAU); 
  mMetSumEt[5] = mets[0].corSumEt(pat::MET::uncorrTAU); 
  
  
  ///-------------------------------------------------------------------------- 
  /// GenMET
  ///--------------------------------------------------------------------------		
  if(isMCTag){	
    const GenMET *genmet;
    // Get Generated MET
    edm::Handle<GenMETCollection> gen;
    iEvent.getByLabel("genMetCalo", gen);
    if(!gen.isValid()){
      edm::LogInfo("OutputInfo") << " failed to retrieve data required by MET Task";
      edm::LogInfo("OutputInfo") << " MET Task cannot continue...!";
      return;
    } 
    else{
      const GenMETCollection *genmetcol = gen.product();
      genmet = &(genmetcol->front());
    }  
    
    mMetPt[6]    =  genmet->pt();
    mMetPhi[6]   =  genmet->phi();
    mMetPx[6]    =  genmet->px();
    mMetPy[6]    =  genmet->py();
    mMetSumEt[6] =  genmet->sumEt();
  }
  
  
  ///-------------------------------------------------------------------------- 
  /// PF MetsType1 Corrected
  ///--------------------------------------------------------------------------
  Handle<View<pat::MET> > PFMetType1Hand;
  //iEvent.getByLabel("patMETsPF",PFMetType1Hand);
  iEvent.getByLabel(PFMETTag_,PFMetType1Hand);
  const View<pat::MET> & pfmetsType1 = *PFMetType1Hand;
  
  //cout<<"PHAT-PFMET: "<<pfmetsType1[0].et()<<endl;
  
  mMetPt[10]    = pfmetsType1[0].et();
  mMetPhi[10]   = pfmetsType1[0].phi();
  mMetPx[10]    = pfmetsType1[0].px();
  mMetPy[10]    = pfmetsType1[0].py();
  mMetSumEt[10] = pfmetsType1[0].sumEt();
  
  
  ///-------------------------------------------------------------------------- 
  /// PF Mets
  ///--------------------------------------------------------------------------
  Handle<View<pat::MET> > PFMetHand;
  iEvent.getByLabel("patMETsPF", PFMetHand);
  const View<pat::MET> & pfmets = *PFMetHand;
  
  mMetPt[11]    = pfmets[0].et();
  mMetPhi[11]   = pfmets[0].phi();
  mMetPx[11]    = pfmets[0].px();
  mMetPy[11]    = pfmets[0].py();
  mMetSumEt[11] = pfmets[0].sumEt();
  
  mMetPt[12]    = pfmets[0].uncorrectedPt(pat::MET::uncorrALL); 
  mMetPhi[12]   = pfmets[0].uncorrectedPhi(pat::MET::uncorrALL); 
  mMetPx[12]    = pfmets[0].corEx(pat::MET::uncorrALL); 
  mMetPy[12]    = pfmets[0].corEy(pat::MET::uncorrALL); 
  mMetSumEt[12] = pfmets[0].corSumEt(pat::MET::uncorrALL); 
  
  mMetPt[13]    = pfmets[0].uncorrectedPt(pat::MET::uncorrJES); 
  mMetPhi[13]   = pfmets[0].uncorrectedPhi(pat::MET::uncorrJES); 
  mMetPx[13]    = pfmets[0].corEx(pat::MET::uncorrJES); 
  mMetPy[13]    = pfmets[0].corEy(pat::MET::uncorrJES); 
  mMetSumEt[13] = pfmets[0].corSumEt(pat::MET::uncorrJES); 
  
  mMetPt[14]    = pfmets[0].uncorrectedPt(pat::MET::uncorrMUON); 
  mMetPhi[14]   = pfmets[0].uncorrectedPhi(pat::MET::uncorrMUON); 
  mMetPx[14]    = pfmets[0].corEx(pat::MET::uncorrMUON); 
  mMetPy[14]    = pfmets[0].corEy(pat::MET::uncorrMUON); 
  mMetSumEt[14] = pfmets[0].corSumEt(pat::MET::uncorrMUON); 
  
  mMetPt[15]    = pfmets[0].uncorrectedPt(pat::MET::uncorrTAU); 
  mMetPhi[15]   = pfmets[0].uncorrectedPhi(pat::MET::uncorrTAU); 
  mMetPx[15]    = pfmets[0].corEx(pat::MET::uncorrTAU); 
  mMetPy[15]    = pfmets[0].corEy(pat::MET::uncorrTAU); 
  mMetSumEt[15] = pfmets[0].corSumEt(pat::MET::uncorrTAU); 
	
  
  ///-------------------------------------------------------------------------- 
  /// TC Mets
  ///--------------------------------------------------------------------------
  Handle<View<pat::MET> > TCMetHand;
  iEvent.getByLabel("patMETsTC",TCMetHand);
  const View<pat::MET> & tcmets = *TCMetHand;
  
  mMetPt[20]    = tcmets[0].et();
  mMetPhi[20]   = tcmets[0].phi();
  mMetPx[20]    = tcmets[0].px();
  mMetPy[20]    = tcmets[0].py();
  mMetSumEt[20] = tcmets[0].sumEt();
  
  mMetPt[21]    = tcmets[0].uncorrectedPt(pat::MET::uncorrNONE); 
  mMetPhi[21]   = tcmets[0].uncorrectedPhi(pat::MET::uncorrNONE); 
  mMetPx[21]    = tcmets[0].corEx(pat::MET::uncorrNONE); 
  mMetPy[21]    = tcmets[0].corEy(pat::MET::uncorrNONE); 
  mMetSumEt[21] = tcmets[0].corSumEt(pat::MET::uncorrNONE); 
  
  mMetPt[22]    = tcmets[0].uncorrectedPt(pat::MET::uncorrALL); 
  mMetPhi[22]   = tcmets[0].uncorrectedPhi(pat::MET::uncorrALL); 
  mMetPx[22]    = tcmets[0].corEx(pat::MET::uncorrALL); 
  mMetPy[22]    = tcmets[0].corEy(pat::MET::uncorrALL); 
  mMetSumEt[22] = tcmets[0].corSumEt(pat::MET::uncorrALL); 
  
  mMetPt[23]    = tcmets[0].uncorrectedPt(pat::MET::uncorrJES); 
  mMetPhi[23]   = tcmets[0].uncorrectedPhi(pat::MET::uncorrJES); 
  mMetPx[23]    = tcmets[0].corEx(pat::MET::uncorrJES); 
  mMetPy[23]    = tcmets[0].corEy(pat::MET::uncorrJES); 
  mMetSumEt[23] = tcmets[0].corSumEt(pat::MET::uncorrJES); 
  
  mMetPt[24]    = tcmets[0].uncorrectedPt(pat::MET::uncorrMUON); 
  mMetPhi[24]   = tcmets[0].uncorrectedPhi(pat::MET::uncorrMUON); 
  mMetPx[24]    = tcmets[0].corEx(pat::MET::uncorrMUON); 
  mMetPy[24]    = tcmets[0].corEy(pat::MET::uncorrMUON); 
  mMetSumEt[24] = tcmets[0].corSumEt(pat::MET::uncorrMUON); 
  
  mMetPt[25]    = tcmets[0].uncorrectedPt(pat::MET::uncorrTAU); 
  mMetPhi[25]   = tcmets[0].uncorrectedPhi(pat::MET::uncorrTAU); 
  mMetPx[25]    = tcmets[0].corEx(pat::MET::uncorrTAU); 
  mMetPy[25]    = tcmets[0].corEy(pat::MET::uncorrTAU); 
  mMetSumEt[25] = tcmets[0].corSumEt(pat::MET::uncorrTAU); 
  
  
  ///-------------------------------------------------------------------------- 
  /// Pat MHT
  ///--------------------------------------------------------------------------
  /*
    edm::Handle<edm::View<pat::MHT> > MHTHand;
    iEvent.getByLabel("patMHTsAK5Calo",MHTHand);
    const edm::View<pat::MHT> & mhts = *MHTHand;
    
    if ( MHTHand->size()!=0)
    {
    mMHTPt    = mhts[0].pt();
    //mMHTPhi   = mhts[0].phi();
    
    //cout  << mMHTPhi << endl;
    mMHTSign  = mhts[0].significance();
    }
  */
  
  
  ///-------------------------------------------------------------------------- 
  /// Vertices
  ///--------------------------------------------------------------------------
  reco::Vertex primaryvtx;
  Handle<reco::VertexCollection> recVtxs;
  iEvent.getByLabel("offlinePrimaryVertices",recVtxs);
  int  pvind=0;
  for(unsigned int ind=0;ind<recVtxs->size();ind++){
    if(!((*recVtxs)[ind].isFake())){
      mPVx[pvind]      = (*recVtxs)[ind].x();
      mPVy[pvind]      = (*recVtxs)[ind].y();
      mPVz[pvind]      = (*recVtxs)[ind].z();
      mPVchi2[pvind]   = (*recVtxs)[ind].chi2();
      mPVndof[pvind]   = (*recVtxs)[ind].ndof();
      mPVntracks[pvind]= (*recVtxs)[ind].tracksSize();
      if(pvind == 0) primaryvtx = (*recVtxs)[ind];
      pvind++;
    }
  }
  mNPV = pvind; 
  
  
  ///-------------------------------------------------------------------------- 
  /// BeamSpot
  ///--------------------------------------------------------------------------
  BeamSpot beamSpot;
  Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
  if (beamSpotHandle.isValid()){
    beamSpot = *beamSpotHandle;
  } 
  else{
    edm::LogInfo("MyAnalyzer")
      << "No beam spot available from EventSetup \n";
  }
  math::XYZPoint point(beamSpot.x0(),beamSpot.y0(), beamSpot.z0());
  
  
  ///-------------------------------------------------------------------------- 
  /// Muons
  ///--------------------------------------------------------------------------
  edm::Handle<edm::View<pat::Muon> > MuonHand;
  iEvent.getByLabel("cleanPatMuons",MuonHand);
  int muoni=0;
  /*
  for(unsigned int ind=0; ind<(*MuonHand).size() && ind<MAXMUON; ind++){ 
  const pat::Muon& muon = (*MuonHand)[ind];
  mMuonPt[muoni]           = muon.pt();
  mMuonEt[muoni]           = muon.et();
  mMuonE[muoni]            = muon.energy();
  mMuonPx[muoni]           = muon.momentum().X();
  mMuonPy[muoni]           = muon.momentum().Y();
  mMuonPz[muoni]           = muon.momentum().Z();
  mMuonEta[muoni]          = muon.eta();
  mMuonPhi[muoni]          = muon.phi();
  mMuonCharge[muoni]       = muon.charge();
  //
  mMuonIsGlobal[muoni]     = muon.isGlobalMuon();
  mMuonIsStandAlone[muoni] = muon.isStandAloneMuon();
  mMuonIsTracker[muoni]    = muon.isTrackerMuon();
  //
  mMuonSumPtDR03[muoni]    = muon.isolationR03().sumPt;
  mMuonSumPtDR05[muoni]    = muon.isolationR05().sumPt;
  mMuonEmEtDR03[muoni]     = muon.isolationR03().emEt;
  mMuonHadEtDR03[muoni]    = muon.isolationR03().hadEt;
  //
  mMuonNumOfMatches[muoni] = muon.numberOfMatches();
  //
  if( muon.isGlobalMuon() && muon.combinedMuon().isNonnull() ){
  mMuonCombChi2Norm[muoni]    = muon.combinedMuon()->normalizedChi2();
  mMuonCombValidHits[muoni]   = muon.combinedMuon()->found();
  mMuonCombLostHits[muoni]    = muon.combinedMuon()->lost();
  mMuonCombPt[muoni]          = muon.combinedMuon()->pt();
  mMuonCombPz[muoni]          = muon.combinedMuon()->pz();
  mMuonCombP[muoni]           = muon.combinedMuon()->p();
  mMuonCombEta[muoni]         = muon.combinedMuon()->eta();
  mMuonCombPhi[muoni]         = muon.combinedMuon()->phi();
  mMuonCombChi2[muoni]        = muon.combinedMuon()->chi2();
  mMuonCombCharge[muoni]      = muon.combinedMuon()->charge();
  mMuonCombQOverPError[muoni] = muon.combinedMuon()->qoverpError();		
  mMuonCombNdof[muoni]        = muon.combinedMuon()->ndof();
  mMuonCombVx[muoni]          = muon.combinedMuon()->vx();
  mMuonCombVy[muoni]          = muon.combinedMuon()->vy();
  mMuonCombVz[muoni]          = muon.combinedMuon()->vz();
  mMuonCombD0[muoni]          = muon.combinedMuon()->d0();
  mMuonCombDz[muoni]          = muon.combinedMuon()->dz();
  } 
  else{
  mMuonCombChi2Norm[muoni]    = 999.;
  mMuonCombValidHits[muoni]   = 999.;
  mMuonCombLostHits[muoni]    = 999.;
  mMuonCombPt[muoni]          = 999.;
  mMuonCombPz[muoni]          = 999.;
  mMuonCombP[muoni]           = 999.;
  mMuonCombEta[muoni]         = 999.;
  mMuonCombPhi[muoni]         = 999.;
  mMuonCombChi2[muoni]        = 999.;
  mMuonCombCharge[muoni]      = 999.;
  mMuonCombQOverPError[muoni] = 999.;
  mMuonCombNdof[muoni]        = 999.;
  mMuonCombVx[muoni]          = 999.;
  mMuonCombVy[muoni]          = 999.;
  mMuonCombVz[muoni]          = 999.;
  mMuonCombD0[muoni]          = 999.;
  mMuonCombDz[muoni]          = 999.;
  }
  //
  if (muon.standAloneMuon().isNonnull()){
  mMuonStandChi2Norm[muoni]    = muon.standAloneMuon()->normalizedChi2();
  mMuonStandValidHits[muoni]   = muon.standAloneMuon()->found();
  mMuonStandLostHits[muoni]    = muon.standAloneMuon()->lost();
  mMuonStandPt[muoni]          = muon.standAloneMuon()->pt();
  mMuonStandPz[muoni]          = muon.standAloneMuon()->pz();
  mMuonStandP[muoni]           = muon.standAloneMuon()->p();
  mMuonStandEta[muoni]         = muon.standAloneMuon()->eta();
  mMuonStandPhi[muoni]         = muon.standAloneMuon()->phi();
  mMuonStandChi2[muoni]        = muon.standAloneMuon()->chi2();
  mMuonStandCharge[muoni]      = muon.standAloneMuon()->charge();
  mMuonStandQOverPError[muoni] = muon.standAloneMuon()->qoverpError();
  } 
  else{
  mMuonStandChi2Norm[muoni]    = 999.; 
  mMuonStandValidHits[muoni]   = 999.; 
  mMuonStandLostHits[muoni]    = 999.; 
  mMuonStandPt[muoni]          = 999.; 
  mMuonStandPz[muoni]          = 999.; 
  mMuonStandP[muoni]           = 999.; 
  mMuonStandEta[muoni]         = 999.; 
  mMuonStandPhi[muoni]         = 999.; 
  mMuonStandChi2[muoni]        = 999.; 
  mMuonStandCharge[muoni]      = 999.; 
  mMuonStandQOverPError[muoni] = 999.; 
  }
  //
  if(muon.track().isNonnull()){
  mMuonTrkChi2Norm[muoni]    = muon.track()->normalizedChi2();
  mMuonTrkValidHits[muoni]   = muon.track()->found();
  mMuonTrkLostHits[muoni]    = muon.track()->lost();
  mMuonTrkPt[muoni]          = muon.track()->pt();
  mMuonTrkPz[muoni]          = muon.track()->pz();
  mMuonTrkP[muoni]           = muon.track()->p();
  mMuonTrkEta[muoni]         = muon.track()->eta();
  mMuonTrkPhi[muoni]         = muon.track()->phi();
  mMuonTrkChi2[muoni]        = muon.track()->chi2();
  mMuonTrkCharge[muoni]      = muon.track()->charge();
  mMuonTrkQOverPError[muoni] = muon.track()->qoverpError();
  mMuonTrkDxy[muoni]         = muon.track()->dxy( beamSpotHandle->position() );
  mMuonTrkNumOfValidPixHits[muoni] =  muon.track()->hitPattern().numberOfValidPixelHits();
  }
  else{
  mMuonTrkChi2Norm[muoni]    = 999.; 
  mMuonTrkValidHits[muoni]   = 999.; 
  mMuonTrkLostHits[muoni]    = 999.; 
  mMuonTrkPt[muoni]          = 999.; 
  mMuonTrkPz[muoni]          = 999.; 
  mMuonTrkP[muoni]           = 999.; 
  mMuonTrkEta[muoni]         = 999.; 
  mMuonTrkPhi[muoni]         = 999.; 
  mMuonTrkChi2[muoni]        = 999.; 
  mMuonTrkCharge[muoni]      = 999.; 
  mMuonTrkQOverPError[muoni] = 999.; 
  mMuonTrkDxy[muoni]         = 999.;
  mMuonTrkNumOfValidPixHits[muoni] = 999.;
  }  
  muoni++;
  }
  */
  mNMuon=muoni;

  
  ///-------------------------------------------------------------------------- 
  /// PFMuons
  ///--------------------------------------------------------------------------
  iEvent.getByLabel(PFMuonTag_,MuonHand);
  muoni=0;
  for(unsigned int ind=0; ind<(*MuonHand).size() && ind<MAXMUON; ind++){ 
    const pat::Muon& muon = (*MuonHand)[ind];
    mPFMuonPt[muoni]                  = muon.pt();
    mPFMuonEt[muoni]                  = muon.et();
    mPFMuonE[muoni]                   = muon.energy();
    mPFMuonPx[muoni]                  = muon.momentum().X();
    mPFMuonPy[muoni]                  = muon.momentum().Y();
    mPFMuonPz[muoni]                  = muon.momentum().Z();
    mPFMuonEta[muoni]                 = muon.eta();
    mPFMuonPhi[muoni]                 = muon.phi();
    mPFMuonCharge[muoni]              = muon.charge();
    //
    mPFMuonIsGlobal[muoni]            = muon.isGlobalMuon();
    mPFMuonIsStandAlone[muoni]        = muon.isStandAloneMuon();
    mPFMuonIsTracker[muoni]           = muon.isTrackerMuon();
    //
    mPFMuonChargedHadronIso[muoni]    = muon.chargedHadronIso();
    mPFMuonPhotonIso[muoni]           = muon.photonIso();
    mPFMuonNeutralHadronIso[muoni]    = muon.neutralHadronIso();
    mPFMuonisGMPT[muoni]              = muon.muonID("GlobalMuonPromptTight");
    mPFMuonNumOfMatches[muoni]        = muon.numberOfMatches(); 
    mPFMuonR04ChargedHadronPt[muoni]  = muon.pfIsolationR04().sumChargedHadronPt;
    mPFMuonR04NeutralHadronEt[muoni]  = muon.pfIsolationR04().sumNeutralHadronEt;
    mPFMuonR04PhotonEt[muoni]         = muon.pfIsolationR04().sumPhotonEt;
    mPFMuonR04PUPt[muoni]             = muon.pfIsolationR04().sumPUPt;
    //
    if(muon.innerTrack().isNonnull()){
      mPFMuoninnertrackPt[muoni]     = muon.innerTrack()->pt();
      mPFMuonnValidHits[muoni]       = muon.innerTrack()->numberOfValidHits();
      mPFMuonnValidPixelHits[muoni]  = muon.innerTrack()->hitPattern().numberOfValidPixelHits();
      mPFMuondxy[muoni]              = muon.innerTrack()->dxy(primaryvtx.position());
      mPFMuondz[muoni]               = muon.vz() - primaryvtx.position().z();
    }
    //
    if(muon.isGlobalMuon() && muon.combinedMuon().isNonnull()){
      mPFMuonCombChi2Norm[muoni]    = muon.combinedMuon()->normalizedChi2();
      mPFMuonCombValidHits[muoni]   = muon.combinedMuon()->found();
      mPFMuonCombLostHits[muoni]    = muon.combinedMuon()->lost();
      mPFMuonCombPt[muoni]          = muon.combinedMuon()->pt();
      mPFMuonCombPz[muoni]          = muon.combinedMuon()->pz();
      mPFMuonCombP[muoni]           = muon.combinedMuon()->p();
      mPFMuonCombEta[muoni]         = muon.combinedMuon()->eta();
      mPFMuonCombPhi[muoni]         = muon.combinedMuon()->phi();
      mPFMuonCombChi2[muoni]        = muon.combinedMuon()->chi2();
      mPFMuonCombCharge[muoni]      = muon.combinedMuon()->charge();
      mPFMuonCombQOverPError[muoni] = muon.combinedMuon()->qoverpError();		
      mPFMuonCombNdof[muoni]        = muon.combinedMuon()->ndof();
      mPFMuonCombVx[muoni]          = muon.combinedMuon()->vx();
      mPFMuonCombVy[muoni]          = muon.combinedMuon()->vy();
      mPFMuonCombVz[muoni]          = muon.combinedMuon()->vz();
      mPFMuonCombD0[muoni]          = muon.combinedMuon()->d0();
      mPFMuonCombDz[muoni]          = muon.combinedMuon()->dz();
    } 
    else{
      mPFMuonCombChi2Norm[muoni]    = 999.;
      mPFMuonCombValidHits[muoni]   = 999.;
      mPFMuonCombLostHits[muoni]    = 999.;
      mPFMuonCombPt[muoni]          = 999.;
      mPFMuonCombPz[muoni]          = 999.;
      mPFMuonCombP[muoni]           = 999.;
      mPFMuonCombEta[muoni]         = 999.;
      mPFMuonCombPhi[muoni]         = 999.;
      mPFMuonCombChi2[muoni]        = 999.;
      mPFMuonCombCharge[muoni]      = 999.;
      mPFMuonCombQOverPError[muoni] = 999.;
      mPFMuonCombNdof[muoni]        = 999.;
      mPFMuonCombVx[muoni]          = 999.;
      mPFMuonCombVy[muoni]          = 999.;
      mPFMuonCombVz[muoni]          = 999.;
      mPFMuonCombD0[muoni]          = 999.;
      mPFMuonCombDz[muoni]          = 999.;
    }
    //
    if(muon.standAloneMuon().isNonnull()){
      mPFMuonStandChi2Norm[muoni]    = muon.standAloneMuon()->normalizedChi2();
      mPFMuonStandValidHits[muoni]   = muon.standAloneMuon()->found();
      mPFMuonStandLostHits[muoni]    = muon.standAloneMuon()->lost();
      mPFMuonStandPt[muoni]          = muon.standAloneMuon()->pt();
      mPFMuonStandPz[muoni]          = muon.standAloneMuon()->pz();
      mPFMuonStandP[muoni]           = muon.standAloneMuon()->p();
      mPFMuonStandEta[muoni]         = muon.standAloneMuon()->eta();
      mPFMuonStandPhi[muoni]         = muon.standAloneMuon()->phi();
      mPFMuonStandChi2[muoni]        = muon.standAloneMuon()->chi2();
      mPFMuonStandCharge[muoni]      = muon.standAloneMuon()->charge();
      mPFMuonStandQOverPError[muoni] = muon.standAloneMuon()->qoverpError();
    } 
    else{
      mPFMuonStandChi2Norm[muoni]    = 999.; 
      mPFMuonStandValidHits[muoni]   = 999.; 
      mPFMuonStandLostHits[muoni]    = 999.; 
      mPFMuonStandPt[muoni]          = 999.; 
      mPFMuonStandPz[muoni]          = 999.; 
      mPFMuonStandP[muoni]           = 999.; 
      mPFMuonStandEta[muoni]         = 999.; 
      mPFMuonStandPhi[muoni]         = 999.; 
      mPFMuonStandChi2[muoni]        = 999.; 
      mPFMuonStandCharge[muoni]      = 999.; 
      mPFMuonStandQOverPError[muoni] = 999.; 
    }
    //
    if(muon.track().isNonnull()){
      mPFMuonTrkChi2Norm[muoni]    = muon.track()->normalizedChi2();
      mPFMuonTrkValidHits[muoni]   = muon.track()->found();
      mPFMuonTrkLostHits[muoni]    = muon.track()->lost();
      mPFMuonTrkPt[muoni]          = muon.track()->pt();
      mPFMuonTrkPz[muoni]          = muon.track()->pz();
      mPFMuonTrkP[muoni]           = muon.track()->p();
      mPFMuonTrkEta[muoni]         = muon.track()->eta();
      mPFMuonTrkPhi[muoni]         = muon.track()->phi();
      mPFMuonTrkChi2[muoni]        = muon.track()->chi2();
      mPFMuonTrkCharge[muoni]      = muon.track()->charge();
      mPFMuonTrkQOverPError[muoni] = muon.track()->qoverpError();
      mPFMuonTrkDxy[muoni]         = muon.track()->dxy( beamSpotHandle->position() );
      mPFMuonTrkNumOfValidPixHits[muoni] =  muon.track()->hitPattern().numberOfValidPixelHits();  
    }
    else{
      mPFMuonTrkChi2Norm[muoni]    = 999.; 
      mPFMuonTrkValidHits[muoni]   = 999.; 
      mPFMuonTrkLostHits[muoni]    = 999.; 
      mPFMuonTrkPt[muoni]          = 999.; 
      mPFMuonTrkPz[muoni]          = 999.; 
      mPFMuonTrkP[muoni]           = 999.; 
      mPFMuonTrkEta[muoni]         = 999.; 
      mPFMuonTrkPhi[muoni]         = 999.; 
      mPFMuonTrkChi2[muoni]        = 999.; 
      mPFMuonTrkCharge[muoni]      = 999.; 
      mPFMuonTrkQOverPError[muoni] = 999.; 
      mPFMuonTrkDxy[muoni]         = 999.;
      mPFMuonTrkNumOfValidPixHits[muoni] = 999.;
    }
    muoni++;
  }
  mNPFMuon=muoni;
 
  
  ///-------------------------------------------------------------------------- 
  /// B-Field
  ///--------------------------------------------------------------------------
  edm::Handle<DcsStatusCollection> dcsHandle;
  iEvent.getByLabel("scalersRawToDigi", dcsHandle);
  double bField = 3.8112;
  if( !isMCTag && dcsHandle->size() > 0){
    float currentToBFieldScaleFactor = 2.09237036221512717e-04;
    float  current = (*dcsHandle)[0].magnetCurrent();
    bField = current*currentToBFieldScaleFactor;
  }
  else {
    edm::ESHandle<MagneticField> magneticField;
    iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
    bField = magneticField->inTesla(GlobalPoint(0.,0.,0.)).z();
  }
  
  
  ///-------------------------------------------------------------------------- 
  /// ---
  ///--------------------------------------------------------------------------
  edm::Handle<reco::TrackCollection> trkHandle;
  iEvent.getByLabel("generalTracks",trkHandle);

  
  ///-------------------------------------------------------------------------- 
  /// Electrons
  ///--------------------------------------------------------------------------
  edm::Handle<edm::View<pat::Electron> > ElecHand;
  iEvent.getByLabel("cleanPatElectrons",ElecHand);
  int eleci=0;
  /*
  for(unsigned int ind=0; ind<(*ElecHand).size() && ind<MAXELEC; ind++){ 
  const pat::Electron& elec = (*ElecHand)[ind];
  Double_t sc_et = elec.superCluster()->energy()/TMath::CosH(elec.gsfTrack()->eta());
  
  mElecE[eleci]              = elec.superCluster()->energy();
  mElecPt[eleci]             = sc_et;
  mElecPx[eleci]             = elec.px();
  mElecPy[eleci]             = elec.py();
  mElecPz[eleci]             = elec.pz();
  
  int ecalseed = elec.ecalDrivenSeed();
  int eID95 = ((int)elec.electronID("simpleEleId95cIso") & 1);
  int eID80 = ((int)elec.electronID("simpleEleId80cIso") & 1);
  
  mElecEcalDrivenSeed[eleci] = ecalseed;
  mElecID80[eleci]           = eID80;
  mElecID95[eleci]           = eID95;
  
  mElecEta[eleci]            = elec.eta();
  mElecPhi[eleci]            = elec.phi();
  mElecCharge[eleci]         = elec.charge();
  mElecdr03HcalTowerSumEt[eleci]   = elec.dr03HcalTowerSumEt();//hcalIso();
  mElecdr03EcalRecHitSumEt[eleci]  = elec.dr03EcalRecHitSumEt();//ecalIso();
  mElecdr03TkSumPt[eleci]    = elec.dr03TkSumPt(); //trackIso();
  mElecNumOfValidHits[eleci] = elec.gsfTrack()->numberOfValidHits();
  mElecInnerNumOfHits[eleci] = elec.gsfTrack()->trackerExpectedHitsInner().numberOfHits();
  
  ConversionFinder convFinder;
  ConversionInfo convInfo = convFinder.getConversionInfo(elec, trkHandle, bField);
  
  mElecdist[eleci]           = convInfo.dist();
  mElecdcot[eleci]           = convInfo.dcot();
  mElecNormChi2[eleci]       = elec.gsfTrack()->normalizedChi2();
  mElecdxy[eleci]            = elec.gsfTrack()->dxy(primaryvtx.position());
  mElecdz[eleci]             = elec.gsfTrack()->dz(primaryvtx.position());
  mElecdB[eleci]             = elec.dB();
  mElecIsEB[eleci]           = elec.isEB();
  mElecfbrem[eleci]          = elec.fbrem();
  mElecDEtaSuTrAtVtx[eleci]  = elec.deltaEtaSuperClusterTrackAtVtx();
  mElecDPhiSuTrAtVtx[eleci]  = elec.deltaPhiSuperClusterTrackAtVtx();
  mElecHadronicOverEm[eleci] = elec.hadronicOverEm();
  mElecHcalOverEcal[eleci]   = elec.hcalOverEcal();
  mElecSuperClusOverP[eleci] = elec.eSuperClusterOverP();
  mElecetaeta[eleci]         = elec.sigmaEtaEta();
  mElecietaieta[eleci]       = elec.sigmaIetaIeta();
  
  eleci++;
  }
  */
  mNElec=eleci;
  

  ///-------------------------------------------------------------------------- 
  /// PFElectrons
  ///--------------------------------------------------------------------------
  //iEvent.getByLabel("selectedPatElectronsPF",ElecHand);
  iEvent.getByLabel(PFElectronTag_,ElecHand);
  eleci=0;
  for(unsigned int ind=0; ind<(*ElecHand).size() && ind<MAXELEC; ind++){ 
    const pat::Electron& elec = (*ElecHand)[ind];

    //std::cout<<"PFElectron: eta = "<<elec.eta()<<" | isEB = "<<elec.isEB()<<" | isEE = "<<elec.isEE()<<" | isEBEEGap = "<<elec.isEBEEGap()<<std::endl;
    
    mPFElecE[eleci]                    = elec.energy();
    mPFElecPt[eleci]                   = elec.pt();
    mPFElecPx[eleci]                   = elec.px();
    mPFElecPy[eleci]                   = elec.py();
    mPFElecPz[eleci]                   = elec.pz();
    mPFElecEta[eleci]                  = elec.eta();
    mPFElecPhi[eleci]                  = elec.phi();
    mPFElecCharge[eleci]               = elec.charge();
    
    mPFElecCharHadIso[eleci]           = elec.chargedHadronIso();
    mPFElecPhoIso[eleci]               = elec.photonIso();
    mPFElecNeuHadIso[eleci]            = elec.neutralHadronIso();
    mPFElecMva[eleci]                  = elec.mva();
    
    mPFElecEffArea[eleci]              = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, 
											 elec.superCluster()->eta(),
											 ElectronEffectiveArea::kEleEAData2012);
    
    mPFElecdxy[eleci]                  = elec.gsfTrack()->dxy(primaryvtx.position());
    mPFElecdz[eleci]                   = elec.gsfTrack()->dz(primaryvtx.position());
    
    mPFElecIsEB[eleci]                 = elec.isEB();
    mPFElecHadOverEm[eleci]            = elec.hadronicOverEm();
    mPFElecHcalOverEm[eleci]           = elec.hcalOverEcal();
    mPFElecSupClusOverP[eleci]         = elec.eSuperClusterOverP();
    
    mPFElecInnerHits[eleci]            = elec.gsfTrack()->trackerExpectedHitsInner().numberOfHits();
    mPFElecConvDist[eleci]             = elec.convDist();//convInfo.dist();
    mPFElecConvDcot[eleci]             = elec.convDcot();//convInfo.dcot();
    
    mPFElecEcalDrivenSeed[eleci]       = elec.ecalDrivenSeed();
    mPFElecdB[eleci]                   = elec.dB();
    mPFElecNumOfValidHits[eleci]       = elec.gsfTrack()->numberOfValidHits();
    mPFElecdr03HcalTowerSumEt[eleci]   = elec.dr03HcalTowerSumEt();//hcalIso();
    mPFElecdr03EcalRecHitSumEt[eleci]  = elec.dr03EcalRecHitSumEt();//ecalIso();
    mPFElecdr03TkSumPt[eleci]          = elec.dr03TkSumPt(); //trackIso();
    mPFElecNormChi2[eleci]             = elec.gsfTrack()->normalizedChi2();
    mPFElecfbrem[eleci]                = elec.fbrem();
    mPFElecDEtaSuTrAtVtx[eleci]        = elec.deltaEtaSuperClusterTrackAtVtx();
    mPFElecDPhiSuTrAtVtx[eleci]        = elec.deltaPhiSuperClusterTrackAtVtx();
    mPFElecHadronicOverEm[eleci]       = elec.hadronicOverEm();
    mPFElecHcalOverEcal[eleci]         = elec.hcalOverEcal();
    mPFElecSuperClusOverP[eleci]       = elec.eSuperClusterOverP();
    mPFElecetaeta[eleci]               = elec.sigmaEtaEta();
    mPFElecietaieta[eleci]             = elec.sigmaIetaIeta();
    
    mPFeidLoose[eleci]                 = ((int)elec.electronID("eidLoose") & 1);
    mPFeidRobustHighEnergy[eleci]      = ((int)elec.electronID("eidRobustHighEnergy") & 1);
    mPFeidRobustLoose[eleci]           = ((int)elec.electronID("eidRobustLoose") & 1);
    mPFeidRobustTight[eleci]           = ((int)elec.electronID("eidRobustTight") & 1);
    mPFeidTight[eleci]                 = ((int)elec.electronID("eidTight") & 1);
    mPFevspi[eleci]                    = ((int)elec.electronID("pf_evspi") & 1);
    mPFevsmu[eleci]                    = ((int)elec.electronID("pf_evsmu") & 1);
    
    eleci++;
  }
  mNPFElec=eleci;
  
  
  ///-------------------------------------------------------------------------- 
  /// Taus
  ///--------------------------------------------------------------------------  
  edm::Handle<edm::View<pat::Tau> > TauHand;
  iEvent.getByLabel(TauTag_,TauHand); 
      
  int taui=0;
  /*
  for(unsigned int ind=0; ind<(*TauHand).size() && ind<MAXTAU; ind++){ 
  const pat::Tau& tau = (*TauHand)[ind];
  
  mTauPt[taui]                                             = tau.pt();
  mTauPx[taui]                                             = tau.momentum().X();
  mTauPy[taui]                                             = tau.momentum().Y();
  mTauPz[taui]                                             = tau.momentum().Z();
  mTauE[taui]                                              = tau.energy();
  mTauEta[taui]                                            = tau.eta();
  mTauPhi[taui]                                            = tau.phi();
  mTauCharge[taui]                                         = tau.charge();
  
  //
  mTauEtaEtaMoment[taui]                                   = tau.etaetaMoment();
  mTauPhiPhiMoment[taui]                                   = tau.phiphiMoment();
  mTauEtaPhiMoment[taui]                                   = tau.etaphiMoment();
  
  //PF objects
  mTauLeadPFChargedHadrCandsignedSipt[taui]                = tau.leadPFChargedHadrCandsignedSipt();  
  mTauIsoPFChargedHadrCandsPtSum[taui]                     = tau.isolationPFChargedHadrCandsPtSum();
  mTauIsoPFGammaCandsEtSum[taui]                           = tau.isolationPFGammaCandsEtSum();      
  mTauMaximumHCALPFClusterEt[taui]                         = tau.maximumHCALPFClusterEt();          
  mTauEmFraction[taui]                                     = tau.emFraction();                      
  mTauHcalTotOverPLead[taui]                               = tau.hcalTotOverPLead();                
  mTauHcalMaxOverPLead[taui]                               = tau.hcalMaxOverPLead();                
  mTauHcal3x3OverPLead[taui]                               = tau.hcal3x3OverPLead();                
  mTauEcalStripSumEOverPLead[taui]                         = tau.ecalStripSumEOverPLead();          
  mTauBremsRecoveryEOverPLead[taui]                        = tau.bremsRecoveryEOverPLead();                 
  mTauElectronPreIDOutput[taui]                            = tau.electronPreIDOutput();             
  mTauElectronPreIDDecision[taui]                          = tau.electronPreIDDecision();            
  mTauCaloComp[taui]                                       = tau.caloComp();                        
  mTauSegComp[taui]                                        = tau.segComp();                         
  mTauMuonDecision[taui]                                   = tau.muonDecision(); 
  
  //
  mTausignalPFChargedHadrCands[taui]                       = tau.signalPFChargedHadrCands().size();
  mTausignalPFGammaCands[taui]                             = tau.signalPFGammaCands().size();
  
  //ID
  mTauDisAgainstElectronDeadECAL[taui]                     = tau.tauID("againstElectronDeadECAL");
  mTauDisAgainstElectronLooseMVA2[taui]                    = tau.tauID("againstElectronLooseMVA2");
  mTauDisAgainstElectronLooseMVA3[taui]                    = tau.tauID("againstElectronLooseMVA3");
  mTauDisAgainstElectronLoose[taui]                        = tau.tauID("againstElectronLoose");
  mTauDisAgainstElectronMVA2category[taui]                 = tau.tauID("againstElectronMVA2category");
  mTauDisAgainstElectronMVA2raw[taui]                      = tau.tauID("againstElectronMVA2raw");
  mTauDisAgainstElectronMVA3category[taui]                 = tau.tauID("againstElectronMVA3category");
  mTauDisAgainstElectronMVA3raw[taui]                      = tau.tauID("againstElectronMVA3raw");
  mTauDisAgainstElectronMVA[taui]                          = tau.tauID("againstElectronMVA");
  mTauDisAgainstElectronMediumMVA2[taui]                   = tau.tauID("againstElectronMediumMVA2");
  mTauDisAgainstElectronMediumMVA3[taui]                   = tau.tauID("againstElectronMediumMVA3");
  mTauDisAgainstElectronMedium[taui]                       = tau.tauID("againstElectronMedium");
  mTauDisAgainstElectronTightMVA2[taui]                    = tau.tauID("againstElectronTightMVA2");
  mTauDisAgainstElectronTightMVA3[taui]                    = tau.tauID("againstElectronTightMVA3");
  mTauDisAgainstElectronTight[taui]                        = tau.tauID("againstElectronTight");
  mTauDisAgainstElectronVLooseMVA2[taui]                   = tau.tauID("againstElectronVLooseMVA2");
  mTauDisAgainstElectronVTightMVA3[taui]                   = tau.tauID("againstElectronVTightMVA3");
  mTauDisAgainstMuonLoose2[taui]                           = tau.tauID("againstMuonLoose2");
  mTauDisAgainstMuonLoose[taui]                            = tau.tauID("againstMuonLoose");
  mTauDisAgainstMuonMedium2[taui]                          = tau.tauID("againstMuonMedium2");
  mTauDisAgainstMuonMedium[taui]                           = tau.tauID("againstMuonMedium");
  mTauDisAgainstMuonTight2[taui]                           = tau.tauID("againstMuonTight2");
  mTauDisAgainstMuonTight[taui]                            = tau.tauID("againstMuonTight");
  mTauDisByCombinedIsolationDeltaBetaCorrRaw3Hits[taui]    = tau.tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits");
  mTauDisByCombinedIsolationDeltaBetaCorrRaw[taui]         = tau.tauID("byCombinedIsolationDeltaBetaCorrRaw");
  mTauDisByIsolationMVA2raw[taui]                          = tau.tauID("byIsolationMVA2raw");
  mTauDisByIsolationMVAraw[taui]                           = tau.tauID("byIsolationMVAraw");
  mTauDisByLooseCombinedIsolationDeltaBetaCorr3Hits[taui]  = tau.tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits");
  mTauDisByLooseCombinedIsolationDeltaBetaCorr[taui]       = tau.tauID("byLooseCombinedIsolationDeltaBetaCorr");
  mTauDisByLooseIsolationMVA2[taui]                        = tau.tauID("byLooseIsolationMVA2");
  mTauDisByLooseIsolationMVA[taui]                         = tau.tauID("byLooseIsolationMVA");
  mTauDisByMediumCombinedIsolationDeltaBetaCorr3Hits[taui] = tau.tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits");
  mTauDisByMediumCombinedIsolationDeltaBetaCorr[taui]      = tau.tauID("byMediumCombinedIsolationDeltaBetaCorr");
  mTauDisByMediumIsolationMVA2[taui]                       = tau.tauID("byMediumIsolationMVA2");
  mTauDisByMediumIsolationMVA[taui]                        = tau.tauID("byMediumIsolationMVA");
  mTauDisByTightCombinedIsolationDeltaBetaCorr3Hits[taui]  = tau.tauID("byTightCombinedIsolationDeltaBetaCorr3Hits");
  mTauDisByTightCombinedIsolationDeltaBetaCorr[taui]       = tau.tauID("byTightCombinedIsolationDeltaBetaCorr");
  mTauDisByTightIsolationMVA2[taui]                        = tau.tauID("byTightIsolationMVA2");
  mTauDisByTightIsolationMVA[taui]                         = tau.tauID("byTightIsolationMVA");
  mTauDisByVLooseCombinedIsolationDeltaBetaCorr[taui]      = tau.tauID("byVLooseCombinedIsolationDeltaBetaCorr");
  mTauDisDecayModeFinding[taui]                            = tau.tauID("decayModeFinding");
  
  //GenJet Pt
  mTauJetPt[taui]  =  -99.;
  mTauJetEta[taui] =  -99.;
  mTauJetPhi[taui] =  -99.;
  if(isMCTag && tau.genJet()!= 0){
  mTauJetPt[taui]  =  tau.genJet()->pt();
  mTauJetEta[taui] =  tau.genJet()->eta();
  mTauJetPhi[taui] =  tau.genJet()->phi();
  }
  
  taui++;
  }
  */
  mNTau = taui;

  
  ///-------------------------------------------------------------------------- 
  /// PFTaus
  ///--------------------------------------------------------------------------
  iEvent.getByLabel(PFTauTag_,TauHand);
  taui=0;
  for(unsigned int ind=0; ind<(*TauHand).size() && ind<MAXTAU; ind++){ 
    const pat::Tau& tau = (*TauHand)[ind];
    
    mPFTauPt[taui]                                             = tau.pt();
    mPFTauPx[taui]                                             = tau.momentum().X();
    mPFTauPy[taui]                                             = tau.momentum().Y();
    mPFTauPz[taui]                                             = tau.momentum().Z();
    mPFTauE[taui]                                              = tau.energy();
    mPFTauEta[taui]                                            = tau.eta();
    mPFTauPhi[taui]                                            = tau.phi();
    mPFTauCharge[taui]                                         = tau.charge();
    
    //
    mPFTauEtaEtaMoment[taui]                                   = tau.etaetaMoment();
    mPFTauPhiPhiMoment[taui]                                   = tau.phiphiMoment();
    mPFTauEtaPhiMoment[taui]                                   = tau.etaphiMoment();
    
    //PF objects
    mPFTauLeadPFChargedHadrCandsignedSipt[taui]                = tau.leadPFChargedHadrCandsignedSipt();  
    mPFTauIsoPFChargedHadrCandsPtSum[taui]                     = tau.isolationPFChargedHadrCandsPtSum();
    mPFTauIsoPFGammaCandsEtSum[taui]                           = tau.isolationPFGammaCandsEtSum();      
    mPFTauMaximumHCALPFClusterEt[taui]                         = tau.maximumHCALPFClusterEt();          
    mPFTauEmFraction[taui]                                     = tau.emFraction();                      
    mPFTauHcalTotOverPLead[taui]                               = tau.hcalTotOverPLead();                
    mPFTauHcalMaxOverPLead[taui]                               = tau.hcalMaxOverPLead();                
    mPFTauHcal3x3OverPLead[taui]                               = tau.hcal3x3OverPLead();                
    mPFTauEcalStripSumEOverPLead[taui]                         = tau.ecalStripSumEOverPLead();          
    mPFTauBremsRecoveryEOverPLead[taui]                        = tau.bremsRecoveryEOverPLead();                 
    mPFTauElectronPreIDOutput[taui]                            = tau.electronPreIDOutput();             
    mPFTauElectronPreIDDecision[taui]                          = tau.electronPreIDDecision();            
    mPFTauCaloComp[taui]                                       = tau.caloComp();                        
    mPFTauSegComp[taui]                                        = tau.segComp();                         
    mPFTauMuonDecision[taui]                                   = tau.muonDecision(); 
    
    //
    mPFTausignalPFChargedHadrCands[taui]                       = tau.signalPFChargedHadrCands().size();
    mPFTausignalPFGammaCands[taui]                             = tau.signalPFGammaCands().size();
    
    //ID
    mPFTauDisAgainstElectronDeadECAL[taui]                     = tau.tauID("againstElectronDeadECAL");
    mPFTauDisAgainstElectronLooseMVA2[taui]                    = tau.tauID("againstElectronLooseMVA2");
    mPFTauDisAgainstElectronLooseMVA3[taui]                    = tau.tauID("againstElectronLooseMVA3");
    mPFTauDisAgainstElectronLoose[taui]                        = tau.tauID("againstElectronLoose");
    mPFTauDisAgainstElectronMVA2category[taui]                 = tau.tauID("againstElectronMVA2category");
    mPFTauDisAgainstElectronMVA2raw[taui]                      = tau.tauID("againstElectronMVA2raw");
    mPFTauDisAgainstElectronMVA3category[taui]                 = tau.tauID("againstElectronMVA3category");
    mPFTauDisAgainstElectronMVA3raw[taui]                      = tau.tauID("againstElectronMVA3raw");
    mPFTauDisAgainstElectronMVA[taui]                          = tau.tauID("againstElectronMVA");
    mPFTauDisAgainstElectronMediumMVA2[taui]                   = tau.tauID("againstElectronMediumMVA2");
    mPFTauDisAgainstElectronMediumMVA3[taui]                   = tau.tauID("againstElectronMediumMVA3");
    mPFTauDisAgainstElectronMedium[taui]                       = tau.tauID("againstElectronMedium");
    mPFTauDisAgainstElectronTightMVA2[taui]                    = tau.tauID("againstElectronTightMVA2");
    mPFTauDisAgainstElectronTightMVA3[taui]                    = tau.tauID("againstElectronTightMVA3");
    mPFTauDisAgainstElectronTight[taui]                        = tau.tauID("againstElectronTight");
    mPFTauDisAgainstElectronVLooseMVA2[taui]                   = tau.tauID("againstElectronVLooseMVA2");
    mPFTauDisAgainstElectronVTightMVA3[taui]                   = tau.tauID("againstElectronVTightMVA3");
    mPFTauDisAgainstMuonLoose2[taui]                           = tau.tauID("againstMuonLoose2");
    mPFTauDisAgainstMuonLoose[taui]                            = tau.tauID("againstMuonLoose");
    mPFTauDisAgainstMuonMedium2[taui]                          = tau.tauID("againstMuonMedium2");
    mPFTauDisAgainstMuonMedium[taui]                           = tau.tauID("againstMuonMedium");
    mPFTauDisAgainstMuonTight2[taui]                           = tau.tauID("againstMuonTight2");
    mPFTauDisAgainstMuonTight[taui]                            = tau.tauID("againstMuonTight");
    mPFTauDisByCombinedIsolationDeltaBetaCorrRaw3Hits[taui]    = tau.tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits");
    mPFTauDisByCombinedIsolationDeltaBetaCorrRaw[taui]         = tau.tauID("byCombinedIsolationDeltaBetaCorrRaw");
    mPFTauDisByIsolationMVA2raw[taui]                          = tau.tauID("byIsolationMVA2raw");
    mPFTauDisByIsolationMVAraw[taui]                           = tau.tauID("byIsolationMVAraw");
    mPFTauDisByLooseCombinedIsolationDeltaBetaCorr3Hits[taui]  = tau.tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits");
    mPFTauDisByLooseCombinedIsolationDeltaBetaCorr[taui]       = tau.tauID("byLooseCombinedIsolationDeltaBetaCorr");
    mPFTauDisByLooseIsolationDeltaBetaCorr[taui]               = tau.tauID("byLooseIsolationDeltaBetaCorr");
    mPFTauDisByLooseIsolationMVA2[taui]                        = tau.tauID("byLooseIsolationMVA2");
    mPFTauDisByLooseIsolationMVA[taui]                         = tau.tauID("byLooseIsolationMVA");
    mPFTauDisByLooseIsolation[taui]                            = tau.tauID("byLooseIsolation");
    mPFTauDisByMediumCombinedIsolationDeltaBetaCorr3Hits[taui] = tau.tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits");
    mPFTauDisByMediumCombinedIsolationDeltaBetaCorr[taui]      = tau.tauID("byMediumCombinedIsolationDeltaBetaCorr");
    mPFTauDisByMediumIsolationDeltaBetaCorr[taui]              = tau.tauID("byMediumIsolationDeltaBetaCorr");
    mPFTauDisByMediumIsolationMVA2[taui]                       = tau.tauID("byMediumIsolationMVA2");
    mPFTauDisByMediumIsolationMVA[taui]                        = tau.tauID("byMediumIsolationMVA");
    mPFTauDisByMediumIsolation[taui]                           = tau.tauID("byMediumIsolation");
    mPFTauDisByTightCombinedIsolationDeltaBetaCorr3Hits[taui]  = tau.tauID("byTightCombinedIsolationDeltaBetaCorr3Hits");
    mPFTauDisByTightCombinedIsolationDeltaBetaCorr[taui]       = tau.tauID("byTightCombinedIsolationDeltaBetaCorr");
    mPFTauDisByTightIsolationDeltaBetaCorr[taui]               = tau.tauID("byTightIsolationDeltaBetaCorr");
    mPFTauDisByTightIsolationMVA2[taui]                        = tau.tauID("byTightIsolationMVA2");
    mPFTauDisByTightIsolationMVA[taui]                         = tau.tauID("byTightIsolationMVA");
    mPFTauDisByTightIsolation[taui]                            = tau.tauID("byTightIsolation");
    mPFTauDisByVLooseCombinedIsolationDeltaBetaCorr[taui]      = tau.tauID("byVLooseCombinedIsolationDeltaBetaCorr");
    mPFTauDisByVLooseIsolationDeltaBetaCorr[taui]              = tau.tauID("byVLooseIsolationDeltaBetaCorr");
    mPFTauDisByVLooseIsolation[taui]                           = tau.tauID("byVLooseIsolation");
    mPFTauDisDecayModeFinding[taui]                            = tau.tauID("decayModeFinding");

    //GenJet Pt
    mPFTauJetPt[taui]  =  -99.;
    mPFTauJetEta[taui] =  -99.;
    mPFTauJetPhi[taui] =  -99.;
    if(isMCTag && tau.genJet()!= 0){
      mPFTauJetPt[taui]  =  tau.genJet()->pt();
      mPFTauJetEta[taui] =  tau.genJet()->eta();
      mPFTauJetPhi[taui] =  tau.genJet()->phi();
    }
    
    taui++;  
  }
  mNPFTau = taui;
  
  
  ///-------------------------------------------------------------------------- 
  /// Photons
  ///--------------------------------------------------------------------------
  edm::Handle<edm::View<pat::Photon> > PhotHand;
  iEvent.getByLabel("cleanPatPhotons",PhotHand);
  
  int photi=0;
  for(unsigned int ind=0; ind<(*PhotHand).size() && ind<MAXPHOT; ind++){ 
    const pat::Photon& phot = (*PhotHand)[ind];
    
    mPhotPt[photi]  = phot.pt() ;
    mPhotPx[photi]  = phot.momentum().X() ;
    mPhotPy[photi]  = phot.momentum().Y() ;
    mPhotPz[photi]  = phot.momentum().Z() ;
    mPhotE[photi]   = phot.energy() ;
    mPhotEta[photi] = phot.eta() ;
    mPhotPhi[photi] = phot.phi() ;
    mPhotE1x5[eleci]= phot.e1x5(); 
    mPhotE2x5[photi]= phot.e2x5(); 
    mPhotE5x5[photi]= phot.e5x5(); 
    mPhotSigEta[photi] = phot.sigmaEtaEta();
    //mPhotSigPhi[photi] = phot.sigmaPhiPhi();
    mPhotEcalIso04[photi] = phot.ecalIso(); 
    mPhotHcalIso04[photi] = phot.hcalIso();
    mPhotTrackIso04[photi] = phot.trackIso();
    
    mPhotHasPixSeed[photi] = phot.hasPixelSeed();
    mPhotIsPhot[photi]     = phot.isPhoton();   
    
    photi++;
  }
  mNPhot = photi;
  
  
  ///-------------------------------------------------------------------------- 
  /// MC Products
  ///--------------------------------------------------------------------------
  if(isMCTag){
    /// Gen Particles
    Handle<reco::GenParticleCollection>  GenParHand;
    iEvent.getByLabel("genParticles", GenParHand);
    
    //modified by Shuichi & Latife	
    
    int igcount=0;
    
    for( size_t i = 0; i < GenParHand->size(); ++ i ){
      const GenParticle &p  = (*GenParHand)[i];
      int id = p.pdgId();
      
      //printf("%2d   %10d    %6.1f   %6.1f   %6.1f  %6.1f   %6.1f  %3d  %6.2f  %6.2f \n", 
      //  p.status() ,  p.pdgId(), p.pt() , p.px(), p.py(), p.pz(), p.mass(),p.charge(),  p.eta(), p.phi());
      
      //cout  << id  << endl; 
      if( p.status() ==3 || abs( p.status() ) ==23 || abs(id) == 23 || abs(id) == 24 || abs(id) == 39 || abs(id)==5 || abs(id)==6
	  || abs(id) == 11 || abs(id) == 12 || abs(id)==13 || abs(id) == 14 || abs(id) == 15 || abs(id)==16 || abs(id)==5000039 || 
	  abs(id) == 17 || abs(id) == 18 )  
	
	//if(  abs( p.status() ) ==23 && abs(id)==5000039 )  
	{ 
	  //mGenParIndex[igcount]  = i;
	  mGenParId[igcount]     = p.pdgId();
	  mGenParStatus[igcount] = p.status();
	  mGenParCharge[igcount] = p.charge();
	  mGenParE[igcount]      = p.energy();
	  mGenParPt[igcount]     = p.pt();
	  mGenParPx[igcount]     = p.px();
	  mGenParPy[igcount]     = p.py();
	  mGenParPz[igcount]     = p.pz();
	  mGenParEta[igcount]    = p.eta();
	  mGenParPhi[igcount]    = p.phi();
	  mGenParMass[igcount]   = p.mass();

	  //cout<<i<<" "<<p.pdgId()<<endl;
	  
	  //  get pid of parent particle...
	  mGenParDoughterOf[igcount]      = 0;
	  //mGenParDoughterOfIndex[igcount] = 0;
	  
	  int n = p.numberOfMothers();
	  if(n>0){
	    const reco::Candidate *pa = p.mother();
	    int parentID = pa->pdgId();
	    mGenParDoughterOf[igcount]=parentID;
	    //cout<<"   - Mother "<<parentID<<endl;
	  }
	  
	  //const GenParticleRefVector& motherRefs = p.motherRefVector();
	  //for(reco::GenParticleRefVector::const_iterator imr = motherRefs.begin(); imr!= motherRefs.end(); ++imr) {
	  //cout<<"   - Mother-2 "<<(*imr).key()<<" "<<(*imr)->pdgId()<<endl;
	  //}
	  //cout<<"+++"<<endl;
	  
	  /*if( p.numberOfMothers() >1 ){
	    mGenParMother1[igcount] =  p.mother(0)->pdgId() ; 
	    mGenParMother2[igcount] =  p.mother(1)->pdgId() ; 
	    }
	  */ 
	  
	  igcount++;
	}
    }
    mNGenPar=igcount;

    //for(int i=0; i<mNGenPar; i++)
    //cout<<mGenParId[i]<<" | "<<mGenParDoughterOf[i]<<endl;
    //cout<<"--------------------------"<<endl;
    
    ///---
    //Handle< double > genEventScale;
    //iEvent.getByLabel( "genEventScale", genEventScale );
    //mGenScale = *genEventScale;

    
    ///---Checking
    /*
    for(size_t i = 0; i < GenParHand->size(); ++ i) {
      if(i>50) break;
      const GenParticle & ParticleCand = (*GenParHand)[i];
      cout<<i<<") Particle = "<<ParticleCand.pdgId()<<", Status = "<<ParticleCand.status()<<endl;
      // Daughter
      const GenParticleRefVector& daughterRefs = ParticleCand.daughterRefVector();
      for(reco::GenParticleRefVector::const_iterator idr = daughterRefs.begin(); idr!= daughterRefs.end(); ++idr) {
	cout<<"    - Daughter "<<(*idr).key()<<" "<<(*idr)->pdgId()<<endl;
      }
      // Mother
      const GenParticleRefVector& motherRefs = ParticleCand.motherRefVector();
      for(reco::GenParticleRefVector::const_iterator imr = motherRefs.begin(); imr!= motherRefs.end(); ++imr) {
	cout<<"   - Mother "<<(*imr).key()<<" "<<(*imr)->pdgId()<<endl;
      }
    }
    */
    
    ///--- W-Tau+Nu information
    bool foundW_d1 = false;
    bool foundW_d2 = false; 
    mWTauDecayMode = 0;
    int wtauDecayCount=0;
    for( size_t i = 0; i < GenParHand->size(); ++ i ){
      if(foundW_d1==true && foundW_d2==true) break;
      const GenParticle &p  = (*GenParHand)[i];
      if(abs(p.pdgId())==24 && p.status()==3){
	for(int j=0;p.daughter(j)!=NULL;j++) {//loop on W daughter
	  const reco::Candidate* p1 = p.daughter(j); 

	  if(abs(p1->pdgId())==12 ||abs(p1->pdgId())==14 ||abs(p1->pdgId())==16){
	    foundW_d2 = true; 
	    //cout<<"Neutrino (from W)"<<endl; 
	    mWTauDecayId[wtauDecayCount]     = p1->pdgId(); 
	    mWTauDecayStatus[wtauDecayCount] = p1->status(); 
	    mWTauDecayPt[wtauDecayCount]     = p1->pt(); 
	    mWTauDecayEta[wtauDecayCount]    = p1->eta();
	    mWTauDecayPhi[wtauDecayCount]    = p1->phi();
	    mWTauDecayMass[wtauDecayCount]   = p1->mass();
	    wtauDecayCount++;
	  }
	  else if(abs(p1->pdgId())==11){
	    foundW_d1 = true;
	    //cout<<"Electron (from W)"<<endl; 
	    mWTauDecayMode = 1;
	    mWTauDecayId[wtauDecayCount]     = p1->pdgId(); 
	    mWTauDecayStatus[wtauDecayCount] = p1->status(); 
	    mWTauDecayPt[wtauDecayCount]     = p1->pt(); 
	    mWTauDecayEta[wtauDecayCount]    = p1->eta();
	    mWTauDecayPhi[wtauDecayCount]    = p1->phi();
	    mWTauDecayMass[wtauDecayCount]   = p1->mass();
	    wtauDecayCount++;
	  }
	  else if(abs(p1->pdgId())==13){
	    foundW_d1 = true;
	    //cout<<"Muon (from W)"<<endl; 
	    mWTauDecayMode = 2;
	    mWTauDecayId[wtauDecayCount]     = p1->pdgId(); 
	    mWTauDecayStatus[wtauDecayCount] = p1->status();  
	    mWTauDecayPt[wtauDecayCount]     = p1->pt(); 
	    mWTauDecayEta[wtauDecayCount]    = p1->eta();
	    mWTauDecayPhi[wtauDecayCount]    = p1->phi();
	    mWTauDecayMass[wtauDecayCount]   = p1->mass();
	    wtauDecayCount++; 
	  }
	  else if(abs(p1->pdgId())==15){ 
	    foundW_d1 = true;
	    //cout<<"Tau (from W)"<<endl;
	    
	    Int_t npi = 0;
	    
	    //if(p1->numberOfDaughters()==1 && abs(p1->daughter(0)->pdgId())==15){
	    const reco::Candidate* p2 = p1->daughter(0);
	    for(unsigned int k=0; k<p2->numberOfDaughters();++k){
	      const reco::Candidate* p3 = p2->daughter(k);
	      //cout<<"  -"<<p3->pdgId()<<endl;
	      
	      if(abs(p3->pdgId())==12 || abs(p3->pdgId())==14 || abs(p3->pdgId())==16){
		mWTauDecayId[wtauDecayCount]     = p3->pdgId();
		mWTauDecayStatus[wtauDecayCount] = p3->status();  
		mWTauDecayPt[wtauDecayCount]     = p3->pt(); 
		mWTauDecayEta[wtauDecayCount]    = p3->eta();
		mWTauDecayPhi[wtauDecayCount]    = p3->phi();
		mWTauDecayMass[wtauDecayCount]   = p3->mass();
		wtauDecayCount++;
	      }
	      
	      else if(std::abs(p3->pdgId())==11){
		mWTauDecayMode = 11;
		mWTauDecayId[wtauDecayCount]     = p3->pdgId(); 
		mWTauDecayStatus[wtauDecayCount] = p3->status(); 
		mWTauDecayPt[wtauDecayCount]     = p3->pt(); 
		mWTauDecayEta[wtauDecayCount]    = p3->eta();
		mWTauDecayPhi[wtauDecayCount]    = p3->phi();
		mWTauDecayMass[wtauDecayCount]   = p3->mass();
		wtauDecayCount++;
	      }
	      
	      else if(std::abs(p3->pdgId())==13){
		mWTauDecayMode = 12;
		mWTauDecayId[wtauDecayCount]     = p3->pdgId();
		mWTauDecayStatus[wtauDecayCount] = p3->status();  
		mWTauDecayPt[wtauDecayCount]     = p3->pt(); 
		mWTauDecayEta[wtauDecayCount]    = p3->eta();
		mWTauDecayPhi[wtauDecayCount]    = p3->phi();
		mWTauDecayMass[wtauDecayCount]   = p3->mass();
		wtauDecayCount++;
	      }
		
	      else if(std::abs(p3->pdgId())==321){
		mWTauDecayMode = 13;
		mWTauDecayId[wtauDecayCount]     = p3->pdgId(); 
		mWTauDecayStatus[wtauDecayCount] = p3->status(); 
		mWTauDecayPt[wtauDecayCount]     = p3->pt(); 
		mWTauDecayEta[wtauDecayCount]    = p3->eta();
		mWTauDecayPhi[wtauDecayCount]    = p3->phi();
		mWTauDecayMass[wtauDecayCount]   = p3->mass();
		wtauDecayCount++;
	      }
	      
	      else if(std::abs(p3->pdgId())==323 || std::abs(p3->pdgId())==213){
		if(std::abs(p3->pdgId())==323) mWTauDecayMode = 14;
		if(std::abs(p3->pdgId())==213) mWTauDecayMode = 15;
		for(unsigned int l=0; l<p3->numberOfDaughters();++l){
		  const reco::Candidate* p4 = p3->daughter(l);
		  //cout<<"PHATDEBUG: Mode-323/213: "<<p4->pdgId()<<" | "<<p4->status()<<endl;
		  if(p4->status()==1){
		    mWTauDecayId[wtauDecayCount]     = p4->pdgId(); 
		    mWTauDecayStatus[wtauDecayCount] = p4->status(); 
		    mWTauDecayPt[wtauDecayCount]     = p4->pt(); 
		    mWTauDecayEta[wtauDecayCount]    = p4->eta();
		    mWTauDecayPhi[wtauDecayCount]    = p4->phi();
		    mWTauDecayMass[wtauDecayCount]   = p4->mass();
		    wtauDecayCount++;
		  }
		  else{
		    for(unsigned int ll=0; ll<p4->numberOfDaughters();++ll){
		      const reco::Candidate* p5 = p4->daughter(ll);
		      //cout<<"                   - "<<p5->pdgId()<<" | "<<p5->status()<<endl;
		      mWTauDecayId[wtauDecayCount]     = p5->pdgId(); 
		      mWTauDecayStatus[wtauDecayCount] = p5->status();
		      mWTauDecayPt[wtauDecayCount]     = p5->pt(); 
		      mWTauDecayEta[wtauDecayCount]    = p5->eta();
		      mWTauDecayPhi[wtauDecayCount]    = p5->phi();
		      mWTauDecayMass[wtauDecayCount]   = p5->mass();
		      wtauDecayCount++;
		    }
		  }
		}
	      }
	      
	      else if(std::abs(p3->pdgId())==20213){
		Int_t pi = 0;
		for(unsigned int l=0; l<p3->numberOfDaughters();++l){
		  const reco::Candidate* p4 = p3->daughter(l);
		  //cout<<"PHATDEBUG: Mode-20213: "<<p4->pdgId()<<" | "<<p4->status()<<endl;
		  if (std::abs(p4->pdgId()) == 211) pi++;
		  //
		  if(p4->status()==1){
		    mWTauDecayId[wtauDecayCount]     = p4->pdgId(); 
		    mWTauDecayStatus[wtauDecayCount] = p4->status();
		    mWTauDecayPt[wtauDecayCount]     = p4->pt(); 
		    mWTauDecayEta[wtauDecayCount]    = p4->eta();
		    mWTauDecayPhi[wtauDecayCount]    = p4->phi();
		    mWTauDecayMass[wtauDecayCount]   = p4->mass();
		    wtauDecayCount++;
		  }
		  else{
		    for(unsigned int ll=0; ll<p4->numberOfDaughters();++ll){
		      const reco::Candidate* p5 = p4->daughter(ll);
		      //cout<<"                   - "<<p5->pdgId()<<" | "<<p5->status()<<endl;
		      mWTauDecayId[wtauDecayCount]     = p5->pdgId(); 
		      mWTauDecayStatus[wtauDecayCount] = p5->status();
		      mWTauDecayPt[wtauDecayCount]     = p5->pt(); 
		      mWTauDecayEta[wtauDecayCount]    = p5->eta();
		      mWTauDecayPhi[wtauDecayCount]    = p5->phi();
		      mWTauDecayMass[wtauDecayCount]   = p5->mass();
		      wtauDecayCount++;
		    }
		  }
		}
		if(pi==1) mWTauDecayMode = 16;
		else if(pi==3) mWTauDecayMode = 17;
		else if(pi>3)  mWTauDecayMode = 18;
		else mWTauDecayMode = -10;
	      }
	      
	      else if(std::abs(p3->pdgId())==24){
		for(unsigned int l=0; l<p3->numberOfDaughters();++l){
		  const reco::Candidate* p4 = p3->daughter(l);
		  if (std::abs(p4->pdgId()) == 211) npi++;
		  //cout<<"PHATDEBUG: Mode-24: "<<p4->pdgId()<<" | "<<p4->status()<<endl;
		  //
		  if(p4->status()==1){
		    mWTauDecayId[wtauDecayCount]     = p4->pdgId();
		    mWTauDecayStatus[wtauDecayCount] = p4->status(); 
		    mWTauDecayPt[wtauDecayCount]     = p4->pt(); 
		    mWTauDecayEta[wtauDecayCount]    = p4->eta();
		    mWTauDecayPhi[wtauDecayCount]    = p4->phi();
		    mWTauDecayMass[wtauDecayCount]   = p4->mass();
		    wtauDecayCount++;
		  }
		  else{
		    for(unsigned int ll=0; ll<p4->numberOfDaughters();++ll){
		      const reco::Candidate* p5 = p4->daughter(ll);
		      //cout<<"                   - "<<p5->pdgId()<<" | "<<p5->status()<<endl;
		      mWTauDecayId[wtauDecayCount]     = p5->pdgId(); 
		      mWTauDecayStatus[wtauDecayCount] = p5->status();
		      mWTauDecayPt[wtauDecayCount]     = p5->pt(); 
		      mWTauDecayEta[wtauDecayCount]    = p5->eta();
		      mWTauDecayPhi[wtauDecayCount]    = p5->phi();
		      mWTauDecayMass[wtauDecayCount]   = p5->mass();
		      wtauDecayCount++;
		    }
		  }
		}
	      }
	      
	      else if(std::abs(p3->pdgId())==211){ 
		npi++;
		mWTauDecayId[wtauDecayCount]     = p3->pdgId();
		mWTauDecayStatus[wtauDecayCount] = p3->status(); 
		mWTauDecayPt[wtauDecayCount]     = p3->pt(); 
		mWTauDecayEta[wtauDecayCount]    = p3->eta();
		mWTauDecayPhi[wtauDecayCount]    = p3->phi();
		mWTauDecayMass[wtauDecayCount]   = p3->mass();
		wtauDecayCount++;
	      }
	      
	      else continue; 
	    }
	    if(mWTauDecayMode==0){
	      if(npi==1)      mWTauDecayMode = 19;
	      else if(npi==3) mWTauDecayMode = 20;
	      else if(npi>3)  mWTauDecayMode = 21;
	      else mWTauDecayMode = -20;
	    }
	  }
	 
	  else {}
	}
	/*
	std::cout<<" - DecayMode = "<<mWTauDecayMode<<" ( Run = "<<mRun<<", Event = "<<mEvent<<", Lumi = "<<mLumi<<" )"<<std::endl;
	//if(mWTauDecayMode<0){
	for(int i=0; i<wtauDecayCount; i++){
	  if(i==0)
	    std::cout<<"CHECK: ";
	  std::cout<<mWTauDecayId[i]<<" ("<<mWTauDecayStatus[i]<<")";
	  if(i<wtauDecayCount-1)
	    std::cout<<" + ";
	}
	std::cout<<std::endl;
	//}
	*/
      }
    }
    mWTauN = wtauDecayCount;
    //cout<<"------------------"<<endl;
   
    
    ///--- Default PDF
    Handle<GenEventInfoProduct> pdfstuff;
    iEvent.getByLabel("generator",pdfstuff);
    
    mPdfx1    = pdfstuff->pdf()->x.first;
    mPdfx2    = pdfstuff->pdf()->x.second;
    mPdff1    = pdfstuff->pdf()->id.first; 
    mPdff2    = pdfstuff->pdf()->id.second;
    mPdfscale = pdfstuff->pdf()->scalePDF;
    mPdfpdf1  = pdfstuff->pdf()->xPDF.first;
    mPdfpdf2  = pdfstuff->pdf()->xPDF.second; 
  }

  
  ///-------------------------------------------------------------------------- 
  /// PDF
  ///--------------------------------------------------------------------------
  if(isMCTag && isSignalTag==1.){
    
    ///----------PDF Weight from file---------------------------------------
    edm::InputTag pdfWeightTag("pdfWeights1:cteq66"); // or any other PDF set
    edm::Handle<std::vector<double> > weightHandle;
    iEvent.getByLabel(pdfWeightTag, weightHandle);
    
    std::vector<double> weights = (*weightHandle);
    //std::cout << "Event weight for central PDF:" << weights[0] << std::endl;
    unsigned int nmembers = weights.size();
    
    for (unsigned int j=0; j<nmembers; j++){
      mPdfWeights1[j] = weights[j];
    }
    mNPdfWeights1 = nmembers;  
  }
  
  if(isMCTag && isSignalTag==2.){
  
    ///----------PDF Weight from file---------------------------------------
    edm::InputTag pdfWeightTag("pdfWeights2:MSTW2008nlo68cl"); // or any other PDF set
    edm::Handle<std::vector<double> > weightHandle;
    iEvent.getByLabel(pdfWeightTag, weightHandle);
    
    std::vector<double> weights = (*weightHandle);
    //std::cout << "Event weight for central PDF:" << weights[0] << std::endl;
    unsigned int nmembers = weights.size();
    
    for (unsigned int j=0; j<nmembers; j++){
      mPdfWeights[j] = weights[j];
    }
    mNPdfWeights = nmembers;  
  }
  
  if(isMCTag && isSignalTag==3.){
    ///----------PDF Weight from file---------------------------------------
    edm::InputTag pdfWeightTag("pdfWeights3:NNPDF20"); // or any other PDF set
    edm::Handle<std::vector<double> > weightHandle;
    iEvent.getByLabel(pdfWeightTag, weightHandle);
    
    std::vector<double> weights = (*weightHandle);
    //std::cout << "Event weight for central PDF:" << weights[0] << std::endl;
    unsigned int nmembers = weights.size();
    
    for (unsigned int j=0; j<nmembers; j++){
      mPdfWeights[j] = weights[j];
    }	
    mNPdfWeights = nmembers;  
  }

  
  ///-------------------------------------------------------------------------- 
  /// L1
  ///--------------------------------------------------------------------------
  if(!isMCTag){
    
    ///-------------------L1 Trigger----------------------------------------------
    Handle <L1GlobalTriggerReadoutRecord> gtRecord_h;
    iEvent.getByType (gtRecord_h); // assume only one L1 trigger record here
    const L1GlobalTriggerReadoutRecord* gtRecord = gtRecord_h.failedToGet () ? 0 : &*gtRecord_h;
    
    DecisionWord gtDecisionWord = gtRecord->decisionWord();
    
    for(int i=0; i<128; i++){
      L1Array[i] =  gtDecisionWord[i];
    }
    nL1 = 128;
    
    
    ///-------------------- L1 Technical Trigger----------------------------------
    Handle<L1GlobalTriggerReadoutRecord> gtRecord2;
    iEvent.getByLabel("gtDigis",gtRecord2);
    const TechnicalTriggerWord tWord = gtRecord2->technicalTriggerWord();
    
    for(int i=0; i<64; i++){
      L1TArray[i] = tWord.at(i);
    }
    nL1T = 64; 
  }
  
  
  ///-------------------------------------------------------------------------- 
  /// Tracking Failure
  ///--------------------------------------------------------------------------
  edm::Handle<std::vector<reco::Track> > tracks2;
  iEvent.getByLabel(Tracks_, tracks2);
  
  edm::Handle<std::vector<reco::Vertex> > vtxs;
  iEvent.getByLabel("offlinePrimaryVertices", vtxs);
  
  // ht coming from pat jets see above
  double sumpt = 0;
  if (vtxs->size() > 0){
    const reco::Vertex * vtx = &((*vtxs)[0]);
    for (std::vector<reco::Track>::const_iterator tr = tracks2->begin(); tr != tracks2->end(); ++tr) {
      if (fabs(tr->dz(vtx->position())) > 1.0) continue;
      if (fabs(tr->dxy(vtx->position())) > 0.2) continue;
      sumpt += tr->pt();
    }
  }
  mSumTrackPt = sumpt;
  
  
  ///-------------------------------------------------------------------------- 
  /// Beam Halo Flag
  ///--------------------------------------------------------------------------
  Handle<reco::BeamHaloSummary> beamHaloSummary;
  iEvent.getByLabel("BeamHaloSummary" , beamHaloSummary);
  if(beamHaloSummary.isValid()){
    mbeamHaloTight = beamHaloSummary->CSCTightHaloId();
    mbeamHaloLoose = beamHaloSummary->CSCLooseHaloId();
  }
  else{
    mbeamHaloTight = 0;
    mbeamHaloLoose = 0;
  } 
  
  
  ///-------------------------------------------------------------------------- 
  /// TIV
  ///--------------------------------------------------------------------------
  /*	
    Handle<CandidateView> PatTracksHand;  
    iEvent.getByLabel("selectedPatTracks" ,PatTracksHand);
    
    int pattracksi=0;
    for(unsigned int ind=0; ind<(*PatTracksHand).size() && ind<100; ind++){ 
    CandidateBaseRef trCandRef = PatTracksHand->refAt(ind); 
    const Candidate & trCand = (*PatTracksHand)[ind]; //the candidate
    const reco::Tracks & tracks = dynamic_cast<const reco::Tracks &>(trCand);
    edm::RefToBase<reco::Track> track(trackCollectionH, i);
    double  pt= tracks.pt();
    }
  */
  
  Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel(Tracks_,tracks);
  
  /*
  for(int i=0; i<TIVMAX;i++){
  TIV[i]=-99;
  TIV_pt[i]=-99;
  TIV_eta[i]=-99;
  TIV_phi[i]=-99;
  TIV_px[i]=-99;
  TIV_py[i]=-99;
  TIV_pz[i]=-99;
  TIV_dxy[i]=-99;
  TIV_dsz[i]=-99;
  TIV_dR[i] = -99;
  TIV_d0[i]=-99;
  TIV_dz[i]=-99;
  TIV_dxy_corr[i]=-99;
  TIV_dsz_corr[i]=-99;
  TIV_d0_corr[i]=-99;
  TIV_dz_corr[i]=-99;
  }
  */
  
  tivN=0;
  /*
    for(reco::TrackCollection::const_iterator itTrack = tracks->begin();itTrack != tracks->end();++itTrack){
    float trkPt = itTrack->pt();
    float ILV_isoPT = 0.;
    
    if(trkPt < tiv_ltrack_thr_) continue ;
    //if( fabs(itTrack->dz()) > tiv_dz_thr_) continue;
    //if( fabs(itTrack->dxy()) > tiv_dxy_thr_) continue;
    
    const math::XYZVector trackMomentum = itTrack->momentum() ;
    if(DEBUG==1)
      std::cout <<"---- TIV_N="<< tivN << " lTrkPt=" << trkPt  << " eta:"<<itTrack->eta()
		<<" phi:"<<itTrack->phi() << " dz:" << itTrack->dz() << " dxy:" << itTrack->dxy()
		<< std::endl;
    
    float tmpPt[TIVMAX],tmpPx[TIVMAX],tmpPy[TIVMAX],tmpPz[TIVMAX];
    float tmpEta[TIVMAX],tmpPhi[TIVMAX], tmpDxy[TIVMAX],tmpDsz[TIVMAX], tmpDr[TIVMAX], tmpDz[TIVMAX], tmpD0[TIVMAX];
    float tmpDxy_corr[TIVMAX],tmpDsz_corr[TIVMAX], tmpDz_corr[TIVMAX], tmpD0_corr[TIVMAX];
    for(int i=0; i<TIVMAX;i++){
	tmpPt[i]=0;tmpPx[i]=0;tmpPy[i]=0;tmpPz[i]=0;tmpEta[i]=0;tmpPhi[i]=0;tmpDxy[i]=0;tmpDsz[i]=0;tmpDr[i]=0;
	tmpD0[i]=0;tmpDz[i]=0;
	tmpD0_corr[i]=0;tmpDz_corr[i]=0; tmpDxy_corr[i]=0;tmpDsz_corr[i]=0;
      }
    int tmpN=0;
    
    for(reco::TrackCollection::const_iterator itTrack2 = tracks->begin();itTrack2 != tracks->end();++itTrack2){
      float trkPt2 = itTrack2->pt();
      if(trkPt2 < tiv_strack_thr_) continue;
      //if( fabs(itTrack2->dz()) > tiv_dz_thr_) continue;
      //if( fabs(itTrack2->dxy()) > tiv_dxy_thr_) continue;
      
      const math::XYZVector trackMomentum2 = itTrack2->momentum() ;
      
      float dR = ROOT::Math::VectorUtil::DeltaR(trackMomentum, trackMomentum2);
      if(dR < tiv_cone_ && dR>tiv_inner_cone_){
	
	if(DEBUG==1)	   
	  std::cout << "--- tmpN=" << tmpN << " sTrkPt=" << trkPt2 << std::endl; 
	
	
	tmpPt[tmpN] = trkPt2;
	tmpPx[tmpN] = itTrack2->px();
	tmpPy[tmpN] = itTrack2->py();
	tmpPz[tmpN] = itTrack2->pz();
	tmpPhi[tmpN] = itTrack2->phi();
	tmpEta[tmpN] = itTrack2->eta();
	tmpDxy[tmpN] = itTrack2->dxy();
	tmpDsz[tmpN] = itTrack2->dsz();
	tmpDz[tmpN] = itTrack2->dz();
	tmpD0[tmpN] = itTrack2->d0();
	tmpDxy_corr[tmpN] = itTrack2->dxy(point);
	tmpDsz_corr[tmpN] = itTrack2->dsz(point);
	tmpDz_corr[tmpN] = itTrack2->dz(point);
	tmpD0_corr[tmpN] = -1.*itTrack2->dxy(point);
	
	tmpDr[tmpN] = dR;
	tmpN++;
	ILV_isoPT+=trkPt2;
      }
    }
    
    if(DEBUG==1)
      std::cout << " -- tmpN=" << tmpN << " IsoTrk=" << ILV_isoPT/trkPt << std::endl;
    

    if( (ILV_isoPT/trkPt) < 10.){
      TIV[tivN] = ILV_isoPT/trkPt;
      TIV_lead[tivN] = 1;
      TIV_pt[tivN] = trkPt;
      TIV_px[tivN] = itTrack->px();
      TIV_py[tivN] = itTrack->py();
      TIV_pz[tivN] = itTrack->pz();
      TIV_phi[tivN] = itTrack->phi();
      TIV_eta[tivN] = itTrack->eta();
      TIV_dxy[tivN] = itTrack->dxy();
      TIV_dsz[tivN] = itTrack->dsz();
      TIV_d0[tivN] = itTrack->d0();
      TIV_dz[tivN] = itTrack->dz();
      TIV_dxy_corr[tivN] = itTrack->dxy(point);
      TIV_dsz_corr[tivN] = itTrack->dsz(point);
      TIV_d0_corr[tivN] = -1.*itTrack->dxy(point);
      TIV_dz_corr[tivN] = itTrack->dz(point);
      TIV_dR[tivN] = tiv_cone_;
      tivN++;
      
      if(DEBUG==1){
	std::cout << "+" << tivN-1 << " " << trkPt << std::endl;
      }
      
      for(int t=0;t<tmpN;t++){
	if(DEBUG==1)
	  std::cout << "     -" << tivN << " " <<  tmpPt[t] << std::endl;
	
	TIV_lead[tivN] = 0;
	TIV_pt[tivN] = tmpPt[t];
	TIV_px[tivN] = tmpPx[t];
	TIV_py[tivN] = tmpPy[t];
	TIV_pz[tivN] = tmpPz[t];
	TIV_phi[tivN] = tmpPhi[t];
	TIV_eta[tivN] = tmpEta[t];
	TIV_dxy[tivN] = tmpDxy[t];
	TIV_dsz[tivN] = tmpDsz[t];
	TIV_dz[tivN] = tmpDz[t];
	TIV_d0[tivN] = tmpD0[t];
	TIV_dxy_corr[tivN] = tmpDxy_corr[t];
	TIV_dsz_corr[tivN] = tmpDsz_corr[t];
	TIV_dz_corr[tivN] = tmpDz_corr[t];
	TIV_d0_corr[tivN] = tmpD0_corr[t];
	TIV_dR[tivN] = tmpDr[t];
	tivN++;
      }
    }
  }
  */
  
  /*
  ///-------------------------------------------------------------------------- 
  /// Lower TIV Calculation
  ///--------------------------------------------------------------------------
  float Lower_TIV = 100;
  float ILV_isoPT;
  
  float TIV_pt_l_thr = 10;
  float TIV_pt_s_thr = 1;
  //float TIV_dxy_thr = 100;
  //float TIV_dz_thr = 100;
  float TIV_dR_inner_thr = 0.02;
  float TIV_dR_outer_thr = 0.3;
  
  for(int tl=0; tl<tivN; tl++){
  ILV_isoPT = 100.;
  
  bool isMuon=false;
  for(int mu=0; mu<mNMuon; mu++){
  //if( mMuonPt[mu] > 20 && fabs(varFloatArr["Muon_isGood_AllGlobalMuons"][mu]-1 ) < 0.1 )
  if( mMuonPt[mu] > 20 ){
  if( mMuonSumPtDR03[mu] >= 0 && mMuonSumPtDR03[mu] < 100){
  float dPhi = deltaPhi( mMuonPhi[mu], TIV_phi[tl] );
  float dEta = mMuonEta[mu] - TIV_eta[tl];
  if( sqrt(dPhi*dPhi + dEta*dEta) < 10) {isMuon=true; break;}
  }
  }
  }
  if(isMuon) continue;
  
  if( TIV_lead[tl]==1 && TIV_pt[tl] > TIV_pt_l_thr  ){ 
  ILV_isoPT = 0.;
  for(int ts = tl+1; ts< tivN && TIV_lead[ts]!=1 ;ts++ ){
  if( TIV_dR[ts] < TIV_dR_outer_thr  && TIV_dR[ts] > TIV_dR_inner_thr && TIV_pt[ts] > TIV_pt_s_thr){
  ILV_isoPT+= TIV_pt[ts];
  }
  }
  if( ILV_isoPT / TIV_pt[tl] < Lower_TIV ) Lower_TIV = ILV_isoPT / TIV_pt[tl];
  }
  }
  LowTIV = Lower_TIV;
  */
  
  ///-------------------------------------------------------------------------- 
  /// Fill tree
  ///--------------------------------------------------------------------------
  mtree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void NtupleAnalyzer::beginJob()
{
  /// Run and Event lumi bx weight
  mtree->Branch("run"      ,&mRun       , "run/I");
  mtree->Branch("event"    ,&mEvent     , "event/L");
  mtree->Branch("lumi"     ,&mLumi      , "lumi/I");	
  mtree->Branch("bx"       ,&mBX        , "bx/I");
  mtree->Branch("npvm1"    ,&mnpvm1     , "npvm1/I");
  mtree->Branch("npv0"     ,&mnpv0      , "npv0/I");
  mtree->Branch("npvp1"    ,&mnpvp1     , "npvp1/I");
  mtree->Branch("ptHat"    ,&WeightTag  , "ptHat/D");	
  
  mtree->Branch("CaloTowerdEx"    ,&mCaloTowerdEx  , "CaloTowerdEx/D");	
  mtree->Branch("CaloTowerdEy"    ,&mCaloTowerdEy  , "CaloTowerdEy/D");	

  mtree->Branch("fastJetRho"      ,&mfastJetRho    , "fastJetRho/D");
  
  /// Calo AK5 Jets
  mtree->Branch("NCaloAK5Jets"            ,&mNCaloAK5Jets           ,  "NCaloAK5Jets/I"                      );
  mtree->Branch("CaloAK5JetE"             ,mCaloAK5JetE             ,  "CaloAK5JetE[NCaloAK5Jets]/D"         );
  mtree->Branch("CaloAK5JetPt"            ,mCaloAK5JetPt            ,  "CaloAK5JetPt[NCaloAK5Jets]/D"        );
  mtree->Branch("CaloAK5JetPx"            ,mCaloAK5JetPx            ,  "CaloAK5JetPx[NCaloAK5Jets]/D"        );
  mtree->Branch("CaloAK5JetPy"            ,mCaloAK5JetPy            ,  "CaloAK5JetPy[NCaloAK5Jets]/D"        );
  mtree->Branch("CaloAK5JetPz"            ,mCaloAK5JetPz            ,  "CaloAK5JetPz[NCaloAK5Jets]/D"        );
  mtree->Branch("CaloAK5JetEta"           ,mCaloAK5JetEta           ,  "CaloAK5JetEta[NCaloAK5Jets]/D"       );
  mtree->Branch("CaloAK5JetPhi"           ,mCaloAK5JetPhi           ,  "CaloAK5JetPhi[NCaloAK5Jets]/D"       );
  mtree->Branch("CaloAK5JetEmf"           ,mCaloAK5JetEmf           ,  "CaloAK5JetFem[NCaloAK5Jets]/D"       ); 
  mtree->Branch("CaloAK5JetfHPD"          ,mCaloAK5JetfHPD          ,  "CaloAK5JetfHPD[NCaloAK5Jets]/D"      ); 
  mtree->Branch("CaloAK5JetfRBX"          ,mCaloAK5JetfRBX          ,  "CaloAK5JetfRBX[NCaloAK5Jets]/D"      ); 
  mtree->Branch("CaloAK5JetN90Hits"       ,mCaloAK5JetN90Hits       ,  "CaloAK5JetN90Hits[NCaloAK5Jets]/D"   ); 
  mtree->Branch("CaloAK5JetN90"           ,mCaloAK5JetN90           ,  "CaloAK5JetN90[NCaloAK5Jets]/I"       ); 
  mtree->Branch("CaloAK5JetSigEta"        ,mCaloAK5JetSigEta        ,  "CaloAK5JetSigEta[NCaloAK5Jets]/D"    ); 
  mtree->Branch("CaloAK5JetSigPhi"        ,mCaloAK5JetSigPhi        ,  "CaloAK5JetSigPhi[NCaloAK5Jets]/D"    ); 
  mtree->Branch("CaloAK5JetIDEmf"         ,mCaloAK5JetIDEmf         ,  "CaloAK5JetIDEmf[NCaloAK5Jets]/D"     ); 
  
  mtree->Branch("CaloAK5JetECor"          ,mCaloAK5JetECor          ,  "CaloAK5JetECor[NCaloAK5Jets]/D"      );
  mtree->Branch("CaloAK5JetPtCor"         ,mCaloAK5JetPtCor         ,  "CaloAK5JetPtCor[NCaloAK5Jets]/D"     );
  mtree->Branch("CaloAK5JetPxCor"         ,mCaloAK5JetPxCor         ,  "CaloAK5JetPxCor[NCaloAK5Jets]/D"     );
  mtree->Branch("CaloAK5JetPyCor"         ,mCaloAK5JetPyCor         ,  "CaloAK5JetPyCor[NCaloAK5Jets]/D"     );
  mtree->Branch("CaloAK5JetPzCor"         ,mCaloAK5JetPzCor         ,  "CaloAK5JetPzCor[NCaloAK5Jets]/D"     );
  
  mtree->Branch("CaloAK5JetBtagTkCountHighEff"   ,mCaloAK5JetBtagTkCountHighEff   ,"CaloAK5JetBtagTkCountHighEff[NCaloAK5Jets]/D"     );
  mtree->Branch("CaloAK5JetBTagSimpleSecVtx"     ,mCaloAK5JetBTagSimpleSecVtx     ,"CaloAK5JetBTagSimpleSecVtx[NCaloAK5Jets]/D"     );
  mtree->Branch("CaloAK5JetBTagCombSecVtx"       ,mCaloAK5JetBTagCombSecVtx       ,"CaloAK5JetBTagCombSecVtx[NCaloAK5Jets]/D"     );
  
  mtree->Branch("CaloAK5TrackPt"          ,mCaloAK5TrackPt          ,  "CaloAK5TrackPt[NCaloAK5Jets]/D"     );
  
  mtree->Branch("CaloAK5JetIDLOOSE"       ,mCaloAK5JetIDLOOSE       ,  "CaloAK5JetIDLOOSE[NCaloAK5Jets]/I"     );
  mtree->Branch("CaloAK5JetIDTIGHT"       ,mCaloAK5JetIDTIGHT       ,  "CaloAK5JetIDTIGHT[NCaloAK5Jets]/I"     );
  
  
  if(isMCTag){
    /// Gen AK5 Jets
    mtree->Branch("GenAK5JetE"                ,mGenAK5JetE             ,  "GenAK5JetE[NCaloAK5Jets]/D"         );
    mtree->Branch("GenAK5JetPt"               ,mGenAK5JetPt            ,  "GenAK5JetPt[NCaloAK5Jets]/D"        );
    mtree->Branch("GenAK5JetPx"               ,mGenAK5JetPx            ,  "GenAK5JetPx[NCaloAK5Jets]/D"        );
    mtree->Branch("GenAK5JetPy"               ,mGenAK5JetPy            ,  "GenAK5JetPy[NCaloAK5Jets]/D"        );
    mtree->Branch("GenAK5JetPz"               ,mGenAK5JetPz            ,  "GenAK5JetPz[NCaloAK5Jets]/D"        );
    mtree->Branch("GenAK5JetEta"              ,mGenAK5JetEta           ,  "GenAK5JetEta[NCaloAK5Jets]/D"       );
    mtree->Branch("GenAK5JetPhi"              ,mGenAK5JetPhi           ,  "GenAK5JetPhi[NCaloAK5Jets]/D"       );
    mtree->Branch("GenAK5JetEmEnergy"         ,mGenAK5JetEmEnergy      ,  "GenAK5JetEmEnergy[NCaloAK5Jets]/D"  );
    mtree->Branch("GenAK5JetHadEnergy"        ,mGenAK5JetHadEnergy     ,  "GenAK5JetHadEnergy[NCaloAK5Jets]/D" );
  }      
  
  
  /// PF AK5 Jets
  mtree->Branch("NPFAK5Jets"                  ,&mNPFAK5Jets           ,  "NPFAK5Jets/I"                    );
  mtree->Branch("PFAK5JetE"                   ,mPFAK5JetE             ,  "PFAK5JetE[NPFAK5Jets]/D"         );
  mtree->Branch("PFAK5JetPt"                  ,mPFAK5JetPt            ,  "PFAK5JetPt[NPFAK5Jets]/D"        );
  mtree->Branch("PFAK5JetPx"                  ,mPFAK5JetPx            ,  "PFAK5JetPx[NPFAK5Jets]/D"        );
  mtree->Branch("PFAK5JetPy"                  ,mPFAK5JetPy            ,  "PFAK5JetPy[NPFAK5Jets]/D"        );
  mtree->Branch("PFAK5JetPz"                  ,mPFAK5JetPz            ,  "PFAK5JetPz[NPFAK5Jets]/D"        );
  mtree->Branch("PFAK5JetEta"                 ,mPFAK5JetEta           ,  "PFAK5JetEta[NPFAK5Jets]/D"       );
  mtree->Branch("PFAK5JetPhi"                 ,mPFAK5JetPhi           ,  "PFAK5JetPhi[NPFAK5Jets]/D"       );
  
  mtree->Branch("PFAK5JetfHPD"                ,mPFAK5JetfHPD          ,  "PFAK5JetfHPD[NPFAK5Jets]/D"      ); 
  mtree->Branch("PFAK5JetfRBX"                ,mPFAK5JetfRBX          ,  "PFAK5JetfRBX[NPFAK5Jets]/D"      ); 
  mtree->Branch("PFAK5JetN90Hits"             ,mPFAK5JetN90Hits       ,  "PFAK5JetN90Hits[NPFAK5Jets]/D"   ); 
  mtree->Branch("PFAK5JetN90"                 ,mPFAK5JetN90           ,  "PFAK5JetN90[NPFAK5Jets]/I"       ); 
  mtree->Branch("PFAK5JetSigEta"              ,mPFAK5JetSigEta        ,  "PFAK5JetSigEta[NPFAK5Jets]/D"    ); 
  mtree->Branch("PFAK5JetSigPhi"              ,mPFAK5JetSigPhi        ,  "PFAK5JetSigPhi[NPFAK5Jets]/D"    ); 
  mtree->Branch("PFAK5JetIDEmf"               ,mPFAK5JetIDEmf         ,  "PFAK5JetIDEmf[NPFAK5Jets]/D"     ); 
  
  mtree->Branch("PFAK5JetECor"                ,mPFAK5JetECor          ,  "PFAK5JetECor[NPFAK5Jets]/D"      );
  mtree->Branch("PFAK5JetPtCor"               ,mPFAK5JetPtCor         ,  "PFAK5JetPtCor[NPFAK5Jets]/D"     );
  mtree->Branch("PFAK5JetPxCor"               ,mPFAK5JetPxCor         ,  "PFAK5JetPxCor[NPFAK5Jets]/D"     );
  mtree->Branch("PFAK5JetPyCor"               ,mPFAK5JetPyCor         ,  "PFAK5JetPyCor[NPFAK5Jets]/D"     );
  mtree->Branch("PFAK5JetPzCor"               ,mPFAK5JetPzCor         ,  "PFAK5JetPzCor[NPFAK5Jets]/D"     );
  
  mtree->Branch("PFAK5JetBtagTkCountHighEff"  ,mPFAK5JetBtagTkCountHighEff,  "PFAK5JetBtagTkCountHighEff[NPFAK5Jets]/D");
  mtree->Branch("PFAK5JetBtagTkCountHighPur"  ,mPFAK5JetBtagTkCountHighPur,  "PFAK5JetBtagTkCountHighPur[NPFAK5Jets]/D");
  mtree->Branch("PFAK5JetBtagJetProbability"  ,mPFAK5JetBtagJetProbability,  "PFAK5JetBtagJetProbability[NPFAK5Jets]/D");
  mtree->Branch("PFAK5JetBtagJetBProbability" ,mPFAK5JetBtagJetBProbability, "PFAK5JetBtagJetBProbability[NPFAK5Jets]/D");
  mtree->Branch("PFAK5JetBTagSimpleSecVtx"    ,mPFAK5JetBTagSimpleSecVtx,    "PFAK5JetBTagSimpleSecVtx[NPFAK5Jets]/D");
  mtree->Branch("PFAK5JetBTagCombSecVtx"      ,mPFAK5JetBTagCombSecVtx,      "PFAK5JetBTagCombSecVtx[NPFAK5Jets]/D");
  mtree->Branch("PFAK5JetBTagCombSecVtxMVA"   ,mPFAK5JetBTagCombSecVtxMVA,   "PFAK5JetBTagCombSecVtxMVA[NPFAK5Jets]/D");
    
  mtree->Branch("PFAK5JetNeuEmEngFrac"        ,mPFAK5JetNeuEmEngFrac  ,  "PFAK5JetNeuEmEngFrac[NPFAK5Jets]/D" ); 
  mtree->Branch("PFAK5JetChaEmEngFrac"        ,mPFAK5JetChaEmEngFrac  ,  "PFAK5JetChaEmEngFrac[NPFAK5Jets]/D" ); 
  mtree->Branch("PFAK5JetChaHadEngFrac"       ,mPFAK5JetChaHadEngFrac ,  "PFAK5JetChaHadEngFrac[NPFAK5Jets]/D" ); 
  mtree->Branch("PFAK5JetNeuHadEngFrac"       ,mPFAK5JetNeuHadEngFrac ,  "PFAK5JetNeuHadEngFrac[NPFAK5Jets]/D" ); 
  mtree->Branch("PFAK5JetChaMuEng"            ,mPFAK5JetChaMuEng      ,  "PFAK5JetChaMuEng[NPFAK5Jets]/D" ); 
  mtree->Branch("PFAK5JetMuonEng"             ,mPFAK5JetMuonEng       ,  "PFAK5JetMuonEng[NPFAK5Jets]/D" ); 
  mtree->Branch("PFAK5JetPhotEng"             ,mPFAK5JetPhotEng       ,  "PFAK5JetPhotEng[NPFAK5Jets]/D" ); 
  mtree->Branch("PFAK5JetElecEng"             ,mPFAK5JetElecEng       ,  "PFAK5JetElecEng[NPFAK5Jets]/D" );
	
  mtree->Branch("PFAK5JetNumOfChaMu"          ,mPFAK5JetNumOfChaMu   ,  "PFAK5JetNumOfChaMu[NPFAK5Jets]/I" ); 
  mtree->Branch("PFAK5JetNumOfMuon"           ,mPFAK5JetNumOfMuon    ,  "PFAK5JetNumOfMuon[NPFAK5Jets]/I" ); 
  mtree->Branch("PFAK5JetNumOfPhot"           ,mPFAK5JetNumOfPhot    ,  "PFAK5JetNumOfPhot[NPFAK5Jets]/I" ); 
  mtree->Branch("PFAK5JetNumOfElec"           ,mPFAK5JetNumOfElec    ,  "PFAK5JetNumOfElec[NPFAK5Jets]/I" ); 
  mtree->Branch("PFAK5JetNumOfNeu"            ,mPFAK5JetNumOfNeu     ,  "PFAK5JetNumOfNeu[NPFAK5Jets]/I" ); 
  mtree->Branch("PFAK5JetNumOfCha"            ,mPFAK5JetNumOfCha     ,  "PFAK5JetNumOfCha[NPFAK5Jets]/I" ); 
  mtree->Branch("PFAK5JetNumOfNeuHad"         ,mPFAK5JetNumOfNeuHad  ,  "PFAK5JetNumOfNeuHad[NPFAK5Jets]/I" ); 
  mtree->Branch("PFAK5JetNumOfChaHad"         ,mPFAK5JetNumOfChaHad  ,  "PFAK5JetNumOfChaHad[NPFAK5Jets]/I" ); 
  mtree->Branch("PFAK5JetNumOfDaughters"      ,mPFAK5JetNumOfDaughters  ,"PFAK5JetNumOfDaughters[NPFAK5Jets]/I" );
  mtree->Branch("PFAK5JetIDLOOSE"             ,mPFAK5JetIDLOOSE      ,"PFAK5JetIDLOOSE[NPFAK5Jets]/I" );
  mtree->Branch("PFAK5JetIDTIGHT"             ,mPFAK5JetIDTIGHT      ,"PFAK5JetIDTIGHT[NPFAK5Jets]/I" );
  mtree->Branch("PFAK5JetPUFullJetId"         ,mPFAK5JetPUFullJetId      ,"PFAK5JetPUFullJetId[NPFAK5Jets]/I" );
  mtree->Branch("PFAK5uncer"                  ,mPFAK5uncer           ,"PFAK5uncer[NPFAK5Jets]/D");
  
  
  /// Met 
  mtree->Branch("NMet"     ,&mNMet    ,"NMet/I");
  mtree->Branch("MetPt"    ,mMetPt    ,"MetPt[NMet]/D");
  mtree->Branch("MetPx"    ,mMetPx    ,"MetPx[NMet]/D");
  mtree->Branch("MetPy"    ,mMetPy    ,"MetPy[NMet]/D");
  mtree->Branch("MetPhi"   ,mMetPhi   ,"MetPhi[NMet]/D");
  mtree->Branch("MetSumEt" ,mMetSumEt ,"MetSumEt[NMet]/D");
  mtree->Branch("MetSign"  ,mMetSign  ,"MetSign[NMet]/D");
  
  
  /// MHT 
  mtree->Branch("MHTPt"    ,&mMHTPt    ,"MHTPt/D");
  //mtree->Branch("MHTPhi"   ,&mMHTPhi   ,"MHTPhi/D");
  mtree->Branch("MHTSign"  ,&mMHTSign  ,"MHTSign/D");
	
  
  /// Muon
  mtree->Branch("NMuon"            ,&mNMuon                        ,"NMuon/I");
  mtree->Branch("MuonPt"           ,mMuonPt                        ,"MuonPt[NMuon]/D" );
  mtree->Branch("MuonEt"           ,mMuonEt                        ,"MuonEt[NMuon]/D" );
  mtree->Branch("MuonE"            ,mMuonE                         ,"MuonE[NMuon]/D" );
  mtree->Branch("MuonPx"           ,mMuonPx                        ,"MuonPx[NMuon]/D" );
  mtree->Branch("MuonPy"           ,mMuonPy                        ,"MuonPy[NMuon]/D" );
  mtree->Branch("MuonPz"           ,mMuonPz                        ,"MuonPz[NMuon]/D" );
  mtree->Branch("MuonEta"          ,mMuonEta                       ,"MuonEta[NMuon]/D" );
  mtree->Branch("MuonPhi"          ,mMuonPhi                       ,"MuonPhi[NMuon]/D" );
  mtree->Branch("MuonCharge"       ,mMuonCharge                    ,"MuonCharge[NMuon]/D" );
  
  mtree->Branch("MuonIsGlobal"     ,mMuonIsGlobal                  ,"MuonIsGlobal[NMuon]/I" );
  mtree->Branch("MuonIsStandAlone" ,mMuonIsStandAlone              ,"MuonIsStandAlone[NMuon]/I" );
  mtree->Branch("MuonIsTracker"    ,mMuonIsTracker                 ,"MuonIsTracker[NMuon]/I" );
  
  mtree->Branch("MuonSumPtDR03"    ,mMuonSumPtDR03                 ,"MuonSumPtDR03[NMuon]/D" );
  mtree->Branch("MuonSumPtDR05"    ,mMuonSumPtDR05                 ,"MuonSumPtDR05[NMuon]/D" );
  mtree->Branch("MuonEmEtDR03"     ,mMuonEmEtDR03                  ,"MuonEmEtDR03[NMuon]/D" );
  mtree->Branch("MuonHadEtDR03"    ,mMuonHadEtDR03                 ,"MuonHadEtDR03[NMuon]/D" );
  mtree->Branch("MuonNumOfMatches" ,mMuonNumOfMatches              ,"MuonNumOfMatches[NMuon]/I" );
  
  mtree->Branch("MuonCombChi2Norm" ,mMuonCombChi2Norm              ,"MuonCombChi2Norm[NMuon]/D" );
  mtree->Branch("MuonCombValidHits",mMuonCombValidHits             ,"MuonCombValidHits[NMuon]/I" );
  mtree->Branch("MuonCombLostHits" ,mMuonCombLostHits              ,"MuonCombLostHits[NMuon]/I" );
  mtree->Branch("MuonCombPt"       ,mMuonCombPt                    ,"MuonCombPt[NMuon]/D" );
  mtree->Branch("MuonCombPz"       ,mMuonCombPz                    ,"MuonCombPz[NMuon]/D" );
  mtree->Branch("MuonCombP"        ,mMuonCombP                     ,"MuonCombP[NMuon]/D" );
  mtree->Branch("MuonCombEta"      ,mMuonCombEta                   ,"MuonCombEta[NMuon]/D" );
  mtree->Branch("MuonCombPhi"      ,mMuonCombPhi                   ,"MuonCombPhi[NMuon]/D" );
  mtree->Branch("MuonCombChi2"     ,mMuonCombChi2                  ,"MuonCombChi2[NMuon]/D" );
  mtree->Branch("MuonCombCharge"   ,mMuonCombCharge                ,"MuonCombCharge[NMuon]/D" );
  mtree->Branch("MuonCombQOverPError",mMuonCombQOverPError         ,"MuonCombQOverPError[NMuon]/D" );
  mtree->Branch("MuonCombNdof"     ,mMuonCombNdof                  ,"MuonCombNdof[NMuon]/D" );
  mtree->Branch("MuonCombVx"       ,mMuonCombVx                    ,"MuonCombVx[NMuon]/D" );
  mtree->Branch("MuonCombVy"       ,mMuonCombVy                    ,"MuonCombVy[NMuon]/D" );
  mtree->Branch("MuonCombVz"       ,mMuonCombVz                    ,"MuonCombVz[NMuon]/D" );
  mtree->Branch("MuonCombD0"       ,mMuonCombD0                    ,"MuonCombD0[NMuon]/D" );
  mtree->Branch("MuonCombDz"       ,mMuonCombDz                    ,"MuonCombDz[NMuon]/D" );
  
  mtree->Branch("MuonStandChi2Norm",mMuonStandChi2Norm             ,"MuonStandChi2Norm[NMuon]/D" );
  mtree->Branch("MuonStandValidHits",mMuonStandValidHits           ,"MuonStandValidHits[NMuon]/I" );
  mtree->Branch("MuonStandLostHits",mMuonStandLostHits             ,"MuonStandLostHits[NMuon]/I" );
  mtree->Branch("MuonStandPt"      ,mMuonStandPt                   ,"MuonStandPt[NMuon]/D" );
  mtree->Branch("MuonStandPz"      ,mMuonStandPz                   ,"MuonStandPz[NMuon]/D" );
  mtree->Branch("MuonStandP"       ,mMuonStandP                    ,"MuonStandP[NMuon]/D" );
  mtree->Branch("MuonStandEta"     ,mMuonStandEta                  ,"MuonStandEta[NMuon]/D" );
  mtree->Branch("MuonStandPhi"     ,mMuonStandPhi                  ,"MuonStandPhi[NMuon]/D" );
  mtree->Branch("MuonStandChi2"    ,mMuonStandChi2                 ,"MuonStandChi2[NMuon]/D" );
  mtree->Branch("MuonStandCharge"  ,mMuonStandCharge               ,"MuonStandCharge[NMuon]/D" );
  mtree->Branch("MuonStandQOverPError",mMuonStandQOverPError       ,"MuonStandQOverPError[NMuon]/D" );	
  
  mtree->Branch("MuonTrkChi2Norm"  ,mMuonTrkChi2Norm               ,"MuonTrkChi2Norm[NMuon]/D" );
  mtree->Branch("MuonTrkValidHits" ,mMuonTrkValidHits              ,"MuonTrkValidHits[NMuon]/I" );
  mtree->Branch("MuonTrkLostHits"  ,mMuonTrkLostHits               ,"MuonTrkLostHits[NMuon]/I" );
  mtree->Branch("MuonTrkPt"        ,mMuonTrkPt                     ,"MuonTrkPt[NMuon]/D" );
  mtree->Branch("MuonTrkPz"        ,mMuonTrkPz                     ,"MuonTrkPz[NMuon]/D" );
  mtree->Branch("MuonTrkP"         ,mMuonTrkP                      ,"MuonTrkP[NMuon]/D" );
  mtree->Branch("MuonTrkEta"       ,mMuonTrkEta                    ,"MuonTrkEta[NMuon]/D" );
  mtree->Branch("MuonTrkPhi"       ,mMuonTrkPhi                    ,"MuonTrkPhi[NMuon]/D" );
  mtree->Branch("MuonTrkChi2"      ,mMuonTrkChi2                   ,"MuonTrkChi2[NMuon]/D" );
  mtree->Branch("MuonTrkCharge"    ,mMuonTrkCharge                 ,"MuonTrkCharge[NMuon]/D" );
  mtree->Branch("MuonTrkQOverPError",mMuonTrkQOverPError           ,"MuonTrkQOverPError[NMuon]/D" );
  mtree->Branch("MuonTrkDxy"       ,mMuonTrkDxy                    ,"MuonTrkDxy[NMuon]/D" );
  mtree->Branch("MuonTrkNumOfValidPixHits" ,mMuonTrkNumOfValidPixHits  ,"MuonTrkNumOfValidPixHits[NMuon]/I" );
  
     
  /// PF Muons
  mtree->Branch("NPFMuon"                      ,&mNPFMuon                  ,"NPFMuon/I"                   );
  mtree->Branch("PFMuonPt"                     ,mPFMuonPt                  ,"PFMuonPt[NPFMuon]/D"         );               
  mtree->Branch("PFMuonEt"                     ,mPFMuonEt                  ,"PFMuonEt[NPFMuon]/D"         );             
  mtree->Branch("PFMuonE"                      ,mPFMuonE                   ,"PFMuonE[NPFMuon]/D"          );                
  mtree->Branch("PFMuonPx"                     ,mPFMuonPx                  ,"PFMuonPx[NPFMuon]/D"         );               
  mtree->Branch("PFMuonPy"                     ,mPFMuonPy                  ,"PFMuonPy[NPFMuon]/D"         );               
  mtree->Branch("PFMuonPz"                     ,mPFMuonPz                  ,"PFMuonPz[NPFMuon]/D"         );               
  mtree->Branch("PFMuonEta"                    ,mPFMuonEta                 ,"PFMuonEta[NPFMuon]/D"        );              
  mtree->Branch("PFMuonPhi"                    ,mPFMuonPhi                 ,"PFMuonPhi[NPFMuon]/D"        );              
  mtree->Branch("PFMuonCharge"                 ,mPFMuonCharge              ,"PFMuonCharge[NPFMuon]/I"     );           
  
  mtree->Branch("PFMuonIsGlobal"               ,mPFMuonIsGlobal            ,"PFMuonIsGlobal[NPFMuon]/I"    );         
  mtree->Branch("PFMuonIsStandAlone"           ,mPFMuonIsStandAlone        ,"PFMuonIsStandAlone[NPFMuon]/I");     
  mtree->Branch("PFMuonIsTracker"              ,mPFMuonIsTracker           ,"PFMuonIsTracker[NPFMuon]/I"   );        
  
  mtree->Branch("PFMuonChargedHadronIso"       ,mPFMuonChargedHadronIso    ,"PFMuonChargedHadronIso[NPFMuon]/D" ); 
  mtree->Branch("PFMuonPhotonIso"              ,mPFMuonPhotonIso           ,"PFMuonPhotonIso[NPFMuon]/D"        );        
  mtree->Branch("PFMuonNeutralHadronIso"       ,mPFMuonNeutralHadronIso    ,"PFMuonNeutralHadronIso[NPFMuon]/D" ); 
  mtree->Branch("PFMuonisGMPT"                 ,mPFMuonisGMPT              ,"PFMuonisGMPT[NPFMuon]/I"           );           
  mtree->Branch("PFMuonNumOfMatches"           ,mPFMuonNumOfMatches        ,"PFMuonNumOfMatches[NPFMuon]/I"     );  
  mtree->Branch("PFMuonR04ChargedHadronPt"     ,mPFMuonR04ChargedHadronPt  ,"PFMuonR04ChargedHadronPt[NPFMuon]/D");
  mtree->Branch("PFMuonR04NeutralHadronEt"     ,mPFMuonR04NeutralHadronEt  ,"PFMuonR04NeutralHadronEt[NPFMuon]/D");
  mtree->Branch("PFMuonR04PhotonEt"            ,mPFMuonR04PhotonEt         ,"PFMuonR04PhotonEt[NPFMuon]/D");
  mtree->Branch("PFMuonR04PUPt"                ,mPFMuonR04PUPt             ,"PFMuonR04PUPt[NPFMuon]/D"); 
  
  mtree->Branch("PFMuoninnertrackPt"           ,mPFMuoninnertrackPt        ,"PFMuoninnertrackPt[NPFMuon]/D"     );     
  mtree->Branch("PFMuonnValidHits"             ,mPFMuonnValidHits          ,"PFMuonnValidHits[NPFMuon]/I"       );       
  mtree->Branch("PFMuonnValidPixelHits"        ,mPFMuonnValidPixelHits     ,"PFMuonnValidPixelHits[NPFMuon]/I"  );  
  mtree->Branch("PFMuondxy"                    ,mPFMuondxy                 ,"PFMuondxy[NPFMuon]/D"              );              
  mtree->Branch("PFMuondz"                     ,mPFMuondz                  ,"PFMuondz[NPFMuon]/D"               );               
  
  mtree->Branch("PFMuonCombChi2Norm"           ,mPFMuonCombChi2Norm        ,"PFMuonCombChi2Norm[NPFMuon]/D"     );    
  mtree->Branch("PFMuonCombValidHits"          ,mPFMuonCombValidHits       ,"PFMuonCombValidHits[NPFMuon]/I"    );   
  mtree->Branch("PFMuonCombLostHits"           ,mPFMuonCombLostHits        ,"PFMuonCombLostHits[NPFMuon]/I"     );    
  mtree->Branch("PFMuonCombPt"                 ,mPFMuonCombPt              ,"PFMuonCombPt[NPFMuon]/D"           );          
  mtree->Branch("PFMuonCombPz"                 ,mPFMuonCombPz              ,"PFMuonCombPz[NPFMuon]/D"           );          
  mtree->Branch("PFMuonCombP"                  ,mPFMuonCombP               ,"PFMuonCombP[NPFMuon]/D"            );           
  mtree->Branch("PFMuonCombEta"                ,mPFMuonCombEta             ,"PFMuonCombEta[NPFMuon]/D"          );         
  mtree->Branch("PFMuonCombPhi"                ,mPFMuonCombPhi             ,"PFMuonCombPhi[NPFMuon]/D"          );         
  mtree->Branch("PFMuonCombChi2"               ,mPFMuonCombChi2            ,"PFMuonCombChi2[NPFMuon]/D"         );        
  mtree->Branch("PFMuonCombCharge"             ,mPFMuonCombCharge          ,"PFMuonCombCharge[NPFMuon]/D"       );      
  mtree->Branch("PFMuonCombQOverPError"        ,mPFMuonCombQOverPError     ,"PFMuonCombQOverPError[NPFMuon]/D"  ); 
  mtree->Branch("PFMuonCombNdof"               ,mPFMuonCombNdof            ,"PFMuonCombNdof[NPFMuon]/D"         );        
  mtree->Branch("PFMuonCombVx"                 ,mPFMuonCombVx              ,"PFMuonCombVx[NPFMuon]/D" );          
  mtree->Branch("PFMuonCombVy"                 ,mPFMuonCombVy              ,"PFMuonCombVy[NPFMuon]/D" );          
  mtree->Branch("PFMuonCombVz"                 ,mPFMuonCombVz              ,"PFMuonCombVz[NPFMuon]/D" );          
  mtree->Branch("PFMuonCombD0"                 ,mPFMuonCombD0              ,"PFMuonCombD0[NPFMuon]/D" );          
  mtree->Branch("PFMuonCombDz"                 ,mPFMuonCombDz              ,"PFMuonCombDz[NPFMuon]/D" );          
  
  mtree->Branch("PFMuonStandChi2Norm"          ,mPFMuonStandChi2Norm       ,"PFMuonStandChi2Norm[NPFMuon]/D" );;   
  mtree->Branch("PFMuonStandValidHits"         ,mPFMuonStandValidHits      ,"PFMuonStandValidHits[NPFMuon]/I" );;  
  mtree->Branch("PFMuonStandLostHits"          ,mPFMuonStandLostHits       ,"PFMuonStandLostHits[NPFMuon]/I" );;   
  mtree->Branch("PFMuonStandPt"                ,mPFMuonStandPt             ,"PFMuonStandPt[NPFMuon]/D" );;         
  mtree->Branch("PFMuonStandPz"                ,mPFMuonStandPz             ,"PFMuonStandPz[NPFMuon]/D" );;         
  mtree->Branch("PFMuonStandP"                 ,mPFMuonStandP              ,"PFMuonStandP[NPFMuon]/D" );;          
  mtree->Branch("PFMuonStandEta"               ,mPFMuonStandEta            ,"PFMuonStandEta[NPFMuon]/D" );;        
  mtree->Branch("PFMuonStandPhi"               ,mPFMuonStandPhi            ,"PFMuonStandPhi[NPFMuon]/D" );;        
  mtree->Branch("PFMuonStandChi2"              ,mPFMuonStandChi2           ,"PFMuonStandChi2[NPFMuon]/D" );;       
  mtree->Branch("PFMuonStandCharge"            ,mPFMuonStandCharge         ,"PFMuonStandCharge[NPFMuon]/D" );;     
  mtree->Branch("PFMuonStandQOverPError"       ,mPFMuonStandQOverPError    ,"PFMuonStandQOverPError[NPFMuon]/D" );;
  
  mtree->Branch("PFMuonTrkChi2Norm"            ,mPFMuonTrkChi2Norm         ,"PFMuonTrkChi2Norm[NPFMuon]/D" );;    
  mtree->Branch("PFMuonTrkValidHits"           ,mPFMuonTrkValidHits        ,"PFMuonTrkValidHits[NPFMuon]/I" );;   
  mtree->Branch("PFMuonTrkLostHits"            ,mPFMuonTrkLostHits         ,"PFMuonTrkLostHits[NPFMuon]/I" );;    
  mtree->Branch("PFMuonTrkPt"                  ,mPFMuonTrkPt               ,"PFMuonTrkPt[NPFMuon]/D" );;          
  mtree->Branch("PFMuonTrkPz"                  ,mPFMuonTrkPz               ,"PFMuonTrkPz[NPFMuon]/D" );;          
  mtree->Branch("PFMuonTrkP"                   ,mPFMuonTrkP                ,"PFMuonTrkP[NPFMuon]/D" );;           
  mtree->Branch("PFMuonTrkEta"                 ,mPFMuonTrkEta              ,"PFMuonTrkEt[NPFMuon]/D" );;         
  mtree->Branch("PFMuonTrkPhi"                 ,mPFMuonTrkPhi              ,"PFMuonTrkPhi[NPFMuon]/D" );;         
  mtree->Branch("PFMuonTrkChi2"                ,mPFMuonTrkChi2             ,"PFMuonTrkChi2[NPFMuon]/D" );;        
  mtree->Branch("PFMuonTrkCharge"              ,mPFMuonTrkCharge           ,"PFMuonTrkCharge[NPFMuon]/D" );;      
  mtree->Branch("PFMuonTrkQOverPError"         ,mPFMuonTrkQOverPError      ,"PFMuonTrkQOverPError[NPFMuon]/D" );; 
  mtree->Branch("PFMuonTrkDxy"                 ,mPFMuonTrkDxy              ,"PFMuonTrkDxy[NPFMuon]/D" );;         
  mtree->Branch("PFMuonTrkNumOfValidPixHits"   ,mPFMuonTrkNumOfValidPixHits,"PFMuonTrkNumOfValidPixHits[NPFMuon]/D" );;
  
  
  /// Electrons
  mtree->Branch("NElec"                    ,&mNElec                         ,"NElec/I");
  mtree->Branch("ElecE"                    ,mElecE                          ,"ElecE[NElec]/D");
  mtree->Branch("ElecPt"                   ,mElecPt                         ,"ElecPt[NElec]/D");
  mtree->Branch("ElecPx"                   ,mElecPx                         ,"ElecPx[NElec]/D");
  mtree->Branch("ElecPy"                   ,mElecPy                         ,"ElecPy[NElec]/D");
  mtree->Branch("ElecPz"                   ,mElecPz                         ,"ElecPz[NElec]/D");
  mtree->Branch("ElecEcalDrivenSeed"       ,mElecEcalDrivenSeed             ,"ElecEcalDrivenSeed[NElec]/I");
  mtree->Branch("ElecID80"                 ,mElecID80                       ,"ElecID80[NElec]/I");
  mtree->Branch("ElecID95"                 ,mElecID95                       ,"ElecID95[NElec]/I");
  
  mtree->Branch("ElecEta"                  ,mElecEta                        ,"ElecEta[NElec]/D");
  mtree->Branch("ElecPhi"                  ,mElecPhi                        ,"ElecPhi[NElec]/D");
  mtree->Branch("ElecCharge"               ,mElecCharge                     ,"ElecCharge[NElec]/I");
  mtree->Branch("Elecdr03HcalTowerSumEt"   ,mElecdr03HcalTowerSumEt         ,"Elecdr03HcalTowerSumEt[NElec]/D");
  mtree->Branch("Elecdr03EcalRecHitSumEt"  ,mElecdr03EcalRecHitSumEt        ,"Elecdr03EcalRecHitSumEt[NElec]/D");
  mtree->Branch("Elecdr03TkSumPt"          ,mElecdr03TkSumPt                ,"Elecdr03TkSumPt[NElec]/D");
  mtree->Branch("ElecNumOfValidHits"       ,mElecNumOfValidHits             ,"ElecNumOfValidHits[NElec]/I");
  mtree->Branch("ElecInnerNumOfHits"       ,mElecInnerNumOfHits             ,"ElecInnerNumOfHits[NElec]/I");
  mtree->Branch("Elecdist"                 ,mElecdist                       ,"Elecdist[NElec]/D");
  mtree->Branch("Elecdcot"                 ,mElecdcot                       ,"Elecdcot[NElec]/D");
  mtree->Branch("ElecNormChi2"             ,mElecNormChi2                   ,"ElecNormChi2[NElec]/D");
  mtree->Branch("Elecdxy"                  ,mElecdxy                        ,"Elecdxy[NElec]/D");
  mtree->Branch("Elecdz"                   ,mElecdz                         ,"Elecdz[NElec]/D");
  mtree->Branch("ElecdB"                   ,mElecdB                         ,"ElecdB[NElec]/I");
  mtree->Branch("ElecIsEB"                 ,mElecIsEB                       ,"ElecIsEB[NElec]/I");
  mtree->Branch("Elecfbrem"                ,mElecfbrem                      ,"Elecfbrem[NElec]/D");
  mtree->Branch("ElecDEtaSuTrAtVtx"        ,mElecDEtaSuTrAtVtx              ,"ElecDEtaSuTrAtVtx[NElec]/D");
  mtree->Branch("ElecDPhiSuTrAtVtx"        ,mElecDPhiSuTrAtVtx              ,"ElecDPhiSuTrAtVtx[NElec]/D");
  mtree->Branch("ElecHadronicOverEm"       ,mElecHadronicOverEm             ,"ElecHadronicOverEm[NElec]/D");
  mtree->Branch("ElecHcalOverEcal"         ,mElecHcalOverEcal               ,"ElecHcalOverEcal[NElec]/D");
  mtree->Branch("ElecSuperClusOverP"       ,mElecSuperClusOverP             ,"ElecSuperClusOverP[NElec]/D");
  mtree->Branch("Elecetaeta"               ,mElecetaeta                     ,"Elecetaeta[NElec]/D");
  mtree->Branch("Elecietaieta"             ,mElecietaieta                   ,"Elecietaieta[NElec]/D");
  
  
  /// PF Electrons
  mtree->Branch("NPFElec"            ,&mNPFElec                 ,  "NPFElec/I"                    );
  mtree->Branch("PFElecCharge"       ,mPFElecCharge             ,  "PFElecCharge[NPFElec]/I"      );
  mtree->Branch("PFElecIsEB"         ,mPFElecIsEB               ,  "PFElecIsEB[NPFElec]/I"        );  
  
  mtree->Branch("PFElecE"            ,mPFElecE                  ,  "PFElecE[NPFElec]/D"           );                    
  mtree->Branch("PFElecPt"           ,mPFElecPt                 ,  "PFElecPt[NPFElec]/D"          );                  
  mtree->Branch("PFElecPx"           ,mPFElecPx                 ,  "PFElecPx[NPFElec]/D"          );                  
  mtree->Branch("PFElecPy"           ,mPFElecPy                 ,  "PFElecPy[NPFElec]/D"          );                  
  mtree->Branch("PFElecPz"           ,mPFElecPz                 ,  "PFElecPz[NPFElec]/D"          );                  
  mtree->Branch("PFElecEta"          ,mPFElecEta                ,  "PFElecEta[NPFElec]/D"         );                
  mtree->Branch("PFElecPhi"          ,mPFElecPhi                ,  "PFElecPhi[NPFElec]/D"         );                
  mtree->Branch("PFElecCharHadIso"   ,mPFElecCharHadIso         ,  "PFElecCharHadIso[NPFElec]/D"  );  
  mtree->Branch("PFElecPhoIso"       ,mPFElecPhoIso             ,  "PFElecPhoIso[NPFElec]/D"      );          
  mtree->Branch("PFElecNeuHadIso"    ,mPFElecNeuHadIso          ,  "PFElecNeuHadIso[NPFElec]/D"   );    
  mtree->Branch("PFElecMva"          ,mPFElecMva                ,  "PFElecMva[NPFElec]/D"         ); 
  mtree->Branch("PFElecEffArea"      ,mPFElecEffArea            ,  "PFElecEffArea[NPFElec]/D"     );

  mtree->Branch("PFElecdxy"          ,mPFElecdxy                ,  "PFElecdxy[NPFElec]/D"         );                
  mtree->Branch("PFElecdz"           ,mPFElecdz                 ,  "PFElecdz[NPFElec]/D"          );                  
  mtree->Branch("PFElecHadOverEm"    ,mPFElecHadOverEm          ,  "PFElecHadOverEm[NPFElec]/D"   );    
  mtree->Branch("PFElecHcalOverEm"   ,mPFElecHcalOverEm         ,  "PFElecHcalOverEm[NPFElec]/D"  );  
  mtree->Branch("PFElecSupClusOverP" ,mPFElecSupClusOverP       ,  "PFElecSupClusOverP[NPFElec]/D");
  mtree->Branch("PFElecInnerHits"    ,mPFElecInnerHits          ,  "PFElecInnerHits[NPFElec]/D"   );    
  mtree->Branch("PFElecConvDist"     ,mPFElecConvDist           ,  "PFElecConvDist[NPFElec]/D"    );      
  mtree->Branch("PFElecConvDcot"     ,mPFElecConvDcot           ,  "PFElecConvDcot[NPFElec]/D"    );
  
  mtree->Branch("PFElecEcalDrivenSeed"      ,mPFElecEcalDrivenSeed       ,  "PFElecEcalDrivenSeed[NPFElec]/I"       );
  mtree->Branch("PFElecdB"                  ,mPFElecdB                   ,  "PFElecdB[NPFElec]/I"                 );
  mtree->Branch("PFElecNumOfValidHits"      ,mPFElecNumOfValidHits       ,  "PFElecNumOfValidHits[NPFElec]/I"     );
  mtree->Branch("PFElecdr03HcalTowerSumEt"  ,mPFElecdr03HcalTowerSumEt   ,  "PFElecdr03HcalTowerSumEt[NPFElec]/D" );
  mtree->Branch("PFElecdr03EcalRecHitSumEt" ,mPFElecdr03EcalRecHitSumEt  ,  "PFElecdr03EcalRecHitSumEt[NPFElec]/D");
  mtree->Branch("PFElecdr03TkSumPt"         ,mPFElecdr03TkSumPt          ,  "PFElecdr03TkSumPt[NPFElec]/D"        );
  mtree->Branch("PFElecNormChi2"            ,mPFElecNormChi2             ,  "PFElecNormChi2[NPFElec]/D"           );
  mtree->Branch("PFElecfbrem"               ,mPFElecfbrem                ,  "PFElecfbrem[NPFElec]/D"              );
  mtree->Branch("PFElecDEtaSuTrAtVtx"       ,mPFElecDEtaSuTrAtVtx        ,  "PFElecDEtaSuTrAtVtx[NPFElec]/D"      );
  mtree->Branch("PFElecDPhiSuTrAtVtx"       ,mPFElecDPhiSuTrAtVtx        ,  "PFElecDPhiSuTrAtVtx[NPFElec]/D"      );
  mtree->Branch("PFElecHadronicOverEm"      ,mPFElecHadronicOverEm       ,  "PFElecHadronicOverEm[NPFElec]/D"     );
  mtree->Branch("PFElecHcalOverEcal"        ,mPFElecHcalOverEcal         ,  "PFElecHcalOverEcal[NPFElec]/D"       );
  mtree->Branch("PFElecSuperClusOverP"      ,mPFElecSuperClusOverP       ,  "PFElecSuperClusOverP[NPFElec]/D"     );
  mtree->Branch("PFElecetaeta"              ,mPFElecetaeta               ,  "PFElecetaeta[NPFElec]/D"             );
  mtree->Branch("PFElecietaieta"            ,mPFElecietaieta             ,  "PFElecietaieta[NPFElec]/D"           );
  
  mtree->Branch("PFeidLoose"             ,mPFeidLoose             ,  "PFeidLoose[NPFElec]/I"    );
  mtree->Branch("PFeidRobustHighEnergy"  ,mPFeidRobustHighEnergy  ,  "PFeidRobustHighEnergy[NPFElec]/I"    );
  mtree->Branch("PFeidRobustLoose"       ,mPFeidRobustLoose       ,  "PFeidRobustLoose[NPFElec]/I"    );
  mtree->Branch("PFeidRobustTight"       ,mPFeidRobustTight       ,  "PFeidRobustTight[NPFElec]/I"    );
  mtree->Branch("PFeidTight"             ,mPFeidTight             ,  "PFeidTight[NPFElec]/I"    );
  mtree->Branch("PFevspi"                ,mPFevspi                ,  "PFevspi[NPFElec]/I"    );
  mtree->Branch("PFevsmu"                ,mPFevsmu                ,  "PFevsmu[NPFElec]/I"    );
  
  
  /// Taus
  mtree->Branch("NTau"                                               ,&mNTau                                              ,"NTau/I");
  mtree->Branch("TauE"                                               ,mTauE                                               ,"TauE[NTau]/D" );
  mtree->Branch("TauPt"                                              ,mTauPt                                              ,"TauPt[NTau]/D" );
  mtree->Branch("TauPx"                                              ,mTauPx                                              ,"TauPx[NTau]/D" );
  mtree->Branch("TauPy"                                              ,mTauPy                                              ,"TauPy[NTau]/D" );
  mtree->Branch("TauPz"                                              ,mTauPz                                              ,"TauPz[NTau]/D" );
  mtree->Branch("TauEta"                                             ,mTauEta                                             ,"TauEta[NTau]/D" );
  mtree->Branch("TauPhi"                                             ,mTauPhi                                             ,"TauPhi[NTau]/D" );
  mtree->Branch("TauCharge"                                          ,mTauCharge                                          ,"TauCharge[NTau]/I");
  //
  mtree->Branch("TauEtaEtaMoment"                                    ,mTauEtaEtaMoment                                    ,"TauEtaEtaMoment[NTau]/D" );
  mtree->Branch("TauPhiPhiMoment"                                    ,mTauPhiPhiMoment                                    ,"TauPhiPhiMoment[NTau]/D" );
  mtree->Branch("TauEtaPhiMoment"                                    ,mTauEtaPhiMoment                                    ,"TauEtaPhiMoment[NTau]/D" );
  //
  mtree->Branch("TauLeadPFChargedHadrCandsignedSipt"                 ,mTauLeadPFChargedHadrCandsignedSipt                 ,"TauLeadPFChargedHadrCandsignedSipt[NTau]/D" );
  mtree->Branch("TauIsoPFChargedHadrCandsPtSum"                      ,mTauIsoPFChargedHadrCandsPtSum                      ,"TauIsoPFChargedHadrCandsPtSum[NTau]/D" );
  mtree->Branch("TauIsoPFGammaCandsEtSum"                            ,mTauIsoPFGammaCandsEtSum                            ,"TauIsoPFGammaCandsEtSum[NTau]/D" );
  mtree->Branch("TauMaximumHCALPFClusterEt"                          ,mTauMaximumHCALPFClusterEt                          ,"TauMaximumHCALPFClusterEt[NTau]/D" );
  mtree->Branch("TauEmFraction"                                      ,mTauEmFraction                                      ,"TauEmFraction[NTau]/D" );
  mtree->Branch("TauHcalTotOverPLead"                                ,mTauHcalTotOverPLead                                ,"TauHcalTotOverPLead[NTau]/D" );
  mtree->Branch("TauHcalMaxOverPLead"                                ,mTauHcalMaxOverPLead                                ,"TauHcalMaxOverPLead[NTau]/D" );
  mtree->Branch("TauHcal3x3OverPLead"                                ,mTauHcal3x3OverPLead                                ,"TauHcal3x3OverPLead[NTau]/D" );
  mtree->Branch("TauEcalStripSumEOverPLead"                          ,mTauEcalStripSumEOverPLead                          ,"TauEcalStripSumEOverPLead[NTau]/D" );
  mtree->Branch("TauBremsRecoveryEOverPLead"                         ,mTauBremsRecoveryEOverPLead                         ,"TauBremsRecoveryEOverPLead[NTau]/D" );
  mtree->Branch("TauElectronPreIDOutput"                             ,mTauElectronPreIDOutput                             ,"TauElectronPreIDOutput[NTau]/D" );
  mtree->Branch("TauElectronPreIDDecision"                           ,mTauElectronPreIDDecision                           ,"TauElectronPreIDDecision[NTau]/D" );
  mtree->Branch("TauCaloComp"                                        ,mTauCaloComp                                        ,"TauCaloComp[NTau]/D" );
  mtree->Branch("TauSegComp"                                         ,mTauSegComp                                         ,"TauSegComp[NTau]/D" );
  mtree->Branch("TauMuonDecision"                                    ,mTauMuonDecision                                    ,"TauMuonDecision[NTau]/D" );
  //
  mtree->Branch("TausignalPFChargedHadrCands"                        ,mTausignalPFChargedHadrCands                        ,"TausignalPFChargedHadrCands[NTau]/D" );
  mtree->Branch("TausignalPFGammaCands"                              ,mTausignalPFGammaCands                              ,"TausignalPFGammaCands[NTau]/D" );
  //
  mtree->Branch("TauDisAgainstElectronDeadECAL"                      ,mTauDisAgainstElectronDeadECAL                      ,"TauDisAgainstElectronDeadECAL[NTau]/D");
  mtree->Branch("TauDisAgainstElectronLoose"                         ,mTauDisAgainstElectronLoose                         ,"TauDisAgainstElectronLoose[NTau]/D");
  mtree->Branch("TauDisAgainstElectronLooseMVA2"                     ,mTauDisAgainstElectronLooseMVA2                     ,"TauDisAgainstElectronLooseMVA2[NTau]/D");
  mtree->Branch("TauDisAgainstElectronLooseMVA3"                     ,mTauDisAgainstElectronLooseMVA3                     ,"TauDisAgainstElectronLooseMVA3[NTau]/D");
  mtree->Branch("TauDisAgainstElectronMVA2category"                  ,mTauDisAgainstElectronMVA2category                  ,"TauDisAgainstElectronMVA2category[NTau]/D");
  mtree->Branch("TauDisAgainstElectronMVA2raw"                       ,mTauDisAgainstElectronMVA2raw                       ,"TauDisAgainstElectronMVA2raw[NTau]/D");
  mtree->Branch("TauDisAgainstElectronMVA3category"                  ,mTauDisAgainstElectronMVA3category                  ,"TauDisAgainstElectronMVA3category[NTau]/D");
  mtree->Branch("TauDisAgainstElectronMVA3raw"                       ,mTauDisAgainstElectronMVA3raw                       ,"TauDisAgainstElectronMVA3raw[NTau]/D");
  mtree->Branch("TauDisAgainstElectronMVA"                           ,mTauDisAgainstElectronMVA                           ,"TauDisAgainstElectronMVA[NTau]/D");
  mtree->Branch("TauDisAgainstElectronMedium"                        ,mTauDisAgainstElectronMedium                        ,"TauDisAgainstElectronMedium[NTau]/D");
  mtree->Branch("TauDisAgainstElectronMediumMVA2"                    ,mTauDisAgainstElectronMediumMVA2                    ,"TauDisAgainstElectronMediumMVA2[NTau]/D");
  mtree->Branch("TauDisAgainstElectronMediumMVA3"                    ,mTauDisAgainstElectronMediumMVA3                    ,"TauDisAgainstElectronMediumMVA3[NTau]/D");
  mtree->Branch("TauDisAgainstElectronTight"                         ,mTauDisAgainstElectronTight                         ,"TauDisAgainstElectronTight[NTau]/D");
  mtree->Branch("TauDisAgainstElectronTightMVA2"                     ,mTauDisAgainstElectronTightMVA2                     ,"TauDisAgainstElectronTightMVA2[NTau]/D");
  mtree->Branch("TauDisAgainstElectronTightMVA3"                     ,mTauDisAgainstElectronTightMVA3                     ,"TauDisAgainstElectronTightMVA3[NTau]/D");
  mtree->Branch("TauDisAgainstElectronVLooseMVA2"                    ,mTauDisAgainstElectronVLooseMVA2                    ,"TauDisAgainstElectronVLooseMVA2[NTau]/D");
  mtree->Branch("TauDisAgainstElectronVTightMVA3"                    ,mTauDisAgainstElectronVTightMVA3                    ,"TauDisAgainstElectronVTightMVA3[NTau]/D");
  mtree->Branch("TauDisAgainstMuonLoose2"                            ,mTauDisAgainstMuonLoose2                            ,"TauDisAgainstMuonLoose2[NTau]/D");
  mtree->Branch("TauDisAgainstMuonLoose"                             ,mTauDisAgainstMuonLoose                             ,"TauDisAgainstMuonLoose[NTau]/D");
  mtree->Branch("TauDisAgainstMuonMedium2"                           ,mTauDisAgainstMuonMedium2                           ,"TauDisAgainstMuonMedium2[NTau]/D");
  mtree->Branch("TauDisAgainstMuonMedium"                            ,mTauDisAgainstMuonMedium                            ,"TauDisAgainstMuonMedium[NTau]/D");
  mtree->Branch("TauDisAgainstMuonTight2"                            ,mTauDisAgainstMuonTight2                            ,"TauDisAgainstMuonTight2[NTau]/D");
  mtree->Branch("TauDisAgainstMuonTight"                             ,mTauDisAgainstMuonTight                             ,"TauDisAgainstMuonTight[NTau]/D");
  mtree->Branch("TauDisByCombinedIsolationDeltaBetaCorrRaw3Hits"     ,mTauDisByCombinedIsolationDeltaBetaCorrRaw3Hits     ,"TauDisByCombinedIsolationDeltaBetaCorrRaw3Hits[NTau]/D");
  mtree->Branch("TauDisByCombinedIsolationDeltaBetaCorrRaw"          ,mTauDisByCombinedIsolationDeltaBetaCorrRaw          ,"TauDisByCombinedIsolationDeltaBetaCorrRaw[NTau]/D");
  mtree->Branch("TauDisByIsolationMVA2raw"                           ,mTauDisByIsolationMVA2raw                           ,"TauDisByIsolationMVA2raw[NTau]/D");
  mtree->Branch("TauDisByIsolationMVAraw"                            ,mTauDisByIsolationMVAraw                            ,"TauDisByIsolationMVAraw[NTau]/D");
  mtree->Branch("TauDisByLooseCombinedIsolationDeltaBetaCorr3Hits"   ,mTauDisByLooseCombinedIsolationDeltaBetaCorr3Hits   ,"TauDisByLooseCombinedIsolationDeltaBetaCorr3Hits[NTau]/D");
  mtree->Branch("TauDisByLooseCombinedIsolationDeltaBetaCorr"        ,mTauDisByLooseCombinedIsolationDeltaBetaCorr        ,"TauDisByLooseCombinedIsolationDeltaBetaCorr[NTau]/D");
  mtree->Branch("TauDisByLooseIsolationMVA2"                         ,mTauDisByLooseIsolationMVA2                         ,"TauDisByLooseIsolationMVA2[NTau]/D");
  mtree->Branch("TauDisByLooseIsolationMVA"                          ,mTauDisByLooseIsolationMVA                          ,"TauDisByLooseIsolationMVA[NTau]/D");
  mtree->Branch("TauDisByMediumCombinedIsolationDeltaBetaCorr3Hits"  ,mTauDisByMediumCombinedIsolationDeltaBetaCorr3Hits  ,"TauDisByMediumCombinedIsolationDeltaBetaCorr3Hits[NTau]/D");
  mtree->Branch("TauDisByMediumCombinedIsolationDeltaBetaCorr"       ,mTauDisByMediumCombinedIsolationDeltaBetaCorr       ,"TauDisByMediumCombinedIsolationDeltaBetaCorr[NTau]/D");
  mtree->Branch("TauDisByMediumIsolationMVA2"                        ,mTauDisByMediumIsolationMVA2                        ,"TauDisByMediumIsolationMVA2[NTau]/D");
  mtree->Branch("TauDisByMediumIsolationMVA"                         ,mTauDisByMediumIsolationMVA                         ,"TauDisByMediumIsolationMVA[NTau]/D");
  mtree->Branch("TauDisByTightCombinedIsolationDeltaBetaCorr3Hits"   ,mTauDisByTightCombinedIsolationDeltaBetaCorr3Hits   ,"TauDisByTightCombinedIsolationDeltaBetaCorr3Hits[NTau]/D");
  mtree->Branch("TauDisByTightCombinedIsolationDeltaBetaCorr"        ,mTauDisByTightCombinedIsolationDeltaBetaCorr        ,"TauDisByTightCombinedIsolationDeltaBetaCorr[NTau]/D");
  mtree->Branch("TauDisByTightIsolationMVA2"                         ,mTauDisByTightIsolationMVA2                         ,"TauDisByTightIsolationMVA2[NTau]/D");
  mtree->Branch("TauDisByTightIsolationMVA"                          ,mTauDisByTightIsolationMVA                          ,"TauDisByTightIsolationMVA[NTau]/D");
  mtree->Branch("TauDisByVLooseCombinedIsolationDeltaBetaCorr"       ,mTauDisByVLooseCombinedIsolationDeltaBetaCorr       ,"TauDisByVLooseCombinedIsolationDeltaBetaCorr[NTau]/D");
  mtree->Branch("TauDisDecayModeFinding"                             ,mTauDisDecayModeFinding                             ,"TauDisDecayModeFinding[NTau]/D");
  //
  mtree->Branch("TauJetPt"                                           ,mTauJetPt                                           ,"TauJetPt[NTau]/D"); 
  mtree->Branch("TauJetEta"                                          ,mTauJetEta                                          ,"TauJetEta[NTau]/D"); 
  mtree->Branch("TauJetPhi"                                          ,mTauJetPhi                                          ,"TauJetPhi[NTau]/D");
  
  
  /// PF Taus
  mtree->Branch("NPFTau"                                             ,&mNPFTau                                            ,"NPFTau/I");
  mtree->Branch("PFTauE"                                             ,mPFTauE                                             ,"PFTauE[NPFTau]/D" );
  mtree->Branch("PFTauPt"                                            ,mPFTauPt                                            ,"PFTauPt[NPFTau]/D" );
  mtree->Branch("PFTauPx"                                            ,mPFTauPx                                            ,"PFTauPx[NPFTau]/D" );
  mtree->Branch("PFTauPy"                                            ,mPFTauPy                                            ,"PFTauPy[NPFTau]/D" );
  mtree->Branch("PFTauPz"                                            ,mPFTauPz                                            ,"PFTauPz[NPFTau]/D" );
  mtree->Branch("PFTauEta"                                           ,mPFTauEta                                           ,"PFTauEta[NPFTau]/D" );
  mtree->Branch("PFTauPhi"                                           ,mPFTauPhi                                           ,"PFTauPhi[NPFTau]/D" );
  mtree->Branch("PFTauCharge"                                        ,mPFTauCharge                                        ,"PFTauCharge[NPFTau]/I");
  //
  mtree->Branch("PFTauEtaEtaMoment"                                  ,mPFTauEtaEtaMoment                                  ,"PFTauEtaEtaMoment[NPFTau]/D" );
  mtree->Branch("PFTauPhiPhiMoment"                                  ,mPFTauPhiPhiMoment                                  ,"PFTauPhiPhiMoment[NPFTau]/D" );
  mtree->Branch("PFTauEtaPhiMoment"                                  ,mPFTauEtaPhiMoment                                  ,"PFTauEtaPhiMoment[NPFTau]/D" );
  //
  mtree->Branch("PFTauLeadPFChargedHadrCandsignedSipt"               ,mPFTauLeadPFChargedHadrCandsignedSipt               ,"PFTauLeadPFChargedHadrCandsignedSipt[NPFTau]/D" );
  mtree->Branch("PFTauIsoPFChargedHadrCandsPtSum"                    ,mPFTauIsoPFChargedHadrCandsPtSum                    ,"PFTauIsoPFChargedHadrCandsPtSum[NPFTau]/D" );
  mtree->Branch("PFTauIsoPFGammaCandsEtSum"                          ,mPFTauIsoPFGammaCandsEtSum                          ,"PFTauIsoPFGammaCandsEtSum[NPFTau]/D" );
  mtree->Branch("PFTauMaximumHCALPFClusterEt"                        ,mPFTauMaximumHCALPFClusterEt                        ,"PFTauMaximumHCALPFClusterEt[NPFTau]/D" );
  mtree->Branch("PFTauEmFraction"                                    ,mPFTauEmFraction                                    ,"PFTauEmFraction[NPFTau]/D" );
  mtree->Branch("PFTauHcalTotOverPLead"                              ,mPFTauHcalTotOverPLead                              ,"PFTauHcalTotOverPLead[NPFTau]/D" );
  mtree->Branch("PFTauHcalMaxOverPLead"                              ,mPFTauHcalMaxOverPLead                              ,"PFTauHcalMaxOverPLead[NPFTau]/D" );
  mtree->Branch("PFTauHcal3x3OverPLead"                              ,mPFTauHcal3x3OverPLead                              ,"PFTauHcal3x3OverPLead[NPFTau]/D" );
  mtree->Branch("PFTauEcalStripSumEOverPLead"                        ,mPFTauEcalStripSumEOverPLead                        ,"PFTauEcalStripSumEOverPLead[NPFTau]/D" );
  mtree->Branch("PFTauBremsRecoveryEOverPLead"                       ,mPFTauBremsRecoveryEOverPLead                       ,"PFTauBremsRecoveryEOverPLead[NPFTau]/D" );
  mtree->Branch("PFTauElectronPreIDOutput"                           ,mPFTauElectronPreIDOutput                           ,"PFTauElectronPreIDOutput[NPFTau]/D" );
  mtree->Branch("PFTauElectronPreIDDecision"                         ,mPFTauElectronPreIDDecision                         ,"PFTauElectronPreIDDecision[NPFTau]/D" );
  mtree->Branch("PFTauCaloComp"                                      ,mPFTauCaloComp                                      ,"PFTauCaloComp[NPFTau]/D" );
  mtree->Branch("PFTauSegComp"                                       ,mPFTauSegComp                                       ,"PFTauSegComp[NPFTau]/D" );
  mtree->Branch("PFTauMuonDecision"                                  ,mPFTauMuonDecision                                  ,"PFTauMuonDecision[NPFTau]/D" );
  //
  mtree->Branch("PFTausignalPFChargedHadrCands"                      ,mPFTausignalPFChargedHadrCands                      ,"PFTausignalPFChargedHadrCands[NPFTau]/D" );
  mtree->Branch("PFTausignalPFGammaCands"                            ,mPFTausignalPFGammaCands                            ,"PFTausignalPFGammaCands[NPFTau]/D" );
  //
  mtree->Branch("PFTauDisAgainstElectronDeadECAL"                    ,mPFTauDisAgainstElectronDeadECAL                    ,"PFTauDisAgainstElectronDeadECAL[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronLoose"                       ,mPFTauDisAgainstElectronLoose                       ,"PFTauDisAgainstElectronLoose[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronLooseMVA2"                   ,mPFTauDisAgainstElectronLooseMVA2                   ,"PFTauDisAgainstElectronLooseMVA2[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronLooseMVA3"                   ,mPFTauDisAgainstElectronLooseMVA3                   ,"PFTauDisAgainstElectronLooseMVA3[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronMVA2category"                ,mPFTauDisAgainstElectronMVA2category                ,"PFTauDisAgainstElectronMVA2category[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronMVA2raw"                     ,mPFTauDisAgainstElectronMVA2raw                     ,"PFTauDisAgainstElectronMVA2raw[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronMVA3category"                ,mPFTauDisAgainstElectronMVA3category                ,"PFTauDisAgainstElectronMVA3category[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronMVA3raw"                     ,mPFTauDisAgainstElectronMVA3raw                     ,"PFTauDisAgainstElectronMVA3raw[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronMVA"                         ,mPFTauDisAgainstElectronMVA                         ,"PFTauDisAgainstElectronMVA[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronMedium"                      ,mPFTauDisAgainstElectronMedium                      ,"PFTauDisAgainstElectronMedium[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronMediumMVA2"                  ,mPFTauDisAgainstElectronMediumMVA2                  ,"PFTauDisAgainstElectronMediumMVA2[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronMediumMVA3"                  ,mPFTauDisAgainstElectronMediumMVA3                  ,"PFTauDisAgainstElectronMediumMVA3[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronTight"                       ,mPFTauDisAgainstElectronTight                       ,"PFTauDisAgainstElectronTight[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronTightMVA2"                   ,mPFTauDisAgainstElectronTightMVA2                   ,"PFTauDisAgainstElectronTightMVA2[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronTightMVA3"                   ,mPFTauDisAgainstElectronTightMVA3                   ,"PFTauDisAgainstElectronTightMVA3[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronVLooseMVA2"                  ,mPFTauDisAgainstElectronVLooseMVA2                  ,"PFTauDisAgainstElectronVLooseMVA2[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstElectronVTightMVA3"                  ,mPFTauDisAgainstElectronVTightMVA3                  ,"PFTauDisAgainstElectronVTightMVA3[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstMuonLoose2"                          ,mPFTauDisAgainstMuonLoose2                          ,"PFTauDisAgainstMuonLoose2[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstMuonLoose"                           ,mPFTauDisAgainstMuonLoose                           ,"PFTauDisAgainstMuonLoose[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstMuonMedium2"                         ,mPFTauDisAgainstMuonMedium2                         ,"PFTauDisAgainstMuonMedium2[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstMuonMedium"                          ,mPFTauDisAgainstMuonMedium                          ,"PFTauDisAgainstMuonMedium[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstMuonTight2"                          ,mPFTauDisAgainstMuonTight2                          ,"PFTauDisAgainstMuonTight2[NPFTau]/D");
  mtree->Branch("PFTauDisAgainstMuonTight"                           ,mPFTauDisAgainstMuonTight                           ,"PFTauDisAgainstMuonTight[NPFTau]/D");
  mtree->Branch("PFTauDisByCombinedIsolationDeltaBetaCorrRaw3Hits"   ,mPFTauDisByCombinedIsolationDeltaBetaCorrRaw3Hits   ,"PFTauDisByCombinedIsolationDeltaBetaCorrRaw3Hits[NPFTau]/D");
  mtree->Branch("PFTauDisByCombinedIsolationDeltaBetaCorrRaw"        ,mPFTauDisByCombinedIsolationDeltaBetaCorrRaw        ,"PFTauDisByCombinedIsolationDeltaBetaCorrRaw[NPFTau]/D");
  mtree->Branch("PFTauDisByIsolationMVA2raw"                         ,mPFTauDisByIsolationMVA2raw                         ,"PFTauDisByIsolationMVA2raw[NPFTau]/D");
  mtree->Branch("PFTauDisByIsolationMVAraw"                          ,mPFTauDisByIsolationMVAraw                          ,"PFTauDisByIsolationMVAraw[NPFTau]/D");
  mtree->Branch("PFTauDisByLooseCombinedIsolationDeltaBetaCorr3Hits" ,mPFTauDisByLooseCombinedIsolationDeltaBetaCorr3Hits ,"PFTauDisByLooseCombinedIsolationDeltaBetaCorr3Hits[NPFTau]/D");
  mtree->Branch("PFTauDisByLooseCombinedIsolationDeltaBetaCorr"      ,mPFTauDisByLooseCombinedIsolationDeltaBetaCorr      ,"PFTauDisByLooseCombinedIsolationDeltaBetaCorr[NPFTau]/D");
  mtree->Branch("PFTauDisByLooseIsolationDeltaBetaCorr"              ,mPFTauDisByLooseIsolationDeltaBetaCorr              ,"PFTauDisByLooseIsolationDeltaBetaCorr[NPFTau]/D");
  mtree->Branch("PFTauDisByLooseIsolation"                           ,mPFTauDisByLooseIsolation                           ,"PFTauDisByLooseIsolation[NPFTau]/D");
  mtree->Branch("PFTauDisByLooseIsolationMVA2"                       ,mPFTauDisByLooseIsolationMVA2                       ,"PFTauDisByLooseIsolationMVA2[NPFTau]/D");
  mtree->Branch("PFTauDisByLooseIsolationMVA"                        ,mPFTauDisByLooseIsolationMVA                        ,"PFTauDisByLooseIsolationMVA[NPFTau]/D");
  mtree->Branch("PFTauDisByMediumCombinedIsolationDeltaBetaCorr3Hits",mPFTauDisByMediumCombinedIsolationDeltaBetaCorr3Hits,"PFTauDisByMediumCombinedIsolationDeltaBetaCorr3Hits[NPFTau]/D");
  mtree->Branch("PFTauDisByMediumCombinedIsolationDeltaBetaCorr"     ,mPFTauDisByMediumCombinedIsolationDeltaBetaCorr     ,"PFTauDisByMediumCombinedIsolationDeltaBetaCorr[NPFTau]/D");
  mtree->Branch("PFTauDisByMediumIsolationDeltaBetaCorr"             ,mPFTauDisByMediumIsolationDeltaBetaCorr             ,"PFTauDisByMediumIsolationDeltaBetaCorr[NPFTau]/D");
  mtree->Branch("PFTauDisByMediumIsolation"                          ,mPFTauDisByMediumIsolation                          ,"PFTauDisByMediumIsolation[NPFTau]/D");
  mtree->Branch("PFTauDisByMediumIsolationMVA2"                      ,mPFTauDisByMediumIsolationMVA2                      ,"PFTauDisByMediumIsolationMVA2[NPFTau]/D");
  mtree->Branch("PFTauDisByMediumIsolationMVA"                       ,mPFTauDisByMediumIsolationMVA                       ,"PFTauDisByMediumIsolationMVA[NPFTau]/D");
  mtree->Branch("PFTauDisByTightCombinedIsolationDeltaBetaCorr3Hits" ,mPFTauDisByTightCombinedIsolationDeltaBetaCorr3Hits ,"PFTauDisByTightCombinedIsolationDeltaBetaCorr3Hits[NPFTau]/D");
  mtree->Branch("PFTauDisByTightCombinedIsolationDeltaBetaCorr"      ,mPFTauDisByTightCombinedIsolationDeltaBetaCorr      ,"PFTauDisByTightCombinedIsolationDeltaBetaCorr[NPFTau]/D");
  mtree->Branch("PFTauDisByTightIsolationDeltaBetaCorr"              ,mPFTauDisByTightIsolationDeltaBetaCorr              ,"PFTauDisByTightIsolationDeltaBetaCorr[NPFTau]/D");
  mtree->Branch("PFTauDisByTightIsolation"                           ,mPFTauDisByTightIsolation                           ,"PFTauDisByTightIsolation[NPFTau]/D");
  mtree->Branch("PFTauDisByTightIsolationMVA2"                       ,mPFTauDisByTightIsolationMVA2                       ,"PFTauDisByTightIsolationMVA2[NPFTau]/D");
  mtree->Branch("PFTauDisByTightIsolationMVA"                        ,mPFTauDisByTightIsolationMVA                        ,"PFTauDisByTightIsolationMVA[NPFTau]/D");
  mtree->Branch("PFTauDisByVLooseCombinedIsolationDeltaBetaCorr"     ,mPFTauDisByVLooseCombinedIsolationDeltaBetaCorr     ,"PFTauDisByVLooseCombinedIsolationDeltaBetaCorr[NPFTau]/D");
  mtree->Branch("PFTauDisByVLooseIsolationDeltaBetaCorr"             ,mPFTauDisByVLooseIsolationDeltaBetaCorr             ,"PFTauDisByVLooseIsolationDeltaBetaCorr[NPFTau]/D");
  mtree->Branch("PFTauDisByVLooseIsolation"                          ,mPFTauDisByVLooseIsolation                          ,"PFTauDisByVLooseIsolation[NPFTau]/D");
  mtree->Branch("PFTauDisDecayModeFinding"                           ,mPFTauDisDecayModeFinding                           ,"PFTauDisDecayModeFinding[NPFTau]/D");
  //
  mtree->Branch("PFTauJetPt"                                         ,mPFTauJetPt                                         ,"PFTauJetPt[NPFTau]/D"); 
  mtree->Branch("PFTauJetEta"                                        ,mPFTauJetEta                                        ,"PFTauJetEta[NPFTau]/D"); 
  mtree->Branch("PFTauJetPhi"                                        ,mPFTauJetPhi                                        ,"PFTauJetPhi[NPFTau]/D");
  
  
  /// Photons
  mtree->Branch("NPhot"             ,&mNPhot            ,"NPhot/I");
  mtree->Branch("PhotE"             ,mPhotE             ,"PhotE[NPhot]/D" );
  mtree->Branch("PhotPt"            ,mPhotPt            ,"PhotPt[NPhot]/D" );
  mtree->Branch("PhotPx"            ,mPhotPx            ,"PhotPx[NPhot]/D" );
  mtree->Branch("PhotPy"            ,mPhotPy            ,"PhotPy[NPhot]/D" );
  mtree->Branch("PhotPz"            ,mPhotPz            ,"PhotPz[NPhot]/D" );
  mtree->Branch("PhotEta"           ,mPhotEta           ,"PhotEta[NPhot]/D" );
  mtree->Branch("PhotPhi"           ,mPhotPhi           ,"PhotPhi[NPhot]/D" );
  mtree->Branch("PhotE1x5"          ,mPhotE1x5          ,"PhotE1x5[NPhot]/D" );
  mtree->Branch("PhotE2x5"          ,mPhotE2x5          ,"PhotE2x5[NPhot]/D" );
  mtree->Branch("PhotE5x5"          ,mPhotE5x5          ,"PhotE5x5[NPhot]/D" );
  mtree->Branch("PhotSigEta"        ,mPhotSigEta        ,"PhotSigEta[NPhot]/D" );
  mtree->Branch("PhotSigPhi"        ,mPhotSigPhi        ,"PhotSigPhi[NPhot]/D" );
  mtree->Branch("PhotEcalIso04"     ,mPhotEcalIso04     ,"PhotEcalIso04[NPhot]/D" );
  mtree->Branch("PhotHcalIso04"     ,mPhotHcalIso04     ,"PhotHcalIso04[NPhot]/D" );
  mtree->Branch("PhotTrackIso04"    ,mPhotTrackIso04    ,"PhotTrackIso04[NPhot]/D" );
  mtree->Branch("PhotHasPixSeed"    ,mPhotHasPixSeed    ,"PhotHasPixSeed[NPhot]/D" );
  mtree->Branch("PhotIsPhot"        ,mPhotIsPhot        ,"PhotIsPhot[NPhot]/D" );
  	
  
  /// Primary Vertices
  mtree->Branch("NPV"         ,&mNPV         ,"NPV/I");
  mtree->Branch("PVx"         ,mPVx          ,"PVx[NPV]/D" );
  mtree->Branch("PVy"         ,mPVy          ,"PVy[NPV]/D" );
  mtree->Branch("PVz"         ,mPVz          ,"PVz[NPV]/D" );
  mtree->Branch("PVchi2"      ,mPVchi2       ,"PVchi2[NPV]/D" );
  mtree->Branch("PVndof"      ,mPVndof       ,"PVndof[NPV]/D" );
  mtree->Branch("PVntracks"   ,mPVntracks    ,"PVntracks[NPV]/I" );
  
  if(isMCTag){
    /// Gen Particle
    mtree->Branch("NGenPar"        ,&mNGenPar     , "NGenPar/I" );
    mtree->Branch("GenParId"       ,mGenParId     , "GenParId[NGenPar]/I");
    mtree->Branch("GenParStatus"   ,mGenParStatus , "GenParStatus[NGenPar]/I");
    mtree->Branch("GenParE"        ,mGenParE      , "GenParE[NGenPar]/D");
    mtree->Branch("GenParPx"       ,mGenParPx     , "GenParPx[NGenPar]/D");
    mtree->Branch("GenParPy"       ,mGenParPy     , "GenParPy[NGenPar]/D");
    mtree->Branch("GenParPz"       ,mGenParPz     , "GenParPz[NGenPar]/D");
    mtree->Branch("GenParEta"      ,mGenParEta    , "GenParEta[NGenPar]/D");
    mtree->Branch("GenParPhi"      ,mGenParPhi    , "GenParPhi[NGenPar]/D");
    mtree->Branch("GenParCharge"   ,mGenParCharge , "GenParCharge[NGenPar]/I");
    mtree->Branch("GenParPt"       ,mGenParPt     , "GenParPt[NGenPar]/D");
    mtree->Branch("GenParMass"     ,mGenParMass   , "GenParMass[NGenPar]/D");
    mtree->Branch("GenParDoughterOf"   ,mGenParDoughterOf , "GenParDoughterOf[NGenPar]/I");
    
    mtree->Branch("GenParMother1"   ,mGenParMother1 , "GenParMother1[NGenPar]/I");
    mtree->Branch("GenParMother2"   ,mGenParMother2 , "GenParMother2[NGenPar]/I");	
    
    mtree->Branch("GenScale", &mGenScale,     "GenScale/D");
    mtree->Branch("PDFx1",    &mPdfx1,        "PDFx1/D");
    mtree->Branch("PDFx2",    &mPdfx2,        "PDFx2/D");
    mtree->Branch("PDFf1",    &mPdff1,        "PDFf1/I");
    mtree->Branch("PDFf2",    &mPdff2,        "PDFf2/I");
    mtree->Branch("PDFscale", &mPdfscale,     "PDFscale/D");
    mtree->Branch("PDFpdf1",  &mPdfpdf1,      "PDFpdf1/D");
    mtree->Branch("PDFpdf2",  &mPdfpdf2,      "PDFpdf2/D");
    
    mtree->Branch("WTauDecayMode"     ,&mWTauDecayMode  ,"WTauDecayMode/I");
    mtree->Branch("WTauN"             ,&mWTauN          ,"WTauN/I" );
    mtree->Branch("WTauDecayId"       ,mWTauDecayId     ,"WTauDecayId[WTauN]/I");
    mtree->Branch("WTauDecayStatus"   ,mWTauDecayStatus ,"WTauDecayStatus[WTauN]/I");
    mtree->Branch("WTauDecayPt"       ,mWTauDecayPt     ,"WTauDecayPt[WTauN]/D");
    mtree->Branch("WTauDecayEta"      ,mWTauDecayEta    ,"WTauDecayEta[WTauN]/D");
    mtree->Branch("WTauDecayPhi"      ,mWTauDecayPhi    ,"WTauDecayPhi[WTauN]/D"); 
    mtree->Branch("WTauDecayMass"     ,mWTauDecayMass   ,"WTauDecayMass[WTauN]/D");
    
  }
  
  if(isSignalTag==1.)
    {
      mtree->Branch("NPDFWeights1", &mNPdfWeights1, "NPDFWeights1/I");
      mtree->Branch("PDFWeights1",  mPdfWeights1,   "PDFWeights1[NPDFWeights1]/D");
    }
  if(isSignalTag==2.)
    {
      mtree->Branch("NPDFWeights", &mNPdfWeights, "NPDFWeights/I");
      mtree->Branch("PDFWeights",  mPdfWeights,   "PDFWeights[NPDFWeights]/D");
    }
  if(isSignalTag==3.)
    {
      mtree->Branch("NPDFWeights", &mNPdfWeights, "NPDFWeights/I");
      mtree->Branch("PDFWeights",  mPdfWeights,   "PDFWeights[NPDFWeights]/D");
    }
  
  
  /// HLT
  mtree->Branch("nHLT"           ,&nHLT          ,"nHLT/I");
  mtree->Branch("HLTArray"       ,HLTArray       ,"HLTArray[nHLT]/I");
  mtree->Branch("HLTArray2"      ,HLTArray2      ,"HLTArray2[100]/I");
  mtree->Branch("HLTNames"       ,trgnm          ,"HLTNames/C");
  mtree->Branch("HLTPreScale2"   ,HLTPreScale2   ,"HLTPreScale2[100]/I");
  
  mtree->Branch("nNoiseFlag"     ,&nNoiseFlag    ,"nNoiseFlag/I");
  mtree->Branch("NoiseFlag"      ,NoiseFlag      ,"NoiseFlag[nNoiseFlag]/I"); //Before it was [10]!!
  
  
  if(!isMCTag){
    /// L1
    mtree->Branch("nL1"        ,&nL1      ,"nL1/I");
    mtree->Branch("L1Array"    ,L1Array   ,"L1Array[nL1]/I");
    
    /// L1T
    mtree->Branch("nL1T"       ,&nL1T     ,"nL1T/I");
    mtree->Branch("L1TArray"   ,L1TArray  ,"L1TArray[nL1T]/I");
  }
  
  
  ///Flags
  mtree->Branch("HCFlag"           ,&flg_hnoise     , "HCFlag/I");
  mtree->Branch("HFFlag"           ,&flg_hfbadhit   , "HFFlag/I");
  mtree->Branch("ESFlag"           ,&flg_ecalspike  , "ESFlag/I");
  mtree->Branch("BeamHaloTight"    ,&mbeamHaloTight  , "BeamHaloTight/I");
  mtree->Branch("BeamHaloLoose"    ,&mbeamHaloLoose  , "BeamHaloLoose/I");
  
  mtree->Branch("SumTrackPt"    ,&mSumTrackPt  , "SumTrackPt/D");
  
  
  ///TIV
  mtree->Branch("TIV_N",&tivN,"TIV_N/I");
  mtree->Branch("TIV",TIV,"TIV[TIV_N]/F");
  mtree->Branch("TIV_pt",TIV_pt,"TIV_pt[TIV_N]/F");
  mtree->Branch("TIV_px",TIV_px,"TIV_px[TIV_N]/F");
  mtree->Branch("TIV_py",TIV_py,"TIV_py[TIV_N]/F");
  mtree->Branch("TIV_pz",TIV_pz,"TIV_pz[TIV_N]/F");
  mtree->Branch("TIV_phi",TIV_phi,"TIV_phi[TIV_N]/F");
  mtree->Branch("TIV_eta",TIV_eta,"TIV_eta[TIV_N]/F");
  mtree->Branch("TIV_dsz",TIV_dsz,"TIV_dsz[TIV_N]/F");
  mtree->Branch("TIV_dxy",TIV_dxy,"TIV_dxy[TIV_N]/F");
  mtree->Branch("TIV_d0",TIV_d0,"TIV_d0[TIV_N]/F");
  mtree->Branch("TIV_dz",TIV_dz,"TIV_dz[TIV_N]/F");
  
  mtree->Branch("TIV_dsz_corr",TIV_dsz_corr,"TIV_dsz_corr[TIV_N]/F");
  mtree->Branch("TIV_dxy_corr",TIV_dxy_corr,"TIV_dxy_corr[TIV_N]/F");
  mtree->Branch("TIV_d0_corr",TIV_d0_corr,"TIV_d0_corr[TIV_N]/F");
  mtree->Branch("TIV_dz_corr",TIV_dz_corr,"TIV_dz_corr[TIV_N]/F");
  mtree->Branch("TIV_dR",TIV_dR,"TIV_dR[TIV_N]/F");
  mtree->Branch("TIV_lead",TIV_lead,"TIV_lead[TIV_N]/I");
  
  mtree->Branch("LowTIV",&LowTIV,"LowTIV/F");
}

// ------------ method called once each job just after ending the event loop  ------------
void NtupleAnalyzer::endJob() 
{

}


//define this as a plug-in
DEFINE_FWK_MODULE(NtupleAnalyzer);
