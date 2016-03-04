//
//  Structure "Event"
//
//  Dec. 2011 Zhe Wang
//

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
    EventNo = -1;
    TimeSec = -1;
    TimeNano = -1;
    Det = -1;
    
    T2PrevMuon = -1;
    EPrevMuon = -1;
    D2PrevMuon = -1;
    
    Fold = -1;
    
    for( unsigned int nn=0; nn<MaxFold; ++nn ) {
      TrigType[nn] = -1;
      TrigSec[nn] = -1;
      TrigNano[nn] = -1;
      E[nn] = -1;
      X[nn] = -1;
      Y[nn] = -1;
      Z[nn] = -1;
      D2First[nn] = -1;
      T2PrevSubEvt[nn] = -1;
    }
    
    return 1;
  };

 public:
  /// Event information
  int    Run;
  int    EventNo;
  /// Earliest trigger time of all sub-event
  int    TimeSec;
  int    TimeNano;
  int    Det;

  double T2PrevMuon;
  double EPrevMuon;
  double D2PrevMuon;

  /// number of coincidence
  int    Fold;

  /// Sub-event list
  int    TrigType[MaxFold];
  int    TrigSec[MaxFold];
  int    TrigNano[MaxFold];

  double E[MaxFold];
  double X[MaxFold];
  double Y[MaxFold];
  double Z[MaxFold];
  double D2First[MaxFold];
  double T2PrevSubEvt[MaxFold];
};
