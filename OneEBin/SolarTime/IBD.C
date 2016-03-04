

void IBD()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	Double_t EveTime;

	Int_t NumOfIBDInEachBin[8][16968];
	memset(NumOfIBDInEachBin,0,sizeof(NumOfIBDInEachBin));
	Int_t NumOfIBDInEachBin_t[8];

	Int_t TotalIBD[8]={0};

	const char *file_Name[8] = {
		"../Input/P14AIBD/EH1/result/IBD/IBD_EH1_AD1.root","../Input/P14AIBD/EH1/result/IBD/IBD_EH1_AD2.root",
		"../Input/P14AIBD/EH2/result/IBD/IBD_EH2_AD1.root","../Input/P14AIBD/EH2/result/IBD/IBD_EH2_AD2.root",
		"../Input/P14AIBD/EH3/result/IBD/IBD_EH3_AD1.root","../Input/P14AIBD/EH3/result/IBD/IBD_EH3_AD2.root",
		"../Input/P14AIBD/EH3/result/IBD/IBD_EH3_AD3.root","../Input/P14AIBD/EH3/result/IBD/IBD_EH3_AD4.root"
	};

	TFile *IBD_F[8];
	TTree *IBD_Tree[8];

	for(int Det=0;Det<8;Det++)
	{
		IBD_F[Det] = new TFile(file_Name[Det]);
		IBD_Tree[Det] = (TTree*)IBD_F[Det]->Get("IBD");
		Int_t NEntry = IBD_Tree[Det]->GetEntries();
		IBD_Tree[Det]->SetBranchAddress("EveTime",&EveTime);
		IBD_Tree[Det]->GetEntry(0);
		cout<<file_Name[Det]<<endl;
		cout<<"first event: "<<setiosflags(ios::fixed)<<EveTime;
		IBD_Tree[Det]->GetEntry(NEntry-1);
		cout<<"   last event: "<<EveTime;
		for(int i=0;i<NEntry;i++)
		{
		Int_t Bin;
		IBD_Tree[Det]->GetEntry(i);
		if((EveTime>=StartTime)&&(EveTime<EndTime))
		{
		Bin = (EveTime-StartTime)/WidthOfBin;
		NumOfIBDInEachBin[Det][Bin] ++;
		TotalIBD[Det] ++;
		}
		}
		cout<<"    Total IBD: "<<TotalIBD[Det]<<endl;
	}

	TFile  *F_NumOfIBDInEachBin = new TFile("IBD.root","recreate");
	TTree *Tree_NumOfIBDInEachBin = new TTree("IBD","IBD");
	Tree_NumOfIBDInEachBin->Branch("IBD",NumOfIBDInEachBin_t,"NumOfIBDInEachBin_t[8]/I");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			NumOfIBDInEachBin_t[Det] = NumOfIBDInEachBin[Det][Bin];
		}
		Tree_NumOfIBDInEachBin->Fill();
	}
	Tree_NumOfIBDInEachBin->Write();
	

}