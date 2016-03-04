

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



void MC_Chi2()
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

	double Chi2_Flat_Real[3];
	double Chi2_Sid_Real[3];

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

   Chi2_Sid_Real[Hidx] = amin;
   //gMinuit->mnprin(3,amin);
   //gMinuit->SetPrintLevel(-1);
   /////////////////
	}

	//const fit
	for(int Hidx=0;Hidx<3;Hidx++)
	{
/////////////////////
   TMinuit *gMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 5 params
   if(Hidx==0){
	   gMinuit->SetFCN(ChiSquare_EH1_Const);}
   if(Hidx==1){
	   gMinuit->SetFCN(ChiSquare_EH2_Const);}
   if(Hidx==2){
	   gMinuit->SetFCN(ChiSquare_EH3_Const);}

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

   Chi2_Flat_Real[Hidx] = amin;
   //gMinuit->mnprin(3,amin);
   //gMinuit->SetPrintLevel(-1);
   ///const fit
   /////////////////
	}


	//shuffle the simple fit result
	double Shuffle_5P_Mean[3][4];
	double Shuffle_5P_Sigma[3][4];

	double Shuffle_5P_E_Mean[3][4];
	double Shuffle_5P_E_Sigma[3][4];

	const int nSample = 1000;
	
	

	TCanvas *myC_Flat[3];
	TCanvas *myC_Sid[3];
	TCanvas *myC_E[3];

	const char* c_Name_Flat[3] = {"EH1_Flat","EH2_Flat","EH3_Flat"};
	const char* c_Name_Sid[3] = {"EH1_Sid","EH2_Sid","EH3_Sid"};

	const char* file_Name_Flat[3] = {"Shuffle/Chi2One/Simple_Shuffle_EH1_Flat.root","Shuffle/Chi2One/Simple_Shuffle_EH2_Flat.root","Shuffle/Chi2One/Simple_Shuffle_EH3_Flat.root"};
	const char* file_Name_2_Flat[3] = {"Shuffle/Chi2One/Simple_Shuffle_EH1_Flat.pdf","Shuffle/Chi2One/Simple_Shuffle_EH2_Flat.pdf","Shuffle/Chi2One/Simple_Shuffle_EH3_Flat.pdf"};

	const char* file_Name_Sid[3] = {"Shuffle/Chi2One/Simple_Shuffle_EH1_Sid.root","Shuffle/Chi2One/Simple_Shuffle_EH2_Sid.root","Shuffle/Chi2One/Simple_Shuffle_EH3_Sid.root"};
	const char* file_Name_2_Sid[3] = {"Shuffle/Chi2One/Simple_Shuffle_EH1_Sid.pdf","Shuffle/Chi2One/Simple_Shuffle_EH2_Sid.pdf","Shuffle/Chi2One/Simple_Shuffle_EH3_Sid.pdf"};

	double Error_Mean[3]={0.002392,0.002441,0.0041};


	TH1F *hist_Chi2_Flat[3];		
	TH1F *hist_Chi2_Sid[3];			
	TH1F *hist_Chi2_Real_Flat[3];	
	TH1F *hist_Chi2_Real_Sid[3];	
	TLegend *leg_Flat[3];
	TLegend *leg2_Flat[3];
	TLegend *leg_Sid[3];
	TLegend *leg2_Sid[3];

	const char* chi2_Name_Flat_MC[3] = {"EH1_Chi2 flat - MC","EH2_Chi2 flat - MC","EH3_Chi2 flat - MC"};
	const char* chi2_Name_Sid_MC[3] = {"EH1_Chi2 sid - MC","EH2_Chi2 sid - MC","EH3_Chi2 sid - MC"};

	const char* chi2_Name_Flat_Real[3] = {"EH1_Chi2 flat - Real","EH2_Chi2 flat - Real","EH3_Chi2 flat - Real"};
	const char* chi2_Name_Sid_Real[3] = {"EH1_Chi2 sid - Real","EH2_Chi2 sid - Real","EH3_Chi2 sid - Real"};


	//A1*sinwt + A2 coswt + A3 sin2wt + A4 cos2wt
	for(int Hidx=0;Hidx<3;Hidx++)
	{
		HallID = Hidx;

	hist_Chi2_Flat[Hidx]		= new TH1F(chi2_Name_Flat_MC[Hidx],chi2_Name_Flat_MC[Hidx],50,0,40.0);
	hist_Chi2_Sid[Hidx]			= new TH1F(chi2_Name_Sid_MC[Hidx],chi2_Name_Sid_MC[Hidx],50,0,40.0);
	hist_Chi2_Real_Flat[Hidx]	= new TH1F(chi2_Name_Flat_Real[Hidx],chi2_Name_Flat_Real[Hidx],nSample,0,40.0);
	hist_Chi2_Real_Sid[Hidx]	= new TH1F(chi2_Name_Sid_Real[Hidx],chi2_Name_Sid_Real[Hidx],nSample,0,40.0);

	for(int iS=0;iS<nSample;iS++)
	{
		//cout<<iS<<endl;
		Double_t Chi2_Flat=0.0;	
		Double_t Chi2_Sid=0.0;	

		for(int N24=0;N24<24;N24++)
		{
			R[Hidx][N24] = my_Random->Gaus(AVEP[Hidx],AVEP[Hidx]*RD_R_Save[Hidx][N24]);
		}

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
   //hist_Chi2->Fill(amin);
   Chi2_Sid = amin;

   ////////////////const fit
   TMinuit *gMinuit_const = new TMinuit(4);  //initialize TMinuit with a maximum of 5 params
   if(Hidx==0){
	   gMinuit_const->SetFCN(ChiSquare_EH1_Const);}
   if(Hidx==1){
	   gMinuit_const->SetFCN(ChiSquare_EH2_Const);}
   if(Hidx==2){
	   gMinuit_const->SetFCN(ChiSquare_EH3_Const);}

   Double_t arglist_const[10];
   Int_t ierflg_const = 0;
   gMinuit_const->SetPrintLevel(-1);
   arglist_const[0] = 1;
   gMinuit_const->mnexcm("SET ERR", arglist_const ,1,ierflg_const);

// Set starting values and step_const sizes for parameters
   Double_t vstart_const[6] = {0};
   Double_t step_const[6] = {0.01,0.01,0.01,0.01};
   gMinuit_const->mnparm(0, "A1", vstart_const[0], step_const[0], 0,0,ierflg_const);
   gMinuit_const->mnparm(1, "A2", vstart_const[1], step_const[1], 0,0,ierflg_const);
   gMinuit_const->mnparm(2, "A3", vstart_const[2], step_const[2], 0,0,ierflg_const);
   gMinuit_const->mnparm(3, "A4", vstart_const[3], step_const[3], 0,0,ierflg_const);

// Now ready for minimization step_const
   arglist_const[0] = 2000;
   arglist_const[1] = 1.;
   gMinuit_const->mnexcm("MIGRAD", arglist_const ,2,ierflg_const);

// Print results
   Double_t amin_const,edm_const,errdef_const;
   Int_t nvpar_const,nparx_const,icstat_const;
   gMinuit_const->mnstat(amin_const,edm_const,errdef_const,nvpar_const,nparx_const,icstat_const);
   //gMinuit_const->mnprin(3,amin_const);
   //gMinuit_const->SetPrintLevel(-1);
   //hist_Chi2->Fill(amin_const);
   Chi2_Flat = amin_const;
   
   hist_Chi2_Flat[Hidx]->Fill(Chi2_Flat);
   hist_Chi2_Sid[Hidx]->Fill(Chi2_Sid);

	}

	for(int i=0;i<400;i++)
	{
		hist_Chi2_Real_Flat[Hidx]->Fill(Chi2_Flat_Real[Hidx]);
		hist_Chi2_Real_Sid[Hidx]->Fill(Chi2_Sid_Real[Hidx]);
	}

	myC_Flat[Hidx] =  new TCanvas(c_Name_Flat[Hidx],c_Name_Flat[Hidx],200,10,800,600);
	gStyle->SetOptStat(0);
	hist_Chi2_Flat[Hidx]->Draw();
	//hist_Chi2->GetYaxis()->SetUserRange(0,400);
	hist_Chi2_Flat[Hidx]->SetLineColor(kBlue);
	hist_Chi2_Flat[Hidx]->SetLineWidth(3);
	hist_Chi2_Flat[Hidx]->GetXaxis()->SetLabelSize(0.05);
	hist_Chi2_Flat[Hidx]->GetXaxis()->SetTitle("#chi^{2}_{Flat}");
	hist_Chi2_Flat[Hidx]->GetYaxis()->SetLabelSize(0.04);
	hist_Chi2_Flat[Hidx]->GetYaxis()->SetTitle("Entries");

	hist_Chi2_Flat[Hidx]->GetYaxis()->SetTitleOffset(0.9);
	hist_Chi2_Flat[Hidx]->GetYaxis()->SetTitleSize(0.05);
	hist_Chi2_Flat[Hidx]->GetXaxis()->SetTitleOffset(0.8);
	hist_Chi2_Flat[Hidx]->GetXaxis()->SetTitleSize(0.05);

	hist_Chi2_Flat[Hidx]->SetTitle("");
	hist_Chi2_Real_Flat[Hidx]->Draw("same");
	hist_Chi2_Real_Flat[Hidx]->SetLineColor(kRed);
	hist_Chi2_Real_Flat[Hidx]->SetLineWidth(3);
	hist_Chi2_Real_Flat[Hidx]->SetTitle("");
	leg_Flat[Hidx] = new TLegend(0.6, 0.75, 0.9, 0.9);
	leg_Flat[Hidx]->AddEntry(hist_Chi2_Flat[Hidx],"MC","l");
	leg_Flat[Hidx]->AddEntry(hist_Chi2_Real_Flat[Hidx],"Data","l");
	leg_Flat[Hidx]->SetFillStyle(0);
	leg_Flat[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
	leg_Flat[Hidx]->Draw();

	leg2_Flat[Hidx] = new TLegend(0.5, 0.5, 0.9, 0.7);
	leg2_Flat[Hidx]->AddEntry(hist_Chi2_Flat[Hidx],c_Name_Flat[Hidx],"");
	leg2_Flat[Hidx]->SetFillStyle(0);
	leg2_Flat[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
	leg2_Flat[Hidx]->Draw();
	//myC_Flat[Hidx]->SaveAs(file_Name_2_Flat[Hidx]);
		////////////
	myC_Sid[Hidx] =  new TCanvas(c_Name_Sid[Hidx],c_Name_Sid[Hidx],200,10,800,600);
	gStyle->SetOptStat(0);
	hist_Chi2_Sid[Hidx]->Draw();
	//hist_Chi2->GetYaxis()->SetUserRange(0,400);
	hist_Chi2_Sid[Hidx]->SetLineColor(kBlue);
	hist_Chi2_Sid[Hidx]->SetLineWidth(3);
	hist_Chi2_Sid[Hidx]->GetXaxis()->SetLabelSize(0.05);
	hist_Chi2_Sid[Hidx]->GetXaxis()->SetTitle("#chi^{2}_{Sid}");
	hist_Chi2_Sid[Hidx]->GetYaxis()->SetLabelSize(0.04);
	hist_Chi2_Sid[Hidx]->GetYaxis()->SetTitle("Entries");

	hist_Chi2_Sid[Hidx]->GetYaxis()->SetTitleOffset(0.9);
	hist_Chi2_Sid[Hidx]->GetYaxis()->SetTitleSize(0.05);
	hist_Chi2_Sid[Hidx]->GetXaxis()->SetTitleOffset(0.8);
	hist_Chi2_Sid[Hidx]->GetXaxis()->SetTitleSize(0.05);

	hist_Chi2_Sid[Hidx]->SetTitle("");
	hist_Chi2_Real_Sid[Hidx]->Draw("same");
	hist_Chi2_Real_Sid[Hidx]->SetLineColor(kRed);
	hist_Chi2_Real_Sid[Hidx]->SetLineWidth(3);
	hist_Chi2_Real_Sid[Hidx]->SetTitle("");
	leg_Sid[Hidx] = new TLegend(0.6, 0.75, 0.9, 0.9);
	leg_Sid[Hidx]->AddEntry(hist_Chi2_Sid[Hidx],"MC","l");
	leg_Sid[Hidx]->AddEntry(hist_Chi2_Real_Sid[Hidx],"Data","l");
	leg_Sid[Hidx]->SetFillStyle(0);
	leg_Sid[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
	leg_Sid[Hidx]->Draw();

	leg2_Sid[Hidx] = new TLegend(0.5, 0.5, 0.9, 0.7);
	leg2_Sid[Hidx]->AddEntry(hist_Chi2_Sid[Hidx],c_Name_Sid[Hidx],"");
	leg2_Sid[Hidx]->SetFillStyle(0);
	leg2_Sid[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
	leg2_Sid[Hidx]->Draw();
	//myC_Sid[Hidx]->SaveAs(file_Name_2_Sid[Hidx]);

	}

	//TH1F *hist_Chi2_Flat[3];		
	//TH1F *hist_Chi2_Sid[3];			
	//TH1F *hist_Chi2_Real_Flat[3];	
	//TH1F *hist_Chi2_Real_Sid[3];	

	TCanvas *myC_One =  new TCanvas("Chi2 - Canv","Chi2 - Canv",200,10,1200,800);
	myC_One->Divide(3,2);
	myC_One->cd(1);
	hist_Chi2_Flat[0]->Draw();
	hist_Chi2_Real_Flat[0]->Draw("same");
	leg_Flat[0]->Draw();
	leg2_Flat[0]->Draw();
	myC_One->cd(2);
	hist_Chi2_Flat[1]->Draw();
	hist_Chi2_Real_Flat[1]->Draw("same");
	leg_Flat[1]->Draw();
	leg2_Flat[1]->Draw();
	myC_One->cd(3);
	hist_Chi2_Flat[2]->Draw();
	hist_Chi2_Real_Flat[2]->Draw("same");
	leg_Flat[2]->Draw();
	leg2_Flat[2]->Draw();
	myC_One->cd(4);
	hist_Chi2_Sid[0]->Draw();
	hist_Chi2_Real_Sid[0]->Draw("same");
	leg_Sid[0]->Draw();
	leg2_Sid[0]->Draw();
	myC_One->cd(5);
	hist_Chi2_Sid[1]->Draw();
	hist_Chi2_Real_Sid[1]->Draw("same");
	leg_Sid[1]->Draw();
	leg2_Sid[1]->Draw();
	myC_One->cd(6);
	hist_Chi2_Sid[2]->Draw();
	hist_Chi2_Real_Sid[2]->Draw("same");
	leg_Sid[2]->Draw();
	leg2_Sid[2]->Draw();
	myC_One->SaveAs("Shuffle/Chi2One/Simple_Shuffle_One_Chi2.pdf");
	myC_One->SaveAs("Shuffle/Chi2One/Simple_Shuffle_One_Chi2.root");

	cout<<"Real data Chi2_Flat:"<<endl;
	cout<<Chi2_Flat_Real[0]<<"   "<<Chi2_Flat_Real[1]<<"   "<<Chi2_Flat_Real[2]<<endl;
	
	cout<<"Real data Chi2_Sid:"<<endl;
	cout<<Chi2_Sid_Real[0]<<"   "<<Chi2_Sid_Real[1]<<"   "<<Chi2_Sid_Real[2]<<endl;


}


void ChiSquare_EH1_Const(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH1
   for (i=0;i<nbins; i++) {
     delta  = (R[0][i]-AVEP[0])/(RD_R[0][i]*R[0][i]);
     chisq += delta*delta;
   }

   f = chisq;
}

void ChiSquare_EH2_Const(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH2
   for (i=0;i<nbins; i++) {
     delta  = (R[1][i]-AVEP[1])/(RD_R[1][i]*R[1][i]);
     chisq += delta*delta;
   }

   f = chisq;
}

void ChiSquare_EH3_Const(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 24;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   //EH3
   for (i=0;i<nbins; i++) {
     delta  = (R[2][i]-AVEP[2])/(RD_R[2][i]*R[2][i]);
     chisq += delta*delta;
   }

   f = chisq;
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
