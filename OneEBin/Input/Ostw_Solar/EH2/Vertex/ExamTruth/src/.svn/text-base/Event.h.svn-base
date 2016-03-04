//
//  Structure "Event"
//
//  Dec. 2011 Zhe Wang
//

#ifndef _EVENT_H_
#define _EVENT_H_ 1

#define MaxFold 20

class Event
{
 public:
  Event()
    { Reset(); };

  ~Event()
    {  };
  
 public:
  int Reset()
  {
    Run = -1;
    Det = -1;
    
    T2PrevMu   = -1;
    T2PrevPlMu = -1;
    T2PrevAdMu = -1;
    T2PrevShMu = -1;
    T2PrevNetMu = -1;
    
    Fold = 0;
    
    for( unsigned int nn=0; nn<MaxFold; ++nn ) {
      TrigSec[nn] = -1;
      TrigNano[nn] = -1;
      E[nn] = -1;
      X[nn] = -1;
      Y[nn] = -1;
      Z[nn] = -1;
      D2First[nn] = -1;
      T2PrevSubEvt[nn] = -1;

      TrigSecT[nn] = -1;
      TrigNanoT[nn] = -1;
      ET[nn] = -1;
      XT[nn] = -1;
      YT[nn] = -1;
      ZT[nn] = -1;
      D2FirstT[nn] = -1;
      T2PrevSubEvtT[nn] = -1;

      XDepC[nn] = -1;
      YDepC[nn] = -1;
      ZDepC[nn] = -1;
      CapTarget = -1;
    }
    
    return 1;
  };

 public:
  /// Event information
  int    Run;
  int    Det;

  double T2PrevMu  ;
  double T2PrevPlMu;
  double T2PrevAdMu;
  double T2PrevShMu;
  double T2PrevNetMu;

  /// number of coincidence
  int    Fold;

  /// Sub-event list
  int    TrigSec[MaxFold];
  int    TrigNano[MaxFold];

  double E[MaxFold];
  double X[MaxFold];
  double Y[MaxFold];
  double Z[MaxFold];
  double D2First[MaxFold];
  double T2PrevSubEvt[MaxFold];

  /// The same list from the truth
  int    TrigSecT[MaxFold];
  int    TrigNanoT[MaxFold];

  double ET[MaxFold];
  double XT[MaxFold];
  double YT[MaxFold];
  double ZT[MaxFold];
  double D2FirstT[MaxFold];
  double T2PrevSubEvtT[MaxFold];

  double XDepC[MaxFold];
  double YDepC[MaxFold];
  double ZDepC[MaxFold];
  double CapTarget;
};

#endif // _EVENT_H_
