#include "TFile.h"
#include "TTree.h"
#include "TList.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TArrayD.h"
#include "TMath.h"
#include "TDirectory.h"
#include "TRandom3.h"
#include "TStopwatch.h"
#include <iostream>
#include <unistd.h>
#include <complex>
#include <cmath>

TRandom3 * ran;

typedef complex<double> comp;

int epord_ = 2.;
bool trkoff = true;

static const double MaxCent = 70;
static const int MaxEvents = -1;
int MaxFiles = 1000;
static const int ntrkbins = 15;
static const double trkBins[]={0,20,30,40,50,60,80,100,120,150,185,220,260,300,350,500};
static const int ncentbins = 11;
static const double centBins[]={0,5,10,15,20,25,30,35,40,50,60,70};
static const int nanals = 40;
enum AnalType {
  N2SUB2,       N2SUB3,      N3SUB2,     N3SUB3,     N4SUB2,      N4SUB3,  
  N42SUB2,      N42SUB3,     N5SUB2,     N5SUB3,     N6SUB2,      N6SUB3,   
  N7SUB2,       N7SUB3,      N523SUB2,   N523SUB3,   N723SUB2,    N723SUB3,
  N723ASUB2,    N723ASUB3,   N62SUB2,    N62SUB3,    N63SUB2,     N63SUB3,  
  D24SUB2,      D24SUB3,     D34SUB2,    D34SUB3,    D2232SUB2,   D2232SUB3,
  D2432SUB2,    D2432SUB3,   D2232ASUB2, D2232ASUB3, D2432ASUB2,  D2432ASUB3,
  N523ASUB2,    N523ASUB3,   D26SUB2,    D26SUB3
};
string AnalNames[]={
  "N2SUB2",       "N2SUB3",      "N3SUB2",     "N3SUB3",     "N4SUB2",      "N4SUB3",  
  "N42SUB2",      "N42SUB3",     "N5SUB2",     "N5SUB3",     "N6SUB2",      "N6SUB3",   
  "N7SUB2",       "N7SUB3",      "N523SUB2",   "N523SUB3",   "N723SUB2",    "N723SUB3",
  "N723ASUB2",    "N723ASUB3",   "N62SUB2",    "N62SUB3",    "N63SUB2",     "N63SUB3",  
  "D24SUB2",      "D24SUB3",     "D34SUB2",    "D34SUB3",    "D2232SUB2",   "D2232SUB3",
  "D2432SUB2",    "D2432SUB3",   "D2232ASUB2", "D2232ASUB3", "D2432ASUB2",  "D2432ASUB3",
  "N523ASUB2",    "N523ASUB3",   "D26SUB2",    "D26SUB3"
};
int ANAL;
int epa;
int epb;
int epc;
int ep3a;
int ep3b;
int ep3c;

#include "HiEvtPlaneList.h"
using namespace hi;
Bool_t ispPb ;

int GetMidIndx(Int_t epord, TString midn) {
  int mid = -1;
  string match = midn.Data();
  for(int i = 0; i<hi::NumEPNames; i++) {
    string ct = hi::EPNames[i];
    if(epord==3) ct=hi::EPNames[i];
    if(match==ct) mid = i;
  }
  if(mid<0) {cout<<midn.Data()<< "not found"<<endl; return -1;}
  return mid;
}


Int_t flipENUM(int ein){
  if(ein<0) {
    cout<<"flipENUM called with ein = "<<ein<<"  EXPECT TO CRASH!"<<endl;
  }
  if(!ispPb) return ein;
  string ename = hi::EPNames[ein];
  if(ename.find("mid") != std::string::npos) return ein;
  if(ename.find("m") != std::string::npos) {
    ename.replace(ename.find("m"),1,"p");
  } else if (ename.find("p") != std::string::npos){
    ename.replace(ename.find("p"),1,"m");
  }
  //int epord = 2;
  //if(ename.find("3")!=std::string::npos) epord = 3;
  return GetMidIndx(epord_,ename);
}

#include "src/GetEventInfo.h"

string rpnames[hi::NumEPNames];
//----------------------------------
// Tree Variables:
//
double centval;
int noff;
double vtx;
double epang[hi::NumEPNames];
Double_t qx[hi::NumEPNames];
Double_t qy[hi::NumEPNames];
Double_t q[hi::NumEPNames];
Double_t epmult[hi::NumEPNames];
unsigned int  runno_;
Double_t rescor[hi::NumEPNames];
Double_t rescorErr[hi::NumEPNames];
Double_t sumw[hi::NumEPNames];
TH2D * qxtrk_;
TH2D * qytrk_;
TH2D * qxtrk3_;
TH2D * qytrk3_;
TH2D * qcnt_;
TH2D * avpt_;

