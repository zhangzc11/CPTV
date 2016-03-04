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
  int    Event;
  int    TimeSec;
  int    TimeNano;
  int    Det;

  double T2PrevMuon;
  double EPrevMuon;
  double D2PrevMuon;

  /// number of coincidence
  int    Fold;

  /// Sub-event list
  int    TrigType[Max];
  int    TrigSec[Max];
  int    TrigNano[Max];

  double E[Max];
  double X[Max];
  double Y[Max];
  double Z[Max];
  double D2First[Max];
  double T2PrevSubEvt[Max];

 private:
  TFile* m_file;
  TTree* m_tree;
  
  int m_brief;
};

#endif  // _EVENT_TREE_H_
