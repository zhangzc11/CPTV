//
//  From SubEvt to Event
//
//  Zhe Wang, Nov. 2011
//
//  Dec. 26, 2011: A major upgrade to seperate each individule AD stream.
//                 They won't be mixed and won't introduce ambiguous cross references.
//
//
#include "Globals.h"

using namespace std;

extern Cuts*          AllCut;

/* Muon information */
extern TimeStamp LastMuonT      ;
extern map<int /* AD No. */, TimeStamp /* last pool muon time */  > LastPoolMuonT;
extern map<int /* AD No. */, TimeStamp /* last AD muon time */    > LastAdMuonT;
extern map<int /* AD No. */, TimeStamp /* last shower muon time */> LastShowerMuonT;

/* The definition of NetMuonT is the end of the previous muon veto window, which is different from the rest. */
extern map<int /* AD No. */, TimeStamp /* last net muon time */   > LastNetMuonT;

extern map<int /* AD No. */, TimeStamp /* veto all SubEvt till */ > MuonVetoTime;
extern map<int /* AD No. */, MuonId::MuonId_t /* Last Muon Id  */ > MuonVetoId;

/* The core of the second loop of the code */
extern map<int /* AD No. */, RunStatus::RunStatus_t /* Running Status */> RunStatusDict;
extern map<int /* AD No. */, Event /* Event under construction */       > EventDict;

extern map<int /* AD No. */, TimeStamp /* time of last subevt */ > LastSubEvtT;

extern EventTree*    aEventTree;

extern double  CTimeAviPl [4][timebins];
extern double  CSingleUpPl[4][timebins];
extern double  CSingleLwPl[4][timebins];
extern double  CRatePl    [4][timebins];
       
extern double  CTimeAviAd [4][timebins];
extern double  CSingleUpAd[4][timebins];
extern double  CSingleLwAd[4][timebins];
extern double  CRateAd    [4][timebins];
       
extern double  CTimeAviSh [4][timebins];
extern double  CSingleUpSh[4][timebins];
extern double  CSingleLwSh[4][timebins];
extern double  CRateSh    [4][timebins];
       
extern double  CTimeAvi   [4][timebins];
extern double  CSingleUp  [4][timebins];
extern double  CSingleLw  [4][timebins];
extern double  CRate      [4][timebins];

extern RunInfo CurrRun;

/* BuildEvent will call the following four functions */
int BeginEvent     ( int AdNo, SubEvt* pSubEvt );
int AppendSubEvt   ( int AdNo, SubEvt* pSubEvt );
int NormalEndEvent ( int AdNo, SubEvt* pSubEvt );
int AbruptStopEvent( int AdNo, SubEvt* pSubEvt );

