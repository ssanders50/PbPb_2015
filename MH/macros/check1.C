TFile * fin = new TFile("../MH.root");
void check1(){
 
  TH2D * qAc = (TH2D *) fin->Get("vnanalyzer/Harmonics/25_30/N112A/qA");
  TH2D * wAc = (TH2D *) fin->Get("vnanalyzer/Harmonics/25_30/N112A/wnA");
  qAc->Divide(wAc);
  TH1D * pjAc = (TH1D *) qAc->ProjectionY("pjAc",1,11);
  TH2D * qBc = (TH2D *) fin->Get("vnanalyzer/Harmonics/25_30/N112A/qB");
  TH2D * wBc = (TH2D *) fin->Get("vnanalyzer/Harmonics/25_30/N112A/wnB");
  qBc->Divide(wBc);
  TH1D * pjBc = (TH1D *) qBc->ProjectionY("pjBc",1,11);

  pjAc->SetMarkerStyle(20);
  pjAc->SetMarkerColor(kBlue);
  pjBc->SetMarkerStyle(24);
  pjBc->SetMarkerColor(kRed);
  
  TCanvas * c = new TCanvas("c","c",1200,900);
  TH1D *  h = (TH1D *) pjAc->Clone("h");
  h->Reset();
  h->SetMaximum(0.001);
  h->SetMinimum(-0.001);
  c->cd();
  h->Draw();
  pjAc->Draw("same");
  pjBc->Draw("same");
  TCanvas * c2 = new TCanvas("c2","c2",1200,900);
  c2->Divide(2,2);
  c2->cd(1);
  gPad->SetRightMargin(0.15);
  TH2D * r = (TH2D *) qBc->Clone("r");
  r->Divide(qAc);
  r->GetXaxis()->SetRange(1,10);
  r->Draw("colz");
  TH2D * rn = (TH2D *) wBc->Clone("rn");
  rn->Divide(wAc);
  c2->cd(2);
  gPad->SetRightMargin(0.15);
  rn->GetXaxis()->SetRange(1,10);
  rn->Draw("colz");
  c2->cd(3);
  TH1D * py1 = (TH1D *) r->ProjectionY("py1",1,10);
  py1->SetMarkerStyle(20);
  py1->SetMarkerColor(kBlue);
  py1->SetMinimum(-500);
  py1->SetMaximum(500);
  py1->Draw();
  c2->cd(4);
  TH1D * py2 = (TH1D *) rn->ProjectionY("py2",1,10);
  py2->SetMarkerStyle(20);
  py2->SetMarkerColor(kBlue);
  py2->Draw();
}
