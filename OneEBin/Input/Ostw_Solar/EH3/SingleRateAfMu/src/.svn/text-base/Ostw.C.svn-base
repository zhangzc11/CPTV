//
//   Every readout -> Good SubEvt -> Event
//
//   Zhe Wang, Jan. 27, 2012
//
//   TH1F has a limit of 0x1000000 for each bin for integer counting
//
#include "Globals.h"
#include "TGraph.h"

TChain*  StreamChain;
StreamReader* Reader;
Cuts*         AllCut;
string   RunInfoOutput;

/* The core of the first loop of the code */
SubEvtQueue CachedQueue;

/* Delay the output of each SubEvt. They are cached in CachedQueue. */
/* Through caching, there is a chance to test the SubEvts in the queue and build up association. */
SubEvtQueue CachedQueueInsert( TimeStamp time, SubEvt* pSubEvt );

/* Muon information */
TimeStamp LastMuonT;
map<int /* AD No. */, TimeStamp /* last pool muon time */  > LastPoolMuonT;
map<int /* AD No. */, TimeStamp /* last AD muon time */    > LastAdMuonT;
map<int /* AD No. */, TimeStamp /* last shower muon time */> LastShowerMuonT;
map<int /* AD No. */, TimeStamp /* last net muon time */   > LastNetMuonT;

map<int /* AD No. */, TimeStamp /* veto all SubEvt till */ > MuonVetoTime;
map<int /* AD No. */, MuonId::MuonId_t /* Last Muon Id  */ > MuonVetoId;

/* The core of the second loop of the code */
map<int /* AD No. */, RunStatus::RunStatus_t /* Running Status */> RunStatusDict;
map<int /* AD No. */, Event /* Event under construction */       > EventDict;

map<int /* AD No. */, TimeStamp /* time of last subevt */ > LastSubEvtT;

int BuildEvent( SubEvt* pSubEvt );

/* Output TWin tree */
EventTree*    aEventTree;
//#define TreeOutput 1

/* Histogram for time counting, events number and rate measurement */
/* Three set of histograms for three types of muon */
map<int /* AD No. */, TGraph * /* Time available after a pool muon */ >  TimeAviPl;
map<int /* AD No. */, TGraph * /* Single upper limit counting      */ >  SingleUpPl;
map<int /* AD No. */, TGraph * /* Single lower limit counting      */ >  SingleLwPl;
map<int /* AD No. */, TGraph * /* Average rate                     */ >  RatePl;

map<int /* AD No. */, TGraph * /* Time available after a pool muon */ >  TimeAviAd;
map<int /* AD No. */, TGraph * /* Single upper limit counting      */ >  SingleUpAd;
map<int /* AD No. */, TGraph * /* Single lower limit counting      */ >  SingleLwAd;
map<int /* AD No. */, TGraph * /* Average rate                     */ >  RateAd;

map<int /* AD No. */, TGraph * /* Time available after a pool muon */ >  TimeAviSh;
map<int /* AD No. */, TGraph * /* Single upper limit counting      */ >  SingleUpSh;
map<int /* AD No. */, TGraph * /* Single lower limit counting      */ >  SingleLwSh;
map<int /* AD No. */, TGraph * /* Average rate                     */ >  RateSh;

map<int /* AD No. */, TGraph * /* Time available after a pool muon */ >  TimeAvi;
map<int /* AD No. */, TGraph * /* Single upper limit counting      */ >  SingleUp;
map<int /* AD No. */, TGraph * /* Single lower limit counting      */ >  SingleLw;
map<int /* AD No. */, TGraph * /* Average rate                     */ >  Rate;

/* For counting */
double  CTimeAviPl [4][timebins];
double  CSingleUpPl[4][timebins];
double  CSingleLwPl[4][timebins];
double  CRatePl    [4][timebins];
      				
double  CTimeAviAd [4][timebins];
double  CSingleUpAd[4][timebins];
double  CSingleLwAd[4][timebins];
double  CRateAd    [4][timebins];
      				
double  CTimeAviSh [4][timebins];
double  CSingleUpSh[4][timebins];
double  CSingleLwSh[4][timebins];
double  CRateSh    [4][timebins];
      				
double  CTimeAvi   [4][timebins];
double  CSingleUp  [4][timebins];
double  CSingleLw  [4][timebins];
double  CRate      [4][timebins];

double TimeX[timebins];

int Usage()
{
  cout<<"Usage:"<<endl;
  cout<<"    Ostw InputFile.root(.list) OutputFile.TWin.root RunInfo.txt Gd|H"<<endl;
  cout<<endl;
  exit(1);
}

