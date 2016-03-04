#include "Truth.h"
#include "Constants.h"
#include "Flux.h"
#include "Crosssection.h"
#include "ProtonNumber.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "IGetFlux.h"
#include "GetWeeklyFlux.h"
#include "Baseline.h"
#include "AnalyzeData.h"
#include "AdMap.h"
#include "OstwEff.h"
#include "SurvProb.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace CLHEP;
using namespace std;

int Truth::SetupTruth()
{
  /// Reset all bin contents
  Reset();

  IGetFlux* GetFlux;
  if( Basic::DailyFlux == true )  {
  } else {
    GetFlux = gGetWeeklyFlux;
  }

  const std::map< int /* RunNumber */, RunBrief* > Runs = gAnalyzeData->GetRuns();
  std::map< int /* RunNumber */, RunBrief* >::const_iterator  iRun, iRunEnd = Runs.end();

  /* ============================================== */
  for( iRun = Runs.begin(); iRun!=iRunEnd; iRun++ )  {

    const RunBrief* const Brief = iRun->second;

    int Site = ToSite(m_AdNo+1);
    int LocalAdNo = ToLocalAdNo(m_AdNo+1);

    /* Must be from the same site */
    if( Site != Brief->Site ) continue;

    for( TimeStamp Time = Brief->StartTime; Time < Brief->StopTime; /* Complex addition */)  {
            
      /* Through this, runs span over a day are split into days at exactly 00:00:00 */
      unsigned int StartDate,StartYY,StartMM,StartDD;
      unsigned int StopDate, StopYY, StopMM, StopDD;
      
      StartDate =            Time.GetDate( true, 0, &StartYY, &StartMM, &StartDD );
      StopDate  = Brief->StopTime.GetDate( true, 0, &StopYY,  &StopMM,  &StopDD  );

      TimeStamp Step;
      if( StartDate == StopDate )  {
	Step = Brief->StopTime - Time;
      } else {
	/* The closest day's end */
	TimeStamp DaysEnd( StartYY,StartMM,StartDD+1, 0, 0, 0, 0);
	Step = DaysEnd - Time;
      }

      /* live time in this step */
      double fulltime     = Brief->Fulltime;
      double livefraction = Brief->Livetime[LocalAdNo-1] / fulltime;
      double thislivetime = Step.GetSeconds()*CLHEP::second * livefraction;
      double Rmu          = Brief->Rnetmu[LocalAdNo-1];
      double Rs           = Brief->Rs[LocalAdNo-1];

      for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
	for( unsigned int RctIdx = 0; RctIdx < Basic::NoRct; RctIdx++ )  {
	  
	  double NTruth = GetBinContent( BinIdx );
	  double Increment = 0;
	  double Incre8 = 0, Incre22 = 0;
	  
	  double Evis = Binning::BeginEnergy + (BinIdx-1) * (Binning::EndEnergy-Binning::BeginEnergy)/Binning::NHistoBin;
	  double Enu  = Evis + Phys::EnuToEprompt;

	  if( m_dataset == Dataset::GdCap ) {

	    cout<<BinIdx<<"  "<<gCrosssection->GetBinContent( BinIdx )
              * GetFlux->Get( Time, RctIdx, BinIdx )<<endl;
	    
	    Incre8 += 
	      gCrosssection->GetBinContent( BinIdx )
	      * GetFlux->Get( Time, RctIdx, BinIdx )
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPGdLs 
	      * thislivetime 
	      * REN(Rs, Rmu, Phys::Tc/CLHEP::second, 1, 1.0, 0.90 /*PRL*/, 1, Phys::GdLS_Cap_Lam*CLHEP::second, 0 ) /* RIBD=1 for efficiency measurement. */ 
	      * Phys::GdLS_Gd_Cap_Frac
	      * SurvProb( s_2_2_13, Baseline(RctIdx, m_AdNo), Enu)
	      * Phys::GdLS_Distance_eff  /* Not finalized. */
	      * UnknownEffi;
	  }

	  if( m_dataset == Dataset::HCap ) {
	    /// GdLS part
	    Incre22 +=
	      gCrosssection->GetBinContent( BinIdx )
	      * GetFlux->Get( Time, RctIdx, BinIdx )
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPGdLs
              * thislivetime
	      * REN(Rs, Rmu, Phys::Tc/CLHEP::second, 1, 1.0, 0.90 /*PRL*/, 1, Phys::GdLS_Cap_Lam*CLHEP::second, 0 ) /* RIBD=1 for efficiency measurement. */
	      * Phys::GdLS_H_Cap_Frac
	      * SurvProb( s_2_2_13, Baseline(RctIdx, m_AdNo), Enu)
	      * Phys::GdLS_Distance_eff  /* Not finalized. */
	      * UnknownEffi;

	    //cout<<s_2_2_13<<" "<<Baseline(RctIdx, m_AdNo)/CLHEP::m<<" "<<Enu/CLHEP::MeV<<" "<<SurvProb( s_2_2_13, Baseline(RctIdx, m_AdNo), Enu)<<endl;
	    
	    /// LS part
	    Incre22 +=
	      gCrosssection->GetBinContent( BinIdx )
	      * GetFlux->Get( Time, RctIdx, BinIdx )
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPLs
              * thislivetime
	      * REN(Rs, Rmu, Phys::Tc/CLHEP::second, 1, 1.0, Phys::LowECut_eff, 1, Phys::LS_Cap_Lam*CLHEP::second, 0 ) /* RIBD=1 for efficiency measurement */
	      * Phys::En3sigma_eff
	      * SurvProb( s_2_2_13, Baseline(RctIdx, m_AdNo), Enu)
	      * Phys::LS_Distance_eff  /* Not finalized. */
	      * UnknownEffi;
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
