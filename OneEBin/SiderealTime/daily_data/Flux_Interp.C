
Double_t StartTime = 1324678393.80705;
Double_t StartTime_Power =  1324684800.0;
double WidthOfBin = 86164.09/24.00; 
const int NumOfBin = 17016;
const int n_pow = 705;

//int DetID = 0;

double Flux_Daily_AD[8][n_pow]={{0.0}};
double FluxInEachBin[8][NumOfBin]={{0.0}};
double FluxInOneDay[8][24]={{0.0}};

double Fraction_AD_Bin[8][NumOfBin]={{0.0}};
double Fraction_AD_Day[8][24]={{0.0}};
double Fraction_Hall_Bin[3][NumOfBin]={{0.0}};
double Fraction_Hall_Day[3][24]={{0.0}};

double AlphaBetaInEachBin[2][NumOfBin]={{0.0}};



double Point_x[n_pow]; 


Double_t FullTime[8][NumOfBin];

Double_t LinearInter(Double_t *x, Double_t *par);

void Flux_Interp()	
{
	for(int i=0;i<n_pow;i++)
	{
		Point_x[i] = 12.0 + 24.0*i;
	}

	//read the .root file (daily flux)
	double Flux_Daily_AD_temp[8];
	TFile  *F_Flux_Daily_AD = new TFile("Flux_Daily_AD.root");
	TTree *Tree_Flux_Daily_AD = (TTree*)F_Flux_Daily_AD->Get("Flux_Daily_AD");
	Tree_Flux_Daily_AD->SetBranchAddress("Flux_Daily_AD",Flux_Daily_AD_temp);
	for(int Bin=0;Bin<n_pow;Bin++)
	{
		Tree_Flux_Daily_AD->GetEntry(Bin);
		//cout<<Bin<<"   ";
		for(int Det=0;Det<8;Det++)
		{
			Flux_Daily_AD[Det][Bin] = Flux_Daily_AD_temp[Det];
			//cout<<Flux_Daily_AD_temp[Det]<<"   ";
		}
		//cout<<endl;
	}
	
	Double_t FullTime_temp[8];
	TFile *F_FullTime = new TFile("../FullTime.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
	Tree_FullTime->SetBranchAddress("FullTime",FullTime_temp);
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		Tree_FullTime->GetEntry(Bin);
		for(int Det=0;Det<8;Det++)
		{
		FullTime[Det][Bin] = FullTime_temp[Det];
		}
	}

	//linear interpolation
	TCanvas *c1 = new TCanvas("c1","interpolation",0,0,1000,800);
//	c1->SetLogy();
	TF1 *seg[8];
	const char *seg_name[8] = {"AD1","AD2","AD3","AD4","AD5","AD6","AD7","AD8"};
	for(int Det=0;Det<8;Det++)
	{
	//	DetID = Det;
		seg[Det] = new TF1(seg_name[Det], LinearInter, 0, NumOfBin*WidthOfBin/3600.0, 1); 
		seg[Det]->SetParameter(0,1.0*Det);
		seg[Det]->SetLineColor(Det+1);
		
		if(Det==0)
		{
			seg[Det]->Draw("l");
			seg[Det]->GetYaxis()->SetRangeUser(0,2.0e16);
	//		seg[Det]->GetYAxis()-
		}
		else
		{
			seg[Det]->Draw("lsame");
		}

		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			 Double_t InterBin_L = Bin*WidthOfBin/3600.0;
			 Double_t InterBin_R = (Bin+1.0)*WidthOfBin/3600.0;
			 Fraction_AD_Bin[Det][Bin] = seg[Det]->Integral(InterBin_L,InterBin_R)*FullTime[Det][Bin]/(WidthOfBin/3600.0);
		}
		
	}

	for(int Det=0;Det<8;Det++)
	{
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N24 = Bin%24;
		Fraction_AD_Day[Det][N24] += Fraction_AD_Bin[Det][Bin];
	}
	}

	for(int Det=0;Det<2;Det++)
	{
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			Fraction_Hall_Bin[0][Bin] += Fraction_AD_Bin[Det][Bin];
		}
		for(int N24=0;N24<24;N24++)
		{
			Fraction_Hall_Day[0][N24] += Fraction_AD_Day[Det][N24];
		}
	}
	for(int Det=2;Det<4;Det++)
	{
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			Fraction_Hall_Bin[1][Bin] += Fraction_AD_Bin[Det][Bin];
		}
		for(int N24=0;N24<24;N24++)
		{
			Fraction_Hall_Day[1][N24] += Fraction_AD_Day[Det][N24];
		}
	}
	for(int Det=4;Det<8;Det++)
	{
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			Fraction_Hall_Bin[2][Bin] += Fraction_AD_Bin[Det][Bin];
		}
		for(int N24=0;N24<24;N24++)
		{
			Fraction_Hall_Day[2][N24] += Fraction_AD_Day[Det][N24];
		}
	}
