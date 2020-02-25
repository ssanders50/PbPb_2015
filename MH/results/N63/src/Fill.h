void Fill_N2SUB3(int bin, TH2D *qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double Ax, double Ay, double Bx, double By, double Cx, double Cy, double wA, double wB, double wC){
  qA[bin][0]->Add(qxtrk_,Ax);
  qA[bin][0]->Add(qytrk_,Ay);
  qB[bin][0]->Add(qxtrk_,Bx);
  qB[bin][0]->Add(qytrk_,By);
  wnA[bin][0]->Add(qcnt_,wA);
  wnB[bin][0]->Add(qcnt_,wB);
  qBA[bin][0]->Fill(0.,Bx*Ax + By*Ay);
  qCA[bin][0]->Fill(0.,Cx*Ax + Cy*Ay);
  qCB[bin][0]->Fill(0.,Cx*Bx + Cy*By);
  qBAcnt[bin][0]->Fill(0.,wB*wA);
  qCAcnt[bin][0]->Fill(0.,wC*wA);
  qCBcnt[bin][0]->Fill(0.,wC*wB);
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_,Ax);
  qA[bin][j]->Add(qytrk_,Ay);
  qB[bin][j]->Add(qxtrk_,Bx);
  qB[bin][j]->Add(qytrk_,By);
  wnA[bin][j]->Add(qcnt_,wA);
  wnB[bin][j]->Add(qcnt_,wB);
  qBA[bin][j]->Fill(0.,Bx*Ax + By*Ay);
  qCA[bin][j]->Fill(0.,Cx*Ax + Cy*Ay);
  qCB[bin][j]->Fill(0.,Cx*Bx + Cy*By);
  qBAcnt[bin][j]->Fill(0.,wB*wA);
  qCAcnt[bin][j]->Fill(0.,wC*wA);
  qCBcnt[bin][j]->Fill(0.,wC*wB);
  
}

void Fill_N42SUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double Ax, double Ay, double Bx, double By, double Cx, double Cy, double wA, double wB, double wC){
  qA[bin][0]->Add(qxtrk_,pow(Ax,2)-pow(Ay,2));
  qA[bin][0]->Add(qytrk_,2*Ax*Ay);
  qB[bin][0]->Add(qxtrk_,pow(Bx,2)-pow(By,2));
  qB[bin][0]->Add(qytrk_,2*Bx*By);
  wnA[bin][0]->Add(qcnt_,pow(wA,2));
  wnB[bin][0]->Add(qcnt_,pow(wB,2));
  qBA[bin][0]->Fill(0.,pow(Ax,2)*(pow(Bx,2)-pow(By,2)) + pow(Ay,2)*(pow(By,2)-pow(Bx,2))+4*Ax*Ay*Bx*By);
  qCA[bin][0]->Fill(0.,pow(Ax,2)*(pow(Cx,2)-pow(Cy,2)) + pow(Ay,2)*(pow(Cy,2)-pow(Cx,2))+4*Ax*Ay*Cx*Cy);
  qCB[bin][0]->Fill(0.,pow(Bx,2)*(pow(Cx,2)-pow(Cy,2)) + pow(By,2)*(pow(Cy,2)-pow(Cx,2))+4*Bx*By*Cx*Cy);
  qBAcnt[bin][0]->Fill(0.,pow(wA*wB,2));
  qCAcnt[bin][0]->Fill(0.,pow(wA*wC,2));
  qCBcnt[bin][0]->Fill(0.,pow(wB*wC,2));
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_,pow(Ax,2)-pow(Ay,2));
  qA[bin][j]->Add(qytrk_,2*Ax*Ay);
  qB[bin][j]->Add(qxtrk_,pow(Bx,2)-pow(By,2));
  qB[bin][j]->Add(qytrk_,2*Bx*By);
  wnA[bin][j]->Add(qcnt_,pow(wA,2));
  wnB[bin][j]->Add(qcnt_,pow(wB,2));
  qBA[bin][j]->Fill(0.,pow(Ax,2)*(pow(Bx,2)-pow(By,2)) + pow(Ay,2)*(pow(By,2)-pow(Bx,2))+4*Ax*Ay*Bx*By);
  qCA[bin][j]->Fill(0.,pow(Ax,2)*(pow(Cx,2)-pow(Cy,2)) + pow(Ay,2)*(pow(Cy,2)-pow(Cx,2))+4*Ax*Ay*Cx*Cy);
  qCB[bin][j]->Fill(0.,pow(Bx,2)*(pow(Cx,2)-pow(Cy,2)) + pow(By,2)*(pow(Cy,2)-pow(Cx,2))+4*Bx*By*Cx*Cy);
  qBAcnt[bin][j]->Fill(0.,pow(wA*wB,2));
  qCAcnt[bin][j]->Fill(0.,pow(wA*wC,2));
  qCBcnt[bin][j]->Fill(0.,pow(wB*wC,2));
}

