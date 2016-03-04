#include "StreamTree.h"
#include <string>
#include <vector>
#include "Tree2Selector.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  string inputfile;

  string filenamebase;
  string filenameext = "Stream.root";
  string outputpathname;
  string outputfilename;
  string outputfile;
  
  if( argc != 3 ) {
    cout<<"Usage:"<<endl;
    cout<<"    Streamer inputfile.root output/path/"<<endl;
    cout<<endl;
    return 1;
  } else {
    inputfile = argv[1];
    outputpathname = argv[2];

    filenamebase = inputfile;
    filenamebase = filenamebase.erase( inputfile.length()-4, 4 );
    int lastBS = filenamebase.find_last_of("/");
    filenamebase = filenamebase.erase( 0, lastBS+1 );
    outputfilename = filenamebase + filenameext;
    
    outputfile = outputpathname + outputfilename;

    cout<<"Converting "<<argv[1]<<" to "<<outputfile<<endl;
  }

  StreamTree stream("Stream",outputfile.c_str(),0);

  // Case 1:
  //++++++++


  // Case 2:
  //++++++++
  TFile *f = new TFile( inputfile.c_str(), "READ" );
  TTree *Rec = (TTree*)f->Get("Rec");
  Tree2Selector er;
  er.Init(Rec);

  unsigned int entry = 0;
  int result = 0;
  result = er.GetEntry( entry );

  while ( result !=0 ) {
    stream.Reset();   
    ///========
    stream.Run = er.Run;
    stream.Event = er.Event;
    stream.Site = er.Site;
    stream.Det = er.Det;

    stream.TrigType = er.TrigType;
    stream.TrigSec = er.TrigSec;
    stream.TrigNano = er.TrigNanoSec;

    stream.NPmt = er.NPmt;

    stream.E = er.ScaledEnergy;
    stream.X = er.ScaledX;
    stream.Y = er.ScaledY;
    stream.Z = er.ScaledZ;

    stream.TRms = er.EffTimeRMS;
    stream.Quadrant = er.Quadrant;
    stream.QMax2Sum = er.EffRatioMaxQ;


    stream.Fill();
    entry++;
    result = er.GetEntry( entry );
  }

  stream.Close();

  return 1;
}
