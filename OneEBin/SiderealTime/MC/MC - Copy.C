

#include <ctime>
#include <cstdlib>

#include <math.h>
#include "TMinuit.h"

double R[3][24]={0.0};
double RD_R[3][24]={0.0};
Double_t ParResult[7],ParErrResult[7];
Double_t ParResult_EH1[7],ParErrResult_EH1[7];
Double_t ParResult_EH2[7],ParErrResult_EH2[7];
Double_t ParResult_EH3[7],ParErrResult_EH3[7];

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
double Table_ImSeeMee[3][6][3][3];//[Hall][Rct][e/mu/tau][e/mu/tau]
void SrandNumber(int Maximum,int number,int RandomArray[]);
//void RandIBD();

double LatHall[3] = {22.598,22.606,22.612};//latitude of the three halls, degree, read from goole maps
	double Ave_Energy = 4.21;
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
	double RotAngl = 9.0*pi/180.0;//9 degrees of rotation

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

	int ShuffleIndex[24];

	double IBD_Total[8]={0.0};
	double FullTime_Weight[8][24]={0.0};
	double IBD_Frac_Exp[8][24]={0.0};
	double IBD_AD_Bin[8][24]={0.0};
	double IBD_AD_Bin_Exp[8][24]={0.0};

	TRandom *myRandom = new TRandom(unsigned(time(0)));
	double RD_Power = 0.009;
	double RD_Eff = 0.0013;
	Double_t CrossSection = 0.94;//Averaged cross-section, in unit of 1e-43 cm^2;

	Double_t Np = 1.43;//Total number of target protons in AD1,AD2, in unit of 1e30
	Double_t FractionInOneDay[3][6][24];
	Double_t AlphaBetaInOneDay[2][24];


	double Table_Chi2_3Site_5Bin[6]={0.0};
	double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
	double Table_Chi2_3Site_1Bin[6]={0.0};
	double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};

	int NOF_3Site_5Bin = 352; //3*5*24-8
	int NOF_SiteBySite_5Bin = 112; //5*24-8
	int NOF_3Site_1Bin = 66; // 3*24-6
	int NOF_SiteBySite_1Bin = 18; //24-6

