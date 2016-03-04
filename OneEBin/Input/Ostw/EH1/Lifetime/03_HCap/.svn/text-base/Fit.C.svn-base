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
  //gStyle->SetStatH(0.5);
  //gStyle->SetStatW(0.6);
  //gROOT->ProcessLine(".L CapT.C");

  TF1 HCapT_F("HCapT", CapT, 0, 1500e-6, 3);

  HCapT_F.SetParNames  ("N", "LambdaCap","FlatBkg");

  HCapT_F.SetParLimits( 2, 0, 10000);

  //  TFile f("EH1_AD1.root");
  //  h->Fit("HCapT","","",5e-6,800e-6);
  //  return;

  const int TotalNo = 7;

  string file[7] = {
    "../01_MakeHisto/ForBi214/EH0_AD1.root",
    "../01_MakeHisto/Bi214/EH1_AD1.root",
    "../01_MakeHisto/Bi214/EH1_AD2.root",
    "../01_MakeHisto/Bi214/EH2_AD1.root",
    "../01_MakeHisto/Bi214/EH3_AD1.root",
    "../01_MakeHisto/Bi214/EH3_AD2.root",
    "../01_MakeHisto/Bi214/EH3_AD3.root"
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
  double x[7];
  double x_e[7] = {0,0,0,0,0,0,0};
  double LambdaCap[7], LambdaCap_e[7];
  double Background[7], Background_e[7];

  for( int AdNo = 0; AdNo<TotalNo; AdNo++ )  {

    cout<<file[AdNo]<<endl;

    TFile f( file[AdNo].c_str() );
    h[AdNo] = (TH1F*)f.Get("h");

    HCapT_F.SetParameters(0.02, 4700     ,1);
    h[AdNo]->Fit("HCapT","L","",5e-6,1500e-6);

    x[AdNo]         = AdNo;

    LambdaCap[AdNo]   = HCapT_F.GetParameter(1);
    LambdaCap_e[AdNo] = HCapT_F.GetParError(1);
    
    Background[AdNo]  = HCapT_F.GetParameter(2);
    Background_e[AdNo]= HCapT_F.GetParError(2);
    f.Close();
  }
  
  for( int AdNo = 0; AdNo<TotalNo; AdNo++ )  {
    
    TCanvas* c = new TCanvas(file[AdNo].c_str(),file[AdNo].c_str());
    c->SetLogy();
    h[AdNo]->GetXaxis()->SetTitle("Capture time [s]");
    h[AdNo]->GetYaxis()->SetTitle("Entries / 3e-6 s");
    h[AdNo]->GetYaxis()->SetTitleOffset(1.2);
    h[AdNo]->SetTitle( title[AdNo].c_str() );
    h[AdNo]->SetName( title[AdNo].c_str() );
    h[AdNo]->Draw("E");
    
    cout<<"LambdaCap: "<<LambdaCap[AdNo]<<"+/-"<<LambdaCap_e[AdNo]
	<<"\t Background: "<<Background[AdNo]<<"+/-"<<Background_e[AdNo]<<endl;

    c->Print( (title[AdNo]+".ps").c_str() );
  }

  /* Calculate average with the first 3 ADs */
  double LambdaCap_ave = 0, LambdaCap_ttl_w = 0; 
  double LambdaCap_ave_err;
  double w;
  for( int AdNo = 1; AdNo<=6; AdNo++ )  {

    w = (1/LambdaCap_e[AdNo])*(1/LambdaCap_e[AdNo]);
    LambdaCap_ttl_w += w;
    LambdaCap_ave += LambdaCap[AdNo] * w;
  }
  LambdaCap_ave = LambdaCap_ave/LambdaCap_ttl_w;
  LambdaCap_ave_err = sqrt(1/LambdaCap_ttl_w);

  cout<<"Average: "<<endl;
  cout<<"LambdaCap: "<<LambdaCap_ave<<" +- "<<LambdaCap_ave_err<<endl;
  

  TGraphErrors* gLambdaCap = new TGraphErrors(TotalNo-1,&x[1],&LambdaCap[1],&x_e[1],&LambdaCap_e[1]);
  gLambdaCap->SetTitle("LambdaCap");
  gLambdaCap->SetMarkerColor(4);
  gLambdaCap->SetMarkerStyle(21);
  TCanvas* cLambdaCap = new TCanvas;
  gLambdaCap->GetXaxis()->SetTitle("Ad Number");
  gLambdaCap->GetYaxis()->SetTitle("1/Capture time [1/s]");
  gLambdaCap->GetYaxis()->SetTitleOffset(1.3);
  gLambdaCap->Draw("ALP");
  cLambdaCap->Print("LambdaCap.ps");
}
