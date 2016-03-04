/*
  RooFit is not very convinient.
*/
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooCBShape.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH2F.h"
#include "TH1D.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
using namespace RooFit ;

void FitPeak()
{
  // S e t u p   m o d e l 
  // ---------------------

  // Declare variables x,mean,sigma with associated name, title, initial value and allowed range
  RooRealVar E("E","E",0,10) ;
  RooRealVar mean("mean","mean of gaussian",   2, 0, 3) ;
  RooRealVar sigma("sigma","width of gaussian",1, 0, 3) ;
  RooRealVar a("a","crystal ball a", 1.5, 0, 10) ;
  RooRealVar n("n","crystal ball n", 1.5, 0, 10) ;

  RooCBShape  cbs("cbs", "crystal ball PDF",E,mean,sigma,a,n) ;

  // Construct plot frame in 'E'
  RooPlot* eframe = E.frame(Title("crystal ball p.d.f.")) ;

  
  // G e t   e v e n t s 
  // -----------------------------
  TFile f( "../data/Sample/06_1MeV_Trial/EH1.root" ) ;
  TH1F * h1dNeutron = (TH1F*)f.Get("h1dNeutron_1");

  RooDataHist data("data","dataset with E",E,h1dNeutron) ;
  data.plotOn(eframe) ;
  eframe->Draw() ;
  

  // F i t   m o d e l   t o   d a t a
  // -----------------------------

  // Fit pdf to data
  RooFitResult* FitRes = cbs.fitTo(data, Range(1.6, 3), Save(true) ) ;

  // Print values of mean and sigma (that now reflect fitted values and errors)
  cout<<"======================="<<endl;
  FitRes->Print();

  // Draw all frames on a canvas
  cbs.plotOn(eframe,LineColor(kRed)) ;
  eframe->Draw() ;


}

