/*
  Ugly - > Awesome
*/

#include "Table.h"
#include <string>
#include <iostream>
#include "TTree.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TAxis.h"
#include <stdlib.h>
#include <map>
using namespace std;

void DailyRate()
{
  /// Write it to a TTree readable Format
  string DBFile = "RunInfo.txt";
  Table RunInfo(DBFile);

  const int Max = RunInfo.NRows;
  map<unsigned int, double> Rate[6];
  map<unsigned int, double> RateErr[6];

  for( int row=0; row<Max; row++ )  {
    int Site = atoi( RunInfo.Columns["Site"][row].c_str() );
    int Run  = atoi( RunInfo.Columns["Run"][row].c_str() );
    if( Run < 21221 ) continue;
    unsigned int start, stop, mid;
    double up, low, fulltime, veto;
    
    // EH1
    if( Site==1 )  {      
      start      = atoi( RunInfo.Columns["StartSec"][row].c_str() );
      stop       = atoi( RunInfo.Columns["StopSec"][row].c_str() );
      mid = (start+stop)/2;

      /// AD 1
      up         = atof( RunInfo.Columns["NSgUp1"][row].c_str() );
      low        = atof( RunInfo.Columns["NSgLw1"][row].c_str() );
      fulltime   = atof( RunInfo.Columns["FullTime"][row].c_str() );
      veto       = atof( RunInfo.Columns["Veto1"][row].c_str() );
      Rate[0].insert   ( pair<double,double>(mid, (up+low)/2/(fulltime-veto)) );
      RateErr[0].insert( pair<double,double>(mid, sqrt((up+low)/2)/(fulltime-veto)) );      
      
      /// AD 2
      up         = atof( RunInfo.Columns["NSgUp2"][row].c_str() );
      low        = atof( RunInfo.Columns["NSgLw2"][row].c_str() );
      fulltime   = atof( RunInfo.Columns["FullTime"][row].c_str() );
      veto       = atof( RunInfo.Columns["Veto2"][row].c_str() );
      Rate[1].insert   ( pair<double,double>(mid, (up+low)/2/(fulltime-veto)) );
      RateErr[1].insert( pair<double,double>(mid, sqrt((up+low)/2)/(fulltime-veto)) );
    }

    // EH2
    if( Site==2 )  {
      start      = atoi( RunInfo.Columns["StartSec"][row].c_str() );
      stop       = atoi( RunInfo.Columns["StopSec"][row].c_str() );
      mid = (start+stop)/2;

      /// AD 1
      up         = atof( RunInfo.Columns["NSgUp1"][row].c_str() );
      low        = atof( RunInfo.Columns["NSgLw1"][row].c_str() );
      fulltime   = atof( RunInfo.Columns["FullTime"][row].c_str() );
      veto       = atof( RunInfo.Columns["Veto1"][row].c_str() );
      Rate[2].insert   ( pair<double,double>(mid, (up+low)/2/(fulltime-veto)) );
      RateErr[2].insert( pair<double,double>(mid, sqrt((up+low)/2)/(fulltime-veto)) );
    }
    
    /// EH3 
    if( Site==4 )  {
      start      = atoi( RunInfo.Columns["StartSec"][row].c_str() );
      stop       = atoi( RunInfo.Columns["StopSec"][row].c_str() );
      mid = (start+stop)/2;

      /// AD 1
      up         = atof( RunInfo.Columns["NSgUp1"][row].c_str() );
      low        = atof( RunInfo.Columns["NSgLw1"][row].c_str() );
      fulltime   = atof( RunInfo.Columns["FullTime"][row].c_str() );
      veto       = atof( RunInfo.Columns["Veto1"][row].c_str() );
      Rate[3].insert   ( pair<double,double>(mid, (up+low)/2/(fulltime-veto)) );
      RateErr[3].insert( pair<double,double>(mid, sqrt((up+low)/2)/(fulltime-veto)) );

      /// AD 2
      up         = atof( RunInfo.Columns["NSgUp2"][row].c_str() );
      low        = atof( RunInfo.Columns["NSgLw2"][row].c_str() );
      fulltime   = atof( RunInfo.Columns["FullTime"][row].c_str() );
      veto       = atof( RunInfo.Columns["Veto2"][row].c_str() );
      Rate[4].insert   ( pair<double,double>(mid, (up+low)/2/(fulltime-veto)) );
      RateErr[4].insert( pair<double,double>(mid, sqrt((up+low)/2)/(fulltime-veto)) );

      /// AD 3
      up         = atof( RunInfo.Columns["NSgUp3"][row].c_str() );
      low        = atof( RunInfo.Columns["NSgLw3"][row].c_str() );
      fulltime   = atof( RunInfo.Columns["FullTime"][row].c_str() );
      veto       = atof( RunInfo.Columns["Veto3"][row].c_str() );
      Rate[5].insert   ( pair<double,double>(mid, (up+low)/2/(fulltime-veto)) );
      RateErr[5].insert( pair<double,double>(mid, sqrt((up+low)/2)/(fulltime-veto)) );
    }

  }

  /*
  map<unsigned int, double>::iterator it;
  for ( it=Rate[0].begin(); it!=Rate[0].end(); it++ )  {
    unsigned int time = it->first;
    cout<<Rate[0][time]<<"+/-"<<RateErr[0][time]<<endl;
  }
  */

  TGraphErrors* ge[6];

  for( int AdNo=0; AdNo<6; AdNo++ )  {
    int n = Rate[AdNo].size();
    double time[n];
    double timeE[n];
    double gRate[n];
    double gRateE[n];

    map<unsigned int, double>::iterator it;
    int ct=0;
    for ( it=Rate[AdNo].begin(); it!=Rate[AdNo].end(); it++ )  {
      unsigned int mid = it->first;
      time[ct] = mid;
      timeE[ct] = 0;
      gRate[ct] = Rate[AdNo][mid];
      gRateE[ct] = RateErr[AdNo][mid];
      ct++;
    }

    ge[AdNo] = new TGraphErrors( n, time, gRate, timeE, gRateE);
  }

  /* Plot them */

  /// EH1
  TMultiGraph *mgEH1 = new TMultiGraph();
  
  TCanvas *cEH1 = new TCanvas;
  ge[0]->SetLineColor(2);
  ge[1]->SetLineColor(4);
  
  TLegend * legEH1 = new TLegend(0.5,0.7,0.8,0.9);
  legEH1->AddEntry( ge[0],"EH1-AD1","lep" );
  legEH1->AddEntry( ge[1],"EH1-AD2","lep" );

  mgEH1->Add( ge[0] );
  mgEH1->Add( ge[1] );
  mgEH1->Draw("ALP");
  mgEH1->GetXaxis()->SetTimeDisplay(1);
  mgEH1->GetXaxis()->SetTitle("Date");
  mgEH1->GetYaxis()->SetTitle("Singles Rate [Hz]");

  legEH1->Draw();
  cEH1->Print("Daily.EH1.ps");
  

  /// EH2
  TMultiGraph *mgEH2 = new TMultiGraph();

  TCanvas *cEH2 = new TCanvas;
  ge[2]->SetLineColor(2);

  TLegend * legEH2 = new TLegend(0.5,0.7,0.8,0.9);
  legEH2->AddEntry( ge[2],"EH2-AD1","lep" );

  mgEH2->Add( ge[2] );
  mgEH2->Draw("ALP");
  mgEH2->GetXaxis()->SetTimeDisplay(1);
  mgEH2->GetXaxis()->SetTitle("Date");
  mgEH2->GetYaxis()->SetTitle("Singles Rate [Hz]");

  legEH2->Draw();
  cEH2->Print("Daily.EH2.ps");
  

  /// EH3
  TMultiGraph *mgEH3 = new TMultiGraph();

  TCanvas *cEH3 = new TCanvas;
  ge[3]->SetLineColor(2);
  ge[4]->SetLineColor(4);
  ge[5]->SetLineColor(6);

  TLegend * legEH3 = new TLegend(0.5,0.7,0.8,0.9);
  legEH3->AddEntry( ge[3],"EH3-AD1","lep" );
  legEH3->AddEntry( ge[4],"EH3-AD2","lep" );
  legEH3->AddEntry( ge[5],"EH3-AD3","lep" );

  mgEH3->Add( ge[3] );
  mgEH3->Add( ge[4] );
  mgEH3->Add( ge[5] );
  mgEH3->Draw("ALP");
  mgEH3->GetXaxis()->SetTimeDisplay(1);
  mgEH3->GetXaxis()->SetTitle("Date");
  mgEH3->GetYaxis()->SetTitle("Singles Rate [Hz]");

  legEH3->Draw();
  cEH3->Print("Daily.EH3.ps");

}
