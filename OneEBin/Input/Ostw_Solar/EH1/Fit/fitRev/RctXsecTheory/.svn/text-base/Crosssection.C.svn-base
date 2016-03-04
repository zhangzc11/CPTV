/*
  Unit: cm*cm
*/
#include "Crosssection.h"
#include "InverseBetaCS.h"
#include "TF1.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "iostream"
using namespace CLHEP;

Crosssection* gCrosssection = new Crosssection;

int Crosssection::SetupCrosssection()
{
  //TF1 * cf = new TF1("Crosssection", gSigmaTotal, 0, 20);
  double step = (Binning::EndEnergy - Binning::BeginEnergy)/Binning::NPreciseBin;

  for( unsigned int BinIdx = 1; BinIdx <= Binning::NPreciseBin; BinIdx++ )  {
    
    //double dgamma = cf->Integral( Binning::BeginEnergy + (BinIdx-1) * step,
    //				  Binning::BeginEnergy +     BinIdx * step ) * 1e-42 * cm*cm;

    double Enu[1], dummy[1];
    Enu[0] = Binning::BeginEnergy + (BinIdx-1) * step;
    double cross = gSigmaTotal( Enu, dummy ) * 1e-42;
    SetBinContent( BinIdx, cross );

  }

  return 1;
}
