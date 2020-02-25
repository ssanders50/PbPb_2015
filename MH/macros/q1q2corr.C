#include "src/HiEvtPlaneList.h"
TFile * tf = new TFile("../MH.root","read");
TBrowser br;
using namespace hi;
void q1q2corr(string cent="25_30",bool UseHF = false){
  TH2D * res12ep = (TH2D *) tf->Get(Form("vnanalyzer/Resolutions/%s/resep12",cent.data()));
  TH2D * res12cnt = (TH2D *) tf->Get(Form("vnanalyzer/Resolutions/%s/rescnt12",cent.data()));
  res12ep->Divide(res12cnt);
  res12ep->Draw();
  int refp = trackp222;
  int refm = trackm222;
  string etapref = "2<#eta<2.4";
  string etamref = "-2.4<#eta<-2.0";
  if(UseHF) {
    refp = HFp2g;
    refm = HFm2g;
    etapref = "4.0<#eta<5.0";
    etamref = "-5.0<#eta<-4.0";
  }
  TH1D * prjp = res12ep->ProjectionX("prjp",refp-HFm2+1,refp-HFm2+1);
  TH1D * prjm = res12ep->ProjectionX("prjm",refm-HFm2+1,refm-HFm2+1);
  TCanvas * c = new TCanvas(Form("c_%s",cent.data()),Form("c_%s",cent.data()),1000,800);
  c->cd();
  double xp[12];
  double yp[12];
  double xm[12];
  double ym[12];
  for(int i = 0; i<12; i++) {
    xp[i] = -2.2+i*0.4;
    yp[i] = prjp->GetBinContent(trackm122+i+1);
    xm[i] = -2.2+i*0.4;
    ym[i] = prjm->GetBinContent(trackm122+i+1);
  }
  TGraph * gp = new TGraph(12,xp,yp);
  gp->SetMarkerStyle(20);
  gp->SetMarkerColor(kBlue);
  TGraph * gm = new TGraph(12,xm,ym);
  gm->SetMarkerStyle(20);
  gm->SetMarkerColor(kRed);
  TH1D * h = new TH1D("h","h",100,-3,3);
  h->SetMinimum(0);
  h->SetMaximum(0.06);
  h->SetXTitle("#eta");
  h->SetYTitle("Q_{1}^{2}Q_{2}^{*}");
  h->Draw();
  gp->Draw("p");
  gm->Draw("p");
  TLegend * leg = new TLegend(0.2,0.2,0.4,0.4);
  leg->SetBorderSize(0);
  leg->AddEntry(gp,Form("Q_{2} (%s)",etapref.data()),"lp");
  leg->AddEntry(gm,Form("Q_{2} (%s)",etamref.data()),"lp");
  leg->Draw();
  c->Print(Form("q1q2/q1q2corr_%s.pdf",cent.data()),"pdf");
}
