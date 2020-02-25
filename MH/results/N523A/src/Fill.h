void Fill_NSUB3(int bin, TH2D *qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double Ax, double Ay, double Bx, double By, double Cx, double Cy, double wA, double wB, double wC){
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

  qA[bin][0]->Add(qxtrk_,a2x*a3x-a2y*a3y);
  qA[bin][0]->Add(qytrk_,a2y*a3x+a2x*a3y);
  qB[bin][0]->Add(qxtrk_,b2x*b3x-b2y*b3y);
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
  qA[bin][j]->Add(qxtrk_,a2x*a3x-a2y*a3y);
  qA[bin][j]->Add(qytrk_,a2y*a3x+a2x*a3y);
  qB[bin][j]->Add(qxtrk_,b2x*b3x-b2y*b3y);
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

  qA[bin][0]->Add(qxtrk_,a2x*a3x-a2y*a3y);
  qA[bin][0]->Add(qytrk_,a2y*a3x+a2x*a3y);
  qB[bin][0]->Add(qxtrk_,b2x*b3x-b2y*b3y);
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
  qA[bin][j]->Add(qxtrk_,a2x*a3x-a2y*a3y);
  qA[bin][j]->Add(qytrk_,a2y*a3x+a2x*a3y);
  qB[bin][j]->Add(qxtrk_,b2x*b3x-b2y*b3y);
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

void Fill_N62SUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
  double ax = qx[HFp2];
  double ay = qy[HFp2];
  double wa = sumw[HFp2];

  double bx = qx[HFm2];
  double by = qy[HFm2];
  double wb = sumw[HFm2];

  double cx = qx[trackmid2];
  double cy = qy[trackmid2];
  double wc = sumw[trackmid2];
  qA[bin][0]->Add(qxtrk_,pow(ax,3)-3*ax*pow(ay,2));
  qA[bin][0]->Add(qytrk_,3*ay*pow(ax,2)-pow(ay,3));
  qB[bin][0]->Add(qxtrk_,pow(bx,3)-3*bx*pow(by,2));
  qB[bin][0]->Add(qytrk_,3*by*pow(bx,2)-pow(by,3));
  wnA[bin][0]->Add(qcnt_,pow(wa,3));
  wnB[bin][0]->Add(qcnt_,pow(wb,3));
  qBA[bin][0]->Fill(0.,pow(ax,3)*pow(bx,3) - 3*ax*pow(ay,2)*pow(bx,3) + 9*pow(ax,2)*ay*pow(bx,2)*by - 3*pow(ay,3)*pow(bx,2)*by - 3*pow(ax,3)*bx*pow(by,2) + 
   9*ax*pow(ay,2)*bx*pow(by,2) - 3*pow(ax,2)*ay*pow(by,3) + pow(ay,3)*pow(by,3));
  qCA[bin][0]->Fill(0.,pow(ax,3)*pow(cx,3) - 3*ax*pow(ay,2)*pow(cx,3) + 9*pow(ax,2)*ay*pow(cx,2)*cy - 3*pow(ay,3)*pow(cx,2)*cy - 3*pow(ax,3)*cx*pow(cy,2) + 
   9*ax*pow(ay,2)*cx*pow(cy,2) - 3*pow(ax,2)*ay*pow(cy,3) + pow(ay,3)*pow(cy,3));
  qCB[bin][0]->Fill(0.,pow(bx,3)*pow(cx,3) - 3*bx*pow(by,2)*pow(cx,3) + 9*pow(bx,2)*by*pow(cx,2)*cy - 3*pow(by,3)*pow(cx,2)*cy - 3*pow(bx,3)*cx*pow(cy,2) + 
   9*bx*pow(by,2)*cx*pow(cy,2) - 3*pow(bx,2)*by*pow(cy,3) + pow(by,3)*pow(cy,3));
  qBAcnt[bin][0]->Fill(0.,pow(wa*wb,3));
  qCAcnt[bin][0]->Fill(0.,pow(wa*wc,3));
  qCBcnt[bin][0]->Fill(0.,pow(wb*wc,3));
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_,pow(ax,3)-3*ax*pow(ay,2));
  qA[bin][j]->Add(qytrk_,3*ay*pow(ax,2)-pow(ay,3));
  qB[bin][j]->Add(qxtrk_,pow(bx,3)-3*bx*pow(by,2));
  qB[bin][j]->Add(qytrk_,3*by*pow(bx,2)-pow(by,3));
  wnA[bin][j]->Add(qcnt_,pow(wa,3));
  wnB[bin][j]->Add(qcnt_,pow(wb,3));
  qBA[bin][j]->Fill(0.,pow(ax,3)*pow(bx,3) - 3*ax*pow(ay,2)*pow(bx,3) + 9*pow(ax,2)*ay*pow(bx,2)*by - 3*pow(ay,3)*pow(bx,2)*by - 3*pow(ax,3)*bx*pow(by,2) + 
   9*ax*pow(ay,2)*bx*pow(by,2) - 3*pow(ax,2)*ay*pow(by,3) + pow(ay,3)*pow(by,3));
  qCA[bin][j]->Fill(0.,pow(ax,3)*pow(cx,3) - 3*ax*pow(ay,2)*pow(cx,3) + 9*pow(ax,2)*ay*pow(cx,2)*cy - 3*pow(ay,3)*pow(cx,2)*cy - 3*pow(ax,3)*cx*pow(cy,2) + 
   9*ax*pow(ay,2)*cx*pow(cy,2) - 3*pow(ax,2)*ay*pow(cy,3) + pow(ay,3)*pow(cy,3));
  qCB[bin][j]->Fill(0.,pow(bx,3)*pow(cx,3) - 3*bx*pow(by,2)*pow(cx,3) + 9*pow(bx,2)*by*pow(cx,2)*cy - 3*pow(by,3)*pow(cx,2)*cy - 3*pow(bx,3)*cx*pow(cy,2) + 
   9*bx*pow(by,2)*cx*pow(cy,2) - 3*pow(bx,2)*by*pow(cy,3) + pow(by,3)*pow(cy,3));
  qBAcnt[bin][j]->Fill(0.,pow(wa*wb,3));
  qCAcnt[bin][j]->Fill(0.,pow(wa*wc,3));
  qCBcnt[bin][j]->Fill(0.,pow(wb*wc,3));
 

}
void Fill_N723SUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
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

  qA[bin][0]->Add(qxtrk_,pow(a2x,2)*a3x - pow(a2y,2)*a3x - 2*a2x*a2y*a3y);
  qA[bin][0]->Add(qytrk_,2*a2x*a2y*a3x  + pow(a2x,2)*a3y - pow(a2y,2)*a3y );
  qB[bin][0]->Add(qxtrk_,pow(b2x,2)*b3x - pow(b2y,2)*b3x - 2*b2x*b2y*b3y);
  qB[bin][0]->Add(qytrk_, 2*b2x*b2y*b3x + pow(b2x,2)*b3y - pow(b2y,2)*b3y );
  wnA[bin][0]->Add(qcnt_,wa2*wa2*wa3);
  wnB[bin][0]->Add(qcnt_,wb2*wa2*wb3);
  qBA[bin][0]->Fill(0.,pow(a2x,2)*a3x*pow(b2x,2)*b3x - pow(a2y,2)*a3x*pow(b2x,2)*b3x - 2*a2x*a2y*a3y*pow(b2x,2)*b3x + 4*a2x*a2y*a3x*b2x*b2y*b3x + 2*pow(a2x,2)*a3y*b2x*b2y*b3x - 
   2*pow(a2y,2)*a3y*b2x*b2y*b3x - pow(a2x,2)*a3x*pow(b2y,2)*b3x + pow(a2y,2)*a3x*pow(b2y,2)*b3x + 2*a2x*a2y*a3y*pow(b2y,2)*b3x + 2*a2x*a2y*a3x*pow(b2x,2)*b3y + 
   pow(a2x,2)*a3y*pow(b2x,2)*b3y - pow(a2y,2)*a3y*pow(b2x,2)*b3y - 2*pow(a2x,2)*a3x*b2x*b2y*b3y + 2*pow(a2y,2)*a3x*b2x*b2y*b3y + 4*a2x*a2y*a3y*b2x*b2y*b3y - 
   2*a2x*a2y*a3x*pow(b2y,2)*b3y - pow(a2x,2)*a3y*pow(b2y,2)*b3y + pow(a2y,2)*a3y*pow(b2y,2)*b3y);
  qCA[bin][0]->Fill(0.,pow(a2x,2)*a3x*pow(c2x,2)*c3x - pow(a2y,2)*a3x*pow(c2x,2)*c3x - 2*a2x*a2y*a3y*pow(c2x,2)*c3x + 4*a2x*a2y*a3x*c2x*c2y*c3x + 2*pow(a2x,2)*a3y*c2x*c2y*c3x - 
   2*pow(a2y,2)*a3y*c2x*c2y*c3x - pow(a2x,2)*a3x*pow(c2y,2)*c3x + pow(a2y,2)*a3x*pow(c2y,2)*c3x + 2*a2x*a2y*a3y*pow(c2y,2)*c3x + 2*a2x*a2y*a3x*pow(c2x,2)*c3y + 
   pow(a2x,2)*a3y*pow(c2x,2)*c3y - pow(a2y,2)*a3y*pow(c2x,2)*c3y - 2*pow(a2x,2)*a3x*c2x*c2y*c3y + 2*pow(a2y,2)*a3x*c2x*c2y*c3y + 4*a2x*a2y*a3y*c2x*c2y*c3y - 
   2*a2x*a2y*a3x*pow(c2y,2)*c3y - pow(a2x,2)*a3y*pow(c2y,2)*c3y + pow(a2y,2)*a3y*pow(c2y,2)*c3y);
  qCB[bin][0]->Fill(0.,pow(b2x,2)*b3x*pow(c2x,2)*c3x - pow(b2y,2)*b3x*pow(c2x,2)*c3x - 2*b2x*b2y*b3y*pow(c2x,2)*c3x + 4*b2x*b2y*b3x*c2x*c2y*c3x + 2*pow(b2x,2)*b3y*c2x*c2y*c3x - 
   2*pow(b2y,2)*b3y*c2x*c2y*c3x - pow(b2x,2)*b3x*pow(c2y,2)*c3x + pow(b2y,2)*b3x*pow(c2y,2)*c3x + 2*b2x*b2y*b3y*pow(c2y,2)*c3x + 2*b2x*b2y*b3x*pow(c2x,2)*c3y + 
   pow(b2x,2)*b3y*pow(c2x,2)*c3y - pow(b2y,2)*b3y*pow(c2x,2)*c3y - 2*pow(b2x,2)*b3x*c2x*c2y*c3y + 2*pow(b2y,2)*b3x*c2x*c2y*c3y + 4*b2x*b2y*b3y*c2x*c2y*c3y - 
   2*b2x*b2y*b3x*pow(c2y,2)*c3y - pow(b2x,2)*b3y*pow(c2y,2)*c3y + pow(b2y,2)*b3y*pow(c2y,2)*c3y);
  qBAcnt[bin][0]->Fill(0.,wb2*wb2*wb3*wa2*wa2*wa3);
  qCAcnt[bin][0]->Fill(0.,wc2*wc2*wc3*wa2*wa2*wa3);
  qCBcnt[bin][0]->Fill(0.,wc2*wc2*wc3*wb2*wb2*wb3);
 
 int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_,pow(a2x,2)*a3x - pow(a2y,2)*a3x- 2*a2x*a2y*a3y);
  qA[bin][j]->Add(qytrk_,2*a2x*a2y*a3x + pow(a2x,2)*a3y- pow(a2y,2)*a3y );
  qB[bin][j]->Add(qxtrk_,pow(b2x,2)*b3x - pow(b2y,2)*b3x - 2*b2x*b2y*b3y);
  qB[bin][j]->Add(qytrk_, 2*b2x*b2y*b3x + pow(b2x,2)*b3y - pow(b2y,2)*b3y );
  wnA[bin][j]->Add(qcnt_,wa2*wa2*wa3);
  wnB[bin][j]->Add(qcnt_,wb2*wa2*wb3);
  qBA[bin][j]->Fill(0.,pow(a2x,2)*a3x*pow(b2x,2)*b3x - pow(a2y,2)*a3x*pow(b2x,2)*b3x - 2*a2x*a2y*a3y*pow(b2x,2)*b3x + 4*a2x*a2y*a3x*b2x*b2y*b3x + 2*pow(a2x,2)*a3y*b2x*b2y*b3x - 
   2*pow(a2y,2)*a3y*b2x*b2y*b3x - pow(a2x,2)*a3x*pow(b2y,2)*b3x + pow(a2y,2)*a3x*pow(b2y,2)*b3x + 2*a2x*a2y*a3y*pow(b2y,2)*b3x + 2*a2x*a2y*a3x*pow(b2x,2)*b3y + 
   pow(a2x,2)*a3y*pow(b2x,2)*b3y - pow(a2y,2)*a3y*pow(b2x,2)*b3y - 2*pow(a2x,2)*a3x*b2x*b2y*b3y + 2*pow(a2y,2)*a3x*b2x*b2y*b3y + 4*a2x*a2y*a3y*b2x*b2y*b3y - 
   2*a2x*a2y*a3x*pow(b2y,2)*b3y - pow(a2x,2)*a3y*pow(b2y,2)*b3y + pow(a2y,2)*a3y*pow(b2y,2)*b3y);
  qCA[bin][j]->Fill(0.,pow(a2x,2)*a3x*pow(c2x,2)*c3x - pow(a2y,2)*a3x*pow(c2x,2)*c3x - 2*a2x*a2y*a3y*pow(c2x,2)*c3x + 4*a2x*a2y*a3x*c2x*c2y*c3x + 2*pow(a2x,2)*a3y*c2x*c2y*c3x - 
   2*pow(a2y,2)*a3y*c2x*c2y*c3x - pow(a2x,2)*a3x*pow(c2y,2)*c3x + pow(a2y,2)*a3x*pow(c2y,2)*c3x + 2*a2x*a2y*a3y*pow(c2y,2)*c3x + 2*a2x*a2y*a3x*pow(c2x,2)*c3y + 
   pow(a2x,2)*a3y*pow(c2x,2)*c3y - pow(a2y,2)*a3y*pow(c2x,2)*c3y - 2*pow(a2x,2)*a3x*c2x*c2y*c3y + 2*pow(a2y,2)*a3x*c2x*c2y*c3y + 4*a2x*a2y*a3y*c2x*c2y*c3y - 
   2*a2x*a2y*a3x*pow(c2y,2)*c3y - pow(a2x,2)*a3y*pow(c2y,2)*c3y + pow(a2y,2)*a3y*pow(c2y,2)*c3y);
  qCB[bin][j]->Fill(0.,pow(b2x,2)*b3x*pow(c2x,2)*c3x - pow(b2y,2)*b3x*pow(c2x,2)*c3x - 2*b2x*b2y*b3y*pow(c2x,2)*c3x + 4*b2x*b2y*b3x*c2x*c2y*c3x + 2*pow(b2x,2)*b3y*c2x*c2y*c3x - 
   2*pow(b2y,2)*b3y*c2x*c2y*c3x - pow(b2x,2)*b3x*pow(c2y,2)*c3x + pow(b2y,2)*b3x*pow(c2y,2)*c3x + 2*b2x*b2y*b3y*pow(c2y,2)*c3x + 2*b2x*b2y*b3x*pow(c2x,2)*c3y + 
   pow(b2x,2)*b3y*pow(c2x,2)*c3y - pow(b2y,2)*b3y*pow(c2x,2)*c3y - 2*pow(b2x,2)*b3x*c2x*c2y*c3y + 2*pow(b2y,2)*b3x*c2x*c2y*c3y + 4*b2x*b2y*b3y*c2x*c2y*c3y - 
   2*b2x*b2y*b3x*pow(c2y,2)*c3y - pow(b2x,2)*b3y*pow(c2y,2)*c3y + pow(b2y,2)*b3y*pow(c2y,2)*c3y);
  qBAcnt[bin][j]->Fill(0.,wb2*wb2*wb3*wa2*wa2*wa3);
  qCAcnt[bin][j]->Fill(0.,wc2*wc2*wc3*wa2*wa2*wa3);
  qCBcnt[bin][j]->Fill(0.,wc2*wc2*wc3*wb2*wb2*wb3);

}

