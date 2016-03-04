

#include <ctime>
#include <cstdlib>

#include <math.h>
#include "TMinuit.h"


double AVEP[3] = {0.985,0.983,0.951455};
const double pi = 3.141592653;

Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds

Double_t StartTime = 1324678393.80705;
Double_t EndTime = 1385769600.00000;

double R[3][24] = {{0.0}};
double RD_R[3][24] = {{0.0}};

int HallID = 0;

TRandom *my_Random = new TRandom(754);


void MC()
{

	Double_t Ratio_t[3];
    TFile *F_Ratio = new TFile("RatioInOneDay.root");
    TTree *Tree_Ratio = (TTree*)F_Ratio->Get("RatioInOneDay");
    Tree_Ratio->SetBranchAddress("RatioInOneDay",Ratio_t);

    for(int N24=0;N24<24;N24++)
    {

        Tree_Ratio->GetEntry(N24);
        for(int Det=0;Det<3;Det++)
        {
            R[Det][N24] = Ratio_t[Det];
        }
    }

	Double_t RD_Ratio_t[3];
    TFile *F_RD_Ratio = new TFile("RD_RatioInOneDay.root");
    TTree *Tree_RD_Ratio = (TTree*)F_RD_Ratio->Get("RD_RatioInOneDay");
    Tree_RD_Ratio->SetBranchAddress("RD_RatioInOneDay",RD_Ratio_t);

    for(int N24=0;N24<24;N24++)
    {

        Tree_RD_Ratio->GetEntry(N24);
        for(int Det=0;Det<3;Det++)
        {
            RD_R[Det][N24] = RD_Ratio_t[Det];
        }
    }

	////////////////////////////////////////////////////////////////////

	double R_Save[3][24],RD_R_Save[3][24];
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<24;j++)
		{
			R_Save[i][j]=R[i][j];
			RD_R_Save[i][j]=RD_R[i][j];
		}
	}


	
	//normal simple-5P fit:
	double normal_5P[3][4];
	double normal_5P_Err[3][4];
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		HallID = Hidx;

