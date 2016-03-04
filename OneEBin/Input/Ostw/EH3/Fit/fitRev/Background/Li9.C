#include "Li9.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "AnalyzeData.h"
#include "Constants.h"
#include "AdMap.h"
#include <iostream>
using namespace CLHEP;
using namespace std;

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
  
  SetBinContent( 1, totalNumber );

  return 1;
}
