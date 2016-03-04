//
//   Accidental Generation
//
//      1. Generate accidental background 2-d spectrum (E-prompt vs. E-decay)
//           Sample prompt from the first half the Event tree and sample delayed from
//           the second half of the Event tree. Apply the rest cuts, like D2First, etc.
//      2. Generate accidental background 1-d spectrum (just E-prompt)
//      3. Correctly normalize the background spectra according to LiveTime
//      4. Background substraction 2-d
//      5. Background substraction 1-d
//
//   Zhe Wang, Nov. 2011
//
#include <string>
#include <vector>
#include "EventReader.h"
#include "Common/Cuts.h"
#include "Common/OstwEff.h"
#include "Common/RunStat.h"
#include <map>
#include "TFile.h"
#include "TH2F.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include <sstream>
#include "Table.h"
#include <stdlib.h>
#include "AdMap.h"

using namespace std;

string i2a(int intValue) {

  ostringstream oss (ostringstream::out);
  oss <<intValue;
  string strRetVal=oss.str();
  return(strRetVal);
};

string d2a(double dValue) {
  ostringstream oss (ostringstream::out);
  oss <<dValue;
  string strRetVal=oss.str();
  return(strRetVal);
};

/////////////////////////////////////////////////////////////////////////////////////
TFile* rootfile;

const int n2dhists = 10;

string h2name[7], h2title[7];

const int FnBin = 1200;
const int CsBin = 120;

/// genrate the singles time distribution
TRandom3 r;
/// Average singles rates in Hz
const double SingleR[3] = { 21.2*0.38, 20.3*0.38, 22*0.38 };

/// Histogram per run per detector
map< int /* Run */, map< int /* AdNo */, TH2F* > >  h2dAll;    /// 2d hist including everything
map< int /* Run */, map< int /* AdNo */, TH2F* > >  h2dVtx;    /// 2d hist after vertices distance cut	
map< int /* Run */, map< int /* AdNo */, TH2F* > >  h2dAccBkg; /// 2d hist for accidental background
map< int /* Run */, map< int /* AdNo */, TH2F* > >  h2dAcc;    /// 2d hist after accidental background subtraction
TH2F CsVtxTmp;
TH2F CsBkgTmp;

/// A set of 2d histogram for vertex distribution
map< int /* Run */, map< int /* AdNo */, TH2F* > >  h2dZR2Vtx; /// 2d hist for Z vs R^2 after vertex distance cut   
map< int /* Run */, map< int /* AdNo */, TH2F* > >  h2dZR2Bkg; /// 2d hist for Z vs R^2 made of singles repository  
map< int /* Run */, map< int /* AdNo */, TH2F* > >  h2dZR2Acc; /// 2d hist for Z vs R^2 after background subtraction

/// Histogram per run
map< int /* Run */, TH2F* >  h2dAllDet    ;
map< int /* Run */, TH2F* >  h2dVtxDet    ;
map< int /* Run */, TH2F* >  h2dAccBkgDet ;
map< int /* Run */, TH2F* >  h2dAccDet    ;

map< int /* Run */, TH2F* >  h2dZR2VtxDet;
map< int /* Run */, TH2F* >  h2dZR2BkgDet;
map< int /* Run */, TH2F* >  h2dZR2AccDet;

/// Histogram for all
TH2F*  h2dAllSum    ;
TH2F*  h2dVtxSum    ;
TH2F*  h2dAccBkgSum ;
TH2F*  h2dAccSum    ;

TH2F*  h2dZR2VtxSum;
TH2F*  h2dZR2BkgSum;
TH2F*  h2dZR2AccSum;

string h1name[14], h1title[14];

/// Histogram per run per detector
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dAll22;    /// 1d hist including everything for 2.2 MeV signal region
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dVtx22;    /// 1d hist after vertices distance cut for 2.2 signal region
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dAccBkg22; /// 1d hist for accidental background for 2.2 signal region
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dAccBkg22S; /// 1d hist for accidental background for 2.2 signal region, scaled by livetime
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dAcc22;    /// 1d hist after accidental background subtraction for 2.2 signal region
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dNeutron;  /// 1d hist of neutron spectrum after background subtraction

/// A set of distance plots
const double DistS = 0;
const double DistE = 5000;
const int DistB = 250;
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dDistVtx;   /// 1d hist of distance plot after coarse vertex cut      
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dDistBkg;   /// 1d hist of distance plot made of singles repository   
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dDistBkgS;   /// 1d hist of distance plot made of singles repository after scaling
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dDistAcc;   /// 1d hist of distance plot after background subtraction 

/// A set of phi plots
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dPhiVtx;   /// 1d hist of phi plot after coarse vertex cut
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dPhiBkg;   /// 1d hist of phi plot made of singles repository
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dPhiAcc;   /// 1d hist of phi plot after background subtraction

/// A set of delta t plots
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dDtVtx;   /// 1d hist of phi plot after coarse vertex cut      
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dDtBkg;   /// 1d hist of phi plot made of singles repository   
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dDtBkgS;   /// 1d hist of phi plot made of singles repository after scaling
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dDtAcc;   /// 1d hist of phi plot after background subtraction    

/// Histogram per run
map< int /* Run */, TH1F* >  h1dAll22Det    ;
map< int /* Run */, TH1F* >  h1dVtx22Det    ;
map< int /* Run */, TH1F* >  h1dAccBkg22Det ;
map< int /* Run */, TH1F* >  h1dAcc22Det    ;
map< int /* Run */, TH1F* >  h1dNeutronDet  ;

map< int /* Run */, TH1F* >  h1dDistVtxDet;
map< int /* Run */, TH1F* >  h1dDistBkgDet;
map< int /* Run */, TH1F* >  h1dDistAccDet;

map< int /* Run */, TH1F* >  h1dPhiVtxDet;
map< int /* Run */, TH1F* >  h1dPhiBkgDet;
map< int /* Run */, TH1F* >  h1dPhiAccDet;

map< int /* Run */, TH1F* >  h1dDtVtxDet;
map< int /* Run */, TH1F* >  h1dDtBkgDet;
map< int /* Run */, TH1F* >  h1dDtAccDet;


/// Histogram for all
TH1F*  h1dAll22Sum    ;
TH1F*  h1dVtx22Sum    ;
TH1F*  h1dAccBkg22Sum ;
TH1F*  h1dAcc22Sum    ;
TH1F*  h1dNeutronSum  ;

TH1F*  h1dDistVtxSum;
TH1F*  h1dDistBkgSum;
TH1F*  h1dDistAccSum;

TH1F*  h1dPhiVtxSum;
TH1F*  h1dPhiBkgSum;
TH1F*  h1dPhiAccSum;

TH1F*  h1dDtVtxSum;
TH1F*  h1dDtBkgSum;
TH1F*  h1dDtAccSum;

string h1name8[3];
string h1title8[3];

/// Histogram per run per detector
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dVtx8;     /// 1d hist after vertex distance cut for 8 MeV signal region
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dAccBkg8;  /// 1d hist for accidental background for 8 MeV signal region
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dAccBkg8S;  /// 1d hist for accidental background for 8 MeV signal region, scaled by livetime
map< int /* Run */, map< int /* AdNo */, TH1F* > >  h1dAcc8;     /// 1d hist after accidental background for 8 MeV signal region

/// Histogram per run
map< int /* AdNo */, TH1F* >  h1dVtx8Det    ;
map< int /* AdNo */, TH1F* >  h1dAccBkg8Det ;
map< int /* AdNo */, TH1F* >  h1dAcc8Det    ;

/// Histogram for all
TH1F*  h1dVtx8Sum     ;
TH1F*  h1dAccBkg8Sum  ;
TH1F*  h1dAcc8Sum     ;

/* Run-by-run record */
vector< int /* Run */ > runList;   /// Run number list
map< int /* Run */, double /* Run start time */  >  beginTime;    /// Run begin time
map< int /* Run */, double /* Run stop time */   >  endTime;      /// Run end time
map< int /* Run */, double /* Run middle time */ >  middleTime;   /// Run middle time
map< int /* Run */, map< int /* AdNo */, int /* Singles upper limit */ > > nSinglesUp;    /// Singles upper limits
map< int /* Run */, map< int /* AdNo */, int /* Singles upper limit */ > > nSinglesLow;   /// Singles lower limits
map< int /* Run */, map< int /* AdNo */, int /* 2-fold */ > > nTwoFold;    /// Number of two-fold events
map< int /* Run */, map< int /* AdNo */, int /* 3-fold */ > > nThreeFold;  /// Number of three-fold events
map< int /* Run */, map< int /* AdNo */, int /* Before Vtx Dist cut */ > > nBVtx; /// Number of generated accidental background before vtx distance cut
map< int /* Run */, map< int /* AdNo */, int /* After Vtx Dist cut */ > >  nAVtx; /// Number of generated accidental background after vtx distance cut
map< int /* Run */, map< int /* AdNo */, int /* After energy cut */ > >  nAEng; /// Number of generated accidental background after energy cut
map< int /* Run */, map< int /* AdNo */, double /* Vtx Dist cut efficiency */ > >  effVtx;  /// Vertices distance cut efficiency
map< int /* Run */, map< int /* AdNo */, double /* scale */ > >            scale;  /// Scale factor used for singles background normalization
map< int /* Run */, map< int /* AdNo */, double /* scale */ > >            scaleE;  /// Scale factor used for singles background normalization
map< int /* Run */, map< int /* AdNo */, double /* n8MeV */ > >            n8MeV;  /// Number of events for 8MeV signal
map< int /* Run */, map< int /* AdNo */, double /* n22Mev */ > >           n22MeV; /// Number of events for 2.2MeV signal
/////////////////////////////////////////////////////////////////////////////////////
map< int /* Run */, RunStat * > RunStats;

EventReader*  EvtReader;
Cuts*         Cut;
//string        RunInfoFileName = "../DataBase/RunInfo.txt";
string        RunInfoFileName = "RunInfo.txt";
Table         RunInfoTable(RunInfoFileName);

string        RunInfoOutputFile;

struct EventBrief {
  double E;
  double X,Y,Z;
};

/// Singles pool for all ADs
map<int /* AdNo */, vector< EventBrief > > SinglesPool;

int BeginRun( int run );
int EndRun( int run );

int BeginJob();
int EndJob();

/// Add Scale Error
double ScaleE;

void AddScaleError( TH1F* h1, double err );
void AddScaleError( TH2F* h2, double err );

