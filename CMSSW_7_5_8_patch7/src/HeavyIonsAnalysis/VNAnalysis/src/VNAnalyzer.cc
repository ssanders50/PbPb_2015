// -*- C++ -*-
//
// Package:    VNAnalyzer
// Class:      VNAnalyzer
// 

// system include files
#include <memory>
#include <algorithm>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "Math/Vector3D.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include <DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h>
#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CondFormats/DataRecord/interface/HeavyIonRPRcd.h"
#include "CondFormats/DataRecord/interface/HeavyIonRcd.h"
#include "CondFormats/HIObjects/interface/CentralityTable.h"
#include "CondFormats/HIObjects/interface/RPFlatParams.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "HeavyIonsAnalysis/VNAnalysis/interface/TrackEfficiency.h"

#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TH1I.h"
#include "TF1.h"
#include "TMath.h"
#include "TRandom.h"
#include <time.h>
#include <cstdlib>
	
#include <vector>
using std::vector;
using std::rand;
using namespace std;
#include "RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneFlatten.h"
#include "RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneList.h"
#include "RecoHI/HiEvtPlaneAlgos/interface/LoadEPDB.h"
using namespace hi;
using namespace edm;

static const int ntrkbins = 25;
static const  double trkBins[]={0, 10, 20, 30, 40, 50, 60, 70, 80, 100, 120, 135, 150, 160, 185, 210, 230, 250, 270, 300, 330, 350, 370, 390, 420, 500};

static const int ncentbins = 13;
static const  double centbins[]={0, 5, 10, 15, 20, 25, 30, 35, 40,  50, 60, 70, 80, 100};

static const int nptbins = 28;
static const float ptbins[]={0.3, 0.4, 0.5,  0.6,  0.8,  1.0,  1.25,  1.50,  2.0,
			      2.5,  3.0,  3.5,  4.0,  5.0,  6.0,  7.0, 8.0, 10., 12.0, 14.0, 16.0,  20.0, 26.0, 35.0, 45.0, 60.0, 80.0, 100., 200.};

static const int netabinsDefault = 12;
static const float etabinsDefault[]={-2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};
static const int nanals = 48;
enum AnalType {
  N1MCm22, N1MCm18, N1MCm14, N1MCm10, N1MCm06,
  N1MCm02, N1MCp22, N1MCp18, N1MCp14, N1MCp10,
  N1MCp06, N1MCp02,   N112A,   N112B,   N123A,
    N123B,     N1A,     N1B,      N2,      
       N3,      N4,      N5,      N6,      N7,     
      N42,    N42A,    N42B,    N42C,    N523,   
    N523A,     N63,    N63A,    N63B,    N63C,
      N62,    N62A,    N723,   N723A,     D24,
     D24A,     D26,    D26A,     D34,    D34A,
    D2232,  D2232A,   D2432,  D2432A
};
string AnalNames[]={
  "N1MCm22", "N1MCm18", "N1MCm14", "N1MCm10","N1MCm06",
  "N1MCm02", "N1MCp22", "N1MCp18", "N1MCp14","N1MCp10",
  "N1MCp06", "N1MCp02",   "N112A",  "N112B",   "N123A",  
    "N123B",     "N1A",     "N1B",     "N2",    
       "N3",      "N4",      "N5",      "N6",     "N7",   
      "N42",    "N42A",    "N42B",    "N42C",   "N523",   
    "N523A",     "N63",    "N63A",    "N63B",   "N63C",
      "N62",   "N62A",     "N723",   "N723A",    "D24",
     "D24A",    "D26",     "D26A",     "D34",   "D34A",
    "D2232", "D2232A",    "D2432",   "D2432A"
};


//
// class declaration
//

class VNAnalyzer : public edm::EDAnalyzer {
public:
  explicit VNAnalyzer(const edm::ParameterSet&);
  ~VNAnalyzer();
      
private:
  int NtrkToBin(int ntrk){
    for(int i = 0; i<=ntrkbins; i++) {
      if(ntrk < trkBins[i]) return i;
    }
    return ntrkbins;
  }
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  bool CaloMatch(const reco::Track & track, const edm::Event & iEvent, unsigned int idx);
  // ----------member data ---------------------------
  int eporder_;

  std::string centralityVariable_;
  std::string centralityLabel_;
  std::string centralityMC_;
  edm::InputTag centralityBinTag_;
  edm::EDGetTokenT<int> centralityBinToken;
  edm::Handle<int> cbin_;
  edm::EDGetTokenT<int> tag_;
  edm::InputTag centralityTag_;
  edm::EDGetTokenT<reco::Centrality> centralityToken;
  edm::Handle<reco::Centrality> centrality_;

  edm::InputTag pfTag_;
  edm::EDGetTokenT<reco::PFCandidateCollection> pfToken_;

  edm::InputTag vertexTag_;
  edm::EDGetTokenT<std::vector<reco::Vertex>> vertexToken;
  edm::Handle<std::vector<reco::Vertex>> vertex_;

  edm::InputTag trackTag_;
  edm::EDGetTokenT<reco::TrackCollection> trackToken;
  edm::Handle<reco::TrackCollection> trackCollection_;

  edm::InputTag inputPlanesTag_;
  edm::EDGetTokenT<reco::EvtPlaneCollection> inputPlanesToken;
  edm::Handle<reco::EvtPlaneCollection> inputPlanes_;

  edm::Service<TFileService> fs;
  TFile * frecenter;
  string offsetFileName;

  double caloCentRef_;
  double caloCentRefWidth_;
  int caloCentRefMinBin_;
  int caloCentRefMaxBin_;

  bool useNtrk_;

  int vs_sell;   // vertex collection size
  float vzr_sell;
  float vzErr_sell;
  TH1D * hcent;
  TH1D * hcentbins;
  TH1D * hcentres;
  TH1D * hptNtrk;
  TH1D * hptNtrkGood;
  TH1I * hNtrkRet;
  //  TH2D * hEff[ntrkbins];
  double centval;
  int ntrkval;
  int Noff;
  double vtx;

  double reso_;
  bool bCaloMatching_;
  int nvtx_;
  double minvz_;
  double maxvz_;
  double dzdzerror_pix_;
  double chi2_;

  double dzdzerror_;
  double d0d0error_;
  double pterror_;

  Double_t epang[NumEPNames];
  Double_t eporig[NumEPNames];
  Double_t epsin[NumEPNames];
  Double_t epcos[NumEPNames];

  Double_t qx[NumEPNames];
  Double_t qy[NumEPNames];
  Double_t q[NumEPNames];
  Double_t epmult[NumEPNames];
  Double_t sumw[NumEPNames];
  Double_t sumw2[NumEPNames];
  Double_t vn[NumEPNames];

  Double_t rescor[NumEPNames];
  Double_t rescorErr[NumEPNames];
  TH1D * hPsi[NumEPNames];
  TH1D * hPsiOffset[NumEPNames];
  TH1D * hPsiFlat[NumEPNames];


  unsigned int runno_;

  TH1D * hNtrk;
  TH1D * hNoff;
  int nEtaBins;
  TH1I * hrun;
  string rpnames[NumEPNames];
  string effTable_;
  TTree * tree;
  TrackEfficiency *teff;
  int FlatOrder_;
  int NumFlatBins_;
  int CentBinCompression_;
  int Noffmin_;
  int Noffmax_;
  TH2D * qxtrk[7];
  TH2D * qytrk[7];
  TH2D * qcnt;
  TH2D * avpt;
  TH2D * res[7][ntrkbins];
  TH2D * resw[7][ntrkbins];
  TH2D * resep[7][ntrkbins];
  TH2D * rescnt[7][ntrkbins];
  TH2D * res12;
  TH2D * resw12;
  TH2D * res23;
  TH2D * resw23;
  
  HiEvtPlaneFlatten * flat[NumEPNames];
  bool loadDB_;
  bool useNtrkBins_; 
  bool bypassCentrality_;
  bool FirstEvent_;
  bool makeTree_;
  bool Recenter_;
  int minrun_;
  int maxrun_;
  TH2D * wqxtrkRef[7][40];
  TH2D * wqytrkRef[7][40];

  int nCentBins_ = 1;
  int ntrack;


  //==============  Harmonics ============
  TH2D * ptav[ntrkbins];
  TH2D * ptcnt[ntrkbins];
  TH2D * badcnt[ntrkbins];
  TH2D * qA[ntrkbins][11];
  TH2D * qB[ntrkbins][11];
  TH1D * qres;
  TH1D * qBA[ntrkbins][11];
  TH1D * qCA[ntrkbins][11];
  TH1D * qCB[ntrkbins][11];
  TH1D * qBAcnt[ntrkbins][11];
  TH1D * qCAcnt[ntrkbins][11];
  TH1D * qCBcnt[ntrkbins][11];
  TH2D * qxav[7][ntrkbins];
  TH2D * qyav[7][ntrkbins];
  TH2D * qxycnt[ntrkbins];
  TH2D * wnA[ntrkbins][11];
  TH2D * wnB[ntrkbins][11];
  TH2D * hTemplate;
  TH2D * qxt = 0;
  TH2D * qyt = 0;
  TH2D * qct = 0;
  TH2D * qxy = 0;
  TH2D * qxxy = 0;
  TH2D * qxyy = 0;
  TH2D * qx2y3 = 0;
  TH2D * qy2x3 = 0;
  TH2D * qx2x2x3;
  TH2D * qx2x3y2;
  TH2D * qx3y2y2;
  TH2D * qx2x2y3;
  TH2D * qx2y2y3;
  TH2D * qy2y2y3;
  TH2D * qcnt3;

