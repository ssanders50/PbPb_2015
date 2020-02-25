#include <math.h>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLine.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TGraphErrors.h"
#include <stdio.h>
#include <iostream>
double fw = 1.3;
double fakescale = 1.;
double fake(int cent, double eta, double pt) {
  double cb[14]={0,5,10,15,20,25,30,35,40,50,60,70,80,100};
  TFile * f = new TFile("EffAndFake/FakeRatesPixelPbPb_nominal.root");
  TH1I * cen = new TH1I("cen","cen",13,cb);
  int ib = cen->FindBin(cent);
  string rc = "hfak_"+to_string((int)cb[ib])+"_"+to_string((int)cb[ib+1]);
  TH2D * hf = (TH2D *) f->Get(rc.data());
  int ptbin = hf->GetYaxis()->FindBin(pt);
  int etabin = hf->GetXaxis()->FindBin(eta);
  double val = hf->GetBinContent(etabin,ptbin);
  cen->Delete();
  f->Close();
  return fakescale*val ;
}
int cbins[14]={0,5,10,15,20,25,30,35,40,50,60,70,80,100};
TH2D * hm2[11];
TH2D * hp2[11];
TH1D * hm1[11];
TH1D * hp1[11];
TH1D * hr[11];
TH1D * hav[11];
TH1D * havpt[11];
TH1D * hintm[11];
TH1D * hintp[11];
TGraphErrors * gr[11];
TGraphErrors * grold[11];
enum selcalc {nominal, noeprecenter, notrackrecenter};
void CheckSymmetry(int sel=nominal){
  string anal="";
  string title="";
  string outpdf="";
  if(sel==nominal) {
    anal = "v2"; 
    title =  "v_{2}\{EP\} (w/ EP recentering)"; 
    outpdf = Form("figures/Nominal_%03.1f_%03.1f.pdf",fw,fakescale);;
  } else if (sel==noeprecenter) {
    anal = "v2ep_nocorr"; 
    title =  "v_{2}\{EP\} (w/o EP recentering)"; 
    outpdf = "figures/NoEPRecenter.pdf";
  } else if (sel==notrackrecenter) {
    anal = "v2"; 
    title =  "v_{2}\{EP\} (w/ EP recentering)"; 
    outpdf = "figures/Nominal.pdf";
  }
  string sfilem = "../results/"+anal+"/results/results_trackmid2/2015_N2SUB3/PbPb_2015_N2SUB3_v2_HFm2.root";
  string sfilep = "../results/"+anal+"/results/results_trackmid2/2015_N2SUB3/PbPb_2015_N2SUB3_v2_HFp2.root";
  TFile * tm = new TFile(sfilem.data());
  TFile * tp = new TFile(sfilep.data());
  TCanvas * can = new TCanvas("can","can",1400,1200);
  can->Divide(4,3);
  TH1D * href = new TH1D("href","href",100,0,14);
  href->SetXTitle("p_{T} (GeV/c)");
  href->SetYTitle("ratio");
  href->GetXaxis()->SetTitleFont(43);
  href->GetXaxis()->SetLabelFont(43);
  href->GetXaxis()->SetTitleSize(20);
  href->GetXaxis()->SetLabelSize(16);
  href->GetYaxis()->SetTitleFont(43);
  href->GetYaxis()->SetLabelFont(43);
  href->GetYaxis()->SetTitleSize(20);
  href->GetYaxis()->SetLabelSize(16);
  href->GetXaxis()->SetTitleOffset(3.5);
  href->GetXaxis()->CenterTitle();
  href->GetYaxis()->SetTitleOffset(5.0);
  href->GetYaxis()->CenterTitle();
  href->SetMinimum(0.8);
  href->SetMaximum(1.2);
  for(int i = 0; i<11; i++) {
    string c=to_string(cbins[i])+"_"+to_string(cbins[i+1]);
    havpt[i] =(TH1D *) ( (TH2D *) tm->Get(Form("%s/avpt",c.data())))->ProjectionX(Form("%s_avpt",c.data()),5,8);
    havpt[i]->Scale(0.25);
    hintm[i] = (TH1D *) tm->Get(Form("%s/epInt",c.data()));
    hintp[i] = (TH1D *) tp->Get(Form("%s/epInt",c.data()));
    double intm = (hintm[i]->GetBinContent(7)+hintm[i]->GetBinContent(8))/2.;
    double intp = (hintp[i]->GetBinContent(5)+hintm[i]->GetBinContent(6))/2.;

    hm2[i] = (TH2D *) tm->Get(Form("%s/epVn",c.data()));
    hp2[i] = (TH2D *) tp->Get(Form("%s/epVn",c.data()));
    hm1[i] = (TH1D *) hm2[i]->ProjectionX(Form("%s_m",c.data()),7,8);
    hp1[i] = (TH1D *) hp2[i]->ProjectionX(Form("%s_p",c.data()),5,6);
    hr[i] = (TH1D *) hm1[i]->Clone(Form("%s_r",c.data()));
    hr[i]->Divide(hp1[i]);
    hav[i] = (TH1D *) hm1[i]->Clone(Form("%s_av",c.data()));
    hav[i]->Add(hp1[i]);
    hav[i]->Scale(0.25);
    for(int j = 1; j<= hm1[i]->GetNbinsX(); j++) {
      double avpt = havpt[i]->GetBinContent(j);
      if(avpt>14) continue;
      double f = fake(cbins[i],0.,avpt);
      double vint = (intm+intp)/2.;
      double wof = hav[i]->GetBinContent(j);
      double wf= (wof - fw*f*vint)/(1-f);
      if(fw<0.5) wf = wof;
      //cout<<"fake: "<<avpt<<"\t"<<f<<"\t"<<vint<<"\t"<<wof<<"\t"<<wf<<endl;
      hav[i]->SetBinContent(j,wf);
      hav[i]->SetBinError(j,hav[i]->GetBinError(j)*wf/wof);
    }
    can->cd(i+2);
    hr[i]->SetAxisRange(hr[i]->GetBinLowEdge(1),hr[i]->GetBinLowEdge(17),"x");
    hr[i]->SetMinimum(0.9);
    hr[i]->SetMaximum(1.1);
    hr[i]->SetMarkerColor(kBlue);
    hr[i]->SetLineColor(kBlue);
    href->Draw();
    //hr[i]->Draw("same");
    TLine * line = new TLine(hr[i]->GetBinLowEdge(1),1.,hr[i]->GetBinLowEdge(18),1.);
    line->SetLineStyle(2);
    line->SetLineColor(kBlue);
    line->Draw();
    TLatex * l = new TLatex(1.,1.08,Form("%d - %d%c",cbins[i],cbins[i+1],'%'));
    l->Draw();
    string prevname = Form("data/EP_10_002_PtDists/v2_pt_ep_cen%d_%d_eta08.txt",cbins[i],cbins[i+1]);
    double x[40];
    double y[40];
    double stat[40];
    double sys[40];
    FILE * fin = fopen(prevname.data(),"r");
    cout<<prevname<<endl;
    char buf[80];
    int n = 0;
    while(fgets(buf,80,fin)!=NULL) {
      sscanf(buf,"%lf\t%lf\t%lf\t%lf",&x[n],&y[n],&stat[n],&sys[n]);
      ++n;
    }

    double gx[40];
    double gy[40];
    double gey[40];
    int ng = 0;

    double gxold[40];
    double gyold[40];
    double geyold[40];
    int ngold = 0;
    for(int j = 1; j<= hm1[i]->GetNbinsX(); j++) {
      double avpt = havpt[i]->GetBinContent(j);
      gx[ng] = avpt;
      gy[ng] = hr[i]->GetBinContent(j);
      gey[ng] = hr[i]->GetBinError(j);
      ++ng;
      if(avpt>14) break;
      int k1 = -1;
      int k2 = -1;
      for(int k = 0; k<n; k++) {
	if(x[k]<avpt) k1 = k;
	if(x[k]>avpt) {k2 = k; break;}
      }
      double slope = (y[k2]-y[k1])/(x[k2]-x[k1]);
      double val = y[k1]+slope*(avpt-x[k1]);
      cout<<avpt<<"\t"<<hav[i]->GetBinContent(j)<<"\t"<<val<<endl;
      gxold[ngold]=avpt;
      gyold[ngold] = hav[i]->GetBinContent(j)/val;
      geyold[ngold] = hav[i]->GetBinError(j)/val;
      ++ngold;
    }
    gr[i] = new TGraphErrors(ng,gx,gy,0,gey);
    gr[i]->SetMarkerStyle(20);
    gr[i]->SetMarkerColor(kBlue);
    gr[i]->SetLineColor(kBlue);
    gr[i]->Draw("p");

    for(int j = 0; j<ngold; j++) cout<<"rold: "<<gxold[j]<<"\t"<<gyold[j]<<"\t"<<geyold[j]<<endl;
    grold[i] = new TGraphErrors(ngold,gxold,gyold,0,geyold);
    grold[i]->SetMarkerStyle(20);
    grold[i]->SetMarkerColor(kRed);
    grold[i]->SetLineColor(kRed);
    grold[i]->Draw("p");
  }
  can->cd(1);
  TPaveText * txt = new TPaveText(0.1,0.1,0.9,0.9);
  txt->SetTextFont(43);
  txt->SetTextSize(20);
  txt->SetFillColor(kWhite);
  txt->SetBorderSize(0);
  txt->AddText("#frac{v_{2}^{HF-}(0<#eta<0.8)}{v_{2}^{HF+}(-0.8<#eta<0)}");
  ((TText*)txt->GetListOfLines()->Last())->SetTextColor(kBlue);
  txt->AddText("#frac{v_{2}(-0.8<|#eta|<0.8; 5.02 Tev)}{v_{2}(-0.8<|#eta|<0.8; 2.76 Tev)}");
  ((TText*)txt->GetListOfLines()->Last())->SetTextColor(kRed);

  txt->AddText(title.data());
  txt->Draw();
  can->Print(outpdf.data());
}
