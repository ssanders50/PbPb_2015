#ifndef DEBUG
#define DEBUG
bool debug = false;
#endif
bool epselection(string anal, string side, double etamin, bool threesub, bool decor, int & A, int & B, int & C){
  bool isgood = false;
  int ieta = (int) ( (etamin+2.4)/0.4 + 0.01 );
  A = -1;
  B = -1;
  C = -1;
  if(debug) cout<<"epselection: "<<anal<<"\t"<<side<<"\t"<<ieta<<endl;
  //+++ N1
  if(anal.find("N1") != std::string::npos) {
    if(side.find("+") != std::string::npos) {
      A = HFp1f;
      B = HFm1f;
      if(!decor) {
	C = trackm110;
      } else {
	C = trackmid1 + ieta;
      }
    } else {
      A = HFm1f;
      B = HFp1f;
      if(!decor) {
	C = trackp110;
      } else {
	C = trackmid1 + ieta;
      }
    }
  }

  //+++ N2
  if(anal.find("N2") != std::string::npos) {
    if(side.find("+") != std::string::npos) {
      A = HFp2;
      B = HFm2;
      if(!decor) {
	C = trackmid2;
      } else {
	C = trackm222 + ieta;
      }
    } else {
      A = HFm2;
      B = HFp2;
      if(!decor) {
	C = trackmid2;
      } else {
	C = trackm222 + ieta;
      }
    }
  }
  //+++ N3
  if(anal.find("N3") != std::string::npos) {
    if(side.find("+") != std::string::npos) {
      A = HFp3;
      B = HFm3;
      if(!decor) {
	C = trackmid3;
      } else {
	C = trackm322 + ieta;
      }
    } else {
      A = HFm3;
      B = HFp3;
      if(!decor) {
	C = trackmid3;
      } else {
	C = trackm322 + ieta;
      }
    }
  }
  //+++ N4
  if(anal.find("N4") != std::string::npos) {
    if(side.find("+") != std::string::npos) {
      A = HFp4;
      B = HFm4;
      if(!decor) {
	C = trackmid4;
      } else {
	C = trackm422 + ieta;
      }
    } else {
      A = HFm4;
      B = HFp4;
      if(!decor) {
	C = trackmid4;
      } else {
	C = trackm422 + ieta;
      }
    }
  }
  //+++ N5
  if(anal.find("N5") != std::string::npos) {
    if(side.find("+") != std::string::npos) {
      A = HFp5;
      B = HFm5;
      if(!decor) {
	C = trackmid5;
      } else {
	C = trackm522 + ieta;
      }
    } else {
      A = HFm5;
      B = HFp5;
      if(!decor) {
	C = trackmid5;
      } else {
	C = trackm522 + ieta;
      }
    }
  }
  //+++ N6
  if(anal.find("N6") != std::string::npos) {
    if(side.find("+") != std::string::npos) {
      A = HFp6;
      B = HFm6;
      if(!decor) {
	C = trackmid6;
      } else {
	C = trackm622 + ieta;
      }
    } else {
      A = HFm6;
      B = HFp6;
      if(!decor) {
	C = trackmid6;
      } else {
	C = trackm622 + ieta;
      }
    }
  }
  //+++ N7
  if(anal.find("N7") != std::string::npos) {
    if(side.find("+") != std::string::npos) {
      A = HFp7;
      B = HFm7;
      if(!decor) {
	C = trackmid7;
      } else {
	C = trackm722 + ieta;
      }
    } else {
      A = HFm7;
      B = HFp7;
      if(!decor) {
	C = trackmid7;
      } else {
	C = trackm722 + ieta;
      }
    }
  }
  if(debug) {
    cout<<"A: "<<A<<endl;
    cout<<"B: "<<B<<endl;
    cout<<"C: "<<C<<endl;
  }
  if(A>0 && B>0 && C>0) isgood = true;
  return isgood;
}
