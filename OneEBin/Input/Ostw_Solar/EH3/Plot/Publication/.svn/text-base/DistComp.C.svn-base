/* 
   Usage:
   > root
   [0] .L ZeroGd.C+
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
#include "TPaveLabel.h"
using namespace std;

const double FullRange = 5000;
const int    Nbin      = 250;
const int    At2000mm  = 100;
const int    At500mm   = 25;

TLegend*  lDiffSum;
TMultiGraph *mgDiffBi;
TMultiGraph *mgDiffGd;

// This is for background spectrum only
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

  if( ESta<0 ) ESta = 0;
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

void ZeroBi214()
{
  ///////////////////////////
  const int nSet = 6;
  string SumName[nSet]   = { "AD1 Bi", "AD2 Bi", "AD3 Bi", "AD4 Bi", "AD5 Bi", "AD6 Bi" };
  string SumPsName[nSet] = { "AD1.ps", "AD2.ps", "AD3.ps", "AD4.ps", "AD5.ps", "AD6.ps" };
  string EffSumName[nSet]   = { "AD1 Efficiency", "AD2 Efficiency", "AD3 Efficiency", "AD4 Efficiency", "AD5 Efficiency", "AD6 Efficiency" };
  // Gd
  string NFFile[nSet] = { "../../../../AccSubOutput/P12e_0.7MeV_Scaled_Bi214/H/EH1.root",
			  "../../../../AccSubOutput/P12e_0.7MeV_Scaled_Bi214/H/EH1.root",
                          "../../../../AccSubOutput/P12e_0.7MeV_Scaled_Bi214/H/EH2.root",
                          "../../../../AccSubOutput/P12e_0.7MeV_Scaled_Bi214/H/EH3.root",
			  "../../../../AccSubOutput/P12e_0.7MeV_Scaled_Bi214/H/EH3.root",
			  "../../../../AccSubOutput/P12e_0.7MeV_Scaled_Bi214/H/EH3.root"
  };
  
  double Systematic[nSet] = { 0.0018, 0.0018, 0.0016, 0.0005, 0.0005, 0.0005 };
  //double Systematic[nSet] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  TH1F* h1dVtx[nSet];
  TH1F* h1dBkg[nSet];  
  TH1F* h1dBkgNS[nSet];  // No systematic
  TH1F* h1dSum[nSet];
  TH1F* h1dSumNS[nSet];  // No systematic
  TCanvas * cSum[nSet];
  
  string idx[6] = {"1","2","1","1","2","3"};

  for( int s=0; s<nSet; s++ ) {
    TFile f( NFFile[s].c_str() );
    h1dVtx[s] = (TH1F*)f.Get( ("h1dDistVtx_"+idx[s]).c_str()  );
    h1dVtx[s]->SetDirectory(0);
    h1dBkg[s] = (TH1F*)f.Get( ("h1dDistBkg_"+idx[s]).c_str()  );
    h1dBkg[s]->SetDirectory(0);
    h1dBkgNS[s] = new TH1F( (SumName[s]+"Bkg").c_str(), (SumName[s]+"Bkg").c_str(), h1dBkg[s]->GetNbinsX(), 0, h1dBkg[s]->GetXaxis()->GetXmax());
    h1dBkgNS[s]->SetDirectory(0);
    h1dSum[s] = (TH1F*)f.Get( ("h1dDistAcc_"+idx[s]).c_str()  );
    h1dSum[s]->SetDirectory(0);
    h1dSumNS[s] = new TH1F( SumName[s].c_str(), SumName[s].c_str(), h1dBkg[s]->GetNbinsX(), 0, h1dBkg[s]->GetXaxis()->GetXmax());
    h1dSumNS[s]->SetDirectory(0);
  }

  // The global validataion
  const int bS = 126;  // 2500 mm
  const int bE = 250;
  
  double C, CESta, CESys;
  C = CESta = CESys = 0;

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
  }
  
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

  double Entry1   = 0;
  double EntryOth = 0;

  /// Differential validataion
  for( int s=0; s<nSet; s++ ) {
    
    h1dSumNS[s]->GetXaxis()->SetRangeUser(0,1990);
    h1dSumNS[s]->GetXaxis()->SetNdivisions(405);

    h1dSumNS[s]->GetYaxis()->SetLabelSize(0.07);
    h1dSumNS[s]->GetYaxis()->SetTitleSize(0.07);
    h1dSumNS[s]->GetYaxis()->SetTitleOffset(0.9);

    h1dSumNS[s] ->SetLineStyle(20);
    h1dSumNS[s] ->SetLineColor(2+s);
    h1dSumNS[s] ->SetMarkerStyle(25);
    h1dSumNS[s] ->SetMarkerSize(0.5);
    h1dSumNS[s] ->SetMarkerColor(2+s);
    lDiffSum->AddEntry( h1dSumNS[s], SumName[s].c_str(), "lp" );

    // Without sytematic
    if( s==0 ) {
      h1dSumNS[s]->Draw();

      h1dSumNS[s]->GetXaxis()->SetTitle("Distance [mm]");
      h1dSumNS[s]->GetYaxis()->SetTitle("Entries / 20 mm");

      Entry1 = h1dSumNS[s]->Integral();
    } else {

      TH1F *hnew = (TH1F*)h1dSumNS[s]->Clone("hnew");
      EntryOth = hnew->Integral();
      hnew->Scale( Entry1/EntryOth );
      hnew->Draw("same");

    }
  }
  
  /* For efficiency difference */
  /// Efficiency curve
  /// 0 for all near ADs and 1 for all far ADs
  string NFName[nSet] = { "AD1", "AD2", "AD3", "AD4", "AD5", "AD6" };

  const int topbin = At2000mm;  // 2000 mm
  double effi   [nSet][topbin];
  double effiErr[nSet][topbin];
  double distance     [topbin];
  double distErr      [topbin];

  for( int bn=1; bn<=topbin; bn++ ) {
    distance [bn-1] = h1dSum[1]->GetBinCenter(bn);
    distErr  [bn-1] = 0;
  }

  for( int b=0; b<nSet; b++ ) {

    double V = h1dVtx[b]->Integral(1,topbin);
    double B = h1dBkg[b]->Integral(1,topbin);

    for( int bn=1; bn<=topbin; bn++ ) {

      double VCut = h1dVtx[b]->Integral(1,bn);
      double BCut = h1dBkg[b]->Integral(1,bn);

      double pV = VCut/V;
      double EVCut = sqrt( V * pV * (1-pV) );
      double EBCut = GetTotErr( h1dBkg[b], 1, bn );

      double reS = 0;
      reS = 0.0018;
      //reS = 0;

      effi[b][bn-1]    = (VCut - BCut)/(V - B);
      effiErr[b][bn-1] = sqrt( pow( 1/(V-B)*EVCut, 2) +
			       pow( 1/(V-B)*EBCut, 2) +
			       pow( ( -BCut/(V-B) + (VCut-BCut)/((V-B)*(V-B)) *B )* reS, 2 ) );

      if( bn == At500mm ) {
        cout<< "==========" <<endl;
        cout<< effi[b][bn-1] <<"+/-"<< effiErr[b][bn-1]<<endl;
      }
    }
  }

  TMultiGraph *mg = new TMultiGraph();

  TGraphErrors *gEffiSum[nSet];

  for( int b=0; b<nSet; b++ ) {
    gEffiSum[b] = new TGraphErrors( topbin, distance, effi[b], distErr, effiErr[b] );
    gEffiSum[b] ->SetLineStyle(b);
    gEffiSum[b] ->SetMarkerStyle(20);
    gEffiSum[b] ->SetMarkerColor(2+b);
    mg->Add(gEffiSum[b],"lp");
  }

  double EffAve[topbin];
  for( int bn=1; bn<=topbin; bn++ ) {
    EffAve[bn-1] = (effi[0][bn-1] + effi[1][bn-1] + effi[2][bn-1] + effi[3][bn-1] + effi[4][bn-1] + effi[5][bn-1])/6;
  }    

  /////////////////////////
  /// DiffSum
  double DiffSum [nSet][topbin];
  double DiffSumE[nSet][topbin];

  for( int d=0; d<nSet; d++ ) {
    for( int bn=1; bn<=topbin; bn++ ) {
      
      double a = EffAve[bn-1];
      double b = effi[d][bn-1];
      double da= 0;
      double db= effiErr[d][bn-1];
      
      double D = (a-b)/(a+b);
      double dD= 2/((a+b)*(a+b)) * sqrt((a*db*a*db + b*da*b*da));
      
      DiffSum [d][bn-1] = D;
      DiffSumE[d][bn-1] = 0; // dD;
    }
  }
  
  mgDiffBi = new TMultiGraph();
  TLegend*  lDiffSum = new TLegend(0.5,0.5,0.7,0.8);
  TGraphErrors *gDiffSum[nSet];

  for( int b=0; b<nSet; b++ ) { // Start from AD 2
    gDiffSum[b] = new TGraphErrors( topbin, distance, DiffSum[b], distErr, DiffSumE[b] );
    gDiffSum[b] ->SetLineStyle(20);
    gDiffSum[b] ->SetLineColor(2+b);
    gDiffSum[b] ->SetMarkerStyle(25);
    gDiffSum[b] ->SetMarkerSize(0.5);
    gDiffSum[b] ->SetMarkerColor(2+b);
    mgDiffBi->Add( gDiffSum[b],"lp" );
  }
}

