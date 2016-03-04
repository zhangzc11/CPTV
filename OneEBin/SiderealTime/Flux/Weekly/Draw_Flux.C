
const Int_t NumOfHour = 24;
	Double_t Point_x[NumOfHour]={0};
	Double_t Point_y0[NumOfHour]={0};
	Double_t Point_y1[NumOfHour]={0};
	Double_t Point_y2[NumOfHour]={0};
	Double_t Point_y3[NumOfHour]={0};
	Double_t Point_y4[NumOfHour]={0};
	Double_t Point_y5[NumOfHour]={0};

void Draw_Flux()
{
	Double_t Flux6And8AD_D1[24] = {0};
	Double_t Flux6And8AD_D2[24] = {0};
	Double_t Flux6And8AD_L1[24] = {0};
	Double_t Flux6And8AD_L2[24] = {0};
	Double_t Flux6And8AD_L3[24] = {0};
	Double_t Flux6And8AD_L4[24] = {0};
	Double_t Flux[6];
	Double_t Flux_Save2[6];
	
	TFile *FluxF_6AD = new TFile("../../Period6ADOnly/Flux/FluxInOneDay.root");
	TTree *FluxTree_6AD = (TTree*)FluxF_6AD->Get("Flux");
	FluxTree_6AD->SetBranchAddress("Flux",Flux);
	for(int idx=0;idx<24;idx++)
	{
		FluxTree_6AD->GetEntry(idx);
		Flux6And8AD_D1[idx] += Flux[0];
		Flux6And8AD_D2[idx] += Flux[1];
		Flux6And8AD_L1[idx] += Flux[2];
		Flux6And8AD_L2[idx] += Flux[3];
		Flux6And8AD_L3[idx] += Flux[4];
		Flux6And8AD_L4[idx] += Flux[5];
	}

	TFile *FluxF_8AD = new TFile("../../Period8ADOnly/Flux/FluxInOneDay.root");
	TTree *FluxTree_8AD = (TTree*)FluxF_8AD->Get("Flux");
	FluxTree_8AD->SetBranchAddress("Flux",Flux);
	for(int idx=0;idx<24;idx++)
	{
		FluxTree_8AD->GetEntry(idx);
		Flux6And8AD_D1[idx] += Flux[0];
		Flux6And8AD_D2[idx] += Flux[1];
		Flux6And8AD_L1[idx] += Flux[2];
		Flux6And8AD_L2[idx] += Flux[3];
		Flux6And8AD_L3[idx] += Flux[4];
		Flux6And8AD_L4[idx] += Flux[5];
	}

	//save to root file 
	TFile  *Fout2 = new TFile("FluxInOneDay.root","recreate");
	TTree *FluxTree2 = new TTree("Flux","Flux");
	FluxTree2->Branch("Flux",Flux_Save2,"Flux_Save2[6]/D");

	for(int Bin=0;Bin<24;Bin++)
	{
		Flux_Save2[0]=Flux6And8AD_D1[Bin];
		Flux_Save2[1]=Flux6And8AD_D2[Bin];
		Flux_Save2[2]=Flux6And8AD_L1[Bin];
		Flux_Save2[3]=Flux6And8AD_L2[Bin];
		Flux_Save2[4]=Flux6And8AD_L3[Bin];
		Flux_Save2[5]=Flux6And8AD_L4[Bin];
		cout<<Bin<<"         ";
		for(int i=0;i<6;i++)
		{

			cout<<Flux_Save2[i]<<"      ";
		}
		cout<<endl;
		FluxTree2->Fill();
	}

	FluxTree2->Write();

	// Draw,D1
	for(int i=0;i<24;i++)
	{
		Point_y0[i] = Flux6And8AD_D1[i];
	}
	TCanvas *c_D1 = new TCanvas("c_D1","Flux_D1",0,0,1000,800);
	TF1 *t_D1 = new TF1("Flux", GetY0, 0, 24, 0);
	t_D1->SetTitle("Flux_D1");
	t_D1->GetHistogram()->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	t_D1->GetHistogram()->GetYaxis()->SetTitle("Flux(e^20 neutrinos per second)");
    t_D1->Draw();
	c_D1->SaveAs("FluxInOneDay_D1.gif");

	// Draw,D2
	for(int i=0;i<24;i++)
	{
		Point_y1[i] = Flux6And8AD_D2[i];
	}
	TCanvas *c_D2 = new TCanvas("c_D2","Flux_D2",0,0,1000,800);
	TF1 *t_D2 = new TF1("Flux", GetY1, 0, 24, 0);
	t_D2->SetTitle("Flux_D2");
	t_D2->GetHistogram()->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	t_D2->GetHistogram()->GetYaxis()->SetTitle("Flux(e^20 neutrinos per second)");
    t_D2->Draw();
	c_D2->SaveAs("FluxInOneDay_D2.gif");

	// Draw,L1
	for(int i=0;i<24;i++)
	{
		Point_y2[i] = Flux6And8AD_L1[i];
	}
	TCanvas *c_L1 = new TCanvas("c_L1","Flux_L1",0,0,1000,800);
	TF1 *t_L1 = new TF1("Flux", GetY2, 0, 24, 0);
	t_L1->SetTitle("Flux_L1");
	t_L1->GetHistogram()->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	t_L1->GetHistogram()->GetYaxis()->SetTitle("Flux(e^20 neutrinos per second)");
    t_L1->Draw();
	c_L1->SaveAs("FluxInOneDay_L1.gif");

	// Draw,L2
	for(int i=0;i<24;i++)
	{
		Point_y3[i] = Flux6And8AD_L2[i];
	}
	TCanvas *c_L2 = new TCanvas("c_L2","Flux_L2",0,0,1000,800);
	TF1 *t_L2 = new TF1("Flux", GetY3, 0, 24, 0);
	t_L2->SetTitle("Flux_L2");
	t_L2->GetHistogram()->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	t_L2->GetHistogram()->GetYaxis()->SetTitle("Flux(e^20 neutrinos per second)");
    t_L2->Draw();
	c_L2->SaveAs("FluxInOneDay_L2.gif");

	// Draw,L3
	for(int i=0;i<24;i++)
	{
		Point_y4[i] = Flux6And8AD_L3[i];
	}
	TCanvas *c_L3 = new TCanvas("c_L3","Flux_L3",0,0,1000,800);
	TF1 *t_L3 = new TF1("Flux", GetY4, 0, 24, 0);
	t_L3->SetTitle("Flux_L3");
	t_L3->GetHistogram()->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	t_L3->GetHistogram()->GetYaxis()->SetTitle("Flux(e^20 neutrinos per second)");
    t_L3->Draw();
	c_L3->SaveAs("FluxInOneDay_L3.gif");

	// Draw,L4
	for(int i=0;i<24;i++)
	{
		Point_y5[i] = Flux6And8AD_L4[i];
	}
	TCanvas *c_L4 = new TCanvas("c_L4","Flux_L4",0,0,1000,800);
	TF1 *t_L4 = new TF1("Flux", GetY5, 0, 24, 0);
	t_L4->SetTitle("Flux_L4");
	t_L4->GetHistogram()->GetXaxis()->SetTitle("sidereal time(1 bin = 86164.00/24.00 seconds)");
	t_L4->GetHistogram()->GetYaxis()->SetTitle("Flux(e^20 neutrinos per second)");
    t_L4->Draw();
	c_L4->SaveAs("FluxInOneDay_L4.gif");


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
Double_t  GetY3(Double_t *x, Double_t *par)
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
	return Point_y3[X_Int];
}
Double_t  GetY4(Double_t *x, Double_t *par)
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
	return Point_y4[X_Int];
}
Double_t  GetY5(Double_t *x, Double_t *par)
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
	return Point_y5[X_Int];
}
