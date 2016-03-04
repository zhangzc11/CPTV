/*
  Be careful with the correlated systematic error for accidental background.

  -- Zhe Wang
*/

#include "Constants.h"
#include "Measurement.h"
#include "Truth.h"
#include "Background/Background.h"
#include "Background/Li9.h"
#include "Background/Acc.h"
#include "Background/FastN.h"
#include "Background/AmC.h"
#include "DailyPlot.h"
#include "Baseline.h"
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
#include "ProtonNumber.h"

#include "AnalyzeData.h"

#include "../../Common/OstwEff.h"
using namespace std;

double        s_2_2_13;
double        Epsilon[2];
double        Eta_d    [2][ Basic::NoAd ];
double        Epsilon_d[2][ Basic::NoAd ];
double        Epsilon_r   [ Basic::NoRct ];

double ratio ( double a, double ea, double b, double eb );
double eratio( double a, double ea, double b, double eb );

void fcn(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);

Measurement*  MeasuSpec[2][ Basic::NoAd ];
Truth*        TruthSpec[2][ Basic::NoAd ];
Background*   BkgSpec  [2][ Basic::NoAd ];
Acc*          AccSpec  [2][ Basic::NoAd ];
FastN*        FastNSpec[2][ Basic::NoAd ];
Li9*          Li9Spec  [2][ Basic::NoAd ];
AmC*          AmCSpec  [2][ Basic::NoAd ];

RctXsec* gU238Xsec = 0;
RctXsec* gU235Xsec = 0;
RctXsec* gPu239Xsec= 0;
RctXsec* gPu241Xsec= 0;
Crosssection* gCrosssection = 0; //new Crosssection;
GetFluxXsec* gGetFluxXsec = 0; //new GetFluxXsec;

