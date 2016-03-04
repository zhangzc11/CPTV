#ifndef ReactorCore_h
#define ReactorCore_h

#include "TROOT.h"
#include "TObject.h"
#include "TF1.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ReactorCore:public TObject {
  public :
    ReactorCore();
    ~ReactorCore();
    
    void BuilddNdE();
    
    void SetFractions(Double_t frac_U235,Double_t frac_U238,Double_t frac_Pu239,Double_t frac_Pu241);
    void SetVEFluxPars(string isotope, Double_t fpar[3]);
    void SetHSFluxPars(string isotope, Double_t fpar[5]);
    void SetModel(string model);
    void SetExpectedPower(Double_t power);
    void SetActualPower(Double_t power);
    void SetFissionsPerSecondGW(Double_t f);
    void SetSigma_r(Double_t sigma);
    
    Double_t GetFraction(string isotope);
    Double_t GetVEFluxPars(string isotope,Int_t parno);
    Double_t GetHSFluxPars(string isotope,Int_t parno);
    void PrintModel();
    Double_t GetExpectedPower();
    Double_t GetActualPower();
    Double_t GetFissionsPerSecondGW();
    Double_t GetSigma_r();
    
    TF1 *dNdE_Expected;
    TF1 *dNdE_Actual;
    
  private :
    
    Double_t fFractionU235;
    Double_t fFractionU238;
    Double_t fFractionPu239;
    Double_t fFractionPu241;
    
    Double_t fVEFluxParU235[3];
    Double_t fVEFluxParU238[3];
    Double_t fVEFluxParPu239[3];
    Double_t fVEFluxParPu241[3];
    
    Double_t fHSFluxParU235[6];
    Double_t fHSFluxParU238[6];
    Double_t fHSFluxParPu239[6];
    Double_t fHSFluxParPu241[6];
    
    string fModel;
    
    Double_t fExpectedPower;
    Double_t fActualPower;
    
    Double_t fFissionspersecondGW;
    
    Double_t fSigma_r;//reactor-related uncorrelated uncertainty for this core
    
    
  ClassDef(ReactorCore,1)
};



#endif
