#
#  SUSY-PAT configuration file
#
#  PAT configuration for the SUSY group - 53X series
#  More information here:
#  https://twiki.cern.ch/twiki/bin/view/CMS/SusyPatLayer1DefV12
#

# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *

#-- Meta data to be logged in DBS ---------------------------------------------
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.42 $'),
    name = cms.untracked.string('$Source: /afs/cern.ch/project/cvs/reps/CMSSW/CMSSW/PhysicsTools/Configuration/test/SUSY_pattuple_cfg.py,v $'),
    annotation = cms.untracked.string('SUSY pattuple definition')
)

#-- Message Logger ------------------------------------------------------------
process.MessageLogger.categories.append('PATSummaryTables')
process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet(
    limit = cms.untracked.int32(-1),
    reportEvery = cms.untracked.int32(1)
    )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-- VarParsing ----------------------------------------------------------------
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ('standard')

options.output = "SUSYPAT.root"
options.maxEvents = 100
#  for SusyPAT configuration
options.register('GlobalTag', "", VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "GlobalTag to use (if empty default Pat GT is used)")
options.register('mcInfo', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "process MonteCarlo data")
options.register('jetCorrections', 'L1FastJet', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "Level of jet corrections to use: Note the factors are read from DB via GlobalTag")
options.jetCorrections.append('L2Relative')
options.jetCorrections.append('L3Absolute')
options.jetCorrections.append('L2L3Residual')
options.register('hltName', 'HLT', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "HLT menu to use for trigger matching")
options.register('mcVersion', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Currently not needed and supported")
options.register('jetTypes', '', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "Additional jet types that will be produced (AK5Calo and AK5PF, cross cleaned in PF2PAT, are included anyway)")
options.register('hltSelection', '', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "hlTriggers (OR) used to filter events")
options.register('doValidation', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "Include the validation histograms from SusyDQM (needs extra tags)")
options.register('doExtensiveMatching', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "Matching to simtracks (needs extra tags)")
options.register('doSusyTopProjection', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "Apply Susy selection in PF2PAT to obtain lepton cleaned jets (needs validation)")
options.register('doType1MetCorrection', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "Apply Type1 MET correction in PF2PAT")
options.register('doType0MetCorrection', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "Apply Type1 MET correction in PF2PAT")
options.register('addKeep', '', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "Additional keep and drop statements to trim the event content")

#---parse user input
options.parseArguments()
options._tagOrder =[]

#-- Input Source --------------------------------------------------------------
if options.files:
    process.source.fileNames = cms.untracked.vstring (options.files)
process.source.fileNames = [
     '/store/data/Run2012A/MET/AOD/13Jul2012-v1/00000/B04890C1-DBD2-E111-B6AA-00261894391B.root'
    ]

process.maxEvents.input = options.maxEvents
# Due to problem in production of LM samples: same event number appears multiple times
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

#-- Calibration tag -----------------------------------------------------------
if options.GlobalTag:
    process.GlobalTag.globaltag = options.GlobalTag

############################# START SUSYPAT specifics ####################################
from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
#Apply SUSYPAT
addDefaultSUSYPAT(process,options.mcInfo,options.hltName,options.jetCorrections,options.mcVersion,options.jetTypes,options.doValidation,options.doExtensiveMatching,options.doSusyTopProjection,options.doType1MetCorrection,options.doType0MetCorrection)
SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )
############################## END SUSYPAT specifics ####################################

#-- TimeReport and TrigReport after running ----------------------------------
process.options.wantSummary = False

#-- HLT selection ------------------------------------------------------------
import HLTrigger.HLTfilters.hltHighLevel_cfi as hlt
if options.hltSelection:
    process.hltFilter = hlt.hltHighLevel.clone(
        HLTPaths = cms.vstring(options.hltSelection),
        TriggerResultsTag = cms.InputTag("TriggerResults","",options.hltName),
        throw = False
    )
    process.susyPatDefaultSequence.replace(process.eventCountProducer, process.eventCountProducer * process.hltFilter)

#-- Output module configuration -----------------------------------------------
process.out.fileName = options.output

# Custom settings
process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files???)
process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections
process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )
if options.hltSelection:
    process.out.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring("p"))
if options.addKeep:
    process.out.outputCommands.extend(options.addKeep)



#---------------------------------------good Vertex filter------------------------------------------------------


process.goodVertices = cms.EDFilter("VertexSelector",
	filter = cms.bool(False),
	src = cms.InputTag("offlinePrimaryVertices"),
	cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.rho < 2")
)

#---------------------------------------good collision filter------------------------------------------------------