void Fill_N723ASUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
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

  qA[bin][0]->Add(qxtrk_,pow(a2x,2)*a3x - pow(a2y,2)*a3x- 2*a2x*a2y*a3y);
  qA[bin][0]->Add(qytrk_,2*a2x*a2y*a3x + pow(a2x,2)*a3y- pow(a2y,2)*a3y );
  qB[bin][0]->Add(qxtrk_,pow(b2x,2)*b3x - pow(b2y,2)*b3x - 2*b2x*b2y*b3y);
  qB[bin][0]->Add(qytrk_, 2*b2x*b2y*b3x + pow(b2x,2)*b3y - pow(b2y,2)*b3y );
  wnA[bin][0]->Add(qcnt_,wa2*wa2*wa3);
  wnB[bin][0]->Add(qcnt_,wb2*wa2*wb3);
  qBA[bin][0]->Fill(0.,pow(a2x,2)*a3x*pow(b2x,2)*b3x - pow(a2y,2)*a3x*pow(b2x,2)*b3x - 2*a2x*a2y*a3y*pow(b2x,2)*b3x + 4*a2x*a2y*a3x*b2x*b2y*b3x + 2*pow(a2x,2)*a3y*b2x*b2y*b3x - 
   2*pow(a2y,2)*a3y*b2x*b2y*b3x - pow(a2x,2)*a3x*pow(b2y,2)*b3x + pow(a2y,2)*a3x*pow(b2y,2)*b3x + 2*a2x*a2y*a3y*pow(b2y,2)*b3x + 2*a2x*a2y*a3x*pow(b2x,2)*b3y + 
   pow(a2x,2)*a3y*pow(b2x,2)*b3y - pow(a2y,2)*a3y*pow(b2x,2)*b3y - 2*pow(a2x,2)*a3x*b2x*b2y*b3y + 2*pow(a2y,2)*a3x*b2x*b2y*b3y + 4*a2x*a2y*a3y*b2x*b2y*b3y - 
   2*a2x*a2y*a3x*pow(b2y,2)*b3y - pow(a2x,2)*a3y*pow(b2y,2)*b3y + pow(a2y,2)*a3y*pow(b2y,2)*b3y);
  qCA[bin][0]->Fill(0.,pow(a2x,2)*a3x*pow(c2x,2)*c3x - pow(a2y,2)*a3x*pow(c2x,2)*c3x - 2*a2x*a2y*a3y*pow(c2x,2)*c3x + 4*a2x*a2y*a3x*c2x*c2y*c3x + 2*pow(a2x,2)*a3y*c2x*c2y*c3x - 
   2*pow(a2y,2)*a3y*c2x*c2y*c3x - pow(a2x,2)*a3x*pow(c2y,2)*c3x + pow(a2y,2)*a3x*pow(c2y,2)*c3x + 2*a2x*a2y*a3y*pow(c2y,2)*c3x + 2*a2x*a2y*a3x*pow(c2x,2)*c3y + 
   pow(a2x,2)*a3y*pow(c2x,2)*c3y - pow(a2y,2)*a3y*pow(c2x,2)*c3y - 2*pow(a2x,2)*a3x*c2x*c2y*c3y + 2*pow(a2y,2)*a3x*c2x*c2y*c3y + 4*a2x*a2y*a3y*c2x*c2y*c3y - 
   2*a2x*a2y*a3x*pow(c2y,2)*c3y - pow(a2x,2)*a3y*pow(c2y,2)*c3y + pow(a2y,2)*a3y*pow(c2y,2)*c3y);
  qCB[bin][0]->Fill(0.,pow(b2x,2)*b3x*pow(c2x,2)*c3x - pow(b2y,2)*b3x*pow(c2x,2)*c3x - 2*b2x*b2y*b3y*pow(c2x,2)*c3x + 4*b2x*b2y*b3x*c2x*c2y*c3x + 2*pow(b2x,2)*b3y*c2x*c2y*c3x - 
   2*pow(b2y,2)*b3y*c2x*c2y*c3x - pow(b2x,2)*b3x*pow(c2y,2)*c3x + pow(b2y,2)*b3x*pow(c2y,2)*c3x + 2*b2x*b2y*b3y*pow(c2y,2)*c3x + 2*b2x*b2y*b3x*pow(c2x,2)*c3y + 
   pow(b2x,2)*b3y*pow(c2x,2)*c3y - pow(b2y,2)*b3y*pow(c2x,2)*c3y - 2*pow(b2x,2)*b3x*c2x*c2y*c3y + 2*pow(b2y,2)*b3x*c2x*c2y*c3y + 4*b2x*b2y*b3y*c2x*c2y*c3y - 
   2*b2x*b2y*b3x*pow(c2y,2)*c3y - pow(b2x,2)*b3y*pow(c2y,2)*c3y + pow(b2y,2)*b3y*pow(c2y,2)*c3y);
  qBAcnt[bin][0]->Fill(0.,wb2*wb2*wb3*wa2*wa2*wa3);
  qCAcnt[bin][0]->Fill(0.,wc2*wc2*wc3*wa2*wa2*wa3);
  qCBcnt[bin][0]->Fill(0.,wc2*wc2*wc3*wb2*wb2*wb3);
 
 int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_,pow(a2x,2)*a3x - pow(a2y,2)*a3x- 2*a2x*a2y*a3y);
  qA[bin][j]->Add(qytrk_,2*a2x*a2y*a3x + pow(a2x,2)*a3y- pow(a2y,2)*a3y );
  qB[bin][j]->Add(qxtrk_,pow(b2x,2)*b3x - pow(b2y,2)*b3x - 2*b2x*b2y*b3y);
  qB[bin][j]->Add(qytrk_, 2*b2x*b2y*b3x + pow(b2x,2)*b3y - pow(b2y,2)*b3y );
  wnA[bin][j]->Add(qcnt_,wa2*wa2*wa3);
  wnB[bin][j]->Add(qcnt_,wb2*wa2*wb3);
  qBA[bin][j]->Fill(0.,pow(a2x,2)*a3x*pow(b2x,2)*b3x - pow(a2y,2)*a3x*pow(b2x,2)*b3x - 2*a2x*a2y*a3y*pow(b2x,2)*b3x + 4*a2x*a2y*a3x*b2x*b2y*b3x + 2*pow(a2x,2)*a3y*b2x*b2y*b3x - 
   2*pow(a2y,2)*a3y*b2x*b2y*b3x - pow(a2x,2)*a3x*pow(b2y,2)*b3x + pow(a2y,2)*a3x*pow(b2y,2)*b3x + 2*a2x*a2y*a3y*pow(b2y,2)*b3x + 2*a2x*a2y*a3x*pow(b2x,2)*b3y + 
   pow(a2x,2)*a3y*pow(b2x,2)*b3y - pow(a2y,2)*a3y*pow(b2x,2)*b3y - 2*pow(a2x,2)*a3x*b2x*b2y*b3y + 2*pow(a2y,2)*a3x*b2x*b2y*b3y + 4*a2x*a2y*a3y*b2x*b2y*b3y - 
   2*a2x*a2y*a3x*pow(b2y,2)*b3y - pow(a2x,2)*a3y*pow(b2y,2)*b3y + pow(a2y,2)*a3y*pow(b2y,2)*b3y);
  qCA[bin][j]->Fill(0.,pow(a2x,2)*a3x*pow(c2x,2)*c3x - pow(a2y,2)*a3x*pow(c2x,2)*c3x - 2*a2x*a2y*a3y*pow(c2x,2)*c3x + 4*a2x*a2y*a3x*c2x*c2y*c3x + 2*pow(a2x,2)*a3y*c2x*c2y*c3x - 
   2*pow(a2y,2)*a3y*c2x*c2y*c3x - pow(a2x,2)*a3x*pow(c2y,2)*c3x + pow(a2y,2)*a3x*pow(c2y,2)*c3x + 2*a2x*a2y*a3y*pow(c2y,2)*c3x + 2*a2x*a2y*a3x*pow(c2x,2)*c3y + 
   pow(a2x,2)*a3y*pow(c2x,2)*c3y - pow(a2y,2)*a3y*pow(c2x,2)*c3y - 2*pow(a2x,2)*a3x*c2x*c2y*c3y + 2*pow(a2y,2)*a3x*c2x*c2y*c3y + 4*a2x*a2y*a3y*c2x*c2y*c3y - 
   2*a2x*a2y*a3x*pow(c2y,2)*c3y - pow(a2x,2)*a3y*pow(c2y,2)*c3y + pow(a2y,2)*a3y*pow(c2y,2)*c3y);
  qCB[bin][j]->Fill(0.,pow(b2x,2)*b3x*pow(c2x,2)*c3x - pow(b2y,2)*b3x*pow(c2x,2)*c3x - 2*b2x*b2y*b3y*pow(c2x,2)*c3x + 4*b2x*b2y*b3x*c2x*c2y*c3x + 2*pow(b2x,2)*b3y*c2x*c2y*c3x - 
   2*pow(b2y,2)*b3y*c2x*c2y*c3x - pow(b2x,2)*b3x*pow(c2y,2)*c3x + pow(b2y,2)*b3x*pow(c2y,2)*c3x + 2*b2x*b2y*b3y*pow(c2y,2)*c3x + 2*b2x*b2y*b3x*pow(c2x,2)*c3y + 
   pow(b2x,2)*b3y*pow(c2x,2)*c3y - pow(b2y,2)*b3y*pow(c2x,2)*c3y - 2*pow(b2x,2)*b3x*c2x*c2y*c3y + 2*pow(b2y,2)*b3x*c2x*c2y*c3y + 4*b2x*b2y*b3y*c2x*c2y*c3y - 
   2*b2x*b2y*b3x*pow(c2y,2)*c3y - pow(b2x,2)*b3y*pow(c2y,2)*c3y + pow(b2y,2)*b3y*pow(c2y,2)*c3y);
  qBAcnt[bin][j]->Fill(0.,wb2*wb2*wb3*wa2*wa2*wa3);
  qCAcnt[bin][j]->Fill(0.,wc2*wc2*wc3*wa2*wa2*wa3);
  qCBcnt[bin][j]->Fill(0.,wc2*wc2*wc3*wb2*wb2*wb3);

}
TH2D * qxy = 0;
void Fill_D24SUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
  double ax = qx[HFp2];
  double ay = qy[HFp2];
  double wa = sumw[HFp2];

  double bx = qx[HFm2];
  double by = qy[HFm2];
  double wb = sumw[HFm2];

  double cx = qx[trackmid2];
  double cy = qy[trackmid2];
  double wc = sumw[trackmid2];
  qxy->Reset();
  qxy->Add(qxtrk_,1.);
  qxy->Multiply(qytrk_);

  qxtrk_->Multiply(qxtrk_);
  qytrk_->Multiply(qytrk_);
  qcnt_->Multiply(qcnt_);

  qA[bin][0]->Add(qxtrk_, pow(ax,2) - pow(ay,2));
  qA[bin][0]->Add(qytrk_, pow(ay,2) - pow(ax,2));
  qA[bin][0]->Add(qxy, 4*ax*ay);
  
  qB[bin][0]->Add(qxtrk_, pow(bx,2) - pow(by,2));
  qB[bin][0]->Add(qytrk_, pow(by,2) - pow(bx,2));
  qB[bin][0]->Add(qxy, 4*bx*by);
  
  wnA[bin][0]->Add(qcnt_,pow(wa,2));
  wnB[bin][0]->Add(qcnt_,pow(wb,2));
  qBA[bin][0]->Fill(0.,pow(ax,2)*(pow(bx,2)-pow(by,2)) + pow(ay,2)*(pow(by,2)-pow(bx,2))+4*ax*ay*bx*by);
  qCA[bin][0]->Fill(0.,pow(ax,2)*(pow(cx,2)-pow(cy,2)) + pow(ay,2)*(pow(cy,2)-pow(cx,2))+4*ax*ay*cx*cy);
  qCB[bin][0]->Fill(0.,pow(bx,2)*(pow(cx,2)-pow(cy,2)) + pow(by,2)*(pow(cy,2)-pow(cx,2))+4*bx*by*cx*cy);
  qBAcnt[bin][0]->Fill(0.,pow(wa*wb,2));
  qCAcnt[bin][0]->Fill(0.,pow(wa*wc,2));
  qCBcnt[bin][0]->Fill(0.,pow(wb*wc,2));
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_, pow(ax,2) - pow(ay,2));
  qA[bin][j]->Add(qytrk_, pow(ay,2) - pow(ax,2));
  qA[bin][j]->Add(qxy, 4*ax*ay);
  
  qB[bin][j]->Add(qxtrk_, pow(bx,2) - pow(by,2));
  qB[bin][j]->Add(qytrk_, pow(by,2) - pow(bx,2));
  qB[bin][j]->Add(qxy, 4*bx*by);
  
  wnA[bin][j]->Add(qcnt_,pow(wa,2));
  wnB[bin][j]->Add(qcnt_,pow(wb,2));
  qBA[bin][j]->Fill(0.,pow(ax,2)*(pow(bx,2)-pow(by,2)) + pow(ay,2)*(pow(by,2)-pow(bx,2))+4*ax*ay*bx*by);
  qCA[bin][j]->Fill(0.,pow(ax,2)*(pow(cx,2)-pow(cy,2)) + pow(ay,2)*(pow(cy,2)-pow(cx,2))+4*ax*ay*cx*cy);
  qCB[bin][j]->Fill(0.,pow(bx,2)*(pow(cx,2)-pow(cy,2)) + pow(by,2)*(pow(cy,2)-pow(cx,2))+4*bx*by*cx*cy);
  qBAcnt[bin][j]->Fill(0.,pow(wa*wb,2));
  qCAcnt[bin][j]->Fill(0.,pow(wa*wc,2));
  qCBcnt[bin][j]->Fill(0.,pow(wb*wc,2));
  
}

