
#include <string>
#include <fstream>
#include <sstream>


void AlphaBeta()
{
	Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324678393.80705;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;//17016

	Double_t AlphaBeta_t[2];
	

	Double_t AlphaBetaInOneDay[2][24];
	memset(AlphaBetaInOneDay,0.0,sizeof(AlphaBetaInOneDay));

	TFile *F_AlphaBeta = new TFile("../AlphaBeta.root");
	TTree *Tree_AlphaBeta = (TTree*)F_AlphaBeta->Get("AlphaBeta");
	Tree_AlphaBeta->SetBranchAddress("AlphaBeta",AlphaBeta_t);

	for(int Bin=0;Bin<24;Bin++)
	{
		Tree_AlphaBeta->GetEntry(Bin);
		AlphaBetaInOneDay[0][Bin] = AlphaBeta_t[0];
		AlphaBetaInOneDay[1][Bin] = AlphaBeta_t[1];
	}
	

	Double_t Ave_AlphaBeta[2]={0.0};
	for(int i=0;i<2;i++)
	{
		for(int N24=0;N24<24;N24++)
		{
			Ave_AlphaBeta[i] += AlphaBetaInOneDay[i][N24];
		}
	}
	cout<<"Ave_Alpha:  "<<Ave_AlphaBeta[0]/24.0<<endl;
	cout<<"Ave_Beta:  "<<Ave_AlphaBeta[1]/24.0<<endl;
	
	const char *hist_Name[2] = {"Alpha","Beta"};
	const char *file_Name[2] = {"Alpha.pdf","Beta.pdf"};
	TCanvas *myC[2];
	TH1F *my_h[2];
	TLegend *leg[2];
	for(int Det=0;Det<2;Det++)
	{
		myC[Det] = new TCanvas(hist_Name[Det],hist_Name[Det],0,0,800,600);
		my_h[Det] = new TH1F(hist_Name[Det],hist_Name[Det],24,0,24);
	    for(int i=0;i<24;i++)
	    {
		   my_h[Det]->SetBinContent(i+1,AlphaBetaInOneDay[Det][i]);
		   cout<<i<<"   "<<AlphaBetaInOneDay[Det][i]<<endl;
	    }
		

		my_h[Det]->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.09/24.00 seconds)");
	//my_h[Det]->GetYaxis()->SetTitle("DAQ Livetime /seconds");
	//my_h[Det]->GetYaxis()->SetRangeUser(1990*1e3,2080*1e3);
	my_h[Det]->GetXaxis()->SetRangeUser(0,24);
	my_h[Det]->GetXaxis()->SetNdivisions(24);
	
	my_h[Det]->SetTitle("");
	my_h[Det]->SetLineWidth(3);

	my_h[Det]->GetYaxis()->SetTitleOffset(0.7);
	my_h[Det]->GetYaxis()->SetTitleSize(0.07);
	my_h[Det]->GetYaxis()->SetLabelSize(0.05);
	my_h[Det]->GetYaxis()->SetLabelOffset(0.0);
	
	my_h[Det]->GetXaxis()->SetTitleOffset(0.8);
	my_h[Det]->GetXaxis()->SetTitleSize(0.06);
	my_h[Det]->GetXaxis()->SetLabelSize(0.035);
	my_h[Det]->GetXaxis()->SetLabelOffset(0.0);
	
	my_h[Det]->Draw();

   leg[Det] = new TLegend(0.35, 0.75, 0.65, 0.9);
   leg[Det]->AddEntry(my_h[Det],hist_Name[Det],"");
   leg[Det]->SetFillStyle(0);
   leg[Det]->SetBorderSize(0);
   leg[Det]->SetTextColor(kRed);
   leg[Det]->Draw();

	myC[Det]->SaveAs(file_Name[Det]);
	}

	for(int i=0;i<12;i++)
	{
		fprintf(stderr,"%5d  & ",i);
	}
	fprintf(stderr,"\\\\ \\hline \n");

	for(int i=0;i<12;i++)
	{
		fprintf(stderr,"%10.6f & ",AlphaBetaInOneDay[0][i]);
	}
	fprintf(stderr,"\\\\ \\hline \n");
	for(int i=0;i<12;i++)
	{
		fprintf(stderr,"%10.6f & ",AlphaBetaInOneDay[1][i]);
	}
	fprintf(stderr,"\\\\ \\hline \n");

	for(int i=12;i<24;i++)
	{
		fprintf(stderr,"%5d  & ",i);
	}
	fprintf(stderr,"\\\\ \\hline \n");

	for(int i=12;i<24;i++)
	{
		fprintf(stderr,"%10.6f & ",AlphaBetaInOneDay[0][i]);
	}
	fprintf(stderr,"\\\\ \\hline \n");
	for(int i=12;i<24;i++)
	{
		fprintf(stderr,"%10.6f & ",AlphaBetaInOneDay[1][i]);
	}
	fprintf(stderr,"\\\\ \\hline \n");

}