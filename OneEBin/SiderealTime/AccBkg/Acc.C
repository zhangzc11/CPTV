
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void Acc()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
//	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;//17016
		const int NumOfBin = 17016;

	//
	Double_t TotalAcc[8]={0.0};
	Double_t Acc_t[8];

	Double_t AccInOneDay[8][24];
	Double_t RD_AccInOneDay[8][24];
	memset(AccInOneDay,0.0,sizeof(AccInOneDay));
	
	//
	Double_t TotalFullTime[8]={0.0};
	Double_t FullTime_t[8];

	Double_t FullTimeInOneDay[8][24];
	memset(FullTimeInOneDay,0.0,sizeof(FullTimeInOneDay));

	TFile *F_FullTime = new TFile("../FullTime.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
	Tree_FullTime->SetBranchAddress("FullTime",FullTime_t);

	double AccInEachBin[8][NumOfBin]={{0.0}};
	double RD_AccInEachBin[8][NumOfBin]={{0.0}};

		
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N24 = Bin%24;
		Tree_FullTime->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			FullTimeInOneDay[Det][N24] += FullTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
		}
	}

	const char *AccFName[8] = {
		"NumOfAccInOneDay_EH1_AD1.root","NumOfAccInOneDay_EH1_AD2.root","NumOfAccInOneDay_EH2_AD1.root","NumOfAccInOneDay_EH2_AD2.root",
		"NumOfAccInOneDay_EH3_AD1.root","NumOfAccInOneDay_EH3_AD2.root","NumOfAccInOneDay_EH3_AD3.root","NumOfAccInOneDay_EH3_AD4.root"};
	const char *E2_AccFName[8] = {
		"E2_NumOfAccInOneDay_EH1_AD1.root","E2_NumOfAccInOneDay_EH1_AD2.root","E2_NumOfAccInOneDay_EH2_AD1.root","E2_NumOfAccInOneDay_EH2_AD2.root",
		"E2_NumOfAccInOneDay_EH3_AD1.root","E2_NumOfAccInOneDay_EH3_AD2.root","E2_NumOfAccInOneDay_EH3_AD3.root","E2_NumOfAccInOneDay_EH3_AD4.root"};

	const char *AccFName_Bin[8] = {
		"NumOfAccInEachBin_EH1_AD1.root","NumOfAccInEachBin_EH1_AD2.root","NumOfAccInEachBin_EH2_AD1.root","NumOfAccInEachBin_EH2_AD2.root",
		"NumOfAccInEachBin_EH3_AD1.root","NumOfAccInEachBin_EH3_AD2.root","NumOfAccInEachBin_EH3_AD3.root","NumOfAccInEachBin_EH3_AD4.root"};
	const char *E2_AccFName_Bin[8] = {
		"E2_NumOfAccInEachBin_EH1_AD1.root","E2_NumOfAccInEachBin_EH1_AD2.root","E2_NumOfAccInEachBin_EH2_AD1.root","E2_NumOfAccInEachBin_EH2_AD2.root",
		"E2_NumOfAccInEachBin_EH3_AD1.root","E2_NumOfAccInEachBin_EH3_AD2.root","E2_NumOfAccInEachBin_EH3_AD3.root","E2_NumOfAccInEachBin_EH3_AD4.root"};

		
	TFile *FAcc[8];
	TFile *FE2_Acc[8];
	TTree *TreeAcc[8];
	TTree *TreeE2_Acc[8];

    for(int Det=0;Det<8;Det++)
	{
		Double_t NumOfAcc, E2_NumOfAcc;
		FAcc[Det] = new TFile(AccFName[Det]);
		TreeAcc[Det] = (TTree*)FAcc[Det]->Get("NumOfAccInOneDay");
		TreeAcc[Det]->SetBranchAddress("NumOfAccInOneDay",&NumOfAcc);

		FE2_Acc[Det] = new TFile(E2_AccFName[Det]);
		TreeE2_Acc[Det] = (TTree*)FE2_Acc[Det]->Get("E2_NumOfAccInOneDay");
		TreeE2_Acc[Det]->SetBranchAddress("E2_NumOfAccInOneDay",&E2_NumOfAcc);

		for(int N24=0;N24<24;N24++)
		{
			TreeAcc[Det]->GetEntry(N24);
			TreeE2_Acc[Det]->GetEntry(N24);
			AccInOneDay[Det][N24] = NumOfAcc;
			RD_AccInOneDay[Det][N24] = sqrt(E2_NumOfAcc)/AccInOneDay[Det][N24];
			TotalAcc[Det] += NumOfAcc;
		}
	}
    for(int Det=0;Det<8;Det++)
	{
		Double_t NumOfAcc, E2_NumOfAcc;
		FAcc[Det] = new TFile(AccFName_Bin[Det]);
		TreeAcc[Det] = (TTree*)FAcc[Det]->Get("NumOfAccInEachBin");
		TreeAcc[Det]->SetBranchAddress("NumOfAccInEachBin",&NumOfAcc);

		FE2_Acc[Det] = new TFile(E2_AccFName_Bin[Det]);
		TreeE2_Acc[Det] = (TTree*)FE2_Acc[Det]->Get("E2_NumOfAccInEachBin");
		TreeE2_Acc[Det]->SetBranchAddress("E2_NumOfAccInEachBin",&E2_NumOfAcc);

		for(int N24=0;N24<NumOfBin;N24++)
		{
			TreeAcc[Det]->GetEntry(N24);
			TreeE2_Acc[Det]->GetEntry(N24);
			AccInEachBin[Det][N24] = NumOfAcc;
			if(AccInEachBin[Det][N24]>0.0001)
			{
			RD_AccInEachBin[Det][N24] = sqrt(E2_NumOfAcc)/AccInEachBin[Det][N24];
			if(RD_AccInEachBin[Det][N24]>1.0)
			{
				AccInEachBin[Det][N24] = 0.0;
				RD_AccInEachBin[Det][N24]=0.0;
			}
			}
			TotalAcc[Det] += NumOfAcc;
		}
	}


	//////////Draw
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	const char *file_Name[8] = {
		"AccRate_EH1_AD1.pdf","AccRate_EH1_AD2.pdf","AccRate_EH2_AD1.pdf","AccRate_EH2_AD2.pdf",
		"AccRate_EH3_AD1.pdf","AccRate_EH3_AD2.pdf","AccRate_EH3_AD3.pdf","AccRate_EH3_AD4.pdf"};
	TCanvas *myC[8];
	TH1F *my_h[8];
	TLegend *leg[8];
	for(int Det=0;Det<8;Det++)
	{
		myC[Det] = new TCanvas(hist_Name[Det],hist_Name[Det],0,0,800,420);
		my_h[Det] = new TH1F(hist_Name[Det],hist_Name[Det],24,0,24);
	   Double_t MaxR=0.0,MeanR=0.0,MinR=86400.0*AccInOneDay[Det][0]/FullTimeInOneDay[Det][0],MaxE=0.0;

	    for(int i=0;i<24;i++)
	    {
		   my_h[Det]->SetBinContent(i+1,86400.0*AccInOneDay[Det][i]/FullTimeInOneDay[Det][i]);
		   my_h[Det]->SetBinError(i+1,RD_AccInOneDay[Det][i]*86400.0*AccInOneDay[Det][i]/FullTimeInOneDay[Det][i]);
		   MeanR += 86400.0*AccInOneDay[Det][i]/FullTimeInOneDay[Det][i];
		   if(86400.0*AccInOneDay[Det][i]/FullTimeInOneDay[Det][i]>MaxR){MaxR=86400.0*AccInOneDay[Det][i]/FullTimeInOneDay[Det][i];}
		   if(86400.0*AccInOneDay[Det][i]/FullTimeInOneDay[Det][i]<MinR){MinR=86400.0*AccInOneDay[Det][i]/FullTimeInOneDay[Det][i];}
		   if(RD_AccInOneDay[Det][i] > MaxE){MaxE = RD_AccInOneDay[Det][i];}
	    }
		cout<<"Ave Acc rate of "<<hist_Name[Det]<<"   "<<86400.0*TotalAcc[Det]/TotalFullTime[Det]<<endl;
		cout<<"Time Variation: "<<24.0*(MaxR-MinR)/MeanR<<endl;
		cout<<"Maximum Error: "<<MaxE<<endl;

		my_h[Det]->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.09/24.00 seconds)");
	my_h[Det]->GetYaxis()->SetTitle("Acc Rate (/day)");
	//my_h[Det]->GetYaxis()->SetRangeUser(1990*1e3,2080*1e3);
	my_h[Det]->GetXaxis()->SetRangeUser(0,24);
	my_h[Det]->GetXaxis()->SetNdivisions(24);
	
	my_h[Det]->SetTitle("");
	my_h[Det]->SetLineWidth(3);

	my_h[Det]->GetYaxis()->SetTitleOffset(0.9);
	my_h[Det]->GetYaxis()->SetTitleSize(0.05);
	my_h[Det]->GetYaxis()->SetLabelSize(0.05);
	my_h[Det]->GetYaxis()->SetLabelOffset(0.0);
	
	my_h[Det]->GetXaxis()->SetTitleOffset(0.8);
	my_h[Det]->GetXaxis()->SetTitleSize(0.05);
	my_h[Det]->GetXaxis()->SetLabelSize(0.045);
	my_h[Det]->GetXaxis()->SetLabelOffset(0.0);
	
	my_h[Det]->Draw();

   leg[Det] = new TLegend(0.35, 0.75, 0.65, 0.9);
   leg[Det]->AddEntry(my_h[Det],hist_Name[Det],"");
   leg[Det]->SetFillStyle(0);
   leg[Det]->SetBorderSize(0);
   leg[Det]->SetTextColor(kRed);
   leg[Det]->Draw();

	myC[Det]->SaveAs(file_Name[Det]);
	}

	//save
	TFile  *F_AccInOneDay = new TFile("AccInOneDay.root","recreate");
	TTree *Tree_AccInOneDay = new TTree("AccInOneDay","AccInOneDay");
	Tree_AccInOneDay->Branch("AccInOneDay",Acc_t,"Acc_t[8]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			Acc_t[Det] = AccInOneDay[Det][Bin];
		}
		Tree_AccInOneDay->Fill();
	}
	Tree_AccInOneDay->Write();

	TFile  *F_RD_AccInOneDay = new TFile("RD_AccInOneDay.root","recreate");
	TTree *Tree_RD_AccInOneDay = new TTree("RD_AccInOneDay","RD_AccInOneDay");
	Tree_RD_AccInOneDay->Branch("RD_AccInOneDay",Acc_t,"Acc_t[8]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			Acc_t[Det] = RD_AccInOneDay[Det][Bin];
		}
		Tree_RD_AccInOneDay->Fill();
	}
	Tree_RD_AccInOneDay->Write();

		
		
	TFile  *F_AccInEachBin = new TFile("AccInEachBin.root","recreate");
	TTree *Tree_AccInEachBin = new TTree("AccInEachBin","AccInEachBin");
	Tree_AccInEachBin->Branch("AccInEachBin",Acc_t,"Acc_t[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			Acc_t[Det] = AccInEachBin[Det][Bin];
		}
		Tree_AccInEachBin->Fill();
	}
	Tree_AccInEachBin->Write();

	TFile  *F_RD_AccInEachBin = new TFile("RD_AccInEachBin.root","recreate");
	TTree *Tree_RD_AccInEachBin = new TTree("RD_AccInEachBin","RD_AccInEachBin");
	Tree_RD_AccInEachBin->Branch("RD_AccInEachBin",Acc_t,"Acc_t[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			Acc_t[Det] = RD_AccInEachBin[Det][Bin];
		}
		Tree_RD_AccInEachBin->Fill();
	}
	Tree_RD_AccInEachBin->Write();


		
		
}
