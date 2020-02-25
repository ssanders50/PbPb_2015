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
