#ifndef _RUN_STAT_H_
#define _RUN_STAT_H_

#include "TObject.h"

class RunStat : public TObject
{
 public:
  RunStat();
  virtual ~RunStat();
  
 public:
  Int_t   RunNumber;
  
  /// About calibration information
  Int_t   IsCalib;
  Int_t   Axis;
  Int_t   Source;
  Double_t Z;
  
  /// 
  Int_t   Site;
  Int_t   StartSec;
  Int_t   StartNano;
  Int_t   EndSec;
  Int_t   EndNano;
  Double_t FullTime;

  /// Somehow array doesn't work
  /// For each there are 4 ADs at most
  Double_t Veto1, Veto2, Veto3, Veto4;
  
  Double_t Scale1, Scale2, Scale3, Scale4;
  Double_t ScaleE1, ScaleE2, ScaleE3, ScaleE4;
  
  ClassDef(RunStat,1);  // Run Statistics
};

#endif // _RUN_STAT_H_
