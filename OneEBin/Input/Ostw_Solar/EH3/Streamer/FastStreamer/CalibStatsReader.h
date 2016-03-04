//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 20 15:08:44 2012 by ROOT version 5.30/02
// from TTree CalibStats/Tree at /Event/Data/CalibStats holding Data_CalibStats
// found on file: /home/wangzhe/share/data/exp/recon.Neutrino.0021201.Physics.EH2-Merged.P12B-I._0001.root
//////////////////////////////////////////////////////////

#ifndef CalibStatsReader_h
#define CalibStatsReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
   const Int_t kMaxinputHeaders3 = 20;

#include <vector>
using namespace std;

class CalibStatsReader : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
 //PerHeaderObject *Data_CalibStats;
   Int_t           clID;
   Int_t           earliest_mSec;
   Int_t           earliest_mNanoSec;
   Int_t           latest_mSec;
   Int_t           latest_mNanoSec;
   Int_t           context_mSite;
   Int_t           context_mSimFlag;
   Int_t           context_mTimeStamp_mSec;
   Int_t           context_mTimeStamp_mNanoSec;
   Int_t           context_mDetId;
   Int_t           execNumber;
   UInt_t          jobId_m_data[4];
   vector<unsigned long> randomState;
   Int_t           inputHeaders_;
   Int_t           inputHeaders_m_entry[kMaxinputHeaders3];   //[inputHeaders_]
   string          inputHeaders_m_path[kMaxinputHeaders3];
   Float_t         ColumnKurtosis;
   Int_t           Column_2inchPMT;
   Int_t           ELast_ADCalibShower_pe;
   Int_t           ELast_ADShower_pe;
   Float_t         EarlyCharge;
   Float_t         Kurtosis;
   Float_t         LateCharge;
   Float_t         MainPeakRMS;
   Float_t         MaxQ;
   Float_t         MaxQ_2inchPMT;
   Float_t         MiddleTimeRMS;
   Float_t         NominalCharge;
   Float_t         PeakRMS;
   Float_t         Q1;
   Float_t         Q2;
   Float_t         Q3;
   Float_t         Quadrant;
   Float_t         QuadrantQ1;
   Float_t         QuadrantQ2;
   Float_t         QuadrantQ3;
   Float_t         QuadrantQ4;
   Float_t         RingKurtosis;
   Float_t         SecondPeakRMS;
   Int_t           blocked_trigger;
   Int_t           buffer_full_flag;
   Float_t         charge_sum_flasher_max;
   Float_t         dtLastAD1_ms;
   Float_t         dtLastAD2_ms;
   Float_t         dtLastAD3_ms;
   Float_t         dtLastAD4_ms;
   Float_t         dtLastIWS_ms;
   Float_t         dtLastOWS_ms;
   Float_t         dtLastRPC_ms;
   Int_t           dtLast_ADCalibShower_ms;
   Int_t           dtLast_ADMuon_ms;
   Int_t           dtLast_ADShower_ms;
   Float_t         dtNextAD1_ms;
   Float_t         dtNextAD2_ms;
   Float_t         dtNextAD3_ms;
   Float_t         dtNextAD4_ms;
   Float_t         dtNextIWS_ms;
   Float_t         dtNextOWS_ms;
   Float_t         dtNextRPC_ms;
   Int_t           flasher_column;
   Float_t         flasher_flag;
   Int_t           flasher_ring;
   Float_t         integralLiveTime_blocked_trigger_ms;
   Float_t         integralLiveTime_buffer_full_ms;
   Float_t         integralRunTime_ms;
   Int_t           maxqCol;
   Int_t           maxqRing;
   Float_t         nCalibPESum;
   Int_t           nHit;
   Float_t         nPEMax;
   Float_t         nPEMedian;
   Float_t         nPERMS;
   Float_t         nPESum;
   Float_t         nPulseMedian;
   Float_t         nPulseRMS;
   Float_t         nPulseSum;
   Float_t         tEarliest;
   Float_t         tLatest;
   Float_t         tMean;
   Float_t         tMedian;
   Float_t         tRMS;
   Float_t         time_PSD;
   Float_t         time_PSD1;
   Float_t         time_PSD_local_RMS;
   Int_t           triggerNumber;

   // List of branches
   TBranch        *b_Data_CalibStats_clID;   //!
   TBranch        *b_Data_CalibStats_earliest_mSec;   //!
   TBranch        *b_Data_CalibStats_earliest_mNanoSec;   //!
   TBranch        *b_Data_CalibStats_latest_mSec;   //!
   TBranch        *b_Data_CalibStats_latest_mNanoSec;   //!
   TBranch        *b_Data_CalibStats_context_mSite;   //!
   TBranch        *b_Data_CalibStats_context_mSimFlag;   //!
   TBranch        *b_Data_CalibStats_context_mTimeStamp_mSec;   //!
   TBranch        *b_Data_CalibStats_context_mTimeStamp_mNanoSec;   //!
   TBranch        *b_Data_CalibStats_context_mDetId;   //!
   TBranch        *b_Data_CalibStats_execNumber;   //!
   TBranch        *b_Data_CalibStats_jobId_m_data;   //!
   TBranch        *b_Data_CalibStats_randomState;   //!
   TBranch        *b_Data_CalibStats_inputHeaders_;   //!
   TBranch        *b_inputHeaders_m_entry;   //!
   TBranch        *b_inputHeaders_m_path;   //!
   TBranch        *b_ColumnKurtosis;   //!
   TBranch        *b_Column_2inchPMT;   //!
   TBranch        *b_ELast_ADCalibShower_pe;   //!
   TBranch        *b_ELast_ADShower_pe;   //!
   TBranch        *b_EarlyCharge;   //!
   TBranch        *b_Kurtosis;   //!
   TBranch        *b_LateCharge;   //!
   TBranch        *b_MainPeakRMS;   //!
   TBranch        *b_MaxQ;   //!
   TBranch        *b_MaxQ_2inchPMT;   //!
   TBranch        *b_MiddleTimeRMS;   //!
   TBranch        *b_NominalCharge;   //!
   TBranch        *b_PeakRMS;   //!
   TBranch        *b_Q1;   //!
   TBranch        *b_Q2;   //!
   TBranch        *b_Q3;   //!
   TBranch        *b_Quadrant;   //!
   TBranch        *b_QuadrantQ1;   //!
   TBranch        *b_QuadrantQ2;   //!
   TBranch        *b_QuadrantQ3;   //!
   TBranch        *b_QuadrantQ4;   //!
   TBranch        *b_RingKurtosis;   //!
   TBranch        *b_SecondPeakRMS;   //!
   TBranch        *b_blocked_trigger;   //!
   TBranch        *b_buffer_full_flag;   //!
   TBranch        *b_charge_sum_flasher_max;   //!
   TBranch        *b_dtLastAD1_ms;   //!
   TBranch        *b_dtLastAD2_ms;   //!
   TBranch        *b_dtLastAD3_ms;   //!
   TBranch        *b_dtLastAD4_ms;   //!
   TBranch        *b_dtLastIWS_ms;   //!
   TBranch        *b_dtLastOWS_ms;   //!
   TBranch        *b_dtLastRPC_ms;   //!
   TBranch        *b_dtLast_ADCalibShower_ms;   //!
   TBranch        *b_dtLast_ADMuon_ms;   //!
   TBranch        *b_dtLast_ADShower_ms;   //!
   TBranch        *b_dtNextAD1_ms;   //!
   TBranch        *b_dtNextAD2_ms;   //!
   TBranch        *b_dtNextAD3_ms;   //!
   TBranch        *b_dtNextAD4_ms;   //!
   TBranch        *b_dtNextIWS_ms;   //!
   TBranch        *b_dtNextOWS_ms;   //!
   TBranch        *b_dtNextRPC_ms;   //!
   TBranch        *b_flasher_column;   //!
   TBranch        *b_flasher_flag;   //!
   TBranch        *b_flasher_ring;   //!
   TBranch        *b_integralLiveTime_blocked_trigger_ms;   //!
   TBranch        *b_integralLiveTime_buffer_full_ms;   //!
   TBranch        *b_integralRunTime_ms;   //!
   TBranch        *b_maxqCol;   //!
   TBranch        *b_maxqRing;   //!
   TBranch        *b_nCalibPESum;   //!
   TBranch        *b_nHit;   //!
   TBranch        *b_nPEMax;   //!
   TBranch        *b_nPEMedian;   //!
   TBranch        *b_nPERMS;   //!
   TBranch        *b_nPESum;   //!
   TBranch        *b_nPulseMedian;   //!
   TBranch        *b_nPulseRMS;   //!
   TBranch        *b_nPulseSum;   //!
   TBranch        *b_tEarliest;   //!
   TBranch        *b_tLatest;   //!
   TBranch        *b_tMean;   //!
   TBranch        *b_tMedian;   //!
   TBranch        *b_tRMS;   //!
   TBranch        *b_time_PSD;   //!
   TBranch        *b_time_PSD1;   //!
   TBranch        *b_time_PSD_local_RMS;   //!
   TBranch        *b_triggerNumber;   //!

   CalibStatsReader(TTree * /*tree*/ =0) { }
   virtual ~CalibStatsReader() { }
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

   ClassDef(CalibStatsReader,0);
};

