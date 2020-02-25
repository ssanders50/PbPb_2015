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
TGraphErrors *  v1Mixed(int mincent = 10, int maxcent = 60, int marker = 25, int color = kBlack){
  bool threesub = true;
  if(debug) cout<<"infile: "<<infile<<endl;
  if(debug) cout<<"=++++++++++++ A"<<endl;
  TGraphErrors * gA = qnint("N112I","+",mincent,maxcent,threesub,decor);
  if(debug) cout<<"=++++++++++++ B"<<endl;
  TGraphErrors * gB = qnint("N112J","+",mincent,maxcent,threesub,decor);
  gB->SetMarkerColor(kRed);
  gB->SetLineColor(kRed);

  TGraphErrors * gOdd = (TGraphErrors *) gA->Clone(Form("%s_Odd",gA->GetName()));
  gOdd->SetMarkerStyle(marker);
  gOdd->SetMarkerColor(color);
  gOdd->SetLineColor(color);
  gOdd->SetMarkerSize(1.2);
  int gcnt = 0;
  for(int i = 0; i<gOdd->GetN();i++) {
    if(debug) cout<<gA->GetX()[i]<<"\t"<<gA->GetY()[i]<<"\t"<<gB->GetX()[i]<<"\t"<<gB->GetY()[i]<<endl;
    gOdd->GetY()[i] -= gB->GetY()[i];
    gOdd->GetY()[i]/=2.;
  }
  if(graph) {
    TH1D * h = new TH1D("h","h",100,-3,3);
    h->SetXTitle("#eta");
    h->SetYTitle("v_{1}^{odd}");
    h->SetMinimum(-0.0005);
    h->SetMaximum(0.0005);
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
/*
    if(ian==N112A)  Fill_N112(N112A,  ibin, HFp1,   HFm1g, trackm114,   trackp2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112B)  Fill_N112(N112B,  ibin, HFm1,   HFp1g, trackp114,   trackm2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112C)  Fill_N112(N112C,  ibin, HFp1c,  HFm1g, trackm114,   trackp2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112D)  Fill_N112(N112D,  ibin, HFm1c,  HFp1g, trackp114,   trackm2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112E)  Fill_N112(N112E,  ibin, HFp1d,  HFm1g, trackm114,   trackp2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112F)  Fill_N112(N112F,  ibin, HFm1d,  HFp1g, trackp114,   trackm2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112G)  Fill_N112(N112G,  ibin, HFp1e,  HFm1g, trackm114,   trackp2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112H)  Fill_N112(N112H,  ibin, HFm1e,  HFp1g, trackp114,   trackm2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112I)  Fill_N112(N112I,  ibin, HFp1f,  HFm1g, trackm114,   trackp2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112J)  Fill_N112(N112J,  ibin, HFm1f,  HFp1g, trackp114,   trackm2, HFp2, HFm2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
    if(ian==N112MCA)  Fill_N112(N112MCA,  ibin, trackm122mc, trackp122mc, trackmid1mc,     HFp2, HFm2, trackmid2, qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);
     if(ian==N112Combined)  Fill_N112Combined(N112Combined,  ibin,  HFp1g, HFm1g, HFm1e, trackmid2, HFp2, HFm2,qxtrk[0], qytrk[0], qcnt, qx, qy, sumw);



void Fill_N112(int anal, int bin, int a1, int b1, int c1, int a2, int b2, int c2, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
  double a1x = qx[a1];
  double a1y = qy[a1];
  double a1w = sumw[a1];
  double b1x = qx[b1];
  double b1y = qy[b1];
  double b1w = sumw[b1];
  double c1x = qx[c1];
  double c1y = qy[c1];
  double c1w = sumw[c1];

  double a2x = qx[a2];
  double a2y = qy[a2];
  double a2w = sumw[a2];
  double b2x = qx[b2];
  double b2y = qy[b2];
  double b2w = sumw[b2];
  double c2x = qx[c2];
  double c2y = qy[c2];
  double c2w = sumw[c2];


  if(pow(a1x,2)+pow(a1y,2) < 1e-12) return;
  if(pow(b1x,2)+pow(b1y,2) < 1e-12) return;
  if(pow(c1x,2)+pow(c1y,2) < 1e-12) return;
  if(pow(a2x,2)+pow(a2y,2) < 1e-12) return;
  if(pow(b2x,2)+pow(b2y,2) < 1e-12) return;
  if(pow(c2x,2)+pow(c2y,2) < 1e-12) return;
  
  qanal[anal].thA[bin][0]->Fill(TMath::ATan2(a1y,a1x)/EPOrder[a1]);
  qanal[anal].thB[bin][0]->Fill(TMath::ATan2(b1y,b1x)/EPOrder[b1]);
  qanal[anal].thC[bin][0]->Fill(TMath::ATan2(c1y,c1x)/EPOrder[c1]);
  qanal[anal].thA2[bin][0]->Fill(TMath::ATan2(a2y,a2x)/EPOrder[a2]);
  qanal[anal].thB2[bin][0]->Fill(TMath::ATan2(b2y,b2x)/EPOrder[b2]);
  qanal[anal].thC2[bin][0]->Fill(TMath::ATan2(c2y,c2x)/EPOrder[c2]);
  qanal[anal].thn[bin][0]->Fill(TMath::ATan2(qytrk_->GetBinContent(5,9),qxtrk_->GetBinContent(5,9))/EPOrder[a1]);

  qanal[anal].qA[bin][0]->Add(qxtrk_,  a1x*a2x+a1y*a2y);
  qanal[anal].qA[bin][0]->Add(qytrk_, -a1y*a2x+a1x*a2y);
  qanal[anal].qB[bin][0]->Add(qxtrk_,  b1x*a2x+b1y*a2y);
  qanal[anal].qB[bin][0]->Add(qytrk_, -b1y*a2x+b1x*a2y);
  qanal[anal].wnA[bin][0]->Add(qcnt_,a1w*a2w);
  qanal[anal].wnB[bin][0]->Add(qcnt_,b1w*a2w);
  qanal[anal].qBA[bin][0]->Fill(0., a1x*b1x + a1y*b1y);
  qanal[anal].qCA[bin][0]->Fill(0., a1x*c1x + a1y*c1y); 
  qanal[anal].qCB[bin][0]->Fill(0., b1x*c1x + b1y*c1y);
  qanal[anal].qBAcnt[bin][0]->Fill(0.,b1w*a1w);
  qanal[anal].qCAcnt[bin][0]->Fill(0.,a1w*c1w);
  qanal[anal].qCBcnt[bin][0]->Fill(0.,b1w*c1w);
  qanal[anal].qBA2[bin][0]->Fill(0., a2x*b2x + a2y*b2y);
  qanal[anal].qCA2[bin][0]->Fill(0., a2x*c2x + a2y*c2y); 
  qanal[anal].qCB2[bin][0]->Fill(0., b2x*c2x + b2y*c2y);
  qanal[anal].qBAcnt2[bin][0]->Fill(0.,b2w*a2w);
  qanal[anal].qCAcnt2[bin][0]->Fill(0.,a2w*c2w);
  qanal[anal].qCBcnt2[bin][0]->Fill(0.,b2w*c2w);
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qanal[anal].qA[bin][j]->Add(qxtrk_,  a1x*a2x+a1y*a2y);
  qanal[anal].qA[bin][j]->Add(qytrk_, -a1y*a2x+a1x*a2y);
  qanal[anal].qB[bin][j]->Add(qxtrk_,  b1x*a2x+b1y*a2y);
  qanal[anal].qB[bin][j]->Add(qytrk_, -b1y*a2x+b1x*a2y);
  qanal[anal].wnA[bin][j]->Add(qcnt_,a1w*a2w);
  qanal[anal].wnB[bin][j]->Add(qcnt_,b1w*a2w);
  qanal[anal].qBA[bin][j]->Fill(0., a1x*b1x + a1y*b1y);
  qanal[anal].qCA[bin][j]->Fill(0., a1x*c1x + a1y*c1y); 
  qanal[anal].qCB[bin][j]->Fill(0., b1x*c1x + b1y*c1y);
  qanal[anal].qBAcnt[bin][j]->Fill(0.,b1w*a1w);
  qanal[anal].qCAcnt[bin][j]->Fill(0.,a1w*c1w);
  qanal[anal].qCBcnt[bin][j]->Fill(0.,b1w*c1w);
  qanal[anal].qBA2[bin][j]->Fill(0., a2x*b2x + a2y*b2y);
  qanal[anal].qCA2[bin][j]->Fill(0., a2x*c2x + a2y*c2y); 
  qanal[anal].qCB2[bin][j]->Fill(0., b2x*c2x + b2y*c2y);
  qanal[anal].qBAcnt2[bin][j]->Fill(0.,b2w*a2w);
  qanal[anal].qCAcnt2[bin][j]->Fill(0.,a2w*c2w);
  qanal[anal].qCBcnt2[bin][j]->Fill(0.,b2w*c2w);
}

void Fill_N112Combined(int anal, int bin, int a1, int b1, int c1, int a2, int b2, int c2,TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){

  double a1x = qx[a1];
  double a1y = qy[a1];
  double b1x = qx[b1];
  double b1y = qy[b1];
  double c1x = qx[c1];
  double c1y = qy[c1];
  
  double a2x = qx[a2];
  double a2y = qy[a2];
  double b2x = qx[b2];
  double b2y = qy[b2];
  double c2x = qx[c2];
  double c2y = qy[c2];
  
  if(pow(a1x,2)+pow(a1y,2) < 1e-8) return;
  if(pow(b1x,2)+pow(b1y,2) < 1e-8) return;
  if(pow(c1x,2)+pow(c1y,2) < 1e-8) return;
  if(pow(a2x,2)+pow(a2y,2) < 1e-8) return;
  if(pow(b2x,2)+pow(b2y,2) < 1e-8) return;
  if(pow(c2x,2)+pow(c2y,2) < 1e-8) return;
  
  a2x/=sqrt(pow(a2x,2)+pow(a2y,2));
  a2y/=sqrt(pow(a2x,2)+pow(a2y,2));
  b2x/=sqrt(pow(b2x,2)+pow(b2y,2));
  b2y/=sqrt(pow(b2x,2)+pow(b2y,2));
  c2x/=sqrt(pow(c2x,2)+pow(c2y,2));
  c2y/=sqrt(pow(c2x,2)+pow(c2y,2));
  
  double psi1A = TMath::ATan2(a1y,a1x);
  double psi1B = TMath::ATan2(b1y,b1x)+TMath::Pi();
  double psi2A = TMath::ATan2(a2y,a2x)/2.;
  double psi2B = TMath::ATan2(b2y,b2x)/2.;
  double psi2C = TMath::ATan2(c2y,c2x)/2.;
  qanal[anal].qA[bin][0]->Add(qxtrk_, TMath::Cos(psi1A-2*psi2A));
  qanal[anal].qA[bin][0]->Add(qytrk_, -TMath::Sin(psi1A-2*psi2A));
  qanal[anal].qB[bin][0]->Add(qxtrk_, TMath::Cos(psi1B-2*psi2A));
  qanal[anal].qB[bin][0]->Add(qytrk_, -TMath::Sin(psi1B-2*psi2A));
  qanal[anal].wnA[bin][0]->Add(qcnt_);
  qanal[anal].wnB[bin][0]->Add(qcnt_);
  qanal[anal].qBA[bin][0]->Fill(0., TMath::Cos(psi1A+psi1B-2*psi2A));
  qanal[anal].qCA[bin][0]->Fill(0.); 
  qanal[anal].qCB[bin][0]->Fill(0.);
  qanal[anal].qBAcnt[bin][0]->Fill(0.);
  qanal[anal].qCAcnt[bin][0]->Fill(0.);
  qanal[anal].qCBcnt[bin][0]->Fill(0.);
  qanal[anal].qBA2[bin][0]->Fill(0., TMath::Cos(psi2A-psi2B));
  qanal[anal].qCA2[bin][0]->Fill(0., TMath::Cos(psi2A-psi2C)); 
  qanal[anal].qCB2[bin][0]->Fill(0., TMath::Cos(psi2B-psi2C));
  qanal[anal].qBAcnt2[bin][0]->Fill(0.);
  qanal[anal].qCAcnt2[bin][0]->Fill(0.);
  qanal[anal].qCBcnt2[bin][0]->Fill(0.);
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qanal[anal].qA[bin][j]->Add(qxtrk_, TMath::Cos(psi1A-2*psi2A));
  qanal[anal].qA[bin][j]->Add(qytrk_, -TMath::Sin(psi1A-2*psi2A));
  qanal[anal].qB[bin][j]->Add(qxtrk_, TMath::Cos(psi1B-2*psi2A));
  qanal[anal].qB[bin][j]->Add(qytrk_, -TMath::Sin(psi1B-2*psi2A));
  qanal[anal].wnA[bin][j]->Add(qcnt_);
  qanal[anal].wnB[bin][j]->Add(qcnt_);
  qanal[anal].qBA[bin][j]->Fill(0., TMath::Cos(psi1A+psi1B-2*psi2A));
  qanal[anal].qCA[bin][j]->Fill(0.); 
  qanal[anal].qCB[bin][j]->Fill(0.);
  qanal[anal].qBAcnt[bin][j]->Fill(0.);
  qanal[anal].qCAcnt[bin][j]->Fill(0.);
  qanal[anal].qCBcnt[bin][j]->Fill(0.);
  qanal[anal].qBA2[bin][j]->Fill(0., TMath::Cos(psi2A-psi2B));
  qanal[anal].qCA2[bin][j]->Fill(0., TMath::Cos(psi2A-psi2C)); 
  qanal[anal].qCB2[bin][j]->Fill(0., TMath::Cos(psi2B-psi2C));
  qanal[anal].qBAcnt2[bin][j]->Fill(0.);
  qanal[anal].qCAcnt2[bin][j]->Fill(0.);
  qanal[anal].qCBcnt2[bin][j]->Fill(0.);
}





*/
