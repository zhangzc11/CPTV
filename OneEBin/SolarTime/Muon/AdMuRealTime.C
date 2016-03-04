
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void AdMuRealTime()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	//
	Double_t TotalAdMu[8]={0.0};
	Double_t AdMu_t[8];

	Double_t AdMuInEachDay[8][707];
	Double_t E2_AdMuInEachDay[8][707];
	memset(AdMuInEachDay,0.0,sizeof(AdMuInEachDay));

	TFile *F_AdMu = new TFile("../AdMu.root");
	TTree *Tree_AdMu = (TTree*)F_AdMu->Get("AdMu");
	Tree_AdMu->SetBranchAddress("AdMu",AdMu_t);
	
	//
	Double_t TotalFullTime[8]={0.0};
	Double_t FullTime_t[8];

	Double_t FullTimeInEachDay[8][707];
	memset(FullTimeInEachDay,0.0,sizeof(FullTimeInEachDay));

	TFile *F_FullTime = new TFile("../FullTime.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
	Tree_FullTime->SetBranchAddress("FullTime",FullTime_t);

	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N707 = int(Bin/24);
		Tree_FullTime->GetEntry(Bin);
		Tree_AdMu->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			FullTimeInEachDay[Det][N707] += FullTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
			AdMuInEachDay[Det][N707] += AdMu_t[Det];

		}
	}

	for(int Det=0;Det<8;Det++)
	{
	for(int N707 = 0;N707<707;N707++)
	{
		E2_AdMuInEachDay[Det][N707]=AdMuInEachDay[Det][N707];
	}
	}
   
	//////////Draw
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	const char *c_Name[3] = {"EH1","EH2","EH3"};
	const char *file_Name[3] = {"AdMuRealTime_EH1.pdf","AdMuRealTime_EH2.pdf","AdMuRealTime_EH3.pdf"};

	TGraphErrors *gr[8];
	TMultiGraph *mg[3];// =  new TMultiGraph();
	for(int i=0;i<3;i++)
	{
		mg[i] = new TMultiGraph();
	}
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalAdMu[Det]<<endl;
		const Int_t n = 707;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			if(FullTimeInEachDay[Det][i]>1)
			{
		x[i]=i;
		y[i]=86400.0*AdMuInEachDay[Det][i]/FullTimeInEachDay[Det][i];
		ex[i]=0;
		ey[i]=0.0;//(86400.0*AdMuInEachDay[Det][i]/FullTimeInEachDay[Det][i])*sqrt(E2_AdMuInEachDay[Det][i])/AdMuInEachDay[Det][i];
			}
			else
			{
		x[i]=i;
		y[i]=0.0;
		ex[i]=0;
		ey[i]=0.0;
			}
			/*if(y[i]>20)
			{

				//cout<<Det<<"   "<<i<<"   "<<y[i]<<"   "<<AdMuInEachDay[Det][i]<<"   "<<FullTimeInEachDay[Det][i]<<endl;
		x[i]=i;
		y[i]=0.0;
		ex[i]=0;
		ey[i]=0.0;
			}*/
			//cout<<AdMuInEachDay[Det][i]<<"   ";
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
	}

    TCanvas *myC[3];//= new TCanvas("AdMu1","AdMu1",200,10,900,200);

	for(int i=0;i<3;i++)
	{
		myC[i] = new TCanvas(c_Name[i],c_Name[i],200,10,900,400);
		TLegend* leg = new TLegend(0.25, 0.15, 0.45, 0.45);
		if(i==2)
		{
			for(int j=4;j<8;j++)
			{
				mg[i]->Add(gr[j]);
				leg->AddEntry(gr[j],hist_Name[j],"lp");
			}
		}
		else
		{
			mg[i]->Add(gr[i*2]);
		    mg[i]->Add(gr[i*2+1]);
			leg->AddEntry(gr[i*2],hist_Name[i*2],"lp");
			leg->AddEntry(gr[i*2+1],hist_Name[i*2+1],"lp");
		}

	mg[i]->Draw("AP");
	mg[i]->GetXaxis()->SetTitle("days since 2011-12-24");
    mg[i]->GetYaxis()->SetTitle("Ad muon rate (/day)");
	mg[i]->GetYaxis()->SetTitleSize(0.075);
	mg[i]->GetYaxis()->SetLabelSize(0.060);
	mg[i]->GetYaxis()->SetTitleOffset(0.6);
	mg[i]->GetXaxis()->SetTitleSize(0.075);
	mg[i]->GetXaxis()->SetLabelSize(0.04);
	mg[i]->GetXaxis()->SetTitleOffset(0.6);
	

	if(i==0)
	{
		mg[0]->GetYaxis()->SetRangeUser(1795.0e3,1830.0e3);
	}
	if(i==1)
	{
		mg[1]->GetYaxis()->SetRangeUser(1310.0e3,1380.0e3);
	}
	if(i==2)
	{
		mg[2]->GetYaxis()->SetRangeUser(86.0e3,93.0e3);
	}

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();

	gPad->Modified();

	myC[i]->SaveAs(file_Name[i]);

	}
	

}