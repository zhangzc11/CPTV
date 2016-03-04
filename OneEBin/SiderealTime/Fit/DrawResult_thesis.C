
double AVEP[3] = {0.985,0.983,0.951455};
const double pi = 3.141592653;

Double_t WidthOfBin = 86164.09/24.00;// 1 sidereal day = 86164.09 seconds

Double_t StartTime = 1324678393.80705;
Double_t EndTime = 1385769600.00000;

Double_t EveFrac_Hall[3][6][24]={0.0};
Double_t EveFrac_Hall_Total[3][24] = {0.0};
Double_t EveFrac_Hall_Ave[3][6]={0.0};
Double_t EveFrac_Total[3] = {0.0};
Double_t EveFrac[3][6];

int HallID = 0;
Double_t Baseline_Hall[3][6];//[Hall][Rct]

double LatHall[3] = {22.598,22.606,22.612};//latitude of the three halls, degree, read from goole maps

double PositionAD[8][3] = {
		{362.8329,	50.4206		,	-70.8174},
		{358.8044,	54.8583		,	-70.8135},
		{7.6518	,	-873.4882	,	-67.5241},
		{936.7486,	-1419.013	,	-66.4852},
		{941.4493,	-1415.305	,	-66.4966},
		{940.4612,	-1423.737	,	-66.4965},
		{945.1678,	-1420.0282	,	-66.4851},
		{9.5968	,	-879.149	,	-67.5202}};//in unit of meter, [ADNo.][X/Y/Z]
	double PositionRct[6][3] = {
		{359.2029	,	411.4896	,	-40.2308},
		{448.0015	,	411.0017	,	-40.2392},
		{-319.666	,	-540.7481	,	-39.7296},
		{-267.0633	,	-469.2051	,	-39.723},
		{-543.284	,	-954.7018	,	-39.7987},
		{-490.6906	,	-883.152	,	-39.7884}};//in unit of meter, [RctNo.][X/Y/Z]
	double PositionADn[8][3] = {0.0};
	double PositionHalln[3][3] = {0.0};//position of the hall, center of the ADs,[HallNo][X/Y/Z]
	double PositionRctn[6][3] = {0.0};
	double RotAngl = 9.0*pi/180.0;//9 degrees of rotation

	double A_chi[3][6] = {0.0};//angle chi, [HallNo][RctNo],in unit of radius
	double A_theta[3][6] = {0.0};//angle theta, [HallNo][RctNo]
	double A_phi[3][6] = {0.0};//angle phi, [HallNo][RctNo]

	double Nx[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Ny[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Nz[3][6] = {0.0};//direction factor, [HallNo][RctNo]


void DrawResult_thesis()
{

	TFile *F_EveFrac = new TFile("../Fraction.root");
	TTree *Tree_EveFrac = (TTree*)F_EveFrac->Get("Fraction");
	Tree_EveFrac->SetBranchAddress("Fraction",EveFrac);

	for(int N24 = 0;N24<24;N24++)
	{
		Tree_EveFrac->GetEntry(N24);
		for(int Rct = 0;Rct<6;Rct++)
		{
			EveFrac_Hall[0][Rct][N24] = EveFrac[0][Rct];
			EveFrac_Hall[1][Rct][N24] = EveFrac[1][Rct];
			EveFrac_Hall[2][Rct][N24] = EveFrac[2][Rct];
			for(int i=0;i<3;i++)
			{
				EveFrac_Hall_Ave[i][Rct] += EveFrac_Hall[i][Rct][N24];
				EveFrac_Total[i] += EveFrac_Hall[i][Rct][N24];
				EveFrac_Hall_Total[i][N24] += EveFrac_Hall[i][Rct][N24];
			}
		}
	}

	//fprintf(stderr,"Event fraction:\n");
	//fprintf(stderr,"%5s %12s %12s %12s %12s %12s %12s %12s \n","Hall","D1","D2","L1","L2","L3","L4","Total");
	for(int Hallidx=0;Hallidx<3;Hallidx++)
	{
		/*fprintf(stderr,"%5d %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f \n",Hallidx,EveFrac_Hall_Ave[Hallidx][0],EveFrac_Hall_Ave[Hallidx][1],
			EveFrac_Hall_Ave[Hallidx][2],EveFrac_Hall_Ave[Hallidx][3],EveFrac_Hall_Ave[Hallidx][4],EveFrac_Hall_Ave[Hallidx][5],EveFrac_Total[Hallidx]);
			*/
	}

	//fprintf(stderr,"Positions after rotation:\n");
	for(int ADidx = 0;ADidx<8;ADidx++)
	{
		PositionADn[ADidx][0] = PositionAD[ADidx][0]*cos(RotAngl)+PositionAD[ADidx][1]*sin(RotAngl);//x'=xcos + ysin
		PositionADn[ADidx][1] = -1.0*PositionAD[ADidx][0]*sin(RotAngl)+PositionAD[ADidx][1]*cos(RotAngl);//y'=-xsin + ycos
		PositionADn[ADidx][2] = PositionAD[ADidx][2];
		//////cout<<PositionADn[ADidx][0]<<"      "<<PositionADn[ADidx][1]<<"      "<<PositionADn[ADidx][2]<<endl;
	}

	for(int Rctidx = 0;Rctidx<6;Rctidx++)
	{
		PositionRctn[Rctidx][0] = PositionRct[Rctidx][0]*cos(RotAngl)+PositionRct[Rctidx][1]*sin(RotAngl);//x'=xcos + ysin
		PositionRctn[Rctidx][1] = -1*PositionRct[Rctidx][0]*sin(RotAngl)+PositionRct[Rctidx][1]*cos(RotAngl);//y'=-xsin + ycos
		PositionRctn[Rctidx][2] = PositionRct[Rctidx][2];
		//////cout<<PositionRctn[Rctidx][0]<<"      "<<PositionRctn[Rctidx][1]<<"      "<<PositionRctn[Rctidx][2]<<endl;
	}

	for(int i=0;i<3;i++)
	{
		PositionHalln[0][i] = 0.5*(PositionADn[0][i]+PositionADn[1][i]);
		PositionHalln[1][i] = 0.5*(PositionADn[2][i]+PositionADn[7][i]);
		PositionHalln[2][i] = 0.25*(PositionADn[3][i]+PositionADn[4][i]+PositionADn[5][i]+PositionADn[6][i]);
	}

	////////cout<<acos(-0.5)<<"   "<<120.0*pi/180.0<<endl;
	
	////////cout<<"Hall			Rct			theta			phi			chi			Nx			Ny			Nz"<<endl;			
	//fprintf(stderr,"\n");
	//fprintf(stderr,"%5s %5s %12s %12s %12s %12s %12s %12s \n","Hall","Rct","theta","phi","chi","Nx","Ny","Nz");
	for(int Hallidx = 0;Hallidx<3;Hallidx++)
	{
		for(int Rctidx = 0;Rctidx<6;Rctidx++)
		{
			double D_beam[3] = {0.0};//beam direction
			for(int i=0;i<3;i++)
			{
				D_beam[i] = PositionHalln[Hallidx][i] -  PositionRctn[Rctidx][i];
			}
			A_theta[Hallidx][Rctidx] = acos(D_beam[2]/sqrt(pow(D_beam[0],2.0)+pow(D_beam[1],2.0)+pow(D_beam[2],2.0)));
			if(D_beam[0]<0)
			{
				A_phi[Hallidx][Rctidx] = acos(D_beam[1]/sqrt(pow(D_beam[0],2.0)+pow(D_beam[1],2.0)));
			}
			else
			{
				A_phi[Hallidx][Rctidx] = 2*pi - acos(D_beam[1]/sqrt(pow(D_beam[0],2.0)+pow(D_beam[1],2.0)));
			}
			A_chi[Hallidx][Rctidx] = 0.5*pi - LatHall[Hallidx]*pi/180.0;
			Nx[Hallidx][Rctidx] = cos(A_chi[Hallidx][Rctidx])*sin(A_theta[Hallidx][Rctidx])*cos(A_phi[Hallidx][Rctidx]) + sin(A_chi[Hallidx][Rctidx])*cos(A_theta[Hallidx][Rctidx]);
			Ny[Hallidx][Rctidx] = sin(A_theta[Hallidx][Rctidx])*sin(A_phi[Hallidx][Rctidx]);
			Nz[Hallidx][Rctidx] = -1*sin(A_chi[Hallidx][Rctidx])*sin(A_theta[Hallidx][Rctidx])*cos(A_phi[Hallidx][Rctidx]) + cos(A_chi[Hallidx][Rctidx])*cos(A_theta[Hallidx][Rctidx]);
			//fprintf(stderr,"%5d %5d %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f \n", Hallidx, Rctidx, A_theta[Hallidx][Rctidx]*180.0/pi, A_phi[Hallidx][Rctidx]*180.0/pi, A_chi[Hallidx][Rctidx]*180.0/pi, Nx[Hallidx][Rctidx], Ny[Hallidx][Rctidx], Nz[Hallidx][Rctidx]);
		}
	}

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		for(int Rct = 0;Rct<6;Rct++)
		{
			Baseline_Hall[Hidx][Rct] = sqrt(pow(PositionHalln[Hidx][0]-PositionRctn[Rct][0],2.0)+pow(PositionHalln[Hidx][1]-PositionRctn[Rct][1],2.0)+pow(PositionHalln[Hidx][2]-PositionRctn[Rct][2],2.0));
		}
	}


	//////////////////////////////////////////////////////////////////////////////////
	double R[3][24] = {{0.0}};
	double RD_R[3][24] = {{0.0}};

	Double_t Ratio_t[3];
    TFile *F_Ratio = new TFile("RatioInOneDay.root");
    TTree *Tree_Ratio = (TTree*)F_Ratio->Get("RatioInOneDay");
    Tree_Ratio->SetBranchAddress("RatioInOneDay",Ratio_t);

    for(int N24=0;N24<24;N24++)
    {

        Tree_Ratio->GetEntry(N24);
        for(int Det=0;Det<3;Det++)
        {
            R[Det][N24] = Ratio_t[Det];
        }
    }

	Double_t RD_Ratio_t[3];
    TFile *F_RD_Ratio = new TFile("RD_RatioInOneDay.root");
    TTree *Tree_RD_Ratio = (TTree*)F_RD_Ratio->Get("RD_RatioInOneDay");
    Tree_RD_Ratio->SetBranchAddress("RD_RatioInOneDay",RD_Ratio_t);

    for(int N24=0;N24<24;N24++)
    {

        Tree_RD_Ratio->GetEntry(N24);
        for(int Det=0;Det<3;Det++)
        {
            RD_R[Det][N24] = RD_Ratio_t[Det];
        }
    }


	///////////////////distribution
	//EH1
	HallID = 0;
	TCanvas *myC_distr_EH1 = new TCanvas("CRatio_EH1","CRatio_EH1",200,10,800,600);
	TH1F *hist_R_EH1 = new TH1F("Data/Expectation","Data/Expectation",20,AVEP[HallID]-0.03,AVEP[HallID]+0.03);
	for(int i=0;i<24;i++)
	{
		hist_R_EH1->Fill(R[HallID][i]);
	}
	hist_R_EH1->SetLineWidth(3);
	hist_R_EH1->GetYaxis()->SetTitle("Entries");
	hist_R_EH1->GetXaxis()->SetTitle("Data/Expectation");

	hist_R_EH1->GetXaxis()->SetTitleOffset(0.8);
	hist_R_EH1->GetXaxis()->SetTitleSize(0.05);
	hist_R_EH1->GetXaxis()->SetLabelSize(0.042);
	hist_R_EH1->GetXaxis()->SetLabelOffset(0.0);
	
	hist_R_EH1->GetYaxis()->SetTitleOffset(0.8);
	hist_R_EH1->GetYaxis()->SetTitleSize(0.06);
	hist_R_EH1->GetYaxis()->SetLabelSize(0.06);
	hist_R_EH1->GetYaxis()->SetLabelOffset(0.0);

	hist_R_EH1->SetFillColor(4);
	hist_R_EH1->Draw("hbar");
	myC_distr_EH1->RedrawAxis();
	myC_distr_EH1->Update();
	myC_distr_EH1->SaveAs("RatioDistr_EH1.pdf");
	myC_distr_EH1->SaveAs("RatioDistr_EH1.gif");
	//EH2
	HallID = 1;
	TCanvas *myC_distr_EH2 = new TCanvas("CRatio_EH2","CRatio_EH2",200,10,800,600);
	TH1F *hist_R_EH2 = new TH1F("Data/Expectation","Data/Expectation",20,AVEP[HallID]-0.03,AVEP[HallID]+0.03);
	for(int i=0;i<24;i++)
	{
		hist_R_EH2->Fill(R[HallID][i]);
	}
	hist_R_EH2->SetLineWidth(3);
	hist_R_EH2->GetYaxis()->SetTitle("Entries");
	hist_R_EH2->GetXaxis()->SetTitle("Data/Expectation");

	hist_R_EH2->GetXaxis()->SetTitleOffset(0.8);
	hist_R_EH2->GetXaxis()->SetTitleSize(0.05);
	hist_R_EH2->GetXaxis()->SetLabelSize(0.042);
	hist_R_EH2->GetXaxis()->SetLabelOffset(0.0);
	
	hist_R_EH2->GetYaxis()->SetTitleOffset(0.8);
	hist_R_EH2->GetYaxis()->SetTitleSize(0.06);
	hist_R_EH2->GetYaxis()->SetLabelSize(0.06);
	hist_R_EH2->GetYaxis()->SetLabelOffset(0.0);

	hist_R_EH2->SetFillColor(4);
	hist_R_EH2->Draw("hbar");
	myC_distr_EH2->RedrawAxis();
	myC_distr_EH2->Update();
	myC_distr_EH2->SaveAs("RatioDistr_EH2.pdf");
	myC_distr_EH2->SaveAs("RatioDistr_EH2.gif");
	//EH3
	HallID = 2;
	TCanvas *myC_distr_EH3 = new TCanvas("CRatio_EH3","CRatio_EH3",200,10,800,600);
	TH1F *hist_R_EH3 = new TH1F("Data/Expectation","Data/Expectation",20,AVEP[HallID]-0.03,AVEP[HallID]+0.03);
	for(int i=0;i<24;i++)
	{
		hist_R_EH3->Fill(R[HallID][i]);
	}
	hist_R_EH3->SetLineWidth(3);
	hist_R_EH3->GetYaxis()->SetTitle("Entries");
	hist_R_EH3->GetXaxis()->SetTitle("Data/Expectation");

	hist_R_EH3->GetXaxis()->SetTitleOffset(0.8);
	hist_R_EH3->GetXaxis()->SetTitleSize(0.05);
	hist_R_EH3->GetXaxis()->SetLabelSize(0.042);
	hist_R_EH3->GetXaxis()->SetLabelOffset(0.0);
	
	hist_R_EH3->GetYaxis()->SetTitleOffset(0.8);
	hist_R_EH3->GetYaxis()->SetTitleSize(0.06);
	hist_R_EH3->GetYaxis()->SetLabelSize(0.06);
	hist_R_EH3->GetYaxis()->SetLabelOffset(0.0);

	hist_R_EH3->SetFillColor(4);
	hist_R_EH3->Draw("hbar");
	myC_distr_EH3->RedrawAxis();
	myC_distr_EH3->Update();
	myC_distr_EH3->SaveAs("RatioDistr_EH3.pdf");
	myC_distr_EH3->SaveAs("RatioDistr_EH3.gif");

	////////const fit
	const Int_t n = 24;

	//////points
	TCanvas *myC[3];
	TGraphErrors *gr[3];
	TLegend* leg[3];
	TF1 *f_Plot[3];

	const char *c_Name[3]={"Daya Bay - EH1","Daya Bay - EH2","Daya Bay - EH3"};
	const char *file_Name[3]={"Ratio_EH1_OneDay_sidereal_const.pdf","Ratio_EH2_OneDay_sidereal_const.pdf","Ratio_EH3_OneDay_sidereal_const.pdf"};

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		Float_t x[n],y[n],ex[n],ey[n];
		myC[Hidx] = new TCanvas(c_Name[Hidx],c_Name[Hidx],200,10,800,600);
		gStyle->SetOptFit(1);
		//myC[Hidx]->SetGrid();
		myC[Hidx]->GetFrame()->SetFillColor(21);
		myC[Hidx]->GetFrame()->SetBorderSize(12);
		for(int i=0;i<n;i++)
		{
		x[i]=i*WidthOfBin;
		y[i]=R[Hidx][i];
		ex[i]=0;
		ey[i]=R[Hidx][i]*RD_R[Hidx][i];
		}
		gr[Hidx] = new TGraphErrors(n,x,y,ex,ey);

		gr[Hidx]->SetMarkerColor(4);
		gr[Hidx]->SetMarkerStyle(21);
		//gr[Hidx]->GetXaxis()->SetTitle("sidereal time(seconds)");
		//gr[Hidx]->GetYaxis()->SetTitle("Data/Expectation");
		gr[Hidx]->GetYaxis()->SetRangeUser(AVEP[Hidx]-0.03,AVEP[Hidx]+0.03);

		gr[Hidx]->SetTitle("");

		gr[Hidx]->GetYaxis()->SetTitleOffset(0.8);
		gr[Hidx]->GetYaxis()->SetTitleSize(0.05);
		gr[Hidx]->GetYaxis()->SetLabelSize(0.042);
		gr[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
		gr[Hidx]->GetXaxis()->SetTitleOffset(0.8);
		gr[Hidx]->GetXaxis()->SetTitleSize(0.06);
		//gr[Hidx]->GetXaxis()->SetLabelSize(0.045);
		gr[Hidx]->GetXaxis()->SetLabelOffset(0.0);

		//gr[Hidx]->SetMarkerStyle(21);
		gr[Hidx]->Draw("AP");
		/////////////////plot the fit result:three sites////////////////////////
		f_Plot[Hidx] = new TF1(c_Name[Hidx],func_Prob_combine_const,0,86165.0,1);

		f_Plot[Hidx]->SetParName(0,"R");

		//gr[Hidx]->Fit(f_Plot[Hidx],"R");
		
		////////////////////////////////////////////////////////////
		leg[Hidx] = new TLegend(0.2, 0.75, 0.6, 0.9);
		leg[Hidx]->AddEntry(gr[Hidx],c_Name[Hidx],"");
		leg[Hidx]->SetFillStyle(0);
		leg[Hidx]->SetBorderSize(0);
		leg[Hidx]->SetTextColor(kRed);
		//leg[Hidx]->Draw();

		myC[Hidx]->Update();
		//myC[Hidx]->SaveAs(file_Name[Hidx]);
	}

	////////simple fit

	//////points
	TCanvas *myC_Sp[3];
	TGraphErrors *gr_Sp[3];
	TLegend* leg_Sp[3];
	TF1 *f_Plot_Sp[3];

	const char *c_Name_Sp[3]={"Daya Bay - EH1 - 4P fit","Daya Bay - EH2 - 4P fit","Daya Bay - EH3 - 4P fit"};
	const char *file_Name_Sp[3]={"Ratio_EH1_OneDay_sidereal_Simple.pdf","Ratio_EH2_OneDay_sidereal_Simple.pdf","Ratio_EH3_OneDay_sidereal_Simple.pdf"};

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		Float_t x[n],y[n],ex[n],ey[n];
		myC_Sp[Hidx] = new TCanvas(c_Name_Sp[Hidx],c_Name_Sp[Hidx],200,10,800,600);
		gStyle->SetOptFit(1);
		//myC_Sp[Hidx]->SetGrid();
		myC_Sp[Hidx]->GetFrame()->SetFillColor(21);
		myC_Sp[Hidx]->GetFrame()->SetBorderSize(12);
		for(int i=0;i<n;i++)
		{
		x[i]=i*WidthOfBin;
		y[i]=R[Hidx][i];
		ex[i]=0;
		ey[i]=R[Hidx][i]*RD_R[Hidx][i];
		}
		gr_Sp[Hidx] = new TGraphErrors(n,x,y,ex,ey);

		gr_Sp[Hidx]->SetMarkerColor(4);
		gr_Sp[Hidx]->SetMarkerStyle(21);
		//gr_Sp[Hidx]->GetXaxis()->SetTitle("sidereal time(seconds)");
		//gr_Sp[Hidx]->GetYaxis()->SetTitle("Data/Expectation");
		gr_Sp[Hidx]->GetYaxis()->SetRangeUser(AVEP[Hidx]-0.03,AVEP[Hidx]+0.03);

		gr_Sp[Hidx]->SetTitle("");

		gr_Sp[Hidx]->GetYaxis()->SetTitleOffset(0.8);
		gr_Sp[Hidx]->GetYaxis()->SetTitleSize(0.05);
		gr_Sp[Hidx]->GetYaxis()->SetLabelSize(0.042);
		gr_Sp[Hidx]->GetYaxis()->SetLabelOffset(0.0);
	
		gr_Sp[Hidx]->GetXaxis()->SetTitleOffset(0.8);
		gr_Sp[Hidx]->GetXaxis()->SetTitleSize(0.06);
		//gr_Sp[Hidx]->GetXaxis()->SetLabelSize(0.045);
		gr_Sp[Hidx]->GetXaxis()->SetLabelOffset(0.0);

		//gr_Sp[Hidx]->SetMarkerStyle(21);
		gr_Sp[Hidx]->Draw("AP");
		/////////////////plot the fit result:three sites////////////////////////
		f_Plot_Sp[Hidx] = new TF1(c_Name_Sp[Hidx],func_Simple,0,86165.0,5);

		f_Plot_Sp[Hidx]->SetParName(0,"C0");
		f_Plot_Sp[Hidx]->SetParName(1,"A1");
		f_Plot_Sp[Hidx]->SetParName(2,"A2");
		f_Plot_Sp[Hidx]->SetParName(3,"A3");
		f_Plot_Sp[Hidx]->SetParName(4,"A4");
		f_Plot_Sp[Hidx]->SetParameter(0,AVEP[Hidx]);
		for(int i=1;i<5;i++)
		{
		f_Plot_Sp[Hidx]->SetParameter(i,0.0);
		}

		gr_Sp[Hidx]->Fit(f_Plot_Sp[Hidx],"R");
		
		////////////////////////////////////////////////////////////
		HallID = 2;
		leg_Sp[Hidx] = new TLegend(0.2, 0.75, 0.6, 0.9);
		leg_Sp[Hidx]->AddEntry(gr_Sp[Hidx],c_Name_Sp[Hidx],"");
		leg_Sp[Hidx]->SetFillStyle(0);
		leg_Sp[Hidx]->SetBorderSize(0);
		leg_Sp[Hidx]->SetTextColor(kRed);
		//leg_Sp[Hidx]->Draw();

		myC_Sp[Hidx]->Update();
		myC_Sp[Hidx]->SaveAs(file_Name_Sp[Hidx]);
	}
	/////////////////////////EH3 compared with Double Chooz////////////////////////////
	const Int_t n_DC = 24;
	Float_t x_DC[n_DC],y_DC[n_DC],ex_DC[n_DC],ey_DC[n_DC];
	for(int i=0;i<n;i++)
	{
		x_DC[i]=i*WidthOfBin;
		y_DC[i]=R[2][i];
		ex_DC[i]=0;
		ey_DC[i]=R[2][i]*RD_R[2][i];
	}

	TCanvas *myC_DC = new TCanvas("C_DC","C_DC",200,10,800,400);
	//myC_DC->SetGrid();
	TGraphErrors *gr_DC = new TGraphErrors(n_DC,x_DC,y_DC,ex_DC,ey_DC);
	gStyle->SetOptFit(0);
	gr_DC->SetMarkerColor(4);
	gr_DC->SetMarkerStyle(21);
	gr_DC->GetXaxis()->SetTitle("sidereal time(seconds)");
	gr_DC->GetYaxis()->SetTitle("P(#bar{#nu}_{e}->#bar{#nu}_{e})");
	//gr_DC->GetYaxis()->SetRangeUser(0.90,1.00);
	gr_DC->GetYaxis()->SetRangeUser(0.7,1.1);
	gr_DC->GetXaxis()->SetRangeUser(0,86200.);
	gr_DC->SetTitle("");

	gr_DC->GetYaxis()->SetTitleOffset(0.6);
	gr_DC->GetYaxis()->SetTitleSize(0.08);
	//gr_DC->GetYaxis()->SetLabelSize(0.042);
	gr_DC->GetYaxis()->SetLabelSize(0.062);
	gr_DC->GetYaxis()->SetLabelOffset(0.0);
	
	gr_DC->GetXaxis()->SetTitleOffset(0.68);
	gr_DC->GetXaxis()->CenterTitle();
	gr_DC->GetYaxis()->CenterTitle();
	gr_DC->GetXaxis()->SetTitleSize(0.07);
	gr_DC->GetXaxis()->SetLabelSize(0.06);
	//gr_DC->GetXaxis()->SetLabelSize(0.060);
	gr_DC->GetXaxis()->SetLabelOffset(0.0);

	//gr_DC->SetMarkerStyle(21);
	gr_DC->Draw("AP");
	

	TLegend* leg_DC = new TLegend(0.2, 0.75, 0.6, 0.9);
	leg_DC->AddEntry(gr_DC,"Daya Bay - e#mu fit","");
   leg_DC->SetFillStyle(0);
   leg_DC->SetBorderSize(0);
   leg_DC->SetTextColor(kRed);
   leg_DC->Draw();
   myC_DC->Update();
   myC_DC->SaveAs("Ratio_EH3_OneDay_sidereal_NoFit_DC.pdf");

   //////////////////DC wrong eu fit
   TF1 *fcn_DC_eu = new TF1("fcn_DC_eu",func_Short_eu,0,86165.0,3);
	fcn_DC_eu->SetParName(0,"C");
	fcn_DC_eu->SetParName(1,"As");
	fcn_DC_eu->SetParName(2,"Ac");
	
	for(int i=0;i<3;i++)
	{
		fcn_DC_eu->SetParameter(i,1.0e-21);
	}
	gr_DC->Fit(fcn_DC_eu,"R");

}

