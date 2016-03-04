
const Int_t NumOfDay = 705;//number of week from 2011-12-24 00:00:00 to 2012-07-28 00:00:00
Double_t FluxIJ[8][NumOfDay];//FluxIJ[i][j] means i-th AD j-th day
Double_t Point_x[NumOfDay];

Double_t Point_y[NumOfDay];

void ReadData();

void Flux()
{
	Double_t WidthOfBin = 86164.00/24.00;// 1 sidereal day = 86164 seconds
	Double_t StartTime = 1324684800;//in unit of second,it stands for 2011-12-24 00:00:00, UTC 0 time;
	Double_t EndTime = 1385769600;//in unit of second,it stands for 2012-07-28 00:00:00, UTC 0 time;
	Int_t NumOfBin = (EndTime - StartTime)/WidthOfBin;

	Int_t StartBin8AD =7080;//first,BinNo
	Int_t EndBin6AD = 5221;//last,BinNo

	Double_t Flux_Save[8];

	Point_x[0]=12;
	for(int i=1;i<NumOfDay;i++)
	{
		Point_x[i] = Point_x[i-1] + 24;
	}

	ReadData();

	FILE* m_outfile = fopen("DayRate.txt", "w");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		fprintf(m_outfile,"%10d",Bin);
		for(int i=0;i<8;i++)
		{
			fprintf(m_outfile,"%10.3f",FluxIJ[i][Bin]);
		}
		fprintf(m_outfile,"\n");
	}
	fclose(m_outfile);

	for(int i=0;i<NumOfDay;i++)
	{
		Point_y[i] = FluxIJ[0][i];
		//if(Point_y[i]>Point_y[i+1]
	}
	
	TCanvas *c1 = new TCanvas("c1","interpolation",0,0,1200,900);
	//EH1_AD1
   TF1 *seg1 = new TF1("Linear", LinearInter, 0, NumOfDay*24.0+100.0,1);
   seg1->SetParameter(0,0);
   seg1->SetLineColor(kRed);
   seg1->SetTitle("Flux seen at each AD");
   seg1->GetXaxis()->SetLimits(0,NumOfDay*24+100);
   seg1->GetXaxis()->SetRangeUser(0,NumOfDay*24+100);
   seg1->GetXaxis()->SetTitle("Time(number of hours start from 2011-12-24 00:00:00)");
   seg1->GetXaxis()->CenterTitle();
   seg1->GetYaxis()->SetLimits(0, 1200);
   seg1->GetYaxis()->SetTitleOffset(1.2);
   seg1->GetYaxis()->SetRangeUser(0, 1200);
   seg1->GetYaxis()->SetTitle("neutrino flux(arbitrary unit)");
   seg1->GetYaxis()->CenterTitle();
   seg1->Draw("l");
   //EH1_AD2
    TF1 *seg2 = new TF1("Linear", LinearInter, 0, NumOfDay*24.0+100.0,1);
   seg2->SetParameter(0,1);
   seg2->SetLineColor(kBlue);
   seg2->Draw("lsame");
   //EH2_AD1
    TF1 *seg3 = new TF1("Linear", LinearInter, 0, NumOfDay*24.0+100.0,1);
   seg3->SetParameter(0,2);
   seg3->SetLineColor(kGreen);
   seg3->Draw("lsame");
   //EH2_AD2
    TF1 *seg4 = new TF1("Linear", LinearInter, 0, NumOfDay*24.0+100.0,1);
   seg4->SetParameter(0,3);
   seg4->SetLineColor(kYellow);
   seg4->Draw("lsame");
   //EH3_AD1
    TF1 *seg5 = new TF1("Linear", LinearInter, 0, NumOfDay*24.0+100.0,1);
   seg5->SetParameter(0,4);
   seg5->SetLineColor(kPink);
   seg5->Draw("lsame");
   //EH3_AD2
    TF1 *seg6 = new TF1("Linear", LinearInter, 0, NumOfDay*24.0+100.0,1);
   seg6->SetParameter(0,5);
   seg6->SetLineColor(kAzure);
   seg6->Draw("lsame");
   //EH3_AD3
    TF1 *seg7 = new TF1("Linear", LinearInter, 0, NumOfDay*24.0+100.0,1);
   seg7->SetParameter(0,6);
   seg7->SetLineColor(kTeal);
   seg7->Draw("lsame");
   //EH3_AD1
    TF1 *seg8 = new TF1("Linear", LinearInter, 0, NumOfDay*24.0+100.0,1);
   seg8->SetParameter(0,7);
   seg8->SetLineColor(kOrange);
   seg8->Draw("lsame");

    TLegend* leg = new TLegend(0.7, 0.2, 0.90, 0.45);
   leg->AddEntry(seg1,"EH1_AD1","l");
   leg->AddEntry(seg2,"EH1_AD2","l");
   leg->AddEntry(seg3,"EH2_AD1","l");
   leg->AddEntry(seg4,"EH2_AD2","l");
   leg->AddEntry(seg5,"EH3_AD1","l");
   leg->AddEntry(seg6,"EH3_AD2","l");
   leg->AddEntry(seg7,"EH3_AD3","l");
   leg->AddEntry(seg8,"EH3_AD4","l");
   leg->Draw();
   c1->SaveAs("NeutrinoFluxAD.gif");

   //////save the result of the interpolation
   gStyle->SetOptStat(0);
	TCanvas *c2 = new TCanvas("c2","Flux_AD",0,0,1200,900);
	TH1F *h1 = new TH1F("h1","Flux",NumOfBin,0,NumOfBin);
	TH1F *h2 = new TH1F("h2","Flux",NumOfBin,0,NumOfBin);
	TH1F *h3 = new TH1F("h3","Flux",NumOfBin,0,NumOfBin);
	TH1F *h4 = new TH1F("h4","Flux",NumOfBin,0,NumOfBin);
	TH1F *h5 = new TH1F("h5","Flux",NumOfBin,0,NumOfBin);
	TH1F *h6 = new TH1F("h6","Flux",NumOfBin,0,NumOfBin);
	TH1F *h7 = new TH1F("h7","Flux",NumOfBin,0,NumOfBin);
	TH1F *h8 = new TH1F("h8","Flux",NumOfBin,0,NumOfBin);

   TFile  *Fout = new TFile("Flux.root","recreate");
	TTree *FluxTree = new TTree("Flux","Flux");
	FluxTree->Branch("Flux",Flux_Save,"Flux_Save[8]/D");

	for(int Bin = 0;Bin<NumOfBin;Bin++)
	{
		Double_t InterBin_L = Bin*WidthOfBin/3600.0;
		Double_t InterBin_R = (Bin+1.0)*WidthOfBin/3600.0;
		Flux_Save[0] = seg1->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		Flux_Save[1] = seg2->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		Flux_Save[2] = seg3->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		Flux_Save[3] = seg4->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		Flux_Save[4] = seg5->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		Flux_Save[5] = seg6->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		Flux_Save[6] = seg7->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		Flux_Save[7] = seg8->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);


		h1->SetBinContent(Bin,Flux_Save[0]);
		h2->SetBinContent(Bin,Flux_Save[1]);
		h3->SetBinContent(Bin,Flux_Save[2]);
		h4->SetBinContent(Bin,Flux_Save[3]);
		h5->SetBinContent(Bin,Flux_Save[4]);
		h6->SetBinContent(Bin,Flux_Save[5]);
		h7->SetBinContent(Bin,Flux_Save[6]);
		h8->SetBinContent(Bin,Flux_Save[7]);
		/*for(int i=0;i<8;i++)
		{
			cout<<Flux_Save[i]<<"      ";
		}
		cout<<endl;*/
		FluxTree->Fill();
	}

	FluxTree->Write();
	
	h1->SetLineColor(kRed);
	h1->SetTitle("Flux seen at each AD");
	h1->GetXaxis()->SetTitle("Time(number of sidereal hours start from 2011-12-24 00:00:00)");
	h1->GetYaxis()->SetTitle("Flux");
	h1->GetYaxis()->SetRangeUser(0,1200);
	h1->GetXaxis()->SetRangeUser(0,NumOfBin-1);
	h1->GetXaxis()->SetNdivisions(10);
	h1->GetYaxis()->SetTitleOffset(1.3);
	h1->Draw();
	
	h2->SetLineColor(kBlue);
	h2->Draw("same");
	
	h3->SetLineColor(kGreen);
	h3->Draw("same");
	
	h4->SetLineColor(kYellow);
	h4->Draw("same");
	
	h5->SetLineColor(kPink);
	h5->Draw("same");
	
	h6->SetLineColor(kAzure);
	h6->Draw("same");
	
	h7->SetLineColor(kTeal);
	h7->Draw("same");
	
	h8->SetLineColor(kOrange);
	h8->Draw("same");

	TLegend* leg2 = new TLegend(0.7, 0.2, 0.90, 0.45);
   leg2->AddEntry(h1,"EH1_AD1","l");
   leg2->AddEntry(h2,"EH1_AD2","l");
   leg2->AddEntry(h3,"EH2_AD1","l");
   leg2->AddEntry(h4,"EH2_AD2","l");
   leg2->AddEntry(h5,"EH3_AD1","l");
   leg2->AddEntry(h6,"EH3_AD2","l");
   leg2->AddEntry(h7,"EH3_AD3","l");
   leg2->AddEntry(h8,"EH3_AD4","l");
   leg2->Draw();

	c2->SaveAs("Flux_AD_interpolation.gif");

	/*
	///////////////////////////////////////////////////////////////////////////
	
	
	

   ///////////////////////
   //save the result of the interpolation
	TFile  *Fout = new TFile("Flux_D1.root","recreate");
	TTree *FluxTree = new TTree("Flux","Flux");
	FluxTree->Branch("Flux",&Flux_t,"Flux_t/D");

	Double_t SegTime[6] ={Point_x[ShutDownWeek1 - 1],Point_x[ShutDownWeek1 + 1],Point_x[ShutDownWeek2 - 1],Point_x[ShutDownWeek2 + 1],Point_x[ShutDownWeek3 - 1],Point_x[ShutDownWeek3 - 1]}; 
	for(int Bin = 0;Bin<NumOfBin;Bin++)
	{
		
		//seg1:  from hour 0 to 2436, cubic pspline//0 to 
		//seg2: from hour 2436 to 3780 exponentially
		//seg3:from hour 3780 to 5208, cubic pspline
		
		Double_t InterBin_M = (Bin+0.5)*WidthOfBin/3600.0;
		Double_t InterBin_L = InterBin_M - 0.5*WidthOfBin/3600.0;
		Double_t InterBin_R = InterBin_M + 0.5*WidthOfBin/3600.0;
		///
		if(InterBin_R<=SegTime[0])
		{
			Flux_t = seg1->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		}
		else if(InterBin_L<SegTime[0])
		{
			Flux_t = (seg1->Integral(InterBin_L,SegTime[0])+seg2->Integral(SegTime[0],InterBin_R))/(WidthOfBin/3600.0);
		}
		///
		else if(InterBin_R<=SegTime[1])
		{
			Flux_t = seg2->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		}
		else if(InterBin_L<SegTime[1])
		{
			Flux_t = (seg2->Integral(InterBin_L,SegTime[1])+seg3->Integral(SegTime[1],InterBin_R))/(WidthOfBin/3600.0);
		}
		///
		else if(InterBin_R<=SegTime[2])
		{
			Flux_t = seg3->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		}
		else if(InterBin_L<SegTime[2])
		{
			Flux_t = (seg3->Integral(InterBin_L,SegTime[2])+seg4->Integral(SegTime[2],InterBin_R))/(WidthOfBin/3600.0);
		}
		///
		else if(InterBin_R<=SegTime[3])
		{
			Flux_t = seg4->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		}
		else if(InterBin_L<SegTime[3])
		{
			Flux_t = (seg4->Integral(InterBin_L,SegTime[3])+seg5->Integral(SegTime[3],InterBin_R))/(WidthOfBin/3600.0);
		}
		///
		else if(InterBin_R<=SegTime[4])
		{
			Flux_t = seg5->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		}
		else if(InterBin_L<SegTime[4])
		{
			Flux_t = (seg5->Integral(InterBin_L,SegTime[4])+seg6->Integral(SegTime[4],InterBin_R))/(WidthOfBin/3600.0);
		}
		///
		else if(InterBin_R<=SegTime[5])
		{
			Flux_t = seg6->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		}
		else if(InterBin_L<SegTime[5])
		{
			Flux_t = (seg6->Integral(InterBin_L,SegTime[5])+seg7->Integral(SegTime[5],InterBin_R))/(WidthOfBin/3600.0);
		}
		///
		else
		{
			Flux_t = seg7->Integral(InterBin_L,InterBin_R)/(WidthOfBin/3600.0);
		}

		FluxTree->Fill();
		if(Flux_t<0)
		{
			//cout<<Bin<<"      "<<Flux_t<<endl;
		}
		//cout<<setw(10)<<Bin<<setw(20)<<Flux_t<<endl;
	}
	FluxTree->Write();*/
}

