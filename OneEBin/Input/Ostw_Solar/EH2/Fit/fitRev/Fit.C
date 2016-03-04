#include "Constants.h"
#include "Measurement.h"
#include "Truth.h"
#include "Background/Background.h"
#include "Background/Li9.h"
#include "Background/Acc.h"
#include "Background/FastN.h"
#include "DailyPlot.h"
#include "SurvProb.h"
#include <iostream>
#include "TMinuit.h"
#include "TFile.h"
#include "TGraph.h"
#include "math.h"

#include "RctXsecTheory/RctSpec.h"
#include "RctXsecTheory/Crosssection.h"
#include "RctXsecTheory/RctXsec.h"
#include "Flux/GetFluxXsec.h"

#include "AnalyzeData.h"

using namespace std;

double        s_2_2_13;
double        Epsilon;
double        Eta_d[2][ Basic::NoAd ];
double        Epsilon_d[2][ Basic::NoAd ];
double        Epsilon_r[ Basic::NoAd ];

Measurement*  MeasuSpec[2][ Basic::NoAd ];
Truth*        TruthSpec[2][ Basic::NoAd ];
Background*   BkgSpec  [2][ Basic::NoAd ];
Acc*          AccSpec  [2][ Basic::NoAd ];
FastN*        FastNSpec[2][ Basic::NoAd ];
Li9*          Li9Spec  [2][ Basic::NoAd ];

void fcn(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);