TH2D * qxxy = 0;
TH2D * qxyy = 0;

void Fill_D26SUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
  double ax = qx[HFp2];
  double ay = qy[HFp2];
  double wa = sumw[HFp2];

  double bx = qx[HFm2];
  double by = qy[HFm2];
  double wb = sumw[HFm2];

  double cx = qx[trackmid2];
  double cy = qy[trackmid2];
  double wc = sumw[trackmid2];
  qxxy->Reset();
  qxxy->Add(qxtrk_,1.);
  qxxy->Multiply(qxtrk_);
  qxxy->Multiply(qytrk_);

  qxyy->Reset();
  qxyy->Add(qxtrk_,1.);
  qxyy->Multiply(qytrk_);
  qxyy->Multiply(qytrk_);

  qxtrk_->Multiply(qxtrk_);
  qxtrk_->Multiply(qxtrk_);

  qytrk_->Multiply(qytrk_);
  qytrk_->Multiply(qytrk_);

  qcnt_->Multiply(qcnt_);
  qcnt_->Multiply(qcnt_);

  qA[bin][0]->Add(qxtrk_, pow(ax,3) - 3*ax*pow(ay,2));
  qA[bin][0]->Add(qytrk_, pow(ay,3) - 3*ay*pow(ax,2));
  qA[bin][0]->Add(qxxy, 9*pow(ax,2)*ay - 3*pow(ay,3));
  qA[bin][0]->Add(qxyy, 9*pow(ay,2)*ax - 3*pow(ax,3));

  qB[bin][0]->Add(qxtrk_, pow(bx,3) - 3*bx*pow(by,2));
  qB[bin][0]->Add(qytrk_, pow(by,3) - 3*by*pow(bx,2));
  qB[bin][0]->Add(qxxy, 9*pow(bx,2)*by - 3*pow(by,3));
  qB[bin][0]->Add(qxyy, 9*pow(by,2)*bx - 3*pow(bx,3));
  
  wnA[bin][0]->Add(qcnt_,pow(wa,3));
  wnB[bin][0]->Add(qcnt_,pow(wb,3));
  qBA[bin][0]->Fill(0.,pow(ax,3)*pow(bx,3) - 2*pow(ax,2)*ay*pow(bx,3) - ax*pow(ay,2)*pow(bx,3) + 3*pow(ax,3)*pow(bx,2)*by + 6*pow(ax,2)*ay*pow(bx,2)*by - 
		    3*ax*pow(ay,2)*pow(bx,2)*by - 3*pow(ax,3)*bx*pow(by,2) + 6*pow(ax,2)*ay*bx*pow(by,2) + 3*ax*pow(ay,2)*bx*pow(by,2) - 
		    pow(ax,3)*pow(by,3) - 2*pow(ax,2)*ay*pow(by,3) + ax*pow(ay,2)*pow(by,3));
  qCA[bin][0]->Fill(0.,pow(ax,3)*pow(cx,3) - 2*pow(ax,2)*ay*pow(cx,3) - ax*pow(ay,2)*pow(cx,3) + 3*pow(ax,3)*pow(cx,2)*cy + 6*pow(ax,2)*ay*pow(cx,2)*cy - 
		    3*ax*pow(ay,2)*pow(cx,2)*cy - 3*pow(ax,3)*cx*pow(cy,2) + 6*pow(ax,2)*ay*cx*pow(cy,2) + 3*ax*pow(ay,2)*cx*pow(cy,2) - 
		    pow(ax,3)*pow(cy,3) - 2*pow(ax,2)*ay*pow(cy,3) + ax*pow(ay,2)*pow(cy,3));
  qCB[bin][0]->Fill(0.,pow(bx,3)*pow(cx,3) - 2*pow(bx,2)*by*pow(cx,3) - bx*pow(by,2)*pow(cx,3) + 3*pow(bx,3)*pow(cx,2)*cy + 6*pow(bx,2)*by*pow(cx,2)*cy - 
		    3*bx*pow(by,2)*pow(cx,2)*cy - 3*pow(bx,3)*cx*pow(cy,2) + 6*pow(bx,2)*by*cx*pow(cy,2) + 3*bx*pow(by,2)*cx*pow(cy,2) - 
		    pow(bx,3)*pow(cy,3) - 2*pow(bx,2)*by*pow(cy,3) + bx*pow(by,2)*pow(cy,3));
  qBAcnt[bin][0]->Fill(0.,pow(wa*wb,3));
  qCAcnt[bin][0]->Fill(0.,pow(wa*wc,3));
  qCBcnt[bin][0]->Fill(0.,pow(wb*wc,3));
  
  int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_, pow(ax,3) - 3*ax*pow(ay,2));
  qA[bin][j]->Add(qytrk_, pow(ay,3) - 3*ay*pow(ax,2));
  qA[bin][j]->Add(qxxy, 9*pow(ax,2)*ay - 3*pow(ay,3));
  qA[bin][j]->Add(qxyy, 9*pow(ay,2)*ax - 3*pow(ax,3));
  
  qB[bin][j]->Add(qxtrk_, pow(bx,3) - 3*bx*pow(by,2));
  qB[bin][j]->Add(qytrk_, pow(by,3) - 3*by*pow(bx,2));
  qB[bin][j]->Add(qxxy, 9*pow(bx,2)*by - 3*pow(by,3));
  qB[bin][j]->Add(qxyy, 9*pow(by,2)*bx - 3*pow(bx,3));
  
  wnA[bin][j]->Add(qcnt_,pow(wa,3));
  wnB[bin][j]->Add(qcnt_,pow(wb,3));
  qBA[bin][j]->Fill(0.,pow(ax,3)*pow(bx,3) - 2*pow(ax,2)*ay*pow(bx,3) - ax*pow(ay,2)*pow(bx,3) + 3*pow(ax,3)*pow(bx,2)*by + 6*pow(ax,2)*ay*pow(bx,2)*by - 
		    3*ax*pow(ay,2)*pow(bx,2)*by - 3*pow(ax,3)*bx*pow(by,2) + 6*pow(ax,2)*ay*bx*pow(by,2) + 3*ax*pow(ay,2)*bx*pow(by,2) - 
		    pow(ax,3)*pow(by,3) - 2*pow(ax,2)*ay*pow(by,3) + ax*pow(ay,2)*pow(by,3));
  qCA[bin][j]->Fill(0.,pow(ax,3)*pow(cx,3) - 2*pow(ax,2)*ay*pow(cx,3) - ax*pow(ay,2)*pow(cx,3) + 3*pow(ax,3)*pow(cx,2)*cy + 6*pow(ax,2)*ay*pow(cx,2)*cy - 
		    3*ax*pow(ay,2)*pow(cx,2)*cy - 3*pow(ax,3)*cx*pow(cy,2) + 6*pow(ax,2)*ay*cx*pow(cy,2) + 3*ax*pow(ay,2)*cx*pow(cy,2) - 
		    pow(ax,3)*pow(cy,3) - 2*pow(ax,2)*ay*pow(cy,3) + ax*pow(ay,2)*pow(cy,3));
  qCB[bin][j]->Fill(0.,pow(bx,3)*pow(cx,3) - 2*pow(bx,2)*by*pow(cx,3) - bx*pow(by,2)*pow(cx,3) + 3*pow(bx,3)*pow(cx,2)*cy + 6*pow(bx,2)*by*pow(cx,2)*cy - 
		    3*bx*pow(by,2)*pow(cx,2)*cy - 3*pow(bx,3)*cx*pow(cy,2) + 6*pow(bx,2)*by*cx*pow(cy,2) + 3*bx*pow(by,2)*cx*pow(cy,2) - 
		    pow(bx,3)*pow(cy,3) - 2*pow(bx,2)*by*pow(cy,3) + bx*pow(by,2)*pow(cy,3));
  qBAcnt[bin][j]->Fill(0.,pow(wa*wb,3));
  qCAcnt[bin][j]->Fill(0.,pow(wa*wc,3));
  qCBcnt[bin][j]->Fill(0.,pow(wb*wc,3));
  
}
void Fill_D34SUB3(int bin, TH2D * qxtrk_, TH2D * qytrk_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
  double ax = qx[HFp3];
  double ay = qy[HFp3];
  double wa = sumw[HFp3];

  double bx = qx[HFm3];
  double by = qy[HFm3];
  double wb = sumw[HFm3];

  double cx = qx[trackmid3];
  double cy = qy[trackmid3];
  double wc = sumw[trackmid3];
  qxy->Reset();
  qxy->Add(qxtrk_,1.);
  qxy->Multiply(qytrk_);

  qxtrk_->Multiply(qxtrk_);
  qytrk_->Multiply(qytrk_);
  qcnt_->Multiply(qcnt_);

  qA[bin][0]->Add(qxtrk_, pow(ax,2) - pow(ay,2));
  qA[bin][0]->Add(qytrk_, pow(ay,2) - pow(ax,2));
  qA[bin][0]->Add(qxy, 4*ax*ay);

  qB[bin][0]->Add(qxtrk_, pow(bx,2) - pow(by,2));
  qB[bin][0]->Add(qytrk_, pow(by,2) - pow(bx,2));
  qB[bin][0]->Add(qxy, 4*bx*by);

  wnA[bin][0]->Add(qcnt_,pow(wa,2));
  wnB[bin][0]->Add(qcnt_,pow(wb,2));
  qBA[bin][0]->Fill(0.,pow(ax,2)*(pow(bx,2)-pow(by,2)) + pow(ay,2)*(pow(by,2)-pow(bx,2))+4*ax*ay*bx*by);
  qCA[bin][0]->Fill(0.,pow(ax,2)*(pow(cx,2)-pow(cy,2)) + pow(ay,2)*(pow(cy,2)-pow(cx,2))+4*ax*ay*cx*cy);
  qCB[bin][0]->Fill(0.,pow(bx,2)*(pow(cx,2)-pow(cy,2)) + pow(by,2)*(pow(cy,2)-pow(cx,2))+4*bx*by*cx*cy);
  qBAcnt[bin][0]->Fill(0.,pow(wa*wb,2));
  qCAcnt[bin][0]->Fill(0.,pow(wa*wc,2));
  qCBcnt[bin][0]->Fill(0.,pow(wb*wc,2));

  int j=(int)(ran->Uniform(0,9.999))+1;
  qA[bin][j]->Add(qxtrk_, pow(ax,2) - pow(ay,2));
  qA[bin][j]->Add(qytrk_, pow(ay,2) - pow(ax,2));
  qA[bin][j]->Add(qxy, 4*ax*ay);
  
  qB[bin][j]->Add(qxtrk_, pow(bx,2) - pow(by,2));
  qB[bin][j]->Add(qytrk_, pow(by,2) - pow(bx,2));
  qB[bin][j]->Add(qxy, 4*bx*by);
  
  wnA[bin][j]->Add(qcnt_,pow(wa,2));
  wnB[bin][j]->Add(qcnt_,pow(wb,2));
  qBA[bin][j]->Fill(0.,pow(ax,2)*(pow(bx,2)-pow(by,2)) + pow(ay,2)*(pow(by,2)-pow(bx,2))+4*ax*ay*bx*by);
  qCA[bin][j]->Fill(0.,pow(ax,2)*(pow(cx,2)-pow(cy,2)) + pow(ay,2)*(pow(cy,2)-pow(cx,2))+4*ax*ay*cx*cy);
  qCB[bin][j]->Fill(0.,pow(bx,2)*(pow(cx,2)-pow(cy,2)) + pow(by,2)*(pow(cy,2)-pow(cx,2))+4*bx*by*cx*cy);
  qBAcnt[bin][j]->Fill(0.,pow(wa*wb,2));
  qCAcnt[bin][j]->Fill(0.,pow(wa*wc,2));
  qCBcnt[bin][j]->Fill(0.,pow(wb*wc,2));
  
  
}
TH2D * qx2y3 = 0;
TH2D * qy2x3 = 0;