void MC()
{
	

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
		/*fprintf(stderr,"%5d %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f \n",Hallidx,EveFrac_Hall_Ave[Hallidx][0],EveFrac_Hall_Ave[Hallidx][1],
			EveFrac_Hall_Ave[Hallidx][2],EveFrac_Hall_Ave[Hallidx][3],EveFrac_Hall_Ave[Hallidx][4],EveFrac_Hall_Ave[Hallidx][5],EveFrac_Total[Hallidx]);
			*/
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

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int Rct = 0;Rct<6;Rct++)
		{
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
			Table_ImSeeMee[Hidx][Rct][i][j] = ImSeeMee(Ave_Energy,Baseline_Hall[Hidx][Rct],i,j);
				}
			}
			//fprintf(stderr,"&  %7.4f & %7.4f & %7.4f  & %7.4f & %7.4f &  %7.4f  \\\\ \\hline \n",
				//Table_ImSeeMee[Hidx][Rct][0][0],Table_ImSeeMee[Hidx][Rct][1][1],Table_ImSeeMee[Hidx][Rct][2][2],
				//Table_ImSeeMee[Hidx][Rct][0][1],Table_ImSeeMee[Hidx][Rct][0][2],Table_ImSeeMee[Hidx][Rct][1][2]);
		}
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	
	//IBD candidate
	Double_t IBDInOneDay[8][24];
	Double_t IBD_t[8];
	memset(IBDInOneDay,0.0,sizeof(IBDInOneDay));
	TFile *F_IBD = new TFile("../IBD/IBDInOneDay.root");
	TTree *Tree_IBD = (TTree*)F_IBD->Get("IBDInOneDay");
	Tree_IBD->SetBranchAddress("IBDInOneDay",IBD_t);


	//FullTime
	double FullTimeInOneDay[8][24]={0.0};
	double FullTimeTotal[8] = {0.0};
	Double_t FullTime_t[8];
	memset(FullTimeInOneDay,0.0,sizeof(FullTimeInOneDay));
	TFile *F_FullTime = new TFile("../FullTime/FullTimeInOneDay.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTimeInOneDay");
	Tree_FullTime->SetBranchAddress("FullTimeInOneDay",FullTime_t);

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
	
	Double_t Fraction_t[3][6];
	memset(FractionInOneDay,0.0,sizeof(FractionInOneDay));
	TFile *F_Fraction = new TFile("../Fraction.root");
	TTree *Tree_Fraction = (TTree*)F_Fraction->Get("Fraction");
	Tree_Fraction->SetBranchAddress("Fraction",Fraction_t);

	for(int N24=0;N24<24;N24++)
	{
		Tree_IBD->GetEntry(N24);
		Tree_FullTime->GetEntry(N24);
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
			FullTimeInOneDay[Det][N24] = FullTime_t[Det];
			
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
			FullTimeTotal[Det] += FullTime_t[Det]/MultiEff_t[Det];
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
	
	//IBD total and weight
	memset(IBD_Total,0.0,sizeof(IBD_Total));
	memset(FullTime_Weight,0.0,sizeof(FullTime_Weight));
	
	for(int Det=0;Det<8;Det++)
	{
		for(int N24=0;N24<24;N24++)
		{
		IBD_Total[Det] += IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
		FullTime_Weight[Det][N24] = (FullTimeInOneDay[Det][N24]/MultiEffInOneDay[Det][N24])/FullTimeTotal[Det];

		if(N24!=0)
		{
			FullTime_Weight[Det][N24] += FullTime_Weight[Det][N24-1];
		}

		IBD_AD_Bin_Exp[Det][N24] = IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
		}
		for(int N24=0;N24<24;N24++)
		{
			IBD_Frac_Exp[Det][N24] = IBD_AD_Bin_Exp[Det][N24]/IBD_Total[Det];
		}
	}


	//////////////EH1////////////////////////////////////////////////
	int HallID = 0;

	Double_t M[24];//={0.0};
	memset(M,0.0,sizeof(M));
	Double_t RD_M[24];//={0.0};
	memset(RD_M,0.0,sizeof(RD_M));
	Double_t NBar[24];//
	memset(NBar,0.0,sizeof(NBar));
	Double_t RD_NBar[24];//
	memset(RD_NBar,0.0,sizeof(RD_NBar));

	for(int N24=0;N24<24;N24++)
	{
		for(int Det=0;Det<2;Det++)
		{
			M[N24] += IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
			RD_M[N24] += (IBDInOneDay[Det][N24]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccInOneDay[Det][N24],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9InOneDay[Det][N24],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNInOneDay[Det][N24],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);


		}
		RD_M[N24] += pow(M[N24]*RD_Eff,2.0);

		RD_M[N24] = sqrt(RD_M[N24])/M[N24];
		Double_t temp=0.0,temp2=0.0;
		for(int Rct=0;Rct<6;Rct++)
		{
			temp += FractionInOneDay[HallID][Rct][N24];
			temp2 += pow(FractionInOneDay[HallID][Rct][N24],2.0);
		}

		NBar[N24] = 1.0e-17*Np*CrossSection*temp/(4.0*pi);
		//RD_NBar[N24] = RD_Power;

		R[0][N24] = M[N24]/NBar[N24];
		RD_R[0][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
		//cout<<N24<<"   "<<R[0][N24]<<"   "<<RD_R[0][N24]<<"   "<<endl;
	}

	//////////////EH2////////////////////////////////////////////////
	HallID = 1;
	for(int i=0;i<24;i++)
	{
		M[i]=0.0;
		RD_M[i]=0.0;
		NBar[i]=0.0;
		RD_NBar[i]=0.0;
	}

	for(int N24=0;N24<24;N24++)
	{
		for(int Det=2;Det<4;Det++)
		{
			M[N24] += IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
			RD_M[N24] += (IBDInOneDay[Det][N24]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccInOneDay[Det][N24],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9InOneDay[Det][N24],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNInOneDay[Det][N24],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);


		}
		RD_M[N24] += pow(M[N24]*RD_Eff,2.0);

		RD_M[N24] = sqrt(RD_M[N24])/M[N24];
		Double_t temp=0.0,temp2=0.0;
		for(int Rct=0;Rct<6;Rct++)
		{
			temp += FractionInOneDay[HallID][Rct][N24];
			temp2 += pow(FractionInOneDay[HallID][Rct][N24],2.0);
		}

		NBar[N24] = 1.0e-17*Np*CrossSection*temp/(4.0*pi);
		//RD_NBar[N24] = RD_Power;

		R[1][N24] = M[N24]/NBar[N24];
		RD_R[1][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
		//cout<<N24<<"   "<<R[N24]<<"   "<<RD_R[N24]<<"   "<<RD_M[N24]<<"   "<<endl;
	}

	/////////////////////////////////EH3////////////////////////////////////////////
	HallID = 2;
	Double_t Mf[24]={0.0};//={0.0};
	Double_t RD_Mf[24]={0.0};//={0.0};
	
	Double_t Ma[24]={0.0};//={0.0};
	Double_t RD_Ma[24]={0.0};//={0.0};
	
	Double_t Mb[24]={0.0};//={0.0};
	Double_t RD_Mb[24]={0.0};//={0.0};
	for(int N24=0;N24<24;N24++)
	{
		for(int Det=4;Det<8;Det++)
		{
			Mf[N24] += IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
			RD_Mf[N24] += (IBDInOneDay[Det][N24]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccInOneDay[Det][N24],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9InOneDay[Det][N24],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNInOneDay[Det][N24],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);
		}

		for(int Det=0;Det<2;Det++)
		{
			Ma[N24] += IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
			RD_Ma[N24] += (IBDInOneDay[Det][N24]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccInOneDay[Det][N24],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9InOneDay[Det][N24],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNInOneDay[Det][N24],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);
		}

		for(int Det=2;Det<4;Det++)
		{
			Mb[N24] += IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
			RD_Mb[N24] += (IBDInOneDay[Det][N24]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccInOneDay[Det][N24],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9InOneDay[Det][N24],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNInOneDay[Det][N24],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);
		}

		RD_Mf[N24] += pow(Mf[N24]*RD_Eff,2.0);
		RD_Mf[N24] = sqrt(RD_Mf[N24])/Mf[N24];

		RD_Ma[N24] += pow(Ma[N24]*RD_Eff,2.0);
		RD_Ma[N24] = sqrt(RD_Ma[N24])/Ma[N24];

		RD_Mb[N24] += pow(Mb[N24]*RD_Eff,2.0);
		RD_Mb[N24] = sqrt(RD_Mb[N24])/Mb[N24];

		R[2][N24] = Mf[N24]/((AlphaBetaInOneDay[0][N24]-0.0000)*Ma[N24]+(AlphaBetaInOneDay[1][N24]+0.00)*Mb[N24]);

		RD_R[2][N24] = sqrt(pow(RD_Mf[N24],2.0)+(pow(AlphaBetaInOneDay[0][N24]*Ma[N24]*RD_Ma[N24],2.0)
			+pow(AlphaBetaInOneDay[1][N24]*Mb[N24]*RD_Mb[N24],2.0))/pow(AlphaBetaInOneDay[0][N24]*Ma[N24]+AlphaBetaInOneDay[1][N24]*Mb[N24],2.0)+pow(0.047*RD_Power,2.0));
		//cout<<N24<<"   "<<R[N24]<<"   "<<RD_R[N24]<<"   "<<RD_Ma[N24]<<"   "<<RD_Mb[N24]<<"   "<<RD_Mf[N24]<<"   "<<Mf[N24]<<"   "<<Ma[N24]<<"   "<<Mb[N24]<<"   "<<AlphaBetaInOneDay[0][N24]<<"   "<<AlphaBetaInOneDay[1][N24]<<endl;
	}
	
	//////Normalize EH1 and EH2 to 1.0
	Double_t MeanRatio[3] = {0.0};
	for(int i=0;i<24;i++)
	{
		MeanRatio[0] += R[0][i];
		MeanRatio[1] += R[1][i];
		MeanRatio[2] += R[2][i];
	}
	for(int i=0;i<24;i++)
	{
		R[0][i]=24.0*R[0][i]/MeanRatio[0];
		R[1][i]=24.0*R[1][i]/MeanRatio[1];
		R[2][i]=24.0*R[2][i]/MeanRatio[2];
		//cout<<R[0][i]<<"   "<<RD_R[0][i]<<"   "<<R[1][i]<<"   "<<RD_R[1][i]<<"   "<<R[2][i]<<"   "<<RD_R[2][i]<<"   "<<endl;
	}

	double R_Save[3][24],RD_R_Save[3][24];
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<24;j++)
		{
			R_Save[i][j]=R[i][j];
			RD_R_Save[i][j]=RD_R[i][j];
		}
	}

	//RandIBD();
	double MC_IBD_AD_Bin_t[8][24];
	const int nSample = 1000;

	TFile  *F_MC_IBD_AD_Bin = new TFile("MC_IBD_AD_Bin.root","recreate");
	TTree *Tree_MC_IBD_AD_Bin = new TTree("MC_IBD_AD_Bin","MC_IBD_AD_Bin");
	Tree_MC_IBD_AD_Bin->Branch("MC_IBD_AD_Bin",MC_IBD_AD_Bin_t,"MC_IBD_AD_Bin_t[8][24]/D");
	
	srand(unsigned(time(0)));

	for(int iS=0;iS<nSample;iS++)
	{
		cout<<iS<<endl;
		memset(MC_IBD_AD_Bin_t,0.0,sizeof(MC_IBD_AD_Bin_t));

	for(int Det=0;Det<8;Det++)
	{
		//cout<<"Det: "<<Det<<endl;
		int TotalN = int(IBD_Total[Det]);
		double this_TotalN=0;
		double this_Time;
		int this_TimeBin;

		for(int i_IBD=0;i_IBD<TotalN;i_IBD++)
		{
			this_TimeBin=0;
			this_Time = (rand()%32761)/32760.0;
			for(int N24=0;N24<24;N24++)
			{
				if(this_Time>FullTime_Weight[Det][N24])
				{
					this_TimeBin++;
				}
			}
			if(this_TimeBin>23){this_TimeBin=23;}
			MC_IBD_AD_Bin_t[Det][this_TimeBin] += 1.0;
		}

		/*
		for(int N24=0;N24<24;N24++)
		{

			//IBD_AD_Bin[Det][N24] = (myRandom->Binomial(TotalN,FullTime_Weight[Det][N24]))*1.0;
			//IBD_AD_Bin[Det][N24] = (myRandom->Poisson(IBD_AD_Bin_Exp[Det][N24]))*1.0;
			this_TotalN += int(MC_IBD_AD_Bin_t[Det][N24]);
			if(N24==0){
				cout<<IBD_Frac_Exp[Det][N24]<<"   "<<FullTime_Weight[Det][N24]<<"   "<<MC_IBD_AD_Bin_t[Det][N24]/IBD_Total[Det]<<endl;}
			else{
				cout<<IBD_Frac_Exp[Det][N24]<<"   "<<FullTime_Weight[Det][N24]-FullTime_Weight[Det][N24-1]<<"   "<<MC_IBD_AD_Bin_t[Det][N24]/IBD_Total[Det]<<endl;}
		}
		cout<<"Total IBD:"<<TotalN<<"   "<<this_TotalN<<endl;
		*/
	}
	
	Tree_MC_IBD_AD_Bin->Fill();

	}

	Tree_MC_IBD_AD_Bin->Write();
	
}



