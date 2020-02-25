#ifndef QAB
#define QAB
#ifndef INFILE
#define INFILE
string infile = "data.root";
#endif
#ifndef DEBUG
#define DEBUG
bool debug = false;
#endif
#include "HiEvtPlaneList.h"
using namespace hi;
using namespace std;
int fbeg[7] = {HFm1,HFm2,HFm3,HFm4,HFm5,HFm6,HFm7};
double qAB(int Aname=HFm2, int Bname=HFp2, string crnge="15_20"){
  TFile * fin = new TFile(infile.data());
  TH2D *res;
  TH2D *resw;
  if(EPOrder[Aname]==EPOrder[Bname]) {
    res = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/res%d",crnge.data(),EPOrder[Aname]));
    resw = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/resw%d",crnge.data(),EPOrder[Aname]));
  }  else if(EPOrder[Aname]==1 && EPOrder[Bname]==2) {
    res = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/res12",crnge.data()));
    resw = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/resw12",crnge.data()));
  }
  res->Divide(resw);
  int indx1 = Aname-fbeg[EPOrder[Aname]-1];
  int indx2 = Bname-fbeg[EPOrder[Bname]-1];
  if(indx2<indx1) {
    int hold = indx1;
    indx1 = indx2;
    indx2 = hold;
  }

  double ret = res->GetBinContent(indx1+1,indx2+1);
  fin->Close();
  return ret;

}
double resAB(int Aname=HFm2, int Bname=HFp2,  string crnge="15_20"){
  TFile * fin = new TFile(infile.data());
  TH2D *res;
  TH2D *resw;
  if(EPOrder[Aname]==EPOrder[Bname]) {
    res = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/resep%d",crnge.data(),EPOrder[Aname]));
    resw = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/rescnt%d",crnge.data(),EPOrder[Aname]));
  }  else if(EPOrder[Aname]==1 && EPOrder[Bname]==2) {
    res = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/resep12",crnge.data()));
    resw = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%s/rescnt12",crnge.data()));
  }
  res->Divide(resw);
  int indx1 = Aname-fbeg[EPOrder[Aname]-1];
  int indx2 = Bname-fbeg[EPOrder[Bname]-1];

  if(indx2<indx1) {
    int hold = indx1;
    indx1 = indx2;
    indx2 = hold;
  }
  double ret = res->GetBinContent(indx1+1,indx2+1);
  if(debug) cout<<EPNames[Aname]<<"/"<<EPNames[Bname]<<" EP Resolution "<<crnge<<"\t"<<ret<<endl;
  fin->Close();
  return ret;

}
#endif
