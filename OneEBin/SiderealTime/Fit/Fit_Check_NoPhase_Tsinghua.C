

#include <math.h>
#include "TMinuit.h"


double AVEP[3] = {0.985,0.983,0.951455};

void ChiSquare(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void ChiSquare_EH1(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void ChiSquare_EH2(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void ChiSquare_EH3(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);

Double_t PlotFunc(Double_t *x, Double_t *par);
Double_t PlotFunc1(Double_t *x, Double_t *par);
Double_t PlotFunc2(Double_t *x, Double_t *par);
Double_t PlotFunc3(Double_t *x, Double_t *par);

double R[3][24]={0.0};
double R_noI[3][24]={0.0};
double RD_R[3][24]={0.0};
double RD_R_noI[3][24]={0.0};
double R_Det[8][24]={{0.0}};
double RD_R_Det[8][24]={{0.0}};
double R_Bin[8][24]={{0.0}};
double RD_R_Bin[8][24]={{0.0}};

double R_simu[8][24]={{0.0}};
double RD_R_simu[8][24]={{0.0}};


Double_t ParResult[8],ParErrResult[8];
Double_t ParResult_EH1[8],ParErrResult_EH1[8];
Double_t ParResult_EH2[8],ParErrResult_EH2[8];
Double_t ParResult_EH3[8],ParErrResult_EH3[8];

const double pi = 3.141592653;

int  IndexCD[2] = {0,0};

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

	int NOF_3Site_5Bin = 352; //3*5*24-9
	int NOF_SiteBySite_5Bin = 112; //5*24-9
	int NOF_3Site_1Bin = 66; // 3*24-7
	int NOF_SiteBySite_1Bin = 18; //24-7


   Double_t vstart[8] = {1.0,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,0};
   Double_t step[8] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1,0.1,0.1};
   

void Fit_Check_NoPhase_Tsinghua()
{
	
cout<<"start..."<<endl;
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
		//////cout<<PositionADn[ADidx][0]<<"      "<<PositionADn[ADidx][1]<<"      "<<PositionADn[ADidx][2]<<endl;
	}

	for(int Rctidx = 0;Rctidx<6;Rctidx++)
	{
		PositionRctn[Rctidx][0] = PositionRct[Rctidx][0]*cos(RotAngl)+PositionRct[Rctidx][1]*sin(RotAngl);//x'=xcos + ysin
		PositionRctn[Rctidx][1] = -1*PositionRct[Rctidx][0]*sin(RotAngl)+PositionRct[Rctidx][1]*cos(RotAngl);//y'=-xsin + ycos
		PositionRctn[Rctidx][2] = PositionRct[Rctidx][2];
		//////cout<<PositionRctn[Rctidx][0]<<"      "<<PositionRctn[Rctidx][1]<<"      "<<PositionRctn[Rctidx][2]<<endl;
	}

	for(int i=0;i<3;i++)
	{
		PositionHalln[0][i] = 0.5*(PositionADn[0][i]+PositionADn[1][i]);
		PositionHalln[1][i] = 0.5*(PositionADn[2][i]+PositionADn[7][i]);
		PositionHalln[2][i] = 0.25*(PositionADn[3][i]+PositionADn[4][i]+PositionADn[5][i]+PositionADn[6][i]);
	}

	////////cout<<acos(-0.5)<<"   "<<120.0*pi/180.0<<endl;
	
	////////cout<<"Hall			Rct			theta			phi			chi			Nx			Ny			Nz"<<endl;			
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

	cout<<"Im SeeMee used in the fit..........................."<<endl;
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
			fprintf(stderr,"&  %7.4f & %7.4f & %7.4f  & %7.4f & %7.4f &  %7.4f  \\\\ \\hline \n",
				Table_ImSeeMee[Hidx][Rct][0][0],Table_ImSeeMee[Hidx][Rct][1][1],Table_ImSeeMee[Hidx][Rct][2][2],
				Table_ImSeeMee[Hidx][Rct][0][1],Table_ImSeeMee[Hidx][Rct][0][2],Table_ImSeeMee[Hidx][Rct][1][2]);
		}
	}


