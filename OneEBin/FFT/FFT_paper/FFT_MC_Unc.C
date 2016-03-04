#include "TRandom.h"
#include <math.h>

const int nSample = 100;
const int NumOfBin = 16944;
double R[3][NumOfBin] = {{0.0}};
double R_data[3][NumOfBin] = {{0.0}};
double AVEP[3] = {0.985,0.983,0.951455};
void Normalization();
void Exclusion_3s();

TRandom *my_Random = new TRandom(754);

double Alpha_6AD = 0.0444;//CPC paper;
double Alpha_8AD = 0.0554;//from the histogram of daily alphabeta data
double Beta_6AD = 0.2991;//CPC
double Beta_8AD = 0.1971;//from the histogram of daily alphabeta data

int EndBin_6AD = 6000;

int NumOfGoodBin[8]={0};
bool IsGoodBin[8][NumOfBin];


////////SYS
double RD_Acc[8] ={0.0};// {0.008/4.9,0.008/4.9,0.01/4.9,0.01/4.9,0.02/4.9,0.02/4.9,0.02/4.9,0.02/4.9};
double RD_FN[8] ={0.0};// {0.0002/4.9,0.0002/4.9,0.0002/4.9,0.0002/4.9,0.001/4.9,0.001/4.9,0.001/4.9,0.001/4.9};
double RD_Li9[8] ={0.0};// {0.0002/4.9,0.0002/4.9,0.0002/4.9,0.0002/4.9,0.001/4.9};
double RD_AmC[8] ={0.0};// {0.02,0.02,0.02,0.02,0.02,0.02,0.02,0.02};

double TotalAcc[8] = {0.0};
double TotalFN[8] = {0.0};
double TotalLi9[8] = {0.0};
double TotalAmC[8] = {0.0};

double RD_Power = 0.009;
double RD_Eff = 0.00088;
////////SYS

