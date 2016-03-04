
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void HMuG5()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;//17016

	Double_t TotalHMuG5[8]={0.0};
	Double_t HMuG5_t[8];

	Double_t HMuG5InOneDay[8][24];
	memset(HMuG5InOneDay,0.0,sizeof(HMuG5InOneDay));

	TFile *F_HMuG5 = new TFile("../HMuG5.root");
	TTree *Tree_HMuG5 = (TTree*)F_HMuG5->Get("HMuG5");
	Tree_HMuG5->SetBranchAddress("HMuG5",HMuG5_t);

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
		Tree_HMuG5->GetEntry(Bin);
		Tree_FullTime->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			HMuG5InOneDay[Det][N24] += HMuG5_t[Det];
			FullTimeInOneDay[Det][N24] += FullTime_t[Det];
			TotalHMuG5[Det] += HMuG5_t[Det];
		}
	}
	

	////////////////////////////////////////////
	gROOT->SetStyle("Plain");
    TStyle* style = new TStyle(*gStyle);
    style->SetName("myPlain");
	style->SetOptStat(0);
    gROOT->GetListOfStyles()->Add(style);
	 style->SetTextFont(132);
    style->SetLegendFont(132);
    style->SetLabelFont(132,"xyz");
    style->SetTitleFont(132,"");
    style->SetTitleFont(132,"xyz");
	// style->SetLabelSize(10,"xy");
	 style->SetLegendFillColor( 10 );
	 style->SetCanvasColor(0);
	 style->cd();
     gROOT->ForceStyle();


	/////////////////////////////////////////////


	const char *hist_Name[8] = {"EH1-AD1","EH1-AD2","EH2-AD1","EH2-AD2","EH3-AD1","EH3-AD2","EH3-AD3","EH3-AD4"}; 
	const char *file_Name[8] = {
		"HMuG5InOneDay_EH1_AD1.eps","HMuG5InOneDay_EH1_AD2.eps","HMuG5InOneDay_EH2_AD1.eps","HMuG5InOneDay_EH2_AD2.eps",
		"HMuG5InOneDay_EH3_AD1.eps","HMuG5InOneDay_EH3_AD2.eps","HMuG5InOneDay_EH3_AD3.eps","HMuG5InOneDay_EH3_AD4.eps"};
	TCanvas *myC[8];
	TH1F *my_h[8];
	TLegend *leg[8];
	for(int Det=0;Det<8;Det++)
	{
		myC[Det] = new TCanvas(hist_Name[Det],hist_Name[Det],0,0,800,420);
		my_h[Det] = new TH1F(hist_Name[Det],hist_Name[Det],24,0,24);
	    Double_t MaxR=0.0,MinR=86400.0*HMuG5InOneDay[Det][0]/FullTimeInOneDay[Det][0],MeanR=0.0,MaxE=0.0;

	    for(int i=0;i<24;i++)
	    {
		   my_h[Det]->SetBinContent(i+1,0.001*86400.0*HMuG5InOneDay[Det][i]/FullTimeInOneDay[Det][i]);
		   my_h[Det]->SetBinError(i+1,0.001*86400.0*sqrt(HMuG5InOneDay[Det][i])/FullTimeInOneDay[Det][i]);
		   MeanR += 86400.0*HMuG5InOneDay[Det][i]/FullTimeInOneDay[Det][i];
		   if(86400.0*HMuG5InOneDay[Det][i]/FullTimeInOneDay[Det][i]>MaxR){MaxR=86400.0*HMuG5InOneDay[Det][i]/FullTimeInOneDay[Det][i];}
		   if(86400.0*HMuG5InOneDay[Det][i]/FullTimeInOneDay[Det][i]<MinR){MinR=86400.0*HMuG5InOneDay[Det][i]/FullTimeInOneDay[Det][i];}
		   if(1.0/sqrt(HMuG5InOneDay[Det][i]) > MaxE){MaxE = 1.0/sqrt(HMuG5InOneDay[Det][i]);}
	    }
		cout<<"Total HMuG5 of "<<hist_Name[Det]<<TotalHMuG5[Det]<<endl;
		cout<<"Time Variation: "<<24.0*(MaxR-MinR)/MeanR<<endl;
		cout<<"Maximum Error: "<<MaxE<<endl;

		my_h[Det]->GetXaxis()->SetTitle("sidereal time (1 bin = 86164.09/24 seconds)");
		my_h[Det]->GetYaxis()->SetTitle("0.5~2.5GeV Muon Rate (10^{3}/day)");
	//my_h[Det]->GetYaxis()->SetRangeUser(1990*1e3,2080*1e3);
	if(Det==4)
		{
	my_h[Det]->GetYaxis()->SetRangeUser(50.0,50.5);
		}
	my_h[Det]->GetXaxis()->SetRangeUser(0,24);
	my_h[Det]->GetXaxis()->SetNdivisions(24);
	
	my_h[Det]->SetTitle("");
	my_h[Det]->SetLineWidth(3);
	my_h[Det]->GetYaxis()->SetNdivisions(505);
	my_h[Det]->GetYaxis()->SetTitleOffset(0.7);
	my_h[Det]->GetYaxis()->CenterTitle();
	my_h[Det]->GetYaxis()->SetTitleSize(0.07);
	my_h[Det]->GetYaxis()->SetLabelSize(0.06);
	my_h[Det]->GetYaxis()->SetLabelOffset(0.0);
	
	my_h[Det]->GetXaxis()->SetTitleOffset(0.69);
	my_h[Det]->GetXaxis()->SetTitleSize(0.07);
	my_h[Det]->GetXaxis()->SetLabelSize(0.06);
	my_h[Det]->GetXaxis()->SetLabelOffset(0.0);
	
	my_h[Det]->Draw();


   leg[Det] = new TLegend(0.35, 0.75, 0.65, 0.9);
   leg[Det]->AddEntry(my_h[Det],hist_Name[Det],"");
   leg[Det]->SetFillStyle(0);
   leg[Det]->SetBorderSize(0);
   leg[Det]->SetTextColor(kRed);
   //leg[Det]->Draw();

	myC[Det]->SaveAs(file_Name[Det]);
	}

	//save
	TFile  *F_HMuG5InOneDay = new TFile("HMuG5InOneDay.root","recreate");
	TTree *Tree_HMuG5InOneDay = new TTree("HMuG5InOneDay","HMuG5InOneDay");
	Tree_HMuG5InOneDay->Branch("HMuG5InOneDay",HMuG5_t,"HMuG5_t[8]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			HMuG5_t[Det] = HMuG5InOneDay[Det][Bin];
		}
		Tree_HMuG5InOneDay->Fill();
	}
	Tree_HMuG5InOneDay->Write();

}