Double_t PlotFunc(Double_t *x, Double_t *par)
{
	//0   1   2   3   4   5   6  7 
	//C   A1  A2  A3  A4  B1  B2  HallID
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
	Int_t HallID=int(par[7]);
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = par[0];
	Double_t frac[6];
	Double_t IMSM,Nxt,Nyt,Nzt,E;
	E = Ave_Energy*1.0e-3;
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
		IMSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];
		TotalP  += 2.0*Baseline_Hall[HallID][i]*5.07*(frac[i]/TotalEveFrac)*IMSM*1.0e-3*( 
			(Nyt*par[1]*0.001+2.0*E*Nyt*Nzt*par[2]+Nxt*par[3]*0.001-2.0*E*Nxt*Nzt*par[4])*sin(wP*x[0]) +
			(-1.0*Nxt*par[1]*0.001-2.0*E*Nxt*Nzt*par[2]+Nyt*par[3]*0.001-2.0*E*Nyt*Nzt*par[4])*cos(wP*x[0]) +
			(E*Nxt*Nyt*par[5]-E*(Nxt*Nxt-Nyt*Nyt)*par[6])*sin(2.0*wP*x[0])+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[5]-2.0*E*Nxt*Nyt*par[6])*cos(2.0*wP*x[0]));
	}
	return TotalP;

}

