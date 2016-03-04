/*
  Eff15.C
  Calculate the efficiency of 1.5 MeV cut
  
  July 2013, Zhe Wang

  root [0] .x Eff15.C+
*/

#include "TVector3.h"
#include <iostream>
#include <string>
#include <sstream>
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"
#include "TRandom3.h"
#include "TCanvas.h"

using namespace std;

namespace Position
{
  /* DocDb 7560 */
  static const TVector3 Ad[8] =
    { TVector3( 363.0177, 49.1021 , -70.8146 ),
      TVector3( 359.0053, 53.5544 , -70.8107 ),
      TVector3( 4.4758  , -873.507, -67.5209 ),
      TVector3( 931.5798, -1422.41, -66.4819 ),
      TVector3( 936.294 , -1418.72, -66.4935 ),
      TVector3( 935.2752, -1427.15, -66.4933 ),
      TVector3( 0, 0, 0 ),   // unknown                                                     
      TVector3( 0, 0, 0 ),   // unknown                                                     
    };

  static const TVector3 Rct[6] =
    { TVector3( 360.6984, 410.1788, -40.2281 ),
      TVector3( 449.4947, 409.3679, -40.2367 ),
      TVector3( -321.63 , -539.583, -39.7268 ),
      TVector3( -268.767, -468.232, -39.7202 ),
      TVector3( -546.752, -952.721, -39.7959 ),
      TVector3( -493.898, -881.363, -39.7857 ),
    };
}

double Baseline( unsigned int RctNo, unsigned int AdNo)
{
  double length = ( Position::Rct[ RctNo-1 ] - Position::Ad[ AdNo-1 ]).Mag();
  return length;
}

string d2a(double dValue) {
  ostringstream oss (ostringstream::out);
  oss <<dValue;
  string strRetVal=oss.str();
  return(strRetVal);
}


TF1 *neutrino_f=new TF1("neutrino_f","0.58*exp(0.870-0.160*x-0.0910*x*x)+0.3*exp(0.896-0.239*x-0.0981*x*x)+0.07*exp(0.976-0.162*x-0.0790*x*x)+0.05*exp(0.793-0.080*x-0.1085*x*x)", 1.5, 12);

TFormula *positron_m=new TFormula("positron_m","sqrt((x-1.2933)*(x-1.2933)-0.511*0.511)");

TF1 *cross_section=new TF1("cross_section","0.0952e-42*(x-1.2933)*positron_m", 1.5, 12);

TF1 *neutrino_sp=new TF1("neutrino_sp","neutrino_f*cross_section", 1.5, 12);

TH1 *h1dNeuSp;

/* Norminal */
TF1 *resolution=new TF1("resolution","(x-0.782)*sqrt(0.0148*0.0148+0.087*0.087/(x-0.782)+0.0271*0.0271/(x-0.782)/(x-0.782))",1.5,12);

/* Normianl + 1 sigma */
//TF1 *resolution=new TF1("resolution","((x-0.782)*sqrt(0.0148*0.0148+0.087*0.087/(x-0.782)+0.0271*0.0271/(x-0.782)/(x-0.782)))*1.025",1.5,12);

/* Normianl - 1 sigma */
//TF1 *resolution=new TF1("resolution","((x-0.782)*sqrt(0.0148*0.0148+0.087*0.087/(x-0.782)+0.0271*0.0271/(x-0.782)/(x-0.782)))*0.975",1.5,12);

TH1 *h1dReso;

const int nBin = 1000;

TH1D *h1dNeuDet = new TH1D("NeuDet","NeuDet",nBin, 1.5, 12);

void NeuSmear( TH1D* NeuDet, TH1* NeuSp, TH1* Reso )
{
  TRandom3 r;

  for( int b=1; b<=nBin; b++ ) {
    double mea = 1.5 + (12-1.5)/nBin*(b-0.5);
    double wei = NeuSp->GetBinContent( b );
    double res = Reso ->GetBinContent( b );
    
    for( int s=1; s<=1000; s++ ) {
      double d = r.Gaus( mea, res );
      NeuDet->Fill( d, wei/nBin );
    }
  }
}

