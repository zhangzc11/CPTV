
const Int_t NumOfHour = 24;
	Double_t Point_x[NumOfHour]={0};
	Double_t Point_y0[NumOfHour]={0};
	Double_t Point_y1[NumOfHour]={0};
	Double_t Point_y2[NumOfHour]={0};
	

void Flux_Hall()
{
	Double_t Flux6And8AD_EH1[24] = {0};
	Double_t Flux6And8AD_EH2[24] = {0};
	Double_t Flux6And8AD_EH3[24] = {0};
	Double_t Flux[3];
	Double_t Flux_Save2[3];
	
	TFile *FluxF_6AD = new TFile("../../Period6ADOnly/Flux/Flux_Hall.root");
	TTree *FluxTree_6AD = (TTree*)FluxF_6AD->Get("Flux");
	FluxTree_6AD->SetBranchAddress("Flux",Flux);
	for(int idx=0;idx<24;idx++)
	{
		FluxTree_6AD->GetEntry(idx);
		Flux6And8AD_EH1[idx] += Flux[0];
		Flux6And8AD_EH2[idx] += Flux[1];
		Flux6And8AD_EH3[idx] += Flux[2];
	}

	TFile *FluxF_8AD = new TFile("../../Period8ADOnly/Flux/Flux_Hall.root");
	TTree *FluxTree_8AD = (TTree*)FluxF_8AD->Get("Flux");
	FluxTree_8AD->SetBranchAddress("Flux",Flux);
	for(int idx=0;idx<24;idx++)
	{
		FluxTree_8AD->GetEntry(idx);
		Flux6And8AD_EH1[idx] += Flux[0];
		Flux6And8AD_EH2[idx] += Flux[1];
		Flux6And8AD_EH3[idx] += Flux[2];
	}

	//save to root file 
	TFile  *Fout2 = new TFile("Flux_Hall.root","recreate");
	TTree *FluxTree2 = new TTree("Flux","Flux");
	FluxTree2->Branch("Flux",Flux_Save2,"Flux_Save2[3]/D");

	for(int Bin=0;Bin<24;Bin++)
	{
		Flux_Save2[0]=Flux6And8AD_EH1[Bin];
		Flux_Save2[1]=Flux6And8AD_EH2[Bin];
		Flux_Save2[2]=Flux6And8AD_EH3[Bin];

		FluxTree2->Fill();
	}

	FluxTree2->Write();

	// Draw,EH1
	gStyle->SetOptStat(0);
	TCanvas *c1 = new TCanvas("c1","Flux",0,0,1000,800);
	TH1F *h1 = new TH1F("h1","Flux",24,0,24);
	for(int i=0;i<24;i++)
	{
		h1->SetBinContent(i,Flux6And8AD_EH1[i]);
	}
	h1->SetTitle("Neutrino flux vs. time - EH1");
	h1->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	h1->GetYaxis()->SetTitle("Flux (arbitary unit)");
	//h1->GetYaxis()->SetRangeUser(1990*1e3,2080*1e3);
	h1->GetXaxis()->SetRangeUser(0,23);
	h1->GetXaxis()->SetNdivisions(24);
	h1->GetYaxis()->SetLabelSize(0.025);
	h1->GetYaxis()->SetTitleOffset(1.3);
	h1->Draw();
	c1->SaveAs("Flux_EH1.gif");

	gStyle->SetOptStat(0);
	TCanvas *c2 = new TCanvas("c2","Flux",0,0,1000,800);
	TH1F *h2 = new TH1F("h2","Flux",24,0,24);
	for(int i=0;i<24;i++)
	{
		h2->SetBinContent(i,Flux6And8AD_EH2[i]);
	}
	h2->SetTitle("Neutrino flux vs. time - EH2");
	h2->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	h2->GetYaxis()->SetTitle("Flux (arbitary unit)");
	//h2->GetYaxis()->SetRangeUser(1990*1e3,2080*1e3);
	h2->GetXaxis()->SetRangeUser(0,23);
	h2->GetXaxis()->SetNdivisions(24);
	h2->GetYaxis()->SetLabelSize(0.025);
	h2->GetYaxis()->SetTitleOffset(1.3);
	h2->Draw();
	c2->SaveAs("Flux_EH2.gif");

	gStyle->SetOptStat(0);
	TCanvas *c3 = new TCanvas("c3","Flux",0,0,1000,800);
	TH1F *h3 = new TH1F("h3","Flux",24,0,24);
	for(int i=0;i<24;i++)
	{
		h3->SetBinContent(i,Flux6And8AD_EH3[i]);
	}
	h3->SetTitle("Neutrino flux vs. time - EH3");
	h3->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	h3->GetYaxis()->SetTitle("Flux (arbitary unit)");
	//h3->GetYaxis()->SetRangeUser(1990*1e3,2080*1e3);
	h3->GetXaxis()->SetRangeUser(0,23);
	h3->GetXaxis()->SetNdivisions(24);
	h3->GetYaxis()->SetLabelSize(0.025);
	h3->GetYaxis()->SetTitleOffset(1.3);
	h3->Draw();
	c3->SaveAs("Flux_EH3.gif");
	

}

Double_t  GetY(Double_t *x, Double_t *par)
{
	Int_t X_Int;
	if((x[0]>0)&&(x[0]<23.999999999))
	{
		X_Int= int(x[0]);
	}
	else if(x[0]<0)
	{
		X_Int = 0;
	}
	else
	{
		X_Int = 23;
	}
	return Point_y[X_Int];
}
Double_t  GetY0(Double_t *x, Double_t *par)
{
	Int_t X_Int;
	if((x[0]>0)&&(x[0]<23.999999999))
	{
		X_Int= int(x[0]);
	}
	else if(x[0]<0)
	{
		X_Int = 0;
	}
	else
	{
		X_Int = 23;
	}
	return Point_y0[X_Int];
}
Double_t  GetY1(Double_t *x, Double_t *par)
{
	Int_t X_Int;
	if((x[0]>0)&&(x[0]<23.999999999))
	{
		X_Int= int(x[0]);
	}
	else if(x[0]<0)
	{
		X_Int = 0;
	}
	else
	{
		X_Int = 23;
	}
	return Point_y1[X_Int];
}
Double_t  GetY2(Double_t *x, Double_t *par)
{
	Int_t X_Int;
	if((x[0]>0)&&(x[0]<23.999999999))
	{
		X_Int= int(x[0]);
	}
	else if(x[0]<0)
	{
		X_Int = 0;
	}
	else
	{
		X_Int = 23;
	}
	return Point_y2[X_Int];
}