  struct qvec {
    TH2D * qA[ntrkbins][11];
    TH2D * qB[ntrkbins][11];
    TH2D * wnA[ntrkbins][11];
    TH2D * wnB[ntrkbins][11];
    TH1D * qBA[ntrkbins][11];
    TH1D * qCA[ntrkbins][11];
    TH1D * qCB[ntrkbins][11];
    TH1D * qBAcnt[ntrkbins][11];
    TH1D * qCAcnt[ntrkbins][11];
    TH1D * qCBcnt[ntrkbins][11];
  } qanal[nanals];

  //===================================

  
  TH2D * Eff_0_5;
  TH2D * Eff_5_10;
  TH2D * Eff_10_30;
  TH2D * Eff_30_50;
  TH2D * Eff_50_100;
  enum    TrackCut {trackUndefine = 0, ppReco = 1, HIReco, Pixel};
  TrackCut sTrackQuality;
  bool TrackQuality_ppReco(const reco::TrackCollection::const_iterator&, const reco::VertexCollection&);
  bool TrackQuality_HIReco(const reco::TrackCollection::const_iterator&, const reco::VertexCollection&);
  bool TrackQuality_Pixel(const reco::TrackCollection::const_iterator&, const reco::VertexCollection&);


  TRandom * ran;
#include "HeavyIonsAnalysis/VNAnalysis/interface/Harmonics.h"
  
  //===================================
  
  int getNoff(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    int N = 0;
    using namespace edm;
    using namespace reco;
    iEvent.getByToken(vertexToken,vertex_);
    VertexCollection recoVertices = *vertex_;
    int primaryvtx = 0;
    double hold_d0d0error_ = d0d0error_;
    double hold_dzdzerror_ = dzdzerror_;
    double hold_pterror_ = pterror_;
    double hold_dzdzerror_pix_ = dzdzerror_pix_;
    double hold_chi2_ = chi2_;
    d0d0error_ = 3.;
    dzdzerror_ = 3.;
    pterror_ = 0.1;
    if(sTrackQuality == ppReco) {
      if ( recoVertices.size() > 100 ) return -1;
      sort(recoVertices.begin(), recoVertices.end(), [](const reco::Vertex &a, const reco::Vertex &b){
	  if ( a.tracksSize() == b.tracksSize() ) return a.chi2() < b.chi2();
	  return a.tracksSize() > b.tracksSize();
	});
    } else {
      sort(recoVertices.begin(), recoVertices.end(), [](const reco::Vertex &a, const reco::Vertex &b){
	  return a.tracksSize() > b.tracksSize();
	});    
    }
    
    vtx = recoVertices[primaryvtx].z();
    if (fabs(vtx) < minvz_ || fabs(vtx) > maxvz_) {
      return -1;
    }        
    
    iEvent.getByLabel(trackTag_,trackCollection_);
    
    for(TrackCollection::const_iterator itTrack = trackCollection_->begin(); itTrack != trackCollection_->end(); ++itTrack) { 
      if ( sTrackQuality == HIReco and not TrackQuality_HIReco(itTrack, recoVertices) ) continue;
      else if ( sTrackQuality == ppReco and not TrackQuality_ppReco(itTrack, recoVertices) ) continue;
      else if ( sTrackQuality == Pixel  and not TrackQuality_Pixel (itTrack, recoVertices) ) continue;
      
      if( itTrack->pt() < 0.4 ) continue;
      ++N;
    }
    d0d0error_ = hold_d0d0error_;
    dzdzerror_ = hold_dzdzerror_;
    pterror_ = hold_pterror_;
    dzdzerror_pix_ = hold_dzdzerror_pix_;
    chi2_ = hold_chi2_;
    return N;
  }
  
  
  int fillTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, int bin)
  {
    int Ntrk = 0;
    using namespace edm;
    using namespace reco;
    for(int i = 0; i<7; i++) {
      qxtrk[i]->Reset();
      qytrk[i]->Reset();
    }
    qcnt->Reset();
    avpt->Reset();
    iEvent.getByToken(vertexToken,vertex_);
    VertexCollection recoVertices = *vertex_;
    int primaryvtx = 0;
    if(sTrackQuality == ppReco) {
      if ( recoVertices.size() > 100 ) return -1;
      sort(recoVertices.begin(), recoVertices.end(), [](const reco::Vertex &a, const reco::Vertex &b){
	  if ( a.tracksSize() == b.tracksSize() ) return a.chi2() < b.chi2();
	  return a.tracksSize() > b.tracksSize();
	});
    } else {
      sort(recoVertices.begin(), recoVertices.end(), [](const reco::Vertex &a, const reco::Vertex &b){
	  return a.tracksSize() > b.tracksSize();
	});    
    }
          
    vtx = recoVertices[primaryvtx].z();
    if (fabs(vtx) < minvz_ || fabs(vtx) > maxvz_) {
      return -1;
    }        
    
    iEvent.getByLabel(trackTag_,trackCollection_);

    for(TrackCollection::const_iterator itTrack = trackCollection_->begin(); itTrack != trackCollection_->end(); ++itTrack) { 
      if ( sTrackQuality == HIReco and not TrackQuality_HIReco(itTrack, recoVertices) ) continue;
      else if ( sTrackQuality == ppReco and not TrackQuality_ppReco(itTrack, recoVertices) ) continue;
      else if ( sTrackQuality == Pixel  and not TrackQuality_Pixel (itTrack, recoVertices) ) continue;
 
      int ipt = qxtrk[0]->GetXaxis()->FindBin(itTrack->pt());
      int ieta = qxtrk[0]->GetYaxis()->FindBin(itTrack->eta());
      double eff = 1.;
      if(effTable_!="NULL") {
	int ieffpt = Eff_0_5->GetYaxis()->FindBin(itTrack->pt());
	int ieffeta = Eff_0_5->GetXaxis()->FindBin(itTrack->eta());
	if(centval<5) eff = Eff_0_5->GetBinContent(ieffeta,ieffpt);
	else if (centval < 10) eff = Eff_5_10->GetBinContent(ieffeta,ieffpt);
	else if (centval < 30) eff = Eff_10_30->GetBinContent(ieffeta,ieffpt);
	else if (centval < 50) eff = Eff_30_50->GetBinContent(ieffeta,ieffpt);
	else eff = Eff_50_100->GetBinContent(ieffeta,ieffpt);	
	if(eff == 0) eff = 1;
	eff=1/eff;
      }
      for(int iorder = 1; iorder <=7; iorder++) {
	qxtrk[iorder-1]->Fill(itTrack->pt(), itTrack->eta(), eff*(TMath::Cos(iorder*itTrack->phi()) - wqxtrkRef[iorder-1][bin]->GetBinContent(ipt,ieta)));
	qytrk[iorder-1]->Fill(itTrack->pt(), itTrack->eta(), eff*(TMath::Sin(iorder*itTrack->phi()) - wqytrkRef[iorder-1][bin]->GetBinContent(ipt,ieta)));
      }
      qcnt->Fill(itTrack->pt(), itTrack->eta(), eff);
      avpt->Fill(itTrack->pt(), itTrack->eta(), eff*itTrack->pt());
      
      if( itTrack->pt() < 0.2 ) continue;
      ++Ntrk;
    }
    return Ntrk;
  }
};


//
// constructors and destructor
//
VNAnalyzer::VNAnalyzer(const edm::ParameterSet& iConfig):runno_(0)
  
