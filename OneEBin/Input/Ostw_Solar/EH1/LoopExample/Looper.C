//
//   An example tree looper
//
//   Zhe Wang, Jan. 27, 2012
//
#include "TreeReader.h"
#include <string>
#include <iostream>
#include "TChain.h"
using namespace std;

TreeReader* TR;

int BeginJob();
int EndJob();

int main(int argc, char** argv)
{
  string inputfile;

  TChain *ReadinChain = new TChain("Stream");

  if( argc != 2 ) {
    cout<<"Usage:"<<endl;
    cout<<"    Looper inputfile"<<endl;
    cout<<endl;
    return 1;
  } else {
    inputfile = argv[1];
    ReadinChain->Add( inputfile.c_str() );
  }    

  // Load the ReadinChain Tree
  // Get the ReadinChain Tree reader
  TR = new TreeReader;
  TR->Init(ReadinChain);

  /* Begin Job */
  /* --------- */
  if( BeginJob() == 0 ) {
    cout<<"BeginJob failed"<<endl;
    return 0;
  }

  /* The main loop over every stream entries */
  /* --------------------------------------- */
  unsigned int entries = ReadinChain->GetEntries();
  for( unsigned int entry=0; entry<entries; entry++ )  {
    unsigned int localentry = ReadinChain->LoadTree(entry);
    int ret = TR->GetEntry( localentry );
    if( ret==0 ) { 
      cout<<"Warning: Read error"<<endl;
    }
    /*** Test each entry here ***/
    cout<< "TrigNum: "<<TR->TrigNum<<" Energy= "<<TR->E <<endl;
    /***  End of each entry   ***/
  }

  /* End Job */
  /* ------- */
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
