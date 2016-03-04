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
    //"MCCorr.root",
    "MC.root",
    "AD1.root",
    "AD2.root",
    "AD3.root",
    "AD4.root",
    "AD5.root",
    "AD6.root",
  };

  TH1F *dist[7];
  TH1F *distX[7];
  TH1F *distY[7];
  TH1F *distZ[7];

  
  TH1::AddDirectory(kFALSE);
  for( int ad=0; ad<=6; ad++ ) {
    TFile f( file[ad].c_str() );
    dist[ad] = (TH1F*)f.Get( "dist" );
    dist[ad]->SetDirectory(0);
    distX[ad] = (TH1F*)f.Get( "distX" );
    distX[ad]->SetDirectory(0);
    distY[ad] = (TH1F*)f.Get( "distY" );
    distY[ad]->SetDirectory(0);
    distZ[ad] = (TH1F*)f.Get( "distZ" );
    distZ[ad]->SetDirectory(0);
    
    f.Close();
  }

  for( int ad=0; ad<=6; ad++ ) {
    double scale = 1.0/dist[ad]->Integral(7,17);
    dist[ad]->Scale(scale);
    distX[ad]->Scale(scale);
    distY[ad]->Scale(scale);
    distZ[ad]->Scale(scale);
  }

  //////////////////////////////
  // Compare 12
  TCanvas *cdist = new TCanvas();  
  dist[1]->Draw("p");

  for( int ad=0; ad<=2; ad++ ) {
    
    if( ad==0 )  {
      dist[ad]->Draw("same");
    } else {
      dist[ad]->SetMarkerStyle(26+ad);
      dist[ad]->SetMarkerSize(1);
      dist[ad]->Draw("samep");
    }
  }

  TLegend*  legComp12 = new TLegend(0.3,0.5,0.48,0.8);
  //legComp12->SetHeader("Poisson Distribution");
  //legComp12->AddEntry(dist[0],"MC" ,"lp");
  legComp12->AddEntry(dist[1],"AD1","p");
  legComp12->AddEntry(dist[2],"AD2","p");
  legComp12->SetTextSize(0.04);
  legComp12->Draw(); 

  cdist->Print("DComp12.ps");

  // Compare 12  XXXXXXX
  {
    TCanvas *cdistX = new TCanvas();
    distX[0]->GetXaxis()->SetTitle("Xpmt-Xdelay [mm]");
    distX[0]->GetYaxis()->SetTitle("Entries/40mm");
    distX[0]->Draw("p");
    
    for( int ad=0; ad<=2; ad++ ) {
      cout<<ad<<endl;
      
      if( ad==0 ) {
	distX[ad]->Draw("same");
      } else {
	distX[ad]->SetMarkerStyle(26+ad);
	distX[ad]->SetMarkerSize(1);
	distX[ad]->Draw("samep");
      }
    }
    
    TLegend*  legCompX12 = new TLegend(0.7,0.5,0.88,0.8);
    legCompX12->AddEntry(dist[0],"MC" ,"lp");
    legCompX12->AddEntry(dist[1],"AD1","p");
    legCompX12->AddEntry(dist[2],"AD2","p");
    legCompX12->SetTextSize(0.04);
    legCompX12->Draw();
  
    cdistX->Print("DXComp12.ps");
  }

  // Compare 12 YYYYYYY
  {
    TCanvas *cdistY = new TCanvas();
    distY[0]->GetXaxis()->SetTitle("Ypmt-Ydelay [mm]");
    distY[0]->GetYaxis()->SetTitle("Entries/40mm");
    distY[0]->Draw("p");
    
    for( int ad=0; ad<=2; ad++ ) {
      cout<<ad<<endl;
      
      if( ad==0 ) {
	distY[ad]->Draw("same");
      } else {
	distY[ad]->SetMarkerStyle(26+ad);
	distY[ad]->SetMarkerSize(1);
	distY[ad]->Draw("samep");
      }
    }
    
    TLegend*  legCompY12 = new TLegend(0.7,0.5,0.88,0.8);
    legCompY12->AddEntry(distY[0],"MC" ,"lp");
    legCompY12->AddEntry(distY[1],"AD1","p");
    legCompY12->AddEntry(distY[2],"AD2","p");
    legCompY12->SetTextSize(0.04);
    legCompY12->Draw();
    
    cdistY->Print("DYComp12.ps");
  }
  
  // Compare 12 ZZZZZZZ
  {
    TCanvas *cdistZ = new TCanvas();
    distZ[1]->GetXaxis()->SetTitle("Zpmt-Zdelay [mm]");
    distZ[1]->GetYaxis()->SetTitle("Entries/40mm");
    distZ[1]->Draw("p");

    for( int ad=0; ad<=2; ad++ ) {
      cout<<ad<<endl;
      
      if( ad==0 ) {
	distZ[ad]->Draw("same");
      } else {
	distZ[ad]->SetMarkerStyle(26+ad);
	distZ[ad]->SetMarkerSize(1);
	distZ[ad]->Draw("samep");
      }
    }
    
    TLegend*  legCompZ12 = new TLegend(0.7,0.5,0.88,0.8);
    legCompZ12->AddEntry(distZ[0],"MC" ,"lp");
    legCompZ12->AddEntry(distZ[1],"AD1","p");
    legCompZ12->AddEntry(distZ[2],"AD2","p");
    legCompZ12->SetTextSize(0.04);
    legCompZ12->Draw();
    
    cdistZ->Print("DZComp12.ps");
  }

  // Compare 4,5,6
  TCanvas *c456 = new TCanvas();
  dist[5]->Draw("p");

  for( int ad=4; ad<=6; ad++ ) {
    cout<<ad<<endl;

    dist[ad]->SetMarkerStyle(23+ad);
    dist[ad]->SetMarkerSize(1);
    dist[ad]->Draw("samep");
  }
  //dist[0]->Draw("same");
  TLegend*  legComp456 = new TLegend(0.3,0.5,0.48,0.8);
  //legComp456->SetHeader("Poisson Distribution");
  //legComp456->AddEntry(dist[0],"MC" ,"lp");
  legComp456->AddEntry(dist[4],"AD4","p");
  legComp456->AddEntry(dist[5],"AD5","p");
  legComp456->AddEntry(dist[6],"AD6","p");
  legComp456->SetTextSize(0.04);
  legComp456->Draw();

  c456->Print("DComp456.ps");


  const int nAD = 7;
  const int nbins = dist[0]->GetNbinsX();
  double energy [nbins];
  double energyE[nbins];
  
  double effi [nAD][nbins];
  double effiE[nAD][nbins];

  for( int bn=1; bn<=nbins; bn++ ) {
    energy [bn-1] = dist[0]->GetBinCenter(bn);
    energyE[bn-1] = 0;    
  }
  
  for( int ad=0; ad<nAD; ad++ ) {
    for( int bn=1; bn<=nbins; bn++ ) {
      double p = dist[ad]->Integral(1,bn)/dist[ad]->Integral(1,50);
      effi [ad][bn-1] = p;

      effiE[ad][bn-1] = sqrt(p*(1-p)/dist[ad]->Integral());
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

  cDiff->Print("Diff.ps");

  /// Corrrection function
  double correction[nbins];

  for( int bn=1; bn<=nbins; bn++ ) {
    double a = dist[0]->GetBinContent(bn);
    double b = dist[1]->GetBinContent(bn);
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