///in each bin//////////////////////////////////////////////////////////////////////////////////////////////////
//cout<<"line 244..."<<endl;
	//IBD candidate
	Double_t IBDInEachBin[8][NumOfBin];
	Int_t IBD_t_Bin[8];
	memset(IBDInEachBin,0.0,sizeof(IBDInEachBin));
	TFile *F_Bin_IBD = new TFile("../IBD.root");
	TTree *Tree_Bin_IBD = (TTree*)F_Bin_IBD->Get("IBD");
	Tree_Bin_IBD->SetBranchAddress("IBD",IBD_t_Bin);

	Double_t FullTimeInEachBin[8][NumOfBin];
	Double_t FullTime_t_Bin[8];
	memset(FullTimeInEachBin,0.0,sizeof(FullTimeInEachBin));
	TFile *F_Bin_FullTime = new TFile("../FullTime.root");
	TTree *Tree_Bin_FullTime = (TTree*)F_Bin_FullTime->Get("FullTime");
	Tree_Bin_FullTime->SetBranchAddress("FullTime",FullTime_t_Bin);

	Double_t LiveTimeInEachBin[8][NumOfBin];
	Double_t LiveTime_t_Bin[8];
	memset(LiveTimeInEachBin,0.0,sizeof(LiveTimeInEachBin));
	TFile *F_Bin_LiveTime = new TFile("../LiveTime.root");
	TTree *Tree_Bin_LiveTime = (TTree*)F_Bin_LiveTime->Get("LiveTime");
	Tree_Bin_LiveTime->SetBranchAddress("LiveTime",LiveTime_t_Bin);

	//AmC
        Double_t AmCInEachBin[8][NumOfBin];
	Double_t AmC_t_Bin[8];
	memset(AmCInEachBin,0.0,sizeof(AmCInEachBin));
	TFile *F_Bin_AmC = new TFile("../AmC/AmCInEachBin.root");
	TTree *Tree_Bin_AmC = (TTree*)F_Bin_AmC->Get("AmCInEachBin");
	Tree_Bin_AmC->SetBranchAddress("AmCInEachBin",AmC_t_Bin);
	
	//RD_AmC
	Double_t RD_AmCInEachBin[8][NumOfBin];
	Double_t RD_AmC_t_Bin[8];
	memset(RD_AmCInEachBin,0.0,sizeof(RD_AmCInEachBin));
	TFile *F_Bin_RD_AmC = new TFile("../AmC/RD_AmCInEachBin.root");
	TTree *Tree_Bin_RD_AmC = (TTree*)F_Bin_RD_AmC->Get("RD_AmCInEachBin");
	Tree_Bin_RD_AmC->SetBranchAddress("RD_AmCInEachBin",RD_AmC_t_Bin);

	//Acc
	Double_t AccInEachBin[8][NumOfBin];
	Double_t Acc_t_Bin[8];
	memset(AccInEachBin,0.0,sizeof(AccInEachBin));
	TFile *F_Bin_Acc = new TFile("../AccBkg/AccInEachBin.root");
	TTree *Tree_Bin_Acc = (TTree*)F_Bin_Acc->Get("AccInEachBin");
	Tree_Bin_Acc->SetBranchAddress("AccInEachBin",Acc_t_Bin);

	//RD_Acc
	Double_t RD_AccInEachBin[8][NumOfBin];
	Double_t RD_Acc_t_Bin[8];
	memset(RD_AccInEachBin,0.0,sizeof(RD_AccInEachBin));
	TFile *F_Bin_RD_Acc = new TFile("../AccBkg/RD_AccInEachBin.root");
	TTree *Tree_Bin_RD_Acc = (TTree*)F_Bin_RD_Acc->Get("RD_AccInEachBin");
	Tree_Bin_RD_Acc->SetBranchAddress("RD_AccInEachBin",RD_Acc_t_Bin);

	//Li9
	Double_t Li9InEachBin[8][NumOfBin];
	Double_t Li9_t_Bin[8];
	memset(Li9InEachBin,0.0,sizeof(Li9InEachBin));
	TFile *F_Bin_Li9 = new TFile("../Li9/Li9InEachBin.root");
	TTree *Tree_Bin_Li9 = (TTree*)F_Bin_Li9->Get("Li9InEachBin");
	Tree_Bin_Li9->SetBranchAddress("Li9InEachBin",Li9_t_Bin);

	//RD_Li9
	Double_t RD_Li9InEachBin[8][NumOfBin];
	Double_t RD_Li9_t_Bin[8];
	memset(RD_Li9InEachBin,0.0,sizeof(RD_Li9InEachBin));
	TFile *F_Bin_RD_Li9 = new TFile("../Li9/RD_Li9InEachBin.root");
	TTree *Tree_Bin_RD_Li9 = (TTree*)F_Bin_RD_Li9->Get("RD_Li9InEachBin");
	Tree_Bin_RD_Li9->SetBranchAddress("RD_Li9InEachBin",RD_Li9_t_Bin);

	//FastN
	Double_t FastNInEachBin[8][NumOfBin];
	Double_t FastN_t_Bin[8];
	memset(FastNInEachBin,0.0,sizeof(FastNInEachBin));
	TFile *F_Bin_FastN = new TFile("../FastN/FastNInEachBin.root");
	TTree *Tree_Bin_FastN = (TTree*)F_Bin_FastN->Get("FastNInEachBin");
	Tree_Bin_FastN->SetBranchAddress("FastNInEachBin",FastN_t_Bin);

	//RD_FastN
	Double_t RD_FastNInEachBin[8][NumOfBin];
	Double_t RD_FastN_t_Bin[8];
	memset(RD_FastNInEachBin,0.0,sizeof(RD_FastNInEachBin));
	TFile *F_Bin_RD_FastN = new TFile("../FastN/RD_FastNInEachBin.root");
	TTree *Tree_Bin_RD_FastN = (TTree*)F_Bin_RD_FastN->Get("RD_FastNInEachBin");
	Tree_Bin_RD_FastN->SetBranchAddress("RD_FastNInEachBin",RD_FastN_t_Bin);

	//MultiEff
	Double_t MultiEffInEachBin[8][NumOfBin];
	Double_t MultiEff_t_Bin[8];
	memset(MultiEffInEachBin,0.0,sizeof(MultiEffInEachBin));
	TFile *F_Bin_MultiEff = new TFile("../MultiEff/MultiEffInEachBin.root");
	TTree *Tree_Bin_MultiEff = (TTree*)F_Bin_MultiEff->Get("MultiEffInEachBin");
	Tree_Bin_MultiEff->SetBranchAddress("MultiEffInEachBin",MultiEff_t_Bin);

	//MuEff
	Double_t MuEffInEachBin[8][NumOfBin];
	Double_t MuEff_t_Bin[8];
	memset(MuEffInEachBin,0.0,sizeof(MuEffInEachBin));
	TFile *F_Bin_MuEff = new TFile("../MuEff/MuEffInEachBin.root");
	TTree *Tree_Bin_MuEff = (TTree*)F_Bin_MuEff->Get("MuEffInEachBin");
	Tree_Bin_MuEff->SetBranchAddress("MuEffInEachBin",MuEff_t_Bin);



	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		Tree_Bin_IBD->GetEntry(Bin);
		Tree_Bin_FullTime->GetEntry(Bin);
		Tree_Bin_LiveTime->GetEntry(Bin);
		Tree_Bin_AmC->GetEntry(Bin);
		Tree_Bin_RD_AmC->GetEntry(Bin);
		Tree_Bin_Acc->GetEntry(Bin);
		Tree_Bin_RD_Acc->GetEntry(Bin);
		Tree_Bin_Li9->GetEntry(Bin);
		Tree_Bin_RD_Li9->GetEntry(Bin);
		Tree_Bin_FastN->GetEntry(Bin);
		Tree_Bin_RD_FastN->GetEntry(Bin);
		Tree_Bin_MultiEff->GetEntry(Bin);
		Tree_Bin_MuEff->GetEntry(Bin);
	//	Tree_Bin_Fraction->GetEntry(Bin);
	//	Tree_Bin_FractionAD->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			IBDInEachBin[Det][Bin] = 1.0*IBD_t_Bin[Det];
			FullTimeInEachBin[Det][Bin] = FullTime_t_Bin[Det];
			LiveTimeInEachBin[Det][Bin] = LiveTime_t_Bin[Det];
			AmCInEachBin[Det][Bin] = AmC_t_Bin[Det];
			RD_AmCInEachBin[Det][Bin] = RD_AmC_t_Bin[Det];
			AccInEachBin[Det][Bin] = Acc_t_Bin[Det];
			RD_AccInEachBin[Det][Bin] = RD_Acc_t_Bin[Det];
			Li9InEachBin[Det][Bin] = Li9_t_Bin[Det];
			RD_Li9InEachBin[Det][Bin] = RD_Li9_t_Bin[Det];
			FastNInEachBin[Det][Bin] = FastN_t_Bin[Det];
			RD_FastNInEachBin[Det][Bin] = RD_FastN_t_Bin[Det];
			MultiEffInEachBin[Det][Bin] = MultiEff_t_Bin[Det];
			MuEffInEachBin[Det][Bin] = MuEff_t_Bin[Det];
			
		}
	}

