#-- Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *


#-- Meta data to be logged in DBS
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.42 $'),
    name = cms.untracked.string('$Source: /local/reps/CMSSW/CMSSW/PhysicsTools/Configuration/test/SUSY_pattuple_cfg.py,v $'),
    annotation = cms.untracked.string('SUSY pattuple definition')
)


#-- Message Logger
process.MessageLogger.categories.append('PATSummaryTables')
process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet(
    limit = cms.untracked.int32(-1),
    reportEvery = cms.untracked.int32(1)
    )
process.MessageLogger.cerr.FwkReport.reportEvery = 100


############################# Monojet setting #############################
iRunData       = False #True or False
iData          = "Aug24" #No meaning if iRunData = False
                            #Jul13,Aug06,Aug24,PromptC2,PromptD
iSignal        = False #True or False, if True, PDF will be collected. No meaning if iRunData = True
iTrigger       = "MET" #MET, SingleMuon, DoubleMuon, SingleElectron, DoubleElectron, Physics, NoTrig
                          #(If isSignal, trigger will be set to NoTrig automatically)
iFileData      = '/store/data/Run2012C/MET/AOD/PromptReco-v2/000/203/002/04BCEC26-AA02-E211-A81D-003048CF99BA.root'
iFileMC        = '/store/group/phys_higgs/vbfHinv/DataSample/AODSIM_WJetsToLNu.root'
#iFileMC        = '/store/group/phys_higgs/vbfHinv/DataSample/AODSIM_DYJetsToLL.root'
iMaxEvent      = 1000
iPFElectronTag = "selectedPatElectronsPF"
iPFMuonTag     = "selectedPatMuonsPF"
iPFTauTag      = "patTausPF"
iTauTag        = "patTaus" 
iPFJetTag      = "selectedPatJetsPF" #cleanPatJetsAK5PF
iPFMETTag      = "patMETsPF"
############################# Monojet setting #############################


#-- VarParsing
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ('standard')


#--  For SusyPAT configuration
options.register('GlobalTag', "", VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "GlobalTag to use (if empty default Pat GT is used)")
options.register('mcInfo', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "process MonteCarlo data")
options.register('jetCorrections', 'L1FastJet', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "Level of jet corrections to use: Note the factors are read from DB via GlobalTag")
options.register('hltName', 'HLT', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "HLT menu to use for trigger matching")
options.register('mcVersion', '', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Currently not needed and supported")
options.register('jetTypes', '', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "Additional jet types that will be produced (AK5Calo and AK5PF, cross cleaned in PF2PAT, are included anyway)")
options.register('hltSelection', '', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "hlTriggers (OR) used to filter events")
options.register('doValidation', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "Include the validation histograms from SusyDQM (needs extra tags)")
options.register('doExtensiveMatching', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "Matching to simtracks (needs extra tags)")
options.register('doSusyTopProjection', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "Apply Susy selection in PF2PAT to obtain lepton cleaned jets (needs validation)")
options.register('doType1MetCorrection', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "Apply Type1 MET correction in PF2PAT")
options.register('doType0MetCorrection', True, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "Apply Type0 MET correction in PF2PAT")
options.register('addKeep', '', VarParsing.VarParsing.multiplicity.list, VarParsing.VarParsing.varType.string, "Additional keep and drop statements to trim the event content")


#-- Parse user input
options.parseArguments()
options._tagOrder =[]
options.output = "SUSYPAT.root"
options.maxEvents = iMaxEvent
options.jetCorrections.append('L2Relative')
options.jetCorrections.append('L3Absolute')
options.doType1MetCorrection = 1
options.doType0MetCorrection = 1
options.jetTypes.append('AK5PF')
options.addKeep.append('keep *_pfMet_*_*')

if iRunData == True:
    options.jetCorrections.append('L2L3Residual')
    options.mcInfo = 0
    if (iData.find("Jul13")==0):
        options.GlobalTag = "FT_53_V6_AN3::All"
    elif (iData.find("Aug06")==0):
        options.GlobalTag = "FT_53_V6C_AN3::All"
    elif (iData.find("Aug24")==0):
        options.GlobalTag = "FT_53_V10_AN3::All"
    elif (iData.find("PromptC2")==0):
        options.GlobalTag = "GR_P_V41_AN3::All"
    elif (iData.find("PromptD")==0):
        options.GlobalTag = "GR_P_V42_AN3::All"
    else:
        options.GlobalTag = "GR_P_V42_AN3::All"
else:
    options.mcInfo = 1
    options.GlobalTag = "START53_V7G::All"


#-- Input Source
if options.files:
    process.source.fileNames = cms.untracked.vstring (options.files)

if iRunData == True:
    process.source.fileNames = [iFileData]
else:
    process.source.fileNames = [iFileMC]
    
process.maxEvents.input = options.maxEvents
# Due to problem in production of LM samples: same event number appears multiple times
if iRunData == False:
    process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')


#-- Calibration tag
if options.GlobalTag:
    process.GlobalTag.globaltag = options.GlobalTag


############################# START SUSYPAT specifics ####################################
from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
#Apply SUSYPAT
addDefaultSUSYPAT(process,options.mcInfo,options.hltName,options.jetCorrections,options.mcVersion,options.jetTypes,options.doValidation,options.doExtensiveMatching,options.doSusyTopProjection,options.doType1MetCorrection,options.doType0MetCorrection)
SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )
############################## END SUSYPAT specifics ####################################


