#include "Background.h"
#include "CLHEP/Units/SystemOfUnits.h"
using namespace CLHEP;


int Background::SetupBkg()
{
  for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
    SetBinContent( BinIdx, 0 );
  }

  return 1;
}
