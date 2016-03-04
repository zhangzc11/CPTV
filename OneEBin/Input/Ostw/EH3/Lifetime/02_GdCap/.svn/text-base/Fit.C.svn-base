/*
  Usage:
  
  $ root
  root [0] .L CapT.C+
  root [1] .L Fit.C+
  root [2] Fit()

*/

#include "TH1.h"
#include "TROOT.h"
#include "TF1.h"
#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include <string>
#include <iostream>
using namespace std;

extern double CapT(double *x,double *par);

void Fit()
{  
  TH1::AddDirectory(kFALSE);  /* Without this fitted histogram will be lost after return */
  //  gStyle->SetStatH(0.5);
  //  gStyle->SetStatW(0.6);
  //  gROOT->ProcessLine(".L CapT.C+");

  TF1 GdCapT_F("GdCapT", CapT, 0, 400e-6, 5);

  GdCapT_F.SetParNames  ("N",   "Alpha","LambdaCap","LambdaGen","FlatBkg");
  GdCapT_F.SetParameters(0.004, 0.24,    3.8e4,     2.2e5,      1.3      );



  string file[7] = {
    "../../data/Lifetime/GdCap/EH0_AD1.root",
    "../../data/Lifetime/GdCap/EH1_AD1.root",
    "../../data/Lifetime/GdCap/EH1_AD2.root",
    "../../data/Lifetime/GdCap/EH2_AD1.root",
    "../../data/Lifetime/GdCap/EH3_AD1.root",
    "../../data/Lifetime/GdCap/EH3_AD2.root",
    "../../data/Lifetime/GdCap/EH3_AD3.root",
  };

  string title[7] = {
    "EH0_AD1",
    "EH1_AD1",
    "EH1_AD2",
    "EH2_AD1",
    "EH3_AD1",
    "EH3_AD2",
    "EH3_AD3"
  };

  TH1F* h[7];  /* Fit result */
  int nAd = 7;
  double x[7];
  double x_e[7] = {0,0,0,0,0,0,0};
  double Alpha[7], Alpha_e[7];
  double LambdaCap[7], LambdaCap_e[7];
  double LambdaGen[7], LambdaGen_e[7];
  

  for( int AdNo = 0; AdNo<nAd; AdNo++ )  {

    cout<<file[AdNo]<<endl;

    TFile f( file[AdNo].c_str() );
    h[AdNo] = (TH1F*)f.Get("h");

    GdCapT_F.SetParameters(0.004, 0.24,    3.8e4,     2.2e5,      1.3      );
    h[AdNo]->Fit("GdCapT","L","",1e-6,400e-6);

    x[AdNo]         = AdNo;

    Alpha[AdNo]     = GdCapT_F.GetParameter(1);
    Alpha_e[AdNo]   = GdCapT_F.GetParError(1);

    LambdaCap[AdNo]   = GdCapT_F.GetParameter(2);
    LambdaCap_e[AdNo] = GdCapT_F.GetParError(2);

    LambdaGen[AdNo]   = GdCapT_F.GetParameter(3);
    LambdaGen_e[AdNo] = GdCapT_F.GetParError(3);

    f.Close();
  }

  for( int AdNo = 0; AdNo<nAd; AdNo++ )  {
    
    TCanvas* c = new TCanvas(file[AdNo].c_str(),file[AdNo].c_str());
    c->SetLogy();
    h[AdNo]->GetXaxis()->SetTitle("Capture time [s]");
    h[AdNo]->GetYaxis()->SetTitle("Entries / 1e-6 s");
    h[AdNo]->GetYaxis()->SetTitleOffset(1.2);
    h[AdNo]->SetTitle( title[AdNo].c_str() );
    h[AdNo]->SetName( title[AdNo].c_str() );
    h[AdNo]->Draw("E");
    
    cout<<"Alpha: "<<Alpha[AdNo]<<" +/- "<<Alpha_e[AdNo]<<"\t"
	<<"LambdaCap: "<<LambdaCap[AdNo]<<" +/- "<<LambdaCap_e[AdNo]<<"\t"
	<<"LambdaGen: "<<LambdaGen[AdNo]<<" +/- "<<LambdaGen_e[AdNo]<<endl;
    c->Print( (title[AdNo]+".ps").c_str() );
  }

  /* Calculate average with the first 3 ADs */
  double Alpha_ave = 0, Alpha_ttl_w = 0;
  double LambdaCap_ave = 0, LambdaCap_ttl_w = 0;
  double LambdaGen_ave = 0, LambdaGen_ttl_w = 0;
  double w;
  for( int AdNo = 1; AdNo<nAd; AdNo++ )  {
    w = (1/Alpha_e[AdNo])*(1/Alpha_e[AdNo]);
    Alpha_ttl_w += w;
    Alpha_ave += Alpha[AdNo] * w;

    w = (1/LambdaCap_e[AdNo])*(1/LambdaCap_e[AdNo]);
    LambdaCap_ttl_w += w;
    LambdaCap_ave += LambdaCap[AdNo] * w;

    w = (1/LambdaGen_e[AdNo])*(1/LambdaGen_e[AdNo]);
    LambdaGen_ttl_w += w;
    LambdaGen_ave += LambdaGen[AdNo] * w;
  }
  Alpha_ave = Alpha_ave/Alpha_ttl_w;
  LambdaCap_ave = LambdaCap_ave/LambdaCap_ttl_w;
  LambdaGen_ave = LambdaGen_ave/LambdaGen_ttl_w;

  cout<<"Average: "<<endl;
  cout<<"Alpha: "<<Alpha_ave<<"\t"
      <<"LambdaCap: "<<LambdaCap_ave<<"\t"
      <<"LambdaGen: "<<LambdaGen_ave<<endl;

  TGraphErrors * gAlpha = new TGraphErrors(nAd,x,Alpha,x_e,Alpha_e);
  gAlpha->SetTitle("Alpha");
  gAlpha->SetMarkerColor(4);
  gAlpha->SetMarkerStyle(21);
  TCanvas* cAlpha = new TCanvas;
  gAlpha->GetXaxis()->SetTitle("Ad Number");
  gAlpha->GetYaxis()->SetTitle("Alpha");
  gAlpha->Draw("ALP");
  cAlpha->Print("Alpha.ps");
  
  TGraphErrors * gLambdaCap = new TGraphErrors(nAd,x,LambdaCap,x_e,LambdaCap_e);
  gLambdaCap->SetTitle("LambdaCap [1/s]");
  gLambdaCap->SetMarkerColor(4);
  gLambdaCap->SetMarkerStyle(21);
  TCanvas* cLambdaCap = new TCanvas;
  gLambdaCap->GetXaxis()->SetTitle("Ad Number");
  gLambdaCap->GetYaxis()->SetTitle("LambdaCap");
  gLambdaCap->GetYaxis()->SetTitleOffset(1.3);
  gLambdaCap->Draw("ALP");
  cLambdaCap->Print("LambdaCap.ps");

  TGraphErrors * gLambdaGen = new TGraphErrors(nAd,x,LambdaGen,x_e,LambdaGen_e);
  gLambdaGen->SetTitle("LambdaGen [1/s]");
  gLambdaGen->SetMarkerColor(4);
  gLambdaGen->SetMarkerStyle(21);
  TCanvas* cLambdaGen = new TCanvas;
  gLambdaGen->GetXaxis()->SetTitle("Ad Number");
  gLambdaGen->GetYaxis()->SetTitle("LambdaGen");
  gLambdaGen->Draw("ALP");
  cLambdaGen->Print("LambdaGen.ps");

}
