TFile * tf = new TFile("ampt.root");
TBrowser br;
void centcalib(){
  TH1D * ref = (TH1D *) tf->Get("evtPlaneCalibTree/b");
  ref->SetDirectory(0);
  ref->Draw();
  double tot = ref->Integral(1,ref->GetNbinsX());
  cout<<"tot: "<<tot<<endl;
  double del = tot/200;
  double cent = 0;
  int bin = 0;
  double sum = 0;
  int x[210];
  int y[210];
  x[0] = 0;
  y[0] = 0;
  for(int i = 1; i<=ref->GetNbinsX(); i++){
    double lim = (bin+1)*del;
    sum+=ref->GetBinContent(i);
    if(sum>=lim) {
      cout<<bin<<"\t"<<i<<"\t"<<sum<<endl;
      ++bin;
      x[bin] = i;
      y[bin] = bin;
    }


  }
  //TGraph * g = new TGraph(200,x,y);
  //for(int i = 0; i<200; i++) {
  //  cout<<"bin: "<<i<<"\t"<<x[i]<<"\t"<<y[i]<<endl;
  // }
  //TCanvas * c = new TCanvas("c","c",800,650);
  //TH1D * h = new TH1D("h","h",10000,0,10000);
  //h->SetMaximum(200);
  //h->Draw();
  //g->SetMarkerStyle(20);
  //g->Draw("p");
  //TF1 * f = new TF1("fit","pol9",0,1852);
  //g->Fit(f);
  //for(int i = 0; i<10; i++) cout<<f->GetParameter(i)<<",";
  // cout<<endl;
  FILE * fout = fopen("bToCent.C","w");
  fprintf(fout,"int bToCent(int b){\n");
  fprintf(fout,"int bounds[200]={\n");
  for(int i = 0; i<200; i++) {
    fprintf(fout,"%d",x[i]);
    if(i<199) fprintf(fout,",");
    if(fmod(i,10)==0&&i>0) fprintf(fout,"\n");
  }
  fprintf(fout,"};\n");
  fprintf(fout,"for(int i=199; i>0; i--) {\n");
  fprintf(fout,"if(b<bounds[i]) continue;\n");
  fprintf(fout,"return i;\n");
  fprintf(fout,"}\n");
  fprintf(fout,"return 0;\n");
  fprintf(fout,"}\n");
}