int main(int argc, char** argv)
{
  gCrosssection = new Crosssection;

  gU238  = new RctSpec( Reactor::U238SpecFile,  "U238"  );
  gU235  = new RctSpec( Reactor::U235SpecFile,  "U235"  );
  gPu239 = new RctSpec( Reactor::Pu239SpecFile, "Pu239" );
  gPu241 = new RctSpec( Reactor::Pu241SpecFile, "Pu241" );

  gU238Xsec  = new RctXsec( "U238Xsec",  gCrosssection, gU238  );
  gU235Xsec  = new RctXsec( "U235Xsec",  gCrosssection, gU235  );
  gPu239Xsec = new RctXsec( "Pu239Xsec", gCrosssection, gPu239 );
  gPu241Xsec = new RctXsec( "Pu241Xsec", gCrosssection, gPu241 );

  gGetFluxXsec = new GetFluxXsec;
  

  cout.precision(6);
  cout<<" [ Baseline for each AD ] "<<endl;
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    cout<<"AD "<<AdIdx<<": ";
    for( unsigned int rct = 1; rct <= Basic::NoRct; rct++ ) {
      cout<<Baseline(rct, AdIdx)/1000<<" ";
    }
    cout<<endl;
  }
  cout<<endl;

  cout<<" [ Deficit factor for each AD ] "<<endl;
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    double deficit=0;
    for( unsigned int rct = 1; rct <= Basic::NoRct; rct++ ) {
      deficit += RePRL::Omega_d_r[ AdIdx-1 ][ rct-1 ] * RePRL::Delta_d_r[ AdIdx-1 ][ rct-1 ];
    }
    cout<< deficit <<"\t";
  }
  cout<<endl;

  // 1. Initialize some truth and measurement information
  s_2_2_13 = 0;
  Epsilon[0] = 0;
  Epsilon[1] = 0;
  for( unsigned int rct = 1; rct<=Basic::NoRct; rct++ ) {
    Epsilon_r[ rct-1 ] = 0;
  }  

  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  {

      MeasuSpec[set][AdIdx-1] = new Measurement(AdIdx,set);
      TruthSpec[set][AdIdx-1] = new Truth(AdIdx,set);
      AccSpec[set][AdIdx-1]   = new Acc(AdIdx,set);
      FastNSpec[set][AdIdx-1] = new FastN(AdIdx,set);
      Li9Spec[set][AdIdx-1]   = new Li9(AdIdx,set);
      AmCSpec[set][AdIdx-1]   = new AmC(AdIdx,set);
      
      BkgSpec[set][AdIdx-1]   = new Background(AdIdx,set);
      BkgSpec[set][AdIdx-1]->AddBkg( AccSpec[set][AdIdx-1] );
      BkgSpec[set][AdIdx-1]->AddBkg( FastNSpec[set][AdIdx-1] );
      BkgSpec[set][AdIdx-1]->AddBkg( Li9Spec[set][AdIdx-1] );
      BkgSpec[set][AdIdx-1]->AddBkg( AmCSpec[set][AdIdx-1] );
    }
  }
  
  cout.precision(6);
  cout<<" [ IBD fraction from each reactor ]"<<endl;
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    cout<<"AD"<<AdIdx<<": ";
    for( unsigned int rct = 1; rct<=Basic::NoRct; rct++ ) {
      cout<<TruthSpec[ Dataset::GdCap ][ AdIdx-1 ]->Omega_r( rct )<<"\t";
    }
    cout<<endl;
  }

  for( int set=Dataset::GdCap; set<=Dataset::HCap; set++ ) {
    cout<<" [ Run Summary for "<< Dataset::Name[set] <<" ] "<<endl;
    cout<<" ======================== "<<endl;

    cout.precision(4);
    cout<<fixed;
    cout<<"Fulltime (d)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  { 
      cout<<gAnalyzeData->Fulltime( set, AdIdx )/(24*60*60);
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    cout<<"Livetime (d)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  {
      cout<<gAnalyzeData->Livetime( set, AdIdx )/(24*60*60);
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;    

    cout.precision(4);
    cout<<fixed;
    cout<<"$R_{\\mu}$ (Hz)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<gAnalyzeData->NNet[ set ][ AdIdx-1 ] / gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    cout.precision(2);
    cout<<fixed;
    cout<<"Veto (d) "<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<(gAnalyzeData->Fulltime( set, AdIdx )-gAnalyzeData->Livetime( set, AdIdx ))/(24*60*60);
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    cout.precision(4);
    cout<<fixed;
    cout<<"$\\varepsilon_{\\mu}$ "<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<gAnalyzeData->Livetime( set, AdIdx )/gAnalyzeData->Fulltime( set, AdIdx );
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;
    
    cout.precision(4);
    cout<<fixed;
    cout<<"$\\varepsilon_{m}$ "<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<gAnalyzeData->OstwEff( set, AdIdx );
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;
    
    cout<<"$\\varepsilon_{\\mu}\\varepsilon_{m}$ "<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<gAnalyzeData->OstwEff( set, AdIdx )*
	gAnalyzeData->Livetime( set, AdIdx )/
	gAnalyzeData->Fulltime( set, AdIdx );
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    
    if( set == Dataset::HCap ) {
      /* About singles and accidental background subtraction */
      cout<<"============================================================================="<<endl;
      cout.precision(0);
      cout<<fixed;
      cout<<"NNet "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< gAnalyzeData->NNet[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;
      
      cout.precision(0);
      cout<<fixed;
      cout<<"NSgUp "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< gAnalyzeData->NSgUp[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;
      
      cout<<"NSgLw "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< gAnalyzeData->NSgLw[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;
      
      cout.precision(4);
      cout<<fixed;
      cout<<"Up/Lw "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< gAnalyzeData->NSgUp[ set ][ AdIdx-1 ]/gAnalyzeData->NSgLw[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;
      
      cout.precision(4);
      cout<<fixed;
      cout<<"Rs "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< (gAnalyzeData->NSgUp[ set ][ AdIdx-1 ]+gAnalyzeData->NSgLw[ set ][ AdIdx-1 ]) /
	  2.0/gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ]<<" & ";
      cout<<endl;
      
      cout.precision(0);
      cout<<fixed;
      cout<<"TwoFold "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< gAnalyzeData->TwoFold[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;
      
      cout<<"ThreeFold "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< gAnalyzeData->ThreeFold[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;
      
      cout<<"One Pred "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      }
      cout<<endl;

      cout<<"Two Pred "<<" & ";
      cout<<endl;

      cout<<"Three Pred "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
	
	double tri=0;
	
	double Rs = gAnalyzeData->NSgUp[ set ][ AdIdx-1 ]/gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
	double Rmu = gAnalyzeData->NNet[ set ][ AdIdx-1 ]/gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
	double Tc = 400e-6;
	double RIBD = (70+2.16*ReCPC::IbdRate[ AdIdx-1 ])/(24*60*60);
	
	double rsss = RSSS(Rs, Rmu, Tc);
	double nsss = rsss * gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
	tri += nsss;

	double rsen = RSEN(Rs, Rmu, Tc, RIBD, 1, 1, 1, 1/45e-6,  0, 0);
	double nsen = rsen * gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
	tri += nsen;

	double re_n_s = RE_N_S(Rs, Rmu, Tc, RIBD, 1, 1, 1, 1/45e-6,  0, 0 );
	double ne_n_s = re_n_s * gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
	tri += ne_n_s;

	double rs_e_s = RS_E_S(Rs, Rmu, Tc, RIBD, 1, 0.95, 1, 1/45e-6,  0, 0 );
	double ns_e_s = rs_e_s * gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
        tri += ns_e_s;
	
	double ress = RESS(Rs, Rmu, Tc, RIBD, 1, 0.95, 1, 1/45e-6,  0, 0 );
        double ness = ress * gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
        tri += ness;

	double rnss = RNSS(Rs, Rmu, Tc, RIBD, 1, 0.95, 1, 1/45e-6,  0, 0 );
	double nnss = rnss * gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
        tri += nnss;

        double rs_n_s = RS_N_S(Rs, Rmu, Tc, RIBD, 1, 0.95, 1, 1/45e-6,  0, 0 );
	double ns_n_s = rs_n_s * gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
        tri += ns_n_s;

	cout<<tri<<" & ";
      }
      cout<<endl;

      cout<<"============================================================================="<<endl;

      cout<<"NBVtx "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< gAnalyzeData->NBVtx[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;
      
      cout<<"NAVtx "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< gAnalyzeData->NAVtx[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;
      
      cout<<"NAEng "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
        cout<< gAnalyzeData->NAEng[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;

      cout.precision(4);
      cout<<fixed;
      cout<<"AVtx/BVtx "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
	cout<< gAnalyzeData->NAVtx[ set ][ AdIdx-1 ]/gAnalyzeData->NBVtx[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;

      cout.precision(4);
      cout<<fixed;
      cout<<"AEng/AVtx "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
        cout<< gAnalyzeData->NAEng[ set ][ AdIdx-1 ]/gAnalyzeData->NAVtx[ set ][ AdIdx-1 ] <<" & ";
      cout<<endl;
      
      cout.precision(4);
      cout<<fixed;
      cout<<"RSS "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
	double Rs = (gAnalyzeData->NSgUp[ set ][ AdIdx-1 ]+gAnalyzeData->NSgLw[ set ][ AdIdx-1 ])
	  /2.0
	  /gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
	
	double Rmu = gAnalyzeData->NNet[ set ][ AdIdx-1 ]/gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
	double Tc = 400e-6;
	
	double rss = RSS_DYB( Rs, Rmu, Tc );
	cout<< rss <<" & ";
      }
      cout<<endl;
      
      cout<<"NSS "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
	double Rs = (gAnalyzeData->NSgUp[ set ][ AdIdx-1 ]+gAnalyzeData->NSgLw[ set ][ AdIdx-1 ])
	  /2.0
	  /gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
	
	double Rmu = gAnalyzeData->NNet[ set ][ AdIdx-1 ]/gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ];
	double Tc = 400e-6;
	
	double nss = RSS_DYB( Rs, Rmu, Tc ) * gAnalyzeData->m_Livetime[ set ][ AdIdx-1 ] * 
	  gAnalyzeData->NAEng[ set ][ AdIdx-1 ]/gAnalyzeData->NBVtx[ set ][ AdIdx-1 ];
	cout<< nss <<" & ";
      }
      cout<<endl;
      
      cout<<"NAcc "<<" & ";
      for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
	cout<< gAnalyzeData->NAcc[ set ][ AdIdx-1 ] <<" & ";
      }
      cout<<endl;
      
      cout<<"============================================================================="<<endl;
    }

    cout<<"Candidates "<<" & ";
    cout.precision(0);
    cout<<fixed;
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<MeasuSpec[ set ][ AdIdx-1 ]->GetTotalEnt()<<"$\\pm$"
          <<MeasuSpec[ set ][ AdIdx-1 ]->GetTotalErr();
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    ///
    cout.precision(2);
    cout<<fixed;
    cout<<"Acc. Bkg. "<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<AccSpec[ set ][ AdIdx-1 ]->GetTotalEnt()<<"$\\pm$"
          <<AccSpec[ set ][ AdIdx-1 ]->GetTotalErr();
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;
    
    cout<<"$R_{ACC}$ (1/d)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<"$"
	  <<AccSpec[ set ][ AdIdx-1 ]->GetTotalEnt() / 
	gAnalyzeData->Livetime( set, AdIdx )*24*60*60 /
	gAnalyzeData->OstwEff( set, AdIdx ) <<"\\pm"
	  <<AccSpec[ set ][ AdIdx-1 ]->GetTotalErr() /
        gAnalyzeData->Livetime( set, AdIdx )*24*60*60 /
        gAnalyzeData->OstwEff( set, AdIdx )
	  <<"$";
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    cout.precision(0);
    cout<<"Can.-Acc.  "<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      double c = MeasuSpec[ set ][ AdIdx-1 ]->GetTotalEnt() - AccSpec[ set ][ AdIdx-1 ]->GetTotalEnt();
      double e = sqrt( pow( MeasuSpec[ set ][ AdIdx-1 ]->GetTotalErr(),2 )
                       + pow( AccSpec[ set ][ AdIdx-1 ]->GetTotalErr(),2 )
                       + pow( c*Un3sigma::frac[AdIdx-1], 2) );
      cout<<c<<"$\\pm$"<<e;
      if( AdIdx<Basic::NoAd ) {
	cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;
    
    cout.precision(2);
    cout<<"N FastN  :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  
      cout<<"$"
	  <<FastNSpec[ set ][ AdIdx-1 ]->GetTotalEnt()<<"\\pm"
          <<FastNSpec[ set ][ AdIdx-1 ]->GetTotalErr()
	  <<"$ & ";
    cout<<endl;
    
    cout<<"$R_{FastN}$ (1/d)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<"$"
	  <<FastNSpec[ set ][ AdIdx-1 ]->GetTotalEnt() /
	gAnalyzeData->Livetime( set, AdIdx )*24*60*60 /
	gAnalyzeData->OstwEff( set, AdIdx ) 
	  <<"\\pm"
	  <<FastNSpec[ set ][ AdIdx-1 ]->GetTotalErr() /
        gAnalyzeData->Livetime( set, AdIdx )*24*60*60 /
        gAnalyzeData->OstwEff( set, AdIdx )
	  <<"$";
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;
    
    cout<<"N Li9    :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  
      cout<<"$"
	  <<Li9Spec[ set ][ AdIdx-1 ]->GetTotalEnt()<<"\\pm"
	  <<Li9Spec[ set ][ AdIdx-1 ]->GetTotalErr()
	  <<"$ & ";
    cout<<endl;

    cout<<"$R_{Li9}$ (1/d)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<"$"
	  <<Li9Spec[ set ][ AdIdx-1 ]->GetTotalEnt() /
	gAnalyzeData->Livetime( set, AdIdx )*24*60*60 /
	gAnalyzeData->OstwEff( set, AdIdx )<<"\\pm" 
	  <<Li9Spec[ set ][ AdIdx-1 ]->GetTotalErr() /
        gAnalyzeData->Livetime( set, AdIdx )*24*60*60 /
        gAnalyzeData->OstwEff( set, AdIdx )
	  <<"$";
      if( AdIdx<Basic::NoAd ) {
	cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    cout<<"$R_{AmC}$ (1/d)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<"$"
          <<AmCSpec[ set ][ AdIdx-1 ]->GetTotalEnt() /
        gAnalyzeData->Livetime( set, AdIdx )*24*60*60 /
        gAnalyzeData->OstwEff( set, AdIdx )<<"\\pm"
          <<AmCSpec[ set ][ AdIdx-1 ]->GetTotalErr() /
        gAnalyzeData->Livetime( set, AdIdx )*24*60*60 /
        gAnalyzeData->OstwEff( set, AdIdx )
          <<"$";
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    cout.precision(0);
    cout<<"N Bkg    :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  
      cout<<"$"
	  <<BkgSpec[ set ][ AdIdx-1 ]->GetTotalEnt()<<"\\pm"
	  <<BkgSpec[ set ][ AdIdx-1 ]->GetTotalErr()
	  <<"$ & ";
    cout<<endl;

    cout<<"IBD    "<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd;AdIdx++ ) {
      double c = MeasuSpec[ set ][ AdIdx-1 ]->GetTotalEnt() - BkgSpec[ set ][ AdIdx-1 ]->GetTotalEnt();
      double e = sqrt( pow( MeasuSpec[ set ][ AdIdx-1 ]->GetTotalErr(),2 )
                       + pow( BkgSpec[ set ][ AdIdx-1 ]->GetTotalErr(),2 )
                       + pow( c*Un3sigma::frac[AdIdx-1], 2) );
      cout<<c<<"$\\pm$"<<e;
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    /// IBD rate and its ratio to PRL result
    double rate [Basic::NoAd];
    double erate[Basic::NoAd];
    double rPRL [Basic::NoAd];
    double erPRL[Basic::NoAd];
    double rCPC [Basic::NoAd];
    double erCPC[Basic::NoAd];
    
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      rate[ AdIdx-1 ] = (MeasuSpec[ set ][ AdIdx-1 ]->GetTotalEnt() - BkgSpec[ set ][ AdIdx-1 ]->GetTotalEnt()) /
	( gAnalyzeData->OstwEff( set, AdIdx )*
	  gAnalyzeData->Livetime( set, AdIdx ) ) * 24*60*60;
      erate[ AdIdx-1] = sqrt( pow(MeasuSpec[ set ][ AdIdx-1 ]->GetTotalErr(),2) + 
			      pow(BkgSpec[ set ][ AdIdx-1 ]->GetTotalErr(),  2) +
			      pow(rate[ AdIdx-1 ]*Un3sigma::frac[AdIdx-1],   2) ) /
	( gAnalyzeData->OstwEff( set, AdIdx )*
	  gAnalyzeData->Livetime( set, AdIdx ) ) * 24*60*60;
    }

    cout.precision(2);
    cout<<fixed;
    cout<<"$R_{IBD}$ (1/d)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      if( RepeatPRL ) {
        cout<<(MeasuSpec[ set ][ AdIdx-1 ]->GetTotalEnt()
               - BkgSpec[ set ][ AdIdx-1 ]->GetTotalEnt()) /
          ( RePRL::MuonOstwEf[ AdIdx-1 ] *
            gAnalyzeData->Fulltime( set, AdIdx ) ) * 24*60*60;
      } else {
        cout<<"$"
	    <<rate[ AdIdx-1 ]<<"\\pm"
	    <<erate[ AdIdx-1]
	    <<"$";	
      }
      if( AdIdx<Basic::NoAd ) {
	cout<<" & ";
      } else {
	cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    double otherEff = Eff::Flasher_8_eff*Eff::Spill_in_8_eff*Eff::Time_8_eff*Phys::Gd_Cap_Pmpt_eff*Phys::Gd_Cap_Dlyd_eff*Phys::GdLS_Gd_Cap_Frac;
    cout<<"$R_{RAW_IBD_Gd}$ (1/d)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<"$"
	  <<rate[ AdIdx-1 ]/otherEff
	  <<"\\pm"
	  <<erate[ AdIdx-1]/otherEff
	  <<"$";
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    cout<<"$R_{Pred}$ (1/d)"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<"$"
          <<TruthSpec[set][AdIdx-1]->GetTotalEnt()/otherEff/gAnalyzeData->OstwEff( set, AdIdx ) /
	(gAnalyzeData->Livetime( set, AdIdx ) / (24*60*60))
          <<"$";
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      rPRL[ AdIdx-1 ] = ratio( rate[ AdIdx-1 ],
			       erate[ AdIdx-1 ],
			       RePRL::IbdRate[ AdIdx-1 ],
			       RePRL::EIbdRate[ AdIdx-1 ]);
      erPRL[ AdIdx-1 ] = eratio( rate[ AdIdx-1 ],
				 erate[ AdIdx-1 ],
				 RePRL::IbdRate[ AdIdx-1 ],
				 RePRL::EIbdRate[ AdIdx-1 ]);
      
      rCPC[ AdIdx-1 ] = ratio( rate[ AdIdx-1 ],
                               erate[ AdIdx-1 ],
                               ReCPC::IbdRate[ AdIdx-1 ],
                               ReCPC::EIbdRate[ AdIdx-1 ]);
      erCPC[ AdIdx-1 ] = eratio( rate[ AdIdx-1 ],
                                 erate[ AdIdx-1 ],
                                 ReCPC::IbdRate[ AdIdx-1 ],
                                 ReCPC::EIbdRate[ AdIdx-1 ]);
      }

    cout.precision(3);
    cout<<fixed;
    cout<<"R to PRL:"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<"$"
	  <<rPRL[ AdIdx-1 ]<<"\\pm"
	  <<erPRL[ AdIdx-1]
	  <<"$";
      if( AdIdx<Basic::NoAd ) {
        cout<<" & ";
      } else {
        cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    cout<<"R to CPC:"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<"$"
          <<rCPC[ AdIdx-1 ]<<"\\pm"
          <<erCPC[ AdIdx-1]
          <<"$";
      if( AdIdx<Basic::NoAd ) {
	cout<<" & ";
      } else {
	cout<<" \\\\\\hline";
      }
    }
    cout<<endl;

    /*
    s_2_2_13 = 0;
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      TruthSpec[set][AdIdx-1]->SetupTruth();
    }
    */
    cout<<"Pre0     :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) { 
      cout<<TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt()*1.00<<" & "; 
    }
    cout<<endl;

    cout<<"Pre0-scl :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt() * (1+Eff::BestEpsilon[set])<<" & ";
    }
    cout<<endl;

    cout<<"Pre0/PRL :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt()*1.00 / RePRL::TotalPredi[AdIdx-1] <<" & ";
    }
    cout<<endl;
    
    /* Ratio to non-oscillation prediction */
    double r[6],e[6];
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      r[AdIdx-1] = ratio ( (MeasuSpec[ set ][ AdIdx-1 ]->GetTotalEnt() - BkgSpec[ set ][ AdIdx-1 ]->GetTotalEnt()), 
			   sqrt( pow(MeasuSpec[ set ][ AdIdx-1 ]->GetTotalErr(),2) +
				 pow(BkgSpec[ set ][ AdIdx-1 ]->GetTotalErr(),2) ),
			   TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt() * (1+Eff::BestEpsilon[set]),
			   TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt() * (1+Eff::BestEpsilon[set]) * Eff::EffUncer[set]);
      e[AdIdx-1] =eratio ( (MeasuSpec[ set ][ AdIdx-1 ]->GetTotalEnt() - BkgSpec[ set ][ AdIdx-1 ]->GetTotalEnt()),
                           sqrt( pow(MeasuSpec[ set ][ AdIdx-1 ]->GetTotalErr(),2) +
                                 pow(BkgSpec[ set ][ AdIdx-1 ]->GetTotalErr(),2) ),
                           TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt() * (1+Eff::BestEpsilon[set]),
                           TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt() * (1+Eff::BestEpsilon[set]) * Eff::EffUncer[set]);
    }

    cout<<"Ratio 0  :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  
      cout<< (MeasuSpec[ set ][ AdIdx-1 ]->GetTotalEnt() - BkgSpec[ set ][ AdIdx-1 ]->GetTotalEnt() )
	/ (TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt() * (1+Eff::BestEpsilon[set]))<<" & ";
    cout<<endl;

    cout<<"Ratio 0  :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
      cout<< r[AdIdx-1]<<"_"<<e[AdIdx-1]<<" & ";
    cout<<endl;
    
    s_2_2_13 = 0.092;
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      TruthSpec[set][AdIdx-1]->SetupTruth();
    }

    cout<<"Pre92    :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  cout<<TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt()*1.00<<" & ";
    cout<<endl;

    cout<<"Pre92/PRL:"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
      cout<<TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt()*1.00 / RePRL::TotalPredi[AdIdx-1] <<" & ";
    }
    cout<<endl;

    cout<<"Ratio92  :"<<" & ";
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )
      cout<< (MeasuSpec[ set ][ AdIdx-1 ]->GetTotalEnt() - BkgSpec[ set ][ AdIdx-1 ]->GetTotalEnt() )
	/ (TruthSpec[ set ][ AdIdx-1 ]->GetTotalEnt()*(1+Eff::BestEpsilon[set]))<<" & ";
    cout<<endl;
  }

  cout<<" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
  cout<<" nH/nGd background and signal rate ratios "<<endl;
  cout.precision(3);
  
  cout<<"$Ratio_{FastN}$ &";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    double Hrate, HrateE;
    double Grate, GrateE;
 
    Hrate=FastNSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalEnt() /
      gAnalyzeData->Livetime( Dataset::HCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::HCap, AdIdx );

    HrateE=FastNSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalErr() /
      gAnalyzeData->Livetime( Dataset::HCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::HCap, AdIdx );

    Grate=FastNSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalEnt() /
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx );

    GrateE=FastNSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalErr() /
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx );

    double eratio = Hrate/Grate*sqrt(pow((HrateE/Hrate),2)+pow((GrateE/Grate),2));

    cout<<"$"
        <<Hrate/Grate
        <<"\\pm"
	<<eratio
        <<"$";
    if( AdIdx<Basic::NoAd ) {
      cout<<" & ";
    } else {
      cout<<" \\\\\\hline";
    }         
  }
  cout<<endl;
  
  cout<<"$Ratio_{Li9}$ &";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    double Hrate, HrateE;
    double Grate, GrateE;

    Hrate=Li9Spec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalEnt() /
      gAnalyzeData->Livetime( Dataset::HCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::HCap, AdIdx );

    HrateE=Li9Spec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalErr() /
      gAnalyzeData->Livetime( Dataset::HCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::HCap, AdIdx );

    Grate=Li9Spec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalEnt() /
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx );

    GrateE=Li9Spec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalErr() /
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx );
    
    double eratio = Hrate/Grate*sqrt(pow((HrateE/Hrate),2)+pow((GrateE/Grate),2));

    cout<<"$"
        <<Hrate/Grate
        <<"\\pm"
	<<eratio
        <<"$";
    if( AdIdx<Basic::NoAd ) {
      cout<<" & ";
    } else {
      cout<<" \\\\\\hline";
    }
  }
  cout<<endl;
  
  cout<<"$Ratio_{AmC}$ &";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    double Hrate, HrateE;
    double Grate, GrateE;

    Hrate=AmCSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalEnt() /
      gAnalyzeData->Livetime( Dataset::HCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::HCap, AdIdx );

    HrateE=AmCSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalErr() /
      gAnalyzeData->Livetime( Dataset::HCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::HCap, AdIdx );

    Grate=AmCSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalEnt() /
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx );

    GrateE=AmCSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalErr() /
      gAnalyzeData->Livetime( Dataset::GdCap, AdIdx )*24*60*60 /
      gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx );

    double eratio = Hrate/Grate*sqrt(pow((HrateE/Hrate),2)+pow((GrateE/Grate),2));

    cout<<"$"
        <<Hrate/Grate
        <<"\\pm"
	<<eratio
        <<"$";
    if( AdIdx<Basic::NoAd ) {
      cout<<" & ";
    } else {
      cout<<" \\\\\\hline";
    }
  }
  cout<<endl;

  cout.precision(4);
  cout<<"$Ratio_{IBD}$ &";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    double Hrate, HrateE;
    double Grate, GrateE;
    
    Hrate = (MeasuSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalEnt() - BkgSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalEnt()) /
      ( gAnalyzeData->OstwEff( Dataset::HCap, AdIdx )*
	gAnalyzeData->Livetime( Dataset::HCap, AdIdx ) ) * 24*60*60;
    HrateE= sqrt( pow(MeasuSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalErr(),2) +
		  pow(BkgSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalErr(),  2) +
		  pow(Hrate*Un3sigma::frac[AdIdx-1],   2) ) /
      ( gAnalyzeData->OstwEff( Dataset::HCap, AdIdx )*
	gAnalyzeData->Livetime( Dataset::HCap, AdIdx ) ) * 24*60*60;
    
    Grate = (MeasuSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalEnt() - BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalEnt()) /
      ( gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx )*
	gAnalyzeData->Livetime( Dataset::GdCap, AdIdx ) ) * 24*60*60;
    GrateE= sqrt( pow(MeasuSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalErr(),2) +
		  pow(BkgSpec[ Dataset::GdCap ][ AdIdx-1 ]->GetTotalErr(),  2) +
		  pow(Grate*Un3sigma::frac[AdIdx-1],   2) ) /
      ( gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx )*
	gAnalyzeData->Livetime( Dataset::GdCap, AdIdx ) ) * 24*60*60;
    
    double eratio = Hrate/Grate*sqrt(pow((HrateE/Hrate),2)+pow((GrateE/Grate),2));
    
    cout<<"$"
	<<Hrate/Grate
	<<"\\pm"
	<<eratio
	<<"$";
    if( AdIdx<Basic::NoAd ) {
      cout<<" & ";
    } else {
      cout<<" \\\\\\hline";
    }
  }
  cout<<endl;
  
  cout.precision(4);
  cout<<"$Ratio_{IBD_Shape}$ &";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    double Hrate, HrateE;
    double Grate, GrateE;

    Hrate = (MeasuSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalEnt() - BkgSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalEnt()) /
      ( gAnalyzeData->OstwEff( Dataset::HCap, AdIdx )*
        gAnalyzeData->Livetime( Dataset::HCap, AdIdx ) ) * 24*60*60;
    HrateE= sqrt( pow(MeasuSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalErr(),2) +
                  pow(BkgSpec[ Dataset::HCap ][ AdIdx-1 ]->GetTotalErr(),  2) +
                  pow(Hrate*Un3sigma::frac[AdIdx-1],   2) ) /
      ( gAnalyzeData->OstwEff( Dataset::HCap, AdIdx )*
	gAnalyzeData->Livetime( Dataset::HCap, AdIdx ) ) * 24*60*60;

    Grate = ShapePaper::IbdRate[ AdIdx-1 ];
    GrateE= ShapePaper::EIbdRate[ AdIdx-1 ];

    double eratio = Hrate/Grate*sqrt(pow((HrateE/Hrate),2)+pow((GrateE/Grate),2));

    cout<<"$"
        <<Hrate/Grate
        <<"\\pm"
        <<eratio
        <<"$";
    if( AdIdx<Basic::NoAd ) {
      cout<<" & ";
    } else {
      cout<<" \\\\\\hline";
    }
  }
  cout<<endl;

  cout<<"$Ratio_{pred}$ &";
  TimeStamp Time(2012,1,1,1,1,1);
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    double Hpred3m, Hpred3mE, Hpred4m, Hpred4mE, HpredAc, HpredAcE;
    double Hpred, HpredE;
    double Gpred, GpredE;

    Hpred3m = gProtonNumber->Get( Time, AdIdx ).NPGdLs
      * Phys::GdLS_H_Cap_Frac
      * Phys::GdLS_H_Cap_E_Eff
      * Phys::GdLS_H_Cap_T_Eff;
    Hpred3mE = Phys::Hpred3mE;

    Hpred4m = gProtonNumber->Get( Time, AdIdx ).NPLs
      * Phys::LS_H_Cap_Frac
      * Phys::LS_H_Cap_E_Eff
      * Phys::LS_H_Cap_T_Eff;
    Hpred4mE = Phys::Hpred4mE;

    HpredAc = (0.730+1.673)*1000
      *4.78e25
      * Phys::LS_H_Cap_Frac
      * Phys::Acry_H_Cap_Eff;
    HpredAcE = Phys::HpredAcE;

    Hpred = (Hpred3m+Hpred4m+HpredAc) 
      * Phys::H_Cap_D_eff
      * gAnalyzeData->OstwEff( Dataset::HCap, AdIdx );
      

    HpredE= Hpred * sqrt((Hpred3mE*Hpred3mE + Hpred4mE*Hpred4mE + HpredAcE*HpredAcE)/pow((Hpred3m+Hpred4m+HpredAc),2) 
			 + pow(Phys::H_Cap_D_effE,2));

    Gpred=gProtonNumber->Get( Time, AdIdx ).NPGdLs
      * Phys::Gd_Cap_Pmpt_eff
      * Phys::Gd_Cap_Dlyd_eff
      * Phys::GdLS_Gd_Cap_Frac
      * Phys::GdLS_Gd_Cap_D_eff
      * Eff::Flasher_8_eff
      * Eff::Time_8_eff
      * Eff::Spill_in_8_eff
      *gAnalyzeData->OstwEff( Dataset::GdCap, AdIdx );

    GpredE=Gpred *0.015; // CPC paper

    double eratio = Hpred/Gpred*sqrt(pow((HpredE/Hpred),2)+pow((GpredE/Gpred),2));

    cout<<"$"
        <<Hpred/Gpred
        <<"\\pm"
        <<eratio
        <<"$";
    if( AdIdx<Basic::NoAd ) {
      cout<<" & ";
    } else {
      cout<<" \\\\\\hline";
    }
  }
  cout<<endl;


  TFile file("result.root", "recreate");
  // 2. Make some useful plots and table output
  DailyPlot();


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
      AmCSpec[set][AdIdx-1]  ->Write();
      BkgSpec[set][AdIdx-1]  ->Write();
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
  
  TMinuit minuit(33);

  minuit.SetFCN( fcn );  
  double arglist[10];
  int ierflg = 0;
  minuit.mnparm( 0 , "s_2_2_13",   0.1,   0.01,  -0.5,  0.5,  ierflg );
  minuit.mnparm( 1 , "EpsilonGd", -0.0,   0.01,  -0.04, 0.04, ierflg );
  minuit.mnparm( 2 , "EpsilonH",  -0.0,   0.01,  -0.04, 0.04, ierflg );

  minuit.mnparm( 3 , "Eta_d_01", 0,     0.001, -5, 5, ierflg );
  minuit.mnparm( 4 , "Eta_d_02", 0,     0.001, -5, 5, ierflg );
  minuit.mnparm( 5 , "Eta_d_03", 0,     0.001, -5, 5, ierflg );
  minuit.mnparm( 6 , "Eta_d_04", 0,     0.001, -5, 5, ierflg );
  minuit.mnparm( 7 , "Eta_d_05", 0,     0.001, -5, 5, ierflg );
  minuit.mnparm( 8 , "Eta_d_06", 0,     0.001, -5, 5, ierflg );

  minuit.mnparm( 9 , "Eta_d_11", 0,     0.01, -5, 5, ierflg );
  minuit.mnparm( 10, "Eta_d_12", 0,     0.01, -5, 5, ierflg );
  minuit.mnparm( 11, "Eta_d_13", 0,     0.01, -5, 5, ierflg );
  minuit.mnparm( 12, "Eta_d_14", 0,     0.01, -5, 5, ierflg );
  minuit.mnparm( 13, "Eta_d_15", 0,     0.01, -5, 5, ierflg );
  minuit.mnparm( 14, "Eta_d_16", 0,     0.01, -5, 5, ierflg );


  minuit.mnparm( 15, "Eps_d_01", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 16, "Eps_d_02", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 17, "Eps_d_03", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 18, "Eps_d_04", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 19, "Eps_d_05", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 20, "Eps_d_06", 0,   0.01, -5, 5, ierflg );

  minuit.mnparm( 21, "Eps_d_11", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 22, "Eps_d_12", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 23, "Eps_d_13", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 24, "Eps_d_14", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 25, "Eps_d_15", 0,   0.01, -5, 5, ierflg );
  minuit.mnparm( 26, "Eps_d_16", 0,   0.01, -5, 5, ierflg );
  
  minuit.mnparm( 27, "Eps_r_01", 0.017,   0.0001, -5, 5, ierflg );
  minuit.mnparm( 28, "Eps_r_02", 0.017,    0.0001, -5, 5, ierflg );
  minuit.mnparm( 29, "Eps_r_03", 0.007,    0.0001, -5, 5, ierflg );
  minuit.mnparm( 30, "Eps_r_04", 0.007,    0.0001, -5, 5, ierflg );
  minuit.mnparm( 31, "Eps_r_05", 0.009,    0.0001, -5, 5, ierflg );
  minuit.mnparm( 32, "Eps_r_06", 0.012,    0.0001, -5, 5, ierflg );

  /* for systematic error calculation */
  /*
  for( int v=3; v<=32; v++ ) {
    minuit.FixParameter(v);
  }
  */

  if( Basic::GdFit && ! Basic::HFit ) {
    minuit.FixParameter(2 );

    minuit.FixParameter(9 );
    minuit.FixParameter(10);
    minuit.FixParameter(11);
    minuit.FixParameter(12);
    minuit.FixParameter(13);
    minuit.FixParameter(14);

    minuit.FixParameter(21);
    minuit.FixParameter(22);
    minuit.FixParameter(23);
    minuit.FixParameter(24);
    minuit.FixParameter(25);
    minuit.FixParameter(26);
  }
   
  if( ! Basic::GdFit && Basic::HFit ) {
    minuit.FixParameter(1 );

    minuit.FixParameter(3 );
    minuit.FixParameter(4 );
    minuit.FixParameter(5 );
    minuit.FixParameter(6 );
    minuit.FixParameter(7 );
    minuit.FixParameter(8 );
    
    minuit.FixParameter(15);
    minuit.FixParameter(16);
    minuit.FixParameter(17);
    minuit.FixParameter(18);
    minuit.FixParameter(19);
    minuit.FixParameter(20);
  }

  /*
  minuit.FixParameter(26);
  minuit.FixParameter(27);
  minuit.FixParameter(28);
  minuit.FixParameter(29);
  minuit.FixParameter(30);
  minuit.FixParameter(31);
  */
  
  // Minimize
  minuit.SetErrorDef( 1 );
  arglist[0] = 50000;
  minuit.mnexcm( "MIGRAD", arglist, 1, ierflg );
  
  cout.precision(6);
  double par[33],err[33];
  minuit.GetParameter( 0,par[ 0],err[ 0]);  cout<<par[ 0]<<" "<<err[ 0]<<endl;
  minuit.GetParameter( 1,par[ 1],err[ 1]);  cout<<par[ 1]<<" "<<err[ 1]<<endl;
  minuit.GetParameter( 2,par[ 2],err[ 2]);  cout<<par[ 2]<<" "<<err[ 2]<<endl;
  minuit.GetParameter( 3,par[ 3],err[ 3]);  cout<<par[ 3]<<" "<<err[ 3]<<endl;
  minuit.GetParameter( 4,par[ 4],err[ 4]);  cout<<par[ 4]<<" "<<err[ 4]<<endl;
  minuit.GetParameter( 5,par[ 5],err[ 5]);  cout<<par[ 5]<<" "<<err[ 5]<<endl;
  minuit.GetParameter( 6,par[ 6],err[ 6]);  cout<<par[ 6]<<" "<<err[ 6]<<endl;
  minuit.GetParameter( 7,par[ 7],err[ 7]);  cout<<par[ 7]<<" "<<err[ 7]<<endl;
  minuit.GetParameter( 8,par[ 8],err[ 8]);  cout<<par[ 8]<<" "<<err[ 8]<<endl;
  minuit.GetParameter( 9,par[ 9],err[ 9]);  cout<<par[ 9]<<" "<<err[ 9]<<endl;
		      	     	     		      		    					
  minuit.GetParameter(10,par[10],err[10]);  cout<<par[10]<<" "<<err[10]<<endl;
  minuit.GetParameter(11,par[11],err[11]);  cout<<par[11]<<" "<<err[11]<<endl;
  minuit.GetParameter(12,par[12],err[12]);  cout<<par[12]<<" "<<err[12]<<endl;
  minuit.GetParameter(13,par[13],err[13]);  cout<<par[13]<<" "<<err[13]<<endl;
  minuit.GetParameter(14,par[14],err[14]);  cout<<par[14]<<" "<<err[14]<<endl;
  minuit.GetParameter(15,par[15],err[15]);  cout<<par[15]<<" "<<err[15]<<endl;
  minuit.GetParameter(16,par[16],err[16]);  cout<<par[16]<<" "<<err[16]<<endl;
  minuit.GetParameter(17,par[17],err[17]);  cout<<par[17]<<" "<<err[17]<<endl;
  minuit.GetParameter(18,par[18],err[18]);  cout<<par[18]<<" "<<err[18]<<endl;
  minuit.GetParameter(19,par[19],err[19]);  cout<<par[19]<<" "<<err[19]<<endl;
		      	     	     		      		    					
  minuit.GetParameter(20,par[20],err[20]);  cout<<par[20]<<" "<<err[20]<<endl;
  minuit.GetParameter(21,par[21],err[21]);  cout<<par[21]<<" "<<err[21]<<endl;
  minuit.GetParameter(22,par[22],err[22]);  cout<<par[22]<<" "<<err[22]<<endl;
  minuit.GetParameter(23,par[23],err[23]);  cout<<par[23]<<" "<<err[23]<<endl;
  minuit.GetParameter(24,par[24],err[24]);  cout<<par[24]<<" "<<err[24]<<endl;
  minuit.GetParameter(25,par[25],err[25]);  cout<<par[25]<<" "<<err[25]<<endl;
  minuit.GetParameter(26,par[26],err[26]);  cout<<par[26]<<" "<<err[26]<<endl;
  minuit.GetParameter(27,par[27],err[27]);  cout<<par[27]<<" "<<err[27]<<endl;
  minuit.GetParameter(28,par[28],err[28]);  cout<<par[28]<<" "<<err[28]<<endl;
  minuit.GetParameter(29,par[29],err[29]);  cout<<par[29]<<" "<<err[29]<<endl;
		      	     	     		      		    					
  minuit.GetParameter(30,par[30],err[30]);  cout<<par[30]<<" "<<err[30]<<endl;
  minuit.GetParameter(31,par[31],err[31]);  cout<<par[31]<<" "<<err[31]<<endl;
  minuit.GetParameter(32,par[32],err[32]);  cout<<par[32]<<" "<<err[32]<<endl;

  // Chi2 scan
  return 1; 
  minuit.SetPrintLevel(-1);
  for( double s13 = 0; s13<=0.185; s13+=0.185/20) {
    minuit.mnparm( 0 , "s_2_2_13", s13,  0.01,   0, 1, ierflg );
    minuit.FixParameter( 0);
    minuit.SetErrorDef( 1 );
    arglist[0] = 50000;
    minuit.mnexcm( "MIGRAD", arglist, 1, ierflg );

    double chi2,edm,errdef;
    int nvpar,nparx,icstat;
    minuit.mnstat(chi2,edm,errdef,nvpar,nparx,icstat);

    cout<<"sin22t13 "<<s13<<" best chi2 "<<chi2<<endl;
  }

  // get the graph and write it to the root file:
  // In this scan method, the other scan parameters are not reevaluated.
  
  return 1;
  minuit.Command("SCAn 1 30 0 0.185");
  TGraph *gr = (TGraph*)minuit.GetPlot();
  gr->Write(); 
  gr->Dump();
  
  
  return 1;
}

