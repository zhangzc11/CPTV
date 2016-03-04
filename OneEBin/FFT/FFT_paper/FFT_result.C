

#include <math.h>

const int NumOfBin = 16944;

const double SidToSol = 86164.09/86400.0;


Double_t PlotFunc_1(Double_t *x, Double_t *par);

Double_t PlotFunc_2(Double_t *x, Double_t *par);

void FFT_result()
{

	double an_MC_Gap[3][2];
	TFile *F_an_MC_Gap = new TFile("an_MC_Gap.root");
	TTree *Tree_an_MC_Gap = (TTree*)F_an_MC_Gap->Get("an");
	Tree_an_MC_Gap->SetBranchAddress("an",an_MC_Gap);

	double an_MC_Unc[3][2];
	TFile *F_an_MC_Unc = new TFile("an_MC_Unc.root");
	TTree *Tree_an_MC_Unc = (TTree*)F_an_MC_Unc->Get("an");
	Tree_an_MC_Unc->SetBranchAddress("an",an_MC_Unc);

	double an_MC_NoGap[3][2];
	TFile *F_an_MC_NoGap = new TFile("an_MC_NoGap.root");
	TTree *Tree_an_MC_NoGap = (TTree*)F_an_MC_NoGap->Get("an");
	Tree_an_MC_NoGap->SetBranchAddress("an",an_MC_NoGap);

	double an_MC_WithGap[3][2];
	TFile *F_an_MC_WithGap = new TFile("an_MC_WithGap.root");
	TTree *Tree_an_MC_WithGap = (TTree*)F_an_MC_WithGap->Get("an");
	Tree_an_MC_WithGap->SetBranchAddress("an",an_MC_WithGap);

	double an_data[3][2];
	TFile *F_an_data = new TFile("an_data.root");
	TTree *Tree_an_data = (TTree*)F_an_data->Get("an");
	Tree_an_data->SetBranchAddress("an",an_data);

	double bn_MC_Gap[3][2];
	TFile *F_bn_MC_Gap = new TFile("bn_MC_Gap.root");
	TTree *Tree_bn_MC_Gap = (TTree*)F_bn_MC_Gap->Get("bn");
	Tree_bn_MC_Gap->SetBranchAddress("bn",bn_MC_Gap);

	double bn_MC_Unc[3][2];
	TFile *F_bn_MC_Unc = new TFile("bn_MC_Unc.root");
	TTree *Tree_bn_MC_Unc = (TTree*)F_bn_MC_Unc->Get("bn");
	Tree_bn_MC_Unc->SetBranchAddress("bn",bn_MC_Unc);

	double bn_MC_NoGap[3][2];
	TFile *F_bn_MC_NoGap = new TFile("bn_MC_NoGap.root");
	TTree *Tree_bn_MC_NoGap = (TTree*)F_bn_MC_NoGap->Get("bn");
	Tree_bn_MC_NoGap->SetBranchAddress("bn",bn_MC_NoGap);

	double bn_MC_WithGap[3][2];
	TFile *F_bn_MC_WithGap = new TFile("bn_MC_WithGap.root");
	TTree *Tree_bn_MC_WithGap = (TTree*)F_bn_MC_WithGap->Get("bn");
	Tree_bn_MC_WithGap->SetBranchAddress("bn",bn_MC_WithGap);

	double bn_data[3][2];
	TFile *F_bn_data = new TFile("bn_data.root");
	TTree *Tree_bn_data = (TTree*)F_bn_data->Get("bn");
	Tree_bn_data->SetBranchAddress("bn",bn_data);


	double mean_an[3][NumOfBin] = {{0.0}};
	double sigma_an[3][NumOfBin] = {{0.0}};
	double mean_bn[3][NumOfBin] = {{0.0}};
	double sigma_bn[3][NumOfBin] = {{0.0}};

	double sum_mean_an[3][NumOfBin] = {{0.0}};
	double sum_sigma_an[3][NumOfBin] = {{0.0}};
	double sum_mean_bn[3][NumOfBin] = {{0.0}};
	double sum_sigma_bn[3][NumOfBin] = {{0.0}};


    FILE* m_outfile = fopen("log_result.txt", "w+");

//	fprintf(m_outfile,"Bin                    an_result             bn_result                     an_data                  bn_data                    an_MC_Gap                bn_MC_Gap                  an_MC_NoGap            bn_MC_NoGap                 an_MC_WithGap            bn_MC_WithGap                           an_result             bn_result                     an_data                  bn_data                    an_MC_Gap                bn_MC_Gap                  an_MC_NoGap            bn_MC_NoGap                 an_MC_WithGap            bn_MC_WithGap                           an_result             bn_result                     an_data                  bn_data                    an_MC_Gap                bn_MC_Gap                  an_MC_NoGap            bn_MC_NoGap                 an_MC_WithGap            bn_MC_WithGap             \n");

	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		Tree_an_MC_Gap->GetEntry(Bin);
		Tree_an_MC_Unc->GetEntry(Bin);
		Tree_an_MC_NoGap->GetEntry(Bin);
		Tree_an_MC_WithGap->GetEntry(Bin);
		Tree_an_data->GetEntry(Bin);
		Tree_bn_MC_Gap->GetEntry(Bin);
		Tree_bn_MC_Unc->GetEntry(Bin);
		Tree_bn_MC_NoGap->GetEntry(Bin);
		Tree_bn_MC_WithGap->GetEntry(Bin);
		Tree_bn_data->GetEntry(Bin);


		//calculate the result
		for(int Hidx=0;Hidx<3;Hidx++)
		{
			mean_an[Hidx][Bin] = an_data[Hidx][0] - an_MC_WithGap[Hidx][0];
			mean_bn[Hidx][Bin] = bn_data[Hidx][0] - bn_MC_WithGap[Hidx][0];
			sigma_an[Hidx][Bin] = an_MC_Unc[Hidx][1];
			sigma_bn[Hidx][Bin] = bn_MC_Unc[Hidx][1];
		
		}

		/*
		//print
		fprintf(m_outfile,"%6d  ",Bin);
		for(int Hidx=0;Hidx<3;Hidx++)
		{
			fprintf(m_outfile,"||EH%1d  %8.4f $\\pm$ %8.4f  %8.4f $\\pm$ %8.4f     %8.4f $\\pm$ %8.4f  %8.4f $\\pm$ %8.4f     %8.4f $\\pm$ %8.4f  %8.4f $\\pm$ %8.4f     %8.4f $\\pm$ %8.4f  %8.4f $\\pm$ %8.4f     %8.4f $\\pm$ %8.4f  %8.4f $\\pm$ %8.4f EH%1d||",
						Hidx+1,
						mean_an[Hidx][Bin],sigma_an[Hidx][Bin],mean_bn[Hidx][Bin],sigma_bn[Hidx][Bin],
						an_data[Hidx][0],an_data[Hidx][1],bn_data[Hidx][0],bn_data[Hidx][1],
						an_MC_Gap[Hidx][0],an_MC_Gap[Hidx][1],bn_MC_Gap[Hidx][0],bn_MC_Gap[Hidx][1],
						an_MC_NoGap[Hidx][0],an_MC_NoGap[Hidx][1],bn_MC_NoGap[Hidx][0],bn_MC_NoGap[Hidx][1],
						an_MC_WithGap[Hidx][0],an_MC_WithGap[Hidx][1],bn_MC_WithGap[Hidx][0],bn_MC_WithGap[Hidx][1],
						Hidx+1);
		}
		fprintf(m_outfile,"\n");
		*/
	

		if(Bin>0&&Bin<=(NumOfBin/2))
		{
		fprintf(m_outfile, "$%6.2f$ & $%8.4f \\pm %8.4f $ & $%8.4f \\pm %8.4f $ \\\\ \n", 
					SidToSol*706.00/(1.0*Bin),
					mean_an[2][Bin], sigma_an[2][Bin],
					mean_bn[2][Bin], sigma_bn[2][Bin]);
		}

	}
	const int nX = 1450;
	double nBins = 706.0;

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
//	style->SetHatchesLineWidth(6);
	style->cd();
	gROOT->ForceStyle();

