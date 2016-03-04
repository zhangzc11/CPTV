#include "InverseBetaCS.h"
#include "stdio.h"

ClassImp(InverseBetaCS)

  ;

InverseBetaCS* gInverseBeta;

InverseBetaCS::InverseBetaCS() {
  fF = 1;
  fG = 1.26;
  fF2 = 3.706;
  fDelta = gkMassNeutron - gkMassProton;
  fMassEsq = gkMassElectron*gkMassElectron;
  fYsq = (fDelta*fDelta - fMassEsq)/2;
  fF2Plus3G2 = fF*fF + 3*fG*fG;
  fF2MinusG2 = fF*fF - fG*fG;
  fSigma0 = 0.0952/(fF2Plus3G2); // *10^{-42} cm^2, eqn 9
  fDifferential = new TF1("fDifferential",gDSigmaByDCosTheta, -1, 1, 1);
  fDifferential->SetParameter(0,3); // default enu = 3 MeV
  fHTotalCrossSection = NULL;
}

/// in the calculation of the cross section, this must be called first.
Double_t InverseBetaCS::Ee1(Double_t aEnu, Double_t aCosTheta) {
  Double_t answer;
  fE0 = Ee0(aEnu);
  if( fE0 <= gkMassElectron ) { // below threshold
    fE0 = 0;
    fP0 = 0;
    answer = 0;
  } else {
    fP0 = TMath::Sqrt(fE0*fE0 - fMassEsq);
    fV0 = fP0/fE0;
    Double_t sqBracket = 1 - aEnu*(1-fV0*aCosTheta)/gkMassProton;
    answer = fE0*sqBracket - fYsq/gkMassProton;
  }
  return answer;
}

Double_t InverseBetaCS::DSigDCosTh(Double_t aEnu, Double_t aCosTheta) {
  fE1 = Ee1(aEnu, aCosTheta);
  Double_t answer;
  if( fE1<gkMassElectron ) {
    answer = 0;
  } else {
    Double_t pe1 = TMath::Sqrt(fE1*fE1 - fMassEsq);
    Double_t ve1 = pe1/fE1;
    Double_t firstLine = (fSigma0/2) * (fF2Plus3G2 + fF2MinusG2*ve1*aCosTheta)* fE1*pe1;
    Double_t secondLine = fSigma0 * GammaTerm(aCosTheta) * fE0 * fP0 / (2* gkMassProton); 
    answer = firstLine - secondLine;
  }
  return answer;
}

Double_t InverseBetaCS::GammaTerm(Double_t aCosTheta) {
  Double_t firstLine = (2*fE0+fDelta)*(1-fV0*aCosTheta)-fMassEsq/fE0;
  firstLine *= (2*(fF+fF2)*fG);
  Double_t secondLine = fDelta*(1+fV0*aCosTheta) +fMassEsq/fE0;
  secondLine *= (fF*fF+fG*fG);
  Double_t thirdLine = fF2Plus3G2 *( (fE0+fDelta)*(1-aCosTheta/fV0) - fDelta);
  Double_t fourthLine = (fF*fF - fG*fG)*fV0*aCosTheta;
  fourthLine *= ( (fE0+fDelta)*(1-aCosTheta/fV0) - fDelta );

  Double_t answer = firstLine + secondLine + thirdLine + fourthLine;
  return answer;

}

Double_t InverseBetaCS::SigmaTot(Double_t aEnu) {
  //  fDifferential->SetParameter(0, aEnu);
  Double_t answer;
  if( aEnu<0 ) {
    Warning("SigmaTot(Double_t aEnu)","Tried to calculate cross section for -ve nu energy");
    return 0;
  }
  if( aEnu>10 ) {
    // table on precalculated to 10 MeV
    answer = fDifferential->Integral(-1.0, 1.0, &aEnu, 1e-9);
    return answer;
  }
  if( fHTotalCrossSection==NULL ) setupTotalCrossSection();
  int bin = fHTotalCrossSection->FindBin(aEnu);
  Double_t answer1 =  fHTotalCrossSection->GetBinContent(bin);
  Double_t e1 = fHTotalCrossSection->GetBinCenter(bin);
  Double_t answer2, e2;
  if( bin!=1000 ) {
    answer2 =  fHTotalCrossSection->GetBinContent(bin+1);
    e2 = fHTotalCrossSection->GetBinCenter(bin+1);
  } else {
    answer2 =  fHTotalCrossSection->GetBinContent(bin-1);
    e2 = fHTotalCrossSection->GetBinCenter(bin-1);
  }
  answer = answer1 + (answer2-answer1)*( aEnu-e1)/(e2-e1); // answer1 + slope correction
  return answer;
}

void InverseBetaCS::setupTotalCrossSection() {
  fHTotalCrossSection = new TH1D("htotalCross","Total #nu (p,n) e Cross Section", 1000, 0, 10);
  Double_t enu;
  for( int i=1 ; i<=1000 ; i++ ) {
    enu = fHTotalCrossSection->GetBinCenter(i);
    fHTotalCrossSection->SetBinContent(i, fDifferential->Integral(-1.0, 1.0, &enu, 1e-9) );

  }
}


/// takes given prompt energy and turns it into a neutrino energy
/// inverts eqn 11
Double_t InverseBetaCS::PromptEnergyToNeutrinoEnergy(Double_t aE_prompt) {
  Double_t ePos = aE_prompt - gkMassElectron; // paper uses total E so only
  // subtract one mass
  Double_t a = -1/(gkMassProton);
  Double_t b = 1+fDelta/gkMassProton;
  Double_t c = -fYsq/gkMassProton - ePos - fDelta;
  Double_t answer1 = ( -b + sqrt(b*b-4*a*c) )/(2*a);
  Double_t answer2 = ( -b - sqrt(b*b-4*a*c) )/(2*a);
  //  printf("%e\t%e\t%e\t%e\t%e\n", aE_prompt, ePos, answer1, answer2, ePos+fDelta);
  return answer1;
}

///global function to allow calls from a TF1.
///This is necessary to use the gaussian quadrature method 
///built into TF1
/// dsig/dcos(theta)
Double_t gDSigmaByDCosTheta(Double_t* x, Double_t*a) {
  Double_t cosTheta = x[0];
  Double_t enu = a[0];
  if( gInverseBeta==NULL ) gInverseBeta = new InverseBetaCS();
  return gInverseBeta->DSigDCosTh(enu, cosTheta);

}


//a global function to allow the total cross section call be put into a TF1
// a redirect to InverseBetaCS::SigmaTot()
Double_t gSigmaTotal(Double_t* x, Double_t*a) {
  // a not used
  // x[0] = neutrino energy (MeV)
  if( gInverseBeta==NULL ) gInverseBeta = new InverseBetaCS();
  return gInverseBeta->SigmaTot(x[0]);
}

