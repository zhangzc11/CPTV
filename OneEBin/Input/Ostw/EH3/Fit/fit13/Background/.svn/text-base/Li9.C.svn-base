#include "Li9.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "AnalyzeData.h"
#include "Constants.h"
#include "AdMap.h"
#include <math.h>
#include <iostream>
using namespace CLHEP;
using namespace std;

double Li9::shape(double energy) // return entries in 0.1 MeV bin;  
{
  double entry;
  
  if( m_dataset == Dataset::HCap ) {
    double p0 = 0.00849202;    
    double p1 = -0.0023184; 
    double p2 = 0.00158047; 
    double p3 = -0.000227924; 
    double p4 = 8.99263e-06; 
  
    entry = p0+p1*energy+p2*pow(energy,2)+p3*pow(energy,3)+p4*pow(energy,4);
    entry = entry/0.993;
  }

  if( m_dataset == Dataset::GdCap ) {
    double p0 =   -0.0181603;
    double p1 =    0.0507968;
    double p2 =   -0.0386139;
    double p3 =    0.0152854;
    double p4 =  -0.00340626;
    double p5 =  0.000446699;
    double p6 = -3.43744e-05;
    double p7 =  1.43861e-06;
    double p8 = -2.52829e-08;

    entry = 
      p0+p1*energy+p2*pow(energy,2)+p3*pow(energy,3)+p4*pow(energy,4)
      +p5*pow(energy,5)+p6*pow(energy,6)+p7*pow(energy,7)
      +p8*pow(energy,8);
  }
  
  return entry;
}

int Li9::SetupBkg()
{
  /* No shape so far */
  int site = ToSite( m_AdNo );
  /* 1,2,4 -> 0,1,2 */
  if(site==4) site=3;
  site=site-1;

  double totalNumber = 
    Li9Bkg::Daily_Yield[m_dataset][site]
    * gAnalyzeData->Livetime(m_dataset,m_AdNo)/24/60/60 
    * gAnalyzeData->OstwEff(m_dataset,m_AdNo);

  double error =
    Li9Bkg::Daily_Yield_Err[m_dataset][site]
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
