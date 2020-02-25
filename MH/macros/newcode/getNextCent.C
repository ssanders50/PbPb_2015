#ifndef GETNEXTCENT
#define GETNEXTCENT
const  int ncent = 13;
const  int centbins[]={0,5,10,15,20,25,30,35,40,50,60,70,80,100};
string getNextCent(int mincent,int maxcent, int & ccount, double & avcent, int & centminval, int & centmaxval){
  int imin = -1;
  int imax = -1;
  for(int i = 0; i<ncent; i++) {
    if(mincent==centbins[i]) imin=i;
    if(maxcent==centbins[i]) imax=i;
  }
  centminval = centbins[imin+ccount];
  centmaxval = centbins[imin+ccount+1];
  string cbin = to_string(centbins[imin+ccount])+"_"+to_string(centbins[imin+ccount+1]);
  avcent = (centbins[imin+ccount] + centbins[imin+ccount+1])/2.;
  if(imin+ccount+1>imax) cbin="stop";
  ++ccount;
  return cbin;
}
#endif
