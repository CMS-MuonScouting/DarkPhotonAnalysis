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
    False, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether or not to ask the event to fire a trigger used in the analysis'
)

params.register(
    'filterMuons', 
    False, 
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
    '101X_dataRun2_Prompt_v11', 
    VarParsing.multiplicity.singleton,VarParsing.varType.string,
    'Process name for the HLT paths'
)

params.register(
    'GlobalTagMC', 
    '102X_upgrade2018_realistic_v15', 
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
    wantSummary      = cms.untracked.bool(False),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

# How many events to process
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# Input EDM files
process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring([
#	'/store/data/Run2018C/ScoutingPFMuon/RAW/v1/000/320/065/00000/0062203A-118E-E811-8326-FA163E1C334D.root',
       #'/store/data/Run2018A/ScoutingPFMuon/RAW/v1/000/316/569/00000/D6AB8ED4-7F65-E811-BCCC-FA163ED6BA41.root',
#	'/store/data/Run2018A/ScoutingPFMuon/RAW/v1/000/316/569/00000/7C89F148-8E65-E811-82AF-FA163EE95896.root',

#	'/store/data/Run2018A/ScoutingPFMuon/RAW/v1/000/316/766/00000/00F2EA01-9065-E811-B74C-FA163E01E6A8.root',
#	'/store/data/Run2018A/ScoutingPFMuon/RAW/v1/000/316/716/00000/380CA87D-9165-E811-BAB0-FA163E2908BD.root',
#	'/store/data/Run2018A/ScoutingPFMuon/RAW/v1/000/316/944/00000/2CC668CD-9165-E811-9154-02163E019FEA.root',
#	'/store/data/Run2018A/ScoutingPFMuon/RAW/v1/000/316/928/00000/0AF24D1E-9365-E811-924E-FA163E3EC021.root',
#	'/store/data/Run2018A/ScoutingPFMuon/RAW/v1/000/316/716/00000/7E80212A-9365-E811-A0B4-FA163E0A0A94.root'
	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v2/00000/21C3D4A5-B75F-B141-902A-EDA977914093.root',
	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v2/00000/51CD5D75-CD9B-1A43-B987-BA54190A0961.root',
	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v2/00000/21C3D4A5-B75F-B141-902A-EDA977914093.root',
	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v2/00000/F9AC6615-86E8-AC4A-8CF5-0E216199AD1A.root',
'	/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v2/00000/1B2E0CD1-84F8-1E47-95D2-11E931C72853.root',
	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v2/00000/342F8B89-93FE-DD43-95BE-C6766A5B3D56.root',
	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v2/00000/424A6AC8-24DA-3546-B90C-304E601993B5.root'


#	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v1/00000/1A456290-FB02-E24A-9F46-11706EE74E69.root',
#	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v1/00003/FFA1B3FE-866F-AF47-B847-CBEE3F1FD4FD.root',
#	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v1/00003/F5EC7431-9450-DD4B-9795-A3DD9D432F58.root',
#	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v1/00003/352FE5CB-949A-1E41-ABB1-1700BBDD8B6F.root',
#	'/store/mc/RunIIAutumn18DRPremix/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/AODSIM/102X_upgrade2018_realistic_v15-v1/00003/736B416D-C7E5-7D4B-9AD3-3738BF70A85D.root',

#	'/store/data/Run2018C/ScoutingPFMuon/RAW/v1/000/320/185/00000/E2BE9426-6B8F-E811-A5E1-FA163E46A172.root'
	])
)

# Load the standard set of configuration modules
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')

##--- l1 stage2 digis ---
process.load("EventFilter.L1TRawToDigi.gtStage2Digis_cfi")
process.gtStage2Digis.InputLabel = cms.InputTag( "hltFEDSelectorL1" )
process.load('PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff')

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

from DarkPhotonAnalysis.DimuonAnalysis2018.TriggerPaths_cfi import getL1Conf

# Make tree
process.mmtree = cms.EDAnalyzer('PFScoutingTreeMaker2018',
	isMC             = cms.bool(params.isMC),
	xsec             = cms.double(params.xsec),
	useLHEWeights    = cms.bool(params.useWeights),
	applyHLTFilter   = cms.bool(params.filterTrigger),
	require2Muons    = cms.bool(params.filterMuons),
	storeReducedInfo = cms.bool(params.reducedInfo),
    	triggerresults   = cms.InputTag("TriggerResults", "", params.trigProcess),
	doL1 = cms.bool(True),
        triggerConfiguration = cms.PSet(
    		hltResults            = cms.InputTag('TriggerResults','','HLT'),
    		l1tResults            = cms.InputTag(''),
    		daqPartitions         = cms.uint32(1),
    		l1tIgnoreMaskAndPrescale = cms.bool(False),
    		throw                 = cms.bool(False)
  	),
	ReadPrescalesFromFile = cms.bool( False ),
        AlgInputTag = cms.InputTag("gtStage2Digis"),
        l1tAlgBlkInputTag = cms.InputTag("gtStage2Digis"),
        l1tExtBlkInputTag = cms.InputTag("gtStage2Digis"),
        l1Seeds           = cms.vstring(getL1Conf()),
	#vertices         = cms.InputTag("hltScoutingMuonPacker","displacedVtx"),
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