//cout<<"line 378...."<<endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	Double_t CrossSection = 0.94;//Averaged cross-section, in unit of 1e-43 cm^2;

	Double_t Np = 1.43;//Total number of target protons in AD1,AD2, in unit of 1e30

	//IBD candidate
	Double_t IBDInOneDay[8][24];
	Double_t IBD_t[8];
	memset(IBDInOneDay,0.0,sizeof(IBDInOneDay));
	TFile *F_IBD = new TFile("../IBD/IBDInOneDay.root");
	TTree *Tree_IBD = (TTree*)F_IBD->Get("IBDInOneDay");
	Tree_IBD->SetBranchAddress("IBDInOneDay",IBD_t);

	Double_t FullTimeInOneDay[8][24];
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
	Double_t FractionInOneDay[3][24];
	Double_t Fraction_t[3];
	memset(FractionInOneDay,0.0,sizeof(FractionInOneDay));
	TFile *F_Fraction = new TFile("../daily_data/Fraction_Hall_Day.root");
	TTree *Tree_Fraction = (TTree*)F_Fraction->Get("Fraction");
	Tree_Fraction->SetBranchAddress("Fraction",Fraction_t);

	Double_t FractionInOneDayAD[8][24];
	Double_t Fraction_tAD[8];
	memset(FractionInOneDayAD,0.0,sizeof(FractionInOneDayAD));
	TFile *F_FractionAD = new TFile("../daily_data/Fraction_AD_Day.root");
	TTree *Tree_FractionAD = (TTree*)F_FractionAD->Get("Fraction");
	Tree_FractionAD->SetBranchAddress("Fraction",Fraction_tAD);


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
		Tree_FractionAD->GetEntry(N24);

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
			FractionInOneDayAD[Det][N24] = Fraction_tAD[Det];
			
		}
		for(int Hall=0;Hall<3;Hall++)
		{
				FractionInOneDay[Hall][N24] = Fraction_t[Hall];
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

	//
	double RD_Power = 0.00022;
	double RD_Eff = 0.00088;

	////////////////////////////ratio per AD //////////////////////////////////////////////
	Double_t M[24];//={0.0};
	memset(M,0.0,sizeof(M));
	Double_t RD_M[24];//={0.0};
	memset(RD_M,0.0,sizeof(RD_M));
	Double_t NBar[24];//
	double NBar_noI[24]={0.0};
	memset(NBar,0.0,sizeof(NBar));
	Double_t RD_NBar[24];//
	memset(RD_NBar,0.0,sizeof(RD_NBar));

	for(int Det=0;Det<8;Det++)
	{
		int HallID;
		for(int i=0;i<24;i++)
		{
		M[i]=0.0;
		RD_M[i]=0.0;
		NBar[i]=0.0;
		RD_NBar[i]=0.0;
		}
		for(int N24=0;N24<24;N24++)
		{
			M[N24] += IBDInOneDay[Det][N24]/(MuEffInOneDay[Det][N24]*MultiEffInOneDay[Det][N24])-
				(AmCInOneDay[Det][N24]+AccInOneDay[Det][N24]+Li9InOneDay[Det][N24]+FastNInOneDay[Det][N24])/MultiEffInOneDay[Det][N24];
			RD_M[N24] += (IBDInOneDay[Det][N24]/pow(MuEffInOneDay[Det][N24],2.0)+
					pow(RD_AmCInOneDay[Det][N24]*AmCInOneDay[Det][N24],2.0)+
					pow(RD_AccInOneDay[Det][N24]*AccInOneDay[Det][N24],2.0)+
					pow(RD_Li9InOneDay[Det][N24]*Li9InOneDay[Det][N24],2.0)+
					pow(RD_FastNInOneDay[Det][N24]*FastNInOneDay[Det][N24],2.0)
					)/pow(MultiEffInOneDay[Det][N24],2.0);


		RD_M[N24] += pow(M[N24]*RD_Eff,2.0);

		RD_M[N24] = sqrt(RD_M[N24])/M[N24];
		Double_t temp=0.0,temp_noI=0.0,temp2=0.0;
		temp = FractionInOneDayAD[Det][N24];
		
		double tempFrac = 0.0;
		if(Det<2)
		{
			HallID=0;
			tempFrac = FullTimeInOneDay[Det][N24]/(FullTimeInOneDay[0][N24]+FullTimeInOneDay[1][N24]);
		}
		else if(Det<4)
		{
			HallID=1;
			tempFrac = FullTimeInOneDay[Det][N24]/(FullTimeInOneDay[2][N24]+FullTimeInOneDay[3][N24]);
		}
		else
		{
			HallID=2;
			tempFrac = FullTimeInOneDay[Det][N24]/(FullTimeInOneDay[4][N24]+FullTimeInOneDay[5][N24]+FullTimeInOneDay[6][N24]+FullTimeInOneDay[7][N24]);
		}

		for(int Rct=0;Rct<6;Rct++)
		{
		temp2 += pow(EveFrac_Hall[HallID][Rct][N24]*tempFrac,2.0);
		}
		
		NBar[N24] = 1.0e-17*Np*CrossSection*temp/(4.0*pi);
		R_Det[Det][N24] = M[N24]/NBar[N24];
		RD_R_Det[Det][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
		}
	}



	//////////////////////////////////////////////////////////////////////////////////////

	//////////////EH1////////////////////////////////////////////////
	int HallID = 0;
	for(int i=0;i<24;i++)
	{
		M[i]=0.0;
		RD_M[i]=0.0;
		NBar[i]=0.0;
		RD_NBar[i]=0.0;
	}

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
		Double_t temp=0.0,temp_noI=0.0,temp2=0.0;
		temp = FractionInOneDay[HallID][N24];
		for(int Rct=0;Rct<6;Rct++)
		{
			temp_noI += EveFrac_Hall[HallID][Rct][N24];

		temp2 += pow(EveFrac_Hall[HallID][Rct][N24],2.0);
		}
		NBar[N24] = 1.0e-17*Np*CrossSection*temp/(4.0*pi);
		NBar_noI[N24] = 1.0e-17*Np*CrossSection*temp_noI/(4.0*pi);
		//RD_NBar[N24] = RD_Power;

		R[0][N24] = M[N24]/NBar[N24];
		R_noI[0][N24] = M[N24]/NBar_noI[N24];
		RD_R[0][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
		RD_R_noI[0][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp_noI,2.0));
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
		Double_t temp=0.0,temp_noI=0.0,temp2=0.0;
			temp = FractionInOneDay[HallID][N24];
			for(int Rct=0;Rct<6;Rct++)
		{
			temp_noI += EveFrac_Hall[HallID][Rct][N24];
		temp2 += pow(EveFrac_Hall[HallID][Rct][N24],2.0);
		}
		//	temp2 = pow(FractionInOneDay[HallID][N24],2.0);

		NBar[N24] = 1.0e-17*Np*CrossSection*temp/(4.0*pi);
		//RD_NBar[N24] = RD_Power;

		 NBar_noI[N24] = 1.0e-17*Np*CrossSection*temp_noI/(4.0*pi);

		R[1][N24] = M[N24]/NBar[N24];
		R_noI[1][N24] = M[N24]/NBar_noI[N24];
		RD_R[1][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
		RD_R_noI[1][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp_noI,2.0));
		////cout<<N24<<"   "<<R[N24]<<"   "<<RD_R[N24]<<"   "<<RD_M[N24]<<"   "<<endl;
	}

	/////////////////////////////////EH3////////////////////////////////////////////
	HallID = 2;
	Double_t Mf[24]={0.0};//={0.0};
	Double_t RD_Mf[24]={0.0};//={0.0};
	
	Double_t Ma[24]={0.0};//={0.0};
	Double_t RD_Ma[24]={0.0};//={0.0};
	
	Double_t Mb[24]={0.0};//={0.0};
	Double_t RD_Mb[24]={0.0};//={0.0};

	Double_t NBarF[24]={0.0};//={0.0};
	Double_t RD_NBarF[24]={0.0};//={0.0};

	Double_t Mf_Bin[24] = {0.0};
	Double_t RD_Mf_Bin[24] = {0.0};

	Double_t Ma_simu[24] = {0.0};
	Double_t Mb_simu[24] = {0.0};
	Double_t Mf_simu[24] = {0.0};

	Double_t RD_Ma_simu[24] = {0.0};
	Double_t RD_Mb_simu[24] = {0.0};
	Double_t RD_Mf_simu[24] = {0.0};

	double TotalIBD_Before[8] = {0.0};
	double TotalIBD_After[8] ={0.0};


	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		float a=0.0,b=0.0,rd_a=0.0,rd_b=0.0;
		int N24 = Bin%24;
		float ff=0.0,rd_ff=0.0;
		bool IsRun_EH1=false;
		bool IsRun_EH2=false;
		bool IsRun_EH3=false;

		double Th_LiveTime = 10.0;
		for(int Det=0;Det<2;Det++)
		{
			TotalIBD_Before[Det] += 1.0*IBDInEachBin[Det][Bin];
			//	if(LiveTimeInEachBin[Det][Bin]>Th_LiveTime)
			if((LiveTimeInEachBin[Det][Bin]>Th_LiveTime)&&(MuEffInEachBin[Det][Bin]>0.001)&&(MultiEffInEachBin[Det][Bin]>0.001))
			//if((MuEffInEachBin[Det][Bin]>0.001)&&(MultiEffInEachBin[Det][Bin]>0.001))
			//if(IBDInEachBin[Det][Bin]>0)
			{

				IsRun_EH1=true;
			a += IBDInEachBin[Det][Bin]/(MuEffInEachBin[Det][Bin]*MultiEffInEachBin[Det][Bin])-
				(AmCInEachBin[Det][Bin]+AccInEachBin[Det][Bin]+Li9InEachBin[Det][Bin]+FastNInEachBin[Det][Bin])/MultiEffInEachBin[Det][Bin];
			rd_a += (IBDInEachBin[Det][Bin]/pow(MuEffInEachBin[Det][Bin],2.0)+
					pow(RD_AmCInEachBin[Det][Bin]*AmCInEachBin[Det][Bin],2.0)+
					pow(RD_AccInEachBin[Det][Bin]*AccInEachBin[Det][Bin],2.0)+
					pow(RD_Li9InEachBin[Det][Bin]*Li9InEachBin[Det][Bin],2.0)+
					pow(RD_FastNInEachBin[Det][Bin]*FastNInEachBin[Det][Bin],2.0)
					)/pow(MultiEffInEachBin[Det][Bin],2.0);
			}
		
		}

		for(int Det=2;Det<4;Det++)
		{
			TotalIBD_Before[Det] += 1.0*IBDInEachBin[Det][Bin];
//				if(LiveTimeInEachBin[Det][Bin]>Th_LiveTime)
			if((LiveTimeInEachBin[Det][Bin]>Th_LiveTime)&&(MuEffInEachBin[Det][Bin]>0.01)&&(MultiEffInEachBin[Det][Bin]>0.01))
			//if(IBDInEachBin[Det][Bin]>0)
		//	if((MuEffInEachBin[Det][Bin]>0.001)&&(MultiEffInEachBin[Det][Bin]>0.001))
			{
				IsRun_EH2=true;
			b += IBDInEachBin[Det][Bin]/(MuEffInEachBin[Det][Bin]*MultiEffInEachBin[Det][Bin])-
				(AmCInEachBin[Det][Bin]+AccInEachBin[Det][Bin]+Li9InEachBin[Det][Bin]+FastNInEachBin[Det][Bin])/MultiEffInEachBin[Det][Bin];
			rd_b += (IBDInEachBin[Det][Bin]/pow(MuEffInEachBin[Det][Bin],2.0)+
					pow(RD_AmCInEachBin[Det][Bin]*AmCInEachBin[Det][Bin],2.0)+
					pow(RD_AccInEachBin[Det][Bin]*AccInEachBin[Det][Bin],2.0)+
					pow(RD_Li9InEachBin[Det][Bin]*Li9InEachBin[Det][Bin],2.0)+
					pow(RD_FastNInEachBin[Det][Bin]*FastNInEachBin[Det][Bin],2.0)
					)/pow(MultiEffInEachBin[Det][Bin],2.0);
			}
			
		}

	
			
		for(int Det=4;Det<8;Det++)
		{
			TotalIBD_Before[Det] += 1.0*IBDInEachBin[Det][Bin];
		//		if(LiveTimeInEachBin[Det][Bin]>Th_LiveTime)
				if((LiveTimeInEachBin[Det][Bin]>Th_LiveTime)&&(MuEffInEachBin[Det][Bin]>0.01)&&(MultiEffInEachBin[Det][Bin]>0.01))
			//	if((MuEffInEachBin[Det][Bin]>0.001)&&(MultiEffInEachBin[Det][Bin]>0.001))
				//if(IBDInEachBin[Det][Bin]>0)
				{
					IsRun_EH3=true;
			ff += IBDInEachBin[Det][Bin]/(MuEffInEachBin[Det][Bin]*MultiEffInEachBin[Det][Bin])-
				(AmCInEachBin[Det][Bin]+AccInEachBin[Det][Bin]+Li9InEachBin[Det][Bin]+FastNInEachBin[Det][Bin])/MultiEffInEachBin[Det][Bin];
			rd_ff += (IBDInEachBin[Det][Bin]/pow(MuEffInEachBin[Det][Bin],2.0)+
					pow(RD_AmCInEachBin[Det][Bin]*AmCInEachBin[Det][Bin],2.0)+
					pow(RD_AccInEachBin[Det][Bin]*AccInEachBin[Det][Bin],2.0)+
					pow(RD_Li9InEachBin[Det][Bin]*Li9InEachBin[Det][Bin],2.0)+
					pow(RD_FastNInEachBin[Det][Bin]*FastNInEachBin[Det][Bin],2.0)
					)/pow(MultiEffInEachBin[Det][Bin],2.0);
			
				}
			}
			
			if(IsRun_EH1&&IsRun_EH2&&IsRun_EH3)
			{
				for(int Det=0;Det<8;Det++)
				{
				TotalIBD_After[Det] += 1.0*IBDInEachBin[Det][Bin];
				}
				Ma_simu[N24] += a;
				Mb_simu[N24] += b;
				Mf_simu[N24] += ff;

				RD_Ma_simu[N24] += rd_a;
				RD_Mb_simu[N24] += rd_b;
				RD_Mf_simu[N24] += rd_ff;

				Mf_Bin[N24] += ff;
				RD_Mf_Bin[N24] += rd_ff;
			NBarF[N24] += AlphaBetaInEachBin[0][Bin]*a+AlphaBetaInEachBin[1][Bin]*b;
			RD_NBarF[N24] += pow(AlphaBetaInEachBin[0][Bin],2.0)*rd_a+ pow(AlphaBetaInEachBin[1][Bin],2.0)*rd_b;
			}
		
	}

	


	///
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
			+pow(AlphaBetaInOneDay[1][N24]*Mb[N24]*RD_Mb[N24],2.0))/pow(AlphaBetaInOneDay[0][N24]*Ma[N24]+AlphaBetaInOneDay[1][N24]*Mb[N24],2.0)+pow(RD_Power,2.0));

		RD_Mf_simu[N24] += pow(Mf_simu[N24]*RD_Eff,2.0);
		RD_Mf_simu[N24] = sqrt(RD_Mf_simu[N24])/Mf_simu[N24];

		RD_Ma_simu[N24] += pow(Ma_simu[N24]*RD_Eff,2.0);
		RD_Ma_simu[N24] = sqrt(RD_Ma_simu[N24])/Ma_simu[N24];

		RD_Mb_simu[N24] += pow(Mb_simu[N24]*RD_Eff,2.0);
		RD_Mb_simu[N24] = sqrt(RD_Mb_simu[N24])/Mb_simu[N24];

		R_simu[2][N24] = Mf_simu[N24]/((AlphaBetaInOneDay[0][N24]-0.0000)*Ma_simu[N24]+(AlphaBetaInOneDay[1][N24]+0.00)*Mb_simu[N24]);

		RD_R_simu[2][N24] = sqrt(pow(RD_Mf_simu[N24],2.0)+(pow(AlphaBetaInOneDay[0][N24]*Ma_simu[N24]*RD_Ma_simu[N24],2.0)
			+pow(AlphaBetaInOneDay[1][N24]*Mb_simu[N24]*RD_Mb_simu[N24],2.0))/pow(AlphaBetaInOneDay[0][N24]*Ma_simu[N24]+AlphaBetaInOneDay[1][N24]*Mb_simu[N24],2.0)+pow(RD_Power,2.0));
	
		//////
		R_Bin[2][N24] = Mf_simu[N24]/NBarF[N24];

		RD_Mf_Bin[N24] += pow(Mf_simu[N24]*RD_Eff,2.0);
		RD_Mf_Bin[N24] = sqrt(RD_Mf_simu[N24])/Mf_simu[N24];

		RD_R_Bin[2][N24] = RD_R_simu[2][N24];//sqrt (pow(RD_Mf_Bin[N24],2.0)+RD_NBarF[N24]/pow(NBarF[N24],2.0)+pow(0.047*RD_Power,2.0)+pow(RD_Eff,2.0));
        
		cout<<N24<<"   "<<Ma_simu[N24]<<"   "<<Mb_simu[N24]<<"   "<<Mf_simu[N24]<<"   "<<R[2][N24]<<"   "<<R_simu[2][N24]<<"   "<<R_Bin[2][N24]<<"   "<<RD_R[2][N24]<<"   "<<RD_R_simu[2][N24]<<"    "<<Mf[N24]<<"   "<<Mf_simu[N24]<<"   "<<NBarF[N24]<<"   "<<RD_NBarF[N24]<<"   "<<RD_Mf_Bin[N24]<<"   "<<RD_Mf[N24]<<endl;

	//	cout<<N24<<"   "<<Mf_simu[N24]<<"   "<<NBarF[N24]<<"   "<<R_Bin[2][N24]<<"   "<<Mf[N24]<<"   "<<Mf_simu[N24]<<endl;