int main(int argc, char** argv)
{

  // 1. Initialize some truth and measurement information
  s_2_2_13 = 0.00;
  Epsilon = 0.0;
  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  {

      MeasuSpec[set][AdIdx-1] = new Measurement(AdIdx,set);
      TruthSpec[set][AdIdx-1] = new Truth(AdIdx,set);
      AccSpec[set][AdIdx-1]   = new Acc(AdIdx,set);
      FastNSpec[set][AdIdx-1] = new FastN(AdIdx,set);
      Li9Spec[set][AdIdx-1]   = new Li9(AdIdx,set);
      
      BkgSpec[set][AdIdx-1]   = new Background(AdIdx,set);
      BkgSpec[set][AdIdx-1]->AddBkg( (TH1F*) AccSpec[set][AdIdx-1] );
      BkgSpec[set][AdIdx-1]->AddBkg( (TH1F*) FastNSpec[set][AdIdx-1] );
      BkgSpec[set][AdIdx-1]->AddBkg( (TH1F*) Li9Spec[set][AdIdx-1] );
    }
  }

  cout<<" [ Run Summary ] "<<endl;
  cout.precision(5);

  cout<<"Fulltime8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<gAnalyzeData->Fulltime( Dataset::GdCap, AdIdx )/(24*60*60)<<"\t";
  cout<<endl;

  cout<<"Livetime8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )/(24*60*60)<<"\t";
  cout<<endl;

  cout<<"MuVeEff 8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  
    cout<<gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )/gAnalyzeData->Fulltime( Dataset::GdCap, AdIdx )<<"\t";
  cout<<endl;

  cout<<"OstwEff 8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx )<<"\t";
  cout<<endl;

  cout<<"MuOsEff 8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  
    cout<<gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx )*
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )/
      gAnalyzeData->Fulltime( Dataset::GdCap, AdIdx )<<"\t";
  cout<<endl;
  
  cout<<"N AccBkg8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<AccSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  cout<<"RtAccBkg8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
    cout<<AccSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral() / 
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )*24*60*60 <<"\t";
  cout<<endl;


  cout<<"N FastN 8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<FastNSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  cout<<"RtFastN 8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
    cout<<FastNSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral() /
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx ) *
      (12-0.7)/(10-0.7)<<"\t";   /* Restore to PRL 0.7-10 MeV fit range */
  cout<<endl;


  cout<<"N Li9   8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<Li9Spec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  cout<<"RtLi9   8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  
    cout<<Li9Spec[ Dataset::GdCap ][ AdIdx-1 ]->Integral() /
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx ) <<"\t";
  cout<<endl;

  cout<<"N Bkg   8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  cout<<"N BkgErr8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalErr()<<"\t";
  cout<<endl;

  cout<<"N Candid8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<MeasuSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  cout<<"N IBD   8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  
    cout<<MeasuSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral() 
      - BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  cout<<"RaIBD   8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
    cout<<(MeasuSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()
	   - BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()) / 
      ( gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx )*
	gAnalyzeData->Livetime( Dataset::GdCap, AdIdx ) ) * 24*60*60 <<"\t";
  cout<<endl;

  cout<<"Pre0    8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<TruthSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  cout<<"Ratio 0 8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  
    cout<< (MeasuSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral() - BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral() )
      / TruthSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  s_2_2_13 = 0.092;
  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ ) {
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      TruthSpec[set][AdIdx-1]->SetupTruth();
    }
  }
  cout<<"Pre0.92 8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<TruthSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  cout<<"Ratio92 8:"<<"\t";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
    cout<< (MeasuSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral() - BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral() )
      / TruthSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral()<<"\t";
  cout<<endl;

  // 2. Make some useful plots and table output
  DailyPlot();

  TFile file("result.root", "recreate");

  /* test area */
  /*
  class TInt : public TObject
  {
  public:
    TInt() 
    {
      mRun=5;
      mSource=1;
    };
    
    int mRun;
    int mSource;
  };
  
  TInt RInt;
  RInt.Write("RunSetup");
  */

  /* Reactor truth and crossection */
  gU238 ->Write();
  gU235 ->Write();
  gPu239->Write();
  gPu241->Write();

  gCrosssection->Write();

  /* HD */
  gU238X  ->Multiply( gU238 , gCrosssection); 
  gU235X  ->Multiply( gU235 , gCrosssection); 
  gPu239X ->Multiply( gPu239, gCrosssection); 
  gPu241X ->Multiply( gPu241, gCrosssection); 

  gU238X  ->Write();
  gU235X  ->Write();
  gPu239X ->Write();
  gPu241X ->Write();

  /* LD */
  gU238Xsec ->Write();
  gU235Xsec ->Write();
  gPu239Xsec->Write();
  gPu241Xsec->Write();

  // Save all relavent supporting information
  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  {
      MeasuSpec[set][AdIdx-1]->Write();
      TruthSpec[set][AdIdx-1]->Write();
      Li9Spec[set][AdIdx-1]  ->Write();
      AccSpec[set][AdIdx-1]  ->Write();
      FastNSpec[set][AdIdx-1]->Write();
    }
  }

  // 3. Rate analysis
  //return 1;
  cout<<"========================================================="<<endl;
  cout<<"Start s_2_2_13 fitting... , including ";
  if( Basic::GdFit ) cout<< "GdCap ";
  if( Basic::HFit ) cout<< "HCap ";
  cout<<endl;
  cout<<"========================================================="<<endl;
  
  TMinuit minuit(32);

  minuit.SetFCN( fcn );  
  double arglist[10];
  int ierflg = 0;
  minuit.mnparm( 0 , "s_2_2_13", 0.1, 0.01,  0, 1, ierflg );
  minuit.mnparm( 1 , "Epsilon",  0,   0.01, -5, 5, ierflg );

  minuit.mnparm( 2 , "Eta_d_01", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 3 , "Eta_d_02", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 4 , "Eta_d_03", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 5 , "Eta_d_04", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 6 , "Eta_d_05", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 7 , "Eta_d_06", 0,   0.01, -5, 5, ierflg );

  minuit.mnparm( 8 , "Eta_d_11", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 9 , "Eta_d_12", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 10, "Eta_d_13", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 11, "Eta_d_14", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 12, "Eta_d_15", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 13, "Eta_d_16", 0,   0.01, -5, 5, ierflg );


  minuit.mnparm( 14, "Eps_d_01", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 15, "Eps_d_02", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 16, "Eps_d_03", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 17, "Eps_d_04", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 18, "Eps_d_05", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 19, "Eps_d_06", 0,   0.01, -5, 5, ierflg );

  minuit.mnparm( 20, "Eps_d_11", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 21, "Eps_d_12", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 22, "Eps_d_13", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 23, "Eps_d_14", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 24, "Eps_d_15", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 25, "Eps_d_16", 0,   0.01, -5, 5, ierflg );
  
  minuit.mnparm( 26, "Eps_r_01", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 27, "Eps_r_02", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 28, "Eps_r_03", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 29, "Eps_r_04", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 30, "Eps_r_05", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 31, "Eps_r_06", 0,   0.01, -5, 5, ierflg );

  /*
  minuit.FixParameter(20);
  minuit.FixParameter(21);
  minuit.FixParameter(22);
  minuit.FixParameter(23);
  minuit.FixParameter(24);
  minuit.FixParameter(25);

  minuit.FixParameter(26);
  minuit.FixParameter(27);
  minuit.FixParameter(28);
  minuit.FixParameter(29);
  minuit.FixParameter(30);
  minuit.FixParameter(31);
  */

  minuit.SetErrorDef( 1 );
  arglist[0] = 10000;
  minuit.mnexcm( "MIGRAD", arglist, 1, ierflg );

  /*
  double theta13[96], chisq[96];
  double step = 0.002;
  for( double t13=0; t13<0.19001; t13+=step ) {
    s_2_2_13 = t13;
    minuit.mnparm( 0 , "s_2_2_13", s_2_2_13, 0.00, 0, 1, ierflg );
    minuit.mnexcm( "MIGRAD", arglist, 1, ierflg );

    double chi2,edm,errdef;
    int nvpar,nparx,icstat;
    minuit.mnstat(chi2,edm,errdef,nvpar,nparx,icstat);
    theta13[ int(t13/step) ] = t13;
    chisq[ int(t13/step) ] = chi2;
  }
  TGraph* gr = new TGraph( 96, theta13, chisq );
  gr->Write();
  */
  return 1;
}

