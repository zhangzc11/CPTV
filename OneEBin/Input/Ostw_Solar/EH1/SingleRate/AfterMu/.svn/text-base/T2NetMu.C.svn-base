#include "Table.h"
#include <string>
#include <iostream>
#include "TChain.h"
#include "TH1F.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TAxis.h"
#include <stdlib.h>
#include <map>
using namespace std;

void T2NetMu()
{
  int StudySite = 1;

  string DBFile = "/home/dayabay/depot/data/TWin/11_P12e_AdSimple_OWSNhit15_Tc400us_1.5MeV/H/RunInfo.txt";
  Table RunInfo(DBFile);

  const int Max = RunInfo.NRows;

  double total_netMu = 0;
  double total_livetime = 0;
  double rate = 0;
  double rate_E = 0;

  for( int row=0; row<Max; row++ ) {

    int Site = atoi( RunInfo.Columns["Site"][row].c_str() );
    int Run  = atoi( RunInfo.Columns["Run"][row].c_str() );

    if( Run < 21221 ) continue;
    double fulltime, veto;
    double netMu;
    // EH1 and AD1 only
    if( Site==StudySite ) {
      fulltime   = atof( RunInfo.Columns["FullTime"][row].c_str() );
      veto       = atof( RunInfo.Columns["Veto1"][row].c_str() );
      netMu      = atof( RunInfo.Columns["NNet1"][row].c_str() );
      
      total_livetime += (fulltime - veto);
      total_netMu += netMu;      
    }
  }
  rate = total_netMu/total_livetime;
  rate_E = rate/ sqrt(total_netMu);

  cout<<"TotalMu: "<<total_netMu <<"\t"<<"Livetime: "<<total_livetime<<"\t"<<"Rate ="<< rate <<"+/-"<< rate_E <<endl;


  TChain Event("Event");
  if( StudySite==1 ) {
    Event.Add("/home/dayabay/depot/data/TWin/11_P12e_AdSimple_OWSNhit15_Tc400us_1.5MeV/H/EH1/*.TWin.root");
  }

  if( StudySite==4 ) {
    Event.Add("/home/dayabay/depot/data/TWin/11_P12e_AdSimple_OWSNhit15_Tc400us_1.5MeV/H/EH3/*.TWin.root");
  }
    
  double low [6] = { 0, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1 };
  double high[6] = {    1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1 };
  string cuts[6] = { "T2PrevNetMu>0    && T2PrevNetMu<=1e-5   && Det==1",
		     "T2PrevNetMu>1e-5 && T2PrevNetMu<=1e-4   && Det==1",
		     "T2PrevNetMu>1e-4 && T2PrevNetMu<=1e-3   && Det==1",
		     "T2PrevNetMu>1e-3 && T2PrevNetMu<=1e-2   && Det==1",
		     "T2PrevNetMu>1e-2 && T2PrevNetMu<=1e-1   && Det==1",
		     "T2PrevNetMu>1e-1 && T2PrevNetMu<=1      && Det==1" };

  double aviT,   entries;
  double aviT_E, entries_E;
  double singleR, singleR_E;
  for( int om = 0; om<6; om++ ) {

    aviT   = ( exp(-rate*low[om]) - exp(-rate*high[om]) ) * total_livetime;
    aviT_E = rate_E * sqrt( pow(exp(-rate*low[om])*low[om],2) + pow(exp(-rate*high[om])*high[om], 2)  ) * total_livetime;
    cout<<aviT_E<< " " <<aviT_E/aviT<<endl;

    entries   = Event.Draw("D2First", cuts[om].c_str() );  /* D2First will be plotted twice for 2-fold events ... */
    entries_E = sqrt(entries);
    cout<<entries_E<<endl;
    
    singleR   = entries/aviT;
    singleR_E = singleR * sqrt( pow(aviT_E/aviT,2) + pow(entries_E/entries,2) );
    cout<<singleR_E<<endl;

    cout<<entries <<"\t"<< aviT <<"\t"<< entries/aviT <<endl;
    cout<<"Singles Rate "<<singleR<<"+/-"<<singleR_E<<endl; 

  }

}