/////////////////////
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
   Double_t step[6] = {0.01,0.01,0.01,0.01};
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

   double vRe[4],vRe_E[4];
   for(int i=0;i<4;i++)
   {
	   Double_t v,ev;
	   gMinuit->GetParameter(i,v,ev);
	   normal_5P[Hidx][i] = v;
	   normal_5P_Err[Hidx][i] = ev;
   }
   /////////////////
	}

	//shuffle the simple fit result
	double Shuffle_5P_Mean[3][4]={{0.0}};
	double Shuffle_5P_Sigma[3][4]={{0.0}};

	double Shuffle_5P_E_Mean[3][4]={{0.0}};
	double Shuffle_5P_E_Sigma[3][4]={{0.0}};

	const int nSample = 1000;

	
	//
	
	
	TCanvas *myC[3];
	TCanvas *myC_E[3];

	const char* c_Name[3] = {"C_EH1","C_EH2","C_EH3"};
	const char* file_Name[3] = {"Shuffle/Simple_Shuffle_EH1.root","Shuffle/Simple_Shuffle_EH2.root","Shuffle/Simple_Shuffle_EH3.root"};
	const char* file_Name_2[3] = {"Shuffle/Simple_Shuffle_EH1.pdf","Shuffle/Simple_Shuffle_EH2.pdf","Shuffle/Simple_Shuffle_EH3.pdf"};

	const char* c_Name_E[3] = {"C_EH1_E","C_EH2_E","C_EH3_E"};

	const char* file_Name_E[3] = {"Shuffle/Simple_Shuffle_EH1_E.root","Shuffle/Simple_Shuffle_EH2_E.root","Shuffle/Simple_Shuffle_EH3_E.root"};
	const char* file_Name_E_2[3] = {"Shuffle/Simple_Shuffle_EH1_E.pdf","Shuffle/Simple_Shuffle_EH2_E.pdf","Shuffle/Simple_Shuffle_EH3_E.pdf"};

	double Error_Mean[3]={0.002394,0.00228,0.00393};

	
	
	//A1*sinwt + A2 coswt + A3 sin2wt + A4 cos2wt
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		HallID = Hidx;

	TH1F *hist_A1 = new TH1F("hist - A1","hist - A1",100,-0.03,0.03);
	TH1F *hist_A2 = new TH1F("hist - A2","hist - A2",100,-0.03,0.03);
	TH1F *hist_A3 = new TH1F("hist - A3","hist - A3",100,-0.03,0.03);
	TH1F *hist_A4 = new TH1F("hist - A4","hist - A4",100,-0.03,0.03);


	TH1F *hist_A1_E = new TH1F("hist - A1_E","hist - A1_E",nSample,Error_Mean[Hidx]-0.005,Error_Mean[Hidx]+0.005);//,50,0.00238,0.0024);
	TH1F *hist_A2_E = new TH1F("hist - A2_E","hist - A2_E",nSample,Error_Mean[Hidx]-0.005,Error_Mean[Hidx]+0.005);//,50,0.00238,0.0024);
	TH1F *hist_A3_E = new TH1F("hist - A3_E","hist - A3_E",nSample,Error_Mean[Hidx]-0.005,Error_Mean[Hidx]+0.005);//,50,0.00238,0.0024);
	TH1F *hist_A4_E = new TH1F("hist - A4_E","hist - A4_E",nSample,Error_Mean[Hidx]-0.005,Error_Mean[Hidx]+0.005);//,50,0.00238,0.0024);

	for(int iS=0;iS<nSample;iS++)
	{
	
		for(int N24=0;N24<24;N24++)
		{
			R[Hidx][N24] = my_Random->Gaus(AVEP[Hidx],AVEP[Hidx]*RD_R_Save[Hidx][N24]);
		}

//////////////////////////////////////////////////////////////////////////////////////////
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
   Double_t step[6] = {0.01,0.01,0.01,0.01};
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

   ///////////////////
		}

	myC[Hidx] =  new TCanvas(c_Name[Hidx],c_Name[Hidx],200,10,1200,800);
	myC[Hidx]->Divide(2,2);

	myC[Hidx]->cd(1);
	gStyle->SetOptFit(0001);
	gStyle->SetOptStat(0);
	hist_A1->Draw();
	hist_A1->GetXaxis()->SetLabelSize(0.04);
	hist_A1->GetYaxis()->SetLabelSize(0.06);
	hist_A1->Fit("gaus");

	myC[Hidx]->cd(2);
	hist_A2->Draw();
	hist_A2->GetXaxis()->SetLabelSize(0.04);
	hist_A2->GetYaxis()->SetLabelSize(0.06);
	hist_A2->Fit("gaus");

	myC[Hidx]->cd(3);
	hist_A3->Draw();
	hist_A3->GetXaxis()->SetLabelSize(0.04);
	hist_A3->GetYaxis()->SetLabelSize(0.06);
	hist_A3->Fit("gaus");

	myC[Hidx]->cd(4);
	hist_A4->Draw();
	hist_A4->GetXaxis()->SetLabelSize(0.04);
	hist_A4->GetYaxis()->SetLabelSize(0.06);
	hist_A4->Fit("gaus");

	myC[Hidx]->SaveAs(file_Name[Hidx]);
	myC[Hidx]->SaveAs(file_Name_2[Hidx]);

	myC_E[Hidx] =  new TCanvas(c_Name_E[Hidx],c_Name_E[Hidx],200,10,1200,800);
	//gStyle->SetOptStat(1);
	myC_E[Hidx]->Divide(2,2);
	myC_E[Hidx]->cd(1);
	gStyle->SetOptFit(0001);
	gStyle->SetOptStat(0);
	hist_A1_E->Draw();
	hist_A1_E->GetXaxis()->SetLabelSize(0.041);
	hist_A1_E->GetYaxis()->SetLabelSize(0.06);
	hist_A1_E->Fit("gaus");
	myC_E[Hidx]->cd(2);
	hist_A2_E->Draw();
	hist_A2_E->GetXaxis()->SetLabelSize(0.041);
	hist_A2_E->GetYaxis()->SetLabelSize(0.06);
	hist_A2_E->Fit("gaus");
	myC_E[Hidx]->cd(3);
	hist_A3_E->Draw();
	hist_A3_E->GetXaxis()->SetLabelSize(0.041);
	hist_A3_E->GetYaxis()->SetLabelSize(0.06);
	hist_A3_E->Fit("gaus");
	myC_E[Hidx]->cd(4);
	hist_A4_E->Draw();
	hist_A4_E->GetXaxis()->SetLabelSize(0.041);
	hist_A4_E->GetYaxis()->SetLabelSize(0.06);
	hist_A4_E->Fit("gaus");
	myC_E[Hidx]->SaveAs(file_Name_E[Hidx]);
	myC_E[Hidx]->SaveAs(file_Name_E_2[Hidx]);

	Shuffle_5P_Mean[Hidx][0] = hist_A1->GetMean();
	Shuffle_5P_Mean[Hidx][1] = hist_A2->GetMean();
	Shuffle_5P_Mean[Hidx][2] = hist_A3->GetMean();
	Shuffle_5P_Mean[Hidx][3] = hist_A4->GetMean();

	Shuffle_5P_Sigma[Hidx][0] = hist_A1->GetStdDev();
	Shuffle_5P_Sigma[Hidx][1] = hist_A2->GetStdDev();
	Shuffle_5P_Sigma[Hidx][2] = hist_A3->GetStdDev();
	Shuffle_5P_Sigma[Hidx][3] = hist_A4->GetStdDev();

	Shuffle_5P_E_Mean[Hidx][0] = hist_A1_E->GetMean();
	Shuffle_5P_E_Mean[Hidx][1] = hist_A2_E->GetMean();
	Shuffle_5P_E_Mean[Hidx][2] = hist_A3_E->GetMean();
	Shuffle_5P_E_Mean[Hidx][3] = hist_A4_E->GetMean();

	Shuffle_5P_E_Sigma[Hidx][0] = hist_A1_E->GetStdDev();
	Shuffle_5P_E_Sigma[Hidx][1] = hist_A2_E->GetStdDev();
	Shuffle_5P_E_Sigma[Hidx][2] = hist_A3_E->GetStdDev();
	Shuffle_5P_E_Sigma[Hidx][3] = hist_A4_E->GetStdDev();

	}
	
	cout<<"real vs. shuffle:"<<endl;
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int i=0;i<4;i++)
		{
			fprintf(stderr,"&%6.4f $\\pm$ %6.4f & %6.4f  & %6.4f & %6.4f  & %6.4f \\\\ \n", normal_5P[Hidx][i], normal_5P_Err[Hidx][i],
				Shuffle_5P_Mean[Hidx][i],Shuffle_5P_Sigma[Hidx][i],
				Shuffle_5P_E_Mean[Hidx][i],Shuffle_5P_E_Sigma[Hidx][i]);
		}
	}
	
	

	
}

