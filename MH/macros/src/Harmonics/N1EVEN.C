TGraphErrors * N1EVEN(int replay, int bin, double eMin, double eMax, double & ymin, double & ymax, TGraphErrors * &g,TGraphErrors * &gA, TGraphErrors * &gB, TGraphErrors * &gSpec, TGraphErrors * &gint, TGraphErrors *& gintA, TGraphErrors *& gintB ){
  fin = new TFile(rootFile.data(),"r");
  double vint = 0;
  double vinte = 0;
  double vintA = 0;
  double vintAe = 0;
  double vintB = 0;
  double vintBe = 0;
  int epindx = -1;
  TGraphErrors * gtmp;
  TGraphErrors * g2;
  TGraphErrors * gA2;
  TGraphErrors * gB2;
  TGraphErrors * gSpec2;
  int pRef2 = N1MCp18SUB2;
  int pRef3 = N1MCp18SUB3;
  int mRef2 = N1MCm18SUB2;
  int mRef3 = N1MCm18SUB3;
  int ioff = 2;

  // int pRef2 = N1MCp22SUB2;
  // int pRef3 = N1MCp22SUB3;
  // int mRef2 = N1MCm22SUB2;
  // int mRef3 = N1MCm22SUB3;
  // int ioff = 1;

  Decor = false;
  //
  // Start with eta distribution
  //
  if(replay==N1EVENSUB2 || replay==N1EVENSUB3) {
    for(int i = 0+ioff; i<12-ioff; i++) {
      double EtaMin = -2.4 + 0.4*i;
      double EtaMax = EtaMin+0.4;
      if(fabs(EtaMin)<0.001) EtaMin = 0.;
      if(fabs(EtaMax)<0.001) EtaMax = 0.;
      if(i<6) {
	int rep = pRef2;
	if(replay==N1EVENSUB3) rep = pRef3;
	gtmp = GetVNPt(rep,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
	gint->GetY()[i-ioff] = vintA;
	gint->GetEY()[i-ioff] = vintAe;
      } else {
	int rep = mRef2;
	if(replay==N1EVENSUB3) rep = mRef3;
	gtmp = GetVNPt(rep,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
	gint->GetY()[i-ioff] = vintA;
	gint->GetEY()[i-ioff] = vintAe;
      }
      gint->GetX()[i-ioff] = gint->GetX()[i];
      gintA->GetX()[i-ioff] = gintA->GetX()[i];
      gintB->GetX()[i-ioff] = gintB->GetX()[i];
      gintA->GetY()[i-ioff]=vintA;
      gintA->GetEY()[i-ioff]=vintAe;
      gintB->GetY()[i-ioff]=vintB;
      gintB->GetEY()[i-ioff]=vintBe;
    }
    gint->Set(12-2*ioff);
    gintA->Set(12-2*ioff);
    gintB->Set(12-2*ioff);
  } else {
    for(int i = 0; i<12; i++) {
      double EtaMin = -2.4 + 0.4*i;
      double EtaMax = EtaMin+0.4;
      if(fabs(EtaMin)<0.001) EtaMin = 0.;
      if(fabs(EtaMax)<0.001) EtaMax = 0.;
      gtmp = GetVNPt(replay,bin,epindx,EtaMin,EtaMax,gtmp, gtmp, gtmp, vint, vinte, vintA, vintAe, vintB, vintBe, false);
      gint->GetY()[i] = vint;
      gint->GetEY()[i] = vinte;
      gintA->GetY()[i]=vintA;
      gintA->GetEY()[i]=vintAe;
      gintB->GetY()[i]=vintB;
      gintB->GetEY()[i]=vintBe;
    }
  }
  //
  // Now do requested calculation
  //
  if(replay != N1EVENSUB3  && replay !=N1EVENSUB2){
    g = GetVNPt(replay,bin,epindx,eMin,eMax,gA, gB, gSpec, vint, vinte, vintA,vintAe,vintB,vintBe,false);
    for(int i = 0; i<g->GetN(); i++) {
      g->GetY()[i] = gA->GetY()[i];
      g->GetEY()[i] = gA->GetEY()[i];
    }
    SetToA = true;
    ymin = setYmin(g,gA,gB);
    ymax = setYmax(g,gA,gB);
    fin->Close();
    outint = fopen(soutint.data(),"a+");
    fprintf(outint,"%d\t%d\t%15.10f\t%15.10f\n",cmin[bin],cmax[bin],vint,vinte);
    fclose(outint);
  } else {
    int settype = 0;
    if(eMin*eMax>0) {
      if(eMin < 0 ) {
	settype = pRef2;
	if(replay==N1EVENSUB3) settype=pRef3;
      } else {
	settype = mRef2;
	if(replay==N1EVENSUB3) settype=mRef3;
      }
      g = GetVNPt(settype,bin,epindx,eMin,eMax,gA, gB, gSpec, vint, vinte,vintA,vintAe,vintB,vintBe, false);
    } else {
      settype = pRef2;
      if(replay==N1EVENSUB3) settype=pRef3;
      g = GetVNPt(settype,bin,epindx,eMin,0.,gA, gB, gSpec, vint, vinte,vintA,vintAe,vintB,vintBe, false);
      settype = mRef2;
      if(replay==N1EVENSUB3) settype=mRef3;
      g2 = GetVNPt(settype,bin,epindx,0.,eMax,gA2, gB2, gSpec, vint, vinte,vintA,vintAe,vintB,vintBe, false);
      for(int i = 0; i<g->GetN(); i++) {
	g->GetY()[i] = (g->GetY()[i]+g2->GetY()[i])/2.;
	g->GetEY()[i] = (g->GetEY()[i]+g2->GetEY()[i])/2.;
	gA->GetY()[i] = (gA->GetY()[i]+gA2->GetY()[i])/2.;
	gA->GetEY()[i] = (gA->GetEY()[i]+gA2->GetEY()[i])/2.;
	gB->GetY()[i] = (gB->GetY()[i]+gB2->GetY()[i])/2.;
	gB->GetEY()[i] = (gB->GetEY()[i]+gB2->GetEY()[i])/2.;
      }
    }
  }
      ymin = setYmin(g,gA,gB);
      ymax = setYmax(g,gA,gB);

  return g;
}
