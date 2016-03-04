//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Nov 20 22:43:25 2011 by ROOT version 5.30/02
// from TTree Rec/Rec
// found on file: /home/wangzhe/share/data/exp/ntuple.Neutrino.0017764.Physics.EH1-Merged.KUP11A-IHEP._0212.root
//////////////////////////////////////////////////////////

#ifndef Tree2Selector_h
#define Tree2Selector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

class Tree2Selector : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Event;
   Int_t           ExecNum;
   Int_t           Site;
   Int_t           Det;
   Int_t           TrigType;
   Int_t           TrigSec;
   Int_t           TrigNanoSec;
   Int_t           Status;
   Float_t         Energy;
   Float_t         X;
   Float_t         Y;
   Float_t         Z;
   Float_t         MLEnergy;
   Float_t         MLX;
   Float_t         MLY;
   Float_t         MLZ;
   Float_t         Px;
   Float_t         Py;
   Float_t         Pz;
   Float_t         ScaledEnergy;
   Float_t         ScaledX;
   Float_t         ScaledY;
   Float_t         ScaledZ;
   Int_t           NPmt;
   Float_t         PERMS;
   Float_t         PESum;
   Float_t         TimeRMS;
   Float_t         RatioMaxQ;
   Float_t         EarlyChargeSum;
   Float_t         MiddleChargeSum;
   Float_t         LateChargeSum;
   Int_t           EffNPmt;
   Float_t         EffPERMS;
   Float_t         EffPESum;
   Float_t         EffTimeRMS;
   Float_t         EffRatioMaxQ;
   Float_t         EffRatioMaxQ123;
   Float_t         EffRatioMaxQ3x3;
   Float_t         MiddleTimeRMS;
   Float_t         MaxQ;
   Float_t         Quadrant;
   Float_t         PeakRMS;
   Float_t         Kurtosis;
   Float_t         QuadrantQ1;
   Float_t         QuadrantQ2;
   Float_t         QuadrantQ3;
   Float_t         QuadrantQ4;
   Float_t         RingKurtosis;
   Float_t         ColumnKurtosis;
   Float_t         MainPeakRMS;
   Float_t         SecondPeakRMS;
   Float_t         charge_sum_flasher_flag;
   Float_t         charge_sum_flasher_max;
   Int_t           flasher_ring;
   Int_t           flasher_column;
   Float_t         tRMS_local;
   Float_t         tRMS_local_wo_1st_hit;

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_ExecNum;   //!
   TBranch        *b_Site;   //!
   TBranch        *b_Det;   //!
   TBranch        *b_TrigType;   //!
   TBranch        *b_TrigSec;   //!
   TBranch        *b_TrigNanoSec;   //!
   TBranch        *b_Status;   //!
   TBranch        *b_Energy;   //!
   TBranch        *b_X;   //!
   TBranch        *b_Y;   //!
   TBranch        *b_Z;   //!
   TBranch        *b_MLEnergy;   //!
   TBranch        *b_MLX;   //!
   TBranch        *b_MLY;   //!
   TBranch        *b_MLZ;   //!
   TBranch        *b_Px;   //!
   TBranch        *b_Py;   //!
   TBranch        *b_Pz;   //!
   TBranch        *b_ScaledEnergy;   //!
   TBranch        *b_ScaledX;   //!
   TBranch        *b_ScaledY;   //!
   TBranch        *b_ScaledZ;   //!
   TBranch        *b_NPmt;   //!
   TBranch        *b_PERMS;   //!
   TBranch        *b_PESum;   //!
   TBranch        *b_TimeRMS;   //!
   TBranch        *b_RatioMaxQ;   //!
   TBranch        *b_EarlyChargeSum;   //!
   TBranch        *b_MiddleChargeSum;   //!
   TBranch        *b_LateChargeSum;   //!
   TBranch        *b_EffNPmt;   //!
   TBranch        *b_EffPERMS;   //!
   TBranch        *b_EffPESum;   //!
   TBranch        *b_EffTimeRMS;   //!
   TBranch        *b_EffRatioMaxQ;   //!
   TBranch        *b_EffRatioMaxQ123;   //!
   TBranch        *b_EffRatioMaxQ3x3;   //!
   TBranch        *b_MiddleTimeRMS;   //!
   TBranch        *b_MaxQ;   //!
   TBranch        *b_Quadrant;   //!
   TBranch        *b_PeakRMS;   //!
   TBranch        *b_Kurtosis;   //!
   TBranch        *b_QuadrantQ1;   //!
   TBranch        *b_QuadrantQ2;   //!
   TBranch        *b_QuadrantQ3;   //!
   TBranch        *b_QuadrantQ4;   //!
   TBranch        *b_RingKurtosis;   //!
   TBranch        *b_ColumnKurtosis;   //!
   TBranch        *b_MainPeakRMS;   //!
   TBranch        *b_SecondPeakRMS;   //!
   TBranch        *b_charge_sum_flasher_flag;   //!
   TBranch        *b_charge_sum_flasher_max;   //!
   TBranch        *b_flasher_ring;   //!
   TBranch        *b_flasher_column;   //!
   TBranch        *b_tRMS_local;   //!
   TBranch        *b_tRMS_local_wo_1st_hit;   //!

   Tree2Selector(TTree * /*tree*/ =0) { }
   virtual ~Tree2Selector() { }
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

   ClassDef(Tree2Selector,0);
};

#endif

