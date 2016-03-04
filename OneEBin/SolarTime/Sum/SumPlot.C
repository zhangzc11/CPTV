
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>


void SumPlot()
{
	Double_t WidthOfBin = 3600.0;
	const int NumOfHourInEachDay = 24;
	const int NumOfDay = 704;
	const int NumOfBin = 16896;	
	
	//IBD candidate in each day
	Double_t TotalIBD[8]={0.0};
	Int_t IBD_t[8];
	Double_t IBDInEachDay[8][NumOfDay];
	Double_t E2_IBDInEachDay[8][NumOfDay];
	memset(IBDInEachDay,0.0,sizeof(IBDInEachDay));
	memset(E2_IBDInEachDay,0.0,sizeof(E2_IBDInEachDay));
	TFile *F_IBD = new TFile("../IBD.root");
	TTree *Tree_IBD = (TTree*)F_IBD->Get("IBD");
	Tree_IBD->SetBranchAddress("IBD",IBD_t);
	
	//FullTime in each day
	Double_t TotalFullTime[8]={0.0};
	Double_t FullTime_t[8];
	Double_t FullTimeInEachDay[8][NumOfDay];
	memset(FullTimeInEachDay,0.0,sizeof(FullTimeInEachDay));
	TFile *F_FullTime = new TFile("../FullTime.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
	Tree_FullTime->SetBranchAddress("FullTime",FullTime_t);

	//LiveTime in each day
	Double_t TotalLiveTime[8]={0.0};
	Double_t LiveTime_t[8];
	Double_t LiveTimeInEachDay[8][NumOfDay];
	memset(LiveTimeInEachDay,0.0,sizeof(LiveTimeInEachDay));
	TFile *F_LiveTime = new TFile("../LiveTime.root");
	TTree *Tree_LiveTime = (TTree*)F_LiveTime->Get("LiveTime");
	Tree_LiveTime->SetBranchAddress("LiveTime",LiveTime_t);
	
	
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N704 = int(Bin/NumOfHourInEachDay);
		Tree_FullTime->GetEntry(Bin);
		Tree_LiveTime->GetEntry(Bin);
		Tree_IBD->GetEntry(Bin);
		
		if(N704<NumOfDay)
		{
		for(int Det=0;Det<8;Det++)
		{
			FullTimeInEachDay[Det][N704] += FullTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
			LiveTimeInEachDay[Det][N704] += LiveTime_t[Det];
			IBDInEachDay[Det][N704] += 1.0*IBD_t[Det];
		}
		}
	}
	
	//Multiplicity in each day
	Double_t MultiplicityEff_t[8];
	Double_t MultiplicityEffInEachDay[8][NumOfDay];
	memset(MultiplicityEffInEachDay,0.0,sizeof(MultiplicityEffInEachDay));
	TFile *F_MultiplicityEff = new TFile("../MultiEff/MultiplicityEff.root");
	TTree *Tree_MultiplicityEff = (TTree*)F_MultiplicityEff->Get("MultiplicityEff");
	Tree_MultiplicityEff->SetBranchAddress("MultiplicityEff",MultiplicityEff_t);
	
	//Acc rate in each day
	Double_t AccRate_t[8];
	Double_t AccRateInEachDay[8][NumOfDay];
	memset(AccRateInEachDay,0.0,sizeof(AccRateInEachDay));
	TFile *F_AccRate = new TFile("../AccBkg/AccRate.root");
	TTree *Tree_AccRate = (TTree*)F_AccRate->Get("AccRate");
	Tree_AccRate->SetBranchAddress("AccRate",AccRate_t);
	
	//AmC rate in each day
	Double_t AmCRate_t[8];
	Double_t AmCRateInEachDay[8][NumOfDay];
	memset(AmCRateInEachDay,0.0,sizeof(AmCRateInEachDay));
	TFile *F_AmCRate = new TFile("../AmC/AmCRate.root");
	TTree *Tree_AmCRate = (TTree*)F_AmCRate->Get("AmCRate");
	Tree_AmCRate->SetBranchAddress("AmCRate",AmCRate_t);
	
	//Muon rate in each day
	Double_t MuonRate_t[8];
	Double_t MuonRateInEachDay[8][NumOfDay];
	memset(MuonRateInEachDay,0.0,sizeof(MuonRateInEachDay));
	TFile *F_MuonRate = new TFile("../Muon/MuonRate.root");
	TTree *Tree_MuonRate = (TTree*)F_MuonRate->Get("MuonRate");
	Tree_MuonRate->SetBranchAddress("MuonRate",MuonRate_t);
	
	//Pred rate in each day
	Double_t TotalPredRate[8] = {0.0};
	Double_t PredRate_t[8];
	Double_t PredRateInEachDay[8][NumOfDay];
	memset(PredRateInEachDay,0.0,sizeof(PredRateInEachDay));
	TFile *F_PredRate = new TFile("../Flux/PredRate.root");
	TTree *Tree_PredRate = (TTree*)F_PredRate->Get("PredRate");
	Tree_PredRate->SetBranchAddress("PredRate",PredRate_t);
	
	//
	
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		Tree_PredRate->GetEntry(Bin);
		
		Tree_AccRate->GetEntry(Bin);
		Tree_AmCRate->GetEntry(Bin);
		Tree_MuonRate->GetEntry(Bin);
		Tree_MultiplicityEff->GetEntry(Bin);
		for(int Det=0;Det<8;Det++)
		{
			PredRateInEachDay[Det][Bin] = PredRate_t[Det];
			if((LiveTimeInEachDay[Det][Bin]>10))
			{
			TotalPredRate[Det] += PredRate_t[Det];
			}
			AccRateInEachDay[Det][Bin] = AccRate_t[Det];
			AmCRateInEachDay[Det][Bin] = AmCRate_t[Det];
			MuonRateInEachDay[Det][Bin] = MuonRate_t[Det];
			MultiplicityEffInEachDay[Det][Bin] = MultiplicityEff_t[Det];
		}
	}
	//Average Muon Rate
	Double_t AveMuonRate[8]={0.0};
	Double_t TotalMuonN[8]={0.0};
	for(int Det=0;Det<8;Det++)
	{
		for(int Bin=0;Bin<NumOfDay;Bin++)
		{
			TotalMuonN[Det] += MuonRateInEachDay[Det][Bin]*FullTimeInEachDay[Det][Bin];		
		}
		AveMuonRate[Det] = TotalMuonN[Det]/TotalFullTime[Det];
	}
	//E_Acc
	Double_t RD_AccRate[8] = {0.09/8.92,0.09/8.94,0.07/6.76,0.07/6.86,0.02/1.70,0.02/1.59,0.02/1.57,0.01/1.26}; 
	Double_t RD_AmCRate[8] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
	//Li9
	Double_t Li9RateInEachDay[8][NumOfDay] = {0.0};
	Double_t Li9Rate[8] = {2.8,2.8,1.7,1.7,0.27,0.27,0.27,0.27};
	Double_t RD_Li9Rate[8] = {1.5/2.8,1.5/2.8,0.9/1.7,0.9/1.7,0.14/0.27,0.14/0.27,0.14/0.27,0.14/0.27};
	//FastN
	Double_t FastNRateInEachDay[8][NumOfDay] = {0.0};
	Double_t FastNRate[8] = {0.78,0.78,0.54,0.54,0.05,0.05,0.05,0.05};
	Double_t RD_FastNRate[8] = {0.12/0.78,0.12/0.78,0.19/0.54,0.19/0.54,0.01/0.05,0.01/0.05,0.01/0.05,0.01/0.05};
	for(int Det=0;Det<8;Det++)
	{
		for(int Bin=0;Bin<NumOfDay;Bin++)
		{
			Li9RateInEachDay[Det][Bin] = Li9Rate[Det]*MuonRateInEachDay[Det][Bin]/AveMuonRate[Det];
			FastNRateInEachDay[Det][Bin] = FastNRate[Det]*MuonRateInEachDay[Det][Bin]/AveMuonRate[Det];
		}
	}
	
	//IBD rate, with bkg. and eff. correction
	double TotalIBDRate[8] = {0.0};
	
	double IBDRate[8][NumOfDay];
	double E_IBDRate[8][NumOfDay];
	memset(IBDRate,0.0,sizeof(IBDRate));
	memset(E_IBDRate,0.0,sizeof(E_IBDRate));
	for(int Det=0;Det<8;Det++)
	{
		
		for(int Bin=0;Bin<NumOfDay;Bin++)
		{
		if((LiveTimeInEachDay[Det][Bin]>10))
		{
			if((Det<4&&IBDInEachDay[Det][Bin]>100)||(Det>3&&IBDInEachDay[Det][Bin]>10))
			{
			IBDRate[Det][Bin] = 86400.0*IBDInEachDay[Det][Bin]/(LiveTimeInEachDay[Det][Bin]*MultiplicityEffInEachDay[Det][Bin])
			- AccRateInEachDay[Det][Bin]
			- AmCRateInEachDay[Det][Bin] 
			- Li9RateInEachDay[Det][Bin]
			- FastNRateInEachDay[Det][Bin];
			E_IBDRate[Det][Bin] = IBDRate[Det][Bin]/sqrt(IBDInEachDay[Det][Bin]);
			}
			TotalIBDRate[Det] += 86400.0*IBDInEachDay[Det][Bin]/(LiveTimeInEachDay[Det][Bin]*MultiplicityEffInEachDay[Det][Bin])
			- AccRateInEachDay[Det][Bin]
			- AmCRateInEachDay[Det][Bin] 
			- Li9RateInEachDay[Det][Bin]
			- FastNRateInEachDay[Det][Bin];
		}
		
		}
	}
	//total Bkg
	double BkgRate[8][NumOfDay];
	double E_BkgRate[8][NumOfDay];
	memset(BkgRate,0.0,sizeof(BkgRate));
	memset(E_BkgRate,0.0,sizeof(E_BkgRate));
	for(int Det=0;Det<8;Det++)
	{
		
		for(int Bin=0;Bin<NumOfDay;Bin++)
		{
		if((LiveTimeInEachDay[Det][Bin]>10))
		{
			//if((Det<4&&IBDInEachDay[Det][Bin]>100)||(Det>3&&IBDInEachDay[Det][Bin]>10))
			{
			BkgRate[Det][Bin] = AccRateInEachDay[Det][Bin]
			+ AmCRateInEachDay[Det][Bin] 
			+ Li9RateInEachDay[Det][Bin]
			+ FastNRateInEachDay[Det][Bin];
			E_BkgRate[Det][Bin] = sqrt(pow(AccRateInEachDay[Det][Bin]*RD_AccRate[Det],2.0)
			+ pow(AmCRateInEachDay[Det][Bin]*RD_AmCRate[Det],2.0)
			+ pow(Li9RateInEachDay[Det][Bin]*RD_Li9Rate[Det],2.0)
			+ pow(FastNRateInEachDay[Det][Bin]*RD_FastNRate[Det],2.0)
			);//BkgRate[Det][Bin]/sqrt(IBDInEachDay[Det][Bin]);
			}
		}
		}
	}
	//Normalize the IBD prediction
	double AVEP[8] = {0.985,0.985,0.983,0.983,0.951455,0.951455,0.951455,0.951455};
	
	double P_IBDRate[8][NumOfDay];
	double E_P_IBDRate[8][NumOfDay];
	memset(P_IBDRate,0.0,sizeof(P_IBDRate));
	memset(E_P_IBDRate,0.0,sizeof(E_P_IBDRate));
	for(int Det=0;Det<8;Det++)
	{
		for(int Bin=0;Bin<NumOfDay;Bin++)
		{
			P_IBDRate[Det][Bin] = PredRateInEachDay[Det][Bin]*TotalIBDRate[Det]/(TotalPredRate[Det]*AVEP[Det]);
		}
	}
	
	//
	/*
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		cout<<Bin<<"  ";
		for(int Det=0;Det<8;Det++)
		{
			cout<<P_IBDRate[Det][Bin]<<"  ";
		}
		cout<<endl;
	}
	*/
		
	gROOT->SetStyle("Plain");
    TStyle* style = new TStyle(*gStyle);
    style->SetName("myPlain");
    gROOT->GetListOfStyles()->Add(style);
	 style->SetTextFont(132);
    style->SetLegendFont(132);
    style->SetLabelFont(132,"xyz");
    style->SetTitleFont(132,"");
    style->SetTitleFont(132,"xyz");
	 style->SetLabelSize(10,"xy");
	 style->SetLegendFillColor( 10 );
	 style->SetCanvasColor(0);
	 style->cd();
    gROOT->ForceStyle();
	//////////Draw
	const char *hist_Name[3] = {"EH1_hist","EH2_hist","EH3_hist"}; 
	const char *c_Name[3] = {"EH1","EH2","EH3"};
	
	TGraphErrors *gr[3];
	TGraphErrors *Pre_gr[3];
	TGraphErrors *Bkg_gr[3];
	TGraphErrors *Ratio_gr[3];
	
	TMultiGraph *mg[3];// =  new TMultiGraph();
	for(int i=0;i<3;i++)
	{
		mg[i] = new TMultiGraph();
	}

	const Int_t n1 = 704;
	Double_t x1[n1],y1[n1],ex1[n1],ey1[n1];
	for(int i=0;i<n1;i++)
	{
		x1[i]=(i+0.5)*86400.0;
		y1[i]=(IBDRate[0][i]+IBDRate[1][i])/2.0;
		ex1[i]=0;
		ey1[i]=sqrt(pow(E_IBDRate[0][i],2.0)+pow(E_IBDRate[1][i],2.0))/2.0;
	}
	gr[0] = new TGraphErrors(n1,x1,y1,ex1,ey1);

	const Int_t n2 = 704;
	Double_t x2[n2],y2[n2],ex2[n2],ey2[n2];
	for(int i=0;i<n2;i++)
	{
		x2[i]=(i+0.5)*86400.0;
		ex2[i]=0;
		if(IBDRate[3][i]>0)
		{
		y2[i]=(IBDRate[2][i]+IBDRate[3][i])/2.0;
		ey2[i]=sqrt(pow(E_IBDRate[2][i],2.0)+pow(E_IBDRate[3][i],2.0))/2.0;
		}
		else
		{
			y2[i] = IBDRate[2][i];
			ey2[i] = E_IBDRate[2][i];
		}
	}
	gr[1] = new TGraphErrors(n2,x2,y2,ex2,ey2);

	const Int_t n3 = 704;
	Double_t x3[n3],y3[n3],ex3[n3],ey3[n3];
	for(int i=0;i<n3;i++)
	{
		x3[i]=(i+0.5)*86400.0;
		ex3[i]=0;
		if(IBDRate[7][i]>0)
		{
		y3[i]=(IBDRate[4][i]+IBDRate[5][i]+IBDRate[6][i]+IBDRate[7][i])/4.0;
		ey3[i]=sqrt(pow(E_IBDRate[4][i],2.0)+pow(E_IBDRate[5][i],2.0)+pow(E_IBDRate[6][i],2.0)+pow(E_IBDRate[7][i],2.0))/4.0;
		}
		else
		{
		y3[i]=(IBDRate[4][i]+IBDRate[5][i]+IBDRate[6][i])/3.0;
		ey3[i]=sqrt(pow(E_IBDRate[4][i],2.0)+pow(E_IBDRate[5][i],2.0)+pow(E_IBDRate[6][i],2.0))/3.0;
		}
	}
	gr[2] = new TGraphErrors(n3,x3,y3,ex3,ey3);
	////////////////////////Prediction///////////////////////////////////////////////////////

	const Int_t Pre_n1 = 704;
	Double_t Pre_x1[Pre_n1],Pre_y1[Pre_n1],ePre_x1[Pre_n1],ePre_y1[Pre_n1];
	for(int i=0;i<Pre_n1;i++)
	{
		Pre_x1[i]=(i+0.5)*86400.0;
		Pre_y1[i]=(P_IBDRate[0][i]+P_IBDRate[1][i])/2.0;
		ePre_x1[i]=0;
		ePre_y1[i]=0;//sqrt(pow(E_P_IBDRate[0][i],2.0)+pow(E_P_IBDRate[1][i],2.0))/2.0;
	}
	Pre_gr[0] = new TGraphErrors(Pre_n1,Pre_x1,Pre_y1,ePre_x1,ePre_y1);

	const Int_t Pre_n2 = 704;
	Double_t Pre_x2[Pre_n2],Pre_y2[Pre_n2],ePre_x2[Pre_n2],ePre_y2[Pre_n2];
	for(int i=0;i<Pre_n2;i++)
	{
		Pre_x2[i]=(i+0.5)*86400.0;
		ePre_x2[i]=0;
		if(IBDRate[3][i]>0)
		{
		Pre_y2[i]=(P_IBDRate[2][i]+P_IBDRate[3][i])/2.0;
		ePre_y2[i]=0;//sqrt(pow(E_P_IBDRate[2][i],2.0)+pow(E_P_IBDRate[3][i],2.0))/2.0;
		}
		else
		{
			Pre_y2[i] = P_IBDRate[2][i];
			ePre_y2[i] = 0;//E_P_IBDRate[2][i];
		}
	}
	Pre_gr[1] = new TGraphErrors(Pre_n2,Pre_x2,Pre_y2,ePre_x2,ePre_y2);

	const Int_t Pre_n3 = 704;
	Double_t Pre_x3[Pre_n3],Pre_y3[Pre_n3],ePre_x3[Pre_n3],ePre_y3[Pre_n3];
	for(int i=0;i<Pre_n3;i++)
	{
		Pre_x3[i]=(i+0.5)*86400.0;
		ePre_x3[i]=0;
			if(IBDRate[7][i]>0)
		{
		Pre_y3[i]=(P_IBDRate[4][i]+P_IBDRate[5][i]+P_IBDRate[6][i]+P_IBDRate[7][i])/4.0;
		ePre_y3[i]=0;//sqrt(pow(E_P_IBDRate[4][i],2.0)+pow(E_P_IBDRate[5][i],2.0)+pow(E_P_IBDRate[6][i],2.0)+pow(E_P_IBDRate[7][i],2.0))/4.0;
		}
		else
		{
		Pre_y3[i]=(P_IBDRate[4][i]+P_IBDRate[5][i]+P_IBDRate[6][i])/3.0;
		ePre_y3[i]=0;//sqrt(pow(E_P_IBDRate[4][i],2.0)+pow(E_P_IBDRate[5][i],2.0)+pow(E_P_IBDRate[6][i],2.0))/3.0;
		}
	}
	Pre_gr[2] = new TGraphErrors(Pre_n3,Pre_x3,Pre_y3,ePre_x3,ePre_y3);
	////////////////////////////////////background//////////////////////////////////////////////////////
	////////////////////////background///////////////////////////////////////////////////////

	const Int_t Bkg_n1 = 704;
	Double_t Bkg_x1[Bkg_n1],Bkg_y1[Bkg_n1],eBkg_x1[Bkg_n1],eBkg_y1[Bkg_n1];
	for(int i=0;i<Bkg_n1;i++)
	{
		Bkg_x1[i]=(i+0.5)*86400.0;
		Bkg_y1[i]=(BkgRate[0][i]+BkgRate[1][i])/2.0;
		eBkg_x1[i]=0;
		eBkg_y1[i]=sqrt(pow(E_BkgRate[0][i],2.0)+pow(E_BkgRate[1][i],2.0))/2.0;
	}
	Bkg_gr[0] = new TGraphErrors(Bkg_n1,Bkg_x1,Bkg_y1,eBkg_x1,eBkg_y1);

	const Int_t Bkg_n2 = 704;
	Double_t Bkg_x2[Bkg_n2],Bkg_y2[Bkg_n2],eBkg_x2[Bkg_n2],eBkg_y2[Bkg_n2];
	for(int i=0;i<Bkg_n2;i++)
	{
		Bkg_x2[i]=(i+0.5)*86400.0;
		eBkg_x2[i]=0;
		if(IBDRate[3][i]>0)
		{
		Bkg_y2[i]=(BkgRate[2][i]+BkgRate[3][i])/2.0;
		eBkg_y2[i]=sqrt(pow(E_BkgRate[2][i],2.0)+pow(E_BkgRate[3][i],2.0))/2.0;
		}
		else
		{
			Bkg_y2[i] = BkgRate[2][i];
			eBkg_y2[i] = E_BkgRate[2][i];
		}
	}
	Bkg_gr[1] = new TGraphErrors(Bkg_n2,Bkg_x2,Bkg_y2,eBkg_x2,eBkg_y2);

	const Int_t Bkg_n3 = 704;
	Double_t Bkg_x3[Bkg_n3],Bkg_y3[Bkg_n3],eBkg_x3[Bkg_n3],eBkg_y3[Bkg_n3];
	for(int i=0;i<Bkg_n3;i++)
	{
		Bkg_x3[i]=(i+0.5)*86400.0;
		eBkg_x3[i]=0;
			if(IBDRate[7][i]>0)
		{
		Bkg_y3[i]=(BkgRate[4][i]+BkgRate[5][i]+BkgRate[6][i]+BkgRate[7][i])/4.0;
		eBkg_y3[i]=sqrt(pow(E_BkgRate[4][i],2.0)+pow(E_BkgRate[5][i],2.0)+pow(E_BkgRate[6][i],2.0)+pow(E_BkgRate[7][i],2.0))/4.0;
		}
		else
		{
		Bkg_y3[i]=(BkgRate[4][i]+BkgRate[5][i]+BkgRate[6][i])/3.0;
		eBkg_y3[i]=sqrt(pow(E_BkgRate[4][i],2.0)+pow(E_BkgRate[5][i],2.0)+pow(E_BkgRate[6][i],2.0))/3.0;
		}
	}
	Bkg_gr[2] = new TGraphErrors(Bkg_n3,Bkg_x3,Bkg_y3,eBkg_x3,eBkg_y3);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//measurement/prediction ratio
	Double_t Ratio[3][NumOfDay] = {0.0};
	Double_t E_Ratio[3][NumOfDay] = {0.0};
	
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		//EH1
		if(Pre_y1[Bin]>1.0)
		{
		Ratio[0][Bin] = y1[Bin]/Pre_y1[Bin] - AVEP[0];
		E_Ratio[0][Bin] = ey1[Bin]/Pre_y1[Bin];
		}
		else
		{
			Ratio[0][Bin] = -10.0;
		}
		//EH2
		if(Pre_y2[Bin]>1.0)
		{
		Ratio[1][Bin] = y2[Bin]/Pre_y2[Bin] - AVEP[2];
		E_Ratio[1][Bin] = ey2[Bin]/Pre_y2[Bin];
		}
		else
		{
			Ratio[1][Bin] = -10.0;
		}
		//EH3
		if(Pre_y3[Bin]>1.0)
		{
		Ratio[2][Bin] = y3[Bin]/Pre_y3[Bin] - AVEP[4];
		E_Ratio[2][Bin] = ey3[Bin]/Pre_y3[Bin];
		}
		else
		{
			Ratio[2][Bin] = -10.0;
		}	
		//cout<<Bin<<"   "<<E_Ratio[0][Bin]<<"   "<<E_Ratio[1][Bin]<<"   "<<E_Ratio[2][Bin]<<endl;
	}
	
	////////////////////////ratio///////////////////////////////////////////////////////

	const Int_t Ratio_n1 = 704;
	Double_t Ratio_x1[Ratio_n1],Ratio_y1[Ratio_n1],eRatio_x1[Ratio_n1],eRatio_y1[Ratio_n1];
	for(int i=0;i<Ratio_n1;i++)
	{
		Ratio_x1[i]=(i+0.5)*86400.0;
		Ratio_y1[i]=Ratio[0][i];
		eRatio_x1[i]=0;
		eRatio_y1[i]=E_Ratio[0][i];
	}
	Ratio_gr[0] = new TGraphErrors(Ratio_n1,Ratio_x1,Ratio_y1,eRatio_x1,eRatio_y1);

	const Int_t Ratio_n2 = 704;
	Double_t Ratio_x2[Ratio_n2],Ratio_y2[Ratio_n2],eRatio_x2[Ratio_n2],eRatio_y2[Ratio_n2];
	for(int i=0;i<Ratio_n2;i++)
	{
		Ratio_x2[i]=(i+0.5)*86400.0;
		eRatio_x2[i]=0;
		Ratio_y2[i]=Ratio[1][i];
		eRatio_y2[i]=E_Ratio[1][i];
		
	}
	Ratio_gr[1] = new TGraphErrors(Ratio_n2,Ratio_x2,Ratio_y2,eRatio_x2,eRatio_y2);

	const Int_t Ratio_n3 = 704;
	Double_t Ratio_x3[Ratio_n3],Ratio_y3[Ratio_n3],eRatio_x3[Ratio_n3],eRatio_y3[Ratio_n3];
	for(int i=0;i<Ratio_n3;i++)
	{
		Ratio_x3[i]=(i+0.5)*86400.0;
		eRatio_x3[i]=0;
		
		Ratio_y3[i]=Ratio[2][i];
		eRatio_y3[i]=E_Ratio[2][i];
		
	}
	Ratio_gr[2] = new TGraphErrors(Ratio_n3,Ratio_x3,Ratio_y3,eRatio_x3,eRatio_y3);
	////////////////////////////////////////////////////////////////////////////////////////////////////

    TCanvas *myC[3];//= new TCanvas("IBD1","IBD1",200,10,900,200);
	
	const char *canv_Name[3] = {"EH1","EH2","EH3"};
	
	const char *file_Name[3] = {"SumPlot_EH1.eps","SumPlot_EH2.eps","SumPlot_EH3.eps"};
	
	for(int i=0;i<3;i++)
	{
	myC[i] = new TCanvas(canv_Name[i],canv_Name[i],200,10,800,600);
	myC[i]->Divide(1,2,0);
	
	myC[i]->cd(2);
	
	Ratio_gr[i]->SetMarkerStyle(8);
	Ratio_gr[i]->SetMarkerColor(1);
	Ratio_gr[i]->SetLineColor(1);
	Ratio_gr[i]->SetLineWidth(2);
	Ratio_gr[i]->SetMarkerSize(0.8);
	
	Ratio_gr[i]->Draw("APZ");
	
	Ratio_gr[i]->SetTitle("");
	Ratio_gr[i]->GetXaxis()->SetTitle("");
    Ratio_gr[i]->GetYaxis()->SetTitle("R(t) - R_{0}");
	//Ratio_gr[i]->GetYaxis()->SetTitle("IBD candidate number");
	Ratio_gr[i]->GetYaxis()->SetTitleSize(0.12);
	Ratio_gr[i]->GetYaxis()->SetLabelSize(0.09);
	Ratio_gr[i]->GetYaxis()->CenterTitle();
	
	Ratio_gr[i]->GetYaxis()->SetNdivisions(505);
	Ratio_gr[i]->GetXaxis()->SetNdivisions(505);
	Ratio_gr[i]->GetYaxis()->SetTitleOffset(0.37);
	Ratio_gr[i]->GetXaxis()->SetTitleSize(0.055);
	Ratio_gr[i]->GetXaxis()->SetLabelSize(0.10);
	Ratio_gr[i]->GetXaxis()->SetTitleOffset(0.8);
	Ratio_gr[i]->GetXaxis()->SetRangeUser(0,705.0*86400.0);
	Ratio_gr[i]->GetXaxis()->SetTimeDisplay(1);
	Ratio_gr[i]->GetXaxis()->SetTimeFormat("%b\/20%y%F2011-12-24 00:00:00");
	
	Ratio_gr[i]->GetYaxis()->SetRangeUser(-0.3,0.3);
	
	
	myC[i]->cd(1);
	//myC[i]->SetLogy();	
	gr[i]->SetMarkerStyle(8);
	gr[i]->SetMarkerColor(4);
	gr[i]->SetLineColor(4);
	gr[i]->SetLineWidth(2);
	gr[i]->SetMarkerSize(0.8);

	gr[i]->Draw("APZ");
	gr[i]->SetTitle("");
	gr[i]->GetXaxis()->SetTitle("");
	
    gr[i]->GetYaxis()->SetTitle("Event Rate (/AD/day)");

	//gr[i]->GetYaxis()->SetTitle("IBD candidate number");
	gr[i]->GetYaxis()->SetTitleSize(0.12);
	gr[i]->GetYaxis()->SetLabelSize(0.10);
	gr[i]->GetYaxis()->CenterTitle();
	
	gr[i]->GetYaxis()->SetNdivisions(510);
	gr[i]->GetYaxis()->SetTitleOffset(0.40);
	gr[i]->GetXaxis()->SetTitleSize(0.055);
	gr[i]->GetXaxis()->SetLabelSize(0.10);
	gr[i]->GetXaxis()->SetTitleOffset(0.8);
	gr[i]->GetXaxis()->SetRangeUser(0,705.0*86400.0);
	gr[i]->GetXaxis()->SetTimeDisplay(1);
	gr[i]->GetXaxis()->SetTimeFormat("%b\/20%y%F2011-12-24 00:00:00");
	
	if(i==0)
	{
		gr[0]->GetYaxis()->SetRangeUser(0,875);//(375,875);
	}
	if(i==1)
	{
		gr[1]->GetYaxis()->SetRangeUser(0,825);//(275,825);
	}
	if(i==2)
	{
		gr[2]->GetYaxis()->SetRangeUser(0,110);//(30,110);
	}
	
	Bkg_gr[i]->SetMarkerStyle(8);
	Bkg_gr[i]->SetMarkerColor(3);
	Bkg_gr[i]->SetLineColor(3);
	Bkg_gr[i]->SetLineWidth(2);
	Bkg_gr[i]->SetMarkerSize(0.8);
	
	Bkg_gr[i]->Draw("PZsame");
	Pre_gr[i]->Draw("same");
	Pre_gr[i]->SetLineWidth(2);
	Pre_gr[i]->SetLineColor(2);
	
	//if(i==2)
	{
	TLegend* leg = new TLegend(0.36, 0.65, 0.5, 0.95);
	leg->AddEntry(gr[i],canv_Name[i],"");
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();
	
	
	TLegend* leg2 = new TLegend(0.5, 0.04, 0.99, 0.38);
	leg2->AddEntry(gr[i],"measured IBD rate","ep");
	leg2->AddEntry(Pre_gr[i],"predicted IBD rate (sin^{2}2#theta_{13} = 0)","l");
	leg2->AddEntry(Bkg_gr[i],"total backgrounds rate","ep");
	leg2->AddEntry(Ratio_gr[i],"IBD measurement/prediction","ep");
	
	//leg2->SetFillStyle(0);
	leg2->SetBorderSize(1);
	leg2->Draw();
	}
	myC[i]->SaveAs(file_Name[i]);
	}
	
	/*
	TCanvas *myC_One = new TCanvas("myC_One","myC_One",200,10,800,600);
	myC_One->SetBorderSize(0);
	myC_One->SetFillColor(0);

	myC_One->Divide(3,2,0.001,0.001);

	for(int i=0;i<3;i++)
	{
		
		myC_One->cd(i+1);
	//myC[i] = new TCanvas(c_Name[i],c_Name[i],200,10,900,400);
	
	gr[i]->SetMarkerStyle(8);
	gr[i]->SetMarkerColor(4);
	gr[i]->SetLineColor(4);
	gr[i]->SetLineWidth(2);
	gr[i]->SetMarkerSize(0.8);

	gr[i]->Draw("APZ");
	gr[i]->SetTitle("");
	gr[i]->GetXaxis()->SetTitle("");
	
	if(i==1)
	{
    gr[i]->GetYaxis()->SetTitle("IBD Rate (/AD/day)");
	}
	else
	{
		gr[i]->GetYaxis()->SetTitle("");
	}
	//gr[i]->GetYaxis()->SetTitle("IBD candidate number");
	gr[i]->GetYaxis()->SetTitleSize(0.132);
	if(i==2)
	{
	gr[i]->GetYaxis()->SetLabelSize(0.11);
	}
	else
	{
		gr[i]->GetYaxis()->SetLabelSize(0.11);
	}
	
	gr[i]->GetYaxis()->SetNdivisions(505);
	gr[i]->GetYaxis()->SetTitleOffset(0.34);
	gr[i]->GetXaxis()->SetTitleSize(0.055);
	gr[i]->GetXaxis()->SetLabelSize(0.08);
	gr[i]->GetXaxis()->SetTitleOffset(0.8);
	gr[i]->GetXaxis()->SetRangeUser(0,710.0*86400.0);
	gr[i]->GetXaxis()->SetTimeDisplay(1);
	gr[i]->GetXaxis()->SetTimeFormat("%b\/20%y%F2011-12-24 00:00:00");
	
	if(i==0)
	{
		gr[0]->GetYaxis()->SetRangeUser(375,875);
	}
	if(i==1)
	{
		gr[1]->GetYaxis()->SetRangeUser(275,825);
	}
	if(i==2)
	{
		gr[2]->GetYaxis()->SetRangeUser(30,110);
	}
	
	
	Pre_gr[i]->Draw("same");
	Pre_gr[i]->SetLineWidth(2);
	Pre_gr[i]->SetLineColor(2);
//	Pre_gr[i]->SetLineStyle(7);

	TLegend* leg = new TLegend(0.36, 0.65, 0.5, 0.95);
	leg->AddEntry(gr[i],c_Name[i],"");

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();

	if(i==0)
	{
	TLegend* leg2 = new TLegend(0.32, 0.05, 0.69, 0.45);
	leg2->AddEntry(gr[0],"measured","ep");
	leg2->AddEntry(Pre_gr[0],"predicted (sin^{2}2#theta_{13} = 0)","l");
	//leg2->AddEntry(Pre_Osci_gr[0],"predicted (sin^{2}2#theta_{13} = 0.071)","l");

	//leg2->SetFillStyle(0);
	leg2->SetBorderSize(1);
	//leg2->Draw();
	}
	gPad->Modified();

	
	

	//myC[i]->SaveAs(file_Name[i]);
	//myC[i]->SaveAs(file_Name_2[i]);
	}
	myC_One->SaveAs("SumPlot.eps");
//	myC_One->SaveAs("SumPlot.png");
//	myC_One->SaveAs("SumPlot.eps");
	
	*/
	
	
}