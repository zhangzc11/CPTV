/**
 * SubEvt Tree
 *
 * Nov. 10, 2011 Created by Zhe Wang
 */

#ifndef _SUBEVT_TREE_H_
#define _SUBEVT_TREE_H_

#include "TFile.h"
#include "TTree.h"
#include <iostream>

using namespace std;

class SubEvtTree
{
 public:
  /// Tree creation
  SubEvtTree(const char* TreeName, const char* FileName, int BriefLevel);
  ~SubEvtTree();
  
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

  /// SubEvt information
  int    Run;
  int    Site;
  int    NDet;
  int    SubEvtSec;
  int    SubEvtNano;

  double MuonProb;
  double RetrigProb;
  double T2PrevSubEvt;
  double T2PrevMuon;

  // AD, pool and Rpc SubEvt
  int    Valid[7];
  int    Event[7];
  int    Det[7];

  int    TrigType[7];
  int    TrigSec[7];
  int    TrigNano[7];

  int    NPmt[7];

  double E[7];
  double X[7];
  double Y[7];
  double Z[7];

  double TRms[7];
  double Quadrant[7];
  double QMax2Sum[7];
  
 private:
  TFile* m_file;
  TTree* m_tree;

  int m_brief;
};

#endif  // _SUBEVT_TREE_H_