//cout<<N24<<"   "<<R[2][N24]<<"   "<<R_Bin[2][N24]<<"   "<<R_simu[2][N24]<<"   "<<RD_R[2][N24]<<"   "<<RD_R_Bin[2][N24]<<"   "<<RD_R_simu[2][N24]<<"   "<<RD_Mf_Bin[N24]<<"   "<<RD_NBarF[N24]<<"   "<<NBarF[N24]<<"   "<<RD_NBarF[N24]/pow(NBarF[N24],2.0)<<endl;
		//////cout<<N24<<"   "<<R[N24]<<"   "<<RD_R[N24]<<"   "<<RD_Ma[N24]<<"   "<<RD_Mb[N24]<<"   "<<RD_Mf[N24]<<"   "<<Mf[N24]<<"   "<<Ma[N24]<<"   "<<Mb[N24]<<"   "<<AlphaBetaInOneDay[0][N24]<<"   "<<AlphaBetaInOneDay[1][N24]<<endl;

	
	}

	cout<<"Before......";
	for(int Det=0;Det<8;Det++)
	{
		cout<<TotalIBD_Before[Det]<<"   ";
	}

	cout<<endl;

	cout<<"After......";
	for(int Det=0;Det<8;Det++)
	{
		cout<<TotalIBD_After[Det]<<"   ";
	}
	cout<<endl;


	cout<<"(B-A)/B (%):   ";
	for(int Det=0;Det<8;Det++)
	{
		cout<<100*(TotalIBD_Before[Det]-TotalIBD_After[Det])/TotalIBD_Before[Det]<<"   ";
	}
	cout<<endl;
	
	///////////////////////////////////////////normalization///////////////////////////////////////////////////////////////////////////////////
	Double_t MeanRatio_AD[8]={0.0};
	for (int Det=0;Det<8;Det++)
	{
		for(int N24=0;N24<24;N24++)
		{
			MeanRatio_AD[Det] += R_Det[Det][N24];
		}
		for(int N24=0;N24<24;N24++)
		{
			R_Det[Det][N24] = 24.0*R_Det[Det][N24]/MeanRatio_AD[Det];
		}
	}
	

	///////////////////////////////////////////choose the type to fit//////////////////////////////////////////////////////////////////////////
	for(int i=0;i<24;i++)
	{
		double w1,w2;
		//EH1
		w1 = pow(R_Det[1][i]*RD_R_Det[1][i],2.0)/(pow(R_Det[0][i]*RD_R_Det[0][i],2.0)+pow(R_Det[1][i]*RD_R_Det[1][i],2.0));
		w2 = pow(R_Det[0][i]*RD_R_Det[0][i],2.0)/(pow(R_Det[0][i]*RD_R_Det[0][i],2.0)+pow(R_Det[1][i]*RD_R_Det[1][i],2.0));
		R[0][i]=(w1*R_Det[0][i]+w2*R_Det[1][i]);
		RD_R[0][i]=sqrt(pow(w1*R_Det[0][i]*RD_R_Det[0][i],2.0)+pow(w2*R_Det[1][i]*RD_R_Det[1][i],2.0));
		
		//EH2
		w1 = pow(R_Det[3][i]*RD_R_Det[3][i],2.0)/(pow(R_Det[2][i]*RD_R_Det[2][i],2.0)+pow(R_Det[3][i]*RD_R_Det[3][i],2.0));
		w2 = pow(R_Det[2][i]*RD_R_Det[2][i],2.0)/(pow(R_Det[2][i]*RD_R_Det[2][i],2.0)+pow(R_Det[3][i]*RD_R_Det[3][i],2.0));
		R[1][i]=(w1*R_Det[2][i]+w2*R_Det[3][i]);
		RD_R[1][i]=sqrt(pow(w1*R_Det[2][i]*RD_R_Det[2][i],2.0)+pow(w2*R_Det[3][i]*RD_R_Det[3][i],2.0));
		
		//EH3
		R[2][i] = R_Bin[2][i];
		RD_R[2][i] = RD_R_Bin[2][i];
		cout<<i<<"   ";//
		/*for(int Hidx=0;Hidx<3;Hidx++)
		{
			cout<<R[Hidx][i]<<"   "<<RD_R[Hidx][i]<<"      ";
		}
		cout<<endl;*/
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
		R[0][i]=AVEP[0]*24.0*R[0][i]/MeanRatio[0];
		R[1][i]=AVEP[1]*24.0*R[1][i]/MeanRatio[1];
		R[2][i]=AVEP[2]*24.0*R[2][i]/MeanRatio[2];
	}
	for(int i=0;i<24;i++)
	{
		for(int Hidx=0;Hidx<3;Hidx++)
		{
			cout<<R[Hidx][i]<<"   "<<RD_R[Hidx][i]<<"      ";
		}
		cout<<endl;
	}
	//save to .root for FFT
	/*
	double Ratio_t[3];
	TFile  *F_RatioInOneDay = new TFile("RatioInOneDay.root","recreate");
	TTree *Tree_RatioInOneDay = new TTree("RatioInOneDay","RatioInOneDay");
	Tree_RatioInOneDay->Branch("RatioInOneDay",Ratio_t,"Ratio_t[3]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<3;Det++)
		{
			Ratio_t[Det] = R[Det][Bin];
		}
		Tree_RatioInOneDay->Fill();
	}
	Tree_RatioInOneDay->Write();
	
	double RD_Ratio_t[3];
	TFile  *F_RD_RatioInOneDay = new TFile("RD_RatioInOneDay.root","recreate");
	TTree *Tree_RD_RatioInOneDay = new TTree("RD_RatioInOneDay","RD_RatioInOneDay");
	Tree_RD_RatioInOneDay->Branch("RD_RatioInOneDay",RD_Ratio_t,"RD_Ratio_t[3]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<3;Det++)
		{
			RD_Ratio_t[Det] = RD_R[Det][Bin];
		}
		Tree_RD_RatioInOneDay->Fill();
	}
	Tree_RD_RatioInOneDay->Write();
	*/
	////////use the result from another program//////
	/* TFile *F_Bin_IBD = new TFile("../IBD.root");
	     TTree *Tree_Bin_IBD = (TTree*)F_Bin_IBD->Get("IBD");
		     Tree_Bin_IBD->SetBranchAddress("IBD",IBD_t_Bin);
	double Ratio_t[3], RD_Ratio_t[3];
	TFile *F_RatioInOneDay = new TFile("RatioInOneDay.root");
	TTree *Tree_RatioInOneDay = (TTree*)F_RatioInOneDay->Get("RatioInOneDay");
	Tree_RatioInOneDay->SetBranchAddress("RatioInOneDay",Ratio_t);
	TFile *F_RD_RatioInOneDay = new TFile("RD_RatioInOneDay.root");
	TTree *Tree_RD_RatioInOneDay = (TTree*)F_RD_RatioInOneDay->Get("RD_RatioInOneDay");
	Tree_RD_RatioInOneDay->SetBranchAddress("RD_RatioInOneDay",RD_Ratio_t);
	for(int Bin=0;Bin<24;Bin++)
	{
		Tree_RatioInOneDay->GetEntry(Bin);
		Tree_RD_RatioInOneDay->GetEntry(Bin);
		for(int Det=0;Det<3;Det++)
		{
			R[Det][Bin] = Ratio_t[Det];
			RD_R[Det][Bin] = RD_Ratio_t[Det];
		}
	}
*/

