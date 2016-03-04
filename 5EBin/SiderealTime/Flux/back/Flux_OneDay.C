

void Flux_OneDay()
{

	Double_t WidthOfBin = 86164.00/24.00;// 1 sidereal day = 86164 seconds
	Double_t StartTime = 1324678393.80705;//in unit of second,it stands for 2011-12-24 00:00:00, UTC 0 time;
	Double_t EndTime = 1385769600;//in unit of second,it stands for 2012-07-28 00:00:00, UTC 0 time;
	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;

	Int_t StartBin8AD =7080;//first,BinNo
	Int_t EndBin6AD = 5221;//last,BinNo

	Double_t Flux[8];
	Double_t Flux_Day[8][24];
	memset(Flux_Day,0.0,sizeof(Flux_Day));

	TFile *FFlux= new TFile("Flux.root");
	TTree *FluxTree= (TTree*)FFlux->Get("Flux");
	FluxTree->SetBranchAddress("Flux",Flux);

	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		FluxTree->GetEntry(Bin);
		Int_t N24=Bin%24;
		if((Bin<=EndBin6AD)||(Bin>=StartBin8AD))
		{
			for(int i=0;i<8;i++)
			{
				Flux_Day[i][N24] += Flux[i];
			}
		}

	}

	 gStyle->SetOptStat(0);
	
	TH1F *h1 = new TH1F("h1","Flux",24,0,24);
	TH1F *h2 = new TH1F("h2","Flux",24,0,24);
	TH1F *h3 = new TH1F("h3","Flux",24,0,24);
	TH1F *h4 = new TH1F("h4","Flux",24,0,24);
	TH1F *h5 = new TH1F("h5","Flux",24,0,24);
	TH1F *h6 = new TH1F("h6","Flux",24,0,24);
	TH1F *h7 = new TH1F("h7","Flux",24,0,24);
	TH1F *h8 = new TH1F("h8","Flux",24,0,24);
	for(int Bin=0;Bin<24;Bin++)
	{
		h1->SetBinContent(Bin,Flux_Day[0][Bin]);
		h2->SetBinContent(Bin,Flux_Day[1][Bin]);
		h3->SetBinContent(Bin,Flux_Day[2][Bin]);
		h4->SetBinContent(Bin,Flux_Day[3][Bin]);
		h5->SetBinContent(Bin,Flux_Day[4][Bin]);
		h6->SetBinContent(Bin,Flux_Day[5][Bin]);
		h7->SetBinContent(Bin,Flux_Day[6][Bin]);
		h8->SetBinContent(Bin,Flux_Day[7][Bin]);
	}
	TCanvas *c1 = new TCanvas("c1","Flux_AD",0,0,1200,900);
	//h1->SetLineColor(kRed);
	h1->SetTitle("Flux seen in EH1_AD1");
	h1->GetXaxis()->SetTitle("Time(number of sidereal hours start from 2011-12-24 00:00:00)");
	h1->GetYaxis()->SetTitle("Flux");
	//h1->GetYaxis()->SetRangeUser(0.48*1e6,0.58*1e6);
	h1->GetXaxis()->SetRangeUser(0,23);
	h1->GetXaxis()->SetNdivisions(24);
	h1->GetYaxis()->SetTitleOffset(1.3);
	h1->Draw();
	c1->SaveAs("Flux_OneDay_EH1_AD1.gif");

	TCanvas *c2 = new TCanvas("c2","Flux_AD",0,0,1200,900);
	//h2->SetLineColor(kRed);
	h2->SetTitle("Flux seen in EH1_AD2");
	h2->GetXaxis()->SetTitle("Time(number of sidereal hours start from 2011-12-24 00:00:00)");
	h2->GetYaxis()->SetTitle("Flux");
	//h2->GetYaxis()->SetRangeUser(0.48*1e6,0.58*1e6);
	h2->GetXaxis()->SetRangeUser(0,23);
	h2->GetXaxis()->SetNdivisions(24);
	h2->GetYaxis()->SetTitleOffset(1.3);
	h2->Draw();
	c2->SaveAs("Flux_OneDay_EH1_AD2.gif");

	TCanvas *c3 = new TCanvas("c3","Flux_AD",0,0,1200,900);
	//h3->SetLineColor(kRed);
	h3->SetTitle("Flux seen in EH2_AD1");
	h3->GetXaxis()->SetTitle("Time(number of sidereal hours start from 2011-12-24 00:00:00)");
	h3->GetYaxis()->SetTitle("Flux");
	//h3->GetYaxis()->SetRangeUser(0.48*1e6,0.58*1e6);
	h3->GetXaxis()->SetRangeUser(0,23);
	h3->GetXaxis()->SetNdivisions(24);
	h3->GetYaxis()->SetTitleOffset(1.3);
	h3->Draw();
	c3->SaveAs("Flux_OneDay_EH2_AD1.gif");

	TCanvas *c4 = new TCanvas("c4","Flux_AD",0,0,1200,900);
	//h4->SetLineColor(kRed);
	h4->SetTitle("Flux seen in EH2_AD2");
	h4->GetXaxis()->SetTitle("Time(number of sidereal hours start from 2011-12-24 00:00:00)");
	h4->GetYaxis()->SetTitle("Flux");
	//h4->GetYaxis()->SetRangeUser(0.48*1e6,0.58*1e6);
	h4->GetXaxis()->SetRangeUser(0,23);
	h4->GetXaxis()->SetNdivisions(24);
	h4->GetYaxis()->SetTitleOffset(1.3);
	h4->Draw();
	c4->SaveAs("Flux_OneDay_EH2_AD2.gif");

	TCanvas *c5 = new TCanvas("c5","Flux_AD",0,0,1200,900);
	//h5->SetLineColor(kRed);
	h5->SetTitle("Flux seen in EH3_AD1");
	h5->GetXaxis()->SetTitle("Time(number of sidereal hours start from 2011-12-24 00:00:00)");
	h5->GetYaxis()->SetTitle("Flux");
	//h5->GetYaxis()->SetRangeUser(0.48*1e6,0.58*1e6);
	h5->GetXaxis()->SetRangeUser(0,23);
	h5->GetXaxis()->SetNdivisions(24);
	h5->GetYaxis()->SetTitleOffset(1.3);
	h5->Draw();
	c5->SaveAs("Flux_OneDay_EH3_AD1.gif");

	TCanvas *c6 = new TCanvas("c6","Flux_AD",0,0,1200,900);
	//h6->SetLineColor(kRed);
	h6->SetTitle("Flux seen in EH3_AD2");
	h6->GetXaxis()->SetTitle("Time(number of sidereal hours start from 2011-12-24 00:00:00)");
	h6->GetYaxis()->SetTitle("Flux");
	//h6->GetYaxis()->SetRangeUser(0.48*1e6,0.58*1e6);
	h6->GetXaxis()->SetRangeUser(0,23);
	h6->GetXaxis()->SetNdivisions(24);
	h6->GetYaxis()->SetTitleOffset(1.3);
	h6->Draw();
	c6->SaveAs("Flux_OneDay_EH3_AD2.gif");

	TCanvas *c7 = new TCanvas("c7","Flux_AD",0,0,1200,900);
	//h7->SetLineColor(kRed);
	h7->SetTitle("Flux seen in EH3_AD3");
	h7->GetXaxis()->SetTitle("Time(number of sidereal hours start from 2011-12-24 00:00:00)");
	h7->GetYaxis()->SetTitle("Flux");
	//h7->GetYaxis()->SetRangeUser(0.48*1e6,0.58*1e6);
	h7->GetXaxis()->SetRangeUser(0,23);
	h7->GetXaxis()->SetNdivisions(24);
	h7->GetYaxis()->SetTitleOffset(1.3);
	h7->Draw();
	c7->SaveAs("Flux_OneDay_EH3_AD3.gif");

	TCanvas *c8 = new TCanvas("c8","Flux_AD",0,0,1200,900);
	//h8->SetLineColor(kRed);
	h8->SetTitle("Flux seen in EH3_AD4");
	h8->GetXaxis()->SetTitle("Time(number of sidereal hours start from 2011-12-24 00:00:00)");
	h8->GetYaxis()->SetTitle("Flux");
	//h8->GetYaxis()->SetRangeUser(0.48*1e6,0.58*1e6);
	h8->GetXaxis()->SetRangeUser(0,23);
	h8->GetXaxis()->SetNdivisions(24);
	h8->GetYaxis()->SetTitleOffset(1.3);
	h8->Draw();
	c8->SaveAs("Flux_OneDay_EH3_AD4.gif");

	
}