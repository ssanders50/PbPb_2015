#ifndef VNPT
#define VNPT

#include "HiEvtPlaneList.h"
#include "spec.C"
#include "ptav.C"
#include "qn.C"
using namespace hi;
using namespace std;

TGraphErrors * vnpt(int norder = 2, int mincent=10, int maxcent=15, double etamin=-0.8, double etamax=0.8){
  TH1D * hspec = spec(mincent,maxcent,etamin,etamax);
  TH1D * hptav = ptav(mincent,maxcent,etamin,etamax);
  string anal = "";
  int A = -1;
  int B = -1;
  int C = -1;
  if(norder == 1) {
    anal = "N1HFp1g";
  } else if (norder == 2) {
    anal = "N2";
    A = HFp2;
    B = HFm2;
  } else if (norder == 3) {
    anal = "N3";
  } else if (norder == 4) {
    anal = "N4";
  } else if (norder == 5) {
    anal = "N5";
  } else if (norder == 6) {
    anal = "N6";
  } else if (norder == 7) {
    anal = "N7";
  }
  TH1D * qnA = qn(anal,"+",mincent,maxcent,etamin,etamax);
  TH1D * qnB = qn(anal,"-",mincent,maxcent,etamin,etamax);
  double x[10];
  double y[10];
  TGraphErrors * g = new TGraphErrors(10,x,y,0,0);
  return g ;
}

#endif
