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


#define TIVMAX  10000
#define MAXMUON 30
#define MAXTAU  50
#define MAXELEC 30
#define MAXJET  30
#define MAXPHOT 30
#define MAXGENPAR  1000

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"


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

		InputTag TriggerTag;


		double JetPtCutTag, JetEtaCutTag, WeightTag;
		bool isMCTag;
		double isSignalTag;


		///HLT  L1, L1Tech
		int nHLT, nL1, nL1T, nNoiseFlag; 
		int HLTArray[500], L1Array[128], L1TArray[64],  HLTArray2[100], HLTPreScale[500], HLTPreScale2[100], NoiseFlag[10]; 
		char trgnm[15000];
		TriggerNames trgnm_, trgnm2_;
		int nhlt;

		
		///Run event Lumi BX
		int  mRun, mLumi,mBX, mnpvm1, mnpv0, mnpvp1;
		long  mEvent;

		///Noise Flags
		int flg_hnoise, flg_hfbadhit, flg_ecalspike , mbeamHaloLoose, mbeamHaloTight;
		double  mSumTrackPt;


		///Gen Particle 	
		int     mNGenPar;
		int     mGenParId[MAXGENPAR]; 
		int     mGenParStatus[MAXGENPAR]; 
		int     mGenParMother[MAXGENPAR]; 
		int     mGenParCharge[MAXGENPAR];
		int     mGenParDoughterOf[MAXGENPAR]; 
		int     mGenParMother1[MAXGENPAR]; 
		int     mGenParMother2[MAXGENPAR];

		double  mGenParE[MAXGENPAR];
		double  mGenParPt[MAXGENPAR]; 
		double  mGenParPx[MAXGENPAR]; 
		double  mGenParPy[MAXGENPAR]; 
		double  mGenParPz[MAXGENPAR]; 
		double  mGenParEta[MAXGENPAR]; 
		double  mGenParPhi[MAXGENPAR]; 
		double  mGenParMass[MAXGENPAR];

		double  mGenScale;
		double  mPdfscale;
		double  mPdfx1; 
		double  mPdfx2; 
		double  mPdfpdf1;
		double  mPdfpdf2; 
		double  mPdfWeights[150] , mPdfWeights1[150];
		
		int     mPdff1; 
		int     mPdff2;	
		int     mNPdfWeights, mNPdfWeights1;

		
		///------------------------Jet Algos------------------------------------------------------
		
		///Calo AK5 Jets
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


		///PF AK5 Jets
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
		double  mPFAK5JetBtagTkCountHighEff[MAXJET];
		double  mPFAK5JetBTagSimpleSecVtx[MAXJET];
		double  mPFAK5JetBTagCombSecVtx[MAXJET] ; 	
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

		
		///Mets
		int mNMet;
		double mMetPt[30], mMetPhi[30],mMetSumEt[30],mMetPx[30],mMetPy[30],mMetSign[30];

		///MHTs
		double mMHTPt, mMHTPhi,mMHTPx,mMHTPy,mMHTSign;
		
		
		///------------MUONS-------------------------------------------
		int     mNMuon;
		double	mMuonPt[MAXMUON]             ;
		double	mMuonEt[MAXMUON]             ;
		double	mMuonE[MAXMUON]              ;
		double	mMuonPx[MAXMUON]             ;
		double	mMuonPy[MAXMUON]             ;
		double	mMuonPz[MAXMUON]             ;
		double	mMuonEta[MAXMUON]            ;
		double	mMuonPhi[MAXMUON]            ;
		double	mMuonCharge[MAXMUON]         ;  			  
		int	    mMuonIsGlobal[MAXMUON]       ;
		int	    mMuonIsStandAlone[MAXMUON]   ;
		int	    mMuonIsTracker[MAXMUON]      ;			  
		double	mMuonSumPtDR03[MAXMUON]      ;
		double	mMuonSumPtDR05[MAXMUON]      ;
		double	mMuonEmEtDR03[MAXMUON]       ;
		double	mMuonHadEtDR03[MAXMUON]      ;
		int     mMuonNumOfMatches[MAXMUON]   ;

		//comb muon	
		double	mMuonCombChi2Norm[MAXMUON]   ;  
		int	    mMuonCombValidHits[MAXMUON]  ;  
		int	    mMuonCombLostHits[MAXMUON]   ;
		double	mMuonCombPt[MAXMUON]         ; 
		double	mMuonCombPz[MAXMUON]         ; 
		double	mMuonCombP[MAXMUON]          ; 
		double	mMuonCombEta[MAXMUON]        ; 
		double	mMuonCombPhi[MAXMUON]        ; 
		double	mMuonCombChi2[MAXMUON]       ; 
		double	mMuonCombCharge[MAXMUON]     ; 
		double	mMuonCombQOverPError[MAXMUON]; 
		double	mMuonCombNdof[MAXMUON]       ; 
		double	mMuonCombVx[MAXMUON]         ; 
		double	mMuonCombVy[MAXMUON]         ; 
		double	mMuonCombVz[MAXMUON]         ; 
		double	mMuonCombD0[MAXMUON]         ; 
		double	mMuonCombDz[MAXMUON]         ; 
		
		// stand alone muon	
		double	mMuonStandChi2Norm[MAXMUON]    ;
		int	    mMuonStandValidHits[MAXMUON]   ;
		int	    mMuonStandLostHits[MAXMUON]    ;
		double	mMuonStandPt[MAXMUON]          ;
		double	mMuonStandPz[MAXMUON]          ;
		double	mMuonStandP[MAXMUON]           ;
		double	mMuonStandEta[MAXMUON]         ;
		double	mMuonStandPhi[MAXMUON]         ;
		double	mMuonStandChi2[MAXMUON]        ;
		double	mMuonStandCharge[MAXMUON]      ;
		double	mMuonStandQOverPError[MAXMUON] ;

		// track muon	
		double	mMuonTrkChi2Norm[MAXMUON]   ; 
		int	    mMuonTrkValidHits[MAXMUON]  ;
		int	    mMuonTrkLostHits[MAXMUON]   ;
		double	mMuonTrkPt[MAXMUON]         ; 
		double	mMuonTrkPz[MAXMUON]         ; 
		double	mMuonTrkP[MAXMUON]          ; 
		double	mMuonTrkEta[MAXMUON]        ; 
		double	mMuonTrkPhi[MAXMUON]        ; 
		double	mMuonTrkChi2[MAXMUON]       ; 
		double	mMuonTrkCharge[MAXMUON]     ; 
		double	mMuonTrkQOverPError[MAXMUON]; 
		double	mMuonTrkDxy[MAXMUON]        ; 
		int     mMuonTrkNumOfValidPixHits[MAXMUON] ;
		
		///------------PF MUONS-------------------------------------------
		
		int     mNPFMuon;
		double	mPFMuonPt[MAXMUON];               
		double	mPFMuonEt[MAXMUON];               
		double	mPFMuonE[MAXMUON];                
		double	mPFMuonPx[MAXMUON];               
		double	mPFMuonPy[MAXMUON];               
		double	mPFMuonPz[MAXMUON];               
		double	mPFMuonEta[MAXMUON];              
		double	mPFMuonPhi[MAXMUON];              
		int     mPFMuonCharge[MAXMUON];           

		int     mPFMuonIsGlobal[MAXMUON];         
		int     mPFMuonIsStandAlone[MAXMUON];     
		int     mPFMuonIsTracker[MAXMUON];        

		double	mPFMuonChargedHadronIso[MAXMUON]; 
		double	mPFMuonPhotonIso[MAXMUON];        
		double	mPFMuonNeutralHadronIso[MAXMUON]; 
		int     mPFMuonisGMPT[MAXMUON];           
		int     mPFMuonNumOfMatches[MAXMUON];     

		double	mPFMuoninnertrackPt[MAXMUON];     
		int     mPFMuonnValidHits[MAXMUON];       
		int     mPFMuonnValidPixelHits[MAXMUON];  
		double	mPFMuondxy[MAXMUON];              
		double	mPFMuondz[MAXMUON];               

		double	mPFMuonCombChi2Norm[MAXMUON];    
		int     mPFMuonCombValidHits[MAXMUON];   
		int     mPFMuonCombLostHits[MAXMUON];    
		double	mPFMuonCombPt[MAXMUON];          
		double	mPFMuonCombPz[MAXMUON];          
		double	mPFMuonCombP[MAXMUON];           
		double	mPFMuonCombEta[MAXMUON];         
		double	mPFMuonCombPhi[MAXMUON];         
		double	mPFMuonCombChi2[MAXMUON];        
		double	mPFMuonCombCharge[MAXMUON];      
		double	mPFMuonCombQOverPError[MAXMUON]; 	
		double	mPFMuonCombNdof[MAXMUON];        
		double	mPFMuonCombVx[MAXMUON];          
		double	mPFMuonCombVy[MAXMUON];          
		double	mPFMuonCombVz[MAXMUON];          
		double	mPFMuonCombD0[MAXMUON];          
		double	mPFMuonCombDz[MAXMUON];          


		double	mPFMuonStandChi2Norm[MAXMUON];   
		int     mPFMuonStandValidHits[MAXMUON];  
		int     mPFMuonStandLostHits[MAXMUON];   
		double	mPFMuonStandPt[MAXMUON];         
		double	mPFMuonStandPz[MAXMUON];         
		double	mPFMuonStandP[MAXMUON];          
		double	mPFMuonStandEta[MAXMUON];        
		double	mPFMuonStandPhi[MAXMUON];        
		double	mPFMuonStandChi2[MAXMUON];       
		double	mPFMuonStandCharge[MAXMUON];     
		double	mPFMuonStandQOverPError[MAXMUON];

		double	mPFMuonTrkChi2Norm[MAXMUON];    
		int     mPFMuonTrkValidHits[MAXMUON];   
		int     mPFMuonTrkLostHits[MAXMUON];    
		double	mPFMuonTrkPt[MAXMUON];          
		double	mPFMuonTrkPz[MAXMUON];          
		double	mPFMuonTrkP[MAXMUON];           
		double	mPFMuonTrkEta[MAXMUON];         
		double	mPFMuonTrkPhi[MAXMUON];         
		double	mPFMuonTrkChi2[MAXMUON];        
		double	mPFMuonTrkCharge[MAXMUON];      
		double	mPFMuonTrkQOverPError[MAXMUON]; 
		double	mPFMuonTrkDxy[MAXMUON];         
		double	mPFMuonTrkNumOfValidPixHits[MAXMUON];
             
	
		
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
		int    mNPFElec;
		int    mPFElecCharge[MAXELEC]; 
		int    mPFElecIsEB[MAXELEC];  
		
		double mPFElecE[MAXELEC];           
		double mPFElecPt[MAXELEC];          
		double mPFElecPx[MAXELEC];          
		double mPFElecPy[MAXELEC];          
		double mPFElecPz[MAXELEC];          
		double mPFElecEta[MAXELEC];         
		double mPFElecPhi[MAXELEC];         
		double mPFElecCharHadIso[MAXELEC];  
		double mPFElecPhoIso[MAXELEC];      
		double mPFElecNeuHadIso[MAXELEC];   
		double mPFElecMva[MAXELEC];           
		double mPFElecdxy[MAXELEC];         
		double mPFElecdz[MAXELEC];          
		double mPFElecHadOverEm[MAXELEC];   
		double mPFElecHcalOverEm[MAXELEC];  
		double mPFElecSupClusOverP[MAXELEC];
		double mPFElecInnerHits[MAXELEC];   
		double mPFElecConvDist[MAXELEC];    
		double mPFElecConvDcot[MAXELEC];

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
		
		int mPFeidLoose[MAXELEC];              
		int mPFeidRobustHighEnergy[MAXELEC];   
		int mPFeidRobustLoose[MAXELEC];        
		int mPFeidRobustTight[MAXELEC];        
		int mPFeidTight[MAXELEC];              
		int mPFevspi[MAXELEC];                 
		int mPFevsmu[MAXELEC];                 



		///-------------Taus--------------------------------------------------
		
		int     mNTau;
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
			
		double  mTauTracksInvariantMass[MAXTAU];
		double  mTauSignalTracksInvariantMass[MAXTAU];
		double  mTauMaximumHCALhitEt[MAXTAU];
		double  mTauIsolationECALhitsEtSum[MAXTAU];
		double  mTauIsolationTracksPtSum[MAXTAU];
		double  mTauLeadTrackHCAL3x3hottesthitDEta[MAXTAU];
		double  mTauLeadTrackHCAL3x3hitsEtSum[MAXTAU];
		double  mTauLeadTracksignedSipt[MAXTAU];

		
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

		double mPFTauLeadTrackPtCut[MAXTAU];             
		double mPFTauByIso[MAXTAU];
		double mPFTauByTaNCfrHalfPercent[MAXTAU];

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
		
		
		double	mPVx[40], mPVy[40], mPVz[40] , mPVchi2[40], mPVndof[40] ; 
		int	mPVntracks[40], mNPV;


		///TIV
		float TIV[TIVMAX];
		int tivN;
		double tiv_ltrack_thr_, tiv_strack_thr_, tiv_cone_, tiv_inner_cone_;
		double tiv_dz_thr_, tiv_dxy_thr_;
		float TIV_pt[TIVMAX],TIV_eta[TIVMAX],TIV_phi[TIVMAX],TIV_px[TIVMAX],TIV_py[TIVMAX],TIV_pz[TIVMAX];
		float TIV_dxy[TIVMAX], TIV_dsz[TIVMAX], TIV_dR[TIVMAX], TIV_dz[TIVMAX], TIV_d0[TIVMAX];
		float TIV_dxy_corr[TIVMAX], TIV_dsz_corr[TIVMAX], TIV_dz_corr[TIVMAX], TIV_d0_corr[TIVMAX];

		int TIV_lead[TIVMAX];
		
		float LowTIV;
		
		///Tracks
		edm::InputTag Tracks_;
		
		int DEBUG;

		///Calo Tower
		//double CaloTowerEt[30]  CaloTowerPhi[30]; 
		double mCaloTowerdEx, mCaloTowerdEy;

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

	///TIV
	tiv_ltrack_thr_ = iConfig.getParameter<double>("TIV_ltrack_thr");
	tiv_strack_thr_ = iConfig.getParameter<double>("TIV_strack_thr");
	tiv_dz_thr_     = iConfig.getParameter<double>("TIV_dz_thr");
	tiv_dxy_thr_    = iConfig.getParameter<double>("TIV_dxy_thr");
	tiv_cone_       = iConfig.getParameter<double>("TIV_cone_thr");
	tiv_inner_cone_ = iConfig.getParameter<double>("TIV_inner_cone_thr");
	Tracks_         = iConfig.getUntrackedParameter<edm::InputTag>("Tracks");

	
	DEBUG=0;
  

}


