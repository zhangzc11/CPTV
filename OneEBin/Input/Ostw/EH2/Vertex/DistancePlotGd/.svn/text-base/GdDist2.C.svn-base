int GdDist2()
{
  gROOT->ProcessLine(".x chainEH1.C");

  TH1F * h = new TH1F("h","h",100,0,3000);
  Event.Draw("D2First[1]>>h","Fold==2 && E[0]<10 && E[1]>6 && Det==2");
  h->GetXaxis()->SetTitle("Distance [mm]");
  h->GetYaxis()->SetTitle("Entries/30 mm");

  TFile f("AD2.root", "RECREATE");
  h->Write();
  f.Write();
}