void Fill_D2232SUB3(int bin, TH2D * qxtrk2_, TH2D * qytrk2_, TH2D * qxtrk3_, TH2D * qytrk3_, TH2D * qcnt_, double * qx, double * qy, double * sumw){

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

  qx2y3->Reset();
  qx2y3->Add(qxtrk2_,1.);
  qx2y3->Multiply(qytrk3_);

  qy2x3->Reset();
  qy2x3->Add(qytrk2_,1.);
  qy2x3->Multiply(qxtrk3_);

  qxtrk2_->Multiply(qxtrk3_);
  qytrk2_->Multiply(qytrk3_);

  qcnt_->Multiply(qcnt_);

  qA[bin][0]->Add(qxtrk2_,a2x*a3x-a2y*a3y);
  qA[bin][0]->Add(qytrk2_,a2y*a3y-a2x*a3x);
  qA[bin][0]->Add(qy2x3,  a2y*a3x+a2x*a3y);
  qA[bin][0]->Add(qx2y3,  a2y*a3x+a2x*a3y);

  qB[bin][0]->Add(qxtrk2_,b2x*b3x-b2y*b3y);
  qB[bin][0]->Add(qytrk2_,b2y*b3y-b2x*b3x);
  qB[bin][0]->Add(qy2x3,  b2y*b3x+b2x*b3y);
  qB[bin][0]->Add(qx2y3,  b2y*b3x+b2x*b3y);

  wnA[bin][0]->Add(qcnt_,wa2*wa3);
  wnB[bin][0]->Add(qcnt_,wb2*wb3);

  qBA[bin][0]->Fill(0.,a2x*a3x*b2x*b3x - a2y*a3y*b2x*b3x + a2y*a3x*b2y*b3x + a2x*a3y*b2y*b3x + a2y*a3x*b2x*b3y + a2x*a3y*b2x*b3y - a2x*a3x*b2y*b3y + a2y*a3y*b2y*b3y);
  qCA[bin][0]->Fill(0.,a2x*a3x*c2x*c3x - a2y*a3y*c2x*c3x + a2y*a3x*c2y*c3x + a2x*a3y*c2y*c3x + a2y*a3x*c2x*c3y + a2x*a3y*c2x*c3y - a2x*a3x*c2y*c3y + a2y*a3y*c2y*c3y);
  qCB[bin][0]->Fill(0.,b2x*b3x*c2x*c3x - b2y*b3y*c2x*c3x + b2y*b3x*c2y*c3x + b2x*b3y*c2y*c3x + b2y*b3x*c2x*c3y + b2x*b3y*c2x*c3y - b2x*b3x*c2y*c3y + b2y*b3y*c2y*c3y);
  qBAcnt[bin][0]->Fill(0.,wb2*wb3*wa2*wa3);
  qCAcnt[bin][0]->Fill(0.,wc2*wc3*wa2*wa3);
  qCBcnt[bin][0]->Fill(0.,wc2*wc3*wb2*wb3);
  
  int j=(int)(ran->Uniform(0,9.999))+1;


  qA[bin][j]->Add(qxtrk2_,a2x*a3x-a2y*a3y);
  qA[bin][j]->Add(qytrk2_,a2y*a3y-a2x*a3x);
  qA[bin][j]->Add(qy2x3,  a2y*a3x+a2x*a3y);
  qA[bin][j]->Add(qx2y3,  a2y*a3x+a2x*a3y);

  qB[bin][j]->Add(qxtrk2_,b2x*b3x-b2y*b3y);
  qB[bin][j]->Add(qytrk2_,b2y*b3y-b2x*b3x);
  qB[bin][j]->Add(qy2x3,  b2y*b3x+b2x*b3y);
  qB[bin][j]->Add(qx2y3,  b2y*b3x+b2x*b3y);

  wnA[bin][j]->Add(qcnt_,wa2*wa3);
  wnB[bin][j]->Add(qcnt_,wb2*wb3);

  qBA[bin][j]->Fill(0.,a2x*a3x*b2x*b3x - a2y*a3y*b2x*b3x + a2y*a3x*b2y*b3x + a2x*a3y*b2y*b3x + a2y*a3x*b2x*b3y + a2x*a3y*b2x*b3y - a2x*a3x*b2y*b3y + a2y*a3y*b2y*b3y);
  qCA[bin][j]->Fill(0.,a2x*a3x*c2x*c3x - a2y*a3y*c2x*c3x + a2y*a3x*c2y*c3x + a2x*a3y*c2y*c3x + a2y*a3x*c2x*c3y + a2x*a3y*c2x*c3y - a2x*a3x*c2y*c3y + a2y*a3y*c2y*c3y);
  qCB[bin][j]->Fill(0.,b2x*b3x*c2x*c3x - b2y*b3y*c2x*c3x + b2y*b3x*c2y*c3x + b2x*b3y*c2y*c3x + b2y*b3x*c2x*c3y + b2x*b3y*c2x*c3y - b2x*b3x*c2y*c3y + b2y*b3y*c2y*c3y);
  qBAcnt[bin][j]->Fill(0.,wb2*wb3*wa2*wa3);
  qCAcnt[bin][j]->Fill(0.,wc2*wc3*wa2*wa3);
  qCBcnt[bin][j]->Fill(0.,wc2*wc3*wb2*wb3);
  
  
}

