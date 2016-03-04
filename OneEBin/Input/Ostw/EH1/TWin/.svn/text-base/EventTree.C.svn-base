/**
 * Event Tree
 *
 * Nov. 10, 2011 Created by Zhe Wang
 */

#include "EventTree.h"

#include <sstream>

EventTree::EventTree(const char* TreeName, const char* FileName, int BriefLevel)
  :Invalid(0)
{
  m_file = new TFile(FileName,"recreate");
  m_tree = new TTree(TreeName,"Analysis Tree");    /// create tree
  m_brief = BriefLevel;
  
  /// No spliting
  /// m_tree->SetMaxTreeSize(500000000);  // 500M

  /// Tree entry information
  /// For delayed signal
  m_tree->Branch( "Run",          &Run,          "Run/I"          );
  m_tree->Branch( "Event",        &Event,        "Event/I"        );
  m_tree->Branch( "TimeSec",      &TimeSec,      "TimeSec/I"      );
  m_tree->Branch( "TimeNano",     &TimeNano,     "TimeNano/I"     );
  m_tree->Branch( "Det",          &Det,          "Det/I"          );

  m_tree->Branch( "T2PrevMuon",   &T2PrevMuon,   "T2PrevMuon/D"   );
  m_tree->Branch( "EPrevMuon",    &EPrevMuon,    "EPrevMuon/D"    );
  m_tree->Branch( "D2PrevMuon",   &D2PrevMuon,   "D2PrevMuon/D"   );

  m_tree->Branch( "Fold",         &Fold,         "Fold/I"         );

  m_tree->Branch( "TrigType",     TrigType,      "TrigType[Fold]/I"      );
  m_tree->Branch( "TrigSec",      TrigSec,       "TrigSec[Fold]/I"       );
  m_tree->Branch( "TrigNano",     TrigNano,      "TrigNano[Fold]/I"      );
  m_tree->Branch( "E",            E,             "E[Fold]/D"             );
  m_tree->Branch( "X",            X,             "X[Fold]/D"             );
  m_tree->Branch( "Y",            Y,             "Y[Fold]/D"             );
  m_tree->Branch( "Z",            Z,             "Z[Fold]/D"             );
  m_tree->Branch( "D2First",      D2First,       "D2First[Fold]/D"       );
  m_tree->Branch( "T2PrevSubEvt", T2PrevSubEvt,  "T2PrevSubEvt[Fold]/D"  );
}

EventTree::~EventTree()
{}

int EventTree::Reset()
{
  Run = Invalid;
  Event = Invalid;
  TimeSec = Invalid;
  TimeNano = Invalid;
  Det = Invalid;

  T2PrevMuon = Invalid;
  EPrevMuon = Invalid;
  D2PrevMuon = Invalid;

  Fold = Invalid;

  for( unsigned int nn=0; nn<Max; ++nn ) {
    TrigType[nn] = Invalid;
    TrigSec[nn] = Invalid;
    TrigNano[nn] = Invalid;
    E[nn] = Invalid;
    X[nn] = Invalid;
    Y[nn] = Invalid;
    Z[nn] = Invalid;
    D2First[nn] = Invalid;
    T2PrevSubEvt[nn] = Invalid;
  }

  return 1;  // 1 for SUCCESS;
}

int EventTree::Fill()
{
  m_tree->Fill();
  
  return  1; // 1 for SUCCESS;
}

int EventTree::Close()
{
  // Pay attention to the last line. It is necessary to file splitting.
  // http://root.cern.ch/root/htmldoc/TTree.html#TTree:ChangeFile
  m_file = m_tree->GetCurrentFile(); //to get the pointer to the current file
  m_file->Write();

  return  1; // 1 for SUCCESS;
}
