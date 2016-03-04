
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void HMuL5RealTime()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	//
	Double_t TotalHMuL5[8]={0.0};
	Double_t HMuL5_t[8];

	Double_t HMuL5InEachDay[8][707];
	Double_t E2_HMuL5InEachDay[8][707];
	memset(HMuL5InEachDay,0.0,sizeof(HMuL5InEachDay));

	TFile *F_HMuL5 = new TFile("../HMuL5.root");
	TTree *Tree_HMuL5 = (TTree*)F_HMuL5->Get("HMuL5");
	Tree_HMuL5->SetBranchAddress("HMuL5",HMuL5_t);
	
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
		Tree_HMuL5->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			FullTimeInEachDay[Det][N707] += FullTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
			HMuL5InEachDay[Det][N707] += HMuL5_t[Det];

		}
	}

	for(int Det=0;Det<8;Det++)
	{
	for(int N707 = 0;N707<707;N707++)
	{
		E2_HMuL5InEachDay[Det][N707]=HMuL5InEachDay[Det][N707];
	}
	}
   
	//////////Draw
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	
	TCanvas *myC= new TCanvas("HMuL5","HMuL5",200,10,900,600);

	TGraphErrors *gr[8];
	TMultiGraph *mg =  new TMultiGraph();
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalHMuL5[Det]<<endl;
		const Int_t n = 707;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			if(FullTimeInEachDay[Det][i]>1)
			{
		x[i]=i;
		y[i]=86400.0*HMuL5InEachDay[Det][i]/FullTimeInEachDay[Det][i];
		ex[i]=0;
		ey[i]=0.0;//(86400.0*HMuL5InEachDay[Det][i]/FullTimeInEachDay[Det][i])*sqrt(E2_HMuL5InEachDay[Det][i])/HMuL5InEachDay[Det][i];
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

				//cout<<Det<<"   "<<i<<"   "<<y[i]<<"   "<<HMuL5InEachDay[Det][i]<<"   "<<FullTimeInEachDay[Det][i]<<endl;
		x[i]=i;
		y[i]=0.0;
		ex[i]=0;
		ey[i]=0.0;
			}*/
			//cout<<HMuL5InEachDay[Det][i]<<"   ";
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

    
	mg->Draw("AP");

	mg->GetXaxis()->SetTitle("days since 2011-12-24");
    mg->GetYaxis()->SetTitle("0~500MeV muon rate (/day)");
	mg->GetYaxis()->SetTitleSize(0.055);
	mg->GetYaxis()->SetTitleOffset(0.7);
	//mg->GetYaxis()->SetRangeUser(600.0,1000.0);

	TLegend* leg = new TLegend(0.38, 0.25, 0.60, 0.55);
	for(int Det=0;Det<8;Det++)
	{
		leg->AddEntry(gr[Det],hist_Name[Det],"lp");
	}
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();

	gPad->Modified();

	myC->SaveAs("HMuL5RealTime.pdf");
	
}