/**
 * Stream Tree
 *
 * Nov. 10, 2011 Created by Zhe Wang
 */

#include "StreamTree.h"

#include <sstream>

StreamTree::StreamTree(const char* TreeName, const char* FileName, int BriefLevel)
  :Invalid(0)
{
  m_file = new TFile(FileName,"recreate");
  m_tree = new TTree(TreeName,"Analysis Stream Tree");    /// create tree
  m_brief = BriefLevel;
  
  //m_tree->SetMaxTreeSize(500000000);  // 500M

  /// Raw data stream
  m_tree->Branch( "Run",          &Run,          "Run/I"          );
  m_tree->Branch( "Site",         &Site,         "Site/I"         );
  m_tree->Branch( "Det",          &Det,          "Det/I"          );

  m_tree->Branch( "TrigNum",      &TrigNum,      "TrigNum/I"      );
  m_tree->Branch( "TrigType",     &TrigType,     "TrigType/I"     );
  m_tree->Branch( "TrigSec",      &TrigSec,      "TrigSec/I"      );
  m_tree->Branch( "TrigNano",     &TrigNano,     "TrigNano/I"     );

  m_tree->Branch( "NPmt",         &NPmt,         "NPmt/I"         );

  m_tree->Branch( "E",            &E,            "E/D"            );
  m_tree->Branch( "X",            &X,            "X/D"            );
  m_tree->Branch( "Y",            &Y,            "Y/D"            );
  m_tree->Branch( "Z",            &Z,            "Z/D"            );

  m_tree->Branch( "TRms",         &TRms,         "TRms/D"         );
  m_tree->Branch( "Quadrant",     &Quadrant,     "Quadrant/D"     );
  m_tree->Branch( "QMax2Sum",     &QMax2Sum,     "QMax2Sum/D"     );
  m_tree->Branch( "MaxQ2Inch",    &MaxQ2Inch,    "MaxQ2Inch/D"    );
}

StreamTree::~StreamTree()
{}

int StreamTree::Reset()
{
  Run = Invalid;
  Site = Invalid;
  Det = Invalid;

  TrigNum = Invalid;
  TrigType = Invalid;
  TrigSec = Invalid;
  TrigNano = Invalid;

  NPmt = Invalid;

  E = Invalid;
  X = Invalid;
  Y = Invalid;
  Z = Invalid;

  TRms = Invalid;
  Quadrant = Invalid;
  QMax2Sum = Invalid;
  MaxQ2Inch = Invalid;

  return 1;  // 1 for SUCCESS;
}

int StreamTree::Fill()
{
  m_tree->Fill();
  
  return  1; // 1 for SUCCESS;
}

int StreamTree::Close()
{
  // Pay attention to the last line. It is necessary to file splitting.
  // http://root.cern.ch/root/htmldoc/TTree.html#TTree:ChangeFile
  m_file = m_tree->GetCurrentFile(); //to get the pointer to the current file
  m_file->Write();
  m_file->Close();
  return  1; // 1 for SUCCESS;
}