#ifdef Tree2Selector_cxx
void Tree2Selector::Init(TTree *tree)
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
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("ExecNum", &ExecNum, &b_ExecNum);
   fChain->SetBranchAddress("Site", &Site, &b_Site);
   fChain->SetBranchAddress("Det", &Det, &b_Det);
   fChain->SetBranchAddress("TrigType", &TrigType, &b_TrigType);
   fChain->SetBranchAddress("TrigSec", &TrigSec, &b_TrigSec);
   fChain->SetBranchAddress("TrigNanoSec", &TrigNanoSec, &b_TrigNanoSec);
   fChain->SetBranchAddress("Status", &Status, &b_Status);
   fChain->SetBranchAddress("Energy", &Energy, &b_Energy);
   fChain->SetBranchAddress("X", &X, &b_X);
   fChain->SetBranchAddress("Y", &Y, &b_Y);
   fChain->SetBranchAddress("Z", &Z, &b_Z);
   fChain->SetBranchAddress("MLEnergy", &MLEnergy, &b_MLEnergy);
   fChain->SetBranchAddress("MLX", &MLX, &b_MLX);
   fChain->SetBranchAddress("MLY", &MLY, &b_MLY);
   fChain->SetBranchAddress("MLZ", &MLZ, &b_MLZ);
   fChain->SetBranchAddress("Px", &Px, &b_Px);
   fChain->SetBranchAddress("Py", &Py, &b_Py);
   fChain->SetBranchAddress("Pz", &Pz, &b_Pz);
   fChain->SetBranchAddress("ScaledEnergy", &ScaledEnergy, &b_ScaledEnergy);
   fChain->SetBranchAddress("ScaledX", &ScaledX, &b_ScaledX);
   fChain->SetBranchAddress("ScaledY", &ScaledY, &b_ScaledY);
   fChain->SetBranchAddress("ScaledZ", &ScaledZ, &b_ScaledZ);
   fChain->SetBranchAddress("NPmt", &NPmt, &b_NPmt);
   fChain->SetBranchAddress("PERMS", &PERMS, &b_PERMS);
   fChain->SetBranchAddress("PESum", &PESum, &b_PESum);
   fChain->SetBranchAddress("TimeRMS", &TimeRMS, &b_TimeRMS);
   fChain->SetBranchAddress("RatioMaxQ", &RatioMaxQ, &b_RatioMaxQ);
   fChain->SetBranchAddress("EarlyChargeSum", &EarlyChargeSum, &b_EarlyChargeSum);
   fChain->SetBranchAddress("MiddleChargeSum", &MiddleChargeSum, &b_MiddleChargeSum);
   fChain->SetBranchAddress("LateChargeSum", &LateChargeSum, &b_LateChargeSum);
   fChain->SetBranchAddress("EffNPmt", &EffNPmt, &b_EffNPmt);
   fChain->SetBranchAddress("EffPERMS", &EffPERMS, &b_EffPERMS);
   fChain->SetBranchAddress("EffPESum", &EffPESum, &b_EffPESum);
   fChain->SetBranchAddress("EffTimeRMS", &EffTimeRMS, &b_EffTimeRMS);
   fChain->SetBranchAddress("EffRatioMaxQ", &EffRatioMaxQ, &b_EffRatioMaxQ);
   fChain->SetBranchAddress("EffRatioMaxQ123", &EffRatioMaxQ123, &b_EffRatioMaxQ123);
   fChain->SetBranchAddress("EffRatioMaxQ3x3", &EffRatioMaxQ3x3, &b_EffRatioMaxQ3x3);
   fChain->SetBranchAddress("MiddleTimeRMS", &MiddleTimeRMS, &b_MiddleTimeRMS);
   fChain->SetBranchAddress("MaxQ", &MaxQ, &b_MaxQ);
   fChain->SetBranchAddress("Quadrant", &Quadrant, &b_Quadrant);
   fChain->SetBranchAddress("PeakRMS", &PeakRMS, &b_PeakRMS);
   fChain->SetBranchAddress("Kurtosis", &Kurtosis, &b_Kurtosis);
   fChain->SetBranchAddress("QuadrantQ1", &QuadrantQ1, &b_QuadrantQ1);
   fChain->SetBranchAddress("QuadrantQ2", &QuadrantQ2, &b_QuadrantQ2);
   fChain->SetBranchAddress("QuadrantQ3", &QuadrantQ3, &b_QuadrantQ3);
   fChain->SetBranchAddress("QuadrantQ4", &QuadrantQ4, &b_QuadrantQ4);
   fChain->SetBranchAddress("RingKurtosis", &RingKurtosis, &b_RingKurtosis);
   fChain->SetBranchAddress("ColumnKurtosis", &ColumnKurtosis, &b_ColumnKurtosis);
   fChain->SetBranchAddress("MainPeakRMS", &MainPeakRMS, &b_MainPeakRMS);
   fChain->SetBranchAddress("SecondPeakRMS", &SecondPeakRMS, &b_SecondPeakRMS);
   fChain->SetBranchAddress("charge_sum_flasher_flag", &charge_sum_flasher_flag, &b_charge_sum_flasher_flag);
   fChain->SetBranchAddress("charge_sum_flasher_max", &charge_sum_flasher_max, &b_charge_sum_flasher_max);
   fChain->SetBranchAddress("flasher_ring", &flasher_ring, &b_flasher_ring);
   fChain->SetBranchAddress("flasher_column", &flasher_column, &b_flasher_column);
   fChain->SetBranchAddress("tRMS_local", &tRMS_local, &b_tRMS_local);
   fChain->SetBranchAddress("tRMS_local_wo_1st_hit", &tRMS_local_wo_1st_hit, &b_tRMS_local_wo_1st_hit);
}

Bool_t Tree2Selector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Tree2Selector_cxx
