TGraphErrors * ErrorPlot(string name, bool pt, bool ratio,  int order, TGraphErrors * g1, TGraphErrors * g2,TGraph *& gshade, TGraph * &gmin, TGraph * &gmax, int marker, int color) {
  int n = g1->GetN();
  double minx = 0;
  double maxx = 10;

  if(!pt) {
    minx = -3;
    maxx = 3; 
  } 
  double x[100];
  double y[100];
  double ey[100];
  double ymin[100];
  double ymax[100];
  int npts = 0;
  double xerr[100],yerr[100];
  int nerr = 0;
  for(int i = 0; i<n; i++) {
    bool skip = false;
    double y1 = g1->GetY()[i];
    double ey1 = g1->GetEY()[i];
    double y2 = g2->GetY()[i];
    double ey2 = g2->GetEY()[i];
    double val,err;
    if(ratio ) {
      if(y2!=0) {
	val = y1/y2;
      } else {
	val = 0;
	skip = true;
      }
      err = pow(ey1/y1,2)+pow(ey2/y2,2)-2*pow(min(ey1,ey2),2)/y1/y2;
      if(err<=0) err=pow(ey1/y1,2);
      err = sqrt(err)*val;
    } else {
      val = y1-y2;
      err = sqrt(fabs(pow(ey1,2)-pow(ey2,2)));
    }
    if(!skip) {
      x[npts] = g1->GetX()[i];
      y[npts] = val;
      ey[npts] = err;
      ++npts;
    }
  }
  TGraphErrors * g = new TGraphErrors(npts,x,y,0,ey);
  g->SetMarkerStyle(marker);
  g->SetMarkerColor(color);
  g->SetName(name.data());
  g->SetTitle(name.data());
  string fits[3]={"pol0","pol1","pol2"};
  TF1 * f0 = 0;
  TF1 * f1 = 0; 
  TF1 * f2 = 0;
  double f0min;
  double f0max;
  double f1min;
  double f1max;
  double f2min;
  double f2max;
  if(pt) {
    f0min = 0.3;
    f0max = 0.81;
    f1min = 0.8;
    f1max = 3.1;
    f2min = 3.0;
    f2max = 8.0;
  } else {
    f0min = -2.4;
    f0max = -1.2;
    f1min = -1.6;
    f1max = 1.6;
    f2min = 1.2;
    f2max = 2.4;
  }
  f0 = new TF1("f0",fits[order].data(),f0min,f0max);
  f1 = new TF1("f1",fits[order].data(),f1min,f1max);
  f2 = new TF1("f2",fits[order].data(),f2min,f2max);
  g->Fit(f0,"qR");
  g->Fit(f1,"qR+");
  g->Fit(f2,"qR+");

  double xs[100],ymins[100],ymaxs[100];
  for(int i = 0; i<n; i++) {
    double xv = g1->GetX()[i];
    xs[i] = xv;
    double ymin,ymax;
    if(xv<f1min) {
      ymin = f0->Eval(xv)-f0->GetParError(0) - 1;
      ymax = f0->Eval(xv)+f0->GetParError(0) - 1;
    } else if ( xv < f0max) {
      ymin = (f0->Eval(xv) + f1->Eval(xv) - f0->GetParError(0) - f1->GetParError(0) - 2)/2.;
      ymax = (f0->Eval(xv) + f1->Eval(xv) + f0->GetParError(0) + f1->GetParError(0) - 2)/2.;
    } else if ( xv < f2min) {
      ymin = f1->Eval(xv)-f1->GetParError(0) - 1;
      ymax = f1->Eval(xv)+f1->GetParError(0) - 1;
    } else if ( xv < f1max) { 
      ymin = (f1->Eval(xv) + f2->Eval(xv) - f1->GetParError(0) - f2->GetParError(0) - 2)/2.;
      ymax = (f1->Eval(xv) + f2->Eval(xv) + f1->GetParError(0) + f2->GetParError(0) - 2)/2.;
   } else if ( xv >= f1max) {
      ymin = f2->Eval(xv)-f1->GetParError(0) - 1;
      ymax = f2->Eval(xv)+f1->GetParError(0) - 1;
    }
    ymin=fabs(ymin);
    ymax = fabs(ymax);
    if(ratio) {
      ymin*=100.;
      ymax*=100.;
    }
    ymins[i] = min(ymin,ymax);
    ymaxs[i] = max(ymin,ymax);
  }
  gmin = new TGraph(n,xs,ymins);
  gmax = new TGraph(n,xs,ymaxs);
  gshade = new TGraph(2*n);
  for(int i = 0; i<n; i++) {
    gshade->SetPoint(i,xs[i],ymaxs[i]);
    gshade->SetPoint(n+i,xs[n-i-1],ymins[n-i-1]); 
  }
  gshade->SetFillStyle(3013);
  gshade->SetFillColorAlpha(color,0.5);
  gshade->Draw("f");
  gmin->SetLineColorAlpha(color,0.5);
  gmax->SetLineColorAlpha(color,0.5);
  string gshadeN = name+"_gshade";
  string gminN = name+"_gmin";
  string gmaxN = name+"_gmax";
  gshade->SetName(gshadeN.data());
  gshade->SetTitle(gshadeN.data());
  gmin->SetName(gminN.data());
  gmin->SetTitle(gminN.data());
  gmax->SetName(gmaxN.data());
  gmax->SetTitle(gmaxN.data());
  return g;
}

void RatioPlots(){
  double x[10] =  {0.3,0.4,0.5,0.7,1.0,1.5,2.0,3.0,5.0,10.0};
  double y1[10] = { 1,2,3,4,5,6,7,8,9,10};
  double y2[10]=  { 1,1,2,5,4,7,6,9,10,8};
  double ey1[10];
  double ey2[10];
  for(int i = 0; i<10; i++) {
    ey1[i] = 0.1*y1[i];
    ey2[i] = 0.1*y2[i];
  }
  TGraphErrors * g1 = new TGraphErrors(10,x,y1,0,ey1);
  TGraphErrors * g2 = new TGraphErrors(10,x,y2,0,ey2);
  TGraph * gshade = 0;
  TGraph * gmin = 0;
  TGraph * gmax = 0;
  TGraphErrors * g = ErrorPlot("gtest",true,true,1,g1,g2,gshade,gmin,gmax,20,kBlue);
  cout<<"gmin: "<<gmin<<endl;
  cout<<"gmax: "<<gmax<<endl;
  cout<<"gshade: "<<gshade<<endl;

  TCanvas * c = new TCanvas("c","c",1000,800);
  c->Divide(2);
  c->cd(1);
  TH1D * h = new TH1D("h","h",100,0,12);
  h->SetMinimum(0);
  h->SetMaximum(12);
  h->Draw();
  g->Draw("p");
  TH1D * hr = new TH1D("hr","hr",100,0,12);
  hr->SetMinimum(0);
  hr->SetMaximum(80);
  c->cd(2);
  hr->Draw();
  gmin->Draw("l");
  gmax->Draw("l");
  gshade->Draw("f");
}