void fcn(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag)
{
  s_2_2_13   = par[0];
  Epsilon[0] = par[1];
  Epsilon[1] = par[2];
  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ )  {
    for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ )  {
      Eta_d[set][AdIdx-1]     = par[ 2 + set*Basic::NoAd + AdIdx ];
      Epsilon_d[set][AdIdx-1] = par[ 14 + set*Basic::NoAd + AdIdx ];
    }
  }

  for( unsigned int RctIdx = 1; RctIdx<=Basic::NoRct; RctIdx++ ) {
    Epsilon_r[RctIdx-1] = par[ 26 + RctIdx ];
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
	double Measu  = MeasuSpec[set][AdIdx-1]->GetTotalEnt();
	double MeasuE = MeasuSpec[set][AdIdx-1]->GetTotalErr();	
	
	/// Background
	double Bkg    = BkgSpec[ set ][ AdIdx-1 ]->GetTotalEnt();
	double BkgE   = BkgSpec[ set ][ AdIdx-1 ]->GetTotalErr();

	/// Prediction
	TruthSpec[set][AdIdx-1]->SetupTruth();
	double Truth  = TruthSpec[set][AdIdx-1]->GetTotalEnt();

	/* Prediction's uncertainties */
	double SumR=0;
        for ( unsigned int rct=1; rct<=Basic::NoRct; rct++ )
          {  
	    SumR += TruthSpec[set][AdIdx-1]->Omega_r( rct ) * Epsilon_r[rct-1];  
	  }

	Truth *= ( 1 + SumR + Epsilon[set] + Epsilon_d[set][AdIdx-1] );
	//double Tr_Pull = Epsilon_d[set][AdIdx-1] / 0.00000001; // For stat. study
	//double Tr_Pull = Epsilon_d[set][AdIdx-1] / 0.0065; // With only uncoupled uncertainty
	double Tr_Pull = Epsilon_d[set][AdIdx-1] / Eff::EffUncer[set];

	/// Background
	Bkg *= ( 1+Eta_d[set][AdIdx-1] );
	double Sigma_d_B = BkgE/Bkg;
	//double Bd_Pull = Eta_d[set][AdIdx-1] / 0.00000001; // For stat. study
	double Bd_Pull = Eta_d[set][AdIdx-1] / Sigma_d_B;

	/// chi-square
	cout<<"  "<<AdIdx<<" Measurement:Truth = "<< Measu-Bkg<<"+/-"<<sqrt( pow(MeasuE,2)+pow(BkgE,2) )<<" : "<<Truth
	    <<" = "<<(Measu-Bkg)/Truth
	    <<endl;
	
	chi2 += pow( (Measu - Truth - Bkg), 2) / Measu
	  + pow( Tr_Pull, 2)
	  + pow( Bd_Pull, 2) ;
      }
    }
  }

  for( unsigned int rct=1; rct<=Basic::NoRct; rct++ ) {
    //double Rct_Pull = Epsilon_r[rct-1]/ 0.00000001; // For Stat. study
    double Rct_Pull = Epsilon_r[rct-1]/ 0.008;
    chi2 += pow( Rct_Pull, 2 );
  }

  f = chi2;
  cout<<"  chi2= "<<chi2<<endl;
  
  return;
}


double ratio ( double a, double ea, double b, double eb )
{
  return a/b;
}


double eratio( double a, double ea, double b, double eb )
{
  double r=a/b;
  double dr=sqrt( r*r*( ea*ea/a/a + eb*eb/b/b )  );
  return dr;
}
