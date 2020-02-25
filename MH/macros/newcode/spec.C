#ifndef DEBUG
#define DEBUG
bool debug = false;
#endif
#ifndef SPEC
#define SPEC
#ifndef INFILE
#define INFILE
string infile = "data.root";
#endif
#ifndef EFFFILE
#define EFFFILE
string efffile = "eff.root";
#endif
#include "getNextCent.C"
#include "ptav.C"
#include "HiEvtPlaneList.h"
using namespace hi;
using namespace std;

TH1D *  spec(int mincent = 10, int maxcent = 15, double etamin = -0.8, double etamax = 0.8){
  TFile * fin = new TFile(infile.data());
  TFile * eff = new TFile(efffile.data());
  int ccount = 0;
  TH2D * spec = 0;
  string crnge = "";
  double avcent = 0;
  int centminval = 0;
  int centmaxval = 0;
  TH2D * heff =0;
  while( (crnge = getNextCent(mincent,maxcent,ccount,avcent,centminval,centmaxval)).find("stop") == std::string::npos) {
    TH2D * ptcnt = (TH2D *) fin->Get(Form("vnanalyzer/Harmonics/%s/ptcnt",crnge.data()));
    if(avcent<5) {
      heff = (TH2D *) eff->Get("Eff_0_5");
    } else if (avcent<10) {
      heff = (TH2D *) eff->Get("Eff_5_10");
    } else if (avcent<30) {
      heff = (TH2D *) eff->Get("Eff_10_30");
    } else if (avcent<50) {
      heff = (TH2D *) eff->Get("Eff_30_50");
    } else if (avcent<100) {
      heff = (TH2D *) eff->Get("Eff_50_100");
    }
    if( ccount == 1 ) {
      spec = (TH2D *) ptcnt->Clone(Form("spec_%s",crnge.data()));
      spec->SetDirectory(0);
      for(int i = 1; i<=spec->GetNbinsX(); i++) {
	for(int j = 1; j<=spec->GetNbinsY(); j++) {
	  double binpt = spec->GetXaxis()->GetBinCenter(i);
	  double bineta = spec->GetYaxis()->GetBinCenter(j);
	  double eff = heff->GetBinContent(heff->GetXaxis()->FindBin(bineta),heff->GetYaxis()->FindBin(binpt));
	  if(eff == 0 && debug) cout<<i<<"\t"<<j<<"\t"<<eff<<"\t"<<binpt<<"\t"<<bineta<<endl;
	  if(eff>0) spec->SetBinContent(i,j,spec->GetBinContent(i,j)/eff);
	}
      }
    } else {
    }
  }
  int ietamin = spec->GetYaxis()->FindBin(etamin+0.01);
  int ietamax = spec->GetYaxis()->FindBin(etamax-0.01);
  TH1D * spec1d = (TH1D *) spec->ProjectionX(Form("spec1d_%d_%d_%4.1f_%4.1f",mincent,maxcent,etamin,etamax),ietamin,ietamax);
  spec1d->SetMarkerStyle(20);
  spec1d->SetMarkerColor(kBlue);
  spec1d->SetLineColor(kBlue);
  fin->Close();
  return spec1d;

}

#endif
