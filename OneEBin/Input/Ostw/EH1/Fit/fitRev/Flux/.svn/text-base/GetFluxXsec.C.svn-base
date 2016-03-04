#include "GetFluxXsec.h"
#include "Constants.h"
#include "RctXsecTheory/Crosssection.h"
#include "RctXsecTheory/RctXsec.h"
#include "Tool/Table.h"
#include "Tool/Tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
using namespace CLHEP;
using namespace Reactor;

GetFluxXsec* gGetFluxXsec = new GetFluxXsec;

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
  }

  /* Have a table to read */
  string datafile = Reactor::WeeklyAvg_CorrectedPower_P12AB;
  
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
