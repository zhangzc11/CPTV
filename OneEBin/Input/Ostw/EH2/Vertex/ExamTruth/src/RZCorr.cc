#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "RZCorr.h"
#include "TFile.h"
#include "TH2F.h"
#include "TAxis.h"
#include <math.h>
#include <iostream>
using namespace std;

RZCorr::RZCorr()
{
  string Path;
  Path = getenv ("EXAMTRUTHROOT");
  Path += "/aileron/AdScaleTable/RZCorr.root";
  cout<<" ----****---- RZ correction file: "<<Path<<endl;

  TFile f( Path.c_str() );
  //TFile f( pPath.c_str() );
  TH2F* hZCorr = (TH2F*)f.Get("ZCorr");
  TH2F* hR2Corr = (TH2F*)f.Get("R2Corr");

  r2min = hZCorr->GetXaxis()->GetXmin();
  r2max = hZCorr->GetXaxis()->GetXmax();
  r2step = (r2max-r2min)/hZCorr->GetXaxis()->GetNbins();
  
  zmin = hZCorr->GetYaxis()->GetXmin();
  zmax = hZCorr->GetYaxis()->GetXmax();
  zstep = (zmax-zmin)/hZCorr->GetYaxis()->GetNbins();
  
  for( unsigned int x=1; x<=R2Bin; x++ ) {
    for( unsigned int y=1; y<=ZBin; y++ ) {
      ZCorr[x-1][y-1] = hZCorr->GetBinContent( x, y );
      R2Corr[x-1][y-1] = hR2Corr->GetBinContent( x, y );
    }
  }
  f.Close();

  cout<<r2min<<" "<<r2max<<" "<<r2step<<" "<<zmin<<" "<<zmax<<" "<<zstep<<endl;
}

RZCorr::~RZCorr()
{}
  
int RZCorr::Correct(double recz, double recr2, double& truez, double& truer2)
{
  /* Get center bin */
  unsigned int binr2 = int( (recr2-r2min)/r2step )+1;
  if( recr2<r2min || recr2>r2max ) binr2 = 0;

  unsigned int binz = int( (recz-zmin)/zstep )+1;
  if( recz<zmin || recz>zmax ) binz = 0;
  
  /* Out of range. Invalid. */
  if( binr2==0 || binz==0 ) {
    truer2 = recr2;
    truez = recz;
    return 1;
  }
  cout<<"binr2:binz"<<binr2<<" "<<binz<<endl;

  /* Bin Center */
  double CenR2 = (binr2-0.5)*r2step+r2min;
  double CenZ = (binz-0.5)*zstep+zmin;

  int Nr2,Nz;
  /* Find neighbour bins */
  if( recr2>CenR2 ) { Nr2 = binr2+1; }
  else { Nr2 = binr2-1; }
  if( Nr2<1 ) { Nr2=1; }
    
  if( recz>CenZ ) { Nz = binz+1; }
  else { Nz = binz-1; }
  
  int Br2[4],Bz[4];
  double CenterR2[4], CenterZ[4];
  double cr2[4];
  double cz[4];
  double ds[4];

  Br2[0] = binr2;   Bz[0] = binz;
  Br2[1] = binr2;   Bz[1] = Nz;

  Br2[2] = Nr2;     Bz[2] = binz;
  Br2[3] = Nr2;     Bz[3] = Nz;

  /* Simple interpolation */
  double CorrCenter, Corr, CorrNz;
  double d1, d2;
  
  if( recz<400 && recz>-400 ) {
    CorrCenter = 1;
  } else {
    CorrCenter = ZCorr[ Br2[0]-1 ][ Bz[0]-1 ];
    cout<<"? "<<Br2[0]-1<<" "<<Bz[0]-1<<" "<<CorrCenter<<endl;
  }

  if( Bz[1]<1 || Bz[1]>ZBin ) {
    CorrNz = CorrCenter;
  } else if( recz<400 && recz>-400 )  {
    CorrNz = 1;
  } else  {
    /// only vertically the next bin
    CorrNz = ZCorr[ Br2[1]-1 ][ Bz[1]-1 ];
  }
  d1 = fabs(recz - CenZ);
  d2 = zstep;

  Corr = d1/d2*(CorrNz-CorrCenter) + CorrCenter;

  cout<<CorrCenter<<"  "<<CorrNz<<" "<<d1<<" "<<d2<<" "<<Corr<<endl;
  truez = recz * Corr;
  cout<<"recz -> truez (r2): "<<recz<<" "<<truez<<" ("<<recr2<<")"<<endl;

  return 1;
}
