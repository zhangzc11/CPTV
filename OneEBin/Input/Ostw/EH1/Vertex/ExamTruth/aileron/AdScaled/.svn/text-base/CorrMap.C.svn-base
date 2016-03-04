#include "TH2F.h"
#include "TROOT.h"

void CorrMap()
{
  gROOT->ProcessLine(".x chain.C");

  int nbin = 100;

  TFile f("RZCorr.root","RECREATE");

  TH2F* R2Accu  = new TH2F("R2Accu", "R2Accu", nbin, 0, 6000e3, nbin, -2500, 2500);
  TH2F* NR2Accu = new TH2F("NR2Accu", "NR2Accu", nbin, 0, 6000e3, nbin, -2500, 2500);
  TH2F* R2Corr  = new TH2F("R2Corr",  "R2Corr",  nbin, 0, 6000e3, nbin, -2500, 2500);

  TH2F* ZAccu  = new TH2F("ZAccu", "ZAccu",      nbin, 0, 6000e3, nbin, -2500, 2500);
  TH2F* NZAccu = new TH2F("NZAccu", "NZAccu",    nbin, 0, 6000e3, nbin, -2500, 2500);
  TH2F* ZCorr = new TH2F("ZCorr", "ZCorr",    nbin, 0, 6000e3, nbin, -2500, 2500);
  
  /* Z correction */
  Event.Draw("Z[0] : X[0]**2+Y[0]**2 >> ZAccu","ZT[0]-Z[0]*(Fold==2 && E[0]-ET[0]>-0.443 && E[0]-ET[0]<0.956)", "colz");
  Event.Draw("Z[0] : X[0]**2+Y[0]**2 >> NZAccu",          "(Fold==2 && E[0]-ET[0]>-0.443 && E[0]-ET[0]<0.956)", "colz");

  for( unsigned int nbinx = 1; nbinx<=nbin; nbinx++ ) {
    for( unsigned int nbiny = 1; nbiny<=nbin; nbiny++ ) {
      double A = ZAccu->GetBinContent( nbinx, nbiny );
      double N = NZAccu->GetBinContent( nbinx, nbiny );
      double Corr = 0;
      if( N>0 ) Corr = A/N;

      //if( Corr<-2000 ) cout<<nbinx<<" "<<nbiny<<" "<<A<<" "<<N<<" "<<Corr<<endl;
      ZCorr->SetBinContent( nbinx, nbiny, Corr );
    }
  }

  ZCorr->Draw("colz");
  
  //  ZCorr->Smooth(1);
  //  ZCorr->Smooth(1);
  
  /* R2 corrrection */
  Event.Draw("Z[0] : X[0]**2+Y[0]**2 >> R2Accu","(XT[0]**2+YT[0]**2)-(X[0]**2+Y[0]**2)*(Fold==2 && E[0]-ET[0]>-0.443 && E[0]-ET[0]<0.956)", "colz");
  Event.Draw("Z[0] : X[0]**2+Y[0]**2 >> NR2Accu",                                     "(Fold==2 && E[0]-ET[0]>-0.443 && E[0]-ET[0]<0.956)", "colz");

  for( unsigned int nbinx = 1; nbinx<=nbin; nbinx++ ) {
    for( unsigned int nbiny = 1; nbiny<=nbin; nbiny++ ) {
      double A = R2Accu->GetBinContent( nbinx, nbiny );
      double N = NR2Accu->GetBinContent( nbinx, nbiny );
      double Corr = 0;
      if( N>0 ) Corr = A/N;

      //if( Corr<-2000 ) cout<<nbinx<<" "<<nbiny<<" "<<A<<" "<<N<<" "<<Corr<<endl;                                                                  
      R2Corr->SetBinContent( nbinx, nbiny, Corr );
    }
  }

  R2Corr->Draw("colz");

  //  R2Corr->Smooth(1);
  //  R2Corr->Smooth(1);
  

  f.Write();
}
