#ifndef Experiment_h
#define Experiment_h

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "TROOT.h"
#include "TObject.h"
#include "TString.h"
#include "TH1D.h"
#include "TMinuit.h"
#include "TCanvas.h"
#include "TGraph2D.h"
#include "TGraph.h"
#include "TList.h"
#include "ReactorCore.h"
#include "InverseBetaCS.h"
#include "MixingMatrix.h"
#include "Detector.h"

using namespace std;


class Experiment:public TObject {
  public :
    Experiment();
    ~Experiment();
    
    void SetNPar();
    void AddDetector(Detector *Det);
    void SetupTrueSpectrum();
    void SetupSpectrums();
    void DrawSpectrums(Bool_t save);
    Double_t Minimize();
    void MakeSensitivityPlot(Double_t guess,char *filename);
    Double_t GetSensitivityAt(Double_t deltamsq31 = 2.5e-3,Double_t guess = 0.008);
    
    void SetSigma_c(Double_t sigma);
    void SetSigma_shape(Double_t sigma);
    void SetSigma_D(Double_t sigma);
    void SetSigma_b2b(Double_t sigma);
    
    void SetSinSq2Theta13(Double_t sinsq2theta13);
    void SetDeltaMSq31(Double_t deltamsq31);
    void SetTrueSinSq2Theta13(Double_t truesinsq2theta13);
    void SetTrueDeltaMSq31(Double_t truedeltamsq31);
    
    void SetPrintFit(bool printfit);
    
    void SetNBins(Int_t bins = 28);//set the desired number of bins between 1 and 8 MeV.  this will only set the number of bins to an allowed number, which is determined by the bin width of the input distributions from Detector
    
    Int_t GetNDetectors();
    Int_t GetNBins();
    Bool_t BinInFit(Int_t bin);
    Double_t GetSigma_c();
    Double_t GetSigma_shape();
    Double_t GetSigma_D();
    Double_t GetSigma_b2b();
    Int_t GetNPar();
    Double_t GetSinSq2Theta13();
    Double_t GetDeltaMSq31();
    
    Int_t alpha_c();
    Int_t alpha_r(Int_t core);
    Int_t beta(Int_t bin);
    Int_t epsilon_D();
    Int_t epsilon_d(Int_t det);
    Int_t eta_f(Int_t det);
    Int_t eta_n(Int_t det);
    Int_t eta_s(Int_t det);
    
    TList *fDetectors;
    
    vector<vector<Double_t> > Measured;
    vector<vector<Double_t> > True;
    vector<vector<Double_t> > Li9;
    vector<vector<Double_t> > FastNeutron;
    vector<vector<Double_t> > Accidental;
    
  private :
    Int_t fNDetectors;//number of antineutrino detectors
    
    Int_t fNBins;//number of energy bins
    vector<Bool_t> fBin;
    Int_t fNPar;//number of parameters in the fit (depends on number of reactors and number of detectors)
    vector<Double_t> fEdges;
    Int_t alpha_c_parno;
    vector<Int_t> alpha_r_parno;
    vector<Int_t> beta_parno;
    Int_t epsilon_D_parno;
    vector<Int_t> epsilon_d_parno;
    vector<Int_t> eta_f_parno;
    vector<Int_t> eta_n_parno;
    vector<Int_t> eta_s_parno;
    vector<string> fParNames;
    
    Double_t fSigma_c;//reactor-related correlated uncertainty
    Double_t fSigma_shape;//spectrum shape uncertainty
    Double_t fSigma_D;//detector-related correlated uncertainty
    Double_t fSigma_b2b;//bin to bin uncertainty
    
    Double_t ffSsq2T13;
    Double_t ffDMsq31;
    
    Double_t fTrueSsq2T13;//true value of sin^2(2theta13)
    Double_t fTrueDMsq31;//true value of delta m^2_{31}
    
    Bool_t fSetup;
    
    Bool_t fPrintFit;
    
  ClassDef(Experiment,1)
};

#endif

//note: there's no way to 'remove' a detector once it's been added
//note: if you have called SetupSpectrums or any function that uses it, the spectrums will not be reset unless you add a new detector.  this means you can't e.g. DrawSpectrums(), then change some detector parameter and DrawSpectrums() again to see the effect of the change.
//note: sensitivity calculation assumes that all detectors are exposed to flux from all cores (it actually uses the cores from Detector(0)).  if you want to set up a problem such that detector 1 gets neutrinos from reactor A and B, while detector 2 gets neutrinos only from reactor A, you should add both A and B to both detectors, but set detector 2's exposure time for reactor B to 0.
