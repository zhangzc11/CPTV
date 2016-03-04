
#include <ctime>
#include <cstdlib>

#include <math.h>
#include "TMinuit.h"

double RD_Power = 0.009;
double RD_Eff = 0.0013;

const double pi = 3.141592653;

int NumOfBin = 10;
Double_t WidthOfBin = 86164.09/NumOfBin;// 1 sidereal day = 86164.09 seconds8
double Ma[200],Mb[200],Mf[200],Ra[200],Rb[200],Rf[200],RD_Ra[200],RD_Rb[200],RD_Rf[200];

int nSample = 500;

void MC_Bin_Stat()
{
	double Alpha = 0.0536977;
	double Beta = 0.219111;
	double TotalIBD[8] = {306214.0,310759.0,288258.0,190533.0,41224.0,41434.0,40952.0,27560.0};
	double DAQLivetime[8] = {565.436,565.436,568.019,378.407,562.414,562.414,562.414,372.685};
	double MuEff[8] = {0.8274,0.8244,0.8588,0.8586,0.9845,0.9845,0.9843,0.9845};
	double MultiEff[8] = {0.9768,0.9771,0.978,0.9779,0.9778,0.9777,0.9774,0.9781};
	double TotalAcc[8] = {8.77,8.72,6.71,6.71,1.63,1.54,1.52,1.2};
	double TotalFN[8] = {0.78,0.78,0.54,0.54,0.05,0.05,0.05,0.05};
	double TotalLiHe[8] = {2.8+0.23,2.8+0.23,1.7+0.22,1.7+0.11,0.27+0.14,0.27+0.13,0.27+0.13,0.27+0.04};//LiHe+AmC

	for(int Det=0;Det<8;Det++)
	{
		TotalAcc[Det] = TotalAcc[Det]*DAQLivetime[Det];
		TotalFN[Det] = TotalFN[Det]*DAQLivetime[Det];
		TotalLiHe[Det] = TotalLiHe[Det]*DAQLivetime[Det];
	}

	//double RD_Acc[3] = {0.09/8.93, 0.07/6.81, 0.01/1.60};
	//double RD_FN[3] = {0.12/0.78, 0.19/0.54, 0.01/0.05};
	//double RD_LiHe[3] = {0.5,0.5,0.5};
	double RD_Acc[3] = {0.008/4.9,0.01/4.9,0.02/4.9};
	double RD_FN[3] = {0.0002/4.9,0.0002/4.9,0.001/4.9};
	double RD_LiHe[3] = {0.0002/4.9,0.0002/4.9,0.001/4.9};
	//double RD_AmC[3] = {0.5,0.5,0.5};

	double TotalM[3]={0.0};
	for(int Det=0;Det<2;Det++)
	{
		TotalM[0] += TotalIBD[Det]/(MuEff[Det]*MultiEff[Det]) - TotalAcc[Det] - TotalFN[Det] - TotalLiHe[Det];
	}
	for(int Det=2;Det<4;Det++)
	{
		TotalM[1] += TotalIBD[Det]/(MuEff[Det]*MultiEff[Det]) - TotalAcc[Det] - TotalFN[Det] - TotalLiHe[Det];
	}
	for(int Det=4;Det<8;Det++)
	{
		TotalM[2] += TotalIBD[Det]/(MuEff[Det]*MultiEff[Det]) - TotalAcc[Det] - TotalFN[Det] - TotalLiHe[Det];
	}

	double TotalM_MC[3];
	Double_t MeanRatio[3] = {0.0};
	TRandom *myRandom = new TRandom(unsigned(time(0)));
	double Shuffle_5P_Mean[3][4][200];
	double Shuffle_5P_Sigma[3][4][200];

	double Shuffle_5P_E_Mean[3][4][200];
	double Shuffle_5P_E_Sigma[3][4][200];
	double Shuffle_5P_Chi2[3][200];

	FILE* m_outfile = fopen("MCResult.txt", "a");
	FILE* m_outfile2 = fopen("MCResult_Simple.txt", "a");
	///////change NumOfBin////////////////////
	for(int BinN=4; BinN<90;BinN++)
	{
		NumOfBin = BinN;
		//cout<<NumOfBin<<endl;
	WidthOfBin = 86164.09/NumOfBin;

	

	for(int Hidx=0;Hidx<3;Hidx++)
	{
	TH1F *hist_A1 = new TH1F("hist - A1","hist - A1",5000,-1.0,1.0);
	TH1F *hist_A2 = new TH1F("hist - A2","hist - A2",5000,-1.0,1.0);
	TH1F *hist_A3 = new TH1F("hist - A3","hist - A3",5000,-1.0,1.0);
	TH1F *hist_A4 = new TH1F("hist - A4","hist - A4",5000,-1.0,1.0);


	TH1F *hist_A1_E = new TH1F("hist - A1_E","hist - A1_E",5000,-1.0,1.0);
	TH1F *hist_A2_E = new TH1F("hist - A2_E","hist - A2_E",5000,-1.0,1.0);
	TH1F *hist_A3_E = new TH1F("hist - A3_E","hist - A3_E",5000,-1.0,1.0);
	TH1F *hist_A4_E = new TH1F("hist - A4_E","hist - A4_E",5000,-1.0,1.0);

	TH1F *hist_Chi2_Sid	= new TH1F("hist - Chi2","hist - Chi2",5000,0,200.0);

	for(int iS=0;iS<nSample;iS++)
	{

	memset(Ma,0.0,sizeof(Ma));
	memset(Mb,0.0,sizeof(Mb));
	memset(Mf,0.0,sizeof(Mf));
	memset(Ra,0.0,sizeof(Ra));
	memset(Rb,0.0,sizeof(Rb));
	memset(Rf,0.0,sizeof(Rf));
	memset(RD_Ra,0.0,sizeof(RD_Ra));
	memset(RD_Rb,0.0,sizeof(RD_Rb));
	memset(RD_Rf,0.0,sizeof(RD_Rf));
	
	memset(TotalM_MC,0.0,sizeof(TotalM_MC));
	memset(MeanRatio,0.0,sizeof(MeanRatio));

	Double_t Chi2_Sid=0.0;	

	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		Ma[Bin] = myRandom->Gaus(TotalM[0]/NumOfBin,sqrt(TotalM[0]/NumOfBin));
		Mb[Bin] = myRandom->Gaus(TotalM[1]/NumOfBin,sqrt(TotalM[1]/NumOfBin));
		Mf[Bin] = myRandom->Gaus(TotalM[2]/NumOfBin,sqrt(TotalM[2]/NumOfBin));
		TotalM_MC[0] += Ma[Bin];
		TotalM_MC[1] += Mb[Bin];
		TotalM_MC[2] += Mf[Bin];
	}
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		Ma[Bin] = Ma[Bin]*TotalM[0]/TotalM_MC[0];
		Mb[Bin] = Mb[Bin]*TotalM[1]/TotalM_MC[1];
		Mf[Bin] = Mf[Bin]*TotalM[2]/TotalM_MC[2];
		
		/*
		//backgrounds systematic uncertainty gaussian smearing
		Ma[Bin] = Ma[Bin] + 
			(1 - myRandom->Gaus(1.0,RD_Acc[0]))*(TotalAcc[0]+TotalAcc[1])*sqrt(NumOfBin)/NumOfBin +
			(1 - myRandom->Gaus(1.0,RD_FN[0]))*(TotalFN[0]+TotalFN[1])*sqrt(NumOfBin)/NumOfBin +
			(1 - myRandom->Gaus(1.0,RD_LiHe[0]))*(TotalLiHe[0]+TotalLiHe[1])*sqrt(NumOfBin)/NumOfBin;
		Mb[Bin] = Mb[Bin] + 
			(1 - myRandom->Gaus(1.0,RD_Acc[1]))*(TotalAcc[2]+TotalAcc[3])*sqrt(NumOfBin)/NumOfBin +
			(1 - myRandom->Gaus(1.0,RD_FN[1]))*(TotalFN[2]+TotalFN[3])*sqrt(NumOfBin)/NumOfBin +
			(1 - myRandom->Gaus(1.0,RD_LiHe[1]))*(TotalLiHe[2]+TotalLiHe[3])*sqrt(NumOfBin)/NumOfBin;
		Mf[Bin] = Mf[Bin] + 
			(1 - myRandom->Gaus(1.0,RD_Acc[2]))*(TotalAcc[4]+TotalAcc[5]+TotalAcc[6]+TotalAcc[7])*sqrt(NumOfBin)/NumOfBin +
			(1 - myRandom->Gaus(1.0,RD_FN[2]))*(TotalFN[4]+TotalFN[5]+TotalFN[6]+TotalFN[7])*sqrt(NumOfBin)/NumOfBin +
			(1 - myRandom->Gaus(1.0,RD_LiHe[2]))*(TotalLiHe[4]+TotalLiHe[5]+TotalLiHe[6]+TotalLiHe[7])*sqrt(NumOfBin)/NumOfBin;
		//efficiency systematic uncertainty gaussian smearing
		Ma[Bin] = Ma[Bin]*myRandom->Gaus(1.0,RD_Eff);
		Mb[Bin] = Mb[Bin]*myRandom->Gaus(1.0,RD_Eff);
		Mf[Bin] = Mf[Bin]*myRandom->Gaus(1.0,RD_Eff);

		Ra[Bin] = Ma[Bin];
		Rb[Bin] = Mb[Bin];
		Rf[Bin] = Mf[Bin]/(Alpha*Ma[Bin]+Beta*Mb[Bin]);

		//flux systematic uncertainty gaussian smearing
		Ra[Bin] = Ra[Bin]*myRandom->Gaus(1.0,RD_Power*0.572);
		Rb[Bin] = Rb[Bin]*myRandom->Gaus(1.0,RD_Power*0.472);
		Rf[Bin] = Rf[Bin]*myRandom->Gaus(1.0,RD_Power*0.047);

		RD_Ra[Bin] = sqrt(Ma[Bin] + 
			pow(RD_Acc[0]*(TotalAcc[0]+TotalAcc[1])*sqrt(NumOfBin)/NumOfBin,2.0)+
			pow(RD_FN[0]*(TotalFN[0]+TotalFN[1])*sqrt(NumOfBin)/NumOfBin,2.0)+
			pow(RD_LiHe[0]*(TotalLiHe[0]+TotalLiHe[1])*sqrt(NumOfBin)/NumOfBin,2.0)+
			pow(Ma[Bin]*RD_Eff,2.0))/Ma[Bin];
		RD_Rb[Bin] = sqrt(Mb[Bin] + 
			pow(RD_Acc[1]*(TotalAcc[2]+TotalAcc[3])*sqrt(NumOfBin)/NumOfBin,2.0)+
			pow(RD_FN[1]*(TotalFN[2]+TotalFN[3])*sqrt(NumOfBin)/NumOfBin,2.0)+
			pow(RD_LiHe[1]*(TotalLiHe[2]+TotalLiHe[3])*sqrt(NumOfBin)/NumOfBin,2.0)+
			pow(Mb[Bin]*RD_Eff,2.0))/Mb[Bin];
		RD_Rf[Bin] = sqrt(Mf[Bin] + 
			pow(RD_Acc[2]*(TotalAcc[4]+TotalAcc[5]+TotalAcc[6]+TotalAcc[7])*sqrt(NumOfBin)/NumOfBin,2.0)+
			pow(RD_FN[2]*(TotalFN[4]+TotalFN[5]+TotalFN[6]+TotalFN[7])*sqrt(NumOfBin)/NumOfBin,2.0)+
			pow(RD_LiHe[2]*(TotalLiHe[4]+TotalLiHe[5]+TotalLiHe[6]+TotalLiHe[7])*sqrt(NumOfBin)/NumOfBin,2.0)+
			pow(Mf[Bin]*RD_Eff,2.0))/Mf[Bin];

		RD_Rf[Bin] = sqrt(pow(RD_Rf[Bin],2.0)+(pow(Alpha*Ma[Bin]*RD_Ra[Bin],2.0)
			+pow(Beta*Mb[Bin]*RD_Rb[Bin],2.0))/pow(Alpha*Ma[Bin]+Beta*Mb[Bin],2.0)+pow(0.047*RD_Power,2.0));
		RD_Ra[Bin] = sqrt(pow(RD_Ra[Bin],2.0)+pow(RD_Power*0.572,2.0));
		RD_Rb[Bin] = sqrt(pow(RD_Rb[Bin],2.0)+pow(RD_Power*0.472,2.0));
		*/

		Ra[Bin] = Ma[Bin];
		Rb[Bin] = Mb[Bin];
		Rf[Bin] = Mf[Bin]/(Alpha*Ma[Bin]+Beta*Mb[Bin]);

		RD_Ra[Bin] = sqrt(Ma[Bin])/Ma[Bin];
		RD_Rb[Bin] = sqrt(Mb[Bin])/Mb[Bin];
		RD_Rf[Bin] = sqrt(Mf[Bin])/Mf[Bin];
	}

	for(int i=0;i<NumOfBin;i++)
	{
		MeanRatio[0] += Ra[i];
		MeanRatio[1] += Rb[i];
		MeanRatio[2] += Rf[i];
	}
	for(int i=0;i<NumOfBin;i++)
	{
		Ra[i]=NumOfBin*Ra[i]/MeanRatio[0];
		Rb[i]=NumOfBin*Rb[i]/MeanRatio[1];
		Rf[i]=NumOfBin*Rf[i]/MeanRatio[2];
		//cout<<NumOfBin<<"   "<<Ra[i]<<"   "<<RD_Ra[i]<<"   "<<Rb[i]<<"   "<<RD_Rb[i]<<"   "<<Rf[i]<<"   "<<RD_Rf[i]<<"   "<<endl;
	}

	//fit 
	
	//A1*sinwt + A2 coswt + A3 sin2wt + A4 cos2wt

	TMinuit *gMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 5 params

   if(Hidx==0){
	   gMinuit->SetFCN(ChiSquare_EH1_Simple);}
   if(Hidx==1){
	   gMinuit->SetFCN(ChiSquare_EH2_Simple);}
   if(Hidx==2){
	   gMinuit->SetFCN(ChiSquare_EH3_Simple);}

   Double_t arglist[10];
   Int_t ierflg = 0;
   gMinuit->SetPrintLevel(-1);
   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters
   Double_t vstart[6] = {0};
   Double_t step[6] = {0.01,0.01,0.01,0.01,0.01,0.01};
   gMinuit->mnparm(0, "A1", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "A2", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "A3", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "A4", vstart[3], step[3], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 2000;
   arglist[1] = 1.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   //gMinuit->mnprin(3,amin);
   //gMinuit->SetPrintLevel(-1);
   Chi2_Sid = amin;

   double vRe[4],vRe_E[4];
   for(int i=0;i<4;i++)
   {
	   Double_t v,ev;
	   gMinuit->GetParameter(i,v,ev);
	   vRe[i] = v;
	   vRe_E[i] = ev;
   }
   hist_A1->Fill(vRe[0]);
   hist_A2->Fill(vRe[1]);
   hist_A3->Fill(vRe[2]);
   hist_A4->Fill(vRe[3]);

   hist_A1_E->Fill(vRe_E[0]);
   hist_A2_E->Fill(vRe_E[1]);
   hist_A3_E->Fill(vRe_E[2]);
   hist_A4_E->Fill(vRe_E[3]);

   hist_Chi2_Sid->Fill(Chi2_Sid);
   delete gMinuit;
   }
   ///////////////////
    Shuffle_5P_Chi2[Hidx][BinN-4] = hist_Chi2_Sid->GetMean();

    Shuffle_5P_Mean[Hidx][0][BinN-4] = hist_A1->GetMean();
	Shuffle_5P_Mean[Hidx][1][BinN-4] = hist_A2->GetMean();
	Shuffle_5P_Mean[Hidx][2][BinN-4] = hist_A3->GetMean();
	Shuffle_5P_Mean[Hidx][3][BinN-4] = hist_A4->GetMean();

	Shuffle_5P_Sigma[Hidx][0][BinN-4] = hist_A1->GetStdDev();
	Shuffle_5P_Sigma[Hidx][1][BinN-4] = hist_A2->GetStdDev();
	Shuffle_5P_Sigma[Hidx][2][BinN-4] = hist_A3->GetStdDev();
	Shuffle_5P_Sigma[Hidx][3][BinN-4] = hist_A4->GetStdDev();

	Shuffle_5P_E_Mean[Hidx][0][BinN-4] = hist_A1_E->GetMean();
	Shuffle_5P_E_Mean[Hidx][1][BinN-4] = hist_A2_E->GetMean();
	Shuffle_5P_E_Mean[Hidx][2][BinN-4] = hist_A3_E->GetMean();
	Shuffle_5P_E_Mean[Hidx][3][BinN-4] = hist_A4_E->GetMean();

	Shuffle_5P_E_Sigma[Hidx][0][BinN-4] = hist_A1_E->GetStdDev();
	Shuffle_5P_E_Sigma[Hidx][1][BinN-4] = hist_A2_E->GetStdDev();
	Shuffle_5P_E_Sigma[Hidx][2][BinN-4] = hist_A3_E->GetStdDev();
	Shuffle_5P_E_Sigma[Hidx][3][BinN-4] = hist_A4_E->GetStdDev();

	delete hist_A1;
	delete hist_A2;
	delete hist_A3;
	delete hist_A4;
	delete hist_A1_E;
	delete hist_A2_E;
	delete hist_A3_E;
	delete hist_A4_E;
	delete hist_Chi2_Sid;
	}

	fprintf(m_outfile,"Bin Number:............................. %5d \n", BinN);
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int i=0;i<4;i++)
		{
			fprintf(m_outfile,"%8.4f & %8.4f & %8.4f & %8.4f & %8.4f \\\\ \n", Shuffle_5P_Chi2[Hidx][BinN-4],
				Shuffle_5P_Mean[Hidx][i][BinN-4],Shuffle_5P_Sigma[Hidx][i][BinN-4],
				Shuffle_5P_E_Mean[Hidx][i][BinN-4],Shuffle_5P_E_Sigma[Hidx][i][BinN-4]);
		}
	}

	fprintf(stderr,"Bin Number:............................. %5d \n", BinN);
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int i=0;i<4;i++)
		{
			fprintf(stderr,"%8.4f & %8.4f  & %8.4f & %8.4f  & %8.4f \\\\ \n", Shuffle_5P_Chi2[Hidx][BinN-4],
				Shuffle_5P_Mean[Hidx][i][BinN-4],Shuffle_5P_Sigma[Hidx][i][BinN-4],
				Shuffle_5P_E_Mean[Hidx][i][BinN-4],Shuffle_5P_E_Sigma[Hidx][i][BinN-4]);
		}
	}

	}

	// save to root file
	double MC_data_EH1[5],MC_data_EH2[5],MC_data_EH3[5];//error 1234,chi2, 
	//EH1
	TFile  *F_MC_data_EH1 = new TFile("MC_EH1_Stat.root","recreate");
	TTree *Tree_MC_data_EH1 = new TTree("MC_EH1","MC_EH1");
	Tree_MC_data_EH1->Branch("MC_EH1",MC_data_EH1,"MC_data_EH1[5]/D");
	for(int BinN=4; BinN<90;BinN++)
	{
		for(int i=0;i<4;i++)
		{
			MC_data_EH1[i] = Shuffle_5P_Sigma[0][i][BinN-4];
		}
		MC_data_EH1[4]=Shuffle_5P_Chi2[0][BinN-4];

		Tree_MC_data_EH1->Fill();
	}
	Tree_MC_data_EH1->Write();
	//EH2
	TFile  *F_MC_data_EH2 = new TFile("MC_EH2_Stat.root","recreate");
	TTree *Tree_MC_data_EH2 = new TTree("MC_EH2","MC_EH2");
	Tree_MC_data_EH2->Branch("MC_EH2",MC_data_EH2,"MC_data_EH2[5]/D");
	for(int BinN=4; BinN<90;BinN++)
	{
		for(int i=0;i<4;i++)
		{
			MC_data_EH2[i] = Shuffle_5P_Sigma[1][i][BinN-4];
		}
		MC_data_EH2[4]=Shuffle_5P_Chi2[1][BinN-4];

		Tree_MC_data_EH2->Fill();
	}
	Tree_MC_data_EH2->Write();
	//EH3
	TFile  *F_MC_data_EH3 = new TFile("MC_EH3_Stat.root","recreate");
	TTree *Tree_MC_data_EH3 = new TTree("MC_EH3","MC_EH3");
	Tree_MC_data_EH3->Branch("MC_EH3",MC_data_EH3,"MC_data_EH3[5]/D");
	for(int BinN=4; BinN<90;BinN++)
	{
		for(int i=0;i<4;i++)
		{
			MC_data_EH3[i] = Shuffle_5P_Sigma[2][i][BinN-4];
		}
		MC_data_EH3[4]=Shuffle_5P_Chi2[2][BinN-4];

		Tree_MC_data_EH3->Fill();
	}
	Tree_MC_data_EH3->Write();

}

Double_t FitFunc_Simple(Double_t x, Double_t *par)
{
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency
	return 1.0+par[0]*sin(wP*x)+par[1]*cos(wP*x)+par[2]*sin(2.0*wP*x)+par[3]*cos(2.0*wP*x);
}

void ChiSquare_EH1_Simple(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH1
   for (i=0;i<NumOfBin; i++) {
     delta  = (Ra[i]-FitFunc_Simple(i*WidthOfBin,par))/(RD_Ra[i]*Ra[i]);
     chisq += delta*delta;
   }
   f = chisq;
}


void ChiSquare_EH2_Simple(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH2
   for (i=0;i<NumOfBin; i++) {
     delta  = (Rb[i]-FitFunc_Simple(i*WidthOfBin,par))/(RD_Rb[i]*Rb[i]);
     chisq += delta*delta;
   }

   f = chisq;
}

void ChiSquare_EH3_Simple(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH3
   for (i=0;i<NumOfBin; i++) {
     delta  = (Rf[i]-FitFunc_Simple(i*WidthOfBin,par))/(RD_Rf[i]*Rf[i]);
     chisq += delta*delta;
   }

   f = chisq;
}