int BuildEvent( SubEvt* pSubEvt )
{
  TimeStamp ThisSubEvtTime( pSubEvt->TrigSec, pSubEvt->TrigNano );
  int       ThisSubEvtDet = pSubEvt->Det;

  /* The three essential conditions */
  bool MuonEvt    = false;
  bool AdSubEvt   = false;
  bool GoodAdSubEvt  = false;  /* Important */
  bool Non8InchFlasher = false;
  bool Non2InchFlasher = false;
  bool NonLowE    = false;
  bool NonMuonVeto= false;

  /* Muon Event */
  for( int det=1; det<=4; det++ ) {
    if( pSubEvt->MuonStat[det] != MuonId::NonMuon )  MuonEvt = true;
  }

  /* Good AD sub-event with further judgement.*/
  if( !MuonEvt )  {
    /* AD SubEvt */
    if( ThisSubEvtDet <= 4 && ThisSubEvtDet >= 1 ) AdSubEvt = true;

    /* Flasher Id */
    double Quadrant = pSubEvt->Quadrant;
    double QMax2Sum = pSubEvt->QMax2Sum;
    double ellipse = sqrt(
			  (Quadrant)*(Quadrant) +
			  (QMax2Sum)/0.45*(QMax2Sum)/0.45
			  );
    if( ellipse<1 ) Non8InchFlasher = true;

    if( pSubEvt->MaxQ2Inch < 100 ) Non2InchFlasher = true;
    
    /* Energy too low */
    if( pSubEvt->E > AllCut->QSumLow/MeV  ) NonLowE = true;

    /* In muon veto */
    if( ThisSubEvtTime > MuonVetoTime[ ThisSubEvtDet ] ) NonMuonVeto = true;

    /* Clean up the queue */
    if( AdSubEvt && Non8InchFlasher && Non2InchFlasher && NonLowE && NonMuonVeto )  GoodAdSubEvt = true;
  }

  /* What's left over is a muon or a good Ad SubEvt */
  /* Build up correlation. Each AD has its own queue. */
  if( MuonEvt || GoodAdSubEvt ) {
    for( int AdNo = 1; AdNo <= 4; AdNo++ )   {
      
      RunStatus::RunStatus_t & ThisAdStatus = RunStatusDict[ AdNo ];
      Event                    ThisAdEvent  = EventDict[ AdNo ];
      TimeStamp                ThisAdEventTime( ThisAdEvent.TrigSec[0],
						ThisAdEvent.TrigNano[0] );
      
      TimeStamp T2FirstSubEvt = ThisSubEvtTime - ThisAdEventTime;
      bool SameAd = (ThisSubEvtDet == AdNo);
      
      /* How to normally end an event */
      /*##############################*/
      if( ThisAdStatus == RunStatus::inEvent &&
	  T2FirstSubEvt.GetSeconds() > AllCut->CoinDt/second )   {
	ThisAdStatus = RunStatus::waiting;
	NormalEndEvent( AdNo, pSubEvt );

	/// Here is the trick.
	/// Update singles rate information for this run.
	Event& CurrEvent = EventDict[ AdNo ];
	/// If muon ends this event, then there is a chance that the later subevts are not in livetime window.
	if( MuonEvt )  {
	  /// Upper limit
	  for( int FoldIdx = 0; FoldIdx < CurrEvent.Fold; FoldIdx++ )   {	    
	    /// Upper limit
	    TimeStamp SubEvtTime( CurrEvent.TrigSec[FoldIdx], CurrEvent.TrigNano[FoldIdx] );
	    TimeStamp NewVetoBegin = ThisSubEvtTime;
	    NewVetoBegin.Subtract( AllCut->CoinDt/second );
	    if( SubEvtTime < NewVetoBegin ) {
	      /// Upper limit
	      CurrRun.NSingleUp[ AdNo ] ++;
	      /// Lower limit
	      if( CurrEvent.Fold == 1 && FoldIdx == 0 ) {
		CurrRun.NSingleLow[ AdNo ] += 1;
	      }
	      if( CurrEvent.Fold == 2 && FoldIdx == 1 ) {
		if( CurrEvent.D2First[1] > AllCut->D2First/mm ) {
		  CurrRun.NSingleLow[ AdNo ] += 2;
		}
	      }
	    }
	  }
	}
	/// If ended by AD subevts, nothing to worry.
	else {
	  for( int FoldIdx = 0; FoldIdx < CurrEvent.Fold; FoldIdx++ )   {
	    TimeStamp SubEvtTime( CurrEvent.TrigSec[FoldIdx], CurrEvent.TrigNano[FoldIdx] );
	    /// Upper limit
	    CurrRun.NSingleUp[ AdNo ] ++;
	    /// Lower limit
	    if( CurrEvent.Fold == 1 && FoldIdx == 0 ) {
	      CurrRun.NSingleLow[ AdNo ] += 1;
	    }
	    if( CurrEvent.Fold == 2 && FoldIdx == 1 ) {
	      if( CurrEvent.D2First[1] > AllCut->D2First/mm ) {
		CurrRun.NSingleLow[ AdNo ] += 2;
	      }
	    }
	  }
	}
      }
      /* How to abruptly stop an event */
      /*###############################*/
      if( ThisAdStatus == RunStatus::inEvent &&
	  T2FirstSubEvt.GetSeconds() < AllCut->CoinDt/second &&
	  MuonEvt )   {
	ThisAdStatus = RunStatus::waiting;
	AbruptStopEvent( AdNo, pSubEvt );
	/// In Nov. 2012, retriggers in water shield were found to 
	/// cause some unexpected acceptance loss by these print-out.
	/// /TWin/Ostw/aileron/TreeTxt.py is the one used to generate root txt-based tree.
	/*
	if( ThisAdEvent.Fold == 2 ) { 
	  cout<<ThisAdEvent.TrigNum[0]
	      <<"\t"<<ThisAdEvent.TrigNum[1]
	      <<"\t"<<ThisAdEvent.E[0]
	      <<"\t"<<ThisAdEvent.E[1]
	      <<"\t"<<T2FirstSubEvt.GetSeconds()
	      <<"\t"<<T2FirstSubEvt.GetSeconds()-ThisAdEvent.T2PrevSubEvt[1]
	      <<"\t"<<pSubEvt->Det
	      <<"\t"<<pSubEvt->NPmt
	      <<endl;	  
	}
	*/
      }
      
      /* How to append a sub-event */
      /*###########################*/
      if( ThisAdStatus == RunStatus::inEvent &&
	  SameAd &&
	  T2FirstSubEvt.GetSeconds() < AllCut->CoinDt/second &&
	  !MuonEvt )   {
	AppendSubEvt( AdNo, pSubEvt );
      }
      
      /* How to begin an event */
      /*#######################*/
      if( ThisAdStatus == RunStatus::waiting &&
	  SameAd &&
	  !MuonEvt )   {
	ThisAdStatus = RunStatus::inEvent;
	BeginEvent( AdNo, pSubEvt );
	AppendSubEvt( AdNo, pSubEvt );
      }
    }
  }

  /* Muon Counters and extend muon veto times for each AD. */
  if( MuonEvt )   {
    CurrRun.NMuon += 1;
    LastMuonT = ThisSubEvtTime;

    for( int det=1; det<=4; det++ ) {
      TimeStamp coinT,thisVeto;

      double VetoAddition = 0;

      /* Pool muon */
      if( pSubEvt->MuonStat[det] == MuonId::PlMuon )  {
	/* Counter */
	CurrRun.NPlMuon[det] += 1;
	/* Veto time */
	VetoAddition = AllCut->PlMuVeto/second;
	/* Last muon time */
	LastPoolMuonT[det] = ThisSubEvtTime;	
      }

      /* Ad muon */
      if( pSubEvt->MuonStat[det] == MuonId::AdMuon )  {
	/* Counter */
	CurrRun.NAdMuon[det] += 1;
	/* Veto time */
	VetoAddition = AllCut->AdMuVeto/second;
	/* Last muon time */
	LastAdMuonT[det] = ThisSubEvtTime;
      }

      /* Shower muon */
      if( pSubEvt->MuonStat[det] == MuonId::ShMuon )  {
	/* Counter */
	CurrRun.NShMuon[det] += 1;
	/* Veto time */
	VetoAddition = AllCut->ShMuVeto/second;
	/* Last muon time */
        LastShowerMuonT[det] = ThisSubEvtTime;
      }
      
      /* Record veto record */
      /*      CoinT     Muon SubEvtTime         ThisVeto       */
      /* -------+-------------+--------------------+---------- */

      coinT = ThisSubEvtTime;
      coinT.Subtract( AllCut->CoinDt/second );

      thisVeto = ThisSubEvtTime;
      thisVeto.Add( VetoAddition );

      /// New muon time surpasses current veto time end.
      if( MuonVetoTime[det] < coinT )   {
	/* Record the available times for singles in histograms*/
	double deltaT = (coinT - MuonVetoTime[det]).GetSeconds();
	for( int bin=1; bin<=timebins; bin++ ) {
	  double UpEdge = (timeEnd-timeStart)/timebins * bin;
	  double center = (timeEnd-timeStart)/timebins * (bin-0.5);
	  if( deltaT > UpEdge ) {
	    if( MuonVetoId[det] == MuonId::PlMuon ) CTimeAviPl[det-1][bin-1] += 1;
	    if( MuonVetoId[det] == MuonId::AdMuon ) CTimeAviAd[det-1][bin-1] += 1;
	    if( MuonVetoId[det] == MuonId::ShMuon ) CTimeAviSh[det-1][bin-1] += 1;
	    CTimeAvi[det-1][bin-1] += 1;
	  }
	}
	
	/* Update each time record */
	CurrRun.VetoTime[det].Add( AllCut->CoinDt/second );
	CurrRun.VetoTime[det].Add( VetoAddition );
	MuonVetoTime[det] = thisVeto;
	MuonVetoId[det] = pSubEvt->MuonStat[det];
	/* This defines an effective muon in livetime axis */
	CurrRun.NNetMuon[det] += 1;
	LastNetMuonT[det] = MuonVetoTime[det];
      }
      /// Current muon veto time end is in between of the new muon's CoinT and ThisVeto.
      else if( ( MuonVetoTime[det] >= coinT ) &&
	       ( MuonVetoTime[det] < thisVeto ) ) {
	TimeStamp dveto = thisVeto - MuonVetoTime[det];
	CurrRun.VetoTime[det].Add( dveto );
	MuonVetoTime[det] = thisVeto;
	LastNetMuonT[det] = MuonVetoTime[det];
	MuonVetoId[det] = pSubEvt->MuonStat[det];
      }
      /// Current muon veto time is way in the furture. New short muon veto doesn't matter.
      else if( MuonVetoTime[det] > thisVeto ) {
	/* Nothing to do */
      }
      
    }
  }
  
  return 1;
}