int BeginJob( int argc, char** argv );
int EndJob();

RunInfo CurrRun;
int BeginRun(StreamReader* Reader);
int EndRun(StreamReader* Reader);

/* Main function */
int main(int argc, char** argv)
{

  if( BeginJob( argc, argv ) == 0 ) {
    cout<<"BeginJob failed"<<endl;
    return 0;
  }

  /* Layer 1. The main loop over every stream entries */
  /* ------------------------------------------------ */
  CurrRun.Run = -1;
  cout<<"StreamChain add "<<StreamChain<<endl;
  unsigned int entries = StreamChain->GetEntries();
  for( unsigned int entry=0; entry<entries; entry++ )  {
    unsigned int localentry = StreamChain->LoadTree(entry);
    int ret = Reader->GetEntry( localentry );
    if( ret==0 ) { 
      cout<<"Error: Read error"<<endl;
      return 1;
    }
    
    /* Process run information and possible long time jump */
    if( Reader->Run != CurrRun.Run )  {
      if( CurrRun.Run != -1 )  {
	/* End Run */
	if( EndRun( Reader ) == 0 ) {
	  cout<<"EndRun failed"<<endl;
	  return 0;
	}
      }
      /* Begin Run */
      if( BeginRun( Reader ) == 0 ) {
	cout<<"BeginRun failed"<<endl;
	return 0;
      }
    }
    
    /*** Test each entry here ***/
    SubEvt* pSubEvt = new SubEvt( Reader );
    TimeStamp NewTime( pSubEvt->TrigSec, pSubEvt->TrigNano );
    if( (NewTime - CurrRun.CurrTime).GetSeconds() > 120 /* Two minutes */ ) {
      CurrRun.Breaks.push_back( CurrRun.CurrTime );
      CurrRun.Breaks.push_back( NewTime );
      CurrRun.SkipTime.Add( (NewTime - CurrRun.CurrTime).GetSeconds() );
    }
    CurrRun.CurrTime = NewTime;

    /* Cache all temporal related event. Give a chance to clean up the queue and do muon Id */
    SubEvtQueue PassedQueue = CachedQueueInsert( NewTime, pSubEvt );

    /* Layer 2. The main loop over every non-muon SubEvt */
    /* ------------------------------------------------- */
    SubEvtQueueIterator it, it_end = PassedQueue.end();
    for( it = PassedQueue.begin(); it != it_end; it++ )  {
      
      /* Build delay coincident event */
      SubEvt* pSubEvt = it->second;
      int ret = BuildEvent( pSubEvt );
      if( ret == 0 )  {
	cout<<"Error in BuildEvent"<<endl;
      }
      
      delete pSubEvt;

    }
    /***  End of SubEvt loop  ***/

  }
  /***  End of stream entry loop  ***/

  if( EndRun( Reader ) == 0 ) {
    cout<<"EndRun failed"<<endl;
    return 0;
  }

  /* End Job */
  /* ------- */
  if( EndJob() == 0 ) {
    cout<<"BeginJob failed"<<endl;
    return 0;
  }

  return 1;
}