Int_t NumEvents[40];
Int_t TotNumEvents; 
TString KeyNames[40];
int NumKeys;

string reac_;
//----------------------------------
#include "src/GenSupport.h"
#include "src/Qvec.h"
#include "src/Setup.h"

void ReadTree(GetEventInfo * info,  string inlist);
int GetMidIndx(Int_t epord, TString midn);
void  GetNumEvents( string inlist);
void GenerateVN(string anal="", TString reac="", string inlist="", int FileLimit=5000) {
  MaxFiles = FileLimit;
  cout<<"ANAL: "<<anal<<endl;
  cout<<"REAC: "<<reac<<endl;
  FILE *  flist;
  flist = fopen(inlist.data(),"r");
  TString mid2n;
  TString mid3n;
#include "src/PbPbSetup.h"
  //#include "src/pPbSetup.h"
  ran = new TRandom3();
  reac_ = reac.Data();
 
  //
  //Locate information about data structure
  //
  GetEventInfo * info=0;
  char buf[120];
  while(fgets(buf,120,flist)!=NULL) {
    buf[strlen(buf)-1]=0;
    TString inFile = buf;
    FILE *ftest = fopen(inFile.Data(),"r");
    if(ftest==NULL) continue;
    fclose(ftest);
    TFile * tf    = new TFile(inFile.Data(),"read");
    if(tf->IsZombie())                 {cout<<"ZOMBIE:    " <<inFile.Data()<<endl; continue;}
    if(tf->TestBit(TFile::kRecovered)) {cout<<"RECOVERED: " <<inFile.Data()<<endl; continue;}
    tf->Close();
    cout<<"Found: "<<inFile.Data()<<endl;
    info = new GetEventInfo(inFile);
    if(info->status == 0) {cout<<inFile.Data()<<" not found or has error"<<endl; continue;}
    Setup(anal, info);
    fclose(flist);
    break;
  }
  GetNumEvents(inlist);
  for(int i = 0; i<NumKeys; i++) cout<<i<<"\t"<<KeyNames[i].Data()<<"\t"<<NumEvents[i]<<endl;
  ReadTree(info, inlist);
  OutputResults(reac, mid2n);
}

