#include "Measurement.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "AdMap.h"
#include "Tool.h"
#include "TFile.h"
#include <math.h>
#include <string>
#include <iostream>
using namespace CLHEP;
using namespace std;

int Measurement::SetupMeas()
{
  TFile *f;
  int Site = ToSite( m_AdNo+1 );
  int LocalAdNo = ToLocalAdNo( m_AdNo+1 );

  if( Site == 1 ) f = new TFile( DataPath::EH1Root, "READ" );
  if( Site == 2 ) f = new TFile( DataPath::EH2Root, "READ" );
  if( Site == 4 ) f = new TFile( DataPath::EH3Root, "READ" );

  string name;
  if( m_dataset == Dataset::GdCap ) {
    name = "h1dAcc8_";
  }
  if( m_dataset == Dataset::HCap ) {
    name = "h1dAcc22_";
  }
   
  name += i2a(LocalAdNo);
  TH1F * h = (TH1F*)(f->Get( name.c_str() ));

  m_TotalErr=0;
  for( unsigned int BinIdx = 1; BinIdx <= Binning::NHistoBin; BinIdx++ )  {
    /* By default I have 100 bins. */
    double content = 0;
    double error = 0;
    unsigned int low, high;
    int ratio = 100/Binning::NHistoBin; /* This must be an interger */
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
}
