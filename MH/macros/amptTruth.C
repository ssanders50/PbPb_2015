TFile * tf = new TFile("../MH_AMPT.root");
TFile * tfdata = new TFile("vnPlots.root");
static const int cent[]={0,5,10,15,20,25,30,35,40,50,60,70,80,100};
void fix(TH1D * h, int marker, int color, double ymin, double ymax, string xtitle, string ytitle){
  h->SetMarkerStyle(marker);
  h->SetMarkerColor(color);
  h->SetLineColor(color);
  h->SetMinimum(ymin);
  h->SetMaximum(ymax);
  h->SetXTitle(xtitle.data());
  h->SetYTitle(ytitle.data());
  h->GetXaxis()->SetTitleFont(43);
  h->GetXaxis()->SetTitleSize(24);
  h->GetXaxis()->SetTitleOffset(1.6);
  h->GetYaxis()->SetTitleFont(43);
  h->GetYaxis()->SetTitleSize(24);
  h->GetYaxis()->SetTitleOffset(3.4);
  h->GetXaxis()->SetLabelFont(43);
  h->GetXaxis()->SetLabelSize(16);
  //h->GetXaxis()->SetLabelOffset(1.6);
  h->GetYaxis()->SetLabelFont(43);
  h->GetYaxis()->SetLabelSize(16);
  //h->GetYaxis()->SetLabelOffset(2.2);
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();

  return;
}
void fixG(TGraphErrors * g, int marker, int color){
  g->SetMarkerStyle(marker);
  g->SetMarkerColor(color);
  g->SetLineColor(color);
  return;
}
void amptTruth(int icent = 5){
  TH2D * v1_2D;
  TH2D * v2_2D;
  TH1D * v1etaRP;
  TH1D * v2etaRP;
  TGraphErrors * v1eta[5];
  TGraphErrors * v2eta[5];
  TGraphErrors * v1etaA[5];
  TGraphErrors * v2etaA[5];
  TGraphErrors * v1etaB[5];
  TGraphErrors * v2etaB[5];
  TGraphErrors * v1eta_decor[5];
  TGraphErrors * v2eta_decor[5];
  TGraphErrors * v1etaA_decor[5];
  TGraphErrors * v2etaA_decor[5];
  TGraphErrors * v1etaB_decor[5];
  TGraphErrors * v2etaB_decor[5];

  TGraphErrors * v1eta_AMPT[5];
  TGraphErrors * v2eta_AMPT[5];
  TGraphErrors * v1etaA_AMPT[5];
  TGraphErrors * v2etaA_AMPT[5];
  TGraphErrors * v1etaB_AMPT[5];
  TGraphErrors * v2etaB_AMPT[5];
  TGraphErrors * v1eta_decor_AMPT[5];
  TGraphErrors * v2eta_decor_AMPT[5];
  TGraphErrors * v1etaA_decor_AMPT[5];
  TGraphErrors * v2etaA_decor_AMPT[5];
  TGraphErrors * v1etaB_decor_AMPT[5];
  TGraphErrors * v2etaB_decor_AMPT[5];
  TH2D * vcnt_2D;
  TH1D * vcnt_1D;
  TCanvas * can[5];
  TLegend * legA[5];
  TLegend * legB[5];
  TLegend * legC[5];
  double etaHFmin;
  double etaHFmax;
  string crng = to_string(cent[icent])+"_"+to_string(cent[icent+1]);
  v1_2D = (TH2D *) tf->Get(Form("vnanalyzer/MC/%s/v1",crng.data()));
  v2_2D = (TH2D *) tf->Get(Form("vnanalyzer/MC/%s/v2",crng.data()));
  v1etaRP = (TH1D *) v1_2D->ProjectionY(Form("v1eta_%s",crng.data()),1,10);
  v2etaRP = (TH1D *) v2_2D->ProjectionY(Form("v2eta_%s",crng.data()),1,10);
  vcnt_2D = (TH2D *) tf->Get(Form("vnanalyzer/MC/%s/vnCntMC",crng.data()));
  vcnt_1D = (TH1D *) vcnt_2D->ProjectionY(Form("vcnt_%s",crng.data()),1,10);
  v1etaRP->Divide(vcnt_1D);
  v2etaRP->Divide(vcnt_1D);
  fix(v1etaRP,20,kBlue,-0.08,0.04,"#eta","v_{1}");
  fix(v2etaRP,20,kBlue,-0.05,0.2,"#eta","v_{2}");
  for(int j = 0; j< 5; j++) {
    char etahf = 'c'+j;
    if(etahf=='c') {
      etaHFmin = 3.0;
      etaHFmax = 3.5;
    }
    if(etahf=='d') {
      etaHFmin = 3.5;
      etaHFmax = 4.0;
    }
    if(etahf=='e') {
      etaHFmin = 4.0;
      etaHFmax = 4.5;
    }
    if(etahf=='f') {
      etaHFmin = 4.5;
      etaHFmax = 5.0;
    }
    if(etahf=='g') {
      etaHFmin = 4.0;
      etaHFmax = 5.0;
    }
    
    
    v1eta[j] = (TGraphErrors *) tfdata->Get(Form("default/N1HF%cSUB3/-0.8_0.8/%s/gint",etahf,crng.data()));
    v2eta[j] = (TGraphErrors *) tfdata->Get(Form("default/N2SUB3/-0.8_0.8/%s/gint",crng.data()));
    v1etaA[j] = (TGraphErrors *) tfdata->Get(Form("default/N1HF%cSUB3/-0.8_0.8/%s/gintA",etahf,crng.data()));
    v2etaA[j] = (TGraphErrors *) tfdata->Get(Form("default/N2SUB3/-0.8_0.8/%s/gintA",crng.data()));
    v1etaB[j] = (TGraphErrors *) tfdata->Get(Form("default/N1HF%cSUB3/-0.8_0.8/%s/gintB",etahf,crng.data()));
    v2etaB[j] = (TGraphErrors *) tfdata->Get(Form("default/N2SUB3/-0.8_0.8/%s/gintB",crng.data()));
    fixG(v1eta[j],21,kRed);
    fixG(v2eta[j],21,kRed);
    fixG(v1etaA[j],25,kRed);
    fixG(v2etaA[j],25,kRed);
    fixG(v1etaB[j],24,kRed);
    fixG(v2etaB[j],24,kRed);
    
    v1eta_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N1HF%cSUB3/-0.8_0.8/%s/gint",etahf,crng.data()));
    v2eta_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N2SUB3/-0.8_0.8/%s/gint",crng.data()));
    v1etaA_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N1HF%cSUB3/-0.8_0.8/%s/gintA",etahf,crng.data()));
    v2etaA_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N2SUB3/-0.8_0.8/%s/gintA",crng.data()));
    v1etaB_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N1HF%cSUB3/-0.8_0.8/%s/gintB",etahf,crng.data()));
    v2etaB_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N2SUB3/-0.8_0.8/%s/gintB",crng.data()));
    fixG(v1eta_AMPT[j],21,kGreen);
    fixG(v2eta_AMPT[j],21,kGreen);
    fixG(v1etaA_AMPT[j],25,kGreen);
    fixG(v2etaA_AMPT[j],25,kGreen);
    fixG(v1etaB_AMPT[j],24,kGreen);
    fixG(v2etaB_AMPT[j],24,kGreen);
    
    v1eta_decor[j] = (TGraphErrors *) tfdata->Get(Form("default/N1HF%cSUB3_decor/-0.8_0.8/%s/gint",etahf,crng.data()));
    v2eta_decor[j] = (TGraphErrors *) tfdata->Get(Form("default/N2SUB3_decor/-0.8_0.8/%s/gint",crng.data()));
    v1etaA_decor[j] = (TGraphErrors *) tfdata->Get(Form("default/N1HF%cSUB3_decor/-0.8_0.8/%s/gintA",etahf,crng.data()));
    v2etaA_decor[j] = (TGraphErrors *) tfdata->Get(Form("default/N2SUB3_decor/-0.8_0.8/%s/gintA",crng.data()));
    v1etaB_decor[j] = (TGraphErrors *) tfdata->Get(Form("default/N1HF%cSUB3_decor/-0.8_0.8/%s/gintB",etahf,crng.data()));
    v2etaB_decor[j] = (TGraphErrors *) tfdata->Get(Form("default/N2SUB3_decor/-0.8_0.8/%s/gintB",crng.data()));
    fixG(v1eta_decor[j],21,kRed);
    fixG(v2eta_decor[j],21,kRed);
    fixG(v1etaA_decor[j],25,kRed);
    fixG(v2etaA_decor[j],25,kRed);
    fixG(v1etaB_decor[j],24,kRed);
    fixG(v2etaB_decor[j],24,kRed);
    
    v1eta_decor_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N1HF%cSUB3_decor/-0.8_0.8/%s/gint",etahf,crng.data()));
    v2eta_decor_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N2SUB3_decor/-0.8_0.8/%s/gint",crng.data()));
    v1etaA_decor_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N1HF%cSUB3_decor/-0.8_0.8/%s/gintA",etahf,crng.data()));
    v2etaA_decor_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N2SUB3_decor/-0.8_0.8/%s/gintA",crng.data()));
    v1etaB_decor_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N1HF%cSUB3_decor/-0.8_0.8/%s/gintB",etahf,crng.data()));
    v2etaB_decor_AMPT[j] = (TGraphErrors *) tfdata->Get(Form("AMPT/N2SUB3_decor/-0.8_0.8/%s/gintB",crng.data()));
    fixG(v1eta_decor_AMPT[j],21,kGreen);
    fixG(v2eta_decor_AMPT[j],21,kGreen);
    fixG(v1etaA_decor_AMPT[j],25,kGreen);
    fixG(v2etaA_decor_AMPT[j],25,kGreen);
    fixG(v1etaB_decor_AMPT[j],24,kGreen);
    fixG(v2etaB_decor_AMPT[j],24,kGreen);
    
    string crngn = crng + "_" + Form("%3.1f_%3.1f",etaHFmin,etaHFmax);
    can[j] = new TCanvas(Form("canAMPT_%s",crngn.data()),Form("canAMPT_%s",crngn.data()),1000,900);
    can[j]->Divide(2,2);
    can[j]->cd(1);
    v1etaRP->Draw();
    TLatex * l1 = new TLatex(1.0,0.02,"#eta_{C} = 0");
    l1->Draw();
    TLatex * l1A = new TLatex(0.5,0.03,Form("%3.1f<|#eta_{HF}|<%3.1f",etaHFmin,etaHFmax));
    l1A->Draw();
    v1eta[j]->Draw("p");
    v1etaA[j]->Draw("p");
    v1etaB[j]->Draw("p");
    v1eta_AMPT[j]->Draw("p");
    v1etaA_AMPT[j]->Draw("p");
    v1etaB_AMPT[j]->Draw("p");
    can[j]->cd(2);
    v2etaRP->Draw();
    TLatex * l1AA = new TLatex(0.5,0.184,"3.0<|#eta_{HF}|<5.0");
    l1AA->Draw();
    v2eta[j]->Draw("p");
    v2etaA[j]->Draw("p");
    v2etaB[j]->Draw("p");
    v2eta_AMPT[j]->Draw("p");
    v2etaA_AMPT[j]->Draw("p");
    v2etaB_AMPT[j]->Draw("p");
    
    can[j]->cd(3);
    v1etaRP->Draw();
    TLatex * l2 = new TLatex(1.0,0.03,"#eta_{C} = #eta_{ROI}");
    l2->Draw();
    v1eta_decor[j]->Draw("p");
    v1etaA_decor[j]->Draw("p");
    v1etaB_decor[j]->Draw("p");
    v1eta_decor_AMPT[j]->Draw("p");
    v1etaA_decor_AMPT[j]->Draw("p");
    v1etaB_decor_AMPT[j]->Draw("p");
    can[j]->cd(4);
    v2etaRP->Draw();
    v2eta_decor[j]->Draw("p");
    v2etaA_decor[j]->Draw("p");
    v2etaB_decor[j]->Draw("p");
    v2eta_decor_AMPT[j]->Draw("p");
    v2etaA_decor_AMPT[j]->Draw("p");
    v2etaB_decor_AMPT[j]->Draw("p");
    legA[j]=new TLegend(0.19,0.15,0.37,0.3);
    legA[j]->SetBorderSize(0);
    legA[j]->SetTextFont(43);
    legA[j]->SetTextSize(14);
    legA[j]->AddEntry(v1etaRP,"v_{n}^{AMPT} \{RP}","p");
    legA[j]->Draw();
    legB[j]=new TLegend(0.4,0.15,0.63,0.3);
    legB[j]->SetBorderSize(0);
    legB[j]->SetTextFont(43);
    legB[j]->SetTextSize(14);
    legB[j]->AddEntry(v1eta[j],"v_{n}^{DATA} \{EP}","p");
    legB[j]->AddEntry(v1etaA[j],"v_{n}^{DATA} \{EP:HF+}","p");
    legB[j]->AddEntry(v1etaB[j],"v_{n}^{DATA} \{EP:HF-}","p");
    legB[j]->Draw();
    legC[j]=new TLegend(0.65,0.15,0.95,0.3);
    legC[j]->SetBorderSize(0);
    legC[j]->SetTextFont(43);
    legC[j]->SetTextSize(14);
    legC[j]->AddEntry(v1eta_AMPT[j],"v_{n}^{AMPT} \{EP}","p");
    legC[j]->AddEntry(v1etaA_AMPT[j],"v_{n}^{AMPT} \{EP:HF+}","p");
    legC[j]->AddEntry(v1etaB_AMPT[j],"v_{n}^{AMPT} \{EP:HF-}","p");
    legC[j]->Draw();
    if(j==0) {
      can[j]->cd(1);
      TLatex * cr = new TLatex(-2,0.02,Form("%d - %d%c",cent[icent],cent[icent+1],'%'));
      cr->Draw();
    }
    can[j]->Print(Form("amptFigs/%s_%3.1f_%3.1f.pdf",can[j]->GetName(),etaHFmin,etaHFmax),"pdf");
  }
  
  TCanvas * c2;
  TLegend * legA2;
  TLegend * legB2;
  TLegend * legC2;
  legA2=new TLegend(0.3,0.2,0.5,0.3);
  legA2->SetBorderSize(0);
  legA2->SetTextFont(43);
  legA2->SetTextSize(14);
  legA2->AddEntry(v1etaRP,"v_{n}^{AMPT} \{RP}","p");
  legB2=new TLegend(0.3,0.2,0.5,0.3);
  legB2->SetBorderSize(0);
  legB2->SetTextFont(43);
  legB2->SetTextSize(14);
  legB2->AddEntry(v1eta[0],"v_{n}^{DATA} \{EP}","p");
  legB2->AddEntry(v1etaA[0],"v_{n}^{DATA} \{EP:HF+}","p");
  legB2->AddEntry(v1etaB[0],"v_{n}^{DATA} \{EP:HF-}","p");
  legC2=new TLegend(0.3,0.2,0.5,0.3);
  legC2->SetBorderSize(0);
  legC2->SetTextFont(43);
  legC2->SetTextSize(14);
  legC2->AddEntry(v1eta_AMPT[0],"v_{n}^{AMPT} \{EP}","p");
  legC2->AddEntry(v1etaA_AMPT[0],"v_{n}^{AMPT} \{EP:HF+}","p");
  legC2->AddEntry(v1etaB_AMPT[0],"v_{n}^{AMPT} \{EP:HF-}","p");
  string c2rngn = "epscan_"+crng;
  c2 = new TCanvas(c2rngn.data(),c2rngn.data(),1400,1000);
  c2->Divide(5,2,0.,0.);
  for(int j=0;j<5;j++) {
    char etahf = 'c'+j;
    if(etahf=='c') {
      etaHFmin = 3.0;
      etaHFmax = 3.5;
    }
    if(etahf=='d') {
      etaHFmin = 3.5;
      etaHFmax = 4.0;
    }
    if(etahf=='e') {
      etaHFmin = 4.0;
      etaHFmax = 4.5;
    }
    if(etahf=='f') {
      etaHFmin = 4.5;
      etaHFmax = 5.0;
    }
    if(etahf=='g') {
      etaHFmin = 4.0;
      etaHFmax = 5.0;
    }
    
    c2->cd(j+1);
    v1etaRP->Draw();
    v1eta[j]->Draw("p");
    v1etaA[j]->Draw("p");
    v1etaB[j]->Draw("p");
    v1eta_AMPT[j]->Draw("p");
    v1etaA_AMPT[j]->Draw("p");
    v1etaB_AMPT[j]->Draw("p");
    TLatex * al1A = new TLatex(0.0,0.03,Form("%3.1f<|#eta_{HF}|<%3.1f",etaHFmin,etaHFmax));
    al1A->SetTextFont(43);
    al1A->SetTextSize(20);
    al1A->Draw();
    c2->cd(j+6);
    v1etaRP->Draw();
    v1eta_decor[j]->Draw("p");
    v1etaA_decor[j]->Draw("p");
    v1etaB_decor[j]->Draw("p");
    v1eta_decor_AMPT[j]->Draw("p");
    v1etaA_decor_AMPT[j]->Draw("p");
    v1etaB_decor_AMPT[j]->Draw("p");
    
    if(j==0) {
      c2->cd(1);
      TLatex * al1 = new TLatex(-2.0,0.021,"#eta_{C} = 0");
      al1->Draw();
      TLatex * cr = new TLatex(-2,0.03,Form("%d - %d%c",cent[icent],cent[icent+1],'%'));
      cr->SetTextFont(43);
      cr->SetTextSize(20);
      cr->Draw();
      c2->cd(6);
      TLatex * bl1 = new TLatex(-2.0,0.021,"#eta_{C} = #eta_{ROI}");
      bl1->Draw();
      legA2->Draw();
      
    }
    if(j==1) {
      legB2->Draw();
    }
    if(j==2) {
      legC2->Draw();
    }
  }
  c2->Print(Form("amptFigs/%s.pdf",c2->GetTitle()),"pdf");
  TCanvas * c3 = new TCanvas("c3","c3",500,400);
  c3->cd();
  
  cout<<"finished"<<endl;
}
