//
//  From SubEvt to Event
//
//  Zhe Wang, Nov. 2011
//
//  Dec. 26, 2011: A major upgrade to seperate each individule AD stream.
//                 They won't be mixed and won't introduce ambiguous cross references.
//
//
#include <string>
#include <vector>
#include "Event.h"
#include "EventTree.h"
#include "SubEvtReader.h"
#include "Common/Cuts.h"
#include <map>
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include "TimeStamp.h"

using namespace std;

SubEvtReader* SEReader;
EventTree*    aEventTree;
int           Fold;
Cuts          cuts;

/* For SubEvent searching loop */
int CurrEventAd;
int CurrSingleDet;
TimeStamp CurrSubEvtTime;

/* Running status */
namespace RunStatus {
  enum RunStatus_t  { waiting, inEvent };
}

map<int /* AD No. */, RunStatus::RunStatus_t /* Running Status */>  RunStatusDict;
map<int /* AD No. */, Event /* Event under construction */> EventDict;

int BeginEvent( int AdNo );
int AppendSubEvt( int AdNo );
int NormalEndEvent( int AdNo );
int AbruptStopEvent( int AdNo );

/* For run control */
int CurrRun;
TimeStamp RunStartTime;
TimeStamp PrevSubEvtTime;
TimeStamp PrevMuonTime;
TimeStamp RunEndTime;
TimeStamp FullTime;
TimeStamp LiveTime;

TimeStamp MuonShadowTime; /* Total dead time introduced by muon */
int MuonCounter;          /* Number of muons in each run */
map<int /* AD No. */, int > SinglesUpCounter;  /* Singles Counter, upper limit */
map<int /* AD No. */, int > SinglesLowCounter; /* Singles Counter, lower limit */

map< int /* RunNumber */, double /* FullTime */ > FullTimes;
map< int /* RunNumber */, double /* LiveTime */ > LiveTimes;
map< int /* RunNumber */, int /* MuonCounter */ > MuonCounters;
map< int /* RunNumber */, map<int /* AD No. */, int > /* NSinglesUp */  > NSinglesUp;
map< int /* RunNumber */, map<int /* AD No. */, int > /* NSinglesLow */ > NSinglesLow;

int BeginRun();
int EndRun();

/* For job control */
int BeginJob();
int EndJob();

