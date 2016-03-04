#include<iostream>
using namespace std;

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

#include<sstream>
#include<fstream>
#include<iomanip>
#include<map>

int main(int argc, char *argv[])
{
  //////
  string usr_run_str = argv[1];
  int usr_run = 0;

  stringstream convert(usr_run_str);
  if(!(convert>>usr_run))
    usr_run = 0;

  int RunBgn = usr_run;
  int RunEnd = usr_run;

  TString roostr = "";
  
  roostr = TString::Format("/back1/dayabay_back1/data/TWin/20_P14A/Gd/EH1/%07d.TWin.root", usr_run);

  ifstream ReadFile(roostr);
  if(!ReadFile) return 0;

  ///////
  TChain *Event = new TChain("Event");
  Event->Add(roostr);

  const int Max = 20;//Maximum number of Fold
  int    TrigNano[Max];
  int    TrigSec[Max];
  double E[Max];
  int    Fold;
  double Z[Max];
  int Det;
  double D2First[Max];

  //Associate branches with variables//
  Event->SetBranchAddress("TrigNano",TrigNano);
  Event->SetBranchAddress("TrigSec",TrigSec);
  Event->SetBranchAddress("E",E);
  Event->SetBranchAddress("Fold",&Fold);
  Event->SetBranchAddress("Det",&Det);
  Event->SetBranchAddress("Z",Z);
  Event->SetBranchAddress("D2First",D2First);

  int entries = Event->GetEntries();

  //////IBD_EH1_AD1
  double EveTime;
  roostr = TString::Format("./result/IBD/%07d_IBD_EH1_AD1.root", usr_run);
  TFile *F_IBD_EH1_AD1 = new TFile(roostr, "recreate");
  TTree *IBD_Tree_EH1_AD1 = new TTree("IBD","IBD");
  IBD_Tree_EH1_AD1->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if (E[1]>6&&E[1]<12&&E[0]>0.7&&E[0]<12&&Fold==2&&Det==1&&(((TrigSec[1]-TrigSec[0])*1e9+(TrigNano[1]-TrigNano[0]))<200000)&&(((TrigSec[1]-TrigSec[0])*1e9+(TrigNano[1]-TrigNano[0]))>1000))
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  IBD_Tree_EH1_AD1->Fill();
	}
    }

  IBD_Tree_EH1_AD1->Write();
  F_IBD_EH1_AD1->Close();

  //////IBD_EH1_AD2
 
  roostr = TString::Format("./result/IBD/%07d_IBD_EH1_AD2.root", usr_run);
  TFile *F_IBD_EH1_AD2 = new TFile(roostr, "recreate");
  TTree *IBD_Tree_EH1_AD2 = new TTree("IBD","IBD");
  IBD_Tree_EH1_AD2->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if (E[1]>6&&E[1]<12&&E[0]>0.7&&E[0]<12&&Fold==2&&Det==2&&(((TrigSec[1]-TrigSec[0])*1e9+(TrigNano[1]-TrigNano[0]))<200000)&&(((TrigSec[1]-TrigSec[0])*1e9+(TrigNano[1]-TrigNano[0]))>1000))
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  IBD_Tree_EH1_AD2 ->Fill();
	}
    }

  IBD_Tree_EH1_AD2->Write();
  F_IBD_EH1_AD2->Close();

  //nLikeUp_EH1_AD1

  roostr = TString::Format("./result/nLikeUp/%07d_Up_EH1_AD1.root", usr_run);
  TFile *F_Up_EH1_AD1 = new TFile(roostr, "recreate");
  TTree *nLikeUpTree_EH1_AD1 = new TTree("nLikeUp","nLikeUp");
  nLikeUpTree_EH1_AD1->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if ((Fold==1)&&(E[0]>6)&&(E[0]<12)&&(Z[0]>0)&&Det==1)
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  nLikeUpTree_EH1_AD1->Fill();
	}
    }

  nLikeUpTree_EH1_AD1->Write();
  F_Up_EH1_AD1->Close();

   //nLikeUp_EH1_AD2
  roostr = TString::Format("./result/nLikeUp/%07d_Up_EH1_AD2.root", usr_run);
  TFile *F_Up_EH1_AD2 = new TFile(roostr, "recreate");
  TTree *nLikeUpTree_EH1_AD2 = new TTree("nLikeUp","nLikeUp");
  nLikeUpTree_EH1_AD2->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if ((Fold==1)&&(E[0]>6)&&(E[0]<12)&&(Z[0]>0)&&Det==2)
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  nLikeUpTree_EH1_AD2->Fill();
	}
    }

  nLikeUpTree_EH1_AD2->Write();
  F_Up_EH1_AD2->Close();
  
 //nLikeDown_EH1_AD1

  roostr = TString::Format("./result/nLikeDown/%07d_Down_EH1_AD1.root", usr_run);
  TFile *F_Down_EH1_AD1 = new TFile(roostr, "recreate");
  TTree *nLikeDownTree_EH1_AD1 = new TTree("nLikeDown","nLikeDown");
  nLikeDownTree_EH1_AD1->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if ((Fold==1)&&(E[0]>6)&&(E[0]<12)&&(Z[0]<0)&&Det==1)
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  nLikeDownTree_EH1_AD1->Fill();
	}
    }

  nLikeDownTree_EH1_AD1->Write();
  F_Down_EH1_AD1->Close();

   //nLikeDown_EH1_AD2
  roostr = TString::Format("./result/nLikeDown/%07d_Down_EH1_AD2.root", usr_run);
  TFile *F_Down_EH1_AD2 = new TFile(roostr, "recreate");
  TTree *nLikeDownTree_EH1_AD2 = new TTree("nLikeDown","nLikeDown");
  nLikeDownTree_EH1_AD2->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if ((Fold==1)&&(E[0]>6)&&(E[0]<12)&&(Z[0]<0)&&Det==2)
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  nLikeDownTree_EH1_AD2->Fill();
	}
    }

  nLikeDownTree_EH1_AD2->Write();
  F_Down_EH1_AD2->Close();
  
  //nSingleUp_EH1_AD1
  roostr = TString::Format("./result/nSgUp/%07d_SgUp_EH1_AD1.root", usr_run);
  TFile *F_SgUp_EH1_AD1 = new TFile(roostr, "recreate");
  TTree *SgUpTree_EH1_AD1 = new TTree("nSgUp","nSgUp");
  SgUpTree_EH1_AD1->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if (Det==1)
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  SgUpTree_EH1_AD1->Fill();
	}
    }

  SgUpTree_EH1_AD1->Write();
  F_SgUp_EH1_AD1->Close();

  //nSingleUp_EH1_AD2
  roostr = TString::Format("./result/nSgUp/%07d_SgUp_EH1_AD2.root", usr_run);
  TFile *F_SgUp_EH1_AD2 = new TFile(roostr, "recreate");
  TTree *SgUpTree_EH1_AD2 = new TTree("nSgUp","nSgUp");
  SgUpTree_EH1_AD2->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if (Det==2)
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  SgUpTree_EH1_AD2->Fill();
	}
    }

  SgUpTree_EH1_AD2->Write();
  F_SgUp_EH1_AD2->Close();

  //nSingleLow_EH1_AD1
  roostr = TString::Format("./result/nSgLow/%07d_SgLow_EH1_AD1.root", usr_run);
  TFile *F_SgLow_EH1_AD1 = new TFile(roostr, "recreate");
  TTree *SgLowTree_EH1_AD1 = new TTree("nSgLow","nSgLow");
  SgLowTree_EH1_AD1->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if ((Det==1)&&(Fold==1))
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  SgLowTree_EH1_AD1->Fill();
	}
	  else if((Det==1)&&(Fold==2)&&D2First[1]>500)
	  {
		  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
		  SgLowTree_EH1_AD1->Fill();
		  SgLowTree_EH1_AD1->Fill();
	  }
    }

  SgLowTree_EH1_AD1->Write();
  F_SgLow_EH1_AD1->Close();

  //nSingleLow_EH1_AD2
  roostr = TString::Format("./result/nSgLow/%07d_SgLow_EH1_AD2.root", usr_run);
  TFile *F_SgLow_EH1_AD2 = new TFile(roostr, "recreate");
  TTree *SgLowTree_EH1_AD2 = new TTree("nSgLow","nSgLow");
  SgLowTree_EH1_AD2->Branch("EveTime",&EveTime,"EveTime/D");
  
  for(int idx=0; idx<entries; idx++)
    {
      Event->GetEntry(idx);

      if ((Det==2)&&(Fold==1))
	{
	  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
	  SgLowTree_EH1_AD2->Fill();
	}
	  else if((Det==2)&&(Fold==2)&&D2First[1]>500)
	  {
		  EveTime=TrigSec[0]+TrigNano[0]*1e-9;
		  SgLowTree_EH1_AD2->Fill();
		  SgLowTree_EH1_AD2->Fill();
	  }
    }

  SgLowTree_EH1_AD2->Write();
  F_SgLow_EH1_AD2->Close();



  return 0;
}
