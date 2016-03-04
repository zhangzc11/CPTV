#include <math.h>

int HallID = 0;
const double pi = 3.141592653;

double IndexCD[4] = {0,0,0,0};

const double Dm21 = 7.53e-23;//GeV^2;
const double Dm31 = 2.52e-21;//GeV^2;

double Dm[3][3] = {
	{0.0,-1*Dm21,-1*Dm31},
	{Dm21,0.0,Dm21-Dm31},
	{Dm31,Dm31-Dm21,0.0}};//Dm[i][j] = m^2i - m^2j,GeV^2

const double Th12 = 0.5*asin(sqrt(0.846));//theta 12
const double Th23 = 0.5*asin(sqrt(0.999));//theta 23
const double Th13 = 0.0;//0.5*asin(sqrt(0.093));//theta 13


double U[3][3] = {
	{cos(Th12)*cos(Th13),sin(Th12)*cos(Th13),sin(Th13)},
	{-1*sin(Th12)*cos(Th23)-cos(Th12)*sin(Th13)*sin(Th23),cos(Th12)*cos(Th23)-sin(Th12)*sin(Th13)*sin(Th23),cos(Th13)*sin(Th23)},
	{sin(Th12)*sin(Th23)-cos(Th12)*sin(Th13)*cos(Th23),-1*cos(Th12)*sin(Th23)-sin(Th12)*sin(Th13)*cos(Th23),cos(Th13)*cos(Th23)}};

TComplex Tauab(int a,int b,double E,double L);//E:MeV,L:m
TComplex Mee(double E,double L,int i,int j);//E:MeV,L:m;e,mu,tau
TComplex Mee_2(double E,double L,int i, int j, int k,int l);//E:MeV,L:m
TComplex See(double E,double L);//E:MeV,L:m
double ImSeeMee(double E,double L,int i,int j);//E:MeV,L:m;e,mu,tau
double ReSeeMee_2(double E,double L,int i,int j,int k, int l);//E:MeV,L:m;e,mu,tau
double Psur(double E,double L);//E:MeV,L:m
double Table_ImSeeMee[3][6][3][3][4];//[Hall][Rct][e/mu/tau][e/mu/tau][E]
double Table_ReSeeMee_2[3][6][3][3][3][3][4];//[Hall][Rct][e/mu/tau][e/mu/tau][E]
double Table_Mee_2_2[3][6][3][3][3][3][4];//[Hall][Rct][e/mu/tau][e/mu/tau][E]
double Table_Mee_1_2[3][6][3][3][4];//[Hall][Rct][e/mu/tau][e/mu/tau][E]