{
  ran = new TRandom();
  ran->SetSeed(0);
  runno_ = 0;
  loadDB_ = kTRUE;
  FirstEvent_ = kTRUE;
  for(int i = 0; i<NumEPNames; i++) {
    epang[i] = -10;
    eporig[i] = -10;
    epsin[i] = 0;
    epcos[i] = 0;
    qx[i] = 0;
    qy[i] = 0;
    q[i] = 0;
    epmult[i] = 0;
    rescor[i] = 0;
    rescorErr[i] = 0;
  }

  centralityVariable_ = iConfig.getParameter<std::string>("centralityVariable");
  if(iConfig.exists("nonDefaultGlauberModel")){
    centralityMC_ = iConfig.getParameter<std::string>("nonDefaultGlauberModel");
  }
  centralityLabel_ = centralityVariable_+centralityMC_;

  centralityBinTag_ = iConfig.getParameter<edm::InputTag>("centralityBinTag_");
  centralityBinToken = consumes<int>(centralityBinTag_);

  centralityTag_ = iConfig.getParameter<edm::InputTag>("centralityTag_");
  centralityToken = consumes<reco::Centrality>(centralityTag_);
  if(centralityToken.isUninitialized()) {
    std::cout<<"centralityToken is uninitialized."<<std::endl;
  }
  vertexTag_  = iConfig.getParameter<edm::InputTag>("vertexTag_");
  vertexToken = consumes<std::vector<reco::Vertex>>(vertexTag_);
  if(vertexToken.isUninitialized()) {
    std::cout<<"vertexToken is uninitialized."<<std::endl;
  }

  trackTag_ = iConfig.getParameter<edm::InputTag>("trackTag_");
  trackToken = consumes<reco::TrackCollection>(trackTag_);
  if(trackToken.isUninitialized()) {
    std::cout<<"trackToken is uninitialized."<<std::endl;
  }
  if ( trackTag_.label() == "hiGeneralTracks" ) {
    sTrackQuality = HIReco;
    cout<<"hiGeneralTracks"<<endl;
  } else if ( trackTag_.label() == "generalTracks" ) {
    sTrackQuality = ppReco;
    cout<<"generalTracks"<<endl;
  } else if ( trackTag_.label() == "hiGeneralAndPixelTracks" ) {
    sTrackQuality = Pixel;
    cout<<"hiGeneralAndPixelTracks"<<endl;
  } else {
    sTrackQuality = trackUndefine;
  }
  useNtrk_ = iConfig.getUntrackedParameter<bool>("useNtrk",false);
  if(useNtrk_) {
    NumFlatBins_ = ntrkbins;
    CentBinCompression_ = 1;
  }

  inputPlanesTag_ = iConfig.getParameter<edm::InputTag>("inputPlanesTag_");
  inputPlanesToken = consumes<reco::EvtPlaneCollection>(inputPlanesTag_);
  if(inputPlanesToken.isUninitialized()) {
    std::cout<<"inputPlanesToken is uninitialized."<<std::endl;
  }
  tag_ = consumes<int>(iConfig.getParameter<edm::InputTag>("BinLabel"));

  FlatOrder_ = iConfig.getUntrackedParameter<int>("FlatOrder_", 9);
  NumFlatBins_ = iConfig.getUntrackedParameter<int>("NumFlatBins_",20);
  caloCentRef_ = iConfig.getUntrackedParameter<double>("caloCentRef_",80.);
  caloCentRefWidth_ = iConfig.getUntrackedParameter<double>("caloCentRefWidth_",5.);
  CentBinCompression_ = iConfig.getUntrackedParameter<int>("CentBinCompression_",5);
  Noffmin_ = iConfig.getUntrackedParameter<int>("Noffmin_", 0);
  Noffmax_ = iConfig.getUntrackedParameter<int>("Noffmax_", 50000);	
  minrun_ = iConfig.getUntrackedParameter<int>("minrun_", 0);
  maxrun_ = iConfig.getUntrackedParameter<int>("maxrun_", 50000);	
  effTable_ = iConfig.getParameter<std::string>("effTable_");
  bCaloMatching_ = iConfig.getUntrackedParameter<bool>("bCaloMaching", false);
  Recenter_ = iConfig.getUntrackedParameter<bool>("Recenter",true);
  makeTree_ = iConfig.getUntrackedParameter<bool>("makeTree_",false);

  nvtx_ = iConfig.getUntrackedParameter<int>("nvtx_", 100);
  reso_ = iConfig.getUntrackedParameter<double>("reso", 0.2);
  if(reso_<0.01) bCaloMatching_ = false;
  if(bCaloMatching_) {
    pfTag_ = iConfig.getUntrackedParameter<edm::InputTag>("pfTag");
    pfToken_ = consumes<reco::PFCandidateCollection>(pfTag_);
  }
  dzdzerror_ = iConfig.getUntrackedParameter<double>("dzdzerror_", 3.);
  d0d0error_ = iConfig.getUntrackedParameter<double>("d0d0error_", 3.);
  pterror_ = iConfig.getUntrackedParameter<double>("pterror_",0.1);
  dzdzerror_pix_ = iConfig.getUntrackedParameter<double>("dzdzerror_pix_") ;
  chi2_  = iConfig.getUntrackedParameter<double>("chi2_") ;
  teff = 0;
  if(effTable_!="NULL") teff = new TrackEfficiency(effTable_.data());
  minvz_ = iConfig.getUntrackedParameter<double>("minvz_", -15.);
  maxvz_ = iConfig.getUntrackedParameter<double>("maxvz_", 15.);
  offsetFileName = iConfig.getUntrackedParameter<std::string>("offsetFile");
  frecenter = new TFile(offsetFileName.data(),"read");
  int mx = ntrkbins;
  if(!useNtrk_) {
    mx = ncentbins;
  }
  for(int i = 0; i<mx; i++) {
    for(int j = 1; j<=7; j++){
      wqxtrkRef[j-1][i] = (TH2D *) frecenter->Get(Form("wqxtrk_%d_%d",j,i));
      wqytrkRef[j-1][i] = (TH2D *) frecenter->Get(Form("wqytrk_%d_%d",j,i));
    }
  }

  std::cout<<"==============================================="<<std::endl;
  std::cout<<"centralityBinTag_           "<<centralityBinTag_.encode()<<std::endl;
  std::cout<<"centralityTag_              "<<centralityTag_.encode()<<std::endl;
  std::cout<<"vertexTag_                  "<<vertexTag_.encode()<<std::endl;
  std::cout<<"trackTag_                   "<<trackTag_.encode()<<std::endl;
  std::cout<<"inputPlanesTag_             "<<inputPlanesTag_.encode()<<std::endl;
  std::cout<<"FlatOrder_                  "<<FlatOrder_<<std::endl;
  std::cout<<"NumFlatBins_                "<<NumFlatBins_<<std::endl;
  std::cout<<"caloCentRef_                "<<caloCentRef_<<std::endl;
  std::cout<<"caloCentRefWidth_           "<<caloCentRefWidth_<<std::endl;
  std::cout<<"CentBinCompression_         "<<CentBinCompression_<<std::endl;
  std::cout<<"Noffmin_                    "<<Noffmin_<<std::endl;
  std::cout<<"Noffmax_                    "<<Noffmax_<<std::endl;
  std::cout<<"minrun_                     "<<minrun_<<std::endl;
  std::cout<<"maxrun_                     "<<maxrun_<<std::endl;
  std::cout<<"effTable_                   "<<effTable_<<std::endl;
  std::cout<<"dzerror_                    "<<dzdzerror_<<endl;
  std::cout<<"d0error_                    "<<d0d0error_<<endl;
  std::cout<<"pterror_                    "<<pterror_<<endl;
  std::cout<<"nvtx_                       "<<nvtx_<<endl;
  if(bCaloMatching_) { 
    std::cout<<"bCaloMatching_              true"<<std::endl;
    std::cout<<"reso_                     "<<reso_<<std::endl;   
  }
  std::cout<<"dzdzerror_pix_               "<<dzdzerror_pix_<<std::endl;
  std::cout<<"chi2_                        "<<chi2_<<std::endl;
  if(Recenter_) { 
    std::cout<<"Recenter_                  true"<<std::endl;
  } else {
    std::cout<<"Recenter_                  false"<<std::endl;
  }
  if(useNtrk_) { 
    std::cout<<"Ntrk binning                  "<<std::endl;
  } else {
    std::cout<<"Centrality binning            "<<std::endl;
  }
  std::cout<<"==============================================="<<std::endl;
  TDirectory * save = gDirectory;
  TFileDirectory conddir = fs->mkdir("Conditions");
  conddir.make<TH1I>(centralityBinTag_.label().data(),centralityBinTag_.label().data(),1,0,1);
  conddir.make<TH1I>(centralityTag_.label().data(), centralityTag_.label().data(),1,0,1);
  conddir.make<TH1I>(vertexTag_.label().data(), vertexTag_.label().data(),1,0,1);
  conddir.make<TH1I>(trackTag_.label().data(), trackTag_.label().data(),1,0,1);
  conddir.make<TH1I>(inputPlanesTag_.label().data(), inputPlanesTag_.label().data(),1,0,1);
  string etable = Form("EffTable_%s",effTable_.data());
  conddir.make<TH1I>(etable.data(), etable.data(),1,0,1);
  string note_FlatOrder = Form("FlatOrder_%d",FlatOrder_);
  conddir.make<TH1I>(note_FlatOrder.data(), note_FlatOrder.data(),1,0,1);
  string note_NumFlatBins = Form("NumFlatBins_%d",NumFlatBins_);
  conddir.make<TH1I>(note_NumFlatBins.data(), note_NumFlatBins.data(),1,0,1);
  string note_caloCentRef = Form("caloCentRef_%d",(int)caloCentRef_);
  conddir.make<TH1I>(note_caloCentRef.data(), note_caloCentRef.data(),1,0,1);
  string note_caloCentRefWidth = Form("caloCentRefWidth_%d",(int)caloCentRefWidth_);
  conddir.make<TH1I>(note_caloCentRefWidth.data(), note_caloCentRefWidth.data(),1,0,1);
  string note_dzdzerror = Form("dzdzerror_%07.2f",dzdzerror_);
  conddir.make<TH1I>(note_dzdzerror.data(), note_dzdzerror.data(),1,0,1);
  string note_d0d0error = Form("d0d0error_%07.2f",d0d0error_);
  conddir.make<TH1I>(note_d0d0error.data(), note_d0d0error.data(),1,0,1);
  string note_dzdzerror_pix = Form("dzdzerror_pix_%07.2f",dzdzerror_pix_);
  conddir.make<TH1I>(note_dzdzerror_pix.data(), note_dzdzerror_pix.data(),1,0,1);
  string note_chi2 = Form("chi2_%07.2f",chi2_);
  conddir.make<TH1I>(note_chi2.data(), note_chi2.data(),1,0,1);
  string note_vtx_range = Form("vtx_%5.1f_%5.1f",minvz_,maxvz_);
  conddir.make<TH1I>(note_vtx_range.data(), note_vtx_range.data(),1,0,1);
  string note_nvtx = Form("nvtx_%d",nvtx_);
  conddir.make<TH1I>(note_nvtx.data(), note_nvtx.data(),1,0,1);
  if(bCaloMatching_) {
    conddir.make<TH1I>("bCaloMatching_Set_True", "bCaloMatching_Set_True",1,0,1);
    string note_reso = Form("reso_%07.2f",reso_);
    conddir.make<TH1I>(note_reso.data(),note_reso.data(),1,0,1);
  } else {
    conddir.make<TH1I>("bCaloMatching_Set_False", "bCaloMatching_Set_False",1,0,1);
  }
  if(Recenter_) {
    conddir.make<TH1I>("RecenterTracks", "RecenterTracks",1,0,1);
  } else {
    conddir.make<TH1I>("DoNotRecenterTracks", "DoNotRecenterTracks",1,0,1);
  }
  if(useNtrk_) {
    conddir.make<TH1I>("useNtrk_Set_True", "useNtrk_Set_True",1,0,1);
  } else {
    conddir.make<TH1I>("useNtrk_Set_False", "useNtrk_Set_False",1,0,1);
  }
  
  save->cd();
  hNtrk = fs->make<TH1D>("Ntrk","Ntrk",1001,0,3000);
  hNoff = fs->make<TH1D>("Noff","Noff",1001,0,3000);
  int npt = nptbins;
  for(int iorder = 1; iorder<=7; iorder++) {
    qxtrk[iorder-1] = fs->make<TH2D>(Form("qxtrk%d",iorder),Form("qxtrk%d",iorder),npt,ptbins, netabinsDefault, etabinsDefault);
    qytrk[iorder-1] = fs->make<TH2D>(Form("qytrk%d",iorder),Form("qytrk%d",iorder),npt,ptbins, netabinsDefault, etabinsDefault);
    qxtrk[iorder-1]->SetOption("colz");
    qytrk[iorder-1]->SetOption("colz");
    qxtrk[iorder-1]->Sumw2();
    qytrk[iorder-1]->Sumw2();
  }
  qcnt =  fs->make<TH2D>("qcnt", "qcnt",npt,ptbins, netabinsDefault, etabinsDefault);
  avpt =  fs->make<TH2D>("avpt","avpt",npt,ptbins, netabinsDefault, etabinsDefault);
  qcnt->SetOption("colz");
  avpt->SetOption("colz");
  qcnt->Sumw2();
  avpt->Sumw2();
  hTemplate = (TH2D *) qcnt->Clone("hTemplate");
  hTemplate->SetDirectory(0);
  hTemplate->Reset();

  hcent = fs->make<TH1D>("cent","cent",220,-10,110);
  hcentbins = fs->make<TH1D>("centbins","centbins",201,0,200);
  if(useNtrk_) {
    hcentres = fs->make<TH1D>("centres","centres",ntrkbins,trkBins);
  } else {
    hcentres = fs->make<TH1D>("centres","centres",ncentbins,centbins);
  }
  hrun = fs->make<TH1I>("runs","runs",maxrun_-minrun_+1,minrun_,maxrun_);
  hptNtrk = fs->make<TH1D>("ptNtrk","ptNtrk",npt,ptbins);
  hptNtrk->SetXTitle("p_{T} (GeV/c)");
  hptNtrk->SetYTitle("Ntrks (|#eta|<1; 0-5)");
  hptNtrkGood = fs->make<TH1D>("ptNtrkGood","ptNtrkGood",npt,ptbins);
  hptNtrkGood->SetXTitle("p_{T} (GeV/c)");
  hptNtrkGood->SetYTitle("Ntrks (Good) (|#eta|<1; 0-5)");
  hNtrkRet = fs->make<TH1I>("NtrkRet","NtrkRet", 10,0,10);
  TString epnames = EPNames[0].data();
  epnames = epnames+"/D";
  NumFlatBins_ = ntrkbins;
  for(int i = 0; i<NumEPNames; i++) {
    if(i>0) epnames = epnames + ":" + EPNames[i].data() + "/D";
    TFileDirectory subdir = fs->mkdir(Form("%s",EPNames[i].data()));
    flat[i] = new HiEvtPlaneFlatten();
    flat[i]->init(FlatOrder_,NumFlatBins_,EPNames[i],EPOrder[i]);
    Double_t psirange = 4;
    if(EPOrder[i]==1 ) psirange = 3.5;
    if(EPOrder[i]==2 ) psirange = 2;
    if(EPOrder[i]==3 ) psirange = 1.5;
    if(EPOrder[i]==4 ) psirange = 1;
    if(EPOrder[i]==5) psirange = 0.8;
    if(EPOrder[i]==6) psirange = 0.6;
    if(EPOrder[i]==7) psirange = 0.5;

    hPsi[i] = subdir.make<TH1D>("psi","psi",800,-psirange,psirange);
    hPsi[i]->SetXTitle("#Psi");
    hPsi[i]->SetYTitle(Form("Counts (cent<80%c)",'%'));
    
    hPsiOffset[i] = subdir.make<TH1D>("psiOffset","psiOffset",800,-psirange,psirange);
    hPsiOffset[i]->SetXTitle("#Psi");
    hPsiOffset[i]->SetYTitle(Form("Counts (cent<80%c)",'%'));

    
    hPsiFlat[i] = subdir.make<TH1D>("psiFlat","psiFlat",800,-psirange,psirange);
    hPsiFlat[i]->SetXTitle("#Psi");
    hPsiFlat[i]->SetYTitle(Form("Counts (cent<80%c)",'%'));

  }
  //=====================
  TFileDirectory hardir = fs->mkdir("Harmonics");
  qxt = (TH2D *) hTemplate->Clone("qxt");
  qyt = (TH2D *) hTemplate->Clone("qyt");
  qct = (TH2D *) hTemplate->Clone("qct");
  
  qxy = (TH2D *) hTemplate->Clone("qxy");
  qxxy = (TH2D *) hTemplate->Clone("qxxy");
  qxyy = (TH2D *) hTemplate->Clone("qxyy");
  qx2y3 = (TH2D *) hTemplate->Clone("qx2y3");
  qy2x3 = (TH2D *) hTemplate->Clone("qy2x3");
  qx2x2x3= (TH2D *) hTemplate->Clone("qx2x2x3");
  qx2x3y2= (TH2D *) hTemplate->Clone("qx2x3y2");
  qx3y2y2= (TH2D *) hTemplate->Clone("qx3y2y2");
  qx2x2y3= (TH2D *) hTemplate->Clone("qx2x2y3");
  qx2y2y3= (TH2D *) hTemplate->Clone("qx2y2y3");
  qy2y2y3= (TH2D *) hTemplate->Clone("qy2y2y3");    
  qcnt3  = (TH2D *) hTemplate->Clone("qcnt3");
  qxy->SetDirectory(0);
  qxxy->SetDirectory(0);
  qxyy->SetDirectory(0);
  qx2y3->SetDirectory(0);
  qy2x3->SetDirectory(0);
  qx2x2x3->SetDirectory(0);
  qx2x3y2->SetDirectory(0);
  qx3y2y2->SetDirectory(0);
  qx2x2y3->SetDirectory(0);
  qx2y2y3->SetDirectory(0);
  qy2y2y3->SetDirectory(0);
  qcnt3->SetDirectory(0);
  int nanalbins = 0;
  if(useNtrk_) {
    nanalbins = ntrkbins;
  } else {
    nanalbins = ncentbins;
  }

  //==============   Resolution terms  ========
  TFileDirectory resdir = fs->mkdir("Resolutions");
  for(int i = 0; i<nanalbins; i++) {
    TFileDirectory ressubdir;
    for(int iorder = 1; iorder<=7; iorder++) {
      if(useNtrk_) {
	ressubdir = resdir.mkdir(Form("%d_%d",(int)trkBins[i],(int)trkBins[i+1]));
      } else {
	ressubdir = resdir.mkdir(Form("%d_%d",(int)centbins[i],(int)centbins[i+1]));
      }
      res[iorder-1][i] = ressubdir.make<TH2D>(Form("res%d",iorder),Form("res%d",iorder),46,0,46,46,0,46);
      resw[iorder-1][i] = ressubdir.make<TH2D>(Form("resw%d",iorder),Form("resw%d",iorder),46,0,46,46,0,46);
      resep[iorder-1][i] = ressubdir.make<TH2D>(Form("resep%d",iorder),Form("resep%d",iorder),46,0,46,46,0,46);
      rescnt[iorder-1][i] = ressubdir.make<TH2D>(Form("rescnt%d",iorder),Form("rescnt%d",iorder),46,0,46,46,0,46);
      res[iorder-1][i]->Reset();
      res[iorder-1][i]->Sumw2();
      res[iorder-1][i]->SetOption("colz");
      resw[iorder-1][i]->Reset();
      resw[iorder-1][i]->Sumw2();
      resw[iorder-1][i]->SetOption("colz");
      resep[iorder-1][i]->Reset();
      resep[iorder-1][i]->Sumw2();
      resep[iorder-1][i]->SetOption("colz");
      rescnt[iorder-1][i]->Reset();
      rescnt[iorder-1][i]->Sumw2();
      rescnt[iorder-1][i]->SetOption("colz");
    }
    res12 = ressubdir.make<TH2D>("res12","res12",46,0,46,46,0,46);
    resw12 = ressubdir.make<TH2D>("resw12","resw12",46,0,46,46,0,46);
    res12->Reset();
    resw12->Reset();
    res12->Sumw2();
    resw12->Sumw2();
    res12->SetOption("colz");
    resw12->SetOption("colz");
    res12->GetXaxis()->SetTitle("n = 1");
    res12->GetXaxis()->SetTitle("n = 2");
    
    res23 = ressubdir.make<TH2D>("res23","res23",46,0,46,46,0,46);
    resw23 = ressubdir.make<TH2D>("resw23","resw23",46,0,46,46,0,46);
    res23->Reset();
    resw23->Reset();
    res23->Sumw2();
    resw23->Sumw2();
    res23->SetOption("colz");
    resw23->SetOption("colz");
    res23->GetXaxis()->SetTitle("n = 3");
    res23->GetXaxis()->SetTitle("n = 2");
  }


  for(int i = 0; i<nanalbins; i++) {

    TFileDirectory subdir;
    if(useNtrk_) {
      subdir= hardir.mkdir(Form("%d_%d",(int)trkBins[i],(int)trkBins[i+1]));
    } else {
      subdir = hardir.mkdir(Form("%d_%d",(int)centbins[i],(int)centbins[i+1]));
    }
    ptav[i] = subdir.make<TH2D>("ptav","ptav",npt,ptbins, netabinsDefault, etabinsDefault);
    ptcnt[i] = subdir.make<TH2D>("ptcnt","ptcnt",npt,ptbins, netabinsDefault, etabinsDefault);
    badcnt[i] = subdir.make<TH2D>("badcnt","badcnt",npt,ptbins, netabinsDefault, etabinsDefault);
    for(int iorder = 1; iorder<=7; iorder++) {
      qxav[iorder-1][i] = subdir.make<TH2D>(Form("qxav%d",iorder),Form("qxav%d",iorder),npt,ptbins, netabinsDefault, etabinsDefault);
      qyav[iorder-1][i] = subdir.make<TH2D>(Form("qyav%d",iorder),Form("qyav%d",iorder),npt,ptbins, netabinsDefault, etabinsDefault);
      qxav[iorder-1][i]->Sumw2();
      qyav[iorder-1][i]->Sumw2();
      qxav[iorder-1][i]->SetOption("colz");
      qyav[iorder-1][i]->SetOption("colz");
    }
    qxycnt[i] = subdir.make<TH2D>("qxcnt","qxcnt",npt,ptbins, netabinsDefault, etabinsDefault);

    ptav[i]->Sumw2();
    ptcnt[i]->Sumw2();
    badcnt[i]->Sumw2();
    qxycnt[i]->Sumw2();

    ptav[i]->SetOption("colz");
    ptcnt[i]->SetOption("colz");
    badcnt[i]->SetOption("colz");
    qxycnt[i]->SetOption("colz");

    for(int ian = 0; ian<nanals; ian++) {
      TFileDirectory andir = subdir.mkdir(AnalNames[ian].data());
      
      qanal[ian].qA[i][0] = andir.make<TH2D>("qA","qA",npt,ptbins, netabinsDefault, etabinsDefault);
      qanal[ian].qB[i][0] = andir.make<TH2D>("qB","qB",npt,ptbins, netabinsDefault, etabinsDefault);
      qanal[ian].wnA[i][0] = andir.make<TH2D>("wnA","wnA",npt,ptbins, netabinsDefault, etabinsDefault);
      qanal[ian].wnB[i][0] = andir.make<TH2D>("wnB","wnB",npt,ptbins, netabinsDefault, etabinsDefault);
      qanal[ian].qA[i][0]->Sumw2();
      qanal[ian].qB[i][0]->Sumw2();
      qanal[ian].wnA[i][0]->Sumw2();
      qanal[ian].wnB[i][0]->Sumw2();
      qanal[ian].qA[i][0]->SetOption("colz");
      qanal[ian].qB[i][0]->SetOption("colz");
      qanal[ian].wnA[i][0]->SetOption("colz");
      qanal[ian].wnB[i][0]->SetOption("colz");
      
      qanal[ian].qBA[i][0] = andir.make<TH1D>("qBA","qBA",1,0,1);
      qanal[ian].qCA[i][0] = andir.make<TH1D>("qCA","qCA",1,0,1);
      qanal[ian].qCB[i][0] = andir.make<TH1D>("qCB","qCB",1,0,1);
      qanal[ian].qBAcnt[i][0] = andir.make<TH1D>("qBAcnt","qBAcnt",1,0,1);
      qanal[ian].qCAcnt[i][0] = andir.make<TH1D>("qCAcnt","qCAcnt",1,0,1);
      qanal[ian].qCBcnt[i][0] = andir.make<TH1D>("qCBcnt","qCBcnt",1,0,1);
      
      TFileDirectory subev = andir.mkdir("SubEvents");
      for(int j = 1; j<=10; j++) {	  
	qanal[ian].qA[i][j] = subev.make<TH2D>(Form("qA_%d",j),Form("qA_%d",j),npt,ptbins, netabinsDefault, etabinsDefault); 
	qanal[ian].qB[i][j] = subev.make<TH2D>(Form("qB_%d",j),Form("qB_%d",j),npt,ptbins, netabinsDefault, etabinsDefault);
	qanal[ian].wnA[i][j] = subev.make<TH2D>(Form("wnA_%d",j),Form("wnA_%d",j),npt,ptbins, netabinsDefault, etabinsDefault);
	qanal[ian].wnB[i][j] = subev.make<TH2D>(Form("wnB_%d",j),Form("wnB_%d",j),npt,ptbins, netabinsDefault, etabinsDefault);
	qanal[ian].qA[i][j]->Sumw2();
	qanal[ian].qB[i][j]->Sumw2();
	qanal[ian].wnA[i][j]->Sumw2();
	qanal[ian].wnB[i][j]->Sumw2();
	qanal[ian].qA[i][j]->SetOption("colz");
	qanal[ian].qB[i][j]->SetOption("colz");
	qanal[ian].wnA[i][j]->SetOption("colz");
	qanal[ian].wnB[i][j]->SetOption("colz");
	
	qanal[ian].qBA[i][j] = subev.make<TH1D>(Form("qBA_%d",j),Form("qBA_%d",j),1,0,1);
	qanal[ian].qCA[i][j] = subev.make<TH1D>(Form("qCA_%d",j),Form("qCA_%d",j),1,0,1);      
	qanal[ian].qCB[i][j] = subev.make<TH1D>(Form("qCB_%d",j),Form("qCB_%d",j),1,0,1);
	
	qanal[ian].qBAcnt[i][j] = subev.make<TH1D>(Form("qBAcnt_%d",j),Form("qBAcnt_%d",j),1,0,1);
	qanal[ian].qCAcnt[i][j] = subev.make<TH1D>(Form("qCAcnt_%d",j),Form("qCAcnt_%d",j),1,0,1);      
	qanal[ian].qCBcnt[i][j] = subev.make<TH1D>(Form("qCBcnt_%d",j),Form("qCBcnt_%d",j),1,0,1);
	
      }
      
    }
  }
  //==============================
  
  
  if(makeTree_) {
    tree = fs->make<TTree>("tree","EP tree");
    tree->Branch("Cent",&centval,"cent/D");
    tree->Branch("NtrkOff",&Noff,"Noff/I");
    tree->Branch("ntrkflat",&ntrkval,"nofftrak/I");
    tree->Branch("Vtx",&vtx,"vtx/D");
    tree->Branch("epang",&epang, epnames.Data());
    tree->Branch("eporig",&eporig, epnames.Data());
    tree->Branch("qx",      &qx,       epnames.Data());
    tree->Branch("qy",      &qy,       epnames.Data());
    tree->Branch("q",       &q,       epnames.Data());
    tree->Branch("vn", &vn, epnames.Data());
    tree->Branch("mult",    &epmult,  epnames.Data());
    tree->Branch("sumw",    &sumw,  epnames.Data());
    tree->Branch("sumw2",    &sumw2,  epnames.Data());
    tree->Branch("Run",     &runno_,   "run/i");
    tree->Branch("Rescor",  &rescor,   epnames.Data());
    tree->Branch("RescorErr",  &rescorErr,   epnames.Data());
    tree->Branch("qxtrk1",  "TH2D",  &qxtrk[0], 128000, 0);
    tree->Branch("qytrk1",  "TH2D",  &qytrk[0], 128000, 0);
    tree->Branch("qxtrk2",  "TH2D",  &qxtrk[1], 128000, 0);
    tree->Branch("qytrk2",  "TH2D",  &qytrk[1], 128000, 0);
    tree->Branch("qxtrk3",  "TH2D",  &qxtrk[2], 128000, 0);
    tree->Branch("qytrk3",  "TH2D",  &qytrk[2], 128000, 0);
    tree->Branch("qxtrk4",  "TH2D",  &qxtrk[3], 128000, 0);
    tree->Branch("qytrk4",  "TH2D",  &qytrk[3], 128000, 0);
    tree->Branch("qxtrk5",  "TH2D",  &qxtrk[4], 128000, 0);
    tree->Branch("qytrk5",  "TH2D",  &qytrk[4], 128000, 0);
    tree->Branch("qxtrk6",  "TH2D",  &qxtrk[5], 128000, 0);
    tree->Branch("qytrk6",  "TH2D",  &qytrk[5], 128000, 0);
    tree->Branch("qxtrk7",  "TH2D",  &qxtrk[6], 128000, 0);
    tree->Branch("qytrk7",  "TH2D",  &qytrk[6], 128000, 0);
    tree->Branch("qcnt",    "TH2D",  &qcnt, 128000, 0);
    tree->Branch("avpt",    "TH2D",  &avpt, 128000, 0);
  }
}


