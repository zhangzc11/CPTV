{
  TF1 *neutrino_f=new TF1("neutrino_f","0.58*exp(0.870-0.160*x-0.0910*x*x)+0.3*exp(0.896-0.239*x-0.0981*x*x)+0.07*exp(0.976-0.162*x-0.0790*x*x)+0.05*exp(0.793-0.080*x-0.1085*x*x)", 1.5, 10);
  
  TFormula *positron_m=new TFormula("positron_m","sqrt((x-1.2933)*(x-1.2933)-0.511*0.511)");
  
  TF1 *cross_section=new TF1("cross_section","0.0952e-42*(x-1.2933)*positron_m", 1.5, 10);
  
  TF1 *neutrino_sp=new TF1("neutrino_sp","neutrino_f*cross_section", 1.5, 10);

  double FluxTrue = 5.2450e57;
  double FluxMeas = FluxTrue * 0.99;
  
  double dn =  30000;  // cm
  double df = 150000;  // cm

  ///
  TF1 *PSurvN = new TF1("PSurvN","1-0.1*pow(sin(1.267*2.3e-3* 300/x),2)", 1.5, 10);
  TF1 *PSurvF = new TF1("PSurvF","1-0.1*pow(sin(1.267*2.3e-3*1500/x),2)", 1.5, 10);


  // Total number of candidates
  TF1 *neu_near = new TF1("neu_near","neutrino_f*cross_section*PSurvN", 1.5, 10);
  neu_near->Draw();
  double nearN = FluxTrue/(4*3.14159*dn*dn) * neu_near->Integral( 1.5, 10);
  cout<<nearN<<endl;


  TF1 *neu_far  = new TF1("neu_far" ,"neutrino_f*cross_section*PSurvF", 1.5, 10);
  // Total number of candidates
  double farN  = FluxTrue/(4*3.14159*df*df) * neu_far ->Integral( 1.5, 10);  
  cout<<farN <<endl;

  TH1F *hNear = new TH1F("Near","Near",170, 1.5, 10);
  hNear->FillRandom( "neu_near", nearN );
  new TCanvas;
  hNear->Draw();
  hNear->GetXaxis()->SetTitle("Neutrino energy [MeV]");
  hNear->GetYaxis()->SetTitle("Entries/0.5 MeV");

  TH1F *hFar  = new TH1F("Far", "Far", 170, 1.5, 10);
  hFar->FillRandom( "neu_far", farN );
  new TCanvas;
  hFar->Draw();
  hFar->GetXaxis()->SetTitle("Neutrino energy [MeV]");
  hFar->GetYaxis()->SetTitle("Entries/0.5 MeV");

  cout<<"Measured total neutrinos: "<<FluxMeas<<" +/- "<<FluxMeas*0.01<<endl;
  cout<<"Baseline near: "<<dn<<" cm"<<endl;
  cout<<"Baseline far:  "<<df<<" cm"<<endl;
  
  TFile Proj4("Proj4.root","RECREATE");
  hNear->Write();
  hFar ->Write();
  Proj4.Close();
}

