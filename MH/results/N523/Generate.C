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
int MaxFiles = 50;
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

TH1D * trkbins;
TH1D * centbins;
TH2D * ptav[ncentbins];
TH2D * ptcnt[ncentbins];
TH2D * badcnt[ncentbins];
TH2D * qA[ncentbins][11];
TH2D * qB[ncentbins][11];
TH2D * qnorm[ncentbins][11];
TH1D * qres;
TH1D * qBA[ncentbins][11];
TH1D * qCA[ncentbins][11];
TH1D * qCB[ncentbins][11];
TH1D * qBAcnt[ncentbins][11];
TH1D * qCAcnt[ncentbins][11];
TH1D * qCBcnt[ncentbins][11];

TH2D * wnA[ncentbins][11];
TH2D * wnB[ncentbins][11];
TH1D * wBA[ncentbins][11];
TH1D * wCA[ncentbins][11];
TH1D * wCB[ncentbins][11];
#include "HiEvtPlaneList.h"
using namespace hi;
#include "src/Fill.h"
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
TH2D * qxtrk2_;
TH2D * qytrk2_;
TH2D * qxtrk3_;
TH2D * qytrk3_;
TH2D * qxtrk4_;
TH2D * qytrk4_;
TH2D * qxtrk5_;
TH2D * qytrk5_;
TH2D * qxtrk6_;
TH2D * qytrk6_;
TH2D * qxtrk7_;
TH2D * qytrk7_;
TH2D * qcnt_;
TH2D * avpt_;

Int_t NumEvents[40];
Int_t TotNumEvents; 
TString KeyNames[40];
int NumKeys;

string reac_;
//----------------------------------