void FFT_MC_Unc()
{

	for(int Det=0;Det<8;Det++)

	{

	RD_Acc[Det] = 0.25;
	RD_FN[Det] = 0.01;
	RD_Li9[Det] = 0.01;
	RD_AmC[Det] = 0.44;
	}



	//cout<<"hello......"<<endl;

	const double pi = 3.141592653;
	Double_t CrossSection = 0.94;//Averaged cross-section, in unit of 1e-43 cm^2;
    Double_t Np = 1.43;//Total number of target protons in AD1,AD2, in unit of 1e30
	
	for(int Det=0;Det<8;Det++)
	{
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		IsGoodBin[Det][Bin] = false;
	}
	}

	//Prediction candidate
	double Prediction_t_Bin[8];
	double TotalPrediction[8]={0.0};
	TFile *F_Bin_Prediction = new TFile("../daily_data/Fraction_AD_Bin.root");
	TTree *Tree_Bin_Prediction = (TTree*)F_Bin_Prediction->Get("Fraction");
	Tree_Bin_Prediction->SetBranchAddress("Fraction",Prediction_t_Bin);

	//IBD candidate
	Int_t IBD_t_Bin[8];
	double TotalIBD[8]={0.0};
	TFile *F_Bin_IBD = new TFile("../IBD_NoEBin.root");
	TTree *Tree_Bin_IBD = (TTree*)F_Bin_IBD->Get("IBD");
	Tree_Bin_IBD->SetBranchAddress("IBD",IBD_t_Bin);

	//FullTime
	Double_t FullTime_t_Bin[8];
	TFile *F_Bin_FullTime = new TFile("../FullTime.root");
	TTree *Tree_Bin_FullTime = (TTree*)F_Bin_FullTime->Get("FullTime");
	Tree_Bin_FullTime->SetBranchAddress("FullTime",FullTime_t_Bin);

	//LiveTime
	Double_t LiveTime_t_Bin[8];
	double TotalLiveTime[8]={0.0};
	TFile *F_Bin_LiveTime = new TFile("../LiveTime.root");
	TTree *Tree_Bin_LiveTime = (TTree*)F_Bin_LiveTime->Get("LiveTime");
	Tree_Bin_LiveTime->SetBranchAddress("LiveTime",LiveTime_t_Bin);


	double BkgInEachBin[8][NumOfBin]={{0.0}};

	//AmC
	Double_t AmC_t_Bin[8];
	TFile *F_Bin_AmC = new TFile("../AmC/AmCInEachBin.root");
	TTree *Tree_Bin_AmC = (TTree*)F_Bin_AmC->Get("AmCInEachBin");
	Tree_Bin_AmC->SetBranchAddress("AmCInEachBin",AmC_t_Bin);
	
	//Acc
	Double_t Acc_t_Bin[8];
	TFile *F_Bin_Acc = new TFile("../AccBkg/AccInEachBin.root");
	TTree *Tree_Bin_Acc = (TTree*)F_Bin_Acc->Get("AccInEachBin");
	Tree_Bin_Acc->SetBranchAddress("AccInEachBin",Acc_t_Bin);
	
	Double_t Li9_t_Bin[8];
	TFile *F_Bin_Li9 = new TFile("../Li9/Li9InEachBin.root");
	TTree *Tree_Bin_Li9 = (TTree*)F_Bin_Li9->Get("Li9InEachBin");
	Tree_Bin_Li9->SetBranchAddress("Li9InEachBin",Li9_t_Bin);

	//FastN
	Double_t FastN_t_Bin[8];
	TFile *F_Bin_FastN = new TFile("../FastN/FastNInEachBin.root");
	TTree *Tree_Bin_FastN = (TTree*)F_Bin_FastN->Get("FastNInEachBin");
	Tree_Bin_FastN->SetBranchAddress("FastNInEachBin",FastN_t_Bin);


	double EffInEachBin[8][NumOfBin]={{0.0}};
	//MultiEff
	Double_t MultiEff_t_Bin[8];
	TFile *F_Bin_MultiEff = new TFile("../MultiEff/MultiEffInEachBin.root");
	TTree *Tree_Bin_MultiEff = (TTree*)F_Bin_MultiEff->Get("MultiEffInEachBin");
	Tree_Bin_MultiEff->SetBranchAddress("MultiEffInEachBin",MultiEff_t_Bin);

	//MuEff
	Double_t MuEff_t_Bin[8];
	TFile *F_Bin_MuEff = new TFile("../MuEff/MuEffInEachBin.root");
	TTree *Tree_Bin_MuEff = (TTree*)F_Bin_MuEff->Get("MuEffInEachBin");
	Tree_Bin_MuEff->SetBranchAddress("MuEffInEachBin",MuEff_t_Bin);

	//alpha beta
	double AlphaBeta_t[2];
	TFile *F_Bin_AlphaBeta = new TFile("../daily_data/AlphaBeta_Bin.root");
	TTree *Tree_Bin_AlphaBeta = (TTree*)F_Bin_AlphaBeta->Get("AlphaBeta");
	Tree_Bin_AlphaBeta->SetBranchAddress("AlphaBeta",AlphaBeta_t);

	FILE* m_outfile = fopen("log_MC_Unc.txt", "w+");

	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		Tree_Bin_IBD->GetEntry(Bin);
		Tree_Bin_AlphaBeta->GetEntry(Bin);
		Tree_Bin_Prediction->GetEntry(Bin);
		Tree_Bin_FullTime->GetEntry(Bin);
		Tree_Bin_LiveTime->GetEntry(Bin);
		Tree_Bin_AmC->GetEntry(Bin);
		Tree_Bin_Acc->GetEntry(Bin);
		Tree_Bin_Li9->GetEntry(Bin);
		Tree_Bin_FastN->GetEntry(Bin);
		Tree_Bin_MultiEff->GetEntry(Bin);
		Tree_Bin_MuEff->GetEntry(Bin);
		

		for(int Det=0;Det<8;Det++)
		{
			TotalLiveTime[Det] += LiveTime_t_Bin[Det];
			TotalIBD[Det] += 1.0*IBD_t_Bin[Det];
			TotalPrediction[Det] += 1.0*Prediction_t_Bin[Det]*1.0e-17*Np*CrossSection/(4.0*pi);
////////SYS
			TotalAcc[Det] += Acc_t_Bin[Det];
			TotalFN[Det] += FastN_t_Bin[Det];
			TotalLi9[Det] += Li9_t_Bin[Det];
			TotalAmC[Det] += AmC_t_Bin[Det];
///////SYS
		
			if(IBD_t_Bin[Det]>0)
			{
				IsGoodBin[Det][Bin] = true;
				NumOfGoodBin[Det] ++;
			}
		}

		double M[3]={0.0};
		double P[3]={0.0};
		for(int Det=0;Det<2;Det++)
		{
			if(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]>0.01)
			{
			M[0] += IBD_t_Bin[Det]/(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]) - (AmC_t_Bin[Det]+Acc_t_Bin[Det]+Li9_t_Bin[Det]+FastN_t_Bin[Det]);
			P[0] += 1.0*Prediction_t_Bin[Det]*1.0e-17*Np*CrossSection/(4.0*pi);
			}
		}
		for(int Det=2;Det<4;Det++)
		{
			if(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]>0.01)
			{
			M[1] += IBD_t_Bin[Det]/(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]) - (AmC_t_Bin[Det]+Acc_t_Bin[Det]+Li9_t_Bin[Det]+FastN_t_Bin[Det]);
			P[1] += 1.0*Prediction_t_Bin[Det]*1.0e-17*Np*CrossSection/(4.0*pi);
			}
		}
		for(int Det=4;Det<8;Det++)
		{
			if(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]>0.01)
			{
			M[2] += IBD_t_Bin[Det]/(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]) - (AmC_t_Bin[Det]+Acc_t_Bin[Det]+Li9_t_Bin[Det]+FastN_t_Bin[Det]);
			}
		}
		
		P[2] = AlphaBeta_t[0]*M[0]+AlphaBeta_t[1]*M[1];

		for(int Hidx=0;Hidx<3;Hidx++)
		{
			if(P[Hidx]>0.0001)
			{
				R_data[Hidx][Bin] = M[Hidx]/P[Hidx];
			}
		}
	}


	////cout empty bins..........

	FILE* m_outfile_bin = fopen("empty_bin.txt", "w+");
	for(int Det=0;Det<8;Det++)
	{
		fprintf(m_outfile_bin,"AD..... %2d \n \n",Det+1);
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			if(!IsGoodBin[Det][Bin])
			{
				fprintf(m_outfile_bin,"%6d ",Bin);
			}
		}
		fprintf(m_outfile_bin,"\n");
	}
	//FFT
	
	double mean_an[3][NumOfBin]={{0.0}};
	double mean_bn[3][NumOfBin]={{0.0}};
	double sigma_an[3][NumOfBin]={{0.0}};
	double sigma_bn[3][NumOfBin]={{0.0}};
	
	TH1F *hist_a0 = new TH1F("hist_a0","hist_a0",1000,-2.0,2.0);
	TH1F *hist_a1 = new TH1F("hist_a1","hist_a1",1000,-0.1,0.1);
	TH1F *hist_a2 = new TH1F("hist_a2","hist_a2",1000,-0.1,0.1);
	TH1F *hist_b1 = new TH1F("hist_b1","hist_b1",1000,-0.1,0.1);
	TH1F *hist_b2 = new TH1F("hist_b2","hist_b2",1000,-0.1,0.1);


	Double_t re, im, Frk;

	for(int idx=0;idx<nSample;idx++)
	{
//cout<<idx<<endl;
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
		double M[3]={0.0};
		double P[3]={0.0};

		for(int Det=0;Det<2;Det++)
		{
		//	if(!IsGoodBin[Det][Bin])
			{
				M[0] += my_Random->PoissonD(TotalIBD[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_Eff) 
					- (TotalAcc[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_Acc[Det])
					- (TotalFN[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_FN[Det])
					- (TotalAmC[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_AmC[Det])
					- (TotalLi9[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_Li9[Det]);
				P[0] += TotalIBD[Det]/NumOfBin*my_Random->Gaus(1.0,RD_Power);//*0.572);
			}
		}
		for(int Det=2;Det<4;Det++)
		{
//			if(!IsGoodBin[Det][Bin])
			{
				M[1] += my_Random->PoissonD(TotalIBD[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_Eff) 
					- (TotalAcc[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_Acc[Det])
					- (TotalFN[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_FN[Det])
					- (TotalAmC[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_AmC[Det])
					- (TotalLi9[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_Li9[Det]);
				P[1] += TotalIBD[Det]/NumOfBin*my_Random->Gaus(1.0,RD_Power);//*0.472);
			}
			
		}
		for(int Det=4;Det<8;Det++)
		{
		//	if(!IsGoodBin[Det][Bin])
			{
					M[2] += my_Random->PoissonD(TotalIBD[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_Eff) 
					- (TotalAcc[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_Acc[Det])
					- (TotalFN[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_FN[Det])
					- (TotalAmC[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_AmC[Det])
					- (TotalLi9[Det]/NumOfBin)*my_Random->Gaus(1.0,RD_Li9[Det]);
			}
		}

		P[2] = (Alpha_8AD*M[0]+Beta_8AD*M[1])*my_Random->Gaus(1.0,RD_Power*0.047);

		for(int Hidx=0;Hidx<3;Hidx++)
		{
			if((P[Hidx]>0.00001)&&(M[Hidx]>0.00001))
			{
				R[Hidx][Bin] = M[Hidx]/P[Hidx];
			}
		}
		}

	
	//	Exclusion_3s();
		Normalization();
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
		for(int Hidx=0;Hidx<3;Hidx++)
		{
			R[Hidx][Bin] = R[Hidx][Bin]*AVEP[Hidx];
			if(R[Hidx][Bin]>0.001)
			{
			R[Hidx][Bin] = R[Hidx][Bin] - AVEP[Hidx];
			}
			else
			{
				R[Hidx][Bin] = 0.0;
			}
		}
		}

	for(int Hidx=0;Hidx<3;Hidx++)
	{

		int n = NumOfBin;

	    TVirtualFFT *fftr2c = TVirtualFFT::FFT(1, &n, "R2C");
		double in[NumOfBin];

		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			in[Bin] = R[Hidx][Bin];
		}
		fftr2c->SetPoints(in);
		fftr2c->Transform();

		fftr2c->GetPointComplex(0, re, im);

		mean_an[Hidx][0] += re/NumOfBin;
		mean_bn[Hidx][0] += -1.0*im/NumOfBin;
		sigma_an[Hidx][0] += pow(re/NumOfBin,2.0);
		sigma_bn[Hidx][0] += pow(-1.0*im/NumOfBin,2.0);

		if(Hidx==2)
		{
		hist_a0->Fill(re/NumOfBin);
		}
		//cout<<idx<<"   "<<Hidx<<"   "<<"   "<<re/NumOfBin<<"   "<<-1.0*im/NumOfBin<<endl;
			 
		for(int Bin=1;Bin<NumOfBin;Bin++)
		{
			fftr2c->GetPointComplex(Bin, re, im);
			double a = re*2.0/NumOfBin;
			double b = -1.0*im*2.0/NumOfBin;

			mean_an[Hidx][Bin] += a;
			mean_bn[Hidx][Bin] += b;
			sigma_an[Hidx][Bin] += a*a;
			sigma_bn[Hidx][Bin] += b*b;
			if(Hidx==2)
			{
			if(Bin==706)
			{
				hist_a1->Fill(a);
				hist_b1->Fill(b);
			}
			if(Bin==1414)
			{
				hist_a2->Fill(a);
				hist_b2->Fill(b);
			}
			}
		}
	}
	}

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			mean_an[Hidx][Bin] = mean_an[Hidx][Bin]/nSample;
			mean_bn[Hidx][Bin] = mean_bn[Hidx][Bin]/nSample;
			sigma_an[Hidx][Bin]  = sigma_an[Hidx][Bin]/nSample -pow(mean_an[Hidx][Bin],2.0);
			sigma_an[Hidx][Bin] = pow(sigma_an[Hidx][Bin],0.5);
			sigma_bn[Hidx][Bin]  = sigma_bn[Hidx][Bin]/nSample -pow(mean_bn[Hidx][Bin],2.0);
			sigma_bn[Hidx][Bin] = pow(sigma_bn[Hidx][Bin],0.5);

			//normalization
		/*	mean_an[Hidx][Bin] = mean_an[Hidx][Bin]/mean_an[Hidx][0];
			mean_bn[Hidx][Bin] = mean_bn[Hidx][Bin]/mean_an[Hidx][0];
			sigma_an[Hidx][Bin] = sigma_an[Hidx][Bin]/mean_an[Hidx][0];
			sigma_bn[Hidx][Bin] = sigma_bn[Hidx][Bin]/mean_an[Hidx][0];*/
		}
	}

	
		TCanvas *myC_a0 = new TCanvas("c_a0","c_a0",0,0,800,420);
		hist_a0->Draw();
		TCanvas *myC_a1 = new TCanvas("c_a1","c_a1",0,0,800,420);
		hist_a1->Draw();
		TCanvas *myC_a2 = new TCanvas("c_a2","c_a2",0,0,800,420);
		hist_a2->Draw();
		TCanvas *myC_b1 = new TCanvas("c_b1","c_b1",0,0,800,420);
		hist_b1->Draw();
		TCanvas *myC_b2 = new TCanvas("c_b2","c_b2",0,0,800,420);
		hist_b2->Draw();

	//print
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{

		fprintf(m_outfile,"%6d   %7.4f \\pm %7.4f  %7.4f \\pm %7.4f    %7.4f \\pm %7.4f  %7.4f \\pm %7.4f    %7.4f \\pm %7.4f  %7.4f \\pm %7.4f      ",Bin,
					mean_an[0][Bin],sigma_an[0][Bin],
					mean_bn[0][Bin],sigma_bn[0][Bin],
					mean_an[1][Bin],sigma_an[1][Bin],
					mean_bn[1][Bin],sigma_bn[1][Bin],
					mean_an[2][Bin],sigma_an[2][Bin],
					mean_bn[2][Bin],sigma_bn[2][Bin]);
		for(int Det=0;Det<8;Det++)
		{
			//fprintf(m_outfile,"%4.1f  %4.1f  %4.1f    ",IBDInEachBin[Det][Bin],LiveTimeInEachBin[Det][Bin]*TotalIBD[Det]/TotalLiveTime[Det],PredictionInEachBin[Det][Bin]);
	//		fprintf(m_outfile,"%4.1f  ",IBDInEachBin[Det][Bin]);
		}

		fprintf(m_outfile,"\n");
	}

	const int nX = 1450;

	double nBins = 706.0;


/*
   //Draw, Rt
	const char* hist_Name_Rt[3] = {"EH1_Rt","EH2_Rt","EH3_Rt"};
	const char* file_Name_Rt[3] = {"EH1_Rt_NoGap.eps","EH2_Rt_NoGap.eps","EH3_Rt_NoGap.eps"};
	TCanvas *myC_Rt[3];
	TGraphErrors *gr_Rt[3];

	TLegend *leg_Rt[3];
	const char* leg_Name_Rt[3] = {"EH1 - R(t) - no gap","EH2 - R(t) - no gap","EH3 - R(t) - no gap"};

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		myC_Rt[Hidx] = new TCanvas(hist_Name_Rt[Hidx],hist_Name_Rt[Hidx],0,0,800,420);

		int n = NumOfBin;

		double x[n],y[n],ex[n],ey[n];

		for(int Bin=0;Bin<n;Bin++)
		{
		x[Bin] = Bin;
		y[Bin] = R[Hidx][Bin];
		ex[Bin]=0.0;
		ey[Bin] = 0.0;
		}
		gr_Rt[Hidx] = new TGraphErrors(n,x,y,ex,ey);
		gr_Rt[Hidx]->GetYaxis()->SetRangeUser(-1.5,1.5);
		gr_Rt[Hidx]->GetXaxis()->SetRangeUser(0,n);
		gr_Rt[Hidx]->SetMarkerColor(kBlue);
		gr_Rt[Hidx]->SetMarkerStyle(6);
		gr_Rt[Hidx]->GetXaxis()->SetTitle("sidereal time(1 bin =86164.09/24 seconds)");
		gr_Rt[Hidx]->GetYaxis()->SetTitle("R(t) - R0");

		gr_Rt[Hidx]->SetTitle("");

		gr_Rt[Hidx]->GetYaxis()->SetTitleOffset(0.4);
		gr_Rt[Hidx]->GetYaxis()->SetTitleSize(0.08);
		gr_Rt[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_Rt[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
		gr_Rt[Hidx]->GetXaxis()->SetTitleOffset(0.7);
		gr_Rt[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_Rt[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr_Rt[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_Rt[Hidx]->Draw("APZ");
		
		leg_Rt[Hidx] = new TLegend(0.25, 0.5, 0.75, 0.8);
		leg_Rt[Hidx]->AddEntry(gr_Rt[Hidx],leg_Name_Rt[Hidx],"");
		leg_Rt[Hidx]->SetFillStyle(0);
		leg_Rt[Hidx]->SetBorderSize(0);
		leg_Rt[Hidx]->SetTextColor(kRed);
		leg_Rt[Hidx]->Draw();

		myC_Rt[Hidx]->SaveAs(file_Name_Rt[Hidx]);
	}



//Draw, _abn
	
	const char* hist_Name_abn[3] = {"EH1_abn","EH2_abn","EH3_abn"};

	const char* file_Name_abn[3] = {"EH1_abn_MC_NoGap.eps","EH2_abn_MC_NoGap.eps","EH3_abn_MC_NoGap.eps"};
	TCanvas *myC_abn[3];

	TGraphErrors *gr_an[3];

	TLegend *leg_an[3];
	const char* leg_Name_an[3] = {"EH1 - MC - a_{n} - no gap","EH2 - MC - a_{n} - no gap","EH3 - MC - a_{n} - no gap"};
	TGraphErrors *gr_bn[3];

	TLegend *leg_bn[3];
	const char* leg_Name_bn[3] = {"EH1 - MC - b_{n} - no gap","EH2 - MC - b_{n} - no gap","EH3 - MC - b_{n} - no gap"};


	for(int Hidx=0;Hidx<3;Hidx++)
	{

		myC_abn[Hidx] = new TCanvas(hist_Name_abn[Hidx],hist_Name_abn[Hidx],0,0,800,600);
		myC_abn[Hidx]->Divide(1,2,0);
		{
		myC_abn[Hidx]->cd(1);

		double x[nX],y[nX],ex[nX],ey[nX];

		for(int Bin=0;Bin<nX;Bin++)
		{
		x[Bin] = Bin/nBins;
		int kM = int(706.0*x[Bin]);

		y[Bin] = mean_an[Hidx][kM];
		ex[Bin]=0.0;
		ey[Bin]=sigma_an[Hidx][kM];
		}
		gr_an[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_an[Hidx]->GetYaxis()->SetRangeUser(-0.065,0.065);
		gr_an[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_an[Hidx]->SetMarkerColor(kBlue);
		gr_an[Hidx]->SetLineColor(kBlue);
		gr_an[Hidx]->SetLineWidth(2);
		gr_an[Hidx]->SetMarkerStyle(8);
		gr_an[Hidx]->SetMarkerSize(0.5);
		gr_an[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_an[Hidx]->GetYaxis()->SetTitle("a");

		gr_an[Hidx]->SetTitle("");

		gr_an[Hidx]->GetYaxis()->SetTitleOffset(0.4);
		gr_an[Hidx]->GetYaxis()->SetTitleSize(0.08);
		gr_an[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_an[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
		gr_an[Hidx]->GetXaxis()->SetTitleOffset(0.7);
		gr_an[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_an[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr_an[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_an[Hidx]->Draw("APZ");

		leg_an[Hidx] = new TLegend(0.25, 0.5, 0.75, 0.8);
		leg_an[Hidx]->AddEntry(gr_an[Hidx],leg_Name_an[Hidx],"");
		leg_an[Hidx]->SetFillStyle(0);
		leg_an[Hidx]->SetBorderSize(0);
		leg_an[Hidx]->SetTextColor(kRed);
		leg_an[Hidx]->Draw();
		}

	
		{
		myC_abn[Hidx]->cd(2);

		double x[nX],y[nX],ex[nX],ey[nX];

		for(int Bin=0;Bin<nX;Bin++)
		{
		x[Bin] = Bin/nBins;
		int kM = int(706.0*x[Bin]);

		y[Bin] = mean_bn[Hidx][kM];
		ex[Bin]=0.0;
		ey[Bin]=sigma_bn[Hidx][kM];
		}
		gr_bn[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_bn[Hidx]->GetYaxis()->SetRangeUser(-0.065,0.065);
		gr_bn[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_bn[Hidx]->SetMarkerColor(kBlue);
		gr_bn[Hidx]->SetLineColor(kBlue);
		gr_bn[Hidx]->SetLineWidth(2);
		gr_bn[Hidx]->SetMarkerStyle(8);
		gr_bn[Hidx]->SetMarkerSize(0.5);
		gr_bn[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_bn[Hidx]->GetYaxis()->SetTitle("b");

		gr_bn[Hidx]->SetTitle("");

		gr_bn[Hidx]->GetYaxis()->SetTitleOffset(0.4);
		gr_bn[Hidx]->GetYaxis()->SetTitleSize(0.08);
		gr_bn[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_bn[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
		gr_bn[Hidx]->GetXaxis()->SetTitleOffset(0.7);
		gr_bn[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_bn[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr_bn[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_bn[Hidx]->Draw("APZ");
	
		leg_bn[Hidx] = new TLegend(0.25, 0.5, 0.75, 0.8);
		leg_bn[Hidx]->AddEntry(gr_bn[Hidx],leg_Name_bn[Hidx],"");
		leg_bn[Hidx]->SetFillStyle(0);
		leg_bn[Hidx]->SetBorderSize(0);
		leg_bn[Hidx]->SetTextColor(kRed);
		leg_bn[Hidx]->Draw();
		}
	
		myC_abn[Hidx]->SaveAs(file_Name_abn[Hidx]);
}

*/

//save to .root file

	 double an_t[3][2];
	 TFile  *F_an = new TFile("an_MC_Unc.root","recreate");
	 TTree *Tree_an = new TTree("an","an");
	 Tree_an->Branch("an",an_t,"an_t[3][2]/D");
	 for(int Bin=0; Bin<NumOfBin;Bin++)
	 {
		 for(int Hidx=0;Hidx<3;Hidx++)
		 {
		 an_t[Hidx][0] = mean_an[Hidx][Bin];
		 an_t[Hidx][1] = sigma_an[Hidx][Bin];
		 }
		 Tree_an->Fill();
	 }
	 Tree_an->Write();

	 double bn_t[3][2];
	 TFile  *F_bn = new TFile("bn_MC_Unc.root","recreate");
	 TTree *Tree_bn = new TTree("bn","bn");
	 Tree_bn->Branch("bn",bn_t,"bn_t[3][2]/D");
	 for(int Bin=0; Bin<NumOfBin;Bin++)
	 {
		 for(int Hidx=0;Hidx<3;Hidx++)
		 {
		 bn_t[Hidx][0] = mean_bn[Hidx][Bin];
		 bn_t[Hidx][1] = sigma_bn[Hidx][Bin];
		 }
		 Tree_bn->Fill();
	 }
	 Tree_bn->Write();
}

void Normalization()
{
	int NumOfGood[3] = {0};
	double TotalR[3]={0.0};

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			if(R[Hidx][Bin]>0.001)
			{
				NumOfGood[Hidx]++;
				TotalR[Hidx] += R[Hidx][Bin];
			}
		}
	}
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		for(int Hidx=0;Hidx<3;Hidx++)
		{
			R[Hidx][Bin] = R[Hidx][Bin]*(1.0*NumOfGood[Hidx])/TotalR[Hidx];
		}
	}
}
void Exclusion_3s()
{
	//3 sigma exclusion

	const char* hist_Name_3s[3] = {"EH1-3s","EH2-3s","EH3-3s"};
	TH1F *hist_R_3s[3];
	double sigma[3]={0.0};
	double mean[3]={0.0};
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		hist_R_3s[Hidx] = new TH1F(hist_Name_3s[Hidx],hist_Name_3s[Hidx],NumOfBin,0.01,3.0);
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			hist_R_3s[Hidx]->Fill(R[Hidx][Bin]);
		}
		sigma[Hidx] = hist_R_3s[Hidx]->GetRMS();
		mean[Hidx] = hist_R_3s[Hidx]->GetMean();
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			if((R[Hidx][Bin]>(mean[Hidx]+3.0*sigma[Hidx]))||((R[Hidx][Bin]<(mean[Hidx]-3.0*sigma[Hidx]))))
			{
				R[Hidx][Bin] = 0.0;
			}
		}
	}
}

//backup codes
/*
	double IBDInOneDay_1[8][24]={{0.0}};
	double IBDInOneDay_2[8][24]={{0.0}};
	TH1F *h1st = new TH1F("h1st","original",24,0,24);
	TH1F *h2st = new TH1F("h2st","Flux_prediction",24,0,24);

    for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N24 = Bin%24;
		for(int Det=0;Det<8;Det++)
		{
			IBDInOneDay_1[Det][N24] += IBDInEachBin[Det][Bin];
			IBDInOneDay_2[Det][N24] += PredictionInEachBin[Det][Bin]*TotalIBD[Det]/TotalPrediction[Det];
		}
	}
	for(int N24=0;N24<24;N24++)
	{
		h1st->SetBinContent(N24+1,IBDInOneDay_1[1][N24]);
		h2st->SetBinContent(N24+1,IBDInOneDay_2[1][N24]);
	}
	TCanvas *myC1 =  new TCanvas("myC_original","myC_original",0,0,800,600);
	h1st->Draw();
	TCanvas *myC2 =  new TCanvas("myC_Flux","myC_Flux",0,0,800,600);
	h2st->Draw();

	double AlphaBeta_t[2];
	Double_t AlphaBetaInEachBin[2][NumOfBin];
	memset(AlphaBetaInEachBin,0.0,sizeof(AlphaBetaInEachBin));
	TFile *F_Bin_AlphaBeta = new TFile("../daily_data/AlphaBeta_Bin.root");
	TTree *Tree_Bin_AlphaBeta = (TTree*)F_Bin_AlphaBeta->Get("AlphaBeta");
	Tree_Bin_AlphaBeta->SetBranchAddress("AlphaBeta",AlphaBeta_t);
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		Tree_Bin_AlphaBeta->GetEntry(Bin);
		AlphaBetaInEachBin[0][Bin] = AlphaBeta_t[0];
		AlphaBetaInEachBin[1][Bin] = AlphaBeta_t[1];
	}



*/


