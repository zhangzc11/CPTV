#include "AnalyzeData.h"
#include "AdMap.h"
#include "Table.h"
#include "Constants.h"
#include "Tool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

AnalyzeData* gAnalyzeData = new AnalyzeData;

AnalyzeData::AnalyzeData()
{
  for( unsigned int i=0; i<Basic::NoAd; i++ ) {
    m_Livetime[i]=0;
  }

  m_HistFile[0] = new TFile(DataPath::EH1Root);
  m_HistFile[1] = new TFile(DataPath::EH2Root);
  m_HistFile[2] = new TFile(DataPath::EH3Root);
  
  Table RunInfoTable( DataPath::RunInfo );
  
  for( int row = 0; row<RunInfoTable.NRows; row++ )   {

    RunBrief * Brief = new RunBrief;

    Brief->RunNumber = atoi( RunInfoTable.Columns["Run"][row].c_str() );
    Brief->Site      = atoi( RunInfoTable.Columns["Site"][row].c_str() );

    Brief->StartTime = TimeStamp( atof( RunInfoTable.Columns["StartSec"][row].c_str() ), 
				  atof( RunInfoTable.Columns["StartNano"][row].c_str() ) );
    Brief->StopTime  = TimeStamp( atof( RunInfoTable.Columns["StopSec"][row].c_str() ),
                                  atof( RunInfoTable.Columns["StopNano"][row].c_str() ) );
    Brief->Fulltime  = atof( RunInfoTable.Columns["FullTime"][row].c_str() );

    /* Per Ad Information */
    Brief->Livetime[0]  = Brief->Fulltime - atof( RunInfoTable.Columns["Veto1"][row].c_str() );
    Brief->Livetime[1]  = Brief->Fulltime - atof( RunInfoTable.Columns["Veto2"][row].c_str() );
    Brief->Livetime[2]  = Brief->Fulltime - atof( RunInfoTable.Columns["Veto3"][row].c_str() );
    Brief->Livetime[3]  = Brief->Fulltime - atof( RunInfoTable.Columns["Veto4"][row].c_str() );

    Brief->Rnetmu[0]  =  atof( RunInfoTable.Columns["NNet1"][row].c_str() ) / Brief->Livetime[0];
    Brief->Rnetmu[1]  =  atof( RunInfoTable.Columns["NNet2"][row].c_str() ) / Brief->Livetime[1];
    Brief->Rnetmu[2]  =  atof( RunInfoTable.Columns["NNet3"][row].c_str() ) / Brief->Livetime[2];
    Brief->Rnetmu[3]  =  atof( RunInfoTable.Columns["NNet4"][row].c_str() ) / Brief->Livetime[3];

    Brief->Rs[0]  =  atof( RunInfoTable.Columns["NSgUp1"][row].c_str() ) / Brief->Livetime[0];      
    Brief->Rs[1]  =  atof( RunInfoTable.Columns["NSgUp2"][row].c_str() ) / Brief->Livetime[1];
    Brief->Rs[2]  =  atof( RunInfoTable.Columns["NSgUp3"][row].c_str() ) / Brief->Livetime[2];
    Brief->Rs[3]  =  atof( RunInfoTable.Columns["NSgUp4"][row].c_str() ) / Brief->Livetime[3];

    if( Brief->Rs[0] > 0 ) Brief->nEffAd = 1;
    if( Brief->Rs[1] > 0 ) Brief->nEffAd = 2;
    if( Brief->Rs[2] > 0 ) Brief->nEffAd = 3;
    if( Brief->Rs[3] > 0 ) Brief->nEffAd = 4;

    int Site = Brief->Site;

    /* From 1,2,4 to 0,1,2 */
    int siteIdx = Site;
    if( siteIdx == 4 ) siteIdx = 3;
    siteIdx = siteIdx - 1;

    string name8base = "/h1dAcc8_";
    string name8;

    string name22base = "/h1dAcc22_";
    string name22;

    for( int AdNo = 1; AdNo<=4; AdNo++)  { 

      
      name8 = i2a(Brief->RunNumber) + name8base + i2a(Brief->RunNumber)+"_"+i2a(AdNo);
      Brief->h1dAcc8[AdNo-1]  = (TH1F*) m_HistFile[siteIdx]->Get( name8.c_str() );

      name22 = i2a(Brief->RunNumber) + name22base + i2a(Brief->RunNumber)+"_"+i2a(AdNo);
      Brief->h1dAcc22[AdNo-1]  = (TH1F*) m_HistFile[siteIdx]->Get( name22.c_str() );
      

      /// Calculate livetime for each detector
      if(Site==1 && AdNo>=3 ) continue;
      if(Site==2 && AdNo>=2 ) continue;
      if(Site==4 && AdNo>=4 ) continue;
      int GblAd = GlobalAdIdx( Site, AdNo );
      m_Livetime[GblAd-1] += Brief->Livetime[AdNo-1];
    }    
    
    /* Save it */
    m_RunBrief.insert( pair<int /* RunNumber */, RunBrief*> (Brief->RunNumber, Brief) );
  }

  for( unsigned int i=0; i<Basic::NoAd; i++ ) {
    cout<<"Total Livetime "<<m_Livetime[i]<<endl;
  }

}
