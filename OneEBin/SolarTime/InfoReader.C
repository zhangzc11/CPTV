
#include <string>
#include <fstream>
#include <sstream>

void InfoReader()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968
	Int_t Bin_8AD = 7060;


	Double_t FullTime_t;
	Double_t Veto_t[4],SgUp_t[4],SgLow_t[4],NetMu_t[4],AdMu_t[4],HMuL5_t[4],HMuG5_t[4],HMuG10_t[4],HMuG15_t[4];

	Double_t FullTime[8];
	Double_t FullTimeInEachBin[8][16968];
	memset(FullTimeInEachBin,0.0,sizeof(FullTimeInEachBin));

    Double_t LiveTime[8];
	Double_t LiveTimeInEachBin[8][16968];
	memset(LiveTimeInEachBin,0.0,sizeof(LiveTimeInEachBin));

	Double_t SgUp[8];
	Double_t SgUpInEachBin[8][16968];
	memset(SgUpInEachBin,0.0,sizeof(SgUpInEachBin));

	Double_t SgLow[8];
	Double_t SgLowInEachBin[8][16968];
	memset(SgLowInEachBin,0.0,sizeof(SgLowInEachBin));

	Double_t NetMu[8];
	Double_t NetMuInEachBin[8][16968];
	memset(NetMuInEachBin,0.0,sizeof(NetMuInEachBin));

	Double_t AdMu[8];
	Double_t AdMuInEachBin[8][16968];
	memset(AdMuInEachBin,0.0,sizeof(AdMuInEachBin));

	Double_t HMuL5[8];
	Double_t HMuL5InEachBin[8][16968];
	memset(HMuL5InEachBin,0.0,sizeof(HMuL5InEachBin));

	Double_t HMuG5[8];
	Double_t HMuG5InEachBin[8][16968];
	memset(HMuG5InEachBin,0.0,sizeof(HMuG5InEachBin));

	Double_t HMuG10[8];
	Double_t HMuG10InEachBin[8][16968];
	memset(HMuG10InEachBin,0.0,sizeof(HMuG10InEachBin));

	Double_t HMuG15[8];
	Double_t HMuG15InEachBin[8][16968];
	memset(HMuG15InEachBin,0.0,sizeof(HMuG15InEachBin));


	std::string s;
	//EH1
	ifstream is_EH1("InfoInEachBin_EH1.txt");
	while(!is_EH1.eof())
	{
		Int_t Bin;
		getline(is_EH1,s);
		
		{
		string subs;
		stringstream ss;
		subs = s.substr(27,5);//Bin
		ss<<subs;
		ss>>Bin;
		}

		{
		string subs;
		stringstream ss;
		subs = s.substr(92,16);//FullTime
		ss<<subs;
		ss>>FullTime_t;
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(125+16*Det,16);//Veto time
		ss<<subs;
		ss>>Veto_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(189+16*Det,16);//SgUp
		ss<<subs;
		ss>>SgUp_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(253+16*Det,16);//SgLow
		ss<<subs;
		ss>>SgLow_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(317+16*Det,16);//NetMu
		ss<<subs;
		ss>>NetMu_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(381+16*Det,16);//AdMu
		ss<<subs;
		ss>>AdMu_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(444+16*Det,16);
		ss<<subs;
		ss>>HMuL5_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(508+16*Det,16);
		ss<<subs;
		ss>>HMuG5_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(572+16*Det,16);
		ss<<subs;
		ss>>HMuG10_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(636+16*Det,16);
		ss<<subs;
		ss>>HMuG15_t[Det];
		}


		FullTimeInEachBin[0][Bin] += FullTime_t;
		FullTimeInEachBin[1][Bin] += FullTime_t;

		LiveTimeInEachBin[0][Bin] += FullTime_t - Veto_t[0];
		LiveTimeInEachBin[1][Bin] += FullTime_t - Veto_t[1];

		SgUpInEachBin[0][Bin] += SgUp_t[0];
		SgUpInEachBin[1][Bin] += SgUp_t[1];

		SgLowInEachBin[0][Bin] += SgLow_t[0];
		SgLowInEachBin[1][Bin] += SgLow_t[1];

		NetMuInEachBin[0][Bin] += NetMu_t[0];
		NetMuInEachBin[1][Bin] += NetMu_t[1];

		AdMuInEachBin[0][Bin] += AdMu_t[0];
		AdMuInEachBin[1][Bin] += AdMu_t[1];

		HMuL5InEachBin[0][Bin] += HMuL5_t[0];
		HMuL5InEachBin[1][Bin] += HMuL5_t[1];

		HMuG5InEachBin[0][Bin] += HMuG5_t[0];
		HMuG5InEachBin[1][Bin] += HMuG5_t[1];

		HMuG10InEachBin[0][Bin] += HMuG10_t[0];
		HMuG10InEachBin[1][Bin] += HMuG10_t[1];

		HMuG15InEachBin[0][Bin] += HMuG15_t[0];
		HMuG15InEachBin[1][Bin] += HMuG15_t[1];

		//cout<<Bin<<"   "<<NetMuInEachBin[0][Bin]<<"      "<<AdMuInEachBin[0][Bin]<<"      "<<HMuL5InEachBin[0][Bin]<<"      "<<HMuG5InEachBin[0][Bin]<<"      "<<HMuG10InEachBin[0][Bin]<<"      "<<HMuG15InEachBin[0][Bin]<<"      "<<endl;

	}
	is_EH1.close();


	//EH2
	ifstream is_EH2("InfoInEachBin_EH2.txt");
	while(!is_EH2.eof())
	{
		Int_t Bin;
		getline(is_EH2,s);
		
		{
		string subs;
		stringstream ss;
		subs = s.substr(27,5);//Bin
		ss<<subs;
		ss>>Bin;
		}

		{
		string subs;
		stringstream ss;
		subs = s.substr(92,16);//FullTime
		ss<<subs;
		ss>>FullTime_t;
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(125+16*Det,16);//Veto time
		ss<<subs;
		ss>>Veto_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(189+16*Det,16);//SgUp
		ss<<subs;
		ss>>SgUp_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(253+16*Det,16);//SgLow
		ss<<subs;
		ss>>SgLow_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(317+16*Det,16);//NetMu
		ss<<subs;
		ss>>NetMu_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(381+16*Det,16);//AdMu
		ss<<subs;
		ss>>AdMu_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(444+16*Det,16);
		ss<<subs;
		ss>>HMuL5_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(508+16*Det,16);
		ss<<subs;
		ss>>HMuG5_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(572+16*Det,16);
		ss<<subs;
		ss>>HMuG10_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(636+16*Det,16);
		ss<<subs;
		ss>>HMuG15_t[Det];
		}

		if(Bin>Bin_8AD)
		{
		FullTimeInEachBin[2][Bin] += FullTime_t;
		FullTimeInEachBin[3][Bin] += FullTime_t;

		LiveTimeInEachBin[2][Bin] += FullTime_t - Veto_t[0];
		LiveTimeInEachBin[3][Bin] += FullTime_t - Veto_t[1];

		SgUpInEachBin[2][Bin] += SgUp_t[0];
		SgUpInEachBin[3][Bin] += SgUp_t[1];

		SgLowInEachBin[2][Bin] += SgLow_t[0];
		SgLowInEachBin[3][Bin] += SgLow_t[1];

		NetMuInEachBin[2][Bin] += NetMu_t[0];
		NetMuInEachBin[3][Bin] += NetMu_t[1];

		AdMuInEachBin[2][Bin] += AdMu_t[0];
		AdMuInEachBin[3][Bin] += AdMu_t[1];

		HMuL5InEachBin[2][Bin] += HMuL5_t[0];
		HMuL5InEachBin[3][Bin] += HMuL5_t[1];

		HMuG5InEachBin[2][Bin] += HMuG5_t[0];
		HMuG5InEachBin[3][Bin] += HMuG5_t[1];

		HMuG10InEachBin[2][Bin] += HMuG10_t[0];
		HMuG10InEachBin[3][Bin] += HMuG10_t[1];

		HMuG15InEachBin[2][Bin] += HMuG15_t[0];
		HMuG15InEachBin[3][Bin] += HMuG15_t[1];
		}
		else
		{
		FullTimeInEachBin[2][Bin] += FullTime_t;

		LiveTimeInEachBin[2][Bin] += FullTime_t - Veto_t[0];

		SgUpInEachBin[2][Bin] += SgUp_t[0];

		SgLowInEachBin[2][Bin] += SgLow_t[0];

		NetMuInEachBin[2][Bin] += NetMu_t[0];

		AdMuInEachBin[2][Bin] += AdMu_t[0];

		HMuL5InEachBin[2][Bin] += HMuL5_t[0];

		HMuG5InEachBin[2][Bin] += HMuG5_t[0];

		HMuG10InEachBin[2][Bin] += HMuG10_t[0];

		HMuG15InEachBin[2][Bin] += HMuG15_t[0];
		}

		//cout<<Bin<<"   "<<NetMuInEachBin[0][Bin]<<"      "<<AdMuInEachBin[0][Bin]<<"      "<<HMuL5InEachBin[0][Bin]<<"      "<<HMuG5InEachBin[0][Bin]<<"      "<<HMuG10InEachBin[0][Bin]<<"      "<<HMuG15InEachBin[0][Bin]<<"      "<<endl;

	}
	is_EH2.close();


	//EH3
	ifstream is_EH3("InfoInEachBin_EH3.txt");
	while(!is_EH3.eof())
	{
		Int_t Bin;
		getline(is_EH3,s);
		
		{
		string subs;
		stringstream ss;
		subs = s.substr(27,5);//Bin
		ss<<subs;
		ss>>Bin;
		}

		{
		string subs;
		stringstream ss;
		subs = s.substr(92,16);//FullTime
		ss<<subs;
		ss>>FullTime_t;
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(125+16*Det,16);//Veto time
		ss<<subs;
		ss>>Veto_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(189+16*Det,16);//SgUp
		ss<<subs;
		ss>>SgUp_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(253+16*Det,16);//SgLow
		ss<<subs;
		ss>>SgLow_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(317+16*Det,16);//NetMu
		ss<<subs;
		ss>>NetMu_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(381+16*Det,16);//AdMu
		ss<<subs;
		ss>>AdMu_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(444+16*Det,16);
		ss<<subs;
		ss>>HMuL5_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(508+16*Det,16);
		ss<<subs;
		ss>>HMuG5_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(572+16*Det,16);
		ss<<subs;
		ss>>HMuG10_t[Det];
		}

		for(int Det=0;Det<4;Det++)
		{
		string subs;
		stringstream ss;
		subs = s.substr(636+16*Det,16);
		ss<<subs;
		ss>>HMuG15_t[Det];
		}

		FullTimeInEachBin[4][Bin] += FullTime_t;
		FullTimeInEachBin[5][Bin] += FullTime_t;

		LiveTimeInEachBin[4][Bin] += FullTime_t - Veto_t[0];
		LiveTimeInEachBin[5][Bin] += FullTime_t - Veto_t[1];

		SgUpInEachBin[4][Bin] += SgUp_t[0];
		SgUpInEachBin[5][Bin] += SgUp_t[1];

		SgLowInEachBin[4][Bin] += SgLow_t[0];
		SgLowInEachBin[5][Bin] += SgLow_t[1];

		NetMuInEachBin[4][Bin] += NetMu_t[0];
		NetMuInEachBin[5][Bin] += NetMu_t[1];

		AdMuInEachBin[4][Bin] += AdMu_t[0];
		AdMuInEachBin[5][Bin] += AdMu_t[1];

		HMuL5InEachBin[4][Bin] += HMuL5_t[0];
		HMuL5InEachBin[5][Bin] += HMuL5_t[1];

		HMuG5InEachBin[4][Bin] += HMuG5_t[0];
		HMuG5InEachBin[5][Bin] += HMuG5_t[1];

		HMuG10InEachBin[4][Bin] += HMuG10_t[0];
		HMuG10InEachBin[5][Bin] += HMuG10_t[1];

		HMuG15InEachBin[4][Bin] += HMuG15_t[0];
		HMuG15InEachBin[5][Bin] += HMuG15_t[1];
		
		FullTimeInEachBin[6][Bin] += FullTime_t;

		LiveTimeInEachBin[6][Bin] += FullTime_t - Veto_t[2];

		SgUpInEachBin[6][Bin] += SgUp_t[2];

		SgLowInEachBin[6][Bin] += SgLow_t[2];

		NetMuInEachBin[6][Bin] += NetMu_t[2];

		AdMuInEachBin[6][Bin] += AdMu_t[2];

		HMuL5InEachBin[6][Bin] += HMuL5_t[2];

		HMuG5InEachBin[6][Bin] += HMuG5_t[2];

		HMuG10InEachBin[6][Bin] += HMuG10_t[2];

		HMuG15InEachBin[6][Bin] += HMuG15_t[2];

		if(Bin>Bin_8AD)
		{
		FullTimeInEachBin[7][Bin] += FullTime_t;

		LiveTimeInEachBin[7][Bin] += FullTime_t - Veto_t[3];

		SgUpInEachBin[7][Bin] += SgUp_t[3];

		SgLowInEachBin[7][Bin] += SgLow_t[3];

		NetMuInEachBin[7][Bin] += NetMu_t[3];

		AdMuInEachBin[7][Bin] += AdMu_t[3];

		HMuL5InEachBin[7][Bin] += HMuL5_t[3];

		HMuG5InEachBin[7][Bin] += HMuG5_t[3];

		HMuG10InEachBin[7][Bin] += HMuG10_t[3];

		HMuG15InEachBin[7][Bin] += HMuG15_t[3];

		}


		//cout<<Bin<<"   "<<NetMuInEachBin[0][Bin]<<"      "<<AdMuInEachBin[0][Bin]<<"      "<<HMuL5InEachBin[0][Bin]<<"      "<<HMuG5InEachBin[0][Bin]<<"      "<<HMuG10InEachBin[0][Bin]<<"      "<<HMuG15InEachBin[0][Bin]<<"      "<<endl;

	}
	is_EH3.close();
	//////////////////save to .root file///////////////////////
	//FullTime
	TFile  *F_FullTime = new TFile("FullTime.root","recreate");
	TTree *Tree_FullTime = new TTree("FullTime","FullTime");
	Tree_FullTime->Branch("FullTime",FullTime,"FullTime[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			FullTime[Det] = FullTimeInEachBin[Det][Bin];
		}
		Tree_FullTime->Fill();
	}
	Tree_FullTime->Write();

	//LiveTime
	TFile  *F_LiveTime = new TFile("LiveTime.root","recreate");
	TTree *Tree_LiveTime = new TTree("LiveTime","LiveTime");
	Tree_LiveTime->Branch("LiveTime",LiveTime,"LiveTime[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			LiveTime[Det] = LiveTimeInEachBin[Det][Bin];
		}
		Tree_LiveTime->Fill();
	}
	Tree_LiveTime->Write();

	//SgUp
	TFile  *F_SgUp = new TFile("SgUp.root","recreate");
	TTree *Tree_SgUp = new TTree("SgUp","SgUp");
	Tree_SgUp->Branch("SgUp",SgUp,"SgUp[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			SgUp[Det] = SgUpInEachBin[Det][Bin];
		}
		Tree_SgUp->Fill();
	}
	Tree_SgUp->Write();

	//SgLow
	TFile  *F_SgLow = new TFile("SgLow.root","recreate");
	TTree *Tree_SgLow = new TTree("SgLow","SgLow");
	Tree_SgLow->Branch("SgLow",SgLow,"SgLow[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			SgLow[Det] = SgLowInEachBin[Det][Bin];
		}
		Tree_SgLow->Fill();
	}
	Tree_SgLow->Write();


	//NetMu
	TFile  *F_NetMu = new TFile("NetMu.root","recreate");
	TTree *Tree_NetMu = new TTree("NetMu","NetMu");
	Tree_NetMu->Branch("NetMu",NetMu,"NetMu[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			NetMu[Det] = NetMuInEachBin[Det][Bin];
		}
		Tree_NetMu->Fill();
	}
	Tree_NetMu->Write();

	//AdMu
	TFile  *F_AdMu = new TFile("AdMu.root","recreate");
	TTree *Tree_AdMu = new TTree("AdMu","AdMu");
	Tree_AdMu->Branch("AdMu",AdMu,"AdMu[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			AdMu[Det] = AdMuInEachBin[Det][Bin];
		}
		Tree_AdMu->Fill();
	}
	Tree_AdMu->Write();

	//HMuL5
	TFile  *F_HMuL5 = new TFile("HMuL5.root","recreate");
	TTree *Tree_HMuL5 = new TTree("HMuL5","HMuL5");
	Tree_HMuL5->Branch("HMuL5",HMuL5,"HMuL5[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			HMuL5[Det] = HMuL5InEachBin[Det][Bin];
		}
		Tree_HMuL5->Fill();
	}
	Tree_HMuL5->Write();

	//HMuG5
	TFile  *F_HMuG5 = new TFile("HMuG5.root","recreate");
	TTree *Tree_HMuG5 = new TTree("HMuG5","HMuG5");
	Tree_HMuG5->Branch("HMuG5",HMuG5,"HMuG5[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			HMuG5[Det] = HMuG5InEachBin[Det][Bin];
		}
		Tree_HMuG5->Fill();
	}
	Tree_HMuG5->Write();

	//HMuG10
	TFile  *F_HMuG10 = new TFile("HMuG10.root","recreate");
	TTree *Tree_HMuG10 = new TTree("HMuG10","HMuG10");
	Tree_HMuG10->Branch("HMuG10",HMuG10,"HMuG10[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			HMuG10[Det] = HMuG10InEachBin[Det][Bin];
		}
		Tree_HMuG10->Fill();
	}
	Tree_HMuG10->Write();

	//HMuG15
	TFile  *F_HMuG15 = new TFile("HMuG15.root","recreate");
	TTree *Tree_HMuG15 = new TTree("HMuG15","HMuG15");
	Tree_HMuG15->Branch("HMuG15",HMuG15,"HMuG15[8]/D");

	for(int Bin=0; Bin<NumOfBin;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			HMuG15[Det] = HMuG15InEachBin[Det][Bin];
		}
		Tree_HMuG15->Fill();
	}
	Tree_HMuG15->Write();


}