double LatHall[3] = {22.598,22.606,22.612};//latitude of the three halls, degree, read from goole maps
	double Ave_Energy = 4.2;
	double Energy_Table[4]={5.0,4.0,3.0,2.0};
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
	double PositionHall[3][3] = {0.0};//position of the hall, center of the ADs,[HallNo][X/Y/Z]
	double PositionRctn[6][3] = {0.0};

	double PositionADn2[8][3] = {0.0};
	double PositionHalln2[3][3] = {0.0};//position of the hall, center of the ADs,[HallNo][X/Y/Z]
	double PositionRctn2[6][3] = {0.0};

	double RotAngl = 9.0*pi/180.0;//9 degrees of rotation
	double RotAngl2 = 8.0*pi/180.0;//9 degrees of rotation

	double A_chi[3][6] = {0.0};//angle chi, [HallNo][RctNo],in unit of radius
	double A_theta[3][6] = {0.0};//angle theta, [HallNo][RctNo]
	double A_phi[3][6] = {0.0};//angle phi, [HallNo][RctNo]

	double A_chi2[3][6] = {0.0};//angle chi, [HallNo][RctNo],in unit of radius
	double A_theta2[3][6] = {0.0};//angle theta, [HallNo][RctNo]
	double A_phi2[3][6] = {0.0};//angle phi, [HallNo][RctNo]

	double Nx[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Ny[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Nz[3][6] = {0.0};//direction factor, [HallNo][RctNo]

	double Nx2[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Ny2[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Nz2[3][6] = {0.0};//direction factor, [HallNo][RctNo]

	double A_chi_NoRotate[3][6] = {0.0};//angle chi, [HallNo][RctNo],in unit of radius
	double A_theta_NoRotate[3][6] = {0.0};//angle theta, [HallNo][RctNo]
	double A_phi_NoRotate[3][6] = {0.0};//angle phi, [HallNo][RctNo]

	double Nx_NoRotate[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Ny_NoRotate[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Nz_NoRotate[3][6] = {0.0};//direction factor, [HallNo][RctNo]

	double up_limits[14] ;

	Double_t EveFrac_Hall[3][6][24]={0.0};
	Double_t EveFrac_Hall_Total[3][24] = {0.0};
	Double_t EveFrac_Hall_Ave[3][6]={0.0};
	Double_t EveFrac_Total[3] = {0.0};
	Double_t EveFrac[3][6];

	Double_t Baseline_Hall[3][6];//[Hall][Rct]
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds

void OscP()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
	const int NumOfBin = 17016;// (EndTime - StartTime)/WidthOfBin;//17016

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////fit preparation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<14;i++)
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

		PositionADn2[ADidx][0] = PositionAD[ADidx][0]*cos(RotAngl2)+PositionAD[ADidx][1]*sin(RotAngl2);//x'=xcos + ysin
		PositionADn2[ADidx][1] = -1.0*PositionAD[ADidx][0]*sin(RotAngl2)+PositionAD[ADidx][1]*cos(RotAngl2);//y'=-xsin + ycos
		PositionADn2[ADidx][2] = PositionAD[ADidx][2];
		//cout<<PositionADn[ADidx][0]<<"      "<<PositionADn[ADidx][1]<<"      "<<PositionADn[ADidx][2]<<endl;
	}

	for(int Rctidx = 0;Rctidx<6;Rctidx++)
	{
		PositionRctn[Rctidx][0] = PositionRct[Rctidx][0]*cos(RotAngl)+PositionRct[Rctidx][1]*sin(RotAngl);//x'=xcos + ysin
		PositionRctn[Rctidx][1] = -1*PositionRct[Rctidx][0]*sin(RotAngl)+PositionRct[Rctidx][1]*cos(RotAngl);//y'=-xsin + ycos
		PositionRctn[Rctidx][2] = PositionRct[Rctidx][2];

		PositionRctn2[Rctidx][0] = PositionRct[Rctidx][0]*cos(RotAngl2)+PositionRct[Rctidx][1]*sin(RotAngl2);//x'=xcos + ysin
		PositionRctn2[Rctidx][1] = -1*PositionRct[Rctidx][0]*sin(RotAngl2)+PositionRct[Rctidx][1]*cos(RotAngl2);//y'=-xsin + ycos
		PositionRctn2[Rctidx][2] = PositionRct[Rctidx][2];
		//cout<<PositionRctn[Rctidx][0]<<"      "<<PositionRctn[Rctidx][1]<<"      "<<PositionRctn[Rctidx][2]<<endl;
	}

	for(int i=0;i<3;i++)
	{
		PositionHalln[0][i] = 0.5*(PositionADn[0][i]+PositionADn[1][i]);
		PositionHalln[1][i] = 0.5*(PositionADn[2][i]+PositionADn[7][i]);
		PositionHalln[2][i] = 0.25*(PositionADn[3][i]+PositionADn[4][i]+PositionADn[5][i]+PositionADn[6][i]);

		PositionHalln2[0][i] = 0.5*(PositionADn2[0][i]+PositionADn2[1][i]);
		PositionHalln2[1][i] = 0.5*(PositionADn2[2][i]+PositionADn2[7][i]);
		PositionHalln2[2][i] = 0.25*(PositionADn2[3][i]+PositionADn2[4][i]+PositionADn2[5][i]+PositionADn2[6][i]);


		PositionHall[0][i] = 0.5*(PositionAD[0][i]+PositionAD[1][i]);
		PositionHall[1][i] = 0.5*(PositionAD[2][i]+PositionAD[7][i]);
		PositionHall[2][i] = 0.25*(PositionAD[3][i]+PositionAD[4][i]+PositionAD[5][i]+PositionAD[6][i]);
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

	for(int Hallidx = 0;Hallidx<3;Hallidx++)
	{
		for(int Rctidx = 0;Rctidx<6;Rctidx++)
		{
			double D_beam[3] = {0.0};//beam direction
			for(int i=0;i<3;i++)
			{
				D_beam[i] = PositionHalln2[Hallidx][i] -  PositionRctn2[Rctidx][i];
			}
			A_theta2[Hallidx][Rctidx] = acos(D_beam[2]/sqrt(pow(D_beam[0],2.0)+pow(D_beam[1],2.0)+pow(D_beam[2],2.0)));
			if(D_beam[0]<0)
			{
				A_phi2[Hallidx][Rctidx] = acos(D_beam[1]/sqrt(pow(D_beam[0],2.0)+pow(D_beam[1],2.0)));
			}
			else
			{
				A_phi2[Hallidx][Rctidx] = 2*pi - acos(D_beam[1]/sqrt(pow(D_beam[0],2.0)+pow(D_beam[1],2.0)));
			}
			A_chi2[Hallidx][Rctidx] = 0.5*pi - LatHall[Hallidx]*pi/180.0;
			Nx2[Hallidx][Rctidx] = cos(A_chi2[Hallidx][Rctidx])*sin(A_theta2[Hallidx][Rctidx])*cos(A_phi2[Hallidx][Rctidx]) + sin(A_chi2[Hallidx][Rctidx])*cos(A_theta2[Hallidx][Rctidx]);
			Ny2[Hallidx][Rctidx] = sin(A_theta2[Hallidx][Rctidx])*sin(A_phi2[Hallidx][Rctidx]);
			Nz2[Hallidx][Rctidx] = -1*sin(A_chi2[Hallidx][Rctidx])*sin(A_theta2[Hallidx][Rctidx])*cos(A_phi2[Hallidx][Rctidx]) + cos(A_chi2[Hallidx][Rctidx])*cos(A_theta2[Hallidx][Rctidx]);
			//fprintf(stderr,"%5d %5d %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f \n", Hallidx, Rctidx, A_theta[Hallidx][Rctidx]*180.0/pi, A_phi[Hallidx][Rctidx]*180.0/pi, A_chi[Hallidx][Rctidx]*180.0/pi, Nx[Hallidx][Rctidx], Ny[Hallidx][Rctidx], Nz[Hallidx][Rctidx]);
		}
	}
	
	for(int Hallidx = 0;Hallidx<3;Hallidx++)
	{
		for(int Rctidx = 0;Rctidx<6;Rctidx++)
		{
			double D_beam_NoRotate[3] = {0.0};//beam direction
			for(int i=0;i<3;i++)
			{
				D_beam_NoRotate[i] = PositionHall[Hallidx][i] -  PositionRct[Rctidx][i];
			}
			A_theta_NoRotate[Hallidx][Rctidx] = acos(D_beam_NoRotate[2]/sqrt(pow(D_beam_NoRotate[0],2.0)+pow(D_beam_NoRotate[1],2.0)+pow(D_beam_NoRotate[2],2.0)));
			if(D_beam_NoRotate[0]<0)
			{
				A_phi_NoRotate[Hallidx][Rctidx] = acos(D_beam_NoRotate[1]/sqrt(pow(D_beam_NoRotate[0],2.0)+pow(D_beam_NoRotate[1],2.0)));
			}
			else
			{
				A_phi_NoRotate[Hallidx][Rctidx] = 2*pi - acos(D_beam_NoRotate[1]/sqrt(pow(D_beam_NoRotate[0],2.0)+pow(D_beam_NoRotate[1],2.0)));
			}
			A_chi_NoRotate[Hallidx][Rctidx] = 0.5*pi - LatHall[Hallidx]*pi/180.0;
			Nx_NoRotate[Hallidx][Rctidx] = cos(A_chi_NoRotate[Hallidx][Rctidx])*sin(A_theta_NoRotate[Hallidx][Rctidx])*cos(A_phi_NoRotate[Hallidx][Rctidx]) + sin(A_chi_NoRotate[Hallidx][Rctidx])*cos(A_theta_NoRotate[Hallidx][Rctidx]);
			Ny_NoRotate[Hallidx][Rctidx] = sin(A_theta_NoRotate[Hallidx][Rctidx])*sin(A_phi_NoRotate[Hallidx][Rctidx]);
			Nz_NoRotate[Hallidx][Rctidx] = -1*sin(A_chi_NoRotate[Hallidx][Rctidx])*sin(A_theta_NoRotate[Hallidx][Rctidx])*cos(A_phi_NoRotate[Hallidx][Rctidx]) + cos(A_chi_NoRotate[Hallidx][Rctidx])*cos(A_theta_NoRotate[Hallidx][Rctidx]);
			//fprintf(stderr,"%5d %5d %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f \n", Hallidx, Rctidx, A_theta_NoRotate[Hallidx][Rctidx]*180.0/pi, A_phi_NoRotate[Hallidx][Rctidx]*180.0/pi, A_chi_NoRotate[Hallidx][Rctidx]*180.0/pi, Nx_NoRotate[Hallidx][Rctidx], Ny_NoRotate[Hallidx][Rctidx], Nz_NoRotate[Hallidx][Rctidx]);
		}
	}

	const char* RctName[6] = {"D1","D2","L1","L2","L3","L4"};
	for(int Hallidx=0;Hallidx<3;Hallidx++)
	{
		for(int Rctidx = 0;Rctidx<6;Rctidx++)
		{
			fprintf(stderr,"EH%1d & %2s & %8.3f & %8.3f & %8.3f & %8.3f & %8.3f & %8.3f & %8.3f & %8.3f & %8.3f \\\\ \n",
				Hallidx+1, RctName[Rctidx],
				Nx[Hallidx][Rctidx], Nx2[Hallidx][Rctidx], (Nx2[Hallidx][Rctidx]-Nx[Hallidx][Rctidx]),///Nx[Hallidx][Rctidx],
				Ny[Hallidx][Rctidx], Ny2[Hallidx][Rctidx], (Ny2[Hallidx][Rctidx]-Ny[Hallidx][Rctidx]),///Ny[Hallidx][Rctidx],
				Nz[Hallidx][Rctidx], Nz2[Hallidx][Rctidx], (Nz2[Hallidx][Rctidx]-Nz[Hallidx][Rctidx]));///Nz[Hallidx][Rctidx]);
		}
	}

	cout<<sqrt(pow(PositionRct[1][0]-PositionRct[3][0],2.0)+pow(PositionRct[1][1]-PositionRct[3][1],2.0)+pow(PositionRct[1][2]-PositionRct[3][2],2.0))<<endl;
	
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int Rct = 0;Rct<6;Rct++)
		{
			Baseline_Hall[Hidx][Rct] = sqrt(pow(PositionHalln[Hidx][0]-PositionRctn[Rct][0],2.0)+pow(PositionHalln[Hidx][1]-PositionRctn[Rct][1],2.0)+pow(PositionHalln[Hidx][2]-PositionRctn[Rct][2],2.0));
		}
	}
	//typical values of See Mee
	cout<<"Hall  Rct         See(0)                    Mee(1)                   Mee(2)"<<endl;
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		
		for(int Rct = 0;Rct<6;Rct++)
		{
			fprintf(stderr,"%2d   &   %2d   &   %6.4f + i %6.4f    &   %6.4f + i %6.4f   &   %6.4f + i %6.4f \n",Hidx,Rct, 
				See(Ave_Energy,Baseline_Hall[Hidx][Rct]).Re(), See(Ave_Energy,Baseline_Hall[Hidx][Rct]).Im(),
				Mee(Ave_Energy,Baseline_Hall[Hidx][Rct],0,0).Re(), Mee(Ave_Energy,Baseline_Hall[Hidx][Rct],0,0).Im(),
				Mee_2(Ave_Energy,Baseline_Hall[Hidx][Rct],0,0,0,0).Re(), Mee_2(Ave_Energy,Baseline_Hall[Hidx][Rct],0,0,0,0).Im());
		}
	}
	
	fprintf(stderr,"ImSee0Mee1 ee uu tt eu et ut:\n");
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int Rct = 0;Rct<6;Rct++)
		{
			cout<<Eidx<<"   "<<Hidx<<"   "<<Rct<<endl;
			for(int c=0;c<3;c++){
		for(int d=0;d<3;d++){
			for(int e=0;e<3;e++){
				for(int f=0;f<3;f++){
					Table_Mee_2_2[Hidx][Rct][c][d][e][f][Eidx] = pow(Mee_2(Energy_Table[Eidx],Baseline_Hall[Hidx][Rct],c,d,e,f).Rho(),2.0);
					Table_ReSeeMee_2[Hidx][Rct][c][d][e][f][Eidx] = ReSeeMee_2(Energy_Table[Eidx],Baseline_Hall[Hidx][Rct],c,d,e,f);
				}}}}

	for(int c=0;c<3;c++){
		for(int d=0;d<3;d++){
					Table_Mee_1_2[Hidx][Rct][c][d][Eidx] = pow(Mee(Energy_Table[Eidx],Baseline_Hall[Hidx][Rct],c,d).Rho(),2.0);
				}}

			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
			Table_ImSeeMee[Hidx][Rct][i][j][Eidx] = ImSeeMee(Energy_Table[Eidx],Baseline_Hall[Hidx][Rct],i,j);
				}
			}
		}
	}
	}

	cout<<"calculation finished..."<<endl;

	/*
	cout<<"SEE MEE TABLE..........................."<<endl;
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int Rct = 0;Rct<6;Rct++)
		{
			fprintf(stderr,"&  %9.4f &  %7.4f &  %7.4f & %7.4f & %7.4f  & %7.4f & %7.4f &  %7.4f  \\\\ \\hline \n",
				Baseline_Hall[Hidx][Rct],pow(See(Ave_Energy,Baseline_Hall[Hidx][Rct]).Rho(),2.0),
				Table_ImSeeMee[Hidx][Rct][0][0],Table_ImSeeMee[Hidx][Rct][1][1],Table_ImSeeMee[Hidx][Rct][2][2],
				Table_ImSeeMee[Hidx][Rct][0][1],Table_ImSeeMee[Hidx][Rct][0][2],Table_ImSeeMee[Hidx][Rct][1][2]);
		}

	}
	*/

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//EH1
	HallID=0;
	const char * EH1_Prob_Name_P1[4]={"EH1_Prob_P1_5MeV","EH1_Prob_P1_4MeV","EH1_Prob_P1_3MeV","EH1_Prob_P1_2MeV"};
	TF1 *f_EH1_Prob_P1[4];
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	f_EH1_Prob_P1[Eidx]= new TF1(EH1_Prob_Name_P1[Eidx],func_Prob,0,86165.0,15);
	for(int j=0;j<=13;j++)
	{
		f_EH1_Prob_P1[Eidx]->SetParameter(j,up_limits[j]);
	}
	f_EH1_Prob_P1[Eidx]->SetParameter(14,double(Eidx));
	}

	TGraph *gr_EH1_Prob_P1[4];
	for(int i=0;i<4;i++)
	{
		gr_EH1_Prob_P1[i] = new TGraph(f_EH1_Prob_P1[i]);
		gr_EH1_Prob_P1[i]->SetLineColor(i/2+2);
		gr_EH1_Prob_P1[i]->SetLineStyle(i%2+1);
	}

	TCanvas *C_EH1_P1 = new TCanvas("EH1_P1","EH1_P1",200,10,800,600);

	TMultiGraph *mg_EH1_Prob_P1 = new TMultiGraph();

	for(int i=0;i<4;i++)
	{
		mg_EH1_Prob_P1->Add(gr_EH1_Prob_P1[i]);
	}

	mg_EH1_Prob_P1->Draw("AL");
	mg_EH1_Prob_P1->GetXaxis()->SetTitle("sidereal time(s)");
    mg_EH1_Prob_P1->GetYaxis()->SetTitle("P(1)");
	mg_EH1_Prob_P1->GetYaxis()->SetTitleOffset(1.3);
	mg_EH1_Prob_P1->GetYaxis()->SetLabelSize(0.042);

	TLegend* leg_EH1_Prob_P1 = new TLegend(0.50, 0.5, 0.80, 0.9);
    leg_EH1_Prob_P1->AddEntry(gr_EH1_Prob_P1[0],"5MeV","l");
	leg_EH1_Prob_P1->AddEntry(gr_EH1_Prob_P1[1],"4MeV","l");
	leg_EH1_Prob_P1->AddEntry(gr_EH1_Prob_P1[2],"3MeV","l");
	leg_EH1_Prob_P1->AddEntry(gr_EH1_Prob_P1[3],"2MeV","l");
	leg_EH1_Prob_P1->SetFillStyle(0);
	leg_EH1_Prob_P1->SetBorderSize(0);
	leg_EH1_Prob_P1->Draw();
	gPad->Modified();

   C_EH1_P1->SaveAs("OscP/P1_EH1.gif");
   C_EH1_P1->SaveAs("OscP/P1_EH1.eps");
    C_EH1_P1->SaveAs("OscP/P1_EH1.pdf");

	const char * EH1_Prob_Name_P2_1[4]={"EH1_Prob_P2_1_5MeV","EH1_Prob_P2_1_4MeV","EH1_Prob_P2_1_3MeV","EH1_Prob_P2_1_2MeV"};
	TF1 *f_EH1_Prob_P2_1[4];
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	f_EH1_Prob_P2_1[Eidx]= new TF1(EH1_Prob_Name_P2_1[Eidx],func_Prob2_1,0,86165.0,15);
	for(int j=0;j<=13;j++)
	{
		f_EH1_Prob_P2_1[Eidx]->SetParameter(j,up_limits[j]);
	}
	f_EH1_Prob_P2_1[Eidx]->SetParameter(14,double(Eidx));
	}

	TGraph *gr_EH1_Prob_P2_1[4];
	for(int i=0;i<4;i++)
	{
		gr_EH1_Prob_P2_1[i] = new TGraph(f_EH1_Prob_P2_1[i]);
		gr_EH1_Prob_P2_1[i]->SetLineColor(i/2+2);
		gr_EH1_Prob_P2_1[i]->SetLineStyle(i%2+1);
	}

	TCanvas *C_EH1_P2_1 = new TCanvas("EH1_P2_1","EH1_P2_1",200,10,800,600);

	TMultiGraph *mg_EH1_Prob_P2_1 = new TMultiGraph();

	for(int i=0;i<4;i++)
	{
		mg_EH1_Prob_P2_1->Add(gr_EH1_Prob_P2_1[i]);
	}

	mg_EH1_Prob_P2_1->Draw("AL");
	mg_EH1_Prob_P2_1->GetXaxis()->SetTitle("sidereal time(s)");
    mg_EH1_Prob_P2_1->GetYaxis()->SetTitle("P(2): 2Re(See(0)*See(2))");
	mg_EH1_Prob_P2_1->GetYaxis()->SetTitleOffset(1.3);
	mg_EH1_Prob_P2_1->GetYaxis()->SetLabelSize(0.042);

	TLegend* leg_EH1_Prob_P2_1 = new TLegend(0.50, 0.5, 0.80, 0.9);
    leg_EH1_Prob_P2_1->AddEntry(gr_EH1_Prob_P2_1[0],"5MeV","l");
	leg_EH1_Prob_P2_1->AddEntry(gr_EH1_Prob_P2_1[1],"4MeV","l");
	leg_EH1_Prob_P2_1->AddEntry(gr_EH1_Prob_P2_1[2],"3MeV","l");
	leg_EH1_Prob_P2_1->AddEntry(gr_EH1_Prob_P2_1[3],"2MeV","l");
	leg_EH1_Prob_P2_1->SetFillStyle(0);
	leg_EH1_Prob_P2_1->SetBorderSize(0);
	leg_EH1_Prob_P2_1->Draw();
	gPad->Modified();

   C_EH1_P2_1->SaveAs("OscP/P2_1_EH1.gif");
   C_EH1_P2_1->SaveAs("OscP/P2_1_EH1.eps");
    C_EH1_P2_1->SaveAs("OscP/P2_1_EH1.pdf");

	const char * EH1_Prob_Name_P2_2[4]={"EH1_Prob_P2_2_5MeV","EH1_Prob_P2_2_4MeV","EH1_Prob_P2_2_3MeV","EH1_Prob_P2_2_2MeV"};
	TF1 *f_EH1_Prob_P2_2[4];
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	f_EH1_Prob_P2_2[Eidx]= new TF1(EH1_Prob_Name_P2_2[Eidx],func_Prob2_2,0,86165.0,15);
	for(int j=0;j<=13;j++)
	{
		f_EH1_Prob_P2_2[Eidx]->SetParameter(j,up_limits[j]);
	}
	f_EH1_Prob_P2_2[Eidx]->SetParameter(14,double(Eidx));
	}

	TGraph *gr_EH1_Prob_P2_2[4];
	for(int i=0;i<4;i++)
	{
		gr_EH1_Prob_P2_2[i] = new TGraph(f_EH1_Prob_P2_2[i]);
		gr_EH1_Prob_P2_2[i]->SetLineColor(i/2+2);
		gr_EH1_Prob_P2_2[i]->SetLineStyle(i%2+1);
	}

	TCanvas *C_EH1_P2_2 = new TCanvas("EH1_P2_2","EH1_P2_2",200,10,800,600);

	TMultiGraph *mg_EH1_Prob_P2_2 = new TMultiGraph();

	for(int i=0;i<4;i++)
	{
		mg_EH1_Prob_P2_2->Add(gr_EH1_Prob_P2_2[i]);
	}

	mg_EH1_Prob_P2_2->Draw("AL");
	mg_EH1_Prob_P2_2->GetXaxis()->SetTitle("sidereal time(s)");
    mg_EH1_Prob_P2_2->GetYaxis()->SetTitle("P(2): |See(1)|^2");
	mg_EH1_Prob_P2_2->GetYaxis()->SetTitleOffset(1.3);
	mg_EH1_Prob_P2_2->GetYaxis()->SetLabelSize(0.042);

	TLegend* leg_EH1_Prob_P2_2 = new TLegend(0.50, 0.5, 0.80, 0.9);
    leg_EH1_Prob_P2_2->AddEntry(gr_EH1_Prob_P2_2[0],"5MeV","l");
	leg_EH1_Prob_P2_2->AddEntry(gr_EH1_Prob_P2_2[1],"4MeV","l");
	leg_EH1_Prob_P2_2->AddEntry(gr_EH1_Prob_P2_2[2],"3MeV","l");
	leg_EH1_Prob_P2_2->AddEntry(gr_EH1_Prob_P2_2[3],"2MeV","l");
	leg_EH1_Prob_P2_2->SetFillStyle(0);
	leg_EH1_Prob_P2_2->SetBorderSize(0);
	leg_EH1_Prob_P2_2->Draw();
	gPad->Modified();

   C_EH1_P2_2->SaveAs("OscP/P2_2_EH1.gif");
   C_EH1_P2_2->SaveAs("OscP/P2_2_EH1.eps");
    C_EH1_P2_2->SaveAs("OscP/P2_2_EH1.pdf");

	//EH2
	HallID=1;
	const char * EH2_Prob_Name_P1[4]={"EH2_Prob_P1_5MeV","EH2_Prob_P1_4MeV","EH2_Prob_P1_3MeV","EH2_Prob_P1_2MeV"};
	TF1 *f_EH2_Prob_P1[4];
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	f_EH2_Prob_P1[Eidx]= new TF1(EH2_Prob_Name_P1[Eidx],func_Prob,0,86165.0,15);
	for(int j=0;j<=13;j++)
	{
		f_EH2_Prob_P1[Eidx]->SetParameter(j,up_limits[j]);
	}
	f_EH2_Prob_P1[Eidx]->SetParameter(14,double(Eidx));
	}

	TGraph *gr_EH2_Prob_P1[4];
	for(int i=0;i<4;i++)
	{
		gr_EH2_Prob_P1[i] = new TGraph(f_EH2_Prob_P1[i]);
		gr_EH2_Prob_P1[i]->SetLineColor(i/2+2);
		gr_EH2_Prob_P1[i]->SetLineStyle(i%2+1);
	}

	TCanvas *C_EH2_P1 = new TCanvas("EH2_P1","EH2_P1",200,10,800,600);

	TMultiGraph *mg_EH2_Prob_P1 = new TMultiGraph();

	for(int i=0;i<4;i++)
	{
		mg_EH2_Prob_P1->Add(gr_EH2_Prob_P1[i]);
	}

	mg_EH2_Prob_P1->Draw("AL");
	mg_EH2_Prob_P1->GetXaxis()->SetTitle("sidereal time(s)");
    mg_EH2_Prob_P1->GetYaxis()->SetTitle("P(1)");
	mg_EH2_Prob_P1->GetYaxis()->SetTitleOffset(1.3);
	mg_EH2_Prob_P1->GetYaxis()->SetLabelSize(0.042);

	TLegend* leg_EH2_Prob_P1 = new TLegend(0.50, 0.5, 0.80, 0.9);
    leg_EH2_Prob_P1->AddEntry(gr_EH2_Prob_P1[0],"5MeV","l");
	leg_EH2_Prob_P1->AddEntry(gr_EH2_Prob_P1[1],"4MeV","l");
	leg_EH2_Prob_P1->AddEntry(gr_EH2_Prob_P1[2],"3MeV","l");
	leg_EH2_Prob_P1->AddEntry(gr_EH2_Prob_P1[3],"2MeV","l");
	leg_EH2_Prob_P1->SetFillStyle(0);
	leg_EH2_Prob_P1->SetBorderSize(0);
	leg_EH2_Prob_P1->Draw();
	gPad->Modified();

   C_EH2_P1->SaveAs("OscP/P1_EH2.gif");
   C_EH2_P1->SaveAs("OscP/P1_EH2.eps");
    C_EH2_P1->SaveAs("OscP/P1_EH2.pdf");

	const char * EH2_Prob_Name_P2_1[4]={"EH2_Prob_P2_1_5MeV","EH2_Prob_P2_1_4MeV","EH2_Prob_P2_1_3MeV","EH2_Prob_P2_1_2MeV"};
	TF1 *f_EH2_Prob_P2_1[4];
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	f_EH2_Prob_P2_1[Eidx]= new TF1(EH2_Prob_Name_P2_1[Eidx],func_Prob2_1,0,86165.0,15);
	for(int j=0;j<=13;j++)
	{
		f_EH2_Prob_P2_1[Eidx]->SetParameter(j,up_limits[j]);
	}
	f_EH2_Prob_P2_1[Eidx]->SetParameter(14,double(Eidx));
	}

	TGraph *gr_EH2_Prob_P2_1[4];
	for(int i=0;i<4;i++)
	{
		gr_EH2_Prob_P2_1[i] = new TGraph(f_EH2_Prob_P2_1[i]);
		gr_EH2_Prob_P2_1[i]->SetLineColor(i/2+2);
		gr_EH2_Prob_P2_1[i]->SetLineStyle(i%2+1);
	}

	TCanvas *C_EH2_P2_1 = new TCanvas("EH2_P2_1","EH2_P2_1",200,10,800,600);

	TMultiGraph *mg_EH2_Prob_P2_1 = new TMultiGraph();

	for(int i=0;i<4;i++)
	{
		mg_EH2_Prob_P2_1->Add(gr_EH2_Prob_P2_1[i]);
	}

	mg_EH2_Prob_P2_1->Draw("AL");
	mg_EH2_Prob_P2_1->GetXaxis()->SetTitle("sidereal time(s)");
    mg_EH2_Prob_P2_1->GetYaxis()->SetTitle("P(2): 2Re(See(0)*See(2))");
	mg_EH2_Prob_P2_1->GetYaxis()->SetTitleOffset(1.3);
	mg_EH2_Prob_P2_1->GetYaxis()->SetLabelSize(0.042);

	TLegend* leg_EH2_Prob_P2_1 = new TLegend(0.50, 0.5, 0.80, 0.9);
    leg_EH2_Prob_P2_1->AddEntry(gr_EH2_Prob_P2_1[0],"5MeV","l");
	leg_EH2_Prob_P2_1->AddEntry(gr_EH2_Prob_P2_1[1],"4MeV","l");
	leg_EH2_Prob_P2_1->AddEntry(gr_EH2_Prob_P2_1[2],"3MeV","l");
	leg_EH2_Prob_P2_1->AddEntry(gr_EH2_Prob_P2_1[3],"2MeV","l");
	leg_EH2_Prob_P2_1->SetFillStyle(0);
	leg_EH2_Prob_P2_1->SetBorderSize(0);
	leg_EH2_Prob_P2_1->Draw();
	gPad->Modified();

   C_EH2_P2_1->SaveAs("OscP/P2_1_EH2.gif");
   C_EH2_P2_1->SaveAs("OscP/P2_1_EH2.eps");
    C_EH2_P2_1->SaveAs("OscP/P2_1_EH2.pdf");

	const char * EH2_Prob_Name_P2_2[4]={"EH2_Prob_P2_2_5MeV","EH2_Prob_P2_2_4MeV","EH2_Prob_P2_2_3MeV","EH2_Prob_P2_2_2MeV"};
	TF1 *f_EH2_Prob_P2_2[4];
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	f_EH2_Prob_P2_2[Eidx]= new TF1(EH2_Prob_Name_P2_2[Eidx],func_Prob2_2,0,86165.0,15);
	for(int j=0;j<=13;j++)
	{
		f_EH2_Prob_P2_2[Eidx]->SetParameter(j,up_limits[j]);
	}
	f_EH2_Prob_P2_2[Eidx]->SetParameter(14,double(Eidx));
	}

	TGraph *gr_EH2_Prob_P2_2[4];
	for(int i=0;i<4;i++)
	{
		gr_EH2_Prob_P2_2[i] = new TGraph(f_EH2_Prob_P2_2[i]);
		gr_EH2_Prob_P2_2[i]->SetLineColor(i/2+2);
		gr_EH2_Prob_P2_2[i]->SetLineStyle(i%2+1);
	}

	TCanvas *C_EH2_P2_2 = new TCanvas("EH2_P2_2","EH2_P2_2",200,10,800,600);

	TMultiGraph *mg_EH2_Prob_P2_2 = new TMultiGraph();

	for(int i=0;i<4;i++)
	{
		mg_EH2_Prob_P2_2->Add(gr_EH2_Prob_P2_2[i]);
	}

	mg_EH2_Prob_P2_2->Draw("AL");
	mg_EH2_Prob_P2_2->GetXaxis()->SetTitle("sidereal time(s)");
    mg_EH2_Prob_P2_2->GetYaxis()->SetTitle("P(2): |See(1)|^2");
	mg_EH2_Prob_P2_2->GetYaxis()->SetTitleOffset(1.3);
	mg_EH2_Prob_P2_2->GetYaxis()->SetLabelSize(0.042);

	TLegend* leg_EH2_Prob_P2_2 = new TLegend(0.50, 0.5, 0.80, 0.9);
    leg_EH2_Prob_P2_2->AddEntry(gr_EH2_Prob_P2_2[0],"5MeV","l");
	leg_EH2_Prob_P2_2->AddEntry(gr_EH2_Prob_P2_2[1],"4MeV","l");
	leg_EH2_Prob_P2_2->AddEntry(gr_EH2_Prob_P2_2[2],"3MeV","l");
	leg_EH2_Prob_P2_2->AddEntry(gr_EH2_Prob_P2_2[3],"2MeV","l");
	leg_EH2_Prob_P2_2->SetFillStyle(0);
	leg_EH2_Prob_P2_2->SetBorderSize(0);
	leg_EH2_Prob_P2_2->Draw();
	gPad->Modified();

   C_EH2_P2_2->SaveAs("OscP/P2_2_EH2.gif");
   C_EH2_P2_2->SaveAs("OscP/P2_2_EH2.eps");
    C_EH2_P2_2->SaveAs("OscP/P2_2_EH2.pdf");

	//EH3
	HallID=2;
	const char * EH3_Prob_Name_P1[4]={"EH3_Prob_P1_5MeV","EH3_Prob_P1_4MeV","EH3_Prob_P1_3MeV","EH3_Prob_P1_2MeV"};
	TF1 *f_EH3_Prob_P1[4];
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	f_EH3_Prob_P1[Eidx]= new TF1(EH3_Prob_Name_P1[Eidx],func_Prob,0,86165.0,15);
	for(int j=0;j<=13;j++)
	{
		f_EH3_Prob_P1[Eidx]->SetParameter(j,up_limits[j]);
	}
	f_EH3_Prob_P1[Eidx]->SetParameter(14,double(Eidx));
	}

	TGraph *gr_EH3_Prob_P1[4];
	for(int i=0;i<4;i++)
	{
		gr_EH3_Prob_P1[i] = new TGraph(f_EH3_Prob_P1[i]);
		gr_EH3_Prob_P1[i]->SetLineColor(i/2+2);
		gr_EH3_Prob_P1[i]->SetLineStyle(i%2+1);
	}

	TCanvas *C_EH3_P1 = new TCanvas("EH3_P1","EH3_P1",200,10,800,600);

	TMultiGraph *mg_EH3_Prob_P1 = new TMultiGraph();

	for(int i=0;i<4;i++)
	{
		mg_EH3_Prob_P1->Add(gr_EH3_Prob_P1[i]);
	}

	mg_EH3_Prob_P1->Draw("AL");
	mg_EH3_Prob_P1->GetXaxis()->SetTitle("sidereal time(s)");
    mg_EH3_Prob_P1->GetYaxis()->SetTitle("P(1)");
	mg_EH3_Prob_P1->GetYaxis()->SetTitleOffset(1.3);
	mg_EH3_Prob_P1->GetYaxis()->SetLabelSize(0.042);

	TLegend* leg_EH3_Prob_P1 = new TLegend(0.50, 0.5, 0.80, 0.9);
    leg_EH3_Prob_P1->AddEntry(gr_EH3_Prob_P1[0],"5MeV","l");
	leg_EH3_Prob_P1->AddEntry(gr_EH3_Prob_P1[1],"4MeV","l");
	leg_EH3_Prob_P1->AddEntry(gr_EH3_Prob_P1[2],"3MeV","l");
	leg_EH3_Prob_P1->AddEntry(gr_EH3_Prob_P1[3],"2MeV","l");
	leg_EH3_Prob_P1->SetFillStyle(0);
	leg_EH3_Prob_P1->SetBorderSize(0);
	leg_EH3_Prob_P1->Draw();
	gPad->Modified();

   C_EH3_P1->SaveAs("OscP/P1_EH3.gif");
   C_EH3_P1->SaveAs("OscP/P1_EH3.eps");
    C_EH3_P1->SaveAs("OscP/P1_EH3.pdf");

	const char * EH3_Prob_Name_P2_1[4]={"EH3_Prob_P2_1_5MeV","EH3_Prob_P2_1_4MeV","EH3_Prob_P2_1_3MeV","EH3_Prob_P2_1_2MeV"};
	TF1 *f_EH3_Prob_P2_1[4];
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	f_EH3_Prob_P2_1[Eidx]= new TF1(EH3_Prob_Name_P2_1[Eidx],func_Prob2_1,0,86165.0,15);
	for(int j=0;j<=13;j++)
	{
		f_EH3_Prob_P2_1[Eidx]->SetParameter(j,up_limits[j]);
	}
	f_EH3_Prob_P2_1[Eidx]->SetParameter(14,double(Eidx));
	}

	TGraph *gr_EH3_Prob_P2_1[4];
	for(int i=0;i<4;i++)
	{
		gr_EH3_Prob_P2_1[i] = new TGraph(f_EH3_Prob_P2_1[i]);
		gr_EH3_Prob_P2_1[i]->SetLineColor(i/2+2);
		gr_EH3_Prob_P2_1[i]->SetLineStyle(i%2+1);
	}

	TCanvas *C_EH3_P2_1 = new TCanvas("EH3_P2_1","EH3_P2_1",200,10,800,600);

	TMultiGraph *mg_EH3_Prob_P2_1 = new TMultiGraph();

	for(int i=0;i<4;i++)
	{
		mg_EH3_Prob_P2_1->Add(gr_EH3_Prob_P2_1[i]);
	}

	mg_EH3_Prob_P2_1->Draw("AL");
	mg_EH3_Prob_P2_1->GetXaxis()->SetTitle("sidereal time(s)");
    mg_EH3_Prob_P2_1->GetYaxis()->SetTitle("P(2): 2Re(See(0)*See(2))");
	mg_EH3_Prob_P2_1->GetYaxis()->SetTitleOffset(1.3);
	mg_EH3_Prob_P2_1->GetYaxis()->SetLabelSize(0.042);

	TLegend* leg_EH3_Prob_P2_1 = new TLegend(0.50, 0.5, 0.80, 0.9);
    leg_EH3_Prob_P2_1->AddEntry(gr_EH3_Prob_P2_1[0],"5MeV","l");
	leg_EH3_Prob_P2_1->AddEntry(gr_EH3_Prob_P2_1[1],"4MeV","l");
	leg_EH3_Prob_P2_1->AddEntry(gr_EH3_Prob_P2_1[2],"3MeV","l");
	leg_EH3_Prob_P2_1->AddEntry(gr_EH3_Prob_P2_1[3],"2MeV","l");
	leg_EH3_Prob_P2_1->SetFillStyle(0);
	leg_EH3_Prob_P2_1->SetBorderSize(0);
	leg_EH3_Prob_P2_1->Draw();
	gPad->Modified();

   C_EH3_P2_1->SaveAs("OscP/P2_1_EH3.gif");
   C_EH3_P2_1->SaveAs("OscP/P2_1_EH3.eps");
    C_EH3_P2_1->SaveAs("OscP/P2_1_EH3.pdf");

	const char * EH3_Prob_Name_P2_2[4]={"EH3_Prob_P2_2_5MeV","EH3_Prob_P2_2_4MeV","EH3_Prob_P2_2_3MeV","EH3_Prob_P2_2_2MeV"};
	TF1 *f_EH3_Prob_P2_2[4];
	for(int Eidx=0;Eidx<4;Eidx++)
	{
	f_EH3_Prob_P2_2[Eidx]= new TF1(EH3_Prob_Name_P2_2[Eidx],func_Prob2_2,0,86165.0,15);
	for(int j=0;j<=13;j++)
	{
		f_EH3_Prob_P2_2[Eidx]->SetParameter(j,up_limits[j]);
	}
	f_EH3_Prob_P2_2[Eidx]->SetParameter(14,double(Eidx));
	}

	TGraph *gr_EH3_Prob_P2_2[4];
	for(int i=0;i<4;i++)
	{
		gr_EH3_Prob_P2_2[i] = new TGraph(f_EH3_Prob_P2_2[i]);
		gr_EH3_Prob_P2_2[i]->SetLineColor(i/2+2);
		gr_EH3_Prob_P2_2[i]->SetLineStyle(i%2+1);
	}

	TCanvas *C_EH3_P2_2 = new TCanvas("EH3_P2_2","EH3_P2_2",200,10,800,600);

	TMultiGraph *mg_EH3_Prob_P2_2 = new TMultiGraph();

	for(int i=0;i<4;i++)
	{
		mg_EH3_Prob_P2_2->Add(gr_EH3_Prob_P2_2[i]);
	}

	mg_EH3_Prob_P2_2->Draw("AL");
	mg_EH3_Prob_P2_2->GetXaxis()->SetTitle("sidereal time(s)");
    mg_EH3_Prob_P2_2->GetYaxis()->SetTitle("P(2): |See(1)|^2");
	mg_EH3_Prob_P2_2->GetYaxis()->SetTitleOffset(1.3);
	mg_EH3_Prob_P2_2->GetYaxis()->SetLabelSize(0.042);

	TLegend* leg_EH3_Prob_P2_2 = new TLegend(0.50, 0.5, 0.80, 0.9);
    leg_EH3_Prob_P2_2->AddEntry(gr_EH3_Prob_P2_2[0],"5MeV","l");
	leg_EH3_Prob_P2_2->AddEntry(gr_EH3_Prob_P2_2[1],"4MeV","l");
	leg_EH3_Prob_P2_2->AddEntry(gr_EH3_Prob_P2_2[2],"3MeV","l");
	leg_EH3_Prob_P2_2->AddEntry(gr_EH3_Prob_P2_2[3],"2MeV","l");
	leg_EH3_Prob_P2_2->SetFillStyle(0);
	leg_EH3_Prob_P2_2->SetBorderSize(0);
	leg_EH3_Prob_P2_2->Draw();
	gPad->Modified();

   C_EH3_P2_2->SaveAs("OscP/P2_2_EH3.gif");
   C_EH3_P2_2->SaveAs("OscP/P2_2_EH3.eps");
    C_EH3_P2_2->SaveAs("OscP/P2_2_EH3.pdf");
	
}