//A1*sinwt + A2 coswt + A3 sin2wt + A4 cos2wt
Double_t FitFunc_Simple(Double_t x, Double_t *par)
{
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	return 1.0+par[0]*sin(wP*x)+par[1]*cos(wP*x)+par[2]*sin(2.0*wP*x)+par[3]*cos(2.0*wP*x);
}

void ChiSquare_EH1_Simple(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH1
   for (i=0;i<nbins; i++) {
     delta  = (R[0][i]-FitFunc_Simple(i*WidthOfBin,par))/(RD_R[0][i]*R[0][i]);
     chisq += delta*delta;
   }

   f = chisq;
}

void ChiSquare_EH1_Const(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH1
   for (i=0;i<nbins; i++) {
     delta  = (R[0][i]-1.0)/(RD_R[0][i]*R[0][i]);
     chisq += delta*delta;
   }

   f = chisq;
}


void ChiSquare_EH2_Simple(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH2
   for (i=0;i<nbins; i++) {
     delta  = (R[1][i]-FitFunc_Simple(i*WidthOfBin,par))/(RD_R[1][i]*R[1][i]);
     chisq += delta*delta;
   }

   f = chisq;
}

void ChiSquare_EH2_Const(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH2
   for (i=0;i<nbins; i++) {
     delta  = (R[1][i]-1.0)/(RD_R[1][i]*R[1][i]);
     chisq += delta*delta;
   }

   f = chisq;
}

