
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void IBD_Rate()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;//17016

	Double_t TotalIBD[8]={0.0};

	//IBD candidate
	Double_t IBDInOneDay[8][24];

	Double_t IBD_t[8];
	memset(IBDInOneDay,0.0,sizeof(IBDInOneDay));
	TFile *F_IBD = new TFile("IBDInOneDay.root");
	TTree *Tree_IBD = (TTree*)F_IBD->Get("IBDInOneDay");
	Tree_IBD->SetBranchAddress("IBDInOneDay",IBD_t);

	//AmC
    Double_t AmCInOneDay[8][24];
	Double_t AmC_t[8];
	memset(AmCInOneDay,0.0,sizeof(AmCInOneDay));
	TFile *F_AmC = new TFile("../AmC/AmCInOneDay.root");
	TTree *Tree_AmC = (TTree*)F_AmC->Get("AmCInOneDay");
	Tree_AmC->SetBranchAddress("AmCInOneDay",AmC_t);
	
	//RD_AmC
	Double_t RD_AmCInOneDay[8][24];
	Double_t RD_AmC_t[8];
	memset(RD_AmCInOneDay,0.0,sizeof(RD_AmCInOneDay));
	TFile *F_RD_AmC = new TFile("../AmC/RD_AmCInOneDay.root");
	TTree *Tree_RD_AmC = (TTree*)F_RD_AmC->Get("RD_AmCInOneDay");
	Tree_RD_AmC->SetBranchAddress("RD_AmCInOneDay",RD_AmC_t);

	//Acc
	Double_t AccInOneDay[8][24];
	Double_t Acc_t[8];
	memset(AccInOneDay,0.0,sizeof(AccInOneDay));
	TFile *F_Acc = new TFile("../AccBkg/AccInOneDay.root");
	TTree *Tree_Acc = (TTree*)F_Acc->Get("AccInOneDay");
	Tree_Acc->SetBranchAddress("AccInOneDay",Acc_t);

	//RD_Acc
	Double_t RD_AccInOneDay[8][24];
	Double_t RD_Acc_t[8];
	memset(RD_AccInOneDay,0.0,sizeof(RD_AccInOneDay));
	TFile *F_RD_Acc = new TFile("../AccBkg/RD_AccInOneDay.root");
	TTree *Tree_RD_Acc = (TTree*)F_RD_Acc->Get("RD_AccInOneDay");
	Tree_RD_Acc->SetBranchAddress("RD_AccInOneDay",RD_Acc_t);

	//Li9
	Double_t Li9InOneDay[8][24];
	Double_t Li9_t[8];
	memset(Li9InOneDay,0.0,sizeof(Li9InOneDay));
	TFile *F_Li9 = new TFile("../Li9/Li9InOneDay.root");
	TTree *Tree_Li9 = (TTree*)F_Li9->Get("Li9InOneDay");
	Tree_Li9->SetBranchAddress("Li9InOneDay",Li9_t);

	//RD_Li9
	Double_t RD_Li9InOneDay[8][24];
	Double_t RD_Li9_t[8];
	memset(RD_Li9InOneDay,0.0,sizeof(RD_Li9InOneDay));
	TFile *F_RD_Li9 = new TFile("../Li9/RD_Li9InOneDay.root");
	TTree *Tree_RD_Li9 = (TTree*)F_RD_Li9->Get("RD_Li9InOneDay");
	Tree_RD_Li9->SetBranchAddress("RD_Li9InOneDay",RD_Li9_t);

	//FastN
	Double_t FastNInOneDay[8][24];
	Double_t FastN_t[8];
	memset(FastNInOneDay,0.0,sizeof(FastNInOneDay));
	TFile *F_FastN = new TFile("../FastN/FastNInOneDay.root");
	TTree *Tree_FastN = (TTree*)F_FastN->Get("FastNInOneDay");
	Tree_FastN->SetBranchAddress("FastNInOneDay",FastN_t);

	//RD_FastN
	Double_t RD_FastNInOneDay[8][24];
	Double_t RD_FastN_t[8];
	memset(RD_FastNInOneDay,0.0,sizeof(RD_FastNInOneDay));
	TFile *F_RD_FastN = new TFile("../FastN/RD_FastNInOneDay.root");
	TTree *Tree_RD_FastN = (TTree*)F_RD_FastN->Get("RD_FastNInOneDay");
	Tree_RD_FastN->SetBranchAddress("RD_FastNInOneDay",RD_FastN_t);

	//MultiEff
	Double_t MultiEffInOneDay[8][24];
	Double_t MultiEff_t[8];
	memset(MultiEffInOneDay,0.0,sizeof(MultiEffInOneDay));
	TFile *F_MultiEff = new TFile("../MultiEff/MultiEffInOneDay.root");
	TTree *Tree_MultiEff = (TTree*)F_MultiEff->Get("MultiEffInOneDay");
	Tree_MultiEff->SetBranchAddress("MultiEffInOneDay",MultiEff_t);

	//MuEff
	Double_t MuEffInOneDay[8][24];
	Double_t MuEff_t[8];
	memset(MuEffInOneDay,0.0,sizeof(MuEffInOneDay));
	TFile *F_MuEff = new TFile("../MuEff/MuEffInOneDay.root");
	TTree *Tree_MuEff = (TTree*)F_MuEff->Get("MuEffInOneDay");
	Tree_MuEff->SetBranchAddress("MuEffInOneDay",MuEff_t);

	//Fraction
	Double_t FractionInOneDay[3][6][24];
	Double_t Fraction_t[3][6];
	memset(FractionInOneDay,0.0,sizeof(FractionInOneDay));
	TFile *F_Fraction = new TFile("../Fraction.root");
	TTree *Tree_Fraction = (TTree*)F_Fraction->Get("Fraction");
	Tree_Fraction->SetBranchAddress("Fraction",Fraction_t);

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
		}
	}

	for(int N24=0;N24<24;N24++)
	{
		Tree_IBD->GetEntry(N24);
		Tree_AmC->GetEntry(N24);
		Tree_RD_AmC->GetEntry(N24);
		Tree_Acc->GetEntry(N24);
		Tree_RD_Acc->GetEntry(N24);
		Tree_Li9->GetEntry(N24);
		Tree_RD_Li9->GetEntry(N24);
		Tree_FastN->GetEntry(N24);
		Tree_RD_FastN->GetEntry(N24);
		Tree_MultiEff->GetEntry(N24);
		Tree_MuEff->GetEntry(N24);
		Tree_Fraction->GetEntry(N24);

		for(int Det=0;Det<8;Det++)
		{
			IBDInOneDay[Det][N24] = IBD_t[Det];
			AmCInOneDay[Det][N24] = AmC_t[Det];
			RD_AmCInOneDay[Det][N24] = RD_AmC_t[Det];
			AccInOneDay[Det][N24] = Acc_t[Det];
			RD_AccInOneDay[Det][N24] = RD_Acc_t[Det];
			Li9InOneDay[Det][N24] = Li9_t[Det];
			RD_Li9InOneDay[Det][N24] = RD_Li9_t[Det];
			FastNInOneDay[Det][N24] = FastN_t[Det];
			RD_FastNInOneDay[Det][N24] = RD_FastN_t[Det];
			MultiEffInOneDay[Det][N24] = MultiEff_t[Det];
			MuEffInOneDay[Det][N24] = MuEff_t[Det];
		}
		for(int Hall=0;Hall<3;Hall++)
		{
			for(int Rct=0;Rct<6;Rct++)
			{
				FractionInOneDay[Hall][Rct][N24] = Fraction_t[Hall][Rct];
			}
		}
	}
	
	Double_t M[8][24];//={0.0};
	memset(M,0.0,sizeof(M));
	Double_t RD_M[8][24];//={0.0};
	memset(RD_M,0.0,sizeof(RD_M));
	double RD_Power = 0.009;
	double RD_Eff = 0.0013;

	for(int Det=0;Det<8;Det++)
	{
		for(int N24=0;N24<24;N24++)
		{
			M[Det][N24] = IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
			RD_M[Det][N24] = (IBDInOneDay[Det][N24]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccInOneDay[Det][N24],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9InOneDay[Det][N24],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNInOneDay[Det][N24],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);
			RD_M[Det][N24] += pow(M[Det][N24]*RD_Eff,2.0);
		    RD_M[Det][N24] = sqrt(RD_M[Det][N24])/M[Det][N24];
		}
		
	}


	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	const char *file_Name[8] = {
		"IBDRateInOneDay_EH1_AD1.pdf","IBDRateInOneDay_EH1_AD2.pdf","IBDRateInOneDay_EH2_AD1.pdf","IBDRateInOneDay_EH2_AD2.pdf",
		"IBDRateInOneDay_EH3_AD1.pdf","IBDRateInOneDay_EH3_AD2.pdf","IBDRateInOneDay_EH3_AD3.pdf","IBDRateInOneDay_EH3_AD4.pdf"};
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
		   my_h[Det]->SetBinContent(i+1,86400.0*M[Det][i]/FullTimeInOneDay[Det][i]);
		   my_h[Det]->SetBinError(i+1,RD_M[Det][i]*86400.0*M[Det][i]/FullTimeInOneDay[Det][i]);
		   MeanR += 86400.0*M[Det][i]/FullTimeInOneDay[Det][i];
		   if(86400.0*M[Det][i]/FullTimeInOneDay[Det][i]>MaxR){MaxR=86400.0*M[Det][i]/FullTimeInOneDay[Det][i];}
		   if(86400.0*M[Det][i]/FullTimeInOneDay[Det][i]<MinR){MinR=86400.0*M[Det][i]/FullTimeInOneDay[Det][i];}
		   if(RD_M[Det][i]*86400.0*M[Det][i]/FullTimeInOneDay[Det][i]> MaxE){MaxE = RD_M[Det][i]*86400.0*M[Det][i]/FullTimeInOneDay[Det][i];}
	    }
		//cout<<"Total IBD of "<<hist_Name[Det]<<TotalIBD[Det]<<endl;
		cout<<"Time Variation: "<<24.0*(MaxR-MinR)/MeanR<<endl;
		cout<<"Maximum Error: "<<MaxE<<endl;

		my_h[Det]->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.09/24.00 seconds)");
	my_h[Det]->GetYaxis()->SetTitle("IBD Rate (/day)");
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

	




}