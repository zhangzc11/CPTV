/*
  Usage:
  > root
  [0] .L Comp.C+
  [1] Comp()
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

void Comp()
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

  //////////////////////////////
  // Compare DistVtx
  TCanvas * cDistVtx[7];
  string nDistVtx = "DistVtx";
  for( int ad=1; ad<=6; ad++ ) {

    cDistVtx[ad] = new TCanvas( (nDistVtx+nam[ad]).c_str(), (nDistVtx+nam[ad]).c_str(), 0, 0, 500, 500);
    cDistVtx[ad]->SetMargin(0.15,0.15,0.1,0.1);
    h1dDistVtx[ad]->Draw("");
    h1dDistVtx[ad]->GetYaxis()->SetTitleOffset(1.6);
    h1dDistVtx[ad]->GetXaxis()->SetLabelSize(0.035);
    cDistVtx[ad]->Print( (nDistVtx+nam[ad]+".ps").c_str() );
    
  }

  //////////////////////////////
  // Compare DistBkg
  TCanvas * cDistBkg[7];
  string nDistBkg = "DistBkg";
  for( int ad=1; ad<=6; ad++ ) {

    cDistBkg[ad] = new TCanvas( (nDistBkg+nam[ad]).c_str(), (nDistBkg+nam[ad]).c_str(), 0, 0, 500, 500);
    cDistBkg[ad]->SetMargin(0.15,0.15,0.1,0.1);
    h1dDistBkg[ad]->Draw("");
    h1dDistBkg[ad]->GetYaxis()->SetTitleOffset(1.6);
    h1dDistBkg[ad]->GetXaxis()->SetLabelSize(0.035);
    cDistBkg[ad]->Print( (nDistBkg+nam[ad]+".ps").c_str() );

  }

  //////////////////////////////
  // Compare DistAcc
  TCanvas * cDistAcc[7];
  string nDistAcc = "DistAcc";
  for( int ad=1; ad<=6; ad++ ) {

    cDistAcc[ad] = new TCanvas( (nDistAcc+nam[ad]).c_str(), (nDistAcc+nam[ad]).c_str(), 0, 0, 500, 500);
    cDistAcc[ad]->SetMargin(0.15,0.15,0.1,0.1);
    h1dDistAcc[ad]->Draw("");
    h1dDistAcc[ad]->GetYaxis()->SetTitleOffset(1.6);
    h1dDistAcc[ad]->GetXaxis()->SetLabelSize(0.035);
    cDistAcc[ad]->SetGrid();
    cDistAcc[ad]->Print( (nDistAcc+nam[ad]+".ps").c_str() );

  }

  
  //////////////////////////////
  // Compare Acc22
  TCanvas * cAcc22[7];
  string nAcc22 = "Acc22";
  for( int ad=1; ad<=6; ad++ ) {

    cAcc22[ad] = new TCanvas( (nAcc22+nam[ad]).c_str(), (nAcc22+nam[ad]).c_str(), 0, 0, 500, 500);
    cAcc22[ad]->SetMargin(0.15,0.15,0.1,0.1);
    h1dAcc22[ad]->Draw("");
    h1dAcc22[ad]->GetYaxis()->SetTitleOffset(1.6);
    h1dAcc22[ad]->GetXaxis()->SetLabelSize(0.035);
    cAcc22[ad]->SetGrid();
    cAcc22[ad]->Print( (nAcc22+nam[ad]+".ps").c_str() );

  }
  
  //////////////////////////////
  // Compare DistAcc
  string nDistAccSum = "DistAccSum";
  TCanvas * cDistAccSum = new TCanvas( nDistAccSum.c_str(), nDistAccSum.c_str(), 0, 0, 600, 500);
  cDistAccSum->SetMargin(0.15,0.15,0.1,0.1);
  cDistAccSum->SetGrid();
  TLegend*  lDistAccSum = new TLegend(0.5,0.6,0.68,0.8);
  h1dDistAcc[1]->DrawNormalized("p");
  h1dDistAcc[1]->GetYaxis()->SetTitleOffset(1.6);
  h1dDistAcc[1]->GetXaxis()->SetLabelSize(0.035);

  for( int ad=1; ad<=3; ad++ ) {

    h1dDistAcc[ad]->SetMarkerStyle( MkStyle[ad] );
    h1dDistAcc[ad]->SetMarkerSize( 0.7 );
    h1dDistAcc[ad]->SetMarkerColor( MkColor[ad] );
    h1dDistAcc[ad]->DrawNormalized("samep");
    h1dDistAcc[ad]->GetYaxis()->SetTitleOffset(1.6);
    h1dDistAcc[ad]->GetXaxis()->SetLabelSize(0.035);
    lDistAccSum->AddEntry( h1dDistAcc[ad], nam[ad].c_str() );
  }
  
  lDistAccSum->SetTextSize(0.04);
  lDistAccSum->Draw();
  cDistAccSum->Print( "DistAccSum.ps" );

  /////////////////////////////////////
  const int nbins = h1dDistAcc[1]->GetNbinsX();
  double effi [7][nbins];
  double distance [nbins];

  for( int bn=1; bn<=nbins; bn++ ) {
    distance [bn-1] = h1dDistAcc[1]->GetBinCenter(bn);
  }

  for( int ad=1; ad<=6; ad++ ) {
    for( int bn=1; bn<=nbins; bn++ ) {
      double p = h1dDistAcc[ad]->Integral(1,bn)/h1dDistAcc[ad]->Integral(1,100);
      effi [ad][bn-1] = p;
    }
  }
  
  TCanvas *cEffi = new TCanvas("Effi","Effi");
  cEffi->SetMargin(0.15,0.15,0.1,0.1);
  TMultiGraph *mg = new TMultiGraph();
  TLegend*  lEffi = new TLegend(0.5,0.5,0.7,0.8);
  TGraph *gEffi[7];

  for( int ad=1; ad<=3; ad++ ) {
    gEffi[ad] = new TGraph( nbins, distance, effi[ad] );
    gEffi[ad] ->SetLineStyle(ad);
    mg->Add(gEffi[ad],"lp");
    lEffi->AddEntry( gEffi[ad], nam[ad].c_str(), "l" );
  }

  mg->Draw("A");
  lEffi->Draw();
  mg->GetXaxis()->SetTitle("Distance [mm]");
  mg->GetYaxis()->SetTitle("Efficiency");
  mg->GetYaxis()->SetTitleOffset(1.6);
  mg->GetXaxis()->SetLabelSize(0.035);

  cEffi->Print("Effi.ps");

  ///////////////////////////
  /// Difference
  double Diff2 [nbins];
  double Diff3 [nbins];
  
  for( int bn=1; bn<=nbins; bn++ ) {
    double ad1 =effi [1][bn-1];
    double ad2 =effi [2][bn-1];
    double ad3 =effi [3][bn-1];

    double diff2 = (ad2-ad1)/(ad2+ad1);
    Diff2[bn-1] = diff2;

    double diff3 = (ad3-ad1)/(ad3+ad1);
    Diff3[bn-1] = diff3;
  }

  cout<<1<<endl;

  TCanvas *cDiff = new TCanvas("Diff","Diff");
  cDiff->SetMargin(0.15,0.15,0.1,0.1);
  TMultiGraph *mgd = new TMultiGraph();
  TLegend*  legDiff = new TLegend(0.5,0.5,0.7,0.8);
  TGraph *gDiff[7];

  gDiff[2] = new TGraph( nbins, distance, Diff2 );
  gDiff[2] ->SetMarkerStyle(20);
  gDiff[2] ->SetMarkerColor(2);
  mgd->Add(gDiff[2],"lp");
  legDiff->AddEntry( gDiff[2], nam[2].c_str(), "lp" );
  
  gDiff[3] = new TGraph( nbins, distance, Diff3 );
  gDiff[3] ->SetMarkerStyle(20);
  gDiff[3] ->SetMarkerColor(3);
  mgd->Add(gDiff[3],"lp");
  legDiff->AddEntry( gDiff[3], nam[3].c_str(), "lp" );

  cout<<2<<endl;

  mgd->Draw("A");
  legDiff->Draw();
  mgd->GetXaxis()->SetTitle("Distance [mm]");
  mgd->GetYaxis()->SetTitle("Difference");
  mgd->GetYaxis()->SetTitleOffset(1.5);
  mgd->GetXaxis()->SetLabelSize(0.035);

  cDiff->Print("Diff.ps");

#define old 1
#ifdef old
  {
  ///////////////////////////
  /// Near or Far Sum
  //  0 - Near
  //  1 - Far
  string SumName[2]   = { "NearSum", "FarSum" };
  string SumPsName[2] = { "NearSum.ps", "FarSum.ps" };
  string EffSumName[2]   = { "Near Site Efficiency", "Far Site Efficiency" };
  string NFFile[2] = { "../../data/Sample/Distance/P12e_1.5MeV/H/EH1.root",
		       "../../data/Sample/Distance/P12e_1.5MeV/H/EH3.root" };
  TH1F* h1dVtx[2];
  TH1F* h1dBkg[2];  
  TH1F* h1dSum[2];
  TCanvas * cSum[2];
  
  for( unsigned int b=0; b<2; b++ ) {
    TFile f( NFFile[b].c_str() );
    h1dVtx[b] = (TH1F*)f.Get( "h1dDistVtxSum"  );
    h1dVtx[b]->SetDirectory(0);
    h1dBkg[b] = (TH1F*)f.Get( "h1dDistBkgSum"  );
    h1dBkg[b]->SetDirectory(0);
    h1dSum[b] = (TH1F*)f.Get( "h1dDistAccSum"  );
    h1dSum[b]->SetDirectory(0);
  }

  /// Distance distribution
  for( unsigned int b=0; b<2; b++ ) {

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
  double effi   [2][nbins];
  double effiErr[2][nbins];
  double distance [nbins];
  double distErr  [nbins];
  
  for( int bn=1; bn<=nbins; bn++ ) {
    distance [bn-1] = h1dSum[1]->GetBinCenter(bn);
    distErr  [bn-1] = 0;
  }

  for( int b=0; b<2; b++ ) {
    cout<<"Start "<<EffSumName[b]<<endl; 
    
    double V = h1dVtx[b]->Integral(1,100);
    double B = h1dBkg[b]->Integral(1,100);

    for( int bn=1; bn<=nbins; bn++ ) {

      double VCut = h1dVtx[b]->Integral(1,bn);
      double BCut = h1dBkg[b]->Integral(1,bn);

      double pV = VCut/V;
      double reVCut = sqrt( 1/V * pV * (1-pV) );

      double reS = 0;
      if( b==0 ) reS = 0.0018;
      if( b==1 ) reS = 0.0005;

      effi[b][bn-1]    = (VCut - BCut)/(V - B);
      effiErr[b][bn-1] = effi[b][bn-1] * sqrt( pow( V/(VCut-BCut)* reVCut, 2) +
					       pow( (-BCut/(VCut-BCut) + B/(V-B))* reS, 2) );

      //cout<< V<<" "<<B<<" "<<VCut<<" "<<BCut<<endl;
      //cout<< V/(VCut-BCut)* reVCut <<" = "<<V/(VCut-BCut) <<" "<< reVCut<<endl;
      //cout<< (-BCut/(VCut-BCut) + B/(V-B))* reS <<" = "<<(-BCut/(VCut-BCut) + B/(V-B))<<" "<<reS<<" "<<-BCut/(VCut-BCut)<<" "<<B/(V-B)<<endl;

      if( bn == 25 ) {
	cout<< "==========" <<endl;
	cout<< effi[b][bn-1] <<"+/-"<< effiErr[b][bn-1]<<endl;
      }
    }
  }

  TCanvas *cEffiSum = new TCanvas( "EffiSum", "EffiSum" );
  cEffiSum->SetMargin(0.15,0.15,0.1,0.1);
  TMultiGraph *mg = new TMultiGraph();
  TLegend*  lEffiSum = new TLegend(0.5,0.5,0.7,0.8);
  TGraphErrors *gEffiSum[2];

  for( int b=0; b<2; b++ ) {
    gEffiSum[b] = new TGraphErrors( nbins, distance, effi[b], distErr, effiErr[b] );
    gEffiSum[b] ->SetLineStyle(b);
    gEffiSum[b] ->SetMarkerStyle(20);
    gEffiSum[b] ->SetMarkerColor(2+b);
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
  double DiffSum [nbins];
  double DiffSumE[nbins];

  for( int bn=1; bn<=nbins; bn++ ) {
    
    double a = effi[0][bn-1];
    double b = effi[1][bn-1];
    double da= effiErr[0][bn-1];
    double db= effiErr[1][bn-1];
    
    double D = (a-b)/(a+b);
    double dD= 2/((a+b)*(a+b)) * sqrt((a*db*a*db + b*da*b*da));
 
    DiffSum [bn-1] = D;
    DiffSumE[bn-1] = dD;
  }

  TCanvas *cDiffSum = new TCanvas( "DiffSum", "DiffSum" );
  cDiffSum->SetMargin(0.15,0.15,0.1,0.1);
  TMultiGraph *mgDiff = new TMultiGraph();
  TLegend*  lDiffSum = new TLegend(0.5,0.5,0.7,0.8);
  TGraphErrors *gDiffSum;

  gDiffSum = new TGraphErrors( nbins, distance, DiffSum, distErr, DiffSumE );
  gDiffSum ->SetLineStyle(20);
  mgDiff->Add(gDiffSum,"lp");
  lDiffSum->AddEntry( gDiffSum, "Near-Far acceptance difference", "lp" );

  mgDiff->Draw("A");
  lDiffSum->Draw();
  mgDiff->GetXaxis()->SetTitle("Distance [mm]");
  mgDiff->GetYaxis()->SetTitle("Difference");
  mgDiff->GetYaxis()->SetTitleOffset(1.6);
  mgDiff->GetXaxis()->SetLabelSize(0.035);

  cDiffSum->Print( "DiffSum.ps" );
  }
#endif
}

