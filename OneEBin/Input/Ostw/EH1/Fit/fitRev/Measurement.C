#include "Measurement.h"
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

double Measurement::Integral()
{
  if( RepeatPRL ) {
    return RePRL::NCandidate[ m_AdNo-1 ];
  } else {
    return Spectrum::Integral();
  }
}
  
int Measurement::SetupMeas()
{
  TFile *f;
  int Site = ToSite( m_AdNo );
  int LocalAdNo = ToLocalAdNo( m_AdNo );

  string name;
  if( m_dataset == Dataset::GdCap ) {
    name = "h1dVtx8_";
    if( Site == 1 ) f = new TFile( DataPath::GdEH1Root, "READ" );
    if( Site == 2 ) f = new TFile( DataPath::GdEH2Root, "READ" );
    if( Site == 4 ) f = new TFile( DataPath::GdEH3Root, "READ" );
  }
  if( m_dataset == Dataset::HCap ) {
    name = "h1dVtx22_";
    if( Site == 1 ) f = new TFile( DataPath::HEH1Root, "READ" );
    if( Site == 2 ) f = new TFile( DataPath::HEH2Root, "READ" );
    if( Site == 4 ) f = new TFile( DataPath::HEH3Root, "READ" );
  }
   
  name += i2a(LocalAdNo);
  TH1F * h = (TH1F*)(f->Get( name.c_str() ));

  /* Try to match the number of bins of data histograms and these histograms used internally */
  /* And BinNumberData >= BinInternal */
  /* By default I have 100 bins for data histograms. */
  int nDataBin = h->GetNbinsX();
  if( nDataBin%Binning::NHistoBin != 0) {
    cout<<"Error,    Measurement: BinNumberData can't be divided by BinInternal exactly."<<endl;
    exit(0);
  }
  int ratio = nDataBin/Binning::NHistoBin; /* This must be an interger */


  m_TotalErr=0;
  for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
    double content = 0;
    double error = 0;
    unsigned int low, high;
    low = (BinIdx-1)*ratio+1;
    high = (BinIdx-1)*ratio+ratio;
    for( unsigned int myidx = low; myidx<=high; myidx++ )  {
      content += h->GetBinContent(myidx);
      error += pow( h->GetBinError(myidx), 2 );
    }

    SetBinContent( BinIdx, content     );
    SetBinError(   BinIdx, sqrt(error) );
    m_TotalErr += error;
  }

  m_TotalErr = sqrt(m_TotalErr);
  
  f->Close();

  return 1;
}
