#include "AnalyzeData.h"
#include "AdMap.h"
#include "Tool/Table.h"
#include "Constants.h"
#include "Tool/Tool.h"
#include "Common/OstwEff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
using namespace std;

AnalyzeData* gAnalyzeData = new AnalyzeData;

AnalyzeData::AnalyzeData()
{
  for( unsigned int set=0; set<=1; set++) {
    for( unsigned int i=1; i<=Basic::NoAd; i++ ) {
      m_Fulltime[set][i-1] = 0;
      m_Livetime[set][i-1] = 0;
      m_MuVeEff [set][i-1] = 0;
      m_OstwEff [set][i-1] = 0;
      
      NNet[ set ][ i-1 ] = 0;
      NSgUp[ set ][ i-1 ] = 0;
      NSgLw[ set ][ i-1 ] = 0;
      TwoFold[ set ][ i-1 ] = 0;
      ThreeFold[ set ][ i-1 ] = 0;
      NBVtx[ set ][ i-1 ] = 0;
      NAVtx[ set ][ i-1 ] = 0;
      NAEng[ set ][ i-1 ] = 0;
      NAcc[ set ][ i-1 ] = 0;
    }
  }

  /* A two-fold loop for two data sets*/
  for( int dataset=Dataset::GdCap; dataset<=Dataset::HCap; dataset++ ) {
    
    Table RunInfoTable;
    if( dataset == Dataset::GdCap ) {
      m_HistFile[dataset][0] = new TFile(DataPath::GdEH1Root);
      m_HistFile[dataset][1] = new TFile(DataPath::GdEH2Root);
      m_HistFile[dataset][2] = new TFile(DataPath::GdEH3Root);
      
      RunInfoTable.Open( DataPath::GdRunInfo );
    }
    if( dataset == Dataset::HCap ) {
      m_HistFile[dataset][0] = new TFile(DataPath::HEH1Root);
      m_HistFile[dataset][1] = new TFile(DataPath::HEH2Root);
      m_HistFile[dataset][2] = new TFile(DataPath::HEH3Root);

      RunInfoTable.Open( DataPath::HRunInfo );
    }
  
    for( int row = 0; row<RunInfoTable.NRows; row++ )   {

      TimeStamp ST = TimeStamp( atoi( RunInfoTable.Columns["StartSec"][row].c_str() ),
				atoi( RunInfoTable.Columns["StartNano"][row].c_str() ) );

      if( ST < Basic::BeginTime || ST > Basic::EndTime ) continue;

      RunBrief * Brief = new RunBrief;
      
      Brief->Dataset = dataset;
      Brief->RunNumber = atoi( RunInfoTable.Columns["Run"][row].c_str() );
      Brief->Site      = atoi( RunInfoTable.Columns["Site"][row].c_str() );
      
      Brief->StartTime = TimeStamp( atoi( RunInfoTable.Columns["StartSec"][row].c_str() ), 
				    atoi( RunInfoTable.Columns["StartNano"][row].c_str() ) );

      Brief->StopTime  = TimeStamp( atoi( RunInfoTable.Columns["StopSec"][row].c_str() ),
				    atoi( RunInfoTable.Columns["StopNano"][row].c_str() ) );
      Brief->Fulltime  = atof( RunInfoTable.Columns["FullTime"][row].c_str() );
      
      /* Per Ad Information */
      Brief->Livetime[0]  = Brief->Fulltime - atof( RunInfoTable.Columns["Veto1"][row].c_str() );
      Brief->Livetime[1]  = Brief->Fulltime - atof( RunInfoTable.Columns["Veto2"][row].c_str() );
      Brief->Livetime[2]  = Brief->Fulltime - atof( RunInfoTable.Columns["Veto3"][row].c_str() );
      Brief->Livetime[3]  = Brief->Fulltime - atof( RunInfoTable.Columns["Veto4"][row].c_str() );
      
      Brief->NNet[0]  =  atof( RunInfoTable.Columns["NNet1"][row].c_str() );
      Brief->NNet[1]  =  atof( RunInfoTable.Columns["NNet2"][row].c_str() );
      Brief->NNet[2]  =  atof( RunInfoTable.Columns["NNet3"][row].c_str() );
      Brief->NNet[3]  =  atof( RunInfoTable.Columns["NNet4"][row].c_str() );
      
      Brief->Scale[0]  =  atof( RunInfoTable.Columns["Scale1"][row].c_str() );
      Brief->Scale[1]  =  atof( RunInfoTable.Columns["Scale2"][row].c_str() );
      Brief->Scale[2]  =  atof( RunInfoTable.Columns["Scale3"][row].c_str() );
      Brief->Scale[3]  =  atof( RunInfoTable.Columns["Scale4"][row].c_str() );
      
      double up,low;
      up  = atof( RunInfoTable.Columns["NSgUp1"][row].c_str() );
      low = atof( RunInfoTable.Columns["NSgLw1"][row].c_str() );
      Brief->Rs[0]  = ( up+low ) / 2 / Brief->Livetime[0];
      up  = atof( RunInfoTable.Columns["NSgUp2"][row].c_str() );
      low = atof( RunInfoTable.Columns["NSgLw2"][row].c_str() );
      Brief->Rs[1]  = ( up+low ) / 2 / Brief->Livetime[1];
      up  = atof( RunInfoTable.Columns["NSgUp3"][row].c_str() );
      low = atof( RunInfoTable.Columns["NSgLw3"][row].c_str() );
      Brief->Rs[2]  = ( up+low ) / 2 / Brief->Livetime[2];
      up  = atof( RunInfoTable.Columns["NSgUp4"][row].c_str() );
      low = atof( RunInfoTable.Columns["NSgLw4"][row].c_str() );
      Brief->Rs[3]  = ( up+low ) / 2 / Brief->Livetime[3];

      Brief->NSgUp[0]  =  atof( RunInfoTable.Columns["NSgUp1"][row].c_str() );
      Brief->NSgUp[1]  =  atof( RunInfoTable.Columns["NSgUp2"][row].c_str() );
      Brief->NSgUp[2]  =  atof( RunInfoTable.Columns["NSgUp3"][row].c_str() );
      Brief->NSgUp[3]  =  atof( RunInfoTable.Columns["NSgUp4"][row].c_str() );

      Brief->NSgLw[0]  =  atof( RunInfoTable.Columns["NSgLw1"][row].c_str() );
      Brief->NSgLw[1]  =  atof( RunInfoTable.Columns["NSgLw2"][row].c_str() );
      Brief->NSgLw[2]  =  atof( RunInfoTable.Columns["NSgLw3"][row].c_str() );
      Brief->NSgLw[3]  =  atof( RunInfoTable.Columns["NSgLw4"][row].c_str() );

      Brief->TwoFold[0]  =  atof( RunInfoTable.Columns["TwoFold1"][row].c_str() );
      Brief->TwoFold[1]  =  atof( RunInfoTable.Columns["TwoFold2"][row].c_str() );
      Brief->TwoFold[2]  =  atof( RunInfoTable.Columns["TwoFold3"][row].c_str() );
      Brief->TwoFold[3]  =  atof( RunInfoTable.Columns["TwoFold4"][row].c_str() );

      Brief->ThreeFold[0]  =  atof( RunInfoTable.Columns["ThreeFold1"][row].c_str() );
      Brief->ThreeFold[1]  =  atof( RunInfoTable.Columns["ThreeFold2"][row].c_str() );
      Brief->ThreeFold[2]  =  atof( RunInfoTable.Columns["ThreeFold3"][row].c_str() );
      Brief->ThreeFold[3]  =  atof( RunInfoTable.Columns["ThreeFold4"][row].c_str() );

      Brief->NBVtx[0]  =  atof( RunInfoTable.Columns["NBVtx1"][row].c_str() );
      Brief->NBVtx[1]  =  atof( RunInfoTable.Columns["NBVtx2"][row].c_str() );
      Brief->NBVtx[2]  =  atof( RunInfoTable.Columns["NBVtx3"][row].c_str() );
      Brief->NBVtx[3]  =  atof( RunInfoTable.Columns["NBVtx4"][row].c_str() );

      Brief->NAVtx[0]  =  atof( RunInfoTable.Columns["NAVtx1"][row].c_str() );
      Brief->NAVtx[1]  =  atof( RunInfoTable.Columns["NAVtx2"][row].c_str() );
      Brief->NAVtx[2]  =  atof( RunInfoTable.Columns["NAVtx3"][row].c_str() );
      Brief->NAVtx[3]  =  atof( RunInfoTable.Columns["NAVtx4"][row].c_str() );

      Brief->NAEng[0]  =  atof( RunInfoTable.Columns["NAEng1"][row].c_str() );
      Brief->NAEng[1]  =  atof( RunInfoTable.Columns["NAEng2"][row].c_str() );
      Brief->NAEng[2]  =  atof( RunInfoTable.Columns["NAEng3"][row].c_str() );
      Brief->NAEng[3]  =  atof( RunInfoTable.Columns["NAEng4"][row].c_str() );
      
      if( Brief->Rs[0] > 0 ) Brief->nEffAd = 1;
      if( Brief->Rs[1] > 0 ) Brief->nEffAd = 2;
      if( Brief->Rs[2] > 0 ) Brief->nEffAd = 3;
      if( Brief->Rs[3] > 0 ) Brief->nEffAd = 4;

      for( unsigned int ad=0; ad<4; ad++ ) {
	double rs = (Brief->NSgUp[ad]+Brief->NSgLw[ad])/2/Brief->Livetime[ad];
	double rm = Brief->NNet[ad]/Brief->Livetime[ad];
	double rss;
	
	if( rs<=0 || rm<=0 )  { rss = 0; }
	else { rss = RSS_DYB( rs, rm, 400e-6 ); }
	
	double eff_dis;

	if( Brief->NBVtx[ad]<=0 ) { eff_dis=0; }
	else { eff_dis = Brief->NAVtx[ad]/Brief->NBVtx[ad]; }
	
	double eff_delay;
	if( Brief->NAVtx[ad]<=0 ) { eff_delay=0; }
        else { eff_delay = Brief->NAEng[ad]/Brief->NAVtx[ad]; }

	double nss = rss * Brief->Livetime[ad] * eff_dis * eff_delay;
	Brief->NAcc[ad] = nss;
      }
      
      int Site = Brief->Site;
      
      /* From 1,2,4 to 0,1,2 */
      int siteIdx = Site;
      if( siteIdx == 4 )       siteIdx = 2;
      else if ( siteIdx == 2 ) siteIdx = 1;
      else if ( siteIdx == 1 ) siteIdx = 0;

      string DtSet = dataset==Dataset::GdCap ? "8_" : "22_";

      string nameVtxbase = "/h1dVtx"+DtSet;
      string nameVtx;
      
      string nameAccbase = "/h1dAcc"+DtSet;
      string nameAcc;
      
      for( int AdNo = 1; AdNo<=4; AdNo++)  { 
	
	/// names like 21821/h1dAccBkg8_21821_1
	/// get candidates spectrum
	nameVtx = i2a(Brief->RunNumber) + nameVtxbase + i2a(Brief->RunNumber)+"_"+i2a(AdNo);
	Brief->h1dVtx[AdNo-1]  = (TH1F*) m_HistFile[dataset][siteIdx]->Get( nameVtx.c_str() );
	if( dataset==Dataset::GdCap && Site==2 && AdNo==1 ) {
	  double entries = Brief->h1dVtx[AdNo-1]->Integral( Binning::BgnBin, Binning::EndBin );
	}
	
	/// get background spectrum
	/// Since it is already calculted, here is the reversed process vtx - acc = accbkg
	nameAcc = i2a(Brief->RunNumber) + nameAccbase + i2a(Brief->RunNumber)+"_"+i2a(AdNo);
	TH1F* Acc = (TH1F*) m_HistFile[dataset][siteIdx]->Get( nameAcc.c_str() );
	Brief->h1dAccBkg[AdNo-1] = new TH1F(*Acc);


	for( unsigned int bin = 1; bin<=Binning::NHistoBin; bin++ ) {
	  double vtx = Brief->h1dVtx[AdNo-1]->GetBinContent( bin );
	  double acc = Acc->GetBinContent( bin );
	  Brief->h1dAccBkg[AdNo-1]->SetBinContent( bin, vtx-acc );

	  // Remember this is a reversed process
	  double vtxerr = Brief->h1dVtx[AdNo-1]->GetBinError( bin );
	  double accerr = Acc->GetBinError( bin );
	  double error2 = accerr*accerr - vtxerr*vtxerr;
	  if( error2<0 && abs(error2)<1e-16 ) error2=0;
	  Brief->h1dAccBkg[AdNo-1]->SetBinError( bin, sqrt( error2 ) );
	}

	/* Calculate Ostw Efficiency */
	Brief->OstwEff[ AdNo-1 ] = EffEN_DYB( Brief->Rs[ AdNo-1 ], 
					      Brief->NNet[ AdNo-1 ] / Brief->Livetime[ AdNo-1 ], 
					      Phys::Tc[ dataset ]/CLHEP::second );
      }

      /* Save it */
      m_RunBrief.push_back( Brief );
    }
  }

  /* Summary information */ 
  /* Gd runs */
  int NRun[2][ Basic::NoAd ] = { {0,0,0,0,0,0},
				 {0,0,0,0,0,0} };

  for( vector< RunBrief* >::const_iterator iRun = m_RunBrief.begin();
       iRun!=m_RunBrief.end(); iRun++ ) {
    int NAD = 0;
    if( (*iRun)->Site == 1 ) NAD = 2;
    if( (*iRun)->Site == 2 ) NAD = 1;
    if( (*iRun)->Site == 4 ) NAD = 3;

    int dataset = (*iRun)->Dataset;
    for( int iAd = 1; iAd<=NAD; iAd++ ) {
      int nGblAd = GlobalAdIdx( (*iRun)->Site, iAd );

      m_Fulltime[dataset][ nGblAd-1 ] += (*iRun)->Fulltime;
      m_Livetime[dataset][ nGblAd-1 ] += (*iRun)->Livetime[ iAd-1 ]; 
      m_OstwEff [dataset][ nGblAd-1 ] += (*iRun)->OstwEff[ iAd-1 ];
      NRun[dataset][ nGblAd-1 ] += 1;


      /// singles rate and other accidental background subtraction check
      NNet[ dataset ][ nGblAd-1 ] += (*iRun)->NNet[ iAd-1 ];

      NSgUp[ dataset ][ nGblAd-1 ] += (*iRun)->NSgUp[ iAd-1 ];
      NSgLw[ dataset ][ nGblAd-1 ] += (*iRun)->NSgLw[ iAd-1 ];
      
      TwoFold[ dataset ][ nGblAd-1 ] += (*iRun)->TwoFold[ iAd-1 ];
      ThreeFold[ dataset ][ nGblAd-1 ] += (*iRun)->ThreeFold[ iAd-1 ];
      
      NBVtx[ dataset ][ nGblAd-1 ] += (*iRun)->NBVtx[ iAd-1 ];
      NAVtx[ dataset ][ nGblAd-1 ] += (*iRun)->NAVtx[ iAd-1 ];
      NAEng[ dataset ][ nGblAd-1 ] += (*iRun)->NAEng[ iAd-1 ];

      NAcc[ dataset ][ nGblAd-1 ] += (*iRun)->NAcc[ iAd-1 ];
    }
  }

  for( int dataset=Dataset::GdCap; dataset<=Dataset::HCap; dataset++ ) {
    for( unsigned int idx=1; idx<=Basic::NoAd; idx++ ) {
      m_MuVeEff[ dataset ][ idx-1 ] = m_Livetime[ dataset ][ idx-1 ] / m_Fulltime[ dataset ][ idx-1 ];
      m_OstwEff[ dataset ][ idx-1 ] = m_OstwEff[ dataset ][ idx-1 ]/NRun[ dataset ][ idx-1 ];
    }
  }

  cout<<"In AnalyzeData"<<endl;
  cout<<"NAcc "<<" & ";
  for( unsigned int AdIdx = 1; AdIdx<=Basic::NoAd; AdIdx++ ) {
    cout<< NAcc[ 1 ][ AdIdx-1 ] <<" & ";
  }

}