int main(int argc, char** argv)
{
  string inputfilelist;
  vector<string> inputfiles;
  string outputfile;
  string DataSet;

  if( argc != 5 ) {
    cout<<"Usage:"<<endl;
    cout<<"    AccSub inputfiles.list output.root RunInfoOut.txt Gd|H"<<endl;
    cout<<endl;
    return 1;
  } else {
    inputfilelist = argv[1];
    outputfile = argv[2];
    RunInfoOutputFile = argv[3];
    DataSet = argv[4];

    /// The input file parsing
    ifstream inlist( inputfilelist.c_str() );
    string line;
    while( getline( inlist, line ) )  {
      inputfiles.push_back( line.c_str() );
    }
  }

  if( DataSet=="Gd" )      Cut = new Cuts( Cuts::Gd );
  else if( DataSet=="H"  ) Cut = new Cuts( Cuts::H  );
  else {
    cout<<"Unknown data set"<<endl;
    exit(0);
  }

  rootfile = new TFile( outputfile.c_str(), "recreate" );

  //TH1::SetDefaultSumw2();

  BeginJob();
  
  /// Loop over each file, i.e. in the unit of run
  /// ****************************************
  for( unsigned int i=0; i<inputfiles.size(); i++ )  {
    cout<<"Processing "<<inputfiles[i]<<endl;
    /// Add the file to be analyzed
    TChain *Event = new TChain("Event");
    Event->Add( inputfiles[i].c_str() );
    unsigned int entries = Event->GetEntries();

    EvtReader = new EventReader;
    EvtReader->Init(Event);

    int ret = EvtReader->GetEntry( 0 );
    if( ret == 0 ) {
      cout<<"Can't load Event tree entry "<<0<<endl;
    }

    int run = EvtReader->Run;

    BeginRun( run );

    /// Find the run info line for this run
    int lineNum = -1;
    for( int i=0; i<RunInfoTable.NRows; i++ ) {
      if( RunInfoTable.Columns[ "Run" ][i] == i2a( run ) ) {
	lineNum=i;
      }
    }
    if( lineNum == -1 ) {
      cout<<"No RunInfo was found for "<<run<<endl;
      exit(0);
    }
    /// Get site of this run
    int Site = atoi( RunInfoTable.Columns[ "Site" ][ lineNum ].c_str() );

    double tau;
    if( Site==1 ) {
      ScaleE = 0.0018;
      tau = 1/SingleR[0];
    }
    if( Site==2 ) {
      ScaleE = 0.0016;
      tau = 1/SingleR[1];
    }
    if( Site==4 ) {
      ScaleE = 0.0005;
      tau = 1/SingleR[2];
    }

    /// Load in everything together first. The fast way.
    /// ************************************************
    for( int Det=1; Det<=4; Det++ )  {
      SinglesPool[ Det ].clear();
    }

    for( unsigned int entry=0; entry<entries; entry++ )  {
      int ret = EvtReader->GetEntry( entry );
      if( ret == 0 ) {
	cout<<"Can't load Event tree entry "<<entry<<endl;
      }

      int Det = EvtReader->Det;
      int GlbAd = GlobalAdIdx( Site, Det );

      double dt = EvtReader->T2PrevSubEvt[0];

      /// Get singles spectrum
      if( EvtReader->Fold == 1 && 
	  dt > Cut->CoinDt/second ) {
	EventBrief aEvt;
	aEvt.E = EvtReader->E[0];
	aEvt.X = EvtReader->X[0];
	aEvt.Y = EvtReader->Y[0];
	aEvt.Z = EvtReader->Z[0];
	SinglesPool[ Det ].push_back( aEvt );
      }

      if( EvtReader->Fold == 2 ) {
	nTwoFold[ run ][ Det ] += 1;
      }
      if( EvtReader->Fold == 3 ) {
        nThreeFold[ run ][ Det ] += 1;
      }

      if( EvtReader->Fold == 2 )  {
	/// Everything 2d
	h2dAll[ run ][ Det ]->Fill( EvtReader->E[0], EvtReader->E[1] );
	/// 2.2 MeV everything
	if( EvtReader->E[1] > Cut->E22Low[GlbAd-1]/MeV && EvtReader->E[1] < Cut->E22Hgh[GlbAd-1]/MeV )  {
	  h1dAll22[ run ][ Det ]->Fill( EvtReader->E[0] );
	}

	/* Vertices distance */
	/* ################# */
	if( EvtReader->D2First[1]<Cut->D2First/mm 
	    /// && EvtReader->Z[0] > 1200
	    )  {

	  /// 2d
          h2dVtx[ run ][ Det ]->Fill( EvtReader->E[0], EvtReader->E[1] );

	  /// 8 MeV after vtx distance cut
	  if( EvtReader->E[1] > Cut->E8Low/MeV && EvtReader->E[1] < Cut->E8Hgh/MeV )  {
	    h1dVtx8[ run ][ Det ]->Fill( EvtReader->E[0] );
	    h1dDistVtx[ run ][ Det ]->Fill( EvtReader->D2First[1] );
	    h1dDtVtx[ run ][ Det ]->Fill( EvtReader->T2PrevSubEvt[1] );
	  }
	  /// 2.2 MeV
	  if( EvtReader->E[1] > Cut->E22Low[GlbAd-1]/MeV && EvtReader->E[1] < Cut->E22Hgh[GlbAd-1]/MeV )  {
	    h1dVtx22[ run ][ Det ]->Fill( EvtReader->E[0] );
	    double z  = EvtReader->Z[0];
	    double r2 = pow( EvtReader->X[0], 2 ) + pow( EvtReader->Y[0], 2 );
	    h2dZR2Vtx[ run ][ Det ]->Fill( r2, z );
	    h1dPhiVtx[ run ][ Det ]->Fill( atan2( EvtReader->Y[0], EvtReader->X[0] ) );
	  }
	}
      }

    }

    /// A double loop for sampling the prompt and delayed signal
    /// ********************************************************
    for( int Det=1; Det<=4; Det++ )  {
      int nEvt = SinglesPool[ Det ].size();
      int GlbAd = GlobalAdIdx( Site, Det );
      for( int idx=0; idx<nEvt/2-1; idx++ )  {
	int prompt = idx;                       // Prompt is from the first half
	int delayed = idx+nEvt/2;               // Delayed is from the second half

	double dx = SinglesPool[Det][prompt].X - SinglesPool[Det][delayed].X;
	double dy = SinglesPool[Det][prompt].Y - SinglesPool[Det][delayed].Y;
	double dz = SinglesPool[Det][prompt].Z - SinglesPool[Det][delayed].Z;
	double dist = sqrt( dx*dx + dy*dy + dz*dz );
	double Ep = SinglesPool[Det][prompt].E;
	double Ed = SinglesPool[Det][delayed].E;

	/// The cuts
	nBVtx[ run ][ Det ] += 2;
	if( dist<Cut->D2First/mm 
            /// && SinglesPool[Det][prompt].Z  > 1200
	    )   {
	  
	  /// Use them twice to get better background statistics
	  h2dAccBkg[ run ][ Det ]->Fill( Ep, Ed );
          ///

          if( Ed > Cut->E22Low[GlbAd-1]/MeV && Ed < Cut->E22Hgh[GlbAd-1]/MeV ) {
            h1dAccBkg22[ run ][ Det ]->Fill( Ep );

            double z  = SinglesPool[Det][prompt].Z;
            double r2 = pow( SinglesPool[Det][prompt].X, 2 ) + pow( SinglesPool[Det][prompt].Y, 2 );
            h2dZR2Bkg[ run ][ Det ]->Fill( r2, z );
	    h1dPhiBkg[ run ][ Det ]->Fill( atan2(SinglesPool[Det][prompt].Y,SinglesPool[Det][prompt].X) );
	    
	    nAEng[ run ][ Det ] += 1;
          }
	  nAVtx[ run ][ Det ] += 1;
	  ///
	  if( Ed > Cut->E8Low/MeV && Ed < Cut->E8Hgh/MeV ) {
            h1dAccBkg8[ run ][ Det ]->Fill( Ep );
	    // Distance and time
	    h1dDistBkg[ run ][ Det ]->Fill( dist );
            h1dDtBkg[ run ][ Det ]->Fill( r.Uniform( 0.9e-6, 1.5e-3 ) );
          }
	}

	/* Reverse prompt and delayed single repository */
	if( dist<Cut->D2First/mm
            /// && SinglesPool[Det][delayed].Z > 1200
            ) {

	  h2dAccBkg[ run ][ Det ]->Fill( Ed, Ep );
	  ///
	  if( Ep > Cut->E22Low[GlbAd-1]/MeV && Ep < Cut->E22Hgh[GlbAd-1]/MeV ) {
            h1dAccBkg22[ run ][ Det ]->Fill( Ed );

	    double z  = SinglesPool[Det][delayed].Z;
            double r2 = pow( SinglesPool[Det][delayed].X, 2 ) + pow( SinglesPool[Det][delayed].Y, 2 );
            h2dZR2Bkg[ run ][ Det ]->Fill( r2, z );
	    h1dPhiBkg[ run ][ Det ]->Fill( atan2(SinglesPool[Det][prompt].X,SinglesPool[Det][prompt].Y) );

	    nAEng[ run ][ Det ] += 1;
          }
	  nAVtx[ run ][ Det ] += 1;

	  // Distance and time
	  if( Ep > Cut->E8Low/MeV && Ep < Cut->E8Hgh/MeV ) {
            h1dAccBkg8[ run ][ Det ]->Fill( Ed );
	    h1dDistBkg[ run ][ Det ]->Fill( dist );
	    h1dDtBkg[ run ][ Det ]->Fill( r.Uniform( 0.9e-6, 1.5e-3 ) );
          }

	}
      }
    }
    
    EndRun( run );
    delete EvtReader;
    delete Event;
  }
  
  EndJob();

  return 1;
}

