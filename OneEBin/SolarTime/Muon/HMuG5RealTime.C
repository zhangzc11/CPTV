
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void HMuG5RealTime()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	//
	Double_t TotalHMuG5[8]={0.0};
	Double_t HMuG5_t[8];

	Double_t HMuG5InEachDay[8][707];
	Double_t E2_HMuG5InEachDay[8][707];
	memset(HMuG5InEachDay,0.0,sizeof(HMuG5InEachDay));

	TFile *F_HMuG5 = new TFile("../HMuG5.root");
	TTree *Tree_HMuG5 = (TTree*)F_HMuG5->Get("HMuG5");
	Tree_HMuG5->SetBranchAddress("HMuG5",HMuG5_t);
	
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
		Tree_HMuG5->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			FullTimeInEachDay[Det][N707] += FullTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
			HMuG5InEachDay[Det][N707] += HMuG5_t[Det];

		}
	}

	for(int Det=0;Det<8;Det++)
	{
	for(int N707 = 0;N707<707;N707++)
	{
		E2_HMuG5InEachDay[Det][N707]=HMuG5InEachDay[Det][N707];
	}
	}
   
	//////////Draw
	const char *hist_Name[8] = {"EH1-AD1","EH1-AD2","EH2-AD1","EH2-AD2","EH3-AD1","EH3-AD2","EH3-AD3","EH3-AD4"}; 
	const char *c_Name[3] = {"EH1","EH2","EH3"};
	const char *file_Name[3] = {"HMuG5RealTime_EH1.pdf","HMuG5RealTime_EH2.pdf","HMuG5RealTime_EH3.pdf"};

	TGraphErrors *gr[8];
	TMultiGraph *mg[3];// =  new TMultiGraph();
	for(int i=0;i<3;i++)
	{
		mg[i] = new TMultiGraph();
	}
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalHMuG5[Det]<<endl;
		const Int_t n = 707;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			if(FullTimeInEachDay[Det][i]>10)
			{
		x[i]=(i+0.5)*86400.0;
		y[i]=0.001*86400.0*HMuG5InEachDay[Det][i]/FullTimeInEachDay[Det][i];
		ex[i]=0;
		ey[i]=0.0;//(86400.0*HMuG5InEachDay[Det][i]/FullTimeInEachDay[Det][i])*sqrt(E2_HMuG5InEachDay[Det][i])/HMuG5InEachDay[Det][i];
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

				//cout<<Det<<"   "<<i<<"   "<<y[i]<<"   "<<HMuG5InEachDay[Det][i]<<"   "<<FullTimeInEachDay[Det][i]<<endl;
		x[i]=i;
		y[i]=0.0;
		ex[i]=0;
		ey[i]=0.0;
			}*/
			//cout<<HMuG5InEachDay[Det][i]<<"   ";
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

    TCanvas *myC[3];//= new TCanvas("HMuG51","HMuG51",200,10,900,200);

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
	//mg[i]->GetXaxis()->SetTitle("days since 2011-12-24");
    mg[i]->GetYaxis()->SetTitle("Muon Rate (/day)");
	mg[i]->GetYaxis()->SetTitleSize(0.075);
	mg[i]->GetYaxis()->SetLabelSize(0.050);
	mg[i]->GetYaxis()->SetTitleOffset(0.6);
	mg[i]->GetXaxis()->SetTitleSize(0.075);
	mg[i]->GetXaxis()->SetLabelSize(0.04);
	mg[i]->GetXaxis()->SetTitleOffset(0.6);
	mg[i]->GetXaxis()->SetRangeUser(0,710.0*86400.0);
	mg[i]->GetXaxis()->SetTimeDisplay(1);
	mg[i]->GetXaxis()->SetTimeFormat("%b\/20%y%F2011-12-24 00:00:00");
	
	if(i==0)
	{
		mg[0]->GetYaxis()->SetRangeUser(967.0,992.0);
	}
	if(i==1)
	{
		mg[1]->GetYaxis()->SetRangeUser(735.0,785.0);
	}
	if(i==2)
	{
		mg[2]->GetYaxis()->SetRangeUser(48.5,58.5);
	}

	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();

	gPad->Modified();

	myC[i]->SaveAs(file_Name[i]);

	}
	/////////////////////////In One Canvas/////////////////////
	/////////////////////////////////////////////////////////////////
    gROOT->SetStyle("Plain");
    TStyle* style = new TStyle(*gStyle);
    style->SetName("myPlain");
    gROOT->GetListOfStyles()->Add(style);
	 style->SetTextFont(132);
    style->SetLegendFont(132);
    style->SetLabelFont(132,"xyz");
    style->SetTitleFont(132,"");
    style->SetTitleFont(132,"xyz");
	 style->SetLabelSize(10,"xy");
	 style->SetLegendFillColor( 10 );
	 style->SetCanvasColor(0);
	 style->cd();
    gROOT->ForceStyle();
	//////////Draw
	TCanvas *myC_One = new TCanvas("myC_One","myC_One",200,10,800,600);
	myC_One->Divide(1,3,0);
	for(int i=0;i<3;i++)
	{
		myC_One->cd(i+1);
		mg[i]->Draw("AP");
		mg[i]->GetYaxis()->SetNdivisions(505);
		mg[i]->GetYaxis()->SetTitleSize(0.15);
		mg[i]->GetYaxis()->SetLabelSize(0.12);
		mg[i]->GetYaxis()->SetTitleOffset(0.32);
		mg[i]->GetXaxis()->SetLabelSize(0.1);

		
		

		if(i==2)
		{
			TLegend* leg = new TLegend(0.38, 0.39, 0.55, 0.99);
			for(int j=4;j<8;j++)
			{
				leg->AddEntry(gr[j],hist_Name[j],"lp");
			}
			leg->SetBorderSize(0);
			leg->Draw();
		}
		else
		{
			TLegend* leg = new TLegend(0.38, 0.69, 0.55, 0.99);
			leg->AddEntry(gr[i*2],hist_Name[i*2],"lp");
			leg->AddEntry(gr[i*2+1],hist_Name[i*2+1],"lp");
			leg->SetBorderSize(0);
			leg->Draw();
		}
		

		if(i==1)
	{
		mg[i]->GetYaxis()->SetTitle("R_{#mu} (10^{3}/day)");
	}
	else
	{
		mg[i]->GetYaxis()->SetTitle("");
	}
		
		gPad->Modified();
	}
	myC_One->SaveAs("MuRateRealTime.eps");
	
	//
	double MuonRate[8];
	TFile  *F_MuonRate = new TFile("MuonRate.root","recreate");
	TTree *Tree_MuonRate = new TTree("MuonRate","MuonRate");

	Tree_MuonRate->Branch("MuonRate",MuonRate,"MuonRate[8]/D");

	for(int Bin=0; Bin<707;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			if(FullTimeInEachDay[Det][Bin]>10)
			{
			MuonRate[Det] = 0.001*86400.0*HMuG5InEachDay[Det][Bin]/FullTimeInEachDay[Det][Bin];
			}
			else
			{
				MuonRate[Det] = 0.0;
			}
		}
		Tree_MuonRate->Fill();
	}
	Tree_MuonRate->Write();
	
}