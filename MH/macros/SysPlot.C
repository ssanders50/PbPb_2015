#include "TFile.h"
#include "TGraphErrors.h"
#include "TList.h"
#include "TF1.h"
#include "TLine.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLatex.h"
#include <string>
#include <iostream>
int cmin[] = {0,      5,     0,    10,    15,    20,    25,    30,     35,   20,    40,    50,    60,    70};
int cmax[] = {5,     10,    20,    15,    20,    25,    30,    35,     40,   60,    50,    60,    70,    80};
double x[]=  {2.5,  7.5,  10.0,  12.5,  17.5,   22.5, 27.5,  32.5,   37.5,   40.,   45.,   55.,  65.,   75.};
TGraphErrors * getCentDist(string type="N2SUB3", string condition="g_trackQuality",string setting="tight", int fit=0, int marker=20, int color=kBlue){
  TFile * tf = new TFile("vnPlots_save.root");
  double y[14];
  double ey[14];
  for(int i = 0; i<14; i++) {
    string name = "default/"+type+"/-0.8_0.8/"+to_string(cmin[i])+"_"+to_string(cmax[i])+"/systematics/";
    string cond = name+condition;
    cout<<cond<<endl;
    TCanvas * ctrack = (TCanvas *)tf->Get(cond.data()); 
    string gname = condition+"_"+setting;
    TGraphErrors * g = (TGraphErrors *) ctrack->FindObject(gname.data());
    TList * tl = g->GetListOfFunctions();
    TF1 * f = (TF1 *) tl->At(fit);
    y[i] = f->GetParameter(0);
    ey[i] = f->GetParError(0);
  }
  TGraphErrors * g = new TGraphErrors(14,x,y,0,ey);
  string gname = type+"_"+condition+"_"+setting+"_"+to_string(fit);
  g->SetName(gname.data());
  g->SetTitle(gname.data());
  g->SetMarkerStyle(marker);
  g->SetMarkerColor(color);
  g->SetLineColor(color);
  tf->Close();
  return g;
}
void SysPlotPt(string type="N1SUB3", bool diff=false){

  TGraphErrors * gtight0=0;
  TGraphErrors * gtight1=0;
  TGraphErrors * gtight2=0;
  TGraphErrors * gloose0=0;
  TGraphErrors * gloose1=0;
  TGraphErrors * gloose2=0;
  TGraphErrors * gnarrow0=0;
  TGraphErrors * gnarrow1=0;
  TGraphErrors * gnarrow2=0;
  TGraphErrors * gwide0=0;
  TGraphErrors * gwide1=0;
  TGraphErrors * gwide2=0;
  TGraphErrors * gepos0=0;
  TGraphErrors * gepos1=0;
  TGraphErrors * gepos2=0;
  TCanvas * c =0;
  string cname = "cpt_"+type;
  if(diff) {
    gtight0 = getCentDist(type,"g_trackQuality","tight_dif",0,20,kBlue);
    gtight1 = getCentDist(type,"g_trackQuality","tight_dif",1,21,kRed);
    gtight2 = getCentDist(type,"g_trackQuality","tight_dif",2,22,kGreen);
    gloose0 = getCentDist(type,"g_trackQuality","loose_dif",0,20,kBlue);
    gloose1 = getCentDist(type,"g_trackQuality","loose_dif",1,21,kRed);
    gloose2 = getCentDist(type,"g_trackQuality","loose_dif",2,22,kGreen);
    gnarrow0 = getCentDist(type,"g_vtxRange","narrow_dif",0,20,kBlue);
    gnarrow1 = getCentDist(type,"g_vtxRange","narrow_dif",1,21,kRed);
    gnarrow2 = getCentDist(type,"g_vtxRange","narrow_dif",2,22,kGreen);
    gwide0 = getCentDist(type,"g_vtxRange","wide_dif",0,20,kBlue);
    gwide1 = getCentDist(type,"g_vtxRange","wide_dif",1,21,kRed);
    gwide2 = getCentDist(type,"g_vtxRange","wide_dif",2,22,kGreen);
    gepos0 = getCentDist(type,"g_epos","epos_dif",0,20,kBlue);
    gepos1 = getCentDist(type,"g_epos","epos_dif",1,21,kRed);
    gepos2 = getCentDist(type,"g_epos","epos_dif",2,22,kGreen);
    cname = "cpt_diff_"+type;
    c= new TCanvas(cname.data(),cname.data(),1000,1200);
  } else {
    gtight0 = getCentDist(type,"g_trackQuality","tight",0,20,kBlue);
    gtight1 = getCentDist(type,"g_trackQuality","tight",1,21,kRed);
    gtight2 = getCentDist(type,"g_trackQuality","tight",2,22,kGreen);
    gloose0 = getCentDist(type,"g_trackQuality","loose",0,20,kBlue);
    gloose1 = getCentDist(type,"g_trackQuality","loose",1,21,kRed);
    gloose2 = getCentDist(type,"g_trackQuality","loose",2,22,kGreen);
    gnarrow0 = getCentDist(type,"g_vtxRange","narrow",0,20,kBlue);
    gnarrow1 = getCentDist(type,"g_vtxRange","narrow",1,21,kRed);
    gnarrow2 = getCentDist(type,"g_vtxRange","narrow",2,22,kGreen);
    gwide0 = getCentDist(type,"g_vtxRange","wide",0,20,kBlue);
    gwide1 = getCentDist(type,"g_vtxRange","wide",1,21,kRed);
    gwide2 = getCentDist(type,"g_vtxRange","wide",2,22,kGreen);
    gepos0 = getCentDist(type,"g_epos","epos",0,20,kBlue);
    gepos1 = getCentDist(type,"g_epos","epos",1,21,kRed);
    gepos2 = getCentDist(type,"g_epos","epos",2,22,kGreen);
    c= new TCanvas(cname.data(),cname.data(),1000,1200);
  }



  c->Divide(2,3);
  c->cd(1);
  TPaveText * txt = new TPaveText(0.2,0.7,0.7,0.9);
  txt->SetTextFont(43);
  txt->SetTextSize(32);
  txt->AddText(type.data());
  txt->Draw();
  TLegend * leg = new TLegend(0.2,0.2,0.8,0.6);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(43);
  leg->SetTextSize(28);
  leg->AddEntry(gtight0,"0.3<p_{T}<0.6 GeV/c","lp");
  leg->AddEntry(gtight1,"0.5<p_{T}<3.0 GeV/c","lp");
  leg->AddEntry(gtight2,"2.5<p_{T}<8.0 GeV/c","lp");
  leg->Draw();
  //pt tight
  c->cd(3);
  TH1D * h = new TH1D("hpt","hpt",100,0,100);
  h->SetMinimum(0.8);
  h->SetMaximum(1.2);
  h->SetXTitle("\% centrality");
  h->SetYTitle("v_{n}/v_{n}^{default}");
  if(diff) {
    h->SetMinimum(-0.5);
    h->SetMaximum(0.5);
    if(type.find("N2SUB3")!=std::string::npos || type.find("N3SUB3")!=std::string::npos) {
      h->SetMinimum(-2.0);
      h->SetMaximum(2.0);
    }
    h->SetYTitle("v_{n} - v_{n}^{default} (x1000)");
  }
  h->Draw();
  gtight0->Draw("p");
  gtight1->Draw("p");
  gtight2->Draw("p");
  TLine * line = new TLine(0,1,100,1);
  line->SetLineStyle(2);
  line->SetLineColor(kBlack);
  line->Draw();
  TLatex * ttight = new TLatex(10,1.15,"tight");
  ttight->SetTextFont(43);
  ttight->SetTextSize(28);
  ttight->Draw();
  //pt loose
  c->cd(4);
  h->Draw();
  gloose0->Draw("p");
  gloose1->Draw("p");
  gloose2->Draw("p");
  line->Draw();
  TLatex * tloose = new TLatex(10,1.15,"loose");
  tloose->SetTextFont(43);
  tloose->SetTextSize(28);
  tloose->Draw();
  //pt narrow
  c->cd(5);
  h->Draw();
  gnarrow0->Draw("p");
  gnarrow1->Draw("p");
  gnarrow2->Draw("p");
  line->Draw();
  TLatex * tnarrow = new TLatex(10,1.15,"narrow (|vtx|<3 cm)");
  tnarrow->SetTextFont(43);
  tnarrow->SetTextSize(28);
  tnarrow->Draw();
  //pt wide
  c->cd(6);
  h->Draw();
  gwide0->Draw("p");
  gwide1->Draw("p");
  gwide2->Draw("p");
  line->Draw();
  TLatex * twide = new TLatex(10,1.15,"wide (3 < |vtx| <15 cm)");
  twide->SetTextFont(43);
  twide->SetTextSize(28);
  twide->Draw();
  //pt epos
  //c->cd(2);
  //h->Draw();
  //gepos0->Draw("p");
  //gepos1->Draw("p");
  // gepos2->Draw("p");
  //line->Draw();
  //TLatex * tepos = new TLatex(10,1.15,"efficiency (EPOS/HYDJET)");
  //tepos->SetTextFont(43);
  //tepos->SetTextSize(28);
  //tepos->Draw();
  string cpt = "systematics/"+type+"_pt_summary.pdf";
  if(diff) {
  cpt = "systematics/"+type+"_pt_diff_summary.pdf";
  }
  c->Print(cpt.data(),"pdf");
}
void SysPlotInt(string type="N1SUB3",bool diff=false){
  TGraphErrors * gtight0=0;
  TGraphErrors * gtight1=0;
  TGraphErrors * gtight2=0;
  TGraphErrors * gloose0=0;
  TGraphErrors * gloose1=0;
  TGraphErrors * gloose2=0;
  TGraphErrors * gnarrow0=0;
  TGraphErrors * gnarrow1=0;
  TGraphErrors * gnarrow2=0;
  TGraphErrors * gwide0=0;
  TGraphErrors * gwide1=0;
  TGraphErrors * gwide2=0;
  TGraphErrors * gepos0=0;
  TGraphErrors * gepos1=0;
  TGraphErrors * gepos2=0;
  TCanvas * c =0;
  string cname = "cint_"+type;
  if(diff) {
    gtight0 = getCentDist(type,"gint_trackQuality","tight_dif",0,20,kBlue);
    gtight1 = getCentDist(type,"gint_trackQuality","tight_dif",1,21,kRed);
    gtight2 = getCentDist(type,"gint_trackQuality","tight_dif",2,22,kGreen);
    gloose0 = getCentDist(type,"gint_trackQuality","loose_dif",0,20,kBlue);
    gloose1 = getCentDist(type,"gint_trackQuality","loose_dif",1,21,kRed);
    gloose2 = getCentDist(type,"gint_trackQuality","loose_dif",2,22,kGreen);
    gnarrow0 = getCentDist(type,"gint_vtxRange","narrow_dif",0,20,kBlue);
    gnarrow1 = getCentDist(type,"gint_vtxRange","narrow_dif",1,21,kRed);
    gnarrow2 = getCentDist(type,"gint_vtxRange","narrow_dif",2,22,kGreen);
    gwide0 = getCentDist(type,"gint_vtxRange","wide_dif",0,20,kBlue);
    gwide1 = getCentDist(type,"gint_vtxRange","wide_dif",1,21,kRed);
    gwide2 = getCentDist(type,"gint_vtxRange","wide_dif",2,22,kGreen);
    gepos0 = getCentDist(type,"gint_epos","epos_dif",0,20,kBlue);
    gepos1 = getCentDist(type,"gint_epos","epos_dif",1,21,kRed);
    gepos2 = getCentDist(type,"gint_epos","epos_dif",2,22,kGreen);
    cname = "cint_diff_"+type;
    c= new TCanvas(cname.data(),cname.data(),1000,1200);
  } else {
    gtight0 = getCentDist(type,"gint_trackQuality","tight",0,20,kBlue);
    gtight1 = getCentDist(type,"gint_trackQuality","tight",1,21,kRed);
    gtight2 = getCentDist(type,"gint_trackQuality","tight",2,22,kGreen);
    gloose0 = getCentDist(type,"gint_trackQuality","loose",0,20,kBlue);
    gloose1 = getCentDist(type,"gint_trackQuality","loose",1,21,kRed);
    gloose2 = getCentDist(type,"gint_trackQuality","loose",2,22,kGreen);
    gnarrow0 = getCentDist(type,"gint_vtxRange","narrow",0,20,kBlue);
    gnarrow1 = getCentDist(type,"gint_vtxRange","narrow",1,21,kRed);
    gnarrow2 = getCentDist(type,"gint_vtxRange","narrow",2,22,kGreen);
    gwide0 = getCentDist(type,"gint_vtxRange","wide",0,20,kBlue);
    gwide1 = getCentDist(type,"gint_vtxRange","wide",1,21,kRed);
    gwide2 = getCentDist(type,"gint_vtxRange","wide",2,22,kGreen);
    gepos0 = getCentDist(type,"gint_epos","epos",0,20,kBlue);
    gepos1 = getCentDist(type,"gint_epos","epos",1,21,kRed);
    gepos2 = getCentDist(type,"gint_epos","epos",2,22,kGreen);
    c= new TCanvas(cname.data(),cname.data(),1000,1200);
  }
  c->Divide(2,3);
  c->cd(1);
  TPaveText * txt = new TPaveText(0.2,0.7,0.7,0.9);
  txt->SetTextFont(43);
  txt->SetTextSize(32);
  txt->AddText(type.data());
  txt->Draw();
  TLegend * leg = new TLegend(0.2,0.2,0.8,0.6);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(43);
  leg->SetTextSize(28);
  leg->AddEntry(gtight0,"-2.4 < #eta < -1.2","lp");
  leg->AddEntry(gtight1,"-1.6 < #eta <  1.6","lp");
  leg->AddEntry(gtight2," 1.2 < #eta <  2.4","lp");
  leg->Draw();
  //pt tight
  c->cd(3);
  TH1D * h = new TH1D("hint","hint",100,0,100);
  h->SetMinimum(0.8);
  h->SetMaximum(1.2);
  h->SetYTitle("v_{n}/v_{n}^{default}");
  if(diff) {
    h->SetMinimum(-0.5);
    h->SetMaximum(0.5);
    if(type.find("N2SUB3")!=std::string::npos || type.find("N3SUB3")!=std::string::npos) {
      h->SetMinimum(-2.0);
      h->SetMaximum(2.0);
    }
    h->SetYTitle("v_{n}-v_{n}^{default} (x1000)");
  }
  h->SetXTitle("\% centrality");
  h->Draw();
  gtight0->Draw("p");
  gtight1->Draw("p");
  gtight2->Draw("p");
  TLine * line = new TLine(0,1,100,1);
  line->SetLineStyle(2);
  line->SetLineColor(kBlack);
  line->Draw();
  TLatex * ttight = new TLatex(10,1.15,"tight");
  ttight->SetTextFont(43);
  ttight->SetTextSize(28);
  ttight->Draw();
  //pt loose
  c->cd(4);
  h->Draw();
  gloose0->Draw("p");
  gloose1->Draw("p");
  gloose2->Draw("p");
  line->Draw();
  TLatex * tloose = new TLatex(10,1.15,"loose");
  tloose->SetTextFont(43);
  tloose->SetTextSize(28);
  tloose->Draw();
  //pt narrow
  c->cd(5);
  h->Draw();
  gnarrow0->Draw("p");
  gnarrow1->Draw("p");
  gnarrow2->Draw("p");
  line->Draw();
  TLatex * tnarrow = new TLatex(10,1.15,"narrow (|vtx|<3 cm)");
  tnarrow->SetTextFont(43);
  tnarrow->SetTextSize(28);
  tnarrow->Draw();
  //pt wide
  c->cd(6);
  h->Draw();
  gwide0->Draw("p");
  gwide1->Draw("p");
  gwide2->Draw("p");
  line->Draw();
  TLatex * twide = new TLatex(10,1.15,"wide (3 < |vtx| <15 cm)");
  twide->SetTextFont(43);
  twide->SetTextSize(28);
  twide->Draw();
  //pt epos
  c->cd(2);
  h->Draw();
  gepos0->Draw("p");
  gepos1->Draw("p");
  gepos2->Draw("p");
  line->Draw();
  TLatex * tepos = new TLatex(10,1.15,"efficiency (EPOS/HYDJET)");
  tepos->SetTextFont(43);
  tepos->SetTextSize(28);
  tepos->Draw();
  string cint = "systematics/"+type+"_int_ratio_summary.pdf";
  if(diff) {
  cint = "systematics/"+type+"_int_diff_summary.pdf";
  }
  c->Print(cint.data(),"pdf");
}
void SysPlot(){
  string types[9]={"N1SUB3","N1HFcSUB3","N1HFdSUB3","N1HFeSUB3","N1HFfSUB3","N1HFgSUB3","N2SUB3","N3SUB3","N1EVENSUB3"};
  for(int i = 0; i<9; i++) {
    SysPlotPt(types[i]);
    SysPlotInt(types[i]);
    SysPlotPt(types[i],true);
    SysPlotInt(types[i],true);
  }
}