void fcn(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag)
{
  s_2_2_13 = par[0];
  Epsilon  = par[1];
  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  {
      Eta_d[set][AdIdx-1]     = par[ 1 + set*Basic::NoAd + AdIdx ];
      Epsilon_d[set][AdIdx-1] = par[ 13 + set*Basic::NoAd + AdIdx ];
    }
  }

  for( unsigned int RctIdx = 1; RctIdx<=Basic::NoRct; RctIdx++ ) {
    Epsilon_r[RctIdx-1] = par[ 25 + RctIdx ];
  }

  cout<<" Working on s_2_2_13 "<<s_2_2_13<<endl;

  double chi2 = 0;
  /// Rate analysis
  if( Binning::NFitBin == 1 )  {
    for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
      
      if( set==Dataset::GdCap && !Basic::GdFit ) continue;
      if( set==Dataset::HCap  && !Basic::HFit  ) continue;

      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  {      

	/// Measurement
	double add = 0;
	// what if use prl acc background rate
	/*
	if( AdIdx<=2 ) add=70;
	if( AdIdx==3 ) add=50-200;
	if( AdIdx>=4 ) add=12;
	*/
	// double Measu  = MeasuSpec[set][AdIdx-1]->Integral()+add;
	double Measu  = MeasuSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral();
	double MeasuE = sqrt( Measu );

	/// Prediction
	TruthSpec[set][AdIdx-1]->SetupTruth();
	double Truth  = TruthSpec[set][AdIdx-1]->Integral();
	
	double SumR=0;
	for ( int rct=1; rct<=Basic::NoRct; rct++ ) 
	  {  SumR += RePRL::Omega_d_r[ AdIdx-1 ][ rct-1 ] * Epsilon_r[rct-1]; }

	Truth *= ( 1 + SumR + Epsilon + Epsilon_d[set][AdIdx-1] );
	double Tr_Pull = Epsilon_d[set][AdIdx-1] / 0.002;

	/// Background
	double Bd  = BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral();	
	Bd *= ( 1+Eta_d[set][AdIdx-1] );
	double Bd_ReErr = BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalErr() / BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->Integral();
	double Bd_Pull = Eta_d[set][AdIdx-1] / Bd_ReErr;

	/// chi-square
	cout<<"  "<<AdIdx<<" Measurement:Truth = "<< Measu-Bd<<"+/-"<<MeasuE<<" : "<<Truth
	    <<" = "<<(Measu-Bd)/Truth
	    <<endl;

	chi2 += pow( (Measu - Truth - Bd) / MeasuE, 2 )
	  + pow( Tr_Pull, 2)
	  + pow( Bd_Pull, 2) ;
      }
    }
  }

  for( int rct=1; rct<=Basic::NoRct; rct++ ) {
    double Rct_Pull = Epsilon_r[rct-1]/0.008;
    chi2 += pow( Rct_Pull, 2 );
    cout<<Rct_Pull<<" ";
  }

  f = chi2;
  cout<<"  chi2= "<<chi2<<endl;
  
  return;
}