TFile *f_Tsinghua = new TFile("Final_Tsinghua.root");

TH1D *h_EH1_Tsinghua = (TH1D*)f_Tsinghua->Get("hEH1");
TH1D *h_EH2_Tsinghua = (TH1D*)f_Tsinghua->Get("hEH2");
TH1D *h_EH3_Tsinghua = (TH1D*)f_Tsinghua->Get("hEH3");

	for(int Bin=0;Bin<24;Bin++)
	{
		R[0][Bin] = h_EH1_Tsinghua->GetBinContent(Bin+1);
		RD_R[0][Bin] = h_EH1_Tsinghua->GetBinError(Bin+1);
		R[1][Bin] = h_EH2_Tsinghua->GetBinContent(Bin+1);
		RD_R[1][Bin] = h_EH2_Tsinghua->GetBinError(Bin+1);
		R[2][Bin] = h_EH3_Tsinghua->GetBinContent(Bin+1);
		RD_R[2][Bin] = h_EH3_Tsinghua->GetBinError(Bin+1);
	}

	
	//////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////Fit////////////////////////////////////////////////////////////////////////////////////////////////////
  
	TMinuit *gMinuit = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
   gMinuit->SetFCN(ChiSquare);

   Double_t arglist[10];
   Int_t ierflg = 0;

   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
