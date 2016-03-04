

#include <math.h>
#include "TMinuit.h"

//double AVEP[3] = {0.98,0.98,0.951455};

double AVEP[3][5] = {{0.969,0.979,0.985,0.990,0.993},
		     {0.963,0.975,0.983,0.988,0.992},
		     {0.994488, 0.928517,  0.936187,  0.959021,  0.967247}
		    };

double R[3][24][5]={0.0};
double RD_R[3][24][5]={0.0};

Double_t ParResult[9],ParErrResult[9];
Double_t ParResult_EH1[9],ParErrResult_EH1[9];
Double_t ParResult_EH2[9],ParErrResult_EH2[9];
Double_t ParResult_EH3[9],ParErrResult_EH3[9];
Double_t ParResult_this[3][5][9],ParErrResult_this[3][5][9];



const double pi = 3.141592653;

double IndexCD[2] = {0,0};

const double Dm21 = 7.53e-23;//GeV^2;
const double Dm31 = 2.52e-21;//GeV^2;

double Dm[3][3] = {
	{0.0,-1*Dm21,-1*Dm31},
	{Dm21,0.0,Dm21-Dm31},
	{Dm31,Dm31-Dm21,0.0}};//Dm[i][j] = m^2i - m^2j,GeV^2

const double Th12 = 0.5*asin(sqrt(0.846));//theta 12
const double Th23 = 0.5*asin(sqrt(0.999));//theta 23
const double Th13 = 0.5*asin(sqrt(0.093));//theta 13


double U[3][3] = {
	{cos(Th12)*cos(Th13),sin(Th12)*cos(Th13),sin(Th13)},
	{-1*sin(Th12)*cos(Th23)-cos(Th12)*sin(Th13)*sin(Th23),cos(Th12)*cos(Th23)-sin(Th12)*sin(Th13)*sin(Th23),cos(Th13)*sin(Th23)},
	{sin(Th12)*sin(Th23)-cos(Th12)*sin(Th13)*cos(Th23),-1*cos(Th12)*sin(Th23)-sin(Th12)*sin(Th13)*cos(Th23),cos(Th13)*cos(Th23)}};

TComplex Tauab(int a,int b,double E,double L);//E:MeV,L:m
TComplex Mee(double E,double L,int i,int j);//E:MeV,L:m;e,mu,tau
TComplex See(double E,double L);//E:MeV,L:m
double ImSeeMee(double E,double L,int i,int j);//E:MeV,L:m;e,mu,tau
double Psur(double E,double L);//E:MeV,L:m
double Table_ImSeeMee[3][6][3][3][5];//[Hall][Rct][e/mu/tau][e/mu/tau]


