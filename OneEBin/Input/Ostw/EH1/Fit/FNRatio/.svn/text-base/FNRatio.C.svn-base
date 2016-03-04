#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TLine.h"
#include <iostream>
#include "TStyle.h"
#include "TGraphErrors.h"

using namespace std;

double SurvProb( double t13, double baseline /* m */, double Enu /* MeV */)
{
  double s_2_2_13 = t13;  /* sin^2(2theta13) */

  double delta_M31_2 = 2.32e-3;
  double delta_M21_2 = 7.59e-5;
  double s_2_2_12 = 0.83;

  // First term                                                                                                                                    
  double Pee = 1;

  // Second term                                                                                                                                   
  double delta31 = 1.267 * delta_M31_2 * baseline / Enu ;
  double second = - s_2_2_13 * pow( sin( delta31 ), 2 );

  // Third term                                                                                                                                    
  double delta21 = 1.267 * delta_M21_2 * baseline / Enu ;
  double c_1_2_13 = sqrt( 1 - s_2_2_13 );
  double c_4_1_13 = (c_1_2_13 + 1)/2 * (c_1_2_13 + 1)/2;

  double third = - c_4_1_13 * s_2_2_12 * pow( sin( delta21 ), 2 );

  //std::cout<<"In SurvProb "<<Pee<<" "<<second<<" "<<third<<std::endl;                                                                            
  Pee = Pee + second + third;

  return Pee;
}

