#include "TFile.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TDirectory.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
  string FileName;
  
  if( argc != 2 ) {
    cout<<"Usage:"<<endl;
    cout<<"     GetMean Data.root"<<endl;
    cout<<endl;
    return 1;
  } else {
    FileName = argv[1];
  }

  TFile* DataFile = new TFile(FileName.c_str());
  TH1F *hZ = (TH1F*)DataFile->Get("SglZ");
  
  cout<<hZ->GetMean()<<endl;

  delete hZ;
  DataFile->Close();
  delete DataFile;

  return 1;
}
  
  
  
