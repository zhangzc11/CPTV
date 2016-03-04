
#include <string>
#include <fstream>
#include <sstream>


void LiveTime()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968

	Double_t TotalLiveTime[8]={0.0};
	Double_t LiveTime_t[8];

	Double_t LiveTimeInOneDay[8][24];
	memset(LiveTimeInOneDay,0.0,sizeof(LiveTimeInOneDay));

	TFile *F_LiveTime = new TFile("../LiveTime.root");
	TTree *Tree_LiveTime = (TTree*)F_LiveTime->Get("LiveTime");
	Tree_LiveTime->SetBranchAddress("LiveTime",LiveTime_t);

	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N24 = Bin%24;
		Tree_LiveTime->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			LiveTimeInOneDay[Det][N24] += LiveTime_t[Det];
			TotalLiveTime[Det] += LiveTime_t[Det];
		}
	}
	
	const char *hist_Name[8] = {"EH1_AD1","EH1_AD2","EH2_AD1","EH2_AD2","EH3_AD1","EH3_AD2","EH3_AD3","EH3_AD4"}; 
	const char *file_Name[8] = {
		"LiveTimeInOneDay_EH1_AD1.pdf","LiveTimeInOneDay_EH1_AD2.pdf","LiveTimeInOneDay_EH2_AD1.pdf","LiveTimeInOneDay_EH2_AD2.pdf",
		"LiveTimeInOneDay_EH3_AD1.pdf","LiveTimeInOneDay_EH3_AD2.pdf","LiveTimeInOneDay_EH3_AD3.pdf","LiveTimeInOneDay_EH3_AD4.pdf"};
	TCanvas *myC[8];
	TH1F *my_h[8];
	TLegend *leg[8];
	for(int Det=0;Det<8;Det++)
	{
		myC[Det] = new TCanvas(hist_Name[Det],hist_Name[Det],0,0,800,420);
		my_h[Det] = new TH1F(hist_Name[Det],hist_Name[Det],24,0,24);
	    for(int i=0;i<24;i++)
	    {
		   my_h[Det]->SetBinContent(i+1,LiveTimeInOneDay[Det][i]);
	    }
		cout<<"Total LiveTime of "<<hist_Name[Det]<<" (days):   "<<TotalLiveTime[Det]/86400.0<<endl;

		my_h[Det]->GetXaxis()->SetTitle("solar time(1 bin = 3600.0 seconds)");
	my_h[Det]->GetYaxis()->SetTitle("DAQ Livetime /seconds");
	//my_h[Det]->GetYaxis()->SetRangeUser(1990*1e3,2080*1e3);
	my_h[Det]->GetXaxis()->SetRangeUser(0,24);
	my_h[Det]->GetXaxis()->SetNdivisions(24);
	
	my_h[Det]->SetTitle("");
	my_h[Det]->SetLineWidth(3);

	my_h[Det]->GetYaxis()->SetTitleOffset(0.7);
	my_h[Det]->GetYaxis()->SetTitleSize(0.07);
	my_h[Det]->GetYaxis()->SetLabelSize(0.06);
	my_h[Det]->GetYaxis()->SetLabelOffset(0.0);
	
	my_h[Det]->GetXaxis()->SetTitleOffset(0.8);
	my_h[Det]->GetXaxis()->SetTitleSize(0.06);
	my_h[Det]->GetXaxis()->SetLabelSize(0.045);
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


	//save
	TFile  *F_LiveTimeInOneDay = new TFile("LiveTimeInOneDay.root","recreate");
	TTree *Tree_LiveTimeInOneDay = new TTree("LiveTimeInOneDay","LiveTimeInOneDay");
	Tree_LiveTimeInOneDay->Branch("LiveTimeInOneDay",LiveTime_t,"LiveTime_t[8]/D");

	for(int Bin=0; Bin<24;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			LiveTime_t[Det] = LiveTimeInOneDay[Det][Bin];
		}
		Tree_LiveTimeInOneDay->Fill();
	}
	Tree_LiveTimeInOneDay->Write();

}