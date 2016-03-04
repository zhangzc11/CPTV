//
//   Every readout -> Good SubEvt -> Event
//
//   Zhe Wang, Jan. 27, 2012
//
#include "Globals.h"

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

map<int /* AD No. */, TimeStamp /* veto all SubEvt till */>  MuonVetoTime;

/* The core of the second loop of the code */
map<int /* AD No. */, RunStatus::RunStatus_t /* Running Status */> RunStatusDict;
map<int /* AD No. */, Event /* Event under construction */       > EventDict;

map<int /* AD No. */, TimeStamp /* time of last subevt */ > LastSubEvtT;

int BuildEvent( SubEvt* pSubEvt );

/* Output TWin tree */
EventTree*    aEventTree;

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

  return 1;
}

int EndJob()
{
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