void ZeroGd()
{
  ///////////////////////////
  const int nSet = 6;
  string SumName[nSet]   = { "AD1 Gd", "AD2 Gd", "AD3 Gd", "AD4 Gd", "AD5 Gd", "AD6 Gd" };
  string SumPsName[nSet] = { "AD1.ps", "AD2.ps", "AD3.ps", "AD4.ps", "AD5.ps", "AD6.ps" };
  string EffSumName[nSet]   = { "AD1 Efficiency", "AD2 Efficiency", "AD3 Efficiency", "AD4 Efficiency", "AD5 Efficiency", "AD6 Efficiency" };
  // Gd
  string NFFile[nSet] = { "../../data/Sample/Distance/P12e_1.5MeV/Gd5m/EH1.root",
			  "../../data/Sample/Distance/P12e_1.5MeV/Gd5m/EH1.root",
                          "../../data/Sample/Distance/P12e_1.5MeV/Gd5m/EH2.root",
                          "../../data/Sample/Distance/P12e_1.5MeV/Gd5m/EH3.root",
			  "../../data/Sample/Distance/P12e_1.5MeV/Gd5m/EH3.root",
			  "../../data/Sample/Distance/P12e_1.5MeV/Gd5m/EH3.root"
  };
  
  double Systematic[nSet] = { 0.0018, 0.0018, 0.0016, 0.0005, 0.0005, 0.0005 };
  //double Systematic[nSet] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  TH1F* h1dVtx[nSet];
  TH1F* h1dBkg[nSet];  
  TH1F* h1dBkgNS[nSet];  // No systematic
  TH1F* h1dSum[nSet];
  TH1F* h1dSumNS[nSet];  // No systematic
  TCanvas * cSum[nSet];
  
  string idx[6] = {"1","2","1","1","2","3"};

  for( int s=0; s<nSet; s++ ) {
    TFile f( NFFile[s].c_str() );
    h1dVtx[s] = (TH1F*)f.Get( ("h1dDistVtx_"+idx[s]).c_str()  );
    h1dVtx[s]->SetDirectory(0);
    h1dBkg[s] = (TH1F*)f.Get( ("h1dDistBkg_"+idx[s]).c_str()  );
    h1dBkg[s]->SetDirectory(0);
    h1dBkgNS[s] = new TH1F( (SumName[s]+"Bkg").c_str(), (SumName[s]+"Bkg").c_str(), h1dBkg[s]->GetNbinsX(), 0, h1dBkg[s]->GetXaxis()->GetXmax());
    h1dBkgNS[s]->SetDirectory(0);
    h1dSum[s] = (TH1F*)f.Get( ("h1dDistAcc_"+idx[s]).c_str()  );
    h1dSum[s]->SetDirectory(0);
    h1dSumNS[s] = new TH1F( SumName[s].c_str(), SumName[s].c_str(), h1dBkg[s]->GetNbinsX(), 0, h1dBkg[s]->GetXaxis()->GetXmax());
    h1dSumNS[s]->SetDirectory(0);
  }

  // The global validataion
  const int bS = 126;  // 2500 mm
  const int bE = 250;
  
  double C, CESta, CESys;
  C = CESta = CESys = 0;

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
  }
  
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

  double Entry1   = 0;
  double EntryOth = 0;

  /// Differential validataion
  for( int s=0; s<nSet; s++ ) {
    
    h1dSumNS[s]->GetXaxis()->SetRangeUser(0,1990);
    
    h1dSumNS[s] ->SetLineStyle(20);
    h1dSumNS[s] ->SetLineColor(2+s);
    h1dSumNS[s] ->SetMarkerStyle(20);
    h1dSumNS[s] ->SetMarkerSize(0.5);
    h1dSumNS[s] ->SetMarkerColor(2+s);
    lDiffSum->AddEntry( h1dSumNS[s], SumName[s].c_str(), "lp" );

    // Without sytematic
    if( s==0 ) {
      h1dSumNS[s]->Draw("same");
      Entry1 = h1dSumNS[s]->Integral();
    } else {

      TH1F *hnew = (TH1F*)h1dSumNS[s]->Clone("hnew");
      EntryOth = hnew->Integral();
      hnew->Scale( Entry1/EntryOth );
      hnew->Draw("same");

    }
  }

  /* For efficiency difference */
  /// Efficiency curve
  /// 0 for all near ADs and 1 for all far ADs
  string NFName[nSet] = { "AD1", "AD2", "AD3", "AD4", "AD5", "AD6" };

  const int topbin = At2000mm;  // 2000 mm
  double effi   [nSet][topbin];
  double effiErr[nSet][topbin];
  double distance     [topbin];
  double distErr      [topbin];

  for( int bn=1; bn<=topbin; bn++ ) {
    distance [bn-1] = h1dSum[1]->GetBinCenter(bn);
    distErr  [bn-1] = 0;
  }

  for( int b=0; b<nSet; b++ ) {

    double V = h1dVtx[b]->Integral(1,topbin);
    double B = h1dBkg[b]->Integral(1,topbin);

    for( int bn=1; bn<=topbin; bn++ ) {

      double VCut = h1dVtx[b]->Integral(1,bn);
      double BCut = h1dBkg[b]->Integral(1,bn);

      double pV = VCut/V;
      double EVCut = sqrt( V * pV * (1-pV) );
      double EBCut = GetTotErr( h1dBkg[b], 1, bn );

      double reS = 0;
      reS = 0.0018;
      //reS = 0;

      effi[b][bn-1]    = (VCut - BCut)/(V - B);
      effiErr[b][bn-1] = sqrt( pow( 1/(V-B)*EVCut, 2) +
			       pow( 1/(V-B)*EBCut, 2) +
			       pow( ( -BCut/(V-B) + (VCut-BCut)/((V-B)*(V-B)) *B )* reS, 2 ) );

      if( bn == At500mm ) {
        cout<< "==========" <<endl;
        cout<< effi[b][bn-1] <<"+/-"<< effiErr[b][bn-1]<<endl;
      }
    }
  }

  TMultiGraph *mg = new TMultiGraph();

  TGraphErrors *gEffiSum[nSet];

  for( int b=0; b<nSet; b++ ) {
    gEffiSum[b] = new TGraphErrors( topbin, distance, effi[b], distErr, effiErr[b] );
    gEffiSum[b] ->SetLineStyle(b);
    gEffiSum[b] ->SetMarkerStyle(20);
    gEffiSum[b] ->SetMarkerColor(2+b);
    mg->Add(gEffiSum[b],"lp");
  }

  double EffAve[topbin];
  for( int bn=1; bn<=topbin; bn++ ) {
    EffAve[bn-1] = (effi[0][bn-1] + effi[1][bn-1] + effi[2][bn-1] + effi[3][bn-1] + effi[4][bn-1] + effi[5][bn-1])/6;
  }    

  /////////////////////////
  /// DiffSum
  double DiffSum [nSet][topbin];
  double DiffSumE[nSet][topbin];

  for( int d=0; d<nSet; d++ ) {
    for( int bn=1; bn<=topbin; bn++ ) {
      
      double a = EffAve[bn-1];
      double b = effi[d][bn-1];
      double da= 0;
      double db= effiErr[d][bn-1];
      
      double D = (a-b)/(a+b);
      double dD= 2/((a+b)*(a+b)) * sqrt((a*db*a*db + b*da*b*da));
      
      DiffSum [d][bn-1] = D;
      DiffSumE[d][bn-1] = 0; // dD;
    }
  }
  
  mgDiffGd = new TMultiGraph();
  TLegend*  lDiffSum = new TLegend(0.5,0.5,0.7,0.8);
  TGraphErrors *gDiffSum[nSet];

  for( int b=0; b<nSet; b++ ) { // Start from AD 2
    gDiffSum[b] = new TGraphErrors( topbin, distance, DiffSum[b], distErr, DiffSumE[b] );
    gDiffSum[b] ->SetLineStyle(20);
    gDiffSum[b] ->SetLineColor(2+b);
    gDiffSum[b] ->SetMarkerStyle(20);
    gDiffSum[b] ->SetMarkerSize(0.5);
    gDiffSum[b] ->SetMarkerColor(2+b);
    mgDiffGd->Add( gDiffSum[b],"lp" );
  }
}

