#include <string>
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include <iostream>
#include "TStyle.h"

void Comp()
{
  gStyle->SetOptStat(0);

  string file[7] = {
    "MC.root",
    "AD1.root",
    "AD2.root",
    "AD3.root",
    "AD4.root",
    "AD5.root",
    "AD6.root",
  };

  TH1F *h[7];
  
  TH1::AddDirectory(kFALSE);
  for( int ad=0; ad<=6; ad++ ) {
    TFile f( file[ad].c_str() );
    h[ad] = (TH1F*)f.Get( "h" );    
    h[ad]->SetDirectory(0);
    f.Close();
  }

  for( int ad=0; ad<=6; ad++ ) {
    h[ad]->Scale(1/h[ad]->Integral(7,17));
  }

  // Compare 12
  TCanvas *c = new TCanvas();
  h[1]->Draw("p");

  for( int ad=0; ad<=2; ad++ ) {
    
    if( ad==0 )  {
      h[ad]->Draw("same");
    } else {
      h[ad]->SetMarkerStyle(26+ad);
      h[ad]->SetMarkerSize(1);
      h[ad]->Draw("samep");
    }
  }

  TLegend*  legComp12 = new TLegend(0.3,0.5,0.48,0.8);
  //legComp12->SetHeader("Poisson Distribution");
  legComp12->AddEntry(h[0],"MC" ,"lp");
  legComp12->AddEntry(h[1],"AD1","p");
  legComp12->AddEntry(h[2],"AD2","p");
  legComp12->SetTextSize(0.04);
  legComp12->Draw(); 

  c->Print("DComp12.ps");

  // Compare 4,5,6
  TCanvas *c456 = new TCanvas();
  h[5]->Draw("p");

  for( int ad=4; ad<=6; ad++ ) {

    h[ad]->SetMarkerStyle(23+ad);
    h[ad]->SetMarkerSize(1);
    h[ad]->Draw("samep");
  }
  h[0]->Draw("same");
  TLegend*  legComp456 = new TLegend(0.3,0.5,0.48,0.8);
  //legComp456->SetHeader("Poisson Distribution");
  legComp456->AddEntry(h[0],"MC" ,"lp");
  legComp456->AddEntry(h[4],"AD4","p");
  legComp456->AddEntry(h[5],"AD5","p");
  legComp456->AddEntry(h[6],"AD6","p");
  legComp456->SetTextSize(0.04);
  legComp456->Draw();

  c->Print("DComp456.ps");


  const int nAD = 7;
  const int nbins = h[0]->GetNbinsX();
  double energy [nbins];
  double energyE[nbins];
  
  double effi [nAD][nbins];
  double effiE[nAD][nbins];

  for( int bn=1; bn<=nbins; bn++ ) {
    energy [bn-1] = h[0]->GetBinCenter(bn);
    energyE[bn-1] = 0;    
  }
  
  for( int ad=0; ad<nAD; ad++ ) {
    for( int bn=1; bn<=nbins; bn++ ) {
      double p = h[ad]->Integral(1,bn)/h[ad]->Integral();
      effi [ad][bn-1] = p;

      effiE[ad][bn-1] = sqrt(p*(1-p)/h[ad]->Integral());
      effiE[ad][bn-1] = 0;
    }
  }
  TCanvas *cEffi = new TCanvas("Effi","Effi");
  TGraphErrors *gEffiAD1 = new TGraphErrors( nbins, energy, effi[1], energyE, effiE[1] );
  TGraphErrors *gEffiAD2 = new TGraphErrors( nbins, energy, effi[2], energyE, effiE[2] );
  TGraphErrors *gEffiAD3 = new TGraphErrors( nbins, energy, effi[3], energyE, effiE[3] );

  
  TMultiGraph *mg = new TMultiGraph();
  gEffiAD1->SetLineStyle(1);
  mg->Add(gEffiAD1,"lp");
  gEffiAD2->SetLineStyle(2);
  mg->Add(gEffiAD2,"lp");
  mg->Draw("A");
  mg->GetXaxis()->SetTitle("Distance [mm]");
  mg->GetYaxis()->SetTitle("Efficiency");
  TLegend*  legEffi = new TLegend(0.5,0.5,0.7,0.8);
  //legEffi->SetHeader("Poisson Distribution");
  legEffi->AddEntry(gEffiAD1,"AD1","l");
  legEffi->AddEntry(gEffiAD2,"AD2","l");
  legEffi->SetTextSize(0.04);
  legEffi->Draw();

  cEffi->Print("Effi.ps");


  //////////////////////////////////////////////
  double AD12Diff [nbins];
  double AD12DiffE[nbins];

  for( int bn=1; bn<=nbins; bn++ ) {
    double a =effi [1][bn-1];
    double ae=effiE[1][bn-1];
    double b =effi [2][bn-1];
    double be=effiE[2][bn-1];
    double diff = (a-b)/(a+b);
    AD12Diff[bn-1] = diff;

    double deri = diff*(1/(a+b)-(a-b));
    AD12DiffE[bn-1]= sqrt( pow(deri*ae,2) + pow(deri*be,2) );
    AD12DiffE[bn-1]=0;
  }

  TCanvas *cDiff = new TCanvas("Diff","Diff");
  TGraphErrors *gAD12Diff = new TGraphErrors( nbins, energy, AD12Diff, energyE, AD12DiffE );
  gAD12Diff->SetMarkerStyle(20);
  gAD12Diff->SetMarkerColor(2);
  gAD12Diff->Draw("ALP");
  gAD12Diff->GetXaxis()->SetTitle("Distance [mm]");
  gAD12Diff->GetYaxis()->SetTitle("Efficiency difference");
  gAD12Diff->GetYaxis()->SetRangeUser(-0.01,0.01);

  cDiff->Print("Diff12.ps");

  ////// Difference between AD and MC
  double ADMCDiff [nbins];
  double ADMCDiffE[nbins];

  for( int bn=1; bn<=nbins; bn++ ) {
    double a =effi [0][bn-1];
    double ae=effiE[0][bn-1];
    double b =(effi [2][bn-1]+effi [1][bn-1])/2;
    double be=effiE[2][bn-1];
    double diff = (a-b)/(a+b);
    ADMCDiff[bn-1] = diff;

    double deri = diff*(1/(a+b)-(a-b));
    ADMCDiffE[bn-1]= sqrt( pow(deri*ae,2) + pow(deri*be,2) );
    ADMCDiffE[bn-1]=0;
  }

  TCanvas *cDiffMC = new TCanvas("DiffMC","DiffMC");
  TGraphErrors *gADMCDiff = new TGraphErrors( nbins, energy, ADMCDiff, energyE, ADMCDiffE );
  gADMCDiff->SetMarkerStyle(20);
  gADMCDiff->SetMarkerColor(2);
  gADMCDiff->Draw("ALP");
  gADMCDiff->GetXaxis()->SetTitle("Distance [mm]");
  gADMCDiff->GetYaxis()->SetTitle("Efficiency difference");
  gADMCDiff->GetYaxis()->SetRangeUser(-0.03,0.03);

  cDiffMC->Print("DiffADMC.ps");

  /// Corrrection function
  double correction[nbins];

  for( int bn=1; bn<=nbins; bn++ ) {
    double a = h[0]->GetBinContent(bn);
    double b = (h[1]->GetBinContent(bn)+h[2]->GetBinContent(bn))/2;
    correction[bn-1] = a<1e-9 ? 0 : b/a;
  }

  TCanvas *cCorr = new TCanvas("Corr","Corr");
  TGraphErrors *gCorr = new TGraphErrors( nbins, energy, correction, energyE, energyE );
  gCorr->SetMarkerStyle(20);
  gCorr->SetMarkerColor(2);
  gCorr->Draw("ALP");
  gCorr->GetXaxis()->SetTitle("Distance [mm]");
  gCorr->GetYaxis()->SetTitle("Correction");
  //  gCorr->GetYaxis()->SetRangeUser(-0.01,0.01);

  cCorr->Print("Corr.ps");
}
