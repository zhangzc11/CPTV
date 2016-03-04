

void nLike()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	Double_t EveTime;

	Int_t NumOfnLikeInEachBin[8][16968];
	memset(NumOfnLikeInEachBin,0,sizeof(NumOfnLikeInEachBin));
	Int_t NumOfnLikeInEachBin_t[8];

	Int_t NumOfnLikeUpInEachBin[8][16968];
	memset(NumOfnLikeUpInEachBin,0,sizeof(NumOfnLikeUpInEachBin));

	Int_t NumOfnLikeDownInEachBin[8][16968];
	memset(NumOfnLikeDownInEachBin,0,sizeof(NumOfnLikeDownInEachBin));

	Int_t TotalnLike[8]={0};

	const char *file_NameUp[8] = {
		"../Input/P14AIBD/EH1/result/nLikeUp/nLikeUp_EH1_AD1.root","../Input/P14AIBD/EH1/result/nLikeUp/nLikeUp_EH1_AD2.root",
		"../Input/P14AIBD/EH2/result/nLikeUp/nLikeUp_EH2_AD1.root","../Input/P14AIBD/EH2/result/nLikeUp/nLikeUp_EH2_AD2.root",
		"../Input/P14AIBD/EH3/result/nLikeUp/nLikeUp_EH3_AD1.root","../Input/P14AIBD/EH3/result/nLikeUp/nLikeUp_EH3_AD2.root",
		"../Input/P14AIBD/EH3/result/nLikeUp/nLikeUp_EH3_AD3.root","../Input/P14AIBD/EH3/result/nLikeUp/nLikeUp_EH3_AD4.root"
	};

	const char *file_NameDown[8] = {
		"../Input/P14AIBD/EH1/result/nLikeDown/nLikeDown_EH1_AD1.root","../Input/P14AIBD/EH1/result/nLikeDown/nLikeDown_EH1_AD2.root",
		"../Input/P14AIBD/EH2/result/nLikeDown/nLikeDown_EH2_AD1.root","../Input/P14AIBD/EH2/result/nLikeDown/nLikeDown_EH2_AD2.root",
		"../Input/P14AIBD/EH3/result/nLikeDown/nLikeDown_EH3_AD1.root","../Input/P14AIBD/EH3/result/nLikeDown/nLikeDown_EH3_AD2.root",
		"../Input/P14AIBD/EH3/result/nLikeDown/nLikeDown_EH3_AD3.root","../Input/P14AIBD/EH3/result/nLikeDown/nLikeDown_EH3_AD4.root"
	};

	TFile *nLikeUp_F[8];
	TTree *nLikeUp_Tree[8];

	TFile *nLikeDown_F[8];
	TTree *nLikeDown_Tree[8];

	for(int Det=0;Det<8;Det++)
	{
		nLikeUp_F[Det] = new TFile(file_NameUp[Det]);
		nLikeUp_Tree[Det] = (TTree*)nLikeUp_F[Det]->Get("nLikeUp");
		Int_t NEntryUp = nLikeUp_Tree[Det]->GetEntries();
		nLikeUp_Tree[Det]->SetBranchAddress("EveTime",&EveTime);

		nLikeDown_F[Det] = new TFile(file_NameDown[Det]);
		nLikeDown_Tree[Det] = (TTree*)nLikeDown_F[Det]->Get("nLikeDown");
		Int_t NEntryDown = nLikeDown_Tree[Det]->GetEntries();
		nLikeDown_Tree[Det]->SetBranchAddress("EveTime",&EveTime);
		
		for(int i=0;i<NEntryUp;i++)
		{
		Int_t Bin;
		nLikeUp_Tree[Det]->GetEntry(i);
		if((EveTime>=StartTime)&&(EveTime<EndTime))
		{
		Bin = (EveTime-StartTime)/WidthOfBin;
		NumOfnLikeUpInEachBin[Det][Bin] ++;
		}
		}
		
		for(int i=0;i<NEntryDown;i++)
		{
		Int_t Bin;
		nLikeDown_Tree[Det]->GetEntry(i);
		if((EveTime>=StartTime)&&(EveTime<EndTime))
		{
		Bin = (EveTime-StartTime)/WidthOfBin;
		NumOfnLikeDownInEachBin[Det][Bin] ++;
		}
		}

		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			if(NumOfnLikeUpInEachBin[Det][Bin] > NumOfnLikeDownInEachBin[Det][Bin])
			{
			NumOfnLikeInEachBin[Det][Bin] = NumOfnLikeUpInEachBin[Det][Bin] - NumOfnLikeDownInEachBin[Det][Bin];
			TotalnLike[Det] += NumOfnLikeInEachBin[Det][Bin];
			}
		}
	}

	for(int Det=0;Det<8;Det++)
	{
		cout<<"Total nLike in AD"<<Det+1<<":   "<<TotalnLike[Det]<<endl;
	}

	TFile  *F_NumOfnLikeInEachBin = new TFile("nLike.root","recreate");
	TTree *Tree_NumOfnLikeInEachBin = new TTree("nLike","nLike");
	Tree_NumOfnLikeInEachBin->Branch("nLike",NumOfnLikeInEachBin_t,"NumOfnLikeInEachBin_t[8]/I");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			NumOfnLikeInEachBin_t[Det] = NumOfnLikeInEachBin[Det][Bin];
		}
		Tree_NumOfnLikeInEachBin->Fill();
	}
	Tree_NumOfnLikeInEachBin->Write();
}