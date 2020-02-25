TFile * tf = new TFile("vnPlots.root");
TGraphErrors * GetPtDist(string type="N2SUB3", string eta="-0.8_0.8", string cent="10_15", TGraphErrors * sys=0, bool draw = false) {
  string base = "default/"+type+"/"+eta+"/"+cent;
  TGraphErrors * g = (TGraphErrors *) tf->Get(Form("%s/g",base.data()));
  sys = (TGraphErrors *) g->Clone("sys");
  TCanvas *canTrack = (TCanvas *) tf->Get(Form("%s/systematics/g_trackQuality",base.data()));
  TCanvas *canVtx = (TCanvas *) tf->Get(Form("%s/systematics/g_vtxRange",base.data()));
  TGraphErrors * sysTrack = (TGraphErrors *) canTrack->FindObject("DifferenceABS");
  TGraphErrors * sysVtx = (TGraphErrors *) canVtx->FindObject("DifferenceABS");
  TCanvas * c=0;
  TH1D * h=0;
  if(draw) {
    h = new TH1D("h","h",100,0,10);
    c = new TCanvas("c","c",900,1200);
    c->Divide(1,2);
    h->SetMinimum(-2);
    h->SetMaximum(2);
  }
  double minlow = 0.2;
  double maxlow = 1.5;
  double minmid = 1.0;
  double maxmid = 3.0;
  double minhigh = 2.0;
  double maxhigh = 10.0;
  TF1 * fitTrackLow = new TF1("fitTrackLow","pol2",minlow,maxlow);
  TF1 * fitTrackMid = new TF1("fitTrackMid","pol2",minmid,maxmid);
  TF1 * fitTrackHigh = new TF1("fitTrackHigh","pol2",minhigh,maxhigh);
  sysTrack->Fit(fitTrackLow,"qnR");
  sysTrack->Fit(fitTrackMid,"qnR");
  sysTrack->Fit(fitTrackHigh,"qnR");
  TF1 * fitVtxLow = new TF1("fitVtxLow","pol2",minlow,maxlow);
  TF1 * fitVtxMid = new TF1("fitVtxMid","pol2",minmid,maxmid);
  TF1 * fitVtxHigh = new TF1("fitVtxHigh","pol2",minhigh,maxhigh);
  sysVtx->Fit(fitVtxLow,"qnR");
  sysVtx->Fit(fitVtxMid,"qnR");
  sysVtx->Fit(fitVtxHigh,"qnR");
  if(draw) {
    c->cd(1);
    h->Draw();
    sysTrack->Draw("p");
    fitTrackLow->Draw("same");
    fitTrackMid->Draw("same");
    fitTrackHigh->Draw("same");
    c->cd(2);
    h->Draw();
    sysVtx->Draw("p");
    fitVtxLow->Draw("same");
    fitVtxMid->Draw("same");
    fitVtxHigh->Draw("same");
  }
  for(int i = 0; i<g->GetN(); i++) {
    double pt = g->GetX()[i];
    double sysTrack = 0;
    double sysVtx = 0;
    if( pt<minmid ) {sysTrack = fitTrackLow->Eval(pt);sysVtx = fitVtxLow->Eval(pt);}
    if( minmid<pt<=maxlow) {sysTrack = (fitTrackLow->Eval(pt)+fitTrackMid->Eval(pt))/2.;sysVtx = (fitVtxLow->Eval(pt)+fitVtxMid->Eval(pt))/2.;}
    if( maxlow<pt<=minhigh) {sysTrack = fitTrackMid->Eval(pt); sysVtx = fitVtxMid->Eval(pt);}
    if( minhigh<pt<=maxmid) {sysTrack = (fitTrackMid->Eval(pt)+fitTrackHigh->Eval(pt))/2.;sysVtx = (fitVtxMid->Eval(pt)+fitVtxHigh->Eval(pt))/2.;}
    if( pt>maxmid ) {sysTrack = fitTrackHigh->Eval(pt);sysTrack = fitVtxHigh->Eval(pt);}
    sysTrack=fabs(sysTrack)/1000;
    sysVtx=fabs(sysVtx)/1000;
    double sys = sqrt(pow(sysTrack,2)+pow(sysVtx,2));
    cout<<g->GetX()[i]<<"\t"<<g->GetY()[i]<<"\t"<<g->GetEY()[i]<<"\t"<<sysTrack<<"\t"<<100*sys/g->GetY()[i]<<endl;
  }
  
  return g;
}