int main(int argc, char** argv)
{
  string inputfilelist;
  string filenameext = ".TWin.root";
  string outputfilebase;
  string outputfile;

  TChain *SubEvt = new TChain("SubEvt");

  if( argc != 3 ) {
    cout<<"Usage:"<<endl;
    cout<<"    TWin inputfiles.list output/path/namebase"<<endl;
    cout<<endl;
    return 1;
  } else {
    inputfilelist = argv[1];
    outputfilebase = argv[2];

    /// The input file parsing
    ifstream inlist( inputfilelist.c_str() );
    string line;
    while( getline( inlist, line ) )  {
      SubEvt->Add( line.c_str() );
    }

    /// The output file
    outputfile = outputfilebase + filenameext;
  }

  /// Do the work 
  /// ###########
  // Load the SubEvt Tree
  // This should a TChain
  // Get the SubEvt Tree reader
  SEReader = new SubEvtReader;
  SEReader->Init(SubEvt);
  // Prepare the output tree
  aEventTree = new EventTree("Event",outputfile.c_str(),0);

  /// Prepare to Start
  BeginJob();

  /// The main loop
  /// #############
  unsigned int entries = SubEvt->GetEntries();
  for( unsigned int entry=0; entry<entries; entry++ )  {
    int ret = SEReader->GetEntry( entry );
    if( ret==0 ) {
      cout<<"Warning: Read error"<<endl;
    }

    if( SEReader->Run != CurrRun )  {
      if( CurrRun != 0 ) {
	EndRun();
      }
      BeginRun();
    }
    
    /* A few key variables */
    CurrSubEvtTime = TimeStamp(SEReader->SubEvtSec, SEReader->SubEvtNano);
    bool GoodSingleAdSubEvt = false;
    TimeStamp T2PrevMuon;
    if( PrevMuonTime == TimeStamp::GetBOT() )  {
      T2PrevMuon == TimeStamp(0,0);
    } else {
      T2PrevMuon = CurrSubEvtTime - PrevMuonTime;
    }

    CurrSingleDet = 0;
    if( SEReader->NDet == 1 ) {
      for( unsigned int i=0; i<7; i++ )  {
	if( SEReader->Valid[i] ) {
	  CurrSingleDet = SEReader->Det[i];
	}
      }
    }

    if( SEReader->MuonProb < 0.5 &&
	/// SEReader->RetrigProb < 0.5 &&   /// This turns out to be not very useful
	SEReader->NDet == 1 &&
	CurrSingleDet <= 4 &&
	T2PrevMuon.GetSeconds() > cuts.SpallDt/second )  {
      GoodSingleAdSubEvt = true;
    }

    /* For non-muon-event, if it is a single AD sub event */
    /* Need to filter out non-physical events. They should not go into the searching queue. */
    if( SEReader->MuonProb < 0.5 ) {
      if( GoodSingleAdSubEvt ) {
	
	/* Skip flashers */
	double Quadrant = SEReader->Quadrant[ CurrSingleDet - 1 ];
	double QMax2Sum = SEReader->QMax2Sum[ CurrSingleDet - 1 ];
	double ellipse = sqrt(
			      (Quadrant)*(Quadrant) +
			      (QMax2Sum)/0.45*(QMax2Sum)/0.45
			      );
	if( ellipse>1 ) goto EndEachSubEvent;
      
	/* Remove low and high energy events */
	if( SEReader->E[ CurrSingleDet - 1 ] < cuts.QSumLow/MeV  ) {
	  goto EndEachSubEvent;
	}
      }
    }

    /// Each AD has its own queue
    for( int AdNo = 1; AdNo <= 4; AdNo++ )   {
      RunStatus::RunStatus_t & ThisAdStatus = RunStatusDict[ AdNo ];
      Event                    ThisAdEvent = EventDict[ AdNo ];
      TimeStamp                ThisAdEventTime( ThisAdEvent.TimeSec, 
						ThisAdEvent.TimeNano );

      TimeStamp T2FirstSubEvt = CurrSubEvtTime - ThisAdEventTime;
      bool SameAd = (CurrSingleDet == AdNo);

      /* How to normally end an event */
      /*##############################*/
      if( ThisAdStatus == RunStatus::inEvent &&
	  T2FirstSubEvt.GetSeconds() > cuts.CoinDt/second )   {
	ThisAdStatus = RunStatus::waiting;
	NormalEndEvent( AdNo );
      }
      
      /* How to abruptly stop an event */
      /*###############################*/
      if( ThisAdStatus == RunStatus::inEvent &&
	  T2FirstSubEvt.GetSeconds() < cuts.CoinDt/second &&
	  !GoodSingleAdSubEvt )   {
	ThisAdStatus = RunStatus::waiting;
	AbruptStopEvent( AdNo );
      }

      /* How to append a sub-event */
      /*###########################*/
      if( ThisAdStatus == RunStatus::inEvent &&
	  SameAd &&
          T2FirstSubEvt.GetSeconds() < cuts.CoinDt/second &&
          GoodSingleAdSubEvt )   {
	AppendSubEvt( AdNo );
      }
	
      /* How to begin an event */
      /*#######################*/
      if( ThisAdStatus == RunStatus::waiting &&
	  SameAd &&
	  GoodSingleAdSubEvt )   {
	ThisAdStatus = RunStatus::inEvent;
	CurrEventAd = CurrSingleDet;
	BeginEvent( AdNo );
	AppendSubEvt( AdNo );
      }
    }
    
  EndEachSubEvent:
    /* Live time calculation */
    if( SEReader->MuonProb > 0.5 )  {
      MuonCounter += 1;

      double shadowTime = (cuts.SpallDt + cuts.CoinDt)/second ;
      double T2PrevMuon = (CurrSubEvtTime - PrevMuonTime).GetSeconds();
      if( T2PrevMuon < (cuts.SpallDt + cuts.CoinDt)/second )  {
	shadowTime = T2PrevMuon;
      }
      MuonShadowTime.Add( shadowTime );
      
      PrevMuonTime = TimeStamp( SEReader->SubEvtSec, SEReader->SubEvtNano );
    }
    PrevSubEvtTime = TimeStamp( SEReader->SubEvtSec, SEReader->SubEvtNano );
    continue;
  }

  AbruptStopEvent( 1 );
  AbruptStopEvent( 2 );
  AbruptStopEvent( 3 );
  AbruptStopEvent( 4 );
  EndRun();
  
  aEventTree->Close();
  EndJob();

  return 1;
}

