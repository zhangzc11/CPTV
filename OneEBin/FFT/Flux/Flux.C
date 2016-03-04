
const Int_t NumOfDay = 705;//
Double_t FluxIJ[8][NumOfDay];//FluxIJ[i][j] means i-th AD j-th day


void ReadData();

void Flux()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
	const int NumOfBin = 17016;// (EndTime - StartTime)/WidthOfBin;//17016
	Double_t StartTime_Pow = 1324684800.00;//2011-12-24-00:00:00(UTC),the start time of the power data file.

	Double_t Flux_Save[8];

	ReadData();

	FILE* m_outfile = fopen("DayRate.txt", "w");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		fprintf(m_outfile,"%10d",Bin);
		for(int i=0;i<8;i++)
		{
			fprintf(m_outfile,"%10.3f",FluxIJ[i][Bin]);
		}
		fprintf(m_outfile,"\n");
	}
	fclose(m_outfile);

	

   TFile  *Fout = new TFile("Flux.root","recreate");
   TTree *FluxTree = new TTree("Flux","Flux");
   FluxTree->Branch("Flux",Flux_Save,"Flux_Save[8]/D");

   for(int Bin=0;Bin<NumOfBin;Bin++)
  {
	int N_Day = int((Bin*WidthOfBin + StartTime- StartTime_Pow)/86400.0);

	 if(N_Day<0)
	  {
		  N_Day=0;
	  }
	  if(N_Day>NumOfDay -1)
	  {
		  N_Day = NumOfDay-1;
	  }

	for(int Det=0;Det<8;Det++)
	{
		Flux_Save[Det] = FluxIJ[Det][N_Day];
	}

	FluxTree->Fill();
   }
   FluxTree->Write();
	
}

void ReadData()
{
	std::string s;
	//////////read the day rate///////////////////////////////////////////////
	ifstream is_EH1_AD1("../../Input/daily_reactor/AD1DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH1_AD1,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[0][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH1_AD1.close();
	ifstream is_EH1_AD2("../../Input/daily_reactor/AD2DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH1_AD2,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[1][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH1_AD2.close();
	ifstream is_EH2_AD1("../../Input/daily_reactor/AD3DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH2_AD1,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[2][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH2_AD1.close();
	ifstream is_EH2_AD2("../../Input/daily_reactor/AD4DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH2_AD2,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[3][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH2_AD2.close();
	ifstream is_EH3_AD1("../../Input/daily_reactor/AD5DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH3_AD1,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[4][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH3_AD1.close();
	ifstream is_EH3_AD2("../../Input/daily_reactor/AD6DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH3_AD2,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[5][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH3_AD2.close();
	ifstream is_EH3_AD3("../../Input/daily_reactor/AD7DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH3_AD3,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[6][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH3_AD3.close();
	ifstream is_EH3_AD4("../../Input/daily_reactor/AD8DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH3_AD4,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[7][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH3_AD4.close();

}