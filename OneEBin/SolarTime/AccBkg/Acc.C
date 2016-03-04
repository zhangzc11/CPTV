
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void Acc()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

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
		cout<<"Total Acc of "<<hist_Name[Det]<<TotalAcc[Det]<<endl;
		cout<<"Time Variation: "<<24.0*(MaxR-MinR)/MeanR<<endl;
		cout<<"Maximum Error: "<<MaxE<<endl;

		my_h[Det]->GetXaxis()->SetTitle("solar time(1 bin = 3600.0 seconds)");
	my_h[Det]->GetYaxis()->SetTitle("Acc/He8 Rate (/day)");
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

}