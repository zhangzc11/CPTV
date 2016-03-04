

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


	double Table_Chi2_3Site_5Bin[6]={0.0};
	double Table_Chi2_SiteBySite_5Bin[3][6]={0.0};
	double Table_Chi2_3Site_1Bin[6]={0.0};
	double Table_Chi2_SiteBySite_1Bin[3][6]={0.0};

	int NOF_3Site_5Bin = 352; //3*5*24-8
	int NOF_SiteBySite_5Bin = 112; //5*24-8
	int NOF_3Site_1Bin = 66; // 3*24-6
	int NOF_SiteBySite_1Bin = 18; //24-6

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

void ThreeSites_Chi2()
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


	
	//normal simple-5P fit:
	double normal_5P[3][4];
	double normal_5P_Err[3][4];

	double Chi2_Flat_Real[3];
	double Chi2_Sid_Real[3];

	for(int Hidx=0;Hidx<3;Hidx++)
	{
/////////////////////
   TMinuit *gMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 5 params
   if(Hidx==0){
	   gMinuit->SetFCN(ChiSquare_EH1_Simple);}
   if(Hidx==1){
	   gMinuit->SetFCN(ChiSquare_EH2_Simple);}
   if(Hidx==2){
	   gMinuit->SetFCN(ChiSquare_EH3_Simple);}

   Double_t arglist[10];
   Int_t ierflg = 0;
   gMinuit->SetPrintLevel(-1);
   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   Double_t vstart[6] = {0};
   Double_t step[6] = {0.01,0.01,0.01,0.01};
   gMinuit->mnparm(0, "A1", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A2", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A3", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A4", vstart[3], step[3], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 2000;
   arglist[1] = 1.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

   Chi2_Sid_Real[Hidx] = amin;
   //gMinuit->mnprin(3,amin);
   //gMinuit->SetPrintLevel(-1);
   /////////////////
	}

	//const fit
	for(int Hidx=0;Hidx<3;Hidx++)
	{
/////////////////////
   TMinuit *gMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 5 params
   if(Hidx==0){
	   gMinuit->SetFCN(ChiSquare_EH1_Const);}
   if(Hidx==1){
	   gMinuit->SetFCN(ChiSquare_EH2_Const);}
   if(Hidx==2){
	   gMinuit->SetFCN(ChiSquare_EH3_Const);}

   Double_t arglist[10];
   Int_t ierflg = 0;
   gMinuit->SetPrintLevel(-1);
   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   Double_t vstart[6] = {0};
   Double_t step[6] = {0.01,0.01,0.01,0.01};
   gMinuit->mnparm(0, "A1", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A2", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A3", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A4", vstart[3], step[3], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 2000;
   arglist[1] = 1.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

   Chi2_Flat_Real[Hidx] = amin;
   //gMinuit->mnprin(3,amin);
   //gMinuit->SetPrintLevel(-1);
   ///const fit
   /////////////////
	}


	//shuffle the simple fit result
	double Shuffle_5P_Mean[3][4];
	double Shuffle_5P_Sigma[3][4];

	double Shuffle_5P_E_Mean[3][4];
	double Shuffle_5P_E_Sigma[3][4];

	const int nSample = 1000;
	srand(unsigned(time(0)));
	double R_Save[3][24],RD_R_Save[3][24];
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<24;j++)
		{
			R_Save[i][j]=R[i][j];
			RD_R_Save[i][j]=RD_R[i][j];
		}
	}
	//
	

	TCanvas *myC_Flat[3];
	TCanvas *myC_Sid[3];
	TCanvas *myC_E[3];

	const char* c_Name_Flat[3] = {"EH1_Flat","EH2_Flat","EH3_Flat"};
	const char* c_Name_Sid[3] = {"EH1_Sid","EH2_Sid","EH3_Sid"};

	const char* file_Name_Flat[3] = {"Shuffle/Chi2One/Simple_Shuffle_EH1_Flat.root","Shuffle/Chi2One/Simple_Shuffle_EH2_Flat.root","Shuffle/Chi2One/Simple_Shuffle_EH3_Flat.root"};
	const char* file_Name_2_Flat[3] = {"Shuffle/Chi2One/Simple_Shuffle_EH1_Flat.jpg","Shuffle/Chi2One/Simple_Shuffle_EH2_Flat.jpg","Shuffle/Chi2One/Simple_Shuffle_EH3_Flat.jpg"};

	const char* file_Name_Sid[3] = {"Shuffle/Chi2One/Simple_Shuffle_EH1_Sid.root","Shuffle/Chi2One/Simple_Shuffle_EH2_Sid.root","Shuffle/Chi2One/Simple_Shuffle_EH3_Sid.root"};
	const char* file_Name_2_Sid[3] = {"Shuffle/Chi2One/Simple_Shuffle_EH1_Sid.jpg","Shuffle/Chi2One/Simple_Shuffle_EH2_Sid.jpg","Shuffle/Chi2One/Simple_Shuffle_EH3_Sid.jpg"};

	double Error_Mean[3]={0.002392,0.002441,0.0041};

	Double_t MC_IBD_AD_Bin_t[8][24];
	TFile *F_MC_IBD_AD_Bin = new TFile("MC_IBD_AD_Bin.root");
	TTree *Tree_MC_IBD_AD_Bin = (TTree*)F_MC_IBD_AD_Bin->Get("MC_IBD_AD_Bin");
	Tree_MC_IBD_AD_Bin->SetBranchAddress("MC_IBD_AD_Bin",MC_IBD_AD_Bin_t);

	TH1F *hist_Chi2_Flat[3];		
	TH1F *hist_Chi2_Sid[3];			
	TH1F *hist_Chi2_Real_Flat[3];	
	TH1F *hist_Chi2_Real_Sid[3];	
	TLegend *leg_Flat[3];
	TLegend *leg2_Flat[3];
	TLegend *leg_Sid[3];
	TLegend *leg2_Sid[3];

	const char* chi2_Name_Flat_MC[3] = {"EH1_Chi2 flat - MC","EH2_Chi2 flat - MC","EH3_Chi2 flat - MC"};
	const char* chi2_Name_Sid_MC[3] = {"EH1_Chi2 sid - MC","EH2_Chi2 sid - MC","EH3_Chi2 sid - MC"};

	const char* chi2_Name_Flat_Real[3] = {"EH1_Chi2 flat - Real","EH2_Chi2 flat - Real","EH3_Chi2 flat - Real"};
	const char* chi2_Name_Sid_Real[3] = {"EH1_Chi2 sid - Real","EH2_Chi2 sid - Real","EH3_Chi2 sid - Real"};


	//A1*sinwt + A2 coswt + A3 sin2wt + A4 cos2wt
	for(int Hidx=0;Hidx<3;Hidx++)
	{

	hist_Chi2_Flat[Hidx]		= new TH1F(chi2_Name_Flat_MC[Hidx],chi2_Name_Flat_MC[Hidx],50,0,2.0);
	hist_Chi2_Sid[Hidx]			= new TH1F(chi2_Name_Sid_MC[Hidx],chi2_Name_Sid_MC[Hidx],50,0,2.0);
	hist_Chi2_Real_Flat[Hidx]	= new TH1F(chi2_Name_Flat_Real[Hidx],chi2_Name_Flat_Real[Hidx],nSample,0,2.0);
	hist_Chi2_Real_Sid[Hidx]	= new TH1F(chi2_Name_Sid_Real[Hidx],chi2_Name_Sid_Real[Hidx],nSample,0,2.0);

	for(int iS=0;iS<nSample;iS++)
	{
		//cout<<iS<<endl;
		Double_t Chi2_Flat=0.0;	
		Double_t Chi2_Sid=0.0;	
double RD_Power_MC;// = myRandom->Gaus(1.00,RD_Power);
	double RD_Eff_MC;// = myRandom->Gaus(1.00,RD_Eff);
	double RD_Sys_MC;
	Tree_MC_IBD_AD_Bin->GetEntry(iS);
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
		RD_Power_MC = myRandom->Gaus(1.00,RD_Power);
		RD_Eff_MC = myRandom->Gaus(1.00,RD_Eff);

		for(int Det=0;Det<2;Det++)
		{
			 //IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				//(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
			M[N24] +=MC_IBD_AD_Bin_t[Det][N24];
			RD_M[N24] += (MC_IBD_AD_Bin_t[Det][N24] + (AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24])/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])+
					(pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
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

		RD_Sys_MC = myRandom->Gaus(1.0,sqrt(pow(RD_Eff,2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0)));

		R[0][N24] = RD_Sys_MC*M[N24]/NBar[N24];
		RD_R[0][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
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
		RD_Power_MC = myRandom->Gaus(1.00,RD_Power);
		RD_Eff_MC = myRandom->Gaus(1.00,RD_Eff);
		for(int Det=2;Det<4;Det++)
		{
			M[N24] +=MC_IBD_AD_Bin_t[Det][N24];
			RD_M[N24] += (MC_IBD_AD_Bin_t[Det][N24] + (AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24])/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])+
					(pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
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

		RD_Sys_MC = myRandom->Gaus(1.0,sqrt(pow(RD_Eff,2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0)));

		R[1][N24] = RD_Sys_MC*M[N24]/NBar[N24];
		RD_R[1][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
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
		RD_Power_MC = myRandom->Gaus(1.00,RD_Power);
		RD_Eff_MC = myRandom->Gaus(1.00,RD_Eff);

		//RD_Sys_MC = 0.0;

		for(int Det=4;Det<8;Det++)
		{
			Mf[N24] +=MC_IBD_AD_Bin_t[Det][N24];
			RD_Mf[N24] += (MC_IBD_AD_Bin_t[Det][N24] + (AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24])/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])+
					(pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccInOneDay[Det][N24],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9InOneDay[Det][N24],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNInOneDay[Det][N24],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);
		}

		for(int Det=0;Det<2;Det++)
		{
			Ma[N24] +=MC_IBD_AD_Bin_t[Det][N24];
			RD_Ma[N24] += (MC_IBD_AD_Bin_t[Det][N24] + (AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24])/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])+
					(pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccInOneDay[Det][N24],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9InOneDay[Det][N24],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNInOneDay[Det][N24],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);
		}

		for(int Det=2;Det<4;Det++)
		{
			Mb[N24] +=MC_IBD_AD_Bin_t[Det][N24];
			RD_Mb[N24] += (MC_IBD_AD_Bin_t[Det][N24] + (AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24])/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])+
					(pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
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


		RD_Sys_MC = myRandom->Gaus(1.0,sqrt(pow(RD_Eff,2.0)+(pow(AlphaBetaInOneDay[0][N24]*Ma[N24]*RD_Eff,2.0)
			+pow(AlphaBetaInOneDay[1][N24]*Mb[N24]*RD_Eff,2.0))/pow(AlphaBetaInOneDay[0][N24]*Ma[N24]+AlphaBetaInOneDay[1][N24]*Mb[N24],2.0)+pow(0.047*RD_Power,2.0)));

		R[2][N24] = RD_Sys_MC*Mf[N24]/((AlphaBetaInOneDay[0][N24]-0.0000)*Ma[N24]+(AlphaBetaInOneDay[1][N24]+0.00)*Mb[N24]);

		RD_R[2][N24] = sqrt(pow(RD_Mf[N24],2.0)+(pow(AlphaBetaInOneDay[0][N24]*Ma[N24]*RD_Ma[N24],2.0)
			+pow(AlphaBetaInOneDay[1][N24]*Mb[N24]*RD_Mb[N24],2.0))/pow(AlphaBetaInOneDay[0][N24]*Ma[N24]+AlphaBetaInOneDay[1][N24]*Mb[N24],2.0)+pow(0.047*RD_Power,2.0));
	}
	
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
		

