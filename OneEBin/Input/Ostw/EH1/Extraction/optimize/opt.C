/* 
   Input is from Extract2.C generated histograms:
   dis8 and disAcc
*/
{
  TFile f("dis8.root");
  TH1F* sigH = (TH1F*)f.Get("dis8");
  sigH->Draw();

  double l[10];
  double eff[10];
  double bkg[10];
  double e2b[10];
  double D = sigH->Integral(1,40);

  for( int idx=1; idx<=10; idx++ ) {
    l[idx-1]   = idx*2*50;  // 50 mm/bin
    eff[idx-1] = sigH->Integral(1, idx*2) / D;
  }

  TCanvas cEff;
  TGraph gEff(10,l,eff);
  gEff->Draw("APL");
  gEff->SetMarkerStyle(20);
  gEff->GetXaxis()->SetTitle("Distance cut [mm]");
  gEff->GetYaxis()->SetTitle("Efficiency");
  
  for( int idx=1; idx<=10; idx++ ) {
    bkg[idx-1] = 0.5 * l[idx-1] * l[idx-1] * 12.94 / 50;
    e2b[idx-1] = eff[idx-1]/bkg[idx-1];
  }

  TCanvas cBkg;
  TGraph gBkg(10,l,bkg);
  gBkg->Draw("APL");
  gBkg->SetMarkerStyle(20);
  gBkg->GetXaxis()->SetTitle("Distance cut [mm]");
  gBkg->GetYaxis()->SetTitle("Background");

  TCanvas cE2b;
  TGraph gE2b(10,l,e2b);
  gE2b->Draw("APL");

}
