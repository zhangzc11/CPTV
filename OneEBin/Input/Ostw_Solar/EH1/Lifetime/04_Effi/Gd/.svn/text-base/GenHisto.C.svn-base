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
  string BaseCuts = "Fold==2 && E[1]>1.5 && E[1]<3 && TrigSec[1]-TrigSec[0]+(TrigNano[1]-TrigNano[0])*1e-9>1e-6";

  for( int ad=1; ad<=NAd; ad++) {
    string det = " && Det=="+i2a(ad);
    string Cuts = BaseCuts + det;

    string FileName = "EH"+i2a(site)+"_AD"+i2a(ad)+".root";       /* "EH1_AD1.root" */
    cout<<"Generating "<<FileName<<" ... "<<endl;

    TFile* f = new TFile( FileName.c_str(), "recreate" );

    TH1F h("h","Capture time in the GdLS region",200,0,1000e-6);       
    Event.Project("h", Expr.c_str(), Cuts.c_str());
    h.GetXaxis()->SetTitle("Capture time [s]");
    h.GetYaxis()->SetTitle("Entries/5E-6s");

    TH1F h2("h2","h2",80,0,400e-6);
    Event.Project("h2", Expr.c_str(), Cuts.c_str());


    h.Write();
    h2.Write();
    f->Close();
  }

}