void DiffBi214()
{
  mgDiffBi->Draw("A");
  mgDiffBi->GetYaxis()->SetRangeUser(-0.009,0.009);
  mgDiffBi->GetYaxis()->SetNdivisions(405);
  mgDiffBi->GetYaxis()->SetLabelSize(0.155);
  mgDiffBi->GetYaxis()->SetTitle("Effi. diff.");
  mgDiffBi->GetYaxis()->SetTitleSize(0.15);
  mgDiffBi->GetYaxis()->SetTitleOffset(0.4);

  mgDiffBi->GetXaxis()->SetRangeUser(0,2000);

  TPaveLabel *label = new TPaveLabel(1450, -0.008, 1625, -0.003, "Bi");
  label->SetFillColor(0);
  label->SetShadowColor(0);
  label->SetTextSize(0.5);
  label->Draw();
}

void DiffGd()
{
  mgDiffGd->Draw("A");
  mgDiffGd->GetYaxis()->SetRangeUser(-0.009,0.009);
  mgDiffGd->GetYaxis()->SetNdivisions(405);
  mgDiffGd->GetYaxis()->SetLabelSize(0.12);
  mgDiffGd->GetYaxis()->SetTitle("Effi. diff.");
  mgDiffGd->GetYaxis()->SetTitleSize(0.12);
  mgDiffGd->GetYaxis()->SetTitleOffset(0.5);

  mgDiffGd->GetXaxis()->SetRangeUser(0,2000);
  mgDiffGd->GetXaxis()->SetLabelSize(0.12);
  mgDiffGd->GetXaxis()->SetTitle("Distance [mm]");
  mgDiffGd->GetXaxis()->SetTitleSize(0.12);
  mgDiffGd->GetXaxis()->SetTitleOffset(1);
  
  TPaveLabel *label = new TPaveLabel(1450, -0.008, 1625, -0.003, "Gd");
  label->SetFillColor(0);
  label->SetShadowColor(0);
  label->SetTextSize(0.5);
  label->Draw();
}