int BeginJob( int argc, char** argv )
{
  string inputfile;
  string outputfile;
  string DataSet;
  vector<string> datafiles;

  /* Argument parsing */
  /* ---------------- */
  if( argc != 5 ) {
    Usage();
  } else {
    inputfile = argv[1];
    outputfile = argv[2];
    RunInfoOutput = argv[3];
    DataSet = argv[4];

    string extension = inputfile.substr( inputfile.length()-5, 5 );
    /* A single input file */
    if( extension == ".root" )  {
      //cout<<"A single input file, "<<inputfile<<endl;
      datafiles.push_back(inputfile);
    }
    /* Input file is a list */
    else if( extension == ".list" )  {
      //cout<<"A list of root files, "<<inputfile<<endl;
      /* Grab all the data files in the list */
      ifstream inlist( inputfile.c_str() );
      string line;
      while( getline( inlist, line ) )  {
        datafiles.push_back( line );
      }
    }

    if( DataSet == "Gd" )      AllCut = new Cuts( Cuts::Gd );
    else if ( DataSet == "H" ) AllCut = new Cuts( Cuts::H  );
    else {
      cout<<"Unknown data set "<<endl;
      exit(0);
    }
  }

  /* Load the StreamChain and initializa StreamChain Tree reader */
  /* ----------------------------------------------------------- */
  StreamChain = new TChain("Stream");

  for( unsigned int i =0; i<datafiles.size(); i++ ) {
    StreamChain->Add( datafiles[i].c_str() );
  }
  //cout<<datafiles.size()<<" data files will be processed."<<endl;

  Reader = new StreamReader;
  Reader->Init(StreamChain);

  /* Prepare the output tree */
  aEventTree = new EventTree("Event",outputfile.c_str(),0);

  for( int bin = 1; bin<=timebins; bin++ ) {
    double time = (timeEnd-timeStart)/timebins * (bin-0.5);
    TimeX[bin-1] = time;
    
    for( int Ad = 1; Ad<=4; Ad++ ) {
      CTimeAviPl [Ad-1][bin-1]  = 0;
      CSingleUpPl[Ad-1][bin-1]  = 0;
      CSingleLwPl[Ad-1][bin-1]  = 0;
      CRatePl    [Ad-1][bin-1]  = 0;
      
      CTimeAviAd [Ad-1][bin-1]  = 0;
      CSingleUpAd[Ad-1][bin-1]  = 0;
      CSingleLwAd[Ad-1][bin-1]  = 0;
      CRateAd    [Ad-1][bin-1]  = 0;
      
      CTimeAviSh [Ad-1][bin-1]  = 0;
      CSingleUpSh[Ad-1][bin-1]  = 0;
      CSingleLwSh[Ad-1][bin-1]  = 0;
      CRateSh    [Ad-1][bin-1]  = 0;
      
      CTimeAvi   [Ad-1][bin-1]  = 0;
      CSingleUp  [Ad-1][bin-1]  = 0;
      CSingleLw  [Ad-1][bin-1]  = 0;
      CRate      [Ad-1][bin-1]  = 0;
    }
  }

  return 1;
}

