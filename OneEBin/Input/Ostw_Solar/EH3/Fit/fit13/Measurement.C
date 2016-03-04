#include "Measurement.h"
#include "AnalyzeData.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "AdMap.h"
#include "Tool/Tool.h"
#include "TFile.h"
#include <math.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace CLHEP;
using namespace std;

double Measurement::GetTotalEnt()
{
  if( RepeatPRL ) {
    return RePRL::NCandidate[ m_AdNo-1 ];
  } else {
    return Spectrum::GetTotalEnt();
  }
}
  
int Measurement::SetupMeas()
{
  const std::vector< RunBrief* > Runs = gAnalyzeData->GetRuns();

  int Site = ToSite( m_AdNo );
  int LocalAdNo = ToLocalAdNo( m_AdNo );
  for( std::vector< RunBrief* >::const_iterator iRun = Runs.begin();
       iRun!=Runs.end(); iRun++ ) {
    
    const RunBrief* const Brief = (*iRun);

    if( Brief->Dataset != m_dataset ) continue;
    if( Brief->Site != Site ) continue;

    Add( this, Brief->h1dVtx[ LocalAdNo-1 ] );
  }

  m_TotalErr=0;
  for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
    m_TotalErr += pow( GetBinError( BinIdx ), 2 );
  }

  m_TotalErr = sqrt(m_TotalErr);

  return 1;
}