int BeginEvent( int AdNo )
{
  Event& aNewEvent = EventDict[ AdNo ];
  aNewEvent.Reset();

  aNewEvent.Fold = 0;
  
  aNewEvent.Run        = SEReader->Run;
  aNewEvent.TimeSec    = SEReader->SubEvtSec;
  aNewEvent.TimeNano   = SEReader->SubEvtNano;
  aNewEvent.Det        = AdNo;

  aNewEvent.T2PrevMuon = SEReader->T2PrevMuon;

  return 1;
}

int AppendSubEvt( int AdNo )
{
  Event& CurrEvent = EventDict[ AdNo ];
  CurrEvent.Fold += 1;
  int FoldIdx = CurrEvent.Fold - 1;
  
  CurrEvent.TrigType[ FoldIdx ]    = SEReader->TrigType[ AdNo-1 ]; 
  CurrEvent.TrigSec[ FoldIdx ]     = SEReader->TrigSec[ AdNo-1 ];
  CurrEvent.TrigNano[ FoldIdx ]    = SEReader->TrigNano[ AdNo-1 ];

  double X,Y,Z;
  
  X  = SEReader->X[ AdNo-1 ];
  Y  = SEReader->Y[ AdNo-1 ];
  Z  = SEReader->Z[ AdNo-1 ];

  CurrEvent.E[ FoldIdx ]   = SEReader->E[ AdNo-1 ];
  CurrEvent.X[ FoldIdx ]   = X;
  CurrEvent.Y[ FoldIdx ]   = Y;
  CurrEvent.Z[ FoldIdx ]   = Z;

  if( FoldIdx==0 ) {
    CurrEvent.D2First[ FoldIdx ] = 0;
  } else {
    double X1,Y1,Z1;
    X1  = CurrEvent.X[ 0 ];
    Y1  = CurrEvent.Y[ 0 ];
    Z1  = CurrEvent.Z[ 0 ];

    CurrEvent.D2First[ FoldIdx ]  = sqrt( (X-X1)*(X-X1) + (Y-Y1)*(Y-Y1) + (Z-Z1)*(Z-Z1) );
  }

  CurrEvent.T2PrevSubEvt[ FoldIdx ] = SEReader->T2PrevSubEvt;

  return 1;
}

int NormalEndEvent( int AdNo )
{
  Event& CurrEvent = EventDict[ AdNo ];

  aEventTree->Run        = CurrEvent.Run;
  aEventTree->Event      = CurrEvent.EventNo;
  aEventTree->TimeSec    = CurrEvent.TimeSec;
  aEventTree->TimeNano   = CurrEvent.TimeNano;
  aEventTree->Det        = CurrEvent.Det;
  
  aEventTree->T2PrevMuon = CurrEvent.T2PrevMuon;
  aEventTree->EPrevMuon  = CurrEvent.EPrevMuon;
  aEventTree->D2PrevMuon = CurrEvent.D2PrevMuon;

  aEventTree->Fold       = CurrEvent.Fold;
  
  for( int FoldIdx = 0; FoldIdx < CurrEvent.Fold; FoldIdx++ )   {
    aEventTree->TrigType[FoldIdx]     = CurrEvent.TrigType[FoldIdx];
    aEventTree->TrigSec[FoldIdx]      = CurrEvent.TrigSec[FoldIdx];
    aEventTree->TrigNano[FoldIdx]     = CurrEvent.TrigNano[FoldIdx];
    aEventTree->E[FoldIdx]            = CurrEvent.E[FoldIdx];
    aEventTree->X[FoldIdx]            = CurrEvent.X[FoldIdx];
    aEventTree->Y[FoldIdx]            = CurrEvent.Y[FoldIdx];
    aEventTree->Z[FoldIdx]            = CurrEvent.Z[FoldIdx];
    aEventTree->D2First[FoldIdx]      = CurrEvent.D2First[FoldIdx];
    aEventTree->T2PrevSubEvt[FoldIdx] = CurrEvent.T2PrevSubEvt[FoldIdx];
  }
  
  aEventTree->Fill();

  /// End of event statistics
  /// NSingles upper limit
  SinglesUpCounter[ AdNo ] += CurrEvent.Fold;
  /// NSingles lower limit
  if( CurrEvent.Fold == 1 )  {
    SinglesLowCounter[ AdNo ] += 1;
  } 
  if( CurrEvent.Fold == 2 && 
      CurrEvent.D2First[1] > cuts.D2First/mm )  {
    SinglesLowCounter[ AdNo ] += 2;
  }

  CurrEvent.Reset();

  return 1;
}

