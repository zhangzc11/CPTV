/*
  Usage:
  > root
  [0] .L Comp123.C+
  [1] Comp123()
*/
#include <string>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include <iostream>
#include "TStyle.h"
#include "math.h"
using namespace std;

void Comp123()
{
  gStyle->SetOptStat(0);


  string file[7] = {
    "MC.root",
    // 5 meter data set
    /*  
    "../../data/Sample/Distance/P12e_1.5MeV/H5m/EH1.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H5m/EH1.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H5m/EH2.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H5m/EH3.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H5m/EH3.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H5m/EH3.root",
    */
    // 2 meter data set
    "../../data/Sample/Distance/P12e_1.5MeV/H/EH1.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H/EH1.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H/EH2.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H/EH3.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H/EH3.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H/EH3.root",
  };

  TH1F * h1dDistVtx[7];
  TH1F * h1dDistBkg[7];
  TH1F * h1dDistAcc[7];
  TH1F * h1dAcc22[7];
  
  TH1::AddDirectory(kFALSE);

  // which histogram to add
  string nam[7] = {"MC","AD1","AD2","AD3","AD4","AD5","AD6"};
  string idx[7] = {"1","1","2","1","1","2","3"};
  int MkStyle[7] = {31,21,22,23,25,26,32};
  int MkColor[7] = {1,2,3,4,2,3,4};
  
  for( int ad=1; ad<=6; ad++ ) {
    TFile f( file[ad].c_str() );
    h1dDistVtx[ad] = (TH1F*)f.Get( ("h1dDistVtx_"+idx[ad]).c_str()  );
    h1dDistVtx[ad]->SetDirectory(0);
    h1dDistBkg[ad] = (TH1F*)f.Get( ("h1dDistBkg_"+idx[ad]).c_str()  );
    h1dDistBkg[ad]->SetDirectory(0);
    h1dDistAcc[ad] = (TH1F*)f.Get( ("h1dDistAcc_"+idx[ad]).c_str()  );
    h1dDistAcc[ad]->SetDirectory(0);
    h1dAcc22[ad]   = (TH1F*)f.Get( ("h1dAcc22_"+idx[ad]).c_str()    );
    h1dAcc22[ad]   ->SetDirectory(0);
    
    f.Close();
  }

  ///////////////////////////
  /// AD 1, 2, 3
  //  0 - AD1
  //  1 - AD2
  //  2 - AD3
  const int nbins = h1dDistAcc[1]->GetNbinsX();

  string SumName[3]   = { "AD1", "AD2", "AD3" };
  string SumPsName[3] = { "AD1.ps", "AD2.ps", "AD3.ps" };
  string EffSumName[3]   = { "AD1 Efficiency", "AD2 Efficiency", "AD3 Efficiency" };
  string NFFile[3] = { "../../data/Sample/Distance/P12e_1.5MeV/H/EH1.root",
		       "../../data/Sample/Distance/P12e_1.5MeV/H/EH1.root",
		       "../../data/Sample/Distance/P12e_1.5MeV/H/EH2.root" };
  TH1F* h1dVtx[3];
  TH1F* h1dBkg[3];  
  TH1F* h1dSum[3];
  TCanvas * cSum[3];
  
  /// File read and histogram read
  for( unsigned int b=0; b<3; b++ ) {
    TFile f( NFFile[b].c_str() );
    if( b!=1 ) {
      h1dVtx[b] = (TH1F*)f.Get( "h1dDistVtx_1"  );
      h1dVtx[b]->SetDirectory(0);
      h1dBkg[b] = (TH1F*)f.Get( "h1dDistBkg_1"  );
      h1dBkg[b]->SetDirectory(0);
      h1dSum[b] = (TH1F*)f.Get( "h1dDistAcc_1"  );
      h1dSum[b]->SetDirectory(0);
    } else {
      h1dVtx[b] = (TH1F*)f.Get( "h1dDistVtx_2"  );
      h1dVtx[b]->SetDirectory(0);
      h1dBkg[b] = (TH1F*)f.Get( "h1dDistBkg_2"  );
      h1dBkg[b]->SetDirectory(0);
      h1dSum[b] = (TH1F*)f.Get( "h1dDistAcc_2"  );
      h1dSum[b]->SetDirectory(0);
    }
    f.Close();
  }

  /// Distance distribution
  for( unsigned int b=0; b<3; b++ ) {

    cSum[b]   = new TCanvas( SumName[b].c_str(), SumName[b].c_str(), 0, 0, 500, 500);

    cSum[b]->SetMargin(0.15,0.15,0.1,0.1);
    cSum[b]->SetGrid();
    h1dSum[b]->Draw();
    h1dSum[b]->GetYaxis()->SetTitleOffset(1.6);
    h1dSum[b]->GetXaxis()->SetLabelSize(0.035);
    cSum[b]->Print( SumPsName[b].c_str() );
  }

  /////////////////////////////////////
  /// Efficiency curve
  //  const int nbins = h1dSum[1]->GetNbinsX();
  double effi   [3][nbins];
  double effiErr[3][nbins];
  double distance [nbins];
  double distErr  [nbins];
  
  for( int bn=1; bn<=nbins; bn++ ) {
    distance [bn-1] = h1dSum[1]->GetBinCenter(bn);
    distErr  [bn-1] = 0;
  }

  for( int b=0; b<3; b++ ) {
    cout<<"Start "<<EffSumName[b]<<endl; 
    
    double V = h1dVtx[b]->Integral(1,100);
    double B = h1dBkg[b]->Integral(1,100);

    for( int bn=1; bn<=nbins; bn++ ) {

      double VCut = h1dVtx[b]->Integral(1,bn);
      double BCut = h1dBkg[b]->Integral(1,bn);

      double pV = VCut/V;
      double reVCut = sqrt( 1/V * pV * (1-pV) );

      double reS = 0.0018;

      effi[b][bn-1]    = (VCut - BCut)/(V - B);
      effiErr[b][bn-1] = effi[b][bn-1] * sqrt( pow( V/(VCut-BCut)* reVCut, 2) +
					       pow( (-BCut/(VCut-BCut) + B/(V-B))* reS, 2) );
      //cout<< V<<" "<<B<<" "<<VCut<<" "<<BCut<<endl;
      //cout<< V/(VCut-BCut)* reVCut <<" = "<<V/(VCut-BCut) <<" "<< reVCut<<endl;
      //cout<< (-BCut/(VCut-BCut) + B/(V-B))* reS <<" = "<<(-BCut/(VCut-BCut) + B/(V-B))<<" "<<reS<<" "<<-BCut/(VCut-BCut)<<" "<<B/(V-B)<<endl;

      if( bn == 25 ) {
	cout<< effi[b][bn-1] <<"+/-"<< effiErr[b][bn-1]<<endl;
	cout<< "==========" <<endl;
      }
    }
  }

  TCanvas *cEffiSum = new TCanvas( "EffiSum", "EffiSum" );
  cEffiSum->SetMargin(0.15,0.15,0.1,0.1);
  TMultiGraph *mg = new TMultiGraph();
  TLegend*  lEffiSum = new TLegend(0.5,0.5,0.7,0.8);
  TGraphErrors *gEffiSum[3];

  for( int b=0; b<3; b++ ) {
    gEffiSum[b] = new TGraphErrors( nbins, distance, effi[b], distErr, effiErr[b] );
    gEffiSum[b] ->SetLineStyle(b);
    gEffiSum[b] ->SetMarkerStyle(20);
    gEffiSum[b] ->SetMarkerColor(2+b);
    gEffiSum[b] ->SetMarkerSize(0.5);
    mg->Add(gEffiSum[b],"lp");
    lEffiSum->AddEntry( gEffiSum[b], EffSumName[b].c_str(), "lp" );
  }
  
  mg->Draw("A");
  lEffiSum->Draw();
  mg->GetXaxis()->SetTitle("Distance [mm]");
  mg->GetYaxis()->SetTitle("Efficiency");
  mg->GetYaxis()->SetTitleOffset(1.6);
  mg->GetXaxis()->SetLabelSize(0.035);
  
  cEffiSum->Print( "EffiSum.ps" );

  /////////////////////////
  /// DiffSum
  double DiffSum [2][nbins];
  double DiffSumE[2][nbins];

  for( int bn=1; bn<=nbins; bn++ ) {
    /// AD 1 and 2
    double a = effi[0][bn-1];
    double b = effi[1][bn-1];
    double da= effiErr[0][bn-1];
    double db= effiErr[1][bn-1];
    
    double D = (b-a)/(a+b);
    double dD= 2/((a+b)*(a+b)) * sqrt((a*db*a*db + b*da*b*da));
 
    DiffSum [0][bn-1] = D;
    DiffSumE[0][bn-1] = dD;

    /// AD 1 and 3
    a = effi[0][bn-1];
    b = effi[2][bn-1];
    da= effiErr[0][bn-1];
    db= effiErr[2][bn-1];

    D = (b-a)/(a+b);
    dD= 2/((a+b)*(a+b)) * sqrt((a*db*a*db + b*da*b*da));

    DiffSum [1][bn-1] = D;
    DiffSumE[1][bn-1] = dD;
  }

  TCanvas *cDiffSum = new TCanvas( "DiffSum", "DiffSum" );
  cDiffSum->SetMargin(0.15,0.15,0.1,0.1);
  TMultiGraph *mgDiff = new TMultiGraph();
  TLegend*  lDiffSum = new TLegend(0.5,0.5,0.7,0.8);
  TGraphErrors *gDiffSum[2];

  // AD1 and AD2 difference
  gDiffSum[0] = new TGraphErrors( nbins-2, distance, DiffSum[0], distErr, DiffSumE[0] );
  gDiffSum[0] ->SetLineStyle(20);
  gDiffSum[0] ->SetLineColor(kBlue);
  gDiffSum[0] ->SetMarkerStyle(20);
  gDiffSum[0] ->SetMarkerSize(0.5);
  gDiffSum[0] ->SetMarkerColor(kBlue);
  mgDiff->Add(gDiffSum[0],"lp");
  lDiffSum->AddEntry( gDiffSum[0], "AD2, AD1 acceptance difference", "lp" );

  // AD1 and AD2 difference
  gDiffSum[1] = new TGraphErrors( nbins-2, distance, DiffSum[1], distErr, DiffSumE[1] );
  gDiffSum[1] ->SetLineStyle(20);
  gDiffSum[1] ->SetLineColor(kRed);
  gDiffSum[1] ->SetMarkerStyle(20);
  gDiffSum[1] ->SetMarkerSize(0.5);
  gDiffSum[1] ->SetMarkerColor(kRed);
  mgDiff->Add(gDiffSum[1],"lp");
  lDiffSum->AddEntry( gDiffSum[1], "AD3, AD1 acceptance difference", "lp" );
  

  mgDiff->Draw("A");
  lDiffSum->Draw();
  mgDiff->GetXaxis()->SetTitle("Distance [mm]");
  mgDiff->GetYaxis()->SetTitle("Difference");
  mgDiff->GetYaxis()->SetTitleOffset(1.6);
  mgDiff->GetXaxis()->SetLabelSize(0.035);

  cDiffSum->Print( "DiffSum.ps" );

}