#endif

#ifdef CalibStatsReader_cxx
void CalibStatsReader::Init(TTree *tree)
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

   fChain->SetBranchAddress("clID", &clID, &b_Data_CalibStats_clID);
   fChain->SetBranchAddress("earliest.mSec", &earliest_mSec, &b_Data_CalibStats_earliest_mSec);
   fChain->SetBranchAddress("earliest.mNanoSec", &earliest_mNanoSec, &b_Data_CalibStats_earliest_mNanoSec);
   fChain->SetBranchAddress("latest.mSec", &latest_mSec, &b_Data_CalibStats_latest_mSec);
   fChain->SetBranchAddress("latest.mNanoSec", &latest_mNanoSec, &b_Data_CalibStats_latest_mNanoSec);
   fChain->SetBranchAddress("context.mSite", &context_mSite, &b_Data_CalibStats_context_mSite);
   fChain->SetBranchAddress("context.mSimFlag", &context_mSimFlag, &b_Data_CalibStats_context_mSimFlag);
   fChain->SetBranchAddress("context.mTimeStamp.mSec", &context_mTimeStamp_mSec, &b_Data_CalibStats_context_mTimeStamp_mSec);
   fChain->SetBranchAddress("context.mTimeStamp.mNanoSec", &context_mTimeStamp_mNanoSec, &b_Data_CalibStats_context_mTimeStamp_mNanoSec);
   fChain->SetBranchAddress("context.mDetId", &context_mDetId, &b_Data_CalibStats_context_mDetId);
   fChain->SetBranchAddress("execNumber", &execNumber, &b_Data_CalibStats_execNumber);
   fChain->SetBranchAddress("jobId.m_data[4]", jobId_m_data, &b_Data_CalibStats_jobId_m_data);
   fChain->SetBranchAddress("randomState", &randomState, &b_Data_CalibStats_randomState);
   fChain->SetBranchAddress("inputHeaders", &inputHeaders_, &b_Data_CalibStats_inputHeaders_);
   fChain->SetBranchAddress("inputHeaders.m_entry", inputHeaders_m_entry, &b_inputHeaders_m_entry);
   fChain->SetBranchAddress("inputHeaders.m_path", inputHeaders_m_path, &b_inputHeaders_m_path);
   fChain->SetBranchAddress("ColumnKurtosis", &ColumnKurtosis, &b_ColumnKurtosis);
   fChain->SetBranchAddress("Column_2inchPMT", &Column_2inchPMT, &b_Column_2inchPMT);
   fChain->SetBranchAddress("ELast_ADCalibShower_pe", &ELast_ADCalibShower_pe, &b_ELast_ADCalibShower_pe);
   fChain->SetBranchAddress("ELast_ADShower_pe", &ELast_ADShower_pe, &b_ELast_ADShower_pe);
   fChain->SetBranchAddress("EarlyCharge", &EarlyCharge, &b_EarlyCharge);
   fChain->SetBranchAddress("Kurtosis", &Kurtosis, &b_Kurtosis);
   fChain->SetBranchAddress("LateCharge", &LateCharge, &b_LateCharge);
   fChain->SetBranchAddress("MainPeakRMS", &MainPeakRMS, &b_MainPeakRMS);
   fChain->SetBranchAddress("MaxQ", &MaxQ, &b_MaxQ);
   fChain->SetBranchAddress("MaxQ_2inchPMT", &MaxQ_2inchPMT, &b_MaxQ_2inchPMT);
   fChain->SetBranchAddress("MiddleTimeRMS", &MiddleTimeRMS, &b_MiddleTimeRMS);
   fChain->SetBranchAddress("NominalCharge", &NominalCharge, &b_NominalCharge);
   fChain->SetBranchAddress("PeakRMS", &PeakRMS, &b_PeakRMS);
   fChain->SetBranchAddress("Q1", &Q1, &b_Q1);
   fChain->SetBranchAddress("Q2", &Q2, &b_Q2);
   fChain->SetBranchAddress("Q3", &Q3, &b_Q3);
   fChain->SetBranchAddress("Quadrant", &Quadrant, &b_Quadrant);
   fChain->SetBranchAddress("QuadrantQ1", &QuadrantQ1, &b_QuadrantQ1);
   fChain->SetBranchAddress("QuadrantQ2", &QuadrantQ2, &b_QuadrantQ2);
   fChain->SetBranchAddress("QuadrantQ3", &QuadrantQ3, &b_QuadrantQ3);
   fChain->SetBranchAddress("QuadrantQ4", &QuadrantQ4, &b_QuadrantQ4);
   fChain->SetBranchAddress("RingKurtosis", &RingKurtosis, &b_RingKurtosis);
   fChain->SetBranchAddress("SecondPeakRMS", &SecondPeakRMS, &b_SecondPeakRMS);
   fChain->SetBranchAddress("blocked_trigger", &blocked_trigger, &b_blocked_trigger);
   fChain->SetBranchAddress("buffer_full_flag", &buffer_full_flag, &b_buffer_full_flag);
   fChain->SetBranchAddress("charge_sum_flasher_max", &charge_sum_flasher_max, &b_charge_sum_flasher_max);
   fChain->SetBranchAddress("dtLastAD1_ms", &dtLastAD1_ms, &b_dtLastAD1_ms);
   fChain->SetBranchAddress("dtLastAD2_ms", &dtLastAD2_ms, &b_dtLastAD2_ms);
   fChain->SetBranchAddress("dtLastAD3_ms", &dtLastAD3_ms, &b_dtLastAD3_ms);
   fChain->SetBranchAddress("dtLastAD4_ms", &dtLastAD4_ms, &b_dtLastAD4_ms);
   fChain->SetBranchAddress("dtLastIWS_ms", &dtLastIWS_ms, &b_dtLastIWS_ms);
   fChain->SetBranchAddress("dtLastOWS_ms", &dtLastOWS_ms, &b_dtLastOWS_ms);
   fChain->SetBranchAddress("dtLastRPC_ms", &dtLastRPC_ms, &b_dtLastRPC_ms);
   fChain->SetBranchAddress("dtLast_ADCalibShower_ms", &dtLast_ADCalibShower_ms, &b_dtLast_ADCalibShower_ms);
   fChain->SetBranchAddress("dtLast_ADMuon_ms", &dtLast_ADMuon_ms, &b_dtLast_ADMuon_ms);
   fChain->SetBranchAddress("dtLast_ADShower_ms", &dtLast_ADShower_ms, &b_dtLast_ADShower_ms);
   fChain->SetBranchAddress("dtNextAD1_ms", &dtNextAD1_ms, &b_dtNextAD1_ms);
   fChain->SetBranchAddress("dtNextAD2_ms", &dtNextAD2_ms, &b_dtNextAD2_ms);
   fChain->SetBranchAddress("dtNextAD3_ms", &dtNextAD3_ms, &b_dtNextAD3_ms);
   fChain->SetBranchAddress("dtNextAD4_ms", &dtNextAD4_ms, &b_dtNextAD4_ms);
   fChain->SetBranchAddress("dtNextIWS_ms", &dtNextIWS_ms, &b_dtNextIWS_ms);
   fChain->SetBranchAddress("dtNextOWS_ms", &dtNextOWS_ms, &b_dtNextOWS_ms);
   fChain->SetBranchAddress("dtNextRPC_ms", &dtNextRPC_ms, &b_dtNextRPC_ms);
   fChain->SetBranchAddress("flasher_column", &flasher_column, &b_flasher_column);
   fChain->SetBranchAddress("flasher_flag", &flasher_flag, &b_flasher_flag);
   fChain->SetBranchAddress("flasher_ring", &flasher_ring, &b_flasher_ring);
   fChain->SetBranchAddress("integralLiveTime_blocked_trigger_ms", &integralLiveTime_blocked_trigger_ms, &b_integralLiveTime_blocked_trigger_ms);
   fChain->SetBranchAddress("integralLiveTime_buffer_full_ms", &integralLiveTime_buffer_full_ms, &b_integralLiveTime_buffer_full_ms);
   fChain->SetBranchAddress("integralRunTime_ms", &integralRunTime_ms, &b_integralRunTime_ms);
   fChain->SetBranchAddress("maxqCol", &maxqCol, &b_maxqCol);
   fChain->SetBranchAddress("maxqRing", &maxqRing, &b_maxqRing);
   fChain->SetBranchAddress("nCalibPESum", &nCalibPESum, &b_nCalibPESum);
   fChain->SetBranchAddress("nHit", &nHit, &b_nHit);
   fChain->SetBranchAddress("nPEMax", &nPEMax, &b_nPEMax);
   fChain->SetBranchAddress("nPEMedian", &nPEMedian, &b_nPEMedian);
   fChain->SetBranchAddress("nPERMS", &nPERMS, &b_nPERMS);
   fChain->SetBranchAddress("nPESum", &nPESum, &b_nPESum);
   fChain->SetBranchAddress("nPulseMedian", &nPulseMedian, &b_nPulseMedian);
   fChain->SetBranchAddress("nPulseRMS", &nPulseRMS, &b_nPulseRMS);
   fChain->SetBranchAddress("nPulseSum", &nPulseSum, &b_nPulseSum);
   fChain->SetBranchAddress("tEarliest", &tEarliest, &b_tEarliest);
   fChain->SetBranchAddress("tLatest", &tLatest, &b_tLatest);
   fChain->SetBranchAddress("tMean", &tMean, &b_tMean);
   fChain->SetBranchAddress("tMedian", &tMedian, &b_tMedian);
   fChain->SetBranchAddress("tRMS", &tRMS, &b_tRMS);
   fChain->SetBranchAddress("time_PSD", &time_PSD, &b_time_PSD);
   fChain->SetBranchAddress("time_PSD1", &time_PSD1, &b_time_PSD1);
   fChain->SetBranchAddress("time_PSD_local_RMS", &time_PSD_local_RMS, &b_time_PSD_local_RMS);
   fChain->SetBranchAddress("triggerNumber", &triggerNumber, &b_triggerNumber);
}

Bool_t CalibStatsReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef CalibStatsReader_cxx
