######################################################################
#                                                                    #
#                  NtupleAnalyzer_cfi                                #
#                                                                    #
######################################################################


import FWCore.ParameterSet.Config as cms


NtupleAnalyzer = cms.EDAnalyzer('NtupleAnalyzer',
		TriggerTag              = cms.string('TriggerResults::HLT' ),
		jetPtCut                = cms.double(15),
		jetEtaCut               = cms.double(2.4),
		isMC                    = cms.bool(True),
		isSignal                = cms.double(0),
		weight                  = cms.double(1),
		Tracks      = cms.untracked.InputTag("generalTracks"),
		TIV_ltrack_thr = cms.double(5),
		TIV_strack_thr = cms.double(1),
		TIV_dz_thr = cms.double(1),
		TIV_dxy_thr = cms.double(1),
		TIV_cone_thr = cms.double(0.35),
		TIV_inner_cone_thr = cms.double(0.015)

)

