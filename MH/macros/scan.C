double maxR(double val);
TCanvas *  CreateSystematics(TGraphErrors * gDefault=0, TGraphErrors *gSys1=0, string stattype1="", TGraphErrors * gSys2=0, string stattype2="", string etarange="", string centrange="", string xlabel="", string ylabel="",  string title="" );
void scan(string name ){
  TFile * fin = new TFile(name.data(),"update");
  
  TList * l = (TList *) fin->GetListOfKeys();
  indx = 0;
  bool defaultFound = false;
  bool tightFound = false;
  bool looseFound = false;
  bool wideFound = false;
  bool narrowFound = false;
  while(true) {
    string base = l->At(indx)->GetName();
    if(base=="default") {defaultFound=true; cout<<"default found"<<endl;}
    if(base=="tight")   {tightFound=true; cout<<"tight found"<<endl;}
    if(base=="loose") {looseFound = true; cout<<"loose found"<<endl;}
    if(base=="wide") {wideFound = true; cout<<"wide found"<<endl;}
    if(base=="narrow") {narrowFound = true; cout<<"narrowFound"<<endl;}
    if(l->At(indx)==l->Last()) break;
    ++indx;  
  }
  if(defaultFound){
    TDirectory * defaultDir = (TDirectory *) fin->Get("default");
    indx = 0;
    l = (TList *) defaultDir->GetListOfKeys();
    while(true) {
      string base = l->At(indx)->GetName();
      cout<<base<<endl;
      TDirectory * subdir = (TDirectory *) defaultDir->Get(base.data());
      TList * lsub = (TList *) subdir->GetListOfKeys();
      int subindx = 0;
      while(true){
	string subbase = lsub->At(subindx)->GetName();
	cout<<"    "<<subbase<<endl;
	TDirectory * subsubdir = (TDirectory *) subdir->Get(subbase.data());
	TList * lsubsub = (TList *) subsubdir->GetListOfKeys();
	int subsubindx = 0;
	while(true){
	  string subsubbase = lsubsub->At(subsubindx)->GetName();
	  cout<<"         "<<subsubbase<<endl;	  
	  TDirectory * subsubsubdir = (TDirectory *) subsubdir->Get(subsubbase.data());
	  TList * lsubsubsub = (TList *) subsubsubdir->GetListOfKeys();
	  int subsubsubindx = 0;
	  string ytitle = "";
	  while(true){
	    string subsubsubbase = lsubsubsub->At(subsubsubindx)->GetName();
	    cout<<"            "<<subsubsubbase<<endl;
	    if(subsubsubbase=="h") {
	      ytitle = ((TH1D *) subsubsubdir->Get("h"))->GetYaxis()->GetTitle();
	      ytitle=ytitle.substr(0,ytitle.find("}")+1);
	      cout<<"ytitle: "<<ytitle<<endl;
	    }
	    if(subsubsubbase=="g") {
	      TGraphErrors * g = (TGraphErrors *) subsubsubdir->Get("g");
	      TCanvas * can =  CreateSystematics(g, g,"loose", g, "tight", subbase, subsubbase,"#eta", ytitle, base);
	      subsubsubdir->cd();
	      can->Write();
	    }

	    if(lsubsubsub->At(subsubsubindx)==lsubsubsub->Last()) break;


	    ++subsubsubindx;
	  }
	  if(lsubsub->At(subindx)==lsubsub->Last()) break;
	  ++subsubindx;
	}
	if(lsub->At(subindx)==lsub->Last()) break;
	++subindx;
      }
      if(l->At(indx)==l->Last()) break;
      ++indx;  
    }
  }
}

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

