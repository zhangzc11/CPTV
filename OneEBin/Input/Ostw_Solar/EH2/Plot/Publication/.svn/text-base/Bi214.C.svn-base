void Bi214()
{
  TH1::AddDirectory(kFALSE);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TCanvas *c1 = new TCanvas("c1","multipads",700,500);
  c1->SetRightMargin(0.15); 
  c1->SetLogz();

  TFile f("~/WORK/wangzhe/AccSubOutput/P12e_0.7MeV_Scaled_0.5m/H/EH3.root");

  TH2F* Vtx = (TH2F*)f.Get("h2dVtxSum");
  double nVtx = Vtx->Integral();
  TH2F* AccBkg = (TH2F*)f.Get("h2dAccBkgSum");
  double nAccBkg = AccBkg->Integral();
  TH2F* Acc = (TH2F*)f.Get("h2dAccSum");
  double nAcc = Acc->Integral();

  double a = (nVtx - nAcc)/nAccBkg;
  AccBkg->Scale( a );

  TH2F* Acc = new TH2F("Acc","Acc",1200,0,12,1200,0,12);
  Acc->Add( Vtx, AccBkg, 1.0, -1.0);

  Acc->Rebin2D(2,2);
  Acc->GetXaxis()->SetRangeUser(0.5,4);
  Acc->GetYaxis()->SetRangeUser(0.5,4);
  Acc->GetZaxis()->SetRangeUser(5,12000);
  for(int x=1; x<=Acc->GetNbinsX(); x++) {
    for(int y=1; y<=Acc->GetNbinsY(); y++) {
      double n = Acc->GetBinContent(x,y);
      if( n<5 ) Acc->SetBinContent(x,y,0.001);
    }
  }

  //Acc->GetXaxis()->SetTitleSize(0.06);
  //Acc->GetYaxis()->SetTitleSize(0.06);
  Acc->GetXaxis()->SetTitle("Prompt Energy [MeV]");
  Acc->GetYaxis()->SetTitle("Delayed Energy [MeV]");

  Acc->DrawCopy("colz");

  /*
  TLine *line = new TLine;
  line->DrawLine(2.3,0.5, 2.3,0.7);
  
  TPaveLabel *label = new TPaveLabel(2.1,0.15,2.5,0.5,"^{214}Bi");
  label->SetFillColor(0);
  label->SetShadowColor(0);
  label->SetTextSize(0.4);
  label->Draw();

  TLine *line = new TLine;
  line->DrawLine(0.75,0.5, 0.75,0.7);

  TPaveLabel *label = new TPaveLabel(2.1,0.15,2.5,0.5,"^{214}Bi");
  label->SetFillColor(0);
  label->SetShadowColor(0);
  label->SetTextSize(0.4);
  label->Draw();
  */
}