void ChiSquare_EH3_Simple(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH3
   for (i=0;i<nbins; i++) {
     delta  = (R[2][i]-FitFunc_Simple(i*WidthOfBin,par))/(RD_R[2][i]*R[2][i]);
     chisq += delta*delta;
   }

   f = chisq;
}


void ChiSquare_EH3_Const(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH3
   for (i=0;i<nbins; i++) {
     delta  = (R[2][i]-1.0)/(RD_R[2][i]*R[2][i]);
     chisq += delta*delta;
   }

   f = chisq;
}

Double_t FitFunc1(Double_t x, Double_t *par)//EH1, C fixed to 1.0
{
	//0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
	Int_t HallID=0;
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = 1.0;
	Double_t frac[6];
	Double_t IMSM,Nxt,Nyt,Nzt,E;
	E = Ave_Energy*1.0e-3;
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
		IMSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];
		TotalP  += 2.0*Baseline_Hall[HallID][i]*5.07*(frac[i]/TotalEveFrac)*IMSM*1.0e-3*( 
			(Nyt*par[1]*0.001+2.0*E*Nyt*Nzt*par[2]+Nxt*par[3]*0.001-2.0*E*Nxt*Nzt*par[4])*sin(wP*x) +
			(-1.0*Nxt*par[1]*0.001-2.0*E*Nxt*Nzt*par[2]+Nyt*par[3]*0.001-2.0*E*Nyt*Nzt*par[4])*cos(wP*x) +
			(E*Nxt*Nyt*par[5]-E*(Nxt*Nxt-Nyt*Nyt)*par[6])*sin(2.0*wP*x)+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[5]-2.0*E*Nxt*Nyt*par[6])*cos(2.0*wP*x));
	}
	return TotalP;

}

