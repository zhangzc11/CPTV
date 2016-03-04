
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void AccRealTime()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	//
	Double_t TotalAcc[8]={0.0};
	Double_t Acc_t[8];

	Double_t AccInEachDay[8][707];
	Double_t E2_AccInEachDay[8][707];
	memset(AccInEachDay,0.0,sizeof(AccInEachDay));
	
	//
	Double_t TotalFullTime[8]={0.0};
	Double_t FullTime_t[8];

	Double_t FullTimeInEachDay[8][707];
	memset(FullTimeInEachDay,0.0,sizeof(FullTimeInEachDay));

	TFile *F_FullTime = new TFile("../FullTime.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
	Tree_FullTime->SetBranchAddress("FullTime",FullTime_t);
	//
	Double_t MultiplicityEff_t[8];

	Double_t MultiplicityEffInEachDay[8][707];
	memset(MultiplicityEffInEachDay,0.0,sizeof(MultiplicityEffInEachDay));

	TFile *F_MultiplicityEff = new TFile("../MultiEff/MultiplicityEff.root");
	TTree *Tree_MultiplicityEff = (TTree*)F_MultiplicityEff->Get("MultiplicityEff");
	Tree_MultiplicityEff->SetBranchAddress("MultiplicityEff",MultiplicityEff_t);

	
	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N707 = int(Bin/24);
		Tree_FullTime->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			FullTimeInEachDay[Det][N707] += FullTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
		}
	}

	for(int Bin=0;Bin<707;Bin++)
	{
		Tree_MultiplicityEff->GetEntry(Bin);
		for(int Det=0;Det<8;Det++)
		{
			MultiplicityEffInEachDay[Det][Bin] = MultiplicityEff_t[Det];
		}
	}
	const char *AccFName[8] = {
		"NumOfAccInEachBin_EH1_AD1.root","NumOfAccInEachBin_EH1_AD2.root","NumOfAccInEachBin_EH2_AD1.root","NumOfAccInEachBin_EH2_AD2.root",
		"NumOfAccInEachBin_EH3_AD1.root","NumOfAccInEachBin_EH3_AD2.root","NumOfAccInEachBin_EH3_AD3.root","NumOfAccInEachBin_EH3_AD4.root"};
	const char *E2_AccFName[8] = {
		"E2_NumOfAccInEachBin_EH1_AD1.root","E2_NumOfAccInEachBin_EH1_AD2.root","E2_NumOfAccInEachBin_EH2_AD1.root","E2_NumOfAccInEachBin_EH2_AD2.root",
		"E2_NumOfAccInEachBin_EH3_AD1.root","E2_NumOfAccInEachBin_EH3_AD2.root","E2_NumOfAccInEachBin_EH3_AD3.root","E2_NumOfAccInEachBin_EH3_AD4.root"};
    
	TFile *FAcc[8];
	TFile *FE2_Acc[8];
	TTree *TreeAcc[8];
	TTree *TreeE2_Acc[8];

    for(int Det=0;Det<8;Det++)
	{
		Double_t NumOfAcc, E2_NumOfAcc;
		FAcc[Det] = new TFile(AccFName[Det]);
		TreeAcc[Det] = (TTree*)FAcc[Det]->Get("NumOfAccInEachBin");
		TreeAcc[Det]->SetBranchAddress("NumOfAccInEachBin",&NumOfAcc);

		FE2_Acc[Det] = new TFile(E2_AccFName[Det]);
		TreeE2_Acc[Det] = (TTree*)FE2_Acc[Det]->Get("E2_NumOfAccInEachBin");
		TreeE2_Acc[Det]->SetBranchAddress("E2_NumOfAccInEachBin",&E2_NumOfAcc);

		for(int Bin=0;Bin<NumOfBin;Bin++)
		{
			int N707 = int(Bin/24);
			TreeAcc[Det]->GetEntry(Bin);
			TreeE2_Acc[Det]->GetEntry(Bin);

			AccInEachDay[Det][N707] += NumOfAcc;
			E2_AccInEachDay[Det][N707] = E2_NumOfAcc;
			TotalAcc[Det] += NumOfAcc;
		}
	}

	for(int Det=0;Det<8;Det++)
	{
		cout<<"Total Acc:  "<<Det<<"   "<<TotalAcc[Det]<<endl;
	}
	////////////////////////////////////////////
	gROOT->SetStyle("Plain");
    TStyle* style = new TStyle(*gStyle);
    style->SetName("myPlain");
	style->SetOptStat(0);
    gROOT->GetListOfStyles()->Add(style);
	 style->SetTextFont(132);
    style->SetLegendFont(132);
    style->SetLabelFont(132,"xyz");
    style->SetTitleFont(132,"");
    style->SetTitleFont(132,"xyz");
	// style->SetLabelSize(10,"xy");
	 style->SetLegendFillColor( 10 );
	 style->SetCanvasColor(0);
	 style->cd();
     gROOT->ForceStyle();


	/////////////////////////////////////////////
	//////////Draw
	const char *hist_Name[8] = {"EH1-AD1","EH1-AD2","EH2-AD1","EH2-AD2","EH3-AD1","EH3-AD2","EH3-AD3","EH3-AD4"}; 
	
	TCanvas *myC= new TCanvas("Acc","Acc",200,10,800,420);

	TGraphErrors *gr[8];
	TMultiGraph *mg =  new TMultiGraph();
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalAcc[Det]<<endl;
		const Int_t n = 707;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			if(FullTimeInEachDay[Det][i]>1)
			{
		x[i]=(i+0.5)*86400.0;
		y[i]=86400.0*AccInEachDay[Det][i]/(FullTimeInEachDay[Det][i]*MultiplicityEffInEachDay[Det][i]);
		ex[i]=0;
		ey[i]=0.0;//(86400.0*AccInEachDay[Det][i]/FullTimeInEachDay[Det][i])*sqrt(E2_AccInEachDay[Det][i])/AccInEachDay[Det][i];
		if((Det<4)&&(y[i]<5.0))
		{
			y[i]=0.0;
		}
			}
			else
			{
		x[i]=(i+0.5)*86400.0;
		y[i]=0.0;
		ex[i]=0;
		ey[i]=0.0;
			}
			/*if(y[i]>20)
			{

				//cout<<Det<<"   "<<i<<"   "<<y[i]<<"   "<<AccInEachDay[Det][i]<<"   "<<FullTimeInEachDay[Det][i]<<endl;
		x[i]=i;
		y[i]=0.0;
		ex[i]=0;
		ey[i]=0.0;
			}*/
			//cout<<AccInEachDay[Det][i]<<"   ";
	    }
		gr[Det] = new TGraphErrors(n,x,y,ex,ey);
	}
	gr[0]->SetMarkerColor(2);
	gr[1]->SetMarkerColor(4);
	gr[2]->SetMarkerColor(2);
	gr[3]->SetMarkerColor(4);
	gr[4]->SetMarkerColor(2);
	gr[5]->SetMarkerColor(4);
	gr[6]->SetMarkerColor(3);
	gr[7]->SetMarkerColor(1);

	gr[0]->SetMarkerStyle(20);
	gr[1]->SetMarkerStyle(7);
	gr[2]->SetMarkerStyle(4);
	gr[3]->SetMarkerStyle(25);
	gr[4]->SetMarkerStyle(22);
	gr[5]->SetMarkerStyle(23);
	gr[6]->SetMarkerStyle(26);
	gr[7]->SetMarkerStyle(26);
	
	for(int Det=0;Det<8;Det++)
	{
		//gr[Det]->SetMarkerColor(9-Det);
		gr[Det]->SetMarkerSize(0.9);
		mg->Add(gr[Det]);
	}

    
	mg->Draw("APZ");
	
	mg->GetYaxis()->SetTitle("Acc rate (/day)");
	mg->GetYaxis()->SetTitleSize(0.07);
	mg->GetYaxis()->SetLabelSize(0.06);
	mg->GetYaxis()->SetTitleOffset(0.55);
	mg->GetYaxis()->SetRangeUser(0.3,11.5);
	mg->GetYaxis()->SetNdivisions(510);
	mg->GetYaxis()->CenterTitle();
	mg->GetXaxis()->SetRangeUser(0,710.0*86400.0);
	mg->GetXaxis()->SetTimeDisplay(1);
	mg->GetXaxis()->SetTimeFormat("%b\/20%y%F2011-12-24 00:00:00");
	mg->GetXaxis()->SetLabelSize(0.05);
	
