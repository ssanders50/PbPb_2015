void TestReading(string inlist="inlist.dat") {
  FILE *  flist;
  flist = fopen(inlist.data(),"r");
  char buf[250];
  int evcnt=0;
  TFile * tfin;
  TTree * tree;
  while(fgets(buf,250,flist)!=NULL) {
    buf[strlen(buf)-1]=0;
    string inFile=buf;
    cout<<inFile<<endl;
    tfin    = TFile::Open(buf);
    if(tfin==NULL) continue;
    cout<<tfin<<endl;
    if(tfin->IsZombie())                 {
      cout<<"ZOMBIE:    " <<inFile.data()<<endl; 
    //  continue;
     }
    tree = (TTree * ) tfin->Get("vnanalyzer/tree");
    evcnt+=tree->GetEntries();
    cout<<evcnt<<"\t"<<tree->GetEntries()<<"\t"<<inFile.data()<<endl;
    tfin->Close();

  }
}
