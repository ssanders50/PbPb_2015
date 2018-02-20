import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os
import sys
ivars = VarParsing.VarParsing('standard')


ivars.register ('eff',
                'NULL',
                mult=ivars.multiplicity.singleton,
                mytype=ivars.varType.string,
                info="efficiency file")

ivars.parseArguments()

process = cms.Process("VNANAL")


process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load("HeavyIonsAnalysis.MCEvtPlane.MCHiEvtPlane_cfi")
process.load("RecoHI.HiEvtPlaneAlgos.hiEvtPlaneFlat_cfi")
process.load("HeavyIonsAnalysis.VNAnalysis.vnanalyzer_cfi")
process.load("HeavyIonsAnalysis.HiEvtPlaneCalib.evtplanecalibtree_cfi")
process.load("HeavyIonsAnalysis.QWNtrkOfflineProducer.QWGenEvent_cfi")
process.load("CondCore.CondDB.CondDB_cfi")
process.load('Configuration.StandardSequences.Generator_cff')

#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
#process.GlobalTag.toGet.extend([
#   cms.PSet(record = cms.string("HeavyIonRcd"),
#      tag = cms.string("CentralityTable_HFtowers200_DataXeXe_eff942_run2v9313x02_offline"),
#      connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
#      label = cms.untracked.string("HFtowersCymbal5Ev8")
#   ),
#])

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery=5000

process.CondDB.connect = "sqlite_file:HeavyIonRPRcd_PbPb2015_AMPT2015_melt.db"
process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                       process.CondDB,
                                       toGet = cms.VPSet(cms.PSet(record = cms.string('HeavyIonRPRcd'),
                                                                  tag = cms.string('HeavyIonRPRcd')
                                                                  )
                                                         )
                                      )
#process.es_prefer_flatparms = cms.ESPrefer('PoolDBESSource','')


import HLTrigger.HLTfilters.hltHighLevel_cfi

process.hltMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMB.HLTPaths = [
	"HLT_HIL1MinimumBiasHF_OR_SinglePixelTrack_part*"
]
process.hltMB.andOr = cms.bool(True)
process.hltMB.throw = cms.bool(False)

process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')
process.hiCentrality.produceHFhits = False
process.hiCentrality.produceHFtowers = True
process.hiCentrality.produceEcalhits = False
process.hiCentrality.produceZDChits = False
process.hiCentrality.produceETmidRapidity = True
process.hiCentrality.producePixelhits = False
process.hiCentrality.produceTracks = True
process.hiCentrality.producePixelTracks = False
process.hiCentrality.reUseCentrality = False
process.hiCentrality.srcTracks = cms.InputTag("generalTracks")
process.hiCentrality.srcVertex = cms.InputTag("offlinePrimaryVertices")


#process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
#process.centralityBin.Centrality = cms.InputTag("hiCentrality")
#process.centralityBin.centralityVariable = cms.string("HFtowers")
#process.centralityBin.nonDefaultGlauberModel = cms.string("Cymbal5Ev8")


#import FWCore.PythonUtilities.LumiList as LumiList
#goodLumiSecs = LumiList.LumiList(filename = ivars.lumifile ).getCMSSWString().split(',')

readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(),
                             inputCommands=cms.untracked.vstring(
        'keep *'
        )
)



#process.source = cms.Source ("PoolSource",
#        fileNames = cms.untracked.vstring("file:/home/sanders/PbPb_2015/VNAnalysis/amptDefault_cfi_py_GEN_18.root")
#                             )

#process.source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring(
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_1.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_10.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_100.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_101.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_102.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_103.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_104.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_105.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_106.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_107.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_108.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_109.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_11.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_110.root',
#                'root://cmsxrootd.fnal.gov//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_199.root'
#        ),
#                             inputCommands=cms.untracked.vstring(
#        'keep *',
#        'drop *_hiEvtPlane_*_*'
#        )
#                             )


