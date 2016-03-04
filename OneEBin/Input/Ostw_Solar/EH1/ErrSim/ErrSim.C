#include "TRandom.h"
#include "TH1F.h"

void ErrSim()
{
  /* The model */
  /* 
     SSigma     = sqrt(SMean),
     Signal     = Gauss(SMean, SSigma);
     

     BMeanTruth = Gauss(BMean, BError),
     BSigma     = sqrt(BMeanTruth),
     Background = Gauss(BMeanTruth, BSigma);

     Sum = Signal + Background;

     Diff = Sum - BMean.
     
     The mean of Diff is the mean of Signal.
     The error = 

  */
  double Signal,     SMean = 1000, SSigma;
  double Background, BMean = 500,  BError = 30, BMeanTruth, BSigma;
  double Sum;
  double Diff;
  
  TFile file("mc.root", "recreate");

  TH1F* hSig = new TH1F ( "Signal",     "Signal",     1000, 0.5*SMean        ,1.5*SMean          );
  TH1F* hBkg = new TH1F ( "Background", "Background", 1000, 0.5*BMean        ,1.5*BMean          );
  TH1F* hSum = new TH1F ( "Sum",        "Sum",        1000, 0.5*(SMean+BMean),1.5*(SMean+BMean)  );
  TH1F* hDif = new TH1F ( "Difference", "Difference", 1000, 0.5*SMean        ,1.5*SMean          );

  TRandom *rnd = new TRandom();

  for( int i = 1; i<=100000; i++ )  {
    SSigma = sqrt( SMean );
    Signal = rnd->Gaus( SMean, SSigma );
    hSig->Fill( Signal );
    
    BMeanTruth = rnd->Gaus( BMean, BError );
    BSigma = sqrt( BMeanTruth );
    Background = rnd->Gaus( BMeanTruth, BSigma );
    hBkg->Fill( Background );
    
    Sum = Signal + Background;
    hSum->Fill( Sum );
    
    Diff = Sum - BMean;
    hDif->Fill( Diff );
  }

  hSig->Write();
  hBkg->Write();
  hSum->Write();
  hDif->Write();
  
}
  
