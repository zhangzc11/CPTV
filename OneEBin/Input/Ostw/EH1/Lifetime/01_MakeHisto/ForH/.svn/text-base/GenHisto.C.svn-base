/*
  root[0] .L GenHisto.C+
  root[1] GenHisto( datalist, site )
*/

#include "TChain.h"
#include "TFile.h"
#include "TH1F.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

string i2a(int intValue) {

  ostringstream oss (ostringstream::out);
  oss <<intValue;
  string strRetVal=oss.str();
  return(strRetVal);
}

////////////////////////////////
void GenHisto( char* list, int site )
{
  TChain Event("Event");
  ifstream inlist( list );
  string line;
  while( getline( inlist, line ) ) {
    Event.Add( line.c_str() );
  }


  int NAd=0;
  switch (site) {
  case 0:  /* MC */
    NAd = 1;
    break;
  case 1:
    NAd = 2;
    break;
  case 2:
    NAd = 1;
    break;
  case 3:
    NAd = 3;
    break;
  default:
    break;
  }

  string Expr = "TrigSec[1]-TrigSec[0]+(TrigNano[1]-TrigNano[0])*1e-9";
  string BaseCuts = "(X[0]*X[0]+Y[0]*Y[0]>2800e3) && Fold==2 && E[0]<12 && E[0]>3.5 && E[1]>1.8 && E[1]<2.8";

  for( int ad=1; ad<=NAd; ad++) {
    string det = " && Det=="+i2a(ad);
    string Cuts = BaseCuts + det;

    string FileName = "EH"+i2a(site)+"_AD"+i2a(ad)+".root";       /* "EH1_AD1.root" */
    cout<<"Generating "<<FileName<<" ... "<<endl;

    TFile* f = new TFile( FileName.c_str(), "recreate" );
    TH1F h("h","h",500,0,1500e-6);

    Event.Project("h", Expr.c_str(), Cuts.c_str());

    h.Write();
    f->Close();
  }

}