void DistComp()
{
  TH1::AddDirectory(kFALSE);

  TCanvas* c = new TCanvas( "Distance", "Distance", 700, 600 );
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TPad* m  = new TPad("NF","Near and Far",      0, 0.5,   1, 1    );
  TPad* s1 = new TPad("NF","Near and Far",      0, 0.283, 1, 0.5  );
  TPad* s2 = new TPad("NF","Near and Far",      0, 0.0,   1, 0.283);

  m->Draw();
  s1->Draw();
  s2->Draw();

  m->cd();
  m->SetMargin(0.15,0.1,0.0,0.1);
  m->SetGrid();

  lDiffSum = new TLegend(0.58,0.24, 0.85,0.83);
  lDiffSum->SetFillColor(0);
  lDiffSum->SetShadowColor(0);
  lDiffSum->SetNColumns(2);

  ZeroBi214();
  ZeroGd();

  lDiffSum->Draw();


  //
  s1->cd();
  s1->SetMargin(0.15,0.1,0.0,0.0);
  s1->SetGrid();

  DiffBi214();


  //
  s2->cd();
  s2->SetMargin(0.15,0.1,0.30,0.0);
  s2->SetGrid();

  DiffGd();


  // 
  c->Print("Distance.ps");
  c->Print("Distance.eps");
}
