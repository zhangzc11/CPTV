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
  m_tree->Branch( "Det",          &Det,          "Det/I"          );

  /* Time relavant to the trigger time of the previous muon of a certain type. */
  m_tree->Branch( "T2PrevMu",     &T2PrevMu,     "T2PrevMu/D"     );
  m_tree->Branch( "T2PrevPlMu",   &T2PrevPlMu,   "T2PrevPlMu/D "  );
  m_tree->Branch( "T2PrevAdMu",   &T2PrevAdMu,   "T2PrevAdMu/D"   );
  m_tree->Branch( "T2PrevShMu",   &T2PrevShMu,   "T2PrevShMu/D "  );

  /* The definition of NetMuonT is the end of the previous muon veto window, which is different from the rest. */
  m_tree->Branch( "T2PrevNetMu",  &T2PrevNetMu,  "T2PrevNetMu/D "  );

  m_tree->Branch( "Fold",         &Fold,         "Fold/I"         );

  m_tree->Branch( "TrigSec",      TrigSec,       "TrigSec[Fold]/I"       );
  m_tree->Branch( "TrigNano",     TrigNano,      "TrigNano[Fold]/I"      );
  m_tree->Branch( "E",            E,             "E[Fold]/D"             );
  m_tree->Branch( "X",            X,             "X[Fold]/D"             );
  m_tree->Branch( "Y",            Y,             "Y[Fold]/D"             );
  m_tree->Branch( "Z",            Z,             "Z[Fold]/D"             );
  m_tree->Branch( "D2First",      D2First,       "D2First[Fold]/D"       );
  m_tree->Branch( "T2PrevSubEvt", T2PrevSubEvt,  "T2PrevSubEvt[Fold]/D"  );

  m_tree->Branch( "TrigSecT",      TrigSecT,       "TrigSecT[Fold]/I"       );
  m_tree->Branch( "TrigNanoT",     TrigNanoT,      "TrigNanoT[Fold]/I"      );
  m_tree->Branch( "ET",            ET,             "ET[Fold]/D"             );
  m_tree->Branch( "XT",            XT,             "XT[Fold]/D"             );
  m_tree->Branch( "YT",            YT,             "YT[Fold]/D"             );
  m_tree->Branch( "ZT",            ZT,             "ZT[Fold]/D"             );
  m_tree->Branch( "D2FirstT",      D2FirstT,       "D2FirstT[Fold]/D"       );
  m_tree->Branch( "T2PrevSubEvtT", T2PrevSubEvtT,  "T2PrevSubEvtT[Fold]/D"  );

  m_tree->Branch( "XDepC",            XDepC,             "XDepC[Fold]/D"             );
  m_tree->Branch( "YDepC",            YDepC,             "YDepC[Fold]/D"             );
  m_tree->Branch( "ZDepC",            ZDepC,             "ZDepC[Fold]/D"             );
  m_tree->Branch( "CapTarget",    &CapTarget,             "CapTarget/D"         );
}

EventTree::~EventTree()
{}

int EventTree::Reset()
{
  Run = Invalid;
  Det = Invalid;

  T2PrevMu = Invalid;
  T2PrevPlMu = Invalid;
  T2PrevAdMu = Invalid;
  T2PrevShMu = Invalid;
  T2PrevNetMu = Invalid;

  Fold = Invalid;

  for( unsigned int nn=0; nn<Max; ++nn ) {
    TrigSec[nn] = Invalid;
    TrigNano[nn] = Invalid;
    E[nn] = Invalid;
    X[nn] = Invalid;
    Y[nn] = Invalid;
    Z[nn] = Invalid;
    D2First[nn] = Invalid;
    T2PrevSubEvt[nn] = Invalid;

    TrigSecT[nn] = Invalid;
    TrigNanoT[nn] = Invalid;
    ET[nn] = Invalid;
    XT[nn] = Invalid;
    YT[nn] = Invalid;
    ZT[nn] = Invalid;
    D2FirstT[nn] = Invalid;
    T2PrevSubEvtT[nn] = Invalid;

    XDepC[nn] = Invalid;
    YDepC[nn] = Invalid;
    ZDepC[nn] = Invalid;
    CapTarget = Invalid;
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