NtupleAnalyzer::~NtupleAnalyzer()
{

}



// ------------ method called to for each event  ------------

void NtupleAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
//         Handle< View<pat::MET> > PFMetHand2;
//         iEvent.getByLabel("patMETsAK5Calo",PFMetHand2);
//         const View<pat::MET> & pfmets2 = *PFMetHand2;
// 
//         if(pfmets2[0].uncorrectedPt(pat::MET::uncorrALL)< 60) return;

//-------------------------------------------------------------------------


	///--------------------------------------------------------------------------
	Handle<TriggerResults> hltTriggerResultHandle;
	iEvent.getByLabel( TriggerTag , hltTriggerResultHandle);

	trgnm_ = iEvent.triggerNames(*hltTriggerResultHandle);


	const TriggerResults &Hlt = *hltTriggerResultHandle;
	char tmpnm1[3000],tmpnm2[3000];
	nhlt=0;

	
	
	if (&Hlt) 
	{
		//cout <<Hlt.size()<<endl;
		//cout <<"---------------------------------"<<endl;
		nhlt = Hlt.size();
		//trgnm_.init(Hlt);


		for (int itrig = 0; itrig != nhlt; ++itrig)
		{
			string trigName=trgnm_.triggerName(itrig);

			bool accept = Hlt.accept(itrig);
			if (accept && trigName.find("HLT")!=string::npos) 
			{
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
	if (strtrg.find("HLT_MET120")!=string::npos ||
        strtrg.find("HLT_MET200")!=string::npos ||
		strtrg.find("HLT_MET300")!=string::npos ||
		strtrg.find("HLT_MET400")!=string::npos ||
		strtrg.find("HLT_MonoCentralPFJet80_PFMETnoMu95_NHEF0p95")!=string::npos  ) flg_trg=1;

	if (flg_trg==0) return; 
	sprintf(trgnm,"TRG%s", tmpnm2);



	///--------------------HLTrigger---------------------------------------------
	

	int hltCount=0;

	if(!hltTriggerResultHandle.isValid()) 
	{
		cout << "invalid handle for HLT TriggerResults" << std::endl;
	} 
	else 
	{
		
		//HLTNames.init(*hltTriggerResultHandle);

		string tempnames;  
		hltCount = hltTriggerResultHandle->size();

		for(int i = 0 ; i < hltCount ; i++) 
		{
			//tempnames += HLTNames.triggerName(i) + "  ";
			HLTArray[i] = hltTriggerResultHandle->accept(i);

			//cout << i << "  " <<trgnm_.triggerName(i) << "  " << hltTriggerResultHandle->accept(i) << endl;
		}
		
		nHLT = hltCount; 

	}
	



	///--------------------------------------------------------------------------

	//TriggerNames myTrigName;
	Handle<TriggerResults> myTrig;
	iEvent.getByLabel( "TriggerResults", myTrig );
	
	int hltCount2 = myTrig->size();
	 
	for(int i = 0 ; i < hltCount2; i++)
	{
		//cout << i << "  " <<  myTrig->accept(i)  << endl;
		NoiseFlag[i] = myTrig->accept(i);
	}
	nNoiseFlag = hltCount2;




	///--------------------Run  Event Lumi Bx-----------------------------------

	mRun   = iEvent.id().run();
	mEvent = iEvent.id().event();
	mLumi  = iEvent.luminosityBlock();
	mBX    = iEvent.bunchCrossing();



	///--------------------Shuichi's correction Method for PFMET Phi----------------

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
	
		for (CaloTowerCollection::const_iterator kal=towers->begin(); kal!=towers->end(); kal++)
		{	
			// double eta   = kal->eta();
			double phi   = kal->phi();
			double theta = kal->theta();
			double e     = kal->energy();
			double et    = e*sin(theta);

			// double etEM    = (kal->emEnergy())*sin(theta);
			// double etHad   = (kal->hadEnergy())*sin(theta);

			math::PtEtaPhiMLorentzVector ct(kal->p4(vertex_));
			if(et>0.3) 
			{
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
 
       
	///-------------------PileUP Summury--------------------------------------------------
	
	if(isMCTag)
	{
		Handle<std::vector< PileupSummaryInfo > >  PupInfo;
		iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);
		
		std::vector<PileupSummaryInfo>::const_iterator PVI;
		
		int nm1 = -1; int n0 = -1; int np1 = -1;
		for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) 
		{
		
			int BX = PVI->getBunchCrossing();
			
			if(BX == -1) 
			{ 
				nm1 = PVI->getPU_NumInteractions();
			}
			if(BX == 0)
			{ 
				n0 = PVI->getPU_NumInteractions();
			}
			if(BX == 1) 
			{ 
				np1 = PVI->getPU_NumInteractions();
			}
		
		}
		//double MyWeight3D = LumiWeights_.weight3D( nm1,n0,np1);
		mnpvm1 = nm1; 
		mnpv0  = n0;
		mnpvp1 = np1;
	}

 	

	///------------AK5 Jets--------------------------------------------------------------
		
	edm::Handle<edm::View<pat::Jet> > JetHand;
	iEvent.getByLabel("cleanPatJetsAK5Calo" ,JetHand);

	int jeti=0;
	

	for(unsigned int ind=0; ind<(*JetHand).size() && ind<MAXJET; ind++)
	{ 
		
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
		for (size_t i = 0; i < tracks.size(); ++i) 
		{
			ptsum += tracks[i]->pt();
		}
		mCaloAK5TrackPt[jeti] = ptsum; 

		if(isMCTag)
		{
			if(jet.genJet()!= 0) 
			{
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
	mNCaloAK5Jets = jeti;

	///----------------------AK5 PF Jets--------------------------------------------		
	
	iEvent.getByLabel("cleanPatJetsAK5PF" ,JetHand);

	jeti=0;
	
	
	edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
        iSetup.get<JetCorrectionsRecord>().get("AK5PF",JetCorParColl);
        JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
        JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(JetCorPar);


	for(unsigned int ind=0; ind<(*JetHand).size() && ind<MAXJET; ind++)
	{ 
		
		const pat::Jet& jet2 = (*JetHand)[ind];
		const pat::Jet& jet = (*JetHand)[ind].correctedJet("Uncorrected");

		if( jet2.pt() < JetPtCutTag ) continue;

		/// default scale factor: Raw & L1 & L2 & L3
		/// http://cmslxr.fnal.gov/lxr/source/DataFormats/PatCandidates/interface/JetCorrFactors.h

		PFJetIDSelectionFunctor pfjetIDFunctorLoose(PFJetIDSelectionFunctor::FIRSTDATA, PFJetIDSelectionFunctor::LOOSE);
		PFJetIDSelectionFunctor pfjetIDFunctorTight(PFJetIDSelectionFunctor::FIRSTDATA, PFJetIDSelectionFunctor::TIGHT);
		
		mPFAK5JetIDLOOSE[jeti] = pfjetIDFunctorLoose(jet2);
		mPFAK5JetIDTIGHT[jeti] = pfjetIDFunctorTight(jet2);

		mPFAK5JetPt[jeti]      =  jet.pt();
		mPFAK5JetPx [jeti]     =  jet.momentum().X();
		mPFAK5JetPy [jeti]     =  jet.momentum().Y();
		mPFAK5JetPz [jeti]     =  jet.momentum().Z();
		mPFAK5JetE [jeti]      =  jet.energy();
		
		mPFAK5JetEta[jeti]     =  jet2.eta();
		mPFAK5JetPhi[jeti]     =  jet2.phi();		
		mPFAK5JetN90 [jeti]    =  jet2.n90();
		mPFAK5JetNumOfDaughters[jeti] = jet2.numberOfDaughters();
		
		///use uncorrected jet for jetID
		mPFAK5JetN90Hits[jeti] =  jet.jetID().n90Hits ;
		mPFAK5JetfHPD [jeti]   =  jet.jetID().fHPD ;
		mPFAK5JetfRBX [jeti]   =  jet.jetID().fRBX ;
		mPFAK5JetIDEmf[jeti]   =  jet.jetID().restrictedEMF;
		
		mPFAK5JetSigEta[jeti]  =  jet2.etaetaMoment();
		mPFAK5JetSigPhi[jeti]  =  jet2.phiphiMoment();
		mPFAK5JetPtCor[jeti]   =  jet2.pt();
		mPFAK5JetPxCor [jeti]  =  jet2.momentum().X();
		mPFAK5JetPyCor [jeti]  =  jet2.momentum().Y();
		mPFAK5JetPzCor [jeti]  =  jet2.momentum().Z();
		mPFAK5JetECor [jeti]   =  jet2.energy();
		

		mPFAK5JetNeuEmEngFrac[jeti]  = jet2.neutralEmEnergyFraction();
		mPFAK5JetChaEmEngFrac[jeti]  = jet2.chargedEmEnergyFraction();
		mPFAK5JetChaHadEngFrac[jeti] = jet2.chargedHadronEnergyFraction();
		mPFAK5JetNeuHadEngFrac[jeti] = jet2.neutralHadronEnergyFraction();

		mPFAK5JetChaMuEng[jeti]  = jet2.chargedMuEnergy();
		
		
 		mPFAK5JetMuonEng[jeti]   = jet2.muonEnergy();
 		mPFAK5JetPhotEng[jeti]   = jet2.photonEnergy();
 		mPFAK5JetElecEng[jeti]   = jet2.electronEnergy();
 		mPFAK5JetNumOfPhot[jeti] = jet2.photonMultiplicity();
 		mPFAK5JetNumOfElec[jeti] = jet2.electronMultiplicity();
 		mPFAK5JetNumOfNeuHad[jeti] = jet2.neutralHadronMultiplicity();
 		mPFAK5JetNumOfChaHad[jeti] = jet2.chargedHadronMultiplicity();
		
		
		mPFAK5JetNumOfMuon[jeti]   = jet2.muonMultiplicity();
		mPFAK5JetNumOfChaMu[jeti]  = jet2.chargedMultiplicity();
		
		mPFAK5JetNumOfNeu[jeti]  = jet2.neutralMultiplicity();
		mPFAK5JetNumOfCha[jeti]  = jet2.chargedMultiplicity();
		
		
		mPFAK5JetBtagTkCountHighEff[jeti] = jet.bDiscriminator("trackCountingHighEffBJetTags");
		mPFAK5JetBTagSimpleSecVtx[jeti]   = jet.bDiscriminator("simpleSecondaryVertexBJetTags");
		mPFAK5JetBTagCombSecVtx[jeti]     = jet.bDiscriminator("combinedSecondaryVertexBJetTags");


		///-----------Jets Uncertanity --------------------------------------------------------

		if(isMCTag)
		{
			//string JEC_PATH("CondFormats/JetMETObjects/data/");
			//edm::FileInPath fip(JEC_PATH+"Spring10_Uncertainty_AK5Calo.txt");
			//edm::FileInPath fip(JEC_PATH+"Spring10_Uncertainty_AK5PF.txt");
			// edm::FileInPath fip(JEC_PATH+"Spring10_Uncertainty_AK5JPT.txt");
		  // JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty( "/uscms_data/d2/vergili/sep/CMSSW_5_3_3_patch2/src/MonoJetAnalysis/NtupleAnalyzer/data/GR_R_42_V19_AK5PF_Uncertainty.txt" );
			jecUnc->setJetEta(jet2.eta() ); // Give rapidity of jet you want tainty on
			jecUnc->setJetPt( jet2.pt() );// Also give the corrected pt of the jet you want the uncertainty on
			// The following function gives the relative uncertainty in the jet Pt.
			// i.e. ptCorSmeared = (1 +- uncer) * ptCor  
			mPFAK5uncer[jeti] =    jecUnc->getUncertainty(true); 
			// In principle, boolean controls if uncertainty on +ve or -ve side is returned (asymmetric errors) but not yet implemented.

		}
		else
		{
			mPFAK5uncer[jeti]=0.;
		}
			
		jeti++;
	}
	mNPFAK5Jets = jeti;
	

	
	
	///---------------Calo Mets--------------------------------------------------
	
	for(int i=0; i<30; i++)
	{
	      mMetPt[i]=0; mMetPhi[i]=0; mMetSumEt[i]=0; mMetPx[i]=0; mMetPy[i]=0; mMetSign[i]=0;

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
	
     
	

	///-----------GenMET--------------------------------------------------------
			
	if(isMCTag)
	{	
		const GenMET *genmet;
		// Get Generated MET
		edm::Handle<GenMETCollection> gen;
		iEvent.getByLabel("genMetCalo", gen);
		if (!gen.isValid()) 
		{
			edm::LogInfo("OutputInfo") << " failed to retrieve data required by MET Task";
			edm::LogInfo("OutputInfo") << " MET Task cannot continue...!";
			return;
		} 
		else 
		{
			const GenMETCollection *genmetcol = gen.product();
			genmet = &(genmetcol->front());
		}  
	
		mMetPt[6]    =  genmet->pt();
		mMetPhi[6]   =  genmet->phi();
		mMetPx[6]    =  genmet->px();
		mMetPy[6]    =  genmet->py();
		mMetSumEt[6] =  genmet->sumEt();

	}
	
	///-----------PF MetsType1 Corrected----------------------------------
	
	Handle<View<pat::MET> > PFMetType1Hand;
        iEvent.getByLabel("patMETsPF",PFMetType1Hand);
	const View<pat::MET> & pfmetsType1 = *PFMetType1Hand;

	
	mMetPt[10]    = pfmetsType1[0].et();
	mMetPhi[10]   = pfmetsType1[0].phi();
	mMetPx[10]    = pfmetsType1[0].px();
	mMetPy[10]    = pfmetsType1[0].py();
	mMetSumEt[10] = pfmetsType1[0].sumEt();
	
	

	///-----------PF Mets ------------------------------------------------
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
	
	
		
	///-----------TC Mets--------------------------------------------------------
	
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
	
	
	
	
	///-----------------Pat MHT-------------------------------------------------
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
	
	
	///--------------Vertices------------------------------------------------
	reco::Vertex primaryvtx;

	Handle<reco::VertexCollection> recVtxs;
	iEvent.getByLabel("offlinePrimaryVertices",recVtxs);
	
	int  pvind=0;
	for(unsigned int ind=0;ind<recVtxs->size();ind++) 
	{
		if( !((*recVtxs)[ind].isFake()) ) 
		{
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
	
	
	///---------------BeamSpot-------------------------------------------------
	
	BeamSpot beamSpot;
	Handle<reco::BeamSpot> beamSpotHandle;
	iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);

	if ( beamSpotHandle.isValid() )
	{
		beamSpot = *beamSpotHandle;
	} 
	else
	{
		edm::LogInfo("MyAnalyzer")
		<< "No beam spot available from EventSetup \n";
	}
	math::XYZPoint point(beamSpot.x0(),beamSpot.y0(), beamSpot.z0());
	
	

	///-------------------Muons----------------------------------------------------
	
	edm::Handle<edm::View<pat::Muon> > MuonHand;
	iEvent.getByLabel("cleanPatMuons",MuonHand);
	
	int muoni=0;
	for(unsigned int ind=0; ind<(*MuonHand).size() && ind<MAXMUON; ind++)
	{ 
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
		
		mMuonIsGlobal[muoni]     = muon.isGlobalMuon();
		mMuonIsStandAlone[muoni] = muon.isStandAloneMuon();
		mMuonIsTracker[muoni]    = muon.isTrackerMuon();
		
		mMuonSumPtDR03[muoni]    = muon.isolationR03().sumPt;
		mMuonSumPtDR05[muoni]    = muon.isolationR05().sumPt;
		mMuonEmEtDR03[muoni]     = muon.isolationR03().emEt;
		mMuonHadEtDR03[muoni]    = muon.isolationR03().hadEt;
		
		mMuonNumOfMatches[muoni] = muon.numberOfMatches();
		

		if( muon.isGlobalMuon() && muon.combinedMuon().isNonnull() )
		{ 
		  
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
		else
		{
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
		
		if ( muon.standAloneMuon().isNonnull() )
		{
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
		else
		{
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
		if( muon.track().isNonnull() )
		{
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
		else
		{
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

	mNMuon=muoni;

	
	///---------------------PF Muons----------------------------------------------
	
	iEvent.getByLabel("selectedPatMuonsPF",MuonHand);
	
	muoni=0;

	for(unsigned int ind=0; ind<(*MuonHand).size() && ind<MAXMUON; ind++)
	{ 
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

		mPFMuonIsGlobal[muoni]            = muon.isGlobalMuon();
		mPFMuonIsStandAlone[muoni]        = muon.isStandAloneMuon();
		mPFMuonIsTracker[muoni]           = muon.isTrackerMuon();

		mPFMuonChargedHadronIso[muoni]    = muon.chargedHadronIso();
		mPFMuonPhotonIso[muoni]           = muon.photonIso();
		mPFMuonNeutralHadronIso[muoni]    = muon.neutralHadronIso();
		mPFMuonisGMPT[muoni]              = muon.muonID("GlobalMuonPromptTight");
		mPFMuonNumOfMatches[muoni]        = muon.numberOfMatches();

		if(muon.innerTrack().isNonnull())
		{
			mPFMuoninnertrackPt[muoni]     = muon.innerTrack()->pt();
			mPFMuonnValidHits[muoni]       = muon.innerTrack()->numberOfValidHits();
			mPFMuonnValidPixelHits[muoni]  = muon.innerTrack()->hitPattern().numberOfValidPixelHits();
			mPFMuondxy[muoni]              = muon.innerTrack()->dxy(primaryvtx.position());
			mPFMuondz[muoni]               = muon.vz() - primaryvtx.position().z();
		}
		if( muon.isGlobalMuon() && muon.combinedMuon().isNonnull() )
		{
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
		else
		{
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

		if ( muon.standAloneMuon().isNonnull() )
		{
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
		else
		{
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
		if( muon.track().isNonnull() )
		{
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
		else
		{
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
 

	

	

	///-----------------BField----------------------------------------------------

	edm::Handle<DcsStatusCollection> dcsHandle;
	iEvent.getByLabel("scalersRawToDigi", dcsHandle);

	double bField = 3.8112;

	if( !isMCTag && dcsHandle->size() > 0)
	{
		float currentToBFieldScaleFactor = 2.09237036221512717e-04;
		float  current = (*dcsHandle)[0].magnetCurrent();
		bField = current*currentToBFieldScaleFactor;
	}

	else 
	{
		edm::ESHandle<MagneticField> magneticField;
		iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
		bField = magneticField->inTesla(GlobalPoint(0.,0.,0.)).z();
	}

	edm::Handle<reco::TrackCollection> trkHandle;
	iEvent.getByLabel("generalTracks",trkHandle);

	
	///-------------------Electron--------------------------------------------------
	
	edm::Handle<edm::View<pat::Electron> > ElecHand;
	iEvent.getByLabel("cleanPatElectrons",ElecHand);
	
	int eleci=0;
	for(unsigned int ind=0; ind<(*ElecHand).size() && ind<MAXELEC; ind++)
	{ 
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
	mNElec=eleci;


	///-----------------PF Electron--------------------------------------------------

	iEvent.getByLabel("selectedPatElectronsPF",ElecHand);
	
	eleci=0;
	for(unsigned int ind=0; ind<(*ElecHand).size() && ind<MAXELEC; ind++)
	{ 
		const pat::Electron& elec = (*ElecHand)[ind];

		mPFElecE[eleci]              = elec.energy();
		mPFElecPt[eleci]             = elec.pt();
		mPFElecPx[eleci]             = elec.px();
		mPFElecPy[eleci]             = elec.py();
		mPFElecPz[eleci]             = elec.pz();
		mPFElecEta[eleci]            = elec.eta();
		mPFElecPhi[eleci]            = elec.phi();
		mPFElecCharge[eleci]         = elec.charge();
		
		mPFElecCharHadIso[eleci]     = elec.chargedHadronIso();
		mPFElecPhoIso[eleci]         = elec.photonIso();
		mPFElecNeuHadIso[eleci]      = elec.neutralHadronIso();
		mPFElecMva[eleci]            = elec.mva();
		
		mPFElecdxy[eleci]            = elec.gsfTrack()->dxy(primaryvtx.position());
		mPFElecdz[eleci]             = elec.gsfTrack()->dz(primaryvtx.position());
		
		mPFElecIsEB[eleci]           = elec.isEB();
		mPFElecHadOverEm[eleci]      = elec.hadronicOverEm();
		mPFElecHcalOverEm[eleci]     = elec.hcalOverEcal();
		mPFElecSupClusOverP[eleci]   = elec.eSuperClusterOverP();
      

		mPFElecInnerHits[eleci]      = elec.gsfTrack()->trackerExpectedHitsInner().numberOfHits();
		mPFElecConvDist[eleci]       = elec.convDist();//convInfo.dist();
		mPFElecConvDcot[eleci]       = elec.convDcot();//convInfo.dcot();

		mPFElecEcalDrivenSeed[eleci]   = elec.ecalDrivenSeed();
		mPFElecdB[eleci]               = elec.dB();
		mPFElecNumOfValidHits[eleci]   = elec.gsfTrack()->numberOfValidHits();
		mPFElecdr03HcalTowerSumEt[eleci]   = elec.dr03HcalTowerSumEt();//hcalIso();
		mPFElecdr03EcalRecHitSumEt[eleci]  = elec.dr03EcalRecHitSumEt();//ecalIso();
		mPFElecdr03TkSumPt[eleci]          = elec.dr03TkSumPt(); //trackIso();
		mPFElecNormChi2[eleci]       = elec.gsfTrack()->normalizedChi2();
		mPFElecfbrem[eleci]          = elec.fbrem();
		mPFElecDEtaSuTrAtVtx[eleci]  = elec.deltaEtaSuperClusterTrackAtVtx();
		mPFElecDPhiSuTrAtVtx[eleci]  = elec.deltaPhiSuperClusterTrackAtVtx();
		mPFElecHadronicOverEm[eleci] = elec.hadronicOverEm();
		mPFElecHcalOverEcal[eleci]   = elec.hcalOverEcal();
		mPFElecSuperClusOverP[eleci] = elec.eSuperClusterOverP();
		mPFElecetaeta[eleci]         = elec.sigmaEtaEta();
		mPFElecietaieta[eleci]       = elec.sigmaIetaIeta();


		mPFeidLoose[eleci]              = ((int)elec.electronID("eidLoose") & 1);
		mPFeidRobustHighEnergy[eleci]   = ((int)elec.electronID("eidRobustHighEnergy") & 1);
		mPFeidRobustLoose[eleci]        = ((int)elec.electronID("eidRobustLoose") & 1);
		mPFeidRobustTight[eleci]        = ((int)elec.electronID("eidRobustTight") & 1);
		mPFeidTight[eleci]              = ((int)elec.electronID("eidTight") & 1);
		mPFevspi[eleci]                 = ((int)elec.electronID("pf_evspi") & 1);
		mPFevsmu[eleci]                 = ((int)elec.electronID("pf_evsmu") & 1);



 		eleci++;
	}
	mNPFElec=eleci;

	/*///----------------Tau-------------------------------------------------------
	
	edm::Handle<edm::View<pat::Tau> > TauHand;
	iEvent.getByLabel("cleanPatTaus",TauHand);

	int taui=0;
	for(unsigned int ind=0; ind<(*TauHand).size() && ind<MAXTAU; ind++)
	{ 
		const pat::Tau& tau = (*TauHand)[ind];
	
		mTauPt[taui]     = tau.pt() ;
		mTauPx[taui]     = tau.momentum().X() ;
		mTauPy[taui]     = tau.momentum().Y() ;
		mTauPz[taui]     = tau.momentum().Z() ;
		mTauE[taui]      = tau.energy() ;
		mTauEta[taui]    = tau.eta() ;
		mTauPhi[taui]    = tau.phi() ;
		
 		mTauEtaEtaMoment[taui] = tau.etaetaMoment();
 		mTauPhiPhiMoment[taui] = tau.phiphiMoment();
 		mTauEtaPhiMoment[taui] = tau.etaphiMoment();
 	       

		taui++;
	
	}
	mNTau = taui;
	
	///----------------PF Tau-----------------------------------------------------
	
	iEvent.getByLabel("selectedPatTausPF",TauHand);

	taui=0;
	for(unsigned int ind=0; ind<(*TauHand).size() && ind<MAXTAU; ind++)
	{ 
		const pat::Tau& tau = (*TauHand)[ind];
	
		mPFTauPt[taui]     = tau.pt();
		mPFTauPx[taui]     = tau.momentum().X();
		mPFTauPy[taui]     = tau.momentum().Y();
		mPFTauPz[taui]     = tau.momentum().Z();
		mPFTauE[taui]      = tau.energy();
		mPFTauEta[taui]    = tau.eta();
		mPFTauPhi[taui]    = tau.phi();

		mPFTauCharge[taui] = tau.charge();
		
		mPFTauEtaEtaMoment[taui] = tau.etaetaMoment();
		mPFTauPhiPhiMoment[taui] = tau.phiphiMoment();
		mPFTauEtaPhiMoment[taui] = tau.etaphiMoment();
		


		//PF objects
		mPFTauLeadPFChargedHadrCandsignedSipt[taui] = tau.leadPFChargedHadrCandsignedSipt();  
		mPFTauIsoPFChargedHadrCandsPtSum[taui]  = tau.isolationPFChargedHadrCandsPtSum();
		mPFTauIsoPFGammaCandsEtSum[taui]        = tau.isolationPFGammaCandsEtSum();      
		mPFTauMaximumHCALPFClusterEt[taui]      = tau.maximumHCALPFClusterEt();          
		mPFTauEmFraction[taui]                  = tau.emFraction();                      
		mPFTauHcalTotOverPLead[taui]            = tau.hcalTotOverPLead();                
		mPFTauHcalMaxOverPLead[taui]            = tau.hcalMaxOverPLead();                
		mPFTauHcal3x3OverPLead[taui]            = tau.hcal3x3OverPLead();                
		mPFTauEcalStripSumEOverPLead[taui]      = tau.ecalStripSumEOverPLead();          
		mPFTauBremsRecoveryEOverPLead[taui]     = tau.bremsRecoveryEOverPLead();                 
		mPFTauElectronPreIDOutput[taui]         = tau.electronPreIDOutput();             
		mPFTauElectronPreIDDecision[taui]       = tau.electronPreIDDecision();            
		mPFTauCaloComp[taui]                    = tau.caloComp();                        
		mPFTauSegComp[taui]                     = tau.segComp();                         
		mPFTauMuonDecision[taui]                = tau.muonDecision(); 
                  
		mPFTauLeadTrackPtCut[taui]              = tau.tauID("leadingTrackPtCut");
		mPFTauByIso[taui]                       = tau.tauID("byIsolation");
		mPFTauByTaNCfrHalfPercent[taui]         = tau.tauID("byTaNCfrHalfPercent");  



		taui++;
	
	}
	mNPFTau = taui;
	
	*/
	
	///----------------Photon-----------------------------------------------------
	
	edm::Handle<edm::View<pat::Photon> > PhotHand;
	iEvent.getByLabel("cleanPatPhotons",PhotHand);
	
	int photi=0;
	for(unsigned int ind=0; ind<(*PhotHand).size() && ind<MAXPHOT; ind++)
	{ 
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
	
	///-------------------MC Product-------------------------------------------
	
	if(isMCTag)
	{
		/// Gen Particles
		Handle<reco::GenParticleCollection>  GenParHand;
		iEvent.getByLabel("genParticles", GenParHand);
		
		//modified by Shuichi & Latife	
		
		int igcount=0;
		
		for( size_t i = 0; i < GenParHand->size(); ++ i ) 
		{
			const GenParticle &p  = (*GenParHand)[i];

			//const reco::Candidate& p = (*GenParHand)[ i ];

			int id = p.pdgId();
	

			//printf("%2d   %10d    %6.1f   %6.1f   %6.1f  %6.1f   %6.1f  %3d  %6.2f  %6.2f \n", 
			//  p.status() ,  p.pdgId(), p.pt() , p.px(), p.py(), p.pz(), p.mass(),p.charge(),  p.eta(), p.phi());


			//cout  << id  << endl; 

			if( p.status() ==3 || abs( p.status() ) ==23 || abs(id) == 23 || abs(id) == 24 || abs(id) == 39 || abs(id)==5 || abs(id)==6
			    || abs(id) == 11 || abs(id) == 12 || abs(id)==13 || abs(id) == 14 || abs(id) == 15 || abs(id)==16 || abs(id)==5000039 || 
                            abs(id) == 17 || abs(id) == 18 )  

			//if(  abs( p.status() ) ==23 && abs(id)==5000039 )  
			{
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
				mGenParMass[igcount]   = p.mass() ;

				
				
				//  get pid of parent particle...
				mGenParDoughterOf[igcount] = 0;

				
				int n = p.numberOfMothers();
				if(n>0) 
			        {
				    const reco::Candidate *pa = p.mother();
				    int parentID = pa->pdgId();
				    mGenParDoughterOf[igcount]=parentID;

				} 
				
				
				/*if( p.numberOfMothers() >1 ) 
				{
					mGenParMother1[igcount] =  p.mother(0)->pdgId() ; 
					mGenParMother2[igcount] =  p.mother(1)->pdgId() ; 
					}*/ 

				igcount++;
			}
		}
	
		mNGenPar=igcount;
		
		
		//Handle< double > genEventScale;
		//iEvent.getByLabel( "genEventScale", genEventScale );
		//mGenScale = *genEventScale;

		///----------Default PDF------------------------------------------------
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
	
	if(isSignalTag==1.)
	{
		
		///----------PDF Weight from file---------------------------------------
		edm::InputTag pdfWeightTag("pdfWeights1:cteq66"); // or any other PDF set
		edm::Handle<std::vector<double> > weightHandle;
		iEvent.getByLabel(pdfWeightTag, weightHandle);

		std::vector<double> weights = (*weightHandle);
		//std::cout << "Event weight for central PDF:" << weights[0] << std::endl;
		unsigned int nmembers = weights.size();
		
		for (unsigned int j=0; j<nmembers; j++)
		{

		      mPdfWeights1[j] =  weights[j];
		}
		
		mNPdfWeights1 = nmembers;  

	}
		
	if(isSignalTag==2.)
	{

		///----------PDF Weight from file---------------------------------------
		edm::InputTag pdfWeightTag("pdfWeights2:MSTW2008nlo68cl"); // or any other PDF set
		edm::Handle<std::vector<double> > weightHandle;
		iEvent.getByLabel(pdfWeightTag, weightHandle);

		std::vector<double> weights = (*weightHandle);
		//std::cout << "Event weight for central PDF:" << weights[0] << std::endl;
		unsigned int nmembers = weights.size();
		
		for (unsigned int j=0; j<nmembers; j++)
		{

		      mPdfWeights[j] =  weights[j];
		}
		
		mNPdfWeights = nmembers;  

		
	}
	if(isSignalTag==3.)
	{

		///----------PDF Weight from file---------------------------------------
		edm::InputTag pdfWeightTag("pdfWeights3:NNPDF20"); // or any other PDF set
		edm::Handle<std::vector<double> > weightHandle;
		iEvent.getByLabel(pdfWeightTag, weightHandle);

		std::vector<double> weights = (*weightHandle);
		//std::cout << "Event weight for central PDF:" << weights[0] << std::endl;
		unsigned int nmembers = weights.size();
		
		for (unsigned int j=0; j<nmembers; j++)
		{

		      mPdfWeights[j] =  weights[j];
		}
		
		mNPdfWeights = nmembers;  

			
	}
	
	



	if(!isMCTag)
	{
	
	///-------------------L1 Trigger----------------------------------------------
		
		Handle <L1GlobalTriggerReadoutRecord> gtRecord_h;
		iEvent.getByType (gtRecord_h); // assume only one L1 trigger record here
		const L1GlobalTriggerReadoutRecord* gtRecord = gtRecord_h.failedToGet () ? 0 : &*gtRecord_h;
	
		DecisionWord gtDecisionWord = gtRecord->decisionWord();
	
		for(int i=0; i<128; i++)
		{
			L1Array[i] =  gtDecisionWord[i];
		}
		nL1 = 128;
	
		
		///-------------------- L1 Technical Trigger----------------------------------
	
		Handle<L1GlobalTriggerReadoutRecord> gtRecord2;
		iEvent.getByLabel("gtDigis",gtRecord2);
		const TechnicalTriggerWord tWord = gtRecord2->technicalTriggerWord();
	
		for(int i=0; i<64; i++)
		{
			L1TArray[i] = tWord.at(i);
		}
		nL1T = 64;
	
	}
	
	///----------------------Tracking Failure-----------------------------------------------
	

	edm::Handle<std::vector<reco::Track> > tracks2;
	iEvent.getByLabel(Tracks_, tracks2);
	
	edm::Handle<std::vector<reco::Vertex> > vtxs;
	iEvent.getByLabel("offlinePrimaryVertices", vtxs);

	// ht coming from pat jets see above
	double sumpt = 0;
	if (vtxs->size() > 0) 
	{
		const reco::Vertex * vtx = &((*vtxs)[0]);
		for (std::vector<reco::Track>::const_iterator tr = tracks2->begin(); tr != tracks2->end(); ++tr) {
		if (fabs(tr->dz(vtx->position())) > 1.0) continue;
		if (fabs(tr->dxy(vtx->position())) > 0.2) continue;
		sumpt += tr->pt();
		}
	}
	
	mSumTrackPt = sumpt;



        ///-----------------------Beam Halo Flag-------------------------------------------------


	Handle<reco::BeamHaloSummary> beamHaloSummary;
	iEvent.getByLabel("BeamHaloSummary" , beamHaloSummary);
	
	mbeamHaloTight = beamHaloSummary->CSCTightHaloId();
	mbeamHaloLoose = beamHaloSummary->CSCLooseHaloId();

	///-----------------------TIV-------------------------------------------------------------
	/*	

	Handle<CandidateView> PatTracksHand;  
	iEvent.getByLabel("selectedPatTracks" ,PatTracksHand);


	int pattracksi=0;
	for(unsigned int ind=0; ind<(*PatTracksHand).size() && ind<100; ind++)
	{ 
		CandidateBaseRef trCandRef = PatTracksHand->refAt(ind); 
		const Candidate & trCand = (*PatTracksHand)[ind]; //the candidate
		const reco::Tracks & tracks = dynamic_cast<const reco::Tracks &>(trCand);



		edm::RefToBase<reco::Track> track(trackCollectionH, i);

		double  pt= tracks.pt();

	}

	*/
	///-----------------------TIV-------------------------------------------------------------
	
	
	Handle<reco::TrackCollection> tracks;
	iEvent.getByLabel(Tracks_,tracks);

	for(int i=0; i<TIVMAX;i++)
	{
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
	
	tivN=0;
	for(reco::TrackCollection::const_iterator itTrack = tracks->begin();itTrack != tracks->end();++itTrack)
	{
		float trkPt = itTrack->pt();
		float ILV_isoPT = 0.;

		if(trkPt < tiv_ltrack_thr_) continue ;
		//if( fabs(itTrack->dz()) > tiv_dz_thr_) continue;
		//if( fabs(itTrack->dxy()) > tiv_dxy_thr_) continue;


		const math::XYZVector trackMomentum = itTrack->momentum() ;

		if(DEBUG==1)
		std::cout << "---- TIV_N="<< tivN << " lTrkPt=" << trkPt  << " eta:"<<itTrack->eta()<<" phi:"<<itTrack->phi() << " dz:" << itTrack->dz() << " dxy:" << itTrack->dxy()<< std::endl;


		float tmpPt[TIVMAX],tmpPx[TIVMAX],tmpPy[TIVMAX],tmpPz[TIVMAX];
		float tmpEta[TIVMAX],tmpPhi[TIVMAX], tmpDxy[TIVMAX],tmpDsz[TIVMAX], tmpDr[TIVMAX], tmpDz[TIVMAX], tmpD0[TIVMAX];
		float tmpDxy_corr[TIVMAX],tmpDsz_corr[TIVMAX], tmpDz_corr[TIVMAX], tmpD0_corr[TIVMAX];
		for(int i=0; i<TIVMAX;i++)
		{
			tmpPt[i]=0;tmpPx[i]=0;tmpPy[i]=0;tmpPz[i]=0;tmpEta[i]=0;tmpPhi[i]=0;tmpDxy[i]=0;tmpDsz[i]=0;tmpDr[i]=0;
			tmpD0[i]=0;tmpDz[i]=0;
			tmpD0_corr[i]=0;tmpDz_corr[i]=0; tmpDxy_corr[i]=0;tmpDsz_corr[i]=0;
		}
		int tmpN=0;


		for(reco::TrackCollection::const_iterator itTrack2 = tracks->begin();itTrack2 != tracks->end();++itTrack2)
		{
			float trkPt2 = itTrack2->pt();
			if(trkPt2 < tiv_strack_thr_) continue;
			//if( fabs(itTrack2->dz()) > tiv_dz_thr_) continue;
			//if( fabs(itTrack2->dxy()) > tiv_dxy_thr_) continue;


			const math::XYZVector trackMomentum2 = itTrack2->momentum() ;

			float dR = ROOT::Math::VectorUtil::DeltaR(trackMomentum, trackMomentum2);
			if(dR < tiv_cone_ && dR>tiv_inner_cone_)
			{

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


		if( (ILV_isoPT/trkPt) < 10.)
		{
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

			if(DEBUG==1)
			{
				std::cout << "+" << tivN-1 << " " << trkPt << std::endl;
			}

			for(int t=0;t<tmpN;t++)
			{
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
     
	///----------------------------Lover TIV Calculation-----------------------------------------------------
     
	float Lower_TIV = 100;
	float ILV_isoPT;
	
	float TIV_pt_l_thr = 10;
	float TIV_pt_s_thr = 1;
	//float TIV_dxy_thr = 100;
	//float TIV_dz_thr = 100;
	float TIV_dR_inner_thr = 0.02;
	float TIV_dR_outer_thr = 0.3;


	
    for(int tl=0; tl<tivN; tl++)
	{
		ILV_isoPT = 100.;

		bool isMuon=false;
		for(int mu=0; mu<mNMuon; mu++)
		{
			//if( mMuonPt[mu] > 20 && fabs(varFloatArr["Muon_isGood_AllGlobalMuons"][mu]-1 ) < 0.1 )
			if( mMuonPt[mu] > 20 )   
			{
				if( mMuonSumPtDR03[mu] >= 0 && mMuonSumPtDR03[mu] < 100)
				{
					float dPhi = deltaPhi( mMuonPhi[mu], TIV_phi[tl] );
					float dEta = mMuonEta[mu] - TIV_eta[tl];
					if( sqrt(dPhi*dPhi + dEta*dEta) < 10) {isMuon=true; break;}
				}
			}
		}
		if(isMuon) continue;

		if( TIV_lead[tl]==1 && TIV_pt[tl] > TIV_pt_l_thr  )
		{ 
			ILV_isoPT = 0.;
			for(int ts = tl+1; ts< tivN && TIV_lead[ts]!=1 ;ts++ )
			{
				
				if( TIV_dR[ts] < TIV_dR_outer_thr  && TIV_dR[ts] > TIV_dR_inner_thr && TIV_pt[ts] > TIV_pt_s_thr)
				{
					ILV_isoPT+= TIV_pt[ts];
				}
			}
			if( ILV_isoPT / TIV_pt[tl] < Lower_TIV ) Lower_TIV = ILV_isoPT / TIV_pt[tl];
		}
	}
	LowTIV = Lower_TIV;
	
	

	


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

	
	if(isMCTag)
	{
	      /// Gen AK5 Jets
	      mtree->Branch("GenAK5JetE"             ,mGenAK5JetE             ,  "GenAK5JetE[NCaloAK5Jets]/D"         );
	      mtree->Branch("GenAK5JetPt"            ,mGenAK5JetPt            ,  "GenAK5JetPt[NCaloAK5Jets]/D"        );
	      mtree->Branch("GenAK5JetPx"            ,mGenAK5JetPx            ,  "GenAK5JetPx[NCaloAK5Jets]/D"        );
	      mtree->Branch("GenAK5JetPy"            ,mGenAK5JetPy            ,  "GenAK5JetPy[NCaloAK5Jets]/D"        );
	      mtree->Branch("GenAK5JetPz"            ,mGenAK5JetPz            ,  "GenAK5JetPz[NCaloAK5Jets]/D"        );
	      mtree->Branch("GenAK5JetEta"           ,mGenAK5JetEta           ,  "GenAK5JetEta[NCaloAK5Jets]/D"       );
	      mtree->Branch("GenAK5JetPhi"           ,mGenAK5JetPhi           ,  "GenAK5JetPhi[NCaloAK5Jets]/D"       );
	      mtree->Branch("GenAK5JetEmEnergy"      ,mGenAK5JetEmEnergy      ,  "GenAK5JetEmEnergy[NCaloAK5Jets]/D"  );
	      mtree->Branch("GenAK5JetHadEnergy"     ,mGenAK5JetHadEnergy     ,  "GenAK5JetHadEnergy[NCaloAK5Jets]/D" );
	}      
	
	
	/// PF AK5 Jets
	mtree->Branch("NPFAK5Jets"            ,&mNPFAK5Jets           ,  "NPFAK5Jets/I"                    );
	mtree->Branch("PFAK5JetE"             ,mPFAK5JetE             ,  "PFAK5JetE[NPFAK5Jets]/D"         );
	mtree->Branch("PFAK5JetPt"            ,mPFAK5JetPt            ,  "PFAK5JetPt[NPFAK5Jets]/D"        );
	mtree->Branch("PFAK5JetPx"            ,mPFAK5JetPx            ,  "PFAK5JetPx[NPFAK5Jets]/D"        );
	mtree->Branch("PFAK5JetPy"            ,mPFAK5JetPy            ,  "PFAK5JetPy[NPFAK5Jets]/D"        );
	mtree->Branch("PFAK5JetPz"            ,mPFAK5JetPz            ,  "PFAK5JetPz[NPFAK5Jets]/D"        );
	mtree->Branch("PFAK5JetEta"           ,mPFAK5JetEta           ,  "PFAK5JetEta[NPFAK5Jets]/D"       );
	mtree->Branch("PFAK5JetPhi"           ,mPFAK5JetPhi           ,  "PFAK5JetPhi[NPFAK5Jets]/D"       );
	

	mtree->Branch("PFAK5JetfHPD"          ,mPFAK5JetfHPD          ,  "PFAK5JetfHPD[NPFAK5Jets]/D"      ); 
	mtree->Branch("PFAK5JetfRBX"          ,mPFAK5JetfRBX          ,  "PFAK5JetfRBX[NPFAK5Jets]/D"      ); 
	mtree->Branch("PFAK5JetN90Hits"       ,mPFAK5JetN90Hits       ,  "PFAK5JetN90Hits[NPFAK5Jets]/D"   ); 
	mtree->Branch("PFAK5JetN90"           ,mPFAK5JetN90           ,  "PFAK5JetN90[NPFAK5Jets]/I"       ); 
	mtree->Branch("PFAK5JetSigEta"        ,mPFAK5JetSigEta        ,  "PFAK5JetSigEta[NPFAK5Jets]/D"    ); 
	mtree->Branch("PFAK5JetSigPhi"        ,mPFAK5JetSigPhi        ,  "PFAK5JetSigPhi[NPFAK5Jets]/D"    ); 
	mtree->Branch("PFAK5JetIDEmf"         ,mPFAK5JetIDEmf         ,  "PFAK5JetIDEmf[NPFAK5Jets]/D"     ); 
	
	mtree->Branch("PFAK5JetECor"          ,mPFAK5JetECor          ,  "PFAK5JetECor[NPFAK5Jets]/D"      );
	mtree->Branch("PFAK5JetPtCor"         ,mPFAK5JetPtCor         ,  "PFAK5JetPtCor[NPFAK5Jets]/D"     );
	mtree->Branch("PFAK5JetPxCor"         ,mPFAK5JetPxCor         ,  "PFAK5JetPxCor[NPFAK5Jets]/D"     );
	mtree->Branch("PFAK5JetPyCor"         ,mPFAK5JetPyCor         ,  "PFAK5JetPyCor[NPFAK5Jets]/D"     );
	mtree->Branch("PFAK5JetPzCor"         ,mPFAK5JetPzCor         ,  "PFAK5JetPzCor[NPFAK5Jets]/D"     );
	
	mtree->Branch("PFAK5JetBtagTkCountHighEff"   ,mPFAK5JetBtagTkCountHighEff   ,"PFAK5JetBtagTkCountHighEff[NPFAK5Jets]/D"     );
	mtree->Branch("PFAK5JetBTagSimpleSecVtx"     ,mPFAK5JetBTagSimpleSecVtx     ,"PFAK5JetBTagSimpleSecVtx[NPFAK5Jets]/D"     );
	mtree->Branch("PFAK5JetBTagCombSecVtx"       ,mPFAK5JetBTagCombSecVtx       ,"PFAK5JetBTagCombSecVtx[NPFAK5Jets]/D"     );
	
	mtree->Branch("PFAK5JetNeuEmEngFrac"  ,mPFAK5JetNeuEmEngFrac  ,  "PFAK5JetNeuEmEngFrac[NPFAK5Jets]/D" ); 
	mtree->Branch("PFAK5JetChaEmEngFrac"  ,mPFAK5JetChaEmEngFrac  ,  "PFAK5JetChaEmEngFrac[NPFAK5Jets]/D" ); 
	mtree->Branch("PFAK5JetChaHadEngFrac" ,mPFAK5JetChaHadEngFrac ,  "PFAK5JetChaHadEngFrac[NPFAK5Jets]/D" ); 
	mtree->Branch("PFAK5JetNeuHadEngFrac" ,mPFAK5JetNeuHadEngFrac ,  "PFAK5JetNeuHadEngFrac[NPFAK5Jets]/D" ); 
	mtree->Branch("PFAK5JetChaMuEng"      ,mPFAK5JetChaMuEng      ,  "PFAK5JetChaMuEng[NPFAK5Jets]/D" ); 
	mtree->Branch("PFAK5JetMuonEng"       ,mPFAK5JetMuonEng       ,  "PFAK5JetMuonEng[NPFAK5Jets]/D" ); 
	mtree->Branch("PFAK5JetPhotEng"       ,mPFAK5JetPhotEng       ,  "PFAK5JetPhotEng[NPFAK5Jets]/D" ); 
	mtree->Branch("PFAK5JetElecEng"       ,mPFAK5JetElecEng       ,  "PFAK5JetElecEng[NPFAK5Jets]/D" ); 
	
	
	mtree->Branch("PFAK5JetNumOfChaMu"  ,mPFAK5JetNumOfChaMu   ,  "PFAK5JetNumOfChaMu[NPFAK5Jets]/I" ); 
	mtree->Branch("PFAK5JetNumOfMuon"   ,mPFAK5JetNumOfMuon    ,  "PFAK5JetNumOfMuon[NPFAK5Jets]/I" ); 
	mtree->Branch("PFAK5JetNumOfPhot"   ,mPFAK5JetNumOfPhot    ,  "PFAK5JetNumOfPhot[NPFAK5Jets]/I" ); 
	mtree->Branch("PFAK5JetNumOfElec"   ,mPFAK5JetNumOfElec    ,  "PFAK5JetNumOfElec[NPFAK5Jets]/I" ); 
	mtree->Branch("PFAK5JetNumOfNeu"    ,mPFAK5JetNumOfNeu     ,  "PFAK5JetNumOfNeu[NPFAK5Jets]/I" ); 
	mtree->Branch("PFAK5JetNumOfCha"    ,mPFAK5JetNumOfCha     ,  "PFAK5JetNumOfCha[NPFAK5Jets]/I" ); 
	mtree->Branch("PFAK5JetNumOfNeuHad" ,mPFAK5JetNumOfNeuHad  ,  "PFAK5JetNumOfNeuHad[NPFAK5Jets]/I" ); 
	mtree->Branch("PFAK5JetNumOfChaHad" ,mPFAK5JetNumOfChaHad  ,  "PFAK5JetNumOfChaHad[NPFAK5Jets]/I" ); 
	mtree->Branch("PFAK5JetNumOfDaughters" ,mPFAK5JetNumOfDaughters  ,"PFAK5JetNumOfDaughters[NPFAK5Jets]/I" );
	mtree->Branch("PFAK5JetIDLOOSE"     ,mPFAK5JetIDLOOSE      ,"PFAK5JetIDLOOSE[NPFAK5Jets]/I" );
	mtree->Branch("PFAK5JetIDTIGHT"     ,mPFAK5JetIDTIGHT      ,"PFAK5JetIDTIGHT[NPFAK5Jets]/I" );

	mtree->Branch("PFAK5uncer"          ,mPFAK5uncer           ,"PFAK5uncer[NPFAK5Jets]/D");

	
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
	
	
	
	
	///------------PF MUONS-------------------------------

	
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
	mtree->Branch("PFMuonCombQOverPError" 	     ,mPFMuonCombQOverPError     ,"PFMuonCombQOverPError[NPFMuon]/D"  ); 
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
                                           
	                                   
			                                        
	
	/// Electron
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
	
			
	///--------------PF Electron-------------------------------------------
	

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

 
	
	/// Tau
	mtree->Branch("NTau"       ,&mNTau   ,"NTau/I");
	mtree->Branch("TauE"       ,mTauE    ,"TauE[NTau]/D" );
	mtree->Branch("TauPt"      ,mTauPt   ,"TauPt[NTau]/D" );
	mtree->Branch("TauPx"      ,mTauPx   ,"TauPx[NTau]/D" );
	mtree->Branch("TauPy"      ,mTauPy   ,"TauPy[NTau]/D" );
	mtree->Branch("TauPz"      ,mTauPz   ,"TauPz[NTau]/D" );
	mtree->Branch("TauEta"     ,mTauEta  ,"TauEta[NTau]/D" );
	mtree->Branch("TauPhi"     ,mTauPhi  ,"TauPhi[NTau]/D" );
	
	mtree->Branch("TauEtaEtaMoment"   ,mTauEtaEtaMoment   ,"TauEtaEtaMoment[NTau]/D" );
	mtree->Branch("TauPhiPhiMoment"   ,mTauPhiPhiMoment   ,"TauPhiPhiMoment[NTau]/D" );
	mtree->Branch("TauEtaPhiMoment"   ,mTauEtaPhiMoment   ,"TauEtaPhiMoment[NTau]/D" );
	
	mtree->Branch("TauTracksInvariantMass"             ,mTauTracksInvariantMass             ,"TauTracksInvariantMass[NTau]/D" );
	mtree->Branch("TauSignalTracksInvariantMass"       ,mTauSignalTracksInvariantMass       ,"TauSignalTracksInvariantMass[NTau]/D" );
	mtree->Branch("TauMaximumHCALhitEt"                ,mTauMaximumHCALhitEt                ,"TauMaximumHCALhitEt[NTau]/D" );
	mtree->Branch("TauIsolationECALhitsEtSum"          ,mTauIsolationECALhitsEtSum          ,"TauIsolationECALhitsEtSum[NTau]/D" );
	mtree->Branch("TauIsolationTracksPtSum"            ,mTauIsolationTracksPtSum            ,"TauIsolationTracksPtSum[NTau]/D" );
	mtree->Branch("TauLeadTrackHCAL3x3hottesthitDEta"  ,mTauLeadTrackHCAL3x3hottesthitDEta  ,"TauLeadTrackHCAL3x3hottesthitDEta[NTau]/D" );
	mtree->Branch("TauLeadTrackHCAL3x3hitsEtSum"       ,mTauLeadTrackHCAL3x3hitsEtSum       ,"TauLeadTrackHCAL3x3hitsEtSum[NTau]/D" );
	mtree->Branch("TauLeadTracksignedSipt"             ,mTauLeadTracksignedSipt             ,"TauLeadTracksignedSipt[NTau]/D" );
	
	
		
	/// PFTau
	mtree->Branch("NPFTau"       ,&mNPFTau      ,"NPFTau/I");
	mtree->Branch("PFTauCharge"  ,mPFTauCharge  ,"PFTauCharge[NPFTau]/I");
	mtree->Branch("PFTauE"       ,mPFTauE       ,"PFTauE[NPFTau]/D" );
	mtree->Branch("PFTauPt"      ,mPFTauPt      ,"PFTauPt[NPFTau]/D" );
	mtree->Branch("PFTauPx"      ,mPFTauPx      ,"PFTauPx[NPFTau]/D" );
	mtree->Branch("PFTauPy"      ,mPFTauPy      ,"PFTauPy[NPFTau]/D" );
	mtree->Branch("PFTauPz"      ,mPFTauPz      ,"PFTauPz[NPFTau]/D" );
	mtree->Branch("PFTauEta"     ,mPFTauEta     ,"PFTauEta[NPFTau]/D" );
	mtree->Branch("PFTauPhi"     ,mPFTauPhi     ,"PFTauPhi[NPFTau]/D" );

	
	mtree->Branch("PFTauEtaEtaMoment"   ,mPFTauEtaEtaMoment   ,"PFTauEtaEtaMoment[NPFTau]/D" );
	mtree->Branch("PFTauPhiPhiMoment"   ,mPFTauPhiPhiMoment   ,"PFTauPhiPhiMoment[NPFTau]/D" );
	mtree->Branch("PFTauEtaPhiMoment"   ,mPFTauEtaPhiMoment   ,"PFTauEtaPhiMoment[NPFTau]/D" );
	
	
	mtree->Branch("PFTauLeadPFChargedHadrCandsignedSipt"   ,mPFTauLeadPFChargedHadrCandsignedSipt  ,"PFTauLeadPFChargedHadrCandsignedSipt[NPFTau]/D" );
	mtree->Branch("PFTauIsoPFChargedHadrCandsPtSum"        ,mPFTauIsoPFChargedHadrCandsPtSum       ,"PFTauIsoPFChargedHadrCandsPtSum[NPFTau]/D" );
	mtree->Branch("PFTauIsoPFGammaCandsEtSum"              ,mPFTauIsoPFGammaCandsEtSum             ,"PFTauIsoPFGammaCandsEtSum[NPFTau]/D" );
	mtree->Branch("PFTauMaximumHCALPFClusterEt"            ,mPFTauMaximumHCALPFClusterEt           ,"PFTauMaximumHCALPFClusterEt[NPFTau]/D" );
	mtree->Branch("PFTauEmFraction"                        ,mPFTauEmFraction                       ,"PFTauEmFraction[NPFTau]/D" );
	mtree->Branch("PFTauHcalTotOverPLead"                  ,mPFTauHcalTotOverPLead                 ,"PFTauHcalTotOverPLead[NPFTau]/D" );
	mtree->Branch("PFTauHcalMaxOverPLead"                  ,mPFTauHcalMaxOverPLead                 ,"PFTauHcalMaxOverPLead[NPFTau]/D" );
	mtree->Branch("PFTauHcal3x3OverPLead"                  ,mPFTauHcal3x3OverPLead                 ,"PFTauHcal3x3OverPLead[NPFTau]/D" );
	mtree->Branch("PFTauEcalStripSumEOverPLead"            ,mPFTauEcalStripSumEOverPLead           ,"PFTauEcalStripSumEOverPLead[NPFTau]/D" );
	mtree->Branch("PFTauBremsRecoveryEOverPLead"           ,mPFTauBremsRecoveryEOverPLead          ,"PFTauBremsRecoveryEOverPLead[NPFTau]/D" );
	mtree->Branch("PFTauElectronPreIDOutput"               ,mPFTauElectronPreIDOutput              ,"PFTauElectronPreIDOutput[NPFTau]/D" );
	mtree->Branch("PFTauElectronPreIDDecision"             ,mPFTauElectronPreIDDecision            ,"PFTauElectronPreIDDecision[NPFTau]/D" );
	mtree->Branch("PFTauCaloComp"                          ,mPFTauCaloComp                         ,"PFTauCaloComp[NPFTau]/D" );
	mtree->Branch("PFTauSegComp"                           ,mPFTauSegComp                          ,"PFTauSegComp[NPFTau]/D" );
	mtree->Branch("PFTauMuonDecision"                      ,mPFTauMuonDecision                     ,"PFTauMuonDecision[NPFTau]/D" );
	
	mtree->Branch("PFTauLeadTrackPtCut"                    ,mPFTauLeadTrackPtCut                   ,"PFTauLeadTrackPtCut[NPFTau]/D" );
	mtree->Branch("PFTauByIso"                             ,mPFTauByIso                            ,"PFTauByIso[NPFTau]/D" );
	mtree->Branch("PFTauByTaNCfrHalfPercent"               ,mPFTauByTaNCfrHalfPercent              ,"PFTauByTaNCfrHalfPercent[NPFTau]/D" );
	
	
	/// Photon
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
	

		
	
	/// Primary Vertex
	mtree->Branch("NPV"         ,&mNPV         ,"NPV/I");
	mtree->Branch("PVx"         ,mPVx          ,"PVx[NPV]/D" );
	mtree->Branch("PVy"         ,mPVy          ,"PVy[NPV]/D" );
	mtree->Branch("PVz"         ,mPVz          ,"PVz[NPV]/D" );
	mtree->Branch("PVchi2"      ,mPVchi2       ,"PVchi2[NPV]/D" );
	mtree->Branch("PVndof"      ,mPVndof       ,"PVndof[NPV]/D" );
	mtree->Branch("PVntracks"   ,mPVntracks    ,"PVntracks[NPV]/I" );
	

	
	if(isMCTag)
	{
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
	mtree->Branch("NoiseFlag"      ,NoiseFlag      ,"NoiseFlag[10]/I");

	

	if(!isMCTag)
	{
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