#-- TimeReport and TrigReport after running
process.options.wantSummary = True


#-- HLT selection
import HLTrigger.HLTfilters.hltHighLevel_cfi as hlt
if options.hltSelection:
    process.hltFilter = hlt.hltHighLevel.clone(
        HLTPaths = cms.vstring(options.hltSelection),
        TriggerResultsTag = cms.InputTag("TriggerResults","",options.hltName),
        throw = False
    )
    process.susyPatDefaultSequence.replace(process.eventCountProducer, process.eventCountProducer * process.hltFilter)


#-- Output module configuration
process.out.fileName = options.output


#-- Custom settings
process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files???)
process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections
process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )
if options.hltSelection:
    process.out.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring("p"))
if options.addKeep:
    process.out.outputCommands.extend(options.addKeep)


#-- Good Vertex filter
process.goodVertices = cms.EDFilter("VertexSelector",
	filter = cms.bool(False),
	src = cms.InputTag("offlinePrimaryVertices"),
	cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.rho < 2")
)


#-- Good collision filter
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskAlgoTrigConfig_cff')
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.L1T1coll=process.hltLevel1GTSeed.clone()
process.L1T1coll.L1TechTriggerSeeding = cms.bool(True)
#process.L1T1coll.L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND NOT 43) OR (43 AND NOT 42))')
process.L1T1coll.L1SeedsLogicalExpression = cms.string('0 AND NOT (36 OR 37 OR 38 OR 39) ')


#-- Physics Declared
process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'


#-- HLT Trigger Selection
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.andOr = True   # True = OR, False = AND
process.hltHighLevel.throw = False  # tolerate if triggers not available
if (iTrigger.find("MET")==0):
    process.hltHighLevel.HLTPaths = cms.vstring("HLT_MET120_HBHENoiseCleaned_v*","HLT_MonoCentralPFJet80_PFMETnoMu*")
elif (iTrigger.find("SingleMu")==0):
    process.hltHighLevel.HLTPaths = cms.vstring("HLT_IsoMu24_eta2p1_v*","HLT_Mu40_eta2p1_v*")
elif (iTrigger.find("DoubleMu")==0):
    process.hltHighLevel.HLTPaths = cms.vstring("HLT_Mu17_Mu8_v*")
elif (iTrigger.find("SingleElectron")==0):
    process.hltHighLevel.HLTPaths = cms.vstring("HLT_Ele27_WP80_v*")
elif (iTrigger.find("DoubleElectron")==0):
    process.hltHighLevel.HLTPaths = cms.vstring("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*")
elif (iTrigger.find("Physics")==0):
    process.hltHighLevel.HLTPaths = cms.vstring("HLT_Physics_v*")
elif (iTrigger.find("NoTrig")==0):
    process.hltHighLevel.HLTPaths = cms.vstring("*")
else:
    process.hltHighLevel.HLTPaths = cms.vstring("HLT_MET120_HBHENoiseCleaned_v*","HLT_MonoCentralPFJet80_PFMETnoMu*")
## Singal run with NoTrig
if iSignal == True:
    process.hltHighLevel.HLTPaths = cms.vstring("*")


############################# START Noise Flags ####################################
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

## The ECAL dead cell trigger primitive filter _______________________________||
process.load('RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi')

## The EE bad SuperCrystal filter ____________________________________________||
process.load('RecoMET.METFilters.eeBadScFilter_cfi')

## The ECAL laser correction filter
process.load('RecoMET.METFilters.ecalLaserCorrFilter_cfi')

## The Good vertices collection needed by the tracking failure filter ________||
process.goodVertices = cms.EDFilter(
  "VertexSelector",
  filter = cms.bool(False),
  src = cms.InputTag("offlinePrimaryVertices"),
  cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.rho < 2")
)

## The tracking failure filter _______________________________________________||
process.load('RecoMET.METFilters.trackingFailureFilter_cfi')

