
Double_t StartTime = 1324678393.80705;
Double_t StartTime_Power =  1324684800.0;
double WidthOfBin = 86164.09/24.00; 
const int NumOfBin = 17016;
const int n_pow = 705;

//int idxID = 0;

double AlphaBeta_Daily[2][n_pow]={{0.0}};
double AlphaBetaInEachBin[2][NumOfBin]={{0.0}};

double Point_x[n_pow]; 

Double_t LinearInter(Double_t *x, Double_t *par);

void AlphaBeta_Interp()	
{
	for(int i=0;i<n_pow;i++)
	{
		Point_x[i] = 12.0 + 24.0*i;
	}

	//read the .root file (daily flux)
	double AlphaBeta_Daily_temp[2];
	TFile  *F_AlphaBeta_Daily = new TFile("AlphaBeta.root");
	TTree *Tree_AlphaBeta_Daily = (TTree*)F_AlphaBeta_Daily->Get("AlphaBeta");
	Tree_AlphaBeta_Daily->SetBranchAddress("AlphaBeta",AlphaBeta_Daily_temp);
	for(int Bin=0;Bin<n_pow;Bin++)
	{
		Tree_AlphaBeta_Daily->GetEntry(Bin);
		cout<<Bin<<"   ";
		for(int idx=0;idx<2;idx++)
		{
			AlphaBeta_Daily[idx][Bin] = AlphaBeta_Daily_temp[idx];
			cout<<AlphaBeta_Daily_temp[idx]<<"   ";
		}
		cout<<endl;
	}

	//linear interpolation
	TCanvas *c1 = new TCanvas("c1","interpolation",0,0,1000,800);
//	c1->SetLogy();
	TF1 *seg[2];
	const char *seg_name[8] = {"alpha","beta"};
	for(int idx=1;idx>=0;idx--)
	{
	//	idxID = idx;
		seg[idx] = new TF1(seg_name[idx], LinearInter, 0, NumOfBin*WidthOfBin/3600.0, 1); 
		seg[idx]->SetParameter(0,1.0*idx);
		seg[idx]->SetLineColor(idx+2);
		
		if(idx==1)
		{
			seg[idx]->Draw("l");
			seg[idx]->GetYaxis()->SetRangeUser(0,0.4);
	//		seg[idx]->GetYAxis()-
		}
		else
		{
			seg[idx]->Draw("lsame");
		}

		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			 Double_t InterBin_L = Bin*WidthOfBin/3600.0;
			 Double_t InterBin_R = (Bin+1.0)*WidthOfBin/3600.0;
			 AlphaBetaInEachBin[idx][Bin] = seg[idx]->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		}
		
	}
	TLegend *leg = new TLegend(0.4, 0.7, 0.8, 0.9);
	leg->AddEntry(seg[0],"#alpha","l");
	leg->AddEntry(seg[1],"#beta","l");
	leg->SetFillStyle(0);
    leg->SetBorderSize(0);
	leg->Draw();
	c1->SaveAs("AlphaBeta.pdf");

/*
	for(int idx=0;idx<8;idx++)
	{
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N24 = Bin%24;
		Fraction_AD_Day[idx][N24] += Fraction_AD_Bin[idx][Bin];
	}
	}

	for(int idx=0;idx<2;idx++)
	{
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			Fraction_Hall_Bin[0][Bin] += Fraction_AD_Bin[idx][Bin];
		}
		for(int N24=0;N24<24;N24++)
		{
			Fraction_Hall_Day[0][N24] += Fraction_AD_Day[idx][N24];
		}
	}
	for(int idx=2;idx<4;idx++)
	{
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			Fraction_Hall_Bin[1][Bin] += Fraction_AD_Bin[idx][Bin];
		}
		for(int N24=0;N24<24;N24++)
		{
			Fraction_Hall_Day[1][N24] += Fraction_AD_Day[idx][N24];
		}
	}
	for(int idx=4;idx<8;idx++)
	{
		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			Fraction_Hall_Bin[2][Bin] += Fraction_AD_Bin[idx][Bin];
		}
		for(int N24=0;N24<24;N24++)
		{
			Fraction_Hall_Day[2][N24] += Fraction_AD_Day[idx][N24];
		}
	}
*/
	///////////save to .root file;
	double AlphaBeta_t[8];

	TFile  *F_AlphaBeta_Bin = new TFile("AlphaBeta_Bin.root","recreate");
	TTree *Tree_AlphaBeta_Bin = new TTree("AlphaBeta","AlphaBeta");
	Tree_AlphaBeta_Bin->Branch("AlphaBeta",AlphaBeta_t,"AlphaBeta_t[2]/D");
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		for(int idx=0;idx<2;idx++)
		{
			AlphaBeta_t[idx] = AlphaBetaInEachBin[idx][Bin];
		}
		Tree_AlphaBeta_Bin->Fill();
	}
	Tree_AlphaBeta_Bin->Write();
/*
	TFile  *F_Fraction_Hall_Bin = new TFile("Fraction_Hall_Bin.root","recreate");
	TTree *Tree_Fraction_Hall_Bin = new TTree("Fraction","Fraction");
	Tree_Fraction_Hall_Bin->Branch("Fraction",Fraction_Hall_t,"Fraction_Hall_t[3]/D");
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		for(int Hall=0;Hall<8;Hall++)
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
		for(int idx=0;idx<8;idx++)
		{
			Fraction_AD_t[idx] = Fraction_AD_Day[idx][Bin];
		}
		Tree_Fraction_AD_Day->Fill();
	}
	Tree_Fraction_AD_Day->Write();

	TFile  *F_Fraction_Hall_Day = new TFile("Fraction_Hall_Day.root","recreate");
	TTree *Tree_Fraction_Hall_Day = new TTree("Fraction","Fraction");
	Tree_Fraction_Hall_Day->Branch("Fraction",Fraction_Hall_t,"Fraction_Hall_t[3]/D");
	for(int Bin=0;Bin<24;Bin++)
	{
		for(int Hall=0;Hall<8;Hall++)
		{
			Fraction_Hall_t[Hall] = Fraction_Hall_Day[Hall][Bin];
		}
		Tree_Fraction_Hall_Day->Fill();
	}
	Tree_Fraction_Hall_Day->Write();
*/


}

Double_t LinearInter(Double_t *x, Double_t *par)
{

	int idxID = int (par[0]);
	if(x[0]>=Point_x[n_pow-1])
	{
		return (AlphaBeta_Daily[idxID][n_pow-1]+(x[0]-Point_x[n_pow-1])*(AlphaBeta_Daily[idxID][n_pow-1]-AlphaBeta_Daily[idxID][n_pow-2])/24.0);
	}
	else if(x[0]<=Point_x[0])
	{
	return (AlphaBeta_Daily[idxID][0]-(Point_x[0]-x[0])*(AlphaBeta_Daily[idxID][1]-AlphaBeta_Daily[idxID][0])/24.0);
	}
	else
	{
		int i=0;
		while (x[0]>Point_x[i])
		{
			i++;
		}
		return (AlphaBeta_Daily[idxID][i-1]+(x[0]-Point_x[i-1])*(AlphaBeta_Daily[idxID][i]-AlphaBeta_Daily[idxID][i-1])/24.0);
	}
}