///////////save to .root file;
	//AD_Bin
	double Fraction_AD_t[8];
	double Fraction_Hall_t[3];

	TFile  *F_Fraction_AD_Bin = new TFile("Fraction_AD_Bin.root","recreate");
	TTree *Tree_Fraction_AD_Bin = new TTree("Fraction","Fraction");
	Tree_Fraction_AD_Bin->Branch("Fraction",Fraction_AD_t,"Fraction_AD_t[8]/D");
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			Fraction_AD_t[Det] = Fraction_AD_Bin[Det][Bin];
		}
		Tree_Fraction_AD_Bin->Fill();
	}
	Tree_Fraction_AD_Bin->Write();

	TFile  *F_Fraction_Hall_Bin = new TFile("Fraction_Hall_Bin.root","recreate");
	TTree *Tree_Fraction_Hall_Bin = new TTree("Fraction","Fraction");
	Tree_Fraction_Hall_Bin->Branch("Fraction",Fraction_Hall_t,"Fraction_Hall_t[3]/D");
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		for(int Hall=0;Hall<3;Hall++)
		{
			Fraction_Hall_t[Hall] = Fraction_Hall_Bin[Hall][Bin];
		}
		Tree_Fraction_Hall_Bin->Fill();
	}
	Tree_Fraction_Hall_Bin->Write();

	TFile  *F_Fraction_AD_Day = new TFile("Fraction_AD_Day.root","recreate");
	TTree *Tree_Fraction_AD_Day = new TTree("Fraction","Fraction");
	Tree_Fraction_AD_Day->Branch("Fraction",Fraction_AD_t,"Fraction_AD_t[8]/D");
	for(int Bin=0;Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			Fraction_AD_t[Det] = Fraction_AD_Day[Det][Bin];
		}
		Tree_Fraction_AD_Day->Fill();
	}
	Tree_Fraction_AD_Day->Write();

	TFile  *F_Fraction_Hall_Day = new TFile("Fraction_Hall_Day.root","recreate");
	TTree *Tree_Fraction_Hall_Day = new TTree("Fraction","Fraction");
	Tree_Fraction_Hall_Day->Branch("Fraction",Fraction_Hall_t,"Fraction_Hall_t[3]/D");
	for(int Bin=0;Bin<24;Bin++)
	{
		for(int Hall=0;Hall<3;Hall++)
		{
			Fraction_Hall_t[Hall] = Fraction_Hall_Day[Hall][Bin];
		}
		Tree_Fraction_Hall_Day->Fill();
	}
	Tree_Fraction_Hall_Day->Write();



}

Double_t LinearInter(Double_t *x, Double_t *par)
{

	int DetID = int (par[0]);
	if(x[0]>=Point_x[n_pow-1])
	{
		return (Flux_Daily_AD[DetID][n_pow-1]+(x[0]-Point_x[n_pow-1])*(Flux_Daily_AD[DetID][n_pow-1]-Flux_Daily_AD[DetID][n_pow-2])/24.0);
	}
	else if(x[0]<=Point_x[0])
	{
	return (Flux_Daily_AD[DetID][0]-(Point_x[0]-x[0])*(Flux_Daily_AD[DetID][1]-Flux_Daily_AD[DetID][0])/24.0);
	}
	else
	{
		int i=0;
		while (x[0]>Point_x[i])
		{
			i++;
		}
		return (Flux_Daily_AD[DetID][i-1]+(x[0]-Point_x[i-1])*(Flux_Daily_AD[DetID][i]-Flux_Daily_AD[DetID][i-1])/24.0);
	}
}