/* BeginRun: init some histograms */
/* ############################## */
int BeginRun( int run )
{
  runList.push_back( run );

  rootfile->cd();
  string newdir = i2a(run);
  rootfile->mkdir(newdir.c_str());
  rootfile->cd(newdir.c_str());

  string Run = "Run";
  RunStats[ run ] = new RunStat;

  for( int AdNo = 1; AdNo <= 4; AdNo++ )   {

    string this_h2name[n2dhists], this_h2title[n2dhists];

    this_h2name[0] = h2name[0] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2name[1] = h2name[1] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2name[2] = h2name[2] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2name[3] = h2name[3] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2name[4] = h2name[4] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2name[5] = h2name[5] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2name[6] = h2name[6] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;

    this_h2title[0] = h2title[0] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2title[1] = h2title[1] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2title[2] = h2title[2] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2title[3] = h2title[3] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2title[4] = h2title[4] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2title[5] = h2title[5] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h2title[6] = h2title[6] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    
    h2dAll[ run ][ AdNo ]    = new TH2F( this_h2name[0].c_str(), this_h2title[0].c_str(), FnBin,0,12,  FnBin,0,12 );  /// 2d hist including everything               
    h2dVtx[ run ][ AdNo ]    = new TH2F( this_h2name[1].c_str(), this_h2title[1].c_str(), FnBin,0,12,  FnBin,0,12 );  /// 2d hist after vertices distance cut
    h2dAccBkg[ run ][ AdNo ] = new TH2F( this_h2name[2].c_str(), this_h2title[2].c_str(), FnBin,0,12,  FnBin,0,12 );  /// 2d hist for accidental background
    h2dAcc[ run ][ AdNo ]    = new TH2F( this_h2name[3].c_str(), this_h2title[3].c_str(), CsBin,0,12,  CsBin,0,12 );  /// 2d hist after accidental background subtraction
    h2dZR2Vtx[ run ][ AdNo ] = new TH2F( this_h2name[4].c_str(), this_h2title[4].c_str(), 120,0,4500e3, 120,-2500,2500 );
    h2dZR2Bkg[ run ][ AdNo ] = new TH2F( this_h2name[5].c_str(), this_h2title[5].c_str(), 120,0,4500e3, 120,-2500,2500 );
    h2dZR2Acc[ run ][ AdNo ] = new TH2F( this_h2name[6].c_str(), this_h2title[6].c_str(), 120,0,4500e3, 120,-2500,2500 );

    string this_h1name[14], this_h1title[14];

    this_h1name[0] = h1name[0] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[1] = h1name[1] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[2] = h1name[2] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[3] = h1name[3] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[4] = h1name[4] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[5] = h1name[5] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[6] = h1name[6] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[7] = h1name[7] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[8] = h1name[8] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[9] = h1name[9] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[10] = h1name[10] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[11] = h1name[11] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[12] = h1name[12] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name[13] = h1name[13] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;

    this_h1title[0] = h1title[0] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[1] = h1title[1] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[2] = h1title[2] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[3] = h1title[3] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[4] = h1title[4] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[5] = h1title[5] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[6] = h1title[6] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[7] = h1title[7] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[8] = h1title[8] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[9] = h1title[9] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[10] = h1title[10] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[11] = h1title[11] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[12] = h1title[12] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title[13] = h1title[13] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;

    h1dAll22[ run ][ AdNo ]    =  new TH1F( this_h1name[0].c_str(), this_h1title[0].c_str(), CsBin,0,12 ); /// 1d hist including everything for 2.2 MeV signal region
    h1dVtx22[ run ][ AdNo ]    =  new TH1F( this_h1name[1].c_str(), this_h1title[1].c_str(), CsBin,0,12 ); /// 1d hist after vertices distance cut for 2.2 signal region
    h1dAccBkg22[ run ][ AdNo ] =  new TH1F( this_h1name[2].c_str(), this_h1title[2].c_str(), CsBin,0,12 ); /// 1d hist for accidental background for 2.2 signal region
    h1dAccBkg22S[ run ][ AdNo ] =  new TH1F( (this_h1name[2]+"S").c_str(), (this_h1title[2]+"S").c_str(), CsBin,0,12 ); /// 1d hist for accidental background for 2.2 signal region after scale
    h1dAcc22[ run ][ AdNo ]    =  new TH1F( this_h1name[3].c_str(), this_h1title[3].c_str(), CsBin,0,12 ); /// 1d hist after accidental background subtraction for 2.2 signal region
    h1dNeutron[ run ][ AdNo ]  =  new TH1F( this_h1name[4].c_str(), this_h1title[4].c_str(), FnBin,0,12 ); /// 1d hist of neutron spectrum after background subtraction
    h1dDistVtx[ run ][ AdNo ]  =  new TH1F( this_h1name[5].c_str(), this_h1title[5].c_str(), DistB,DistS,DistE );
    h1dDistBkg[ run ][ AdNo ]  =  new TH1F( this_h1name[6].c_str(), this_h1title[6].c_str(), DistB,DistS,DistE );
    h1dDistBkgS[ run ][ AdNo ]  =  new TH1F( (this_h1name[6]+"S").c_str(), (this_h1title[6]+"S").c_str(), DistB,DistS,DistE );
    h1dDistAcc[ run ][ AdNo ]  =  new TH1F( this_h1name[7].c_str(), this_h1title[7].c_str(), DistB,DistS,DistE );

    h1dPhiVtx[ run ][ AdNo ]  =  new TH1F( this_h1name[8].c_str(),  this_h1title[8].c_str(),  50,-3.1415927,3.1415927 );
    h1dPhiBkg[ run ][ AdNo ]  =  new TH1F( this_h1name[9].c_str(),  this_h1title[9].c_str(),  50,-3.1415927,3.1415927 );
    h1dPhiAcc[ run ][ AdNo ]  =  new TH1F( this_h1name[10].c_str(), this_h1title[10].c_str(), 50,-3.1415927,3.1415927 );

    h1dDtVtx[ run ][ AdNo ]  =  new TH1F( this_h1name[11].c_str(),  this_h1title[11].c_str(),  150, 0, 1.5e-3 );
    h1dDtBkg[ run ][ AdNo ]  =  new TH1F( this_h1name[12].c_str(),  this_h1title[12].c_str(),  150, 0, 1.5e-3 );
    h1dDtBkgS[ run ][ AdNo ]  =  new TH1F( (this_h1name[12]+"S").c_str(),  (this_h1title[12]+"S").c_str(),  150, 0, 1.5e-3 );
    h1dDtAcc[ run ][ AdNo ]  =  new TH1F( this_h1name[13].c_str(),  this_h1title[13].c_str(),  150, 0, 1.5e-3 );

    string this_h1name8[4], this_h1title8[4];
    
    this_h1name8[0] = h1name8[0] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name8[1] = h1name8[1] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1name8[2] = h1name8[2] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;

    this_h1title8[0] = h1title8[0] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title8[1] = h1title8[1] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;
    this_h1title8[2] = h1title8[2] +"_"+ i2a(run) +"_"+ i2a(AdNo) ;

    h1dVtx8[ run ][ AdNo ]    =  new TH1F( this_h1name8[0].c_str(), this_h1title8[0].c_str(), CsBin,0,12 );     /// 1d hist for 8 MeV signal region after vtx cut
    h1dAccBkg8[ run ][ AdNo ] =  new TH1F( this_h1name8[1].c_str(), this_h1title8[1].c_str(), CsBin,0,12 );
    h1dAccBkg8S[ run ][ AdNo ] =  new TH1F( (this_h1name8[1]+"S").c_str(), (this_h1title8[1]+"S").c_str(), CsBin,0,12 );
    h1dAcc8[ run ][ AdNo ]    =  new TH1F( this_h1name8[2].c_str(), this_h1title8[2].c_str(), CsBin,0,12 );

    nBVtx[ run ][ AdNo ] = 0;
    nAVtx[ run ][ AdNo ] = 0;
    nAEng[ run ][ AdNo ] = 0;
    effVtx[ run ][ AdNo ] = 0;
    
    nSinglesUp[ run ][ AdNo ] = 0;
    nSinglesLow[ run ][ AdNo ] = 0;

    nTwoFold[ run ][ AdNo ] = 0;
    nThreeFold[ run ][ AdNo ] = 0;
  }

  return 1;
}

