
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void HMuG10RealTime()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	//
	Double_t TotalHMuG10[8]={0.0};
	Double_t HMuG10_t[8];

	Double_t HMuG10InEachDay[8][707];
	Double_t E2_HMuG10InEachDay[8][707];
	memset(HMuG10InEachDay,0.0,sizeof(HMuG10InEachDay));

	TFile *F_HMuG10 = new TFile("../HMuG10.root");
	TTree *Tree_HMuG10 = (TTree*)F_HMuG10->Get("HMuG10");
	Tree_HMuG10->SetBranchAddress("HMuG10",HMuG10_t);
	
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
		Tree_HMuG10->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			FullTimeInEachDay[Det][N707] += FullTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
			HMuG10InEachDay[Det][N707] += HMuG10_t[Det];

		}
	}

	for(int Det=0;Det<8;Det++)
	{
	for(int N707 = 0;N707<707;N707++)
	{
		E2_HMuG10InEachDay[Det][N707]=HMuG10InEachDay[Det][N707];
	}
	}
   
	//////////Draw
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	const char *c_Name[3] = {"EH1","EH2","EH3"};
	const char *file_Name[3] = {"HMuG10RealTime_EH1.pdf","HMuG10RealTime_EH2.pdf","HMuG10RealTime_EH3.pdf"};

	TGraphErrors *gr[8];
	TMultiGraph *mg[3];// =  new TMultiGraph();
	for(int i=0;i<3;i++)
	{
		mg[i] = new TMultiGraph();
	}
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalHMuG10[Det]<<endl;
		const Int_t n = 707;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			if(FullTimeInEachDay[Det][i]>1)
			{
		x[i]=i;
		y[i]=86400.0*HMuG10InEachDay[Det][i]/FullTimeInEachDay[Det][i];
		ex[i]=0;
		ey[i]=0.0;//(86400.0*HMuG10InEachDay[Det][i]/FullTimeInEachDay[Det][i])*sqrt(E2_HMuG10InEachDay[Det][i])/HMuG10InEachDay[Det][i];
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

				//cout<<Det<<"   "<<i<<"   "<<y[i]<<"   "<<HMuG10InEachDay[Det][i]<<"   "<<FullTimeInEachDay[Det][i]<<endl;
		x[i]=i;
		y[i]=0.0;
		ex[i]=0;
		ey[i]=0.0;
			}*/
			//cout<<HMuG10InEachDay[Det][i]<<"   ";
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

    TCanvas *myC[3];//= new TCanvas("HMuG101","HMuG101",200,10,900,200);

	for(int i=0;i<3;i++)
	{
		myC[i] = new TCanvas(c_Name[i],c_Name[i],200,10,900,400);
		TLegend* leg = new TLegend(0.35, 0.15, 0.55, 0.45);
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
    mg[i]->GetYaxis()->SetTitle("1.0~2.5GeV muon rate (/day)");
	mg[i]->GetYaxis()->SetTitleSize(0.075);
	mg[i]->GetYaxis()->SetLabelSize(0.050);
	mg[i]->GetYaxis()->SetTitleOffset(0.6);
	mg[i]->GetXaxis()->SetTitleSize(0.075);
	mg[i]->GetXaxis()->SetLabelSize(0.04);
	mg[i]->GetXaxis()->SetTitleOffset(0.6);
	
	
	if(i==0)
	{
		mg[0]->GetYaxis()->SetRangeUser(116.0e3,132.0e3);
	}
	if(i==1)
	{
		mg[1]->GetYaxis()->SetRangeUser(120.0e3,140.0e3);
	}
	if(i==2)
	{
		mg[2]->GetYaxis()->SetRangeUser(7.0e3,9.2e3);
	}
	
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();

	gPad->Modified();

	myC[i]->SaveAs(file_Name[i]);

	}
	

}