//   Double_t vstart[8] = {0.9,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,10.0};
//   Double_t step[8] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01};
   gMinuit->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg);
   gMinuit->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg);
   gMinuit->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg);
   gMinuit->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg);
//   gMinuit->mnparm(7, "T0", vstart[7], step[7], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 20000;
   arglist[1] = 1.0.;
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

// Set starting values and step sizes for parameters
//   Double_t vstart[8] = {1.0,0,0,0,0,0,0,0};
//   Double_t step[8] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.1};
   gMinuit_EH1->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg_EH1);
//   gMinuit_EH1->mnparm(7, "T0", vstart[7], step[7], 0,0,ierflg_EH1);
// Now ready for minimization step
   arglist_EH1[0] = 20000;
   arglist_EH1[1] = 1.;
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

// Set starting values and step sizes for parameters
//   Double_t vstart[8] = {1.0,0,0,0,0,0,0,0};
//   Double_t step[8] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.1};
   gMinuit_EH2->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg_EH2);
//   gMinuit_EH2->mnparm(7, "T0", vstart[7], step[7], 0,0,ierflg_EH2);

// Now ready for minimization step
   arglist_EH2[0] = 20000;
   arglist_EH2[1] = 1.;
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

// Set starting values and step sizes for parameters
//   Double_t vstart[8] = {1.0,0,0,0,0,0,0,0};
//   Double_t step[8] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.1};
   gMinuit_EH3->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg_EH3);