//A1*sinwt + A2 coswt + A3 sin2wt + A4 cos2wt
Double_t FitFunc_Simple(Double_t x, Double_t *par)
{
	Double_t wP = 2.0*pi/86164.09;//omega plus, sidereal frequency

	return AVEP[HallID]+par[0]*sin(wP*x)+par[1]*cos(wP*x)+par[2]*sin(2.0*wP*x)+par[3]*cos(2.0*wP*x);
}

void ChiSquare_EH1_Simple(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH1
   for (i=0;i<nbins; i++) {
     delta  = (R[0][i]-FitFunc_Simple(i*WidthOfBin,par))/(RD_R[0][i]*R[0][i]);
     chisq += delta*delta;
   }

   f = chisq;
}


void ChiSquare_EH2_Simple(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH2
   for (i=0;i<nbins; i++) {
     delta  = (R[1][i]-FitFunc_Simple(i*WidthOfBin,par))/(RD_R[1][i]*R[1][i]);
     chisq += delta*delta;
   }

   f = chisq;
}

void ChiSquare_EH3_Simple(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH3
   for (i=0;i<nbins; i++) {
     delta  = (R[2][i]-FitFunc_Simple(i*WidthOfBin,par))/(RD_R[2][i]*R[2][i]);
     chisq += delta*delta;
   }

   f = chisq;
}
