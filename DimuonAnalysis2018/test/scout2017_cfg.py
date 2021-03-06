import FWCore.ParameterSet.Config as cms

# Set parameters externally 
from FWCore.ParameterSet.VarParsing import VarParsing
params = VarParsing('analysis')

params.register(
    'isMC', 
    True, 
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
    wantSummary      = cms.untracked.bool(False) 
)

# How many events to process
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

# Input EDM files
process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring([
#		'file:/afs/cern.ch/user/b/bortigno/public/darkphoton/DP_MZd35Epsilon2e-2_fall17_AODSIM_step3.root',
		'/store/mc/RunIIAutumn18DRPremix/DarkPhotonToMuMu_M70_madgraph_pythia8_TuneCP5/AODSIM/102X_upgrade2018_realistic_v15-v1/20000/CE9FD7CE-6BEA-DC44-B5D9-270A5A1EC3C1.root'
	#	'/store/data/Run2018D/ScoutingCaloMuon/RAW/v1/000/321/283/00000/0AF726D6-E09F-E811-966B-FA163E89B4C8.root',
	#	'/store/data/Run2018D/ScoutingCaloMuon/RAW/v1/000/321/283/00000/169D2769-D79F-E811-8F52-FA163EA4D9B7.root',
	#	'/store/data/Run2018D/ScoutingCaloMuon/RAW/v1/000/321/283/00000/22111059-DE9F-E811-9951-FA163E29485B.root',
	#	'/store/data/Run2018D/ScoutingCaloMuon/RAW/v1/000/321/283/00000/26D4821F-D99F-E811-B874-FA163E21C6D9.root',
	#	'/store/data/Run2018D/ScoutingCaloMuon/RAW/v1/000/321/283/00000/28D7FABE-DA9F-E811-B4CE-FA163E35DF95.root',
        	
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
process.mmtree = cms.EDAnalyzer('ScoutingTreeMaker2018',
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
    		#l1tIgnoreMask         = cms.bool(False),
   		#l1techIgnorePrescales = cms.bool(False),
    		throw                 = cms.bool(False)
  	),
	ReadPrescalesFromFile = cms.bool( False ),
        AlgInputTag = cms.InputTag("gtStage2Digis"),
        l1tAlgBlkInputTag = cms.InputTag("gtStage2Digis"),
        l1tExtBlkInputTag = cms.InputTag("gtStage2Digis"),
        l1Seeds           = cms.vstring(getL1Conf()),
	vertices          = cms.InputTag("hltScoutingMuonPackerCalo","displacedVtx"),
#	beamspot          = cms.InputTag("")
	muons             = cms.InputTag("hltScoutingMuonPackerCalo"),
	#pfcands          = cms.InputTag("hltScoutingPFPacker"),
	rho               = cms.InputTag("hltScoutingCaloPacker", "rho"),
    	pileupinfo        = cms.InputTag("addPileupInfo"),
    	geneventinfo      = cms.InputTag("generator"),
    	gens              = cms.InputTag("genParticles", "", "HLT")
)

# Analysis path
if params.isMC : 
    process.p = cms.Path(process.gentree + process.mmtree)
else : 
    process.p = cms.Path(  process.gtStage2Digis + process.mmtree)

