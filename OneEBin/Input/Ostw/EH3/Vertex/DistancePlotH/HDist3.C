int HDist3()
{
  gROOT->ProcessLine(".x chainEH2.C");
  string cut = "Fold==2 && E[0]>4 && E[0]<10 && E[1]>1.8 && E[1]<3 && Det==1";

  TH1F * dist = new TH1F("dist","dist",100,0,3000);
  Event.Project("dist","D2First[1]",cut.c_str(),"",5000000000,0);
  dist->GetXaxis()->SetTitle("Distance [mm]");
  dist->GetYaxis()->SetTitle("Entries/30 mm");

  TH1F * distX = new TH1F("distX","distX",200,-2000,2000);
  Event.Project("distX","X[1]-X[0]",cut.c_str(),"",5000000000,0);
  distX->GetXaxis()->SetTitle("Distance X [mm]");
  distX->GetYaxis()->SetTitle("Entries/40 mm");

  TH1F * distY = new TH1F("distY","distY",200,-2000,2000);
  Event.Project("distY","Y[1]-Y[0]",cut.c_str(),"",5000000000,0);
  distY->GetXaxis()->SetTitle("Distance Y [mm]");
  distY->GetYaxis()->SetTitle("Entries/40 mm");

  TH1F * distZ = new TH1F("distZ","distZ",200,-2000,2000);
  Event.Project("distZ","Z[1]-Z[0]",cut.c_str(),"",5000000000,0);
  distZ->GetXaxis()->SetTitle("Distance Z [mm]");
  distZ->GetYaxis()->SetTitle("Entries/40 mm");

  TFile f("AD3.root", "RECREATE");
  dist->Write();
  distX->Write();
  distY->Write();
  distZ->Write();
  f.Write();
}
