#include "MixingMatrix.h"

MixingMatrix::MixingMatrix() {
  fHierarchy = gNormalHierarchy;
  SetupDefault();
}

MixingMatrix::~MixingMatrix() {
}

Double_t MixingMatrix::SurvivalProb(Double_t aEnergyMeV, Double_t aLengthMeters) {
  
  Double_t E = aEnergyMeV;
  Double_t L = aLengthMeters;

  Double_t firstSineTerm = TMath::Sin(1.267*fDeltaM2_21*L/E);
  Double_t firstTerm = fC4Th13 * fSSq2Th12 * firstSineTerm* firstSineTerm;

  Double_t secondSineTerm = TMath::Sin(1.267*fDeltaM2_31*L/E);
  Double_t secondTerm = fC2Th12* fSSq2Th13 * secondSineTerm* secondSineTerm;
    
  Double_t thirdSineTerm = TMath::Sin( 1.267*fDeltaM2_32*L/E );
  Double_t thirdTerm = fS2Th12* fSSq2Th13 * thirdSineTerm* thirdSineTerm;

  return (1 - firstTerm - secondTerm - thirdTerm ); 
}

void MixingMatrix::SetTheta12Radians(Double_t aX) {
  fTheta_12 = aX;

  fS2Th12 = TMath::Sin(aX); 
  fS2Th12 *= fS2Th12;

  fSSq2Th12 = TMath::Sin(2*aX); 
  fSSq2Th12 *= fSSq2Th12;

  fC2Th12 = TMath::Cos(aX);
  fC2Th12 *= fC2Th12;
}

void MixingMatrix::SetTheta13Radians(Double_t aX) {
  fTheta_13 = aX;

  fSSq2Th13 = TMath::Sin(2*aX); 
  fSSq2Th13 *= fSSq2Th13;

  fC4Th13 = TMath::Cos(aX);
  fC4Th13 *= fC4Th13;
  fC4Th13 *= fC4Th13;  // yes, twice (fourth power)
}

void MixingMatrix::SetDM2_21_31(Double_t dm2_21,Double_t absval_dm2_31)
{
  if(fHierarchy==gNormalHierarchy)
  {
    fDeltaM2_21 = dm2_21;
    fDeltaM2_31 = absval_dm2_31;
    fDeltaM2_32 = fDeltaM2_31-fDeltaM2_21;
  }
  else if(fHierarchy==gInvertedHierarchy)
  {
    fDeltaM2_21 = dm2_21;
    fDeltaM2_31 = -1.*absval_dm2_31;
    fDeltaM2_32 = fDeltaM2_31-fDeltaM2_21;
  }
  
  return;
}
void MixingMatrix::SetDM2_21_32(Double_t dm2_21,Double_t absval_dm2_32)
{
  if(fHierarchy==gNormalHierarchy)
  {
    fDeltaM2_21 = dm2_21;
    fDeltaM2_32 = absval_dm2_32;
    fDeltaM2_31 = fDeltaM2_32+fDeltaM2_21;
  }
  else if(fHierarchy==gInvertedHierarchy)
  {
    fDeltaM2_21 = dm2_21;
    fDeltaM2_32 = -1.*absval_dm2_32;
    fDeltaM2_31 = fDeltaM2_32+fDeltaM2_21;
  }
  
  return;
}
void MixingMatrix::SetDM2_31_32(Double_t absval_dm2_31,Double_t absval_dm2_32)
{
  if(fHierarchy==gNormalHierarchy)
  {
    fDeltaM2_31 = absval_dm2_31;
    fDeltaM2_32 = absval_dm2_32;
    fDeltaM2_21 = fDeltaM2_31-fDeltaM2_32;
  }
  else if(fHierarchy==gInvertedHierarchy)
  {
    fDeltaM2_31 = -1.*absval_dm2_31;
    fDeltaM2_32 = -1.*absval_dm2_32;
    fDeltaM2_21 = fDeltaM2_31-fDeltaM2_32;
  }
  
  return;
}
void MixingMatrix::SetDM2_31(Double_t dm2_31)
{
  fDeltaM2_31 = dm2_31;
  return;
}
void MixingMatrix::SetHierarchy(Int_t aH)
{
  fHierarchy = aH;

  return;
}

void MixingMatrix::SetupDefault() {
  fHierarchy = gNormalHierarchy;
  SetDM2_21_32(7.92e-5,2.4e-3);//numbers taken from TDR
  SetTheta12Degrees(34.08);
  SetTheta23Degrees(41.55);
  SetTheta13Degrees(0.0);
}



void MixingMatrix::NoOsc() {
  SetTheta12Radians(0);
  SetTheta13Radians(0);
  SetTheta23Radians(0);
}

Double_t MixingMatrix::GetDeltaM2_21()
{
  return fDeltaM2_21;
}
Double_t MixingMatrix::GetDeltaM2_31()
{
  return fDeltaM2_31;
}
Double_t MixingMatrix::GetDeltaM2_32()
{
  return fDeltaM2_32;
}
Double_t MixingMatrix::GetTheta_12_Rad()
{
  return fTheta_12;
}
Double_t MixingMatrix::GetTheta_13_Rad()
{
  return fTheta_13;
}
Double_t MixingMatrix::GetTheta_23_Rad()
{
  return fTheta_23;
}
Double_t MixingMatrix::GetTheta_12_Deg()
{
  return fTheta_12*TMath::RadToDeg();
}
Double_t MixingMatrix::GetTheta_13_Deg()
{
  return fTheta_13*TMath::RadToDeg();
}
Double_t MixingMatrix::GetTheta_23_Deg()
{
  return fTheta_23*TMath::RadToDeg();
}