void Fill_N523SUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
  double a2x = qx[HFp2];
  double a2y = qy[HFp2];
  double wa2 = sumw[HFp2];
  double a3x = qx[HFp3];
  double a3y = qy[HFp3];
  double wa3 = sumw[HFp3];

  double b2x = qx[HFm2];
  double b2y = qy[HFm2];
  double wb2 = sumw[HFm2];
  double b3x = qx[HFm3];
  double b3y = qy[HFm3];
  double wb3 = sumw[HFm3];

  double c2x = qx[trackmid2];
  double c2y = qy[trackmid2];
  double wc2 = sumw[trackmid2];
  double c3x = qx[trackmid3];
  double c3y = qy[trackmid3];
  double wc3 = sumw[trackmid3];

  qA[bin][0]->Add(qxtrk_,a2x*a3x-a2x*a3y);
  qA[bin][0]->Add(qytrk_,a2y*a3x+a2x*a3y);
  qB[bin][0]->Add(qxtrk_,b2x*b3x-b2x*b3y);
  qB[bin][0]->Add(qytrk_,b2y*b3x+b2x*b3y);
  wnA[bin][0]->Add(qcnt_,wa2*wa3);
  wnB[bin][0]->Add(qcnt_,wb2*wb3);
  qBA[bin][0]->Fill(0.,a2x*a3x*b2x*b3x - a2y*a3y*b2x*b3x + a2y*a3x*b2y*b3x + a2x*a3y*b2y*b3x + a2y*a3x*b2x*b3y + a2x*a3y*b2x*b3y - a2x*a3x*b2y*b3y + a2y*a3y*b2y*b3y);
  qCA[bin][0]->Fill(0.,a2x*a3x*c2x*c3x - a2y*a3y*c2x*c3x + a2y*a3x*c2y*c3x + a2x*a3y*c2y*c3x + a2y*a3x*c2x*c3y + a2x*a3y*c2x*c3y - a2x*a3x*c2y*c3y + a2y*a3y*c2y*c3y);
  qCB[bin][0]->Fill(0.,b2x*b3x*c2x*c3x - b2y*b3y*c2x*c3x + b2y*b3x*c2y*c3x + b2x*b3y*c2y*c3x + b2y*b3x*c2x*c3y + b2x*b3y*c2x*c3y - b2x*b3x*c2y*c3y + b2y*b3y*c2y*c3y);
  qBAcnt[bin][0]->Fill(0.,wb2*wb3*wa2*wa3);
  qCAcnt[bin][0]->Fill(0.,wc2*wc3*wa2*wa3);
  qCBcnt[bin][0]->Fill(0.,wc2*wc3*wb2*wb3);
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_,a2x*a3x-a2x*a3y);
  qA[bin][j]->Add(qytrk_,a2y*a3x+a2x*a3y);
  qB[bin][j]->Add(qxtrk_,b2x*b3x-b2x*b3y);
  qB[bin][j]->Add(qytrk_,b2y*b3x+b2x*b3y);
  wnA[bin][j]->Add(qcnt_,wa2*wa3);
  wnB[bin][j]->Add(qcnt_,wb2*wb3);
  qBA[bin][j]->Fill(0.,a2x*a3x*b2x*b3x - a2y*a3y*b2x*b3x + a2y*a3x*b2y*b3x + a2x*a3y*b2y*b3x + a2y*a3x*b2x*b3y + a2x*a3y*b2x*b3y - a2x*a3x*b2y*b3y + a2y*a3y*b2y*b3y);
  qCA[bin][j]->Fill(0.,a2x*a3x*c2x*c3x - a2y*a3y*c2x*c3x + a2y*a3x*c2y*c3x + a2x*a3y*c2y*c3x + a2y*a3x*c2x*c3y + a2x*a3y*c2x*c3y - a2x*a3x*c2y*c3y + a2y*a3y*c2y*c3y);
  qCB[bin][j]->Fill(0.,b2x*b3x*c2x*c3x - b2y*b3y*c2x*c3x + b2y*b3x*c2y*c3x + b2x*b3y*c2y*c3x + b2y*b3x*c2x*c3y + b2x*b3y*c2x*c3y - b2x*b3x*c2y*c3y + b2y*b3y*c2y*c3y);
  qBAcnt[bin][j]->Fill(0.,wb2*wb3*wa2*wa3);
  qCAcnt[bin][j]->Fill(0.,wc2*wc3*wa2*wa3);
  qCBcnt[bin][j]->Fill(0.,wc2*wc3*wb2*wb3);
}
void Fill_N523ASUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
  double a2x = qx[HFp2];
  double a2y = qy[HFp2];
  double wa2 = sumw[HFp2];
  double a3x = qx[HFm3];
  double a3y = qy[HFm3];
  double wa3 = sumw[HFm3];

  double b2x = qx[HFm2];
  double b2y = qy[HFm2];
  double wb2 = sumw[HFm2];
  double b3x = qx[HFp3];
  double b3y = qy[HFp3];
  double wb3 = sumw[HFp3];

  double c2x = qx[trackmid2];
  double c2y = qy[trackmid2];
  double wc2 = sumw[trackmid2];
  double c3x = qx[trackmid3];
  double c3y = qy[trackmid3];
  double wc3 = sumw[trackmid3];

  qA[bin][0]->Add(qxtrk_,a2x*a3x-a2x*a3y);
  qA[bin][0]->Add(qytrk_,a2y*a3x+a2x*a3y);
  qB[bin][0]->Add(qxtrk_,b2x*b3x-b2x*b3y);
  qB[bin][0]->Add(qytrk_,b2y*b3x+b2x*b3y);
  wnA[bin][0]->Add(qcnt_,wa2*wa3);
  wnB[bin][0]->Add(qcnt_,wb2*wb3);
  qBA[bin][0]->Fill(0.,a2x*a3x*b2x*b3x - a2y*a3y*b2x*b3x + a2y*a3x*b2y*b3x + a2x*a3y*b2y*b3x + a2y*a3x*b2x*b3y + a2x*a3y*b2x*b3y - a2x*a3x*b2y*b3y + a2y*a3y*b2y*b3y);
  qCA[bin][0]->Fill(0.,a2x*a3x*c2x*c3x - a2y*a3y*c2x*c3x + a2y*a3x*c2y*c3x + a2x*a3y*c2y*c3x + a2y*a3x*c2x*c3y + a2x*a3y*c2x*c3y - a2x*a3x*c2y*c3y + a2y*a3y*c2y*c3y);
  qCB[bin][0]->Fill(0.,b2x*b3x*c2x*c3x - b2y*b3y*c2x*c3x + b2y*b3x*c2y*c3x + b2x*b3y*c2y*c3x + b2y*b3x*c2x*c3y + b2x*b3y*c2x*c3y - b2x*b3x*c2y*c3y + b2y*b3y*c2y*c3y);
  qBAcnt[bin][0]->Fill(0.,wb2*wb3*wa2*wa3);
  qCAcnt[bin][0]->Fill(0.,wc2*wc3*wa2*wa3);
  qCBcnt[bin][0]->Fill(0.,wc2*wc3*wb2*wb3);
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_,a2x*a3x-a2x*a3y);
  qA[bin][j]->Add(qytrk_,a2y*a3x+a2x*a3y);
  qB[bin][j]->Add(qxtrk_,b2x*b3x-b2x*b3y);
  qB[bin][j]->Add(qytrk_,b2y*b3x+b2x*b3y);
  wnA[bin][j]->Add(qcnt_,wa2*wa3);
  wnB[bin][j]->Add(qcnt_,wb2*wb3);
  qBA[bin][j]->Fill(0.,a2x*a3x*b2x*b3x - a2y*a3y*b2x*b3x + a2y*a3x*b2y*b3x + a2x*a3y*b2y*b3x + a2y*a3x*b2x*b3y + a2x*a3y*b2x*b3y - a2x*a3x*b2y*b3y + a2y*a3y*b2y*b3y);
  qCA[bin][j]->Fill(0.,a2x*a3x*c2x*c3x - a2y*a3y*c2x*c3x + a2y*a3x*c2y*c3x + a2x*a3y*c2y*c3x + a2y*a3x*c2x*c3y + a2x*a3y*c2x*c3y - a2x*a3x*c2y*c3y + a2y*a3y*c2y*c3y);
  qCB[bin][j]->Fill(0.,b2x*b3x*c2x*c3x - b2y*b3y*c2x*c3x + b2y*b3x*c2y*c3x + b2x*b3y*c2y*c3x + b2y*b3x*c2x*c3y + b2x*b3y*c2x*c3y - b2x*b3x*c2y*c3y + b2y*b3y*c2y*c3y);
  qBAcnt[bin][j]->Fill(0.,wb2*wb3*wa2*wa3);
  qCAcnt[bin][j]->Fill(0.,wc2*wc3*wa2*wa3);
  qCBcnt[bin][j]->Fill(0.,wc2*wc3*wb2*wb3);
}