process.TFileService = cms.Service("TFileService",
    fileName = cms.string("vnanal.root")
)


process.dump = cms.EDAnalyzer("EventContentAnalyzer")

process.vnanalyzer.offsetFile = cms.untracked.string("offset_PbPb2015_AMPT_melt.root" )
process.vnanalyzer.effFile = cms.untracked.string( ivars.eff )

process.QWEvent = cms.EDProducer("QWGenEventProducer",
               trackSrc  = cms.untracked.InputTag("genParticles","","VNANAL"),
               isPrompt  = cms.untracked.bool(False),
               Etamin = cms.untracked.double(-5.),
               Etamax = cms.untracked.double(5.),
               ptMin = cms.untracked.double(0.),
               ptMax = cms.untracked.double(15.)
               )

process.QWHIEvent = cms.EDProducer("QWHepMCProducer",
		src = cms.untracked.InputTag("generator")
		)

process.bFilter = cms.EDFilter("QWDoubleFilter",
		src = cms.untracked.InputTag("QWHIEvent", "b"),
		dmin = cms.untracked.double(0.0),
		dmax = cms.untracked.double(10.0)
		)

process.mcEvtPlane.loadDB=cms.bool(True)
process.hiEvtPlaneFlat.trackTag = cms.InputTag("mcEvtPlane","","VNANAL")
process.hiEvtPlaneFlat.vertexTag = cms.InputTag("mcEvtPlane","","VNANAL")
process.hiEvtPlaneFlat.nonDefaultGlauberModel = cms.string("")


process.vnanalyzer.vertexTag_ = cms.InputTag("mcEvtPlane","","VNANAL")
process.vnanalyzer.inputPlanesTag_ = cms.InputTag("mcEvtPlane","","VNANAL")
process.vnanalyzer.centralityBinTag_=cms.InputTag("mcEvtPlane","centralityBin","VNANAL")
process.vnanalyzer.trackTag_ = cms.InputTag("mcEvtPlane","","VNANAL")
process.vnanalyzer.genMC = cms.untracked.bool(True)
process.mcEvtPlane.bToCentCalib = cms.vdouble( 
    0,577,817,1002,1158,1294,1417,1530,1637,1736,1831,
    1921,2006,2089,2167,2244,2317,2388,2458,2526,2591,
    2656,2719,2780,2841,2900,2958,3015,3071,3125,3179,
    3232,3285,3336,3386,3435,3484,3533,3581,3627,3673,
    3718,3764,3809,3852,3895,3938,3980,4023,4064,4105,
    4146,4187,4227,4267,4306,4345,4384,4422,4459,4497,
    4535,4573,4610,4646,4682,4719,4754,4789,4825,4860,
    4894,4929,4963,4997,5030,5063,5096,5128,5161,5194,
    5226,5259,5290,5321,5353,5385,5416,5448,5478,5509,
    5540,5570,5600,5630,5660,5689,5719,5748,5777,5806,
    5834,5863,5892,5921,5949,5978,6006,6033,6061,6089,
    6117,6144,6172,6199,6225,6253,6280,6307,6333,6360,
    6386,6413,6439,6465,6491,6517,6542,6567,6592,6618,
    6644,6669,6694,6719,6744,6769,6794,6819,6844,6868,
    6892,6917,6941,6965,6989,7014,7038,7062,7085,7109,
    7133,7157,7181,7205,7228,7252,7276,7300,7324,7347,
    7372,7395,7419,7444,7468,7493,7518,7542,7568,7593,
    7619,7645,7671,7697,7724,7752,7780,7808,7838,7868,
    7899,7930,7963,7997,8032,8069,8109,8150,8193,8239,
    8288,8342,8402,8469,8546,8635,8747,8898,9141        
    )

#process.p = cms.Path(process.QWEvent*process.QWHIEvent*process.mcEvtPlane)
process.p = cms.Path(process.GeneInfo*process.QWEvent*process.QWHIEvent*process.mcEvtPlane*process.vnanalyzer)