void Eff15()
{
  cout.precision(4);
  cout<<fixed;
  
  // Neutrino spectrum
  neutrino_sp->SetNpx(nBin);
  h1dNeuSp = neutrino_sp->GetHistogram();

  // Resolution spectrum
  resolution ->SetNpx(nBin);
  h1dReso  = resolution ->GetHistogram();

  // Detected neutrino spectrum
  NeuSmear( h1dNeuDet, h1dNeuSp, h1dReso);
  
  // Evaluate the efficinecy at 36 baselines
  const int npt = 36;
  double L [npt]= { 0, 150, 300, 400, 500, 650, 800, 900, 1000, 1150, 1300, 1400, 1500, 1600, 1700, 1850, 2000, 2150, 2300, 2400, 2500, 2650, 2800, 2900, 3000, 3150, 3300, 3400, 3500, 3600, 3700, 3850, 4000, 4150, 4300, 4400};  // m
  string Ls[npt]= { "0", "150", "300", "400", "500", "650", "800", "900", "1000", "1150", "1300", "1400", "1500", "1600", "1700", "1850", "2000", "2150", "2300", "2400", "2500", "2650", "2800", "2900", "3000", "3150", "3300", "3400", "3500", "3600", "3700", "3850", "4000", "4150", "4300", "4400"};
  
  /* 1, 2, 3 for plotting, 4 for efficiency reading */
  /// 1. sin22t13 = 0.090
  double eff[npt];
  TF1 *PSurv[npt];
  for( int pt=0; pt<npt; pt++ )  {
    string name = "PSurv"+Ls[pt];
    string func = "1-0.090*pow(sin(1.267*2.3e-3*"+Ls[pt]+"/x),2)";
    //cout<<name<<" "<<func<<endl;
    // Get survival probability
    PSurv[pt] = new TF1(name.c_str(),func.c_str(), 1.5, 12);

    // Total number of candidates
    string neu = "neu"+Ls[pt];
    string spc = "neutrino_sp*"+name;
    TF1 *neu_near = new TF1( neu.c_str(), spc.c_str(), 1.5, 12);
    neu_near->SetNpx(nBin);

    h1dNeuSp = neu_near->GetHistogram();
    h1dNeuDet->Reset();
    NeuSmear( h1dNeuDet, h1dNeuSp, h1dReso);

    int b15 = h1dNeuDet->FindBin(2.282);
    int all = h1dNeuDet->GetNbinsX();

    eff[pt] =  h1dNeuDet->Integral( b15, all )/ h1dNeuDet->Integral();
  }

  /// 1. sin22t13 = 0.080
  double eff2[npt];
  TF1 *PSurv2[npt];
  for( int pt=0; pt<npt; pt++ ) {
    string name = "PSurv0.080"+Ls[pt];
    string func = "1-0.080*pow(sin(1.267*2.3e-3*"+Ls[pt]+"/x),2)";
    //cout<<name<<" "<<func<<endl;
    // Get survival probability
    PSurv2[pt] = new TF1(name.c_str(),func.c_str(), 1.5, 12);

    // Total number of candidates
    string neu = "neu"+Ls[pt];
    string spc = "neutrino_sp*"+name;
    TF1 *neu_near = new TF1( neu.c_str(), spc.c_str(), 1.5, 12);
    neu_near->SetNpx(nBin);

    h1dNeuSp = neu_near->GetHistogram();
    h1dNeuDet->Reset();
    NeuSmear( h1dNeuDet, h1dNeuSp, h1dReso);

    int b15 = h1dNeuDet->FindBin(2.282);
    int all = h1dNeuDet->GetNbinsX();

    eff2[pt] =  h1dNeuDet->Integral( b15, all )/ h1dNeuDet->Integral();
  }
  
  /// 1. sin22t13 = 0.100
  double eff3[npt];
  TF1 *PSurv3[npt];
  for( int pt=0; pt<npt; pt++ ) {
    string name = "PSurv0.100"+Ls[pt];
    string func = "1-0.100*pow(sin(1.267*2.3e-3*"+Ls[pt]+"/x),2)";
    //cout<<name<<" "<<func<<endl;
    // Get survival probability
    PSurv3[pt] = new TF1(name.c_str(),func.c_str(), 1.5, 12);

    // Total number of candidates
    string neu = "neu"+Ls[pt];
    string spc = "neutrino_sp*"+name;
    TF1 *neu_near = new TF1( neu.c_str(), spc.c_str(), 1.5, 12);
    neu_near->SetNpx(nBin);

    h1dNeuSp = neu_near->GetHistogram();
    h1dNeuDet->Reset();
    NeuSmear( h1dNeuDet, h1dNeuSp, h1dReso);

    int b15 = h1dNeuDet->FindBin(2.282);
    int all = h1dNeuDet->GetNbinsX();

    eff3[pt] =  h1dNeuDet->Integral( b15, all )/ h1dNeuDet->Integral();
  }
  
  /// 4. sin22t13 = 0.090, but for exact baselines
  // get the result for each Ad Reactor baseline
  cout<<"Baseline printout"<<endl;
  for( int ad=1; ad<=6; ad++ ) {
    for( int rct=1; rct<=6; rct++ ) {
      double l = Baseline(rct,ad);
      Ls[ (ad-1)*6+rct-1 ] = d2a(l);
      cout<<Ls[ (ad-1)*6+rct-1 ]<<"\t";
    }
    cout<<endl;
  }

  TCanvas * c = new TCanvas;
  double eff4[npt];
  TF1 *PSurv4[npt];
  for( int pt=0; pt<npt; pt++ ) {
    string name = "PSurv0.090"+Ls[pt];
    string func = "1-0.090*pow(sin(1.267*2.3e-3*"+Ls[pt]+"/x),2)";
    //cout<<name<<" "<<func<<endl;
    // Get survival probability    
    PSurv4[pt] = new TF1(name.c_str(),func.c_str(), 1.5, 12);

    // Total number of candidates
    string neu = "neu"+Ls[pt];
    string spc = "neutrino_sp*"+name;
    TF1 *neu_near = new TF1( neu.c_str(), spc.c_str(), 1.5, 12);
    neu_near->SetNpx(nBin);

    h1dNeuSp = neu_near->GetHistogram();
    h1dNeuDet->Reset();
    NeuSmear( h1dNeuDet, h1dNeuSp, h1dReso);

    if( pt==0 ) {
      h1dNeuDet->DrawClone();
    } else {
      h1dNeuDet->DrawClone("same");
    }
    
    int b15 = h1dNeuDet->FindBin(2.282);
    int all = h1dNeuDet->GetNbinsX();

    eff4[pt] =  h1dNeuDet->Integral( b15+1, all )/ h1dNeuDet->Integral();
    //eff4[pt] = neu_near->Integral( 2.282, 12 )/neu_near->Integral( 1.5, 12 );
  }
  
  // Output result
  cout<<"Efficiency printout"<<endl;
  for( int ad=1; ad<=6; ad++ ) {
    for( int rct=1; rct<=6; rct++ ) {
      cout<<eff4[ (ad-1)*6+rct-1 ]<<"\t";
    }
    cout<<endl;
  }

  // Here the x axis is not valid. Not meaningful
  TCanvas* c4 = new TCanvas;
  TGraph* g4 = new TGraph(npt, L, eff4);
  g4->SetMarkerStyle(20);
  g4->Draw("ap");

  // plot efficiency scan
  TCanvas* cn = new TCanvas;
  TGraph* g = new TGraph(npt, L, eff);
  g->Draw("apl");

  TGraph* g2 = new TGraph(npt, L, eff2);
  g2->SetLineColor(kBlue);
  g2->Draw("plsame");

  TGraph* g3 = new TGraph(npt, L, eff3);
  g3->SetLineColor(kBlue);
  g3->Draw("plsame");
}

