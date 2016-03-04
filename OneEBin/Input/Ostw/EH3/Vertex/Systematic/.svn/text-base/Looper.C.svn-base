//
//   An example tree looper
//
//   Zhe Wang, Jan. 27, 2012
//
#include <stdlib.h>
#include <fstream>
#include "TreeReader.h"
#include <string>
#include <iostream>
#include "TChain.h"
#include "TH1F.h"
#include "math.h"
#include "TRandom.h"
using namespace std;

TreeReader* TR;

int Usage()
{
  cout<<"Usage:"<<endl;
  cout<<"    Ostw InputFile.root(.list) Output.root"<<endl;
  cout<<endl;
  exit(1);
}

int BeginJob();
int EndJob();

int main(int argc, char** argv)
{
  string inputfile;
  string outputfile;
  vector<string> datafiles;

  /* Argument parsing */
  /* ---------------- */
  if( argc != 3 ) {
    Usage();
  } else {
    inputfile = argv[1];
    outputfile = argv[2];

    string extension = inputfile.substr( inputfile.length()-5, 5 );
    /* A single input file */
    if( extension == ".root" )  {
      cout<<"A single input file, "<<inputfile<<endl;
      datafiles.push_back(inputfile);
    }
    /* Input file is a list */
    else if( extension == ".list" )  {
      cout<<"A list of root files, "<<inputfile<<endl;
      /* Grab all the data files in the list */
      ifstream inlist( inputfile.c_str() );
      string line;
      while( getline( inlist, line ) )  {
        datafiles.push_back( line );
      }
    }
    /* Other errors */
    else {
      Usage();
    }
  }

  /* Load the StreamChain and initializa StreamChain Tree reader */
  /* ----------------------------------------------------------- */
  TChain* EventChain = new TChain("Event");

  for( unsigned int i =0; i<datafiles.size(); i++ ) {
    EventChain->Add( datafiles[i].c_str() );
  }
  cout<<datafiles.size()<<" data files will be processed."<<endl;


  // Load the ReadinChain Tree
  // Get the ReadinChain Tree reader
  TR = new TreeReader;
  TR->Init(EventChain);

  /* Begin Job */
  /* --------- */
  if( BeginJob() == 0 ) {
    cout<<"BeginJob failed"<<endl;
    return 0;
  }

  TFile f( outputfile.c_str(), "RECREATE" );
  TH1F* hDistOrg = new TH1F("DistOrg","DistOrg",1000,0,3500);
  TH1F* hDistNew = new TH1F("DistNew","DistNew",1000,0,3500);

  int nTot = 0;
  int nOrg = 0;
  int nNew = 0;

  TRandom rand;
  
  /* The main loop over every stream entries */
  /* --------------------------------------- */
  unsigned int entries = EventChain->GetEntries();
  for( unsigned int entry=0; entry<entries; entry++ )  {
    unsigned int localentry = EventChain->LoadTree(entry);
    int ret = TR->GetEntry( localentry );
    if( ret==0 ) { 
      cout<<"Warning: Read error"<<endl;
    }

    /*** Test each entry here ***/
    if( TR->Fold != 2 ) continue;
    if( TR->E[1] < 1.9988 ) continue;
    if( TR->E[1] > 2.9852 ) continue;
    
    nTot++;
    
    /* Original case */
    {
      /* Useful event left */
      double x0,y0,z0, x1,y1,z1;
      /* IBD primary vertex */
      x0 =  TR->XT[0];
      y0 =  TR->YT[0];
      z0 =  TR->ZT[0];
      /* Gamma dep center */
      x1 =  TR->XCpt[1];
      y1 =  TR->YCpt[1];
      z1 =  TR->ZCpt[1];
      
      /* Step 1, gamma range */

      /* Step 2, rec shrink */
      x0 *= 0.97;
      y0 *= 0.97;
      z0 *= 0.89;
     
      /* Step 3, resolution */
      x0 += rand.Gaus(0, 160);
      y0 += rand.Gaus(0, 160);
      z0 += rand.Gaus(0, 120);

      x1 += rand.Gaus(0, 160);
      y1 += rand.Gaus(0, 160);
      z1 += rand.Gaus(0, 120);
      
      double l = sqrt( pow((x1-x0),2) + pow((y1-y0),2) + pow((z1-z0),2) );
      hDistOrg->Fill(l);
      
      if( l<500 ) nOrg++;
    }

    /* New case */
    {
      /* Useful event left */
      double x0,y0,z0, x1,y1,z1;
      /* IBD primary vertex */
      x0 =  TR->XT[0];
      y0 =  TR->YT[0];
      z0 =  TR->ZT[0];
      /* Gamma dep center */
      x1 =  TR->XCpt[1];
      y1 =  TR->YCpt[1];
      z1 =  TR->ZCpt[1];

      /* Step 1, gamma range */
      x1 = x0 + (x1-x0)* (1-0.007);
      y1 = y0 + (y1-y0)* (1-0.007);
      z1 = z0 + (z1-z0)* (1-0.007);

      /* step 2, rec shrink */
      x0 *= 0.97;
      y0 *= 0.97;
      z0 *= 0.89;
      
      x0 *= (1-0.012);
      y0 *= (1-0.012);
      z0 *= (1-0.016);

      /* Step 3, resolution */
      x0 += rand.Gaus(0, 160 * (1-0.019));
      y0 += rand.Gaus(0, 160 * (1-0.019));
      z0 += rand.Gaus(0, 120 * (1-0.025));

      x1 += rand.Gaus(0, 160 * (1-0.019));
      y1 += rand.Gaus(0, 160 * (1-0.019));
      z1 += rand.Gaus(0, 120 * (1-0.025));

      double l = sqrt( pow((x1-x0),2) + pow((y1-y0),2) + pow((z1-z0),2) );
      hDistNew->Fill(l);

      if( l<500 ) nNew++;
    }

    /***  End of each entry   ***/

  }

  f.Write();

  double EffOrg = nOrg/double(nTot);
  double ErrOrg = sqrt( EffOrg*(1-EffOrg)/double(nTot) );
  
  double EffNew = nNew/double(nTot);
  double ErrNew = sqrt( EffNew*(1-EffNew)/double(nTot) );

  cout<<nTot<<"\t"<<nOrg<<"\t"<<nNew<<endl;
  cout<<EffOrg<<"+/-"<<ErrOrg<<" vs. "<<EffNew<<"+/-"<<ErrNew<<endl;
  

  
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