Double_t func_Prob_combine_const(Double_t *x, Double_t *par)
{
	return par[0];
}

Double_t func_Prob(Double_t *x, Double_t *par)
{
	//par: 0	1	 2	  3	   4	5	 6	   7	8	  9    10    11    12    13
    //par: aX,  aY, cTX, cTY, cXX, cXY, cXZ,  cYY, cYZ,,  aT,  aZ,  cTT,  cTZ,  cZZ  

	Double_t wP = 2.0*pi/86164.0;//omega plus, sidereal frequency
	Double_t TotalP = 0.0;
	int Eidx = int(par[14]);
	Double_t TotalEveFrac = 0.0;

	Double_t frac[6];

	for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall_Ave[HallID][i];
		}
	for(int i=0;i<6;i++)
	{
		TotalEveFrac += frac[i];
	}

	Double_t ImSM ;
	Double_t S2;
	Double_t Et = Energy_Table[Eidx];
	Double_t Lt,Nxt,Nyt,Nzt;
	for(int i=0;i<=5;i++)
	{
		Lt = Baseline_Hall[HallID][i];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];

		ImSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]][Eidx];
		S2 = pow(See(Et,Lt).Rho(),2.0);
	//par: 0	1	 2	  3	   4	5	 6	   7	8	  9    10    11    12    13
    //par: aX,  aY, cTX, cTY, cXX, cXY, cXZ,  cYY, cYZ,,  aT,  aZ,  cTT,  cTZ,  cZZ  

    Double_t C1  = par[9] - Nzt*par[10] + 0.001*Et*(-0.5*(3.0-Nzt*Nzt)*par[11] + 2.0*Nzt*par[12]+
		0.5*(1.0-3.0*Nzt*Nzt)*par[13]);
	Double_t As1 = Nyt*par[0] - Nxt*par[1] + 0.001*Et*(-2.0*Nyt*par[2] + 2.0*Nxt*par[3]+
		2.0*Nyt*Nzt*par[6] - 2.0*Nxt*Nzt*par[8]);
	Double_t Ac1 = -1.0*Nxt*par[0] - Nyt*par[1] + 0.001*Et*(2.0*Nxt*par[2] + 2.0*Nyt*par[3]-
		2.0*Nyt*Nzt*par[6] - 2.0*Nxt*Nzt*par[8]);
	Double_t Bs1 = 0.001*Et*(Nxt*Nyt*(par[4]-par[7])-(Nxt*Nxt-Nyt*Nyt)*par[5]);
	Double_t Bc1 = 0.001*Et*(-0.5*(Nxt*Nxt-Nyt*Nyt)*(par[4]-par[7])-2.0*Nxt*Nyt*par[5]);
	
	TotalP += (frac[i]/TotalEveFrac)*(ImSM*2.0*Lt*5.07e15*(C1 + As1*sin(wP*x[0]) + Ac1*cos(wP*x[0]) + Bs1*sin(2.0*wP*x[0])+ Bc1*cos(2.0*wP*x[0])));

	}

	return TotalP;
}