VNAnalyzer::~VNAnalyzer()
{
  frecenter->Close();  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
VNAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  Bool_t newrun = kFALSE;
  if(runno_ != iEvent.id().run()) newrun = kTRUE;
  runno_ = iEvent.id().run();
  hrun->Fill(runno_);
  if(FirstEvent_ || newrun) {
    FirstEvent_ = kFALSE;
    newrun = kFALSE;
    //
    //Get Size of Centrality Table
    //
    if(!useNtrk_) {
      edm::ESHandle<CentralityTable> centDB_;
      iSetup.get<HeavyIonRcd>().get(centralityLabel_,centDB_);
      nCentBins_ = (int) centDB_->m_table.size();
      for(int i = 0; i<NumEPNames; i++) {
	flat[i]->setCaloCentRefBins(-1,-1);
	if(caloCentRef_>0) {
	  int minbin = (caloCentRef_-caloCentRefWidth_/2.)*nCentBins_/100.;
	  int maxbin = (caloCentRef_+caloCentRefWidth_/2.)*nCentBins_/100.;
	  minbin/=CentBinCompression_;
	  maxbin/=CentBinCompression_;
	  if(minbin>0 && maxbin>=minbin) {
	    if(EPDet[i]==HF || EPDet[i]==Castor) flat[i]->setCaloCentRefBins(minbin,maxbin);
	  }
	}
      }
    }
    //
    // Get flattening parameter file.  
    //
    edm::ESHandle<RPFlatParams> flatparmsDB_;
    iSetup.get<HeavyIonRPRcd>().get(flatparmsDB_);
    LoadEPDB * db = new LoadEPDB(flatparmsDB_,flat);
    if(!db->IsSuccess()) {
      std::cout<<"Flattening db inconsistancy, will continue without: "<<std::endl;
      loadDB_ = kFALSE;
    }        
  } //First event
  
  
  //
  // Get Centrality
  //

  int Noff=0;
  
  int bin = 0;
  int cbin = 0;
  if(!useNtrk_) {
    // ntrkval=0;
    // if(Noffmin_>=0) {
    //   iEvent.getByToken(centralityToken, centrality_);
    //   ntrkval = centrality_->Ntracks();
    //   if ( (ntrkval < Noffmin_) || (ntrkval >= Noffmax_) ) {
    // 	return;
    //   }
    // }
    Noff = getNoff(iEvent,iSetup);
    hNoff->Fill(Noff);
    iEvent.getByToken(centralityBinToken, cbin_);
    cbin = *cbin_;
    bin = cbin/CentBinCompression_; 
    double cscale = 100./nCentBins_;
    centval = cscale*cbin;
    hcentres->Fill(centval);
  } else {
    
    iEvent.getByToken(centralityToken, centrality_);
    //ntrkval = centrality_->Ntracks();
    Noff = getNoff(iEvent, iSetup);
    hNoff->Fill(Noff);
    bin = NtrkToBin(Noff)-1;
    cbin = bin;
    centval = Noff;
    hcentres->Fill(Noff);
  }

  int ibin = hcentres->FindBin(centval)-1;
  hcent->Fill(centval);
  hcentbins->Fill(cbin);
  
  if (fabs(vtx) < minvz_ || fabs(vtx) > maxvz_) return;
  
  int ntrkval=fillTracks(iEvent, iSetup, ibin);
  hNtrk->Fill(ntrkval);
  
  //
  // Get Event Planes
  //
  iEvent.getByToken(inputPlanesToken,inputPlanes_);
  
  if(!inputPlanes_.isValid()){
    cout << "Error! Can't get hiEvtPlaneFlat product!" << endl;
    return ;
  }
  
  Int_t indx = 0;
  for(int i = 0; i<NumEPNames; i++) {
    epang[i] = -10;
    epsin[i] = 0;
    epcos[i] = 0;
    qx[i] = 0;
    qy[i] = 0;
    q[i] = 0;
    vn[i] = 0;
    epmult[i] = 0;
    sumw[i] = 0;
    sumw2[i] = 0;
  }
  for (EvtPlaneCollection::const_iterator rp = inputPlanes_->begin();rp !=inputPlanes_->end(); rp++) {
    if(indx != rp->indx() ) {
      cout<<"EP inconsistency found. Abort."<<endl;
      return;
    }
    if(rp->sumSin()!=0 || rp->sumCos()!=0) {
      if(rp->mult()>3 && fabs(vtx)<15) {
	epang[indx]=rp->angle();
	eporig[indx]=rp->angle(0);
	epsin[indx] = rp->sumSin();
	epcos[indx] = rp->sumCos();
	hPsi[indx]->Fill(rp->angle(0));
	hPsiOffset[indx]->Fill(rp->angle(1));
	hPsiFlat[indx]->Fill(rp->angle(2));
	qx[indx]  = rp->qx(); 
	qy[indx]  = rp->qy();
	q[indx]   = rp->q();
	vn[indx] = rp->vn(0);
	epmult[indx] = (double) rp->mult();
	sumw[indx] = rp->sumw();
	sumw2[indx] = rp->sumw2();
	if(!useNtrk_) {
	  rescor[indx] = flat[indx]->getCentRes1((int) centval);
	  rescorErr[indx] = flat[indx]->getCentResErr1((int) centval);
	} else {
	  rescor[indx] = 0.;
	  rescorErr[indx] = 0.;
	}
      } 
    }
    ++indx; 
  }
  ptav[ibin]->Add(avpt);
  ptcnt[ibin]->Add(qcnt);
  for(int iorder = 1; iorder<=7; iorder++) {
    qxav[iorder-1][ibin]->Add(qxtrk[iorder-1]);
    qyav[iorder-1][ibin]->Add(qytrk[iorder-1]);
  }
  qxycnt[ibin]->Add(qcnt);
  for(int ian = 0; ian<nanals; ian++) {
    if(ian==N1MCm22) Fill_N( N1MCm22, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackm122mc], qy[trackm122mc], qx[trackp122mc], qy[trackp122mc], qx[trackp1mc], qy[trackp1mc],     sumw[trackm122mc], sumw[trackp122mc], sumw[trackp1mc]);
    if(ian==N1MCm18) Fill_N( N1MCm18, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackm118mc], qy[trackm118mc], qx[trackp122mc], qy[trackp122mc], qx[trackp1mc], qy[trackp1mc],     sumw[trackm118mc], sumw[trackp122mc], sumw[trackp1mc]);
    if(ian==N1MCm14) Fill_N( N1MCm14, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackm114mc], qy[trackm114mc], qx[trackp122mc], qy[trackp122mc], qx[trackp1mc], qy[trackp1mc],     sumw[trackm114mc], sumw[trackp122mc], sumw[trackp1mc]);
    if(ian==N1MCm10) Fill_N( N1MCm10, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackm110mc], qy[trackm110mc], qx[trackp122mc], qy[trackp122mc], qx[trackp1mc], qy[trackp1mc],     sumw[trackm110mc], sumw[trackp122mc], sumw[trackp1mc]);
    if(ian==N1MCm06) Fill_N( N1MCm06, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackm106mc], qy[trackm106mc], qx[trackp122mc], qy[trackp122mc], qx[trackp110mc], qy[trackp110mc], sumw[trackm106mc], sumw[trackp122mc], sumw[trackp110mc]);
    if(ian==N1MCm02) Fill_N( N1MCm02, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackm102mc], qy[trackm102mc], qx[trackp122mc], qy[trackp122mc], qx[trackp110mc], qy[trackp110mc], sumw[trackm102mc], sumw[trackp122mc], sumw[trackp110mc]);
    
    if(ian==N1MCp02) Fill_N( N1MCp02, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackp102mc], qy[trackp102mc], qx[trackm122mc], qy[trackm122mc], qx[trackm110mc], qy[trackm110mc], sumw[trackp102mc], sumw[trackm122mc], sumw[trackm110mc]);
    if(ian==N1MCp06) Fill_N( N1MCp06, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackp106mc], qy[trackp106mc], qx[trackm122mc], qy[trackm122mc], qx[trackm110mc], qy[trackm110mc], sumw[trackp106mc], sumw[trackm122mc], sumw[trackm110mc]);
    if(ian==N1MCp10) Fill_N( N1MCp10, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackp110mc], qy[trackp110mc], qx[trackm122mc], qy[trackm122mc], qx[trackm1mc], qy[trackm1mc],     sumw[trackp110mc], sumw[trackm122mc], sumw[trackm1mc]);
    if(ian==N1MCp14) Fill_N( N1MCp14, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackp114mc], qy[trackp114mc], qx[trackm122mc], qy[trackm122mc], qx[trackm1mc], qy[trackm1mc],     sumw[trackp114mc], sumw[trackm122mc], sumw[trackm1mc]);
    if(ian==N1MCp18) Fill_N( N1MCp18, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackp118mc], qy[trackp118mc], qx[trackm122mc], qy[trackm122mc], qx[trackm1mc], qy[trackm1mc],     sumw[trackp118mc], sumw[trackm122mc], sumw[trackm1mc]);
    if(ian==N1MCp22) Fill_N( N1MCp22, ibin, qxtrk[0], qytrk[0], qcnt, qx[trackp122mc], qy[trackp122mc], qx[trackm122mc], qy[trackm122mc], qx[trackm1mc], qy[trackm1mc],     sumw[trackp122mc], sumw[trackm122mc], sumw[trackm1mc]);
    
    if(ian==N112A) Fill_N112A(N112A, ibin, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112B) Fill_N112B(N112B, ibin, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N123A) Fill_N123A(N123A, ibin, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N1A) Fill_N( N1A,  ibin, qxtrk[0], qytrk[0], qcnt, qx[HFp1], qy[HFp1], qx[HFm1], qy[HFm1], qx[trackp114], qy[trackp114], sumw[HFp1], sumw[HFm1], sumw[trackp114]);
    if(ian==N1B) Fill_N( N1B,  ibin, qxtrk[0], qytrk[0], qcnt, qx[HFm1], qy[HFm1], qx[HFp1], qy[HFp1], qx[trackm114], qy[trackm114], sumw[HFm1], sumw[HFp1], sumw[trackm114]);
    if(ian==N2) Fill_N( N2,  ibin, qxtrk[1], qytrk[1], qcnt, qx[HFp2], qy[HFp2], qx[HFm2], qy[HFm2], qx[trackmid2], qy[trackmid2], sumw[HFp2], sumw[HFm2], sumw[trackmid2]);
    if(ian==N3) Fill_N( N3,  ibin, qxtrk[2], qytrk[2], qcnt, qx[HFp3], qy[HFp3], qx[HFm3], qy[HFm3], qx[trackmid3], qy[trackmid3], sumw[HFp3], sumw[HFm3], sumw[trackmid3]);
    if(ian==N4) Fill_N( N4,  ibin, qxtrk[3], qytrk[3], qcnt, qx[HFp4], qy[HFp4], qx[HFm4], qy[HFm4], qx[trackmid4], qy[trackmid4], sumw[HFp4], sumw[HFm4], sumw[trackmid4]);
    if(ian==N5) Fill_N( N5,  ibin, qxtrk[4], qytrk[4], qcnt, qx[HFp5], qy[HFp5], qx[HFm5], qy[HFm5], qx[trackmid5], qy[trackmid5], sumw[HFp5], sumw[HFm5], sumw[trackmid5]);
    if(ian==N6) Fill_N( N6,  ibin, qxtrk[5], qytrk[5], qcnt, qx[HFp6], qy[HFp6], qx[HFm6], qy[HFm6], qx[trackmid6], qy[trackmid6], sumw[HFp6], sumw[HFm6], sumw[trackmid6]);
    if(ian==N7) Fill_N( N7,  ibin, qxtrk[6], qytrk[6], qcnt, qx[HFp7], qy[HFp7], qx[HFm7], qy[HFm7], qx[trackmid7], qy[trackmid7], sumw[HFp7], sumw[HFm7], sumw[trackmid7]);
    if(ian==N42)  Fill_N42(N42, ibin, qxtrk[3], qytrk[3], qcnt, qx, qy, sumw);
    if(ian==N42A)  Fill_N42A(N42A, ibin, qxtrk[3], qytrk[3], qcnt, qx, qy, sumw);
    if(ian==N42B)  Fill_N42B(N42B, ibin, qxtrk[3], qytrk[3], qcnt, qx, qy, sumw);
    if(ian==N42C)  Fill_N42C(N42C, ibin, qxtrk[3], qytrk[3], qcnt, qx, qy, sumw);
    if(ian==N523)  Fill_N523(  N523, ibin, qxtrk[4], qytrk[4], qcnt, qx, qy, sumw);
    if(ian==N523A) Fill_N523A(N523A, ibin, qxtrk[4], qytrk[4], qcnt, qx, qy, sumw);
    if(ian==N63)   Fill_N63(N63, ibin, qxtrk[5], qytrk[5], qcnt, qx, qy, sumw);
    if(ian==N63A)   Fill_N63A(N63A, ibin, qxtrk[5], qytrk[5], qcnt, qx, qy, sumw);
    if(ian==N63B)   Fill_N63B(N63B, ibin, qxtrk[5], qytrk[5], qcnt, qx, qy, sumw);
    if(ian==N63C)   Fill_N63C(N63C, ibin, qxtrk[5], qytrk[5], qcnt, qx, qy, sumw);
    if(ian==N62)   Fill_N62(N62, ibin, qxtrk[5], qytrk[5], qcnt, qx, qy, sumw);
    if(ian==N62A)   Fill_N62A(N62A, ibin, qxtrk[5], qytrk[5], qcnt, qx, qy, sumw);
    if(ian==N723)  Fill_N723(N723,ibin, qxtrk[6], qytrk[6], qcnt, qx, qy, sumw);
    if(ian==N723A) Fill_N723A(N723A,ibin, qxtrk[6], qytrk[6], qcnt, qx, qy, sumw);
    if(ian==D24)   Fill_D24(D24,ibin, qxtrk[1], qytrk[1], qcnt, qx, qy, sumw);
    if(ian==D24A)  Fill_D24A(D24A,ibin, qxtrk[1], qytrk[1], qxtrk[1], qytrk[1], qcnt, qx, qy, sumw);
    if(ian==D26)   Fill_D26(D26,ibin, qxtrk[1], qytrk[1], qcnt, qx, qy, sumw);
    if(ian==D26A)   Fill_D26A(D26A,ibin, qxtrk[1], qytrk[1], qcnt, qx, qy, sumw);
    if(ian==D34)   Fill_D34(D34,ibin, qxtrk[2], qytrk[2], qcnt, qx, qy, sumw);
    if(ian==D34A)   Fill_D34A(D34A,ibin, qxtrk[2], qytrk[2],qxtrk[2], qytrk[2], qcnt, qx, qy, sumw);
    if(ian==D2232) Fill_D2232(D2232,ibin,  qxtrk[1], qytrk[1], qxtrk[2], qytrk[2], qcnt, qx, qy, sumw);
    if(ian==D2232A)Fill_D2232A(D2232A,ibin, qxtrk[1], qytrk[1], qxtrk[2], qytrk[2], qcnt, qx, qy, sumw);
    if(ian==D2432) Fill_D2432(D2432,ibin,  qxtrk[1], qytrk[1], qxtrk[2], qytrk[2], qcnt, qx, qy, sumw);
    if(ian==D2432A)Fill_D2432A(D2432A,ibin, qxtrk[1], qytrk[1], qxtrk[2], qytrk[2], qcnt, qx, qy, sumw);
  }
  
  for(int iorder = 1; iorder <=7; iorder++) {
    int epmin = 0;
    int epmax = 0;
    if(iorder == 1 ) {
      epmin = HFm1;
      epmax = HFp1f;
    }else if (iorder == 2) {
      epmin = HFm2;
      epmax = HFp2f;
    }else if (iorder == 3) {
      epmin = HFm3;
      epmax = HFp3f;
    }else if (iorder == 4) {
      epmin = HFm4;
      epmax = HFp4f;
    }else if (iorder == 5) {
      epmin = HFm5;
      epmax = trackp522;
    }else if (iorder == 6) {
      epmin = HFm6;
      epmax = trackp622;
    }else if (iorder == 7) {
      epmin = HFm7;
      epmax = trackp722;
    }
    for(int i = epmin; i<= epmax; i++) {
      for(int j = i; j<=epmax; j++) {
	int ii = i-epmin+1;
	int jj = j-epmin+1;
	double w =(pow(qx[i],2)+pow(qy[i],2))*(pow(qx[j],2)+pow(qy[j],2));
	if(w>0) {
	  res[iorder-1][ibin]->SetBinContent(ii,jj,    res[iorder-1][ibin]->GetBinContent(ii,jj)+(qx[i]*qx[j]+qy[i]*qy[j]));
	  resw[iorder-1][ibin]->SetBinContent(ii,jj,   resw[iorder-1][ibin]->GetBinContent(ii,jj)+sumw[i]*sumw[j]);
	  resep[iorder-1][ibin]->SetBinContent(ii,jj,  resep[iorder-1][ibin]->GetBinContent(ii,jj)+(qx[i]*qx[j]+qy[i]*qy[j])/sqrt(w));
	  rescnt[iorder-1][ibin]->SetBinContent(ii,jj, rescnt[iorder-1][ibin]->GetBinContent(ii,jj)+1.);
	}
      }
    }
    for(int i = HFm1; i<= HFp1f; i++) {
      for(int j = HFm2; j<=HFp2f; j++) {
	int ii = i-HFm1+1;
	int jj = j-HFm2+1;
	double w =(pow(qx[i],2)+pow(qy[i],2))*(pow(qx[j],2)+pow(qy[j],2));
	if(w>0) {
	  res12->SetBinContent(ii,jj,    res12->GetBinContent(ii,jj)+(qx[i]*qx[j]+qy[i]*qy[j]));
	  resw12->SetBinContent(ii,jj,   resw12->GetBinContent(ii,jj)+sumw[i]*sumw[j]);
	}
      }
    }
    for(int i = HFm3; i<= HFp3f; i++) {
      for(int j = HFm2; j<=HFp2f; j++) {
	int ii = i-HFm3+1;
	int jj = j-HFm2+1;
	double w =(pow(qx[i],2)+pow(qy[i],2))*(pow(qx[j],2)+pow(qy[j],2));
	if(w>0) {
	  res23->SetBinContent(ii,jj,    res23->GetBinContent(ii,jj)+(qx[i]*qx[j]+qy[i]*qy[j]));
	  resw23->SetBinContent(ii,jj,   resw23->GetBinContent(ii,jj)+sumw[i]*sumw[j]);
	}
      }
    }
  }
  if(makeTree_) tree->Fill(); 
}



