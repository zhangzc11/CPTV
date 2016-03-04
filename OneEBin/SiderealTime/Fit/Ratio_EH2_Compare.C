

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
double R_2[3][24]={0.0};
double R_3[3][24]={0.0};
double R_noI[3][24]={0.0};
double RD_R[3][24]={0.0};
double RD_R_2[3][24]={0.0};
double RD_R_3[3][24]={0.0};

double RD_R_noI[3][24]={0.0};

double R_Det[8][24]={{0.0}};
double RD_R_Det[8][24]={{0.0}};
double R_Det_2[8][24]={{0.0}};
double RD_R_Det_2[8][24]={{0.0}};
double R_Det_3[8][24]={{0.0}};
double RD_R_Det_3[8][24]={{0.0}};


double R_Bin[8][24]={{0.0}};
double RD_R_Bin[8][24]={{0.0}};

double R_simu[8][24]={{0.0}};
double RD_R_simu[8][24]={{0.0}};


Double_t ParResult[7],ParErrResult[7];
Double_t ParResult_EH1[7],ParErrResult_EH1[7];
Double_t ParResult_EH2[7],ParErrResult_EH2[7];
Double_t ParResult_EH3[7],ParErrResult_EH3[7];

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

	int NOF_3Site_5Bin = 352; //3*5*24-8
	int NOF_SiteBySite_5Bin = 112; //5*24-8
	int NOF_3Site_1Bin = 66; // 3*24-6
	int NOF_SiteBySite_1Bin = 18; //24-6


	int HallIdx = 1;
