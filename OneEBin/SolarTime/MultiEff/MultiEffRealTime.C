
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>


Double_t f_MultiEff(Double_t Ru,Double_t Rs,Double_t Tc);
Double_t f_MultiEff_Div(Double_t Ru,Double_t Nu,Double_t Rs,Double_t Ns,Double_t Tc);

void MultiEffRealTime()
{
	Double_t WidthOfBin = 3600.0;// 1 sidereal day = 86164.09 seconds
	Double_t StartTime = 1324684800.0 ;
	Double_t EndTime = 1385769600.00000;
	Int_t NumOfBin = 16968;//(EndTime - StartTime)/WidthOfBin;//16968
	Double_t Tc = 200*1e-6;

	Double_t MultiEffInEachDay[8][707];
	memset(MultiEffInEachDay,0.0,sizeof(MultiEffInEachDay));
	//
	Double_t TotalLiveTime[8]={0.0};
	Double_t LiveTime_t[8];

	Double_t LiveTimeInEachDay[8][707];
	memset(LiveTimeInEachDay,0.0,sizeof(LiveTimeInEachDay));

	TFile *F_LiveTime = new TFile("../LiveTime.root");
	TTree *Tree_LiveTime = (TTree*)F_LiveTime->Get("LiveTime");
	Tree_LiveTime->SetBranchAddress("LiveTime",LiveTime_t);
	//
	Double_t TotalFullTime[8]={0.0};
	Double_t FullTime_t[8];

	Double_t FullTimeInEachDay[8][707];
	memset(FullTimeInEachDay,0.0,sizeof(FullTimeInEachDay));

	TFile *F_FullTime = new TFile("../FullTime.root");
	TTree *Tree_FullTime = (TTree*)F_FullTime->Get("FullTime");
	Tree_FullTime->SetBranchAddress("FullTime",FullTime_t);
	//
	Double_t TotalSgUp[8]={0.0};
	Double_t SgUp_t[8];

	Double_t SgUpInEachDay[8][707];
	memset(SgUpInEachDay,0.0,sizeof(SgUpInEachDay));

	TFile *F_SgUp = new TFile("../SgUp.root");
	TTree *Tree_SgUp = (TTree*)F_SgUp->Get("SgUp");
	Tree_SgUp->SetBranchAddress("SgUp",SgUp_t);
	//
	Double_t TotalSgLow[8]={0.0};
	Double_t SgLow_t[8];

	Double_t SgLowInEachDay[8][707];
	memset(SgLowInEachDay,0.0,sizeof(SgLowInEachDay));

	TFile *F_SgLow = new TFile("../SgLow.root");
	TTree *Tree_SgLow = (TTree*)F_SgLow->Get("SgLow");
	Tree_SgLow->SetBranchAddress("SgLow",SgLow_t);
	//
	Double_t TotalNetMu[8]={0.0};
	Double_t NetMu_t[8];

	Double_t NetMuInEachDay[8][707];
	memset(NetMuInEachDay,0.0,sizeof(NetMuInEachDay));

	TFile *F_NetMu = new TFile("../NetMu.root");
	TTree *Tree_NetMu = (TTree*)F_NetMu->Get("NetMu");
	Tree_NetMu->SetBranchAddress("NetMu",NetMu_t);

	for(int Bin=0;Bin<NumOfBin;Bin++)
	{
		int N707 = int(Bin/24);
		Tree_FullTime->GetEntry(Bin);
		Tree_LiveTime->GetEntry(Bin);
		Tree_SgUp->GetEntry(Bin);
		Tree_SgLow->GetEntry(Bin);
		Tree_NetMu->GetEntry(Bin);

		for(int Det=0;Det<8;Det++)
		{
			LiveTimeInEachDay[Det][N707] += LiveTime_t[Det];
			FullTimeInEachDay[Det][N707] += FullTime_t[Det];
			SgUpInEachDay[Det][N707] += SgUp_t[Det];
			SgLowInEachDay[Det][N707] += SgLow_t[Det];
			NetMuInEachDay[Det][N707] += NetMu_t[Det];
			
		}
	}

	for(int Det=0;Det<8;Det++)
	{
		for(int N707=0;N707<707;N707++)
		{
			if(LiveTimeInEachDay[Det][N707]>1000)
			{
			MultiEffInEachDay[Det][N707] = f_MultiEff(NetMuInEachDay[Det][N707]/FullTimeInEachDay[Det][N707],0.5*(SgUpInEachDay[Det][N707]+SgLowInEachDay[Det][N707])/LiveTimeInEachDay[Det][N707],Tc);
			}
			else
			{
				MultiEffInEachDay[Det][N707] = 1.0;
			}
		}
	}
	
	//////////Draw
	const char *hist_Name[8] = {"EH1-AD1","EH1-AD2","EH2-AD1","EH2-AD2","EH3-AD1","EH3-AD2","EH3-AD3","EH3-AD4"}; 
	
	TCanvas *myC= new TCanvas("MultiEff","MultiEff",200,10,800,600);

	TGraphErrors *gr[8];
	TMultiGraph *mg =  new TMultiGraph();
	for(int Det=0;Det<8;Det++)
	{
		//cout<<TotalMultiEff[Det]<<endl;
		const Int_t n = 707;
		Double_t x[n],y[n],ex[n],ey[n];

		for(int i=0;i<n;i++)
	    {
			
		x[i]=i;
		y[i]=MultiEffInEachDay[Det][i];
		ex[i]=0;
		ey[i]=0.0;//(86400.0*MultiEffInEachDay[Det][i]/FullTimeInEachDay[Det][i])*sqrt(E2_MultiEffInEachDay[Det][i])/MultiEffInEachDay[Det][i];

	    }
		gr[Det] = new TGraphErrors(n,x,y,ex,ey);
	}
	gr[0]->SetMarkerColor(2);
	gr[1]->SetMarkerColor(4);
	gr[2]->SetMarkerColor(2);
	gr[3]->SetMarkerColor(4);
	gr[4]->SetMarkerColor(2);
	gr[5]->SetMarkerColor(4);
	gr[6]->SetMarkerColor(3);
	gr[7]->SetMarkerColor(1);

	gr[0]->SetMarkerStyle(20);
	gr[1]->SetMarkerStyle(7);
	gr[2]->SetMarkerStyle(4);
	gr[3]->SetMarkerStyle(25);
	gr[4]->SetMarkerStyle(22);
	gr[5]->SetMarkerStyle(23);
	gr[6]->SetMarkerStyle(26);
	gr[7]->SetMarkerStyle(26);
	
	for(int Det=0;Det<8;Det++)
	{
		//gr[Det]->SetMarkerColor(9-Det);
		gr[Det]->SetMarkerSize(0.9);
		mg->Add(gr[Det]);
	}

    
	mg->Draw("AP");

	mg->GetXaxis()->SetTitle("days since 2011-12-24");
    mg->GetYaxis()->SetTitle("Multiplicity Cut Efficiency");
	mg->GetYaxis()->SetTitleSize(0.055);
	mg->GetXaxis()->SetTitleSize(0.055);
	mg->GetYaxis()->SetLabelSize(0.038);
	mg->GetXaxis()->SetLabelSize(0.05);
	mg->GetYaxis()->SetTitleOffset(0.9);
	mg->GetXaxis()->SetTitleOffset(0.8);
	//mg->GetYaxis()->SetRangeUser(0.8,1.0);
	mg->GetYaxis()->SetRangeUser(0.97,0.98);

	TLegend* leg = new TLegend(0.38, 0.25, 0.60, 0.65);
	for(int Det=0;Det<8;Det++)
	{
		leg->AddEntry(gr[Det],hist_Name[Det],"lp");
	}
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw();

	gPad->Modified();

	myC->SaveAs("MultiEffRealTime.pdf");
	myC->SaveAs("MultiEffRealTime.png");

	//save to root file...
	double MultiplicityEff[8];
	TFile  *F_MultiplicityEff = new TFile("MultiplicityEff.root","recreate");
	TTree *Tree_MultiplicityEff = new TTree("MultiplicityEff","MultiplicityEff");
	Tree_MultiplicityEff->Branch("MultiplicityEff",MultiplicityEff,"MultiplicityEff[8]/D");

	for(int Bin=0; Bin<707;Bin++)
	{
		for(int Det=0;Det<8;Det++)
		{
			MultiplicityEff[Det] = MultiEffInEachDay[Det][Bin];
		}
		Tree_MultiplicityEff->Fill();
	}
	Tree_MultiplicityEff->Write();
	

}