/////////////////////
   TMinuit *gMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 5 params
   if(Hidx==0){
	   gMinuit->SetFCN(ChiSquare_EH1_Simple);}
   if(Hidx==1){
	   gMinuit->SetFCN(ChiSquare_EH2_Simple);}
   if(Hidx==2){
	   gMinuit->SetFCN(ChiSquare_EH3_Simple);}

   Double_t arglist[10];
   Int_t ierflg = 0;
   gMinuit->SetPrintLevel(-1);
   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   Double_t vstart[6] = {0};
   Double_t step[6] = {0.01,0.01,0.01,0.01};
   gMinuit->mnparm(0, "A1", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A2", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A3", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A4", vstart[3], step[3], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 2000;
   arglist[1] = 1.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   //gMinuit->mnprin(3,amin);
   //gMinuit->SetPrintLevel(-1);
   //hist_Chi2->Fill(amin);
   Chi2_Sid = amin;

   ////////////////const fit
   TMinuit *gMinuit_const = new TMinuit(4);  //initialize TMinuit with a maximum of 5 params
   if(Hidx==0){
	   gMinuit_const->SetFCN(ChiSquare_EH1_Const);}
   if(Hidx==1){
	   gMinuit_const->SetFCN(ChiSquare_EH2_Const);}
   if(Hidx==2){
	   gMinuit_const->SetFCN(ChiSquare_EH3_Const);}

   Double_t arglist_const[10];
   Int_t ierflg_const = 0;
   gMinuit_const->SetPrintLevel(-1);
   arglist_const[0] = 1;
   gMinuit_const->mnexcm("SET ERR", arglist_const ,1,ierflg_const);

// Set starting values and step_const sizes for parameters
   Double_t vstart_const[6] = {0};
   Double_t step_const[6] = {0.01,0.01,0.01,0.01};
   gMinuit_const->mnparm(0, "A1", vstart_const[0], step_const[0], 0,0,ierflg_const);
   gMinuit_const->mnparm(1, "A2", vstart_const[1], step_const[1], 0,0,ierflg_const);
   gMinuit_const->mnparm(2, "A3", vstart_const[2], step_const[2], 0,0,ierflg_const);
   gMinuit_const->mnparm(3, "A4", vstart_const[3], step_const[3], 0,0,ierflg_const);

// Now ready for minimization step_const
   arglist_const[0] = 2000;
   arglist_const[1] = 1.;
   gMinuit_const->mnexcm("MIGRAD", arglist_const ,2,ierflg_const);

// Print results
   Double_t amin_const,edm_const,errdef_const;
   Int_t nvpar_const,nparx_const,icstat_const;
   gMinuit_const->mnstat(amin_const,edm_const,errdef_const,nvpar_const,nparx_const,icstat_const);
   //gMinuit_const->mnprin(3,amin_const);
   //gMinuit_const->SetPrintLevel(-1);
   //hist_Chi2->Fill(amin_const);
   Chi2_Flat = amin_const;
   
   hist_Chi2_Flat[Hidx]->Fill(Chi2_Flat/23.0);
   hist_Chi2_Sid[Hidx]->Fill(Chi2_Sid/19.0);

	}

	for(int i=0;i<400;i++)
	{
		hist_Chi2_Real_Flat[Hidx]->Fill(Chi2_Flat_Real[Hidx]/23.0);
		hist_Chi2_Real_Sid[Hidx]->Fill(Chi2_Sid_Real[Hidx]/19.0);
	}

	myC_Flat[Hidx] =  new TCanvas(c_Name_Flat[Hidx],c_Name_Flat[Hidx],200,10,800,600);
	gStyle->SetOptStat(0);
	hist_Chi2_Flat[Hidx]->Draw();
	//hist_Chi2->GetYaxis()->SetUserRange(0,400);
	hist_Chi2_Flat[Hidx]->SetLineColor(kBlue);
	hist_Chi2_Flat[Hidx]->SetLineWidth(3);
	hist_Chi2_Flat[Hidx]->GetXaxis()->SetLabelSize(0.05);
	hist_Chi2_Flat[Hidx]->GetXaxis()->SetTitle("#chi^{2}_{Flat}/ndf");
	hist_Chi2_Flat[Hidx]->GetYaxis()->SetLabelSize(0.04);
	hist_Chi2_Flat[Hidx]->GetYaxis()->SetTitle("Entries");

	hist_Chi2_Flat[Hidx]->GetYaxis()->SetTitleOffset(0.9);
	hist_Chi2_Flat[Hidx]->GetYaxis()->SetTitleSize(0.05);
	hist_Chi2_Flat[Hidx]->GetXaxis()->SetTitleOffset(0.8);
	hist_Chi2_Flat[Hidx]->GetXaxis()->SetTitleSize(0.05);

	hist_Chi2_Flat[Hidx]->SetTitle("");
	hist_Chi2_Real_Flat[Hidx]->Draw("same");
	hist_Chi2_Real_Flat[Hidx]->SetLineColor(kRed);
	hist_Chi2_Real_Flat[Hidx]->SetLineWidth(3);
	hist_Chi2_Real_Flat[Hidx]->SetTitle("");
	leg_Flat[Hidx] = new TLegend(0.6, 0.75, 0.9, 0.9);
	leg_Flat[Hidx]->AddEntry(hist_Chi2_Flat[Hidx],"MC","l");
	leg_Flat[Hidx]->AddEntry(hist_Chi2_Real_Flat[Hidx],"Data","l");
	leg_Flat[Hidx]->SetFillStyle(0);
	leg_Flat[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
	leg_Flat[Hidx]->Draw();

	leg2_Flat[Hidx] = new TLegend(0.5, 0.5, 0.9, 0.7);
	leg2_Flat[Hidx]->AddEntry(hist_Chi2_Flat[Hidx],c_Name_Flat[Hidx],"");
	leg2_Flat[Hidx]->SetFillStyle(0);
	leg2_Flat[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
	leg2_Flat[Hidx]->Draw();
	myC_Flat[Hidx]->SaveAs(file_Name_2_Flat[Hidx]);
		////////////
	myC_Sid[Hidx] =  new TCanvas(c_Name_Sid[Hidx],c_Name_Sid[Hidx],200,10,800,600);
	gStyle->SetOptStat(0);
	hist_Chi2_Sid[Hidx]->Draw();
	//hist_Chi2->GetYaxis()->SetUserRange(0,400);
	hist_Chi2_Sid[Hidx]->SetLineColor(kBlue);
	hist_Chi2_Sid[Hidx]->SetLineWidth(3);
	hist_Chi2_Sid[Hidx]->GetXaxis()->SetLabelSize(0.05);
	hist_Chi2_Sid[Hidx]->GetXaxis()->SetTitle("#chi^{2}_{Sid}/ndf");
	hist_Chi2_Sid[Hidx]->GetYaxis()->SetLabelSize(0.04);
	hist_Chi2_Sid[Hidx]->GetYaxis()->SetTitle("Entries");

	hist_Chi2_Sid[Hidx]->GetYaxis()->SetTitleOffset(0.9);
	hist_Chi2_Sid[Hidx]->GetYaxis()->SetTitleSize(0.05);
	hist_Chi2_Sid[Hidx]->GetXaxis()->SetTitleOffset(0.8);
	hist_Chi2_Sid[Hidx]->GetXaxis()->SetTitleSize(0.05);

	hist_Chi2_Sid[Hidx]->SetTitle("");
	hist_Chi2_Real_Sid[Hidx]->Draw("same");
	hist_Chi2_Real_Sid[Hidx]->SetLineColor(kRed);
	hist_Chi2_Real_Sid[Hidx]->SetLineWidth(3);
	hist_Chi2_Real_Sid[Hidx]->SetTitle("");
	leg_Sid[Hidx] = new TLegend(0.6, 0.75, 0.9, 0.9);
	leg_Sid[Hidx]->AddEntry(hist_Chi2_Sid[Hidx],"MC","l");
	leg_Sid[Hidx]->AddEntry(hist_Chi2_Real_Sid[Hidx],"Data","l");
	leg_Sid[Hidx]->SetFillStyle(0);
	leg_Sid[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
	leg_Sid[Hidx]->Draw();

	leg2_Sid[Hidx] = new TLegend(0.5, 0.5, 0.9, 0.7);
	leg2_Sid[Hidx]->AddEntry(hist_Chi2_Sid[Hidx],c_Name_Sid[Hidx],"");
	leg2_Sid[Hidx]->SetFillStyle(0);
	leg2_Sid[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
	leg2_Sid[Hidx]->Draw();
	myC_Sid[Hidx]->SaveAs(file_Name_2_Sid[Hidx]);

	}

	//TH1F *hist_Chi2_Flat[3];		
	//TH1F *hist_Chi2_Sid[3];			
	//TH1F *hist_Chi2_Real_Flat[3];	
	//TH1F *hist_Chi2_Real_Sid[3];	

	TCanvas *myC_One =  new TCanvas("Chi2 - Canv","Chi2 - Canv",200,10,1200,800);
	myC_One->Divide(3,2);
	myC_One->cd(1);
	hist_Chi2_Flat[0]->Draw();
	hist_Chi2_Real_Flat[0]->Draw("same");
	leg_Flat[0]->Draw();
	leg2_Flat[0]->Draw();
	myC_One->cd(2);
	hist_Chi2_Flat[1]->Draw();
	hist_Chi2_Real_Flat[1]->Draw("same");
	leg_Flat[1]->Draw();
	leg2_Flat[1]->Draw();
	myC_One->cd(3);
	hist_Chi2_Flat[2]->Draw();
	hist_Chi2_Real_Flat[2]->Draw("same");
	leg_Flat[2]->Draw();
	leg2_Flat[2]->Draw();
	myC_One->cd(4);
	hist_Chi2_Sid[0]->Draw();
	hist_Chi2_Real_Sid[0]->Draw("same");
	leg_Sid[0]->Draw();
	leg2_Sid[0]->Draw();
	myC_One->cd(5);
	hist_Chi2_Sid[1]->Draw();
	hist_Chi2_Real_Sid[1]->Draw("same");
	leg_Sid[1]->Draw();
	leg2_Sid[1]->Draw();
	myC_One->cd(6);
	hist_Chi2_Sid[2]->Draw();
	hist_Chi2_Real_Sid[2]->Draw("same");
	leg_Sid[2]->Draw();
	leg2_Sid[2]->Draw();
	myC_One->SaveAs("Shuffle/Chi2One/Simple_Shuffle_One.jpg");
	myC_One->SaveAs("Shuffle/Chi2One/Simple_Shuffle_One.root");

	cout<<"Real data Chi2_Flat:"<<endl;
	cout<<Chi2_Flat_Real[0]<<"   "<<Chi2_Flat_Real[1]<<"   "<<Chi2_Flat_Real[2]<<endl;
	
	cout<<"Real data Chi2_Sid:"<<endl;
	cout<<Chi2_Sid_Real[0]<<"   "<<Chi2_Sid_Real[1]<<"   "<<Chi2_Sid_Real[2]<<endl;

	/*
	////////////////////////////////////////////////////Fit////////////////////////////////////////////////////////////////////////////////////////////////////
  
   TMinuit *gMinuit = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
   gMinuit->SetFCN(ChiSquare);

   Double_t arglist[10];
   Int_t ierflg = 0;

   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   Double_t vstart[7] = {0.9,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0};
   Double_t step[7] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01};
   gMinuit->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg);
   gMinuit->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg);
   gMinuit->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg);
   gMinuit->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 2000;
   arglist[1] = 40000.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   gMinuit->mnprin(3,amin);

   //0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
   //Double_t ParResult[7],ParErrResult[7];
   for(int i=0;i<7;i++)
   {
	   Double_t v,ev;
	   gMinuit->GetParameter(i,v,ev);
	   ParResult[i]=v;
	   ParErrResult[i]=ev;
   }

   
   ////////////////////////////////////////////////////Fit site by site (EH1 only)////////////////////////////////////////////////////////////////////////////////////////////////////
   TMinuit *gMinuit_EH1 = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
   gMinuit_EH1->SetFCN(ChiSquare_EH1);

   Double_t arglist_EH1[10];
   Int_t ierflg_EH1 = 0;

   arglist_EH1[0] = 1;
   gMinuit_EH1->mnexcm("SET ERR", arglist_EH1 ,1,ierflg_EH1);

// Set starting values and step_EH1 sizes for parameters
   Double_t vstart_EH1[7] = {1.0,0,0,0,0,0,0};
   Double_t step_EH1[7] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01};
   gMinuit_EH1->mnparm(0, "C", vstart_EH1[0], step_EH1[0], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(1, "A1", vstart_EH1[1], step_EH1[1], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(2, "A2", vstart_EH1[2], step_EH1[2], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(3, "A3", vstart_EH1[3], step_EH1[3], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(4, "A4", vstart_EH1[4], step_EH1[4], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(5, "B1", vstart_EH1[5], step_EH1[5], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(6, "B2", vstart_EH1[6], step_EH1[6], 0,0,ierflg_EH1);

// Now ready for minimization step_EH1
   arglist_EH1[0] = 2000;
   arglist_EH1[1] = 5000.;
   gMinuit_EH1->mnexcm("MIGRAD", arglist_EH1 ,2,ierflg_EH1);

// Print results
   Double_t amin_EH1,edm_EH1,errdef_EH1;
   Int_t nvpar_EH1,nparx_EH1,icstat_EH1;
   gMinuit_EH1->mnstat(amin_EH1,edm_EH1,errdef_EH1,nvpar_EH1,nparx_EH1,icstat_EH1);
   gMinuit_EH1->mnprin(3,amin_EH1);

   //0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
   //Double_t ParResult_EH1[7],ParErrResult_EH1[7];
   for(int i=0;i<7;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH1->GetParameter(i,v,ev);
	   ParResult_EH1[i]=v;
	   ParErrResult_EH1[i]=ev;
   }

   

   ////////////////////////////////////////////////////Fit site by site (EH2 only)////////////////////////////////////////////////////////////////////////////////////////////////////
   TMinuit *gMinuit_EH2 = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
   gMinuit_EH2->SetFCN(ChiSquare_EH2);

   Double_t arglist_EH2[10];
   Int_t ierflg_EH2 = 0;

   arglist_EH2[0] = 1;
   gMinuit_EH2->mnexcm("SET ERR", arglist_EH2 ,1,ierflg_EH2);

// Set starting values and step_EH2 sizes for parameters
   Double_t vstart_EH2[7] = {1.0,0,0,0,0,0,0};
   Double_t step_EH2[7] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01};
   gMinuit_EH2->mnparm(0, "C", vstart_EH2[0], step_EH2[0], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(1, "A1", vstart_EH2[1], step_EH2[1], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(2, "A2", vstart_EH2[2], step_EH2[2], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(3, "A3", vstart_EH2[3], step_EH2[3], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(4, "A4", vstart_EH2[4], step_EH2[4], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(5, "B1", vstart_EH2[5], step_EH2[5], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(6, "B2", vstart_EH2[6], step_EH2[6], 0,0,ierflg_EH2);

// Now ready for minimization step_EH2
   arglist_EH2[0] = 2000;
   arglist_EH2[1] = 5000.;
   gMinuit_EH2->mnexcm("MIGRAD", arglist_EH2 ,2,ierflg_EH2);

// Print results
   Double_t amin_EH2,edm_EH2,errdef_EH2;
   Int_t nvpar_EH2,nparx_EH2,icstat_EH2;
   gMinuit_EH2->mnstat(amin_EH2,edm_EH2,errdef_EH2,nvpar_EH2,nparx_EH2,icstat_EH2);
   gMinuit_EH2->mnprin(3,amin_EH2);

   //0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
   //Double_t ParResult_EH2[7],ParErrResult_EH2[7];
   for(int i=0;i<7;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH2->GetParameter(i,v,ev);
	   ParResult_EH2[i]=v;
	   ParErrResult_EH2[i]=ev;
   }
   



   ////////////////////////////////////////////////////Fit site by site (EH3 only)////////////////////////////////////////////////////////////////////////////////////////////////////
   TMinuit *gMinuit_EH3 = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
   gMinuit_EH3->SetFCN(ChiSquare_EH3);

   Double_t arglist_EH3[10];
   Int_t ierflg_EH3 = 0;

   arglist_EH3[0] = 1;
   gMinuit_EH3->mnexcm("SET ERR", arglist_EH3 ,1,ierflg_EH3);

// Set starting values and step_EH3 sizes for parameters
   Double_t vstart_EH3[7] = {1.0,0,0,0,0,0,0};
   Double_t step_EH3[7] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01};
   gMinuit_EH3->mnparm(0, "C", vstart_EH3[0], step_EH3[0], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(1, "A1", vstart_EH3[1], step_EH3[1], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(2, "A2", vstart_EH3[2], step_EH3[2], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(3, "A3", vstart_EH3[3], step_EH3[3], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(4, "A4", vstart_EH3[4], step_EH3[4], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(5, "B1", vstart_EH3[5], step_EH3[5], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(6, "B2", vstart_EH3[6], step_EH3[6], 0,0,ierflg_EH3);

// Now ready for minimization step_EH3
   arglist_EH3[0] = 2000;
   arglist_EH3[1] = 5000.;
   gMinuit_EH3->mnexcm("MIGRAD", arglist_EH3 ,2,ierflg_EH3);

// Print results
   Double_t amin_EH3,edm_EH3,errdef_EH3;
   Int_t nvpar_EH3,nparx_EH3,icstat_EH3;
   gMinuit_EH3->mnstat(amin_EH3,edm_EH3,errdef_EH3,nvpar_EH3,nparx_EH3,icstat_EH3);
   gMinuit_EH3->mnprin(3,amin_EH3);

   //0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
   //Double_t ParResult_EH3[7],ParErrResult_EH3[7];
   for(int i=0;i<7;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH3->GetParameter(i,v,ev);
	   ParResult_EH3[i]=v;
	   ParErrResult_EH3[i]=ev;
   }
   ///////////print
   fprintf(stderr,"fit result(three sites):\n");
   fprintf(stderr,"C          &$%3.4f  \\pm  %3.4f$  &$%3.4f  \\pm  %3.4f$  &$%3.4f  \\pm  %3.4f$  &$%3.4f  \\pm  %3.4f$  \\\\ \n",ParResult[0],ParErrResult[0],ParResult_EH1[0],ParErrResult_EH1[0],ParResult_EH2[0],ParErrResult_EH2[0],ParResult_EH3[0],ParErrResult_EH3[0]);
   fprintf(stderr,"$A_1$/GeV  &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-21}$ &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-21}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-21}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-21}$  \\\\  \n",ParResult[1],ParErrResult[1],ParResult_EH1[1],ParErrResult_EH1[1],ParResult_EH2[1],ParErrResult_EH2[1],ParResult_EH3[1],ParErrResult_EH3[1]);
   fprintf(stderr,"$A_2$      &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$ &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$   \\\\ \n",ParResult[2],ParErrResult[2],ParResult_EH1[2],ParErrResult_EH1[2],ParResult_EH2[2],ParErrResult_EH2[2],ParResult_EH3[2],ParErrResult_EH3[2]);
   fprintf(stderr,"$A_3$/GeV  &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-21}$ &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-21}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-21}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-21}$   \\\\ \n",ParResult[3],ParErrResult[3],ParResult_EH1[3],ParErrResult_EH1[3],ParResult_EH2[3],ParErrResult_EH2[3],ParResult_EH3[3],ParErrResult_EH3[3]);
   fprintf(stderr,"$A_4$      &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$ &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$   \\\\ \n",ParResult[4],ParErrResult[4],ParResult_EH1[4],ParErrResult_EH1[4],ParResult_EH2[4],ParErrResult_EH2[4],ParResult_EH3[4],ParErrResult_EH3[4]);
   fprintf(stderr,"$B_1$      &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$ &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$   \\\\ \n",ParResult[5],ParErrResult[5],ParResult_EH1[5],ParErrResult_EH1[5],ParResult_EH2[5],ParErrResult_EH2[5],ParResult_EH3[5],ParErrResult_EH3[5]);
   fprintf(stderr,"$B_2$      &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$ &$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$&$(%3.1f  \\pm  %3.1f)\\times 10 ^{-18}$   \\\\ \\hline \n",ParResult[6],ParErrResult[6],ParResult_EH1[6],ParErrResult_EH1[6],ParResult_EH2[6],ParErrResult_EH2[6],ParResult_EH3[6],ParErrResult_EH3[6]);

   
	////////////////////////////////////////////////////Draw////////////////////////////////////////////////////////////////////////////////////////////////////
	const Int_t n = 24;

	//////points
	TCanvas *myC[3];
	TGraphErrors *gr[3];
	TLegend* leg[3];
	TLegend* leg2[3];
	TF1 *f_Plot[3];
	TF1 *f_Plot_single[3];
	const char *c_Name[3]={"EH1: Full energy range","EH2: Full energy range","EH3: Full energy range"};
	const char *c_Name_single[3]={"EH1 Only","EH2 Only","EH3 Only"};
	const char *file_Name[3]={"ThreeSites/Ratio_EH1_OneDay_sidereal.pdf","ThreeSites/Ratio_EH2_OneDay_sidereal.pdf","ThreeSites/Ratio_EH3_OneDay_sidereal.pdf"};

	Double_t ParResult_single[3][7],ParErrResult_single[3][7];
	for(int i=0;i<7;i++)
	{
		ParResult_single[0][i]=ParResult_EH1[i];
		ParResult_single[1][i]=ParResult_EH2[i];
		ParResult_single[2][i]=ParResult_EH3[i];
		ParErrResult_single[0][i]=ParErrResult_EH1[i];
		ParErrResult_single[1][i]=ParErrResult_EH2[i];
		ParErrResult_single[2][i]=ParErrResult_EH3[i];
	}

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		Float_t x[n],y[n],ex[n],ey[n];
		myC[Hidx] = new TCanvas(c_Name[Hidx],c_Name[Hidx],200,10,800,600);
		gStyle->SetOptFit(1);
		//myC[Hidx]->SetGrid();
		myC[Hidx]->GetFrame()->SetFillColor(21);
		myC[Hidx]->GetFrame()->SetBorderSize(12);
		for(int i=0;i<n;i++)
		{
		x[i]=i*WidthOfBin;
		y[i]=R[Hidx][i];
		ex[i]=0;
		ey[i]=R[Hidx][i]*RD_R[Hidx][i];
		//cout<<y[i]<<"   "<<ey[i]<<endl;
		}
		gr[Hidx] = new TGraphErrors(n,x,y,ex,ey);

		gr[Hidx]->SetMarkerColor(1);
		gr[Hidx]->SetMarkerStyle(21);
		gr[Hidx]->GetXaxis()->SetTitle("sidereal time(seconds)");
		gr[Hidx]->GetYaxis()->SetTitle("Data/Expectation");
		gr[Hidx]->GetYaxis()->SetRangeUser(0.94,1.1);

		gr[Hidx]->SetTitle("");

		gr[Hidx]->GetYaxis()->SetTitleOffset(0.98);
		gr[Hidx]->GetYaxis()->SetTitleSize(0.05);
		gr[Hidx]->GetYaxis()->SetLabelSize(0.042);
		gr[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
		gr[Hidx]->GetXaxis()->SetTitleOffset(0.8);
		gr[Hidx]->GetXaxis()->SetTitleSize(0.06);
		//gr[Hidx]->GetXaxis()->SetLabelSize(0.045);
		gr[Hidx]->GetXaxis()->SetLabelOffset(0.0);

		//gr[Hidx]->SetMarkerStyle(21);
		gr[Hidx]->Draw("AP");
		/////////////////plot the fit result:three sites////////////////////////
		f_Plot[Hidx] = new TF1(c_Name[Hidx],PlotFunc,0,86165.0,8);

			f_Plot[Hidx]->SetParameter(0,1.0);

		for(int i=1;i<7;i++)
		{
			f_Plot[Hidx]->SetParameter(i,ParResult[i]);
		}
		f_Plot[Hidx]->SetParameter(7,Hidx);
		f_Plot[Hidx]->SetLineColor(kRed);
		f_Plot[Hidx]->Draw("same");

		/////////////////plot the fit result:site by site////////////////////////
		f_Plot_single[Hidx] = new TF1(c_Name_single[Hidx],PlotFunc,0,86165.0,8);
		
			f_Plot_single[Hidx]->SetParameter(0,1.0);
		
		for(int i=1;i<7;i++)
		{
			f_Plot_single[Hidx]->SetParameter(i,ParResult_single[Hidx][i]);
		}
		f_Plot_single[Hidx]->SetParameter(7,Hidx);
		f_Plot_single[Hidx]->SetLineColor(kBlue);
		//f_Plot_single[Hidx]->SetLineStyle(2);
		f_Plot_single[Hidx]->Draw("same");

		////////////////////////////////////////////////////////Draw the error band///////////////////////////////////////////
		
		Double_t xb[100]={0},yb[100]={0},exb[100]={0},eyb[100]={0};
		Int_t nb=100;
		for(int i=0;i<100;i++)
		{
			xb[i]=861.650*i;
			//yb[i]=1.08;
		}
		//evaluate PlotFunc
		Double_t x_Time=0.0, par_band[8],par_band2[8];
		TRandom *Ran_par = new TRandom();
		Double_t xy_band[100][1000];
		Double_t y_Center[100];
		Double_t sigma_y_band[100];
		Double_t mean_y_band[100];

		par_band[7]=Hidx;
		par_band2[7]=Hidx;
		par_band[0]=1.0;
		par_band2[0]=1.0;

		Double_t sigma_y = 0.0;
		//3 sites
		for(int xN=0;xN<100;xN++)
		{
			TH1F *y_TH1F_band = new TH1F();
			x_Time = 861.650*xN;
			for(int yN=0;yN<1000;yN++)
			{
				
				for(int pN=1;pN<7;pN++)
				{
					Double_t r01 = Ran_par->Gaus(0.0,1.0);
					par_band[pN] = ParResult[pN]+ 1.0*r01*ParErrResult[pN];
				}
				xy_band[xN][yN] = PlotFunc(&x_Time,par_band);
				y_TH1F_band->Fill(xy_band[xN][yN]);
			}
			for(int pN=1;pN<7;pN++)
			{
				par_band2[pN] = ParResult[pN];
			}
			y_Center[xN] = PlotFunc(&x_Time,par_band2);
			mean_y_band[xN] = y_TH1F_band->GetMean();
			sigma_y_band[xN] = y_TH1F_band->GetStdDev();
			sigma_y += 0.01*sigma_y_band[xN];
			cout<<xN<<"   "<<mean_y_band[xN]<<"   "<<sigma_y_band[xN]<<endl;
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
		cout<<sigma_y<<endl;
		sigma_y=0.0;
		

		//site by site
		for(int xN=0;xN<100;xN++)
		{
			TH1F *y_TH1F_band = new TH1F();
			x_Time = 861.650*xN;
			for(int yN=0;yN<1000;yN++)
			{
				
				for(int pN=1;pN<7;pN++)
				{
					Double_t r01 = Ran_par->Gaus(0.0,1.0);
					par_band[pN] = ParResult_single[Hidx][pN]+ 1.0*r01*ParErrResult_single[Hidx][pN];
				}
				xy_band[xN][yN] = PlotFunc(&x_Time,par_band);
				y_TH1F_band->Fill(xy_band[xN][yN]);
			}
			for(int pN=1;pN<7;pN++)
			{
				par_band2[pN] = ParResult_single[Hidx][pN];
			}
			y_Center[xN] = PlotFunc(&x_Time,par_band2);
			mean_y_band[xN] = y_TH1F_band->GetMean();
			sigma_y_band[xN] = y_TH1F_band->GetStdDev();
			sigma_y += 0.01*sigma_y_band[xN];
			cout<<xN<<"   "<<mean_y_band[xN]<<"   "<<sigma_y_band[xN]<<endl;
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
			grb->SetMarkerColor(kBlue);
			grb->SetLineColor(kBlue);
			grb->Draw("CSAME");
		}
		cout<<sigma_y<<endl;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////
		leg[Hidx] = new TLegend(0, 0.75, 0.55, 0.9);
		leg[Hidx]->AddEntry(gr[Hidx],c_Name[Hidx],"");
		leg[Hidx]->SetFillStyle(0);
		leg[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
		leg[Hidx]->Draw();
		////////////
		leg2[Hidx] = new TLegend(0.6, 0.75, 0.9, 0.9);
		leg2[Hidx]->AddEntry(f_Plot[Hidx],"3 sites","l");
		leg2[Hidx]->AddEntry(f_Plot_single[Hidx],c_Name_single[Hidx],"l");
		leg2[Hidx]->SetFillStyle(0);
		leg2[Hidx]->SetBorderSize(0);
		//leg2[Hidx]->SetTextColor(kRed);
		leg2[Hidx]->Draw();

		myC[Hidx]->Update();
		myC[Hidx]->SaveAs(file_Name[Hidx]);
	}
	
	//////////////////////////////////////////////////////all flavor component//////////////////////////////////////////////////////////////////////////////////////////////
	Int_t Table_Index[6][2]={{0,0},{1,1},{2,2},{0,1},{0,2},{1,2}};
	const char *cdIdx_Name[6]={"ee","uu","tt","eu","et","ut"};
	FILE* m_outfile = fopen("FitResult_all.txt", "a");

	for(int cdIdx=0;cdIdx<6;cdIdx++)
	{
		cout<<cdIdx_Name[cdIdx]<<endl;
	IndexCD[0] = Table_Index[cdIdx][0];
	IndexCD[1] = Table_Index[cdIdx][1];
	////////////////////////////////////////////////////Fit
   TMinuit *gMinuit = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
   gMinuit->SetFCN(ChiSquare);

   Double_t arglist[10];
   Int_t ierflg = 0;

   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   Double_t vstart[7] = {0.9,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0};
   Double_t step[7] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01};
   gMinuit->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg);
   gMinuit->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg);
   gMinuit->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg);
   gMinuit->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 2000;
   arglist[1] = 40000.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   Table_Chi2_3Site_1Bin[cdIdx] = amin;
   //gMinuit->mnprin(3,amin);

   //0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
   //Double_t ParResult[7],ParErrResult[7];
   for(int i=0;i<7;i++)
   {
	   Double_t v,ev;
	   gMinuit->GetParameter(i,v,ev);
	   ParResult[i]=v;
	   ParErrResult[i]=ev;
   }


   ////////////////////////////////////////////////////Fit site by site (EH1 only)
   TMinuit *gMinuit_EH1 = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
   gMinuit_EH1->SetFCN(ChiSquare_EH1);

   Double_t arglist_EH1[10];
   Int_t ierflg_EH1 = 0;

   arglist_EH1[0] = 1;
   gMinuit_EH1->mnexcm("SET ERR", arglist_EH1 ,1,ierflg_EH1);

// Set starting values and step_EH1 sizes for parameters
   Double_t vstart_EH1[7] = {1.0,0,0,0,0,0,0};
   Double_t step_EH1[7] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01};
   gMinuit_EH1->mnparm(0, "C", vstart_EH1[0], step_EH1[0], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(1, "A1", vstart_EH1[1], step_EH1[1], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(2, "A2", vstart_EH1[2], step_EH1[2], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(3, "A3", vstart_EH1[3], step_EH1[3], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(4, "A4", vstart_EH1[4], step_EH1[4], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(5, "B1", vstart_EH1[5], step_EH1[5], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(6, "B2", vstart_EH1[6], step_EH1[6], 0,0,ierflg_EH1);

// Now ready for minimization step_EH1
   arglist_EH1[0] = 2000;
   arglist_EH1[1] = 5000.;
   gMinuit_EH1->mnexcm("MIGRAD", arglist_EH1 ,2,ierflg_EH1);

// Print results
   Double_t amin_EH1,edm_EH1,errdef_EH1;
   Int_t nvpar_EH1,nparx_EH1,icstat_EH1;
   gMinuit_EH1->mnstat(amin_EH1,edm_EH1,errdef_EH1,nvpar_EH1,nparx_EH1,icstat_EH1);
   Table_Chi2_SiteBySite_1Bin[0][cdIdx]=amin_EH1;
   //gMinuit_EH1->mnprin(3,amin_EH1);

   //0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
   //Double_t ParResult_EH1[7],ParErrResult_EH1[7];
   for(int i=0;i<7;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH1->GetParameter(i,v,ev);
	   ParResult_EH1[i]=v;
	   ParErrResult_EH1[i]=ev;
   }



   ////////////////////////////////////////////////////Fit site by site (EH2 only)
   TMinuit *gMinuit_EH2 = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
   gMinuit_EH2->SetFCN(ChiSquare_EH2);

   Double_t arglist_EH2[10];
   Int_t ierflg_EH2 = 0;

   arglist_EH2[0] = 1;
   gMinuit_EH2->mnexcm("SET ERR", arglist_EH2 ,1,ierflg_EH2);

// Set starting values and step_EH2 sizes for parameters
   Double_t vstart_EH2[7] = {1.0,0,0,0,0,0,0};
   Double_t step_EH2[7] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01,0.01};
   gMinuit_EH2->mnparm(0, "C", vstart_EH2[0], step_EH2[0], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(1, "A1", vstart_EH2[1], step_EH2[1], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(2, "A2", vstart_EH2[2], step_EH2[2], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(3, "A3", vstart_EH2[3], step_EH2[3], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(4, "A4", vstart_EH2[4], step_EH2[4], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(5, "B1", vstart_EH2[5], step_EH2[5], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(6, "B2", vstart_EH2[6], step_EH2[6], 0,0,ierflg_EH2);

// Now ready for minimization step_EH2
   arglist_EH2[0] = 2000;
   arglist_EH2[1] = 5000.;
   gMinuit_EH2->mnexcm("MIGRAD", arglist_EH2 ,2,ierflg_EH2);

// Print results
   Double_t amin_EH2,edm_EH2,errdef_EH2;
   Int_t nvpar_EH2,nparx_EH2,icstat_EH2;
   gMinuit_EH2->mnstat(amin_EH2,edm_EH2,errdef_EH2,nvpar_EH2,nparx_EH2,icstat_EH2);
   Table_Chi2_SiteBySite_1Bin[1][cdIdx]=amin_EH2;
  // gMinuit_EH2->mnprin(3,amin_EH2);

   //0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
   //Double_t ParResult_EH2[7],ParErrResult_EH2[7];
   for(int i=0;i<7;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH2->GetParameter(i,v,ev);
	   ParResult_EH2[i]=v;
	   ParErrResult_EH2[i]=ev;
   }
   



   ////////////////////////////////////////////////////Fit site by site (EH3 only)
   TMinuit *gMinuit_EH3 = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
   gMinuit_EH3->SetFCN(ChiSquare_EH3);

   Double_t arglist_EH3[10];
   Int_t ierflg_EH3 = 0;

   arglist_EH3[0] = 1;
   gMinuit_EH3->mnexcm("SET ERR", arglist_EH3 ,1,ierflg_EH3);

// Set starting values and step_EH3 sizes for parameters
   Double_t vstart_EH3[7] = {1.0,0,0,0,0,0,0};
   Double_t step_EH3[7] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01};
   gMinuit_EH3->mnparm(0, "C", vstart_EH3[0], step_EH3[0], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(1, "A1", vstart_EH3[1], step_EH3[1], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(2, "A2", vstart_EH3[2], step_EH3[2], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(3, "A3", vstart_EH3[3], step_EH3[3], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(4, "A4", vstart_EH3[4], step_EH3[4], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(5, "B1", vstart_EH3[5], step_EH3[5], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(6, "B2", vstart_EH3[6], step_EH3[6], 0,0,ierflg_EH3);

// Now ready for minimization step_EH3
   arglist_EH3[0] = 2000;
   arglist_EH3[1] = 5000.;
   gMinuit_EH3->mnexcm("MIGRAD", arglist_EH3 ,2,ierflg_EH3);

// Print results
   Double_t amin_EH3,edm_EH3,errdef_EH3;
   Int_t nvpar_EH3,nparx_EH3,icstat_EH3;
   gMinuit_EH3->mnstat(amin_EH3,edm_EH3,errdef_EH3,nvpar_EH3,nparx_EH3,icstat_EH3);
   Table_Chi2_SiteBySite_1Bin[2][cdIdx]=amin_EH3;
   //gMinuit_EH3->mnprin(3,amin_EH3);

   //0   1   2   3   4   5   6
	//C   A1  A2  A3  A4  B1  B2
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
   //Double_t ParResult_EH3[7],ParErrResult_EH3[7];
   for(int i=0;i<7;i++)
   {
	   Double_t v,ev;
	   gMinuit_EH3->GetParameter(i,v,ev);
	   ParResult_EH3[i]=v;
	   ParErrResult_EH3[i]=ev;
   }
   ///////////print
   fprintf(m_outfile,"fit result(three sites) %2s:\n",cdIdx_Name[cdIdx]);
   fprintf(m_outfile,"$a^{X}_R-0.0084c^{TX}_R$/$10^{-21}$GeV          &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[1],ParErrResult[1],ParResult_EH1[1],ParErrResult_EH1[1],ParResult_EH2[1],ParErrResult_EH2[1],ParResult_EH3[1],ParErrResult_EH3[1]);
   fprintf(m_outfile,"$c^{XZ}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[2],ParErrResult[2],ParResult_EH1[2],ParErrResult_EH1[2],ParResult_EH2[2],ParErrResult_EH2[2],ParResult_EH3[2],ParErrResult_EH3[2]);
   fprintf(m_outfile,"$-a^{Y}_R+0.0084c^{TY}_R$/$10^{-21}$GeV           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[3],ParErrResult[3],ParResult_EH1[3],ParErrResult_EH1[3],ParResult_EH2[3],ParErrResult_EH2[3],ParResult_EH3[3],ParErrResult_EH3[3]);
   fprintf(m_outfile,"$c^{YZ}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[4],ParErrResult[4],ParResult_EH1[4],ParErrResult_EH1[4],ParResult_EH2[4],ParErrResult_EH2[4],ParResult_EH3[4],ParErrResult_EH3[4]);
   fprintf(m_outfile,"$c^{XX}_R-c^{YY}_R$/$10^{-18}$           &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[5],ParErrResult[5],ParResult_EH1[5],ParErrResult_EH1[5],ParResult_EH2[5],ParErrResult_EH2[5],ParResult_EH3[5],ParErrResult_EH3[5]);
   fprintf(m_outfile,"$c^{XY}_R$/$10^{-18}$  &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$ &$%3.1f \\pm %3.1f$    \\\\ \n",ParResult[6],ParErrResult[6],ParResult_EH1[6],ParErrResult_EH1[6],ParResult_EH2[6],ParErrResult_EH2[6],ParResult_EH3[6],ParErrResult_EH3[6]);
   fprintf(m_outfile,"$\\chi^2/NDF$  & $%4.1f/%3d$ & $%4.1f/%3d$& $%4.1f/%3d$ & $%4.1f/%3d$      \\\\ \n",
	   Table_Chi2_3Site_1Bin[cdIdx],NOF_3Site_1Bin,
	   Table_Chi2_SiteBySite_1Bin[0][cdIdx],NOF_SiteBySite_1Bin,
	   Table_Chi2_SiteBySite_1Bin[1][cdIdx],NOF_SiteBySite_1Bin,
	   Table_Chi2_SiteBySite_1Bin[2][cdIdx],NOF_SiteBySite_1Bin,);   
}
  
	*/
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