void ReadTree(GetEventInfo * info, string inlist){ 
  TStopwatch * sw = new TStopwatch();
  trkbins->Reset();
  centbins->Reset();
  TFile * tfin;
  int NumEvnts = 0;
  int nbins = ncentbins;
  if(trkoff) nbins=ntrkbins;
  int filecnt=0;
  int NEvt = TotNumEvents*0.7;
  NumEvnts = 0;
  filecnt = 0;
  FILE * flist = fopen(inlist.data(),"r");
  char buf[120];
  sw->Start();
  while(fgets(buf,120,flist)!=NULL) {
      if(filecnt>=MaxFiles) continue;
      buf[strlen(buf)-1]=0;
      TString inFile=buf;
      ispPb = kFALSE;
      if(inFile.Contains("pPb")) ispPb = kTRUE;
      string pPbTag = "Pbp";
      if(ispPb) pPbTag = "pPb";
      if(reac_.find("PbPb")!=std::string::npos) pPbTag="PbPb";
      FILE *ftest = fopen(inFile.Data(),"r");
      if(ftest==NULL) continue;
      fclose(ftest);
      tfin    = new TFile(inFile.Data(),"read");
      if(tfin->IsZombie())                 {cout<<"ZOMBIE:    " <<inFile.Data()<<endl; continue;}
      if(tfin->TestBit(TFile::kRecovered)) {cout<<"RECOVERED: " <<inFile.Data()<<endl; continue;}
      tfin->ResetErrno();
      ++filecnt;
      for(int i = 0; i<info->getNumKeys(); i++) {
	TTree * tree = (TTree * ) tfin->Get(Form("%s/tree",info->getKeyName(i).Data()));
	tree->SetBranchAddress("Cent",       &centval);
	tree->SetBranchAddress("NtrkOff",    &noff);
	tree->SetBranchAddress("Vtx",        &vtx);
	tree->SetBranchAddress("epang",      &epang);
	tree->SetBranchAddress("sumw", &sumw);
	tree->SetBranchAddress("qx",         &qx);
	tree->SetBranchAddress("qy",         &qy);
	tree->SetBranchAddress("q",          &q);
	tree->SetBranchAddress("mult",       &epmult);
	tree->SetBranchAddress("Run",        &runno_);
	tree->SetBranchAddress("Rescor",     &rescor);
	tree->SetBranchAddress("RescorErr",  &rescorErr);
	tree->SetBranchAddress(Form("qxtrk%d",epord_),      &qxtrk_);
	tree->SetBranchAddress(Form("qytrk%d",epord_),      &qytrk_);
	if(ANAL==D2232SUB2 || ANAL==D2432SUB2||ANAL==D2232SUB3 || ANAL==D2432SUB3 || 
	   ANAL==D2232ASUB2 || ANAL==D2432ASUB2||ANAL==D2232ASUB3 || ANAL==D2432ASUB3) {
	  tree->SetBranchAddress("qxtrk3",      &qxtrk3_);
	  tree->SetBranchAddress("qytrk3",      &qytrk3_);
	  qxtrk3_->SetOption("colz");
	  qytrk3_->SetOption("colz");
	}
	tree->SetBranchAddress("qcnt",       &qcnt_);
	tree->SetBranchAddress("avpt",        &avpt_);
	qxtrk_->SetOption("colz");
	qytrk_->SetOption("colz");
	for(int ievent = 0; ievent<tree->GetEntries(); ievent++) {
	  if(MaxEvents>0&&NumEvnts>=MaxEvents) {
	    cout<<"MaxEvents: "<<MaxEvents<<endl;
	    cout<<"NumEvnts: "<<NumEvnts<<endl;
	    break;
	  }
	  tree->GetEntry(ievent);
	  if(fabs(vtx)>15.) continue;
	  if(centval>MaxCent) continue;
	  int bin = -1; 
	  if(trkoff) {
	    bin =  trkbins->FindBin(noff)-1;
	    if(bin>=ntrkbins) continue;
	    if(bin<0) continue;
	  } else {
	    bin =  centbins->FindBin(centval)-1;
	    if(bin>=ncentbins) continue;
	    if(bin<0) continue;
	  }
	  if((int)fmod( NumEvnts, NEvt/20) == 0 ) {
	    sw->Continue();
	    double elapse = sw->RealTime();
	    if(NumEvnts>0) cout<<(int) (100*(NumEvnts/(double)NEvt)+0.5)<<"  Elapsed: "<<elapse<<"\t"<<"  Time per event: "<<elapse/(double)NumEvnts<<endl;
	  }
	  trkbins->Fill(noff);
	  centbins->Fill(centval);
	  int evtchar = centval;
	  if(trkoff) evtchar = noff;
	  int j=0;
	  if(ANAL==D2232SUB2 ||ANAL==D2232SUB3 || ANAL==D2232ASUB2 ||ANAL==D2232ASUB3) {
	    TH2D * qxt = (TH2D *) qxtrk_->Clone("qxt");
	    TH2D * qyt = (TH2D *) qytrk_->Clone("qyt");
	    qxt->Reset();
	    qyt->Reset();
	    for(int ix = 1; ix<=qxt->GetNbinsX(); ix++) {
	      for(int jy = 1; jy<=qyt->GetNbinsY(); jy++) {
	  	if(qcnt_->GetBinContent(ix,jy)>0) {
	  	  double a = qxtrk_->GetBinContent(ix,jy);
	  	  double b = qytrk_->GetBinContent(ix,jy);
	  	  double c = qxtrk3_->GetBinContent(ix,jy);
	  	  double d = qytrk3_->GetBinContent(ix,jy);
	  	  qxt->SetBinContent(ix,jy,a*c-b*d);
	  	  qyt->SetBinContent(ix,jy,b*c+a*d);
	  	}
	      }
	    }
	    genp[bin][j]->add(qxt,qyt,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    genm[bin][j]->add(qxt,qyt,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    j=(int)(ran->Uniform(0,9.999))+1;
	    genp[bin][j]->add(qxt,qyt,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    genm[bin][j]->add(qxt,qyt,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    qxt->Delete();
	    qyt->Delete();
	  } else if (ANAL==D2432SUB2||ANAL==D2432SUB3 || ANAL==D2432ASUB2||ANAL==D2432ASUB3 ){
	    TH2D * qxt = (TH2D *) qxtrk_->Clone("qxt");
	    TH2D * qyt = (TH2D *) qytrk_->Clone("qyt");
	    qxt->Reset();
	    qyt->Reset();
	    for(int ix = 1; ix<=qxt->GetNbinsX(); ix++) {
	      for(int jy = 1; jy<=qyt->GetNbinsY(); jy++) {
	  	if(qcnt_->GetBinContent(ix,jy)>0) {
	  	  double a = qxtrk_->GetBinContent(ix,jy);
	  	  double b = qytrk_->GetBinContent(ix,jy);
	  	  double c = qxtrk3_->GetBinContent(ix,jy);
	  	  double d = qytrk3_->GetBinContent(ix,jy);
		  
	  	  double cc = a*c - b*d;
	  	  double dd = b*c + a*d;
	  	  qxt->SetBinContent(ix,jy,a*cc-b*dd);
	  	  qyt->SetBinContent(ix,jy,b*cc+a*dd);
	  	} 
	      }
	    }
	    genp[bin][j]->add(qxt,qyt,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    genm[bin][j]->add(qxt,qyt,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    j=(int)(ran->Uniform(0,9.999))+1;
	    genp[bin][j]->add(qxt,qyt,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    genm[bin][j]->add(qxt,qyt,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    qxt->Delete();
	    qyt->Delete();

	  }else {
	    genp[bin][j]->add(qxtrk_,qytrk_,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    genm[bin][j]->add(qxtrk_,qytrk_,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    j=(int)(ran->Uniform(0,9.999))+1;
	    genp[bin][j]->add(qxtrk_,qytrk_,qcnt_,qx,qy,sumw,avpt_,evtchar);
	    genm[bin][j]->add(qxtrk_,qytrk_,qcnt_,qx,qy,sumw,avpt_,evtchar);
	  }
	  qxavchk[bin]->Add(qxtrk_);
	  qyavchk[bin]->Add(qytrk_);
	  qcntavchk[bin]->Add(qcnt_);
	  if(ANAL==D2232SUB2 || ANAL==D2432SUB2||ANAL==D2232SUB3 || ANAL==D2432SUB3 
	     || ANAL==D2232ASUB2 || ANAL==D2432ASUB2||ANAL==D2232ASUB3 || ANAL==D2432ASUB3) {
	    qxav3chk[bin]->Add(qxtrk3_);
	    qyav3chk[bin]->Add(qytrk3_);
	  }
	  ++NumEvnts;
	}
	tfin->Close();
      }
    }
  
  for(int i = 0; i<nbins; i++) {
    if(qxavchk[i]) qxavchk[i]->Divide(qcntavchk[i]);
    if(qyavchk[i]) qyavchk[i]->Divide(qcntavchk[i]);
    if(ANAL==D2232SUB2 || ANAL==D2432SUB2||ANAL==D2232SUB3 || ANAL==D2432SUB3 
       || ANAL==D2232ASUB2 || ANAL==D2432ASUB2||ANAL==D2232ASUB3 || ANAL==D2432ASUB3) {
      if(qxav3chk[i]) qxav3chk[i]->Divide(qcntavchk[i]);
      if(qyav3chk[i]) qyav3chk[i]->Divide(qcntavchk[i]);
    }
  }
 
}
void GetNumEvents(string inlist){ 
  //Loop over datasets
  cout<<"GetNumEvents"<<endl;

  int ntrig = 1;
  TotNumEvents = 0;
  for(int i = 0; i<40; i++) NumEvents[i] = 0;
  TString tr = "";
  TFile * tfin;
  int filecnt = 0;
  char buf[120];
  FILE * flist = fopen(inlist.data(),"r");
  while(fgets(buf,120,flist)!=NULL) {
    if(filecnt>=MaxFiles) continue;
    buf[strlen(buf)-1]=0;
    TString inFile=buf;
    FILE *ftest = fopen(inFile.Data(),"r");
    if(ftest==NULL) continue;
    fclose(ftest);
    TList * flist;
    int nkeys = 0;
    tfin    = new TFile(inFile.Data(),"read");
    if(tfin->IsZombie())                 {cout<<"ZOMBIE:    " <<inFile.Data()<<endl; continue;}
    if(tfin->TestBit(TFile::kRecovered)) {cout<<"RECOVERED: " <<inFile.Data()<<endl; continue;}
    tfin->ResetErrno();
    flist = tfin->GetListOfKeys();
    ++filecnt;
    while(flist->At(nkeys) != flist->Last()) ++nkeys;
    ++nkeys;
    for(int i = 0; i<nkeys; i++) {
      TTree * tree = (TTree *) tfin->Get(Form("%s/tree",flist->At(i)->GetName()));
      if(NumKeys==0) KeyNames[i] = flist->At(i)->GetName();
      ++NumEvents[i] += tree->GetEntries();
      ++TotNumEvents += tree->GetEntries();
    }
    if(NumKeys==0) NumKeys = nkeys;
    tfin->Close();
    for(int i = 0; i<NumKeys; i++) {
      cout<<filecnt<<"\t"<<inFile.Data()<<"\t"<<tr.Data()<<"\t"<<KeyNames[i].Data()<<"\t NumEvents: "<<NumEvents[i]<<endl;
    }
  }
  fclose(flist);
  cout<<"Total number of events: "<<TotNumEvents<<endl;
  return;
}
