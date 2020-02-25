#ifndef V1ODD
#define V1ODD
#include "qnint.C"
#ifndef GRAPH
#define GRAPH
bool graph = true;
#endif
#ifndef DEBUG
#define DEBUG
bool debug = true;
#endif
#ifndef DECOR
#define DECOR
bool decor = false;
#endif
#ifndef LEGEND
#define LEGEND
bool legend = true;
#endif
TGraphErrors *  v1odd(int mincent = 15, int maxcent = 20, int marker = 20, int color = kBlack){
  bool threesub = false;
  if(debug) cout<<"infile: "<<infile<<endl;
  if(debug) cout<<"=++++++++++++ A"<<endl;
  TGraphErrors * gA = qnint("N1HFp1f","+",mincent,maxcent,threesub,decor);
  if(debug) cout<<"=++++++++++++ B"<<endl;
  TGraphErrors * gB = qnint("N1HFm1f","-",mincent,maxcent,threesub,decor);
  gB->SetMarkerColor(kRed);
  gB->SetLineColor(kRed);

  TGraphErrors * gOdd = (TGraphErrors *) gA->Clone(Form("%s_Odd",gA->GetName()));
  gOdd->SetMarkerStyle(marker);
  gOdd->SetMarkerColor(color);
  gOdd->SetLineColor(color);
  gOdd->SetMarkerSize(1.2);
  for(int i = 0; i<gOdd->GetN();i++) {
    if(debug) cout<<gA->GetX()[i]<<"\t"<<gA->GetY()[i]<<"\t"<<gB->GetX()[11-i]<<"\t"<<gB->GetY()[11-i]<<endl;
    gOdd->GetY()[i] -= gB->GetY()[11-i];
    gOdd->GetY()[i]/=2.;
  }
  if(graph) {
    TH1D * h = new TH1D("h","h",100,-3,3);
    h->SetXTitle("#eta");
    h->SetYTitle("v_{1}^{odd}");
    h->SetMinimum(-0.05);
    h->SetMaximum(0.05);
    h->Draw();
    gB->SetMarkerStyle(21);
    gA->Draw("p");
    gB->Draw("p");
    gOdd->Draw("p");
    if(legend) {
      TLatex * l = new TLatex(-2.4,0.04,Form("%d - %d%c",mincent,maxcent,'%'));
      l->Draw();
      TLegend * leg = new TLegend(0.35,0.18,0.65,0.28);
      leg->SetBorderSize(0);
      leg->SetTextFont(43);
      leg->SetTextSize(16);
      leg->AddEntry(gOdd,"HF+ - HF-","lp");
      leg->AddEntry(gA,"HF+ (4.5 < #eta < 5.0)","lp");
      leg->AddEntry(gB,"HF- (-5.0 < #eta < -4.5)","lp");
      leg->Draw();
    }
  }
  return gOdd;  
}
#endif
