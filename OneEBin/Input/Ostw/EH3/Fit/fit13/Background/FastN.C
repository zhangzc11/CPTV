#include "FastN.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "AnalyzeData.h"
#include "Constants.h"
#include "AdMap.h"
#include <iostream>
#include <math.h>
using namespace CLHEP;
using namespace std;

double FastN::shape(double energy) // return entries in 0.1 MeV bin;
{
  double entry;

  if( m_dataset == Dataset::HCap ) {
    entry = 0.0102132 * (1- 0.01*energy) /0.9904;
  }

  if( m_dataset == Dataset::GdCap ) {
    entry = 8.84955752212389368e-03;  // 1/113
  }

  return entry;
}

int FastN::SetupBkg()
{
  /* No shape so far */
  int site = ToSite( m_AdNo );
  /* 1,2,4 -> 0,1,2 */
  if(site==4) site=3;
  site=site-1;

  //int Nbins = Binning::NHistoBin;
  double totalNumber = FastNBkg::DailyRate[m_dataset][m_AdNo-1]
    * gAnalyzeData->Livetime( m_dataset, m_AdNo )/(24*60*60) 
    * gAnalyzeData->OstwEff( m_dataset, m_AdNo ) ; /* OstwEff */

  double error = FastNBkg::DailyRateErr[m_dataset][m_AdNo-1]
    * gAnalyzeData->Livetime( m_dataset, m_AdNo )/(24*60*60)
    * gAnalyzeData->OstwEff( m_dataset, m_AdNo ) ;

  // set bin entries and errors
  for( int bin=1; bin<Binning::NHistoBin; bin++ ) {
    double entry, err;
    if( (m_dataset == Dataset::GdCap && bin<8)
        ||
        (m_dataset == Dataset::HCap && bin<16)
        ) {
      entry=0;
      err=0;
    } else {
      entry = shape( bin*0.1 ) * totalNumber;
    }

    err = sqrt(error/totalNumber * entry);

    SetBinContent( bin, entry );
    SetBinError( bin, err );
  }

  m_TotalErr = error;

  return 1;
}