int EndRun( int run ) 
{
  /// Find the run info line for this run
  int lineNum = -1;
  for( int i=0; i<RunInfoTable.NRows; i++ )   {
    if( RunInfoTable.Columns[ "Run" ][i] == i2a( run ) )  {
      lineNum=i;
    }
  }
  if( lineNum == -1 ) {
    cout<<"No RunInfo was found for "<<run<<endl;
    exit(0);
  }

  /// Get live time and nSingles;
  double Fulltime = atof( RunInfoTable.Columns[ "FullTime" ][ lineNum ].c_str() );
  int Site        = atoi( RunInfoTable.Columns[ "Site" ][ lineNum ].c_str() );

  map< int /* AdNo */, double> Veto, Livetime;
  map< int /* AdNo */, int   > NNetMu;
  map< int /* AdNo */, double> nSinglesMean, nSinglesErr;

  Veto[1]         = atof( RunInfoTable.Columns[ "Veto1" ][ lineNum ].c_str() );
  Veto[2]         = atof( RunInfoTable.Columns[ "Veto2" ][ lineNum ].c_str() );
  Veto[3]         = atof( RunInfoTable.Columns[ "Veto3" ][ lineNum ].c_str() );
  Veto[4]         = atof( RunInfoTable.Columns[ "Veto4" ][ lineNum ].c_str() );

  NNetMu[1]       = atoi( RunInfoTable.Columns[ "NNet1" ][ lineNum ].c_str() );
  NNetMu[2]       = atoi( RunInfoTable.Columns[ "NNet2" ][ lineNum ].c_str() );
  NNetMu[3]       = atoi( RunInfoTable.Columns[ "NNet3" ][ lineNum ].c_str() );
  NNetMu[4]       = atoi( RunInfoTable.Columns[ "NNet4" ][ lineNum ].c_str() );

  nSinglesUp[run][1]  = atoi( RunInfoTable.Columns[ "NSgUp1" ][ lineNum ].c_str() );
  nSinglesLow[run][1] = atoi( RunInfoTable.Columns[ "NSgLw1" ][ lineNum ].c_str() );
  nSinglesUp[run][2]  = atoi( RunInfoTable.Columns[ "NSgUp2" ][ lineNum ].c_str() );
  nSinglesLow[run][2] = atoi( RunInfoTable.Columns[ "NSgLw2" ][ lineNum ].c_str() );
  nSinglesUp[run][3]  = atoi( RunInfoTable.Columns[ "NSgUp3" ][ lineNum ].c_str() );
  nSinglesLow[run][3] = atoi( RunInfoTable.Columns[ "NSgLw3" ][ lineNum ].c_str() );
  nSinglesUp[run][4]  = atoi( RunInfoTable.Columns[ "NSgUp4" ][ lineNum ].c_str() );
  nSinglesLow[run][4] = atoi( RunInfoTable.Columns[ "NSgLw4" ][ lineNum ].c_str() );

  double correction = 0;
  if( Site==1 ) correction = 0.0009;
  if( Site==2 ) correction = 0.00082;
  if( Site==4 ) correction = 0.00023;

  double Corr = 1;  // Low energy region bias corrected with Vertex/Zero/ZeroLowCorr.C
  if( Site==1 ) Corr = 0.998106;
  if( Site==2 ) Corr = 0.998475;
  if( Site==4 ) Corr = 0.999068;

  /// Normalize each AccBkg histogram and do background subtraction
  for( int AdNo = 1; AdNo <= 4; AdNo++ )   {
    Livetime[AdNo]     = Fulltime - Veto[AdNo];
    /*
    nSinglesMean[AdNo] = (nSinglesUp[run][AdNo] + nSinglesLow[run][AdNo])/2.0;
    nSinglesErr[AdNo]  = (nSinglesUp[run][AdNo] - nSinglesLow[run][AdNo])/2.0;
    */
    nSinglesMean[AdNo] = nSinglesUp[run][AdNo] * (1-correction);
    nSinglesErr[AdNo]  = nSinglesUp[run][AdNo] * correction;
    /* Diff/2 is 3 sigma. Here I may need just 1 sigma. But anyway it is small.*/

    /// Relative distance cut efficiency
    if( nSinglesMean[ AdNo ] > 0 )   {
      /// For working detectors
      effVtx[ run ][ AdNo ] = (double)nAVtx[ run ][ AdNo ] / nBVtx[ run ][ AdNo ];
    } else { 
      /// For non-working detectors
      effVtx[ run ][ AdNo ] = 0;
    }
    
    /// Need the background spectrum from the last good run, because of a low statistics.
    static int LastGoodBkgRun = 0;
    int    GoodBkgRun = run;
    double bkgEntries = h2dAccBkg[ run ][ AdNo ]->GetEntries();
    if( bkgEntries <= 5000 && LastGoodBkgRun != 0) {
      GoodBkgRun = LastGoodBkgRun;
    } else {
      LastGoodBkgRun = run;
    }
    bkgEntries = h2dAccBkg[ GoodBkgRun ][ AdNo ]->GetEntries();

    /// A new precise rate calculation
    double Rs = nSinglesMean[ AdNo ] / Livetime[ AdNo ];
    double Rmu = NNetMu[ AdNo ] / Livetime[ AdNo ];
    double Tc = Cut->CoinDt/second;

    /// Remove one micro second for the full length of the readout window
    double R_s_s_pair = RSS_DYB( Rs, Rmu, Tc );
    
    double NormalizationFactor = R_s_s_pair * Livetime[ AdNo ] * effVtx[ GoodBkgRun ][ AdNo ];

    /// The old one, higher than true value by a 5-10%
    ///double NormalizationFactor = nSinglesMean[ AdNo ] / Livetime[ AdNo ] * Cut->CoinDt/second * effVtx[ GoodBkgRun ][ AdNo ] * nSinglesMean[ AdNo ];
    
    cout<<"bkgEntries= "<<bkgEntries<<"  NormalizationFactor= "<<NormalizationFactor
	<<" R_s_s_pair= "<<R_s_s_pair<<" Livetime= "<<Livetime[ AdNo ]<<" effVtx= "<<effVtx[ GoodBkgRun ][ AdNo ]
	<<" Rs= "<<Rs<<" RMu= "<<Rmu<<endl;

    /// Scale factor
    double this_scale;
    if( bkgEntries==0 )   {
      this_scale = 0;
    } else {
      this_scale = -NormalizationFactor/bkgEntries * Corr;
    }

    /// Fine binning 2d plots can be downgraded.
    CsVtxTmp = *( h2dVtx[ run ][ AdNo ] );
    CsBkgTmp = *( h2dAccBkg[ GoodBkgRun ][ AdNo ] );
    
    CsVtxTmp.Rebin2D(10,10);
    CsBkgTmp.Rebin2D(10,10);

    /// 2d energy plot
    h2dAcc[ run ][ AdNo ]   -> Add( &CsVtxTmp, &CsBkgTmp, 1, this_scale );
    /// 2d vertex plot
    h2dZR2Acc[ run ][ AdNo ]-> Add( h2dZR2Vtx[ run ][ AdNo ],h2dZR2Bkg[ GoodBkgRun ][ AdNo ], 1, this_scale );
    /// distance plot
    h1dDistAcc[ run ][ AdNo ]-> Add( h1dDistVtx[ run ][ AdNo ],h1dDistBkg[ GoodBkgRun ][ AdNo ], 1, this_scale );
    /// phi plot
    h1dPhiAcc[ run ][ AdNo ]-> Add( h1dPhiVtx[ run ][ AdNo ],h1dPhiBkg[ GoodBkgRun ][ AdNo ], 1, this_scale );
    /// Dt plot
    h1dDtAcc[ run ][ AdNo ]-> Add( h1dDtVtx[ run ][ AdNo ],h1dDtBkg[ GoodBkgRun ][ AdNo ], 1, this_scale );
    /// prompt in 2.2 MeV region
    h1dAcc22[ run ][ AdNo ] -> Add( h1dVtx22[ run ][ AdNo ], h1dAccBkg22[ GoodBkgRun ][ AdNo ], 1, this_scale );
    /// prompt in 8 MeV region
    h1dAcc8[ run ][ AdNo ]  -> Add( h1dVtx8[ run ][ AdNo ],  h1dAccBkg8[ GoodBkgRun ][ AdNo ], 1, this_scale );

    /// high resolution neutron energy spectrum
    TH1D * NentronSpec = h2dVtx[ run ][ AdNo ]->ProjectionY();
    TH1D * AccBkgSpec  = h2dAccBkg[ GoodBkgRun ][ AdNo ]->ProjectionY();
    h1dNeutron[ run ][ AdNo ] -> Add( NentronSpec, AccBkgSpec, 1, this_scale );

    scale[ run ][ AdNo ] = this_scale;

    /// Output nGd and nH number of signals
    int nbins = h1dAcc22[ run ][ AdNo ]->GetNbinsX();
    n22MeV[ run ][ AdNo ] = 0;
    n8MeV[ run ][ AdNo ]  = 0;
    for( int bidx = 1; bidx <= nbins; bidx++ )   {
      n22MeV[ run ][ AdNo ] += h1dAcc22[ run ][ AdNo ] -> GetBinContent(bidx);
      n8MeV[ run ][ AdNo ]  += h1dAcc8[ run ][ AdNo ] ->  GetBinContent(bidx);
    }

    /// Calculate the error bars for h1dAcc22[ run ][ AdNo ] and h1dNeutron[ run ][ AdNo ]
    double rerr_Nsgl;
    if( nSinglesMean[ AdNo ] == 0 )   {
      rerr_Nsgl = 0;
    } else {
      // All these errors are correlated error between runs.
      // Revised and moved to the end
      //rerr_Nsgl = sqrt( pow(nSinglesErr[ AdNo ] / nSinglesMean[ AdNo ], 2) + 0.01*0.01 + 0.001*0.001 );
      rerr_Nsgl = 0;
    }
    cout<<"rerr_Nsgl = "<<rerr_Nsgl<<endl;
    double rerr_nBVtx;
    if( nBVtx[ GoodBkgRun ][ AdNo ] == 0 )   {
      rerr_nBVtx = 0;
    } else {
      rerr_nBVtx = 1/sqrt( nBVtx[ GoodBkgRun ][ AdNo ] );
    }

    double err_scale = this_scale * sqrt( 4*rerr_Nsgl*rerr_Nsgl + rerr_nBVtx * rerr_nBVtx );
    cout<<"this_scale = "<<this_scale<<"  err_scale = "<<err_scale<<endl;

    /// Set error bar for nGd prompt
    nbins = h1dAcc8[ run ][ AdNo ]->GetNbinsX();
    for( int bidx = 1; bidx <= nbins; bidx++ ) {
      //double base     = h1dVtx8[ run ][ AdNo ]    -> GetBinContent(bidx);
      double addi     = h1dAccBkg8[ GoodBkgRun ][ AdNo ] -> GetBinContent(bidx);
      double err_base = h1dVtx8[ run ][ AdNo ]           -> GetBinError(bidx);
      double err_addi = h1dAccBkg8[ GoodBkgRun ][ AdNo ] -> GetBinError(bidx);

      double err = sqrt( (err_base*err_base) +
                         addi*addi * err_scale*err_scale +
                         err_addi*err_addi * this_scale*this_scale );

      h1dAcc8[ run ][ AdNo ] -> SetBinError( bidx, err );
      
      h1dAccBkg8S[ run ][ AdNo ] -> SetBinContent( bidx, -this_scale * addi);
      h1dAccBkg8S[ run ][ AdNo ] -> SetBinError( bidx, sqrt(addi*addi * err_scale*err_scale +
							    err_addi*err_addi * this_scale*this_scale ) );
    }

    /// Set error bar for nH prompt
    nbins = h1dAcc22[ run ][ AdNo ]->GetNbinsX();
    for( int bidx = 1; bidx <= nbins; bidx++ )   {
      //double base     = h1dVtx22[ run ][ AdNo ]    -> GetBinContent(bidx);
      double addi     = h1dAccBkg22[ GoodBkgRun ][ AdNo ] -> GetBinContent(bidx);
      double err_base = h1dVtx22[ run ][ AdNo ]           -> GetBinError(bidx);
      double err_addi = h1dAccBkg22[ GoodBkgRun ][ AdNo ] -> GetBinError(bidx);

      double err = sqrt( (err_base*err_base) +
			 addi*addi * err_scale*err_scale +
			 err_addi*err_addi * this_scale*this_scale );

      h1dAcc22[ run ][ AdNo ] -> SetBinError( bidx, err );

      h1dAccBkg22S[ run ][ AdNo ] -> SetBinContent( bidx, -this_scale * addi);
      h1dAccBkg22S[ run ][ AdNo ] -> SetBinError( bidx, sqrt(addi*addi * err_scale*err_scale +
							     err_addi*err_addi * this_scale*this_scale ) );
    }
    
    /// neutron spectrum
    nbins = h1dNeutron[ run ][ AdNo ]->GetNbinsX();
    for( int bidx = 1; bidx <= nbins; bidx++ ) {
      //double base     = h1dVtx22[ run ][ AdNo ]    -> GetBinContent(bidx);
      double addi     = AccBkgSpec  -> GetBinContent(bidx);
      double err_base = NentronSpec -> GetBinError(bidx);
      double err_addi = AccBkgSpec  -> GetBinError(bidx);

      double err = sqrt( (err_base*err_base) +
                         addi*addi * err_scale*err_scale +
                         err_addi*err_addi * this_scale*this_scale );

      h1dNeutron[ run ][ AdNo ] -> SetBinError( bidx, err );
    }

    /// The distance distribution after accidental subtraction
    nbins = h1dDistAcc[ run ][ AdNo ]->GetNbinsX();
    for( int bidx = 1; bidx <= nbins; bidx++ ) {
      //double base     = h1dVtx22[ run ][ AdNo ]    -> GetBinContent(bidx);
      double addi     = h1dDistBkg[ GoodBkgRun ][ AdNo ] -> GetBinContent(bidx);
      double err_base = h1dDistVtx[ run ][ AdNo ]        -> GetBinError(bidx);
      double err_addi = h1dDistBkg[ GoodBkgRun ][ AdNo ] -> GetBinError(bidx);

      double err = sqrt( (err_base*err_base) +
                         addi*addi * err_scale*err_scale +
                         err_addi*err_addi * this_scale*this_scale );

      h1dDistAcc[ run ][ AdNo ] -> SetBinError( bidx, err );
      h1dDistBkgS[ run ][ AdNo ] -> SetBinContent( bidx, -this_scale * addi);
      h1dDistBkgS[ run ][ AdNo ] -> SetBinError( bidx, sqrt(addi*addi * err_scale*err_scale +
							    err_addi*err_addi * this_scale*this_scale ) );
    }


    nbins = h1dPhiAcc[ run ][ AdNo ]->GetNbinsX();
    for( int bidx = 1; bidx <= nbins; bidx++ ) {
      //double base     = h1dVtx22[ run ][ AdNo ]    -> GetBinContent(bidx);
      double addi     = h1dPhiBkg[ GoodBkgRun ][ AdNo ] -> GetBinContent(bidx);
      double err_base = h1dPhiVtx[ run ][ AdNo ]        -> GetBinError(bidx);
      double err_addi = h1dPhiBkg[ GoodBkgRun ][ AdNo ] -> GetBinError(bidx);

      double err = sqrt( (err_base*err_base) +
                         addi*addi * err_scale*err_scale +
                         err_addi*err_addi * this_scale*this_scale );

      h1dPhiAcc[ run ][ AdNo ] -> SetBinError( bidx, err );
    }

    nbins = h1dDtAcc[ run ][ AdNo ]->GetNbinsX();
    for( int bidx = 1; bidx <= nbins; bidx++ ) {
      double addi     = h1dDtBkg[ GoodBkgRun ][ AdNo ] -> GetBinContent(bidx);
      double err_base = h1dDtVtx[ run ][ AdNo ]        -> GetBinError(bidx);
      double err_addi = h1dDtBkg[ GoodBkgRun ][ AdNo ] -> GetBinError(bidx);

      double err = sqrt( (err_base*err_base) +
                         addi*addi * err_scale*err_scale +
                         err_addi*err_addi * this_scale*this_scale );

      h1dDtAcc[ run ][ AdNo ] -> SetBinError( bidx, err );
      h1dDtBkgS[ run ][ AdNo ] -> SetBinContent( bidx, -this_scale * addi);
      h1dDtBkgS[ run ][ AdNo ] -> SetBinError( bidx, sqrt(addi*addi * err_scale*err_scale +
							  err_addi*err_addi * this_scale*this_scale ) );
    }

  }

  RunStats[ run ]->RunNumber = run;
  
  RunStats[ run ]->IsCalib = 0;
  RunStats[ run ]->Axis = 0;
  RunStats[ run ]->Source = 0;
  RunStats[ run ]->Z = 0;

  RunStats[ run ]->Site = Site;
  RunStats[ run ]->StartSec = 0;
  RunStats[ run ]->StartNano = 0;
  RunStats[ run ]->EndSec = 0;
  RunStats[ run ]->EndNano = 0;
  RunStats[ run ]->FullTime = Fulltime;

  RunStats[ run ]->Veto1 = Veto[1];
  RunStats[ run ]->Veto2 = Veto[2];
  RunStats[ run ]->Veto3 = Veto[3];
  RunStats[ run ]->Veto4 = Veto[4];

  RunStats[ run ]->Scale1 = scale[ run ][ 1 ];
  RunStats[ run ]->Scale2 = scale[ run ][ 2 ];
  RunStats[ run ]->Scale3 = scale[ run ][ 3 ];
  RunStats[ run ]->Scale4 = scale[ run ][ 4 ];

  RunStats[ run ]->ScaleE1 = ScaleE;
  RunStats[ run ]->ScaleE2 = ScaleE;
  RunStats[ run ]->ScaleE3 = ScaleE;
  RunStats[ run ]->ScaleE4 = ScaleE;

  string Run = "Run";
  RunStats[ run ]->Write( (Run+i2a(run)).c_str() );
  
  return 1;
}