Double_t func_Prob_combine_const(Double_t *x, Double_t *par)
{
	return par[0];
}


Double_t func_Simple(Double_t *x, Double_t *par)
{
	Double_t wP = 2.0*pi/86164.0;//omega plus, sidereal frequency

	return par[0]+par[1]*sin(wP*x[0])+par[2]*cos(wP*x[0])+par[3]*sin(2.0*wP*x[0])+par[4]*cos(2.0*wP*x[0]);
}


Double_t func_Short_eu(Double_t *x, Double_t *par)
{
	Double_t wP = 2.0*pi/86164.0;//omega plus, sidereal frequency
	Double_t TotalP = 1.0;

	Double_t TotalEveFrac = 0.0;

	Double_t frac[6];

	int BIN = int(x[0]/WidthOfBin);

	for(int i=0;i<6;i++)
		{
		frac[i] = EveFrac_Hall_Ave[HallID][i];
		}
	for(int i=0;i<6;i++)
	{
		TotalEveFrac += frac[i];
	}

	for(int i=0;i<=5;i++)
	{
		Lt = Baseline_Hall[HallID][i];
		TotalP -= (frac[i]/TotalEveFrac)*pow(Lt*5.07e15,2.0)*pow((par[0]+par[1]*sin(wP*x[0])+par[2]*cos(wP*x[0])),2.0);
	}
	return TotalP;
}