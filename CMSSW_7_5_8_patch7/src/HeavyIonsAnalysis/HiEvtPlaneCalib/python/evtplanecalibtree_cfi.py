import FWCore.ParameterSet.Config as cms

evtPlaneCalibTree = cms.EDAnalyzer("EvtPlaneCalibTree",
                            vertexTag_=cms.InputTag("hiSelectedVertex"),
                            centralityTag_=cms.InputTag("hiCentrality"),
                            centralityBinTag_ = cms.InputTag("centralityBin","HFtowers"),
                            centralityVariable = cms.string("HFtowers"),
                            inputPlanesTag_ = cms.InputTag("hiEvtPlane",""),
                            FlatOrder_ = cms.untracked.int32(9),
                            NumFlatBins_ = cms.untracked.int32(40),
                            CentBinCompression_ = cms.untracked.int32(5),
                            minet_ = cms.untracked.double(-1.),
                            maxet_ = cms.untracked.double(-1.),
                            minpt_ = cms.untracked.double(0.3),
                            maxpt_ = cms.untracked.double(3.0),
                            flatnvtxbins = cms.int32(10),
                            flatminvtx = cms.double(-25.0),
                            flatdelvtx = cms.double(5.0),
#                            dzerr_ = cms.untracked.double(10.),
                            dzdzerror_ = cms.untracked.double(3.),
                            d0d0error_ = cms.untracked.double(3.),
                            pterrorpt_ = cms.untracked.double(0.1),
                            chi2_ = cms.untracked.double(40.),
                            useNtrkBins_ = cms.untracked.bool(False),
                            genMC = cms.untracked.bool(False),
                            bTag_ = cms.InputTag("mcEvtPlane","b","FlatCalib"),
                             bypassCentrality_ = cms.untracked.bool(False),
                            trackTag = cms.InputTag("hiGeneralTracks"),
                            )
                            




    
