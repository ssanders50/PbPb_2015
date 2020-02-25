#include "qn.C"
#include "ptav.C"
#ifndef INFILE
#define INFILE
string infile = "data.root";
#endif
#ifndef PLOTNAME
#define PLOTNAME
string plotname = "ptplot.pdf";
#endif
void Plot_Pt(int mincent = 15, int maxcent = 20){
  TCanvas * c = new TCanvas("c","c",1300,1000);
  c->Divide(2);
  c->cd(1);
  debug = true;
  graph = false;
  TGraphErrors * g[12];
  TGraphErrors * gdecor[12];
  TGraphErrors * gB[12];
  TGraphErrors * gdecorB[12];
  TH1D * h = new TH1D("h","h",100,0,4);
  h->SetXTitle("p_{T} (GeV/c)");
  h->SetYTitle("v_{1}");
  h->SetMinimum(-0.1);
  h->SetMaximum(0.0);
  h->Draw();
  c->cd(2);
  h->Draw();
  TLegend * leg = new TLegend(0.2,0.15,0.40,0.5);
  leg->SetTextFont(43);
  leg->SetTextSize(16);
  leg->SetBorderSize(0);
  TLegend * leg2 = new TLegend(0.45,0.15,0.65,0.5);
  leg2->SetTextFont(43);
  leg2->SetTextSize(16);
  leg2->SetBorderSize(0);
  TLegend * leg3 = new TLegend(0.2,0.2,0.5,0.3);
  leg3->SetTextFont(43);
  leg3->SetTextSize(16);
  leg3->SetBorderSize(0);

  for(int i = 0; i<12; i++) {
    double x[20];
    double y[20];
    double ey[20];
    double etamin = -2.4 + 0.4*i;
    double etamax = etamin + 0.4;
    TH1D * pt = ptav(mincent,maxcent,etamin,etamax);
    bool decor = false;
    TH1D * qn1 = qn("N1","A",mincent,maxcent,etamin,etamax,true,decor);
    decor = true;
    TH1D * qn1d = qn("N1","A",mincent,maxcent,etamin,etamax,true,decor,12-i);
    decor = false;
    TH1D * qn1B = qn("N1","B",mincent,maxcent,etamin,etamax,true,decor);
    decor = true;
    TH1D * qn1dB = qn("N1","B",mincent,maxcent,etamin,etamax,true,decor,i);
    int ibin = 1;
    while(pt->GetBinContent(ibin)>0.3 && pt->GetBinContent(ibin)<4.0) {
      x[ibin]=pt->GetBinContent(ibin);
      y[ibin] = qn1->GetBinContent(ibin);
      ey[ibin] = qn1->GetBinError(ibin);
      ++ibin;
    }
    g[i] = new TGraphErrors(ibin,x,y,0,ey);
    g[i]->SetMarkerStyle(20+i);
    g[i]->SetMarkerSize(1.6);
    g[i]->SetMarkerColor(kBlue);
    g[i]->SetLineColor(kBlue);
    c->cd(1);
    g[i]->Draw("p");
    leg->AddEntry(g[i],Form("%4.1f <= #eta < %4.1f",etamin,etamax),"lp");

    ibin = 1;
    while(pt->GetBinContent(ibin)>0.3 && pt->GetBinContent(ibin)<4.0) {
      x[ibin]=pt->GetBinContent(ibin);
      y[ibin] = qn1d->GetBinContent(ibin);
      ey[ibin] = qn1d->GetBinError(ibin);
      ++ibin;
    }
    gdecor[i] = new TGraphErrors(ibin,x,y,0,ey);
    gdecor[i]->SetMarkerStyle(20+i);
    gdecor[i]->SetMarkerSize(1.6);
    gdecor[i]->SetMarkerColor(kBlue);
    gdecor[i]->SetLineColor(kBlue);
    c->cd(2);
    gdecor[i]->Draw("p");
    ibin = 1;
    while(pt->GetBinContent(ibin)>0.3 && pt->GetBinContent(ibin)<4.0) {
      x[ibin]=pt->GetBinContent(ibin);
      y[ibin] = qn1B->GetBinContent(ibin);
      ey[ibin] = qn1B->GetBinError(ibin);
      ++ibin;
    }
    gB[i] = new TGraphErrors(ibin,x,y,0,ey);
    gB[i]->SetMarkerStyle(20+i);
    gB[i]->SetMarkerSize(1.6);
    gB[i]->SetMarkerColor(kRed);
    gB[i]->SetLineColor(kRed);
    c->cd(1);
    gB[i]->Draw("p");
    leg2->AddEntry(gB[i],Form("%4.1f <= #eta < %4.1f",etamin,etamax),"lp");

    ibin = 1;
    while(pt->GetBinContent(ibin)>0.3 && pt->GetBinContent(ibin)<4.0) {
      x[ibin]=pt->GetBinContent(ibin);
      y[ibin] = qn1dB->GetBinContent(ibin);
      ey[ibin] = qn1dB->GetBinError(ibin);
      ++ibin;
    }
    gdecorB[i] = new TGraphErrors(ibin,x,y,0,ey);
    gdecorB[i]->SetMarkerStyle(20+i);
    gdecorB[i]->SetMarkerSize(1.6);
    gdecorB[i]->SetMarkerColor(kRed);
    gdecorB[i]->SetLineColor(kRed);

    c->cd(2);
    gdecorB[i]->Draw("p");
  }
  c->cd(2);
  leg->Draw();
  leg2->Draw();
  c->cd(1);
  TLatex * l1 = new TLatex(1.5,-0.006,"#eta_{C} = 0");
  l1->Draw();
  c->cd(2);
  TLatex * l2 = new TLatex(1.5,-0.006,"#eta_{C} = #eta_{ROI}");
  l2->Draw();
  leg3->AddEntry(g[1],"HF+ (4.5 < #eta < 5.0)","lp");
  leg3->AddEntry(gB[1],"HF- (-5.0 < #eta < -4.5)","lp");
  c->cd(1);
  leg3->Draw();
  c->Print(plotname.data(),"pdf");
}