void Fill_D2232ASUB3(int bin, TH2D * qxtrk2_, TH2D * qytrk2_, TH2D * qxtrk3_, TH2D * qytrk3_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
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

  qx2y3->Reset();
  qx2y3->Add(qxtrk2_,1.);
  qx2y3->Multiply(qytrk3_);

  qy2x3->Reset();
  qy2x3->Add(qytrk2_,1.);
  qy2x3->Multiply(qxtrk3_);

  qxtrk2_->Multiply(qxtrk3_);
  qytrk2_->Multiply(qytrk3_);

  qcnt_->Multiply(qcnt_);


  qA[bin][0]->Add(qxtrk2_,a2x*a3x-a2y*a3y);
  qA[bin][0]->Add(qytrk2_,a2y*a3y-a2x*a3x);
  qA[bin][0]->Add(qy2x3,  a2y*a3x+a2x*a3y);
  qA[bin][0]->Add(qx2y3,  a2y*a3x+a2x*a3y);

  qB[bin][0]->Add(qxtrk2_,b2x*b3x-b2y*b3y);
  qB[bin][0]->Add(qytrk2_,b2y*b3y-b2x*b3x);
  qB[bin][0]->Add(qy2x3,  b2y*b3x+b2x*b3y);
  qB[bin][0]->Add(qx2y3,  b2y*b3x+b2x*b3y);

  wnA[bin][0]->Add(qcnt_,wa2*wa3);
  wnB[bin][0]->Add(qcnt_,wb2*wb3);

  qBA[bin][0]->Fill(0.,a2x*a3x*b2x*b3x - a2y*a3y*b2x*b3x + a2y*a3x*b2y*b3x + a2x*a3y*b2y*b3x + a2y*a3x*b2x*b3y + a2x*a3y*b2x*b3y - a2x*a3x*b2y*b3y + a2y*a3y*b2y*b3y);
  qCA[bin][0]->Fill(0.,a2x*a3x*c2x*c3x - a2y*a3y*c2x*c3x + a2y*a3x*c2y*c3x + a2x*a3y*c2y*c3x + a2y*a3x*c2x*c3y + a2x*a3y*c2x*c3y - a2x*a3x*c2y*c3y + a2y*a3y*c2y*c3y);
  qCB[bin][0]->Fill(0.,b2x*b3x*c2x*c3x - b2y*b3y*c2x*c3x + b2y*b3x*c2y*c3x + b2x*b3y*c2y*c3x + b2y*b3x*c2x*c3y + b2x*b3y*c2x*c3y - b2x*b3x*c2y*c3y + b2y*b3y*c2y*c3y);
  qBAcnt[bin][0]->Fill(0.,wb2*wb3*wa2*wa3);
  qCAcnt[bin][0]->Fill(0.,wc2*wc3*wa2*wa3);
  qCBcnt[bin][0]->Fill(0.,wc2*wc3*wb2*wb3);
  
  int j=(int)(ran->Uniform(0,9.999))+1;

  qA[bin][j]->Add(qxtrk2_,a2x*a3x-a2y*a3y);
  qA[bin][j]->Add(qytrk2_,a2y*a3y-a2x*a3x);
  qA[bin][j]->Add(qy2x3,  a2y*a3x+a2x*a3y);
  qA[bin][j]->Add(qx2y3,  a2y*a3x+a2x*a3y);

  qB[bin][j]->Add(qxtrk2_,b2x*b3x-b2y*b3y);
  qB[bin][j]->Add(qytrk2_,b2y*b3y-b2x*b3x);
  qB[bin][j]->Add(qy2x3,  b2y*b3x+b2x*b3y);
  qB[bin][j]->Add(qx2y3,  b2y*b3x+b2x*b3y);

  wnA[bin][j]->Add(qcnt_,wa2*wa3);
  wnB[bin][j]->Add(qcnt_,wb2*wb3);

  qBA[bin][j]->Fill(0.,a2x*a3x*b2x*b3x - a2y*a3y*b2x*b3x + a2y*a3x*b2y*b3x + a2x*a3y*b2y*b3x + a2y*a3x*b2x*b3y + a2x*a3y*b2x*b3y - a2x*a3x*b2y*b3y + a2y*a3y*b2y*b3y);
  qCA[bin][j]->Fill(0.,a2x*a3x*c2x*c3x - a2y*a3y*c2x*c3x + a2y*a3x*c2y*c3x + a2x*a3y*c2y*c3x + a2y*a3x*c2x*c3y + a2x*a3y*c2x*c3y - a2x*a3x*c2y*c3y + a2y*a3y*c2y*c3y);
  qCB[bin][j]->Fill(0.,b2x*b3x*c2x*c3x - b2y*b3y*c2x*c3x + b2y*b3x*c2y*c3x + b2x*b3y*c2y*c3x + b2y*b3x*c2x*c3y + b2x*b3y*c2x*c3y - b2x*b3x*c2y*c3y + b2y*b3y*c2y*c3y);
  qBAcnt[bin][j]->Fill(0.,wb2*wb3*wa2*wa3);
  qCAcnt[bin][j]->Fill(0.,wc2*wc3*wa2*wa3);
  qCBcnt[bin][j]->Fill(0.,wc2*wc3*wb2*wb3);
  
  
}
TH2D * qx2x2x3;
TH2D * qx2x3y2;
TH2D * qx3y2y2;
TH2D * qx2x2y3;
TH2D * qx2y2y3;
TH2D * qy2y2y3;
TH2D * qcnt3;

