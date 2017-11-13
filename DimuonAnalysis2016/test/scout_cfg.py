import FWCore.ParameterSet.Config as cms

# Set parameters externally 
from FWCore.ParameterSet.VarParsing import VarParsing
params = VarParsing('analysis')

params.register(
    'isMC', 
    False, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether the sample is simulation or data'
)

params.register(
    'useWeights', 
    False, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether or not to use the events weights from a Monte Carlo generator'
)

params.register(
    'filterTrigger', 
    True, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether or not to ask the event to fire a trigger used in the analysis'
)

params.register(
    'filterMuons', 
    True, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether or not to ask the event to contain at least two muons'
)

params.register(
    'reducedInfo', 
    False, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether or not to store just the reduced information'
)

params.register(
    'trigProcess', 
    'HLT', 
    VarParsing.multiplicity.singleton,VarParsing.varType.string,
    'Process name for the HLT paths'
)

params.register(
    'GlobalTagData', 
    '80X_dataRun2_2016SeptRepro_v7', 
    VarParsing.multiplicity.singleton,VarParsing.varType.string,
    'Process name for the HLT paths'
)

params.register(
    'GlobalTagMC', 
    '80X_mcRun2_asymptotic_2016_TrancheIV_v8', 
    VarParsing.multiplicity.singleton,VarParsing.varType.string,
    'Process name for the HLT paths'
)

params.register(
    'xsec', 
    0.001, 
    VarParsing.multiplicity.singleton,VarParsing.varType.float,
    'Cross-section for a Monte Carlo Sample'
)

# Define the process
process = cms.Process("LL")

# Parse command line arguments
params.parseArguments()

# Message Logger settings
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Set the process options -- Display summary at the end, enable unscheduled execution
process.options = cms.untracked.PSet( 
    allowUnscheduled = cms.untracked.bool(True),
    wantSummary      = cms.untracked.bool(False) 
)

# How many events to process
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000000) )

# Input EDM files
process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring([
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/680/00000/CE8246B6-3913-E611-8815-02163E0128EB.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/680/00000/D8376DB6-5813-E611-A451-02163E011BFF.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/681/00000/B6837F6F-4013-E611-A63F-02163E0133D1.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/728/00000/6AD7A7C3-AC13-E611-AD76-02163E011CA6.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/729/00000/9C9CB45D-AF13-E611-B108-02163E011ADA.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/748/00000/4E4F02EF-C013-E611-92E8-02163E0129B3.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/750/00000/54274C30-C113-E611-8A5F-02163E0126FE.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/760/00000/C8F06C80-D613-E611-8CE6-02163E011E5F.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/761/00000/1AD1CCA3-DA13-E611-A2C0-02163E013872.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/761/00000/40D7CEA7-DA13-E611-A760-02163E0145AC.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/761/00000/965A297E-DA13-E611-AF4F-02163E01373A.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/761/00000/D86F9FE2-DA13-E611-8EC0-02163E01185F.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/762/00000/24EAD19C-E113-E611-904F-02163E01382E.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/762/00000/3017A99B-E113-E611-ABDE-02163E0136B1.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/762/00000/5E311BFF-E113-E611-8481-02163E0135EC.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/762/00000/8C592512-E213-E611-9314-02163E012950.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/762/00000/A6002E9E-E113-E611-AF16-02163E012950.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/771/00000/A0F81344-EB13-E611-9432-02163E0143A8.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/774/00000/C66A780C-F913-E611-B109-02163E01431F.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/775/00000/A89F5119-3314-E611-B73B-02163E011F11.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/776/00000/8281C382-0A14-E611-8DF1-02163E0145FE.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/776/00000/DC3DD94F-0C14-E611-93A8-02163E013740.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/782/00000/F6261A33-3014-E611-8170-02163E013517.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/783/00000/A0DD4C8E-3C14-E611-A597-02163E0137A5.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/784/00000/AAEFD802-4D14-E611-9BE5-02163E013643.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/785/00000/5C20070A-5314-E611-8158-02163E013864.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/786/00000/DE8F72D2-5514-E611-A667-02163E0137AB.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/787/00000/F48D645F-5914-E611-86E4-02163E0129BE.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/791/00000/3C94BF7E-6D14-E611-8DF5-02163E013952.root',
        '/store/data/Run2016B/ScoutingPFHT/RAW/v1/000/272/791/00000/B41A7D19-6C14-E611-B5C4-02163E014601.root',
	])
)

# Load the standard set of configuration modules
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')

# Load the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
if params.isMC : 
    process.GlobalTag.globaltag = params.GlobalTagMC
else :
    process.GlobalTag.globaltag = params.GlobalTagData

# Define the services needed for the treemaker
process.TFileService = cms.Service("TFileService", 
    fileName = cms.string("scout.root")
)

# Tree for the generator weights
process.gentree = cms.EDAnalyzer("LHEWeightsTreeMaker",
    lheInfo = cms.InputTag("externalLHEProducer"),
    genInfo = cms.InputTag("generator"),
    useLHEWeights = cms.bool(params.useWeights)
)

# Make tree
process.mmtree = cms.EDAnalyzer('ScoutingTreeMaker',
	isMC             = cms.bool(params.isMC),
	xsec             = cms.double(params.xsec),
	useLHEWeights    = cms.bool(params.useWeights),
	applyHLTFilter   = cms.bool(params.filterTrigger),
	require2Muons    = cms.bool(params.filterMuons),
	storeReducedInfo = cms.bool(params.reducedInfo),
    triggerresults   = cms.InputTag("TriggerResults", "", params.trigProcess),
	vertices         = cms.InputTag("hltScoutingPFPacker"),
	muons            = cms.InputTag("hltScoutingMuonPacker"),
	pfcands          = cms.InputTag("hltScoutingPFPacker"),
	rho              = cms.InputTag("hltScoutingPFPacker", "rho"),
    pileupinfo       = cms.InputTag("addPileupInfo"),
    geneventinfo     = cms.InputTag("generator"),
    gens             = cms.InputTag("genParticles", "", "HLT")
)

# Analysis path
if params.isMC : 
    process.p = cms.Path(process.gentree + process.mmtree)
else : 
    process.p = cms.Path(                  process.mmtree)