int BeginEvent( int AdNo, SubEvt* pSubEvt )
{
  Event& aNewEvent = EventDict[ AdNo ];
  aNewEvent.Reset();

  aNewEvent.Fold = 0;
  
  aNewEvent.Run        = pSubEvt->Run;
  aNewEvent.Det        = pSubEvt->Det;

  TimeStamp CurrT = TimeStamp(pSubEvt->TrigSec,pSubEvt->TrigNano);
  aNewEvent.T2PrevMu   = (CurrT - LastMuonT).GetSeconds();
  aNewEvent.T2PrevPlMu = (CurrT - LastPoolMuonT[ AdNo ]).GetSeconds();
  aNewEvent.T2PrevAdMu = (CurrT - LastAdMuonT[ AdNo ]).GetSeconds();
  aNewEvent.T2PrevShMu = (CurrT - LastShowerMuonT[ AdNo ]).GetSeconds();
  aNewEvent.T2PrevNetMu= (CurrT - LastNetMuonT[ AdNo ]).GetSeconds();

  return 1;
}

int AppendSubEvt( int AdNo, SubEvt* pSubEvt )
{
  Event& CurrEvent = EventDict[ AdNo ];
  if( CurrEvent.Fold == MaxFold ) {
    cout<<" Warning: Fold>"<<MaxFold<<endl;
    return 1;
  }

  CurrEvent.Fold += 1;
  int FoldIdx = CurrEvent.Fold - 1;
  
  CurrEvent.TrigNum[ FoldIdx ]     = pSubEvt->TrigNum;
  CurrEvent.TrigSec[ FoldIdx ]     = pSubEvt->TrigSec;
  CurrEvent.TrigNano[ FoldIdx ]    = pSubEvt->TrigNano;

  double X,Y,Z;
  
  X  = pSubEvt->X;
  Y  = pSubEvt->Y;
  Z  = pSubEvt->Z;

  CurrEvent.E[ FoldIdx ]   = pSubEvt->E;
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
  
  CurrEvent.T2PrevSubEvt[ FoldIdx ] = ( TimeStamp(pSubEvt->TrigSec, pSubEvt->TrigNano) - LastSubEvtT[ AdNo ] ).GetSeconds();

  CurrEvent.Quadrant[ FoldIdx ] = pSubEvt->Quadrant;
  CurrEvent.QMax2Sum[ FoldIdx ] = pSubEvt->QMax2Sum;

  LastSubEvtT[ AdNo ] = TimeStamp( pSubEvt->TrigSec, pSubEvt->TrigNano );
  return 1;
}

