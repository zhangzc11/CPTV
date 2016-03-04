
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>



void MuEffRealTime()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968
	
	Double_t TotalMuEff[8]={0.0};
	Double_t MuEff_t[8];

	Double_t MuEffInEachDay[8][707];
	memset(MuEffInEachDay,0.0,sizeof(MuEffInEachDay));

	Double_t TotalLiveTime[8]={0.0};
	Double_t LiveTime_t[8];

	Double_t LiveTimeInEachDay[8][707];
	memset(LiveTimeInEachDay,0.0,sizeof(LiveTimeInEachDay));

	TFile *F_LiveTime = new TFile("../LiveTime.root");
	TTree *Tree_LiveTime = (TTree*)F_LiveTime->Get("LiveTime");
	Tree_LiveTime->SetBranchAddress("LiveTime",LiveTime_t);

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
		Tree_LiveTime->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			LiveTimeInEachDay[Det][N707] += LiveTime_t[Det];
			FullTimeInEachDay[Det][N707] += FullTime_t[Det];
			TotalLiveTime[Det] += LiveTime_t[Det];
			TotalFullTime[Det] += FullTime_t[Det];
		}
	}

	for(int Det=0;Det<8;Det++)
	{
		for(int N707=0;N707<707;N707++)
		{
			if(LiveTimeInEachDay[Det][N707]>1000)
			{
			MuEffInEachDay[Det][N707] = LiveTimeInEachDay[Det][N707]/FullTimeInEachDay[Det][N707];
			}
			else{
				MuEffInEachDay[Det][N707] = 1.0;
			}
		}
		TotalMuEff[Det] = TotalLiveTime[Det]/TotalFullTime[Det];
	}
	
	//////////Draw
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	
	TCanvas *myC= new TCanvas("MuEff","MuEff",200,10,900,600);

	TGraphErrors *gr[8];
	TMultiGraph *mg =  new TMultiGraph();
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalMuEff[Det]<<endl;
		const Int_t n = 707;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			
		x[i]=i;
		y[i]=MuEffInEachDay[Det][i];
		ex[i]=0;
		ey[i]=0.0;//(86400.0*MuEffInEachDay[Det][i]/FullTimeInEachDay[Det][i])*sqrt(E2_MuEffInEachDay[Det][i])/MuEffInEachDay[Det][i];

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
    //mg->GetYaxis()->SetTitle("Muon veto effficienncy");
	mg->GetYaxis()->SetTitleSize(0.055);
	mg->GetYaxis()->SetTitleOffset(0.7);
	mg->GetYaxis()->SetRangeUser(0.8,0.99);
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

	myC->SaveAs("MuEffRealTime.pdf");
	
	
	
	//save to root file...
	double MuonEff[8];
	TFile  *F_MuonEff = new TFile("MuonEff.root","recreate");
	TTree *Tree_MuonEff = new TTree("MuonEff","MuonEff");
	Tree_MuonEff->Branch("MuonEff",MuonEff,"MuonEff[8]/D");

	for(int Bin=0; Bin<707;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			MuonEff[Det] = MuEffInEachDay[Det][Bin];
		}
		Tree_MuonEff->Fill();
	}
	Tree_MuonEff->Write();

}