void Fill_D2432SUB3(int bin, TH2D * qxtrk2_, TH2D * qytrk2_, TH2D * qxtrk3_, TH2D * qytrk3_, TH2D * qcnt_, double * qx, double * qy, double * sumw){

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
  
  qx2x2x3->Reset();
  qx2x3y2->Reset();
  qx3y2y2->Reset();
  qx2x2y3->Reset();
  qx2y2y3->Reset();
  qy2y2y3->Reset();
  
  qx2x2x3->Add(qxtrk2_,1.);
  qx2x2x3->Multiply(qxtrk2_);
  qx2x2x3->Multiply(qxtrk3_);

  qx2x3y2->Add(qxtrk2_,1.);
  qx2x3y2->Multiply(qxtrk3_);
  qx2x3y2->Multiply(qytrk2_);

  qx3y2y2->Add(qxtrk3_,1.);
  qx3y2y2->Multiply(qytrk2_);
  qx3y2y2->Multiply(qytrk2_);

  qx2x2y3->Add(qxtrk2_,1.);
  qx2x2y3->Multiply(qxtrk2_);
  qx2x2y3->Multiply(qytrk3_);

  qx2y2y3->Add(qxtrk2_,1.);
  qx2y2y3->Multiply(qytrk2_);
  qx2y2y3->Multiply(qytrk3_);
  
  qy2y2y3->Add(qytrk2_,1.);
  qy2y2y3->Multiply(qytrk2_);
  qy2y2y3->Multiply(qytrk3_);
  
  qcnt3->Add(qcnt_,1.);
  qcnt3->Multiply(qcnt_);
  qcnt3->Multiply(qcnt_);
  
  qA[bin][0]->Add(qx2x2x3,pow(a2x,2)*a3x    - pow(a2y,2)*a3x    - 2*a2x*a2y*a3y);
  qA[bin][0]->Add(qx2x3y2,4*a2x*a2y*a3x     + 2*pow(a2x,2)*a3y  - 2*pow(a2y,2)*a3y);
  qA[bin][0]->Add(qx3y2y2,pow(a2y,2)*a3x    - pow(a2x,2)*a3x    + 2*a2x*a2y*a3y);
  qA[bin][0]->Add(qx2x2y3,2*a2x*a2y*a3x     + pow(a2x,2)*a3y    - pow(a2y,2)*a3y);
  qA[bin][0]->Add(qx2y2y3,-2*pow(a2x,2)*a3x + 2*pow(a2y,2)*a3x  + 4*a2x*a2y*a3y);
  qA[bin][0]->Add(qy2y2y3,pow(a2y,2)*a3y    - pow(a2x,2)*a3y    - 2*a2x*a2y*a3x);
  
  qB[bin][0]->Add(qx2x2x3,pow(b2x,2)*b3x    - pow(b2y,2)*b3x    - 2*b2x*b2y*b3y);
  qB[bin][0]->Add(qx2x3y2,4*b2x*b2y*b3x     + 2*pow(b2x,2)*b3y  - 2*pow(b2y,2)*b3y);
  qB[bin][0]->Add(qx3y2y2,pow(b2y,2)*b3x    - pow(b2x,2)*b3x    + 2*b2x*b2y*b3y);
  qB[bin][0]->Add(qx2x2y3,2*b2x*b2y*b3x     + pow(b2x,2)*b3y    - pow(b2y,2)*b3y);
  qB[bin][0]->Add(qx2y2y3,-2*pow(b2x,2)*b3x + 2*pow(b2y,2)*b3x  + 4*b2x*b2y*b3y);
  qB[bin][0]->Add(qy2y2y3,pow(b2y,2)*b3y    - pow(b2x,2)*b3y    - 2*b2x*b2y*b3x);
  wnA[bin][0]->Add(qcnt3,wa2*wa2*wa3);
  wnB[bin][0]->Add(qcnt3,wb2*wb2*wb3);
  qBA[bin][0]->Fill(0.,pow(a2x,2)*a3x*pow(b2x,2)*b3x - pow(a2y,2)*a3x*pow(b2x,2)*b3x - 2*a2x*a2y*a3y*pow(b2x,2)*b3x + 4*a2x*a2y*a3x*b2x*b2y*b3x + 2*pow(a2x,2)*a3y*b2x*b2y*b3x - 
		    2*pow(a2y,2)*a3y*b2x*b2y*b3x - pow(a2x,2)*a3x*pow(b2y,2)*b3x + pow(a2y,2)*a3x*pow(b2y,2)*b3x + 2*a2x*a2y*a3y*pow(b2y,2)*b3x + 2*a2x*a2y*a3x*pow(b2x,2)*b3y + 
		    pow(a2x,2)*a3y*pow(b2x,2)*b3y - pow(a2y,2)*a3y*pow(b2x,2)*b3y - 2*pow(a2x,2)*a3x*b2x*b2y*b3y + 2*pow(a2y,2)*a3x*b2x*b2y*b3y + 4*a2x*a2y*a3y*b2x*b2y*b3y - 
		    2*a2x*a2y*a3x*pow(b2y,2)*b3y - pow(a2x,2)*a3y*pow(b2y,2)*b3y + pow(a2y,2)*a3y*pow(b2y,2)*b3y);
  qCA[bin][0]->Fill(0.,pow(a2x,2)*a3x*pow(c2x,2)*c3x - pow(a2y,2)*a3x*pow(c2x,2)*c3x - 2*a2x*a2y*a3y*pow(c2x,2)*c3x + 4*a2x*a2y*a3x*c2x*c2y*c3x + 2*pow(a2x,2)*a3y*c2x*c2y*c3x - 
		    2*pow(a2y,2)*a3y*c2x*c2y*c3x - pow(a2x,2)*a3x*pow(c2y,2)*c3x + pow(a2y,2)*a3x*pow(c2y,2)*c3x + 2*a2x*a2y*a3y*pow(c2y,2)*c3x + 2*a2x*a2y*a3x*pow(c2x,2)*c3y + 
		    pow(a2x,2)*a3y*pow(c2x,2)*c3y - pow(a2y,2)*a3y*pow(c2x,2)*c3y - 2*pow(a2x,2)*a3x*c2x*c2y*c3y + 2*pow(a2y,2)*a3x*c2x*c2y*c3y + 4*a2x*a2y*a3y*c2x*c2y*c3y - 
		    2*a2x*a2y*a3x*pow(c2y,2)*c3y - pow(a2x,2)*a3y*pow(c2y,2)*c3y + pow(a2y,2)*a3y*pow(c2y,2)*c3y);
  qCB[bin][0]->Fill(0.,pow(b2x,2)*b3x*pow(c2x,2)*c3x - pow(b2y,2)*b3x*pow(c2x,2)*c3x - 2*b2x*b2y*b3y*pow(c2x,2)*c3x + 4*b2x*b2y*b3x*c2x*c2y*c3x + 2*pow(b2x,2)*b3y*c2x*c2y*c3x - 
		    2*pow(b2y,2)*b3y*c2x*c2y*c3x - pow(b2x,2)*b3x*pow(c2y,2)*c3x + pow(b2y,2)*b3x*pow(c2y,2)*c3x + 2*b2x*b2y*b3y*pow(c2y,2)*c3x + 2*b2x*b2y*b3x*pow(c2x,2)*c3y + 
		    pow(b2x,2)*b3y*pow(c2x,2)*c3y - pow(b2y,2)*b3y*pow(c2x,2)*c3y - 2*pow(b2x,2)*b3x*c2x*c2y*c3y + 2*pow(b2y,2)*b3x*c2x*c2y*c3y + 4*b2x*b2y*b3y*c2x*c2y*c3y - 
		    2*b2x*b2y*b3x*pow(c2y,2)*c3y - pow(b2x,2)*b3y*pow(c2y,2)*c3y + pow(b2y,2)*b3y*pow(c2y,2)*c3y);
  qBAcnt[bin][0]->Fill(0.,wb2*wb2*wb3*wa2*wa2*wa3);
  qCAcnt[bin][0]->Fill(0.,wc2*wc2*wc3*wa2*wa2*wa3);
  qCBcnt[bin][0]->Fill(0.,wc2*wc2*wc3*wb2*wb2*wb3);

  int j=(int)(ran->Uniform(0,9.999))+1;
  
  qA[bin][j]->Add(qx2x2x3,pow(a2x,2)*a3x    - pow(a2y,2)*a3x    - 2*a2x*a2y*a3y);
  qA[bin][j]->Add(qx2x3y2,4*a2x*a2y*a3x     + 2*pow(a2x,2)*a3y  - 2*pow(a2y,2)*a3y);
  qA[bin][j]->Add(qx3y2y2,pow(a2y,2)*a3x    - pow(a2x,2)*a3x    + 2*a2x*a2y*a3y);
  qA[bin][j]->Add(qx2x2y3,2*a2x*a2y*a3x     + pow(a2x,2)*a3y    - pow(a2y,2)*a3y);
  qA[bin][j]->Add(qx2y2y3,-2*pow(a2x,2)*a3x + 2*pow(a2y,2)*a3x  + 4*a2x*a2y*a3y);
  qA[bin][j]->Add(qy2y2y3,pow(a2y,2)*a3y    - pow(a2x,2)*a3y    - 2*a2x*a2y*a3x);
  
  qB[bin][j]->Add(qx2x2x3,pow(b2x,2)*b3x    - pow(b2y,2)*b3x    - 2*b2x*b2y*b3y);
  qB[bin][j]->Add(qx2x3y2,4*b2x*b2y*b3x     + 2*pow(b2x,2)*b3y  - 2*pow(b2y,2)*b3y);
  qB[bin][j]->Add(qx3y2y2,pow(b2y,2)*b3x    - pow(b2x,2)*b3x    + 2*b2x*b2y*b3y);
  qB[bin][j]->Add(qx2x2y3,2*b2x*b2y*b3x     + pow(b2x,2)*b3y    - pow(b2y,2)*b3y);
  qB[bin][j]->Add(qx2y2y3,-2*pow(b2x,2)*b3x + 2*pow(b2y,2)*b3x  + 4*b2x*b2y*b3y);
  qB[bin][j]->Add(qy2y2y3,pow(b2y,2)*b3y    - pow(b2x,2)*b3y    - 2*b2x*b2y*b3x);
  wnA[bin][j]->Add(qcnt_,wa2*wa2*wa3);
  wnB[bin][j]->Add(qcnt_,wb2*wa2*wb3);
  qBA[bin][j]->Fill(0.,pow(a2x,2)*a3x*pow(b2x,2)*b3x - pow(a2y,2)*a3x*pow(b2x,2)*b3x - 2*a2x*a2y*a3y*pow(b2x,2)*b3x + 4*a2x*a2y*a3x*b2x*b2y*b3x + 2*pow(a2x,2)*a3y*b2x*b2y*b3x - 
		    2*pow(a2y,2)*a3y*b2x*b2y*b3x - pow(a2x,2)*a3x*pow(b2y,2)*b3x + pow(a2y,2)*a3x*pow(b2y,2)*b3x + 2*a2x*a2y*a3y*pow(b2y,2)*b3x + 2*a2x*a2y*a3x*pow(b2x,2)*b3y + 
		    pow(a2x,2)*a3y*pow(b2x,2)*b3y - pow(a2y,2)*a3y*pow(b2x,2)*b3y - 2*pow(a2x,2)*a3x*b2x*b2y*b3y + 2*pow(a2y,2)*a3x*b2x*b2y*b3y + 4*a2x*a2y*a3y*b2x*b2y*b3y - 
		    2*a2x*a2y*a3x*pow(b2y,2)*b3y - pow(a2x,2)*a3y*pow(b2y,2)*b3y + pow(a2y,2)*a3y*pow(b2y,2)*b3y);
  qCA[bin][j]->Fill(0.,pow(a2x,2)*a3x*pow(c2x,2)*c3x - pow(a2y,2)*a3x*pow(c2x,2)*c3x - 2*a2x*a2y*a3y*pow(c2x,2)*c3x + 4*a2x*a2y*a3x*c2x*c2y*c3x + 2*pow(a2x,2)*a3y*c2x*c2y*c3x - 
		    2*pow(a2y,2)*a3y*c2x*c2y*c3x - pow(a2x,2)*a3x*pow(c2y,2)*c3x + pow(a2y,2)*a3x*pow(c2y,2)*c3x + 2*a2x*a2y*a3y*pow(c2y,2)*c3x + 2*a2x*a2y*a3x*pow(c2x,2)*c3y + 
		    pow(a2x,2)*a3y*pow(c2x,2)*c3y - pow(a2y,2)*a3y*pow(c2x,2)*c3y - 2*pow(a2x,2)*a3x*c2x*c2y*c3y + 2*pow(a2y,2)*a3x*c2x*c2y*c3y + 4*a2x*a2y*a3y*c2x*c2y*c3y - 
		    2*a2x*a2y*a3x*pow(c2y,2)*c3y - pow(a2x,2)*a3y*pow(c2y,2)*c3y + pow(a2y,2)*a3y*pow(c2y,2)*c3y);
  qCB[bin][j]->Fill(0.,pow(b2x,2)*b3x*pow(c2x,2)*c3x - pow(b2y,2)*b3x*pow(c2x,2)*c3x - 2*b2x*b2y*b3y*pow(c2x,2)*c3x + 4*b2x*b2y*b3x*c2x*c2y*c3x + 2*pow(b2x,2)*b3y*c2x*c2y*c3x - 
		    2*pow(b2y,2)*b3y*c2x*c2y*c3x - pow(b2x,2)*b3x*pow(c2y,2)*c3x + pow(b2y,2)*b3x*pow(c2y,2)*c3x + 2*b2x*b2y*b3y*pow(c2y,2)*c3x + 2*b2x*b2y*b3x*pow(c2x,2)*c3y + 
		    pow(b2x,2)*b3y*pow(c2x,2)*c3y - pow(b2y,2)*b3y*pow(c2x,2)*c3y - 2*pow(b2x,2)*b3x*c2x*c2y*c3y + 2*pow(b2y,2)*b3x*c2x*c2y*c3y + 4*b2x*b2y*b3y*c2x*c2y*c3y - 
		    2*b2x*b2y*b3x*pow(c2y,2)*c3y - pow(b2x,2)*b3y*pow(c2y,2)*c3y + pow(b2y,2)*b3y*pow(c2y,2)*c3y);
  qBAcnt[bin][j]->Fill(0.,wb2*wb2*wb3*wa2*wa2*wa3);
  qCAcnt[bin][j]->Fill(0.,wc2*wc2*wc3*wa2*wa2*wa3);
  qCBcnt[bin][j]->Fill(0.,wc2*wc2*wc3*wb2*wb2*wb3);

}

