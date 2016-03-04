#include "GetWeeklyFlux.h"
#include "Table.h"
#include "Constants.h"
#include "Tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

GetWeeklyFlux* gGetWeeklyFlux = new GetWeeklyFlux;

GetWeeklyFlux::GetWeeklyFlux()
{
  std::string datapath = DataPath::WeeklyFluxData;
  Table fluxTable( datapath );

  for( int row = 0; row<fluxTable.NRows; row++ )   {
    TimeStamp BeginTime( atof( fluxTable.Columns["StartUTC"][row].c_str() ) );
    TimeStamp EndTime  ( atof( fluxTable.Columns["StopUTC" ][row].c_str() ) );

    int RctNo = atoi( fluxTable.Columns["Reactor" ][row].c_str() );
    Flux *spec = new Flux( RctNo-1, fluxTable.Columns["StartUTC"][row] );
    
    /* Read in the Weekly binned flux */
    double Enus[33];
    double Rate[33];
    
    for( int idx=0; idx<33; idx++ )  {
      Enus[ idx ] = 1500 * CLHEP::keV + idx*250*CLHEP::keV;
      
      int Eint = 1500 + idx*250;
      string Estring = "E";
      Estring += i2a(Eint);
      Estring += "keV";

      Rate[idx] = atof( fluxTable.Columns[ Estring ][row].c_str() ) / CLHEP::second;
    }
    
    /* Convert it to expected binning */
    double step = (Binning::EndEnergy - Binning::BeginEnergy) / Binning::NHistoBin;
    for( unsigned int BinIdx = 1; BinIdx<=Binning::NHistoBin; BinIdx++ )   {
      double Eprompt = Binning::BeginEnergy + (BinIdx-1)*step;
      double Enu = Eprompt + Phys::EnuToEprompt;
      
      if( Enu<1500*CLHEP::keV ) {
	spec->SetBinContent( BinIdx, 0 );
      } else {
	for( int idx=0; idx<33; idx++ )  {
	  if( Enu>Enus[ idx ] && Enu<Enus[idx+1] )   {
	    spec->SetBinContent( BinIdx, Rate[idx] );
	    break;
	  }
	}
      }
    }

    /* Fill all specs of this period using this average */
    for( TimeStamp time=BeginTime; time<EndTime; time.Add( Basic::StepTime ) )  {
      m_FluxSpecs[ RctNo-1 ].insert( pair< TimeStamp, Flux* >( time, spec ) );      
    }
  }
}

double GetWeeklyFlux::Get( TimeStamp Time, int RctNo, int BinIdx )
{
  double flux = 0;
  
  unsigned int year, month, day;
  Time.GetDate( true, 0, &year, &month, &day );
  TimeStamp ClosestDate = TimeStamp( year, month, day, 0, 0, 0 );

  flux = m_FluxSpecs[ RctNo ][ ClosestDate ]->GetBinContent( BinIdx );
 
  return flux;
}