int AbruptStopEvent( int AdNo )
{
  Event& CurrEvent = EventDict[ AdNo ];
  CurrEvent.Reset();
  return 1;
}

int BeginRun()
{
  CurrRun = SEReader->Run;
  RunStartTime = TimeStamp( SEReader->SubEvtSec, SEReader->SubEvtNano );
  
  MuonShadowTime = 0;
  MuonCounter = 0;

  for( int det = 1; det <= 4; det++ )   {
    /// Reset singles counters
    SinglesUpCounter[ det ] = 0;
    SinglesLowCounter[ det ] = 0;
    
    /// Reset the run status
    RunStatusDict[ det ] = RunStatus::waiting;
  }

  return 1;
}

int EndRun()
{
  RunEndTime = PrevSubEvtTime;
  FullTimes[ CurrRun ] = (RunEndTime - RunStartTime).GetSeconds();
  LiveTimes[ CurrRun ] = FullTimes[ CurrRun ] - MuonShadowTime.GetSeconds();
  MuonCounters[ CurrRun ] = MuonCounter;
  
  for( int det = 1; det <= 4; det++ )   {
    NSinglesUp[ CurrRun ][ det ]  = SinglesUpCounter[ det ];
    NSinglesLow[ CurrRun ][ det ] = SinglesLowCounter[ det ];
  }


  return 1;
}

int BeginJob()
{
  cout<<"Begin Job"<<endl;
  CurrEventAd = 0;
  CurrSingleDet = 0;
  CurrRun = 0;

  CurrSubEvtTime = TimeStamp::GetBOT();
  RunStartTime = TimeStamp::GetBOT();
  PrevSubEvtTime = TimeStamp::GetBOT();
  PrevMuonTime = TimeStamp::GetBOT();
  RunEndTime = TimeStamp::GetBOT();
  FullTime = TimeStamp::GetBOT();
  LiveTime = TimeStamp::GetBOT();

  return 1;
}

int EndJob()
{
  cout<<"End Job"<<endl;
  map< int /* RunNumber */, double /* FullTime */ >::iterator it, it_end = FullTimes.end();

  string filename = "../DataBase/RunInfo.txt";
  FILE* m_outfile = fopen(filename.c_str(), "a");
  
  // This is only useful for the first time.
  //fprintf(m_outfile, "# [Run] [FullTime] [LiveTime]   [NMuon]  [NSgls1Up] [NSgls1Low] [NSgls2Up] [NSgls2Low] [NSgls3Up] [NSgls3Low] [NSgls4Up] [NSgls4Low]\n");
  for( it = FullTimes.begin(); it!= it_end; it++ )  {
    int run = (it->first);
    fprintf(m_outfile, "%10d %8.3f %8.3f %10d %10d %10d %10d %10d %10d %10d %10d %10d \n",
    	    run, FullTimes[run], LiveTimes[run], MuonCounters[run],
    	    NSinglesUp[run][1], NSinglesLow[run][1], NSinglesUp[run][2], NSinglesLow[run][2],
    	    NSinglesUp[run][3], NSinglesLow[run][3], NSinglesUp[run][4], NSinglesLow[run][4]
    	    );
  }
  
  fclose(m_outfile);

  return 1;
}