/*
	TLegend* leg = new TLegend(0.35, 0.2, 0.60, 0.53);
	for(int Det=0;Det<8;Det++)
	{
		leg->AddEntry(gr[Det],hist_Name[Det],"lp");
	}
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();
*/

TLegend* leg = new TLegend(0.38, 0.20, 0.55, 0.49);
	for(int Det=0;Det<4;Det++)
	{
		leg->AddEntry(gr[Det],hist_Name[Det],"lp");
	}
	//leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();

	TLegend* leg2 = new TLegend(0.52, 0.20, 0.69, 0.49);
	for(int Det=4;Det<8;Det++)
	{
		leg2->AddEntry(gr[Det],hist_Name[Det],"lp");
	}
	//leg2->SetFillStyle(0);
	leg2->SetBorderSize(0);
	leg2->Draw();
	
	
	gPad->Modified();

	myC->SaveAs("AccRealTime.eps");
	
	double AccRate[8];
	TFile  *F_AccRate = new TFile("AccRate.root","recreate");
	TTree *Tree_AccRate = new TTree("AccRate","AccRate");

	Tree_AccRate->Branch("AccRate",AccRate,"AccRate[8]/D");

	for(int Bin=0; Bin<707;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			AccRate[Det] = 86400.0*AccInEachDay[Det][Bin]/(FullTimeInEachDay[Det][Bin]*MultiplicityEffInEachDay[Det][Bin]);
		}
		Tree_AccRate->Fill();
	}
	Tree_AccRate->Write();
	
}