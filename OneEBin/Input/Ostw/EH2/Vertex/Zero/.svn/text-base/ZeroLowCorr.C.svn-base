/* 
   Usage:
   > root
   [0] .L Zero.C+
   [1] Zero()
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


// This is for background spectrum only
// Input: background spectrum, start bin, end bin, systematic error of A,
// Output: background number within [bS, bE], Sta. and Sys. error.       
int GetContErr( TH1F* bkgSpec, const int bS, const int bE, const double dA, 
		double &C, double &ESta, double &ESys )
{
  C = 0;
  ESta = 0;
  ESys = 0;

  for( int bin = bS; bin<=bE; bin++ ) {
    double Cont = bkgSpec->GetBinContent( bin );
    double ESq = pow( bkgSpec->GetBinError( bin ), 2 );
    double ESysSq = Cont*Cont*dA*dA;
    double EStaSq = ESq - ESysSq;

    C += Cont;
    ESta += EStaSq;
  }

  ESta = sqrt( ESta );
  ESys = C*dA;

  return 1;
}

// 
double GetTotErr( TH1F* bkgSpec, const int bS, const int bE )
{
  double ESta = 0;

  for( int bin = bS; bin<=bE; bin++ ) {
    double ESq = pow( bkgSpec->GetBinError( bin ), 2 );
    ESta += ESq;
  }

  ESta = sqrt( ESta );

  return ESta;
}


void Zero()
{
  gStyle->SetOptStat(0);

  ///////////////////////////
  const int nSet = 3;
  string SumName[nSet]   = { "DYB", "LAO", "FAR" };
  string SumPsName[nSet] = { "DYB.ps", "LAO.ps", "FAR.ps" };
  string EffSumName[nSet]   = { "DYB Site Efficiency", "LAO Site Efficiency", "FAR Site Efficiency" };
  string NFFile[nSet] =
    /*
    { "../../data/Sample/Distance/P12e_1.5MeV/H5m/EH1.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H5m/EH2.root",
    "../../data/Sample/Distance/P12e_1.5MeV/H5m/EH3.root" };
    */
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_1.5-3.5/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_1.5-3.5/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_1.5-3.5/H/EH3.root" };
    */
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_1.5-2.0/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_1.5-2.0/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_1.5-2.0/H/EH3.root" };
    */
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_2.0-3.0/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_2.0-3.0/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_2.0-3.0/H/EH3.root" };
    */
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_3.0-4.0/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_3.0-4.0/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_3.0-4.0/H/EH3.root" };
    */
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_2.0-/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_2.0-/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_2.0-/H/EH3.root" };
    */
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_3.0-/H/EH1.root", 
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_3.0-/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_3.0-/H/EH3.root" };
    */
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_3.5-/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_3.5-/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_3.5-/H/EH3.root" };
    */
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_1.5-4.0/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_1.5-4.0/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_1.5-4.0/H/EH3.root" };
    */
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_4.0-/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_4.0-/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_1.5MeV_4.0-/H/EH3.root" };
    */
    
    //  Before Correction
    { "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scale/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scale/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scale/H/EH3.root" };
    
    //  After Correction
    /*
    { "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scaled/H/EH1.root", 
      "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scaled/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scaled/H/EH3.root" };
    */
    /*
    // Bi-214
    { "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scaled_Bi214/H/EH1.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scaled_Bi214/H/EH2.root",
      "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scaled_Bi214/H/EH3.root" };
    */
    /*
    // 0.7 MeV and 1.5 ms
    { "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_1.5ms_Scale/H/EH1.root", 
      "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_1.5ms_Scale/H/EH2.root", 
      "~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_1.5ms_Scale/H/EH3.root" };
    */
  //double Systematic[nSet] = { 0.0018, 0.0016,0.0005 };
  double Systematic[nSet] = { 0, 0, 0 };

  TH1F* h1dVtx[nSet];
  TH1F* h1dBkg[nSet];  
  TH1F* h1dBkgNS[nSet];  // No systematic
  TH1F* h1dSum[nSet];
  TH1F* h1dSumNS[nSet];  // No systematic
  TCanvas * cSum[nSet];
  
  for( int s=0; s<nSet; s++ ) {
    TFile f( NFFile[s].c_str() );
    h1dVtx[s] = (TH1F*)f.Get( "h1dDistVtxSum"  );
    h1dVtx[s]->SetDirectory(0);
    h1dBkg[s] = (TH1F*)f.Get( "h1dDistBkgSum"  );
    h1dBkg[s]->SetDirectory(0);
    h1dBkgNS[s] = new TH1F( (SumName[s]+"Bkg").c_str(), (SumName[s]+"Bkg").c_str(), h1dBkg[s]->GetNbinsX(), 0, h1dBkg[s]->GetXaxis()->GetXmax());
    h1dBkgNS[s]->SetDirectory(0);
    h1dSum[s] = (TH1F*)f.Get( "h1dDistAccSum"  );
    h1dSum[s]->SetDirectory(0);
    h1dSumNS[s] = new TH1F( SumName[s].c_str(), SumName[s].c_str(), h1dBkg[s]->GetNbinsX(), 0, h1dBkg[s]->GetXaxis()->GetXmax());
    h1dSumNS[s]->SetDirectory(0);
  }


  // The global validataion
  const int bS = 126;
  const int bE = 250;
  
  double C, CESta, CESys;
  C = CESta = CESys = 0;

  cout.precision(8);
  cout<<fixed;
  for( int s=0; s<nSet; s++ ) {
    double N = h1dVtx[s]->Integral( bS, bE );
    double B, BESta, BESys;
    GetContErr( h1dBkg[s], bS, bE, Systematic[s], B, BESta, BESys );
    
    C = N - B;
    CESta = sqrt(N + BESta*BESta);
    CESys = BESys;

    cout<<SumName[s]<<" N= "<<N<<" \\pm "<<sqrt(N)<<endl;
    cout<<SumName[s]<<" N-AB= "<<C<<" \\pm "<<CESta<<" \\pm "<<CESys<<endl;
    
    cout<<" Coarse value "<< h1dSum[s]->Integral( bS, bE )<<" \\pm "<<GetTotErr( h1dSum[s], bS, bE )<<endl;
    cout<<" Correction= "<<N/B<<endl;
  }
  /* 2 m to 5 m */
  /*
 Correction= 0.99671589
 Correction= 0.99614411
 Correction= 0.99682257
  */
  /* 2.5 m to 5 m */
  /*
 Correction= 0.99698890
 Correction= 0.99587290
 Correction= 0.99670517
  */

  // Get the subtracted plots with systematic
  for( int s=0; s<nSet; s++ ) {
    for( int bin = 1; bin<=h1dBkg[s]->GetNbinsX(); bin++ ) {

      double N = h1dVtx[s]->Integral( bin, bin );
      double B, BESta, BESys;
      GetContErr( h1dBkg[s], bin, bin, Systematic[s], B, BESta, BESys );
      
      h1dBkgNS[s]->SetBinContent( bin, B );
      h1dBkgNS[s]->SetBinError( bin, BESta );
      
      h1dSumNS[s]->SetBinContent( bin, N-B );
      h1dSumNS[s]->SetBinError( bin, sqrt(N+BESta*BESta) );
    }
  }
  
  /// Differential validataion
  for( int s=0; s<nSet; s++ ) {
    // With systematic
    /*
    TCanvas* cwS = new TCanvas( (SumName[s]+"wS").c_str(), (SumName[s]+"wS").c_str() );
    cwS->SetMargin(0.15,0.15,0.1,0.1);
    cwS->SetGrid();
    h1dSum[s]->Draw();
    h1dSum[s]->Fit("pol0","","",2000,5000);
    */

    // Without sytematic
    cSum[s] = new TCanvas( (SumName[s]+"nS").c_str(), (SumName[s]+"nS").c_str() );
    cSum[s]->SetMargin(0.15,0.15,0.1,0.1);
    cSum[s]->SetGrid();
    //h1dSumNS[s]->GetXaxis()->SetRangeUser(0,2000);
    h1dSumNS[s]->Draw();
    h1dSumNS[s]->Fit("pol0","","",2000,5000);
    h1dSumNS[s]->GetXaxis()->SetTitle("Distance [mm]");
    h1dSumNS[s]->GetYaxis()->SetTitle("Entries / 20 mm");
    h1dSumNS[s]->GetYaxis()->SetTitleOffset(1.6);
    cSum[s]->Print( SumPsName[s].c_str() );
  }

  /// Efficiency curve
  /// 0 for all near ADs and 1 for all far ADs
  TH1F* hVtx[2];
  TH1F* hBkg[2];
  TH1F* hSum[2];
  string NFName[2] = { "Near", "Far" };
  string Type[3] = { "Vtx", "Bkg", "Acc" };

  const int nbins = h1dBkg[0]->GetNbinsX();
  double xMax = h1dBkg[0]->GetXaxis()->GetXmax();

  for( int s=0; s<2; s++ ) {
    hVtx[s] = new TH1F( (NFName[s]+Type[0]).c_str(), (NFName[s]+Type[0]).c_str(), nbins, 0, xMax);
    hBkg[s] = new TH1F( (NFName[s]+Type[1]).c_str(), (NFName[s]+Type[1]).c_str(), nbins, 0, xMax);
    hSum[s] = new TH1F( (NFName[s]+Type[2]).c_str(), (NFName[s]+Type[2]).c_str(), nbins, 0, xMax);
  }
  // EH1 + EH2
  hVtx[0] -> Add( h1dVtx[0], h1dVtx[1] );
  hBkg[0] -> Add( h1dBkgNS[0], h1dBkgNS[1] );
  hSum[0] -> Add( hVtx[0], hBkg[0], 1, -1 );
  
  /* Purely EH1
  hVtx[0] -> Add( h1dVtx[0] );
  hBkg[0] -> Add( h1dBkgNS[0] );
  hSum[0] -> Add( hVtx[0] );
  */
  hVtx[1] -> Add( h1dVtx[2] );
  hBkg[1] -> Add( h1dBkgNS[2] );
  hSum[1] -> Add( h1dSumNS[2] );

  const int topbin = 100;
  double effi   [2][topbin];
  double effiErr[2][topbin];
  double distance [topbin];
  double distErr  [topbin];

  for( int bn=1; bn<=topbin; bn++ ) {
    distance [bn-1] = hSum[1]->GetBinCenter(bn);
    distErr  [bn-1] = 0;
  }

  string EffSum[2]   = { "Near Site Efficiency", "FAR Site Efficiency" };
  for( int b=0; b<2; b++ ) {
    cout<<"Start "<<EffSum[b]<<endl;

    double V = hVtx[b]->Integral(1,topbin);
    double B = hBkg[b]->Integral(1,topbin);

    for( int bn=1; bn<=topbin; bn++ ) {

      double VCut = hVtx[b]->Integral(1,bn);
      double BCut = hBkg[b]->Integral(1,bn);

      double pV = VCut/V;
      double EVCut = sqrt( V * pV * (1-pV) );
      double EBCut = GetTotErr( hBkg[b], 1, bn );

      double reS = 0;
      if( b==0 ) reS = Systematic[0];
      if( b==1 ) reS = Systematic[2];
      //reS = 0;

      effi[b][bn-1]    = (VCut - BCut)/(V - B);
      effiErr[b][bn-1] = sqrt( pow( 1/(V-B)*EVCut, 2) +
			       pow( 1/(V-B)*EBCut, 2) +
			       pow( ( -BCut/(V-B) + (VCut-BCut)/((V-B)*(V-B)) *B )* reS, 2 ) );

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
    gEffiSum[b] = new TGraphErrors( topbin, distance, effi[b], distErr, effiErr[b] );
    gEffiSum[b] ->SetLineStyle(b);
    gEffiSum[b] ->SetMarkerStyle(20);
    gEffiSum[b] ->SetMarkerColor(2+b);
    mg->Add(gEffiSum[b],"lp");
    lEffiSum->AddEntry( gEffiSum[b], EffSum[b].c_str(), "lp" );
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
  double DiffSum [topbin];
  double DiffSumE[topbin];

  for( int bn=1; bn<=topbin; bn++ ) {

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

  gDiffSum = new TGraphErrors( topbin, distance, DiffSum, distErr, DiffSumE );
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
