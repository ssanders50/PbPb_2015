import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process("FlatCalib")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load("RecoHI.HiEvtPlaneAlgos.HiEvtPlane_cfi")
process.load("HeavyIonsAnalysis.HiEvtPlaneCalib.evtplanecalibtree_cfi")
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.load("HeavyIonsAnalysis.Configuration.hfCoincFilter_cff")
process.load("HeavyIonsAnalysis.Configuration.analysisFilters_cff")
process.load("HeavyIonsAnalysis.Configuration.collisionEventSelection_cff")

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v13', '')
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery=1000

import FWCore.PythonUtilities.LumiList as LumiList
goodLumiSecs = LumiList.LumiList(filename = 'Cert_262548-263757_PromptReco_HICollisions15_JSON.txt').getCMSSWString().split(',')

readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(),
                             inputCommands=cms.untracked.vstring(
        'keep *',
        'drop *_hiEvtPlane_*_*'
        )
)


#process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(
#       'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias2/AOD/25Aug2016-v1/00000/D6E868DA-7473-E611-B054-003048F30FD8.root',
#       'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias2/AOD/25Aug2016-v1/00000/3E6F7414-7873-E611-A778-90B11C44432D.root',
#       'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias2/AOD/25Aug2016-v1/00000/E096AAB4-8273-E611-9B34-003048F4FE02.root',
#       'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias2/AOD/25Aug2016-v1/00000/1A12E2A3-8373-E611-9402-F01FAFD69122.root',
#       'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias2/AOD/25Aug2016-v1/00000/741A50F5-8E73-E611-B7EF-003048F316D8.root',
#       'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias2/AOD/25Aug2016-v1/00000/B8DFAA75-9173-E611-9511-F01FAFE15E27.root',
#       'root://cmsxrootd.fnal.gov//store/hidata/HIRun2015/HIMinimumBias2/AOD/25Aug2016-v1/00000/5E9B6CF1-9273-E611-8049-003048F310DC.root'
#       ),
#                             inputCommands=cms.untracked.vstring(
#        'keep *',
#        'drop *_hiEvtPlane_*_*'
#        )
#)

#process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(
#       'file:pixeltracking_1.root'
#       ),
#                             inputCommands=cms.untracked.vstring(
#        'keep *',
#        'drop *_hiEvtPlane_*_*'
#        )
#                             )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("calib.root")
)
# MinBias trigger selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.minbiasHLT = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.minbiasHLT.HLTPaths = [
#    "HLT_HIL1MinimumBiasHF1AND_*",
#    "HLT_HIL1MinimumBiasHF2AND_*"
#]
process.minbiasHLT.HLTPaths = [
    "HLT_HIL1MinimumBiasHF1AND*",
    "HLT_HIL1MinimumBiasHF2AND*"
]
process.minbiasHLT.andOr = cms.bool(True)
process.minbiasHLT.throw = cms.bool(False)
# Event Selection
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('HeavyIonsAnalysis.EventAnalysis.HIClusterCompatibilityFilter_cfi')
process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)
process.clusterCompatibilityFilter.clusterTrunc = cms.double(2.0)

process.eventSelection = cms.Sequence(
    process.hfCoincFilter3
    + process.primaryVertexFilter
    + process.clusterCompatibilityFilter
)



process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.hiEvtPlane.loadDB = cms.bool(False)
process.hiEvtPlane.trackTag = cms.InputTag("hiGeneralAndPixelTracks")
process.evtPlaneCalibTree.trackTag = cms.InputTag("hiGeneralAndPixelTracks");
process.p = cms.Path(process.minbiasHLT*process.eventSelection*process.centralityBin* process.hiEvtPlane * process.evtPlaneCalibTree)



                        

