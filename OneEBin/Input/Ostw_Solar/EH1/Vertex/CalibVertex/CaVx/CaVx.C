#include "TFile.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TDirectory.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int Proj( const char* DataPath, int Ad, double& duration, TH1F* hX, TH1F* hY, TH1F* hZ);

int main(int argc, char** argv)
{
  string ClbData;
  string BkgData;
  string AdNo;
  int Ad;
  string Outputfile;
  

  if( argc != 5 ) {
    cout<<"Usage:"<<endl;
    cout<<"     CaVx  Calib.root  Bkg.root  AdNo  Out.root"<<endl;
    cout<<endl;
    return 1;
  } else {
    ClbData = argv[1];
    BkgData = argv[2];
    AdNo    = argv[3];
    Ad = atoi(AdNo.c_str());
    Outputfile  = argv[4];
  }

  TH1F* ClbX = new TH1F("ClbX","ClbX",100,-2500,2500);
  TH1F* ClbY = new TH1F("ClbY","ClbY",100,-2500,2500);
  TH1F* ClbZ = new TH1F("ClbZ","ClbZ",100,-2500,2500);
  double ClbDur;

  TH1F* BkgX = new TH1F("BkgX","BkgX",100,-2500,2500);
  TH1F* BkgY = new TH1F("BkgY","BkgY",100,-2500,2500);
  TH1F* BkgZ = new TH1F("BkgZ","BkgZ",100,-2500,2500);
  double BkgDur;

  TH1F* SglX = new TH1F("SglX","SglX",100,-2500,2500);
  TH1F* SglY = new TH1F("SglY","SglY",100,-2500,2500);
  TH1F* SglZ = new TH1F("SglZ","SglZ",100,-2500,2500);
  
  /* Start to process calibration and background pair */
  Proj(ClbData.c_str(), Ad, ClbDur, ClbX, ClbY, ClbZ);

  Proj(BkgData.c_str(), Ad, BkgDur, BkgX, BkgY, BkgZ);
  /* End of loop */

  SglX->Add( ClbX, BkgX, 1, -ClbDur/BkgDur );
  SglY->Add( ClbY, BkgY, 1, -ClbDur/BkgDur );
  SglZ->Add( ClbZ, BkgZ, 1, -ClbDur/BkgDur );

  TFile Output(Outputfile.c_str(), "RECREATE");
  ClbX->Write();
  ClbY->Write();
  ClbZ->Write();
  
  BkgX->Write();
  BkgY->Write();
  BkgZ->Write();

  SglX->Write();
  SglY->Write();
  SglZ->Write();

  Output.Close();

}
 
int Proj( const char* DataPath, int Ad, double& duration, TH1F* hX, TH1F* hY, TH1F* hZ) 
{
  TDirectory *where = gDirectory;         /* This must be here. */
  TFile* DataFile = new TFile(DataPath);
  TTree *DataTree = (TTree*)DataFile->Get("Event");
  
  where->cd();                            /* This must be here. Mystery. */

  int Fold, Det;
  int TrigSec[10], TrigNano[10];
  double E[10], X[10], Y[10], Z[10];
  DataTree->SetBranchAddress("Fold",&Fold);
  DataTree->SetBranchAddress("Det",&Det);
  DataTree->SetBranchAddress("TrigSec",TrigSec);
  DataTree->SetBranchAddress("TrigNano",TrigNano);
  DataTree->SetBranchAddress("E",E);
  DataTree->SetBranchAddress("X",X);
  DataTree->SetBranchAddress("Y",Y);
  DataTree->SetBranchAddress("Z",Z);

  int BeginSec(0), BeginNano(0);
  int EndSec(0), EndNano(0);
  
  int nentries = DataTree->GetEntries();
  for (int i = 0; i<nentries; i++) {
    DataTree->GetEntry(i);
    
    if( i==0 ) {
      BeginSec = TrigSec[0];
      BeginNano = TrigNano[0];
    }
    
    if( i == nentries-1 ) {
      EndSec = TrigSec[Fold-1];
      EndNano = TrigNano[Fold-1];
    }

    for ( int f=0; f<Fold; f++) {
      if( E[f]>1 && Det==Ad ) {  /* 1 MeV */
	hX->Fill(X[f]);
	hY->Fill(Y[f]);
	hZ->Fill(Z[f]);
      }
    }
  }

  duration = (EndSec-BeginSec)+1e-9*(EndNano-BeginNano);
  
  delete DataTree;
  DataFile->Close();
  delete DataFile;

  return 1;
}
  
  
  
