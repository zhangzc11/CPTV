#include <math.h>

const int HallID = 2;
const double pi = 3.141592653;


double AVEP[3] = {0.98,0.98,0.951455};

void Ratio_EH3_Compare()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
	const int NumOfBin = 17016;// (EndTime - StartTime)/WidthOfBin;//17016


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

	
	double RD_Power = 0.009*0.047;
	double RD_Eff = 0.00088;



	/////////////////////////////////////////////////////////
	/////////////////////////////////EH3////////////////////////////////////////////
	Double_t Mf[24]={0.0};//={0.0};
	Double_t RD_Mf[24]={0.0};//={0.0};
	
	Double_t Ma[24]={0.0};//={0.0};
	Double_t RD_Ma[24]={0.0};//={0.0};
	
	Double_t Mb[24]={0.0};//={0.0};
	Double_t RD_Mb[24]={0.0};//={0.0};

	Double_t NBarF[24]={0.0};//={0.0};
	Double_t RD_NBarF[24]={0.0};//={0.0};

	Double_t RD_Ma[24] = {0.0};
	Double_t RD_Mb[24] = {0.0};
	Double_t RD_Mf[24] = {0.0};

	Double_t Mf2[24]={0.0};//={0.0};
	Double_t RD_Mf2[24]={0.0};//={0.0};
	
	Double_t Ma2[24]={0.0};//={0.0};
	Double_t RD_Ma2[24]={0.0};//={0.0};
	
	Double_t Mb2[24]={0.0};//={0.0};
	Double_t RD_Mb2[24]={0.0};//={0.0};

	Double_t NBarF2[24]={0.0};//={0.0};
	Double_t RD_NBarF2[24]={0.0};//={0.0};

	Double_t RD_Ma2[24] = {0.0};
	Double_t RD_Mb2[24] = {0.0};
	Double_t RD_Mf2[24] = {0.0};


	Double_t R[24];//
	memset(R,0.0,sizeof(R));
	Double_t RD_R[24];//
	memset(RD_R,0.0,sizeof(RD_R));

	Double_t R2[24];//
	memset(R2,0.0,sizeof(R2));
	Double_t RD_R2[24];//
	memset(RD_R2,0.0,sizeof(RD_R2));

	Double_t R3[24];//
	memset(R3,0.0,sizeof(R3));
	Double_t RD_R3[24];//
	memset(RD_R3,0.0,sizeof(RD_R3));


	double TotalIBD_Before[8] = {0.0};
	double TotalIBD_After[8] ={0.0};


	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		float a=0.0,b=0.0,rd_a=0.0,rd_b=0.0;

		float a2=0.0,b2=0.0,rd_a2=0.0,rd_b2=0.0;


		int N24 = Bin%24;
		float ff=0.0,rd_ff=0.0;
		float ff2=0.0,rd_ff2=0.0;
		bool IsRun_EH1=false;
		bool IsRun_EH2=false;
		bool IsRun_EH3=false;

		double Th_LiveTime = 10.0;
		for(int Det=0;Det<2;Det++)
		{
			TotalIBD_Before[Det] += 1.0*IBDInEachBin[Det][Bin];
			if((LiveTimeInEachBin[Det][Bin]>Th_LiveTime)&&(MuEffInEachBin[Det][Bin]>0.001)&&(MultiEffInEachBin[Det][Bin]>0.001))
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
			a2 += IBDInEachBin[Det][Bin];
			}
		
		}

		for(int Det=2;Det<4;Det++)
		{
			TotalIBD_Before[Det] += 1.0*IBDInEachBin[Det][Bin];
			if((LiveTimeInEachBin[Det][Bin]>Th_LiveTime)&&(MuEffInEachBin[Det][Bin]>0.01)&&(MultiEffInEachBin[Det][Bin]>0.01))
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
			b2 += IBDInEachBin[Det][Bin];
			}
			
		}

	
			
		for(int Det=4;Det<8;Det++)
		{
			TotalIBD_Before[Det] += 1.0*IBDInEachBin[Det][Bin];
				if((LiveTimeInEachBin[Det][Bin]>Th_LiveTime)&&(MuEffInEachBin[Det][Bin]>0.01)&&(MultiEffInEachBin[Det][Bin]>0.01))
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
			ff2 += IBDInEachBin[Det][Bin];
			
				}
			}
			
			if(IsRun_EH1&&IsRun_EH2&&IsRun_EH3)
			{
				for(int Det=0;Det<8;Det++)
				{
				TotalIBD_After[Det] += 1.0*IBDInEachBin[Det][Bin];
				}
				Ma[N24] += a;
				Mb[N24] += b;
				Mf[N24] += ff;

				Ma2[N24] += a2;
				Mb2[N24] += b2;
				Mf2[N24] += ff2;


				RD_Ma[N24] += rd_a;
				RD_Mb[N24] += rd_b;
				RD_Mf[N24] += rd_ff;

			NBarF[N24] += AlphaBetaInEachBin[0][Bin]*a+AlphaBetaInEachBin[1][Bin]*b;
			NBarF2[N24] += AlphaBetaInEachBin[0][Bin]*a2+AlphaBetaInEachBin[1][Bin]*b2;

			RD_NBarF[N24] += pow(AlphaBetaInEachBin[0][Bin],2.0)*rd_a+ pow(AlphaBetaInEachBin[1][Bin],2.0)*rd_b;

			}
	}


	for(int N24=0;N24<24;N24++)
	{
		RD_Mf2[N24] = 1.0/sqrt(Mf2[N24]);

		RD_Ma2[N24] = 1.0/sqrt(Ma2[N24]);

		RD_Mb2[N24] = 1.0/sqrt(Mb2[N24]);

		RD_Mf[N24] += pow(Mf[N24]*RD_Eff,2.0);
		RD_Mf[N24] = sqrt(RD_Mf[N24])/Mf[N24];

		RD_Ma[N24] += pow(Ma[N24]*RD_Eff,2.0);
		RD_Ma[N24] = sqrt(RD_Ma[N24])/Ma[N24];

		RD_Mb[N24] += pow(Mb[N24]*RD_Eff,2.0);
		RD_Mb[N24] = sqrt(RD_Mb[N24])/Mb[N24];
		
		R[N24] = Mf[N24]/NBarF[N24];
		R2[N24] = Mf2[N24]/NBarF2[N24];

		Double_t Alpha_c = 0.0539873,Beta_c = 0.214963;

		R3[N24] = Mf2[N24]/((Alpha_c-0.0000)*Ma2[N24]+(Beta_c+0.00)*Mb2[N24]);


		RD_R[N24] = sqrt(pow(RD_Mf[N24],2.0)+(pow(AlphaBetaInOneDay[0][N24]*Ma[N24]*RD_Ma[N24],2.0)
			+pow(AlphaBetaInOneDay[1][N24]*Mb[N24]*RD_Mb[N24],2.0))/pow(AlphaBetaInOneDay[0][N24]*Ma[N24]+AlphaBetaInOneDay[1][N24]*Mb[N24],2.0)+pow(0.047*RD_Power,2.0));
		RD_R2[N24] = sqrt(pow(RD_Mf2[N24],2.0)+(pow(AlphaBetaInOneDay[0][N24]*Ma2[N24]*RD_Ma2[N24],2.0)
			+pow(AlphaBetaInOneDay[1][N24]*Mb2[N24]*RD_Mb2[N24],2.0))/pow(AlphaBetaInOneDay[0][N24]*Ma2[N24]+AlphaBetaInOneDay[1][N24]*Mb2[N24],2.0)+pow(RD_Power,2.0));
		RD_R3[N24] = sqrt(pow(RD_Mf2[N24],2.0)+(pow(Alpha_c*Ma2[N24]*RD_Ma2[N24],2.0)
			+pow(Beta_c*Mb2[N24]*RD_Mb2[N24],2.0))/pow(Alpha_c*Ma2[N24]+Beta_c*Mb2[N24],2.0));

	}

	Double_t MeanRatio = 0.0, MeanRatio2 = 0.0, MeanRatio3 = 0.0;//to normalize the ratio to 1
	for(int i=0;i<24;i++)
	{
		MeanRatio += R[i];
		MeanRatio2 += R2[i];
		MeanRatio3 += R3[i];
	}

	MeanRatio = MeanRatio/24.0;
	MeanRatio2 = MeanRatio2/24.0;
	MeanRatio3 = MeanRatio3/24.0;
	for(int i=0;i<24;i++)
	{
		R[i]=AVEP[2]*R[i]/MeanRatio;
		R2[i]=AVEP[2]*R2[i]/MeanRatio2;
		R3[i]=AVEP[2]*R3[i]/MeanRatio3;
	}

	TCanvas *myC1 = new TCanvas("C1","C1",200,10,800,600);
	gStyle->SetOptFit(1);
	
	
	const Int_t n = 24;
	Float_t x[n],y[n],ex[n],ey[n];
	for(int i=0;i<n;i++)
	{
		x[i]=i*WidthOfBin;
		y[i]=R[i];
		ex[i]=0;
		ey[i]=R[i]*RD_R[i];
		//cout<<y[i]<<"   "<<ey[i]<<endl;
	}
	TGraphErrors *gr1 = new TGraphErrors(n,x,y,ex,ey);
	//gr1->SetTitle("Time variation of the Data_Vs_Expectation - EH3");
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(21);

	const Int_t n2 = 24;
	Float_t x2[n2],y2[n2],ex2[n2],ey2[n2];
	for(int i=0;i<n2;i++)
	{
		x2[i]=i*WidthOfBin;
		y2[i]=R2[i];
		ex2[i]=0;
		ey2[i]=R2[i]*RD_R2[i];
		//cout<<y[i]<<"   "<<ey[i]<<endl;
	}
	TGraphErrors *gr2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
	//gr1->SetTitle("Time variation of the Data_Vs_Expectation - EH3");
	gr2->SetMarkerColor(3);
	gr2->SetMarkerStyle(21);
	

	const Int_t n3 = 24;
	Float_t x3[n3],y3[n3],ex3[n3],ey3[n3];
	for(int i=0;i<n3;i++)
	{
		x3[i]=i*WidthOfBin;
		y3[i]=R3[i];
		ex3[i]=0;
		ey3[i]=R3[i]*RD_R3[i];
		//cout<<y[i]<<"   "<<ey[i]<<endl;
	}
	TGraphErrors *gr3 = new TGraphErrors(n3,x3,y3,ex3,ey3);
	//gr1->SetTitle("Time variation of the Data_Vs_Expectation - EH3");
	gr3->SetMarkerColor(2);
	gr3->SetMarkerStyle(21);

	TMultiGraph *mg = new TMultiGraph();

	mg->Add(gr1);
	mg->Add(gr2);
	mg->Add(gr3);
	

	mg->Draw("AP");

	mg->GetXaxis()->SetTitle("sidereal time(seconds)");
	mg->GetYaxis()->SetTitle("Data/Expectation");

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

	TLegend* leg2 = new TLegend(0.1, 0.6, 0.8, 0.9);
	leg2->AddEntry(gr3,"EH3-Only IBD candidate considered, alpha=0.05399, beta=0.2150","lP");
	 leg2->AddEntry(gr2,"EH3-Only IBD candidate considered, alpha(t), beta(t)","lP");
   leg2->AddEntry(gr1,"EH3-With bkg., efficiency etc. correction, alpha(t), beta(t)","lP");
   leg2->SetFillStyle(0);
   leg2->SetBorderSize(0);
   leg2->SetTextColor(1);
   leg2->Draw();


   	gPad->Modified();
   myC1->SaveAs("Ratio_EH3_OneDay_sidereal_const_Compare.pdf");


}

Double_t func_Prob_combine_const(Double_t *x, Double_t *par)
{
	return par[0];
}



