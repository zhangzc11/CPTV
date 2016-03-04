//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Nov 27 20:25:44 2011 by ROOT version 5.30/02
// from TChain SubEvt/
//////////////////////////////////////////////////////////

#ifndef SubEvtReader_h
#define SubEvtReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

class SubEvtReader : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Site;
   Int_t           NDet;
   Int_t           SubEvtSec;
   Int_t           SubEvtNano;
   Double_t        MuonProb;
   Double_t        RetrigProb;
   Double_t        T2PrevSubEvt;
   Double_t        T2PrevMuon;
   Int_t           Valid[7];
   Int_t           Event[7];
   Int_t           Det[7];
   Int_t           TrigType[7];
   Int_t           TrigSec[7];
   Int_t           TrigNano[7];
   Int_t           NPmt[7];
   Double_t        E[7];
   Double_t        X[7];
   Double_t        Y[7];
   Double_t        Z[7];
   Double_t        TRms[7];
   Double_t        Quadrant[7];
   Double_t        QMax2Sum[7];

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_Site;   //!
   TBranch        *b_NDet;   //!
   TBranch        *b_SubEvtSec;   //!
   TBranch        *b_SubEvtNano;   //!
   TBranch        *b_MuonProb;   //!
   TBranch        *b_RetrigProb;   //!
   TBranch        *b_T2PrevSubEvt;   //!
   TBranch        *b_T2PrevMuon;   //!
   TBranch        *b_Valid;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_Det;   //!
   TBranch        *b_TrigType;   //!
   TBranch        *b_TrigSec;   //!
   TBranch        *b_TrigNano;   //!
   TBranch        *b_NPmt;   //!
   TBranch        *b_E;   //!
   TBranch        *b_X;   //!
   TBranch        *b_Y;   //!
   TBranch        *b_Z;   //!
   TBranch        *b_TRms;   //!
   TBranch        *b_Quadrant;   //!
   TBranch        *b_QMax2Sum;   //!

   SubEvtReader(TTree * /*tree*/ =0) { }
   virtual ~SubEvtReader() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(SubEvtReader,0);
};

#endif

#ifdef SubEvtReader_cxx
void SubEvtReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Site", &Site, &b_Site);
   fChain->SetBranchAddress("NDet", &NDet, &b_NDet);
   fChain->SetBranchAddress("SubEvtSec", &SubEvtSec, &b_SubEvtSec);
   fChain->SetBranchAddress("SubEvtNano", &SubEvtNano, &b_SubEvtNano);
   fChain->SetBranchAddress("MuonProb", &MuonProb, &b_MuonProb);
   fChain->SetBranchAddress("RetrigProb", &RetrigProb, &b_RetrigProb);
   fChain->SetBranchAddress("T2PrevSubEvt", &T2PrevSubEvt, &b_T2PrevSubEvt);
   fChain->SetBranchAddress("T2PrevMuon", &T2PrevMuon, &b_T2PrevMuon);
   fChain->SetBranchAddress("Valid", Valid, &b_Valid);
   fChain->SetBranchAddress("Event", Event, &b_Event);
   fChain->SetBranchAddress("Det", Det, &b_Det);
   fChain->SetBranchAddress("TrigType", TrigType, &b_TrigType);
   fChain->SetBranchAddress("TrigSec", TrigSec, &b_TrigSec);
   fChain->SetBranchAddress("TrigNano", TrigNano, &b_TrigNano);
   fChain->SetBranchAddress("NPmt", NPmt, &b_NPmt);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("X", X, &b_X);
   fChain->SetBranchAddress("Y", Y, &b_Y);
   fChain->SetBranchAddress("Z", Z, &b_Z);
   fChain->SetBranchAddress("TRms", TRms, &b_TRms);
   fChain->SetBranchAddress("Quadrant", Quadrant, &b_Quadrant);
   fChain->SetBranchAddress("QMax2Sum", QMax2Sum, &b_QMax2Sum);
}

Bool_t SubEvtReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef SubEvtReader_cxx
