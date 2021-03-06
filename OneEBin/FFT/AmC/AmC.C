
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void AmC()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
//	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;//17016

		const int NumOfBin = 17016;

	Int_t Bin_8AD = 7080;


	Double_t AmCRate_6AD[8] = {0.27,0.25,0.27,0.0,0.22,0.21,0.21,0.0};
	Double_t AmCRate_8AD[8] = {0.20,0.21,0.18,0.22,0.06,0.04,0.04,0.07};

	//
	Double_t TotalAmC_6AD[8]={0.0};
	Double_t TotalAmC_8AD[8]={0.0};

	Double_t AmC_t[8];


	Double_t AmCInOneDay[8][24];
	Double_t RD_AmCInOneDay[8][24];
	memset(AmCInOneDay,0.0,sizeof(AmCInOneDay));

	Double_t AmCInOneDay_6AD[8][24];
	Double_t RD_AmCInOneDay_6AD[8][24];
	memset(AmCInOneDay_6AD,0.0,sizeof(AmCInOneDay_6AD));
	Double_t AmCInOneDay_8AD[8][24];
	Double_t RD_AmCInOneDay_8AD[8][24];
	memset(AmCInOneDay_8AD,0.0,sizeof(AmCInOneDay_8AD));

	//
	Double_t TotalnLike_6AD[8]={0.0};
	Double_t TotalnLike_8AD[8]={0.0};
	Int_t nLike_t[8];

	Double_t nLikeInOneDay_6AD[8][24];
	memset(nLikeInOneDay_6AD,0.0,sizeof(nLikeInOneDay_6AD));

	Double_t nLikeInOneDay_8AD[8][24];
	memset(nLikeInOneDay_8AD,0.0,sizeof(nLikeInOneDay_8AD));

	TFile *F_nLike = new TFile("../nLike.root");
	TTree *Tree_nLike = (TTree*)F_nLike->Get("nLike");
	Tree_nLike->SetBranchAddress("nLike",nLike_t);
	//
	Double_t TotalFullTime_6AD[8]={0.0};
	Double_t TotalFullTime_8AD[8]={0.0};

	Double_t FullTime_t[8];

	Double_t FullTimeInOneDay[8][24];
	memset(FullTimeInOneDay,0.0,sizeof(FullTimeInOneDay));

	TFile *F_FullTime = new TFile("../FullTime.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
	Tree_FullTime->SetBranchAddress("FullTime",FullTime_t);

	double AmCInEachBin[8][NumOfBin] = {{0.0}};
	double RD_AmCInEachBin[8][NumOfBin] = {{0.0}};
	double nLikeInEachBin[8][NumOfBin] = {{0.0}};
	double FullTimeInEachBin[8][NumOfBin] = {{0.0}};

		
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N24 = Bin%24;
		Tree_nLike->GetEntry(Bin);
		Tree_FullTime->GetEntry(Bin);
		for(int Det=0;Det<8;Det++)
		{
			nLikeInEachBin[Det][Bin] = 1.0*nLike_t[Det];
			FullTimeInEachBin[Det][Bin] = 1.0*FullTime_t[Det];
		}
		if(Bin<=Bin_8AD)
		{
		for(int Det=0;Det<8;Det++)
		{
			nLikeInOneDay_6AD[Det][N24] += 1.0*nLike_t[Det];
			FullTimeInOneDay[Det][N24] += FullTime_t[Det];
			TotalFullTime_6AD[Det] += FullTime_t[Det];
			TotalnLike_6AD[Det] += 1.0*nLike_t[Det];
		}
		}
		else
		{
			for(int Det=0;Det<8;Det++)
		{
			nLikeInOneDay_8AD[Det][N24] += 1.0*nLike_t[Det];
			FullTimeInOneDay[Det][N24] += FullTime_t[Det];
			TotalFullTime_8AD[Det] += FullTime_t[Det];
			TotalnLike_8AD[Det] += 1.0*nLike_t[Det];
		}

		}
	}



	for(int Det=0;Det<8;Det++)
	{
		TotalAmC_6AD[Det] = AmCRate_6AD[Det]*TotalFullTime_6AD[Det]/86400.0;
		TotalAmC_8AD[Det] = AmCRate_8AD[Det]*TotalFullTime_8AD[Det]/86400.0;

		for(int Bin=0;Bin<=Bin_8AD;Bin++)
		{
			if(FullTimeInEachBin[Det][Bin]>10)
			{
			if(nLikeInEachBin[Det][Bin]>1.0)
			{
			AmCInEachBin[Det][Bin] = TotalAmC_6AD[Det] * nLikeInEachBin[Det][Bin]/TotalnLike_6AD[Det];
			RD_AmCInEachBin[Det][Bin] = sqrt(1.0/nLikeInEachBin[Det][Bin] - 1.0/TotalnLike_6AD[Det]);
			}
			if(RD_AmCInEachBin[Det][Bin]>1.0)
			{
				AmCInEachBin[Det][Bin] = 0.0;
				RD_AmCInEachBin[Det][Bin]=0.0;
			}
			}
		}

		for(int Bin=Bin_8AD+1;Bin<NumOfBin;Bin++)
		{
			if(FullTimeInEachBin[Det][Bin]>10)
			{
			AmCInEachBin[Det][Bin] = TotalAmC_8AD[Det] * nLikeInEachBin[Det][Bin]/TotalnLike_8AD[Det];
			if(nLikeInEachBin[Det][Bin]>1.0)
			{
			RD_AmCInEachBin[Det][Bin] = sqrt(1.0/nLikeInEachBin[Det][Bin] - 1.0/TotalnLike_8AD[Det]);
			}
			if(RD_AmCInEachBin[Det][Bin]>1.0)
			{
				AmCInEachBin[Det][Bin] = 0.0;
				RD_AmCInEachBin[Det][Bin]=0.0;
			}
			}
		}



		for(int N24=0;N24<24;N24++)
		{
			if(TotalnLike_6AD[Det]>1)
			{
			AmCInOneDay_6AD[Det][N24] = TotalAmC_6AD[Det] * nLikeInOneDay_6AD[Det][N24]/TotalnLike_6AD[Det];		
			RD_AmCInOneDay_6AD[Det][N24] = sqrt(1.0/nLikeInOneDay_6AD[Det][N24] - 1.0/TotalnLike_6AD[Det]);
			}
			else
			{
				AmCInOneDay_6AD[Det][N24]=0.0;
				RD_AmCInOneDay_6AD[Det][N24]=0.0;
			}
			AmCInOneDay_8AD[Det][N24] = TotalAmC_8AD[Det] * nLikeInOneDay_8AD[Det][N24]/TotalnLike_8AD[Det];
			RD_AmCInOneDay_8AD[Det][N24] = sqrt(1.0/nLikeInOneDay_8AD[Det][N24] - 1.0/TotalnLike_8AD[Det]);

			AmCInOneDay[Det][N24] = AmCInOneDay_6AD[Det][N24]+AmCInOneDay_8AD[Det][N24];
			cout<<AmCInOneDay[Det][N24]<<endl;

			RD_AmCInOneDay[Det][N24] = sqrt(pow(RD_AmCInOneDay_6AD[Det][N24]*AmCInOneDay_6AD[Det][N24],2.0)+pow(RD_AmCInOneDay_8AD[Det][N24]*AmCInOneDay_8AD[Det][N24],2.0))/(AmCInOneDay[Det][N24]);
		}
	}

	//////////Draw
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	const char *file_Name[8] = {
		"AmCRate_EH1_AD1.pdf","AmCRate_EH1_AD2.pdf","AmCRate_EH2_AD1.pdf","AmCRate_EH2_AD2.pdf",
		"AmCRate_EH3_AD1.pdf","AmCRate_EH3_AD2.pdf","AmCRate_EH3_AD3.pdf","AmCRate_EH3_AD4.pdf"};
	TCanvas *myC[8];
	TH1F *my_h[8];
	TLegend *leg[8];
	for(int Det=0;Det<8;Det++)
	{
		myC[Det] = new TCanvas(hist_Name[Det],hist_Name[Det],0,0,800,420);
		my_h[Det] = new TH1F(hist_Name[Det],hist_Name[Det],24,0,24);
	   Double_t MaxR=0.0,MeanR=0.0,MinR=86400.0*AmCInOneDay[Det][0]/FullTimeInOneDay[Det][0],MaxE=0.0;

	    for(int i=0;i<24;i++)
	    {
		   my_h[Det]->SetBinContent(i+1,86400.0*AmCInOneDay[Det][i]/FullTimeInOneDay[Det][i]);
		   my_h[Det]->SetBinError(i+1,RD_AmCInOneDay[Det][i]*86400.0*AmCInOneDay[Det][i]/FullTimeInOneDay[Det][i]);
		   MeanR += 86400.0*AmCInOneDay[Det][i]/FullTimeInOneDay[Det][i];
		   if(86400.0*AmCInOneDay[Det][i]/FullTimeInOneDay[Det][i]>MaxR){MaxR=86400.0*AmCInOneDay[Det][i]/FullTimeInOneDay[Det][i];}
		   if(86400.0*AmCInOneDay[Det][i]/FullTimeInOneDay[Det][i]<MinR){MinR=86400.0*AmCInOneDay[Det][i]/FullTimeInOneDay[Det][i];}
		   if(RD_AmCInOneDay[Det][i] > MaxE){MaxE = RD_AmCInOneDay[Det][i];}
	    }
		cout<<"Total AmC of "<<hist_Name[Det]<<TotalAmC_6AD[Det]+TotalAmC_8AD[Det]<<endl;
		cout<<"Time Variation: "<<24.0*(MaxR-MinR)/MeanR<<endl;
		cout<<"Maximum Error: "<<MaxE<<endl;

		my_h[Det]->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.09/24.00 seconds)");
	my_h[Det]->GetYaxis()->SetTitle("AmC Rate (/day)");
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
	TFile  *F_AmCInOneDay = new TFile("AmCInOneDay.root","recreate");
	TTree *Tree_AmCInOneDay = new TTree("AmCInOneDay","AmCInOneDay");
	Tree_AmCInOneDay->Branch("AmCInOneDay",AmC_t,"AmC_t[8]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			AmC_t[Det] = AmCInOneDay[Det][Bin];
		}
		Tree_AmCInOneDay->Fill();
	}
	Tree_AmCInOneDay->Write();

	TFile  *F_RD_AmCInOneDay = new TFile("RD_AmCInOneDay.root","recreate");
	TTree *Tree_RD_AmCInOneDay = new TTree("RD_AmCInOneDay","RD_AmCInOneDay");
	Tree_RD_AmCInOneDay->Branch("RD_AmCInOneDay",AmC_t,"AmC_t[8]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			AmC_t[Det] = RD_AmCInOneDay[Det][Bin];
		}
		Tree_RD_AmCInOneDay->Fill();
	}
	Tree_RD_AmCInOneDay->Write();
	
		//save Bin
	TFile  *F_AmCInEachBin = new TFile("AmCInEachBin.root","recreate");
	TTree *Tree_AmCInEachBin = new TTree("AmCInEachBin","AmCInEachBin");
	Tree_AmCInEachBin->Branch("AmCInEachBin",AmC_t,"AmC_t[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			AmC_t[Det] = AmCInEachBin[Det][Bin];
		}
		Tree_AmCInEachBin->Fill();
	}
	Tree_AmCInEachBin->Write();

	TFile  *F_RD_AmCInEachBin = new TFile("RD_AmCInEachBin.root","recreate");
	TTree *Tree_RD_AmCInEachBin = new TTree("RD_AmCInEachBin","RD_AmCInEachBin");
	Tree_RD_AmCInEachBin->Branch("RD_AmCInEachBin",AmC_t,"AmC_t[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			AmC_t[Det] = RD_AmCInEachBin[Det][Bin];
		}
		Tree_RD_AmCInEachBin->Fill();
	}
	Tree_RD_AmCInEachBin->Write();

		
}
