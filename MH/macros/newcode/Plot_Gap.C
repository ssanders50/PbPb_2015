#include "v1odd.C"
#ifndef PLOTNAME
#define PLOTNAME
string plotname = "Plot_GapStudy_Data.pdf";
#endif
#ifndef INFILE
#define INFILE
string infile = "data.root";
#endif
void Plot_Gap(int mincent = 15, int maxcent = 20){
  TCanvas * c = new TCanvas("c","c",1300,1000);
  c->Divide(2);
  c->cd(1);
  debug = false;
  graph = false;

  decor = false;
  TGraphErrors * g30_35 = v1odd("N1c", mincent, maxcent,20,kGreen);
  TGraphErrors * g35_40 = v1odd("N1d", mincent, maxcent,20,kCyan+2);
  TGraphErrors * g40_45 = v1odd("N1e", mincent, maxcent,20,kRed);
  TGraphErrors * g45_50 = v1odd("N1f", mincent, maxcent,20,kBlue);

  decor = true;
  TGraphErrors * g30_35d = v1odd("N1c", mincent, maxcent,20,kGreen);
  TGraphErrors * g35_40d = v1odd("N1d", mincent, maxcent,20,kCyan+2);
  TGraphErrors * g40_45d = v1odd("N1e", mincent, maxcent,20,kRed);
  TGraphErrors * g45_50d = v1odd("N1f", mincent, maxcent,20,kBlue);

  TH1D * h = new TH1D("h","h",100,-3,3);
  h->SetMinimum(-0.02);
  h->SetMaximum(0.02);
  h->SetXTitle("#eta");
  h->SetYTitle("v_{1}^{odd}");
  h->Draw();
  g30_35->Draw("p");
  g35_40->Draw("p");
  g40_45->Draw("p");
  g45_50->Draw("p");
  TLegend * leg = new TLegend(0.4, 0.2,0.50,0.35);
  leg->SetTextFont(43);
  leg->SetTextSize(22);
  leg->SetBorderSize(0);
  leg->AddEntry(g30_35,"3.0 < #eta_{EP} < 3.5","lp");
  leg->AddEntry(g35_40,"3.5 < #eta_{EP} < 4.0","lp");
  leg->AddEntry(g40_45,"4.0 < #eta_{EP} < 4.5","lp");
  leg->AddEntry(g45_50,"4.5 < #eta_{EP} < 5.0","lp");
  leg->Draw();

  c->cd(2);
  h->Draw();
  g30_35d->Draw("p");
  g35_40d->Draw("p");
  g40_45d->Draw("p");
  g45_50d->Draw("p");
  c->cd(1);
  TLatex * l = new TLatex(-2.4,0.017,Form("%d - %d%c",mincent,maxcent,'%'));
  l->Draw();
  TLatex * l2 = new TLatex(1,0.017,"#eta_{C} = 0");
  l2->Draw();
  c->cd(2);
  l3 = new TLatex(1,0.017,"#eta_{C} = #eta_{ROI}");
  l3->Draw();
  c->Print(plotname.data(),"pdf");
}
