#include "RctXsec.h"

//RctXsec* gU238Xsec ;
//RctXsec* gU235Xsec ;
//RctXsec* gPu239Xsec;
//RctXsec* gPu241Xsec;

void RctXsec::SetupRctXsec()
{
  TH1D* HDRctXsec = new TH1D( "tmp ", "tmp", Binning::NPreciseBin, Binning::BeginEnergy, Binning::EndEnergy );

  if( !gCrosssection ) {
    gCrosssection = new Crosssection;    
  }

  HDRctXsec->Multiply( mCrosssection, mRctSpec );

  /* Convert it to expected binning */
  int step = Binning::NPreciseBin/Binning::NHistoBin;

  int shift = int( Phys::EnuToEprompt/( (Binning::EndEnergy - Binning::BeginEnergy) / Binning::NPreciseBin ) );

  /* In Eprompt */
  for( unsigned int BinIdx = 1; BinIdx<=Binning::NHistoBin; BinIdx++ )   {
    
    double ave = 0;
    /* In Enu */
    for( unsigned int FineIdx = (BinIdx-1)*step+shift; FineIdx <= (BinIdx)*step+shift; FineIdx++ )  {
      if( FineIdx>= Binning::NPreciseBin ) {
	ave+=0;
      } else {
	ave += HDRctXsec->GetBinContent( FineIdx );
      }
    }
    ave = ave/(step+1);

    SetBinContent( BinIdx, ave );
  }

  delete HDRctXsec;
}
