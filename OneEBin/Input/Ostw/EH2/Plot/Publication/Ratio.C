#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TStyle.h"

double SurvProb( double t13, double baseline /* m */, double Enu /* MeV */)
{
  double s_2_2_13 = t13;  /* sin^2(2theta13) */

  double delta_M31_2 = 2.32e-3;  
  double delta_M21_2 = 7.59e-5;
  double s_2_2_12 = 0.861;

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

void Ratio()
{
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  double baseline[6]={0.496651, 0.491322, 0.554113, 1.62655-0.03, 1.62818, 1.6321+0.03};
  //double baseline[6]={0.571804, 0.567082, 0.592606, 1.63217-0.03, 1.63368, 1.63768+0.03};
  double be[6]={0,0,0,0,0,0};
  double ratio[6]={0.9834, 0.9849, 0.9864, 0.9282, 0.9086, 0.9571};
  //0.9834_0.0069 & 0.9849_0.0069 & 0.9864_0.0073 & 0.9282_0.0160 & 0.9086_0.0161 & 0.9571_0.0166
  double ratioe[6]={0.0069, 0.0069, 0.0073, 0.0160, 0.0161, 0.0166};
  
  double t13 =  8.78022e-02;
  double t13e = 1.63739e-02;
  double chi2 = 4.54385;

  double x[6],y[4];
  x[0] = 0;
  x[1] = t13 - 3.2*t13e;
  x[2] = t13 - t13e;
  x[3] = t13 + t13e;
  x[4] = t13 + 3.1*t13e;
  x[5] = t13 + 5.2*t13e;
  y[0] = 0;
  y[1] = chi2+1;
  y[2] = chi2+9;
  y[3] = chi2+25;
  
  TGraphErrors *ratiog = new TGraphErrors(6,baseline, ratio, be, ratioe);
  TCanvas* c = new TCanvas("c1","multipads",600,500);
  c->SetLeftMargin(0.15);
  ratiog->GetYaxis()->SetRangeUser(0.88,1.15);
  ratiog->GetXaxis()->SetLimits(0.0,2.0);
  ratiog->SetMarkerStyle(25);
  ratiog->SetLineColor(4);
  ratiog->SetLineWidth(2);
  ratiog->GetYaxis()->SetTitle("Measured/Prediction");
  ratiog->GetYaxis()->SetTitleOffset(1.5);
  ratiog->GetXaxis()->SetTitle("Weighted baseline [km]");

  ratiog->Draw("AP");

  TLine line;
  line.SetLineStyle(2);
  line.DrawLine(0,1,2,1);

  // Make the red curve
  TFile f("result.root");
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

  {
    TPad* pad = new TPad("name","Title",0.35, 0.47, 0.96, 0.95);
    pad->Draw();
    pad->cd();
    pad->SetLeftMargin(0.15);
    pad->SetBottomMargin(0.15);

    TGraph* Graph;
    const int n = 20;    
    double S13[n] = {0.000000, 0.009250, 0.018500, 0.027750, 0.037000, 0.046250, 0.055500, 0.064750, 0.074000, 0.083250, 0.092500, 0.101750, 0.111000, 0.120250, 0.129500, 0.138750, 0.148000, 0.157250, 0.166500, 0.175750};
    double Chi[n] = {28.838118, 24.120320, 19.884366, 16.140633, 12.899639, 10.172040, 7.968632, 6.300351, 5.178271, 4.613608, 4.617718, 5.202101, 6.378396, 8.158386, 10.553995, 13.577293, 17.240488, 21.555937, 26.536136, 32.193726};
    Graph = new TGraph(n, S13, Chi);

    Graph->GetYaxis()->SetRangeUser(0.0, 34.0);
    Graph->GetYaxis()->SetTitle("#chi^{2}");    
    //Graph->GetYaxis()->SetTitleOffset(1.5);
    Graph->GetYaxis()->SetLabelSize(0.07);
    Graph->GetYaxis()->SetTitleSize(0.07);
    Graph->GetYaxis()->SetTitleOffset(0.9);
    Graph->GetYaxis()->CenterTitle();

    Graph->GetXaxis()->SetTitle("sin^{2}(2#theta_{13})");
    //Graph->GetXaxis()->SetTitleOffset(1.5);
    Graph->GetXaxis()->SetLabelSize(0.07);
    Graph->GetXaxis()->SetTitleSize(0.07);
    Graph->GetXaxis()->SetLimits(0,0.18);
    Graph->GetXaxis()->SetNdivisions(4,5,0);
    Graph->GetXaxis()->SetTitleOffset(0.9);
    Graph->GetXaxis()->CenterTitle();

    Graph->SetLineWidth(2);
    Graph->Draw("alp");

    TLatex text;
    text.SetTextSize(0.08);
    text.SetTextAlign(11);

    TLine line;
    line.SetLineStyle(2);
    line.DrawLine(x[0],y[0],x[0],y[3]);
    line.DrawLine(x[0],y[3],x[5],y[3]);
    line.DrawLine(x[5],y[3],x[5],y[0]);
    text.DrawLatex( t13-0.4*t13e, y[3], "5#sigma" );

    line.DrawLine(x[1],y[0],x[1],y[2]);
    line.DrawLine(x[1],y[2],x[4],y[2]);
    line.DrawLine(x[4],y[2],x[4],y[0]);
    text.DrawLatex( t13-0.4*t13e, y[2], "3#sigma" );

    line.DrawLine(x[2],y[0],x[2],y[1]);
    line.DrawLine(x[2],y[1],x[3],y[1]);
    line.DrawLine(x[3],y[1],x[3],y[0]);
    text.DrawLatex( t13-0.4*t13e, y[1], "1#sigma" );
  }

}
