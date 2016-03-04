#include <math.h>
#include "TRandom.h"
#include <math.h>
#include <time.h>

double TotalIBD_Before[8] = {0.0};
double TotalIBD_After[8] ={0.0};

const int NumOfBin = 16944;
double R[3][NumOfBin] = {{0.0}};
double RD_R[3][NumOfBin] = {{0.0}};

double AVEP[3] = {0.985,0.983,0.951455};

void Normalization();
void Exclusion_3s();

void FFT_data()
{
     Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
     Double_t StartTime = 1324678393.80705;

	 //cout<<"hello......"<<endl;

	const double pi = 3.141592653;
	Double_t CrossSection = 0.94;//Averaged cross-section, in unit of 1e-43 cm^2;
    Double_t Np = 1.43;//Total number of target protons in AD1,AD2, in unit of 1e30

	//Prediction candidate
	Double_t PredictionInEachBin[8][NumOfBin];
	double Prediction_t_Bin[8];
	double TotalPrediction[8]={0.0};
	memset(PredictionInEachBin,0.0,sizeof(PredictionInEachBin));
	TFile *F_Bin_Prediction = new TFile("../daily_data/Fraction_AD_Bin.root");
	TTree *Tree_Bin_Prediction = (TTree*)F_Bin_Prediction->Get("Fraction");
	Tree_Bin_Prediction->SetBranchAddress("Fraction",Prediction_t_Bin);

	//IBD candidate
	Double_t IBDInEachBin[8][NumOfBin];
	Int_t IBD_t_Bin[8];
	double TotalIBD[8]={0.0};
	memset(IBDInEachBin,0.0,sizeof(IBDInEachBin));
	TFile *F_Bin_IBD = new TFile("../IBD.root");
	TTree *Tree_Bin_IBD = (TTree*)F_Bin_IBD->Get("IBD");
	Tree_Bin_IBD->SetBranchAddress("IBD",IBD_t_Bin);

	//FullTime
//	Double_t FullTimeInEachBin[8][NumOfBin];
	Double_t FullTime_t_Bin[8];
//	memset(FullTimeInEachBin,0.0,sizeof(FullTimeInEachBin));
	TFile *F_Bin_FullTime = new TFile("../FullTime.root");
	TTree *Tree_Bin_FullTime = (TTree*)F_Bin_FullTime->Get("FullTime");
	Tree_Bin_FullTime->SetBranchAddress("FullTime",FullTime_t_Bin);

	//LiveTime
//	Double_t LiveTimeInEachBin[8][NumOfBin];
	Double_t LiveTime_t_Bin[8];
	double TotalLiveTime[8]={0.0};
//	memset(LiveTimeInEachBin,0.0,sizeof(LiveTimeInEachBin));
	TFile *F_Bin_LiveTime = new TFile("../LiveTime.root");
	TTree *Tree_Bin_LiveTime = (TTree*)F_Bin_LiveTime->Get("LiveTime");
	Tree_Bin_LiveTime->SetBranchAddress("LiveTime",LiveTime_t_Bin);


	double BkgInEachBin[8][NumOfBin]={{0.0}};

	//AmC
//    Double_t AmCInEachBin[8][NumOfBin];
	Double_t AmC_t_Bin[8];
//	memset(AmCInEachBin,0.0,sizeof(AmCInEachBin));
	TFile *F_Bin_AmC = new TFile("../AmC/AmCInEachBin.root");
	TTree *Tree_Bin_AmC = (TTree*)F_Bin_AmC->Get("AmCInEachBin");
	Tree_Bin_AmC->SetBranchAddress("AmCInEachBin",AmC_t_Bin);
	
	//Acc
//	Double_t AccInEachBin[8][NumOfBin];
	Double_t Acc_t_Bin[8];
//	memset(AccInEachBin,0.0,sizeof(AccInEachBin));
	TFile *F_Bin_Acc = new TFile("../AccBkg/AccInEachBin.root");
	TTree *Tree_Bin_Acc = (TTree*)F_Bin_Acc->Get("AccInEachBin");
	Tree_Bin_Acc->SetBranchAddress("AccInEachBin",Acc_t_Bin);
	
//	Double_t Li9InEachBin[8][NumOfBin];
	Double_t Li9_t_Bin[8];
//	memset(Li9InEachBin,0.0,sizeof(Li9InEachBin));
	TFile *F_Bin_Li9 = new TFile("../Li9/Li9InEachBin.root");
	TTree *Tree_Bin_Li9 = (TTree*)F_Bin_Li9->Get("Li9InEachBin");
	Tree_Bin_Li9->SetBranchAddress("Li9InEachBin",Li9_t_Bin);

	//FastN
//	Double_t FastNInEachBin[8][NumOfBin];
	Double_t FastN_t_Bin[8];
//	memset(FastNInEachBin,0.0,sizeof(FastNInEachBin));
	TFile *F_Bin_FastN = new TFile("../FastN/FastNInEachBin.root");
	TTree *Tree_Bin_FastN = (TTree*)F_Bin_FastN->Get("FastNInEachBin");
	Tree_Bin_FastN->SetBranchAddress("FastNInEachBin",FastN_t_Bin);


	double EffInEachBin[8][NumOfBin]={{0.0}};
	//MultiEff
	//Double_t MultiEffInEachBin[8][NumOfBin];
	Double_t MultiEff_t_Bin[8];
//	memset(MultiEffInEachBin,0.0,sizeof(MultiEffInEachBin));
	TFile *F_Bin_MultiEff = new TFile("../MultiEff/MultiEffInEachBin.root");
	TTree *Tree_Bin_MultiEff = (TTree*)F_Bin_MultiEff->Get("MultiEffInEachBin");
	Tree_Bin_MultiEff->SetBranchAddress("MultiEffInEachBin",MultiEff_t_Bin);

	//MuEff
//	Double_t MuEffInEachBin[8][NumOfBin];
	Double_t MuEff_t_Bin[8];
//	memset(MuEffInEachBin,0.0,sizeof(MuEffInEachBin));
	TFile *F_Bin_MuEff = new TFile("../MuEff/MuEffInEachBin.root");
	TTree *Tree_Bin_MuEff = (TTree*)F_Bin_MuEff->Get("MuEffInEachBin");
	Tree_Bin_MuEff->SetBranchAddress("MuEffInEachBin",MuEff_t_Bin);

	//alpha beta
	double AlphaBeta_t[2];
	Double_t AlphaBetaInEachBin[2][NumOfBin];
	memset(AlphaBetaInEachBin,0.0,sizeof(AlphaBetaInEachBin));
	TFile *F_Bin_AlphaBeta = new TFile("../daily_data/AlphaBeta_Bin.root");
	TTree *Tree_Bin_AlphaBeta = (TTree*)F_Bin_AlphaBeta->Get("AlphaBeta");
	Tree_Bin_AlphaBeta->SetBranchAddress("AlphaBeta",AlphaBeta_t);

	FILE* m_outfile_time = fopen("time_info.txt", "w+");

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
		
		AlphaBetaInEachBin[0][Bin] = AlphaBeta_t[0];
		AlphaBetaInEachBin[1][Bin] = AlphaBeta_t[1];

		for(int Det=0;Det<8;Det++)
		{
			TotalLiveTime[Det] += LiveTime_t_Bin[Det];
			TotalIBD[Det] += 1.0*IBD_t_Bin[Det];
			TotalIBD_Before[Det] += 1.0*IBD_t_Bin[Det];
			IBDInEachBin[Det][Bin] = 1.0*IBD_t_Bin[Det];
			PredictionInEachBin[Det][Bin] = 1.0*Prediction_t_Bin[Det]*1.0e-17*Np*CrossSection/(4.0*pi);
			TotalPrediction[Det] += 1.0*Prediction_t_Bin[Det]*1.0e-17*Np*CrossSection/(4.0*pi);
//			FullTimeInEachBin[Det][Bin] = FullTime_t_Bin[Det];
//			LiveTimeInEachBin[Det][Bin] = LiveTime_t_Bin[Det];
			BkgInEachBin[Det][Bin] += AmC_t_Bin[Det]+Acc_t_Bin[Det]+Li9_t_Bin[Det]+FastN_t_Bin[Det];
			EffInEachBin[Det][Bin] = MultiEff_t_Bin[Det]*MuEff_t_Bin[Det];

		}

		double M[3]={0.0};
		double P[3]={0.0};
		for(int Det=0;Det<2;Det++)
		{
			if((LiveTime_t_Bin[Det]>10.0)&&(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]>0.01))
			{
			M[0] += IBD_t_Bin[Det]/(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]) - (AmC_t_Bin[Det]+Acc_t_Bin[Det]+Li9_t_Bin[Det]+FastN_t_Bin[Det]);
			P[0] += 1.0*Prediction_t_Bin[Det]*1.0e-17*Np*CrossSection/(4.0*pi);
			}
		}
		for(int Det=2;Det<4;Det++)
		{
			//if(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]>0.01)
			if((LiveTime_t_Bin[Det]>10.0)&&(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]>0.01))
			{
			M[1] += IBD_t_Bin[Det]/(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]) - (AmC_t_Bin[Det]+Acc_t_Bin[Det]+Li9_t_Bin[Det]+FastN_t_Bin[Det]);
			P[1] += 1.0*Prediction_t_Bin[Det]*1.0e-17*Np*CrossSection/(4.0*pi);
			}
		}
		for(int Det=4;Det<8;Det++)
		{
			//if(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]>0.01)
			if((LiveTime_t_Bin[Det]>10.0)&&(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]>0.01))
			{
			M[2] += IBD_t_Bin[Det]/(MultiEff_t_Bin[Det]*MuEff_t_Bin[Det]) - (AmC_t_Bin[Det]+Acc_t_Bin[Det]+Li9_t_Bin[Det]+FastN_t_Bin[Det]);
			}
		}
	
		if(M[0]>0.001&&M[1]>0.001)
		{
		P[2] = AlphaBeta_t[0]*M[0]+AlphaBeta_t[1]*M[1];
		}

		for(int Hidx=0;Hidx<3;Hidx++)
		{
			if(P[Hidx]>0.0001)
			{
				R[Hidx][Bin] = M[Hidx]/P[Hidx];
				if(Hidx==2)
				{
					for(int Det=0;Det<8;Det++)
					{
						TotalIBD_After[Det] += 1.0*IBD_t_Bin[Det];
					}
				}
			}
			else if(IBD_t_Bin[4]>0)
			{
				if(Hidx==2)
				{
					time_t timep1,timep2;
					timep1 = StartTime+Bin*WidthOfBin;
				//	printf("%s -- ", asctime(gmtime(&timep)));
					fprintf(m_outfile_time,"%s -- ", asctime(gmtime(&timep1)));
					timep1 = StartTime+(1.0+Bin)*WidthOfBin;
					fprintf(m_outfile_time,"%s  ", asctime(gmtime(&timep1)));

					for(int Det=0;Det<8;Det++)
					{
						////cout<<LiveTime_t_Bin[Det]<<"   ";
						fprintf(m_outfile_time,"%8.2f   ",LiveTime_t_Bin[Det]);
					}
					////cout<<endl;
					fprintf(m_outfile_time,"\n");
				}
			}
		}
	}


