#include "Constants.h"
#include "Crosssection.h"
#include "Measurement.h"
#include "Truth.h"
#include "Background.h"
#include "DailyPlot.h"
#include "SurvProb.h"
#include "Li9.h"
#include <iostream>
#include "TMinuit.h"
#include "TFile.h"
#include "math.h"

using namespace std;

double        s_2_2_13;
double        EtaLi9[2][ Basic::NoAd ];
double        UnknownEffi;

Measurement*  MeasuSpec[2][ Basic::NoAd ];
Truth*        TruthSpec[2][ Basic::NoAd ];
Li9*          Li9Spec  [2][ Basic::NoAd ];

void fcn(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);

int main(int argc, char** argv)
{
  // 1. Make a daily plot
  //DailyPlot();
  
  // 2. The theta13 Fit
  s_2_2_13 = 0.0;
  UnknownEffi = 1.0;
  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
    for( unsigned int AdIdx = 0; AdIdx<Basic::NoAd; AdIdx++ )  {    

      MeasuSpec[set][AdIdx] = new Measurement(AdIdx,set);
      TruthSpec[set][AdIdx] = new Truth(AdIdx,set);
      Li9Spec[set][AdIdx]   = new Li9(AdIdx,set);

    }
  }


  TFile file("histos.root", "recreate");

  // Save all relavent supporting information
  gCrosssection->Write();
  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
    for( unsigned int AdIdx = 0; AdIdx<Basic::NoAd; AdIdx++ )  {
      MeasuSpec[set][AdIdx]->Write();
      TruthSpec[set][AdIdx]->Write();
      Li9Spec[set][AdIdx]  ->Write();
    }
  }

  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
    cout<<"Dataset: "<<set<<endl;
    for( unsigned int AdIdx = 0; AdIdx<Basic::NoAd; AdIdx++ )  {

      double Measu  = MeasuSpec[set][AdIdx]->Integral();
      double MeasuE = sqrt(Measu) * 2;
      double Truth  = TruthSpec[set][AdIdx]->Integral();

      cout<<"Measurement:Truth = "<< Measu<<":"<<Truth
	  <<" = "<< Measu / Truth <<"+/-"<< Measu / Truth * MeasuE/Measu <<endl;
    }
  }

  // 3. Rate analysis
  cout<<"========================================================="<<endl;
  cout<<"Start s_2_2_13 fitting... , including ";
  if( Basic::GdFit ) cout<< "GdCap ";
  if( Basic::HFit ) cout<< "HCap ";
  cout<<endl;
  cout<<"========================================================="<<endl;
  
  TMinuit minuit(13);

  minuit.SetFCN( fcn );  
  double arglist[10];
  int ierflg = 0;
  minuit.mnparm( 0 , "s_2_2_13", 0.1, 0.01, 0, 1, ierflg );

  minuit.mnparm( 1 , "EtaLi9_01", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 2 , "EtaLi9_02", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 3 , "EtaLi9_03", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 4 , "EtaLi9_04", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 5 , "EtaLi9_05", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 6 , "EtaLi9_06", 0,   0.01, -5, 5, ierflg );
  
  minuit.mnparm( 7 , "EtaLi9_11", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 8 , "EtaLi9_12", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 9 , "EtaLi9_13", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 10, "EtaLi9_14", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 11, "EtaLi9_15", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 12, "EtaLi9_16", 0,   0.01, -5, 5, ierflg );

  minuit.FixParameter(1);
  minuit.FixParameter(2);
  minuit.FixParameter(3);
  minuit.FixParameter(4);
  minuit.FixParameter(5);
  minuit.FixParameter(6);
  minuit.FixParameter(7);
  minuit.FixParameter(8);
  minuit.FixParameter(9);
  minuit.FixParameter(10);
  minuit.FixParameter(11);
  minuit.FixParameter(12);

  minuit.SetErrorDef( 1 );
  arglist[0] = 500;
  minuit.mnexcm( "MIGRAD", arglist, 1, ierflg );

  return 1;
}

void fcn(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag)
{
  s_2_2_13 = par[0];
  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
    for( unsigned int AdIdx = 0; AdIdx<Basic::NoAd; AdIdx++ )  {
      EtaLi9[set][AdIdx] = par[ set*Basic::NoAd + AdIdx + 1 ];
    }
  }

  cout<<" Working on s_2_2_13 "<<s_2_2_13<<endl;;

  double chi2 = 0;
  /// Rate analysis
  if( Binning::NFitBin == 1 )  {
    for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
      
      if( set==Dataset::GdCap && !Basic::GdFit ) continue;
      if( set==Dataset::HCap  && !Basic::HFit  ) continue;

      for( unsigned int AdIdx = 0; AdIdx<Basic::NoAd; AdIdx++ )  {      

	/// Measurement
	double Measu  = MeasuSpec[set][AdIdx]->Integral();
	double MeasuE = MeasuSpec[set][AdIdx]->GetTotalErr();      
	/*
	for( unsigned int idx = 1; idx<= Binning::NHistoBin; idx++ )  {
	  MeasuE += pow( MeasuSpec[set][AdIdx]->GetBinError(idx), 2) ;
	}
	MeasuE = sqrt( MeasuE );
	*/

	/// Prediction
	TruthSpec[set][AdIdx]->SetupTruth();
	double Truth  = TruthSpec[set][AdIdx]->Integral();

	/// Background
	double Li9 = Li9Spec[set][AdIdx]->Integral() * ( 1+EtaLi9[set][AdIdx] );
	double Li9Pull = EtaLi9[set][AdIdx] / (Li9Bkg::Daily_Yield_Err[set][AdIdx]/Li9Bkg::Daily_Yield[set][AdIdx]);

	/// chi-square
	cout<<"  "<<AdIdx<<" Measurement:Truth = "<< Measu<<"+/-"<<MeasuE<<" : "<<Truth
	    <<" = "<<Measu/Truth
	    <<endl;

	chi2 += pow((Measu - Truth - Li9), 2) / pow( MeasuE, 2 ) + pow(Li9Pull, 2);
      }
    }
  }
  
  f = chi2;
  cout<<"  chi2= "<<chi2<<endl;
  
  return;
}
