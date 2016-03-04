#include "GetFluxXsec.h"
#include "Constants.h"
#include "RctXsecTheory/Crosssection.h"
#include "RctXsecTheory/RctXsec.h"
#include "Tool/Table.h"
#include "Tool/Tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "math.h"
using namespace std;
using namespace CLHEP;
using namespace Reactor;

//GetFluxXsec* gGetFluxXsec = new GetFluxXsec;

double  x[33]={1.5, 1.75, 2, 2.25, 2.5, 2.75, 3, 3.25, 3.5, 3.75, 4, 4.25, 4.5, 4.75, 5, 5.25, 5.5, 5.75, 6, 6.25, 6.5, 6.75, 7, 7.25, 7.5, 7.75, 8, 8.25, 8.5, 8.75, 9, 9.25, 9.5}; // neutrino energy

double Interpolation(double nuE, const double * ILL)  // ILL is pointer of the array of the data set. 
{   
  double answer=0;
  double y[33];
  for (int i=0;i<33;i++)
    y[i]=log10(ILL[i]);
  if (nuE<1.5 || nuE>9.5)
    return 0;
  int idx=int((nuE-1.5)/0.25);
  answer=(nuE-x[idx+1])/(x[idx]-x[idx+1])*y[idx]+(nuE-x[idx])/(x[idx+1]-x[idx])*y[idx+1];
  answer= pow(10, answer) ;
  if (answer!=answer)// logarithm on 0 results nan
    return 0;
  else return answer;
}

