TFile * fdefault;
TFile * fsys;
double maxR(double val){
  double sign = 1.;
  if(val<0) sign = -1.;
  val=abs(val);
  double ex = trunc(log10(val));
  double rem = log10(val)- trunc(log10(val));
  double rn = 0;
  double remck = 0.8*rem;
  //cout<<val<<"\t"<<remck<<endl;
  if(remck>0) {
    if(remck<log10(1)) {
      rn = log10(1);
    } else if (remck<log10(2)){
      rn = log10(2);
    } else if (remck<log10(4)){
      rn = log10(4);
    } else if (remck<log10(5)){
      rn = log10(5);
    } else if (remck<log10(10)){
      rn = log10(10);
    }
  } else {
    if(remck<log10(0.1)) {
      rn = log10(0.1);
    } else if (remck<log10(.2)){
      rn = log10(.2);
    } else if (remck<log10(.4)){
      rn = log10(.4);
    } else if (remck<log10(.5)){
      rn = log10(.5);
    } else if (remck<log10(1.)){
      rn = log10(1.0);
    }
  }
  //cout<<rn<<endl;
  double ret = sign*pow(10,ex+rn);
  return ret;
}

void CreateSystematics2(string replay, string etarange, string centrange, string gname, string rep1, string rep2, string xlabel="", string ylabel="", string stattype="", string title=""){
  TCanvas * c = new TCanvas("compare","compare",600,900);
  string erange = etarange;
  erange.replace(erange.find("_"),1,"< #eta <");
  string crange = centrange;
  crange.replace(centrange.find("_"),1," - ");
  crange=crange+"%";
  c->Divide(1,3,0.01,0);
  c->cd(1);
  fdefault = new TFile(rep1.data(),"read");
  fsys = new TFile(rep2.data(),"read");
  TGraphErrors * gA = (TGraphErrors *) fsys->Get(Form("%s/%s/%s/%s",replay.data(),etarange.data(),centrange.data(),gname.data()));
  TGraphErrors * gB = (TGraphErrors *) fdefault->Get(Form("%s/%s/%s/%s",replay.data(),etarange.data(),centrange.data(),gname.data()));
  gA->SetMarkerStyle(20);
  gA->SetMarkerColor(kBlue);
  gA->SetLineColor(kBlue);
  gB->SetMarkerStyle(20);
  gB->SetMarkerColor(kRed);
  gB->SetLineColor(kBlue);
  double xminA,yminA,xmaxA,ymaxA;
  gA->ComputeRange(xminA,yminA,xmaxA,ymaxA);
  double xminB,yminB,xmaxB,ymaxB;
  gB->ComputeRange(xminB,yminB,xmaxB,ymaxB);
  double minx = 0;
  double maxx = 10;
  string rng = erange;
  if(gname.find("int")!=std::string::npos) {
    minx = -3;
    maxx = 3; 
    rng = crange;
  } 
 
  
  TH1D * h = new TH1D("h","h",100,minx,maxx);
  double setymin = 0;
  if(min(yminA,yminB)<0) setymin = maxR(min(yminA,yminB)); 
  double setymax = maxR(max(ymaxA,ymaxB));
  if(setymin==0) setymin=0.0001*setymax;
  h->SetMinimum(setymin);
  h->SetMaximum(1.3998*setymax);
  h->SetXTitle(xlabel.data());
  h->SetYTitle(ylabel.data());
  h->GetXaxis()->SetLabelFont(43);
  h->GetXaxis()->SetLabelSize(14);
  h->GetXaxis()->SetTitleFont(43);
  h->GetXaxis()->SetTitleSize(22);
  h->GetXaxis()->SetTitleOffset(2.5);
  h->GetXaxis()->CenterTitle(1);
  h->GetYaxis()->SetLabelFont(43);
  h->GetYaxis()->SetLabelSize(14);
  h->GetYaxis()->SetTitleFont(43);
  h->GetYaxis()->SetTitleSize(22);
  h->GetYaxis()->SetTitleOffset(2.8);
  h->GetYaxis()->CenterTitle(1);
  h->Draw();
  TLatex * lcalc = new TLatex(0.1*(maxx-minx)+minx,1.24*setymax,replay.data());
  lcalc->SetTextFont(43);
  lcalc->SetTextSize(26);
  lcalc->Draw(); 
  TLatex * lr = new TLatex(0.1*(maxx-minx)+minx, 1.1*setymax, rng.data());
  lr->SetTextFont(43);
  lr->SetTextSize(26);
  lr->Draw();
  TLegend * leg = new TLegend(0.75,0.75,0.89,0.9);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(43);
  leg->SetTextSize(24);
  leg->AddEntry(gA,stattype.data(),"lp");
  leg->AddEntry(gB,"default","lp");
  leg->Draw();
  gA->Draw("p");
  gB->Draw("p");
  TGraphErrors * gRatio = (TGraphErrors *) gA->Clone("Ratio");
  for(int i = 0; i<gA->GetN(); i++){ 
    if(gB->GetY()[i]!=0) {
      double y1 = gA->GetY()[i];
      double ey1 = gA->GetEY()[i];
      double y2 = gB->GetY()[i];
      double ey2 = gB->GetEY()[i];
      gRatio->GetY()[i]=y1/y2; 
      double try1 = pow(ey1/y1,2)+pow(ey2/y2,2)-2*pow(ey1,2)/y1/y2;
      double try2 = pow(ey1/y1,2)+pow(ey2/y2,2)-2*pow(ey2,2)/y1/y2;
      double err = 0;
      if(try1>0) {
	err = sqrt(try1);
      } else if(try2>0) {
	err = sqrt(try2);
      } else {
	cout<<"unable to calculate sys error"<<endl;
	err = ey1*gRatio->GetY()[i]/y1;
     }
      gRatio->GetEY()[i] = err;
    }
  }
  c->cd(2);
  TH1D * hr = new TH1D("hr","hr",100,minx,maxx);
  hr->SetMinimum(0.901);
  hr->SetMaximum(0.99*1.1);
  hr->SetXTitle(xlabel.data());
  hr->SetYTitle(Form("%s{%s}/%s{default}",ylabel.data(),stattype.data(),ylabel.data()));
  hr->GetXaxis()->SetLabelFont(43);
  hr->GetXaxis()->SetLabelSize(14);
  hr->GetXaxis()->SetTitleFont(43);
  hr->GetXaxis()->SetTitleSize(22);
  hr->GetXaxis()->SetTitleOffset(2.5);
  hr->GetXaxis()->CenterTitle(1);
  hr->GetYaxis()->SetLabelFont(43);
  hr->GetYaxis()->SetLabelSize(14);
  hr->GetYaxis()->SetTitleFont(43);
  hr->GetYaxis()->SetTitleSize(22);
  hr->GetYaxis()->SetTitleOffset(2.8);
  hr->GetYaxis()->CenterTitle(1);
  gPad->SetGrid(1,1);
  hr->Draw();
  TLine * hrline = new TLine(minx,1.,maxx,1.);
  hrline->SetLineColor(kBlack);
  hrline->SetLineWidth(1);
  hrline->Draw();
  gRatio->Draw("p");
  TGraphErrors * gDiff = (TGraphErrors *) gA->Clone("Ratio");
  for(int i = 0; i<gA->GetN(); i++){ 
    gDiff->GetY()[i]=(gB->GetY()[i]-gA->GetY()[i]); 
    double eA = gA->GetEY()[i];
    double eB = gB->GetEY()[i];
    double e = sqrt(fabs(pow(eA,2)-pow(eB,2)));
    gDiff->GetEY()[i] = e;
  }
  gDiff->ComputeRange(xminA,yminA,xmaxA,ymaxA);
  c->cd(3);
  TH1D * hd = new TH1D("hd","hd",100,minx,maxx);
  setymin = 0;
  if(yminA<0) setymin = maxR(yminA); 
  setymax = maxR(ymaxA);
  hd->SetMinimum(setymin);
  hd->SetMaximum(0.99*setymax);
  hd->SetXTitle(xlabel.data());
  hd->SetYTitle(Form("%s{%s} - %s{default}",ylabel.data(),stattype.data(),ylabel.data()));
  hd->GetXaxis()->SetLabelFont(43);
  hd->GetXaxis()->SetLabelSize(14);
  hd->GetXaxis()->SetTitleFont(43);
  hd->GetXaxis()->SetTitleSize(22);
  hd->GetXaxis()->SetTitleOffset(2.5);
  hd->GetXaxis()->CenterTitle(1);
  hd->GetYaxis()->SetLabelFont(43);
  hd->GetYaxis()->SetLabelSize(14);
  hd->GetYaxis()->SetTitleFont(43);
  hd->GetYaxis()->SetTitleSize(22);
  hd->GetYaxis()->SetTitleOffset(2.8);
  hd->GetYaxis()->CenterTitle(1);
  gPad->SetGrid(1,1);
  hd->Draw();
  gDiff->Draw("p");
  if(gname.find("int")!=std::string::npos) {
    c->Print(Form("systematics/%s_%s_%s_%s.pdf",replay.data(),centrange.data(),gname.data(),stattype.data()),"pdf");
  } else {
    c->Print(Form("systematics/%s_%s_%s_%s.pdf",replay.data(),etarange.data(),gname.data(),stattype.data()),"pdf");
  } 
  
}

void CreateSystematics(){
  CreateSystematics2("N2SUB3","-0.8_0.8","25_30","gint",
   		     "/home/sanders/PbPb_2015/MH/macros/MH_hists.root","/home/sanders/PbPb_2015/MH/macros/MH_narrow_hists.root",
   		     "#eta","v_{2}","narrow","");
  // CreateSystematics2("N2SUB3","-0.8_0.8","25_30","g",
  // 		     "/home/sanders/PbPb_2015/MH/macros/MH_hists.root","/home/sanders/PbPb_2015/MH/macros/MH_narrow_hists.root",
  // 		     "#eta","v_{2}","narrow","");
  //  CreateSystematics2("N3SUB3","-0.8_0.8","25_30","g",
  //		     "/home/sanders/PbPb_2015/MH/macros/MH_hists.root","/home/sanders/PbPb_2015/MH/macros/MH_narrow_hists.root",
  //		     "#eta","v_{2}","narrow","");

}
