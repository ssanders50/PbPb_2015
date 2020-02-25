#ifndef DEBUG
#define DEBUG
bool debug = false;
#endif
#ifndef GRAPH
#define GRAPH
bool graph = true;
#endif
#include "HiEvtPlaneList.h"
#include "getNextCent.C"
#include "qAB.C"
#include "qn.C"
#include "ptav.C"
#include "spec.C"

using namespace hi;
using namespace std;

TGraphErrors * qnint(string anal="N2", string side="+",  int mincent = 0, int maxcent = 50, bool threesub = true, bool decor = false) {
  if(debug)cout<<"qnint anal: "<<anal<<endl;
  double x[12];
  double y[12];
  double ey[12];
  TH1D * vnpt;
  TH1D * yld;
  TH1D * pt;
  TGraphErrors * g = new TGraphErrors(12,x,y,0,0);
  int decorOff = 0;
  for(int i = 0; i<12; i++) {
    if(decor) decorOff = i;
    double etamin = 2.0 - i*0.4;
    if(side.substr(0,1).find("+")==std::string::npos) {
      etamin = -2.4 + i*0.4;
    }
    double etamax = etamin + 0.4;
    double eta    = etamin + 0.2;
    int ccount = 0;
    double avcent = 0;
    string crnge = "";
    int centminval = 0;
    int centmaxval = 0;
    TH1D * wgt_vn = 0;
    TH1D * wgt = 0;
    TH1D * wgt_pt = 0;
    while( (crnge = getNextCent(mincent,maxcent,ccount,avcent,centminval,centmaxval)).find("stop") == std::string::npos) {
      if(debug) cout<<centminval<<"\t"<<centmaxval<<endl;
      if( ccount == 1 ) {
        vnpt = qn(anal,side,centminval,centmaxval,etamin,etamax,threesub,decor,decorOff);
	yld = (TH1D *) spec(centminval,centmaxval,etamin,etamax);
	pt = ptav(centminval,centmaxval,etamin,etamax);
	wgt_vn = (TH1D *) vnpt->Clone("wgt_vn");
	wgt = (TH1D *) yld->Clone("wgt");
	wgt_pt = (TH1D *) pt->Clone("wgt_pt");
	wgt_vn->Multiply(yld);
	wgt_pt->Multiply(yld);
	
      } else {
        vnpt = qn(anal,side,centminval,centmaxval,etamin,etamax,threesub,decor,decorOff);
	yld = (TH1D *) spec(centminval,centmaxval,etamin,etamax);
	pt = ptav(centminval,centmaxval,etamin,etamax);
	vnpt->Multiply(yld);
	pt->Multiply(yld);
	wgt_vn->Add(vnpt);
	wgt_pt->Add(pt);
	wgt->Add(yld);
      }
    }
    wgt_vn->Divide(wgt);
    wgt_pt->Divide(wgt);
    g->GetX()[i] = eta;
    int j = 1;
    double vint = 0;
    double w = 0;
    double e = 0;
    while(wgt_pt->GetBinContent(j)>=0.3 && wgt_pt->GetBinContent(j)< 3.0) {
      vint += wgt_vn->GetBinContent(j)*wgt->GetBinContent(j);
      w    += wgt->GetBinContent(j);
      e+=pow(wgt->GetBinContent(j)*wgt_vn->GetBinError(j),2);
      ++j;
    }
    g->GetY()[i] = vint/w;
    g->GetEY()[i] = sqrt(e)/w;
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kBlue);
    g->SetLineColor(kBlue);
    g->SetName(Form("g_%s_%s_%d_%d",anal.data(),side.data(),mincent,maxcent));
    vnpt->Delete();
    yld->Delete();
    pt->Delete();
    wgt_vn->Delete();
    wgt->Delete();
    wgt_pt->Delete();
  }
  if(graph) {
    TH1D * h = new TH1D("h","h",100,-3,3);
    h->SetMinimum(0.0);
    h->SetMaximum(0.3);
    h->Draw();
    gPad->SetGrid();
    g->Draw("p");
  }
  for(int i = 0; i<g->GetN(); i++) cout<<g->GetX()[i]<<"\t"<<g->GetY()[i]<<"\t"<<g->GetEY()[i]<<endl;
  return g;
}
