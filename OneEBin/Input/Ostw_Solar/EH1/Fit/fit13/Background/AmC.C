#include "AmC.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "AnalyzeData.h"
#include "Constants.h"
#include "AdMap.h"
#include <math.h>
#include <iostream>
using namespace CLHEP;
using namespace std;

double AmC::shape(double energy) // return entries in 0.1 MeV bin;
{
  double entry;

  if( m_dataset == Dataset::HCap ) {
    double lambda = 0.643;
    double c = 1/(exp(-lambda*1.5) - exp(-lambda*12));
    entry = 0.1 * c * lambda * exp( -lambda * energy );
  }

  if( m_dataset == Dataset::GdCap ) {
    double lambda = 0.98;
    double c = 1/(exp(-lambda*0.7) - exp(-lambda*12));
    entry = 0.1 * c * lambda * exp( -lambda * energy );
  }

  return entry;
}

int AmC::SetupBkg()
{
  /* No shape so far */
  int site = ToSite( m_AdNo );
  /* 1,2,4 -> 0,1,2 */
  if(site==4) site=3;
  site=site-1;

  double totalNumber = 
    AmCBkg::Daily_Yield[m_dataset][site]
    * gAnalyzeData->Livetime(m_dataset,m_AdNo)/24/60/60 
    * gAnalyzeData->OstwEff(m_dataset,m_AdNo);
  
  double error = 
    AmCBkg::Daily_Yield_Err[m_dataset][site]
    * gAnalyzeData->Livetime(m_dataset,m_AdNo)/24/60/60
    * gAnalyzeData->OstwEff(m_dataset,m_AdNo);

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
