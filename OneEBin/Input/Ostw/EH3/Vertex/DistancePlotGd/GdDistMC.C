int GdDistMC()
{
  gROOT->ProcessLine(".x chainMC.C");

  TH1F * h = new TH1F("h","h",100,0,3000);
  Event.Draw("D2First[1]>>h","Fold==2 && E[0]<10 && E[1]>6 ");
  h->GetXaxis()->SetTitle("Distance [mm]");
  h->GetYaxis()->SetTitle("Entries/30 mm");

  TFile f("MC.root", "update");
  h->Write();
  f.Write();
}
