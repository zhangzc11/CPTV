int GdDist4()
{
  gROOT->ProcessLine(".x chainEH3.C");

  TH1F * h = new TH1F("h","h",100,0,3000);
  Event.Draw("D2First[1]>>h","Fold==2 && E[0]<10 && E[1]>6 && Det==1");
  h->GetXaxis()->SetTitle("Distance [mm]");
  h->GetYaxis()->SetTitle("Entries/30 mm");

  TFile f("AD4.root", "RECREATE");
  h->Write();
  f.Write();
}
