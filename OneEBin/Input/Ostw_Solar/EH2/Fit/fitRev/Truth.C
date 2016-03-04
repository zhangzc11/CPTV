#include "Truth.h"
#include "Constants.h"
#include "Flux/FluxXsec.h"
#include "Flux/IGetFluxXsec.h"
#include "Flux/GetFluxXsec.h"
#include "RctXsecTheory/Crosssection.h"
#include "ProtonNumber.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "Baseline.h"
#include "AnalyzeData.h"
#include "AdMap.h"
#include "SurvProb.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace CLHEP;
using namespace std;

double Truth::Integral()
{
  if( RepeatPRL ) {
    return 
      RePRL::TotalPredi[ m_AdNo-1 ] *
      RePRL::MuonOstwEf[ m_AdNo-1 ] *
      RePRL::OthersEffi *
      ( 1 - RePRL::Deficit_13[ m_AdNo-1 ] * s_2_2_13 );
  } else {
    return Spectrum::Integral();
  }
}

int Truth::SetupTruth()
{
  if( RepeatPRL ) {
    return 1;
  }

  /// Reset all bin contents
  Reset();

  IGetFluxXsec* GetFluxXsec;
  if( Basic::DailyFlux == true )  {
    /// Daily flux blinded.
  } else {
    GetFluxXsec = gGetFluxXsec;
  }

  const std::vector< RunBrief* > Runs = gAnalyzeData->GetRuns();

  /* ============================================== */
  for( std::vector< RunBrief* >::const_iterator iRun = Runs.begin(); 
       iRun!=Runs.end(); iRun++ )  {

    const RunBrief* const Brief = (*iRun);

    int Dataset = Brief->Dataset;
    
    if( m_dataset != Dataset ) continue;
    
    int Site = ToSite(m_AdNo);
    int LocalAdNo = ToLocalAdNo(m_AdNo);

    /* Must be from the same site */
    if( Site != Brief->Site ) continue;
    
    /* Cache run info */
    double fulltime     = Brief->Fulltime;
    double livefraction = Brief->Livetime[ LocalAdNo-1 ] / fulltime;
    double OstwEff      = Brief->OstwEff[ LocalAdNo-1 ];

    /* split it into days */
    for( TimeStamp Time = Brief->StartTime; Time < Brief->StopTime; /* Complex increment */)  {
            
      /* Through this, runs span over a day are split into days at exactly 00:00:00 */
      unsigned int StartDate,StartYY,StartMM,StartDD;
      unsigned int StopDate, StopYY, StopMM, StopDD;
      
      StartDate =            Time.GetDate( true, 0, &StartYY, &StartMM, &StartDD );
      StopDate  = Brief->StopTime.GetDate( true, 0, &StopYY,  &StopMM,  &StopDD  );

      TimeStamp Step(0,0); /* Alway init a TimeStamp, otherwise it will be inited to sys time and too slow. */
      if( StartDate == StopDate )  {
	/* The same day */
	Step = Brief->StopTime - Time;
      } else {
	/* The closest day's end */
	TimeStamp DaysEnd( StartYY,StartMM,StartDD+1, 0, 0, 0, 0);
	Step = DaysEnd - Time;
      }

      /* live time in this step */
      double thislivetime = Step.GetSeconds()*CLHEP::second * livefraction;

      for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
	for( unsigned int RctIdx = 1; RctIdx <= Basic::NoRct; RctIdx++ )  {
	  
	  double NTruth = GetBinContent( BinIdx );
	  double Increment = 0;
	  double Incre8 = 0, Incre22 = 0;
	  
	  double Evis = Binning::BeginEnergy + (BinIdx-1) * (Binning::EndEnergy-Binning::BeginEnergy)/Binning::NHistoBin;
	  double Enu  = Evis + Phys::EnuToEprompt;

	  if( m_dataset == Dataset::GdCap ) {
	    
	    Incre8 += 
	      GetFluxXsec->Get( Time, RctIdx, BinIdx ) 
	      * (Binning::EndEnergy-Binning::BeginEnergy)/Binning::NHistoBin
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPGdLs 
	      * thislivetime 
	      * OstwEff
	      * SurvProb( s_2_2_13, Baseline(RctIdx, m_AdNo), Enu)
	      * Phys::Gd_Cap_Pmpt_eff
	      * Phys::Gd_Cap_Dlyd_eff
	      * Phys::GdLS_Gd_Cap_Frac
	      * Phys::GdLS_Distance_8_eff  /* 100% */
	      * Eff::Flasher_8_eff
	      * Eff::Time_8_eff
	      * Eff::Spill_in_8_eff;
	  }

	  if( m_dataset == Dataset::HCap ) {
	    /// GdLS part
	    Incre22 +=
	      GetFluxXsec->Get( Time, RctIdx, BinIdx )
	      * (Binning::EndEnergy-Binning::BeginEnergy)/Binning::NHistoBin
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPGdLs
              * thislivetime
	      * OstwEff
	      * Phys::GdLS_H_Cap_Frac
	      * SurvProb( s_2_2_13, Baseline(RctIdx, m_AdNo), Enu)
	      * Phys::GdLS_Distance_22_eff;  /* Not finalized. */

	    //cout<<s_2_2_13<<" "<<Baseline(RctIdx, m_AdNo)/CLHEP::m<<" "<<Enu/CLHEP::MeV<<" "<<SurvProb( s_2_2_13, Baseline(RctIdx, m_AdNo), Enu)<<endl;
	    
	    /// LS part
	    Incre22 +=
	      GetFluxXsec->Get( Time, RctIdx, BinIdx )
	      * (Binning::EndEnergy-Binning::BeginEnergy)/Binning::NHistoBin
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPLs
              * thislivetime
	      * OstwEff
	      * Phys::En3sigma_eff
	      * SurvProb( s_2_2_13, Baseline(RctIdx, m_AdNo), Enu)
	      * Phys::LS_Distance_22_eff;  /* Not finalized. */
	  }
	  
	  Increment = Incre8 + Incre22;
	  
	  SetBinContent( BinIdx, NTruth + Increment );

	}
      }
      
      /* After all calculation, calculate the addtion for Time */
      Time.Add( Step );
    }

  }

  return 1;
}
