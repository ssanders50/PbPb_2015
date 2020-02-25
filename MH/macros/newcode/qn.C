#ifndef QN
#define QN
#ifndef INFILE
#define INFILE
string infile = "data.root";
#endif
#ifndef DEBUG
#define DEBUG
bool debug = false;
#endif
#ifndef GRAPH
#define GRAPH
bool graph = true;
#endif
#include "HiEvtPlaneList.h"
using namespace hi;
using namespace std;
#include "getNextCent.C"
#include "epselection.C"
#include "qAB.C"
TH1D * qn(string anal="N2", string side="+",  int mincent = 15, int maxcent = 20, double etamin = -0.8, double etamax = 0.8, bool threesub = true, bool decor = false, int decorOff=0){
  if(debug) {
    cout<<"Input File: "<<infile<<"   anal: "<<anal<<endl;
    if(decor) {
      cout<<"decor true"<<endl;
    } else {
      cout<<"decor false"<<endl;
    } 
  }
    TFile * fin = new TFile(infile.data());
  int A = -1;
  int B = -1;
  int C = -1;
  int xref = -1;
  string harmonicAnal = anal; 
  string harmonicSide = "A";
  if(side.find("-")!=std::string::npos) side = "B";
  epselection(anal,side,etamin,true,decor,A,B,C);
  int ccount = 0;
  string crnge = "";
  TH2D * qn2 = 0;
  TH2D * wn = 0;
  double avcent;
  int centminval = 0;
  int centmaxval = 0;
  while( (crnge = getNextCent(mincent,maxcent,ccount,avcent,centminval,centmaxval)).find("stop") == std::string::npos) {
    double AB = qAB(A,B,crnge);
    double AC = qAB(A,C,crnge);
    double BC = qAB(B,C,crnge);
    double rAB = resAB(A,B,crnge);
    double rAC = resAB(A,C,crnge);
    double rBC = resAB(B,C,crnge);
    double res = sqrt(fabs(AB));
    double epres = sqrt(fabs(rAB));
    if(threesub) res = sqrt(fabs(AB)*fabs(AC)/fabs(BC));
    if(threesub) epres = sqrt(fabs(rAB)*fabs(rAC)/fabs(rBC));
    if(anal.find("N112")!=std::string::npos) {
      AB = 1;
      AC = 1;
      BC = 1;
      rAB = 1;
      rAC = 1;
      rBC = 1;
    }
    if(debug) cout<<etamin<<"\t"<<etamax<<"\t"<<EPNames[A]<<"\t"<<EPNames[B]<<"\t"<<EPNames[C]<<"\tEPres: "<<epres<<endl;
    string tmp = Form("vnanalyzer/Harmonics/%s/%s/q%s",crnge.data(),harmonicAnal.data(),harmonicSide.data());
    if(ccount==1 ) {
      qn2 = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/q%s",crnge.data(),harmonicAnal.data(),harmonicSide.data()));
      qn2->Scale(1/res);
      wn = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/wn%s",crnge.data(),harmonicAnal.data(),harmonicSide.data()));
    } else {
      TH2D * tmpqn2 = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/q%s",crnge.data(),harmonicAnal.data(),harmonicSide.data()));
      tmpqn2->Scale(1/res);
      TH2D * tmpwn = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/%s/wn%s",crnge.data(),harmonicAnal.data(),harmonicSide.data()));
      qn2->Add(tmpqn2);
      wn->Add(tmpwn); 
    }
  }
  int ietamin = qn2->GetYaxis()->FindBin(etamin+0.01);
  int ietamax = qn2->GetYaxis()->FindBin(etamax-0.01);
  TH1D * qn1d = (TH1D *) qn2->ProjectionX(Form("%s_%s_%s_clone",harmonicAnal.data(),harmonicSide.data(),crnge.data()), ietamin,ietamax);
  qn1d->Divide((TH1D *) wn->ProjectionX(Form("%s_%s_%s",harmonicAnal.data(),harmonicSide.data(),crnge.data()),ietamin,ietamax));
  //qn1d->Scale(1/res);
  qn1d->SetDirectory(0);
  qn1d->SetMarkerStyle(20);
  qn1d->SetMarkerColor(kBlue);
  qn1d->SetLineColor(kBlue);
  fin->Close();
  if(graph) qn1d->Draw();
  return qn1d;
}

#endif
