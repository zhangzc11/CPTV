
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void AmCRealTime()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	Int_t Bin_8AD = 7060;
	Int_t Day_ID = 250;

	Double_t AmCRate_6AD[8] = {0.27,0.25,0.27,0.0,0.22,0.21,0.21,0.0};
	Double_t AmCRate_8AD[8] = {0.20,0.21,0.18,0.22,0.06,0.04,0.04,0.07};

	//
	Double_t TotalAmC_6AD[8]={0.0};
	Double_t TotalAmC_8AD[8]={0.0};

	Double_t AmC_t[8];


	Double_t AmCInEachDay[8][707];
	Double_t RD_AmCInEachDay[8][707];
	memset(AmCInEachDay,0.0,sizeof(AmCInEachDay));
	//
	Double_t TotalnLike_6AD[8]={0.0};
	Double_t TotalnLike_8AD[8]={0.0};
	Int_t nLike_t[8];

	Double_t nLikeInEachDay[8][707];
	memset(nLikeInEachDay,0.0,sizeof(nLikeInEachDay));

	TFile *F_nLike = new TFile("../nLike.root");
	TTree *Tree_nLike = (TTree*)F_nLike->Get("nLike");
	Tree_nLike->SetBranchAddress("nLike",nLike_t);
	//
	Double_t TotalFullTime_6AD[8]={0.0};
	Double_t TotalFullTime_8AD[8]={0.0};

	Double_t FullTime_t[8];

	Double_t FullTimeInEachDay[8][707];
	memset(FullTimeInEachDay,0.0,sizeof(FullTimeInEachDay));

	TFile *F_FullTime = new TFile("../FullTime.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
	Tree_FullTime->SetBranchAddress("FullTime",FullTime_t);

	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N707 = int(Bin/24);
		Tree_nLike->GetEntry(Bin);
		Tree_FullTime->GetEntry(Bin);
		if(Bin<=Bin_8AD)
		{
		for(int Det=0;Det<8;Det++)
		{
			nLikeInEachDay[Det][N707] += 1.0*nLike_t[Det];
			FullTimeInEachDay[Det][N707] += FullTime_t[Det];
			TotalFullTime_6AD[Det] += FullTime_t[Det];
			TotalnLike_6AD[Det] += 1.0*nLike_t[Det];
		}
		}
		else
		{
			for(int Det=0;Det<8;Det++)
		{
			nLikeInEachDay[Det][N707] += 1.0*nLike_t[Det];
			FullTimeInEachDay[Det][N707] += FullTime_t[Det];
			TotalFullTime_8AD[Det] += FullTime_t[Det];
			TotalnLike_8AD[Det] += 1.0*nLike_t[Det];
		}

		}
	}



	for(int Det=0;Det<8;Det++)
	{
		TotalAmC_6AD[Det] = AmCRate_6AD[Det]*TotalFullTime_6AD[Det]/86400.0;
		TotalAmC_8AD[Det] = AmCRate_8AD[Det]*TotalFullTime_8AD[Det]/86400.0;
		for(int N707=0;N707<Day_ID;N707++)
		{
			if(TotalnLike_6AD[Det]>1)
			{
			AmCInEachDay[Det][N707] = TotalAmC_6AD[Det] * nLikeInEachDay[Det][N707]/TotalnLike_6AD[Det];		
			RD_AmCInEachDay[Det][N707] = sqrt(1.0/nLikeInEachDay[Det][N707] - 1.0/TotalnLike_6AD[Det]);
			}
			else
			{
				AmCInEachDay[Det][N707]=0.0;
				RD_AmCInEachDay[Det][N707]=0.0;
			}
		}
		for(int N707=Day_ID;N707<707;N707++)
		{
			if(TotalnLike_8AD[Det]>1)
			{
			AmCInEachDay[Det][N707] = TotalAmC_8AD[Det] * nLikeInEachDay[Det][N707]/TotalnLike_8AD[Det];		
			RD_AmCInEachDay[Det][N707] = sqrt(1.0/nLikeInEachDay[Det][N707] - 1.0/TotalnLike_8AD[Det]);
			}
			else
			{
				AmCInEachDay[Det][N707]=0.0;
				RD_AmCInEachDay[Det][N707]=0.0;
			}
		}
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
	
	TCanvas *myC= new TCanvas("AmC","AmC",200,10,800,420);

	TGraphErrors *gr[8];
	TMultiGraph *mg =  new TMultiGraph();
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalAmC[Det]<<endl;
		const Int_t n = 707;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			if(FullTimeInEachDay[Det][i]>1)
			{
		x[i]=(i+0.5)*86400.0;
		y[i]=86400.0*AmCInEachDay[Det][i]/FullTimeInEachDay[Det][i];
		ex[i]=0;
		ey[i]=0.0;//(86400.0*AmCInEachDay[Det][i]/FullTimeInEachDay[Det][i])*RD_AmCInEachDay[Det][i];
			}
			else
			{
		x[i]=(i+0.5)*86400.0;
		y[i]=0.0;
		ex[i]=0;
		ey[i]=0.0;
			}
			if((y[i]>0.4))
			{

				cout<<Det<<"   "<<i<<"   "<<y[i]<<"   "<<AmCInEachDay[Det][i]<<"   "<<FullTimeInEachDay[Det][i]<<endl;
		x[i]=i;
		y[i]=0.0;
		ex[i]=0;
		ey[i]=0.0;
			}
			//cout<<AmCInEachDay[Det][i]<<"   ";
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

	//mg->GetXaxis()->SetTitle("days since 2011-12-707");
    mg->GetYaxis()->SetTitle("AmC Rate (/day)");
	mg->GetYaxis()->SetTitleSize(0.07);
	mg->GetYaxis()->SetLabelSize(0.06);
	mg->GetYaxis()->SetTitleOffset(0.6);
	mg->GetYaxis()->SetRangeUser(0.01,0.5);
	mg->GetYaxis()->SetNdivisions(505);
	mg->GetYaxis()->CenterTitle();
	mg->GetXaxis()->SetRangeUser(0,710.0*86400.0);
	mg->GetXaxis()->SetTimeDisplay(1);
	mg->GetXaxis()->SetTimeFormat("%b\/20%y%F2011-12-24 00:00:00");
	mg->GetXaxis()->SetLabelSize(0.05);

	TLegend* leg = new TLegend(0.58, 0.6, 0.75, 0.89);
	for(int Det=0;Det<4;Det++)
	{
		leg->AddEntry(gr[Det],hist_Name[Det],"lp");
	}
	//leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();

	TLegend* leg2 = new TLegend(0.72, 0.6, 0.89, 0.89);
	for(int Det=4;Det<8;Det++)
	{
		leg2->AddEntry(gr[Det],hist_Name[Det],"lp");
	}
	//leg2->SetFillStyle(0);
	leg2->SetBorderSize(0);
	leg2->Draw();

	gPad->Modified();

	myC->SaveAs("AmCRealTime.eps");
	
	
	double AmCRate[8];
	TFile  *F_AmCRate = new TFile("AmCRate.root","recreate");
	TTree *Tree_AmCRate = new TTree("AmCRate","AmCRate");

	Tree_AmCRate->Branch("AmCRate",AmCRate,"AmCRate[8]/D");

	for(int Bin=0; Bin<707;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			if(FullTimeInEachDay[Det][Bin]>10)
			{
			AmCRate[Det] = 86400.0*AmCInEachDay[Det][Bin]/FullTimeInEachDay[Det][Bin];
			}
			else{
				AmCRate[Det] = 0.0;
			}
		}
		Tree_AmCRate->Fill();
	}
	Tree_AmCRate->Write();
}