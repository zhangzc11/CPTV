{
  /* All it takes for this file to work is a "Event" tree. */

  TCanvas* vtx8c = new TCanvas("","",500,500);
  TH2F *vtx8 = new TH2F( "vtx8","vtx8",100,0,5000e3,100,-2500,2500);
  vtx8->GetXaxis()->SetTitle("R*R [mm*mm]");
  vtx8->GetYaxis()->SetTitle("Z [mm]");
  Event->Draw("Z[0]:X[0]**2+Y[0]**2>>vtx8","Fold==2 && E[1]<12 && E[0]<12 && E[1]>6","colz");
  vtx8c->Print("vtx8.ps");


  TCanvas* tau8c = new TCanvas("","",500,500);
  TH1F *tau8 = new TH1F( "tau8","tau8",100,0,400*1e3);
  tau8->GetXaxis()->SetTitle("Lifetime [ns]");
  tau8->GetYaxis()->SetTitle("Entries");
  tau8c->SetLogy();
  Event->Draw("(TrigSec[1]-TrigSec[0])*1e9+TrigNano[1]-TrigNano[0]>>tau8","Fold==2 && E[1]<12 && E[0]<12 && E[1]>6");
  tau8c->Print("tau8.ps");

  TCanvas* dis8c = new TCanvas("","",500,500);
  TH1F *dis8 = new TH1F( "dis8","dis8",100,0,5000);
  dis8->GetXaxis()->SetTitle("Distance [mm]");
  dis8->GetYaxis()->SetTitle("Entries");
  Event->Draw("D2First[1]>>dis8","Fold==2 && E[1]<12 && E[0]<12 && E[1]>6");
  dis8c->Print("dis8.ps");

  TCanvas* vtx22c = new TCanvas("","",500,500);
  TH2F *vtx22 = new TH2F( "vtx22","vtx22",100,0,5000e3,100,-2500,2500);
  vtx22->GetXaxis()->SetTitle("R*R [mm*mm]");
  vtx22->GetYaxis()->SetTitle("Z [mm]");
  Event->Draw("Z[0]:X[0]**2+Y[0]**2>>vtx22","Fold==2 && E[1]<12 && E[0]<12 && E[1]<3 && E[1]>1.8 && E[0]>3.5","colz");
  vtx22c->Print("vtx22.ps");
  
  TCanvas* tau22c = new TCanvas("","",500,500);
  TH1F *tau22 = new TH1F( "tau22","tau22",100,0,400*1e3);
  tau22->GetXaxis()->SetTitle("Lifetime [ns]");
  tau22->GetYaxis()->SetTitle("Entries");
  tau22c->SetLogy();
  Event->Draw("(TrigSec[1]-TrigSec[0])*1e9+TrigNano[1]-TrigNano[0]>>tau22","Fold==2 && E[1]<12 && E[0]<12 && E[1]<3 && E[1]>1.8 && E[0]>3.5");
  tau22c->Print("tau22.ps");
  
  TCanvas* dis22c = new TCanvas("","",500,500);
  TH1F *dis22 = new TH1F( "dis22","dis22",100,0,5000);
  dis22->GetXaxis()->SetTitle("Distance [mm]");
  dis22->GetYaxis()->SetTitle("Entries");
  Event->Draw("D2First[1]>>dis22","Fold==2 && E[1]<12 && E[0]<12 && E[1]<3 && E[1]>1.8 && E[0]>3.5");
  dis22c->Print("dis22.ps");

  TCanvas* disAccc = new TCanvas("","",500,500);
  TH1F *disAcc = new TH1F( "disAcc","disAcc",100,0,5000);
  disAcc->GetXaxis()->SetTitle("Distance [mm]");
  disAcc->GetYaxis()->SetTitle("Entries");
  Event->Draw("D2First[1]>>disAcc","Fold==2 && E[1]<3 && E[0]<3");
  disAccc->Print("disAcc.ps");

  TCanvas* prmpt22c = new TCanvas("","",500,500);
  TH1F *prmpt22 = new TH1F( "prmpt22","prmpt22",100,0,12);
  prmpt22->GetXaxis()->SetTitle("Energy [mm]");
  prmpt22->GetYaxis()->SetTitle("Entries");
  Event->Draw("E[0]>>prmpt22","Fold==2 && E[1]<12 && E[0]<12 && E[1]<3 && E[1]>2 && D2First[1]<500");
  prmpt22c->Print("prmpt22.ps");

}
