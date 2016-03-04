#include "TH2F.h"
#include "TROOT.h"

void XYMap()
{
  gROOT->ProcessLine(".x chain.C");

  int nbin = 50;

  TFile f("XYCorr.root","RECREATE");

  TH2F* XAccu  = new TH2F("XAccu", "XAccu",   nbin, -2400, 2400, nbin, -2400, 2400);
  TH2F* NXAccu = new TH2F("NXAccu", "NXAccu", nbin, -2400, 2400, nbin, -2400, 2400);
  TH2F* XCorr  = new TH2F("XCorr",  "XCorr",  nbin, -2400, 2400, nbin, -2400, 2400);

  TH2F* YAccu  = new TH2F("YAccu", "YAccu",   nbin, -2400, 2400, nbin, -2400, 2400);
  TH2F* NYAccu = new TH2F("NYAccu", "NYAccu", nbin, -2400, 2400, nbin, -2400, 2400);
  TH2F* YCorr = new TH2F("YCorr", "YCorr",    nbin, -2400, 2400, nbin, -2400, 2400);
  
  /* Y correction */
  Event.Draw("Y[0]:X[0]>>YAccu" ,"(YT[0]-Y[0])*(Fold==2 && E[0]-ET[0]>-0.443 && E[0]-ET[0]<0.956 && abs(ZT[0])<1500)", "colz");
  Event.Draw("Y[0]:X[0]>>NYAccu","             (Fold==2 && E[0]-ET[0]>-0.443 && E[0]-ET[0]<0.956 && abs(ZT[0])<1500)", "colz");

  for( unsigned int nbinx = 1; nbinx<=nbin; nbinx++ ) {
    for( unsigned int nbiny = 1; nbiny<=nbin; nbiny++ ) {
      double A = YAccu->GetBinContent( nbinx, nbiny );
      double N = NYAccu->GetBinContent( nbinx, nbiny );
      double Corr = 0;
      if( N>0 ) Corr = A/N;

      //if( Corr<-2000 ) cout<<nbinx<<" "<<nbiny<<" "<<A<<" "<<N<<" "<<Corr<<endl;
      YCorr->SetBinContent( nbinx, nbiny, Corr );
    }
  }

  YCorr->Draw("colz");
  
  //YCorr->Smooth(1);
  //YCorr->Smooth(1);
  
  /* X corrrection */
  Event.Draw("Y[0]:X[0]>>XAccu","(XT[0]-X[0])*(Fold==2 && E[0]-ET[0]>-0.443 && E[0]-ET[0]<0.956 && abs(ZT[0])<1500)", "colz");
  Event.Draw("Y[0]:X[0]>>NXAccu","            (Fold==2 && E[0]-ET[0]>-0.443 && E[0]-ET[0]<0.956 && abs(ZT[0])<1500)", "colz");

  for( unsigned int nbinx = 1; nbinx<=nbin; nbinx++ ) {
    for( unsigned int nbiny = 1; nbiny<=nbin; nbiny++ ) {
      double A = XAccu->GetBinContent( nbinx, nbiny );
      double N = NXAccu->GetBinContent( nbinx, nbiny );
      double Corr = 0;
      if( N>0 ) Corr = A/N;

      //if( Corr<-2000 ) cout<<nbinx<<" "<<nbiny<<" "<<A<<" "<<N<<" "<<Corr<<endl;                                                                  
      XCorr->SetBinContent( nbinx, nbiny, Corr );
    }
  }

  XCorr->Draw("colz");

  //XCorr->Smooth(1);
  //XCorr->Smooth(1);
  

  f.Write();
}