Double_t FitFunc2(Double_t x, Double_t *par)//EH2, C fixed to 1.0
{
	//0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
	Int_t HallID=1;
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = 1.0;
	Double_t frac[6];
	Double_t IMSM,Nxt,Nyt,Nzt,E;
	E = Ave_Energy*1.0e-3;
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
		IMSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];
		TotalP  += 2.0*Baseline_Hall[HallID][i]*5.07*(frac[i]/TotalEveFrac)*IMSM*1.0e-3*( 
			(Nyt*par[1]*0.001+2.0*E*Nyt*Nzt*par[2]+Nxt*par[3]*0.001-2.0*E*Nxt*Nzt*par[4])*sin(wP*x) +
			(-1.0*Nxt*par[1]*0.001-2.0*E*Nxt*Nzt*par[2]+Nyt*par[3]*0.001-2.0*E*Nyt*Nzt*par[4])*cos(wP*x) +
			(E*Nxt*Nyt*par[5]-E*(Nxt*Nxt-Nyt*Nyt)*par[6])*sin(2.0*wP*x)+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[5]-2.0*E*Nxt*Nyt*par[6])*cos(2.0*wP*x));
	}
	return TotalP;

}

Double_t FitFunc3(Double_t x, Double_t *par)//EH3, C fixed to 1.0
{
	//0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
	Int_t HallID=2;
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = 1.0;
	Double_t frac[6];
	Double_t IMSM,Nxt,Nyt,Nzt,E;
	E = Ave_Energy*1.0e-3;
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
		IMSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];
		TotalP  += 2.0*Baseline_Hall[HallID][i]*5.07*(frac[i]/TotalEveFrac)*IMSM*1.0e-3*( 
			(Nyt*par[1]*0.001+2.0*E*Nyt*Nzt*par[2]+Nxt*par[3]*0.001-2.0*E*Nxt*Nzt*par[4])*sin(wP*x) +
			(-1.0*Nxt*par[1]*0.001-2.0*E*Nxt*Nzt*par[2]+Nyt*par[3]*0.001-2.0*E*Nyt*Nzt*par[4])*cos(wP*x) +
			(E*Nxt*Nyt*par[5]-E*(Nxt*Nxt-Nyt*Nyt)*par[6])*sin(2.0*wP*x)+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[5]-2.0*E*Nxt*Nyt*par[6])*cos(2.0*wP*x));
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
   for (i=0;i<nbins; i++) {
     delta  = (R[0][i]-FitFunc1(i*WidthOfBin,par))/(RD_R[0][i]*R[0][i]);
     chisq += delta*delta;
   }
   //EH2
   for (i=0;i<nbins; i++) {
     delta  = (R[1][i]-FitFunc2(i*WidthOfBin,par))/(RD_R[1][i]*R[1][i]);
     chisq += delta*delta;
   }
   //EH3
   for (i=0;i<nbins; i++) {
     delta  = (R[2][i]-FitFunc3(i*WidthOfBin,par))/(RD_R[2][i]*R[2][i]);
     chisq += delta*delta;
   }

   f = chisq;
}

void ChiSquare_EH1(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH1
   for (i=0;i<nbins; i++) {
     delta  = (R[0][i]-FitFunc1(i*WidthOfBin,par))/(RD_R[0][i]*R[0][i]);
     chisq += delta*delta;
   }

   f = chisq;
   /*
    cout<<f<<"   ";
   for(int i=0;i<6;i++)
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

   //EH2
   for (i=0;i<nbins; i++) {
     delta  = (R[1][i]-FitFunc2(i*WidthOfBin,par))/(RD_R[1][i]*R[1][i]);
     chisq += delta*delta;
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

   //EH3
   for (i=0;i<nbins; i++) {
     delta  = (R[2][i]-FitFunc3(i*WidthOfBin,par))/(RD_R[2][i]*R[2][i]);
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

//随机产生number个范围为【0，Maximum-1】的互不相同的数,放到数组RandomArray[]中
void SrandNumber(int Maximum,int number,int RandomArray[])//Maximum = 24; number = 24
{
	int * temp = new int[Maximum];
	for(int i = 0;i<Maximum;i++)
	{
		temp[i]=i;
	}

	
	for(int j = 0;j<number;j++)
	{
		int n= rand()%Maximum;
		while(temp[n]==-1)
		{
			n = rand()%Maximum;
		}
		RandomArray[j] = temp[n];
		temp[n]=-1;
	}
	delete [] temp;
}
