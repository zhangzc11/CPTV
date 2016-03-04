#include "ProtonNumber.h"
#include "Table.h"
#include "Constants.h"
#include "Tool.h"
#include "AdMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

ProtonNumber* gProtonNumber = new ProtonNumber;

ProtonNumber::ProtonNumber()
{
  std::string datapath = DataPath::NProtonData;
  Table ProtonTable( datapath );
  
  for( int row = 0; row<ProtonTable.NRows; row++ )   {
    TimeStamp BeginTime( atof( ProtonTable.Columns["StartUTC"][row].c_str() ) );
    TimeStamp EndTime(   atof( ProtonTable.Columns["StopUTC" ][row].c_str() ) );

    int site = atoi( ProtonTable.Columns[ "Site" ][row].c_str() );
    int ad   = atoi( ProtonTable.Columns[ "Ad"   ][row].c_str() );
    
    // Convert them to AdNo 0-7
    int AdNo = GlobalAdIdx( site, ad ) - 1;
    
    NProton np;
 
    np.NPGdLs    = atof( ProtonTable.Columns["GdProton"   ][row].c_str() );
    np.NPGdLs_RE = atof( ProtonTable.Columns["GdProtonRE" ][row].c_str() );
    np.NPGdLs_AE = atof( ProtonTable.Columns["GdProtonAE" ][row].c_str() );
    np.NPLs      = atof( ProtonTable.Columns["LsProton"   ][row].c_str() );
    np.NPLs_RE   = atof( ProtonTable.Columns["LsProtonRE" ][row].c_str() );
    np.NPLs_AE   = atof( ProtonTable.Columns["LsProtonAE" ][row].c_str() );

    m_NProtonData[ AdNo ].insert( pair< TimeStamp /* time */, NProton  /* NProton */ > ( BeginTime, np ) );
  }
}
  
NProton ProtonNumber::Get( TimeStamp Time, int AdNo )
{
  unsigned int year, month, day;
  Time.GetDate( true, 0, &year, &month, &day );

  TimeStamp ClosestDate = TimeStamp( year, month, day, 0, 0, 0 );
  
  return m_NProtonData[AdNo][ClosestDate];
}