TCanvas *  CreateSystematics(TGraphErrors * gDefault, TGraphErrors *gSys1, string stattype1, TGraphErrors * gSys2, string stattype2, string etarange, string centrange, string xlabel, string ylabel,  string title ){
  cout<<"In Create: "<<etarange<<"\t"<<centrange<<"\t"<<xlabel<<"\t"<<ylabel<<"\t"<<title<<endl;
  string replay=title;
  string gname="";
  string rep2=stattype2;
  string canname = replay+etarange+centrange+gname;
  TCanvas * c = new TCanvas(canname.data(),canname.data(),600,900);
  c->Draw();
  c->Divide(1,3,0.0,0.0);
  c->cd(1);
  string erange = etarange;
  erange.replace(erange.find("_"),1,"< #eta <");
  string crange = centrange;
  crange.replace(centrange.find("_"),1," - ");
  crange=crange+"%";
  gDefault->SetMarkerStyle(25);
  gDefault->SetMarkerColor(kRed);
  gDefault->SetLineColor(kRed);
  double xminDefault,yminDefault,xmaxDefault,ymaxDefault;
  gDefault->ComputeRange(xminDefault,yminDefault,xmaxDefault,ymaxDefault);
  gSys1->SetMarkerStyle(20);
  gSys1->SetMarkerColor(kBlue);
  gSys1->SetLineColor(kBlue);
  double xminSys1,yminSys1,xmaxSys1,ymaxSys1;
  gSys1->ComputeRange(xminSys1,yminSys1,xmaxSys1,ymaxSys1);
  double xminSys2=0;
  double yminSys2=0;
  double xmaxSys2=0;
  double ymaxSys2=0;
  if(stattype2!="") {
    gSys2->SetMarkerStyle(20);
    gSys2->SetMarkerColor(kGreen);
    gSys2->SetLineColor(kGreen);
    gSys2->ComputeRange(xminSys2,yminSys2,xmaxSys2,ymaxSys2);
  }

  double minx = 0;
  double maxx = 10;
  string rng = erange;
  if(gname.find("int")!=std::string::npos) {
    minx = -3;
    maxx = 3; 
    rng = crange;
  } 
   
  TH1D * h = new TH1D("h","h",100,minx,maxx);
  h->SetDirectory(0);
  double setymin = 0;
  if(min(yminSys1,yminSys1)<0) setymin = maxR(min(yminDefault,yminSys1)); 
  double setymax = maxR(max(ymaxDefault,ymaxSys1));
  if(rep2!="") {
    if(min(setymax,yminSys2)<0) setymin = maxR(min(setymin,yminSys2));
    double setymax = maxR(max(setymax,ymaxSys2));
  }
  if(setymin==0) setymin=0.0001*setymax;
  h->SetMinimum(setymin);
  h->SetMaximum(1.3998*setymax);
  h->SetXTitle(xlabel.data());
  h->SetYTitle(ylabel.data());
  h->GetXaxis()->SetLabelFont(43);
  h->GetXaxis()->SetLabelSize(14);
  h->GetXaxis()->SetTitleFont(43);
  h->GetXaxis()->SetTitleSize(20);
  h->GetXaxis()->SetTitleOffset(2.5);
  h->GetXaxis()->CenterTitle(1);
  h->GetYaxis()->SetLabelFont(43);
  h->GetYaxis()->SetLabelSize(14);
  h->GetYaxis()->SetTitleFont(43);
  h->GetYaxis()->SetTitleSize(20);
  h->GetYaxis()->SetTitleOffset(2.8);
  h->GetYaxis()->CenterTitle(1);
  h->Draw();
  TLatex * lcalc = new TLatex(0.1*(maxx-minx)+minx,1.24*setymax,replay.data());
  lcalc->SetTextFont(43);
  lcalc->SetTextSize(26);
  lcalc->Draw(); 
  TLatex * lr = new TLatex(0.1*(maxx-minx)+minx, 1.1*setymax, crange.data());
  lr->SetTextFont(43);
  lr->SetTextSize(26);
  lr->Draw();
  TLatex * lr2 = new TLatex(0.1*(maxx-minx)+minx, 0.96*setymax, erange.data());
  lr2->SetTextFont(43);
  lr2->SetTextSize(26);
  lr2->Draw();
  gSys1->Draw("p");
  gDefault->Draw("p");
  TLegend * leg = new TLegend(0.75,0.75,0.89,0.95);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(43);
  leg->SetTextSize(24);
  leg->AddEntry(gSys1,stattype1.data(),"lp");
  if(rep2!="") {
    gSys2->Draw("p");
    leg->AddEntry(gSys2,stattype2.data(),"lp");
  }
  leg->AddEntry(gDefault,"default","lp");
  leg->Draw();
  TGraphErrors * gRatio = (TGraphErrors *) gSys1->Clone("Ratio");
  for(int i = 0; i<gSys1->GetN(); i++){ 
    if(gDefault->GetY()[i]!=0) {
      double y1 = gSys1->GetY()[i];
      double ey1 = gSys1->GetEY()[i];
      double y2 = gDefault->GetY()[i];
      double ey2 = gDefault->GetEY()[i];
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
  TGraphErrors * gRatio2 = 0;
  gRatio2 = (TGraphErrors *) gSys2->Clone("Ratio2");
  if(stattype2!="") {
    for(int i = 0; i<gSys2->GetN(); i++){ 
      if(gDefault->GetY()[i]!=0) {
	double y1 = gSys2->GetY()[i];
	double ey1 = gSys2->GetEY()[i];
	double y2 = gDefault->GetY()[i];
	double ey2 = gDefault->GetEY()[i];
	gRatio2->GetY()[i]=y1/y2; 
	double try1 = pow(ey1/y1,2)+pow(ey2/y2,2)-2*pow(ey1,2)/y1/y2;
	double try2 = pow(ey1/y1,2)+pow(ey2/y2,2)-2*pow(ey2,2)/y1/y2;
	double err = 0;
	if(try1>0) {
	  err = sqrt(try1);
	} else if(try2>0) {
	  err = sqrt(try2);
	} else {
	  cout<<"unable to calculate sys error"<<endl;
	  err = ey1*gRatio2->GetY()[i]/y1;
	}
	gRatio2->GetEY()[i] = err;
      }
    }
  }
  c->cd(2);
  TH1D * hr = new TH1D("hr","hr",100,minx,maxx);
  hr->SetDirectory(0);
  hr->SetMinimum(0.901);
  hr->SetMaximum(0.99*1.1);
  hr->SetXTitle(xlabel.data());
  hr->SetYTitle(Form("%s/%s{default}",ylabel.data(),ylabel.data()));
  hr->GetXaxis()->SetLabelFont(43);
  hr->GetXaxis()->SetLabelSize(14);
  hr->GetXaxis()->SetTitleFont(43);
  hr->GetXaxis()->SetTitleSize(20);
  hr->GetXaxis()->SetTitleOffset(2.5);
  hr->GetXaxis()->CenterTitle(1);
  hr->GetYaxis()->SetLabelFont(43);
  hr->GetYaxis()->SetLabelSize(14);
  hr->GetYaxis()->SetTitleFont(43);
  hr->GetYaxis()->SetTitleSize(20);
  hr->GetYaxis()->SetTitleOffset(2.8);
  hr->GetYaxis()->CenterTitle(1);
  gPad->SetGrid(1,1);
  hr->Draw();
  TLine * hrline = new TLine(minx,1.,maxx,1.);
  hrline->SetLineColor(kBlack);
  hrline->SetLineWidth(1);
  hrline->Draw();
  gRatio->Draw("p");
  if(rep2!="" ) gRatio2->Draw("p");

  TGraphErrors * gDiff = (TGraphErrors *) gSys1->Clone("Difference");
  for(int i = 0; i<gSys1->GetN(); i++){ 
    gDiff->GetY()[i]=1000.*(gSys1->GetY()[i]-gDefault->GetY()[i]); 
    double eA = gSys1->GetEY()[i];
    double eB = gDefault->GetEY()[i];
    double e = sqrt(fabs(pow(eA,2)-pow(eB,2)));
    gDiff->GetEY()[i] = 1000.*e;
  }
  gDiff->ComputeRange(xminSys1,yminSys1,xmaxSys1,ymaxSys1);
  TGraphErrors * gDiff2;
  if(rep2!="") {
    gDiff2 = (TGraphErrors *) gSys2->Clone("Difference2");
    for(int i = 0; i<gSys2->GetN(); i++){ 
      gDiff2->GetY()[i]=1000.*(gSys2->GetY()[i]-gDefault->GetY()[i]); 
      double eA = gSys2->GetEY()[i];
      double eB = gDefault->GetEY()[i];
      double e = sqrt(fabs(pow(eA,2)-pow(eB,2)));
      gDiff2->GetEY()[i] = 1000.*e;
    }
    gDiff->ComputeRange(xminSys2,yminSys2,xmaxSys2,ymaxSys2);
  }
  c->cd(3);
  TH1D * hd = new TH1D("hd","hd",100,minx,maxx);
  hd->SetDirectory(0);
  setymin = 0;
  if(yminSys1<0) setymin = maxR(yminSys1); 
  if(rep2!="" && yminSys2<0) setymin = maxR(max(setymin,yminSys2));
  setymax = maxR(ymaxSys1);
  if(rep2!="") setymax = maxR(ymaxSys2);
  hd->SetMinimum(setymin);
  hd->SetMaximum(setymax+0.1*(setymax-setymin));
  hd->SetXTitle(xlabel.data());
  hd->SetYTitle(Form("%s - %s{default} (#times 1000)",ylabel.data(),ylabel.data()));
  hd->GetXaxis()->SetLabelFont(43);
  hd->GetXaxis()->SetLabelSize(14);
  hd->GetXaxis()->SetTitleFont(43);
  hd->GetXaxis()->SetTitleSize(20);
  hd->GetXaxis()->SetTitleOffset(2.5);
  hd->GetXaxis()->CenterTitle(1);
  hd->GetYaxis()->SetLabelFont(43);
  hd->GetYaxis()->SetLabelSize(14);
  hd->GetYaxis()->SetTitleFont(43);
  hd->GetYaxis()->SetTitleSize(20);
  hd->GetYaxis()->SetTitleOffset(2.8);
  hd->GetYaxis()->CenterTitle(1);
  gPad->SetGrid(1,1);
  hd->Draw();
  gDiff->Draw("p");
  if(stattype2!="") gDiff2->Draw("p");
  if(gname.find("int")!=std::string::npos) {
    c->Print(Form("systematics/%s/%s_%s_%s_%s_%s.pdf",replay.data(),replay.data(),centrange.data(),gname.data(),stattype1.data(),stattype2.data()),"pdf");
  } else {
    c->Print(Form("systematics/%s/%s_%s_%s_%s_%s.pdf",replay.data(),replay.data(),etarange.data(),gname.data(),stattype1.data(),stattype2.data()),"pdf");
  } 
  return c;
}
