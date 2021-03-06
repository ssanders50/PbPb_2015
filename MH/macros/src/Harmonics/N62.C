TGraphErrors * N62(int replay, int bin, double eMin, double eMax, double & ymin, double & ymax, TGraphErrors * &g,TGraphErrors * &gA, TGraphErrors * &gB, TGraphErrors * &gSpec,TGraphErrors * &gint, TGraphErrors *& gintA, TGraphErrors *& gintB, double & vint, double & vinte, double & vintA, double & vintAe, double & vintB, double & vintBe){
  fin = new TFile(rootFile.data(),"r");
  Decor = false;
  TGraphErrors * gtmp;
  //
  // Start with eta distribution
  //
  for(int i = 0; i<12; i++) {
    double EtaMin = -2.4 + 0.4*i;
    double EtaMax = EtaMin+0.4;
    if(fabs(EtaMin)<0.001) EtaMin = 0.;
    if(fabs(EtaMax)<0.001) EtaMax = 0.;
    gtmp = GetVNPt(replay,bin,-1,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
    fin->Close();
    fin = new TFile(rootFile.data(),"r");
    gint->GetY()[i] = vint;
    gint->GetEY()[i] = vinte;
    gintA->GetY()[i]=vintA;
    gintA->GetEY()[i]=vintAe;
    gintB->GetY()[i]=vintB;
    gintB->GetEY()[i]=vintBe;
  }
  gint->SetName("gint");
  gintA->SetName("gintA");
  gintB->SetName("gintB");
  //
  // Now do requested calculation
  //
  g = GetVNPt(replay,bin,-1,eMin,eMax,gA, gB, gSpec, vint, vinte,  vintA, vintAe, vintB, vintBe, false);
  ymin = setYmin(g,gA,gB);
  ymax = setYmax(g,gA,gB);
  fin->Close();
  outint = fopen(soutint.data(),"a+");
  fprintf(outint,"%d\t%d\t%15.10f\t%15.10f\n",cmin[bin],cmax[bin],vint,vinte);
  fclose(outint);
  g->SetName("g");
  gA->SetName("gA");
  gB->SetName("gB");
  return g;
}
