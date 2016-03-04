
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void IBD_Candidate()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;//17016

	Double_t TotalIBD[8]={0.0};
	Int_t IBD_t[8];

	Double_t IBDInOneDay[8][24];
	memset(IBDInOneDay,0.0,sizeof(IBDInOneDay));

	TFile *F_IBD = new TFile("../IBD.root");
	TTree *Tree_IBD = (TTree*)F_IBD->Get("IBD");
	Tree_IBD->SetBranchAddress("IBD",IBD_t);

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
		Tree_IBD->GetEntry(Bin);
		Tree_FullTime->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			IBDInOneDay[Det][N24] += 1.0*IBD_t[Det];
			FullTimeInOneDay[Det][N24] += FullTime_t[Det];
			TotalIBD[Det] += 1.0*IBD_t[Det];
		}
	}
	
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	const char *file_Name[8] = {
		"IBDCandidateInOneDay_EH1_AD1.pdf","IBDCandidateInOneDay_EH1_AD2.pdf","IBDCandidateInOneDay_EH2_AD1.pdf","IBDCandidateInOneDay_EH2_AD2.pdf",
		"IBDCandidateInOneDay_EH3_AD1.pdf","IBDCandidateInOneDay_EH3_AD2.pdf","IBDCandidateInOneDay_EH3_AD3.pdf","IBDCandidateInOneDay_EH3_AD4.pdf"};
	TCanvas *myC[8];
	TH1F *my_h[8];
	TLegend *leg[8];
	for(int Det=0;Det<8;Det++)
	{
		myC[Det] = new TCanvas(hist_Name[Det],hist_Name[Det],0,0,800,420);
		my_h[Det] = new TH1F(hist_Name[Det],hist_Name[Det],24,0,24);
	    Double_t MaxR=0.0,MinR=86400.0*IBDInOneDay[Det][0]/FullTimeInOneDay[Det][0],MeanR=0.0,MaxE=0.0;

	    for(int i=0;i<24;i++)
	    {
		   my_h[Det]->SetBinContent(i+1,IBDInOneDay[Det][i]);
		   my_h[Det]->SetBinError(i+1,sqrt(IBDInOneDay[Det][i]));
	    }


		my_h[Det]->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.09/24.00 seconds)");
	my_h[Det]->GetYaxis()->SetTitle("IBD candidate number");
	//my_h[Det]->GetYaxis()->SetRangeUser(1990*1e3,2080*1e3);
	my_h[Det]->GetXaxis()->SetRangeUser(0,24);
	my_h[Det]->GetXaxis()->SetNdivisions(24);
	
	my_h[Det]->SetTitle("");
	my_h[Det]->SetLineWidth(3);

	my_h[Det]->GetYaxis()->SetTitleOffset(0.7);
	my_h[Det]->GetYaxis()->SetTitleSize(0.07);
	my_h[Det]->GetYaxis()->SetLabelSize(0.06);
	my_h[Det]->GetYaxis()->SetLabelOffset(0.0);
	
	my_h[Det]->GetXaxis()->SetTitleOffset(0.8);
	my_h[Det]->GetXaxis()->SetTitleSize(0.06);
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


	//////////////////////IBD Rate Hall////////////////////////////



}