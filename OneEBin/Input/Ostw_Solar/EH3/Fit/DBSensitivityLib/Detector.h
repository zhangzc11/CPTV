#ifndef Detector_h
#define Detector_h

#include "TROOT.h"
#include "TObject.h"
#include "TNamed.h"
#include "TGraph.h"
#include "TSystem.h"
#include "TFile.h"
#include "TList.h"
#include "TCanvas.h"
#include <iostream>
#include <string>
#include <vector>
#include "ReactorCore.h"
#include "InverseBetaCS.h"
#include "MixingMatrix.h"

using namespace std;

class Detector:public TNamed {
  public :
    Detector(const char *name="det");
    ~Detector();
    
    void AddCore(ReactorCore *Core, Double_t distance, Double_t time);//distance in meters, time in years
    
    void BuilddFluxdE(bool oscillated, bool useexpected);
    void BuildFlux(bool oscillated, bool useexpected);
    void BuildCrossSection();
    void BuildSpectrum(bool useexpected);
    void BuildLi9Spectrum();//use input root file
    void BuildFastNeutronSpectrum();//exactly flat
    void BuildAccidentalSpectrum();//use exponential
    
    void DrawdFluxdE(bool oscillated);
    void DrawFlux(bool oscillated);
    void DrawCrossSection();
    
    void SetSigma_d(Double_t sigma);
    void SetSigma_f(Double_t sigma);
    void SetSigma_n(Double_t sigma);
    void SetSigma_s(Double_t sigma);
    void SetSinSq2Theta13(Double_t sinsq2theta13);
    void SetDeltaMSq31(Double_t deltamsq31);
    void SetNtargetnuclei(Double_t n);
    void SetEfficiency(Double_t eff);
    void SetEnergyRes(Double_t eres);
    void SetSigtoBkgd_Li9(Double_t s2b);
    void SetSigtoBkgd_Fast(Double_t s2b);
    void SetSigtoBkgd_Acc(Double_t s2b);
    void SetTrueSpectrum(Bool_t set);
    void SetMeasSpectrum(Bool_t set);
    
    Int_t GetNCores();
    Double_t GetCoreWeight(Int_t core);
    Double_t GetCoreDistance(Int_t core);
    Double_t GetCoreTime(Int_t core);
    Double_t GetSigma_d();
    Double_t GetSigma_f();
    Double_t GetSigma_n();
    Double_t GetSigma_s();
    Double_t GetSinSq2Theta13();
    Double_t GetDeltaMSq31();
    Double_t GetNtargetnuclei();
    Double_t GetEfficiency();
    Double_t GetEnergyRes();
    Double_t GetSigtoBkgd_Li9();
    Double_t GetSigtoBkgd_Fast();
    Double_t GetSigtoBkgd_Acc();
    Int_t GetNBins();
    Double_t GetBinWidth();
    
    TH1D *EnuSpectrum;//neutrino energy spectrum for given set of oscillation parameters
    TH1D *PromptSpectrum;//prompt energy spectrum for given set of oscillation parameters
    TH1D *Li9Bkgd;
    TH1D *FastNeutronBkgd;
    TH1D *AccidentalBkgd;
    
    TList *fCores;
    
  private :
    void BuildERes(Double_t energy);
    
    Int_t fNCores;//number of reactor cores
    vector<Double_t> fCoreWeight;//fraction of neutrino flux from each core
    vector<Double_t> fCoreDistance;//distance to each core in m
    vector<Double_t> fCoreTime;//time of exposure to core in seconds
    
    Double_t fSigma_d;//detector-related uncorrelated uncertainty
    Double_t fSigma_f;//fast neutron background rate uncertainty
    Double_t fSigma_n;//accidental background rate uncertainty
    Double_t fSigma_s;//He8/Li9 background rate uncertainty
    
    Double_t fSsq2T13;
    Double_t fDMsq31;
    
    Double_t fNtargetnuclei;
    
    Double_t fEfficiency;
    
    Double_t fEnergyRes;
    
    Int_t fNbins;
    Double_t fEnuMax;
    
    Double_t fSecinYear;
    
    MixingMatrix *gMixingMatrix;
    
    vector<Double_t> Enu;
    vector<Double_t> dFlux;
    vector<Double_t> XSec;
    
    Bool_t fXSec;
    Bool_t fSpec;
    Bool_t fLi9;
    Bool_t fFast;
    Bool_t fAcc;
    
    TH1D *Flux;
    
    Double_t fS2B_Li9;
    Double_t fS2B_Fast;
    Double_t fS2B_Acc;
    
    TH1D *TempHist;
    TH1D *ERes;
    
  ClassDef(Detector,1)
};

#endif

//note: there's no way to 'remove' a core once it's been added
