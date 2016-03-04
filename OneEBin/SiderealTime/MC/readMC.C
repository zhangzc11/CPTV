

void readMC()
{
	
	Double_t MC_IBD_AD_Bin_t[8][24];
	TFile *F_MC_IBD_AD_Bin = new TFile("MC_IBD_AD_Bin.root");
	TTree *Tree_MC_IBD_AD_Bin = (TTree*)F_MC_IBD_AD_Bin->Get("MC_IBD_AD_Bin");
	Tree_MC_IBD_AD_Bin->SetBranchAddress("MC_IBD_AD_Bin",MC_IBD_AD_Bin_t);

	for(int iS=0;iS<2;iS++)
	{
		Tree_MC_IBD_AD_Bin->GetEntry(iS);
		for(int Det=0;Det<8;Det++)
		{
			cout<<"Det: "<<Det<<endl;
			double IBD_Total = 0.0;
		for(int N24=0;N24<24;N24++)
		{

			//IBD_AD_Bin[Det][N24] = (myRandom->Binomial(TotalN,FullTime_Weight[Det][N24]))*1.0;
			//IBD_AD_Bin[Det][N24] = (myRandom->Poisson(IBD_AD_Bin_Exp[Det][N24]))*1.0;
			IBD_Total += MC_IBD_AD_Bin_t[Det][N24];
		}
		for(int N24=0;N24<24;N24++)
		{
			cout<<MC_IBD_AD_Bin_t[Det][N24]/IBD_Total<<endl;
		}
		
		}
	}
	
}