Double_t func_Prob2_2(Double_t *x, Double_t *par)//|See1|^2
{
	//par: 0	1	 2	  3	   4	5	 6	   7	8	  9    10    11    12    13
    //par: aX,  aY, cTX, cTY, cXX, cXY, cXZ,  cYY, cYZ,,  aT,  aZ,  cTT,  cTZ,  cZZ  

	Double_t wP = 2.0*pi/86164.0;//omega plus, sidereal frequency
	Double_t TotalP = 0.0;
	int Eidx = int(par[14]);
	Double_t TotalEveFrac = 0.0;

	Double_t frac[6];

	for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall_Ave[HallID][i];
		}
	for(int i=0;i<6;i++)
	{
		TotalEveFrac += frac[i];
	}

	Double_t ImSM ;
	Double_t S2;
	Double_t Et = Energy_Table[Eidx];
	Double_t Lt,Nxt,Nyt,Nzt;
	Double_t Mee_S2;
	for(int i=0;i<=5;i++)
	{
		Lt = Baseline_Hall[HallID][i];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];

		ImSM = Table_ImSeeMee[HallID][i][IndexCD[0]][IndexCD[1]][Eidx];
		Mee_S2 = Table_Mee_1_2[HallID][i][IndexCD[0]][IndexCD[1]][Eidx];
		S2 = pow(See(Et,Lt).Rho(),2.0);
	//par: 0	1	 2	  3	   4	5	 6	   7	8	  9    10    11    12    13
    //par: aX,  aY, cTX, cTY, cXX, cXY, cXZ,  cYY, cYZ,,  aT,  aZ,  cTT,  cTZ,  cZZ  

    Double_t C1  = par[9] - Nzt*par[10] + 0.001*Et*(-0.5*(3.0-Nzt*Nzt)*par[11] + 2.0*Nzt*par[12]+
		0.5*(1.0-3.0*Nzt*Nzt)*par[13]);
	Double_t As1 = Nyt*par[0] - Nxt*par[1] + 0.001*Et*(-2.0*Nyt*par[2] + 2.0*Nxt*par[3]+
		2.0*Nyt*Nzt*par[6] - 2.0*Nxt*Nzt*par[8]);
	Double_t Ac1 = -1.0*Nxt*par[0] - Nyt*par[1] + 0.001*Et*(2.0*Nxt*par[2] + 2.0*Nyt*par[3]-
		2.0*Nyt*Nzt*par[6] - 2.0*Nxt*Nzt*par[8]);
	Double_t Bs1 = 0.001*Et*(Nxt*Nyt*(par[4]-par[7])-(Nxt*Nxt-Nyt*Nyt)*par[5]);
	Double_t Bc1 = 0.001*Et*(-0.5*(Nxt*Nxt-Nyt*Nyt)*(par[4]-par[7])-2.0*Nxt*Nyt*par[5]);
	
	Double_t PC  = Mee_S2*(C1*C1+0.5*As1*As1+0.5*Ac1*Ac1+0.5*Bs1*Bs1+0.5*Bc1*Bc1);
	Double_t PBs = Mee_S2*As1*Ac1;
	Double_t PBc = 0.5*Mee_S2*(Ac1*Ac1-As1*As1);
	Double_t PFs = Mee_S2*Bs1*Bc1;
	Double_t PFc = 0.5*Mee_S2*(Bc1*Bc1-Bs1*Bs1);

	TotalP += (frac[i]/TotalEveFrac)*(Lt*5.07e15*Lt*5.07e15*(PC + PBs*sin(2.0*wP*x[0]) + PBc*cos(2.0*wP*x[0]) + PFs*sin(4.0*wP*x[0])+ PFc*cos(4.0*wP*x[0])));

	}

	return TotalP;
}