int NormalEndEvent( int AdNo, SubEvt* pSubEvt )
{
  Event& CurrEvent = EventDict[ AdNo ];

  aEventTree->Run        = CurrEvent.Run;
  aEventTree->Det        = CurrEvent.Det;
  
  aEventTree->T2PrevMu   = CurrEvent.T2PrevMu  ;
  aEventTree->T2PrevPlMu = CurrEvent.T2PrevPlMu;
  aEventTree->T2PrevAdMu = CurrEvent.T2PrevAdMu;
  aEventTree->T2PrevShMu = CurrEvent.T2PrevShMu;
  aEventTree->T2PrevNetMu = CurrEvent.T2PrevNetMu;

  aEventTree->Fold       = CurrEvent.Fold;
  
  if( CurrEvent.Fold>20 ) cout<<"Large Fold: "<<CurrEvent.Fold<<endl;
  for( int FoldIdx = 0; FoldIdx < CurrEvent.Fold; FoldIdx++ )   {
    aEventTree->TrigNum[FoldIdx]      = CurrEvent.TrigNum[FoldIdx];
    aEventTree->TrigSec[FoldIdx]      = CurrEvent.TrigSec[FoldIdx];
    aEventTree->TrigNano[FoldIdx]     = CurrEvent.TrigNano[FoldIdx];
    aEventTree->E[FoldIdx]            = CurrEvent.E[FoldIdx];
    aEventTree->X[FoldIdx]            = CurrEvent.X[FoldIdx];
    aEventTree->Y[FoldIdx]            = CurrEvent.Y[FoldIdx];
    aEventTree->Z[FoldIdx]            = CurrEvent.Z[FoldIdx];
    aEventTree->D2First[FoldIdx]      = CurrEvent.D2First[FoldIdx];
    aEventTree->T2PrevSubEvt[FoldIdx] = CurrEvent.T2PrevSubEvt[FoldIdx];
    aEventTree->Quadrant[FoldIdx]      = CurrEvent.Quadrant[FoldIdx];
    aEventTree->QMax2Sum[FoldIdx]      = CurrEvent.QMax2Sum[FoldIdx];

    /* Fill the event time */
    TimeStamp subevttime(CurrEvent.TrigSec[FoldIdx],CurrEvent.TrigNano[FoldIdx]);
    double deltaT = (subevttime - MuonVetoTime[AdNo]).GetSeconds();
    int bin = (int)(deltaT/((timeEnd-timeStart)/timebins)) + 1;

    if( bin<=timebins && bin>=1 ) {
      if( MuonVetoId[AdNo] == MuonId::PlMuon ) CSingleUpPl[AdNo-1][bin-1] += 1;
      if( MuonVetoId[AdNo] == MuonId::AdMuon ) CSingleUpAd[AdNo-1][bin-1] += 1;
      if( MuonVetoId[AdNo] == MuonId::ShMuon ) CSingleUpSh[AdNo-1][bin-1] += 1;
      CSingleUp[AdNo-1][bin-1] += 1;
      
      if( (CurrEvent.Fold == 1) || 
	  (CurrEvent.Fold == 2 && CurrEvent.D2First[1] > AllCut->D2First/mm) ) {
	if( MuonVetoId[AdNo] == MuonId::PlMuon ) CSingleLwPl[AdNo-1][bin-1] += 1;
	if( MuonVetoId[AdNo] == MuonId::AdMuon ) CSingleLwAd[AdNo-1][bin-1] += 1;
	if( MuonVetoId[AdNo] == MuonId::ShMuon ) CSingleLwSh[AdNo-1][bin-1] += 1;
	CSingleLw[AdNo-1][bin-1] += 1;
      }
    }
  }
  
#ifdef TreeOutput 
  aEventTree->Fill();
#endif
  return 1;
}

int AbruptStopEvent( int AdNo, SubEvt* pSubEvt )
{
  /// Besides updating event building status, nothing to do.
  return 1;
}
