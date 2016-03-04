

#include <math.h>

const int NumOfBin = 16944;

void FFT_result_NE()
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

	fprintf(m_outfile,"Bin                    an_result             bn_result                     an_data                  bn_data                    an_MC_Gap                bn_MC_Gap                  an_MC_NoGap            bn_MC_NoGap                 an_MC_WithGap            bn_MC_WithGap                           an_result             bn_result                     an_data                  bn_data                    an_MC_Gap                bn_MC_Gap                  an_MC_NoGap            bn_MC_NoGap                 an_MC_WithGap            bn_MC_WithGap                           an_result             bn_result                     an_data                  bn_data                    an_MC_Gap                bn_MC_Gap                  an_MC_NoGap            bn_MC_NoGap                 an_MC_WithGap            bn_MC_WithGap             \n");

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

		//	sigma_an[Hidx][Bin] = an_MC_WithGap[Hidx][1]+an_MC_Gap[Hidx][1];//sqrt(pow(an_MC_WithGap[Hidx][1],2.0)+pow(an_MC_Gap[Hidx][1],2.0));
		//	sigma_bn[Hidx][Bin] = bn_MC_WithGap[Hidx][1]+bn_MC_Gap[Hidx][1];//sqrt(pow(bn_MC_WithGap[Hidx][1],2.0)+pow(bn_MC_Gap[Hidx][1],2.0));
	
		//	sum_mean_an[Hidx][Bin] = an_MC_WithGap[Hidx][0] + an_MC_Gap[Hidx][0];
		//	sum_mean_bn[Hidx][Bin] = bn_MC_WithGap[Hidx][0] + bn_MC_Gap[Hidx][0];
		//	sum_sigma_an[Hidx][Bin] = an_MC_WithGap[Hidx][1]+an_MC_Gap[Hidx][1];//sqrt(pow(an_MC_WithGap[Hidx][1],2.0)+pow(an_MC_Gap[Hidx][1],2.0));
		//	sum_sigma_bn[Hidx][Bin] = bn_MC_WithGap[Hidx][1]+bn_MC_Gap[Hidx][1];//sqrt(pow(bn_MC_WithGap[Hidx][1],2.0)+pow(bn_MC_Gap[Hidx][1],2.0));
		
		}

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
	}

	const int nX = 1450;
	double nBins = 706.0;



