#include "Acc.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "AnalyzeData.h"
#include "Constants.h"
#include "AdMap.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace CLHEP;
using namespace std;

int Acc::SetupBkg()
{
  const vector< RunBrief* > Runs = gAnalyzeData->GetRuns();

  int site = ToSite( m_AdNo );
  int localAd = ToLocalAdNo( m_AdNo );

  double ScaleE;
  if( site==1 ) ScaleE = AccBkg::ScaleE[0];
  if( site==2 ) ScaleE = AccBkg::ScaleE[1];
  if( site==4 ) ScaleE = AccBkg::ScaleE[2];

  m_TotalErr=0;

  /// Loop over all runs and find the run for this site and data set
  for( vector< RunBrief* >::const_iterator iRun = Runs.begin();
       iRun!=Runs.end(); iRun++ ) {
    
    const RunBrief* const Brief = (*iRun);
    int Dataset = Brief->Dataset;

    if( site == Brief->Site ) {
      if( m_dataset == Dataset ) {
	//Add( Brief->h1dAccBkg[ localAd-1 ] );
	TH1F* h = Brief->h1dAccBkg[ localAd-1 ];
	
	int nDataBin = h->GetNbinsX();
	//  cout<< nDataBin <<" vs "<< Binning::NHistoBin <<endl;
	if( nDataBin%Binning::NHistoBin != 0) {
	  cout<<"Error,    Measurement: BinNumberData can't be divided by BinInternal exactly."<<endl;
	  exit(0);
	}
	int ratio = nDataBin/Binning::NHistoBin; /* This must be an interger */

	for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ ) {
	  double content = 0;
	  double error = 0;
	  unsigned int low, high;
	  low  = (BinIdx-1)*ratio+1;
	  high = (BinIdx-1)*ratio+ratio;
	  for( unsigned int myidx = low; myidx<=high; myidx++ ) {
	    double singleCnt = h->GetBinContent(myidx);
	    content += singleCnt;	    
	    double singleErr = h->GetBinError(myidx);
	    singleErr = sqrt(singleErr*singleErr - singleCnt*ScaleE*singleCnt*ScaleE);
	    error   += pow( singleErr, 2 );
	  }
	  
	  double LastValue  = GetBinContent( BinIdx );
	  double LastError2 = pow( GetBinError  ( BinIdx ), 2 );
	  SetBinContent( BinIdx, LastValue + content      );
	  SetBinError(   BinIdx, sqrt(LastError2 + error) );

	  m_TotalErr += error;
	}
      }
    }
  }

  m_TotalErr = sqrt( m_TotalErr + GetTotalEnt()*ScaleE*GetTotalEnt()*ScaleE );  
  if( m_dataset==Dataset::GdCap ) {    
    m_TotalErr = GetTotalEnt()*0.025;
  }


  return 1;
}
