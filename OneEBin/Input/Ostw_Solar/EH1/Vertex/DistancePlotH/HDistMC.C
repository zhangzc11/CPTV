int HDistMC()
{
  // LS MC
  gROOT->ProcessLine(".x chainMC-LS.C");
  string cut = "Fold==2 && E[0]>4 && E[0]<10 && E[1]>1.8 && E[1]<3 && Det==1";

  TH1F * distLS = new TH1F("distLS","distLS",100,0,3000);
  Event.Project("distLS","D2First[1]",cut.c_str(),"",5000000000,0);
  distLS->GetXaxis()->SetTitle("Distance [mm]");
  distLS->GetYaxis()->SetTitle("Entries/30 mm");

  TH1F * distLSX = new TH1F("distLSX","distLSX",200,-2000,2000);
  Event.Project("distLSX","X[1]-X[0]",cut.c_str(),"",5000000000,0);
  distLSX->GetXaxis()->SetTitle("Distance X [mm]");
  distLSX->GetYaxis()->SetTitle("Entries/40 mm");

  TH1F * distLSY = new TH1F("distLSY","distLSY",200,-2000,2000);
  Event.Project("distLSY","Y[1]-Y[0]",cut.c_str(),"",5000000000,0);
  distLSY->GetXaxis()->SetTitle("Distance Y [mm]");
  distLSY->GetYaxis()->SetTitle("Entries/40 mm");

  TH1F * distLSZ = new TH1F("distLSZ","distLSZ",200,-2000,2000);
  Event.Project("distLSZ","Z[1]-Z[0]",cut.c_str(),"",5000000000,0);
  distLSZ->GetXaxis()->SetTitle("Distance Z [mm]");
  distLSZ->GetYaxis()->SetTitle("Entries/40 mm");


  // GdLS MC
  gROOT->ProcessLine(".x chainMC-GdLS.C"); 
  TH1F * distGdLS = new TH1F("distGdLS","distGdLS",100,0,3000);
  GdEvent.Project("distGdLS","D2First[1]",cut.c_str(),"",5000000000,0);
  distGdLS->GetXaxis()->SetTitle("Distance [mm]");
  distGdLS->GetYaxis()->SetTitle("Entries/30 mm");

  TH1F * distGdLSX = new TH1F("distGdLSX","distGdLSX",200,-2000,2000);
  GdEvent.Project("distGdLSX","X[1]-X[0]",cut.c_str(),"",5000000000,0);
  distGdLSX->GetXaxis()->SetTitle("Distance X [mm]");
  distGdLSX->GetYaxis()->SetTitle("Entries/40 mm");

  TH1F * distGdLSY = new TH1F("distGdLSY","distGdLSY",200,-2000,2000);
  GdEvent.Project("distGdLSY","Y[1]-Y[0]",cut.c_str(),"",5000000000,0);
  distGdLSY->GetXaxis()->SetTitle("Distance Y [mm]");
  distGdLSY->GetYaxis()->SetTitle("Entries/40 mm");

  TH1F * distGdLSZ = new TH1F("distGdLSZ","distGdLSZ",200,-2000,2000);
  GdEvent.Project("distGdLSZ","Z[1]-Z[0]",cut.c_str(),"",5000000000,0);
  distGdLSZ->GetXaxis()->SetTitle("Distance Z [mm]");
  distGdLSZ->GetYaxis()->SetTitle("Entries/40 mm");
  
  TH1F * dist = new TH1F("dist","dist",100,0,3000);
  TH1F * distX = new TH1F("distX","distX",200,-2000,2000);
  TH1F * distY = new TH1F("distY","distY",200,-2000,2000);
  TH1F * distZ = new TH1F("distZ","distZ",200,-2000,2000);

  dist-> Add( distLS,  distGdLS,  1, 21.5/19.9*478916/411088 );
  distX->Add( distLSX, distGdLSX, 1, 21.5/19.9*478916/411088 );
  distY->Add( distLSY, distGdLSY, 1, 21.5/19.9*478916/411088 );
  distZ->Add( distLSZ, distGdLSZ, 1, 21.5/19.9*478916/411088 );
  
  TFile f("MC.root", "recreate");
  dist ->Write();
  distX->Write();
  distY->Write();
  distZ->Write();

  distLS ->Write();
  distLSX->Write();
  distLSY->Write();
  distLSZ->Write();

  distGdLS ->Write();
  distGdLSX->Write();
  distGdLSY->Write();
  distGdLSZ->Write();
  
  f.Write();
}