double LatHall[3] = {22.598,22.606,22.612};//latitude of the three halls, degree, read from goole maps
	
	double Sab = 0.0;
	double C1 = 1.0;
	double C2 = 0.9;

	double PositionAD[8][3] = {
		{362.8329,	50.4206		,	-70.8174},
		{358.8044,	54.8583		,	-70.8135},
		{7.6518	,	-873.4882	,	-67.5241},
		{936.7486,	-1419.013	,	-66.4852},
		{941.4493,	-1415.305	,	-66.4966},
		{940.4612,	-1423.737	,	-66.4965},
		{945.1678,	-1420.0282	,	-66.4851},
		{9.5968	,	-879.149	,	-67.5202}};//in unit of meter, [ADNo.][X/Y/Z]
	double PositionRct[6][3] = {
		{359.2029	,	411.4896	,	-40.2308},
		{448.0015	,	411.0017	,	-40.2392},
		{-319.666	,	-540.7481	,	-39.7296},
		{-267.0633	,	-469.2051	,	-39.723},
		{-543.284	,	-954.7018	,	-39.7987},
		{-490.6906	,	-883.152	,	-39.7884}};//in unit of meter, [RctNo.][X/Y/Z]
	double PositionADn[8][3] = {0.0};
	double PositionHalln[3][3] = {0.0};//position of the hall, center of the ADs,[HallNo][X/Y/Z]
	double PositionRctn[6][3] = {0.0};
	double RotAngl = 0.0;//9.0*pi/180.0;//9 degrees of rotation

	double A_chi[3][6] = {0.0};//angle chi, [HallNo][RctNo],in unit of radius
	double A_theta[3][6] = {0.0};//angle theta, [HallNo][RctNo]
	double A_phi[3][6] = {0.0};//angle phi, [HallNo][RctNo]

	double Nx[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Ny[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Nz[3][6] = {0.0};//direction factor, [HallNo][RctNo]

	double up_limits[9] ;

	Double_t EveFrac_Hall[3][6][24]={0.0};
	Double_t EveFrac_Hall_Total[3][24] = {0.0};
	Double_t EveFrac_Hall_Ave[3][6]={0.0};
	Double_t EveFrac_Total[3] = {0.0};
	Double_t EveFrac[3][6];

	Double_t Baseline_Hall[3][6];//[Hall][Rct]
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds

	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
	const int NumOfBin = 17016;// (EndTime - StartTime)/WidthOfBin;//17016

	double IntExp(double E1,double E2, double P);//\int_E1^E2 exp(-P*E)dE
	Double_t AccFrac[8][5]={0.0};
	Double_t FastNFrac[8][5]={0.0};
	Double_t AmCFrac[8][5]={0.0};
	Double_t Li9Frac[8][5]={0.0};
	Double_t FastNP[8]={0.6536,0.6536,0.6959,0.6959,0.6453,0.6453,0.6453,0.6453};//nH note page79
	Double_t Li9_Frac_h[8],He8_Frac_h[8];
	Double_t AmCP[8];
	Double_t EPromptBin[6]={0.7,2.0,3.0,4.0,5.0,12.0};
	double Ave_Energy[5] = {2.55,3.36,4.30,5.28,6.57};
	double Ave_Energy_Save[5] = {2.55,3.36,4.30,5.28,6.57};
	double Ave_Energy_2[5] = {2.55+0.53,3.36+0.37,4.30+0.35,5.28+35,6.57+0.63};

	Int_t EBinIdx = 0;

	double Table_Chi2_3Site_5Bin[6]={0.0};
	double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
	double Table_Chi2_3Site_1Bin[6]={0.0};
	double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};

	int NOF_3Site_5Bin = 351; //3*5*24-8-1
	int NOF_SiteBySite_5Bin = 111; //5*24-8-1
	int NOF_3Site_1Bin = 66; // 3*24-6-1
	int NOF_SiteBySite_1Bin = 18; //24-6-1

	int NumOfIrr = 0;

void FitRatio_Paper_v1()
{
	
	//energy bin bkg. fractions
	TFile *Li9_F = new TFile("../../Input/Li9He8Spectrum/Li9_beta_neutron.root");
	TH1F *Li9_h = (TH1F*)Li9_F->Get("h");
	double Li9S_Sum=0.0;
	TAxis *axis_Li9 = Li9_h->GetXaxis();

	for(int Eidx=0;Eidx<5;Eidx++)
	{
		int bmin = axis_Li9->FindBin(EPromptBin[Eidx]); 
		int bmax = axis_Li9->FindBin(EPromptBin[Eidx+1]); 
		Li9_Frac_h[Eidx] = Li9_h->Integral(bmin,bmax);
		Li9S_Sum += Li9_h->Integral(bmin,bmax);
	}
		
	for(int Eidx=0;Eidx<5;Eidx++)
	{
		Li9_Frac_h[Eidx] = Li9_Frac_h[Eidx]/Li9S_Sum;
	}

	TFile *He8_F = new TFile("../../Input/Li9He8Spectrum/He8_beta_neutron.root");
	TH1F *He8_h = (TH1F*)He8_F->Get("h");
	double He8S_Sum=0.0;
	TAxis *axis_He8 = He8_h->GetXaxis();

	for(int Eidx=0;Eidx<5;Eidx++)
	{
		int bmin = axis_He8->FindBin(EPromptBin[Eidx]); 
		int bmax = axis_He8->FindBin(EPromptBin[Eidx+1]); 
		He8_Frac_h[Eidx] = He8_h->Integral(bmin,bmax);
		He8S_Sum += He8_h->Integral(bmin,bmax);
	}
		
	for(int Eidx=0;Eidx<5;Eidx++)
	{
		He8_Frac_h[Eidx] = He8_Frac_h[Eidx]/He8S_Sum;
	}

	for(int i=0;  i<8;i++)
	{
		AmCP[i]=0.9517;//nH note page 95
		for(int Eidx=0;Eidx<5;Eidx++)
		{
			Li9Frac[i][Eidx] = 0.9*Li9_Frac_h[Eidx] + 0.1*He8_Frac_h[Eidx];
		}
	}
	
	const char *AccS_file_Name[8] = {
		"../../Input/AccSpectrum/h1dAccBkg22_AS_org_EH1AD1.root","../../Input/AccSpectrum/h1dAccBkg22_AS_org_EH1AD2.root",
		"../../Input/AccSpectrum/h1dAccBkg22_AS_org_EH2AD1.root","../../Input/AccSpectrum/h1dAccBkg22_AS_org_EH2AD2.root",
		"../../Input/AccSpectrum/h1dAccBkg22_AS_org_EH3AD1.root","../../Input/AccSpectrum/h1dAccBkg22_AS_org_EH3AD2.root",
		"../../Input/AccSpectrum/h1dAccBkg22_AS_org_EH3AD3.root","../../Input/AccSpectrum/h1dAccBkg22_AS_org_EH3AD4.root"
	};
	const char *AccS_h_Name[8] = {
		"h1dAccBkg22_AS_org_EH1AD1","h1dAccBkg22_AS_org_EH1AD2",
		"h1dAccBkg22_AS_org_EH2AD1","h1dAccBkg22_AS_org_EH2AD2",
		"h1dAccBkg22_AS_org_EH3AD1","h1dAccBkg22_AS_org_EH3AD2",
		"h1dAccBkg22_AS_org_EH3AD3","h1dAccBkg22_AS_org_EH3AD4"
	};


	TFile *AccS_F[8];
	TH1F *AccS_TH1F[8];

	for(int Det=0;Det<8;Det++)
	{
		AccS_F[Det] = new TFile(AccS_file_Name[Det]);
		AccS_TH1F[Det] = (TH1F*)AccS_F[Det]->Get(AccS_h_Name[Det]);

		double AccS_Sum=0.0;
		for(int Eidx=0;Eidx<5;Eidx++)
		{
		TAxis *axis = AccS_TH1F[Det]->GetXaxis();
		int bmin = axis->FindBin(EPromptBin[Eidx]); 
		int bmax = axis->FindBin(EPromptBin[Eidx+1]); 
		AccFrac[Det][Eidx] = AccS_TH1F[Det]->Integral(bmin,bmax);
		AccS_Sum += AccS_TH1F[Det]->Integral(bmin,bmax);
		}
		
		for(int Eidx=0;Eidx<5;Eidx++)
		{
			AccFrac[Det][Eidx] = AccFrac[Det][Eidx]/AccS_Sum;
		}
	}

	for(int Det = 0;Det<8;Det++)
	{
		for(int Eidx=0;Eidx<5;Eidx++)
		{
			FastNFrac[Det][Eidx] = IntExp(EPromptBin[Eidx],EPromptBin[Eidx+1],FastNP[Eidx]);
			AmCFrac[Det][Eidx] = IntExp(EPromptBin[Eidx],EPromptBin[Eidx+1],AmCP[Eidx]);
		}
	}

	for(int Eidx=0;Eidx<5;Eidx++)
	{
		fprintf(stderr,"%4.2f - %4.2f  %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f \n", 
			EPromptBin[Eidx],EPromptBin[Eidx+1], 
			FastNFrac[0][Eidx],FastNFrac[2][Eidx],FastNFrac[4][Eidx],
			Li9Frac[0][Eidx],Li9Frac[2][Eidx],Li9Frac[4][Eidx],
			AmCFrac[0][Eidx],AmCFrac[2][Eidx],AmCFrac[4][Eidx],
			AccFrac[0][Eidx],AccFrac[2][Eidx],AccFrac[4][Eidx]);
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////fit preparation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<9;i++)
	{
		up_limits[i] = 1.0e-21;
	}

	TFile *F_EveFrac = new TFile("../Fraction.root");
	TTree *Tree_EveFrac = (TTree*)F_EveFrac->Get("Fraction");
	Tree_EveFrac->SetBranchAddress("Fraction",EveFrac);

	for(int N24 = 0;N24<24;N24++)
	{
		Tree_EveFrac->GetEntry(N24);
		for(int Rct = 0;Rct<6;Rct++)
		{
			EveFrac_Hall[0][Rct][N24] = EveFrac[0][Rct];
			EveFrac_Hall[1][Rct][N24] = EveFrac[1][Rct];
			EveFrac_Hall[2][Rct][N24] = EveFrac[2][Rct];
			for(int i=0;i<3;i++)
			{
				EveFrac_Hall_Ave[i][Rct] += EveFrac_Hall[i][Rct][N24];
				EveFrac_Total[i] += EveFrac_Hall[i][Rct][N24];
				EveFrac_Hall_Total[i][N24] += EveFrac_Hall[i][Rct][N24];
			}
		}
	}

	//fprintf(stderr,"Event fraction:\n");
	//fprintf(stderr,"%5s %12s %12s %12s %12s %12s %12s %12s \n","Hall","D1","D2","L1","L2","L3","L4","Total");
	for(int Hallidx=0;Hallidx<3;Hallidx++)
	{
		//fprintf(stderr,"%5d %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f \n",Hallidx,EveFrac_Hall_Ave[Hallidx][0],EveFrac_Hall_Ave[Hallidx][1],
			//EveFrac_Hall_Ave[Hallidx][2],EveFrac_Hall_Ave[Hallidx][3],EveFrac_Hall_Ave[Hallidx][4],EveFrac_Hall_Ave[Hallidx][5],EveFrac_Total[Hallidx]);
			
	}

	//fprintf(stderr,"Positions after rotation:\n");
	for(int ADidx = 0;ADidx<8;ADidx++)
	{
		PositionADn[ADidx][0] = PositionAD[ADidx][0]*cos(RotAngl)+PositionAD[ADidx][1]*sin(RotAngl);//x'=xcos + ysin
		PositionADn[ADidx][1] = -1.0*PositionAD[ADidx][0]*sin(RotAngl)+PositionAD[ADidx][1]*cos(RotAngl);//y'=-xsin + ycos
		PositionADn[ADidx][2] = PositionAD[ADidx][2];
		//cout<<PositionADn[ADidx][0]<<"      "<<PositionADn[ADidx][1]<<"      "<<PositionADn[ADidx][2]<<endl;
	}

	for(int Rctidx = 0;Rctidx<6;Rctidx++)
	{
		PositionRctn[Rctidx][0] = PositionRct[Rctidx][0]*cos(RotAngl)+PositionRct[Rctidx][1]*sin(RotAngl);//x'=xcos + ysin
		PositionRctn[Rctidx][1] = -1*PositionRct[Rctidx][0]*sin(RotAngl)+PositionRct[Rctidx][1]*cos(RotAngl);//y'=-xsin + ycos
		PositionRctn[Rctidx][2] = PositionRct[Rctidx][2];
		//cout<<PositionRctn[Rctidx][0]<<"      "<<PositionRctn[Rctidx][1]<<"      "<<PositionRctn[Rctidx][2]<<endl;
	}

	for(int i=0;i<3;i++)
	{
		PositionHalln[0][i] = 0.5*(PositionADn[0][i]+PositionADn[1][i]);
		PositionHalln[1][i] = 0.5*(PositionADn[2][i]+PositionADn[7][i]);
		PositionHalln[2][i] = 0.25*(PositionADn[3][i]+PositionADn[4][i]+PositionADn[5][i]+PositionADn[6][i]);
	}

	////cout<<acos(-0.5)<<"   "<<120.0*pi/180.0<<endl;
	
	////cout<<"Hall			Rct			theta			phi			chi			Nx			Ny			Nz"<<endl;			
	//fprintf(stderr,"\n");
	//fprintf(stderr,"%5s %5s %12s %12s %12s %12s %12s %12s \n","Hall","Rct","theta","phi","chi","Nx","Ny","Nz");
	for(int Hallidx = 0;Hallidx<3;Hallidx++)
	{
		for(int Rctidx = 0;Rctidx<6;Rctidx++)
		{
			double D_beam[3] = {0.0};//beam direction
			for(int i=0;i<3;i++)
			{
				D_beam[i] = PositionHalln[Hallidx][i] -  PositionRctn[Rctidx][i];
			}
			A_theta[Hallidx][Rctidx] = acos(D_beam[2]/sqrt(pow(D_beam[0],2.0)+pow(D_beam[1],2.0)+pow(D_beam[2],2.0)));
			if(D_beam[0]<0)
			{
				A_phi[Hallidx][Rctidx] = acos(D_beam[1]/sqrt(pow(D_beam[0],2.0)+pow(D_beam[1],2.0)));
			}
			else
			{
				A_phi[Hallidx][Rctidx] = 2*pi - acos(D_beam[1]/sqrt(pow(D_beam[0],2.0)+pow(D_beam[1],2.0)));
			}
			A_chi[Hallidx][Rctidx] = 0.5*pi - LatHall[Hallidx]*pi/180.0;
			Nx[Hallidx][Rctidx] = cos(A_chi[Hallidx][Rctidx])*sin(A_theta[Hallidx][Rctidx])*cos(A_phi[Hallidx][Rctidx]) + sin(A_chi[Hallidx][Rctidx])*cos(A_theta[Hallidx][Rctidx]);
			Ny[Hallidx][Rctidx] = sin(A_theta[Hallidx][Rctidx])*sin(A_phi[Hallidx][Rctidx]);
			Nz[Hallidx][Rctidx] = -1*sin(A_chi[Hallidx][Rctidx])*sin(A_theta[Hallidx][Rctidx])*cos(A_phi[Hallidx][Rctidx]) + cos(A_chi[Hallidx][Rctidx])*cos(A_theta[Hallidx][Rctidx]);
			//fprintf(stderr,"%5d %5d %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f \n", Hallidx, Rctidx, A_theta[Hallidx][Rctidx]*180.0/pi, A_phi[Hallidx][Rctidx]*180.0/pi, A_chi[Hallidx][Rctidx]*180.0/pi, Nx[Hallidx][Rctidx], Ny[Hallidx][Rctidx], Nz[Hallidx][Rctidx]);
		}
	}

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int Rct = 0;Rct<6;Rct++)
		{
			Baseline_Hall[Hidx][Rct] = sqrt(pow(PositionHalln[Hidx][0]-PositionRctn[Rct][0],2.0)+pow(PositionHalln[Hidx][1]-PositionRctn[Rct][1],2.0)+pow(PositionHalln[Hidx][2]-PositionRctn[Rct][2],2.0));
		}
	}

	cout<<"ImSeeMee:  "<<endl;
	for(int Eidx=0;Eidx<5;Eidx++)
	{
		//cout<<"Energy Bin: "<<Eidx<<endl;
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int Rct = 0;Rct<6;Rct++)
		{
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
			Table_ImSeeMee[Hidx][Rct][i][j][Eidx] = ImSeeMee(Ave_Energy[Eidx],Baseline_Hall[Hidx][Rct],i,j);
				}
			}
			
			//fprintf(stderr,"&  %7.4f & %7.4f & %7.4f  & %7.4f & %7.4f &  %7.4f  \\\\ \\hline \n",
				//Table_ImSeeMee[Hidx][Rct][0][0][Eidx],Table_ImSeeMee[Hidx][Rct][1][1][Eidx],Table_ImSeeMee[Hidx][Rct][2][2][Eidx],
				//Table_ImSeeMee[Hidx][Rct][0][1][Eidx],Table_ImSeeMee[Hidx][Rct][0][2][Eidx],Table_ImSeeMee[Hidx][Rct][1][2][Eidx]);
		}
	}
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	Double_t CrossSection = 0.94;//Averaged cross-section, in unit of 1e-43 cm^2;

	Double_t Np = 1.43;//Total number of target protons in AD1,AD2, in unit of 1e30

	//IBD candidate
	Double_t IBDInOneDay[8][24][5];
	Double_t IBD_t[8][5];
	memset(IBDInOneDay,0.0,sizeof(IBDInOneDay));
	TFile *F_IBD = new TFile("../IBD/IBDInOneDay.root");
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
			for(int Eidx=0;Eidx<5;Eidx++)
			{
			IBDInOneDay[Det][N24][Eidx] = IBD_t[Det][Eidx];
			}
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

	Double_t AlphaBeta_t[2];
	Double_t AlphaBetaInOneDay[2][24];
	memset(AlphaBetaInOneDay,0.0,sizeof(AlphaBetaInOneDay));

	TFile *F_AlphaBeta = new TFile("../AlphaBeta.root");
	TTree *Tree_AlphaBeta = (TTree*)F_AlphaBeta->Get("AlphaBeta");
	Tree_AlphaBeta->SetBranchAddress("AlphaBeta",AlphaBeta_t);

	for(int Bin=0;Bin<24;Bin++)
	{
		Tree_AlphaBeta->GetEntry(Bin);
		AlphaBetaInOneDay[0][Bin] = AlphaBeta_t[0];
		AlphaBetaInOneDay[1][Bin] = AlphaBeta_t[1];
	}
	//
	double RD_Power = 0.009;
	double RD_Eff = 0.00088;


	//////////////EH1////////////////////////////////////////////////
	int HallID = 0;

	Double_t M[24][5];//={0.0};
	memset(M,0.0,sizeof(M));
	Double_t RD_M[24][5];//={0.0};
	memset(RD_M,0.0,sizeof(RD_M));
	Double_t NBar[24][5];//
	memset(NBar,0.0,sizeof(NBar));
	Double_t RD_NBar[24][5];//
	memset(RD_NBar,0.0,sizeof(RD_NBar));

	for(int Eidx=0;Eidx<5;Eidx++)
	{
	for(int N24=0;N24<24;N24++)
	{
		for(int Det=0;Det<2;Det++)
		{
			M[N24][Eidx]+= IBDInOneDay[Det][N24][Eidx]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]+AccInOneDay[Det][N24]*AccFrac[Det][Eidx]+Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]+FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx])/MultiEffInOneDay[Det][N24];
			RD_M[N24][Eidx] += (IBDInOneDay[Det][N24][Eidx]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]*AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccFrac[Det][Eidx]*AccInOneDay[Det][N24]*AccFrac[Det][Eidx],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]*Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx]*FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);


		}
		RD_M[N24][Eidx] += pow(M[N24][Eidx]*RD_Eff,2.0);

		RD_M[N24][Eidx] = sqrt(RD_M[N24][Eidx])/M[N24][Eidx];
		Double_t temp=0.0,temp2=0.0;
		for(int Rct=0;Rct<6;Rct++)
		{
			temp += FractionInOneDay[HallID][Rct][N24];
			temp2 += pow(FractionInOneDay[HallID][Rct][N24],2.0);
		}

		NBar[N24][Eidx] = 1.0e-17*Np*CrossSection*temp/(4.0*pi);
		//RD_NBar[N24][Eidx] = RD_Power;

		R[0][N24][Eidx] = M[N24][Eidx]/NBar[N24][Eidx];
		RD_R[0][N24][Eidx] = sqrt(pow(RD_M[N24][Eidx],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
		//cout<<N24<<"   "<<R[0][N24][Eidx]<<"   "<<RD_R[0][N24][Eidx]<<"   "<<endl;
	}
	}
	//////////////EH2////////////////////////////////////////////////
	HallID = 1;
	for(int i=0;i<24;i++)
	{
	for(int Eidx=0;Eidx<5;Eidx++)
	{
		M[i][Eidx]=0.0;
		RD_M[i][Eidx]=0.0;
		NBar[i][Eidx]=0.0;
		RD_NBar[i][Eidx]=0.0;
	}
	}

	for(int Eidx=0;Eidx<5;Eidx++)
	{
	for(int N24=0;N24<24;N24++)
	{
		for(int Det=2;Det<4;Det++)
		{
			M[N24][Eidx] += IBDInOneDay[Det][N24][Eidx]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]+AccInOneDay[Det][N24]*AccFrac[Det][Eidx]+Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]+FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx])/MultiEffInOneDay[Det][N24];
			RD_M[N24][Eidx] += (IBDInOneDay[Det][N24][Eidx]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]*AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccFrac[Det][Eidx]*AccInOneDay[Det][N24]*AccFrac[Det][Eidx],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]*Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx]*FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);


		}
		RD_M[N24][Eidx] += pow(M[N24][Eidx]*RD_Eff,2.0);

		RD_M[N24][Eidx] = sqrt(RD_M[N24][Eidx])/M[N24][Eidx];
		Double_t temp=0.0,temp2=0.0;
		for(int Rct=0;Rct<6;Rct++)
		{
			temp += FractionInOneDay[HallID][Rct][N24];
			temp2 += pow(FractionInOneDay[HallID][Rct][N24],2.0);
		}

		NBar[N24][Eidx] = 1.0e-17*Np*CrossSection*temp/(4.0*pi);
		//RD_NBar[N24][Eidx] = RD_Power;

		R[1][N24][Eidx] = M[N24][Eidx]/NBar[N24][Eidx];
		RD_R[1][N24][Eidx] = sqrt(pow(RD_M[N24][Eidx],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
		//cout<<N24<<"   "<<R[N24]<<"   "<<RD_R[N24]<<"   "<<RD_M[N24][Eidx]<<"   "<<endl;
	}
	}
	/////////////////////////////////EH3////////////////////////////////////////////
	HallID = 2;
	Double_t Mf[24][5]={0.0};//={0.0};
	Double_t RD_Mf[24][5]={0.0};//={0.0};
	
	Double_t Ma[24][5]={0.0};//={0.0};
	Double_t RD_Ma[24][5]={0.0};//={0.0};
	
	Double_t Mb[24][5]={0.0};//={0.0};
	Double_t RD_Mb[24][5]={0.0};//={0.0};

	cout<<"EH3:"<<endl;
	for(int Eidx=0;Eidx<5;Eidx++)
	{
	for(int N24=0;N24<24;N24++)
	{
		for(int Det=4;Det<8;Det++)
		{
			Mf[N24][Eidx] += IBDInOneDay[Det][N24][Eidx]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]+AccInOneDay[Det][N24]*AccFrac[Det][Eidx]+Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]+FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx])/MultiEffInOneDay[Det][N24];
			RD_Mf[N24][Eidx] += (IBDInOneDay[Det][N24][Eidx]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]*AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccFrac[Det][Eidx]*AccInOneDay[Det][N24]*AccFrac[Det][Eidx],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]*Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx]*FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);
		}

		for(int Det=0;Det<2;Det++)
		{
			Ma[N24][Eidx] += IBDInOneDay[Det][N24][Eidx]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]+AccInOneDay[Det][N24]*AccFrac[Det][Eidx]+Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]+FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx])/MultiEffInOneDay[Det][N24];
			RD_Ma[N24][Eidx] += (IBDInOneDay[Det][N24][Eidx]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]*AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccFrac[Det][Eidx]*AccInOneDay[Det][N24]*AccFrac[Det][Eidx],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]*Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx]*FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);
		}

		for(int Det=2;Det<4;Det++)
		{
			Mb[N24][Eidx] += IBDInOneDay[Det][N24][Eidx]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]+AccInOneDay[Det][N24]*AccFrac[Det][Eidx]+Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]+FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx])/MultiEffInOneDay[Det][N24];
			RD_Mb[N24][Eidx] += (IBDInOneDay[Det][N24][Eidx]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx]*AmCInOneDay[Det][N24]*AmCFrac[Det][Eidx],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccFrac[Det][Eidx]*AccInOneDay[Det][N24]*AccFrac[Det][Eidx],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx]*Li9InOneDay[Det][N24]*Li9Frac[Det][Eidx],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx]*FastNInOneDay[Det][N24]*FastNFrac[Det][Eidx],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);
		}

		RD_Mf[N24][Eidx] += pow(Mf[N24][Eidx]*RD_Eff,2.0);
		RD_Mf[N24][Eidx] = sqrt(RD_Mf[N24][Eidx])/Mf[N24][Eidx];

		RD_Ma[N24][Eidx] += pow(Ma[N24][Eidx]*RD_Eff,2.0);
		RD_Ma[N24][Eidx] = sqrt(RD_Ma[N24][Eidx])/Ma[N24][Eidx];

		RD_Mb[N24][Eidx] += pow(Mb[N24][Eidx]*RD_Eff,2.0);
		RD_Mb[N24][Eidx] = sqrt(RD_Mb[N24][Eidx])/Mb[N24][Eidx];

		R[2][N24][Eidx] = Mf[N24][Eidx]/((AlphaBetaInOneDay[0][N24]-0.0000)*Ma[N24][Eidx]+(AlphaBetaInOneDay[1][N24]+0.00)*Mb[N24][Eidx]);

		RD_R[2][N24][Eidx] = sqrt(pow(RD_Mf[N24][Eidx],2.0)+(pow(AlphaBetaInOneDay[0][N24]*Ma[N24][Eidx]*RD_Ma[N24][Eidx],2.0)
			+pow(AlphaBetaInOneDay[1][N24]*Mb[N24][Eidx]*RD_Mb[N24][Eidx],2.0))/pow(AlphaBetaInOneDay[0][N24]*Ma[N24][Eidx]+AlphaBetaInOneDay[1][N24]*Mb[N24][Eidx],2.0)+pow(0.047*RD_Power,2.0));
		//cout<<N24<<"   "<<R[2][N24][Eidx]<<"   "<<RD_R[2][N24][Eidx]<<endl;
	}
	}
	
	//////Normalize EH1, EH2 and EH3 to 1.0
	Double_t MeanRatio[3][5] = {0.0};
	for(int Eidx=0;Eidx<5;Eidx++)
	{
	for(int i=0;i<24;i++)
	{
		MeanRatio[0][Eidx] += R[0][i][Eidx];
		MeanRatio[1][Eidx] += R[1][i][Eidx];
		MeanRatio[2][Eidx] += R[2][i][Eidx];
	}
	for(int i=0;i<24;i++)
	{
		R[0][i][Eidx]=AVEP[0][Eidx]*24.0*R[0][i][Eidx]/MeanRatio[0][Eidx];
		R[1][i][Eidx]=AVEP[1][Eidx]*24.0*R[1][i][Eidx]/MeanRatio[1][Eidx];
		R[2][i][Eidx]=AVEP[2][Eidx]*24.0*R[2][i][Eidx]/MeanRatio[2][Eidx];
	}
	}

	/////////////////////////////////////use the ratio from the other macro////////////////////////////////////////////////////////////
	Double_t Ratio_t[3][5];
    TFile *F_Ratio = new TFile("RatioInOneDay.root");
    TTree *Tree_Ratio = (TTree*)F_Ratio->Get("RatioInOneDay");
    Tree_Ratio->SetBranchAddress("RatioInOneDay",Ratio_t);

    for(int N24=0;N24<24;N24++)
    {

        Tree_Ratio->GetEntry(N24);
        for(int Det=0;Det<3;Det++)
        {
			for(int Eidx=0;Eidx<5;Eidx++)
			{
            R[Det][N24][Eidx] = Ratio_t[Det][Eidx];
			}
        }
    }
	/*
	Double_t RD_Ratio_t[3][5];
    TFile *F_RD_Ratio = new TFile("RD_RatioInOneDay.root");
    TTree *Tree_RD_Ratio = (TTree*)F_RD_Ratio->Get("RD_RatioInOneDay");
    Tree_RD_Ratio->SetBranchAddress("RD_RatioInOneDay",RD_Ratio_t);

    for(int N24=0;N24<24;N24++)
    {

        Tree_RD_Ratio->GetEntry(N24);
        for(int Det=0;Det<3;Det++)
        {
			for(int Eidx=0;Eidx<5;Eidx++)
			{
            RD_R[Det][N24][Eidx] = RD_Ratio_t[Det][Eidx];
			}
        }
    }
	*/

	
	////////////////////////////////////////////////////Fit////////////////////////////////////////////////////////////////////////////////////////////////////
	//0		1	2	3	4	5	6	7		
	//A11	A12	A2  A31	A32	A4	B1	B2  
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
   TMinuit *gMinuit = new TMinuit(9);  //initialize TMinuit with a maximum of 7 params
   gMinuit->SetFCN(ChiSquare);

   Double_t arglist[10];
   Int_t ierflg = 0;

   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   Double_t vstart[9] = {0};//{-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0};
   Double_t step[9] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01,0.01};
   gMinuit->mnparm(0, "A11", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A12", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A31", vstart[3], step[3], 0,0,ierflg);
   gMinuit->mnparm(4, "A32", vstart[4], step[4], 0,0,ierflg);
   gMinuit->mnparm(5, "A4", vstart[5], step[5], 0,0,ierflg);
   gMinuit->mnparm(6, "B1", vstart[6], step[6], 0,0,ierflg);
   gMinuit->mnparm(7, "B2", vstart[7], step[7], 0,0,ierflg);
   gMinuit->mnparm(8, "T0", vstart[8], step[8], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 2000;
   arglist[1] = 40000.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

   arglist[0] = 2000;
   gMinuit->mnexcm("IMProve", arglist ,1,ierflg);

// Print results

   //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6
   
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   Table_Chi2_3Site_5Bin[0]=amin;

   gMinuit->mnprin(3,amin);

   //0		1	2	3	4	5	6	7		
	//A11	A12	A2  A31	A32	A4	B1	B2  
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
   //Double_t ParResult[8],ParErrResult[8];
   for(int i=0;i<9;i++)
   {
	   Double_t v,ev;
	   gMinuit->GetParameter(i,v,ev);
	   ParResult[i]=v;
	   ParErrResult[i]=ev;
   }

   

   ////////////////////////////////////////////////////Fit site by site (EH1 only)////////////////////////////////////////////////////////////////////////////////////////////////////
   TMinuit *gMinuit_EH1 = new TMinuit(9);  //initialize TMinuit with a maximum of 8 params
   gMinuit_EH1->SetFCN(ChiSquare_EH1);

   Double_t arglist_EH1[10];
   Int_t ierflg_EH1 = 0;

   arglist_EH1[0] = 1;
   gMinuit_EH1->mnexcm("SET ERR", arglist_EH1 ,1,ierflg_EH1);

// Set starting values and step_EH1 sizes for parameters
   Double_t vstart_EH1[9] = {0};//{-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0};
   Double_t step_EH1[9] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01,0.01};
   gMinuit_EH1->mnparm(0, "A11", vstart_EH1[0], step_EH1[0], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(1, "A12", vstart_EH1[1], step_EH1[1], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(2, "A2", vstart_EH1[2], step_EH1[2], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(3, "A31", vstart_EH1[3], step_EH1[3], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(4, "A32", vstart_EH1[4], step_EH1[4], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(5, "A4", vstart_EH1[5], step_EH1[5], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(6, "B1", vstart_EH1[6], step_EH1[6], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(7, "B2", vstart_EH1[7], step_EH1[7], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(8, "T0", vstart_EH1[8], step_EH1[8], 0,0,ierflg_EH1);

// Now ready for minimization step_EH1
   arglist_EH1[0] = 2000;
   arglist_EH1[1] = 40000.;
   gMinuit_EH1->mnexcm("MIGRAD", arglist_EH1 ,2,ierflg_EH1);

   arglist_EH1[0] = 2000;
   gMinuit_EH1->mnexcm("IMProve", arglist_EH1 ,1,ierflg_EH1);

// Print results
    //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6
   Double_t amin_EH1,edm_EH1,errdef_EH1;
   Int_t nvpar_EH1,nparx_EH1,icstat_EH1;
   gMinuit_EH1->mnstat(amin_EH1,edm_EH1,errdef_EH1,nvpar_EH1,nparx_EH1,icstat_EH1);
   Table_Chi2_SiteBySite_5Bin[0][0]=amin_EH1;

   gMinuit_EH1->mnprin(3,amin_EH1);

   
   for(int i=0;i<9;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH1->GetParameter(i,v,ev);
	   ParResult_EH1[i]=v;
	   ParErrResult_EH1[i]=ev;
   }


   
  ////////////////////////////////////////////////////Fit site by site (EH2 only)////////////////////////////////////////////////////////////////////////////////////////////////////
   TMinuit *gMinuit_EH2 = new TMinuit(9);  //initialize TMinuit with a maximum of 8 params
   gMinuit_EH2->SetFCN(ChiSquare_EH2);

   Double_t arglist_EH2[10];
   Int_t ierflg_EH2 = 0;

   arglist_EH2[0] = 1;
   gMinuit_EH2->mnexcm("SET ERR", arglist_EH2 ,1,ierflg_EH2);

// Set starting values and step_EH2 sizes for parameters
   Double_t vstart_EH2[9] = {0};//{-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0};
   Double_t step_EH2[9] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01,0.01};
   gMinuit_EH2->mnparm(0, "A11", vstart_EH2[0], step_EH2[0], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(1, "A12", vstart_EH2[1], step_EH2[1], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(2, "A2", vstart_EH2[2], step_EH2[2], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(3, "A31", vstart_EH2[3], step_EH2[3], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(4, "A32", vstart_EH2[4], step_EH2[4], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(5, "A4", vstart_EH2[5], step_EH2[5], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(6, "B1", vstart_EH2[6], step_EH2[6], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(7, "B2", vstart_EH2[7], step_EH2[7], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(8, "T0", vstart_EH2[8], step_EH2[8], 0,0,ierflg_EH2);

// Now ready for minimization step_EH2
   arglist_EH2[0] = 2000;
   arglist_EH2[1] = 40000.;
   gMinuit_EH2->mnexcm("MIGRAD", arglist_EH2 ,2,ierflg_EH2);

   arglist_EH2[0] = 2000;
   gMinuit_EH2->mnexcm("IMProve", arglist_EH2 ,1,ierflg_EH2);

// Print results
    //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6
   Double_t amin_EH2,edm_EH2,errdef_EH2;
   Int_t nvpar_EH2,nparx_EH2,icstat_EH2;
   gMinuit_EH2->mnstat(amin_EH2,edm_EH2,errdef_EH2,nvpar_EH2,nparx_EH2,icstat_EH2);
   Table_Chi2_SiteBySite_5Bin[0][0]=amin_EH2;

   gMinuit_EH2->mnprin(3,amin_EH2);

   
   for(int i=0;i<9;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH2->GetParameter(i,v,ev);
	   ParResult_EH2[i]=v;
	   ParErrResult_EH2[i]=ev;
   }
   

////////////////////////////////////////////////////Fit site by site (EH3 only)////////////////////////////////////////////////////////////////////////////////////////////////////
   TMinuit *gMinuit_EH3 = new TMinuit(9);  //initialize TMinuit with a maximum of 8 params
   gMinuit_EH3->SetFCN(ChiSquare_EH3);

   Double_t arglist_EH3[10];
   Int_t ierflg_EH3 = 0;

   arglist_EH3[0] = 1;
   gMinuit_EH3->mnexcm("SET ERR", arglist_EH3 ,1,ierflg_EH3);

// Set starting values and step_EH3 sizes for parameters
   Double_t vstart_EH3[9] = {0};//{-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0};
   Double_t step_EH3[9] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01,0.01};
   gMinuit_EH3->mnparm(0, "A11", vstart_EH3[0], step_EH3[0], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(1, "A12", vstart_EH3[1], step_EH3[1], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(2, "A2", vstart_EH3[2], step_EH3[2], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(3, "A31", vstart_EH3[3], step_EH3[3], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(4, "A32", vstart_EH3[4], step_EH3[4], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(5, "A4", vstart_EH3[5], step_EH3[5], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(6, "B1", vstart_EH3[6], step_EH3[6], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(7, "B2", vstart_EH3[7], step_EH3[7], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(8, "T0", vstart_EH3[8], step_EH3[8], 0,0,ierflg_EH3);
// Now ready for minimization step_EH3
   arglist_EH3[0] = 2000;
   arglist_EH3[1] = 40000.;
   gMinuit_EH3->mnexcm("MIGRAD", arglist_EH3 ,2,ierflg_EH3);

   arglist_EH3[0] = 2000;
   gMinuit_EH3->mnexcm("IMProve", arglist_EH3 ,1,ierflg_EH3);

// Print results
    //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6
   Double_t amin_EH3,edm_EH3,errdef_EH3;
   Int_t nvpar_EH3,nparx_EH3,icstat_EH3;
   gMinuit_EH3->mnstat(amin_EH3,edm_EH3,errdef_EH3,nvpar_EH3,nparx_EH3,icstat_EH3);
   Table_Chi2_SiteBySite_5Bin[0][0]=amin_EH3;

   gMinuit_EH3->mnprin(3,amin_EH3);

   
   for(int i=0;i<9;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH3->GetParameter(i,v,ev);
	   ParResult_EH3[i]=v;
	   ParErrResult_EH3[i]=ev;
   }

   ////////////////////////////////This plot only//////////////////////////////////////////////
   for(int Hidx=0;Hidx<3;Hidx++)
   {
	   for(EBinIdx=0;EBinIdx<5;EBinIdx++)
	   {
	   TMinuit *gMinuit_this = new TMinuit(9);  //initialize TMinuit with a maximum of 8 params
	   if(Hidx==0)
	   {
   gMinuit_this->SetFCN(ChiSquare_EH1_this);
	   }
	   if(Hidx==1)
	   {
   gMinuit_this->SetFCN(ChiSquare_EH2_this);
	   }
	   if(Hidx==2)
	   {
   gMinuit_this->SetFCN(ChiSquare_EH3_this);
	   }

   Double_t arglist_this[10];
   Int_t ierflg_this = 0;

   arglist_this[0] = 1;
   gMinuit_this->mnexcm("SET ERR", arglist_this ,1,ierflg_this);

// Set starting values and step_this sizes for parameters
   Double_t vstart_this[9] = {0};//{-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0};
   Double_t step_this[9] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01,0.01};
   gMinuit_this->mnparm(0, "A11", vstart_this[0], step_this[0], 0,0,ierflg_this);
   gMinuit_this->mnparm(1, "A12", vstart_this[1], step_this[1], 0,0,ierflg_this);
   gMinuit_this->mnparm(2, "A2", vstart_this[2], step_this[2], 0,0,ierflg_this);
   gMinuit_this->mnparm(3, "A31", vstart_this[3], step_this[3], 0,0,ierflg_this);
   gMinuit_this->mnparm(4, "A32", vstart_this[4], step_this[4], 0,0,ierflg_this);
   gMinuit_this->mnparm(5, "A4", vstart_this[5], step_this[5], 0,0,ierflg_this);
   gMinuit_this->mnparm(6, "B1", vstart_this[6], step_this[6], 0,0,ierflg_this);
   gMinuit_this->mnparm(7, "B2", vstart_this[7], step_this[7], 0,0,ierflg_this);
   gMinuit_this->mnparm(8, "B2", vstart_this[8], step_this[8], 0,0,ierflg_this);


// Now ready for minimization step_this
   arglist_this[0] = 2000;
   arglist_this[1] = 8000.;
   gMinuit_this->mnexcm("MIGRAD", arglist_this ,2,ierflg_this);

   arglist_this[0] = 2000;
   gMinuit_this->mnexcm("IMProve", arglist_this ,1,ierflg_this);

// Print results
    //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6
   Double_t amin_this,edm_this,errdef_this;
   Int_t nvpar_this,nparx_this,icstat_this;
   gMinuit_this->mnstat(amin_this,edm_this,errdef_this,nvpar_this,nparx_this,icstat_this);
   //Table_Chi2_SiteBySite_5Bin[0][0]=amin_this;

   gMinuit_this->mnprin(3,amin_this);

   
   for(int i=0;i<9;i++)
   {
	   Double_t v,ev;
	   gMinuit_this->GetParameter(i,v,ev);
	   ParResult_this[Hidx][EBinIdx][i]=v;
	   ParErrResult_this[Hidx][EBinIdx][i]=ev;
   }
	   }
   }
   ////////////////////////////////////////////////////////////////////////////////////////////
   ///////////print
	//0		1	2	3	4	5	6	7		
	//A11	A12	A2  A31	A32	A4	B1	B2  
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18

   fprintf(stderr,"fit result(three sites):\n");
   fprintf(stderr,"$a^X_R$/$10^{-21}$GeV           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[0],ParErrResult[0],ParResult_EH1[0],ParErrResult_EH1[0],ParResult_EH2[0],ParErrResult_EH2[0],ParResult_EH3[0],ParErrResult_EH3[0]);
   fprintf(stderr,"$c^{TX}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[1],ParErrResult[1],ParResult_EH1[1],ParErrResult_EH1[1],ParResult_EH2[1],ParErrResult_EH2[1],ParResult_EH3[1],ParErrResult_EH3[1]);
   fprintf(stderr,"$c^{XZ}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[2],ParErrResult[2],ParResult_EH1[2],ParErrResult_EH1[2],ParResult_EH2[2],ParErrResult_EH2[2],ParResult_EH3[2],ParErrResult_EH3[2]);
   fprintf(stderr,"$a^Y_R$/$10^{-21}$GeV           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[3],ParErrResult[3],ParResult_EH1[3],ParErrResult_EH1[3],ParResult_EH2[3],ParErrResult_EH2[3],ParResult_EH3[3],ParErrResult_EH3[3]);
   fprintf(stderr,"$c^{TY}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[4],ParErrResult[4],ParResult_EH1[4],ParErrResult_EH1[4],ParResult_EH2[4],ParErrResult_EH2[4],ParResult_EH3[4],ParErrResult_EH3[4]);
   fprintf(stderr,"$c^{YZ}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[5],ParErrResult[5],ParResult_EH1[5],ParErrResult_EH1[5],ParResult_EH2[5],ParErrResult_EH2[5],ParResult_EH3[5],ParErrResult_EH3[5]);
   fprintf(stderr,"$c^{XX}_R-c^{YY}_R$/$10^{-18}$  &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[6],ParErrResult[6],ParResult_EH1[6],ParErrResult_EH1[6],ParResult_EH2[6],ParErrResult_EH2[6],ParResult_EH3[6],ParErrResult_EH3[6]);
   fprintf(stderr,"$c^{XY}_R$/$10^{-18}$  &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[7],ParErrResult[7],ParResult_EH1[7],ParErrResult_EH1[7],ParResult_EH2[7],ParErrResult_EH2[7],ParResult_EH3[7],ParErrResult_EH3[7]);

	
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
   
   ////////////////////////////////////////////////////Draw////////////////////////////////////////////////////////////////////////////////////////////////////
	const Int_t n = 24;

	//////points
	TCanvas *myC[3][5];
	TGraphErrors *gr[3][5];
	TLegend* leg[3][5];
	TLegend* leg2[3][5];
	TF1 *f_Plot[3][5];
	TF1 *f_Plot_single[3][5];
	TF1 *f_Plot_single_1[3][5];
	TF1 *f_Plot_single_2[3][5];
	TF1 *f_Plot_this[3][5];
	const char *c_Name[3][5]={	{"EH1: 0.7 < E_{p} < 2MeV","EH1: 2 < E_{p} < 3MeV","EH1: 3 < E_{p} < 4MeV","EH1: 4 < E_{p} < 5MeV","EH1: 5 < E_{p} < 12MeV"},
								{"EH2: 0.7 < E_{p} < 2MeV","EH2: 2 < E_{p} < 3MeV","EH2: 3 < E_{p} < 4MeV","EH2: 4 < E_{p} < 5MeV","EH2: 5 < E_{p} < 12MeV"},
								{"EH3: 0.7 < E_{p} < 2MeV","EH3: 2 < E_{p} < 3MeV","EH3: 3 < E_{p} < 4MeV","EH3: 4 < E_{p} < 5MeV","EH3: 5 < E_{p} < 12MeV"}};

	const char *c_Name_single[3]={"EH1 only + 5 E bins","EH2 Only + 5 E bins","EH3 Only + 5 E bins"};
	const char *c_Name_single_1[3]={"EH1 only + 5 E bins - 1","EH2 Only + 5 E bins - 1","EH3 Only + 5 E bins - 1"};
	const char *c_Name_single_2[3]={"EH1 only + 5 E bins - 2","EH2 Only + 5 E bins - 2","EH3 Only + 5 E bins - 2"};
	const char *file_Name[3][5]={{"ThreeSites_Paper/Ratio_EH1_OneDay_sidereal1.eps","ThreeSites_Paper/Ratio_EH1_OneDay_sidereal2.eps","ThreeSites_Paper/Ratio_EH1_OneDay_sidereal3.eps","ThreeSites_Paper/Ratio_EH1_OneDay_sidereal4.eps","ThreeSites_Paper/Ratio_EH1_OneDay_sidereal5.eps"},
								 {"ThreeSites_Paper/Ratio_EH2_OneDay_sidereal1.eps","ThreeSites_Paper/Ratio_EH2_OneDay_sidereal2.eps","ThreeSites_Paper/Ratio_EH2_OneDay_sidereal3.eps","ThreeSites_Paper/Ratio_EH2_OneDay_sidereal4.eps","ThreeSites_Paper/Ratio_EH2_OneDay_sidereal5.eps"},
								 {"ThreeSites_Paper/Ratio_EH3_OneDay_sidereal1.eps","ThreeSites_Paper/Ratio_EH3_OneDay_sidereal2.eps","ThreeSites_Paper/Ratio_EH3_OneDay_sidereal3.eps","ThreeSites_Paper/Ratio_EH3_OneDay_sidereal4.eps","ThreeSites_Paper/Ratio_EH3_OneDay_sidereal5.eps"}};
	const char *file_Name2[3][5]={{"ThreeSites_Paper/Ratio_EH1_OneDay_sidereal1.jpg","ThreeSites_Paper/Ratio_EH1_OneDay_sidereal2.jpg","ThreeSites_Paper/Ratio_EH1_OneDay_sidereal3.jpg","ThreeSites_Paper/Ratio_EH1_OneDay_sidereal4.jpg","ThreeSites_Paper/Ratio_EH1_OneDay_sidereal5.jpg"},
								  {"ThreeSites_Paper/Ratio_EH2_OneDay_sidereal1.jpg","ThreeSites_Paper/Ratio_EH2_OneDay_sidereal2.jpg","ThreeSites_Paper/Ratio_EH2_OneDay_sidereal3.jpg","ThreeSites_Paper/Ratio_EH2_OneDay_sidereal4.jpg","ThreeSites_Paper/Ratio_EH2_OneDay_sidereal5.jpg"},
								  {"ThreeSites_Paper/Ratio_EH3_OneDay_sidereal1.jpg","ThreeSites_Paper/Ratio_EH3_OneDay_sidereal2.jpg","ThreeSites_Paper/Ratio_EH3_OneDay_sidereal3.jpg","ThreeSites_Paper/Ratio_EH3_OneDay_sidereal4.jpg","ThreeSites_Paper/Ratio_EH3_OneDay_sidereal5.jpg"}};

	Double_t ParResult_single[3][9];
	Double_t ParErrResult_single[3][9];
	for(int i=0;i<9;i++)
	{
		ParResult_single[0][i]=ParResult_EH1[i];
		ParResult_single[1][i]=ParResult_EH2[i];
		ParResult_single[2][i]=ParResult_EH3[i];
		ParErrResult_single[0][i]=ParErrResult_EH1[i];
		ParErrResult_single[1][i]=ParErrResult_EH2[i];
		ParErrResult_single[2][i]=ParErrResult_EH3[i];
	}

	for(int Eidx=0;Eidx<5;Eidx++)
	{
		EBinIdx = Eidx;
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		Float_t x[n],y[n],ex[n],ey[n];
		myC[Hidx][Eidx] = new TCanvas(c_Name[Hidx][Eidx],c_Name[Hidx][Eidx],200,10,800,420);
		gStyle->SetOptFit(1);
		//myC[Hidx][Eidx]->SetGrid();
		myC[Hidx][Eidx]->GetFrame()->SetFillColor(21);
		myC[Hidx][Eidx]->GetFrame()->SetBorderSize(12);
		for(int i=0;i<n;i++)
		{
		x[i]=(i+0.5)*WidthOfBin;
		y[i]=R[Hidx][i][Eidx];
		ex[i]=0.5*WidthOfBin;
		ey[i]=R[Hidx][i][Eidx]*RD_R[Hidx][i][Eidx];
		//cout<<y[i]<<"   "<<ey[i]<<endl;
		}
		gr[Hidx][Eidx] = new TGraphErrors(n,x,y,ex,ey);

		gr[Hidx][Eidx]->SetMarkerColor(4);
		gr[Hidx][Eidx]->SetMarkerStyle(21);
		gr[Hidx][Eidx]->GetXaxis()->SetTitle("sidereal time (seconds)");
		gr[Hidx][Eidx]->GetYaxis()->SetTitle("P(#bar{#nu}_{e} #rightarrow #bar{#nu}_{e})");
		
		gr[Hidx][Eidx]->GetYaxis()->SetRangeUser(0.8,1.2);
		
		gr[Hidx][Eidx]->GetYaxis()->SetTitleSize(0.07);
		gr[Hidx][Eidx]->GetYaxis()->SetLabelSize(0.06);
		gr[Hidx][Eidx]->GetYaxis()->SetTitleOffset(0.65);
		gr[Hidx][Eidx]->GetYaxis()->SetNdivisions(505);
		gr[Hidx][Eidx]->GetYaxis()->CenterTitle();

		gr[Hidx][Eidx]->SetTitle("");
	
		gr[Hidx][Eidx]->GetXaxis()->SetTitleOffset(0.7);
		gr[Hidx][Eidx]->GetXaxis()->SetTitleSize(0.07);
		gr[Hidx][Eidx]->GetXaxis()->SetRangeUser(0,86164.09);
		gr[Hidx][Eidx]->GetXaxis()->SetLabelSize(0.05);
		gr[Hidx][Eidx]->GetXaxis()->SetLabelOffset(0.0);

		gr[Hidx][Eidx]->SetMarkerStyle(8);
		gr[Hidx][Eidx]->SetMarkerColor(0);
		gr[Hidx][Eidx]->SetLineColor(1);
		gr[Hidx][Eidx]->SetLineWidth(2);
		gr[Hidx][Eidx]->SetMarkerSize(0.8);


		//gr[Hidx]->SetMarkerStyle(21);
		gr[Hidx][Eidx]->Draw("APZ");
		/////////////////plot the fit result:three sites////////////////////////
		//0		1	2	3	4	5	6	7	8		
		//A11	A12	A2  A31	A32	A4	B1	B2  HallID	
		//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
		f_Plot[Hidx][Eidx] = new TF1(c_Name[Hidx][Eidx],PlotFunc,0,86165.0,10);

		for(int i=1;i<8;i++)
		{
			f_Plot[Hidx][Eidx]->SetParameter(i,ParResult[i]);
		}
		f_Plot[Hidx][Eidx]->SetParameter(8,Hidx);
		f_Plot[Hidx][Eidx]->SetParameter(9,ParResult[8]);

		f_Plot[Hidx][Eidx]->SetLineColor(kRed);
		f_Plot[Hidx][Eidx]->Draw("same");

		/////////////////plot the fit result:site by site////////////////////////
		f_Plot_single[Hidx][Eidx] = new TF1(c_Name_single[Hidx],PlotFunc,0,86165.0,10);

		for(int i=0;i<8;i++)
		{
			f_Plot_single[Hidx][Eidx]->SetParameter(i,ParResult_single[Hidx][i]);
			//f_Plot_single[Hidx][Eidx]->SetParError(i,ParErrResult_single[Hidx][i]);
		}
		f_Plot_single[Hidx][Eidx]->SetParameter(8,Hidx);
		f_Plot_single[Hidx][Eidx]->SetParameter(9,ParResult_single[Hidx][8]);

		f_Plot_single[Hidx][Eidx]->SetLineColor(kBlue);
		//f_Plot_single[Hidx][Eidx]->SetLineStyle(2);
		//f_Plot_single[Hidx][Eidx]->Draw("same");


		/////////////////plot the fit result:this site////////////////////////
		f_Plot_this[Hidx][Eidx] = new TF1("This plot fit",PlotFunc,0,86165.0,10);

		for(int i=0;i<8;i++)
		{
			f_Plot_this[Hidx][Eidx]->SetParameter(i,ParResult_this[Hidx][Eidx][i]);
		}
		f_Plot_this[Hidx][Eidx]->SetParameter(8,Hidx);
		f_Plot_this[Hidx][Eidx]->SetParameter(9,ParResult_this[Hidx][Eidx][8]);

		f_Plot_this[Hidx][Eidx]->SetLineColor(kGreen);
		//f_Plot_this[Hidx][Eidx]->SetLineStyle(2);
		//f_Plot_this[Hidx][Eidx]->Draw("same");
		////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////Draw the error band///////////////////////////////////////////
		
		Double_t xb[100]={0},yb[100]={0},exb[100]={0},eyb[100]={0};
		Int_t nb=100;
		for(int i=0;i<100;i++)
		{
			xb[i]=861.650*i;
			//yb[i]=1.08;
		}
		//evaluate PlotFunc
		Double_t x_Time=0.0, par_band[10],par_band2[10];
		TRandom *Ran_par = new TRandom();
		Double_t xy_band[100][1000];
		Double_t y_Center[100];
		Double_t sigma_y_band[100];
		Double_t mean_y_band[100];

		par_band[9]=Hidx;
		par_band2[9]=Hidx;
		//double par_Result[10];
		///par_Result[9]=Hidx;
		//for()

		Double_t sigma_y = 0.0;
		//3 sites
		for(int xN=0;xN<100;xN++)
		{
			TH1F *y_TH1F_band = new TH1F();
			x_Time = 861.650*xN;
			for(int yN=0;yN<1000;yN++)
			{
				
				for(int pN=0;pN<10;pN++)
				{
					if(pN!=8)
					{
					Double_t r01 = Ran_par->Gaus(0.0,1.0);
					par_band[pN] = ParResult[pN]+ 1.0*r01*ParErrResult[pN];
					}
				}
				xy_band[xN][yN] = PlotFunc(&x_Time,par_band);
				y_TH1F_band->Fill(xy_band[xN][yN]);
			}
			for(int pN=0;pN<8;pN++)
			{
				if(pN!=8)
					{
				par_band2[pN] = ParResult[pN];
				}
			}
			par_band2[9] = ParResult[8];

			//y_Center[xN] = PlotFunc(&x_Time,par_band2);
			//y_Center[xN] = PlotFunc(&x_Time,ParResult);
			y_Center[xN] = f_Plot[Hidx][Eidx]->Eval(x_Time);
			mean_y_band[xN] = y_TH1F_band->GetMean();
			sigma_y_band[xN] = y_TH1F_band->GetStdDev();
			sigma_y += 0.01*sigma_y_band[xN];
			//cout<<xN<<"   "<<mean_y_band[xN]<<"   "<<sigma_y_band[xN]<<endl;
		}
		for(int PN=0;PN<2;PN++)
		{
			for(int xN=0;xN<100;xN++)
			{
				if(PN==0)//positive
				{
					yb[xN]=y_Center[xN]+sigma_y;
				}
				else
				{
					yb[xN]=y_Center[xN]-sigma_y;
				}
			}
			TGraphErrors *grb = new TGraphErrors(nb,xb,yb,exb,eyb);
			grb->SetMarkerStyle(1);
			grb->SetLineStyle(10);
			grb->SetMarkerColor(kRed);
			grb->SetLineColor(kRed);
			grb->Draw("CSAME");
		}
		
		
		
		sigma_y=0.0;
		

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		leg[Hidx][Eidx] = new TLegend(0.15, 0.75, 0.7, 0.9);
		leg[Hidx][Eidx]->AddEntry(gr[Hidx][Eidx],c_Name[Hidx][Eidx],"");
		leg[Hidx][Eidx]->SetFillStyle(0);
		leg[Hidx][Eidx]->SetBorderSize(0);
		//leg[Hidx][Eidx]->SetTextColor(kRed);
		leg[Hidx][Eidx]->Draw();
		////////////
		leg2[Hidx][Eidx] = new TLegend(0.3, 0.1, 0.7, 0.25);
		leg2[Hidx][Eidx]->AddEntry(f_Plot[Hidx][Eidx],"e-e flavor pair best fit","l");
		leg2[Hidx][Eidx]->AddEntry(grb,"1 #sigma error band","l");
		//leg2[Hidx][Eidx]->AddEntry(f_Plot_this[Hidx][Eidx],"This plot only fit","l");
		leg2[Hidx][Eidx]->SetFillStyle(0);
		leg2[Hidx][Eidx]->SetBorderSize(0);
		//leg2[Hidx][Eidx]->SetTextColor(kRed);
		leg2[Hidx][Eidx]->Draw();

		myC[Hidx][Eidx]->Update();
		myC[Hidx][Eidx]->SaveAs(file_Name[Hidx][Eidx]);
		myC[Hidx][Eidx]->SaveAs(file_Name2[Hidx][Eidx]);
	}
	}

	double ParResult_table[6][9] = {0.0};
	double ParErrResult_table[6][9] = {0.0};
	/*
	//////////////////////////////////////////////////////all flavor component//////////////////////////////////////////////////////////////////////////////////////////////
	Int_t Table_Index[6][2]={{0,0},{1,1},{2,2},{0,1},{0,2},{1,2}};
	const char *cdIdx_Name[6]={"ee","uu","tt","eu","et","ut"};
	FILE* m_outfile = fopen("FitResult_all.txt", "w+");

	for(int cdIdx=0;cdIdx<6;cdIdx++)
	{
		cout<<cdIdx_Name[cdIdx]<<endl;
	IndexCD[0] = Table_Index[cdIdx][0];
	IndexCD[1] = Table_Index[cdIdx][1];
	////////////////////////////////////////////////////Fit////////////////////////////////////////////////////////////////////////////////////////////////////
	//0		1	2	3	4	5	6	7		
	//A11	A12	A2  A31	A32	A4	B1	B2  
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
   TMinuit *gMinuit = new TMinuit(9);  //initialize TMinuit with a maximum of 7 params
   gMinuit->SetFCN(ChiSquare);

   Double_t arglist[10];
   Int_t ierflg = 0;

   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   Double_t vstart[9] = {0};//{-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0};
   Double_t step[9] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01,0.01};
   gMinuit->mnparm(0, "A11", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A12", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A31", vstart[3], step[3], 0,0,ierflg);
   gMinuit->mnparm(4, "A32", vstart[4], step[4], 0,0,ierflg);
   gMinuit->mnparm(5, "A4", vstart[5], step[5], 0,0,ierflg);
   gMinuit->mnparm(6, "B1", vstart[6], step[6], 0,0,ierflg);
   gMinuit->mnparm(7, "B2", vstart[7], step[7], 0,0,ierflg);
   gMinuit->mnparm(8, "T0", vstart[8], step[8], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 2000;
   arglist[1] = 40000.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

   arglist[0] = 2000;
   gMinuit->mnexcm("IMProve", arglist ,1,ierflg);

// Print results
    //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   Table_Chi2_3Site_5Bin[cdIdx] = amin;
   gMinuit->mnprin(3,amin);

   //0		1	2	3	4	5	6	7		
	//A11	A12	A2  A31	A32	A4	B1	B2  
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
   //Double_t ParResult[8],ParErrResult[8];
   for(int i=0;i<9;i++)
   {
	   Double_t v,ev;
	   gMinuit->GetParameter(i,v,ev);
	   ParResult[i]=v;
	   ParErrResult[i]=ev;
   }


   ////////////////////////////////////////////////////Fit site by site (EH1 only)////////////////////////////////////////////////////////////////////////////////////////////////////
   TMinuit *gMinuit_EH1 = new TMinuit(9);  //initialize TMinuit with a maximum of 8 params
   gMinuit_EH1->SetFCN(ChiSquare_EH1);

   Double_t arglist_EH1[10];
   Int_t ierflg_EH1 = 0;

   arglist_EH1[0] = 1;
   gMinuit_EH1->mnexcm("SET ERR", arglist_EH1 ,1,ierflg_EH1);

// Set starting values and step_EH1 sizes for parameters
   Double_t vstart_EH1[9] = {0};//{-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0};
   Double_t step_EH1[9] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01,0.01};
   gMinuit_EH1->mnparm(0, "A11", vstart_EH1[0], step_EH1[0], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(1, "A12", vstart_EH1[1], step_EH1[1], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(2, "A2", vstart_EH1[2], step_EH1[2], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(3, "A31", vstart_EH1[3], step_EH1[3], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(4, "A32", vstart_EH1[4], step_EH1[4], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(5, "A4", vstart_EH1[5], step_EH1[5], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(6, "B1", vstart_EH1[6], step_EH1[6], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(7, "B2", vstart_EH1[7], step_EH1[7], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(8, "T0", vstart_EH1[8], step_EH1[8], 0,0,ierflg_EH1);

// Now ready for minimization step_EH1
   arglist_EH1[0] = 2000;
   arglist_EH1[1] = 40000.;
   gMinuit_EH1->mnexcm("MIGRAD", arglist_EH1 ,2,ierflg_EH1);

   arglist_EH1[0] = 2000;
   gMinuit_EH1->mnexcm("IMProve", arglist_EH1 ,1,ierflg_EH1);

// Print results
    //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6
   Double_t amin_EH1,edm_EH1,errdef_EH1;
   Int_t nvpar_EH1,nparx_EH1,icstat_EH1;
   gMinuit_EH1->mnstat(amin_EH1,edm_EH1,errdef_EH1,nvpar_EH1,nparx_EH1,icstat_EH1);
   Table_Chi2_SiteBySite_5Bin[0][cdIdx]=amin_EH1;

   gMinuit_EH1->mnprin(3,amin_EH1);

   
   for(int i=0;i<9;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH1->GetParameter(i,v,ev);
	   ParResult_EH1[i]=v;
	   ParErrResult_EH1[i]=ev;
   }


   
  ////////////////////////////////////////////////////Fit site by site (EH2 only)////////////////////////////////////////////////////////////////////////////////////////////////////
   TMinuit *gMinuit_EH2 = new TMinuit(9);  //initialize TMinuit with a maximum of 8 params
   gMinuit_EH2->SetFCN(ChiSquare_EH2);

   Double_t arglist_EH2[10];
   Int_t ierflg_EH2 = 0;

   arglist_EH2[0] = 1;
   gMinuit_EH2->mnexcm("SET ERR", arglist_EH2 ,1,ierflg_EH2);

// Set starting values and step_EH2 sizes for parameters
   Double_t vstart_EH2[9] = {0};//{-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0};
   Double_t step_EH2[9] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01,0.01};
   gMinuit_EH2->mnparm(0, "A11", vstart_EH2[0], step_EH2[0], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(1, "A12", vstart_EH2[1], step_EH2[1], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(2, "A2", vstart_EH2[2], step_EH2[2], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(3, "A31", vstart_EH2[3], step_EH2[3], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(4, "A32", vstart_EH2[4], step_EH2[4], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(5, "A4", vstart_EH2[5], step_EH2[5], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(6, "B1", vstart_EH2[6], step_EH2[6], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(7, "B2", vstart_EH2[7], step_EH2[7], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(8, "T0", vstart_EH2[8], step_EH2[8], 0,0,ierflg_EH2);

// Now ready for minimization step_EH2
   arglist_EH2[0] = 2000;
   arglist_EH2[1] = 40000.;
   gMinuit_EH2->mnexcm("MIGRAD", arglist_EH2 ,2,ierflg_EH2);

   arglist_EH2[0] = 2000;
   gMinuit_EH2->mnexcm("IMProve", arglist_EH2 ,1,ierflg_EH2);

// Print results
    //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6
   Double_t amin_EH2,edm_EH2,errdef_EH2;
   Int_t nvpar_EH2,nparx_EH2,icstat_EH2;
   gMinuit_EH2->mnstat(amin_EH2,edm_EH2,errdef_EH2,nvpar_EH2,nparx_EH2,icstat_EH2);
   Table_Chi2_SiteBySite_5Bin[1][cdIdx]=amin_EH2;

   gMinuit_EH2->mnprin(3,amin_EH2);

   
   for(int i=0;i<9;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH2->GetParameter(i,v,ev);
	   ParResult_EH2[i]=v;
	   ParErrResult_EH2[i]=ev;
   }
   

////////////////////////////////////////////////////Fit site by site (EH3 only)////////////////////////////////////////////////////////////////////////////////////////////////////
   TMinuit *gMinuit_EH3 = new TMinuit(9);  //initialize TMinuit with a maximum of 8 params
   gMinuit_EH3->SetFCN(ChiSquare_EH3);

   Double_t arglist_EH3[10];
   Int_t ierflg_EH3 = 0;

   arglist_EH3[0] = 1;
   gMinuit_EH3->mnexcm("SET ERR", arglist_EH3 ,1,ierflg_EH3);

// Set starting values and step_EH3 sizes for parameters
   Double_t vstart_EH3[9] = {0};//{-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0};
   Double_t step_EH3[9] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01,0.01};
   gMinuit_EH3->mnparm(0, "A11", vstart_EH3[0], step_EH3[0], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(1, "A12", vstart_EH3[1], step_EH3[1], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(2, "A2", vstart_EH3[2], step_EH3[2], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(3, "A31", vstart_EH3[3], step_EH3[3], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(4, "A32", vstart_EH3[4], step_EH3[4], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(5, "A4", vstart_EH3[5], step_EH3[5], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(6, "B1", vstart_EH3[6], step_EH3[6], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(7, "B2", vstart_EH3[7], step_EH3[7], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(8, "T0", vstart_EH3[8], step_EH3[8], 0,0,ierflg_EH3);

// Now ready for minimization step_EH3
   arglist_EH3[0] = 2000;
   arglist_EH3[1] = 40000.;
   gMinuit_EH3->mnexcm("MIGRAD", arglist_EH3 ,2,ierflg_EH3);

   arglist_EH3[0] = 2000;
   gMinuit_EH3->mnexcm("IMProve", arglist_EH3 ,1,ierflg_EH3);
   // Print results
    //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6
   Double_t amin_EH3,edm_EH3,errdef_EH3;
   Int_t nvpar_EH3,nparx_EH3,icstat_EH3;
   gMinuit_EH3->mnstat(amin_EH3,edm_EH3,errdef_EH3,nvpar_EH3,nparx_EH3,icstat_EH3);
   Table_Chi2_SiteBySite_5Bin[2][cdIdx]=amin_EH3;

   gMinuit_EH3->mnprin(3,amin_EH3);

   
   for(int i=0;i<9;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH3->GetParameter(i,v,ev);
	   ParResult_EH3[i]=v;
	   ParErrResult_EH3[i]=ev;
   }

	for(int i=0;i<9;i++)
	{
		ParResult_table[cdIdx][i] = ParResult[i];
		ParErrResult_table[cdIdx][i] = ParErrResult[i];
	}
   ///////////print
	//0		1	2	3	4	5	6	7		
	//A11	A12	A2  A31	A32	A4	B1	B2  
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
   //double Table_Chi2_3Site_5Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
   //double Table_Chi2_3Site_1Bin[6]={0.0};
   //double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};
   //int NOF_3Site_5Bin = 352; //3*5*24-8
	//int NOF_SiteBySite_5Bin = 112; //5*24-8
	//int NOF_3Site_1Bin = 66; // 3*24-6
	//int NOF_SiteBySite_1Bin = 18; //24-6

   fprintf(m_outfile,"fit result(three sites) %2s:\n",cdIdx_Name[cdIdx]);
   fprintf(m_outfile,"$a^X_R$/$10^{-21}$GeV           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[0],ParErrResult[0],ParResult_EH1[0],ParErrResult_EH1[0],ParResult_EH2[0],ParErrResult_EH2[0],ParResult_EH3[0],ParErrResult_EH3[0]);
   fprintf(m_outfile,"$c^{TX}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[1],ParErrResult[1],ParResult_EH1[1],ParErrResult_EH1[1],ParResult_EH2[1],ParErrResult_EH2[1],ParResult_EH3[1],ParErrResult_EH3[1]);
   fprintf(m_outfile,"$c^{XZ}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[2],ParErrResult[2],ParResult_EH1[2],ParErrResult_EH1[2],ParResult_EH2[2],ParErrResult_EH2[2],ParResult_EH3[2],ParErrResult_EH3[2]);
   fprintf(m_outfile,"$a^Y_R$/$10^{-21}$GeV           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[3],ParErrResult[3],ParResult_EH1[3],ParErrResult_EH1[3],ParResult_EH2[3],ParErrResult_EH2[3],ParResult_EH3[3],ParErrResult_EH3[3]);
   fprintf(m_outfile,"$c^{TY}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[4],ParErrResult[4],ParResult_EH1[4],ParErrResult_EH1[4],ParResult_EH2[4],ParErrResult_EH2[4],ParResult_EH3[4],ParErrResult_EH3[4]);
   fprintf(m_outfile,"$c^{YZ}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[5],ParErrResult[5],ParResult_EH1[5],ParErrResult_EH1[5],ParResult_EH2[5],ParErrResult_EH2[5],ParResult_EH3[5],ParErrResult_EH3[5]);
   fprintf(m_outfile,"$c^{XX}_R-c^{YY}_R$/$10^{-18}$  &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[6],ParErrResult[6],ParResult_EH1[6],ParErrResult_EH1[6],ParResult_EH2[6],ParErrResult_EH2[6],ParResult_EH3[6],ParErrResult_EH3[6]);
   fprintf(m_outfile,"$c^{XY}_R$/$10^{-18}$  &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[7],ParErrResult[7],ParResult_EH1[7],ParErrResult_EH1[7],ParResult_EH2[7],ParErrResult_EH2[7],ParResult_EH3[7],ParErrResult_EH3[7]);
    fprintf(m_outfile,"$T_0(\\mathrm{seconds})$  &$%8.1f \\pm %8.1f$ &$%8.1f \\pm %8.1f$ &$%8.1f \\pm %8.1f$ &$%8.1f \\pm %8.1f$    \\\\ \n",ParResult[8],ParErrResult[8],ParResult_EH1[8],ParErrResult_EH1[8],ParResult_EH2[8],ParErrResult_EH2[8],ParResult_EH3[8],ParErrResult_EH3[8]);
   fprintf(m_outfile,"$\\chi^2/NDF$  & $%4.1f/%3d$ & $%4.1f/%3d$& $%4.1f/%3d$ & $%4.1f/%3d$      \\\\ \n",
	   Table_Chi2_3Site_5Bin[cdIdx],NOF_3Site_5Bin,
	   Table_Chi2_SiteBySite_5Bin[0][cdIdx],NOF_SiteBySite_5Bin,
	   Table_Chi2_SiteBySite_5Bin[1][cdIdx],NOF_SiteBySite_5Bin,
	   Table_Chi2_SiteBySite_5Bin[2][cdIdx],NOF_SiteBySite_5Bin,);
   }
   
   //print for paper
   fprintf(m_outfile, "for paper \n");
  
		fprintf(m_outfile,"$a^X_R$/$10^{-21}$GeV ");
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%3.1f \\pm %3.1f$", ParResult_table[cdIdx][0],ParErrResult_table[cdIdx][0]);
		}
		fprintf(m_outfile,"$c^{TX}_R$/$10^{-18}$ ");
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%3.1f \\pm %3.1f$", ParResult_table[cdIdx][1],ParErrResult_table[cdIdx][1]);
		}
		fprintf(m_outfile,"$c^{XZ}_R$/$10^{-18}$ ");
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%3.1f \\pm %3.1f$", ParResult_table[cdIdx][2],ParErrResult_table[cdIdx][2]);
		}
		fprintf(m_outfile,"$a^Y_R$/$10^{-21}$GeV ");
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%3.1f \\pm %3.1f$", ParResult_table[cdIdx][3],ParErrResult_table[cdIdx][3]);
		}
		fprintf(m_outfile,"$c^{TY}_R$/$10^{-18}$ ");
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%3.1f \\pm %3.1f$", ParResult_table[cdIdx][4],ParErrResult_table[cdIdx][4]);
		}
		fprintf(m_outfile,"$c^{YZ}_R$/$10^{-18}$ ");
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%3.1f \\pm %3.1f$", ParResult_table[cdIdx][5],ParErrResult_table[cdIdx][5]);
		}
		fprintf(m_outfile,"$c^{XX}_R-c^{YY}_R$/$ ");
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%3.1f \\pm %3.1f$", ParResult_table[cdIdx][6],ParErrResult_table[cdIdx][6]);
		}
		fprintf(m_outfile,"$c^{XY}_R$/$10^{-18}$ ");
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%3.1f \\pm %3.1f$", ParResult_table[cdIdx][7],ParErrResult_table[cdIdx][7]);
		}
		fprintf(m_outfile,"$T_0(\\mathrm{seconds})$"); 
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%3.1f \\pm %3.1f$", ParResult_table[cdIdx][8],ParErrResult_table[cdIdx][8]);
		}
		fprintf(m_outfile,"$\\chi^2/NDF$  \n");
		for(int cdIdx=0;cdIdx<6;cdIdx++)
		{
			fprintf(m_outfile,"& $%4.1f/%3d$", Table_Chi2_3Site_5Bin[cdIdx],NOF_3Site_5Bin);
		}
		
   */
  
}

Double_t PlotFunc(Double_t *x, Double_t *par)
{
	//0		1	2	3	4	5	6	7	8		9
	//A11	A12	A2  A31	A32	A4	B1	B2  HallID	T0
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
	double TZero = par[9];
	Int_t HallID=int(par[8]);
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = AVEP[HallID][EBinIdx];
	Double_t frac[6];
	Double_t IMSM,Nxt,Nyt,Nzt,E;
	E = Ave_Energy[EBinIdx]*1.0e-3;
	int BIN = int(x[0]/WidthOfBin);

	if(BIN<24)
	{
		for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall[HallID][i][BIN];
		}
	}
	else
	{
		for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall[HallID][i][23];
		}
	}

	for(int i=0;i<6;i++)
	{
		TotalEveFrac += frac[i];
	}

	for(int i=0;i<6;i++)
	{
		IMSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]][EBinIdx];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];
		//0		1	2	3	4	5	6	7	8		
		//A11	A12	A2  A31	A32	A4	B1	B2  HallID	
		//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
		TotalP  += 2.0*Baseline_Hall[HallID][i]*5.07*(frac[i]/TotalEveFrac)*IMSM*1.0e-3*( 
			(Nyt*(par[0]*0.001-2*E*par[1])+2.0*E*Nyt*Nzt*par[2]+Nxt*(-1.0*par[3]*0.001+2.0*E*par[4])-2.0*E*Nxt*Nzt*par[5])*sin(wP*(x[0]+TZero)) +
			(-1.0*Nxt*(par[0]*0.001-2*E*par[1])-2.0*E*Nxt*Nzt*par[2]+Nyt*(-1.0*par[3]*0.001+2.0*E*par[4])-2.0*E*Nyt*Nzt*par[5])*cos(wP*(x[0]+TZero)) +
			(E*Nxt*Nyt*par[6]-E*(Nxt*Nxt-Nyt*Nyt)*par[7])*sin(2.0*wP*(x[0]+TZero))+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[6]-2.0*E*Nxt*Nyt*par[7])*cos(2.0*wP*(x[0]+TZero)));
	}
	return TotalP;

}

Double_t FitFunc1(Double_t x, Double_t *par)//EH1, C fixed to 1.0
{
	//0		1	2	3	4	5	6	7		
	//A11	A12	A2  A31	A32	A4	B1	B2  
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
	double TZero = par[8];

	Int_t HallID=0;
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = AVEP[HallID][EBinIdx];
	Double_t frac[6];
	Double_t IMSM,Nxt,Nyt,Nzt,E;
	E = Ave_Energy[EBinIdx]*1.0e-3;
	int BIN = int(x/WidthOfBin);

	if(BIN<24)
	{
		for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall[HallID][i][BIN];
		}
	}
	else
	{
		for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall[HallID][i][23];
		}
	}

	for(int i=0;i<6;i++)
	{
		TotalEveFrac += frac[i];
	}

	for(int i=0;i<6;i++)
	{
		IMSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]][EBinIdx];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];
		TotalP  += 2.0*Baseline_Hall[HallID][i]*5.07*(frac[i]/TotalEveFrac)*IMSM*1.0e-3*( 
			(Nyt*(par[0]*0.001-2*E*par[1])+2.0*E*Nyt*Nzt*par[2]+Nxt*(-1.0*par[3]*0.001+2.0*E*par[4])-2.0*E*Nxt*Nzt*par[5])*sin(wP*(x+TZero)) +
			(-1.0*Nxt*(par[0]*0.001-2*E*par[1])-2.0*E*Nxt*Nzt*par[2]+Nyt*(-1.0*par[3]*0.001+2.0*E*par[4])-2.0*E*Nyt*Nzt*par[5])*cos(wP*(x+TZero)) +
			(E*Nxt*Nyt*par[6]-E*(Nxt*Nxt-Nyt*Nyt)*par[7])*sin(2.0*wP*(x+TZero))+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[6]-2.0*E*Nxt*Nyt*par[7])*cos(2.0*wP*(x+TZero)));
	}
	return TotalP;

}

Double_t FitFunc2(Double_t x, Double_t *par)//EH2, C fixed to 1.0
{
	//0		1	2	3	4	5	6	7			
	//A11	A12	A2  A31	A32	A4	B1	B2  
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
	double TZero = par[8];
	Int_t HallID=1;
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = AVEP[HallID][EBinIdx];
	Double_t frac[6];
	Double_t IMSM,Nxt,Nyt,Nzt,E;
	E = Ave_Energy[EBinIdx]*1.0e-3;
	int BIN = int(x/WidthOfBin);

	if(BIN<24)
	{
		for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall[HallID][i][BIN];
		}
	}
	else
	{
		for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall[HallID][i][23];
		}
	}

	for(int i=0;i<6;i++)
	{
		TotalEveFrac += frac[i];
	}

	for(int i=0;i<6;i++)
	{
		IMSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]][EBinIdx];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];
		TotalP  += 2.0*Baseline_Hall[HallID][i]*5.07*(frac[i]/TotalEveFrac)*IMSM*1.0e-3*( 
			(Nyt*(par[0]*0.001-2*E*par[1])+2.0*E*Nyt*Nzt*par[2]+Nxt*(-1.0*par[3]*0.001+2.0*E*par[4])-2.0*E*Nxt*Nzt*par[5])*sin(wP*(x+TZero)) +
			(-1.0*Nxt*(par[0]*0.001-2*E*par[1])-2.0*E*Nxt*Nzt*par[2]+Nyt*(-1.0*par[3]*0.001+2.0*E*par[4])-2.0*E*Nyt*Nzt*par[5])*cos(wP*(x+TZero)) +
			(E*Nxt*Nyt*par[6]-E*(Nxt*Nxt-Nyt*Nyt)*par[7])*sin(2.0*wP*(x+TZero))+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[6]-2.0*E*Nxt*Nyt*par[7])*cos(2.0*wP*(x+TZero)));
	}
	return TotalP;

}

Double_t FitFunc3(Double_t x, Double_t *par)//EH3, C fixed to 1.0
{
	//0		1	2	3	4	5	6	7			
	//A11	A12	A2  A31	A32	A4	B1	B2  
	//A11,A31: 1e-21; A12,A2,A32, A4,B1,B2:1e-18
	double TZero = par[8];
	Int_t HallID=2;
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = AVEP[HallID][EBinIdx];
	Double_t frac[6];
	Double_t IMSM,Nxt,Nyt,Nzt,E;
	E = Ave_Energy[EBinIdx]*1.0e-3;
	int BIN = int(x/WidthOfBin);

	if(BIN<24)
	{
		for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall[HallID][i][BIN];
		}
	}
	else
	{
		for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall[HallID][i][23];
		}
	}

	for(int i=0;i<6;i++)
	{
		TotalEveFrac += frac[i];
	}

	for(int i=0;i<6;i++)
	{
		IMSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]][EBinIdx];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];
		TotalP  += 2.0*Baseline_Hall[HallID][i]*5.07*(frac[i]/TotalEveFrac)*IMSM*1.0e-3*( 
			(Nyt*(par[0]*0.001-2*E*par[1])+2.0*E*Nyt*Nzt*par[2]+Nxt*(-1.0*par[3]*0.001+2.0*E*par[4])-2.0*E*Nxt*Nzt*par[5])*sin(wP*(x+TZero)) +
			(-1.0*Nxt*(par[0]*0.001-2*E*par[1])-2.0*E*Nxt*Nzt*par[2]+Nyt*(-1.0*par[3]*0.001+2.0*E*par[4])-2.0*E*Nyt*Nzt*par[5])*cos(wP*(x+TZero)) +
			(E*Nxt*Nyt*par[6]-E*(Nxt*Nxt-Nyt*Nyt)*par[7])*sin(2.0*wP*(x+TZero))+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[6]-2.0*E*Nxt*Nyt*par[7])*cos(2.0*wP*(x+TZero)));
	}
	return TotalP;

}



void ChiSquare(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH1
   for(EBinIdx=0;EBinIdx<5;EBinIdx++)
   {
   for (i=0;i<nbins; i++) {
	double R2P2 = pow(RD_R[0][i][EBinIdx],2.0);
	double RP1, RP2;
	RP1 = FitFunc1(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_2[ii];
	}
	RP2 = FitFunc1(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_Save[ii];
	}
	 R2P2 += pow(RP1-RP2,2.0);

     delta  = (R[0][i][EBinIdx]-FitFunc1(i*WidthOfBin,par));
     chisq += delta*delta/R2P2;
   }
   //EH2
   for (i=0;i<nbins; i++) {
     double R2P2 = pow(RD_R[1][i][EBinIdx],2.0);
	double RP1, RP2;
	RP1 = FitFunc2(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_2[ii];
	}
	RP2 = FitFunc2(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_Save[ii];
	}
	 R2P2 += pow(RP1-RP2,2.0);

     delta  = (R[1][i][EBinIdx]-FitFunc2(i*WidthOfBin,par));
     chisq += delta*delta/R2P2;
   }
   //EH3
   for (i=0;i<nbins; i++) {
    double R2P2 = pow(RD_R[2][i][EBinIdx],2.0);
	double RP1, RP2;
	RP1 = FitFunc3(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_2[ii];
	}
	RP2 = FitFunc3(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_Save[ii];
	}
	 R2P2 += pow(RP1-RP2,2.0);

     delta  = (R[2][i][EBinIdx]-FitFunc3(i*WidthOfBin,par));
     chisq += delta*delta/R2P2;
   }
   }
   EBinIdx = 0;

   f = chisq;
   /*
   cout<<NumOfIrr<<"   "<<f<<"   ";
   NumOfIrr++;
   for(int i=0;i<9;i++)
   {
	   cout<<par[i]<<"   ";
   }
   cout<<endl;
   */
}

void ChiSquare_EH1(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH1
     for(EBinIdx=0;EBinIdx<5;EBinIdx++)
   {
   for (i=0;i<nbins; i++) {
     double R2P2 = pow(RD_R[0][i][EBinIdx],2.0);
	double RP1, RP2;
	RP1 = FitFunc1(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_2[ii];
	}
	RP2 = FitFunc1(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_Save[ii];
	}
	 R2P2 += pow(RP1-RP2,2.0);

     delta  = (R[0][i][EBinIdx]-FitFunc1(i*WidthOfBin,par));
     chisq += delta*delta/R2P2;
   }
	 }
   f = chisq;
   /*
   cout<<f<<"   ";
   for(int i=0;i<9;i++)
   {
	   cout<<par[i]<<"   ";
   }
   cout<<endl;
   */
}


void ChiSquare_EH2(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
     for(EBinIdx=0;EBinIdx<5;EBinIdx++)
   {
   //EH2
   for (i=0;i<nbins; i++) {
     double R2P2 = pow(RD_R[1][i][EBinIdx],2.0);
	double RP1, RP2;
	RP1 = FitFunc2(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_2[ii];
	}
	RP2 = FitFunc2(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_Save[ii];
	}
	 R2P2 += pow(RP1-RP2,2.0);

     delta  = (R[1][i][EBinIdx]-FitFunc2(i*WidthOfBin,par));
     chisq += delta*delta/R2P2;
   }
	 }
   f = chisq;
}


void ChiSquare_EH3(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
     for(EBinIdx=0;EBinIdx<5;EBinIdx++)
   {
   //EH3
   for (i=0;i<nbins; i++) {
     double R2P2 = pow(RD_R[2][i][EBinIdx],2.0);
	double RP1, RP2;
	RP1 = FitFunc3(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_2[ii];
	}
	RP2 = FitFunc3(i*WidthOfBin,par);
	for(int ii=0;ii<5;ii++)
	{
		Ave_Energy[ii] = Ave_Energy_Save[ii];
	}
	 R2P2 += pow(RP1-RP2,2.0);

     delta  = (R[2][i][EBinIdx]-FitFunc3(i*WidthOfBin,par));
     chisq += delta*delta/R2P2;
   }
	 }
   f = chisq;
}

void ChiSquare_EH1_this(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH1
   for (i=0;i<nbins; i++) {
     delta  = (R[0][i][EBinIdx]-FitFunc1(i*WidthOfBin,par))/RD_R[0][i][EBinIdx];
     chisq += delta*delta;
   }

   f = chisq;

}


void ChiSquare_EH2_this(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH2
   for (i=0;i<nbins; i++) {
     delta  = (R[1][i][EBinIdx]-FitFunc2(i*WidthOfBin,par))/RD_R[1][i][EBinIdx];
     chisq += delta*delta;
   }
   f = chisq;
}


void ChiSquare_EH3_this(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH3
   for (i=0;i<nbins; i++) {
     delta  = (R[2][i][EBinIdx]-FitFunc3(i*WidthOfBin,par))/RD_R[2][i][EBinIdx];
     chisq += delta*delta;
   }
   f = chisq;
}

TComplex Tauab(int a,int b,double E,double L)//E:MeV,L:m
{
	double L2 = L*5.07e15;//GeV^-1
	double E2 = E*0.001;//GeV
	double EbL = Dm[b][0]*L2/(2.0*E2);
	double EaL = Dm[a][0]*L2/(2.0*E2);
	double Dab = Dm[a][b]*L2/(2.0*E2);
	if(a==b)
	{
		TComplex tau = TComplex(cos(EbL),-sin(EbL));
		return tau;
	}
	else
	{
		TComplex CEbL = TComplex(cos(EbL),-1.0*sin(EbL));
		TComplex CEaL = TComplex(cos(EaL),-1.0*sin(EaL));
		TComplex CEabL = TComplex(0.0,-1.0*Dab);
		TComplex result = (CEbL-CEaL)/CEabL;
		return result;
	}
}

TComplex Mee(double E,double L,int i, int j)//E:MeV,L:m
{
	TComplex  result = TComplex(0.0,0.0);
	for(int a=0;a<3;a++)
	{
		for(int b=0;b<3;b++)
		{
			//result += Tauab(a,b,E,L)*pow(U[0][a],2.0)*pow(U[0][b],2.0);
			result += Tauab(a,b,E,L)*U[0][a]*U[i][a]*U[j][b]*U[0][b];
		}
	}
	return result;

}
TComplex See(double E,double L)//E:MeV,L:m
{
	double L2 = L*5.07e15;//GeV^-1
	double E2 = E*0.001;//GeV

	TComplex  result = TComplex(0.0,0.0);
	TComplex CEjL;
	for(int jj=0;jj<3;jj++)
	{
		double EjL = Dm[jj][0]*L2/(2.0*E2);
		Double_t C1 = cos(EjL)*pow(U[0][jj],2.0);
		Double_t C2 = -1.0*sin(EjL)*pow(U[0][jj],2.0);
		CEjL =  TComplex(C1,C2);
		result += CEjL;
	}
	return result;
}

double ImSeeMee(double E,double L,int i, int j)//E:MeV,L:m
{
	TComplex CSee = See(E,L);
	TComplex CMee = Mee(E,L,i,j);
	TComplex result = (TComplex::Conjugate(CSee))*CMee;
	return result.Im();
}


double Psur(double E,double L)
{
	double L2 = L*5.07e15;//GeV^-1
	double E2 = E*0.001;//GeV
	//cout<<"sin2t132: "<<pow(sin(2.0*Th13),2.0)<<endl;
	//cout<<pow(sin(2.0*Th13),2.0)*pow(sin(1.267*Dm[2][0]*L2/E2),2.0)<<endl;
	return 1 - pow(sin(2.0*Th13),2.0)*pow(sin(0.25*Dm[2][0]*L2/E2),2.0) - pow(cos(Th13),4.0)*pow(sin(2.0*Th12),2.0)*pow(sin(0.25*Dm[1][0]*L2/E2),2.0);
}


double IntExp(double E1,double E2, double P)
{
	//(exp(-P*E1)-exp(-P*E2))/P
	return ((exp(-P*E1)-exp(-P*E2))/P)/((exp(-P*0.7)-exp(-P*12.0))/P);
}
