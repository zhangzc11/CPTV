{

  /* Data-MC */
  TChain Event("Event");
  Event.Add("~/share/MCEnergy/*.root");
  Event.Draw("E[1]","Fold==2");
  Event.Draw("E[1]/1.069>>h(250,1.5,4)","Fold==2");
  h->DrawNormalized();

  TFile *_file0 = TFile::Open("../data/Sample/P12e_1.5MeV/H/EH1.root");
  //return;
  h1dNeutronSum->Scale(1/h1dNeutronSum->Integral(151,400));
  h1dNeutronSum->GetXaxis()->SetRangeUser(1.5,4);
  h1dNeutronSum->Draw("same");

  {
    TH1::AddDirectory(kFALSE);

    TH1F* h[4];

    TCanvas* c =new TCanvas;
    TFile *f = TFile::Open("../data/Sample/P12e_1.5MeV/H/EH1.root");
    
    h[0] = (TH1F*)f.Get( "h1dNeutron_1" );

    h[0]->Scale(1/h[0]->Integral(151,400));
    h[0]->GetXaxis()->SetRangeUser(1.5,4);
    h[0]->SetLineColor(kRed);
    h[0]->Draw();

    h[1] = (TH1F*)f.Get( "h1dNeutron_2" );

    h[1]->Scale(1/h[1]->Integral(151,400));
    h[1]->GetXaxis()->SetRangeUser(1.5,4);
    h[1]->SetLineColor(kBlue);
    h[1]->Draw("same");

    f->Close();
    
    TFile *f1 = TFile::Open("../data/Sample/P12e_1.5MeV/H/EH2.root");

    h[2] = (TH1F*)f1.Get( "h1dNeutron_1" );

    h[2]->Scale(1/h[2]->Integral(151,400));
    h[2]->GetXaxis()->SetRangeUser(1.5,4);
    h[2]->SetLineColor(kGreen);
    h[2]->Draw("same");

    f1->Close();

  }

  {
    TH1F* h[4];

    TCanvas* c =new TCanvas;
    TFile *f = TFile::Open("../data/Sample/P12e_1.5MeV/H/Near.root");

    h[0] = (TH1F*)f.Get( "h1dNeutronSum" );

    h[0]->Scale(1/h[0]->Integral(151,400));
    h[0]->GetXaxis()->SetRangeUser(1.5,4);
    h[0]->SetLineColor(kRed);
    h[0]->Draw();

    f->Close();

    TFile *f2 = TFile::Open("../data/Sample/P12e_1.5MeV/H/EH3.root");

    h[3] = (TH1F*)f2.Get( "h1dNeutronSum" );

    h[3]->Scale(1/h[3]->Integral(151,400));
    h[3]->GetXaxis()->SetRangeUser(1.5,4);
    h[3]->SetLineColor(kBlack);
    h[3]->Draw("same");

    f2->Close();
  }


}
