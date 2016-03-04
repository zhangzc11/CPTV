/**
 * Event Tree
 *
 * Nov. 10, 2011 Created by Zhe Wang
 */

#ifndef _EVENT_TREE_H_
#define _EVENT_TREE_H_

#include "TFile.h"
#include "TTree.h"
#include <iostream>

using namespace std;

#define Max 20

class EventTree
{
 public:
  /// Tree creation
  EventTree(const char* TreeName, const char* FileName, int BriefLevel);
  ~EventTree();
  
 public:
  /// Reset all numbers into Invalid
  int Reset();
  /// Fill one entries
  int Fill();
  /// Close the root file
  int Close();

 public:
  
  /// Invalid number 
  const int    Invalid;

  /// Event information
  int    Run;
  int    Det;

  double T2PrevMu;
  double T2PrevPlMu;
  double T2PrevAdMu;
  double T2PrevShMu;
  double T2PrevNetMu;

  /// number of coincidence
  int    Fold;

  /// Sub-event list
  int    TrigSec[Max];
  int    TrigNano[Max];

  double E[Max];
  double X[Max];
  double Y[Max];
  double Z[Max];
  double D2First[Max];
  double T2PrevSubEvt[Max];

  /// For Truth
  int    TrigSecT[Max];
  int    TrigNanoT[Max];

  double ET[Max];
  double XT[Max];
  double YT[Max];
  double ZT[Max];
  double D2FirstT[Max];
  double T2PrevSubEvtT[Max];

  /// Gamma energy deposit center
  double XDepC[Max];
  double YDepC[Max];
  double ZDepC[Max];
  double CapTarget;
 private:
  TFile* m_file;
  TTree* m_tree;
  
  int m_brief;
};

#endif  // _EVENT_TREE_H_
