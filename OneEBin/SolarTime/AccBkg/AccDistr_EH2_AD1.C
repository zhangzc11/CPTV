#include "math.h"

#include <iostream>

double PStart(double Rs, double Rmu, double Tc);
double PNStart(double Rs, double Rmu, double Tc, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );

double TimeEff(double t, int Type, double Lambda_1, double Lambda_2, double a );

double RSStart(double Rs, double Rmu, double Tc);
double RNStart(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a);
double REStart(double Rs, double Rmu, double Tc, double RIBD, double Eff_e);

double RSS(double Rs, double Rmu, double Tc);
double RSS_DYB(double Rs, double Rmu, double Tc);
double REN(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double EffEN_DYB(double Rs, double Rmu, double Tc);

double RS(double Rs, double Rmu, double Tc);
double RE(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double RN(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );

double P_S_E(double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a);
double RSE(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double RES(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );

double RNS(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );

double P_S_EN( double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );

double RSEN(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a);
double RSSS(double Rs, double Rmu, double Tc);
double RESS(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double RNSS(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );
double RS_E_S(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double RS_N_S(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );
double RE_N_S(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );

Double_t  Point_y[24]={0};

void AccDistr_EH2_AD1()
{
	Double_t WidthOfBin		= 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime =   1385769600.00000;
	
	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;

	Int_t ADNo = 0;
	Int_t AD_index = 2;
	const Int_t NumOfRun = 393;
	const Int_t NumOfInfoLine = 14137;
	Double_t Tc = 200.0*1e-6;
	Double_t MultiEffT[8]={1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};

	///////////Acc Per Run information//////////////////////////////////
	Int_t RunID[NumOfRun];
	Double_t AccPerRun[NumOfRun];
	Double_t E_AccPerRun[NumOfRun];

	std::string s;
	ifstream is("Acc_EH2_AD1.txt");
	for(int idx=0;idx<NumOfRun;idx++)
	{
		getline(is,s);

		{
		string subs;
		stringstream ss;
		subs = s.substr(0,15);
		ss<<subs;
		ss>>RunID[idx];
		}

		{
		string subs;
		stringstream ss;
		subs = s.substr(127,16);
		ss<<subs;
		ss>>AccPerRun[idx];
		////coutidx<<"   "<<RunID[idx]<<"   "<<AccPerRun[idx]<<endl;
		}

		{
		string subs;
		stringstream ss;
		subs = s.substr(143,16);
		ss<<subs;
		ss>>E_AccPerRun[idx];
		////coutidx<<"   "<<RunID[idx]<<"   "<<AccPerRun[idx]<<endl;
		}
	}
	is.close();
	/////////////////////////////////////////////////////////////////////////
	//////////////////single's rate information////////////////////////////
	Double_t AccInEachLine[NumOfInfoLine]={0.0};
	Double_t E_AccInEachLine[NumOfInfoLine]={0.0};

	Double_t RunIDInEachLine[NumOfInfoLine];
	Int_t BinIDInEachLine[NumOfInfoLine];
	Double_t WeightInEachLine[NumOfInfoLine]={0.0};
	Double_t AccTotalInEachRun[NumOfInfoLine] = {0.0};
	Double_t E_AccTotalInEachRun[NumOfInfoLine] = {0.0};

	std::string s2;
	ifstream is2("../InfoInEachBin_EH2.txt");
	for(int idx=0;idx<NumOfInfoLine;idx++)
	{ 
		Double_t FullTime,Veto[4],LiveTime,Rs=0.0,Rmu=0.0;
		Double_t NSgUp[4],NSgLow[4],NNet[4];
		getline(is2,s2);

		{
		string subs;
		stringstream ss;
		subs = s2.substr(0,110);//92->95,FullTime
		ss<<subs;
		ss>>RunIDInEachLine[idx];
		////coutRunIDInEachLine[idx]<<endl;
		if(RunIDInEachLine[idx]==0)
		{
			RunIDInEachLine[idx] = RunIDInEachLine[idx-1];
		}
		}

		{
		string subs;
		stringstream ss;
		subs = s2.substr(27,5);//92->95,FullTime
		ss<<subs;
		ss>>BinIDInEachLine[idx];
		}

		{
		string subs;
		stringstream ss;
		subs = s2.substr(92,16);//92->95,FullTime
		ss<<subs;
		ss>>FullTime;
		}
		{
		string subs;
		stringstream ss;
		subs = s2.substr(124,16);//92->95,FullTime
		ss<<subs;
		ss>>Veto[0];
		}
		{
		string subs;
		stringstream ss;
		subs = s2.substr(141,16);//92->95,FullTime
		ss<<subs;
		ss>>Veto[1];
		}
		{
		string subs;
		stringstream ss;
		subs = s2.substr(157,16);//92->95,FullTime
		ss<<subs;
		ss>>Veto[2];
		}
		{
		string subs;
		stringstream ss;
		subs = s2.substr(173,16);//92->95,FullTime
		ss<<subs;
		ss>>Veto[3];
		}

		for(int i=0;i<4;i++)
		{
		string subs;
		stringstream ss;
		subs = s2.substr(189+16*i,16);
		ss<<subs;
		ss>>NSgUp[i];
		}

		for(int i=0;i<4;i++)
		{
		string subs;
		stringstream ss;
		subs = s2.substr(253+16*i,16);
		ss<<subs;
		ss>>NSgLow[i];
		}
		for(int i=0;i<4;i++)
		{
		string subs;
		stringstream ss;
		subs = s2.substr(317+16*i,16);
		ss<<subs;
		ss>>NNet[i];
		}

		LiveTime = FullTime- Veto[ADNo];
		if(LiveTime >0.0001)
		{
		Rs = 0.5*(NSgUp[ADNo]+NSgLow[ADNo])/LiveTime;
		Rmu = NNet[ADNo]/FullTime;
		}
		if(LiveTime >0.0001){
		WeightInEachLine[idx] = FullTime*RSS_DYB(Rs,Rmu,Tc);
		}
		for(int idxRun=0;idxRun<NumOfRun;idxRun++)
		{
			if(RunIDInEachLine[idx]==RunID[idxRun])
			{
				AccTotalInEachRun[idx] = AccPerRun[idxRun];
				E_AccTotalInEachRun[idx] = E_AccPerRun[idxRun];
				break;
			}
		}
		////coutidx<<"   "<<RunIDInEachLine[idx]<<"   "<<NSgUp[ADNo]<<"   "<<NSgLow[ADNo]<<"   "<<FullTime<<"   "<<Veto[ADNo]<<"   "<<LiveTime<<"   "<<WeightInEachLine[idx]<<"   "<<AccTotalInEachRun[idx]<<endl;
	}
	is2.close();

	Double_t TotalWeight = 0.0;
	Int_t idxLine=0;
	Int_t BeginLine=0;
	while(idxLine<NumOfInfoLine)
	{
		TotalWeight += WeightInEachLine[idxLine];
		if(RunIDInEachLine[idxLine+1]!=RunIDInEachLine[idxLine])
		{
			for(int i=BeginLine;i<=idxLine;i++)
			{
				AccInEachLine[i] = WeightInEachLine[i]*AccTotalInEachRun[i]/TotalWeight;
				E_AccInEachLine[i] = sqrt(WeightInEachLine[i]/TotalWeight)*E_AccTotalInEachRun[i];
				////coutE_AccTotalInEachRun[i]<<"   "<<WeightInEachLine[i]<<"   "<<TotalWeight<<endl;
			}
			TotalWeight = 0.0;
			BeginLine = idxLine+1; 
		}
		idxLine ++;
	}
	
	///////////////////NumOfAccInEachBin///////////////////////////////////////////////////
	Double_t *NumOfAccInEachBin = new Double_t[NumOfBin];
	memset(NumOfAccInEachBin,0.0,sizeof(NumOfAccInEachBin));

	Double_t *E2_NumOfAccInEachBin = new Double_t[NumOfBin];
	memset(E2_NumOfAccInEachBin,0.0,sizeof(NumOfAccInEachBin));

	for(int idx=0;idx<NumOfInfoLine;idx++)
	{
		NumOfAccInEachBin[BinIDInEachLine[idx]] += AccInEachLine[idx];
		E2_NumOfAccInEachBin[BinIDInEachLine[idx]] += pow(E_AccInEachLine[idx],2.0);
	}

	//save the  to .root file
	Double_t  NumOfAccInBin;
	TFile  *NumOfAccF = new TFile("NumOfAccInEachBin_EH2_AD1.root","recreate");
	TTree *NumOfAccTree = new TTree("NumOfAccInEachBin","NumOfAccInEachBin");
	NumOfAccTree->Branch("NumOfAccInEachBin",&NumOfAccInBin,"NumOfAccInBin/D");
	for(int i=0;i<NumOfBin;i++)
	{
	////cout<<"   ["<<i<<"]:  "<<NumOfAccInEachBin[i];
	NumOfAccInBin = NumOfAccInEachBin[i]/MultiEffT[AD_index];
	NumOfAccTree->Fill();
	}
	NumOfAccTree->Write();
	NumOfAccF->Close();

	Double_t  E2_NumOfAccInBin;
	TFile  *E2_NumOfAccF = new TFile("E2_NumOfAccInEachBin_EH2_AD1.root","recreate");
	TTree *E2_NumOfAccTree = new TTree("E2_NumOfAccInEachBin","E2_NumOfAccInEachBin");
	E2_NumOfAccTree->Branch("E2_NumOfAccInEachBin",&E2_NumOfAccInBin,"E2_NumOfAccInBin/D");
	for(int i=0;i<NumOfBin;i++)
	{
	
	E2_NumOfAccInBin = E2_NumOfAccInEachBin[i]/pow(MultiEffT[AD_index],2.0);
	E2_NumOfAccTree->Fill();
	//coutNumOfAccInEachBin[i]/MultiEffT[AD_index]<<"   "<<sqrt(E2_NumOfAccInBin)<<endl;
	}
	E2_NumOfAccTree->Write();
	E2_NumOfAccF->Close();



	//live time in one day
	Int_t NumOf24Acc[24]={0};
	Double_t NumOfAccInOneDay;
	TFile  *NumOfAccF2 = new TFile("NumOfAccInOneDay_EH2_AD1.root","recreate");
	TTree *NumOfAccTree2 = new TTree("NumOfAccInOneDay","NumOfAccInOneDay");
	NumOfAccTree2->Branch("NumOfAccInOneDay",&NumOfAccInOneDay,"NumOfAccInOneDay/D");
	for(int i =0;i<NumOfBin;i++)
	{
	Int_t N24 = i%24;
	Point_y[N24] += NumOfAccInEachBin[i]/MultiEffT[AD_index];
	NumOf24Acc[N24] ++;
	}
	Double_t TotalAcc = 0;
	for(int i=0;i<24;i++)
	{
		TotalAcc += Point_y[i];
		NumOfAccInOneDay = Point_y[i];
		NumOfAccTree2->Fill();
	}
	NumOfAccTree2->Write();
	NumOfAccF2->Close();
	cout<<"Total NumOfAcc in EH2_AD1: "<<TotalAcc<<endl;

	////////////////////////////E2
	Int_t E2_NumOf24Acc[24]={0};
	Double_t E2_OneDay[24] = {0.0};
	Double_t E2_NumOfAccInOneDay;
	TFile  *E2_NumOfAccF2 = new TFile("E2_NumOfAccInOneDay_EH2_AD1.root","recreate");
	TTree *E2_NumOfAccTree2 = new TTree("E2_NumOfAccInOneDay","E2_NumOfAccInOneDay");
	E2_NumOfAccTree2->Branch("E2_NumOfAccInOneDay",&E2_NumOfAccInOneDay,"E2_NumOfAccInOneDay/D");
	for(int i =0;i<NumOfBin;i++)
	{
	Int_t N24 = i%24;
	E2_NumOf24Acc[N24] ++;
	E2_OneDay[N24] += E2_NumOfAccInEachBin[i]/pow(MultiEffT[AD_index],2.0);
	}
	for(int i=0;i<24;i++)
	{
		E2_NumOfAccInOneDay = E2_OneDay[i];
		E2_NumOfAccTree2->Fill();
		//coutPoint_y[i]<<"     "<<sqrt(E2_OneDay[i])<<"   "<<E2_NumOf24Acc[i]<<endl;
	}
	E2_NumOfAccTree2->Write();
	E2_NumOfAccF2->Close();

	TCanvas *C_Acc2 = new TCanvas("C_Acc2","C_Acc2",0,0,1000,800);
	TF1 *t_Acc = new TF1("NumOfAcc", GetY, 0, 24, 0);
	t_Acc->SetTitle("NumOfAcc - EH2_AD1");
	t_Acc->GetHistogram()->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	t_Acc->GetHistogram()->GetYaxis()->SetTitle("NumOfAcc in one bin/seconds");
    t_Acc->Draw();
	C_Acc2->SaveAs("NumOfAccInOneDay_EH2_AD1.gif");
	/////////////////////////////////////////////////////////////////////////////////////////////


}

Double_t  GetY(Double_t *x, Double_t *par)
{
	Int_t X_Int;
	if((x[0]>0)&&(x[0]<23.999999999))
	{
		X_Int= int(x[0]);
	}
	else if(x[0]<0)
	{
		X_Int = 0;
	}
	else
	{
		X_Int = 23;
	}
	return Point_y[X_Int];
}

double PStart(double Rs, double Rmu, double Tc)
{
  /// Case a
  double Pa = Rmu / ( Rs + Rmu ) * ( 1 - exp( -(Rs + Rmu) * Tc ) );
  
  /// Case b
  double Pb = exp( -Rs * Tc ) * exp( -Rmu * Tc );

  /// Case c+d
  double Pcd =
      Rs*exp(-Rmu*Tc)*1/(Rs+Rmu)*(1-exp(-(Rs+Rmu)*Tc))
    - Rs*exp(-Rmu*Tc)*1/(2*Rs+Rmu)*(1-exp(-(2*Rs+Rmu)*Tc));

  double Ptot = Pa + Pb + Pcd;

  return Ptot;
}

double PNStart(double Rs, double Rmu, double Tc, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a )
{
  double ret(0);

  if (Type==1){
      /// Case a
      double Pna = Eff_n * Rmu * ( (1- Eff_ne) / ( Rmu + Rs ) *( 1 - exp( -( Rmu + Rs) *Tc)) + Eff_ne / ( Rs + Rmu + Lambda_1) * ( 1 - exp( -(Rmu + Rs + Lambda_1 ) * Tc)) );
      /// Case b
      double Pnb = Eff_n * exp( - (Rmu + Rs) * Tc ) * ( 1 - Eff_ne + Eff_ne * exp(-Lambda_1 * Tc)) ;
      /// Case c
      double Pnc = PStart( Rs, Rmu, Tc) * Eff_n * ( (1 - Eff_ne) * Rs / (Rs + Rmu) * exp(-Rmu * Tc) * ((1 - exp(-Rs * Tc) ) - Rs / (Rmu + 2* Rs) * (1 - exp(-(Rmu + 2 * Rs ) * Tc)) ) 
                  + Eff_ne * (Rmu / (Lambda_1 + 2 * Rmu) * exp( -(Lambda_1 + Rmu) * Tc) + (Lambda_1 + Rmu) / (Lambda_1 + 2*Rmu) * exp( -2 *(Lambda_1 + Rmu) * Tc) ) * Rs / (Rmu +  Rs + Lambda_1 ) * ( (1- exp(- Rs * Tc)) - Rs / (Rmu + 2 * Rs + Lambda_1) * (1 -exp (-(Rmu + 2 * Rs + Lambda_1 ) * Tc) )));	
      /// Case d
      double Pnd = PStart( Rs, Rmu, Tc) * Eff_n * Eff_ne * Lambda_1 / (Lambda_1 + Rmu)  * exp( -(Lambda_1 + Rmu) * Tc) * (1 - exp( -Rs * Tc ) - Rs / (Lambda_1  + Rs + Rmu) * ( 1 - exp( -(Lambda_1 + Rmu + Rs) * Tc)) )  
                  + PStart( Rs, Rmu, Tc) * Eff_n * Eff_ne * Rs / (Rmu + Rs) *(Lambda_1 / (Lambda_1 + Rs) * (1 - exp(-(Rs + Lambda_1 ) * Tc) ) - Lambda_1 / (Lambda_1 + Rmu + 2* Rs) * (1 - exp(-(Rmu + 2 * Rs + Lambda_1 ) * Tc) ));

      double Pntot = Pna + Pnb + Pnc + Pnd;
      
      ret = Pntot;
  }

  return ret;
}

double TimeEff(double t, int Type, double Lambda_1, double Lambda_2, double a )
{
  double ret;
  if (Type == 1) {  
    double TimeEff = 1 - exp( -Lambda_1 * t);
    ret = TimeEff;
  }
  if (Type == 2) {  
    double TimeEff = 1 - ( 1 + a) * exp( -Lambda_1 * t) + a * exp( -Lambda_2 * t);      
    ret = TimeEff;
  }
  return ret;
}

double RSStart(double Rs, double Rmu, double Tc)
{
  double RSStart = Rs * PStart( Rs, Rmu, Tc);
  return RSStart;
}

double RNStart(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a)
{
  double RNStart = RIBD * PNStart( Rs, Rmu, Tc, Eff_n, Eff_ne, Type, Lambda_1,Lambda_2, a);
  return RNStart;
}

double REStart(double Rs, double Rmu, double Tc, double RIBD, double Eff_e)
{
  double REStart = RIBD * Eff_e * PStart( Rs, Rmu, Tc);
  return REStart;
}

double RSS(double Rs, double Rmu, double Tc)
{
  double RSS = RSStart( Rs, Rmu, Tc) * ( Rs*Tc *exp(-Rs*Tc) );
  return RSS;
}

/* Remove 1 us for the length of the realistic dayabay readout window */
double RSS_DYB(double Rs, double Rmu, double Tc)
{
  double RSS = RSStart( Rs, Rmu, Tc ) * Rs * (Tc-1e-6) * exp( -Rs * (Tc-1e-6) );
  return RSS;
}

double REN(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a )
{
  double REN = REStart( Rs, Rmu, Tc, RIBD, Eff_e) * Eff_en * TimeEff( Tc, Type, Lambda_1,Lambda_2, a ) *exp(-Rs*Tc) ;
  return REN;
}

/* Remove 1 us for the length of the realistic dayabay readout window */
double EffEN_DYB(double Rs, double Rmu, double Tc)
{
  /// REN with RIBD=1, Eff_e=1, Eff_en=1, TimeEff is separated and applied outside.
  double REN = REStart( Rs, Rmu, Tc, 1, 1) * exp( -Rs*(Tc-1e-6));
  return REN;
}

double RS(double Rs, double Rmu, double Tc)
{
  double RS = RSStart( Rs, Rmu, Tc) *  exp( -Rs * Tc ) ;
  return RS;
}

double RE(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a )
{
  double RE = REStart( Rs, Rmu, Tc, RIBD, Eff_e) * exp( -Rs*Tc ) *(1-Eff_en * TimeEff(Tc,Type,Lambda_1,Lambda_2,a));
  return RE;
}
double RN(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a )
{
  double RN = RNStart( Rs, Rmu, Tc, RIBD, Eff_n, Eff_ne, Type,Lambda_1,Lambda_2, a) *  exp( -Rs*Tc ) ;
  return RN;
}

double P_S_E(double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a)
{
  double ret;
  if (Type==1){ 
    double P_S_E = Eff_e * ( 1 - Eff_en) * (1 - exp(- RIBD * Tc)) +  Eff_e * Eff_en * RIBD / ( Lambda_1 - RIBD) * ( exp(-RIBD * Tc) - exp( -Lambda_1 * Tc) );
    ret = P_S_E;
  }
  /*  if Type==2{ 
      double P_S_E =RIBD * Eff_e (Tc - Eff_en(T-(1+a) / Lambda_1 * (1 - exp(-Lambda_1 * Tc)) + a / Lambda_2 * ( 1 - exp( -Lambda_2 * Tc)) )) ;
      }	*/
  return ret;
}

double RSE(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a )
{
  
  double RSE = RSStart( Rs, Rmu, Tc) * P_S_E(Tc, RIBD, Eff_e,  Eff_en, Type, Lambda_1, Lambda_2,a) *  exp( -Rs*Tc );
  return RSE;
}

double RSN(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a )
{
  /// Case a
  double RSNa = Rs * Eff_n * RIBD * Rmu * exp(-Rs * Tc ) /( RIBD + Lambda_1) * (1-exp(-( RIBD + Lambda_1) * Tc)) * ((1-Eff_ne) /( Rmu + Rs ) * (1-exp(-( Rmu + Rs) * Tc)) + Eff_ne / (Rmu + Rs + Lambda_1) * (1-exp(-( Rmu + Rs + Lambda_1) * Tc)));
  
  /// Case b
  double RSNb = Rs * Eff_n * exp(-Rmu * Tc) * exp(-2* Rs * Tc) * (1-Eff_ne + Eff_ne * exp(-Lambda_1 * Tc)) * RIBD /( Lambda_1 + RIBD) * (1-exp(-( Lambda_1 + RIBD) * Tc));
  
  /// Case c
  double RSNc = 
    Rs * Eff_n * Eff_ne * RIBD * Rs * exp(-(Rmu + Rs) * Tc) / (Lambda_1 + RIBD) / (2* Rs + Rmu) * (1-exp(-(Lambda_1 + RIBD) * Tc)) * ((1-exp(-Lambda_1 * Tc)) - Lambda_1 / (2* Rs + Rmu + Lambda_1) * (1-exp(-(2* Rs + Rmu + Lambda_1) * Tc )));
  
  double RSN = RSNa + RSNb + RSNc;
  return RSN;
}

double RES(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a )
{
  double RES = REStart( Rs, Rmu, Tc, RIBD, Eff_e) * ( Rs*Tc * exp( -Rs*Tc ) ) *(1-Eff_en * TimeEff(Tc,Type,Lambda_1,Lambda_2,a));
  return RES;
}

double RNS(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a )
{
  double RNS = RNStart( Rs, Rmu, Tc, RIBD, Eff_n, Eff_ne, Type,Lambda_1,Lambda_2,a ) *  (Rs*Tc *exp( -Rs*Tc )) ;
  return RNS;
}

double P_S_EN( double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a )
{  
  double ret;
  if (Type==1){ 
    double P_S_EN = Eff_e * Eff_en * ( 1 - exp(-RIBD * Tc )- RIBD / (Lambda_1 + RIBD) * ( exp( -RIBD * Tc ) - exp( -Lambda_1 * Tc)) ) ;
    ret = P_S_EN;
  }
  /* if (Type==2){ 
     double P_S_EN =RIBD * Eff_e * Eff_en * (T-(1+a) / Lambda_1 * (1 - exp(-Lambda_1 * Tc)) + a / Lambda_2 * ( 1 - exp( -Lambda_2 * Tc)) ) ;
   return P_S_EN;
     }	*/ 
  return ret;
}

double RSEN(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a)
{
  
  double RSEN = RSStart( Rs, Rmu, Tc) *  P_S_EN(Tc, RIBD, Eff_e,  Eff_en, Type, Lambda_1,Lambda_2, a) *  exp( -Rs*Tc );
  return RSEN;
}

double RSSS(double Rs, double Rmu, double Tc)
{
  double RSSS = RSStart( Rs, Rmu, Tc) * ( Rs*Tc * Rs * Tc /2 *exp(-Rs*Tc) );
  return RSSS;
}
double RESS(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a )
{
  double RESS = REStart( Rs, Rmu, Tc, RIBD, Eff_e) * ( Rs*Tc* Rs * Tc /2 * exp( -Rs*Tc ) ) *(1-Eff_en * TimeEff(Tc,Type,Lambda_1,Lambda_2,a));
  return RESS;
}

double RNSS(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a )
{
  double RNSS = RNStart( Rs, Rmu, Tc, RIBD, Eff_n, Eff_ne, Type,Lambda_1,Lambda_2,a ) *  (Rs*Tc* Rs * Tc /2 *exp( -Rs*Tc )) ;
  return RNSS;
}

double RS_E_S(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a )
{
  //RS_E_S=RSES+RSSE;	 
  double RS_E_S = RSStart( Rs, Rmu, Tc) * P_S_E(Tc, RIBD, Eff_e,  Eff_en, Type, Lambda_1,Lambda_2, a) * (Rs*Tc* exp( -Rs*Tc));
  return RS_E_S;
}
double RS_N_S(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a )
{
  //RS_N_S=RSNS+RSSN;	 
  double RS_N_S = RSN(Rs, Rmu, Tc, RIBD, Eff_n,  Eff_ne, Type, Lambda_1,Lambda_2, a) * (Rs*Tc);
  return RS_N_S;
}

double RE_N_S(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a )
{
  //RE_N_S=RENS+RESN;
  double RE_N_S = REStart( Rs, Rmu, Tc, RIBD, Eff_e) * Eff_en * TimeEff( Tc, Type, Lambda_1,Lambda_2, a ) * (Rs*Tc* exp( -Rs*Tc));
  return RE_N_S;
}
double RsExtra(double Rs, double Rmu, double Tc)
{//The extra Rs on live time;
  double RsExtra = Rs * (Tc * exp(- Rmu * Tc ) - (1/Rmu -Tc ) * (1-exp(- Rmu * Tc ) ) ) * RSStart( Rs, Rmu, Tc);
  return RsExtra;
}
double RsLT(double Rs, double Rmu, double Tc)
{//Rs on live time;
  double RsLT =(1+ Tc * Rs ) * RSStart( Rs, Rmu, Tc);
  return RsLT;
}
