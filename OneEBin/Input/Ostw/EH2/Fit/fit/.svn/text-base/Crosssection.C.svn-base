#include "Crosssection.h"
#include "InverseBetaCS.h"
#include "TF1.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "iostream"
using namespace CLHEP;

Crosssection* gCrosssection = new Crosssection;

int Crosssection::SetupCrosssection()
{
  TF1 * cf = new TF1("Crosssection",gSigmaTotal,0,20);
  double step = (Binning::EndEnergy - Binning::BeginEnergy)/Binning::NHistoBin;

  for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {

    double dgamma = cf->Integral( Binning::BeginEnergy + (BinIdx-1) * step + Phys::EnuToEprompt,
				  Binning::BeginEnergy +     BinIdx * step + Phys::EnuToEprompt) * 1e-42 * cm*cm;

    SetBinContent( BinIdx, dgamma );

  }

  return 1;
}
