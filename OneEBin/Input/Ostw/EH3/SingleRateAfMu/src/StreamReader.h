//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 12 15:03:19 2012 by ROOT version 5.30/02
// from TChain Stream/
//////////////////////////////////////////////////////////

#ifndef StreamReader_h
#define StreamReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

class StreamReader : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Site;
   Int_t           Det;
   Int_t           TrigNum;
   Int_t           TrigType;
   Int_t           TrigSec;
   Int_t           TrigNano;
   Int_t           NPmt;
   Double_t        E;
   Double_t        X;
   Double_t        Y;
   Double_t        Z;
   Double_t        TRms;
   Double_t        Quadrant;
   Double_t        QMax2Sum;
   Double_t        MaxQ2Inch;

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_Site;   //!
   TBranch        *b_Det;   //!
   TBranch        *b_TrigNum;   //!
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
   TBranch        *b_MaxQ2Inch;   //!

   StreamReader(TTree * /*tree*/ =0) { }
   virtual ~StreamReader() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(StreamReader,0);
};

#endif

#ifdef StreamReader_cxx
void StreamReader::Init(TTree *tree)
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
   fChain->SetBranchAddress("Det", &Det, &b_Det);
   fChain->SetBranchAddress("TrigNum", &TrigNum, &b_TrigNum);
   fChain->SetBranchAddress("TrigType", &TrigType, &b_TrigType);
   fChain->SetBranchAddress("TrigSec", &TrigSec, &b_TrigSec);
   fChain->SetBranchAddress("TrigNano", &TrigNano, &b_TrigNano);
   fChain->SetBranchAddress("NPmt", &NPmt, &b_NPmt);
   fChain->SetBranchAddress("E", &E, &b_E);
   fChain->SetBranchAddress("X", &X, &b_X);
   fChain->SetBranchAddress("Y", &Y, &b_Y);
   fChain->SetBranchAddress("Z", &Z, &b_Z);
   fChain->SetBranchAddress("TRms", &TRms, &b_TRms);
   fChain->SetBranchAddress("Quadrant", &Quadrant, &b_Quadrant);
   fChain->SetBranchAddress("QMax2Sum", &QMax2Sum, &b_QMax2Sum);
   fChain->SetBranchAddress("MaxQ2Inch", &MaxQ2Inch, &b_MaxQ2Inch);
}

Bool_t StreamReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef StreamReader_cxx
