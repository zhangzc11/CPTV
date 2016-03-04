#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

string i2a(int intValue) {

  ostringstream oss (ostringstream::out);
  oss <<intValue;
  string strRetVal=oss.str();
  return(strRetVal);
};


int Extract()
{
  gStyle->SetOptStat("");
  
  const int nSite = 3;
  const int nAd[nSite] = {2,1,3};
  /*  
  const string record[nSite] = { "../data/Sample/P12b/H/EH1.root",
                                 "../data/Sample/P12b/H/EH2.root",
                                 "../data/Sample/P12b/H/EH3.root" };
  */
  /*
  const string record[nSite] = { "../data/Sample/P12b-ext/H/EH1.root",
				 "../data/Sample/P12b-ext/H/EH2.root",
				 "../data/Sample/P12b-ext/H/EH3.root" }; 
  */
  /*
  const string record[nSite] = { "../data/Sample/P12e_1.5MeV_P12b/H/EH1.root",
				 "../data/Sample/P12e_1.5MeV_P12b/H/EH2.root",
				 "../data/Sample/P12e_1.5MeV_P12b/H/EH3.root" };
  */
  /*
  const string record[nSite] = { "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH1.root",
				 "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH2.root",
				 "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH3.root" };
  */
  const string record[nSite] = { "../data/Sample/P12e_1.5MeV/H/EH1.root",
				 "../data/Sample/P12e_1.5MeV/H/EH2.root",
				 "../data/Sample/P12e_1.5MeV/H/EH3.root" };
  
  string SiteName[3] = { "EH1", "EH2", "EH3" };
  string AdName[4]   = { "AD1", "AD2", "AD3", "AD4" };

  for( int site = 1; site<=nSite; site++ )  {
    TFile file( record[site-1].c_str() );

    /* Everything plots */
    string all_name = "h2dAllSum";
    TH2F *h2dAll = (TH2F*)file.Get( all_name.c_str() );
    TCanvas * cAll = new TCanvas("","",500,500);
    cAll->SetLogz();
    cAll->SetMargin(0.15,0.15,0.1,0.1);
    h2dAll->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h2dAll->GetYaxis()->SetTitle("Delayed Energy [MeV]");
    h2dAll->SetTitle( (SiteName[site-1]).c_str() );
    h2dAll->DrawCopy("colz");
    cAll->Print( (SiteName[site-1]+"_all.ps").c_str() );

    /* After the relative distance cut */
    string vtx_name = "h2dVtxSum";
    TH2F *h2dVtx = (TH2F*)file.Get( vtx_name.c_str() );
    TCanvas * cVtx = new TCanvas("","",500,500);
    cVtx->SetLogz();
    cVtx->SetMargin(0.15,0.15,0.1,0.1);
    h2dVtx->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h2dVtx->GetYaxis()->SetTitle("Delayed Energy [MeV]");
    h2dVtx->SetTitle( (SiteName[site-1]).c_str() );
    h2dVtx->DrawCopy("colz");
    cVtx->Print( (SiteName[site-1]+"_vtx.ps").c_str() );

    /* Acc background spectrum */
    string AccBkg_name = "h2dAccBkgSum";
    TH2F *h2dAccBkgSum = (TH2F*)file.Get( AccBkg_name.c_str() );
    TCanvas * cAccBkg = new TCanvas("","",500,500);
    cAccBkg->SetLogz();
    cAccBkg->SetMargin(0.15,0.15,0.1,0.1);
    h2dAccBkgSum->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h2dAccBkgSum->GetYaxis()->SetTitle("Delayed Energy [MeV]");
    h2dAccBkgSum->SetTitle( (SiteName[site-1]).c_str() );
    h2dAccBkgSum->DrawCopy("colz");
    cAccBkg->Print( (SiteName[site-1]+"_AccBkg.ps").c_str() );

    

    /* After background subtraction */
    string acc_name = "h2dAccSum";
    TH2F *h2dAcc = (TH2F*)file.Get( acc_name.c_str() );
    TCanvas * cAcc = new TCanvas("","",500,500);
    cAcc->SetLogz();
    cAcc->SetMargin(0.15,0.15,0.1,0.1);
    h2dAcc->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h2dAcc->GetYaxis()->SetTitle("Delayed Energy [MeV]");
    h2dAcc->SetTitle( (SiteName[site-1]).c_str() );
    h2dAcc->DrawCopy("colz");
    cAcc->Print( (SiteName[site-1]+"_acc.ps").c_str() );

    /* Acc background in 22 region */
    string accBkg22_name = "h1dAccBkg22Sum";
    TH1F *h1dAccBkg22 = (TH1F*)file.Get( accBkg22_name.c_str() );
    TCanvas * cAccBkg22 = new TCanvas("","",500,500);
    cAccBkg22->SetMargin(0.15,0.15,0.1,0.1);
    //h1dAccBkg22->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    //h1dAccBkg22->GetYaxis()->SetTitle("Entries");
    h1dAccBkg22->SetTitle( (SiteName[site-1]).c_str() );
    h1dAccBkg22->DrawCopy();
    cAccBkg22->Print( (SiteName[site-1]+"_accBkg22.ps").c_str() );

    /* Its projections on Y axis. */
    TH1D *h1dNeuVtx = h2dVtx->ProjectionY();
    TCanvas * cNeuVtx = new TCanvas("","",500,500);
    cNeuVtx->SetMargin(0.15,0.15,0.1,0.1);
    h1dNeuVtx->DrawCopy();    
    cNeuVtx->Print( (SiteName[site-1]+"_NeuVtx.ps").c_str() );
    
    /* The 2.2 MeV slice */
    string vtx22_name = "h1dVtx22Sum";
    TH1F *h1dVtx22 = (TH1F*)file.Get( vtx22_name.c_str() );
    TCanvas * cVtx22 = new TCanvas("","",500,500);
    cVtx22->SetMargin(0.15,0.15,0.1,0.1);
    h1dVtx22->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h1dVtx22->DrawCopy();
    cVtx22->Print( (SiteName[site-1]+"_vtx22.ps").c_str() );

    
    for( int ad = 1; ad<=nAd[site-1]; ad++ )  {

      /* Everything plots */      
      string all_name = "h2dAll_"+i2a(ad);
      TH2F *h2dAll = (TH2F*)file.Get( all_name.c_str() );
      TCanvas * cAll = new TCanvas("","",500,500);
      cAll->SetLogz();
      cAll->SetMargin(0.15,0.15,0.1,0.1);
      h2dAll->GetXaxis()->SetTitle("Prompt Energy [MeV]");
      h2dAll->GetYaxis()->SetTitle("Delayed Energy [MeV]");
      h2dAll->SetTitle( (SiteName[site-1]+" "+AdName[ad-1]).c_str() );
      h2dAll->DrawCopy("colz");
      cAll->Print( (SiteName[site-1]+"_"+AdName[ad-1]+"_all.ps").c_str() );
      
      string histo22_name = "h1dAcc22_"+i2a(ad);
      string histo8_name = "h1dAcc8_"+i2a(ad);

      TH1F *hAcc22Sum = (TH1F*)file.Get( histo22_name.c_str() );
      TH1F *hAcc8Sum = (TH1F*)file.Get( histo8_name.c_str() );
    
      /// Take a look at them
      TCanvas * can = new TCanvas("","",500,500);
      hAcc8Sum->DrawCopy();
      hAcc22Sum->DrawCopy("same");

      /* Get the total area and statistical errors */
      double N22=0, E22=0;
      double N8=0, E8=0;

      unsigned int nbin = hAcc22Sum->GetNbinsX();
      for( unsigned int idx = 1; idx<=nbin; idx++ )  {
	N22 += hAcc22Sum->GetBinContent(idx);
	E22 += hAcc22Sum->GetBinError(idx) * hAcc22Sum->GetBinError(idx);
	
	N8 += hAcc8Sum->GetBinContent(idx);
        E8 += hAcc8Sum->GetBinError(idx) * hAcc8Sum->GetBinError(idx);
      }
      
      E22 = sqrt(E22);
      E8 = sqrt(E8);
      cout<<"Site: "<<site<<" AD: "<<ad<<"   2.2MeV - "<<N22<<"+/-"<<E22<<"   8MeV - "<<N8<<"+/-"<<E8<<endl;

      /// Neutron energy distribution after background subtraction
      string h1dNeutron_name = "h1dNeutron_"+i2a(ad);
      TH1F* h1dNeutron = (TH1F*)file.Get( h1dNeutron_name.c_str() );
      TCanvas * c1dNeutron = new TCanvas("","",500,500);
      c1dNeutron->SetMargin(0.15,0.15,0.1,0.1);
      h1dNeutron->GetYaxis()->SetTitleOffset(1.4);
      h1dNeutron->DrawCopy();
      c1dNeutron->Print( (SiteName[site-1]+i2a(ad)+"_1dNeutron.ps").c_str() );

      /* After background subtraction */
      string acc_name = "h2dAcc_"+i2a(ad);;
      TH2F *h2dAcc = (TH2F*)file.Get( acc_name.c_str() );
      TCanvas * c2dAcc = new TCanvas("","",500,500);
      c2dAcc->SetLogz();
      c2dAcc->SetMargin(0.15,0.15,0.1,0.1);
      h2dAcc->GetXaxis()->SetTitle("Prompt Energy [MeV]");
      h2dAcc->GetYaxis()->SetTitle("Delayed Energy [MeV]");
      h2dAcc->SetTitle( (SiteName[site-1]).c_str() );
      h2dAcc->DrawCopy("colz");
      c2dAcc->Print( (SiteName[site-1]+i2a(ad)+"_2dAcc.ps").c_str() );

      /// 2.2 MeV band prompt energy distribution 
      string h1dAcc22_name = "h1dAcc22_"+i2a(ad);
      TH1F* h1dAcc22 = (TH1F*)file.Get( h1dAcc22_name.c_str() );
      TCanvas * c1dAcc22 = new TCanvas("","",500,500);
      c1dAcc22->SetMargin(0.15,0.15,0.1,0.1);
      h1dAcc22->GetYaxis()->SetTitleOffset(1.3);
      h1dAcc22->DrawCopy();
      c1dAcc22->Print( (SiteName[site-1]+i2a(ad)+"_1dAcc22.ps").c_str() );

      /// Vertex distribution for 2.2 signals
      string h2dZR2Acc_name = "h2dZR2Acc_"+i2a(ad);
      TH2F* h2dZR2Acc = (TH2F*)file.Get( h2dZR2Acc_name.c_str() );
      h2dZR2Acc   ->GetXaxis()->SetTitle("R^{2} [mm^{2}]");
      h2dZR2Acc   ->GetYaxis()->SetTitle("Z [mm]");
      h2dZR2Acc   ->GetYaxis()->SetTitleOffset(1.4);
      TCanvas * c2dZR2Acc = new TCanvas("","",500,500);
      c2dZR2Acc->SetMargin(0.15,0.15,0.1,0.1);
      h2dZR2Acc->DrawCopy("colz");
      c2dZR2Acc->Print( (SiteName[site-1]+i2a(ad)+"_2dZR2Acc.ps").c_str() );

      /// 2.2 MeV band prompt energy distribution, before AccSum and AccBkg
      string h1dVtx22_name = "h1dVtx22_"+i2a(ad);
      TH1F* h1dVtx22 = (TH1F*)file.Get( h1dVtx22_name.c_str() );
      string h1dAccBkg22_name = "h1dAccBkg22_"+i2a(ad);
      TH1F* h1dAccBkg22 = (TH1F*)file.Get( h1dAccBkg22_name.c_str() );

      TCanvas * c1dSub22 = new TCanvas("","",500,500);
      c1dSub22->SetMargin(0.15,0.15,0.1,0.1);
      h1dVtx22->GetYaxis()->SetTitleOffset(1.3);
      h1dVtx22->DrawCopy();
      h1dAccBkg22->DrawCopy("same");
      c1dSub22->Print( (SiteName[site-1]+i2a(ad)+"_1dSub22.ps").c_str() );

     }
  }

  return 1;
}