void Ratio_EH2_Compare()
{
	


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
	double RD_Power = 0.009;
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

	Double_t M_2[24];//={0.0};
	memset(M,0.0,sizeof(M));
	Double_t RD_M_2[24];//={0.0};
	memset(RD_M,0.0,sizeof(RD_M));
	Double_t NBar_2[24];//
	double NBar_noI_2[24]={0.0};
	memset(NBar,0.0,sizeof(NBar));
	Double_t RD_NBar_2[24];//
	memset(RD_NBar,0.0,sizeof(RD_NBar));

	Double_t M_3[24];//={0.0};
	memset(M,0.0,sizeof(M));
	Double_t RD_M_3[24];//={0.0};
	memset(RD_M,0.0,sizeof(RD_M));
	Double_t NBar_3[24];//
	double NBar_noI_3[24]={0.0};
	memset(NBar,0.0,sizeof(NBar));
	Double_t RD_NBar_3[24];//
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
		M_2[i]=0.0;
		RD_M_2[i]=0.0;
		NBar_2[i]=0.0;
		RD_NBar_2[i]=0.0;
		M_3[i]=0.0;
		RD_M_3[i]=0.0;
		NBar_3[i]=0.0;
		RD_NBar_3[i]=0.0;
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
			M_2[N24] +=  IBDInOneDay[Det][N24];
			NBar_3[N24] += FullTimeInOneDay[Det][N24];

		RD_M[N24] += pow(M[N24]*RD_Eff,2.0);

		RD_M[N24] = sqrt(RD_M[N24])/M[N24];

		RD_M_2[N24] = 1.0/sqrt(M_2[N24]);


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
		R_Det_2[Det][N24] = M_2[N24]/NBar[N24];
		R_Det_3[Det][N24] = M_2[N24]/NBar_3[N24];

		RD_R_Det[Det][N24] = sqrt(pow(RD_M[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0));
		RD_R_Det_3[Det][N24] = 1.0/sqrt(M_2[N24]);
	    RD_R_Det_2[Det][N24] =sqrt(pow(RD_M_2[N24],2.0)+pow(RD_Power,2.0)*temp2/pow(temp,2.0)); 	

		}
	}

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

	Double_t MeanRatio_AD_2[8]={0.0};
	for (int Det=0;Det<8;Det++)
	{
		for(int N24=0;N24<24;N24++)
		{
			MeanRatio_AD_2[Det] += R_Det_2[Det][N24];
		}
		for(int N24=0;N24<24;N24++)
		{
			R_Det_2[Det][N24] = 24.0*R_Det_2[Det][N24]/MeanRatio_AD_2[Det];
		}
	}

	Double_t MeanRatio_AD_3[8]={0.0};
	for (int Det=0;Det<8;Det++)
	{
		for(int N24=0;N24<24;N24++)
		{
			MeanRatio_AD_3[Det] += R_Det_3[Det][N24];
		}
		for(int N24=0;N24<24;N24++)
		{
			R_Det_3[Det][N24] = 24.0*R_Det_3[Det][N24]/MeanRatio_AD_3[Det];
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
		//cout<<i<<"   ";//
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


	///////////////////////////////////////////choose the type to fit//////////////////////////////////////////////////////////////////////////
	for(int i=0;i<24;i++)
	{
		double w1,w2;
		//EH1
		w1 = pow(R_Det_2[1][i]*RD_R_Det_2[1][i],2.0)/(pow(R_Det_2[0][i]*RD_R_Det_2[0][i],2.0)+pow(R_Det_2[1][i]*RD_R_Det_2[1][i],2.0));
		w2 = pow(R_Det_2[0][i]*RD_R_Det_2[0][i],2.0)/(pow(R_Det_2[0][i]*RD_R_Det_2[0][i],2.0)+pow(R_Det_2[1][i]*RD_R_Det_2[1][i],2.0));
		R_2[0][i]=(w1*R_Det_2[0][i]+w2*R_Det_2[1][i]);
		RD_R_2[0][i]=sqrt(pow(w1*R_Det_2[0][i]*RD_R_Det_2[0][i],2.0)+pow(w2*R_Det_2[1][i]*RD_R_Det_2[1][i],2.0));
		
		//EH2
		w1 = pow(R_Det_2[3][i]*RD_R_Det_2[3][i],2.0)/(pow(R_Det_2[2][i]*RD_R_Det_2[2][i],2.0)+pow(R_Det_2[3][i]*RD_R_Det_2[3][i],2.0));
		w2 = pow(R_Det_2[2][i]*RD_R_Det_2[2][i],2.0)/(pow(R_Det_2[2][i]*RD_R_Det_2[2][i],2.0)+pow(R_Det_2[3][i]*RD_R_Det_2[3][i],2.0));
		R_2[1][i]=(w1*R_Det_2[2][i]+w2*R_Det_2[3][i]);
		RD_R_2[1][i]=sqrt(pow(w1*R_Det_2[2][i]*RD_R_Det_2[2][i],2.0)+pow(w2*R_Det_2[3][i]*RD_R_Det_2[3][i],2.0));
		
		//EH3
		R_2[2][i] = R_Bin[2][i];
		RD_R_2[2][i] = RD_R_Bin[2][i];
		//cout<<i<<"   ";//
		/*for(int Hidx=0;Hidx<3;Hidx++)
		{
			cout<<R_2[Hidx][i]<<"   "<<RD_R_2[Hidx][i]<<"      ";
		}
		cout<<endl;*/
	}

	Double_t MeanRatio_2[3] = {0.0};
	for(int i=0;i<24;i++)
	{
		MeanRatio_2[0] += R_2[0][i];
		MeanRatio_2[1] += R_2[1][i];
		MeanRatio_2[2] += R_2[2][i];
	}
	for(int i=0;i<24;i++)
	{
		R_2[0][i]=AVEP[0]*24.0*R_2[0][i]/MeanRatio_2[0];
		R_2[1][i]=AVEP[1]*24.0*R_2[1][i]/MeanRatio_2[1];
		R_2[2][i]=AVEP[2]*24.0*R_2[2][i]/MeanRatio_2[2];
	}

	///////////////////////////////////////////choose the type to fit//////////////////////////////////////////////////////////////////////////
	for(int i=0;i<24;i++)
	{
		double w1,w2;
		//EH1
		w1 = pow(R_Det_3[1][i]*RD_R_Det_3[1][i],2.0)/(pow(R_Det_3[0][i]*RD_R_Det_3[0][i],2.0)+pow(R_Det_3[1][i]*RD_R_Det_3[1][i],2.0));
		w2 = pow(R_Det_3[0][i]*RD_R_Det_3[0][i],2.0)/(pow(R_Det_3[0][i]*RD_R_Det_3[0][i],2.0)+pow(R_Det_3[1][i]*RD_R_Det_3[1][i],2.0));
		R_3[0][i]=(w1*R_Det_3[0][i]+w2*R_Det_3[1][i]);
		RD_R_3[0][i]=sqrt(pow(w1*R_Det_3[0][i]*RD_R_Det_3[0][i],2.0)+pow(w2*R_Det_3[1][i]*RD_R_Det_3[1][i],2.0));
		
		//EH2
		w1 = pow(R_Det_3[3][i]*RD_R_Det_3[3][i],2.0)/(pow(R_Det_3[2][i]*RD_R_Det_3[2][i],2.0)+pow(R_Det_3[3][i]*RD_R_Det_3[3][i],2.0));
		w2 = pow(R_Det_3[2][i]*RD_R_Det_3[2][i],2.0)/(pow(R_Det_3[2][i]*RD_R_Det_3[2][i],2.0)+pow(R_Det_3[3][i]*RD_R_Det_3[3][i],2.0));
		R_3[1][i]=(w1*R_Det_3[2][i]+w2*R_Det_3[3][i]);
		RD_R_3[1][i]=sqrt(pow(w1*R_Det_3[2][i]*RD_R_Det_3[2][i],2.0)+pow(w2*R_Det_3[3][i]*RD_R_Det_3[3][i],2.0));
		
		//EH3
		R_3[2][i] = R_Bin[2][i];
		RD_R_3[2][i] = RD_R_Bin[2][i];
		//cout<<i<<"   ";//
		/*for(int Hidx=0;Hidx<3;Hidx++)
		{
			cout<<R_3[Hidx][i]<<"   "<<RD_R_3[Hidx][i]<<"      ";
		}
		cout<<endl;*/
	}

	Double_t MeanRatio_3[3] = {0.0};
	for(int i=0;i<24;i++)
	{
		MeanRatio_3[0] += R_3[0][i];
		MeanRatio_3[1] += R_3[1][i];
		MeanRatio_3[2] += R_3[2][i];
	}
	for(int i=0;i<24;i++)
	{
		R_3[0][i]=AVEP[0]*24.0*R_3[0][i]/MeanRatio_3[0];
		R_3[1][i]=AVEP[1]*24.0*R_3[1][i]/MeanRatio_3[1];
		R_3[2][i]=AVEP[2]*24.0*R_3[2][i]/MeanRatio_3[2];
	}


	TCanvas *myC1 = new TCanvas("C1","C1",200,10,800,600);
	gStyle->SetOptFit(1);
	//myC1->SetGrid();
	myC1->GetFrame()->SetFillColor(21);
	myC1->GetFrame()->SetBorderSize(12);
	
	const Int_t n = 24;
	Float_t x[n],y[n],ex[n],ey[n];
	for(int i=0;i<n;i++)
	{
		x[i]=i*WidthOfBin;
		y[i]=R[HallIdx][i];
		ex[i]=0;
		ey[i]=R[HallIdx][i]*RD_R[HallIdx][i];
		//cout<<y[i]<<"   "<<ey[i]<<endl;
	}
	TGraphErrors *gr1 = new TGraphErrors(n,x,y,ex,ey);
	//gr1->SetTitle("Time variation of the Data_Vs_Expectation - EH1");
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(21);

	
	const Int_t n2 = 24;
	Float_t x2[n2],y2[n2],ex2[n2],ey2[n2];
	for(int i=0;i<n2;i++)
	{
		x2[i]=i*WidthOfBin;
		y2[i]=R_2[HallIdx][i];
		ex2[i]=0;
		ey2[i]=R_2[HallIdx][i]*RD_R_2[HallIdx][i];
		//cout<<y[i]<<"   "<<ey[i]<<endl;
	}
	TGraphErrors *gr2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
	//gr1->SetTitle("Time variation of the Data_Vs_Expectation - EH1");
	gr2->SetMarkerColor(3);
	gr2->SetMarkerStyle(21);

	
	
	const Int_t n3 = 24;
	Float_t x3[n3],y3[n3],ex3[n3],ey3[n3];
	for(int i=0;i<n2;i++)
	{
		x3[i]=i*WidthOfBin;
		y3[i]=R_3[HallIdx][i];
		ex3[i]=0;
		ey3[i]=R_3[HallIdx][i]*RD_R_3[HallIdx][i];
		//cout<<y[i]<<"   "<<ey[i]<<endl;
	}
	TGraphErrors *gr3 = new TGraphErrors(n3,x3,y3,ex3,ey3);
	//gr3->SetTitle("Time variation of the Data_Vs_Expectation - EH1");
	gr3->SetMarkerColor(2);
	gr3->SetMarkerStyle(21);

	TMultiGraph *mg = new TMultiGraph();

	mg->Add(gr1);
	mg->Add(gr2);
	mg->Add(gr3);

	mg->Draw("AP");

	mg->GetXaxis()->SetTitle("sidereal time(seconds)");
	mg->GetYaxis()->SetTitle("Data/Expectation");
	//mg->GetYaxis()->SetRangeUser(0.96,1.04);

	mg->SetTitle("");

	mg->GetYaxis()->SetTitleOffset(0.98);
	mg->GetYaxis()->SetTitleSize(0.05);
	mg->GetYaxis()->SetLabelSize(0.04);
	mg->GetYaxis()->SetLabelOffset(0.0);
	
	mg->GetXaxis()->SetTitleOffset(0.8);
	mg->GetXaxis()->SetTitleSize(0.06);
	mg->GetXaxis()->SetLabelSize(0.035);
	mg->GetXaxis()->SetLabelOffset(0.0);

	

	mg->Draw("AP");

	TLegend* leg2 = new TLegend(0.1, 0.7, 0.8, 0.9);
	leg2->AddEntry(gr3,"EH2-Only IBD candidate considered, flux = const","lP");
	 leg2->AddEntry(gr2,"EH2-Only IBD candidate considered, flux = flux(t)","lP");
   leg2->AddEntry(gr1,"EH2-With bkg., efficiency etc. correction","lP");
   leg2->SetFillStyle(0);
   leg2->SetBorderSize(0);
   leg2->SetTextColor(1);
   leg2->Draw();

	gPad->Modified();
   myC1->SaveAs("Ratio_EH2_OneDay_sidereal_const_Compare.pdf");


}

Double_t func_Prob_combine_const(Double_t *x, Double_t *par)
{
	return par[0];
}



