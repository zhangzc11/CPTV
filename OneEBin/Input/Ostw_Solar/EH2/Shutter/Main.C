//
//   Shuttter ---- SubEvt grouping
//
//   Zhe Wang, Nov. 2011
//
#include <string>
#include <vector>
#include "StreamReader.h"
#include "SubEvtTree.h"
#include "Common/Cuts.h"
#include <map>
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

StreamReader* SR;
SubEvtTree*   aSubEvtTree;
Cuts          ShutterCut;
int           prevSubEvtTimeSec = -999;
int           prevSubEvtTimeNano = -999;
int           currSubEvtEarliestSec = -999;
int           currSubEvtEarliestNano = -999;
int           prevMuonTimeSec = -999;
int           prevMuonTimeNano = -999;

int EndSubEvt();
int BeginSubEvt();
int ContSubEvt();

int main(int argc, char** argv)
{
  string inputfilelist;
  string filenameext = ".SubEvt.root";
  string outputfilebase;
  string outputfile;

  TChain *Stream = new TChain("Stream");

  if( argc != 3 ) {
    cout<<"Usage:"<<endl;
    cout<<"    Shutter inputfiles.list output/path/namebase"<<endl;
    cout<<endl;
    return 1;
  } else {
    inputfilelist = argv[1];
    outputfilebase = argv[2];
    
    /// The input file parsing
    ifstream inlist( inputfilelist.c_str() );
    string line;
    while( getline( inlist, line ) )  {
      Stream->Add( line.c_str() );
    }

    /// The output file
    outputfile = outputfilebase + filenameext;
  }


  /// Do the work ================================================
  // Load the Stream Tree
  // This should a TChain
  // Get the Stream Tree reader
  SR = new StreamReader;
  SR->Init(Stream);
  // Prepare the output tree
  aSubEvtTree = new SubEvtTree("SubEvt",outputfile.c_str(),0);

  /// Initialize detector and CurrTrigTime registers
  map<int /*Det*/, bool /*Occupied*/> Occupied;
  for( int det=1; det<=7; det++) {
    Occupied[det] = false;
  }

  /// The main loop over every stream entries
  static bool firsttime=true;
  unsigned int entries = Stream->GetEntries();
  for( unsigned int entry=0; entry<entries; entry++ )  {
    int ret = SR->GetEntry( entry );
    if( ret==0 ) { 
      cout<<"Warning: Read error"<<endl;
    }

    /*  Non-mulitiplicity trigger */
    if( ((SR->TrigType)&ShutterCut.MultiTrig) != ShutterCut.MultiTrig )  continue;

    /// Shutter algorithm
    double TimeToCurrSubEvt = SR->TrigSec - currSubEvtEarliestSec + (SR->TrigNano - currSubEvtEarliestNano) * 1e-9;
    int CurrRdtDet = SR->Det;

    /// End last SubEvt and prepare for a new one
    if( TimeToCurrSubEvt > ShutterCut.Latency/second ||
	Occupied[ CurrRdtDet ] ) {
      /// Clear Occupied map
      for( int det=1; det<=7; det++) {
	Occupied[det] = false;
      }
      /* ------------------- */
      if( !firsttime ) EndSubEvt( );
      /// New CurrSubEvtTime
      currSubEvtEarliestSec = SR->TrigSec;
      currSubEvtEarliestNano = SR->TrigNano;
      /* --------------------- */
      BeginSubEvt( );
    }
    Occupied[CurrRdtDet] = true;
    /* ------------------------ */
    ContSubEvt( );
    firsttime = false;
  }

  aSubEvtTree->Close();
  return 1;
}


int EndSubEvt()
{
  /// Muon identification
  aSubEvtTree->MuonProb = 0;
  /// Ads
  for( unsigned int i=0; i<4; i++ )  {
    if( aSubEvtTree->Valid[i] ) {
      if( aSubEvtTree->E[i] > ShutterCut.QSumAD )  {
	aSubEvtTree->MuonProb = 1;
	goto EndOfMuonId;
      }
    }
  }
  
  /// Iws
  if( aSubEvtTree->Valid[5-1] ) {
    if( aSubEvtTree->NPmt[5-1] > ShutterCut.NChnlIws )  {
      aSubEvtTree->MuonProb = 1;
      goto EndOfMuonId;
    }
  }

  /// Ows
  if( aSubEvtTree->Valid[6-1] ) {
    if( aSubEvtTree->NPmt[6-1] > ShutterCut.NChnlOws )  {
      aSubEvtTree->MuonProb = 1;
      goto EndOfMuonId;
    }
  }
  
  /// Rpc
  /// 3/4 trigger
  if( aSubEvtTree->Valid[7-1] ) {
    if( ((aSubEvtTree->TrigType[7-1])&0x10040000) == 0x10040000 )  {
      aSubEvtTree->MuonProb = 1;
      goto EndOfMuonId;
    }
  }
 EndOfMuonId:

  /// SubEvt time: Take the time of the earliest readout
  aSubEvtTree->SubEvtSec = currSubEvtEarliestSec;
  aSubEvtTree->SubEvtNano = currSubEvtEarliestNano;

  /// T to previous sub events
  aSubEvtTree->T2PrevSubEvt = currSubEvtEarliestSec - prevSubEvtTimeSec + (currSubEvtEarliestNano - prevSubEvtTimeNano)*1e-9;
  prevSubEvtTimeSec = currSubEvtEarliestSec;
  prevSubEvtTimeNano = currSubEvtEarliestNano;

  /// Retrigger identification
  if( aSubEvtTree->T2PrevSubEvt < ShutterCut.ReTrigWin/second ) {
    aSubEvtTree->RetrigProb = 0.9;
  }
  
  /// Time to Previous Muon
  aSubEvtTree->T2PrevMuon = currSubEvtEarliestSec - prevMuonTimeSec + (currSubEvtEarliestNano - prevMuonTimeNano)*1e-9;
  if( aSubEvtTree->MuonProb > 0.5 )  {
    prevMuonTimeSec = currSubEvtEarliestSec;
    prevMuonTimeNano = currSubEvtEarliestNano;
  }

  aSubEvtTree->Fill();
  return 1;
}

int BeginSubEvt()
{
  aSubEvtTree->Reset();
  return 1;
}

int ContSubEvt()
{
  int Det = SR->Det;

  aSubEvtTree->Run = SR->Run;
  aSubEvtTree->Site = SR->Site;
  aSubEvtTree->NDet += 1;
  
  aSubEvtTree->Valid[Det-1] = 1;
  aSubEvtTree->Event[Det-1] = SR->TrigNum;
  aSubEvtTree->Det[Det-1] = Det;

  aSubEvtTree->TrigType[Det-1] = SR->TrigType;
  aSubEvtTree->TrigSec[Det-1] = SR->TrigSec;
  aSubEvtTree->TrigNano[Det-1] = SR->TrigNano;
  
  aSubEvtTree->NPmt[Det-1] = SR->NPmt;

  aSubEvtTree->E[Det-1] = SR->E;
  aSubEvtTree->X[Det-1] = SR->X;
  aSubEvtTree->Y[Det-1] = SR->Y;
  aSubEvtTree->Z[Det-1] = SR->Z;

  aSubEvtTree->TRms[Det-1] = SR->TRms;
  aSubEvtTree->Quadrant[Det-1] = SR->Quadrant;
  aSubEvtTree->QMax2Sum[Det-1] = SR->QMax2Sum;

  return 1;
}