void Fill_D2432ASUB3(int bin, TH2D * qxtrk2_, TH2D * qytrk2_, TH2D * qxtrk3_, TH2D * qytrk3_, TH2D * qcnt_, double * qx, double * qy, double * sumw){
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

  qx2x2x3->Reset();
  qx2x3y2->Reset();
  qx3y2y2->Reset();
  qx2x2y3->Reset();
  qx2y2y3->Reset();
  qy2y2y3->Reset();
  
  qx2x2x3->Add(qxtrk2_,1.);
  qx2x3y2->Add(qxtrk2_,1.);
  qx3y2y2->Add(qxtrk3_,1.);
  qx2x2y3->Add(qxtrk2_,1.);
  qx2y2y3->Add(qxtrk2_,1.);
  qy2y2y3->Add(qytrk2_,1.);
  
  qx2x2x3->Multiply(qxtrk2_);
  qx2x3y2->Multiply(qxtrk3_);
  qx3y2y2->Multiply(qytrk2_);
  qx2x2y3->Multiply(qxtrk2_);
  qx2y2y3->Multiply(qytrk2_);
  qy2y2y3->Multiply(qytrk2_);
  qx2x2x3->Multiply(qxtrk3_);
  qx2x3y2->Multiply(qytrk2_);
  qx3y2y2->Multiply(qytrk2_);
  qx2x2y3->Multiply(qytrk3_);
  qx2y2y3->Multiply(qytrk3_);
  qy2y2y3->Multiply(qytrk3_);

  qcnt3->Add(qcnt_,1.);
  qcnt3->Multiply(qcnt_);
  qcnt3->Multiply(qcnt_);
  
  qA[bin][0]->Add(qx2x2x3,pow(a2x,2)*a3x    - pow(a2y,2)*a3x    - 2*a2x*a2y*a3y);
  qA[bin][0]->Add(qx2x3y2,4*a2x*a2y*a3x     + 2*pow(a2x,2)*a3y  - 2*pow(a2y,2)*a3y);
  qA[bin][0]->Add(qx3y2y2,pow(a2y,2)*a3x    - pow(a2x,2)*a3x    + 2*a2x*a2y*a3y);
  qA[bin][0]->Add(qx2x2y3,2*a2x*a2y*a3x     + pow(a2x,2)*a3y    - pow(a2y,2)*a3y);
  qA[bin][0]->Add(qx2y2y3,-2*pow(a2x,2)*a3x + 2*pow(a2y,2)*a3x  + 4*a2x*a2y*a3y);
  qA[bin][0]->Add(qy2y2y3,pow(a2y,2)*a3y    - pow(a2x,2)*a3y    - 2*a2x*a2y*a3x);
  
  qB[bin][0]->Add(qx2x2x3,pow(b2x,2)*b3x    - pow(b2y,2)*b3x    - 2*b2x*b2y*b3y);
  qB[bin][0]->Add(qx2x3y2,4*b2x*b2y*b3x     + 2*pow(b2x,2)*b3y  - 2*pow(b2y,2)*b3y);
  qB[bin][0]->Add(qx3y2y2,pow(b2y,2)*b3x    - pow(b2x,2)*b3x    + 2*b2x*b2y*b3y);
  qB[bin][0]->Add(qx2x2y3,2*b2x*b2y*b3x     + pow(b2x,2)*b3y    - pow(b2y,2)*b3y);
  qB[bin][0]->Add(qx2y2y3,-2*pow(b2x,2)*b3x + 2*pow(b2y,2)*b3x  + 4*b2x*b2y*b3y);
  qB[bin][0]->Add(qy2y2y3,pow(b2y,2)*b3y    - pow(b2x,2)*b3y    - 2*b2x*b2y*b3x);
  wnA[bin][0]->Add(qcnt3,wa2*wa2*wa3);
  wnB[bin][0]->Add(qcnt3,wb2*wa2*wb3);
  qBA[bin][0]->Fill(0.,pow(a2x,2)*a3x*pow(b2x,2)*b3x - pow(a2y,2)*a3x*pow(b2x,2)*b3x - 2*a2x*a2y*a3y*pow(b2x,2)*b3x + 4*a2x*a2y*a3x*b2x*b2y*b3x + 2*pow(a2x,2)*a3y*b2x*b2y*b3x - 
		    2*pow(a2y,2)*a3y*b2x*b2y*b3x - pow(a2x,2)*a3x*pow(b2y,2)*b3x + pow(a2y,2)*a3x*pow(b2y,2)*b3x + 2*a2x*a2y*a3y*pow(b2y,2)*b3x + 2*a2x*a2y*a3x*pow(b2x,2)*b3y + 
		    pow(a2x,2)*a3y*pow(b2x,2)*b3y - pow(a2y,2)*a3y*pow(b2x,2)*b3y - 2*pow(a2x,2)*a3x*b2x*b2y*b3y + 2*pow(a2y,2)*a3x*b2x*b2y*b3y + 4*a2x*a2y*a3y*b2x*b2y*b3y - 
		    2*a2x*a2y*a3x*pow(b2y,2)*b3y - pow(a2x,2)*a3y*pow(b2y,2)*b3y + pow(a2y,2)*a3y*pow(b2y,2)*b3y);
  qCA[bin][0]->Fill(0.,pow(a2x,2)*a3x*pow(c2x,2)*c3x - pow(a2y,2)*a3x*pow(c2x,2)*c3x - 2*a2x*a2y*a3y*pow(c2x,2)*c3x + 4*a2x*a2y*a3x*c2x*c2y*c3x + 2*pow(a2x,2)*a3y*c2x*c2y*c3x - 
		    2*pow(a2y,2)*a3y*c2x*c2y*c3x - pow(a2x,2)*a3x*pow(c2y,2)*c3x + pow(a2y,2)*a3x*pow(c2y,2)*c3x + 2*a2x*a2y*a3y*pow(c2y,2)*c3x + 2*a2x*a2y*a3x*pow(c2x,2)*c3y + 
		    pow(a2x,2)*a3y*pow(c2x,2)*c3y - pow(a2y,2)*a3y*pow(c2x,2)*c3y - 2*pow(a2x,2)*a3x*c2x*c2y*c3y + 2*pow(a2y,2)*a3x*c2x*c2y*c3y + 4*a2x*a2y*a3y*c2x*c2y*c3y - 
		    2*a2x*a2y*a3x*pow(c2y,2)*c3y - pow(a2x,2)*a3y*pow(c2y,2)*c3y + pow(a2y,2)*a3y*pow(c2y,2)*c3y);
  qCB[bin][0]->Fill(0.,pow(b2x,2)*b3x*pow(c2x,2)*c3x - pow(b2y,2)*b3x*pow(c2x,2)*c3x - 2*b2x*b2y*b3y*pow(c2x,2)*c3x + 4*b2x*b2y*b3x*c2x*c2y*c3x + 2*pow(b2x,2)*b3y*c2x*c2y*c3x - 
		    2*pow(b2y,2)*b3y*c2x*c2y*c3x - pow(b2x,2)*b3x*pow(c2y,2)*c3x + pow(b2y,2)*b3x*pow(c2y,2)*c3x + 2*b2x*b2y*b3y*pow(c2y,2)*c3x + 2*b2x*b2y*b3x*pow(c2x,2)*c3y + 
		    pow(b2x,2)*b3y*pow(c2x,2)*c3y - pow(b2y,2)*b3y*pow(c2x,2)*c3y - 2*pow(b2x,2)*b3x*c2x*c2y*c3y + 2*pow(b2y,2)*b3x*c2x*c2y*c3y + 4*b2x*b2y*b3y*c2x*c2y*c3y - 
		    2*b2x*b2y*b3x*pow(c2y,2)*c3y - pow(b2x,2)*b3y*pow(c2y,2)*c3y + pow(b2y,2)*b3y*pow(c2y,2)*c3y);
  qBAcnt[bin][0]->Fill(0.,wb2*wb2*wb3*wa2*wa2*wa3);
  qCAcnt[bin][0]->Fill(0.,wc2*wc2*wc3*wa2*wa2*wa3);
  qCBcnt[bin][0]->Fill(0.,wc2*wc2*wc3*wb2*wb2*wb3);

  int j=(int)(ran->Uniform(0,9.999))+1;
  
  qA[bin][j]->Add(qx2x2x3,pow(a2x,2)*a3x    - pow(a2y,2)*a3x    - 2*a2x*a2y*a3y);
  qA[bin][j]->Add(qx2x3y2,4*a2x*a2y*a3x     + 2*pow(a2x,2)*a3y  - 2*pow(a2y,2)*a3y);
  qA[bin][j]->Add(qx3y2y2,pow(a2y,2)*a3x    - pow(a2x,2)*a3x    + 2*a2x*a2y*a3y);
  qA[bin][j]->Add(qx2x2y3,2*a2x*a2y*a3x     + pow(a2x,2)*a3y    - pow(a2y,2)*a3y);
  qA[bin][j]->Add(qx2y2y3,-2*pow(a2x,2)*a3x + 2*pow(a2y,2)*a3x  + 4*a2x*a2y*a3y);
  qA[bin][j]->Add(qy2y2y3,pow(a2y,2)*a3y    - pow(a2x,2)*a3y    - 2*a2x*a2y*a3x);
  
  qB[bin][j]->Add(qx2x2x3,pow(b2x,2)*b3x    - pow(b2y,2)*b3x    - 2*b2x*b2y*b3y);
  qB[bin][j]->Add(qx2x3y2,4*b2x*b2y*b3x     + 2*pow(b2x,2)*b3y  - 2*pow(b2y,2)*b3y);
  qB[bin][j]->Add(qx3y2y2,pow(b2y,2)*b3x    - pow(b2x,2)*b3x    + 2*b2x*b2y*b3y);
  qB[bin][j]->Add(qx2x2y3,2*b2x*b2y*b3x     + pow(b2x,2)*b3y    - pow(b2y,2)*b3y);
  qB[bin][j]->Add(qx2y2y3,-2*pow(b2x,2)*b3x + 2*pow(b2y,2)*b3x  + 4*b2x*b2y*b3y);
  qB[bin][j]->Add(qy2y2y3,pow(b2y,2)*b3y    - pow(b2x,2)*b3y    - 2*b2x*b2y*b3x);
  wnA[bin][j]->Add(qcnt_,wa2*wa2*wa3);
  wnB[bin][j]->Add(qcnt_,wb2*wa2*wb3);
  qBA[bin][j]->Fill(0.,pow(a2x,2)*a3x*pow(b2x,2)*b3x - pow(a2y,2)*a3x*pow(b2x,2)*b3x - 2*a2x*a2y*a3y*pow(b2x,2)*b3x + 4*a2x*a2y*a3x*b2x*b2y*b3x + 2*pow(a2x,2)*a3y*b2x*b2y*b3x - 
		    2*pow(a2y,2)*a3y*b2x*b2y*b3x - pow(a2x,2)*a3x*pow(b2y,2)*b3x + pow(a2y,2)*a3x*pow(b2y,2)*b3x + 2*a2x*a2y*a3y*pow(b2y,2)*b3x + 2*a2x*a2y*a3x*pow(b2x,2)*b3y + 
		    pow(a2x,2)*a3y*pow(b2x,2)*b3y - pow(a2y,2)*a3y*pow(b2x,2)*b3y - 2*pow(a2x,2)*a3x*b2x*b2y*b3y + 2*pow(a2y,2)*a3x*b2x*b2y*b3y + 4*a2x*a2y*a3y*b2x*b2y*b3y - 
		    2*a2x*a2y*a3x*pow(b2y,2)*b3y - pow(a2x,2)*a3y*pow(b2y,2)*b3y + pow(a2y,2)*a3y*pow(b2y,2)*b3y);
  qCA[bin][j]->Fill(0.,pow(a2x,2)*a3x*pow(c2x,2)*c3x - pow(a2y,2)*a3x*pow(c2x,2)*c3x - 2*a2x*a2y*a3y*pow(c2x,2)*c3x + 4*a2x*a2y*a3x*c2x*c2y*c3x + 2*pow(a2x,2)*a3y*c2x*c2y*c3x - 
		    2*pow(a2y,2)*a3y*c2x*c2y*c3x - pow(a2x,2)*a3x*pow(c2y,2)*c3x + pow(a2y,2)*a3x*pow(c2y,2)*c3x + 2*a2x*a2y*a3y*pow(c2y,2)*c3x + 2*a2x*a2y*a3x*pow(c2x,2)*c3y + 
		    pow(a2x,2)*a3y*pow(c2x,2)*c3y - pow(a2y,2)*a3y*pow(c2x,2)*c3y - 2*pow(a2x,2)*a3x*c2x*c2y*c3y + 2*pow(a2y,2)*a3x*c2x*c2y*c3y + 4*a2x*a2y*a3y*c2x*c2y*c3y - 
		    2*a2x*a2y*a3x*pow(c2y,2)*c3y - pow(a2x,2)*a3y*pow(c2y,2)*c3y + pow(a2y,2)*a3y*pow(c2y,2)*c3y);
  qCB[bin][j]->Fill(0.,pow(b2x,2)*b3x*pow(c2x,2)*c3x - pow(b2y,2)*b3x*pow(c2x,2)*c3x - 2*b2x*b2y*b3y*pow(c2x,2)*c3x + 4*b2x*b2y*b3x*c2x*c2y*c3x + 2*pow(b2x,2)*b3y*c2x*c2y*c3x - 
		    2*pow(b2y,2)*b3y*c2x*c2y*c3x - pow(b2x,2)*b3x*pow(c2y,2)*c3x + pow(b2y,2)*b3x*pow(c2y,2)*c3x + 2*b2x*b2y*b3y*pow(c2y,2)*c3x + 2*b2x*b2y*b3x*pow(c2x,2)*c3y + 
		    pow(b2x,2)*b3y*pow(c2x,2)*c3y - pow(b2y,2)*b3y*pow(c2x,2)*c3y - 2*pow(b2x,2)*b3x*c2x*c2y*c3y + 2*pow(b2y,2)*b3x*c2x*c2y*c3y + 4*b2x*b2y*b3y*c2x*c2y*c3y - 
		    2*b2x*b2y*b3x*pow(c2y,2)*c3y - pow(b2x,2)*b3y*pow(c2y,2)*c3y + pow(b2y,2)*b3y*pow(c2y,2)*c3y);
  qBAcnt[bin][j]->Fill(0.,wb2*wb2*wb3*wa2*wa2*wa3);
  qCAcnt[bin][j]->Fill(0.,wc2*wc2*wc3*wa2*wa2*wa3);
  qCBcnt[bin][j]->Fill(0.,wc2*wc2*wc3*wb2*wb2*wb3);

}