GetFluxXsec::GetFluxXsec()
{
  if( !gCrosssection ) {
    gCrosssection = new Crosssection;

    gU238  = new RctSpec( Reactor::U238SpecFile,  "U238"  );
    gU235  = new RctSpec( Reactor::U235SpecFile,  "U235"  );
    gPu239 = new RctSpec( Reactor::Pu239SpecFile, "Pu239" );
    gPu241 = new RctSpec( Reactor::Pu241SpecFile, "Pu241" );
    
    gU238Xsec  = new RctXsec( "U238Xsec",  gCrosssection, gU238  );
    gU235Xsec  = new RctXsec( "U235Xsec",  gCrosssection, gU235  );
    gPu239Xsec = new RctXsec( "Pu239Xsec", gCrosssection, gPu239 );
    gPu241Xsec = new RctXsec( "Pu241Xsec", gCrosssection, gPu241 );
    cout<< gU238Xsec <<gU235Xsec << gPu239Xsec<< gPu241Xsec<<endl;
  }

  if( ! Reactor::DBFlux ) {
    /* Have a table to read from WW */
    string datafile = Reactor::WeeklyFluxDataFile;
    
    Table power(datafile);
    
    for( int row = 0; row<power.NRows; row++ )   {
      TimeStamp BeginTime( atof( power.Columns["BeginUTC"][row].c_str() ) );
      TimeStamp EndTime  ( atof( power.Columns["EndUTC" ][row].c_str() ) );
      int Reactor = atoi( power.Columns["Reactor"][row].c_str() );
      
      double Power    = atof( power.Columns["Power"][row].c_str() );
      double PowerErr = atof( power.Columns["PowerErr"][row].c_str() );
      double U235Frac = atof( power.Columns["U235Frac"][row].c_str() );
      double U238Frac = atof( power.Columns["U238Frac"][row].c_str() );
      double Pu239Frac= atof( power.Columns["Pu239Frac"][row].c_str() );
      double Pu241Frac= atof( power.Columns["Pu241Frac"][row].c_str() );
      
      FluxXsec* aFluxXsec = new FluxXsec( Reactor, power.Columns["BeginUTC"][row] );
      
      double SumE =
	U235Frac  * AveE_U235  +
	U238Frac  * AveE_U238  +
	Pu239Frac * AveE_Pu239 +
	Pu241Frac * AveE_Pu241 ;
      
      double NFission = Reactor::NmlPowerUnbld * Power / SumE;
    
      aFluxXsec->Add( gU238Xsec  ,  NFission * U238Frac  *cm*cm/MeV );
      aFluxXsec->Add( gU235Xsec  ,  NFission * U235Frac  *cm*cm/MeV );
      aFluxXsec->Add( gPu239Xsec ,  NFission * Pu239Frac *cm*cm/MeV );
      aFluxXsec->Add( gPu241Xsec ,  NFission * Pu241Frac *cm*cm/MeV );
      
      /* Fill all specs of this period using this average */
      for( TimeStamp time=BeginTime; time<EndTime; time.Add( Basic::StepTime ) )  {
	m_FluxXsecSpecs[ Reactor-1 ].insert( pair< TimeStamp, FluxXsec* >( time, aFluxXsec ) );
      }
      
      /* Keep track of the earliest and latest */
      if( row==0 )  {
	mEarliest = BeginTime;
	mLatest   = BeginTime;
      }
      if( BeginTime<mEarliest )  {
	mEarliest = BeginTime;
      }
      if( BeginTime>mLatest )  {
	mLatest = BeginTime;
      }
    }
  } else {
    /* Read database flux */
    std::string datapath = Reactor::DBWeeklyFluxDataFile;
    Table fluxTable( datapath );

    for( int row = 0; row<fluxTable.NRows; row++ ) {
      TimeStamp BeginTime( atof( fluxTable.Columns["StartUTC"][row].c_str() ) );
      TimeStamp EndTime  ( atof( fluxTable.Columns["StopUTC" ][row].c_str() ) );

      string RctNoName = fluxTable.Columns["Reactor" ][row];
      int RctNo = atoi( fluxTable.Columns["Reactor" ][row].c_str() );
      RctSpec *spec = new RctSpec();
      spec->SetNameTitle( i2a(RctNo-1).c_str(), fluxTable.Columns["StartUTC"][row].c_str() );

      /* Read in the Weekly binned flux */
      double Enus[33];
      double Rate[33];

      for( int idx=0; idx<33; idx++ ) {
	Enus[ idx ] = 1500 * CLHEP::keV + idx*250*CLHEP::keV;

	int Eint = 1500 + idx*250;
	string Estring = "E";
	Estring += i2a(Eint);
	Estring += "keV";

	Rate[idx] = atof( fluxTable.Columns[ Estring ][row].c_str() ) / CLHEP::second;
      }

      /* Convert it to expected binning */
      double step = (Binning::EndEnergy - Binning::BeginEnergy) / Binning::NPreciseBin;
      for( unsigned int BinIdx = 1; BinIdx<=Binning::NPreciseBin; BinIdx++ ) {
	double Enu = Binning::BeginEnergy + (BinIdx-0.5)*step;

	if( Enu<=1500*CLHEP::keV || Enu>=9500*CLHEP::keV ) {
	  spec->SetBinContent( BinIdx, 0 );
	} else {
	  double rate = Interpolation( Enu/MeV, Rate );
	  spec->SetBinContent( BinIdx, rate );
	}
	//cout<<Enu<<" "<<spec->GetBinContent( BinIdx)<<endl;
      }

      /* times cross section */
      RctXsec* FluxXspec = new RctXsec(fluxTable.Columns["StartUTC"][row], gCrosssection, spec);
      FluxXsec* aFluxXsec = new FluxXsec( RctNo, fluxTable.Columns["StartUTC"][row] );
      aFluxXsec->Add( FluxXspec , 1 *cm*cm/MeV );

      /* Fill all specs of this period using this average */
      for( TimeStamp time=BeginTime; time<EndTime; time.Add( Basic::StepTime )) {
	m_FluxXsecSpecs[ RctNo-1 ].insert( pair< TimeStamp, FluxXsec* >( time, aFluxXsec ) );
      }

      /* Keep track of the earliest and latest */
      if( row==0 ) {
        mEarliest = BeginTime;
        mLatest   = BeginTime;
      }
      if( BeginTime<mEarliest ) {
        mEarliest = BeginTime;
      }
      if( BeginTime>mLatest ) {
        mLatest = BeginTime;
      }
    }
  }



  /* Build default flux */
  mDefaultFluxXsec = new FluxXsec( 0, "Default Flux * Xsec" );
  double SumE =
    NmlU235Frac  * AveE_U235  +
    NmlU238Frac  * AveE_U238  +
    NmlPu239Frac * AveE_Pu239 +
    NmlPu241Frac * AveE_Pu241 ;
  
  double NFission = Reactor::NmlPowerBlind * 1.0 / SumE;

  mDefaultFluxXsec->Add( gU238Xsec  ,  NFission * NmlU238Frac  *cm*cm/MeV );
  mDefaultFluxXsec->Add( gU235Xsec  ,  NFission * NmlU235Frac  *cm*cm/MeV );
  mDefaultFluxXsec->Add( gPu239Xsec ,  NFission * NmlPu239Frac *cm*cm/MeV );
  mDefaultFluxXsec->Add( gPu241Xsec ,  NFission * NmlPu241Frac *cm*cm/MeV );
  
  /* Set last query to some default values. */
  for( int RctNo = 1; RctNo<=6; RctNo++ )  {
    mLastQueryIt[ RctNo-1 ]   = m_FluxXsecSpecs[ RctNo-1 ].begin();
  }
}

double GetFluxXsec::Get( TimeStamp Time, int RctNo, int BinIdx )
{
  double flux = 0;

  TimeStamp ClosestDate = Time.GetClosestDate();

  /* The same as the last one */
  if( ClosestDate == mLastQueryIt[ RctNo-1 ]->first ) {
    return mLastQueryIt[ RctNo-1 ]->second->GetBinContent( BinIdx );
  }

  /* Maybe it is just the next one */
  mLastQueryIt[ RctNo-1 ]++;
  if( ClosestDate == mLastQueryIt[ RctNo-1 ]->first ) {
    return mLastQueryIt[ RctNo-1 ]->second->GetBinContent( BinIdx );
  }

  /* Obviously out of scope */
  if( ClosestDate<mEarliest || ClosestDate>mLatest )  {
    return mDefaultFluxXsec->GetBinContent( BinIdx );
  }

  /* No hope. Do a find. */
  mLastQueryIt[ RctNo-1 ] = m_FluxXsecSpecs[ RctNo-1 ].find( ClosestDate );

  if( mLastQueryIt[ RctNo-1 ] != m_FluxXsecSpecs[ RctNo-1 ].end() )  {
    flux = mLastQueryIt[ RctNo-1 ]->second->GetBinContent( BinIdx );
  } else {
    flux = mDefaultFluxXsec->GetBinContent( BinIdx );
  }

  return flux;
}
