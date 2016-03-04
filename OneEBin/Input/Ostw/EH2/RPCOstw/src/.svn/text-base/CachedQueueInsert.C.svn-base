#include "Globals.h"

extern Cuts*       AllCut;
extern SubEvtQueue CachedQueue;

SubEvtQueue CachedQueueInsert( TimeStamp time, SubEvt* pSubEvt )
{
  SubEvtQueue PassedQueue;
  
  /*  Non-mulitiplicity trigger */
  if( (((pSubEvt->TrigType)&AllCut->MultiTrig) != AllCut->MultiTrig) &&
      (((pSubEvt->TrigType)&AllCut->ESumTrig) != AllCut->ESumTrig) )  {
    delete pSubEvt;
    return PassedQueue;
  }

  /* No SubEvt contained in current CachedQueue */
  if( CachedQueue.size() == 0 )  {
    CachedQueue.insert( pair< TimeStamp, SubEvt* >( time, pSubEvt ) );
    return PassedQueue;
  }

  /* There is at least one SubEvt in current CachedQueue */
  SubEvtQueueIterator it;
  SubEvtQueue::reverse_iterator rit = CachedQueue.rbegin();
  TimeStamp EndTime = rit->first;
  TimeStamp dt = time - EndTime;
  TimeStamp Latency( 0, int(AllCut->Latency/nanosecond) );

  /* Got a SubEvt far in the future */
  if( dt > Latency )  {
    /* Decide if the SubEvts cached are from a muon */
    /* A couple of status word for muon identification */
    bool IwsMuon   = false;
    bool OwsMuon   = false;
    int  IwsHits=0, OwsHits=0, AdHits=0;
    map<int /* AD No. */, bool /* identified */  > AdMuon;
    map<int /* AD No. */, bool /* identified */  > AdShower;
    for( int det = 1; det <= 4; det++ )   {
      AdMuon[det]   = false;
      AdShower[det] = false;
    }

    SubEvtQueueIterator it_end = CachedQueue.end();
    double MaxE = 0;

    for( it = CachedQueue.begin(); it != it_end; it++ )  {
      int Det = it->second->Det;
      /* IWS */
      if( Det == 5 ) {
        if( it->second->NPmt > AllCut->NChnlIws ) {
          IwsMuon = true;
	  IwsHits = it->second->NPmt;
        }
      }
      /* OWS */
      if( Det == 6 ) {
        if( it->second->NPmt > AllCut->NChnlOws ) {
          OwsMuon = true;
	  OwsHits = it->second->NPmt;
        }
      }
    }

    for( it = CachedQueue.begin(); it != it_end; it++ ) {
      int Det = it->second->Det;
      /* AD */
      if( Det <= 4 )  {
	/* Require a pool trigger, otherwise it is like an internal background. */
	if( IwsMuon || OwsMuon ) {
	  if( it->second->E > MaxE ) MaxE = it->second->E;
	  if( it->second->E > AllCut->QSumAD/MeV )  {
	    AdMuon[Det] = true;
	    if( it->second->NPmt > AdHits ) AdHits = it->second->NPmt;
	    if( it->second->E > AllCut->ShowerAD/MeV )  {
	      AdShower[Det] = true;
	    }
	  }
	}
      }
    }

    /* Any parts are triggered. */
    bool Muon     = AdMuon[1] || AdMuon[2] || AdMuon[3] || AdMuon[4] || IwsMuon || OwsMuon;

    if( Muon )  {
      /* Create a special muon SubEvt with mainly time and MuonProb */
      SubEvt* pMuonSE = new SubEvt;
      it = CachedQueue.begin();
      pMuonSE->TrigSec  = it->first.GetSec();
      pMuonSE->TrigNano = it->first.GetNanoSec();
      TimeStamp SubTime = it->first;

      if( OwsMuon )        {  
	pMuonSE->Det = 6; 
	pMuonSE->NPmt = OwsHits;
      }      
      else if ( IwsMuon )  {  
	pMuonSE->Det = 5; 
	pMuonSE->NPmt = IwsHits;
      }
      else                 {  
	pMuonSE->Det = 1; 
	pMuonSE->NPmt = AdHits;
      }   /// For all AD-related cases

      pMuonSE->E = MaxE;
      
      /* Very detailed muon info is passed to next stage */
      for( int det=1; det<=4; det++ ) {
	if( (!AdMuon[det]) && (!AdShower[det]) )      pMuonSE->MuonStat[det] = MuonId::PlMuon;
	if( AdMuon[det] )                             pMuonSE->MuonStat[det] = MuonId::AdMuon;
	if( AdShower[det] )                           pMuonSE->MuonStat[det] = MuonId::ShMuon;
      }

      /* Add this to the current passed queue */
      PassedQueue.insert( pair< TimeStamp, SubEvt* >( SubTime, pMuonSE ) );
     
      /* Delete them from CachedQueue */
      int counter = 0;
      for( it = CachedQueue.begin(); it != it_end; it++ ) {
	SubEvt*   pSEvt = it->second;
	delete    pSEvt;
	counter++;
      }
      CachedQueue.clear();
      
    } else {
      
      /* move SubEvt from CachedQueue to PassedQueue */
      it_end = CachedQueue.end();
      for( it = CachedQueue.begin(); it != it_end; it++ )  {
	TimeStamp SubTime = it->first;
	SubEvt*   pPassSubEvt = it->second;
	PassedQueue.insert( pair< TimeStamp, SubEvt* >( SubTime, pPassSubEvt ) );
      }

      /* Delete them from CachedQueue */
      CachedQueue.clear();
    }
  }
   
  /* Add the new SubEvt to the Queue */
  CachedQueue.insert( pair< TimeStamp, SubEvt* >( time, pSubEvt ) );

  return PassedQueue;
}