process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskAlgoTrigConfig_cff')
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.L1T1coll=process.hltLevel1GTSeed.clone()
process.L1T1coll.L1TechTriggerSeeding = cms.bool(True)
#process.L1T1coll.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND NOT 43) OR (43 AND NOT 42))')

process.L1T1coll.L1SeedsLogicalExpression = cms.string('0 AND NOT (36 OR 37 OR 38 OR 39) ')



#---------------------------------------Physics Declared------------------------------------------------------------

process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'



#-------------------------------------HLT Trigger Selection--------------------------------------------------------------

process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')

process.hltHighLevel.HLTPaths = cms.vstring( "HLT_MET120*",
                                             "HLT_MET200*",
                                             "HLT_MET300*",
                                             "HLT_MET400*",
                                             "HLT_MonoCentralPFJet80_PFMETnoMu95_NHEF0p95*"
)


process.hltHighLevel.andOr = True   # True = OR, False = AND
process.hltHighLevel.throw = False  # tolerate if triggers not available


#-------------------------------------Ntuple Producer Pluggin--------------------------------------------------------------


process.load("MonoJetAnalysis.NtupleAnalyzer.NtupleAnalyzer_cfi")

process.TFileService  = cms.Service("TFileService", fileName = cms.string('ntuple.root') )



#---------------------------Noise FLags---------------------------------------------------------------

## The good primary vertex filter ____________________________________________||
process.primaryVertexFilter = cms.EDFilter(
        "VertexSelector",
            src = cms.InputTag("offlinePrimaryVertices"),
            cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
            filter = cms.bool(True)
            )

## The beam scraping filter __________________________________________________||
process.noscraping = cms.EDFilter(
        "FilterOutScraping",
            applyfilter = cms.untracked.bool(True),
            debugOn = cms.untracked.bool(False),
            numtrack = cms.untracked.uint32(10),
            thresh = cms.untracked.double(0.25)
            )

## The iso-based HBHE noise filter ___________________________________________||
process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')

## The CSC beam halo tight filter ____________________________________________||
process.load('RecoMET.METAnalyzers.CSCHaloFilter_cfi')

## The HCAL laser filter _____________________________________________________||
process.load("RecoMET.METFilters.hcalLaserEventFilter_cfi")
process.hcalLaserEventFilter.vetoByRunEventNumber=cms.untracked.bool(False)
process.hcalLaserEventFilter.vetoByHBHEOccupancy=cms.untracked.bool(True)

## The ECAL dead cell trigger primitive filter _______________________________||
process.load('RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi')
## For AOD and RECO recommendation to use recovered rechits
process.EcalDeadCellTriggerPrimitiveFilter.tpDigiCollection = cms.InputTag("ecalTPSkimNA")

## The EE bad SuperCrystal filter ____________________________________________||
process.load('RecoMET.METFilters.eeBadScFilter_cfi')

## The Good vertices collection needed by the tracking failure filter ________||
process.goodVertices = cms.EDFilter(
      "VertexSelector",
        filter = cms.bool(False),
        src = cms.InputTag("offlinePrimaryVertices"),
        cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.rho < 2")
      )

## The tracking failure filter _______________________________________________||
process.load('RecoMET.METFilters.trackingFailureFilter_cfi')


#--------------------Muons with wrong momenta--------------------------------

process.load('RecoMET.METFilters.inconsistentMuonPFCandidateFilter_cfi')
process.load('RecoMET.METFilters.greedyMuonPFCandidateFilter_cfi')



#-----------------------------Execution path ------------------------------------------------------------

process.p0 = cms.Path(process.noscraping  )
process.p1 = cms.Path(process.HBHENoiseFilter  )
process.p2 = cms.Path(process.CSCTightHaloFilter  )
process.p3 = cms.Path(process.CSCLooseHaloFilter  )
process.p4 = cms.Path(process.hcalLaserEventFilter  )
process.p5 = cms.Path(process.EcalDeadCellTriggerPrimitiveFilter ) 
process.p6 = cms.Path(process.goodVertices * process.trackingFailureFilter )
process.p7 = cms.Path(process.eeBadScFilter )
process.p8 = cms.Path(process.greedyMuonPFCandidateFilter*process.inconsistentMuonPFCandidateFilter)


process.p = cms.EndPath(
		#process.hltPhysicsDeclared *
		#process.L1T1coll *
	    #process.hltHighLevel *

		process.primaryVertexFilter *
		process.susyPatDefaultSequence*
		process.NtupleAnalyzer

)

#-- Dump config ------------------------------------------------------------
file = open('MonoJetPAT_cfg.py','w')
file.write(str(process.dumpPython()))
file.close()










