
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
	double RotAngl = 0.0;//9.0*pi/180.0;//9 degrees of rotation

	double A_chi[3][6] = {0.0};//angle chi, [HallNo][RctNo],in unit of radius
	double A_theta[3][6] = {0.0};//angle theta, [HallNo][RctNo]
	double A_phi[3][6] = {0.0};//angle phi, [HallNo][RctNo]

	double Nx[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Ny[3][6] = {0.0};//direction factor, [HallNo][RctNo]
	double Nz[3][6] = {0.0};//direction factor, [HallNo][RctNo]


void DrawResult_Paper()
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



	////////////////////////////////////////////
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
	 style->cd();
     gROOT->ForceStyle();


	/////////////////////////////////////////////
	


	////////const fit
	const Int_t n = 24;

	//////points
	TCanvas *myC[3];
	TGraphErrors *gr[3];
	TLegend* leg[3];
	TF1 *f_Plot[3];

	const char *c_Name[3]={"EH1: 0.7 < E_{p} < 12MeV","EH2: 0.7 < E_{p} < 12MeV","EH3: 0.7 < E_{p} < 12MeV"};
	const char *file_Name[3]={"ThreeSites_Paper/Ratio_EH1_OneDay_sidereal.eps","ThreeSites_Paper/Ratio_EH2_OneDay_sidereal.eps","ThreeSites_Paper/Ratio_EH3_OneDay_sidereal.eps"};

	for(int Hidx=0;Hidx<3;Hidx++)
	{
		Float_t x[n],y[n],ex[n],ey[n];
		myC[Hidx] = new TCanvas(c_Name[Hidx],c_Name[Hidx],200,10,800,420);
		gStyle->SetOptFit(1);
		//myC[Hidx]->SetGrid();
		myC[Hidx]->GetFrame()->SetFillColor(21);
		myC[Hidx]->GetFrame()->SetBorderSize(12);
		for(int i=0;i<n;i++)
		{
		x[i]=(i+0.5)*WidthOfBin;
		y[i]=R[Hidx][i];
		ex[i]=0.5*WidthOfBin;
		ey[i]=R[Hidx][i]*RD_R[Hidx][i];
		}
		gr[Hidx] = new TGraphErrors(n,x,y,ex,ey);

		gr[Hidx]->SetMarkerColor(4);
		gr[Hidx]->SetMarkerStyle(21);
		gr[Hidx]->GetXaxis()->SetTitle("sidereal time (seconds)");
		gr[Hidx]->GetYaxis()->SetTitle("P(#bar{#nu}_{e} #rightarrow #bar{#nu}_{e})");
		
		gr[Hidx]->GetYaxis()->SetRangeUser(0.85,1.13);
		
		gr[Hidx]->GetYaxis()->SetTitleSize(0.07);
		gr[Hidx]->GetYaxis()->SetLabelSize(0.06);
		gr[Hidx]->GetYaxis()->SetTitleOffset(0.65);
		gr[Hidx]->GetYaxis()->SetNdivisions(505);
		gr[Hidx]->GetYaxis()->CenterTitle();

		gr[Hidx]->SetTitle("");
	
		gr[Hidx]->GetXaxis()->SetTitleOffset(0.7);
		gr[Hidx]->GetXaxis()->SetTitleSize(0.07);
		gr[Hidx]->GetXaxis()->SetRangeUser(0,86164.09);
		gr[Hidx]->GetXaxis()->SetLabelSize(0.05);
		gr[Hidx]->GetXaxis()->SetLabelOffset(0.0);

		gr[Hidx]->SetMarkerStyle(8);
		gr[Hidx]->SetMarkerColor(0);
		gr[Hidx]->SetLineColor(1);
		gr[Hidx]->SetLineWidth(2);
		gr[Hidx]->SetMarkerSize(0.8);


		//gr[Hidx]->SetMarkerStyle(21);
		gr[Hidx]->Draw("APZ");
		/////////////////plot the fit result:three sites////////////////////////
		f_Plot[Hidx] = new TF1(c_Name[Hidx],func_Prob_combine_const,0,86165.0,1);

		f_Plot[Hidx]->SetParName(0,"R");

		//gr[Hidx]->Fit(f_Plot[Hidx],"R");
		
		////////////////////////////////////////////////////////////
		leg[Hidx] = new TLegend(0.15, 0.75, 0.7, 0.9);
		leg[Hidx]->AddEntry(gr[Hidx],c_Name[Hidx],"");
		//leg[Hidx]->AddEntry(gr[Hidx],"EH3 - R(t) - data","");
		leg[Hidx]->SetFillStyle(0);
		leg[Hidx]->SetBorderSize(0);
		//leg[Hidx]->SetTextColor(kRed);
		leg[Hidx]->Draw();

		myC[Hidx]->Update();
		myC[Hidx]->SaveAs(file_Name[Hidx]);
	}

	////////simple fit

	

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