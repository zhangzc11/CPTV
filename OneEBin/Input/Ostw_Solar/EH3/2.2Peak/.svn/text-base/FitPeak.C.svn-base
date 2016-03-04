/*
  Usage:
    root FitPeak.C
*/
{  
  TH1::AddDirectory(kFALSE);  /* Without this fitted histogram will be lost after return */
  //gStyle->SetStatH(0.5);
  //gStyle->SetStatW(0.6);
  gROOT->ProcessLine(".L CBShape.C");

  TF1 CBShape_F("CBShape", CBShape, 0, 5, 5);

  CBShape_F.SetParNames  ("N" ,  "mean", "sigma", "a", "n");
  CBShape_F.SetParameters(2200,  2.37,    0.151,  1.5, 10 );
  
  CBShape_F->SetParLimits(0,  0,  50000);
  CBShape_F->SetParLimits(1,  2,  2.5);
  CBShape_F->SetParLimits(2,  0.1,0.3);
  CBShape_F->SetParLimits(3,  2,  2);
  CBShape_F->SetParLimits(4,  250,  250);

  /*
  TFile f( "../data/Sample/06_1MeV_Trial/EH1.root" );
  TH1F* h = (TH1F*)f.Get("h1dNeutron_1");

  h->Fit("CBShape","I","", 1.7, 3.1);
  */  
  /*
  string file[6] = {
    "../data/Sample/P12e_1.5MeV_P12b/H/EH1.root",
    "../data/Sample/P12e_1.5MeV_P12b/H/EH1.root",
    "../data/Sample/P12e_1.5MeV_P12b/H/EH2.root",
    "../data/Sample/P12e_1.5MeV_P12b/H/EH3.root",
    "../data/Sample/P12e_1.5MeV_P12b/H/EH3.root",
    "../data/Sample/P12e_1.5MeV_P12b/H/EH3.root",
    "../data/Sample/P12e_1.5MeV_P12b/H/EH3.root"
  };
  */
  /*
  string file[6] = {
    "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH1.root",
    "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH1.root",
    "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH2.root",
    "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH3.root",
    "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH3.root",
    "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH3.root",
    "../data/Sample/P12e_1.5MeV_P12b-ext/H/EH3.root" 
  };
  */
      
  string file[6] = {
    "../data/Sample/P12e_1.5MeV/H/EH1.root",
    "../data/Sample/P12e_1.5MeV/H/EH1.root",
    "../data/Sample/P12e_1.5MeV/H/EH2.root",
    "../data/Sample/P12e_1.5MeV/H/EH3.root",
    "../data/Sample/P12e_1.5MeV/H/EH3.root",
    "../data/Sample/P12e_1.5MeV/H/EH3.root",
    "../data/Sample/P12e_1.5MeV/H/EH3.root"
  };
  
  string histo[6] = {
    "h1dNeutron_1",
    "h1dNeutron_2",
    "h1dNeutron_1",
    "h1dNeutron_1",
    "h1dNeutron_2",
    "h1dNeutron_3"
  };
    
  string title[6] = {
    "EH1_AD1",
    "EH1_AD2",
    "EH2_AD1",
    "EH3_AD1",
    "EH3_AD2",
    "EH3_AD3"
  }

  TH1F* h[6];  /* Fit result */
  int nAd = 6;
  double x[6];
  double x_e[6] = {0,0,0,0,0,0};
  double mean[6], mean_e[6];
  double sigma[6], sigma_e[6];
  double a[6], a_e[6];
  double n[6], n_e[6];

  for( int AdNo = 0; AdNo<nAd; AdNo++ )  {

    cout<<file[AdNo]<<endl;

    TFile f( file[AdNo].c_str() );
    h[AdNo] = (TH1F*)f.Get( histo[AdNo].c_str() );
    //h[AdNo]->SetTitle( title[AdNo].c_str() );
    
    CBShape_F.SetParNames  ("N" ,  "mean", "sigma", "a", "n");
    CBShape_F.SetParameters(1500,  2.37,    0.151,  1.5, 141 );
    TFitResultPtr r = h[AdNo]->Fit("CBShape","SI","", 1.8, 3.1);

    x[AdNo]         = AdNo+1;

    mean[AdNo]     = CBShape_F->GetParameter(1);
    mean_e[AdNo]   = CBShape_F->GetParError(1);

    sigma[AdNo]   = CBShape_F->GetParameter(2);
    sigma_e[AdNo] = CBShape_F->GetParError(2);

    a[AdNo]   = CBShape_F->GetParameter(3);
    a_e[AdNo] = CBShape_F->GetParError(3);

    n[AdNo]   = CBShape_F->GetParameter(4);
    n_e[AdNo] = CBShape_F->GetParError(4);
    
    r->Print("V");

    // Print to a ps file
    TCanvas* c = new TCanvas(title[AdNo].c_str(),title[AdNo].c_str(),500,500);
    c->SetMargin(0.15,0.15,0.1,0.1);
    h[AdNo]->GetXaxis()->SetTitle("Delayed Signal Energy [MeV]");
    h[AdNo]->GetYaxis()->SetTitle("Entries / 0.1 MeV");
    h[AdNo]->GetYaxis()->SetTitleOffset(1.2);
    h[AdNo]->SetTitle( title[AdNo].c_str() );
    h[AdNo]->SetName( title[AdNo].c_str() );
    h[AdNo]->GetXaxis()->SetRangeUser(1.5, 3.3);
    h[AdNo]->Draw("E");

    c->Print( (title[AdNo]+".ps").c_str() );

    f.Close();
  }

  for( int AdNo = 0; AdNo<6; AdNo++ )  {
    cout<<"mean: "<<mean[AdNo]<<" +/- "<<mean_e[AdNo]<<"\t"
        <<"sigma: "<<sigma[AdNo]<<" +/- "<<sigma_e[AdNo]<<"\t"
        <<"a: "<<a[AdNo]<<" +/- "<<a_e[AdNo]<<"\t"
        <<"n: "<<n[AdNo]<<" +/- "<<n_e[AdNo]<<endl;
  }


  /* Calculate average with the first 3 ADs */
  double mean_ave = 0, mean_ttl_w = 0;
  double sigma_ave = 0, sigma_ttl_w = 0;
  double a_ave = 0, a_ttl_w = 0;
  double n_ave = 0, n_ttl_w = 0;
  double w;
  for( int AdNo = 0; AdNo<6; AdNo++ )  {
    w = (1/mean_e[AdNo])*(1/mean_e[AdNo]);
    mean_ttl_w += w;
    mean_ave += mean[AdNo] * w;

    w = (1/sigma_e[AdNo])*(1/sigma_e[AdNo]);
    sigma_ttl_w += w;
    sigma_ave += sigma[AdNo] * w;

    w = (1/a_e[AdNo])*(1/a_e[AdNo]);
    a_ttl_w += w;
    a_ave += a[AdNo] * w;

    w = (1/n_e[AdNo])*(1/n_e[AdNo]);
    n_ttl_w += w;
    n_ave += n[AdNo] * w;
  }
  mean_ave = mean_ave/mean_ttl_w;
  sigma_ave = sigma_ave/sigma_ttl_w;
  a_ave = a_ave/a_ttl_w;

  cout<<"Average: "<<endl;
  cout<<"mean: "<<mean_ave<<"\t"
      <<"sigma: "<<sigma_ave<<"\t"
      <<"a: "<<a_ave<<"\t"
      <<"n: "<<n_ave<<endl;

  gmean = new TGraphErrors(nAd,x,mean,x_e,mean_e);
  gmean->SetTitle("mean");
  gmean->SetMarkerColor(4);
  gmean->SetMarkerStyle(21);
  TCanvas* cmean = new TCanvas("mean","mean",500,500);
  cmean->SetMargin(0.15,0.15,0.1,0.1);
  gmean->GetXaxis()->SetTitle("Ad Number");
  gmean->GetYaxis()->SetTitle("mean");
  gmean->Draw("ALP");
  cmean->Print("mean.ps");

  gsigma = new TGraphErrors(nAd,x,sigma,x_e,sigma_e);
  gsigma->SetTitle("sigma");
  gsigma->SetMarkerColor(4);
  gsigma->SetMarkerStyle(21);
  TCanvas* csigma = new TCanvas("sigma","sigma",500,500);
  csigma->SetMargin(0.15,0.15,0.1,0.1);
  gsigma->GetXaxis()->SetTitle("Ad Number");
  gsigma->GetYaxis()->SetTitle("sigma");
  gsigma->GetYaxis()->SetTitleOffset(1.3);
  gsigma->Draw("ALP");
  csigma->Print("sigma.ps");

  ga = new TGraphErrors(nAd,x,a,x_e,a_e);
  ga->SetTitle("a");
  ga->SetMarkerColor(4);
  ga->SetMarkerStyle(21);
  TCanvas* ca = new TCanvas("a","a",500,500);
  ca->SetMargin(0.15,0.15,0.1,0.1);
  ga->GetXaxis()->SetTitle("Ad Number");
  ga->GetYaxis()->SetTitle("a");
  ga->Draw("ALP");
  ca->Print("a.ps");

  gn = new TGraphErrors(nAd,x,n,x_e,n_e);
  gn->SetTitle("n");
  gn->SetMarkerColor(4);
  gn->SetMarkerStyle(21);
  TCanvas* cn = new TCanvas("n","n",500,500);
  cn->SetMargin(0.15,0.15,0.1,0.1);
  gn->GetXaxis()->SetTitle("Ad Number");
  gn->GetYaxis()->SetTitle("n");
  gn->Draw("ALP");
  cn->Print("n.ps");

}
