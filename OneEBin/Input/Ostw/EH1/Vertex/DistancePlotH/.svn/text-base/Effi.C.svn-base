{
  string cut  = "Fold==2 && E[0]>1 && E[0]<12 && E[1]>2.0139 && E[1]<2.9607 && Det==1";
  string cutd = cut+" && D2First[1]<500";

  // LS MC
  gROOT->ProcessLine(".x chainMC-LS.C");

  TH2F * LSSamp = new TH2F("LSSamp","LSSamp",120,0,12,120,0,12);
  Event.Project("LSSamp","E[1]:E[0]",cut.c_str(),"",5000000000,0);
  LSSamp->Draw();
  double nLSSamp = LSSamp->GetEntries();
  cout<<LSSamp->GetEntries()<<endl;
  
  TH2F * LSSele = new TH2F("LSSele","LSSele",120,0,12,120,0,12);
  Event.Project("LSSele","E[1]:E[0]",cutd.c_str(),"",5000000000,0);
  LSSele->Draw();
  double nLSSele = LSSele->GetEntries();
  cout<<LSSele->GetEntries()<<endl;

  double LSEffi = nLSSele/nLSSamp * 1.02;  // 0.02: data MC difference
  cout<<"LS Effi = "<<LSEffi<<endl;

  
  // GdLS MC
  gROOT->ProcessLine(".x chainMC-GdLS.C");

  TH2F * GdLSSamp = new TH2F("GdLSSamp","GdLSSamp",120,0,12,120,0,12);
  GdEvent.Project("GdLSSamp","E[1]:E[0]",cut.c_str(),"",5000000000,0);
  GdLSSamp->Draw();
  double nGdLSSamp = GdLSSamp->GetEntries();
  cout<<GdLSSamp->GetEntries()<<endl;

  TH2F * GdLSSele = new TH2F("GdLSSele","GdLSSele",120,0,12,120,0,12);
  GdEvent.Project("GdLSSele","E[1]:E[0]",cutd.c_str(),"",5000000000,0);
  GdLSSele->Draw();
  double nGdLSSele = GdLSSele->GetEntries();
  cout<<GdLSSele->GetEntries()<<endl;

  double GdLSEffi = nGdLSSele/nGdLSSamp * 1.02;  // 0.02: data MC difference
  cout<<"GdLS Effi = "<<GdLSEffi<<endl;
}
