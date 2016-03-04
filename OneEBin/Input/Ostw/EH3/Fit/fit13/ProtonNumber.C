#include "ProtonNumber.h"
#include "Tool/Table.h"
#include "Constants.h"
#include "Tool/Tool.h"
#include "AdMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

ProtonNumber* gProtonNumber = new ProtonNumber;

ProtonNumber::ProtonNumber()
{
  /* With a data file */
  std::string datapath = DataPath::NProtonData;
  Table ProtonTable( datapath );
  
  for( int row = 0; row<ProtonTable.NRows; row++ )   {
    TimeStamp BeginTime( atof( ProtonTable.Columns["StartUTC"][row].c_str() ) );
    TimeStamp EndTime(   atof( ProtonTable.Columns["StopUTC" ][row].c_str() ) );

    int site = atoi( ProtonTable.Columns[ "Site" ][row].c_str() );
    int ad   = atoi( ProtonTable.Columns[ "Ad"   ][row].c_str() );
    
    // Convert them to AdNo 1-8
    int AdNo = GlobalAdIdx( site, ad );
    
    NProton np;
 
    np.NPGdLs    = atof( ProtonTable.Columns["GdProton"   ][row].c_str() ) /Phys::mH * Phys::fH1;
    np.NPGdLs_RE = atof( ProtonTable.Columns["GdProtonRE" ][row].c_str() );
    np.NPGdLs_AE = atof( ProtonTable.Columns["GdProtonAE" ][row].c_str() );
    np.NPLs      = atof( ProtonTable.Columns["LsProton"   ][row].c_str() );
    np.NPLs_RE   = atof( ProtonTable.Columns["LsProtonRE" ][row].c_str() );
    np.NPLs_AE   = atof( ProtonTable.Columns["LsProtonAE" ][row].c_str() );

    m_NProtonData[ AdNo-1 ].insert( pair< TimeStamp /* time */, NProton  /* NProton */ > ( BeginTime, np ) );

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

  /* Build a default one */
  mDefaultNP.NPGdLs    = 1.42889189397e+30;
  mDefaultNP.NPGdLs_RE = 7.17561753825e+25;
  mDefaultNP.NPGdLs_AE = 0;
  mDefaultNP.NPLs      = 1.53384357189e+30;
  mDefaultNP.NPLs_RE   = 0;
  mDefaultNP.NPLs_AE   = 8.12937424294e+27;

  /* Set last query to some default values. */
  for( int AdNo = 1; AdNo<=8; AdNo++ )  {
    mLastQueryIt[ AdNo-1 ]   = m_NProtonData[ AdNo-1 ].begin();
  }
}
  
NProton ProtonNumber::Get( TimeStamp Time, int AdNo )
{
  /* The result from the database has problems, AD 1 and 2 seem not in order. */
  if( AdNo == 1) mDefaultNP.NPGdLs    = 1.42957029e30;
  if( AdNo == 2) mDefaultNP.NPGdLs    = 1.43136254e30;
  if( AdNo == 3) mDefaultNP.NPGdLs    = 1.42584241e30;
  if( AdNo == 4) mDefaultNP.NPGdLs    = 1.42756297e30;
  if( AdNo == 5) mDefaultNP.NPGdLs    = 1.43301141e30;
  if( AdNo == 6) mDefaultNP.NPGdLs    = 1.42598579e30;
  return mDefaultNP;

  /* This will over write everything */
  if( RepeatPRL ) {
    if( AdNo == 1) mDefaultNP.NPGdLs    = 1.4327e30 * ( 19.941 / 20 );
    if( AdNo == 2) mDefaultNP.NPGdLs    = 1.4327e30 * ( 19.966 / 20 );
    if( AdNo == 3) mDefaultNP.NPGdLs    = 1.4327e30 * ( 19.891 / 20 );
    if( AdNo == 4) mDefaultNP.NPGdLs    = 1.4327e30 * ( 19.913 / 20 );
    if( AdNo == 5) mDefaultNP.NPGdLs    = 1.4327e30 * ( 19.991 / 20 );
    if( AdNo == 6) mDefaultNP.NPGdLs    = 1.4327e30 * ( 19.892 / 20 );
    //mDefaultNP.NPGdLs *=0.988;
    return mDefaultNP;
  }
  
  TimeStamp ClosestDate = Time.GetClosestDate();

  /* The same as the last one */
  if( ClosestDate == mLastQueryIt[ AdNo-1 ]->first ) {
    return mLastQueryIt[ AdNo-1 ]->second;
  } 
  
  /* Maybe it is just the next one */
  mLastQueryIt[ AdNo-1 ]++;
  if( ClosestDate == mLastQueryIt[ AdNo-1 ]->first ) {
    return mLastQueryIt[ AdNo-1 ]->second;
  }

  /* Obviously out of scope */
  if( ClosestDate<mEarliest || ClosestDate>mLatest )  {
    return mDefaultNP;
  }

  /* No hope. Do a find. */
  mLastQueryIt[ AdNo-1 ] = m_NProtonData[ AdNo-1 ].find( ClosestDate );
  
  if( mLastQueryIt[ AdNo-1 ]!=m_NProtonData[ AdNo-1 ].end() )  {
    return mLastQueryIt[ AdNo-1 ]->second;
  } else {
    return mDefaultNP;
  }
}