int BeginJob()
{
  /// Prepare job level histogram
  h2dAllSum    = new TH2F("h2dAllSum",    "All events",                              FnBin,0,12, FnBin,0,12  );
  h2dVtxSum    = new TH2F("h2dVtxSum",    "After vertices distance cut",             FnBin,0,12, FnBin,0,12  );
  h2dAccBkgSum = new TH2F("h2dAccBkgSum", "Accidental background made by singles",   FnBin,0,12, FnBin,0,12  );
  h2dAccSum    = new TH2F("h2dAccSum",    "After accidental background subtraction", CsBin,0,12, CsBin,0,12  );

  /// Vertex distribution
  h2dZR2VtxSum = new TH2F("h2dZR2VtxSum", "Z vs R^2 after vertex distance cut",     120,0,4500e3, 120,-2500,2500  );
  h2dZR2BkgSum = new TH2F("h2dZR2BkgSum", "Z vs R^2 made of singles repository",    120,0,4500e3, 120,-2500,2500  );
  h2dZR2AccSum = new TH2F("h2dZR2AccSum", "Z vs R^2 after background subtraction",  120,0,4500e3, 120,-2500,2500  );

  h1dAll22Sum    = new TH1F("h1dAll22Sum",    "All events for 2.2 MeV region",                              CsBin,0,12  );
  h1dVtx22Sum    = new TH1F("h1dVtx22Sum",    "After vertices distance cut for 2.2 MeV region",             CsBin,0,12  );
  h1dAccBkg22Sum = new TH1F("h1dAccBkg22Sum", "Accidental background made by singles for 2.2 MeV region",   CsBin,0,12  );
  h1dAcc22Sum    = new TH1F("h1dAcc22Sum",    "After accidental background subtraction for 2.2 MeV region", CsBin,0,12  );
  h1dNeutronSum  = new TH1F("h1dNeutronSum",  "Neutron spectrum after background subtraction",              FnBin,0,12  );

  h1dDistVtxSum = new TH1F("h1dDistVtxSum", "Distance plot after coarse vertex cut",       DistB,DistS,DistE  );
  h1dDistBkgSum = new TH1F("h1dDistBkgSum", "Distance plot made of singles repository",    DistB,DistS,DistE  );
  h1dDistAccSum = new TH1F("h1dDistAccSum", "Distance plot after background subtraction",  DistB,DistS,DistE  );

  h1dPhiVtxSum = new TH1F("h1dPhiVtxSum", "Phi plot after coarse vertex cut",       50,-3.1415927,3.1415927  );
  h1dPhiBkgSum = new TH1F("h1dPhiBkgSum", "Phi plot made of singles repository",    50,-3.1415927,3.1415927  );
  h1dPhiAccSum = new TH1F("h1dPhiAccSum", "Phi plot after background subtraction",  50,-3.1415927,3.1415927  );

  h1dDtVtxSum = new TH1F("h1dDtVtxSum", "Dt plot after coarse vertex cut",       150, 0, 1.5e-3  );
  h1dDtBkgSum = new TH1F("h1dDtBkgSum", "Dt plot made of singles repository",    150, 0, 1.5e-3  );
  h1dDtAccSum = new TH1F("h1dDtAccSum", "Dt plot after background subtraction",  150, 0, 1.5e-3  );

  h1dVtx8Sum     = new TH1F("h1dVtx8Sum",     "8 MeV region with vtx cut",                                  CsBin,0,12  );
  h1dAccBkg8Sum  = new TH1F("h1dAccBkg8Sum",  "Accidental background made by singles for 8 MeV region",     CsBin,0,12  );
  h1dAcc8Sum     = new TH1F("h1dAcc8Sum",     "8 MeV region after accidental background subtraction",       CsBin,0,12  );

  /// Set axis titles
  h2dAllSum      ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h2dAllSum      ->GetYaxis()->SetTitle("Delayed  Energy [MeV]");
  h2dVtxSum      ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h2dVtxSum      ->GetYaxis()->SetTitle("Delayed  Energy [MeV]");
  h2dAccBkgSum   ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h2dAccBkgSum   ->GetYaxis()->SetTitle("Delayed  Energy [MeV]");
  h2dAccSum      ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h2dAccSum      ->GetYaxis()->SetTitle("Delayed  Energy [MeV]");

  h2dZR2VtxSum   ->GetXaxis()->SetTitle("Prompt R^{2} [mm^{2}]");
  h2dZR2VtxSum   ->GetYaxis()->SetTitle("Prompt Z [mm]");
  h2dZR2BkgSum   ->GetXaxis()->SetTitle("Prompt R^{2} [mm^{2}]");
  h2dZR2BkgSum   ->GetYaxis()->SetTitle("Prompt Z [mm]");
  h2dZR2AccSum   ->GetXaxis()->SetTitle("Prompt R^{2} [mm^{2}]");
  h2dZR2AccSum   ->GetYaxis()->SetTitle("Prompt Z [mm]");

  h1dAll22Sum    ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h1dVtx22Sum    ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h1dAccBkg22Sum ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h1dAcc22Sum    ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h1dNeutronSum  ->GetXaxis()->SetTitle("Delayed Energy [MeV]");
  		 
  h1dVtx8Sum     ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h1dAccBkg8Sum  ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  h1dAcc8Sum     ->GetXaxis()->SetTitle("Prompt Energy [MeV]");

  h1dAll22Sum    ->GetYaxis()->SetTitle("Entries/0.1MeV");
  h1dVtx22Sum    ->GetYaxis()->SetTitle("Entries/0.1MeV");
  h1dAccBkg22Sum ->GetYaxis()->SetTitle("Entries/0.1MeV");
  h1dAcc22Sum    ->GetYaxis()->SetTitle("Entries/0.1MeV");
  h1dNeutronSum  ->GetYaxis()->SetTitle("Entries/0.01MeV");

  h1dDistVtxSum  ->GetXaxis()->SetTitle("Distance [mm]");
  h1dDistBkgSum  ->GetXaxis()->SetTitle("Distance [mm]");
  h1dDistAccSum  ->GetXaxis()->SetTitle("Distance [mm]");
  
  h1dPhiVtxSum  ->GetXaxis()->SetTitle("Phi");
  h1dPhiBkgSum  ->GetXaxis()->SetTitle("Phi");
  h1dPhiAccSum  ->GetXaxis()->SetTitle("Phi");

  h1dVtx8Sum     ->GetYaxis()->SetTitle("Entries/0.1MeV");
  h1dAccBkg8Sum  ->GetYaxis()->SetTitle("Entries/0.1MeV");
  h1dAcc8Sum     ->GetYaxis()->SetTitle("Entries/0.1MeV");

  h1dDistVtxSum  ->GetYaxis()->SetTitle("Entries/20 mm");
  h1dDistBkgSum  ->GetYaxis()->SetTitle("Entries/20 mm");
  h1dDistAccSum  ->GetYaxis()->SetTitle("Entries/20 mm");

  h1dPhiVtxSum  ->GetYaxis()->SetTitle("Entries/(Pi/50)");
  h1dPhiBkgSum  ->GetYaxis()->SetTitle("Entries/(Pi/50)");
  h1dPhiAccSum  ->GetYaxis()->SetTitle("Entries/(Pi/50)");

  h2dZR2AccSum   ->GetXaxis()->SetTitle("R^{2} [mm^{2}]");
  h2dZR2AccSum   ->GetYaxis()->SetTitle("Z [mm]");

  h2name[0] = "h2dAll"   ;
  h2name[1] = "h2dVtx"   ;
  h2name[2] = "h2dAccBkg";
  h2name[3] = "h2dAcc"   ;
  h2name[4] = "h2dZR2Vtx";
  h2name[5] = "h2dZR2Bkg";
  h2name[6] = "h2dZR2Acc";

  h2title[0] = "All events"                              ;
  h2title[1] = "After vertices distance cut"             ;
  h2title[2] = "Accidental background made by singles"   ;
  h2title[3] = "After accidental background subtraction" ;
  h2title[4] = "Z vs R^2 after vertex distance cut"      ; 
  h2title[5] = "Z vs R^2 made of singles repository"     ;
  h2title[6] = "Z vs R^2 after background subtraction"   ;

  h1name[0] = "h1dAll22"   ;
  h1name[1] = "h1dVtx22"   ;
  h1name[2] = "h1dAccBkg22";
  h1name[3] = "h1dAcc22"   ;
  h1name[4] = "h1dNeutron" ;
  h1name[5] = "h1dDistVtx" ;
  h1name[6] = "h1dDistBkg" ;
  h1name[7] = "h1dDistAcc" ;
  h1name[8] = "h1dPhiVtx" ;
  h1name[9] = "h1dPhiBkg" ;
  h1name[10]= "h1dPhiAcc" ;
  h1name[11]= "h1dDtVtx" ;
  h1name[12]= "h1dDtBkg" ;
  h1name[13]= "h1dDtAcc" ;

  h1title[0] = "All events for 2.2 MeV region"                              ;
  h1title[1] = "After vertices distance cut for 2.2 MeV region"             ;
  h1title[2] = "Accidental background made by singles for 2.2 MeV region"   ;
  h1title[3] = "After accidental background subtraction for 2.2 MeV region" ;
  h1title[4] = "Neutron spectrum after background subtraction"              ;
  h1title[5] = "Distance plot after coarse vertex cut"     ;
  h1title[6] = "Distance plot made of singles repository"  ;
  h1title[7] = "Distance plot after background subtraction";
  h1title[8] = "Phi plot after coarse vertex cut"     ;
  h1title[9] = "Phi plot made of singles repository"  ;
  h1title[10]= "Phi plot after background subtraction";
  h1title[11]= "Dt plot after coarse vertex cut"     ;
  h1title[12]= "Dt plot made of singles repository"  ;
  h1title[13]= "Dt plot after background subtraction";

  h1name8[0]  = "h1dVtx8";
  h1name8[1]  = "h1dAccBkg8";
  h1name8[2]  = "h1dAcc8";

  h1title8[0] = "All events for 8 MeV region with vtx cut";
  h1title8[1] = "Accidental background made by singles for 8 MeV region"   ;
  h1title8[2] = "All events for 8 MeV region after bkg subtraction";

  for( int AdNo = 1; AdNo<=4; AdNo++ )   {

    /// 2-d histogram
    string this_h2name[n2dhists], this_h2title[n2dhists];

    this_h2name[0] = h2name[0] +"_"+ i2a(AdNo) ;
    this_h2name[1] = h2name[1] +"_"+ i2a(AdNo) ;
    this_h2name[2] = h2name[2] +"_"+ i2a(AdNo) ;
    this_h2name[3] = h2name[3] +"_"+ i2a(AdNo) ;
    this_h2name[4] = h2name[4] +"_"+ i2a(AdNo) ;
    this_h2name[5] = h2name[5] +"_"+ i2a(AdNo) ;
    this_h2name[6] = h2name[6] +"_"+ i2a(AdNo) ;

    this_h2title[0] = h2title[0] +"_"+ i2a(AdNo) ;
    this_h2title[1] = h2title[1] +"_"+ i2a(AdNo) ;
    this_h2title[2] = h2title[2] +"_"+ i2a(AdNo) ;
    this_h2title[3] = h2title[3] +"_"+ i2a(AdNo) ;
    this_h2title[4] = h2title[4] +"_"+ i2a(AdNo) ;
    this_h2title[5] = h2title[5] +"_"+ i2a(AdNo) ;
    this_h2title[6] = h2title[6] +"_"+ i2a(AdNo) ;

    h2dAllDet[ AdNo ]    = new TH2F( this_h2name[0].c_str(), this_h2title[0].c_str(), FnBin,0,12,  FnBin,0,12 );
    h2dVtxDet[ AdNo ]    = new TH2F( this_h2name[1].c_str(), this_h2title[1].c_str(), FnBin,0,12,  FnBin,0,12 );
    h2dAccBkgDet[ AdNo ] = new TH2F( this_h2name[2].c_str(), this_h2title[2].c_str(), FnBin,0,12,  FnBin,0,12 );
    h2dAccDet[ AdNo ]    = new TH2F( this_h2name[3].c_str(), this_h2title[3].c_str(), CsBin,0,12,  CsBin,0,12 );
    h2dZR2VtxDet[ AdNo ] = new TH2F( this_h2name[4].c_str(), this_h2title[4].c_str(), 120,0,4500e3, 120,-2500,2500 );
    h2dZR2BkgDet[ AdNo ] = new TH2F( this_h2name[5].c_str(), this_h2title[5].c_str(), 120,0,4500e3, 120,-2500,2500 );
    h2dZR2AccDet[ AdNo ] = new TH2F( this_h2name[6].c_str(), this_h2title[6].c_str(), 120,0,4500e3, 120,-2500,2500 );

    /// 2.2 MeV region
    string this_h1name[14], this_h1title[14];

    this_h1name[0] = h1name[0] +"_"+ i2a(AdNo) ;
    this_h1name[1] = h1name[1] +"_"+ i2a(AdNo) ;
    this_h1name[2] = h1name[2] +"_"+ i2a(AdNo) ;
    this_h1name[3] = h1name[3] +"_"+ i2a(AdNo) ;
    this_h1name[4] = h1name[4] +"_"+ i2a(AdNo) ;
    this_h1name[5] = h1name[5] +"_"+ i2a(AdNo) ;
    this_h1name[6] = h1name[6] +"_"+ i2a(AdNo) ;
    this_h1name[7] = h1name[7] +"_"+ i2a(AdNo) ;
    this_h1name[8] = h1name[8] +"_"+ i2a(AdNo) ;
    this_h1name[9] = h1name[9] +"_"+ i2a(AdNo) ;
    this_h1name[10] = h1name[10] +"_"+ i2a(AdNo) ;
    this_h1name[11] = h1name[11] +"_"+ i2a(AdNo) ;
    this_h1name[12] = h1name[12] +"_"+ i2a(AdNo) ;
    this_h1name[13] = h1name[13] +"_"+ i2a(AdNo) ;

    this_h1title[0] = h1title[0] +"_"+ i2a(AdNo) ;
    this_h1title[1] = h1title[1] +"_"+ i2a(AdNo) ;
    this_h1title[2] = h1title[2] +"_"+ i2a(AdNo) ;
    this_h1title[3] = h1title[3] +"_"+ i2a(AdNo) ;
    this_h1title[4] = h1title[4] +"_"+ i2a(AdNo) ;
    this_h1title[5] = h1title[5] +"_"+ i2a(AdNo) ;
    this_h1title[6] = h1title[6] +"_"+ i2a(AdNo) ;
    this_h1title[7] = h1title[7] +"_"+ i2a(AdNo) ;
    this_h1title[8] = h1title[8] +"_"+ i2a(AdNo) ;
    this_h1title[9] = h1title[9] +"_"+ i2a(AdNo) ;
    this_h1title[10] = h1title[10] +"_"+ i2a(AdNo) ;
    this_h1title[11] = h1title[11] +"_"+ i2a(AdNo) ;
    this_h1title[12] = h1title[12] +"_"+ i2a(AdNo) ;
    this_h1title[13] = h1title[13] +"_"+ i2a(AdNo) ;

    h1dAll22Det[ AdNo ]    =  new TH1F( this_h1name[0].c_str(), this_h1title[0].c_str(), CsBin,0,12 );
    h1dVtx22Det[ AdNo ]    =  new TH1F( this_h1name[1].c_str(), this_h1title[1].c_str(), CsBin,0,12 );
    h1dAccBkg22Det[ AdNo ] =  new TH1F( this_h1name[2].c_str(), this_h1title[2].c_str(), CsBin,0,12 );
    h1dAcc22Det[ AdNo ]    =  new TH1F( this_h1name[3].c_str(), this_h1title[3].c_str(), CsBin,0,12 );
    h1dNeutronDet[ AdNo ]  =  new TH1F( this_h1name[4].c_str(), this_h1title[4].c_str(), FnBin,0,12 );

    h1dDistVtxDet[ AdNo ]  =  new TH1F( this_h1name[5].c_str(), this_h1title[5].c_str(), DistB,DistS,DistE );
    h1dDistBkgDet[ AdNo ]  =  new TH1F( this_h1name[6].c_str(), this_h1title[6].c_str(), DistB,DistS,DistE );
    h1dDistAccDet[ AdNo ]  =  new TH1F( this_h1name[7].c_str(), this_h1title[7].c_str(), DistB,DistS,DistE );

    h1dPhiVtxDet[ AdNo ]  =  new TH1F( this_h1name[8].c_str(),  this_h1title[8].c_str(),  50,-3.1415927,3.1415927  );
    h1dPhiBkgDet[ AdNo ]  =  new TH1F( this_h1name[9].c_str(),  this_h1title[9].c_str(),  50,-3.1415927,3.1415927  );
    h1dPhiAccDet[ AdNo ]  =  new TH1F( this_h1name[10].c_str(), this_h1title[10].c_str(), 50,-3.1415927,3.1415927  );

    h1dDtVtxDet[ AdNo ]  =  new TH1F( this_h1name[11].c_str(), this_h1title[11].c_str(),  150, 0, 1.5e-3  );
    h1dDtBkgDet[ AdNo ]  =  new TH1F( this_h1name[12].c_str(), this_h1title[12].c_str(),  150, 0, 1.5e-3  );
    h1dDtAccDet[ AdNo ]  =  new TH1F( this_h1name[13].c_str(), this_h1title[13].c_str(),  150, 0, 1.5e-3  );

    /// 8 MeV region
    string this_h1name8[3];
    string this_h1title8[3];

    this_h1name8[0] = h1name8[0] +"_"+ i2a(AdNo) ;
    this_h1name8[1] = h1name8[1] +"_"+ i2a(AdNo) ;
    this_h1name8[2] = h1name8[2] +"_"+ i2a(AdNo) ;

    this_h1title8[0] = h1title8[0] +"_"+ i2a(AdNo) ;
    this_h1title8[1] = h1title8[1] +"_"+ i2a(AdNo) ;
    this_h1title8[2] = h1title8[2] +"_"+ i2a(AdNo) ;

    h1dVtx8Det[ AdNo ]    =  new TH1F( this_h1name8[0].c_str(), this_h1title8[0].c_str(), CsBin,0,12 );
    h1dAccBkg8Det[ AdNo ] =  new TH1F( this_h1name8[1].c_str(), this_h1title8[1].c_str(), CsBin,0,12 );
    h1dAcc8Det[ AdNo ]    =  new TH1F( this_h1name8[2].c_str(), this_h1title8[2].c_str(), CsBin,0,12 );
    
    h1dVtx8Det[ AdNo ]     ->Reset();

    /// Set axis titles
    h2dAllDet[ AdNo ]      ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h2dAllDet[ AdNo ]      ->GetYaxis()->SetTitle("Delayed  Energy [MeV]");
    h2dVtxDet[ AdNo ]      ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h2dVtxDet[ AdNo ]      ->GetYaxis()->SetTitle("Delayed  Energy [MeV]");
    h2dAccBkgDet[ AdNo ]   ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h2dAccBkgDet[ AdNo ]   ->GetYaxis()->SetTitle("Delayed  Energy [MeV]");
    h2dAccDet[ AdNo ]      ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h2dAccDet[ AdNo ]      ->GetYaxis()->SetTitle("Delayed  Energy [MeV]");

    h2dZR2VtxDet[ AdNo ]   ->GetXaxis()->SetTitle("Prompt R^{2} [mm^{2}]");
    h2dZR2VtxDet[ AdNo ]   ->GetYaxis()->SetTitle("Prompt Z [mm]");
    h2dZR2BkgDet[ AdNo ]   ->GetXaxis()->SetTitle("Prompt R^{2} [mm^{2}]");
    h2dZR2BkgDet[ AdNo ]   ->GetYaxis()->SetTitle("Prompt Z [mm]");
    h2dZR2AccDet[ AdNo ]   ->GetXaxis()->SetTitle("Prompt R^{2} [mm^{2}]");
    h2dZR2AccDet[ AdNo ]   ->GetYaxis()->SetTitle("Prompt Z [mm]");

    h1dAll22Det[ AdNo ]    ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h1dVtx22Det[ AdNo ]    ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h1dAccBkg22Det[ AdNo ] ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h1dAcc22Det[ AdNo ]    ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h1dNeutronDet[ AdNo ]  ->GetXaxis()->SetTitle("Delayed Energy [MeV]");

    h1dVtx8Det[ AdNo ]     ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h1dAccBkg8Det[ AdNo ]  ->GetXaxis()->SetTitle("Prompt Energy [MeV]");
    h1dAcc8Det[ AdNo ]     ->GetXaxis()->SetTitle("Prompt Energy [MeV]");

    h1dDistVtxDet[ AdNo ]  ->GetXaxis()->SetTitle("Distance [mm]");
    h1dDistBkgDet[ AdNo ]  ->GetXaxis()->SetTitle("Distance [mm]");
    h1dDistAccDet[ AdNo ]  ->GetXaxis()->SetTitle("Distance [mm]");

    h1dPhiVtxDet[ AdNo ]  ->GetXaxis()->SetTitle("Phi");
    h1dPhiBkgDet[ AdNo ]  ->GetXaxis()->SetTitle("Phi");
    h1dPhiAccDet[ AdNo ]  ->GetXaxis()->SetTitle("Phi");

    h1dDtVtxDet[ AdNo ]  ->GetXaxis()->SetTitle("Dt [s]");
    h1dDtBkgDet[ AdNo ]  ->GetXaxis()->SetTitle("Dt [s]");
    h1dDtAccDet[ AdNo ]  ->GetXaxis()->SetTitle("Dt [s]");

    h1dAll22Det[ AdNo ]    ->GetYaxis()->SetTitle("Entries/0.1MeV");
    h1dVtx22Det[ AdNo ]    ->GetYaxis()->SetTitle("Entries/0.1MeV");
    h1dAccBkg22Det[ AdNo ] ->GetYaxis()->SetTitle("Entries/0.1MeV");
    h1dAcc22Det[ AdNo ]    ->GetYaxis()->SetTitle("Entries/0.1MeV");
    h1dNeutronDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/0.01MeV");

    h1dVtx8Det[ AdNo ]     ->GetYaxis()->SetTitle("Entries/0.1MeV");
    h1dAccBkg8Det[ AdNo ]  ->GetYaxis()->SetTitle("Entries/0.1MeV");
    h1dAcc8Det[ AdNo ]     ->GetYaxis()->SetTitle("Entries/0.1MeV");

    h1dDistVtxDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/20 mm");
    h1dDistBkgDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/20 mm");
    h1dDistAccDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/20 mm");
    
    h1dPhiVtxDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/(Pi/50)");
    h1dPhiBkgDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/(Pi/50)");
    h1dPhiAccDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/(Pi/50)");

    h1dDtVtxDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/(1e-6 s)");
    h1dDtBkgDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/(1e-6 s)");
    h1dDtAccDet[ AdNo ]  ->GetYaxis()->SetTitle("Entries/(1e-6 s)");
  }

  /// Load data base information
  /// Load already

  return 1;
}

