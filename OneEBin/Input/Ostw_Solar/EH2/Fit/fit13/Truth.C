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

double Truth::GetTotalEnt()
{
  if( RepeatPRL ) {
    return 
      RePRL::TotalPredi[ m_AdNo-1 ] *
      ( 1 - RePRL::Deficit_13[ m_AdNo-1 ] * s_2_2_13 );
  } else if ( UsePRLFlux ) {
    return 
      RePRL::TotalPredi[ m_AdNo-1 ] *
      ( 1 - RePRL::Deficit_13[ m_AdNo-1 ] * s_2_2_13 ) *
      gAnalyzeData->MuVeEff( Dataset::GdCap, m_AdNo ) * gAnalyzeData->OstwEff( Dataset::GdCap, m_AdNo ) / RePRL::MuonOstwEf[ m_AdNo-1 ];
  } else {
    return Spectrum::GetTotalEnt();
  }
}

int Truth::SetupTruth()
{
  //cout<<"SetupTruth: s_2_2_13 "<<s_2_2_13<<endl;
  if( RepeatPRL || UsePRLFlux ) {
    return 1;
  }

  /// Reset all bin contents
  Reset();

  IGetFluxXsec* getFluxXsec;
  if( Basic::DailyFlux == true )  {
    /// Daily flux blinded.
  } else {
    if( gGetFluxXsec==0 ) getFluxXsec = new GetFluxXsec;
    else getFluxXsec = gGetFluxXsec;
  }

  const std::vector< RunBrief* > Runs = gAnalyzeData->GetRuns();

  /* ============================================== */
  double NTot_non_osci = 0;
  double N_non_osci[ Basic::NoRct ] = { 0,0,0,0,0,0 };

  double TotalFullTime = 0;
  double TotalLiveTime = 0;
  double nu[Basic::NoRct] = { 0,0,0,0,0,0 };

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
    double deltat       = (Brief->StopTime-Brief->StartTime).GetSeconds();  // Total Daq time
    double fulltime     = Brief->Fulltime;  // Bad runs removed 
    double livefraction = Brief->Livetime[ LocalAdNo-1 ] / deltat;  // Muon veto removed
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

      TotalFullTime += Step.GetSeconds()*CLHEP::second;
      TotalLiveTime += thislivetime;

      double EStep = (Binning::EndStudyEnergy-Binning::BgnStudyEnergy)/(Binning::EndBin-Binning::BgnBin+1);

      for( unsigned int BinIdx = Binning::BgnBin; BinIdx <= Binning::EndBin; BinIdx++ )  {
	
	for( unsigned int RctIdx = 1; RctIdx <= Basic::NoRct; RctIdx++ )  {
	  
	  double NTruth = GetBinContent( BinIdx );
	  double Increment = 0;
	  double Incre8 = 0, Incre22 = 0;
	  
	  // Get bin center of visiable energy
	  double Evis = Binning::BgnStudyEnergy + (BinIdx-0.5) * EStep;
	  double Enu  = Evis + Phys::EnuToEprompt;
	  
	  double survp = survp = SurvProb( s_2_2_13, Baseline(RctIdx, m_AdNo), Enu);
	  if( !init ) {
	    survp = 1;
	    
	    nu[RctIdx-1] +=
	      getFluxXsec->Get( Time, RctIdx, BinIdx )
              * EStep
	      * Step.GetSeconds()*CLHEP::second* fulltime/deltat
	      * gProtonNumber->Get( Time, m_AdNo ).NPGdLs
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926;
	  }

	  if( m_dataset == Dataset::GdCap ) {
	    
	    Incre8 += 
	      getFluxXsec->Get( Time, RctIdx, BinIdx ) 
	      * EStep
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPGdLs 
	      * thislivetime 
	      * OstwEff
	      * survp
	      * Phys::Gd_Cap_Pmpt_eff
	      * Phys::Gd_Cap_Dlyd_eff
	      * Phys::GdLS_Gd_Cap_Frac
	      * Phys::GdLS_Gd_Cap_D_eff
	      * Eff::Flasher_8_eff
	      * Eff::Time_8_eff
	      * Eff::Spill_in_8_eff;	     
	    
	      N_non_osci[ RctIdx-1 ] += Incre8;
	      
	  }

	  if( m_dataset == Dataset::HCap ) {
	    /// GdLS part
	    Incre22 +=
	      getFluxXsec->Get( Time, RctIdx, BinIdx )
	      * EStep
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPGdLs
              * thislivetime
	      * OstwEff
	      * Phys::GdLS_H_Cap_Frac
	      * Phys::GdLS_H_Cap_E_Eff
	      * Phys::GdLS_H_Cap_T_Eff
	      * Phys::H_Cap_D_eff
	      * survp
	      * Eff::Eff15[ m_AdNo-1 ][ RctIdx-1 ]/Eff::Eff15NoOsci;  // This should be energy dependent.
	    
	    /// LS part
	    Incre22 +=
	      getFluxXsec->Get( Time, RctIdx, BinIdx )
	      * EStep
	      * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * gProtonNumber->Get( Time, m_AdNo ).NPLs
              * thislivetime
	      * OstwEff
	      * Phys::LS_H_Cap_Frac
	      * Phys::LS_H_Cap_E_Eff
	      * Phys::LS_H_Cap_T_Eff
              * Phys::H_Cap_D_eff
	      * survp
	      * Eff::Eff15[ m_AdNo-1 ][ RctIdx-1 ]/Eff::Eff15NoOsci;  // This should be energy dependent.

	    /// Acrylic part
	    Incre22 +=
	      getFluxXsec->Get( Time, RctIdx, BinIdx )
              * EStep
              * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	      * Phys::AcMass * Phys::AcPD
	      * thislivetime
              * OstwEff
	      * Phys::Acry_H_Cap_Eff
	      * Phys::H_Cap_D_eff
	      * survp
	      * Eff::Eff15[ m_AdNo-1 ][ RctIdx-1 ]/Eff::Eff15NoOsci;  // This should be energy dependent.

	    N_non_osci[ RctIdx-1 ] += Incre22;
	  }
	  
	  Increment = Incre8 + Incre22;
	  
	  SetBinContent( BinIdx, NTruth + Increment );
	}
      }
      
      /* After all calculation, calculate the addtion for Time */
      Time.Add( Step );
    }
  }
  
  //cout<<"totalfulltime Ad "<<m_AdNo<<" "<<TotalFullTime/1e9/24/60/60<<endl;
  //cout<<"totallivetime Ad "<<m_AdNo<<" "<<TotalLiveTime/1e9/24/60/60<<endl;

  if( !init ) {
    cout<<" Expected events from each core ";
    for( unsigned int rct = 1; rct<=Basic::NoRct; rct++ ) {
      cout<< N_non_osci[ rct-1 ]<<" ";
    }
    cout<<endl;
    
    for( unsigned int rct = 1; rct<=Basic::NoRct; rct++ ) {
      NTot_non_osci += N_non_osci[ rct-1 ];
    }
    for( unsigned int rct = 1; rct<=Basic::NoRct; rct++ ) {
      //if( m_Omega_r[ rct-1 ] <1e-20 ) 
      m_Omega_r[ rct-1 ] = N_non_osci[ rct-1 ]/NTot_non_osci;
    }

    cout<<"nu_i: ";
    cout<<nu[0]<<"  "<<nu[1]<<"  "<<nu[2]<<"  "<<nu[3]<<"  "<<nu[4]<<"  "<<nu[5]<<endl;
    double wline=0;  // weighted baseline
    double w=0;
    for( unsigned int rct = 1; rct<=Basic::NoRct; rct++ ) {
      //cout<<Baseline(rct, m_AdNo)<<" "<<nu[rct-1]<<endl;
      wline += pow( Baseline(rct, m_AdNo)/CLHEP::meter, -2) * nu[rct-1];
      w += nu[rct-1];
    }
    wline /= w;
    wline = sqrt(1/wline);

    cout<<"weight_baseline_i: "<<m_AdNo<<" "<<wline<<endl;
  }
  init = true;

  return 1;
}

double Truth::Omega_r( int ReactorIdx )
{
  if( RepeatPRL ) {
    return RePRL::Omega_d_r[ m_AdNo-1 ][ ReactorIdx-1 ];
  } else {
    return m_Omega_r[ ReactorIdx-1 ];
  }
}