void ReadTree(GetEventInfo * info,  string inlist);
int GetMidIndx(Int_t epord, TString midn);
void  GetNumEvents( string inlist);
void Generate(string anal="", TString reac="", string inlist="", int FileLimit=50) {
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
    if(info->isPbPb2015pixel() || info->isMC()) trkoff = false;
    cout<<"setup with epord_: "<<epord_<<" ANAL: "<<AnalNames[ANAL].data()<<endl;
    int nbins = 0;
    if(trkoff) {
      nbins = ntrkbins;
    } else {
      nbins = ncentbins;
    }
    
    trkbins = new TH1D("trkbins","trkbins",ntrkbins,trkBins);
    trkbins->Sumw2();
    centbins = new TH1D("centbins","centbins",ncentbins,centBins);
    centbins->Sumw2();
    trkbins->SetDirectory(0);
    centbins->SetDirectory(0);
    qxy = (TH2D *) info->getTemplate()->Clone("qxy");
    qxxy = (TH2D *) info->getTemplate()->Clone("qxxy");
    qxyy = (TH2D *) info->getTemplate()->Clone("qxyy");
    qx2y3 = (TH2D *) info->getTemplate()->Clone("qx2y3");
    qy2x3 = (TH2D *) info->getTemplate()->Clone("qy2x3");
    qx2x2x3= (TH2D *) info->getTemplate()->Clone("qx2x2x3");
    qx2x3y2= (TH2D *) info->getTemplate()->Clone("qx2x3y2");
    qx3y2y2= (TH2D *) info->getTemplate()->Clone("qx3y2y2");
    qx2x2y3= (TH2D *) info->getTemplate()->Clone("qx2x2y3");
    qx2y2y3= (TH2D *) info->getTemplate()->Clone("qx2y2y3");
    qy2y2y3= (TH2D *) info->getTemplate()->Clone("qy2y2y3");    
    qcnt3  = (TH2D *) info->getTemplate()->Clone("qcnt3");
    for(int i = 0; i<ncentbins; i++) {
      ptav[i] = (TH2D *) info->getTemplate()->Clone(Form("ptav_%d",i));
      ptav[i]->SetDirectory(0);
      ptcnt[i] = (TH2D *) info->getTemplate()->Clone(Form("ptcnt_%d",i));
      ptcnt[i]->SetDirectory(0);
      badcnt[i] = (TH2D *) info->getTemplate()->Clone(Form("badcnt_%d",i));
      badcnt[i]->SetDirectory(0);
      qA[i][0] = (TH2D *) info->getTemplate()->Clone(Form("qA_%d",i));
      qA[i][0]->SetDirectory(0);
      qB[i][0] = (TH2D *) info->getTemplate()->Clone(Form("qB_%d",i));
      qB[i][0]->SetDirectory(0);
      qnorm[i][0] = (TH2D *) info->getTemplate()->Clone(Form("qnorm_%d",i));
      qnorm[i][0]->SetDirectory(0);
      wnA[i][0] = (TH2D *) info->getTemplate()->Clone(Form("wnA_%d",i));
      wnA[i][0]->SetDirectory(0);
      wnB[i][0] = (TH2D *) info->getTemplate()->Clone(Form("wnB_%d",i));
      wnB[i][0]->SetDirectory(0);
      for(int j = 1; j<=10; j++) {
	qA[i][j] = (TH2D *) info->getTemplate()->Clone(Form("qA_%d_%d",i,j)); 
	qA[i][j]->SetDirectory(0);
	qB[i][j] = (TH2D *) info->getTemplate()->Clone(Form("qB_%d_%d",i,j));
	qB[i][j]->SetDirectory(0);
	qnorm[i][j] = (TH2D *) info->getTemplate()->Clone(Form("qnorm_%d_%d",i,j));
	qnorm[i][j]->SetDirectory(0);
	wnA[i][j] = (TH2D *) info->getTemplate()->Clone(Form("wnA_%d_%d",i,j));
	wnA[i][j]->SetDirectory(0);
	wnB[i][j] = (TH2D *) info->getTemplate()->Clone(Form("wnB_%d_%d",i,j));
	wnB[i][j]->SetDirectory(0);
      }
      qBA[i][0] = new TH1D(Form("qBA_%d",i),Form("qBA_%d",i),1,0,1);
      qBA[i][0]->SetDirectory(0);
      qCA[i][0] = new TH1D(Form("qCA_%d",i),Form("qCA_%d",i),1,0,1);
      qCA[i][0]->SetDirectory(0);
      qCB[i][0] = new TH1D(Form("qCB_%d",i),Form("qCB_%d",i),1,0,1);
      qCB[i][0]->SetDirectory(0);
      qBAcnt[i][0] = new TH1D(Form("qBAcnt_%d",i),Form("qBAcnt_%d",i),1,0,1);
      qBAcnt[i][0]->SetDirectory(0);
      qCAcnt[i][0] = new TH1D(Form("qCAcnt_%d",i),Form("qCAcnt_%d",i),1,0,1);
      qCAcnt[i][0]->SetDirectory(0);
      qCBcnt[i][0] = new TH1D(Form("qCBcnt_%d",i),Form("qCBcnt_%d",i),1,0,1);
      qCBcnt[i][0]->SetDirectory(0);

      wBA[i][0] = new TH1D(Form("wBA_%d",i),Form("wBA_%d",i),1,0,1);
      wBA[i][0]->SetDirectory(0);
      wCA[i][0] = new TH1D(Form("wCA_%d",i),Form("wCA_%d",i),1,0,1);
      wCA[i][0]->SetDirectory(0);
      wCB[i][0] = new TH1D(Form("wCB_%d",i),Form("wCB_%d",i),1,0,1);
      wCB[i][0]->SetDirectory(0);

      for(int j = 1; j<=10; j++) {
	qBA[i][j] = new TH1D(Form("qBA_%d_%d",i,j),Form("qBA_%d_%d",i,j),1,0,1);
	qCA[i][j] = new TH1D(Form("qCA_%d_%d",i,j),Form("qCA_%d_%d",i,j),1,0,1);      
	qCB[i][j] = new TH1D(Form("qCB_%d_%d",i,j),Form("qCB_%d_%d",i,j),1,0,1);
	qBA[i][j]->SetDirectory(0);
	qCA[i][j]->SetDirectory(0);
	qCB[i][j]->SetDirectory(0);

	qBAcnt[i][j] = new TH1D(Form("qBAcnt_%d_%d",i,j),Form("qBAcnt_%d_%d",i,j),1,0,1);
	qCAcnt[i][j] = new TH1D(Form("qCAcnt_%d_%d",i,j),Form("qCAcnt_%d_%d",i,j),1,0,1);      
	qCBcnt[i][j] = new TH1D(Form("qCBcnt_%d_%d",i,j),Form("qCBcnt_%d_%d",i,j),1,0,1);
	qBAcnt[i][j]->SetDirectory(0);
	qCAcnt[i][j]->SetDirectory(0);
	qCBcnt[i][j]->SetDirectory(0);

	wBA[i][j] = new TH1D(Form("wBA_%d_%d",i,j),Form("wBA_%d_%d",i,j),1,0,1);
	wCA[i][j] = new TH1D(Form("wCA_%d_%d",i,j),Form("wCA_%d_%d",i,j),1,0,1);      
	wCB[i][j] = new TH1D(Form("wCB_%d_%d",i,j),Form("wCB_%d_%d",i,j),1,0,1);
	wBA[i][j]->SetDirectory(0);
	wCA[i][j]->SetDirectory(0);
	wCB[i][j]->SetDirectory(0);
      }
      
    }
    
    fclose(flist);
    break;
  }
  GetNumEvents(inlist);
  for(int i = 0; i<NumKeys; i++) cout<<i<<"\t"<<KeyNames[i].Data()<<"\t"<<NumEvents[i]<<endl;
  ReadTree(info, inlist);
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
  TDirectory * foutdirs[ncentbins];
  string outFile = "/rfs/sanders/MH/"+AnalNames[ANAL];
  string outFext = outFile+".root";
  //cout<<outFile<<endl;
  TFile * fout =new TFile(outFext.data(),"RECREATE");
  for(int i=0;i<nbins;i++) {
    foutdirs[i] = fout->mkdir(Form("%d_%d",(int)centBins[i],(int)centBins[i+1]));
  }
  for(int i=0;i<nbins;i++) {
    ptav[i]->Reset();
    ptcnt[i]->Reset();
    badcnt[i]->Reset();
  }
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
      string inf = inFile.Data();
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
	tree->SetBranchAddress("qxtrk2",      &qxtrk2_);
	tree->SetBranchAddress("qytrk2",      &qytrk2_);
	tree->SetBranchAddress("qxtrk3",      &qxtrk3_);
	tree->SetBranchAddress("qytrk3",      &qytrk3_);
	tree->SetBranchAddress("qxtrk4",      &qxtrk4_);
	tree->SetBranchAddress("qytrk4",      &qytrk4_);
	tree->SetBranchAddress("qxtrk5",      &qxtrk5_);
	tree->SetBranchAddress("qytrk5",      &qytrk5_);
	tree->SetBranchAddress("qxtrk6",      &qxtrk6_);
	tree->SetBranchAddress("qytrk6",      &qytrk6_);
	tree->SetBranchAddress("qxtrk7",      &qxtrk7_);
	tree->SetBranchAddress("qytrk7",      &qytrk7_);
	tree->SetBranchAddress("qcnt",       &qcnt_);
	tree->SetBranchAddress("avpt",        &avpt_);
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
	  if((int)fmod( NumEvnts, NEvt/50) == 0 ) {
	    sw->Continue();
	    double elapse = sw->RealTime();
	    if(NumEvnts>100) {
	      string foutcopy = "cp "+ outFext +" "+ outFile+ "_"+to_string((int) (100*(NumEvnts/(double)NEvt)+0.5))+"_"+to_string(NumEvnts)+".root";
	      cout<<(int) (100*(NumEvnts/(double)NEvt)+0.5)<<"  Elapsed: "<<elapse<<"\t"<<"  Time per event: "<<elapse/(double)NumEvnts<< " : "<<foutcopy<<endl;
	      for(int k = 0; k<nbins; k++) {
	  	foutdirs[k]->cd();
	  	ptav[k]->Write();
	  	ptcnt[k]->Write();
	  	badcnt[k]->Write();
	  	for(int j = 0; j<=10; j++) {
	  	  qA[k][j]->Write();
	  	  qB[k][j]->Write();
	  	  qBA[k][j]->Write();
	  	  qCA[k][j]->Write();
	  	  qCB[k][j]->Write();
	  	  qBAcnt[k][j]->Write();
	  	  qCAcnt[k][j]->Write();
	  	  qCBcnt[k][j]->Write();
	  	  wnA[k][j]->Write();
	  	  wnB[k][j]->Write();
	  	  wBA[k][j]->Write();
	  	  wCA[k][j]->Write();
	  	  wCB[k][j]->Write();
	  	}
	      }
	      //cout<<foutcopy<<endl;
	      fout->Close();
	      system(foutcopy.data());
	      fout =new TFile(outFext.data(),"RECREATE");
	      for(int i=0;i<nbins;i++) {
	  	foutdirs[i] = fout->mkdir(Form("%d_%d",(int)centBins[i],(int)centBins[i+1]));
	      }
	    }
	  }

	  if(epang[HFm2]<-5 || epang[HFp2]<-5 || epang[trackmid2]<-5) {
	    badcnt[bin]->Add(qcnt_);
	    continue;
	  }
	  trkbins->Fill(noff);
	  centbins->Fill(centval);
	  ptav[bin]->Add(avpt_);
	  ptcnt[bin]->Add(qcnt_);
	  int evtchar = centval;
	  if(trkoff) evtchar = noff;
	  if(ANAL==N2SUB3) Fill_NSUB3(  bin, qxtrk2_, qytrk2_, qcnt_, qx[HFp2], qy[HFp2], qx[HFm2], qy[HFm2], qx[trackmid2], qy[trackmid2], sumw[HFp2], sumw[HFm2], sumw[trackmid2]);
	  if(ANAL==N3SUB3) Fill_NSUB3(  bin, qxtrk3_, qytrk3_, qcnt_, qx[HFp3], qy[HFp3], qx[HFm3], qy[HFm3], qx[trackmid3], qy[trackmid3], sumw[HFp3], sumw[HFm3], sumw[trackmid3]);
	  if(ANAL==N4SUB3) Fill_NSUB3(  bin, qxtrk4_, qytrk4_, qcnt_, qx[HFp4], qy[HFp4], qx[HFm4], qy[HFm4], qx[trackmid4], qy[trackmid4], sumw[HFp4], sumw[HFm4], sumw[trackmid4]);
	  if(ANAL==N5SUB3) Fill_NSUB3(  bin, qxtrk5_, qytrk5_, qcnt_, qx[HFp5], qy[HFp5], qx[HFm5], qy[HFm5], qx[trackmid5], qy[trackmid5], sumw[HFp5], sumw[HFm5], sumw[trackmid5]);
	  if(ANAL==N6SUB3) Fill_NSUB3(  bin, qxtrk6_, qytrk6_, qcnt_, qx[HFp6], qy[HFp6], qx[HFm6], qy[HFm6], qx[trackmid6], qy[trackmid6], sumw[HFp6], sumw[HFm6], sumw[trackmid6]);
	  if(ANAL==N7SUB3) Fill_NSUB3(  bin, qxtrk7_, qytrk7_, qcnt_, qx[HFp7], qy[HFp7], qx[HFm7], qy[HFm7], qx[trackmid7], qy[trackmid7], sumw[HFp7], sumw[HFm7], sumw[trackmid7]);
	  if(ANAL==N42SUB3)   Fill_N42SUB3(  bin, qxtrk4_, qytrk4_, qcnt_, qx[HFp2], qy[HFp2], qx[HFm2], qy[HFm2], qx[trackmid2], qy[trackmid2], sumw[HFp2], sumw[HFm2], sumw[trackmid2]);
	  if(ANAL==N523SUB3)  Fill_N523SUB3(bin, qxtrk5_, qytrk5_, qcnt_, qx, qy, sumw);
	  if(ANAL==N523ASUB3) Fill_N523ASUB3(bin, qxtrk5_, qytrk5_, qcnt_, qx, qy, sumw);
	  if(ANAL==N63SUB3)   Fill_N63SUB3(bin, qxtrk6_, qytrk6_, qcnt_, qx, qy, sumw);
	  if(ANAL==N723SUB3)  Fill_N723SUB3(bin, qxtrk7_, qytrk7_, qcnt_, qx, qy, sumw);
	  if(ANAL==N723ASUB3) Fill_N723ASUB3(bin, qxtrk7_, qytrk7_, qcnt_, qx, qy, sumw);
	  if(ANAL==D24SUB3)   Fill_D24SUB3(bin, qxtrk2_, qytrk2_, qcnt_, qx, qy, sumw);
	  if(ANAL==D26SUB3)   Fill_D26SUB3(bin, qxtrk2_, qytrk2_, qcnt_, qx, qy, sumw);
	  if(ANAL==D34SUB3)   Fill_D34SUB3(bin, qxtrk3_, qytrk3_, qcnt_, qx, qy, sumw);
	  if(ANAL==D2232SUB3) Fill_D2232SUB3(bin,  qxtrk2_, qytrk2_, qxtrk3_, qytrk3_, qcnt_, qx, qy, sumw);
	  if(ANAL==D2232ASUB3)Fill_D2232ASUB3(bin, qxtrk2_, qytrk2_, qxtrk3_, qytrk3_, qcnt_, qx, qy, sumw);
	  if(ANAL==D2432SUB3) Fill_D2432SUB3(bin,  qxtrk2_, qytrk2_, qxtrk3_, qytrk3_, qcnt_, qx, qy, sumw);
	  if(ANAL==D2432ASUB3)Fill_D2432ASUB3(bin, qxtrk2_, qytrk2_, qxtrk3_, qytrk3_, qcnt_, qx, qy, sumw);
	  ++NumEvnts;
	}
	tfin->Close();
      }
  }
  for(int k = 0; k<nbins; k++) {
    foutdirs[k]->cd();
    ptav[k]->Write();
    ptcnt[k]->Write();
    badcnt[k]->Write();
    for(int j = 0; j<=10; j++) {
      qA[k][j]->Write();
      qB[k][j]->Write();
      qBA[k][j]->Write();
      qCA[k][j]->Write();
      qCB[k][j]->Write();
      qBAcnt[k][j]->Write();
      qCAcnt[k][j]->Write();
      qCBcnt[k][j]->Write();
      wnA[k][j]->Write();
      wnB[k][j]->Write();
      wBA[k][j]->Write();
      wCA[k][j]->Write();
      wCB[k][j]->Write();
    }
  }
  fout->Close();
  
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
