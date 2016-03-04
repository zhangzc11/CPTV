#include "Background/Background.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <math.h>
#include <iostream>
using namespace CLHEP;

double Background::Integral()
{
  if( RepeatPRL ) {
    return RePRL::Background[ m_AdNo-1 ];
  } else {
    return Spectrum::Integral();
  }
}

int Background::AddBkg( TH1F* BkgSpec )
{  
  for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
    double Current   = GetBinContent( BinIdx );
    double CurrErr   = GetBinError( BinIdx );
    double Increment = BkgSpec->GetBinContent( BinIdx );
    double IncreErr  = BkgSpec->GetBinError( BinIdx );
    SetBinContent( BinIdx, Current+Increment );
    SetBinError( BinIdx, sqrt(CurrErr*CurrErr+IncreErr*IncreErr) );
    //std::cout<< Current<<"+-"<<CurrErr<<"\t"<<Increment<<"+-"<<IncreErr<<"\t"<<GetBinError( BinIdx )<<std::endl;

    m_TotalErrSqr += IncreErr*IncreErr;
  }

  return 1;
}

double Background::GetTotalErr() {

  if( RepeatPRL ) {
    return RePRL::BkgrdError[ m_AdNo-1 ];
  } else {
    return sqrt( m_TotalErrSqr );
  }
}