//   gMinuit_EH3->mnparm(7, "T0", vstart[7], step[7], 0,0,ierflg_EH3);
// Now ready for minimization step
   arglist_EH3[0] = 20000;
   arglist_EH3[1] = 1.;
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
	const char *file_Name[3]={"ThreeSites_Check_Tsinghua/Ratio_EH1_OneDay_sidereal.pdf","ThreeSites_Check_Tsinghua/Ratio_EH2_OneDay_sidereal.pdf","ThreeSites_Check_Tsinghua/Ratio_EH3_OneDay_sidereal.pdf"};

	Double_t ParResult_single[3][8],ParErrResult_single[3][8];
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
		gr[Hidx]->GetYaxis()->SetRangeUser(AVEP[Hidx]-0.06,AVEP[Hidx]+0.06);

		gr[Hidx]->SetTitle("");

		gr[Hidx]->GetYaxis()->SetTitleOffset(0.8);
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

			f_Plot[Hidx]->SetParameter(0,AVEP[Hidx]);

		for(int i=1;i<7;i++)
		{
			f_Plot[Hidx]->SetParameter(i,ParResult[i]);
		}
		f_Plot[Hidx]->SetParameter(7,Hidx);
//		f_Plot[Hidx]->SetParameter(8,ParResult[7]);

		f_Plot[Hidx]->SetLineColor(kRed);
		f_Plot[Hidx]->Draw("same");

		/////////////////plot the fit result:site by site////////////////////////
		f_Plot_single[Hidx] = new TF1(c_Name_single[Hidx],PlotFunc,0,86165.0,8);
		
			f_Plot_single[Hidx]->SetParameter(0,AVEP[Hidx]);
		
		for(int i=1;i<7;i++)
		{
			f_Plot_single[Hidx]->SetParameter(i,ParResult_single[Hidx][i]);
		}
		f_Plot_single[Hidx]->SetParameter(7,Hidx);
//////////////		f_Plot_single[Hidx]->SetParameter(8,ParResult_single[Hidx][7]);

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
		Double_t x_Time=0.0, par_band[9],par_band2[9];
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
				
				for(int pN=1;pN<8;pN++)
				{
					if(pN!=7)
					{
					Double_t r01 = Ran_par->Gaus(0.0,1.0);
					par_band[pN] = ParResult[pN]+ 1.0*r01*ParErrResult[pN];
					}
				}
				xy_band[xN][yN] = PlotFunc(&x_Time,par_band);
				y_TH1F_band->Fill(xy_band[xN][yN]);
			}
			for(int pN=1;pN<8;pN++)
			{
				if(pN!=7)
					{
				par_band2[pN] = ParResult[pN];
				}
			}
			y_Center[xN] = PlotFunc(&x_Time,par_band2);
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
		//cout<<sigma_y<<endl;
		sigma_y=0.0;
		

		//site by site
		for(int xN=0;xN<100;xN++)
		{
			TH1F *y_TH1F_band = new TH1F();
			x_Time = 861.650*xN;
			for(int yN=0;yN<1000;yN++)
			{
				
				for(int pN=1;pN<8;pN++)
				{
					if(pN!=7)
					{
					Double_t r01 = Ran_par->Gaus(0.0,1.0);
					par_band[pN] = ParResult_single[Hidx][pN]+ 1.0*r01*ParErrResult_single[Hidx][pN];
					}
				}
				xy_band[xN][yN] = PlotFunc(&x_Time,par_band);
				y_TH1F_band->Fill(xy_band[xN][yN]);
			}
			for(int pN=1;pN<8;pN++)
			{
				if(pN!=7)
					{
				par_band2[pN] = ParResult_single[Hidx][pN];
				}
			}
			y_Center[xN] = PlotFunc(&x_Time,par_band2);
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
			grb->SetMarkerColor(kBlue);
			grb->SetLineColor(kBlue);
			grb->Draw("CSAME");
		}
		//cout<<sigma_y<<endl;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////
		leg[Hidx] = new TLegend(0, 0.75, 0.55, 0.9);
		leg[Hidx]->AddEntry(gr[Hidx],c_Name[Hidx],"");
		//leg[Hidx]->AddEntry(gr[Hidx],"EH3 - R(t) - data","");
		leg[Hidx]->SetFillStyle(0);
		leg[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
		leg[Hidx]->Draw();
		////////////
		leg2[Hidx] = new TLegend(0.5, 0.75, 0.9, 0.9);
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
	FILE* m_outfile = fopen("FitResult_Check_NoPhase_Tsinghua.txt", "w+");

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
//   Double_t vstart[8] = {0.9,-10.0,-10.0,-10.0,-10.0,-10.0,-10.0,10.0};
//   Double_t step[8] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.01};
   gMinuit->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg);
   gMinuit->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg);
   gMinuit->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg);
   gMinuit->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg);
//   gMinuit->mnparm(7, "T0", vstart[7], step[7], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 20000;
   arglist[1] = 1.0.;
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

// Set starting values and step sizes for parameters
//   Double_t vstart[8] = {1.0,0,0,0,0,0,0,0};
//   Double_t step[8] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.1};
   gMinuit_EH1->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg_EH1);
   gMinuit_EH1->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg_EH1);
//   gMinuit_EH1->mnparm(7, "T0", vstart[7], step[7], 0,0,ierflg_EH1);

// Now ready for minimization step
   arglist_EH1[0] = 20000;
   arglist_EH1[1] = 1.;
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

// Set starting values and step sizes for parameters
//   Double_t vstart[8] = {1.0,0,0,0,0,0,0,0};
//   Double_t step[8] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.1};
   gMinuit_EH2->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg_EH2);
   gMinuit_EH2->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg_EH2);
//   gMinuit_EH2->mnparm(7, "T0", vstart[7], step[7], 0,0,ierflg_EH2);

// Now ready for minimization step
   arglist_EH2[0] = 20000;
   arglist_EH2[1] = 1.;
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

