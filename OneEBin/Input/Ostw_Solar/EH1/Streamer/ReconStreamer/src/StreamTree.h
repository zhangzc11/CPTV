/**
 * Stream Tree
 *
 * Nov. 10, 2011 Created by Zhe Wang
 */

#ifndef _STREAM_TREE_H_
#define _STREAM_TREE_H_

#include "TFile.h"
#include "TTree.h"
#include <iostream>

using namespace std;

class StreamTree
{
 public:
  /// Tree creation
  StreamTree(const char* TreeName, const char* FileName, int BriefLevel);
  ~StreamTree();
  
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

  /// Stream information
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

 private:
  TFile* m_file;
  TTree* m_tree;

  int m_brief;
};

#endif  // _STREAM_TREE_H_
