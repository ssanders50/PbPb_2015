#include "v1odd.C"
#ifndef INFILE
#define INFILE
string infile = "data.root";
#endif
#ifndef PLOTNAME
#define PLOTNAME
string plotname = "Plot_v1_Integral.pdf";
#endif
void Plot_Integral(){
  graph = true;
  debug = true;
  decor=false;
  TCanvas * c = new TCanvas("c","c",1200,1000);
  c->Divide(2);
  c->cd(1);
  legend = true;
  TGraphErrors * g =  v1odd();
  TLatex * l2; 
  l2 = new TLatex(1,0.04,"#eta_{C} = 0");
  l2->Draw();
  c->cd(2);
  decor=true;
  legend = false;
  TGraphErrors * gd =  v1odd();
  l3 = new TLatex(1.0,0.04,"#eta_{C} = #eta_{ROI}");
  l3->Draw();
  c->Print(plotname.data(),"pdf");

}