void FNRatio()
{
  TH1::AddDirectory(kFALSE); /* Without this fitted histogram will be lost after return*/
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TH1::SetDefaultSumw2(kTRUE);

  /* P12e 0: Gd; 1: H */
  TFile file("../fit13/nHresult.root");

  double con[3][3] = {
    /*
    {0.121463, 0.119577, 0.130696},
    {0.121421, 0.119535, 0.130651},
    {0.120598, 0.118725, 0.129765}
    */
    {0.117905,   0.116036,   0.132538 },
    {0.117825,   0.115957,   0.132448 },
    {0.117078,   0.115222,   0.131608 }
  };

  double wei[3][3] = {
    /*
    {1.18103e-05, 1.16731e-05, 1.22165e-05},
    {1.18103e-05, 1.16731e-05, 1.22165e-05},
    {1.18103e-05, 1.16731e-05, 1.22165e-05}
    */
    {7.90887e-06,  7.81444e-06,   8.54657e-06 },
    {7.90887e-06,  7.81444e-06,   8.54657e-06 },
    {7.90887e-06,  7.81444e-06,   8.54657e-06 }
  };

  /* 0 - Gd, 1 - H */
  double Eff[2][6] = {  /* Mu veto and Ostw efficiency */
    {0.8078,0.8046,0.8403,0.9616,0.9615,0.9610},
    {0.7816,0.7783,0.8206,0.9651,0.9646,0.9642}
  };

  string sig = "sig";
  string st[2] = { "0", "1" };
  string no[6] = { "1", "2", "3", "4", "5", "6" };
  string Measurement = "Measurement";
  string Background = "Background";
  string predictn = "predict";

  TH1F*  MeasuSpec[2][ 6 ];
  TH1F*  BkgSpec  [2][ 6 ];
  TH1F*  signal[2][6];
  TH1F*  predict[2][3]; // prediction for ad 4,5,6

  int bins = 60;
  int rebin = (120+1.0)/bins;
  cout<<rebin<<endl;

  for( int set=0; set<=1; set++ ) {
    for( int ad=1; ad<=6; ad++ ) {
      MeasuSpec[set][ad-1] = (TH1F*) file.Get( (Measurement+"_"+st[set]+no[ad-1]).c_str() );
      BkgSpec  [set][ad-1] = (TH1F*) file.Get( (Background+"_"+st[set]+no[ad-1]).c_str() );
      MeasuSpec[set][ad-1]->Rebin(rebin);
      BkgSpec  [set][ad-1]->Rebin(rebin);

      signal[set][ad-1] = new TH1F( (sig+"_"+st[set]+no[ad-1]).c_str(), (sig+"_"+st[set]+no[ad-1]).c_str(), bins, 0, 12);
      signal[set][ad-1]->Add( MeasuSpec[set][ad-1], BkgSpec[set][ad-1], 1, -1 );
    }

    for( int ad=4; ad<=6; ad++ ) {  // only for far site ads

      predict[set][ad-4] = new TH1F( (predictn+"_"+st[set]+no[ad-1]).c_str(), (predictn+"_"+st[set]+no[ad-1]).c_str(), bins, 0, 12);

      double totwei = wei[ad-4][0]+wei[ad-4][1]+wei[ad-4][2];
      predict[set][ad-4]->Add( signal[set][0], con[ad-4][0] * wei[ad-4][0]/totwei * Eff[set][ad-1]/Eff[set][0] );
      predict[set][ad-4]->Add( signal[set][1], con[ad-4][1] * wei[ad-4][1]/totwei * Eff[set][ad-1]/Eff[set][1] );
      predict[set][ad-4]->Add( signal[set][2], con[ad-4][2] * wei[ad-4][2]/totwei * Eff[set][ad-1]/Eff[set][2] );
    }
  }

  TCanvas * c;
  /*
  c = new TCanvas;
  MeasuSpec[1][0]->Draw("E");
  c = new TCanvas;
  MeasuSpec[1][1]->Draw("E");
  c = new TCanvas;
  MeasuSpec[1][2]->Draw("E");

  c = new TCanvas;
  BkgSpec[1][0]->Draw("E");
  c = new TCanvas;
  BkgSpec[1][1]->Draw("E");
  c = new TCanvas;
  BkgSpec[1][2]->Draw("E");
  */

  c = new TCanvas;
  signal[1][0]->Draw("E");
  c = new TCanvas;
  signal[1][1]->Draw("E");
  c = new TCanvas;
  signal[1][2]->Draw("E");
  
  cout<<signal[1][0]->GetBinContent(30)<<" "<<signal[1][0]->GetBinError(30)<<endl;
  cout<<signal[1][1]->GetBinContent(30)<<" "<<signal[1][1]->GetBinError(30)<<endl;
  cout<<signal[1][2]->GetBinContent(30)<<" "<<signal[1][2]->GetBinError(30)<<endl;
  
  c = new TCanvas;
  predict[1][0]->Draw("E");
  c = new TCanvas;
  predict[1][1]->Draw("E");
  c = new TCanvas;
  predict[1][2]->Draw("E");

  cout<<predict[1][0]->GetBinContent(30)<<" "<<predict[1][0]->GetBinError(30)<<endl;

  TH1F*  far[2];
  TH1F*  prd[2];
  TH1F*  rat[2];
  string farn = "far";
  string prdn = "prd";
  string ratn = "rat";

  for( int set=0; set<=1; set++ ) { /* 1 - nH, 0 - nGd */
    far[set] = new TH1F( (farn+"_"+st[set]).c_str(), (farn+"_"+st[set]).c_str(),bins, 0, 12);
    prd[set] = new TH1F( (prdn+"_"+st[set]).c_str(), (prdn+"_"+st[set]).c_str(),bins, 0, 12);
    rat[set] = new TH1F( (ratn+"_"+st[set]).c_str(), (ratn+"_"+st[set]).c_str(),bins, 0, 12);

    far[set]->Add( signal[set][3] );
    far[set]->Add( signal[set][4] );
    far[set]->Add( signal[set][5] );

    prd[set]->Add( predict[set][0] );
    prd[set]->Add( predict[set][1] );
    prd[set]->Add( predict[set][2] );

    for(int bin=1; bin<=prd[set]->GetNbinsX(); bin++) {
      prd[set]->SetBinError( bin, 
			     prd[set]->GetBinContent(bin)
			     * predict[set][0]->GetBinError(bin)
			     / predict[set][0]->GetBinContent(bin) );
      if( bin<=8 )
	prd[set]->SetBinError( bin, 0);
    }

    rat[set]->Divide( far[set], prd[set] );
  }

  TCanvas * cGd = new TCanvas("Gd");
  far[0]->Draw();
  prd[0]->Draw("same");
  
  TCanvas * cGdr = new TCanvas("Gdr");
  rat[0]->Draw();
  
  // Start to plot
  TCanvas * cH = new TCanvas("H","FNH",650,650);
  TPad* m = new TPad("NF","Near and Far",      0, 0.4, 1, 1  );
  TPad* s = new TPad("Rt","Far to Near ratio", 0, 0,   1, 0.4);
  
  /* ******* Upper plot ****** */
  m->Draw();
  s->Draw();

  m->cd();
  m->SetBottomMargin(0.0);
  m->SetLeftMargin(0.15);
  m->SetRightMargin(0.1);
  far[1]->GetYaxis()->SetRangeUser(-100, 1900);
  far[1]->GetXaxis()->SetRangeUser(1, 12);
  far[1]->GetYaxis()->SetTitle("Entries / 0.5 MeV");
  far[1]->GetYaxis()->SetLabelSize(0.05);
  far[1]->GetYaxis()->SetTitleSize(0.055);
  far[1]->GetYaxis()->SetTitleOffset(1.1);
  //far[1]->GetXaxis()->SetTitle("Detected Energy [MeV]");
  far[1]->SetMarkerStyle(20);
  far[1]->SetLineWidth(2);
  far[1]->SetLineColor(kBlue);
  far[1]->SetMarkerColor(kBlue);  
  far[1]->SetMarkerSize(0.7);
  far[1]->Draw();

  prd[1]->SetMarkerStyle(4);
  prd[1]->SetMarkerSize(0.5);
  prd[1]->SetLineWidth(2);
  prd[1]->Draw("Esame");

  TLegend* leg = new TLegend(0.193, 0.054, 0.461, 0.234);
  leg->AddEntry( far[1], "Far hall", "lep" );
  leg->AddEntry( prd[1], "Near hall weighted", "lep" );
  //leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->Draw();

  /* ******* Lower plot ****** */
  s->cd();
  s->SetTopMargin(0);
  s->SetLeftMargin(0.15);
  s->SetBottomMargin(0.18);
  rat[1]->GetYaxis()->SetRangeUser(0.7,1.125);
  rat[1]->GetXaxis()->SetRangeUser(1, 12);
  rat[1]->GetYaxis()->SetTitle("Far/Near");
  rat[1]->GetYaxis()->SetTitleSize(0.08);
  rat[1]->GetYaxis()->SetTitleOffset(0.8);
  rat[1]->GetYaxis()->SetLabelSize(0.075);

  rat[1]->GetXaxis()->SetTitle("Detected Energy [MeV]");
  rat[1]->GetXaxis()->SetTitleSize(0.08);
  rat[1]->GetXaxis()->SetLabelSize(0.075);

  rat[1]->SetMarkerStyle(33);
  rat[1]->SetMarkerSize(1.5);
  /* mask these bins */
  for( int b=45; b<=bins; b++ ) {
    rat[1]->SetBinContent(b, 100);
  }
  rat[1]->Draw();

  TGraph* Disp;
  int npt = 40;
  double eng[40];
  double farP[40];
  double nearP[40];
  double lost[40];

  for( int dc=0; dc<npt; dc++ ) {
    eng[ dc ] = 1.3 + (8.5-1.3)/(npt-1) * dc;
    //cout<<eng[dc]<<endl;
    // Calculate the survival probability
    farP[dc]  = SurvProb( 8.3e-02, 1628, eng[dc]+0.782 );
    nearP[dc] = SurvProb( 8.3e-02,  513, eng[dc]+0.782 );
    lost[ dc ] = farP[dc]/nearP[dc];
  }
  Disp = new TGraph(npt, eng, lost);
  Disp->SetLineColor(kRed);
  Disp->SetLineWidth(2);
  Disp->Draw("lsame");

  TGraph* DispN = new TGraph(npt, eng, nearP);
  DispN->SetLineColor(kBlue);
  DispN->SetLineWidth(2);
  //DispN->Draw("lsame");

  TGraph* DispF = new TGraph(npt, eng, farP);
  DispF->SetLineColor(kGreen);
  DispF->SetLineWidth(2);
  //DispF->Draw("lsame");

  TLine line;
  line.SetLineStyle(2);
  line.DrawLine(1,1,12,1);

  TLegend* legs = new TLegend(0.65, 0.42, 0.89, 0.63);
  legs->AddEntry( Disp, "Best fit ratio", "lp" );
  //legs->SetLineColor(0);                                                                                                                         
  legs->SetFillColor(0);
  legs->Draw();

  /* ******* Small panel ****** */
  {
    m->cd();
    TPad* pad = new TPad("RatioDist","Ratio vs distance",0.44, 0.35, 0.95, 0.96);
    pad->Draw();
    pad->cd();
    pad->SetLeftMargin(0.25);
    pad->SetBottomMargin(0.18);

    double baseline[6]={0.496651, 0.491322, 0.554113, 1.62655-0.03, 1.62818, 1.6321+0.03};
    //double baseline[6]={0.571804, 0.567082, 0.592606, 1.63217-0.03, 1.63368, 1.63768+0.03};
    double be[6]={0,0,0,0,0,0};
    double ratio[6]={0.9834, 0.9849, 0.9864, 0.9282, 0.9086, 0.9571};
    //0.9834_0.0069 & 0.9849_0.0069 & 0.9864_0.0073 & 0.9282_0.0160 & 0.9086_0.0161 & 0.9571_0.0166
    double ratioe[6]={0.0069, 0.0069, 0.0073, 0.0160, 0.0161, 0.0166};

    double t13 =  8.3e-02;
    double t13e = 1.63739e-02;

    TGraphErrors *ratiog = new TGraphErrors(6,baseline, ratio, be, ratioe);

    pad->SetLeftMargin(0.15);
    ratiog->GetYaxis()->SetRangeUser(0.88,1.02);
    ratiog->GetXaxis()->SetLimits(0.0,2.0);
    ratiog->SetMarkerStyle(25);
    ratiog->SetLineColor(4);
    ratiog->SetLineWidth(2);
    ratiog->GetYaxis()->SetTitle("Meas./Pred.");
    ratiog->GetYaxis()->CenterTitle();
    ratiog->GetYaxis()->SetTitleOffset(1.5);
    ratiog->GetYaxis()->SetTitleSize(0.08);
    ratiog->GetYaxis()->SetTitleOffset(1);
    ratiog->GetYaxis()->SetLabelSize(0.075);
    ratiog->GetYaxis()->SetNdivisions(405);

    ratiog->GetXaxis()->SetTitle("Weighted baseline [km]");
    ratiog->GetXaxis()->SetTitleSize(0.08);
    ratiog->GetXaxis()->SetTitleOffset(1);
    ratiog->GetXaxis()->SetLabelSize(0.075);
    ratiog->GetXaxis()->CenterTitle();
    ratiog->GetXaxis()->SetNdivisions(405);

    ratiog->Draw("AP");


    TLine line;
    line.SetLineStyle(2);
    line.DrawLine(0,1,2,1);

    
    // Make the red curve
    TFile f("../fit13/nHresult.root");
    TH1D * Truth_16 = (TH1D*)f.Get("Truth_13");
    int nbins = Truth_16->GetNbinsX();
    double emin = Truth_16->GetXaxis()->GetXmin();
    double emax = Truth_16->GetXaxis()->GetXmax();
    double eng[nbins];
    double num[nbins];
    for( int b=1; b<=nbins; b++ ) {
      eng[b-1] = emin + (emax-emin)/nbins * (b-0.5);
      num[b-1] = Truth_16->GetBinContent(b);
      //cout<<b<<" "<<eng[b-1]<<" "<<num[b-1]<<endl;
    }

    TGraph* Disp;
    int npt = 30;
    double dist[30];
    double lost[30];

    for( int dc=0; dc<npt; dc++ ) {
      dist[ dc ] = 2.0/(npt-1) * dc;
      // Calculate the survival probability
      double noos=0;
      double osci=0;
      for(int idx=15; idx<nbins; idx++) {
	//cout<<eng[idx]<<endl;
	noos += num[idx];
	osci += num[idx] * SurvProb(t13, dist[dc]*1000, eng[idx]+0.792);
      }
      lost[ dc ] = osci/noos;
    }

    Disp = new TGraph(npt, dist, lost);
    Disp->SetLineColor(kRed);
    Disp->SetLineWidth(2);
    Disp->Draw("lsame");

  }

}