//Draw, _abn
	
	const char* hist_Name_abn[3] = {"EH1_abn","EH2_abn","EH3_abn"};

	const char* file_Name_abn[3] = {"EH1_abn_result.eps","EH2_abn_result.eps","EH3_abn_result.eps"};
	TCanvas *myC_abn[3];

	TGraphErrors *gr_an[3];

	TLegend *leg_an[3];
	const char* leg_Name_an[3] = {"EH1_a_{n}_result","EH2_a_{n}_result","EH3_a_{n}_result"};
	TGraphErrors *gr_bn[3];

	TLegend *leg_bn[3];
	const char* leg_Name_bn[3] = {"EH1_b_{n}_result","EH2_b_{n}_result","EH3_b_{n}_result"};


	for(int Hidx=0;Hidx<3;Hidx++)
	{

		myC_abn[Hidx] = new TCanvas(hist_Name_abn[Hidx],hist_Name_abn[Hidx],0,0,800,600);
		myC_abn[Hidx]->Divide(1,2,0);
		{
		myC_abn[Hidx]->cd(1);

		double x[nX],y[nX],ex[nX],ey[nX];

		for(int Bin=0;Bin<nX;Bin++)
		{
		x[Bin] = Bin/nBins;
		int kM = int(706.0*x[Bin]);

		y[Bin] = mean_an[Hidx][kM];
		ex[Bin]=0.0;
		ey[Bin]=sigma_an[Hidx][kM];
		}
		gr_an[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_an[Hidx]->GetYaxis()->SetRangeUser(-0.017,0.017);
		gr_an[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_an[Hidx]->SetMarkerColor(1);
		gr_an[Hidx]->SetLineColor(1);
		gr_an[Hidx]->SetLineWidth(2);
		gr_an[Hidx]->SetMarkerStyle(8);
		gr_an[Hidx]->SetMarkerSize(0.5);
	//	gr_an[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_an[Hidx]->GetYaxis()->SetTitle("a");

		gr_an[Hidx]->SetTitle("");

		gr_an[Hidx]->GetYaxis()->SetTitleOffset(0.22);
		gr_an[Hidx]->GetYaxis()->SetTitleSize(0.2);
		gr_an[Hidx]->GetYaxis()->SetLabelSize(0.09);
		gr_an[Hidx]->GetYaxis()->SetLabelOffset(0.0);
		gr_an[Hidx]->GetYaxis()->CenterTitle();
		gr_an[Hidx]->GetYaxis()->SetNdivisions(505);
	
		gr_an[Hidx]->GetXaxis()->SetTitleOffset(0.7);
		gr_an[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_an[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr_an[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_an[Hidx]->Draw("APZ");

		leg_an[Hidx] = new TLegend(0.10,0.70,0.90,0.99);
		leg_an[Hidx]->AddEntry(gr_an[Hidx],leg_Name_an[Hidx],"");
		leg_an[Hidx]->SetFillStyle(0);
		leg_an[Hidx]->SetBorderSize(0);
		leg_an[Hidx]->SetTextColor(kRed);
	//	leg_an[Hidx]->Draw();
		}

	
		{
		myC_abn[Hidx]->cd(2);

		double x[nX],y[nX],ex[nX],ey[nX];

		for(int Bin=0;Bin<nX;Bin++)
		{
		x[Bin] = Bin/nBins;
		int kM = int(706.0*x[Bin]);

		y[Bin] = mean_bn[Hidx][kM];
		ex[Bin]=0.0;
		ey[Bin]=sigma_bn[Hidx][kM];
		}
		gr_bn[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_bn[Hidx]->GetYaxis()->SetRangeUser(-0.017,0.017);
		gr_bn[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_bn[Hidx]->SetMarkerColor(1);
		gr_bn[Hidx]->SetLineColor(1);
		gr_bn[Hidx]->SetLineWidth(2);
		gr_bn[Hidx]->SetMarkerStyle(8);
		gr_bn[Hidx]->SetMarkerSize(0.5);
		gr_bn[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_bn[Hidx]->GetYaxis()->SetTitle("b");

		gr_bn[Hidx]->SetTitle("");

		gr_bn[Hidx]->GetYaxis()->SetTitleOffset(0.22);
		gr_bn[Hidx]->GetYaxis()->SetTitleSize(0.2);
		gr_bn[Hidx]->GetYaxis()->SetLabelSize(0.09);
		gr_bn[Hidx]->GetYaxis()->SetLabelOffset(0.0);
		gr_bn[Hidx]->GetYaxis()->CenterTitle();
		gr_bn[Hidx]->GetYaxis()->SetNdivisions(505);
	

		gr_bn[Hidx]->GetXaxis()->SetTitleOffset(0.65);
		gr_bn[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_bn[Hidx]->GetXaxis()->SetLabelSize(0.06);
		gr_bn[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_bn[Hidx]->Draw("APZ");
	
		leg_bn[Hidx] = new TLegend(0.10,0.70,0.90,0.99);
		leg_bn[Hidx]->AddEntry(gr_bn[Hidx],leg_Name_bn[Hidx],"");
		leg_bn[Hidx]->SetFillStyle(0);
		leg_bn[Hidx]->SetBorderSize(0);
		leg_bn[Hidx]->SetTextColor(kRed);
	//	leg_bn[Hidx]->Draw();
		}
	
		myC_abn[Hidx]->SaveAs(file_Name_abn[Hidx]);
}

	
	gStyle->SetOptFit(111);

//	gStyle->SetHatchesLineWidth(2);
	gStyle->SetOptTitle(0);
//Draw histogram
	int HallID = 0;
	//EH1
	TCanvas *myC_distr_EH1 = new TCanvas("C_abn_dist_EH1","C_abn_dist_EH1",0,0,800,600);
	myC_distr_EH1->Divide(1,2,0);
	
	myC_distr_EH1->cd(1);

	TH1F *hist_an_EH1 = new TH1F("hist_an_EH1","hist_an_EH1",80,-0.017,0.017);
	for(int i=1;i<1418;i++)
	{
		hist_an_EH1->Fill(mean_an[HallID][i]);
	}
	hist_an_EH1->SetLineWidth(3);
	hist_an_EH1->Fit("gaus");
	hist_an_EH1->SetTitle("hist_a_{n}_EH1");
	hist_an_EH1->GetYaxis()->SetTitle("Entries");
	hist_an_EH1->GetXaxis()->SetTitle("a");
	hist_an_EH1->GetXaxis()->SetTitleOffset(0.8);
	hist_an_EH1->GetXaxis()->SetTitleSize(0.05);
	hist_an_EH1->GetXaxis()->SetLabelSize(0.042);
	hist_an_EH1->GetXaxis()->SetLabelOffset(0.0);
	hist_an_EH1->GetYaxis()->SetTitleOffset(0.8);
	hist_an_EH1->GetYaxis()->SetTitleSize(0.06);
	hist_an_EH1->GetYaxis()->SetLabelSize(0.06);
	hist_an_EH1->GetYaxis()->SetLabelOffset(0.0);
	hist_an_EH1->SetFillColor(4);
	hist_an_EH1->Draw("hbar");

	
	myC_distr_EH1->cd(2);
	
	TH1F *hist_bn_EH1 = new TH1F("hist_bn_EH1","hist_bn_EH1",80,-0.017,0.017);
	for(int i=1;i<1418;i++)
	{
		hist_bn_EH1->Fill(mean_bn[HallID][i]);
	}
	hist_bn_EH1->SetLineWidth(3);
	hist_bn_EH1->Fit("gaus");
	hist_bn_EH1->SetTitle("hist_b_{n}_EH1");
	hist_bn_EH1->GetYaxis()->SetTitle("Entries");
	hist_bn_EH1->GetXaxis()->SetTitle("b");
	hist_bn_EH1->GetXaxis()->SetTitleOffset(0.8);
	hist_bn_EH1->GetXaxis()->SetTitleSize(0.05);
	hist_bn_EH1->GetXaxis()->SetLabelSize(0.042);
	hist_bn_EH1->GetXaxis()->SetLabelOffset(0.0);
	hist_bn_EH1->GetYaxis()->SetTitleOffset(0.8);
	hist_bn_EH1->GetYaxis()->SetTitleSize(0.06);
	hist_bn_EH1->GetYaxis()->SetLabelSize(0.06);
	hist_bn_EH1->GetYaxis()->SetLabelOffset(0.0);
	hist_bn_EH1->SetFillColor(4);
	hist_bn_EH1->Draw("hbar");

	myC_distr_EH1->RedrawAxis();
	myC_distr_EH1->Update();
	myC_distr_EH1->SaveAs("EH1_abn_dist.eps");
	myC_distr_EH1->SaveAs("EH1_abn_dist.eps");

	HallID = 1;
	//EH2
	TCanvas *myC_distr_EH2 = new TCanvas("C_abn_dist_EH2","C_abn_dist_EH2",0,0,800,600);
	myC_distr_EH2->Divide(1,2,0);
	
	myC_distr_EH2->cd(1);

	TH1F *hist_an_EH2 = new TH1F("hist_an_EH2","hist_an_EH2",80,-0.017,0.017);
	for(int i=1;i<1418;i++)
	{
		hist_an_EH2->Fill(mean_an[HallID][i]);
	}
	hist_an_EH2->SetLineWidth(3);
	hist_an_EH2->Fit("gaus");
	hist_an_EH2->SetTitle("hist_a_{n}_EH2");
	hist_an_EH2->GetYaxis()->SetTitle("Entries");
	hist_an_EH2->GetXaxis()->SetTitle("a");
	hist_an_EH2->GetXaxis()->SetTitleOffset(0.8);
	hist_an_EH2->GetXaxis()->SetTitleSize(0.05);
	hist_an_EH2->GetXaxis()->SetLabelSize(0.042);
	hist_an_EH2->GetXaxis()->SetLabelOffset(0.0);
	hist_an_EH2->GetYaxis()->SetTitleOffset(0.8);
	hist_an_EH2->GetYaxis()->SetTitleSize(0.06);
	hist_an_EH2->GetYaxis()->SetLabelSize(0.06);
	hist_an_EH2->GetYaxis()->SetLabelOffset(0.0);
	hist_an_EH2->SetFillColor(4);
	hist_an_EH2->Draw("hbar");

	
	myC_distr_EH2->cd(2);
	
	TH1F *hist_bn_EH2 = new TH1F("hist_bn_EH2","hist_bn_EH2",80,-0.017,0.017);
	for(int i=1;i<1418;i++)
	{
		hist_bn_EH2->Fill(mean_bn[HallID][i]);
	}
	hist_bn_EH2->SetLineWidth(3);
	hist_bn_EH2->Fit("gaus");
	hist_bn_EH2->SetTitle("hist_b_{n}_EH2");
	hist_bn_EH2->GetYaxis()->SetTitle("Entries");
	hist_bn_EH2->GetXaxis()->SetTitle("b");
	hist_bn_EH2->GetXaxis()->SetTitleOffset(0.8);
	hist_bn_EH2->GetXaxis()->SetTitleSize(0.05);
	hist_bn_EH2->GetXaxis()->SetLabelSize(0.042);
	hist_bn_EH2->GetXaxis()->SetLabelOffset(0.0);
	hist_bn_EH2->GetYaxis()->SetTitleOffset(0.8);
	hist_bn_EH2->GetYaxis()->SetTitleSize(0.06);
	hist_bn_EH2->GetYaxis()->SetLabelSize(0.06);
	hist_bn_EH2->GetYaxis()->SetLabelOffset(0.0);
	hist_bn_EH2->SetFillColor(4);
	hist_bn_EH2->Draw("hbar");

	myC_distr_EH2->RedrawAxis();
	myC_distr_EH2->Update();
	myC_distr_EH2->SaveAs("EH2_abn_dist.eps");
	myC_distr_EH2->SaveAs("EH2_abn_dist.eps");

	HallID = 2;
	//EH3

	TCanvas *myC_distr_EH3 = new TCanvas("C_abn_dist_EH3","C_abn_dist_EH3",0,0,800,600);
	myC_distr_EH3->Divide(1,2,0);
	
	myC_distr_EH3->cd(1);
	TF1 *f_an = new TF1("gaus","gaus",-0.017,0.017);
	TF1 *f_bn = new TF1("gaus","gaus",-0.017,0.017);
	
	TH1F *hist_an_EH3 = new TH1F("hist_an_EH3","hist_an_EH3",50,-0.017,0.017);
	for(int i=1;i<1418;i++)
	{
		hist_an_EH3->Fill(mean_an[HallID][i]);
	}
	hist_an_EH3->Fit(f_an);
	hist_an_EH3->SetLineWidth(3);
	hist_an_EH3->SetFillColor(4);
//	hist_an_EH3->SetFillStyle(3010);
	hist_an_EH3->SetTitle("hist_a_{n}_EH3");
	hist_an_EH3->GetYaxis()->SetTitle("Entries");
	hist_an_EH3->GetXaxis()->SetTitle("a");
	hist_an_EH3->GetXaxis()->CenterTitle();
	hist_an_EH3->GetXaxis()->SetTitleOffset(0.22);
	hist_an_EH3->GetXaxis()->SetTitleSize(0.2);
	hist_an_EH3->GetXaxis()->SetLabelSize(0.09);
	hist_an_EH3->GetXaxis()->SetLabelOffset(0.0);
	hist_an_EH3->GetYaxis()->SetRangeUser(0,139);
	hist_an_EH3->GetYaxis()->SetTitleOffset(0.8);
	hist_an_EH3->GetYaxis()->SetTitleSize(0.09);
	hist_an_EH3->GetYaxis()->SetLabelSize(0.06);
	hist_an_EH3->GetYaxis()->SetLabelOffset(0.0);
	hist_an_EH3->Draw("hbar");

	TH1F *hist_an_EH3_2 = (TH1F*)hist_an_EH3->Clone("hist_an_EH3_2");

	hist_an_EH3_2->SetFillColor(19);
	hist_an_EH3_2->SetMarkerColor(4);
	hist_an_EH3_2->SetLineColor(4);
	hist_an_EH3_2->SetFillStyle(3015);
	
	hist_an_EH3_2->Draw("hbarsame");
	
	
	cout<<"GetParameter................."<<endl;
	double c_an = f_an->GetParameter("Constant");
	double m_an = f_an->GetParameter("Mean");
	double s_an = f_an->GetParameter("Sigma");
    
	cout<<c_an<<endl;
	cout<<m_an<<endl;
	cout<<s_an<<endl;
	//draw the gaussian fit curve
	TF1 *f_an_1 = new TF1("f_an_1",PlotFunc_1,0.0001,c_an,3);
	f_an_1->SetParameter(0,c_an);
	f_an_1->SetParameter(1,m_an);
	f_an_1->SetParameter(2,s_an);
	f_an_1->SetLineColor(2);
	f_an_1->SetNpx(10000);
	f_an_1->Draw("same");
	
	TF1 *f_an_2 = new TF1("f_an_2",PlotFunc_2,0.0001,c_an,3);
	f_an_2->SetParameter(0,c_an);
	f_an_2->SetParameter(1,m_an);
	f_an_2->SetParameter(2,s_an);
	f_an_2->SetLineColor(2);
	f_an_2->SetNpx(10000);
	f_an_2->Draw("same");
	


	
	myC_distr_EH3->cd(2);
	
	TH1F *hist_bn_EH3 = new TH1F("hist_bn_EH3","hist_bn_EH3",50,-0.017,0.017);
	for(int i=1;i<1418;i++)
	{
		hist_bn_EH3->Fill(mean_bn[HallID][i]);
	}
	hist_bn_EH3->Fit(f_bn);
	hist_bn_EH3->SetLineWidth(3);
	hist_bn_EH3->SetFillColor(4);
	hist_bn_EH3->SetFillStyle(3010);
	hist_bn_EH3->SetTitle("hist_b_{n}_EH3");
	hist_bn_EH3->GetYaxis()->SetTitle("Entries");
	hist_bn_EH3->GetXaxis()->SetTitle("b");
	hist_bn_EH3->GetXaxis()->CenterTitle();
	hist_bn_EH3->GetXaxis()->SetTitleOffset(0.22);
	hist_bn_EH3->GetXaxis()->SetTitleSize(0.2);
	hist_bn_EH3->GetXaxis()->SetLabelSize(0.09);
	hist_bn_EH3->GetXaxis()->SetLabelOffset(0.0);
	hist_bn_EH3->GetYaxis()->SetTitleOffset(0.4);
	hist_bn_EH3->GetYaxis()->SetRangeUser(0,139);
	hist_bn_EH3->GetYaxis()->SetTitleSize(0.09);
	hist_bn_EH3->GetYaxis()->SetLabelSize(0.09);
	hist_bn_EH3->GetYaxis()->SetLabelOffset(0.0);
//	hist_bn_EH3->SetFillColor(4);
	hist_bn_EH3->Draw("hbar");

	
	cout<<"GetParameter................."<<endl;
	double c_bn = f_bn->GetParameter("Constant");
	double m_bn = f_bn->GetParameter("Mean");
	double s_bn = f_bn->GetParameter("Sigma");
    
	cout<<c_bn<<endl;
	cout<<m_bn<<endl;
	cout<<s_bn<<endl;
	//draw the gaussian fit curve
	TF1 *f_bn_1 = new TF1("f_bn_1",PlotFunc_1,0.0001,c_bn,3);
	f_bn_1->SetParameter(0,c_bn);
	f_bn_1->SetParameter(1,m_bn);
	f_bn_1->SetParameter(2,s_bn);
	f_bn_1->SetLineColor(kRed);
	f_bn_1->SetNpx(10000);
	f_bn_1->Draw("same");
	
	TF1 *f_bn_2 = new TF1("f_bn_2",PlotFunc_2,0.0001,c_bn,3);
	f_bn_2->SetParameter(0,c_bn);
	f_bn_2->SetParameter(1,m_bn);
	f_bn_2->SetParameter(2,s_bn);
	f_bn_2->SetLineColor(kRed);
	f_bn_2->SetNpx(10000);
	f_bn_2->Draw("same");
	

	myC_distr_EH3->RedrawAxis();
	myC_distr_EH3->Update();
	myC_distr_EH3->SaveAs("EH3_abn_dist.eps");
	myC_distr_EH3->SaveAs("EH3_abn_dist.eps");

///////////////////////////////////////////////////////////////
	//print the outliers//

	double sigma_distr[3][2]={	{0.001484,0.001506},
								{0.001757,0.001796},
								{0.003313,0.003139}};

	for(int Hidx=0;Hidx<3;Hidx++)
	{
	for(int n=1;n<1450;n++)
	{
		if(mean_an[Hidx][n]<-3.0*sigma_distr[Hidx][0]||mean_an[Hidx][n]>3.0*sigma_distr[Hidx][0])
		{
		fprintf(stderr,"EH%1d - $a_{n}$ ($\\sigma=$%7.4f)&$T=%6.1f$ sidereal days&$a_{n}=%7.4f\\pm%7.4f$\\\\ \n",Hidx+1,sigma_distr[Hidx][0],706.0/n,mean_an[Hidx][n],sigma_an[Hidx][n]);
		}
	}

	for(int n=1;n<1450;n++)
	{
	if(mean_bn[Hidx][n]<-3.0*sigma_distr[Hidx][1]||mean_bn[Hidx][n]>3.0*sigma_distr[Hidx][1])
		{
		fprintf(stderr,"EH%1d - $b_{n}$ ($\\sigma=$%7.4f)&$T=%6.1f$ sidereal days&$b_{n}=%7.4f\\pm%7.4f$\\\\ \n",Hidx+1,sigma_distr[Hidx][0],706.0/n,mean_bn[Hidx][n],sigma_bn[Hidx][n]);
		}
	}
	}


	}

Double_t PlotFunc_1(Double_t *x, Double_t *par)
{
	return par[1] + sqrt(-2.0*par[2]*par[2]*log(x[0]/par[0]));
}
Double_t PlotFunc_2(Double_t *x, Double_t *par)
{
	return par[1] - sqrt(-2.0*par[2]*par[2]*log(x[0]/par[0]));
}