// ------------ method called once each job just before starting event loop  ------------
void 
VNAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
VNAnalyzer::endJob() {
  
}
bool
VNAnalyzer::CaloMatch(const reco::Track & track, const edm::Event & iEvent, unsigned int idx)
{
  if ( !bCaloMatching_ ) return true;
  edm::Handle<reco::PFCandidateCollection> pfCand;
  iEvent.getByToken( pfToken_, pfCand );
  double energy = 0;
  for ( reco::PFCandidateCollection::const_iterator it = pfCand->begin(); it != pfCand->end(); ++it ) {
    reco::TrackRef trackRef = it->trackRef();
    if ( !((it->particleId() != reco::PFCandidate::h) ||
	   (it->particleId() != reco::PFCandidate::e) ||
	   (it->particleId() != reco::PFCandidate::mu) )) continue;
    if ( idx == trackRef.key() ) {
      energy = it->ecalEnergy() + it->hcalEnergy();
      break;
    }
  }
  
  if( track.pt() < 20 || ( energy/( track.pt()*TMath::CosH(track.eta() ) ) > reso_ && (energy)/(TMath::CosH(track.eta())) > (track.pt() - 80.0) )  ) return true;
  else {
    return false;
  }
}
///
bool
VNAnalyzer::TrackQuality_ppReco(const reco::TrackCollection::const_iterator& itTrack, const reco::VertexCollection& recoVertices)
{
  if ( itTrack->charge() == 0 ) return false;
  if ( !itTrack->quality(reco::TrackBase::highPurity) ) return false;
  if ( itTrack->ptError()/itTrack->pt() > pterror_ ) return false;
  int primaryvtx = 0;
  math::XYZPoint v1( recoVertices[primaryvtx].position().x(), recoVertices[primaryvtx].position().y(), recoVertices[primaryvtx].position().z() );
  double vxError = recoVertices[primaryvtx].xError();
  double vyError = recoVertices[primaryvtx].yError();
  double vzError = recoVertices[primaryvtx].zError();
  double d0 = -1.* itTrack->dxy(v1);
  double derror=sqrt(itTrack->dxyError()*itTrack->dxyError()+vxError*vyError);
  if ( fabs( d0/derror ) > d0d0error_ ) {
    return false;
  }
  double dz=itTrack->dz(v1);
  double dzerror=sqrt(itTrack->dzError()*itTrack->dzError()+vzError*vzError);
  if ( fabs( dz/dzerror ) > dzdzerror_ ) {
    return false;
  }
  return true;
}

