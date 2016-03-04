#include "Background/Background.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <math.h>
#include <iostream>
using namespace CLHEP;
using namespace std;

double Background::GetTotalEnt()
{
  if( RepeatPRL ) {
    return RePRL::Background[ m_AdNo-1 ];
  } else {
    return Spectrum::GetTotalEnt();
  }
}

int Background::AddBkg( Spectrum* BkgSpec )
{  
  for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
    double Current   = GetBinContent( BinIdx );
    double CurrErr   = GetBinError( BinIdx );
    double Increment = BkgSpec->GetBinContent( BinIdx );
    double IncreErr  = BkgSpec->GetBinError( BinIdx );
    SetBinContent( BinIdx, Current+Increment );
    SetBinError( BinIdx, sqrt(CurrErr*CurrErr+IncreErr*IncreErr) );
    //std::cout<< Current<<"+-"<<CurrErr<<"\t"<<Increment<<"+-"<<IncreErr<<"\t"<<GetBinError( BinIdx )<<std::endl;

  }

  m_TotalErrSqr += ( BkgSpec->GetTotalErr() * BkgSpec->GetTotalErr() );

  return 1;
}

double Background::GetTotalErr() {

  if( RepeatPRL ) {
    return RePRL::BkgrdError[ m_AdNo-1 ];
  } else {
    return sqrt( m_TotalErrSqr );
  }
}
