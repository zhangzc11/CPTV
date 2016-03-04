
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void Li9()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	Double_t Li9Rate[8] = {2.8,2.8,1.7,1.7,0.27,0.27,0.27,0.27};
	Double_t RD_Li9Rate[8] = {1.5/2.8,1.5/2.8,0.9/1.7,0.9/1.7,0.14/0.27,0.14/0.27,0.14/0.27,0.14/0.27};
	//
	Double_t TotalLi9[8]={0.0};
	Double_t Li9_t[8];

	Double_t Li9InOneDay[8][24];
	Double_t RD_Li9InOneDay[8][24];
	memset(Li9InOneDay,0.0,sizeof(Li9InOneDay));
	//
	Double_t TotalHMuG15[8]={0.0};
	Double_t HMuG15_t[8];

	Double_t HMuG15InOneDay[8][24];
	memset(HMuG15InOneDay,0.0,sizeof(HMuG15InOneDay));

	TFile *F_HMuG15 = new TFile("../HMuG15.root");
	TTree *Tree_HMuG15 = (TTree*)F_HMuG15->Get("HMuG15");
	Tree_HMuG15->SetBranchAddress("HMuG15",HMuG15_t);
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
		Tree_HMuG15->GetEntry(Bin);
		Tree_FullTime->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			HMuG15InOneDay[Det][N24] += HMuG15_t[Det];
			FullTimeInOneDay[Det][N24] += FullTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
			TotalHMuG15[Det] += HMuG15_t[Det];
		}
	}

	for(int Det=0;Det<8;Det++)
	{
		TotalLi9[Det] = Li9Rate[Det]*TotalFullTime[Det]/86400.0;
		for(int N24=0;N24<24;N24++)
		{
			Li9InOneDay[Det][N24] = TotalLi9[Det] * HMuG15InOneDay[Det][N24]/TotalHMuG15[Det];
			RD_Li9InOneDay[Det][N24] = sqrt(1.0/HMuG15InOneDay[Det][N24] - 1.0/TotalHMuG15[Det]);
		}
	}

	//////////Draw
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	const char *file_Name[8] = {
		"Li9Rate_EH1_AD1.pdf","Li9Rate_EH1_AD2.pdf","Li9Rate_EH2_AD1.pdf","Li9Rate_EH2_AD2.pdf",
		"Li9Rate_EH3_AD1.pdf","Li9Rate_EH3_AD2.pdf","Li9Rate_EH3_AD3.pdf","Li9Rate_EH3_AD4.pdf"};
	TCanvas *myC[8];
	TH1F *my_h[8];
	TLegend *leg[8];
	for(int Det=0;Det<8;Det++)
	{
		myC[Det] = new TCanvas(hist_Name[Det],hist_Name[Det],0,0,800,420);
		my_h[Det] = new TH1F(hist_Name[Det],hist_Name[Det],24,0,24);
	   Double_t MaxR=0.0,MeanR=0.0,MinR=86400.0*Li9InOneDay[Det][0]/FullTimeInOneDay[Det][0],MaxE=0.0;

	    for(int i=0;i<24;i++)
	    {
		   my_h[Det]->SetBinContent(i+1,86400.0*Li9InOneDay[Det][i]/FullTimeInOneDay[Det][i]);
		   my_h[Det]->SetBinError(i+1,RD_Li9InOneDay[Det][i]*86400.0*Li9InOneDay[Det][i]/FullTimeInOneDay[Det][i]);
		   MeanR += 86400.0*Li9InOneDay[Det][i]/FullTimeInOneDay[Det][i];
		   if(86400.0*Li9InOneDay[Det][i]/FullTimeInOneDay[Det][i]>MaxR){MaxR=86400.0*Li9InOneDay[Det][i]/FullTimeInOneDay[Det][i];}
		   if(86400.0*Li9InOneDay[Det][i]/FullTimeInOneDay[Det][i]<MinR){MinR=86400.0*Li9InOneDay[Det][i]/FullTimeInOneDay[Det][i];}
		   if(RD_Li9InOneDay[Det][i] > MaxE){MaxE = RD_Li9InOneDay[Det][i];}
	    }
		cout<<"Total Li9 of "<<hist_Name[Det]<<TotalLi9[Det]<<endl;
		cout<<"Time Variation: "<<24.0*(MaxR-MinR)/MeanR<<endl;
		cout<<"Maximum Error: "<<MaxE<<endl;

		my_h[Det]->GetXaxis()->SetTitle("solar time(1 bin = 3600.0 seconds)");
	my_h[Det]->GetYaxis()->SetTitle("Li9/He8 Rate (/day)");
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
	TFile  *F_Li9InOneDay = new TFile("Li9InOneDay.root","recreate");
	TTree *Tree_Li9InOneDay = new TTree("Li9InOneDay","Li9InOneDay");
	Tree_Li9InOneDay->Branch("Li9InOneDay",Li9_t,"Li9_t[8]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			Li9_t[Det] = Li9InOneDay[Det][Bin];
		}
		Tree_Li9InOneDay->Fill();
	}
	Tree_Li9InOneDay->Write();

	TFile  *F_RD_Li9InOneDay = new TFile("RD_Li9InOneDay.root","recreate");
	TTree *Tree_RD_Li9InOneDay = new TTree("RD_Li9InOneDay","RD_Li9InOneDay");
	Tree_RD_Li9InOneDay->Branch("RD_Li9InOneDay",Li9_t,"Li9_t[8]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			Li9_t[Det] = RD_Li9InOneDay[Det][Bin];
		}
		Tree_RD_Li9InOneDay->Fill();
	}
	Tree_RD_Li9InOneDay->Write();

}