///
bool
VNAnalyzer::TrackQuality_HIReco(const reco::TrackCollection::const_iterator& itTrack, const reco::VertexCollection& recoVertices)
{
  if ( itTrack->charge() == 0 ) return false;
  if ( !itTrack->quality(reco::TrackBase::highPurity) ) return false;
  if ( itTrack->numberOfValidHits() < 11 ) return false;
  if ( itTrack->normalizedChi2() / itTrack->hitPattern().trackerLayersWithMeasurement() > 0.15 ) {
    return false;
  }
  if ( itTrack->ptError()/itTrack->pt() > pterror_ ) {
    return false;
  }
  if (
      itTrack->originalAlgo() != 4 and
      itTrack->originalAlgo() != 5 and
      itTrack->originalAlgo() != 6 and
      itTrack->originalAlgo() != 7
      ) {
    return false;
  }
  
  int primaryvtx = 0;
  math::XYZPoint v1( recoVertices[primaryvtx].position().x(), recoVertices[primaryvtx].position().y(), recoVertices[primaryvtx].position().z() );
  double vxError = recoVertices[primaryvtx].xError();
  double vyError = recoVertices[primaryvtx].yError();
  double vzError = recoVertices[primaryvtx].zError();
  double d0 = -1.* itTrack->dxy(v1);
  double derror=sqrt(itTrack->dxyError()*itTrack->dxyError()+vxError*vyError);
  if ( fabs( d0/derror ) > d0d0error_ ) {
    return false;
  }
  
  double dz=itTrack->dz(v1);
  double dzerror=sqrt(itTrack->dzError()*itTrack->dzError()+vzError*vzError);
  if ( fabs( dz/dzerror ) > dzdzerror_ ) {
    return false;
  }
  return true;
}

