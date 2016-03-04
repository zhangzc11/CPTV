//this class mostly borrowed from Chris Jillings with a few changes and additions

#ifndef __MixingMatrix__H__
#define __MixingMatrix__H__

#include "TMath.h"
#include "TObject.h"
#include <iostream>

using namespace std;


const Int_t gNormalHierarchy = 1;
const Int_t gInvertedHierarchy = 2;



class MixingMatrix{
private:
  Double_t fTheta_12;     // internally stored in radians
  Double_t fTheta_13;     // internally stored in radians
  Double_t fTheta_23;     // internally stored in radians
  Double_t fDeltaM2_21;   // eV^2
  Double_t fDeltaM2_32;   // eV^2
  Double_t fDeltaM2_31;   // eV^2
  Int_t fHierarchy;       // 1 = normal; 2 = inverted


  // Some utility variables.
  Double_t fC4Th13;
  Double_t fC2Th12;
  Double_t fSSq2Th12;
  Double_t fS2Th12;
  Double_t fSSq2Th13;


public:
  
  MixingMatrix();//defaults to values in TDR but with theta13=0
  ~MixingMatrix();
  
  Double_t SurvivalProb(Double_t aEnergyMeV, Double_t aLengthMeters);
  void NoOsc(); // turns off mixing


  void SetTheta12Radians(Double_t aTheta12);
  void SetTheta12Degrees(Double_t aTheta12)  { SetTheta12Radians(aTheta12*TMath::DegToRad() ); }
  void SetSin2_2Theta12(Double_t aX) { SetTheta12Radians( 0.5*TMath::ASin( TMath::Sqrt(aX) ) ); }

  void SetTheta13Radians(Double_t aTheta13);
  void SetTheta13Degrees(Double_t aTheta13)  { SetTheta13Radians(aTheta13*TMath::DegToRad() ); }
  void SetSin2_2Theta13(Double_t aX) { SetTheta13Radians( 0.5*TMath::ASin( TMath::Sqrt(aX) ) ); }

  void SetTheta23Radians(Double_t aTheta23) { fTheta_23 = aTheta23; }
  void SetTheta23Degrees(Double_t aTheta23)  { SetTheta23Radians(aTheta23*TMath::DegToRad() ); }
  void SetSin2_2Theta23(Double_t aX) { SetTheta23Radians( 0.5*TMath::ASin( TMath::Sqrt(aX) ) ); }

  void SetDM2_21_31(Double_t dm2_21,Double_t absval_dm2_31);
  void SetDM2_21_32(Double_t dm2_21,Double_t absval_dm2_32);
  void SetDM2_31_32(Double_t absval_dm2_31,Double_t absval_dm2_32);
  void SetDM2_31(Double_t dm2_31);

  void SetHierarchy(Int_t aHierarchy);

  void SetupDefault();
  
  Double_t GetDeltaM2_21();
  Double_t GetDeltaM2_31();
  Double_t GetDeltaM2_32();
  Double_t GetTheta_12_Rad();
  Double_t GetTheta_13_Rad();
  Double_t GetTheta_23_Rad();
  Double_t GetTheta_12_Deg();
  Double_t GetTheta_13_Deg();
  Double_t GetTheta_23_Deg();

};



#endif
