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
    
    Fold = -1;
    
    for( unsigned int nn=0; nn<MaxFold; ++nn ) {
      TrigSec[nn] = -1;
      TrigNano[nn] = -1;
      E[nn] = -1;
      X[nn] = -1;
      Y[nn] = -1;
      Z[nn] = -1;
      D2First[nn] = -1;
      T2PrevSubEvt[nn] = -1;
      Quadrant[nn] = -1;
      QMax2Sum[nn] = -1;
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
  int    TrigNum[MaxFold];
  int    TrigSec[MaxFold];
  int    TrigNano[MaxFold];

  double E[MaxFold];
  double X[MaxFold];
  double Y[MaxFold];
  double Z[MaxFold];
  double D2First[MaxFold];
  double T2PrevSubEvt[MaxFold];
  double Quadrant[MaxFold];
  double QMax2Sum[MaxFold];
};

#endif // _EVENT_H_