int EndJob()
{
  map< int /* Run */, map< int /* AdNo */, TH2F* > >::iterator it, it_end = h2dAll.end();

  for( it = h2dAll.begin(); it != it_end; it++ )   {
    int run = it->first;

    for( int AdNo = 1; AdNo<=4; AdNo++ )   {
      /// Aggregate plot for each detector.
      h2dAllDet[ AdNo ]     ->Add( h2dAllDet[ AdNo ] ,    h2dAll[ run ][ AdNo ] );
      h2dVtxDet[ AdNo ]     ->Add( h2dVtxDet[ AdNo ] ,    h2dVtx[ run ][ AdNo ] );
      h2dAccBkgDet[ AdNo ]  ->Add( h2dAccBkgDet[ AdNo ] , h2dAccBkg[ run ][ AdNo ] );
      h2dAccDet[ AdNo ]     ->Add( h2dAccDet[ AdNo ] ,    h2dAcc[ run ][ AdNo ] );

      h2dZR2VtxDet[ AdNo ]  ->Add( h2dZR2VtxDet[ AdNo ] , h2dZR2Vtx[ run ][ AdNo ] );
      h2dZR2BkgDet[ AdNo ]  ->Add( h2dZR2BkgDet[ AdNo ] , h2dZR2Bkg[ run ][ AdNo ] );
      h2dZR2AccDet[ AdNo ]  ->Add( h2dZR2AccDet[ AdNo ] , h2dZR2Acc[ run ][ AdNo ] );

      h1dAll22Det[ AdNo ]   ->Add( h1dAll22Det[ AdNo ] ,    h1dAll22[ run ][ AdNo ] );
      h1dVtx22Det[ AdNo ]   ->Add( h1dVtx22Det[ AdNo ] ,    h1dVtx22[ run ][ AdNo ] );
      h1dAccBkg22Det[ AdNo ]->Add( h1dAccBkg22Det[ AdNo ] , h1dAccBkg22S[ run ][ AdNo ] );
      
      h1dNeutronDet[ AdNo ] ->Add( h1dNeutronDet[ AdNo ] ,  h1dNeutron[ run ][ AdNo ] );

      h1dDistVtxDet[ AdNo ] ->Add( h1dDistVtxDet[ AdNo ] ,  h1dDistVtx[ run ][ AdNo ] );
      h1dDistBkgDet[ AdNo ] ->Add( h1dDistBkgDet[ AdNo ] ,  h1dDistBkgS[ run ][ AdNo ] );

      h1dPhiVtxDet[ AdNo ] ->Add( h1dPhiVtxDet[ AdNo ] ,  h1dPhiVtx[ run ][ AdNo ] );
      h1dPhiBkgDet[ AdNo ] ->Add( h1dPhiBkgDet[ AdNo ] ,  h1dPhiBkg[ run ][ AdNo ] );
      h1dPhiAccDet[ AdNo ] ->Add( h1dPhiAccDet[ AdNo ] ,  h1dPhiAcc[ run ][ AdNo ] );

      h1dDtVtxDet[ AdNo ] ->Add( h1dDtVtxDet[ AdNo ] ,  h1dDtVtx[ run ][ AdNo ] );
      h1dDtBkgDet[ AdNo ] ->Add( h1dDtBkgDet[ AdNo ] ,  h1dDtBkgS[ run ][ AdNo ] );

      h1dVtx8Det[ AdNo ]    ->Add( h1dVtx8Det[ AdNo ] ,    h1dVtx8[ run ][ AdNo ] );
      h1dAccBkg8Det[ AdNo ] ->Add( h1dAccBkg8Det[ AdNo ] , h1dAccBkg8S[ run ][ AdNo ] );

      /// Add all up.
      h2dAllSum     ->Add( h2dAllSum ,    h2dAll[ run ][ AdNo ] );
      h2dVtxSum     ->Add( h2dVtxSum ,    h2dVtx[ run ][ AdNo ] );
      h2dAccBkgSum  ->Add( h2dAccBkgSum , h2dAccBkg[ run ][ AdNo ] );
      h2dAccSum     ->Add( h2dAccSum ,    h2dAcc[ run ][ AdNo ] );      

      h2dZR2VtxSum  ->Add( h2dZR2VtxSum , h2dZR2Vtx[ run ][ AdNo ] );
      h2dZR2BkgSum  ->Add( h2dZR2BkgSum , h2dZR2Bkg[ run ][ AdNo ] );
      h2dZR2AccSum  ->Add( h2dZR2AccSum , h2dZR2Acc[ run ][ AdNo ] );
      
      h1dAll22Sum   ->Add( h1dAll22Sum ,    h1dAll22[ run ][ AdNo ] );
      h1dVtx22Sum   ->Add( h1dVtx22Sum ,    h1dVtx22[ run ][ AdNo ] );
      h1dAccBkg22Sum->Add( h1dAccBkg22Sum , h1dAccBkg22S[ run ][ AdNo ] );
      
      h1dNeutronSum ->Add( h1dNeutronSum ,  h1dNeutron[ run ][ AdNo ] );

      h1dDistVtxSum ->Add( h1dDistVtxSum,  h1dDistVtx[ run ][ AdNo ] );
      h1dDistBkgSum ->Add( h1dDistBkgSum,  h1dDistBkgS[ run ][ AdNo ] );

      h1dPhiVtxSum ->Add( h1dPhiVtxSum,  h1dPhiVtx[ run ][ AdNo ] );
      h1dPhiBkgSum ->Add( h1dPhiBkgSum,  h1dPhiBkg[ run ][ AdNo ] );
      h1dPhiAccSum ->Add( h1dPhiAccSum,  h1dPhiAcc[ run ][ AdNo ] );

      h1dDtVtxSum ->Add( h1dDtVtxSum,  h1dDtVtx[ run ][ AdNo ] );
      h1dDtBkgSum ->Add( h1dDtBkgSum,  h1dDtBkgS[ run ][ AdNo ] );

      h1dVtx8Sum    ->Add( h1dVtx8Sum ,    h1dVtx8[ run ][ AdNo ] );
      h1dAccBkg8Sum ->Add( h1dAccBkg8Sum , h1dAccBkg8S[ run ][ AdNo ] );
    }
  }

  /// Add scale errors
  for( int AdNo = 1; AdNo<=4; AdNo++ )   {
    /// Reset their errors
    AddScaleError( h2dAccBkgDet[ AdNo ]  , ScaleE );
    AddScaleError( h2dZR2BkgDet[ AdNo ]  , ScaleE );
    AddScaleError( h1dAccBkg22Det[ AdNo ], ScaleE );
    AddScaleError( h1dDistBkgDet[ AdNo ] , ScaleE );
    AddScaleError( h1dPhiBkgDet[ AdNo ]  , ScaleE );
    AddScaleError( h1dDtBkgDet[ AdNo ]  , ScaleE );
    AddScaleError( h1dAccBkg8Det[ AdNo ] , ScaleE );
  }

  cout<<"ScaleE "<<ScaleE<<endl;
  AddScaleError( h2dAccBkgSum   , ScaleE );
  AddScaleError( h2dZR2BkgSum   , ScaleE );
  AddScaleError( h1dAccBkg22Sum , ScaleE );
  AddScaleError( h1dDistBkgSum  , ScaleE );
  AddScaleError( h1dPhiBkgSum   , ScaleE );
  AddScaleError( h1dDtBkgSum   , ScaleE );
  AddScaleError( h1dAccBkg8Sum  , ScaleE );

  /// Make the right subtraction
  for( int AdNo = 1; AdNo<=4; AdNo++ ) {
    h1dAcc22Det[ AdNo ]  ->Add( h1dVtx22Det[ AdNo ]  ,h1dAccBkg22Det[ AdNo ], 1, -1 );
    h1dDistAccDet[ AdNo ]->Add( h1dDistVtxDet[ AdNo ],h1dDistBkgDet[ AdNo ] , 1, -1 );
    h1dAcc8Det[ AdNo ]   ->Add( h1dVtx8Det[ AdNo ]   ,h1dAccBkg8Det[ AdNo ] , 1, -1 );
    h1dDtAccDet[ AdNo ]  ->Add( h1dDtVtxDet[ AdNo ]  ,h1dDtBkgDet[ AdNo ]   , 1, -1 );
  }
  h1dAcc22Sum   ->Add( h1dVtx22Sum  ,h1dAccBkg22Sum , 1, -1 );
  h1dDistAccSum ->Add( h1dDistVtxSum,h1dDistBkgSum  , 1, -1 );
  h1dAcc8Sum    ->Add( h1dVtx8Sum   ,h1dAccBkg8Sum  , 1, -1 );
  h1dDtAccSum   ->Add( h1dDtVtxSum  ,h1dDtBkgSum    , 1, -1 );
  
  /// The last thing
  rootfile->Write();

  /// Update run info database  
  for( unsigned int idx = 0; idx<runList.size(); idx++ ) {

    /// get each run number
    int run = runList[idx];

    /// Find the run info line for this run
    int lineNum = -1;
    for( int row=0; row<RunInfoTable.NRows; row++ ) {
      if( RunInfoTable.Columns[ "Run" ][row] == i2a( run ) ) {
	lineNum=row;
      }
    }
    
    /// Update the record
    RunInfoTable.Columns[ "Scale1" ][ lineNum ] = d2a(scale[run][1] );
    RunInfoTable.Columns[ "Scale2" ][ lineNum ] = d2a(scale[run][2] );
    RunInfoTable.Columns[ "Scale3" ][ lineNum ] = d2a(scale[run][3] );
    RunInfoTable.Columns[ "Scale4" ][ lineNum ] = d2a(scale[run][4] );

    RunInfoTable.Columns[ "N8MeV1" ][ lineNum ] = d2a(n8MeV[run][1] );
    RunInfoTable.Columns[ "N8MeV2" ][ lineNum ] = d2a(n8MeV[run][2] );
    RunInfoTable.Columns[ "N8MeV3" ][ lineNum ] = d2a(n8MeV[run][3] );
    RunInfoTable.Columns[ "N8MeV4" ][ lineNum ] = d2a(n8MeV[run][4] );

    RunInfoTable.Columns[ "N22MeV1" ][ lineNum ] =d2a(n22MeV[run][1]);
    RunInfoTable.Columns[ "N22MeV2" ][ lineNum ] =d2a(n22MeV[run][2]);
    RunInfoTable.Columns[ "N22MeV3" ][ lineNum ] =d2a(n22MeV[run][3]);
    RunInfoTable.Columns[ "N22MeV4" ][ lineNum ] =d2a(n22MeV[run][4]);
  }
    
  /// Add in new columns
  RunInfoTable.FieldNames.push_back( "TwoFold1" );
  RunInfoTable.FieldNames.push_back( "TwoFold2" );
  RunInfoTable.FieldNames.push_back( "TwoFold3" );
  RunInfoTable.FieldNames.push_back( "TwoFold4" );
  
  RunInfoTable.FieldNames.push_back( "ThreeFold1" );
  RunInfoTable.FieldNames.push_back( "ThreeFold2" );
  RunInfoTable.FieldNames.push_back( "ThreeFold3" );
  RunInfoTable.FieldNames.push_back( "ThreeFold4" );
  
  RunInfoTable.FieldNames.push_back( "NBVtx1" );
  RunInfoTable.FieldNames.push_back( "NBVtx2" );
  RunInfoTable.FieldNames.push_back( "NBVtx3" );
  RunInfoTable.FieldNames.push_back( "NBVtx4" );
  
  RunInfoTable.FieldNames.push_back( "NAVtx1" );
  RunInfoTable.FieldNames.push_back( "NAVtx2" );
  RunInfoTable.FieldNames.push_back( "NAVtx3" );
  RunInfoTable.FieldNames.push_back( "NAVtx4" );
  
  RunInfoTable.FieldNames.push_back( "NAEng1" );
  RunInfoTable.FieldNames.push_back( "NAEng2" );
  RunInfoTable.FieldNames.push_back( "NAEng3" );
  RunInfoTable.FieldNames.push_back( "NAEng4" );
  
  for( int row=0; row<RunInfoTable.NRows; row++ ) {
    int run = atoi( RunInfoTable.Columns[ "Run" ][ row ].c_str() );

    RunInfoTable.Columns[ "TwoFold1" ].push_back( d2a(nTwoFold[run][1]) );
    RunInfoTable.Columns[ "TwoFold2" ].push_back( d2a(nTwoFold[run][2]) );
    RunInfoTable.Columns[ "TwoFold3" ].push_back( d2a(nTwoFold[run][3]) );
    RunInfoTable.Columns[ "TwoFold4" ].push_back( d2a(nTwoFold[run][4]) );
    
    RunInfoTable.Columns[ "ThreeFold1" ].push_back( d2a(nThreeFold[run][1]) );
    RunInfoTable.Columns[ "ThreeFold2" ].push_back( d2a(nThreeFold[run][2]) );
    RunInfoTable.Columns[ "ThreeFold3" ].push_back( d2a(nThreeFold[run][3]) );
    RunInfoTable.Columns[ "ThreeFold4" ].push_back( d2a(nThreeFold[run][4]) );
    
    RunInfoTable.Columns[ "NBVtx1" ].push_back( d2a(nBVtx[run][1]) );
    RunInfoTable.Columns[ "NBVtx2" ].push_back( d2a(nBVtx[run][2]) );
    RunInfoTable.Columns[ "NBVtx3" ].push_back( d2a(nBVtx[run][3]) );
    RunInfoTable.Columns[ "NBVtx4" ].push_back( d2a(nBVtx[run][4]) );
    
    RunInfoTable.Columns[ "NAVtx1" ].push_back( d2a(nAVtx[run][1]) );
    RunInfoTable.Columns[ "NAVtx2" ].push_back( d2a(nAVtx[run][2]) );
    RunInfoTable.Columns[ "NAVtx3" ].push_back( d2a(nAVtx[run][3]) );
    RunInfoTable.Columns[ "NAVtx4" ].push_back( d2a(nAVtx[run][4]) );

    RunInfoTable.Columns[ "NAEng1" ].push_back( d2a(nAEng[run][1]) );
    RunInfoTable.Columns[ "NAEng2" ].push_back( d2a(nAEng[run][2]) );
    RunInfoTable.Columns[ "NAEng3" ].push_back( d2a(nAEng[run][3]) );
    RunInfoTable.Columns[ "NAEng4" ].push_back( d2a(nAEng[run][4]) );
  }
  
  RunInfoTable.Write( RunInfoOutputFile.c_str() );

  return 1;
}

    
void AddScaleError( TH1F* h1, double rerr )
{
  for( int bin=1; bin<=h1->GetNbinsX(); bin++ ) {
    double conte = h1->GetBinContent( bin );
    double error = h1->GetBinError( bin );
    
    error = sqrt( error*error + conte*rerr*conte*rerr );
    h1->SetBinError( bin, error );
  }
}
  
void AddScaleError( TH2F* h2, double rerr )
{
  for( int binX=1; binX<=h2->GetNbinsX(); binX++ ) {
    for( int binY=1; binY<=h2->GetNbinsY(); binY++ ) {
      int glbbin = h2->GetBin(binX,binY);

      double conte = h2->GetBinContent( glbbin );
      double error = h2->GetBinError( glbbin );

      error = sqrt( error*error + conte*rerr*conte*rerr );
      h2->SetBinError( glbbin, error );
    }
  }
}