Double_t LinearInter(Double_t *x, Double_t *par) 
{
	Int_t RID = int(par[0]);
	if(x[0]>=Point_x[NumOfDay-1])
	{
		return (FluxIJ[RID][NumOfDay-1]+(x[0]-Point_x[NumOfDay-1])*(FluxIJ[RID][NumOfDay-1]-FluxIJ[RID][NumOfDay-2])/168.0);
		
	}
	else if(x[0]<=Point_x[0])
	{
		return (FluxIJ[RID][0]-(Point_x[0]-x[0])*(FluxIJ[RID][1]-FluxIJ[RID][0])/168.0);
	}
	else
	{
		int i=0;
		while (x[0]>Point_x[i])
		{
			i++;
		}
		return (FluxIJ[RID][i-1]+(x[0]-Point_x[i-1])*(FluxIJ[RID][i]-FluxIJ[RID][i-1])/168.0);
	}
}

void ReadData()
{
	std::string s;
	//////////read the day rate///////////////////////////////////////////////
	ifstream is_EH1_AD1("../../Input/daily_reactor/AD1DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH1_AD1,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[0][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH1_AD1.close();
	ifstream is_EH1_AD2("../../Input/daily_reactor/AD2DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH1_AD2,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[1][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH1_AD2.close();
	ifstream is_EH2_AD1("../../Input/daily_reactor/AD3DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH2_AD1,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[2][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH2_AD1.close();
	ifstream is_EH2_AD2("../../Input/daily_reactor/AD4DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH2_AD2,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[3][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH2_AD2.close();
	ifstream is_EH3_AD1("../../Input/daily_reactor/AD5DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH3_AD1,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[4][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH3_AD1.close();
	ifstream is_EH3_AD2("../../Input/daily_reactor/AD6DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH3_AD2,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[5][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH3_AD2.close();
	ifstream is_EH3_AD3("../../Input/daily_reactor/AD7DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH3_AD3,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[6][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH3_AD3.close();
	ifstream is_EH3_AD4("../../Input/daily_reactor/AD8DayRate.txt");
	for(int Bin=0;Bin<NumOfDay;Bin++)
	{
		getline(is_EH3_AD4,s);
		{
		string subs;
		stringstream ss;
		subs = s.substr(8,9);//92->95,FullTime
		ss<<subs;
		ss>>FluxIJ[7][Bin];
		}
		//cout<<Bin<<"   "<<FluxIJ[0][Bin]<<endl;
	}
	is_EH3_AD4.close();

}