## Muons with wrong momenta __________________________________________________||
process.load('RecoMET.METFilters.inconsistentMuonPFCandidateFilter_cfi')
process.load('RecoMET.METFilters.greedyMuonPFCandidateFilter_cfi')
############################# END Noise Flags ####################################


############################# START PDFWeight Flags ####################################
process.pdfWeights1 = cms.EDProducer(
    "PdfWeightProducer",
    # Fix POWHEG if buggy (this PDF set will also appear on output,
    # so only two more PDF sets can be added in PdfSetNames if not "")
    #FixPOWHEG = cms.untracked.string("cteq66.LHgrid"),
    #GenTag = cms.untracked.InputTag("genParticles"),
    PdfInfoTag = cms.untracked.InputTag("generator"),
    PdfSetNames = cms.untracked.vstring(
    "cteq66.LHgrid"
    )
)
process.pdfWeights2 = cms.EDProducer(
    "PdfWeightProducer",
    # Fix POWHEG if buggy (this PDF set will also appear on output,
    # so only two more PDF sets can be added in PdfSetNames if not "")
    #FixPOWHEG = cms.untracked.string("cteq66.LHgrid"),
    #GenTag = cms.untracked.InputTag("genParticles"),
    PdfInfoTag = cms.untracked.InputTag("generator"),
    PdfSetNames = cms.untracked.vstring( 
    "MSTW2008nlo68cl.LHgrid"
    )
)
process.pdfWeights3 = cms.EDProducer(
    "PdfWeightProducer",
    # Fix POWHEG if buggy (this PDF set will also appear on output,
    # so only two more PDF sets can be added in PdfSetNames if not "")
    #FixPOWHEG = cms.untracked.string("cteq66.LHgrid"),
    #GenTag = cms.untracked.InputTag("genParticles"),
    PdfInfoTag = cms.untracked.InputTag("generator"),
    PdfSetNames = cms.untracked.vstring(
    "NNPDF20_100.LHgrid"
    )
)
############################# END PDFWeight Flags ####################################


############################# START FIX TYPE0 ####################################
process.patPFMETtype0Corr.correction.par3 = cms.double(0.909209)
process.patPFMETtype0Corr.correction.par2 = cms.double(0.0303531)
process.patPFMETtype0Corr.correction.par1 = cms.double(-0.703151)
process.patPFMETtype0Corr.correction.par0 = cms.double(0.0)
#
process.patPFMETtype0CorrPF.correction.par3 = cms.double(0.909209)
process.patPFMETtype0CorrPF.correction.par2 = cms.double(0.0303531)
process.patPFMETtype0CorrPF.correction.par1 = cms.double(-0.703151)
process.patPFMETtype0CorrPF.correction.par0 = cms.double(0.0)
############################# END FIX TYPE0 ####################################


############################# Ntuple Producer Plugin #############################
process.load("MonoJetAnalysis.NtupleAnalyzer.NtupleAnalyzer_cfi")
process.TFileService                 = cms.Service("TFileService", fileName = cms.string('ntuple.root'))
process.NtupleAnalyzer               = process.NtupleAnalyzerTemplate.clone()
process.NtupleAnalyzer.TriggerTag    = cms.string('TriggerResults::HLT')
process.NtupleAnalyzer.Tracks        = cms.untracked.InputTag("generalTracks")
process.NtupleAnalyzer.PFElectronTag = cms.untracked.InputTag(iPFElectronTag)
process.NtupleAnalyzer.PFMuonTag     = cms.untracked.InputTag(iPFMuonTag)
process.NtupleAnalyzer.PFTauTag      = cms.untracked.InputTag(iPFTauTag)
process.NtupleAnalyzer.PFJetTag      = cms.untracked.InputTag(iPFJetTag)
process.NtupleAnalyzer.PFMETTag      = cms.untracked.InputTag(iPFMETTag)
process.NtupleAnalyzer.jetPtCut      = cms.double(15)
process.NtupleAnalyzer.jetEtaCut     = cms.double(2.4)
process.NtupleAnalyzer.weight        = cms.double(1)
process.NtupleAnalyzer.TIV_ltrack_thr     = cms.double(5)
process.NtupleAnalyzer.TIV_strack_thr     = cms.double(1)
process.NtupleAnalyzer.TIV_dz_thr         = cms.double(1)
process.NtupleAnalyzer.TIV_dxy_thr        = cms.double(1)
process.NtupleAnalyzer.TIV_cone_thr       = cms.double(0.35)
process.NtupleAnalyzer.TIV_inner_cone_thr = cms.double(0.015)
if iRunData == True:
    process.NtupleAnalyzer.isMC     = cms.bool(False)
    process.NtupleAnalyzer.isSignal = cms.double(0)
