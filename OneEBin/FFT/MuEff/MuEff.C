
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void MuEff()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
//	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;//17016
	const int NumOfBin = 17016;	
	Double_t TotalMuEff[8]={0.0};
	Double_t MuEff_t[8];

	Double_t MuEffInOneDay[8][24];
	memset(MuEffInOneDay,0.0,sizeof(MuEffInOneDay));

	Double_t TotalLiveTime[8]={0.0};
	Double_t LiveTime_t[8];

	Double_t LiveTimeInOneDay[8][24];
	memset(LiveTimeInOneDay,0.0,sizeof(LiveTimeInOneDay));

	TFile *F_LiveTime = new TFile("../LiveTime.root");
	TTree *Tree_LiveTime = (TTree*)F_LiveTime->Get("LiveTime");
	Tree_LiveTime->SetBranchAddress("LiveTime",LiveTime_t);

	Double_t TotalFullTime[8]={0.0};
	Double_t FullTime_t[8];

	Double_t FullTimeInOneDay[8][24];
	memset(FullTimeInOneDay,0.0,sizeof(FullTimeInOneDay));

	TFile *F_FullTime = new TFile("../FullTime.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
	Tree_FullTime->SetBranchAddress("FullTime",FullTime_t);

	double FullTimeInEachBin[8][NumOfBin] = {{0.0}};
	double LiveTimeInEachBin[8][NumOfBin] = {{0.0}};
	double MuEffInEachBin[8][NumOfBin] = {{0.0}};


	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N24 = Bin%24;
		Tree_FullTime->GetEntry(Bin);
		Tree_LiveTime->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			FullTimeInEachBin[Det][Bin] = FullTime_t[Det];
			LiveTimeInEachBin[Det][Bin] = LiveTime_t[Det];


			LiveTimeInOneDay[Det][N24] += LiveTime_t[Det];
			FullTimeInOneDay[Det][N24] += FullTime_t[Det];
			TotalLiveTime[Det] += LiveTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
		}
	}

	for(int Det=0;Det<8;Det++)
	{
		for(int N24=0;N24<24;N24++)
		{
			MuEffInOneDay[Det][N24] = LiveTimeInOneDay[Det][N24]/FullTimeInOneDay[Det][N24];
		}

		for(int N24=0;N24<NumOfBin;N24++)
		{
			if(LiveTimeInEachBin[Det][N24]>10)
			{
			MuEffInEachBin[Det][N24] = LiveTimeInEachBin[Det][N24]/FullTimeInEachBin[Det][N24];
			}
		}

		TotalMuEff[Det] = TotalLiveTime[Det]/TotalFullTime[Det];
	}
	
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	const char *file_Name[8] = {
		"MuEffInOneDay_EH1_AD1.pdf","MuEffInOneDay_EH1_AD2.pdf","MuEffInOneDay_EH2_AD1.pdf","MuEffInOneDay_EH2_AD2.pdf",
		"MuEffInOneDay_EH3_AD1.pdf","MuEffInOneDay_EH3_AD2.pdf","MuEffInOneDay_EH3_AD3.pdf","MuEffInOneDay_EH3_AD4.pdf"};
	TCanvas *myC[8];
	TH1F *my_h[8];
	TLegend *leg[8];
	for(int Det=0;Det<8;Det++)
	{
		myC[Det] = new TCanvas(hist_Name[Det],hist_Name[Det],0,0,800,420);
		my_h[Det] = new TH1F(hist_Name[Det],hist_Name[Det],24,0,24);
	    Double_t MaxR=0.0,MinR=MuEffInOneDay[Det][0],MeanR=0.0,MaxE=0.0;

	    for(int i=0;i<24;i++)
	    {
		   my_h[Det]->SetBinContent(i+1,MuEffInOneDay[Det][i]);
		   MeanR += MuEffInOneDay[Det][i];
		   if(MuEffInOneDay[Det][i]>MaxR){MaxR=MuEffInOneDay[Det][i];}
		   if(MuEffInOneDay[Det][i]<MinR){MinR=MuEffInOneDay[Det][i];}
	    }
		cout<<"Average MuEff of "<<hist_Name[Det]<<":   "<<TotalMuEff[Det]<<endl;
		cout<<"Time Variation: "<<24.0*(MaxR-MinR)/MeanR<<endl;

		my_h[Det]->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.09/24.00 seconds)");
	//my_h[Det]->GetYaxis()->SetTitle("Ad Muon Rate (/day)");
	//my_h[Det]->GetYaxis()->SetRangeUser(1990*1e3,2080*1e3);
	my_h[Det]->GetXaxis()->SetRangeUser(0,24);
	my_h[Det]->GetXaxis()->SetNdivisions(24);
	
	my_h[Det]->SetTitle("");
	my_h[Det]->SetLineWidth(3);

	my_h[Det]->GetYaxis()->SetTitleOffset(0.7);
	//my_h[Det]->GetYaxis()->SetTitleSize(0.07);
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

	//save
	TFile  *F_MuEffInOneDay = new TFile("MuEffInOneDay.root","recreate");
	TTree *Tree_MuEffInOneDay = new TTree("MuEffInOneDay","MuEffInOneDay");
	Tree_MuEffInOneDay->Branch("MuEffInOneDay",MuEff_t,"MuEff_t[8]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			MuEff_t[Det] = MuEffInOneDay[Det][Bin];
		}
		Tree_MuEffInOneDay->Fill();
	}
	Tree_MuEffInOneDay->Write();
	//save in each bin
	TFile  *F_MuEffInEachBin = new TFile("MuEffInEachBin.root","recreate");
	TTree *Tree_MuEffInEachBin = new TTree("MuEffInEachBin","MuEffInEachBin");
	Tree_MuEffInEachBin->Branch("MuEffInEachBin",MuEff_t,"MuEff_t[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			MuEff_t[Det] = MuEffInEachBin[Det][Bin];
		}
		Tree_MuEffInEachBin->Fill();
	}
	Tree_MuEffInEachBin->Write();

}
