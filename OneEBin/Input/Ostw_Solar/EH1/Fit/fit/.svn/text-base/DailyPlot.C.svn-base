#include "Truth.h"
#include "Constants.h"
#include "Flux.h"
#include "Crosssection.h"
#include "ProtonNumber.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "iostream"
#include "IGetFlux.h"
#include "GetWeeklyFlux.h"
#include "Baseline.h"
#include <stdio.h>
#include <math.h>
using namespace CLHEP;
using namespace std;

void DailyPlot()
{
  IGetFlux* GetFlux;
  if( Basic::DailyFlux == true )  {
  } else {
    if( gGetWeeklyFlux == 0 ) {
      gGetWeeklyFlux = new GetWeeklyFlux;
    }
    GetFlux = gGetWeeklyFlux;
  } 

  cout<<"Time:AD1:AD2:AD3:AD4:AD5:AD6"<<endl;
  for( TimeStamp Time = Basic::BeginTime; Time < Basic::EndTime; Time.Add( Basic::StepTime ) )  {

    double Sum[ Basic::NoAd ];

    for( unsigned int m_AdNo = 0; m_AdNo<Basic::NoAd; m_AdNo++ )  {

      double SumSingle=0;

      for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
	for( unsigned int RctIdx = 0; RctIdx < Basic::NoRct; RctIdx++ )  {
	  
	  double Increment = 0;
	  
	  if( Basic::GdFit ) {
	    
	    Increment =
	      gCrosssection->GetBinContent( BinIdx )
	      * GetFlux->Get( Time, RctIdx, BinIdx )
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPGdLs
	      * Basic::StepTime.GetSec() * CLHEP::second;
	    
	    SumSingle += Increment;
	    cout<<Increment<<endl;
	  }
	}
      }      
      Sum[ m_AdNo ] = SumSingle;
    }
    
    /* Write out */
    cout<<Time.GetSec();
    for( unsigned int m_AdNo = 0; m_AdNo<Basic::NoAd; m_AdNo++ )  {
      cout<<" "<<Sum[m_AdNo];
    }
    cout<<endl;
  }
}