else:
    process.NtupleAnalyzer.isMC     = cms.bool(True)
    if iSignal == True:
        process.NtupleAnalyzer.isSignal = cms.double(1)
    else:
        process.NtupleAnalyzer.isSignal = cms.double(0)
if (iTrigger.find("MET")==0):
    process.NtupleAnalyzer.triggerUsed = cms.double(1)
elif (iTrigger.find("SingleMu")==0):
    process.NtupleAnalyzer.triggerUsed = cms.double(2)
elif (iTrigger.find("DoubleMu")==0):
    process.NtupleAnalyzer.triggerUsed = cms.double(3)
elif (iTrigger.find("SingleElectron")==0):
    process.NtupleAnalyzer.triggerUsed = cms.double(4)
elif (iTrigger.find("DoubleElectron")==0):
    process.NtupleAnalyzer.triggerUsed = cms.double(5)
elif (iTrigger.find("Physics")==0):
    process.NtupleAnalyzer.triggerUsed = cms.double(6)
elif (iTrigger.find("NoTrig")==0):
    process.NtupleAnalyzer.triggerUsed = cms.double(99)
else:
    process.NtupleAnalyzer.triggerUsed = cms.double(1)
## Singal run with NoTrig
if iSignal == True:
    process.NtupleAnalyzer.triggerUsed = cms.double(99)
############################# Ntuple Producer Plugin #############################


############################# Load the PU JetID sequence #############################
process.load("CMGTools.External.pujetidsequence_cff")
process.puJetMva.jets = cms.InputTag(iPFJetTag)
process.puJetId.jets = cms.InputTag(iPFJetTag)
############################# Load the PU JetID sequence #############################


############################# START FIX PF COLLECTION ####################################
#-- Electron
process.pfIsolatedElectronsPF.isolationValueMapsCharged  = cms.VInputTag(cms.InputTag("elPFIsoValueCharged03PFIdPF"))
process.pfIsolatedElectronsPF.deltaBetaIsolationValueMap = cms.InputTag("elPFIsoValuePU03PFIdPF")
process.pfIsolatedElectronsPF.isolationValueMapsNeutral  = cms.VInputTag(cms.InputTag("elPFIsoValueNeutral03PFIdPF"),
                                                                         cms.InputTag("elPFIsoValueGamma03PFIdPF"))
process.patElectronsPF.isolationValues = cms.PSet(
    pfNeutralHadrons = cms.InputTag("elPFIsoValueNeutral03PFIdPF"),
    pfChargedAll = cms.InputTag("elPFIsoValueChargedAll03PFIdPF"),
    pfPUChargedHadrons = cms.InputTag("elPFIsoValuePU03PFIdPF"),
    pfPhotons = cms.InputTag("elPFIsoValueGamma03PFIdPF"),
    pfChargedHadrons = cms.InputTag("elPFIsoValueCharged03PFIdPF")
)

#-- Tau & Jet
process.pfNoTauPF.enable = cms.bool(False)
############################## END FIX PF COLLECTION #####################################


#-- Execution path
process.p0  = cms.Path(process.noscraping)
process.p1  = cms.Path(process.HBHENoiseFilter)
process.p2  = cms.Path(process.CSCTightHaloFilter)
process.p3  = cms.Path(process.CSCLooseHaloFilter)
process.p4  = cms.Path(process.hcalLaserEventFilter)
process.p5  = cms.Path(process.EcalDeadCellTriggerPrimitiveFilter) 
process.p6  = cms.Path(process.goodVertices * process.trackingFailureFilter)
process.p7  = cms.Path(process.eeBadScFilter)
process.p8  = cms.Path(process.greedyMuonPFCandidateFilter*process.inconsistentMuonPFCandidateFilter)
process.p9  = cms.Path(process.ecalLaserCorrFilter)
process.p10 = cms.Path(process.primaryVertexFilter)
process.p11 = cms.Path(process.hltHighLevel)
process.p   = cms.Path(process.susyPatDefaultSequence*process.puJetIdSqeuence)
process.ntp = cms.EndPath(process.NtupleAnalyzer)

if iSignal == True:
    process.ntp.replace(process.NtupleAnalyzer,process.pdfWeights1*process.NtupleAnalyzer)


#-- Remove SUSYPAT.root
del(process.out)
del(process.outpath)


#-- Dump config
iFileName = "Monojet"
if iRunData == True:
    iFileName += "_DATA_"
    iFileName += iData
    iFileName += "_"
else:
    if iSignal == True:
        iFileName += "_MCSignal_"
    else:
        iFileName += "_MC_"
iFileName += iTrigger
iFileName += "_cfg.py"
file = open(iFileName,'w')
file.write(str(process.dumpPython()))
file.close()