//	//cout<<"TotalIBD_Before:   ";
	fprintf(m_outfile_time,"TotalIBD_Before:   ");
	for(int Det=0;Det<8;Det++)
	{
		//		//cout<<TotalIBD_Before[Det]<<"   ";
		fprintf(m_outfile_time,"%8.0f   ",TotalIBD_Before[Det]);
	}
	fprintf(m_outfile_time,"\n");
	fprintf(m_outfile_time,"TotalIBD_After:   ");
	for(int Det=0;Det<8;Det++)
	{
		fprintf(m_outfile_time,"%8.0f   ",TotalIBD_After[Det]);
	}
    fprintf(m_outfile_time,"\n");

	//prediction normalization
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			PredictionInEachBin[Det][Bin] = PredictionInEachBin[Det][Bin]*TotalIBD[Det]/TotalPrediction[Det];
		}
	}

	Exclusion_3s();
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


	//FFT
	TVirtualFFT *fftr2c[3];// = TVirtualFFT::FFT(1, &NumOfGroup, "R2C");

	double an[3][NumOfBin]={{0.0}};
	double bn[3][NumOfBin]={{0.0}};

     Double_t re, im, Frk;

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		int n = NumOfBin;
		fftr2c[Hidx] =  TVirtualFFT::FFT(1, &n, "R2C");
		double in[NumOfBin];
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			in[Bin] = R[Hidx][Bin];
		}
		fftr2c[Hidx]->SetPoints(in);
		fftr2c[Hidx]->Transform();
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			fftr2c[Hidx]->GetPointComplex(Bin, re, im);
			Frk = sqrt(pow(re,2)+pow(im,2));
			an[Hidx][Bin] = re*2.0/NumOfBin;
			bn[Hidx][Bin] = -1.0*im*2.0/NumOfBin;
		}
		an[Hidx][0] = an[Hidx][0]*0.5;
		bn[Hidx][0] = bn[Hidx][0]*0.5;
		
		//R0 normalized to 1.0
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
	//		an[Hidx][Bin] = an[Hidx][Bin]/an[Hidx][0];
	//		bn[Hidx][Bin] = bn[Hidx][Bin]/an[Hidx][0];
		}

	}

	
	FILE* m_outfile = fopen("log_data.txt", "w+");


	//print
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{

		fprintf(m_outfile,"%6d  %6.4f  %6.4f  %6.4f   %8.6f p %8.6f  %8.6f p %8.6f  %8.6f p %8.6f   ",Bin,R[0][Bin],R[1][Bin],R[2][Bin],an[0][Bin],bn[0][Bin],an[1][Bin],bn[1][Bin],an[2][Bin],bn[2][Bin]);
		for(int Det=0;Det<8;Det++)
		{
			//fprintf(m_outfile,"%4.1f  %4.1f  %4.1f    ",IBDInEachBin[Det][Bin],LiveTimeInEachBin[Det][Bin]*TotalIBD[Det]/TotalLiveTime[Det],PredictionInEachBin[Det][Bin]);
			fprintf(m_outfile,"%4.1f  ",IBDInEachBin[Det][Bin]);
		}

		fprintf(m_outfile,"\n");
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



	//Draw
	const char* hist_Name[3] = {"EH1","EH2","EH3"};
	const char* file_Name[3] = {"EH1_Rt_data.eps","EH2_Rt_data.eps","EH3_Rt_data.eps"};
	TCanvas *myC_R[3];
	TGraphErrors *gr_R[3];
    
	TLegend *leg_Rt[3];
    const char* leg_Name_Rt[3] = {"EH1_R(t)-R0_data","EH2_R(t)-R0_data","EH3_R(t)-R0_data"};

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		myC_R[Hidx] = new TCanvas(hist_Name[Hidx],hist_Name[Hidx],0,0,800,600);
		double x[NumOfBin],y[NumOfBin],ex[NumOfBin],ey[NumOfBin];

		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
		x[Bin] = 1.0*(Bin+0.5)*WidthOfBin;
		y[Bin] = R[Hidx][Bin];
		ex[Bin]=0.0;
		ey[Bin]=0.0;
		}
		gr_R[Hidx] = new TGraphErrors(NumOfBin,x,y,ex,ey);
		gr_R[Hidx]->GetYaxis()->SetRangeUser(-1.25,1.25);
		gr_R[Hidx]->GetXaxis()->SetRangeUser(0,WidthOfBin*NumOfBin);
		gr_R[Hidx]->GetXaxis()->SetTimeDisplay(1);
		gr_R[Hidx]->GetXaxis()->SetTimeFormat("%b\/20%y%F2011-12-23 22:12:13");
		gr_R[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr_R[Hidx]->SetMarkerColor(1);
		gr_R[Hidx]->SetMarkerStyle(6);
	//	gr_R[Hidx]->GetXaxis()->SetTitle("sidereal time(1 bin =86164.09/24 seconds)");
		gr_R[Hidx]->GetYaxis()->SetTitle("R(t) - R_{0}");

		gr_R[Hidx]->SetTitle("");

		gr_R[Hidx]->GetYaxis()->SetTitleOffset(0.62);
		gr_R[Hidx]->GetYaxis()->SetTitleSize(0.07);
		gr_R[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_R[Hidx]->GetYaxis()->SetLabelOffset(0.0);
		gr_R[Hidx]->GetYaxis()->SetNdivisions(505);
		gr_R[Hidx]->GetXaxis()->SetNdivisions(505);
		gr_R[Hidx]->GetYaxis()->CenterTitle();
	
		gr_R[Hidx]->GetXaxis()->SetTitleOffset(0.8);
		gr_R[Hidx]->GetXaxis()->SetTitleSize(0.06);
		//gr[Hidx]->GetXaxis()->SetLabelSize(0.045);
		gr_R[Hidx]->GetXaxis()->SetLabelOffset(0.0);

		gr_R[Hidx]->Draw("APZ");


		 leg_Rt[Hidx] = new TLegend(0.15, 0.65, 0.85, 0.98);
		 leg_Rt[Hidx]->AddEntry(gr_R[Hidx],leg_Name_Rt[Hidx],"");
		 leg_Rt[Hidx]->SetFillStyle(0);
		 leg_Rt[Hidx]->SetBorderSize(0);
		 leg_Rt[Hidx]->SetTextColor(kRed);
	//	 leg_Rt[Hidx]->Draw();

		myC_R[Hidx]->SaveAs(file_Name[Hidx]);
	}
////////////////////////////////////////////////////////////////////////////////////////////
const int nX = 1450;
double nBins = 706.0;

	
//Draw, _abn
	
	const char* hist_Name_abn[3] = {"EH1_abn","EH2_abn","EH3_abn"};

	const char* file_Name_abn[3] = {"EH1_abn_data.eps","EH2_abn_data.eps","EH3_abn_data.eps"};
	TCanvas *myC_abn[3];

	TGraphErrors *gr_an[3];

	TLegend *leg_an[3];
	const char* leg_Name_an[3] = {"EH1_a_{n}_data","EH2_a_{n}_data","EH3_a_{n}_data"};
	TGraphErrors *gr_bn[3];

	TLegend *leg_bn[3];
	const char* leg_Name_bn[3] = {"EH1_b_{n}_data","EH2_b_{n}_data","EH3_b_{n}_data"};


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

		y[Bin] = an[Hidx][kM];
		ex[Bin]=0.0;
		ey[Bin]=0.0;//sigma_an[Hidx][kM];
		}
		gr_an[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_an[Hidx]->GetYaxis()->SetRangeUser(-0.0125,0.0125);
		gr_an[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_an[Hidx]->SetMarkerColor(1);
		gr_an[Hidx]->SetLineColor(1);
		gr_an[Hidx]->SetLineWidth(2);
		gr_an[Hidx]->SetMarkerStyle(8);
		gr_an[Hidx]->SetMarkerSize(0.5);
		gr_an[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_an[Hidx]->GetYaxis()->SetTitle("a");

		gr_an[Hidx]->SetTitle("");

		gr_an[Hidx]->GetYaxis()->SetTitleOffset(0.22);
		gr_an[Hidx]->GetYaxis()->SetTitleSize(0.2);
		gr_an[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_an[Hidx]->GetYaxis()->SetLabelOffset(0.0);
		gr_an[Hidx]->GetYaxis()->CenterTitle();
		gr_an[Hidx]->GetYaxis()->SetNdivisions(505);
	
		gr_an[Hidx]->GetXaxis()->SetTitleOffset(0.7);
		gr_an[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_an[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr_an[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_an[Hidx]->Draw("APZ");

		leg_an[Hidx] = new TLegend(0.25, 0.65, 0.75, 0.98);
		leg_an[Hidx]->AddEntry(gr_an[Hidx],leg_Name_an[Hidx],"");
		leg_an[Hidx]->SetFillStyle(0);
		leg_an[Hidx]->SetBorderSize(0);
		leg_an[Hidx]->SetTextColor(kRed);
//		leg_an[Hidx]->Draw();
		}

	
		{
		myC_abn[Hidx]->cd(2);

		double x[nX],y[nX],ex[nX],ey[nX];

		for(int Bin=0;Bin<nX;Bin++)
		{
		x[Bin] = Bin/nBins;
		int kM = int(706.0*x[Bin]);

		y[Bin] = bn[Hidx][kM];
		ex[Bin]=0.0;
		ey[Bin]=0.0;//sigma_bn[Hidx][kM];
		}
		gr_bn[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_bn[Hidx]->GetYaxis()->SetRangeUser(-0.0125,0.0125);
		gr_bn[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_bn[Hidx]->SetMarkerColor(1);
		gr_bn[Hidx]->SetLineColor(1);
		gr_bn[Hidx]->SetLineWidth(2);
		gr_bn[Hidx]->SetMarkerStyle(8);
		gr_bn[Hidx]->SetMarkerSize(0.5);
		gr_bn[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_bn[Hidx]->GetYaxis()->SetTitle("b");

		gr_bn[Hidx]->SetTitle("");

		gr_bn[Hidx]->GetYaxis()->SetTitleOffset(0.22);
		gr_bn[Hidx]->GetYaxis()->SetTitleSize(0.2);
		gr_bn[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_bn[Hidx]->GetYaxis()->SetLabelOffset(0.0);
		gr_bn[Hidx]->GetYaxis()->CenterTitle();
		gr_bn[Hidx]->GetYaxis()->SetNdivisions(505);
	

		gr_bn[Hidx]->GetXaxis()->SetTitleOffset(0.83);
		gr_bn[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_bn[Hidx]->GetXaxis()->SetLabelSize(0.07);
		gr_bn[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_bn[Hidx]->Draw("APZ");
	
		leg_bn[Hidx] = new TLegend(0.25, 0.65, 0.75, 0.98);
		leg_bn[Hidx]->AddEntry(gr_bn[Hidx],leg_Name_bn[Hidx],"");
		leg_bn[Hidx]->SetFillStyle(0);
		leg_bn[Hidx]->SetBorderSize(0);
		leg_bn[Hidx]->SetTextColor(kRed);
//		leg_bn[Hidx]->Draw();
		}
	
		myC_abn[Hidx]->SaveAs(file_Name_abn[Hidx]);
}



//save to .root file

	 double an_t[3][2];
	 TFile  *F_an = new TFile("an_data.root","recreate");
	 TTree *Tree_an = new TTree("an","an");
	 Tree_an->Branch("an",an_t,"an_t[3][2]/D");
	 for(int Bin=0; Bin<NumOfBin;Bin++)
	 {
		 for(int Hidx=0;Hidx<3;Hidx++)
		 {
		 an_t[Hidx][0] = an[Hidx][Bin];
		 an_t[Hidx][1] =0.0;// sigma_an[Hidx][Bin];
		 }
		 Tree_an->Fill();
	 }
	 Tree_an->Write();

	 double bn_t[3][2];
	 TFile  *F_bn = new TFile("bn_data.root","recreate");
	 TTree *Tree_bn = new TTree("bn","bn");
	 Tree_bn->Branch("bn",bn_t,"bn_t[3][2]/D");
	 for(int Bin=0; Bin<NumOfBin;Bin++)
	 {
		 for(int Hidx=0;Hidx<3;Hidx++)
		 {
		 bn_t[Hidx][0] = bn[Hidx][Bin];
		 bn_t[Hidx][1] = 0.0;//sigma_bn[Hidx][Bin];
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
