/**
 * SubEvt
 *
 * Nov. 22, 2011 Created by Zhe Wang
 */

#ifndef _SUB_EVT_H_
#define _SUB_EVT_H_

#include "StreamReader.h"

namespace MuonId {
  enum MuonId_t { NonMuon, PlMuon, AdMuon, ShMuon };
}

class SubEvt
{
 public:
  SubEvt();
  SubEvt( StreamReader* Reader );
  ~SubEvt();

  int Dump();
  
 public:
  int    Run;
  int    Site;
  int    Det;

  int    TrigNum;
  int    TrigType;
  int    TrigSec;
  int    TrigNano;

  int    NPmt;

  double E;
  double X;
  double Y;
  double Z;

  double TRms;
  double Quadrant;
  double QMax2Sum;
  double MaxQ2Inch;

  /* new variables */
  std::map<int /* AD No. */, MuonId::MuonId_t /* muon type */     > MuonStat;
};

#endif  // _SUB_EVT_H_