void Fill_N63SUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
  double ax = qx[HFp3];
  double ay = qy[HFp3];
  double wa = sumw[HFp3];

  double bx = qx[HFm3];
  double by = qy[HFm3];
  double wb = sumw[HFm3];

  double cx = qx[trackmid3];
  double cy = qy[trackmid3];
  double wc = sumw[trackmid3];
  qA[bin][0]->Add(qxtrk_,pow(ax,2)-pow(ay,2));
  qA[bin][0]->Add(qytrk_,2*ax*ay);
  qB[bin][0]->Add(qxtrk_,pow(bx,2)-pow(by,2));
  qB[bin][0]->Add(qytrk_,2*bx*by);
  wnA[bin][0]->Add(qcnt_,pow(wa,2));
  wnB[bin][0]->Add(qcnt_,pow(wb,2));
  qBA[bin][0]->Fill(0.,pow(ax,2)*(pow(bx,2)-pow(by,2)) + pow(ay,2)*(pow(by,2)-pow(bx,2))+4*ax*ay*bx*by);
  qCA[bin][0]->Fill(0.,pow(ax,2)*(pow(cx,2)-pow(cy,2)) + pow(ay,2)*(pow(cy,2)-pow(cx,2))+4*ax*ay*cx*cy);
  qCB[bin][0]->Fill(0.,pow(bx,2)*(pow(cx,2)-pow(cy,2)) + pow(by,2)*(pow(cy,2)-pow(cx,2))+4*bx*by*cx*cy);
  qBAcnt[bin][0]->Fill(0.,pow(wa*wb,2));
  qCAcnt[bin][0]->Fill(0.,pow(wa*wc,2));
  qCBcnt[bin][0]->Fill(0.,pow(wb*wc,2));
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_,pow(ax,2)-pow(ay,2));
  qA[bin][j]->Add(qytrk_,2*ax*ay);
  qB[bin][j]->Add(qxtrk_,pow(bx,2)-pow(by,2));
  qB[bin][j]->Add(qytrk_,2*bx*by);
  wnA[bin][j]->Add(qcnt_,pow(wa,2));
  wnB[bin][j]->Add(qcnt_,pow(wb,2));
  qBA[bin][j]->Fill(0.,pow(ax,2)*(pow(bx,2)-pow(by,2)) + pow(ay,2)*(pow(by,2)-pow(bx,2))+4*ax*ay*bx*by);
  qCA[bin][j]->Fill(0.,pow(ax,2)*(pow(cx,2)-pow(cy,2)) + pow(ay,2)*(pow(cy,2)-pow(cx,2))+4*ax*ay*cx*cy);
  qCB[bin][j]->Fill(0.,pow(bx,2)*(pow(cx,2)-pow(cy,2)) + pow(by,2)*(pow(cy,2)-pow(cx,2))+4*bx*by*cx*cy);
  qBAcnt[bin][j]->Fill(0.,pow(wa*wb,2));
  qCAcnt[bin][j]->Fill(0.,pow(wa*wc,2));
  qCBcnt[bin][j]->Fill(0.,pow(wb*wc,2));


}
