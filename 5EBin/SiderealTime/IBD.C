

void IBD()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;//17016

	Double_t EveTime,Ep;

	Int_t NumOfIBDInEachBin[8][17016][5];//[Det][Bin][Energy]
	memset(NumOfIBDInEachBin,0,sizeof(NumOfIBDInEachBin));
	Int_t NumOfIBDInEachBin_t[8][5];

	Int_t TotalIBD[8][5]={0};

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
		IBD_Tree[Det]->SetBranchAddress("Ep",&Ep);
		IBD_Tree[Det]->GetEntry(0);
		cout<<file_Name[Det]<<endl;
		cout<<"first event: "<<setiosflags(ios::fixed)<<EveTime;
		IBD_Tree[Det]->GetEntry(NEntry-1);
		cout<<"   last event: "<<EveTime<<endl;
		for(int i=0;i<NEntry;i++)
		{
		Int_t Bin, EpBin;
		IBD_Tree[Det]->GetEntry(i);
		if((EveTime>=StartTime)&&(EveTime<EndTime))
		{
		Bin = (EveTime-StartTime)/WidthOfBin;
		if(Ep<2.0){EpBin=0;}
		else if(Ep<3.0){EpBin=1;}
		else if(Ep<4.0){EpBin=2;}
		else if(Ep<5.0){EpBin=3;}
		else {EpBin=4;}

		NumOfIBDInEachBin[Det][Bin][EpBin] ++;
		TotalIBD[Det][EpBin] ++;
		}
		}
		for(int EpBin=0;EpBin<5;EpBin++)
		{
		cout<<"AD: "<<Det<<"EBin:  "<<EpBin<<"    Total IBD:    "<<TotalIBD[Det][EpBin]<<endl;
		}
	}

	TFile  *F_NumOfIBDInEachBin = new TFile("IBD.root","recreate");
	TTree *Tree_NumOfIBDInEachBin = new TTree("IBD","IBD");
	Tree_NumOfIBDInEachBin->Branch("IBD",NumOfIBDInEachBin_t,"NumOfIBDInEachBin_t[8][5]/I");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			for(int EIdx=0;EIdx<5;EIdx++)
			{
			NumOfIBDInEachBin_t[Det][EIdx] = NumOfIBDInEachBin[Det][Bin][EIdx];
			}
		}
		Tree_NumOfIBDInEachBin->Fill();
	}
	Tree_NumOfIBDInEachBin->Write();
	

}