Double_t func_Prob2_1(Double_t *x, Double_t *par)//|See1|^2
{
	//par: 0	1	 2	  3	   4	5	 6	   7	8	  9    10    11    12    13
    //par: aX,  aY, cTX, cTY, cXX, cXY, cXZ,  cYY, cYZ,,  aT,  aZ,  cTT,  cTZ,  cZZ  

	Double_t wP = 2.0*pi/86164.0;//omega plus, sidereal frequency
	Double_t TotalP = 0.0;
	int Eidx = int(par[14]);
	Double_t TotalEveFrac = 0.0;

	Double_t frac[6];

	for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall_Ave[HallID][i];
		}
	for(int i=0;i<6;i++)
	{
		TotalEveFrac += frac[i];
	}

	Double_t ReSM ;
	Double_t S2;
	Double_t Et = Energy_Table[Eidx];
	Double_t Lt,Nxt,Nyt,Nzt;
	Double_t Mee_S2;
	for(int i=0;i<=5;i++)
	{
		Lt = Baseline_Hall[HallID][i];
		Nxt = Nx[HallID][i];
		Nyt = Ny[HallID][i];
		Nzt = Nz[HallID][i];

		ReSM = Table_ReSeeMee_2[HallID][i][IndexCD[0]][IndexCD[1]][IndexCD[2]][IndexCD[3]][Eidx];
		//Mee_S2 = Table_Mee_1_2[HallID][i][IndexCD[0]][IndexCD[1]];
		S2 = pow(See(Et,Lt).Rho(),2.0);
	//par: 0	1	 2	  3	   4	5	 6	   7	8	  9    10    11    12    13
    //par: aX,  aY, cTX, cTY, cXX, cXY, cXZ,  cYY, cYZ,,  aT,  aZ,  cTT,  cTZ,  cZZ  

    Double_t C1  = par[9] - Nzt*par[10] + 0.001*Et*(-0.5*(3.0-Nzt*Nzt)*par[11] + 2.0*Nzt*par[12]+
		0.5*(1.0-3.0*Nzt*Nzt)*par[13]);
	Double_t As1 = Nyt*par[0] - Nxt*par[1] + 0.001*Et*(-2.0*Nyt*par[2] + 2.0*Nxt*par[3]+
		2.0*Nyt*Nzt*par[6] - 2.0*Nxt*Nzt*par[8]);
	Double_t Ac1 = -1.0*Nxt*par[0] - Nyt*par[1] + 0.001*Et*(2.0*Nxt*par[2] + 2.0*Nyt*par[3]-
		2.0*Nyt*Nzt*par[6] - 2.0*Nxt*Nzt*par[8]);
	Double_t Bs1 = 0.001*Et*(Nxt*Nyt*(par[4]-par[7])-(Nxt*Nxt-Nyt*Nyt)*par[5]);
	Double_t Bc1 = 0.001*Et*(-0.5*(Nxt*Nxt-Nyt*Nyt)*(par[4]-par[7])-2.0*Nxt*Nyt*par[5]);
	
	Double_t PC  = -0.5*ReSM*(2.0*C1*C1+As1*As1+Ac1*Ac1+Bs1*Bs1+Bc1*Bc1);
	Double_t PBs = -0.5*ReSM*(As1*Ac1+Ac1*As1);
	Double_t PBc = -0.5*ReSM*(-1.0*As1*As1+Ac1*Ac1);
	Double_t PFs = -0.5*ReSM*(Bs1*Bc1+Bc1*Bs1);
	Double_t PFc = -0.5*ReSM*(-1.0*Bs1*Bs1+Bc1*Bc1);

	TotalP += (frac[i]/TotalEveFrac)*(Lt*5.07e15*Lt*5.07e15*(PC + PBs*sin(2.0*wP*x[0]) + PBc*cos(2.0*wP*x[0]) + PFs*sin(4.0*wP*x[0])+ PFc*cos(4.0*wP*x[0])));

	}

	return TotalP;
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

