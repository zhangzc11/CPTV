#include "AnalyzeData.h"
#include "AdMap.h"
#include "Truth.h"
#include "Constants.h"

#include "Flux/FluxXsec.h"
#include "Flux/IGetFluxXsec.h"
#include "Flux/GetFluxXsec.h"
#include "RctXsecTheory/Crosssection.h"
#include "ProtonNumber.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <iostream>
#include "Baseline.h"
#include <stdio.h>
#include <math.h>
using namespace CLHEP;
using namespace std;

extern Truth*        TruthSpec[2][ Basic::NoAd ];

void DailyPlot()
{
  cout<<" [ Measured and predicted rate ] "<<endl;
  /* Predicted daily rate */
  IGetFluxXsec* GetFluxXsec;
  if( Basic::DailyFlux == true ) {
    /// Daily flux blinded.
  } else {
    GetFluxXsec = gGetFluxXsec;
  }


  /* Daily rate */
  TimeStamp BeginTime(2011,12,24,0,0,0);
  TimeStamp EndTime  (2012,02,11,0,0,0);
  TimeStamp Week(7*24*60*60);
  TimeStamp Day(24*60*60);
  map< TimeStamp, double > Rate[ Basic::NoAd ];

  for( TimeStamp Time = BeginTime; Time <= EndTime; Time.Add( Week ) )  {
    for( unsigned int m_AdNo = 1; m_AdNo<=Basic::NoAd; m_AdNo++ )  {
      
      double Sum=0;

      for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
	for( unsigned int RctIdx = 1; RctIdx <= Basic::NoRct; RctIdx++ )  {

	  Sum +=
	    GetFluxXsec->Get( Time, RctIdx, BinIdx )
	    * (Binning::EndEnergy-Binning::BeginEnergy)/Binning::NHistoBin
	    * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	    * gProtonNumber->Get( Time, m_AdNo ).NPGdLs
	    * Day.GetSeconds()*CLHEP::second;

	}
      }
      
      Rate[m_AdNo-1][Time] = Sum;
    }
  }

  /// Sum over all live time
  double Sum8[Basic::NoAd];
  const std::vector< RunBrief* > Runs = gAnalyzeData->GetRuns();

  /* ============================================== */
  for( unsigned int m_AdNo=1; m_AdNo<=Basic::NoAd; m_AdNo++ ) {
    Sum8[m_AdNo-1] = 0;

    int Site = ToSite(m_AdNo);
    int LocalAdNo = ToLocalAdNo(m_AdNo);

    for( std::vector< RunBrief* >::const_iterator iRun = Runs.begin();
	 iRun!=Runs.end(); iRun++ ) {

      const RunBrief* const Brief = (*iRun);

      if( Dataset::GdCap != Brief->Dataset ) continue;

      /* Must be from the same site */
      if( Site != Brief->Site ) continue;

      /* Cache run info */
      double fulltime     = Brief->Fulltime;
      double livefraction = Brief->Livetime[ LocalAdNo-1 ] / fulltime;

      /* split it into days */
      for( TimeStamp Time = Brief->StartTime; Time < Brief->StopTime; /* Complex increment */) {

	/* Through this, runs span over a day are split into days at exactly 00:00:00 */
	unsigned int StartDate,StartYY,StartMM,StartDD;
	unsigned int StopDate, StopYY, StopMM, StopDD;

	StartDate =            Time.GetDate( true, 0, &StartYY, &StartMM, &StartDD );
	StopDate  = Brief->StopTime.GetDate( true, 0, &StopYY,  &StopMM,  &StopDD  );

	TimeStamp Step(0,0); /* Alway init a TimeStamp, otherwise it will be inited to sys time and too slow. */
	if( StartDate == StopDate ) {
	  /* The same day */
	  Step = Brief->StopTime - Time;
	} else {
	  /* The closest day's end */
	  TimeStamp DaysEnd( StartYY,StartMM,StartDD+1, 0, 0, 0, 0);
	  Step = DaysEnd - Time;
	}

	for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ ) {
	  for( unsigned int RctIdx = 1; RctIdx <= Basic::NoRct; RctIdx++ ) {

	    Sum8[m_AdNo-1] +=
	      GetFluxXsec->Get( Time, RctIdx, BinIdx )
	      * (Binning::EndEnergy-Binning::BeginEnergy)/Binning::NHistoBin
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPGdLs
	      * Step.GetSeconds()*CLHEP::second;
	  }
	}
	/* After all calculation, calculate the addtion for Time */
	Time.Add( Step );
      }
    }
  }
  

  /// Printout
  cout<<" [ Weekly rate (day^-1), no oscillation ] "<<endl;
  for( TimeStamp Time = BeginTime; Time <= EndTime; Time.Add( Week ) ) {
    cout<<Time<<"\t";
    for( unsigned int m_AdNo = 1; m_AdNo<=Basic::NoAd; m_AdNo++ ) {
      cout<<Rate[m_AdNo-1][Time]<<"\t";
    }
    cout<<endl;
  }
  
  cout<<"Sum                             ";
  for( unsigned int m_AdNo = 1; m_AdNo<=Basic::NoAd; m_AdNo++ ) 
    cout<<Sum8[m_AdNo-1]<<"\t";
  cout<<endl;

}