///
bool
VNAnalyzer::TrackQuality_Pixel(const reco::TrackCollection::const_iterator& itTrack, const reco::VertexCollection& recoVertices)
{
  if ( itTrack->charge() == 0 ) return false;
  if ( !itTrack->quality(reco::TrackBase::highPurity) ) return false;
  bool bPix = false;
  int nHits = itTrack->numberOfValidHits();
  
  int primaryvtx = 0;
  math::XYZPoint v1( recoVertices[primaryvtx].position().x(), recoVertices[primaryvtx].position().y(), recoVertices[primaryvtx].position().z() );
  double vxError = recoVertices[primaryvtx].xError();
  double vyError = recoVertices[primaryvtx].yError();
  double vzError = recoVertices[primaryvtx].zError();
  double d0 = -1.* itTrack->dxy(v1);
  
  double dz=itTrack->dz(v1);
  double dzerror=sqrt(itTrack->dzError()*itTrack->dzError()+vzError*vzError);
  if ( itTrack->pt() < 2.4 and (nHits==3 or nHits==4 or nHits==5 or nHits==6) ) bPix = true;
  if ( not bPix ) {
    if ( nHits < 11 ) return false;
    if ( itTrack->normalizedChi2() / itTrack->hitPattern().trackerLayersWithMeasurement() > 0.15 ) {
      return false;
    }
    if ( itTrack->ptError()/itTrack->pt() > pterror_ ) {
      return false;
    }
    if (
	itTrack->pt() > 2.4 and
	itTrack->originalAlgo() != 4 and
	itTrack->originalAlgo() != 5 and
	itTrack->originalAlgo() != 6 and
	itTrack->originalAlgo() != 7
	) {
      return false;
    }
    
    double derror=sqrt(itTrack->dxyError()*itTrack->dxyError()+vxError*vyError);
    if ( fabs( d0/derror ) > d0d0error_ ) {
      return false;
    }
    
    if ( fabs( dz/dzerror ) > dzdzerror_ ) {
      return false;
    }
  } else {
    if ( itTrack->normalizedChi2() / itTrack->hitPattern().trackerLayersWithMeasurement() > chi2_ ) return false;
    if ( fabs( dz/dzerror ) > dzdzerror_pix_ ) {
      return false;
    }
  }
  return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(VNAnalyzer);