// Set starting values and step sizes for parameters
//   Double_t vstart[8] = {1.0,0,0,0,0,0,0,0};
//   Double_t step[8] = {0.0001, 0.01, 0.01, 0.01, 0.01, 0.01,0.01,0.1};
   gMinuit_EH3->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(1, "A1", vstart[1], step[1], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(2, "A2", vstart[2], step[2], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(3, "A3", vstart[3], step[3], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(4, "A4", vstart[4], step[4], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(5, "B1", vstart[5], step[5], 0,0,ierflg_EH3);
   gMinuit_EH3->mnparm(6, "B2", vstart[6], step[6], 0,0,ierflg_EH3);
//   gMinuit_EH3->mnparm(7, "T0", vstart[7], step[7], 0,0,ierflg_EH3);


// Now ready for minimization step
   arglist_EH3[0] = 20000;
   arglist_EH3[1] = 1.;
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
  

	
	
}

Double_t PlotFunc(Double_t *x, Double_t *par)
{
	//0   1   2   3   4   5   6  7       8
	//C   A1  A2  A3  A4  B1  B2  HallID  TZero
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
	double TZero = 0.0;//par[7];
	Int_t HallID=int(par[7]);
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = AVEP[HallID];
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
			(Nyt*par[1]*0.001+2.0*E*Nyt*Nzt*par[2]+Nxt*par[3]*0.001-2.0*E*Nxt*Nzt*par[4])*sin(wP*(x[0]+TZero)) +
			(-1.0*Nxt*par[1]*0.001-2.0*E*Nxt*Nzt*par[2]+Nyt*par[3]*0.001-2.0*E*Nyt*Nzt*par[4])*cos(wP*(x[0]+TZero)) +
			(E*Nxt*Nyt*par[5]-E*(Nxt*Nxt-Nyt*Nyt)*par[6])*sin(2.0*wP*(x[0]+TZero))+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[5]-2.0*E*Nxt*Nyt*par[6])*cos(2.0*wP*(x[0]+TZero)));
	}
	return TotalP;

}

Double_t FitFunc1(Double_t x, Double_t *par)//EH1, C fixed to 1.0
{
	//0   1   2   3   4   5   6  7
	//C   A1  A2  A3  A4  B1  B2 TZero
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
	double TZero = 0.0;//par[7];
	Int_t HallID=0;
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = AVEP[HallID];
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
			(Nyt*par[1]*0.001+2.0*E*Nyt*Nzt*par[2]+Nxt*par[3]*0.001-2.0*E*Nxt*Nzt*par[4])*sin(wP*(x+TZero)) +
			(-1.0*Nxt*par[1]*0.001-2.0*E*Nxt*Nzt*par[2]+Nyt*par[3]*0.001-2.0*E*Nyt*Nzt*par[4])*cos(wP*(x+TZero)) +
			(E*Nxt*Nyt*par[5]-E*(Nxt*Nxt-Nyt*Nyt)*par[6])*sin(2.0*wP*(x+TZero))+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[5]-2.0*E*Nxt*Nyt*par[6])*cos(2.0*wP*(x+TZero)));
	}
	return TotalP;

}

Double_t FitFunc2(Double_t x, Double_t *par)//EH2, C fixed to 1.0
{
	//0   1   2   3   4   5   6  7
	//C   A1  A2  A3  A4  B1  B2 TZero
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
	double TZero =0.0;// par[7];
	Int_t HallID=1;
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = AVEP[HallID];
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
			(Nyt*par[1]*0.001+2.0*E*Nyt*Nzt*par[2]+Nxt*par[3]*0.001-2.0*E*Nxt*Nzt*par[4])*sin(wP*(x+TZero)) +
			(-1.0*Nxt*par[1]*0.001-2.0*E*Nxt*Nzt*par[2]+Nyt*par[3]*0.001-2.0*E*Nyt*Nzt*par[4])*cos(wP*(x+TZero)) +
			(E*Nxt*Nyt*par[5]-E*(Nxt*Nxt-Nyt*Nyt)*par[6])*sin(2.0*wP*(x+TZero))+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[5]-2.0*E*Nxt*Nyt*par[6])*cos(2.0*wP*(x+TZero)));
	}
	return TotalP;

}

Double_t FitFunc3(Double_t x, Double_t *par)//EH3, C fixed to 1.0
{
	//0   1   2   3   4   5   6  7
	//C   A1  A2  A3  A4  B1  B2 TZero
	//A1,A3: 1e-21; A2,A4,B1,B2:1e-18
	double TZero = 0.0;//par[7];
	Int_t HallID=2;
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	Double_t TotalEveFrac = 0.0;
	Double_t TotalP = AVEP[HallID];
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
			(Nyt*par[1]*0.001+2.0*E*Nyt*Nzt*par[2]+Nxt*par[3]*0.001-2.0*E*Nxt*Nzt*par[4])*sin(wP*(x+TZero)) +
			(-1.0*Nxt*par[1]*0.001-2.0*E*Nxt*Nzt*par[2]+Nyt*par[3]*0.001-2.0*E*Nyt*Nzt*par[4])*cos(wP*(x+TZero)) +
			(E*Nxt*Nyt*par[5]-E*(Nxt*Nxt-Nyt*Nyt)*par[6])*sin(2.0*wP*(x+TZero))+ 
			(-0.5*E*(Nxt*Nxt-Nyt*Nyt)*par[5]-2.0*E*Nxt*Nyt*par[6])*cos(2.0*wP*(x+TZero)));
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
     delta  = (R[0][i]-FitFunc1(i*WidthOfBin,par))/RD_R[0][i];
     chisq += delta*delta;
   }
   //EH2
   for (i=0;i<nbins; i++) {
     delta  = (R[1][i]-FitFunc2(i*WidthOfBin,par))/RD_R[1][i];
     chisq += delta*delta;
   }
   //EH3
   for (i=0;i<nbins; i++) {
     delta  = (R[2][i]-FitFunc3(i*WidthOfBin,par))/RD_R[2][i];
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
     delta  = (R[0][i]-FitFunc1(i*WidthOfBin,par))/RD_R[0][i];
     chisq += delta*delta;
   }

   f = chisq;
   /*
    //cout<<f<<"   ";
   for(int i=0;i<6;i++)
   {
	   //cout<<par[i]<<"   ";
   }
   //cout<<endl;
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
     delta  = (R[1][i]-FitFunc2(i*WidthOfBin,par))/RD_R[1][i];
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
     delta  = (R[2][i]-FitFunc3(i*WidthOfBin,par))/RD_R[2][i];
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
	////cout<<"sin2t132: "<<pow(sin(2.0*Th13),2.0)<<endl;
	////cout<<pow(sin(2.0*Th13),2.0)*pow(sin(1.267*Dm[2][0]*L2/E2),2.0)<<endl;
	return 1 - pow(sin(2.0*Th13),2.0)*pow(sin(0.25*Dm[2][0]*L2/E2),2.0) - pow(cos(Th13),4.0)*pow(sin(2.0*Th12),2.0)*pow(sin(0.25*Dm[1][0]*L2/E2),2.0);
}