TComplex Tauabc(int a,int b,int c,double E,double L)//E:MeV,L:m
{
	double L2 = L*5.07e15;//GeV^-1
	double E2 = E*0.001;//GeV
	double EbL = Dm[b][0]*L2/(2.0*E2);
	double EaL = Dm[a][0]*L2/(2.0*E2);
	double EcL = Dm[c][0]*L2/(2.0*E2);
	double Dac = Dm[a][c]*L2/(2.0*E2);
	double Dcb = Dm[c][b]*L2/(2.0*E2);

	if(a==c)
	{
		if(b!=c)
		{
		TComplex CEcbL = TComplex(0.0,-1.0*Dcb);
		return (Tauab(a,c,E,L)-Tauab(a,b,E,L))/CEcbL;
		}
		else
		{
			TComplex tau = TComplex(cos(EbL),-sin(EbL));
			return tau;
		}
	}
	else
	{
		TComplex CEacL = TComplex(0.0,-1.0*Dac);
		return (Tauab(a,b,E,L)-Tauab(c,b,E,L))/CEacL;
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

TComplex Mee_2(double E,double L,int i, int j, int k,int l)//E:MeV,L:m
{
	TComplex  result = TComplex(0.0,0.0);
	for(int a=0;a<3;a++)
	{
		for(int b=0;b<3;b++)
		{
			for(int c=0;c<3;c++)
			{
			result += Tauabc(a,b,c,E,L)*U[0][a]*U[i][a]*U[j][c]*U[k][c]*U[l][b]*U[0][b];
			}
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
	//cout<<"See:   "<< CSee.Re()<<"   "<<CSee.Im()<<endl;
	//cout<<"Mee:   "<< CMee.Re()<<"   "<<CMee.Im()<<endl;
	return result.Im();
}

double ReSeeMee_2(double E,double L,int i, int j,int k, int l)//E:MeV,L:m
{
	TComplex CSee = See(E,L);
	TComplex CMee = Mee_2(E,L,i,j,k,l);
	TComplex result = (TComplex::Conjugate(CSee))*CMee;
	//cout<<"See:   "<< CSee.Re()<<"   "<<CSee.Im()<<endl;
	//cout<<"Mee:   "<< CMee.Re()<<"   "<<CMee.Im()<<endl;
	return result.Re();
}



double Psur(double E,double L)
{
	double L2 = L*5.07e15;//GeV^-1
	double E2 = E*0.001;//GeV
	//cout<<"sin2t132: "<<pow(sin(2.0*Th13),2.0)<<endl;
	//cout<<pow(sin(2.0*Th13),2.0)*pow(sin(1.267*Dm[2][0]*L2/E2),2.0)<<endl;
	return 1 - pow(sin(2.0*Th13),2.0)*pow(sin(0.25*Dm[2][0]*L2/E2),2.0) - pow(cos(Th13),4.0)*pow(sin(2.0*Th12),2.0)*pow(sin(0.25*Dm[1][0]*L2/E2),2.0);
}

