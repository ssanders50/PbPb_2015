#ifndef PTAV
#define PTAV
#ifndef INFILE
#define INFILE
string infile = "data.root";
#endif
#include "HiEvtPlaneList.h"
using namespace hi;
using namespace std;

TH1D *  ptav(int mincent = 10, int maxcent = 15, double etamin = -0.8, double etamax = 0.8){
  TFile * fin = new TFile(infile.data());
  TH2D * ptav = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%d_%d/ptav",mincent,maxcent));
  TH2D * ptcnt = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%d_%d/ptcnt",mincent,maxcent));
  int ietamin = ptav->GetYaxis()->FindBin(etamin+0.01);
  int ietamax = ptav->GetYaxis()->FindBin(etamax-0.01);
  TH1D * ptav1 = (TH1D *) ptav->ProjectionX(Form("pt1d_%d_%d_%4.1f_%4.1f",mincent,maxcent,etamin,etamax),ietamin,ietamax);
  TH1D * ptcnt1 = (TH1D *) ptcnt->ProjectionX(Form("ptcnt1d_%d_%d_%4.1f_%4.1f",mincent,maxcent,etamin,etamax),ietamin,ietamax);
  ptav1->SetDirectory(0);

  ptav1->Divide(ptcnt1);
  ptav1->SetMarkerStyle(21);
  ptav1->SetMarkerColor(kGreen);
  ptav1->SetLineColor(kGreen);
  fin->Close();
  return ptav1;

}

#endif