//Draw, _abn
	
	const char* hist_Name_abn[3] = {"EH1_abn","EH2_abn","EH3_abn"};

	const char* file_Name_abn[3] = {"EH1_abn_result_NE.eps","EH2_abn_result_NE.eps","EH3_abn_result_NE.eps"};
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
		ey[Bin]=0.0;//sigma_an[Hidx][kM];
		}
		gr_an[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_an[Hidx]->GetYaxis()->SetRangeUser(-0.015,0.015);
		gr_an[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_an[Hidx]->SetMarkerColor(kBlue);
		gr_an[Hidx]->SetLineColor(kBlue);
		gr_an[Hidx]->SetLineWidth(2);
		gr_an[Hidx]->SetMarkerStyle(8);
		gr_an[Hidx]->SetMarkerSize(0.5);
		gr_an[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_an[Hidx]->GetYaxis()->SetTitle("a");

		gr_an[Hidx]->SetTitle("");

		gr_an[Hidx]->GetYaxis()->SetTitleOffset(0.6);
		gr_an[Hidx]->GetYaxis()->SetTitleSize(0.08);
		gr_an[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_an[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
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
		leg_an[Hidx]->Draw();
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
		ey[Bin]=0.0;//sigma_bn[Hidx][kM];
		}
		gr_bn[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_bn[Hidx]->GetYaxis()->SetRangeUser(-0.015,0.015);
		gr_bn[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_bn[Hidx]->SetMarkerColor(kBlue);
		gr_bn[Hidx]->SetLineColor(kBlue);
		gr_bn[Hidx]->SetLineWidth(2);
		gr_bn[Hidx]->SetMarkerStyle(8);
		gr_bn[Hidx]->SetMarkerSize(0.5);
		gr_bn[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_bn[Hidx]->GetYaxis()->SetTitle("b");

		gr_bn[Hidx]->SetTitle("");

		gr_bn[Hidx]->GetYaxis()->SetTitleOffset(0.6);
		gr_bn[Hidx]->GetYaxis()->SetTitleSize(0.08);
		gr_bn[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_bn[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
		gr_bn[Hidx]->GetXaxis()->SetTitleOffset(0.7);
		gr_bn[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_bn[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr_bn[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_bn[Hidx]->Draw("APZ");
	
		leg_bn[Hidx] = new TLegend(0.10,0.70,0.90,0.99);
		leg_bn[Hidx]->AddEntry(gr_bn[Hidx],leg_Name_bn[Hidx],"");
		leg_bn[Hidx]->SetFillStyle(0);
		leg_bn[Hidx]->SetBorderSize(0);
		leg_bn[Hidx]->SetTextColor(kRed);
		leg_bn[Hidx]->Draw();
		}
	
		myC_abn[Hidx]->SaveAs(file_Name_abn[Hidx]);
}



//Draw, _abn_sum
	
	const char* hist_Name_abn_sum[3] = {"EH1_abn_sum","EH2_abn_sum","EH3_abn_sum"};

	const char* file_Name_abn_sum[3] = {"EH1_abn_sum_result_NE.eps","EH2_abn_sum_result_NE.eps","EH3_abn_sum_result_NE.eps"};
	TCanvas *myC_abn_sum[3];

	TGraphErrors *gr_an_sum[3];

	TLegend *leg_an_sum[3];
	const char* leg_Name_an_sum[3] = {"EH1 - MC - a_{n} ","EH2 - MC - a_{n} ","EH3 - MC - a_{n} "};
	TGraphErrors *gr_bn_sum[3];

	TLegend *leg_bn_sum[3];
	const char* leg_Name_bn_sum[3] = {"EH1 - MC - b_{n} ","EH2 - MC - b_{n} ","EH3 - MC - b_{n} "};


	for(int Hidx=0;Hidx<3;Hidx++)
	{

		myC_abn_sum[Hidx] = new TCanvas(hist_Name_abn_sum[Hidx],hist_Name_abn_sum[Hidx],0,0,800,600);
		myC_abn_sum[Hidx]->Divide(1,2,0);
		{
		myC_abn_sum[Hidx]->cd(1);

		double x[nX],y[nX],ex[nX],ey[nX];

		for(int Bin=0;Bin<nX;Bin++)
		{
		x[Bin] = Bin/nBins;
		int kM = int(706.0*x[Bin]);

		y[Bin] = sum_mean_an[Hidx][kM];
		ex[Bin]=0.0;
		ey[Bin]=0.0;//sum_sigma_an[Hidx][kM];
		}
		gr_an_sum[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_an_sum[Hidx]->GetYaxis()->SetRangeUser(-0.015,0.015);
		gr_an_sum[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_an_sum[Hidx]->SetMarkerColor(kBlue);
		gr_an_sum[Hidx]->SetLineColor(kBlue);
		gr_an_sum[Hidx]->SetLineWidth(2);
		gr_an_sum[Hidx]->SetMarkerStyle(8);
		gr_an_sum[Hidx]->SetMarkerSize(0.5);
		gr_an_sum[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_an_sum[Hidx]->GetYaxis()->SetTitle("a");

		gr_an_sum[Hidx]->SetTitle("");

		gr_an_sum[Hidx]->GetYaxis()->SetTitleOffset(0.6);
		gr_an_sum[Hidx]->GetYaxis()->SetTitleSize(0.08);
		gr_an_sum[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_an_sum[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
		gr_an_sum[Hidx]->GetXaxis()->SetTitleOffset(0.7);
		gr_an_sum[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_an_sum[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr_an_sum[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_an_sum[Hidx]->Draw("APZ");

		leg_an_sum[Hidx] = new TLegend(0.10,0.65,0.90,0.98);
		leg_an_sum[Hidx]->AddEntry(gr_an_sum[Hidx],leg_Name_an_sum[Hidx],"");
		leg_an_sum[Hidx]->SetFillStyle(0);
		leg_an_sum[Hidx]->SetBorderSize(0);
		leg_an_sum[Hidx]->SetTextColor(kRed);
		leg_an_sum[Hidx]->Draw();
		}

	
		{
		myC_abn_sum[Hidx]->cd(2);

		double x[nX],y[nX],ex[nX],ey[nX];

		for(int Bin=0;Bin<nX;Bin++)
		{
		x[Bin] = Bin/nBins;
		int kM = int(706.0*x[Bin]);

		y[Bin] = sum_mean_bn[Hidx][kM];
		ex[Bin]=0.0;
		ey[Bin]=0.0;//sum_sigma_bn[Hidx][kM];
		}
		gr_bn_sum[Hidx] = new TGraphErrors(nX,x,y,ex,ey);
		gr_bn_sum[Hidx]->GetYaxis()->SetRangeUser(-0.015,0.015);
		gr_bn_sum[Hidx]->GetXaxis()->SetRangeUser(0,nX/nBins);
		gr_bn_sum[Hidx]->SetMarkerColor(kBlue);
		gr_bn_sum[Hidx]->SetLineColor(kBlue);
		gr_bn_sum[Hidx]->SetLineWidth(2);
		gr_bn_sum[Hidx]->SetMarkerStyle(8);
		gr_bn_sum[Hidx]->SetMarkerSize(0.5);
		gr_bn_sum[Hidx]->GetXaxis()->SetTitle("#omega/#omega_{0}, #omega_{0}=2#pi/1 sidereal day");
		gr_bn_sum[Hidx]->GetYaxis()->SetTitle("b");

		gr_bn_sum[Hidx]->SetTitle("");

		gr_bn_sum[Hidx]->GetYaxis()->SetTitleOffset(0.6);
		gr_bn_sum[Hidx]->GetYaxis()->SetTitleSize(0.08);
		gr_bn_sum[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr_bn_sum[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
		gr_bn_sum[Hidx]->GetXaxis()->SetTitleOffset(0.7);
		gr_bn_sum[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr_bn_sum[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr_bn_sum[Hidx]->GetXaxis()->SetLabelOffset(0.0);
		gr_bn_sum[Hidx]->Draw("APZ");
	
		leg_bn_sum[Hidx] = new TLegend(0.10,0.65,0.90,0.98);
		leg_bn_sum[Hidx]->AddEntry(gr_bn_sum[Hidx],leg_Name_bn_sum[Hidx],"");
		leg_bn_sum[Hidx]->SetFillStyle(0);
		leg_bn_sum[Hidx]->SetBorderSize(0);
		leg_bn_sum[Hidx]->SetTextColor(kRed);
		leg_bn_sum[Hidx]->Draw();
		}
	
		myC_abn_sum[Hidx]->SaveAs(file_Name_abn_sum[Hidx]);
}




}
