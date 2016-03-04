
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>


void SumEff()
{
	Double_t WidthOfBin = 3600.0;
	const int NumOfHourInEachDay = 24;
	const int NumOfDay = 704;
	const int NumOfBin = 16896;	
	
	
	
	//Multiplicity eff in each day
	Double_t MultiplicityEff_t[8];
	Double_t MultiplicityEffInEachDay[8][NumOfDay];
	memset(MultiplicityEffInEachDay,0.0,sizeof(MultiplicityEffInEachDay));
	TFile *F_MultiplicityEff = new TFile("../MultiEff/MultiplicityEff.root");
	TTree *Tree_MultiplicityEff = (TTree*)F_MultiplicityEff->Get("MultiplicityEff");
	Tree_MultiplicityEff->SetBranchAddress("MultiplicityEff",MultiplicityEff_t);
	
	//Muon eff in each day
	Double_t MuonEff_t[8];
	Double_t MuonEffInEachDay[8][NumOfDay];
	memset(MuonEffInEachDay,0.0,sizeof(MuonEffInEachDay));
	TFile *F_MuonEff = new TFile("../MuEff/MuonEff.root");
	TTree *Tree_MuonEff = (TTree*)F_MuonEff->Get("MuonEff");
	Tree_MuonEff->SetBranchAddress("MuonEff",MuonEff_t);
	
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		Tree_MultiplicityEff->GetEntry(Bin);
		Tree_MuonEff->GetEntry(Bin);
		for(int Det=0;Det<8;Det++)
		{
			MultiplicityEffInEachDay[Det][Bin] = MultiplicityEff_t[Det];
			MuonEffInEachDay[Det][Bin] = MuonEff_t[Det];
		}
	}
	
	////
	
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
	const char *hist_Name[8] = {"EH1-AD1","EH1-AD2","EH2-AD1","EH2-AD2","EH3-AD1","EH3-AD2","EH3-AD3","EH3-AD4"}; 

	TGraphErrors *gr_1[8];
	TMultiGraph *mg[2];
	mg[0] =  new TMultiGraph();
	
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalMuEff[Det]<<endl;
		const Int_t n = 704;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			
		x[i]=(i+0.5)*86400;
		y[i]=MuonEffInEachDay[Det][i];
		ex[i]=0;
		ey[i]=0.0;

	    }
		gr_1[Det] = new TGraphErrors(n,x,y,ex,ey);
	}
	
	/*gr_1[0]->SetMarkerColor(2);
	gr_1[1]->SetMarkerColor(4);
	gr_1[2]->SetMarkerColor(2);
	gr_1[3]->SetMarkerColor(4);
	gr_1[4]->SetMarkerColor(2);
	gr_1[5]->SetMarkerColor(4);
	gr_1[6]->SetMarkerColor(3);
	gr_1[7]->SetMarkerColor(1);
*/
	gr_1[0]->SetMarkerStyle(20);
	gr_1[1]->SetMarkerStyle(7);
	gr_1[2]->SetMarkerStyle(4);
	gr_1[3]->SetMarkerStyle(25);
	gr_1[4]->SetMarkerStyle(22);
	gr_1[5]->SetMarkerStyle(23);
	gr_1[6]->SetMarkerStyle(26);
	gr_1[7]->SetMarkerStyle(26);
	
	
	for(int Det=0;Det<8;Det++)
	{
		//gr_1[Det]->SetMarkerStyle(20);
		gr_1[Det]->SetMarkerColor(8-Det);
		gr_1[Det]->SetMarkerSize(0.7);
		mg[0]->Add(gr_1[Det]);
	}
	
	TGraphErrors *gr_2[8];
	mg[1] =  new TMultiGraph();
	
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalMuEff[Det]<<endl;
		const Int_t n = 704;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			
		x[i]=(i+0.5)*86400;
		y[i]=MultiplicityEffInEachDay[Det][i];
		ex[i]=0;
		ey[i]=0.0;

	    }
		gr_2[Det] = new TGraphErrors(n,x,y,ex,ey);
	}
	/*
	gr_2[0]->SetMarkerColor(2);
	gr_2[1]->SetMarkerColor(4);
	gr_2[2]->SetMarkerColor(2);
	gr_2[3]->SetMarkerColor(4);
	gr_2[4]->SetMarkerColor(2);
	gr_2[5]->SetMarkerColor(4);
	gr_2[6]->SetMarkerColor(3);
	gr_2[7]->SetMarkerColor(1);
	*/
	gr_2[0]->SetMarkerStyle(20);
	gr_2[1]->SetMarkerStyle(7);
	gr_2[2]->SetMarkerStyle(4);
	gr_2[3]->SetMarkerStyle(25);
	gr_2[4]->SetMarkerStyle(22);
	gr_2[5]->SetMarkerStyle(23);
	gr_2[6]->SetMarkerStyle(26);
	gr_2[7]->SetMarkerStyle(26);
	
	for(int Det=0;Det<8;Det++)
	{
		//gr_2[Det]->SetMarkerStyle(20);
		gr_2[Det]->SetMarkerColor(8-Det);
		gr_2[Det]->SetMarkerSize(0.7);
		mg[1]->Add(gr_2[Det]);
	}
	
	TCanvas *myC_One = new TCanvas("myC_One","myC_One",200,10,800,600);
	myC_One->Divide(1,2,0);
	
	for(int i=0;i<2;i++)
	{
		myC_One->cd(i+1);
		mg[i]->Draw("AP");
		
	mg[i]->SetTitle("");
	mg[i]->GetXaxis()->SetTitle("");
	if(i==0)
	{
    mg[i]->GetYaxis()->SetTitle("Muon veto eff.");
	mg[i]->GetYaxis()->SetRangeUser(0.81,0.999);
	}
	else
	{
		mg[i]->GetYaxis()->SetTitle("Multiplicity cut eff.");
		mg[i]->GetYaxis()->SetRangeUser(0.971,0.979);
	}
	//mg[i]->GetYaxis()->SetTitle("IBD candidate number");
	mg[i]->GetYaxis()->SetTitleSize(0.10);
	mg[i]->GetYaxis()->SetLabelSize(0.07);
	mg[i]->GetYaxis()->CenterTitle();
	
	mg[i]->GetYaxis()->SetNdivisions(505);
	//mg[i]->GetXaxis()->SetNdivisions(505);
	mg[i]->GetYaxis()->SetTitleOffset(0.52);
	mg[i]->GetXaxis()->SetTitleSize(0.055);
	mg[i]->GetXaxis()->SetLabelSize(0.07);
	mg[i]->GetXaxis()->SetTitleOffset(0.8);
	mg[i]->GetXaxis()->SetRangeUser(0,705.0*86400.0);
	mg[i]->GetXaxis()->SetTimeDisplay(1);
	mg[i]->GetXaxis()->SetTimeFormat("%b\/20%y%F2011-12-24 00:00:00");
	
	if(i==0)
	{
	TLegend* leg = new TLegend(0.35, 0.3, 0.55, 0.85);
	for(int Det=0;Det<4;Det++)
	{
		leg->AddEntry(gr_1[Det],hist_Name[Det],"p");
	}
	//leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();

	TLegend* leg2 = new TLegend(0.52, 0.3, 0.72, 0.85);
	for(int Det=4;Det<8;Det++)
	{
		leg2->AddEntry(gr_1[Det],hist_Name[Det],"p");
	}
	//leg2->SetFillStyle(0);
	leg2->SetBorderSize(0);
	leg2->Draw();
	}
	}
	myC_One->SaveAs("SumEff.eps");
}