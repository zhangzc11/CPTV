

void DrawMC()
{
	double Error[3][4][84];
	double Chi2[3][84];

	double MC_data_EH1[5],MC_data_EH2[5],MC_data_EH3[5];//error 1234,chi2, 

	TFile *F_MC_data_EH1 = new TFile("MC_EH1.root");
	TTree *Tree_MC_data_EH1 = (TTree*)F_MC_data_EH1->Get("MC_EH1");
	Tree_MC_data_EH1->SetBranchAddress("MC_EH1",MC_data_EH1);

	TFile *F_MC_data_EH2 = new TFile("MC_EH2.root");
	TTree *Tree_MC_data_EH2 = (TTree*)F_MC_data_EH2->Get("MC_EH2");
	Tree_MC_data_EH2->SetBranchAddress("MC_EH2",MC_data_EH2);

	TFile *F_MC_data_EH3 = new TFile("MC_EH3.root");
	TTree *Tree_MC_data_EH3 = (TTree*)F_MC_data_EH3->Get("MC_EH3");
	Tree_MC_data_EH3->SetBranchAddress("MC_EH3",MC_data_EH3);

	for(int i=0;i<84;i++)
	{
		Tree_MC_data_EH1->GetEntry(i);
		Tree_MC_data_EH2->GetEntry(i);
		Tree_MC_data_EH3->GetEntry(i);
		for(int idP=0;idP<4;idP++)
		{
			Error[0][idP][i] = MC_data_EH1[idP];
			Error[1][idP][i] = MC_data_EH2[idP];
			Error[2][idP][i] = MC_data_EH3[idP];
		}
		Chi2[0][i] = MC_data_EH1[4];
		Chi2[1][i] = MC_data_EH2[4];
		Chi2[2][i] = MC_data_EH3[4];
	}

	//Draw//////////////////////////////////////////////////////////////

	TCanvas *myC[3];
	TCanvas *myC_Chi[3];

	const char* hist_Name[4] = {"error_A1","error_A2","error_A3","error_A4"};
	const char* hist_Name_Chi[3] = {"Chi2/ndf_EH1","Chi2/ndf_EH2","Chi2/ndf_EH3"};

	const char* c_Name[3] = {"C_EH1","C_EH2","C_EH3"};
	const char* file_Name[3] = {"Simple_Shuffle_EH1.pdf","Simple_Shuffle_EH2.pdf","Simple_Shuffle_EH3.pdf"};
	const char* file_Name_2[3] = {"Simple_Shuffle_EH1.gif","Simple_Shuffle_EH2.gif","Simple_Shuffle_EH3.gif"};

	const char* c_Name_Chi[3] = {"EH1_Chi2","EH2_Chi2","EH3_Chi2"};
	const char* file_Name_Chi[3] = {"Simple_Shuffle_EH1_Chi2.pdf","Simple_Shuffle_EH2_Chi2.pdf","Simple_Shuffle_EH3_Chi2.pdf"};
	const char* file_Name_2_Chi[3] = {"Simple_Shuffle_EH1_Chi2.gif","Simple_Shuffle_EH2_Chi2.gif","Simple_Shuffle_EH3_Chi2.gif"};

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		//Fit error, A1,A2,A3,A4
		myC[Hidx] =  new TCanvas(c_Name[Hidx],c_Name[Hidx],200,10,1200,800);
		myC[Hidx]->Divide(2,2);

		TH1F *my_h[4];
		for(int idH=0;idH<4;idH++)
		{
		myC[Hidx]->cd(idH+1);
		//gStyle->SetOptFit(0001);
		gStyle->SetOptStat(0);
		my_h[idH] = new TH1F(hist_Name[idH],hist_Name[idH],100,0,100);
		for(int i=6;i<90;i++)
	    {
		   my_h[idH]->SetBinContent(i,Error[Hidx][idH][i-6]);
	    }
		my_h[idH]->Draw();
		my_h[idH]->GetXaxis()->SetLabelSize(0.04);
		my_h[idH]->GetXaxis()->SetTitle("Bin Number");
		my_h[idH]->GetXaxis()->SetTitleSize(0.05);
		my_h[idH]->GetYaxis()->SetLabelSize(0.06);
		}
		myC[Hidx]->SaveAs(file_Name[Hidx]);
		myC[Hidx]->SaveAs(file_Name_2[Hidx]);
		//Chi2
		myC_Chi[Hidx] =  new TCanvas(c_Name_Chi[Hidx],c_Name[Hidx],200,10,1200,800);
		TH1F *my_h_Chi = new TH1F(hist_Name_Chi[Hidx],hist_Name_Chi[Hidx],100,0,100);
		for(int i=6;i<90;i++)
	    {
			my_h_Chi->SetBinContent(i,Chi2[Hidx][i-6]/(i-4.0));
		}
		my_h_Chi->Draw();
		my_h_Chi->GetXaxis()->SetLabelSize(0.04);
		my_h_Chi->GetYaxis()->SetLabelSize(0.06);
		my_h_Chi->GetXaxis()->SetTitle("Bin Number");
		my_h_Chi->GetXaxis()->SetTitleSize(0.05);
		myC_Chi[Hidx]->SaveAs(file_Name_Chi[Hidx]);
		myC_Chi[Hidx]->SaveAs(file_Name_2_Chi[Hidx]);
	}
}