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

void AccPerRun_EH2_AD1()
{
	Double_t WidthOfBin		= 86164.00/24.00;	// 1 sidereal day = 86164 seconds
	Double_t StartTime = 1350096800.51364;//in unit of second,it stands for 2011-12-24 00:00:00, UTC 0 time;
	Double_t EndTime =   1385769600;//in unit of second,it stands for 2012-07-28 00:00:00, UTC 0 time;
	
	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;

	Double_t *NumOfAccInEachBin = new Double_t[NumOfBin];
	memset(NumOfAccInEachBin,0.0,sizeof(NumOfAccInEachBin));
	Double_t MultiEffT[8]={1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};

	Int_t AD_index = 2;//AD1

	//Int_t Run; /*0*/
	//Double_t Run,/*0*/ StartSec,/*2*/ StartNano,/*3*/ StopSec, /*4*/ StopNano, /*5*/ FullTime,/*6*/  Veto,/*7*/   NNet, /*24*/ NSgUp, /*28*/ NSgLow,/*29*/ NBVtx,/*64*/  NAeng; /*72*/
	Double_t Variable[12]={0.0};
	Int_t Position[12]={0,2,3,4,5,6,7,24,28,29,64,72};
	Double_t LiveTime,Rs,Rmu,Tc,Acc,E_Acc;
	Tc=200*1e-6;
	Double_t TotalAcc = 0.0;

	std::string s;
	ifstream is("../../Input/P14A_Info/eff_info_EH2.txt");
	while(!is.eof())
	{
		int startN[75]={0},endN[75]={0},pos=0,num=0;
		bool InNumber = false;
		Double_t Time1,Time2,AccRatio;
		Int_t BinID1,BinID2;
		getline(is,s);
		//cout<<"0";
		while(num<75)
		{
			//cout<<"1";
		int n = s.find(char(32),pos);
		if(n>pos)
		{
		if((n==(pos+1))&&(!InNumber)){
		startN[num]=pos;
		endN[num]=pos;
		num ++;
		}
		else if((n>(pos+1))&&(!InNumber))
		{
		InNumber = true;
		startN[num]=pos;
		}
		else if((n==(pos+1))&&(InNumber))
		{
		endN[num]=pos;
		num ++;
		InNumber = false;
		}
		else {}
		}
		pos ++;
		}
		for(int i=0;i<12;i++)
		{
		stringstream ss;
		string subs;	
		subs = s.substr(startN[Position[i]],endN[Position[i]]-startN[Position[i]]+1);
		ss<<subs;
		ss>>Variable[i];
		}
		//0            1			2				3				4				5				6			7			8				9			10				11
		//Run,/*0*/ StartSec,/*2*/ StartNano,/*3*/ StopSec, /*4*/ StopNano, /*5*/ FullTime,/*6*/  Veto,/*7*/   NNet, /*24*/ NSgUp, /*28*/ NSgLow,/*29*/ NBVtx,/*64*/  NAeng; /*72*/

		LiveTime = Variable[5] - Variable[6];
		Rs = 0.5*(Variable[8]+Variable[9])/LiveTime;
		Rmu = Variable[7]/Variable[5];
		Acc = (Variable[5])*RSS_DYB(Rs,Rmu,Tc)*Variable[11]/Variable[10];

		if(Variable[11]>0)
		{
		E_Acc = Acc * sqrt(1.0/Variable[11] - 1.0/Variable[10] + pow((2.0/Rs-2*Tc)*Rs/sqrt(Variable[8]+Variable[9]),2.0));
		}
		else
		{
			E_Acc = 0.0;
		}

		FILE* m_outfile = fopen("Acc_EH2_AD1.txt", "a");
		//[Run][StartSec][StopSec][StopNano][FullTime][Veto][LiveTime][Acc]
		fprintf(m_outfile,
	  "%15.0f %15.0f %15.0f %15.0f %15.0f %15.5f %15.5f %15.5f %15.5f %15.5f     ",
	  Variable[0],Variable[1],Variable[2],Variable[3],Variable[4],Variable[5],Variable[6],LiveTime,Acc,E_Acc
	  );
		fprintf(m_outfile,"\n");
		fclose(m_outfile);
	}}

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
