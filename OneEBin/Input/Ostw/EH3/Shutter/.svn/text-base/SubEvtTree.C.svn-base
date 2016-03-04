/**
 * SubEvt Tree
 *
 * Nov. 10, 2011 Created by Zhe Wang
 */

#include "SubEvtTree.h"

#include <sstream>

SubEvtTree::SubEvtTree(const char* TreeName, const char* FileName, int BriefLevel)
  :Invalid(0)
{
  m_file = new TFile(FileName,"recreate");
  m_tree = new TTree(TreeName,"Analysis SubEvent Tree");    /// create tree
  m_brief = BriefLevel;
  
  m_tree->SetMaxTreeSize(500000000);  // 500M

  /// SubEvent Stream
  m_tree->Branch( "Run",          &Run,          "Run/I"          );
  m_tree->Branch( "Site",         &Site,         "Site/I"         );
  m_tree->Branch( "NDet",         &NDet,         "NDet/I"         );
  m_tree->Branch( "SubEvtSec",    &SubEvtSec,    "SubEvtSec/I"    );
  m_tree->Branch( "SubEvtNano",   &SubEvtNano,   "SubEvtNano/I"   );

  m_tree->Branch( "MuonProb",     &MuonProb,     "MuonProb/D"     );
  m_tree->Branch( "RetrigProb",   &RetrigProb,   "RetrigProb/D"   );
  m_tree->Branch( "T2PrevSubEvt", &T2PrevSubEvt, "T2PrevSubEvt/D" );
  m_tree->Branch( "T2PrevMuon",   &T2PrevMuon,   "T2PrevMuon/D"   );

  // AD, pool and RPC SubEvt 
  m_tree->Branch( "Valid",        Valid,        "Valid[7]/I"        );
  m_tree->Branch( "Event",        Event,        "Event[7]/I"        );
  m_tree->Branch( "Det",          Det,          "Det[7]/I"          );

  m_tree->Branch( "TrigType",     TrigType,     "TrigType[7]/I"     );
  m_tree->Branch( "TrigSec",      TrigSec,      "TrigSec[7]/I"      );
  m_tree->Branch( "TrigNano",     TrigNano,     "TrigNano[7]/I"     );

  m_tree->Branch( "NPmt",         NPmt,         "NPmt[7]/I"         );

  m_tree->Branch( "E",            E,            "E[7]/D"            );
  m_tree->Branch( "X",            X,            "X[7]/D"            );
  m_tree->Branch( "Y",            Y,            "Y[7]/D"            );
  m_tree->Branch( "Z",            Z,            "Z[7]/D"            );

  m_tree->Branch( "TRms",         TRms,         "TRms[7]/D"         );
  m_tree->Branch( "Quadrant",     Quadrant,     "Quadrant[7]/D"     );
  m_tree->Branch( "QMax2Sum",     QMax2Sum,     "QMax2Sum[7]/D"     );
}

SubEvtTree::~SubEvtTree()
{}

int SubEvtTree::Reset()
{
  
  Run = Invalid;
  Site = Invalid;
  NDet = 0;
  SubEvtSec = Invalid;
  SubEvtNano = Invalid;

  MuonProb = 0;
  RetrigProb = 0;
  T2PrevSubEvt = Invalid;
  T2PrevMuon = Invalid;

  for( unsigned int i=0; i<7; i++ )  {
    Valid[i] = 0;
    Event[i] = Invalid;
    Det[i] = Invalid;
    
    TrigType[i] = Invalid;
    TrigSec[i] = Invalid;
    TrigNano[i] = Invalid;
    
    NPmt[i] = Invalid;
    
    E[i] = Invalid;
    X[i] = Invalid;
    Y[i] = Invalid;
    Z[i] = Invalid;
    
    TRms[i] = Invalid;
    Quadrant[i] = Invalid;
    QMax2Sum[i] = Invalid;
  }

  return 1;  // 1 for SUCCESS;
}

int SubEvtTree::Fill()
{
  m_tree->Fill();
  
  return  1; // 1 for SUCCESS;
}

int SubEvtTree::Close()
{
  // Pay attention to the last line. It is necessary to file splitting.
  // http://root.cern.ch/root/htmldoc/TTree.html#TTree:ChangeFile
  m_file = m_tree->GetCurrentFile(); //to get the pointer to the current file
  m_file->Write();
  m_file->Close();
  return  1; // 1 for SUCCESS;
}
