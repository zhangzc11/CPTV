//
//   Fast recon streamer
//
//   Zhe Wang, Mar. 20, 2012
//
#include "AdSimpleReader.h"
#include "CalibReadoutHeaderReader.h"
#include "CalibStatsReader.h"
#include "StreamTree.h"
#include <string>
#include <iostream>
#include "TChain.h"
#include <stdio.h>
#include <stdlib.h>
//#include "RunSetup.h"

using namespace std;

AdSimpleReader*           AdSimple_Reader;
CalibReadoutHeaderReader* CalibReadoutHeader_Reader;
CalibStatsReader*         CalibStats_Reader;

int BeginJob();
int EndJob();

int main(int argc, char** argv)
{
  TChain *AdSimple           = new TChain("/Event/Rec/AdSimple");
  TChain *CalibReadoutHeader = new TChain("/Event/CalibReadout/CalibReadoutHeader");
  TChain *CalibStats         = new TChain("/Event/Data/CalibStats");

  string inputfile;
  string outputfile;
  int runNumber = 21223;

  if( argc != 4 ) {
    cout<<"Usage:"<<endl;
    cout<<"    FastStreamer inputfile.root outputfile.root runnumber"<<endl;
    cout<<endl;
    return 1;
  } else {
    inputfile = argv[1];
    outputfile = argv[2];
    runNumber = atoi(argv[3]);
  }

  AdSimple           -> Add( inputfile.c_str() );
  CalibReadoutHeader -> Add( inputfile.c_str() );
  CalibStats         -> Add( inputfile.c_str() );    

  StreamTree Stream("Stream",outputfile.c_str(),0);

  // Load the AdSimple Tree
  // Get the AdSimple Tree reader
  AdSimple_Reader = new AdSimpleReader;
  AdSimple_Reader->Init(AdSimple);

  CalibReadoutHeader_Reader = new CalibReadoutHeaderReader;
  CalibReadoutHeader_Reader->Init(CalibReadoutHeader);

  CalibStats_Reader = new CalibStatsReader;
  CalibStats_Reader->Init(CalibStats);

  /* Begin Job */
  /* --------- */
  if( BeginJob() == 0 ) {
    cout<<"BeginJob failed"<<endl;
    return 0;
  }

  /* The main loop over every stream entries */
  /* --------------------------------------- */
  int readerr;
  unsigned int entries = AdSimple->GetEntries();
  for( unsigned int entry=0; entry<entries; entry++ )  {

    Stream.Reset();

    /* Load AdSimple tree */
    readerr = AdSimple_Reader->GetEntry( entry );
    if( readerr==0 ) { 
      cout<<"Warning: Read error"<<endl;
    }
    /* Load CalibReadoutHeader tree */
    readerr = CalibReadoutHeader_Reader->GetEntry( entry );
    if( readerr==0 ) {
      cout<<"Warning: Read error"<<endl;
    }
    /* Load CalibStats tree */
    readerr = CalibStats_Reader->GetEntry( entry );
    if( readerr==0 ) {
      cout<<"Warning: Read error"<<endl;
    }    

    /* Assign each tree branch values */
    Stream.Run  = runNumber;   /// To do:
    Stream.Site = CalibReadoutHeader_Reader->site;
    Stream.Det  = CalibReadoutHeader_Reader->detector;

    Stream.TrigNum  = CalibReadoutHeader_Reader->triggerNumber;
    Stream.TrigType = CalibReadoutHeader_Reader->triggerType;
    Stream.TrigSec  = CalibReadoutHeader_Reader->triggerTimeSec;
    Stream.TrigNano = CalibReadoutHeader_Reader->triggerTimeNanoSec;

    Stream.NPmt = CalibStats_Reader->nHit;

    Stream.E = AdSimple_Reader->energy;
    Stream.X = AdSimple_Reader->x;
    Stream.Y = AdSimple_Reader->y;
    Stream.Z = AdSimple_Reader->z;

    Stream.TRms      = CalibStats_Reader->MiddleTimeRMS;
    Stream.Quadrant  = CalibStats_Reader->Quadrant;
    Stream.QMax2Sum  = CalibStats_Reader->MaxQ;
    Stream.MaxQ2Inch = CalibStats_Reader->MaxQ_2inchPMT;

    Stream.Fill();
  }
  cout<<"Last entry = "<<entries<<endl;

  //RunSetup setup;
  //setup.Write("Setup");
  
  /* End Job */
  /* ------- */
  Stream.Close();

  if( EndJob() == 0 ) {
    cout<<"BeginJob failed"<<endl;
    return 0;
  }

  return 1;
}

int BeginJob()
{
  return 1;
}

int EndJob()
{
  return 1;
}