Double_t f_MultiEff(Double_t Ru,Double_t Rs,Double_t Tc)
{
	//cout<<Ru<<"   "<<Rs<<endl;
	return ( (Ru/(Rs+Ru))*(1-exp(-(Ru+Rs)*Tc)) + exp(-(Ru+Rs)*Tc) 
		+ (Rs/(Rs+Ru))*exp(-Ru*Tc)*(1-exp(-(Ru+Rs)*Tc)) - (Rs/(2*Rs+Ru))*exp(-Ru*Tc)*(1-exp(-(Ru+2*Rs)*Tc)))*exp(-Rs*Tc);

}

Double_t f_MultiEff_Div(Double_t Ru,Double_t Nu,Double_t Rs,Double_t Ns,Double_t Tc)
{
	Double_t RD_Rs	= 1.0/(sqrt(Ns));
	Double_t RD_Ru	= 1.0/sqrt(Nu);

	Double_t RsTc	= exp(-Rs*Tc);
	Double_t D_RsTc= Tc * RD_Rs * Rs * RsTc;

	Double_t RuTc	= exp(-Ru*Tc);
	Double_t D_RuTc= Tc * RD_Ru * Ru * RuTc;

	Double_t RsuTc	= exp(-(Ru+Rs)*Tc);
	Double_t D_RsuTc= RsuTc*Tc*sqrt(pow(Ru*RD_Ru,2.0)+pow(Rs*RD_Rs,2.0));

	Double_t R2suTc	= exp(-(Ru+2*Rs)*Tc);
	Double_t D_R2suTc= R2suTc*Tc*sqrt(pow(Ru*RD_Ru,2.0)+pow(2*Rs*RD_Rs,2.0));

	Double_t Rus	= Ru/(Rs + Ru);
	Double_t RD_Rus = sqrt(1.0/Nu + (pow(Ru*RD_Ru,2.0)+pow(Rs*RD_Rs,2.0))/(pow(Ru+Rs,2.0)));

	Double_t Rsu	= Rs/(Rs + Ru);
	Double_t RD_Rsu = sqrt( pow(RD_Rs, 2.0) + (pow(Ru*RD_Ru,2.0)+pow(Rs*RD_Rs,2.0))/(pow(Ru+Rs,2.0)));
	
	Double_t R2su	= Rs/(2*Rs + Ru);
	Double_t RD_R2su= sqrt( pow(RD_Rs, 2.0) + (pow(Ru*RD_Ru,2.0)+pow(2*Rs*RD_Rs,2.0))/(pow(Ru+2*Rs,2.0)));
	/////////////////////////////////////////////////////////////////////////////
	Double_t In1	= Rus * (1-RsuTc);
	Double_t D_In1	= In1 * sqrt(pow(RD_Rus,2.0) + pow(D_RsuTc/(1-RsuTc),2.0));

	Double_t In2	= RsuTc;
	Double_t D_In2	= D_RsuTc;

	Double_t In3	= Rsu * RuTc * (1-RsuTc);
	Double_t D_In3	= In3 * sqrt(pow(RD_Rsu,2.0)+pow(D_RuTc/RuTc,2.0)+pow(D_RsuTc/(1-RsuTc),2.0));

	Double_t In4	= R2su * RuTc * (1-R2suTc);
	Double_t D_In4	= In4 * sqrt(pow(RD_R2su,2.0)+pow(D_RuTc/RuTc,2.0)+pow(D_R2suTc/(1-R2suTc),2.0));
	
	/////////////////////////////////////////////////////////////////////////////
	Double_t In		= In1 + In2 + In3 - In4;
	Double_t D_In	= sqrt(pow(D_In1,2.0)+pow(D_In2,2.0)+pow(D_In3,2.0)+pow(D_In4,2.0));

	Double_t Out	= RsTc;
	Double_t D_Out	= D_RsTc;
	
	/*cout<<"In1: "<<In1<<"   D_In1:   "<<D_In1<<endl;
	cout<<"In2: "<<In2<<"   D_In2:   "<<D_In2<<endl;
	cout<<"In3: "<<In3<<"   D_In3:   "<<D_In3<<endl;
	cout<<"In4: "<<In4<<"   D_In4:   "<<D_In4<<endl;
	cout<<"In:  "<<In<<"  D_In: "<<D_In<<endl; 
	cout<<"In*Out  "<<In*Out<<endl;
	*/
	return f_MultiEff(Ru,Rs,Tc) * sqrt(pow(D_In/In,2.0)+pow(D_Out/Out,2.0));
}
