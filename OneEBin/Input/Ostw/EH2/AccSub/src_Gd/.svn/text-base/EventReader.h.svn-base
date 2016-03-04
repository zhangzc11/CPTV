//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 13 14:15:20 2012 by ROOT version 5.30/04
// from TTree Event/Analysis Tree
// found on file: /home/bes/wangzhe/userdata/zlab/TWin/data/TWin/EH3/0022014.TWin.root
//////////////////////////////////////////////////////////

#ifndef EventReader_h
#define EventReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

class EventReader : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Det;
   Double_t        T2PrevMu;
   Double_t        T2PrevPlMu;
   Double_t        T2PrevAdMu;
   Double_t        T2PrevShMu;
   Int_t           Fold;
   Int_t           TrigSec[5];   //[Fold]
   Int_t           TrigNano[5];   //[Fold]
   Double_t        E[5];   //[Fold]
   Double_t        X[5];   //[Fold]
   Double_t        Y[5];   //[Fold]
   Double_t        Z[5];   //[Fold]
   Double_t        D2First[5];   //[Fold]
   Double_t        T2PrevSubEvt[5];   //[Fold]

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_Det;   //!
   TBranch        *b_T2PrevMu;   //!
   TBranch        *b_T2PrevPlMu;   //!
   TBranch        *b_T2PrevAdMu;   //!
   TBranch        *b_T2PrevShMu;   //!
   TBranch        *b_Fold;   //!
   TBranch        *b_TrigSec;   //!
   TBranch        *b_TrigNano;   //!
   TBranch        *b_E;   //!
   TBranch        *b_X;   //!
   TBranch        *b_Y;   //!
   TBranch        *b_Z;   //!
   TBranch        *b_D2First;   //!
   TBranch        *b_T2PrevSubEvt;   //!

   EventReader(TTree * /*tree*/ =0) { }
   virtual ~EventReader() { }
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

   ClassDef(EventReader,0);
};

#endif

#ifdef EventReader_cxx
void EventReader::Init(TTree *tree)
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
   fChain->SetBranchAddress("Det", &Det, &b_Det);
   fChain->SetBranchAddress("T2PrevMu", &T2PrevMu, &b_T2PrevMu);
   fChain->SetBranchAddress("T2PrevPlMu", &T2PrevPlMu, &b_T2PrevPlMu);
   fChain->SetBranchAddress("T2PrevAdMu", &T2PrevAdMu, &b_T2PrevAdMu);
   fChain->SetBranchAddress("T2PrevShMu", &T2PrevShMu, &b_T2PrevShMu);
   fChain->SetBranchAddress("Fold", &Fold, &b_Fold);
   fChain->SetBranchAddress("TrigSec", TrigSec, &b_TrigSec);
   fChain->SetBranchAddress("TrigNano", TrigNano, &b_TrigNano);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("X", X, &b_X);
   fChain->SetBranchAddress("Y", Y, &b_Y);
   fChain->SetBranchAddress("Z", Z, &b_Z);
   fChain->SetBranchAddress("D2First", D2First, &b_D2First);
   fChain->SetBranchAddress("T2PrevSubEvt", T2PrevSubEvt, &b_T2PrevSubEvt);
}

Bool_t EventReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef EventReader_cxx
