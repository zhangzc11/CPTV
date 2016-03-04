#include <stdio.h>
#include <stdlib.h>
#include "XYCorr.h"
#include "TFile.h"
#include "TH2F.h"
#include "TAxis.h"
#include <math.h>
#include <iostream>
using namespace std;

XYCorr::XYCorr()
{
  string Path;
  Path = getenv ("EXAMTRUTHROOT");
  Path += "/aileron/AdScaled/XYCorr.root";
  cout<<" ----****---- XY correction file: "<<Path<<endl;
  
  TFile f( Path.c_str() );
  TH2F* hXCorr = (TH2F*)f.Get("XCorr");
  TH2F* hYCorr = (TH2F*)f.Get("YCorr");

  min = hXCorr->GetXaxis()->GetXmin();
  max = hXCorr->GetXaxis()->GetXmax();
  step = (max-min)/hXCorr->GetXaxis()->GetNbins();

  for( unsigned int x=1; x<=XBin; x++ ) {
    for( unsigned int y=1; y<=YBin; y++ ) {
      XCorr[x-1][y-1] = hXCorr->GetBinContent( x, y );
      YCorr[x-1][y-1] = hYCorr->GetBinContent( x, y );
    }
  }

  f.Close();
}

XYCorr::~XYCorr()
{}
  
int XYCorr::Correct(double recx, double recy, double& truex, double& truey)
{
  /* Get center bin */
  unsigned int binx = int( (recx-min)/step )+1;
  if( recx<min || recx>max ) binx = 0;

  unsigned int biny = int( (recy-min)/step )+1;
  if( recy<min || recy>max ) biny = 0;
  
  /* Out of range. Invalid. */
  if( binx==0 || biny==0 ) {
    truex = recx;
    truey = recy;
    return 1;
  }

  /* Bin Center */
  double CenX = (binx-0.5)*step+min;
  double CenY = (biny-0.5)*step+min;
  
  int Nx,Ny;
  /* Find neighbour bins */
  if( recx>CenX ) { Nx = binx+1; }
  else { Nx = binx-1; }

  if( recy>CenY ) { Ny = biny+1; }
  else { Ny = biny-1; }
  
  int Bx[4],By[4];
  double CenterX[4], CenterY[4];
  double cx[4];
  double cy[4];
  double ds[4];

  Bx[0] = binx;   By[0] = biny;
  Bx[1] = binx;   By[1] = Ny;
  Bx[2] = Nx;     By[2] = biny;
  Bx[3] = Nx;     By[3] = Ny;

  double xcorr = 0;
  double ycorr = 0;
  double weight = 0;
  for( int i=0; i<4; i++) {
    
    CenterX[i] = (Bx[i]-0.5)*step+min;
    CenterY[i] = (By[i]-0.5)*step+min;
    ds[i] = sqrt( pow( recx-CenterX[i], 2 ) + pow( recy-CenterY[i], 2 ) );

    if( Bx[i]<1 || Bx[i]>XBin ||
	By[i]<1 || By[i]>YBin ) {
      cx[i] = 0;
      cy[i] = 0;
      goto Sum;
    }
    
    if( ds[i]<1e-9 ) { 
      xcorr = cx[i];
      ycorr = cy[i];
      weight = 1;
      break;
    }
    
    cx[i] = XCorr[ Bx[i]-1 ][ By[i]-1 ];
    cy[i] = YCorr[ Bx[i]-1 ][ By[i]-1 ];
    
  Sum:
    weight += 1/pow(ds[i],4);
    xcorr += cx[i] * 1/pow(ds[i],4);
    ycorr += cy[i] * 1/pow(ds[i],4);
  }
  
  xcorr = xcorr/weight;
  ycorr = ycorr/weight;
  
  truex = recx + xcorr;
  truey = recy + ycorr;
  
  return 1;
}
