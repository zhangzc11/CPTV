#include "AnalyzeData.h"
#include "AdMap.h"
#include "DailyPlot.h"
#include "Constants.h"
#include "Measurement.h"
#include "Truth.h"
#include "Background/Background.h"
#include "Background/Li9.h"
#include "Background/Acc.h"
#include "Background/FastN.h"
#include "Background/AmC.h"

#include "TGraphErrors.h"

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

extern Measurement*  MeasuSpec[2][ Basic::NoAd ];
extern Truth*        TruthSpec[2][ Basic::NoAd ];
extern Background*   BkgSpec  [2][ Basic::NoAd ];
extern Acc*          AccSpec  [2][ Basic::NoAd ];
extern FastN*        FastNSpec[2][ Basic::NoAd ];
extern Li9*          Li9Spec  [2][ Basic::NoAd ];
extern AmC*          AmCSpec  [2][ Basic::NoAd ];

void DailyPlot()
{
  PredNIBD();
  DailyIBD();
  // MuonRate(); // per run
}  

void PredNIBD()
{
  cout<<" [ Measured and predicted rate ] "<<endl;
  /* Predicted daily rate */
  IGetFluxXsec* getFluxXsec;
  if( Basic::DailyFlux == true ) {
    /// Daily flux blinded.
  } else {
    if( gGetFluxXsec==0 ) getFluxXsec = new GetFluxXsec;
    else getFluxXsec = gGetFluxXsec;
  }


  /* Predicted daily rate according to reactor power */
  TimeStamp Week(7*24*60*60);
  TimeStamp Day(24*60*60);
  map< TimeStamp, double > PredDailyRate[ Basic::NoAd ];

  for( TimeStamp Time = Basic::BeginTime; Time <= Basic::EndTime; Time.Add( Week ) )  {
    for( unsigned int m_AdNo = 1; m_AdNo<=Basic::NoAd; m_AdNo++ )  {
      
      double Sum=0;

      for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
	for( unsigned int RctIdx = 1; RctIdx <= Basic::NoRct; RctIdx++ )  {

	  Sum +=
	    getFluxXsec->Get( Time, RctIdx, BinIdx )
	    * (Binning::EndEnergy-Binning::BeginEnergy)/Binning::NHistoBin
	    * pow( Baseline(RctIdx, m_AdNo), -2 ) / 4 /3.1415926
	    * gProtonNumber->Get( Time, m_AdNo ).NPGdLs
	    * Day.GetSeconds()*CLHEP::second;

	}
      }
      
      PredDailyRate[m_AdNo-1][Time] = Sum;
    }
  }

  /// Predicted number of IBD reactions according to detectors' livetime and reactors' power
  double PredSum8[Basic::NoAd];
  const std::vector< RunBrief* > Runs = gAnalyzeData->GetRuns();

  /* ============================================== */
  for( unsigned int m_AdNo=1; m_AdNo<=Basic::NoAd; m_AdNo++ ) {
    PredSum8[m_AdNo-1] = 0;

    int Site = ToSite(m_AdNo);
    //int LocalAdNo = ToLocalAdNo(m_AdNo);

    for( std::vector< RunBrief* >::const_iterator iRun = Runs.begin();
	 iRun!=Runs.end(); iRun++ ) {

      const RunBrief* const Brief = (*iRun);

      if( Dataset::GdCap != Brief->Dataset ) continue;

      /* Must be from the same site */
      if( Site != Brief->Site ) continue;

      /* Cache run info */
      //double fulltime     = Brief->Fulltime;
      //double livefraction = Brief->Livetime[ LocalAdNo-1 ] / fulltime;

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

	    PredSum8[m_AdNo-1] +=
	      getFluxXsec->Get( Time, RctIdx, BinIdx )
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
  cout<<" [ Predicted daily rate (in each week), no oscillation ] "<<endl;
  for( TimeStamp Time = Basic::BeginTime; Time <= Basic::EndTime; Time.Add( Week ) ) {
    cout<<Time<<"\t";
    for( unsigned int m_AdNo = 1; m_AdNo<=Basic::NoAd; m_AdNo++ ) {
      cout<<PredDailyRate[m_AdNo-1][Time]<<"\t";
    }
    cout<<endl;
  }
  
  cout<<"Sum                             ";
  for( unsigned int m_AdNo = 1; m_AdNo<=Basic::NoAd; m_AdNo++ ) 
    cout<<PredSum8[m_AdNo-1]<<"\t";
  cout<<endl;

}


void DailyIBD()
{
  /// Number of IBD events per day plot
  map< TimeStamp, double /*FullT*/ > FullT[ Basic::NoAd ];
  map< TimeStamp, double /*LiTi*/ > LiTi[ Basic::NoAd ];

  map< TimeStamp, double /*NIBD*/ > NIBD[ Basic::NoAd ];
  map< TimeStamp, double /*Errr*/ > ErSq[ Basic::NoAd ];

  map< TimeStamp, double /*NMuon*/ > NMuon[ Basic::NoAd ];
  map< TimeStamp, double /*MErSq*/ > MErSq[ Basic::NoAd ];

  map< TimeStamp, double /*OstwEff*Time*/ > OstTi[ Basic::NoAd ];

  map< TimeStamp, double /*NAcci*/ > NAcci[ Basic::NoAd ];
  map< TimeStamp, double /*NAccE*/ > NAccE[ Basic::NoAd ];

  map< TimeStamp, double /*RSing*/ > RSing[ Basic::NoAd ];
  
  const std::vector< RunBrief* > Runs = gAnalyzeData->GetRuns();

  /* ============================================== */
  for( int set = Dataset::GdCap; set<=Dataset::HCap; set++ ) {

  for( unsigned int m_AdNo=1; m_AdNo<=Basic::NoAd; m_AdNo++ ) {

    FullT[m_AdNo-1].clear();
    LiTi[m_AdNo-1].clear();
    NIBD[m_AdNo-1].clear();
    ErSq[m_AdNo-1].clear();
    NMuon[m_AdNo-1].clear();
    MErSq[m_AdNo-1].clear();
    OstTi[m_AdNo-1].clear();
    NAcci[m_AdNo-1].clear();
    NAccE[m_AdNo-1].clear();
    RSing[m_AdNo-1].clear();

    int Site = ToSite(m_AdNo);
    int LocalAdNo = ToLocalAdNo(m_AdNo);

    for( std::vector< RunBrief* >::const_iterator iRun = Runs.begin();
         iRun!=Runs.end(); iRun++ ) {

      const RunBrief* const Brief = (*iRun);

      /* Hydrogen plots only */
      if( set != Brief->Dataset ) continue;

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
	
	TimeStamp Date( StartYY, StartMM, StartDD, 0,0,0,0);
	if (NIBD[ m_AdNo-1 ].find( Date ) == NIBD[ m_AdNo-1 ].end()) {
	  FullT[ m_AdNo-1 ][ Date ] = 0;
	  LiTi[ m_AdNo-1 ][ Date ] = 0;
	  NIBD[ m_AdNo-1 ][ Date ] = 0;
	  ErSq[ m_AdNo-1 ][ Date ] = 0;
	  NMuon[ m_AdNo-1 ][ Date ] = 0;
	  MErSq[ m_AdNo-1 ][ Date ] = 0;
	  OstTi[ m_AdNo-1 ][ Date ] = 0;
	  NAcci[ m_AdNo-1 ][ Date ] = 0;
	  NAccE[ m_AdNo-1 ][ Date ] = 0;
	  RSing[ m_AdNo-1 ][ Date ] = 0;
	}

	/* 1 */
	FullT[ m_AdNo-1 ][ Date ] += Step.GetSeconds();
	LiTi[ m_AdNo-1 ][ Date ] += Step.GetSeconds() * livefraction;

	double signal = 
	  ( Brief->h1dVtx[ LocalAdNo-1 ]->Integral( Binning::BgnBin, Binning::EndBin ) - Brief->h1dAccBkg[ LocalAdNo-1 ]->Integral( Binning::BgnBin, Binning::EndBin ) )
          * Step.GetSeconds() / fulltime;
	double sigErrSq = Brief->h1dVtx[ LocalAdNo-1 ]->Integral( Binning::BgnBin, Binning::EndBin );
	

	double background = 
	  ( FastNSpec[ set ][ m_AdNo-1 ]->GetTotalEnt() + Li9Spec[ set ][ m_AdNo-1 ]->GetTotalEnt() + AmCSpec[ set ][ m_AdNo-1 ]->GetTotalEnt() )
          / gAnalyzeData->Livetime( set, m_AdNo )
          * Step.GetSeconds() * livefraction;
	double bkgErrSq = 
	  pow ( FastNSpec[ set ][ m_AdNo-1 ]->GetTotalErr() / gAnalyzeData->Livetime( set, m_AdNo ) * Step.GetSeconds() * livefraction , 2) +
	  pow ( Li9Spec[ set ][ m_AdNo-1 ]->GetTotalErr() / gAnalyzeData->Livetime( set, m_AdNo ) * Step.GetSeconds() * livefraction , 2) +
	  pow ( AmCSpec[ set ][ m_AdNo-1 ]->GetTotalErr() / gAnalyzeData->Livetime( set, m_AdNo ) * Step.GetSeconds() * livefraction , 2);
	  
	NIBD[ m_AdNo-1 ][ Date ] += signal;
	NIBD[ m_AdNo-1 ][ Date ] -= background;
	//cout<<signal<<" "<<background<<endl;

	ErSq[ m_AdNo-1 ][ Date ] += sigErrSq + bkgErrSq;

	NMuon[ m_AdNo-1 ][ Date ] += 
	  Brief->NNet[ LocalAdNo-1 ] 
	  * Step.GetSeconds()/fulltime;

	MErSq[ m_AdNo-1 ][ Date ] += NMuon[ m_AdNo-1 ][ Date ];
	
	OstTi[ m_AdNo-1 ][ Date ] += 
	  Brief->OstwEff[ LocalAdNo-1 ] 
	  * Step.GetSeconds() 
	  * livefraction;

	NAcci[ m_AdNo-1 ][ Date ] += 
	  Brief->h1dAccBkg[ LocalAdNo-1 ]->Integral( Binning::BgnBin, Binning::EndBin )
	  * Step.GetSeconds()/fulltime;

	RSing[ m_AdNo-1 ][ Date ] =
	  Brief->Rs[ LocalAdNo-1 ];
	//* Step.GetSeconds()
	//* livefraction;;
	
        /* After all calculation, calculate the addtion for Time */
        Time.Add( Step );
      }
    }
  }

  /*
  for( unsigned int m_AdNo=1; m_AdNo<=Basic::NoAd; m_AdNo++ ) {
    cout<<m_AdNo<<"\n"<<endl;
    for( map< TimeStamp, double >::iterator itr = NIBD[ m_AdNo-1 ].begin();
	 itr != NIBD8[ m_AdNo-1 ].end(); itr++ ) {
      TimeStamp Date = itr->first;
      cout<< Date <<"\t"<< NIBD8[ m_AdNo-1 ][ Date ] <<" +/- "<< sqrt(ErSq8[ m_AdNo-1 ][ Date ]) <<endl;
    }
  }
  */

  /* Count per site per day */
  map< TimeStamp, double /*LiTi*/ > LiTSi[ 3 ];
  map< TimeStamp, double /*NIBD*/ > NSite[ 3 ];
  map< TimeStamp, double /*Errr*/ > ESiSq[ 3 ];
  

  for( unsigned int site=1; site<=3; site++ ) {
    int Ad = 1;
    int gblAd = GlobalAdIdx( site, Ad );

    for( map< TimeStamp, double >::iterator itr = NIBD[ gblAd-1 ].begin();
         itr != NIBD[ gblAd-1 ].end(); itr++ ) {
      TimeStamp Date = itr->first;

      switch (site) {
      case 1:
	LiTSi[ site-1 ][ Date ] = LiTi[ 0 ][ Date ] + LiTi[ 1 ][ Date ];
	NSite[ site-1 ][ Date ] = NIBD[ 0 ][ Date ] + NIBD[ 1 ][ Date ];
	ESiSq[ site-1 ][ Date ] = ErSq[ 0 ][ Date ] + ErSq[ 1 ][ Date ];
	break;
      case 2:
	LiTSi[ site-1 ][ Date ] = LiTi[ 2 ][ Date ];
	NSite[ site-1 ][ Date ] = NIBD[ 2 ][ Date ];
        ESiSq[ site-1 ][ Date ] = ErSq[ 2 ][ Date ];
	break;
      case 3:
	LiTSi[ site-1 ][ Date ] = LiTi[ 3 ][ Date ] + LiTi[ 4 ][ Date ] + LiTi[ 5 ][ Date ];
	NSite[ site-1 ][ Date ] = NIBD[ 3 ][ Date ] + NIBD[ 4 ][ Date ] + NIBD[ 5 ][ Date ];
        ESiSq[ site-1 ][ Date ] = ErSq[ 3 ][ Date ] + ErSq[ 4 ][ Date ] + ErSq[ 5 ][ Date ];
	break;
      default:
	break;
      }
    }
  }


  /// N IBD per day per site 
  for( int site = 1; site<=3; site++ ) {
    int nday = NSite[ site-1 ].size();
    
    double date[ nday ];
    double edate[ nday ];
    double n[ nday ];
    double err[ nday ];
    
    int d = 0;

    for( map< TimeStamp, double >::iterator itr = NSite[ site-1 ].begin();
         itr != NSite[ site-1 ].end(); itr++ ) {
      TimeStamp Date = itr->first;
      
      /// Remove one extra low statistic point
      if( sqrt( ESiSq[ site-1 ][ Date ] ) / LiTSi[ site-1 ][ Date ] * (24*60*60) < 100 ) {
	date[d]  = Date.GetSec();
	edate[d] = 0;
	n[d]     = NSite[ site-1 ][ Date ] / LiTSi[ site-1 ][ Date ] * (24*60*60);
	err[d]   = sqrt( ESiSq[ site-1 ][ Date ] ) / LiTSi[ site-1 ][ Date ] * (24*60*60);

	d++;
      }
    }
    TGraphErrors* grer = new TGraphErrors( d, date, n, edate, err );
    string Name = "REvt"+i2a( site )+"_"+i2a( set );
    string Title = "Event rate for EH" + i2a( site )+"_"+i2a( set );
    grer->SetName( Name.c_str() );
    grer->SetTitle( Title.c_str() );
    grer->Write();
  }

  /// Muon Rate daily plots
  /// Mu veto efficiency per day
  /// Ostw efficiency per day
  /// Number of accidental background per day
  /// Number of IBD per day
  /// Rate of IBD per day
  for( unsigned int m_AdNo=1; m_AdNo<=Basic::NoAd; m_AdNo++ ) {
    //cout<<endl;
    //cout<<"Ad "<<m_AdNo<<endl;

    int NDays = NMuon[ m_AdNo-1 ].size();

    double Date   [ NDays ];
    double DateE  [ NDays ];
    double Rate   [ NDays ];
    double RateE  [ NDays ];
    double MuEff  [ NDays ];
    double MuEffE [ NDays ];
    double OstwEf [ NDays ];
    double OstwEr [ NDays ];
    double RAcc   [ NDays ];
    double RAccE  [ NDays ];
    double RSings [ NDays ];
    double RSingsE[ NDays ];
    double NInvBD [ NDays ];
    double EInvBD [ NDays ];
    double RIBD   [ NDays ];
    double ERIBD  [ NDays ];
    
    int r = 0;

    for( map< TimeStamp, double >::iterator itr = NMuon[ m_AdNo-1 ].begin();
         itr != NMuon[ m_AdNo-1 ].end(); itr++ ) {

      TimeStamp Time = itr->first;
      Date[ r ]  = Time.GetSec();
      DateE[ r ] = 0;
      Rate[ r ]  = NMuon[ m_AdNo-1 ][ Time ] / LiTi [ m_AdNo-1 ][ Time ];
      RateE[ r ] = sqrt( NMuon[ m_AdNo-1 ][ Time ] ) / LiTi [ m_AdNo-1 ][ Time ];
      if( RateE[r]>1 ) RateE[ r ] = 0;
      //cout<<"Time "<<Time<<"\t"<<Rate[ r ]<<" +/- "<<RateE[ r ]<<endl;
      MuEff[ r ] = LiTi[ m_AdNo-1 ][ Time ] / FullT[ m_AdNo-1 ][ Time ];
      MuEffE[ r ]= 0;
      
      OstwEf[ r ]= OstTi[ m_AdNo-1 ][ Time ] / LiTi [ m_AdNo-1 ][ Time ];
      OstwEr[ r ]= 0;

      RAcc[ r ]  = NAcci[ m_AdNo-1 ][ Time ] / LiTi [ m_AdNo-1 ][ Time ] * (24*60*60);
      RAccE[ r ] = 0;

      RSings[ r ]= RSing[ m_AdNo-1 ][ Time ];// / LiTi [ m_AdNo-1 ][ Time ];
      RSingsE[ r]=0;

      NInvBD[ r ]= NIBD[ m_AdNo-1 ][ Time ];
      EInvBD[ r ]= sqrt( ErSq[ m_AdNo-1 ][ Time ] );

      RIBD[ r ]  = NIBD[ m_AdNo-1 ][ Time ] / LiTi [ m_AdNo-1 ][ Time ] * (24*60*60);
      //cout<<set<<" "<<m_AdNo<<" "<<Time<<" "<<NIBD[ m_AdNo-1 ][ Time ]<<" "<<LiTi [ m_AdNo-1 ][ Time ]/24/60/60<<endl;
      ERIBD[ r ] = sqrt( ErSq[ m_AdNo-1 ][ Time ] ) / LiTi [ m_AdNo-1 ][ Time ] * (24*60*60);

      r++;
    }
    
    {
      TGraphErrors* grer = new TGraphErrors( NDays, Date, Rate, DateE, RateE );
      string Name = "RMuon"+i2a( m_AdNo )+"_"+i2a( set );
      string Title = "Muon rate for AD" + i2a( m_AdNo );
      grer->SetName( Name.c_str() );
      grer->SetTitle( Title.c_str() );
      grer->Write();
    }

    {
      TGraphErrors* grer = new TGraphErrors( NDays, Date, MuEff, DateE, MuEffE );
      string Name = "MVEff"+i2a( m_AdNo )+"_"+i2a( set );
      string Title = "Muon veto efficiency for AD" + i2a( m_AdNo );
      grer->SetName( Name.c_str() );
      grer->SetTitle( Title.c_str() );
      grer->Write();
    }
    
    {
      TGraphErrors* grer = new TGraphErrors( NDays, Date, OstwEf, DateE, OstwEr );
      string Name = "MultiE"+i2a( m_AdNo )+"_"+i2a( set );
      string Title = "Multiplicity efficiency for AD" + i2a( m_AdNo );
      grer->SetName( Name.c_str() );
      grer->SetTitle( Title.c_str() );
      grer->Write();
    }

    {
      TGraphErrors* grer = new TGraphErrors( NDays, Date, RAcc, DateE, RAccE );
      string Name = "RAcc"+i2a( m_AdNo )+"_"+i2a( set );
      string Title = "Accidental background daily rate for AD" + i2a( m_AdNo );
      grer->SetName( Name.c_str() );
      grer->SetTitle( Title.c_str() );
      grer->Write();
    }

    {
      TGraphErrors* grer = new TGraphErrors( NDays, Date, RSings, DateE, RSingsE );
      string Name = "RSings"+i2a( m_AdNo )+"_"+i2a( set );
      string Title = "Single's rate for AD" + i2a( m_AdNo );
      grer->SetName( Name.c_str() );
      grer->SetTitle( Title.c_str() );
      grer->Write();
    }
    
    {
      TGraphErrors* grer = new TGraphErrors( NDays, Date, NInvBD, DateE, EInvBD );
      string Name = "NIBD"+i2a( m_AdNo )+"_"+i2a( set );
      string Title = "Number of IBD per day for AD" + i2a( m_AdNo );
      grer->SetName( Name.c_str() );
      grer->SetTitle( Title.c_str() );
      grer->Write();
    }

    {
      TGraphErrors* grer = new TGraphErrors( NDays, Date, RIBD, DateE, ERIBD );
      string Name = "RIBD"+i2a( m_AdNo )+"_"+i2a( set );
      string Title = "Rate of IBD per day for AD" + i2a( m_AdNo );
      grer->SetName( Name.c_str() );
      grer->SetTitle( Title.c_str() );
      grer->Write();
    }

  }
  }
}

