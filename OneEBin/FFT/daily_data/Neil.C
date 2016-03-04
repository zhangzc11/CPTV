#include <time.h>
#include<string>
#include<sstream>
#include<iostream>
#include<fstream>
#include<math.h>
#define n_pow 705
//for P12E: 217 days. for summer break: 83 days, for P14A: 405 days

void Neil(){
 
  char ch1[100];
  char ch2[100];
  char ch3[100];
  char ch4[100];
  char ch5[100];
  char ch6[100];
  char ch7[100];
  char ch8[100];
  double wd1[n_pow][8]={0.};
  double wd2[n_pow][8]={0.};
  double wla1[n_pow][8]={0.};
  double wla2[n_pow][8]={0.};
  double wla3[n_pow][8]={0.};
  double wla4[n_pow][8]={0.};
  string date[n_pow];
  double detRate[n_pow][8]={0.};
  double live[n_pow][8]={0.};

  char ch9[100];
  char ch10[100];
  char ch11[100];
  char ch12[100];
  char ch13[100];
  char ch14[100];
  double reactorRate[n_pow][6]={0.};
  double reactorID[n_pow][6]={0.};
  double goodhour[n_pow][6]={0.};

  double baseline[8][6]={{362.3804, 371.7626, 903.4664, 817.1578, 1353.6177, 1265.3153},
                         {357.9404, 368.4142, 903.3467, 816.8962, 1354.2293, 1265.8861},
                         {1332.4793, 1358.1482, 467.574, 489.5774, 557.5792, 499.2072},
                         {1337.4293, 1362.8763, 472.9709, 495.3458, 558.7073, 501.0714},
                         {1919.6319, 1894.3376, 1533.1804, 1533.6275, 1551.3843, 1524.94},
                         {1917.5188, 1891.9765, 1534.9194, 1535.0322, 1554.7671, 1528.046},
                         {1925.255, 1899.8607, 1538.9301, 1539.4683, 1556.3439, 1530.0787},
                         {1923.1489, 1897.5072, 1540.6667, 1540.8715, 1559.721, 1533.1791}};

  strcpy(ch1, "./detectorDailyRate/AD1DayRate.txt");
  cout<<ch1<<endl;
  ifstream det1file(ch1);
  for(int i=0; i<n_pow; i++){
    det1file>>date[i]>>detRate[i][0]>>live[i][0]>>wd1[i][0]>>wd2[i][0]>>wla1[i][0]>>wla2[i][0]>>wla3[i][0]>>wla4[i][0];
  }  
  det1file.close();

  strcpy(ch2, "./detectorDailyRate/AD2DayRate.txt");
  cout<<ch2<<endl;
  ifstream det2file(ch2);
  for(int i=0; i<n_pow; i++){
    det2file>>date[i]>>detRate[i][1]>>live[i][1]>>wd1[i][1]>>wd2[i][1]>>wla1[i][1]>>wla2[i][1]>>wla3[i][1]>>wla4[i][1];
  }  
  det2file.close();

  strcpy(ch3, "./detectorDailyRate/AD3DayRate.txt");
  cout<<ch3<<endl;
  ifstream det3file(ch3);
  for(int i=0; i<n_pow; i++){
    det3file>>date[i]>>detRate[i][2]>>live[i][2]>>wd1[i][2]>>wd2[i][2]>>wla1[i][2]>>wla2[i][2]>>wla3[i][2]>>wla4[i][2];
  }  
  det3file.close();

  strcpy(ch4, "./detectorDailyRate/AD4DayRate.txt");
  cout<<ch4<<endl;
  ifstream det4file(ch4);
  for(int i=0; i<n_pow; i++){
    det4file>>date[i]>>detRate[i][3]>>live[i][3]>>wd1[i][3]>>wd2[i][3]>>wla1[i][3]>>wla3[i][3]>>wla3[i][3]>>wla4[i][3];
  }  
  det4file.close();

  strcpy(ch5, "./detectorDailyRate/AD5DayRate.txt");
  cout<<ch5<<endl;
  ifstream det5file(ch5);
  for(int i=0; i<n_pow; i++){
    det5file>>date[i]>>detRate[i][4]>>live[i][4]>>wd1[i][4]>>wd2[i][4]>>wla1[i][4]>>wla2[i][4]>>wla3[i][4]>>wla4[i][4];
  }  
  det5file.close();

  strcpy(ch6, "./detectorDailyRate/AD6DayRate.txt");
  cout<<ch6<<endl;
  ifstream det6file(ch6);
  for(int i=0; i<n_pow; i++){
    det6file>>date[i]>>detRate[i][5]>>live[i][5]>>wd1[i][5]>>wd2[i][5]>>wla1[i][5]>>wla2[i][5]>>wla3[i][5]>>wla4[i][5];
  }  
  det6file.close();

  strcpy(ch7, "./detectorDailyRate/AD7DayRate.txt");
  cout<<ch7<<endl;
  ifstream det7file(ch7);
  for(int i=0; i<n_pow; i++){
    det7file>>date[i]>>detRate[i][6]>>live[i][6]>>wd1[i][6]>>wd2[i][6]>>wla1[i][6]>>wla2[i][6]>>wla3[i][6]>>wla4[i][6];
  }  
  det7file.close();

  strcpy(ch8, "./detectorDailyRate/AD8DayRate.txt");
  cout<<ch8<<endl;
  ifstream det8file(ch8);
  for(int i=0; i<n_pow; i++){
    det8file>>date[i]>>detRate[i][7]>>live[i][7]>>wd1[i][7]>>wd2[i][7]>>wla1[i][7]>>wla2[i][7]>>wla3[i][7]>>wla4[i][7];
  }  
  det8file.close();

  strcpy(ch9, "./reactorDailyRate/DayaBayA_rate_p14a.txt");
  cout<<ch9<<endl;
  ifstream reactor1file(ch9);
  for(int i=0; i<n_pow; i++){
    reactor1file>>goodhour[i][0]>>reactorID[i][0]>>reactorRate[i][0];
  }  
  reactor1file.close();

  strcpy(ch10, "./reactorDailyRate/DayaBayB_rate_p14a.txt");
  cout<<ch10<<endl;
  ifstream reactor2file(ch10);
  for(int i=0; i<n_pow; i++){
    reactor2file>>goodhour[i][1]>>reactorID[i][1]>>reactorRate[i][1];
  }  
  reactor2file.close();

  strcpy(ch11, "./reactorDailyRate/LingAoIA_rate_p14a.txt");
  cout<<ch11<<endl;
  ifstream reactor3file(ch11);
  for(int i=0; i<n_pow; i++){
    reactor3file>>goodhour[i][2]>>reactorID[i][2]>>reactorRate[i][2];
  }  
  reactor3file.close();

  strcpy(ch12, "./reactorDailyRate/LingAoIB_rate_p14a.txt");
  cout<<ch12<<endl;
  ifstream reactor4file(ch12);
  for(int i=0; i<n_pow; i++){
    reactor4file>>goodhour[i][3]>>reactorID[i][3]>>reactorRate[i][3];
  }  
  reactor4file.close();

  strcpy(ch13, "./reactorDailyRate/LingAoIIA_rate_p14a.txt");
  cout<<ch13<<endl;
  ifstream reactor5file(ch13);
  for(int i=0; i<n_pow; i++){
    reactor5file>>goodhour[i][4]>>reactorID[i][4]>>reactorRate[i][4];
  }  
  reactor5file.close();

  strcpy(ch14, "./reactorDailyRate/LingAoIIB_rate_p14a.txt");
  cout<<ch14<<endl;
  ifstream reactor6file(ch14);
  for(int i=0; i<n_pow; i++){
    reactor6file>>goodhour[i][5]>>reactorID[i][5]>>reactorRate[i][5];
  }  
  reactor6file.close();

  /*
  strcpy(ch2, "./power_20111224_20120727_newGoodHourweighted.txt");
  cout<<ch2<<endl;
  ifstream powfile(ch2);
  stringstream s;
  for(int i=0; i<217; i++){
    powfile>>pdate[i]>>pd1[i]>>pd2[i]>>pla1[i]>>pla2[i]>>pla3[i]>>pla4[i]; 

    s<<pdate[i].substr(0, pdate[i].find("/"));
    //s>>t1.tm_year;
    s>>month;
    s.clear();

    s<<pdate[i].substr(pdate[i].find("/")+1, pdate[i].rfind("/")-pdate[i].find("/")-1);
    //s>>t1.tm_mon;
    s>>day;
    s.clear();

    s<<pdate[i].substr(pdate[i].rfind("/")+1);
    //s>>t1.tm_mday;
    s>>year;
    s.clear();

    //month = t1.tm_mon;
    //day = t1.tm_mday;
    //year = t1.tm_year;
    fpdate[i] = "20"+year+"-"+month+"-"+day;
  }
  powfile.close(); 

  strcpy(ch3, "./power_20120728_20121018_avg.txt");
  cout<<ch3<<endl;
  ifstream powfile(ch3);
  stringstream s;
  for(int i=217; i<300; i++){
    powfile>>pdate[i]>>pd1[i]>>pd2[i]>>pla1[i]>>pla2[i]>>pla3[i]>>pla4[i]; 

    s<<pdate[i].substr(0, pdate[i].find("/"));
    //s>>t1.tm_year;
    s>>month;
    s.clear();

    s<<pdate[i].substr(pdate[i].find("/")+1, pdate[i].rfind("/")-pdate[i].find("/")-1);
    //s>>t1.tm_mon;
    s>>day;
    s.clear();

    s<<pdate[i].substr(pdate[i].rfind("/")+1);
    //s>>t1.tm_mday;
    s>>year;
    s.clear();

    //month = t1.tm_mon;
    //day = t1.tm_mday;
    //year = t1.tm_year;
    fpdate[i] = "20"+year+"-"+month+"-"+day;
  }
  powfile.close(); 

  strcpy(ch4, "./power_20121019_20131227_goodHourWeighted.txt");
  cout<<ch4<<endl;
  ifstream powfile(ch4);
  stringstream s;
  for(int i=300; i<n_pow; i++){
    powfile>>pdate[i]>>pd1[i]>>pd2[i]>>pla1[i]>>pla2[i]>>pla3[i]>>pla4[i]; 

    s<<pdate[i].substr(0, pdate[i].find("/"));
    //s>>t1.tm_year;
    s>>month;
    s.clear();

    s<<pdate[i].substr(pdate[i].find("/")+1, pdate[i].rfind("/")-pdate[i].find("/")-1);
    //s>>t1.tm_mon;
    s>>day;
    s.clear();

    s<<pdate[i].substr(pdate[i].rfind("/")+1);
    //s>>t1.tm_mday;
    s>>year;
    s.clear();

    //month = t1.tm_mon;
    //day = t1.tm_mday;
    //year = t1.tm_year;
    fpdate[i] = "20"+year+"-"+month+"-"+day;
  }
  powfile.close(); 
*/

  /*/////////////////////////////////////////////////////////////////////commented by ZZC on 2014-10-25////////////////////////////////////////////////////////////////
  for(int i=0; i<n_pow; i++){
    //cout<<date[i]<<" "<<detRate[i][5]<<" "<<live[i][5]<<" "<<wd1[i][5]<<" "<<wd2[i][5]<<" "<<wla1[i][5]<<" "<<wla2[i][5]<<" "<<wla3[i][5]<<" "<<wla4[i][5]<<" "<<endl;
    //cout<<i+1<<" "<<goodhour[i][5]<<" "<<reactorID[i][5]<<" "<<reactorRate[i][5]<<endl;
  }

  // f_i = 1/L/L*flux_i*livetime_d
  double fraction[n_pow][8][6]={0};
  double Far1[n_pow]=0;
  double Far2[n_pow]=0;
  double Far3[n_pow]=0;
  double Far4[n_pow]=0;
  double Far[n_pow]=0;
  double A[n_pow]=0;
  double B[n_pow]=0;
  for(int m=0; m<n_pow; m++){
    for(int i=0; i<8; i++)
    {
      for(int j=0; j<6; j++)
      {
          fraction[m][i][j] = 1/baseline[i][j]/baseline[i][j]*reactorRate[m][j]*live[m][i];
   //       fraction[m][i][j] = 1/baseline[i][j]/baseline[i][j]*reactorRate[m][j];
      }
    }
  }

  for(int m=0; m<n_pow; m++){
      for(int j=0; j<6; j++)
      {
        //A1[m] += fraction[m][0][j];
        //A2[m] += fraction[m][1][j];
        A[m] += fraction[m][1][j] + fraction[m][0][j];
        //B1[m] += fraction[m][2][j];
        //B2[m] += fraction[m][3][j];
        B[m] += fraction[m][3][j] + fraction[m][2][j];
        Far1[m] += fraction[m][4][j];
        Far2[m] += fraction[m][5][j];
        Far3[m] += fraction[m][6][j];
        Far4[m] += fraction[m][7][j];
        Far[m] += fraction[m][4][j] + fraction[m][5][j] + fraction[m][6][j] + fraction[m][7][j];
      }
  }

  double temp1[n_pow]={0};
  double temp2[n_pow]={0};
  double temp3[n_pow]={0};
  double temp4[n_pow]={0};
  double tempf[n_pow]={0};
  double temp[n_pow]={0};
  double alpha1[n_pow]={0};
  double beta1[n_pow]={0};
  double alpha2[n_pow]={0};
  double beta2[n_pow]={0};
  double alpha3[n_pow]={0};
  double beta3[n_pow]={0};
  double alpha4[n_pow]={0};
  double beta4[n_pow]={0};
  double alphaf[n_pow]={0};
  double betaf[n_pow]={0};
  
  for(int m=0; m<n_pow; m++)
  { 
    for(int j=0; j<6; j++)
    {
      if(B[m]!=0)
      {
      temp1[m] += (fraction[m][4][j]-Far1[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]))*(fraction[m][0][j]+fraction[m][1][j]-A[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]));
      temp2[m] += (fraction[m][5][j]-Far2[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]))*(fraction[m][0][j]+fraction[m][1][j]-A[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]));
      temp3[m] += (fraction[m][6][j]-Far3[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]))*(fraction[m][0][j]+fraction[m][1][j]-A[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]));
      temp4[m] += (fraction[m][7][j]-Far4[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]))*(fraction[m][0][j]+fraction[m][1][j]-A[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]));
      tempf[m] += (fraction[m][4][j] + fraction[m][5][j] + fraction[m][6][j] + fraction[m][7][j]-Far[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]))*(fraction[m][0][j]+fraction[m][1][j]-A[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]));
      temp[m] += (fraction[m][0][j]+fraction[m][1][j]-A[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]))*(fraction[m][0][j]+fraction[m][1][j]-A[m]/B[m]*(fraction[m][2][j]+fraction[m][3][j]));
      }
      else{
      temp1[m] += 0;
      temp2[m] += 0;
      temp4[m] += 0;
      temp3[m] += 0;
      tempf[m] += 0;
      temp[m] += 0;
      }
      
    }
    alpha1[m] = temp1[m]/temp[m];
    beta1[m] = (Far1[m] - alpha1[m]*A[m])/B[m];
    alpha2[m] = temp2[m]/temp[m];
    beta2[m] = (Far2[m] - alpha2[m]*A[m])/B[m];
    alpha3[m] = temp3[m]/temp[m];
    beta3[m] = (Far3[m] - alpha3[m]*A[m])/B[m];
    alpha4[m] = temp4[m]/temp[m];
    beta4[m] = (Far4[m] - alpha4[m]*A[m])/B[m];
    alphaf[m] = tempf[m]/temp[m];
    betaf[m] = (Far[m] - alphaf[m]*A[m])/B[m];

    cout<<m+1<<" "<<alphaf[m]<<" "<<betaf[m]<<endl;
    //cout<<"day="<<m+1<<" alpha2/alpha1="<<alphaf[m]/alpha1[m]<<" beta2/beta1="<<betaf[m]/beta1[m]<<endl;

  }
  */
  
  ///////////////////////////////only for Neil////////////////////////////////////////////////////////////
  double Z_Flux_Daily_AD[8][n_pow]={0.0};
  for(int DayIdx=0;DayIdx<n_pow;DayIdx++)
  {
  for(int Det=0;Det<8;Det++)
  {
	  for(int Rct=0;Rct<6;Rct++)
	  {
		  Z_Flux_Daily_AD[Det][DayIdx] += reactorRate[DayIdx][Rct]/pow(baseline[Det][Rct],2.0);
	  }
  }
  }
  //save to .root file
  double Flux_Daily_AD_Neil[8];//AD1~AD8
  TFile  *F_Flux_Daily_AD = new TFile("Flux_Daily_AD.root","recreate");
  TTree *Tree_Flux_Daily_AD = new TTree("Flux_Daily_AD","Flux_Daily_AD");
  Tree_Flux_Daily_AD->Branch("Flux_Daily_AD",Flux_Daily_AD_Neil,"Flux_Daily_AD_Neil[8]/D");

  for(int DayIdx=0; DayIdx<n_pow;DayIdx++)
	{
		for(int Det=0;Det<8;Det++)
		{
			Flux_Daily_AD_Neil[Det] = Z_Flux_Daily_AD[Det][DayIdx];
		}
		Tree_Flux_Daily_AD->Fill();
	}
  Tree_Flux_Daily_AD->Write();
  //save to .txt file
   FILE* m_outfile = fopen("Flux_Daily_AD.txt", "w+");
    for(int DayIdx=0; DayIdx<n_pow;DayIdx++)
	{
		fprintf(m_outfile,"%5d",DayIdx);

		for(int Det=0;Det<8;Det++)
		{
			fprintf(m_outfile,"%12.6g",Z_Flux_Daily_AD[Det][DayIdx]);
		}
		fprintf(m_outfile,"\n");
	}
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////For Neil's new formula////////////////////////////////////////////////
  double sin_2_2_13 = 0.0836;//sin^(2\theta_{134})
  double dm_2 = 0.00244;//eV^2
  double E_Bin[12] = {1.88,2.78,3.78,4.78,5.78,6.78,7.78,8.78,9.78,10.78,11.78,12.03};//E, in unit of MeV
  
  double Flux_Adjust[8][12][n_pow]={{{0.0}}};//[Det][E_Bin][DayIdx]
  for(int DayIdx=0;DayIdx<n_pow;DayIdx++)
  {
  for(int Det=0;Det<8;Det++)
  {
	  for(int EIdx=0;EIdx<12;EIdx++)
	  {
		  for(int Rct=0;Rct<6;Rct++)
			{
			 Flux_Adjust[Det][EIdx][DayIdx] += reactorRate[DayIdx][Rct]*(1-sin_2_2_13*pow(sin(1.267*dm_2*baseline[Det][Rct]/E_Bin[EIdx]),2.0))/pow(baseline[Det][Rct],2.0);
			}
	  }
  }
  }
  //save to .root file
  double Flux_Daily_AD_Neil_Adjust[8][12];//AD1~AD8, Energy Bin 0~11
  TFile  *F_Flux_Daily_AD_Adjust = new TFile("Flux_Daily_AD_Adjust.root","recreate");
  TTree *Tree_Flux_Daily_AD_Adjust = new TTree("Flux_Daily_AD_Adjust","Flux_Daily_AD_Adjust");
  Tree_Flux_Daily_AD_Adjust->Branch("Flux_Daily_AD_Adjust",Flux_Daily_AD_Neil_Adjust,"Flux_Daily_AD_Neil_Adjust[8][12]/D");

  for(int DayIdx=0; DayIdx<n_pow;DayIdx++)
	{
		for(int Det=0;Det<8;Det++)
		{
			for(int EIdx=0;EIdx<12;EIdx++)
			{
			Flux_Daily_AD_Neil_Adjust[Det][EIdx] = Flux_Adjust[Det][EIdx][DayIdx];
			}
		}
		Tree_Flux_Daily_AD_Adjust->Fill();
	}
  Tree_Flux_Daily_AD_Adjust->Write();
  //save to .txt file
  FILE* m_outfile_2 = fopen("Flux_Daily_AD_Adjust.txt", "w+");
    for(int DayIdx=0; DayIdx<n_pow;DayIdx++)
	{
		fprintf(m_outfile_2,"%5d",DayIdx);

		for(int Det=0;Det<8;Det++)
		{
			for(int EIdx=0;EIdx<12;EIdx++)
			{
			fprintf(m_outfile_2,"%12.6g",Flux_Adjust[Det][EIdx][DayIdx]);
			}
			fprintf(m_outfile_2,"      ");//the space between different ADs
		}
		fprintf(m_outfile_2,"\n");
	}
  ////////////////daily alpha and beta////////////////////////////////////////////////
  //double Z_Alpha_Daily[n_pow]={0.0};
  //double Z_Beta_Daily[n_pow]={0.0};
  double Z_Alpha[n_pow]={0.0};
  double Z_Beta[n_pow]={0.0};
  const int Z_NumOfBin_FullTime = 16968;
  Double_t Z_FullTime[8][n_pow] = {0.0};
  Double_t Z_FullTime_temp[8];
  Double_t Z_Fraction[3][6][n_pow]={0.0};
  
  Double_t Z_A[n_pow]={0.0};
  Double_t Z_B[n_pow]={0.0};
  Double_t Z_F[n_pow]={0.0};

  //read the fulltime file.

  TFile *F_FullTime = new TFile("FullTime_Solar.root");
  TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
  Tree_FullTime->SetBranchAddress("FullTime",Z_FullTime_temp);

  for(int Bin=0;Bin<Z_NumOfBin_FullTime;Bin++)
  {
	  Tree_FullTime->GetEntry(Bin);
	  int N_Day = int(Bin/24);
	  if(N_Day<n_pow)
	  {
	  for(int Det=0;Det<8;Det++)
	  {
		  Z_FullTime[Det][N_Day] += Z_FullTime_temp[Det];
	  }
	  }
  }

  for(int N_Day=0;N_Day<n_pow;N_Day++)
  {
	  for(int Rct=0;Rct<6;Rct++)
	  {
		  for(int Det=0;Det<2;Det++)
		  {
		  Z_Fraction[0][Rct][N_Day] += reactorRate[N_Day][Rct]*Z_FullTime[Det][N_Day]/pow(baseline[Det][Rct],2.0);
		  }
		  for(int Det=2;Det<4;Det++)
		  {
		  Z_Fraction[1][Rct][N_Day] += reactorRate[N_Day][Rct]*Z_FullTime[Det][N_Day]/pow(baseline[Det][Rct],2.0);
		  }
		  for(int Det=4;Det<8;Det++)
		  {
		  Z_Fraction[2][Rct][N_Day] += reactorRate[N_Day][Rct]*Z_FullTime[Det][N_Day]/pow(baseline[Det][Rct],2.0);
		  }
	  }
  }

   for(int Rct=0;Rct<6;Rct++)
  {
	  for(int Bin=0;Bin<n_pow;Bin++)
	  {
		 Z_A[Bin] += Z_Fraction[0][Rct][Bin];
		 Z_B[Bin] += Z_Fraction[1][Rct][Bin];
		 Z_F[Bin] += Z_Fraction[2][Rct][Bin];
	  }
  }

    //calculate alpha, beta
  for(int Bin=0;Bin<n_pow;Bin++)
  {
	  Double_t alpha_Up=0.0;
	  Double_t alpha_Down=0.0;
	  for(int Rct=0;Rct<6;Rct++)
	  {
		  if(Z_B[Bin]>0)
		  {
		  alpha_Up += (Z_Fraction[2][Rct][Bin] - Z_F[Bin]*Z_Fraction[1][Rct][Bin]/Z_B[Bin])*(Z_Fraction[0][Rct][Bin] - Z_A[Bin]*Z_Fraction[1][Rct][Bin]/Z_B[Bin]);
		  alpha_Down += pow(Z_Fraction[0][Rct][Bin] - Z_A[Bin]*Z_Fraction[1][Rct][Bin]/Z_B[Bin],2.0);
		  }
	  }
	  if(alpha_Down>0)
	  {
	  Z_Alpha[Bin] = alpha_Up/alpha_Down;
	  Z_Beta[Bin] = (Z_F[Bin] - Z_Alpha[Bin]*Z_A[Bin])/Z_B[Bin];
	  }
  }
  //save to .root file
  //hourly alpha and beta
  Double_t AlphaBeta_t[2],Prediction_t[3];

  TFile  *F_AlphaBeta = new TFile("AlphaBeta.root","recreate");
  TTree *Tree_AlphaBeta = new TTree("AlphaBeta","AlphaBeta");
  Tree_AlphaBeta->Branch("AlphaBeta",AlphaBeta_t,"AlphaBeta[2]/D");

  for(int Bin=0; Bin<n_pow;Bin++)
	{
		AlphaBeta_t[0] = Z_Alpha[Bin];
		AlphaBeta_t[1] = Z_Beta[Bin];
		Tree_AlphaBeta->Fill();
	}
  Tree_AlphaBeta->Write();

}