int EndJob()
{
  /* Prepare histograms */
  string Names[4] = { "TimeAvi", "SingleUp", "SingleLw", "Rate" };
  string Types[3] = { "Pl", "Ad", "Sh" };
  string ADs[4] = { "1", "2", "3", "4" };

  for( int Ad = 1; Ad<=4; Ad++ ) {
    for( int bin=1; bin<=timebins; bin++ ) {
      CRatePl[Ad-1][bin-1] = CSingleUpPl[Ad-1][bin-1] / CTimeAviPl [Ad-1][bin-1] ;
      CRateAd[Ad-1][bin-1] = CSingleUpAd[Ad-1][bin-1] / CTimeAviAd [Ad-1][bin-1] ;
      CRateSh[Ad-1][bin-1] = CSingleUpSh[Ad-1][bin-1] / CTimeAviSh [Ad-1][bin-1] ;
      CRate  [Ad-1][bin-1] = CSingleUp[Ad-1][bin-1]   / CTimeAvi [Ad-1][bin-1]   ;
    }
  }

  for( int Ad=1; Ad<=4; Ad++ ) {
    TimeAviPl [Ad] = new TGraph( timebins, TimeX, CTimeAviPl [Ad-1] );
    SingleUpPl[Ad] = new TGraph( timebins, TimeX, CSingleUpPl[Ad-1] );
    SingleLwPl[Ad] = new TGraph( timebins, TimeX, CSingleLwPl[Ad-1] );
    RatePl    [Ad] = new TGraph( timebins, TimeX, CRatePl    [Ad-1] );
    		  				  		  
    TimeAviAd [Ad] = new TGraph( timebins, TimeX, CTimeAviAd [Ad-1] );
    SingleUpAd[Ad] = new TGraph( timebins, TimeX, CSingleUpAd[Ad-1] );
    SingleLwAd[Ad] = new TGraph( timebins, TimeX, CSingleLwAd[Ad-1] );
    RateAd    [Ad] = new TGraph( timebins, TimeX, CRateAd    [Ad-1] );
    		  				  		  
    TimeAviSh [Ad] = new TGraph( timebins, TimeX, CTimeAviSh [Ad-1] );
    SingleUpSh[Ad] = new TGraph( timebins, TimeX, CSingleUpSh[Ad-1] );
    SingleLwSh[Ad] = new TGraph( timebins, TimeX, CSingleLwSh[Ad-1] );
    RateSh    [Ad] = new TGraph( timebins, TimeX, CRateSh    [Ad-1] );
    		  				  		  
    TimeAvi [Ad]   = new TGraph( timebins, TimeX, CTimeAvi   [Ad-1] );
    SingleUp[Ad]   = new TGraph( timebins, TimeX, CSingleUp  [Ad-1] );
    SingleLw[Ad]   = new TGraph( timebins, TimeX, CSingleLw  [Ad-1] );
    Rate    [Ad]   = new TGraph( timebins, TimeX, CRate      [Ad-1] );
  
    /// Set name for each of them
    TimeAviPl [Ad]->SetName( (Names[0]+Types[0]+ADs[Ad-1]).c_str() );
    SingleUpPl[Ad]->SetName( (Names[1]+Types[0]+ADs[Ad-1]).c_str() );
    SingleLwPl[Ad]->SetName( (Names[2]+Types[0]+ADs[Ad-1]).c_str() );
    RatePl    [Ad]->SetName( (Names[3]+Types[0]+ADs[Ad-1]).c_str() );
  			     			    			    
    TimeAviAd [Ad]->SetName( (Names[0]+Types[1]+ADs[Ad-1]).c_str() );
    SingleUpAd[Ad]->SetName( (Names[1]+Types[1]+ADs[Ad-1]).c_str() );
    SingleLwAd[Ad]->SetName( (Names[2]+Types[1]+ADs[Ad-1]).c_str() );
    RateAd    [Ad]->SetName( (Names[3]+Types[1]+ADs[Ad-1]).c_str() );
			     			    			    
    TimeAviSh [Ad]->SetName( (Names[0]+Types[2]+ADs[Ad-1]).c_str() );
    SingleUpSh[Ad]->SetName( (Names[1]+Types[2]+ADs[Ad-1]).c_str() );
    SingleLwSh[Ad]->SetName( (Names[2]+Types[2]+ADs[Ad-1]).c_str() );
    RateSh    [Ad]->SetName( (Names[3]+Types[2]+ADs[Ad-1]).c_str() );
    			     			    			    
    TimeAvi   [Ad]->SetName( (Names[0]+ADs[Ad-1]).c_str() );
    SingleUp  [Ad]->SetName( (Names[1]+ADs[Ad-1]).c_str() );
    SingleLw  [Ad]->SetName( (Names[2]+ADs[Ad-1]).c_str() );
    Rate      [Ad]->SetName( (Names[3]+ADs[Ad-1]).c_str() );

    /// Write
    TimeAviPl [Ad]->Write();
    SingleUpPl[Ad]->Write();
    SingleLwPl[Ad]->Write();
    RatePl    [Ad]->Write();

    TimeAviAd [Ad]->Write();
    SingleUpAd[Ad]->Write();
    SingleLwAd[Ad]->Write();
    RateAd    [Ad]->Write();

    TimeAviSh [Ad]->Write();
    SingleUpSh[Ad]->Write();
    SingleLwSh[Ad]->Write();
    RateSh    [Ad]->Write();

    TimeAvi   [Ad]->Write();
    SingleUp  [Ad]->Write();
    SingleLw  [Ad]->Write();
    Rate      [Ad]->Write();

  }

  aEventTree->Close();

  return 1;
}

int BeginRun(StreamReader* Reader)
{
  //cout<<"Start to process run: " << Reader->Run <<" ... "<<endl;
  CurrRun.Reset();
  CurrRun.Run = Reader->Run;
  CurrRun.Site = Reader->Site;
  CurrRun.StartTime = TimeStamp( Reader->TrigSec, Reader->TrigNano );
  CurrRun.CurrTime = CurrRun.StartTime;
  CurrRun.SkipTime = TimeStamp( 0, 0 );

  /* Reset all detectors' event searching status to waiting */
  for( int det = 1; det <= 4; det++ ) {
    RunStatusDict[ det ] = RunStatus::waiting;
  }

  /* Reset all last muon time stamp to BOT */
  LastMuonT       = TimeStamp::GetBOT();
  for( int det = 1; det <= 4; det++ ) {
    LastAdMuonT[det]     = TimeStamp::GetBOT();
    LastShowerMuonT[det] = TimeStamp::GetBOT();
    LastNetMuonT[det]    = TimeStamp::GetBOT();
    MuonVetoTime[det]    = TimeStamp::GetBOT();
    LastSubEvtT[det]     = TimeStamp::GetBOT();
  }

  return 1;
}

int EndRun(StreamReader* Reader)
{
  CurrRun.StopTime = TimeStamp( Reader->TrigSec, Reader->TrigNano );
  CurrRun.FullTime = CurrRun.StopTime - CurrRun.StartTime - CurrRun.SkipTime;
  //CurrRun.Dump();
  CurrRun.DumpToFile( RunInfoOutput );
  
  return 1;
}
