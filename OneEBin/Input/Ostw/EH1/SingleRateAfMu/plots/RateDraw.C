#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "../../Common/OstwEff.h"
using namespace std;

void RateDraw()
{
  TFile *fEH[3];
  string file[3];
  
  file[0] = "~/depot/data/Sample/SingleRateAfMu/0.1s/EH1/EH1.root";
  file[1] = "~/depot/data/Sample/SingleRateAfMu/0.1s/EH2/EH2.root";
  file[2] = "~/depot/data/Sample/SingleRateAfMu/0.1s/EH3/EH3.root";

  const int    timebins = 1000;
  const double timeStart = 0;
  const double timeEnd   = 0.1;
  
  /*
  file[0] = "~/depot/data/Sample/SingleRateAfMu/1s/EH1/EH1.root";
  file[1] = "~/depot/data/Sample/SingleRateAfMu/1s/EH2/EH2.root";
  file[2] = "~/depot/data/Sample/SingleRateAfMu/1s/EH3/EH3.root";

  const int    timebins = 100;
  const double timeStart = 0;
  const double timeEnd   = 1;
  */
  TH1F *TimePl[3],*CountUpPl[3],*CountLwPl[3],*RatePl[3],*RatePlC[3];
  TH1F *TimeAd[3],*CountUpAd[3],*CountLwAd[3],*RateAd[3],*RateAdC[3];
  TH1F *TimeSh[3],*CountUpSh[3],*CountLwSh[3],*RateSh[3],*RateShC[3];
  TH1F *Time[3]  ,*CountUp[3]  ,*CountLw[3]  ,*Rate[3]  ,*RateC[3];

  string type[4] = { "Time", "CountUp", "CountLw", "Rate" };
  string name[3] = { "Pl", "Ad", "Sh" };
  string SiteName[3] = { "EH1", "EH2", "EH3" };

  for( int site=0; site<3; site++ ) {
    TimePl[site] = new TH1F( (type[0]+name[0]+SiteName[site]).c_str(), (type[0]+name[0]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    TimeAd[site] = new TH1F( (type[0]+name[1]+SiteName[site]).c_str(), (type[0]+name[1]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    TimeSh[site] = new TH1F( (type[0]+name[2]+SiteName[site]).c_str(), (type[0]+name[2]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    Time[site] = new TH1F( (type[0]+SiteName[site]).c_str(), (type[0]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    
    CountUpPl[site] = new TH1F( (type[1]+name[0]+SiteName[site]).c_str(), (type[1]+name[0]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    CountUpAd[site] = new TH1F( (type[1]+name[1]+SiteName[site]).c_str(), (type[1]+name[1]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    CountUpSh[site] = new TH1F( (type[1]+name[2]+SiteName[site]).c_str(), (type[1]+name[2]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    CountUp[site] = new TH1F( (type[1]+SiteName[site]).c_str(), (type[1]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);

    CountLwPl[site] = new TH1F( (type[2]+name[0]+SiteName[site]).c_str(), (type[2]+name[0]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    CountLwAd[site] = new TH1F( (type[2]+name[1]+SiteName[site]).c_str(), (type[2]+name[1]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    CountLwSh[site] = new TH1F( (type[2]+name[2]+SiteName[site]).c_str(), (type[2]+name[2]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    CountLw[site] = new TH1F( (type[2]+SiteName[site]).c_str(), (type[2]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);

    RatePl[site] = new TH1F( (type[3]+name[0]+SiteName[site]).c_str(), (type[3]+name[0]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    RateAd[site] = new TH1F( (type[3]+name[1]+SiteName[site]).c_str(), (type[3]+name[1]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    RateSh[site] = new TH1F( (type[3]+name[2]+SiteName[site]).c_str(), (type[3]+name[2]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);
    Rate[site] = new TH1F( (type[3]+SiteName[site]).c_str(), (type[3]+SiteName[site]).c_str(), timebins, timeStart, timeEnd);

    RatePlC[site] = new TH1F( (type[3]+name[0]+SiteName[site]+"C").c_str(), (type[3]+name[0]+SiteName[site]+"C").c_str(), timebins/10, timeStart, timeEnd);
    RateAdC[site] = new TH1F( (type[3]+name[1]+SiteName[site]+"C").c_str(), (type[3]+name[1]+SiteName[site]+"C").c_str(), timebins/10, timeStart, timeEnd);
    RateShC[site] = new TH1F( (type[3]+name[2]+SiteName[site]+"C").c_str(), (type[3]+name[2]+SiteName[site]+"C").c_str(), timebins/10, timeStart, timeEnd);
    RateC[site] = new TH1F( (type[3]+SiteName[site]+"C").c_str(), (type[3]+SiteName[site]+"C").c_str(), timebins/10, timeStart, timeEnd);
  }
  
  for( int site=0; site<3; site++ ) {
    fEH[site] = new TFile( file[site].c_str() );
    TH1F * TimeAviPl1 = (TH1F*) fEH[site]->Get( "TimeAviPl1" );
    TH1F * TimeAviPl2 = (TH1F*) fEH[site]->Get( "TimeAviPl2" );
    TH1F * TimeAviPl3 = (TH1F*) fEH[site]->Get( "TimeAviPl3" );
    TH1F * TimeAviPl4 = (TH1F*) fEH[site]->Get( "TimeAviPl4" );
    TH1F * SingleUpPl1 = (TH1F*) fEH[site]->Get( "SingleUpPl1" );
    TH1F * SingleUpPl2 = (TH1F*) fEH[site]->Get( "SingleUpPl2" );
    TH1F * SingleUpPl3 = (TH1F*) fEH[site]->Get( "SingleUpPl3" );
    TH1F * SingleUpPl4 = (TH1F*) fEH[site]->Get( "SingleUpPl4" );
    TH1F * SingleLwPl1 = (TH1F*) fEH[site]->Get( "SingleLwPl1" );
    TH1F * SingleLwPl2 = (TH1F*) fEH[site]->Get( "SingleLwPl2" );
    TH1F * SingleLwPl3 = (TH1F*) fEH[site]->Get( "SingleLwPl3" );
    TH1F * SingleLwPl4 = (TH1F*) fEH[site]->Get( "SingleLwPl4" );

    TH1F * TimeAviAd1 = (TH1F*) fEH[site]->Get( "TimeAviAd1" );
    TH1F * TimeAviAd2 = (TH1F*) fEH[site]->Get( "TimeAviAd2" );
    TH1F * TimeAviAd3 = (TH1F*) fEH[site]->Get( "TimeAviAd3" );
    TH1F * TimeAviAd4 = (TH1F*) fEH[site]->Get( "TimeAviAd4" );
    TH1F * SingleUpAd1 = (TH1F*) fEH[site]->Get( "SingleUpAd1" );
    TH1F * SingleUpAd2 = (TH1F*) fEH[site]->Get( "SingleUpAd2" );
    TH1F * SingleUpAd3 = (TH1F*) fEH[site]->Get( "SingleUpAd3" );
    TH1F * SingleUpAd4 = (TH1F*) fEH[site]->Get( "SingleUpAd4" );
    TH1F * SingleLwAd1 = (TH1F*) fEH[site]->Get( "SingleLwAd1" );
    TH1F * SingleLwAd2 = (TH1F*) fEH[site]->Get( "SingleLwAd2" );
    TH1F * SingleLwAd3 = (TH1F*) fEH[site]->Get( "SingleLwAd3" );
    TH1F * SingleLwAd4 = (TH1F*) fEH[site]->Get( "SingleLwAd4" );

    TH1F * TimeAviSh1 = (TH1F*) fEH[site]->Get( "TimeAviSh1" );
    TH1F * TimeAviSh2 = (TH1F*) fEH[site]->Get( "TimeAviSh2" );
    TH1F * TimeAviSh3 = (TH1F*) fEH[site]->Get( "TimeAviSh3" );
    TH1F * TimeAviSh4 = (TH1F*) fEH[site]->Get( "TimeAviSh4" );
    TH1F * SingleUpSh1 = (TH1F*) fEH[site]->Get( "SingleUpSh1" );
    TH1F * SingleUpSh2 = (TH1F*) fEH[site]->Get( "SingleUpSh2" );
    TH1F * SingleUpSh3 = (TH1F*) fEH[site]->Get( "SingleUpSh3" );
    TH1F * SingleUpSh4 = (TH1F*) fEH[site]->Get( "SingleUpSh4" );
    TH1F * SingleLwSh1 = (TH1F*) fEH[site]->Get( "SingleLwSh1" );
    TH1F * SingleLwSh2 = (TH1F*) fEH[site]->Get( "SingleLwSh2" );
    TH1F * SingleLwSh3 = (TH1F*) fEH[site]->Get( "SingleLwSh3" );
    TH1F * SingleLwSh4 = (TH1F*) fEH[site]->Get( "SingleLwSh4" );

    TH1F * TimeAvi1 = (TH1F*) fEH[site]->Get( "TimeAvi1" );
    TH1F * TimeAvi2 = (TH1F*) fEH[site]->Get( "TimeAvi2" );
    TH1F * TimeAvi3 = (TH1F*) fEH[site]->Get( "TimeAvi3" );
    TH1F * TimeAvi4 = (TH1F*) fEH[site]->Get( "TimeAvi4" );
    TH1F * SingleUp1 = (TH1F*) fEH[site]->Get( "SingleUp1" );
    TH1F * SingleUp2 = (TH1F*) fEH[site]->Get( "SingleUp2" );
    TH1F * SingleUp3 = (TH1F*) fEH[site]->Get( "SingleUp3" );
    TH1F * SingleUp4 = (TH1F*) fEH[site]->Get( "SingleUp4" );
    TH1F * SingleLw1 = (TH1F*) fEH[site]->Get( "SingleLw1" );
    TH1F * SingleLw2 = (TH1F*) fEH[site]->Get( "SingleLw2" );
    TH1F * SingleLw3 = (TH1F*) fEH[site]->Get( "SingleLw3" );
    TH1F * SingleLw4 = (TH1F*) fEH[site]->Get( "SingleLw4" );

    if( site==0 ) {
      TimePl[0]->Add( TimePl[0] , TimeAviPl1 );
      TimePl[0]->Add( TimePl[0] , TimeAviPl2 );
      CountUpPl[0]->Add( CountUpPl[0] , SingleUpPl1 );
      CountUpPl[0]->Add( CountUpPl[0] , SingleUpPl2 );
      CountLwPl[0]->Add( CountLwPl[0] , SingleLwPl1 );
      CountLwPl[0]->Add( CountLwPl[0] , SingleLwPl2 );

      TimeAd[0]->Add( TimeAd[0] , TimeAviAd1 );
      TimeAd[0]->Add( TimeAd[0] , TimeAviAd2 );
      CountUpAd[0]->Add( CountUpAd[0] , SingleUpAd1 );
      CountUpAd[0]->Add( CountUpAd[0] , SingleUpAd2 );
      CountLwAd[0]->Add( CountLwAd[0] , SingleLwAd1 );
      CountLwAd[0]->Add( CountLwAd[0] , SingleLwAd2 );

      TimeSh[0]->Add( TimeSh[0] , TimeAviSh1 );
      TimeSh[0]->Add( TimeSh[0] , TimeAviSh2 );
      CountUpSh[0]->Add( CountUpSh[0] , SingleUpSh1 );
      CountUpSh[0]->Add( CountUpSh[0] , SingleUpSh2 );
      CountLwSh[0]->Add( CountLwSh[0] , SingleLwSh1 );
      CountLwSh[0]->Add( CountLwSh[0] , SingleLwSh2 );

      Time[0]->Add( Time[0] , TimeAvi1 );
      Time[0]->Add( Time[0] , TimeAvi2 );
      CountUp[0]->Add( CountUp[0] , SingleUp1 );
      CountUp[0]->Add( CountUp[0] , SingleUp2 );
      CountLw[0]->Add( CountLw[0] , SingleLw1 );
      CountLw[0]->Add( CountLw[0] , SingleLw2 );
    }
    if( site==1 ) {
      TimePl[1]->Add( TimePl[1] , TimeAviPl1 );
      CountUpPl[1]->Add( CountUpPl[1] , SingleUpPl1 );
      CountLwPl[1]->Add( CountLwPl[1] , SingleLwPl1 );

      TimeAd[1]->Add( TimeAd[1] , TimeAviAd1 );
      CountUpAd[1]->Add( CountUpAd[1] , SingleUpAd1 );
      CountLwAd[1]->Add( CountLwAd[1] , SingleLwAd1 );

      TimeSh[1]->Add( TimeSh[1] , TimeAviSh1 );
      CountUpSh[1]->Add( CountUpSh[1] , SingleUpSh1 );
      CountLwSh[1]->Add( CountLwSh[1] , SingleLwSh1 );

      Time[1]->Add( Time[1] , TimeAvi1 );
      CountUp[1]->Add( CountUp[1] , SingleUp1 );
      CountLw[1]->Add( CountLw[1] , SingleLw1 );
    }
    if( site==2 ) {
      TimePl[2]->Add( TimePl[2] , TimeAviPl1 );
      TimePl[2]->Add( TimePl[2] , TimeAviPl2 );
      TimePl[2]->Add( TimePl[2] , TimeAviPl3 );
      CountUpPl[2]->Add( CountUpPl[2] , SingleUpPl1 );
      CountUpPl[2]->Add( CountUpPl[2] , SingleUpPl2 );
      CountUpPl[2]->Add( CountUpPl[2] , SingleUpPl3 );
      CountLwPl[2]->Add( CountLwPl[2] , SingleLwPl1 );
      CountLwPl[2]->Add( CountLwPl[2] , SingleLwPl2 );
      CountLwPl[2]->Add( CountLwPl[2] , SingleLwPl3 );
      
      TimeAd[2]->Add( TimeAd[2] , TimeAviAd1 );
      TimeAd[2]->Add( TimeAd[2] , TimeAviAd2 );
      TimeAd[2]->Add( TimeAd[2] , TimeAviAd3 );
      CountUpAd[2]->Add( CountUpAd[2] , SingleUpAd1 );
      CountUpAd[2]->Add( CountUpAd[2] , SingleUpAd2 );
      CountUpAd[2]->Add( CountUpAd[2] , SingleUpAd3 );
      CountLwAd[2]->Add( CountLwAd[2] , SingleLwAd1 );
      CountLwAd[2]->Add( CountLwAd[2] , SingleLwAd2 );
      CountLwAd[2]->Add( CountLwAd[2] , SingleLwAd3 );

      TimeSh[2]->Add( TimeSh[2] , TimeAviSh1 );
      TimeSh[2]->Add( TimeSh[2] , TimeAviSh2 );
      TimeSh[2]->Add( TimeSh[2] , TimeAviSh3 );
      CountUpSh[2]->Add( CountUpSh[2] , SingleUpSh1 );
      CountUpSh[2]->Add( CountUpSh[2] , SingleUpSh2 );
      CountUpSh[2]->Add( CountUpSh[2] , SingleUpSh3 );
      CountLwSh[2]->Add( CountLwSh[2] , SingleLwSh1 );
      CountLwSh[2]->Add( CountLwSh[2] , SingleLwSh2 );
      CountLwSh[2]->Add( CountLwSh[2] , SingleLwSh3 );
      
      Time[2]->Add( Time[2] , TimeAvi1 );
      Time[2]->Add( Time[2] , TimeAvi2 );
      Time[2]->Add( Time[2] , TimeAvi3 );
      CountUp[2]->Add( CountUp[2] , SingleUp1 );
      CountUp[2]->Add( CountUp[2] , SingleUp2 );
      CountUp[2]->Add( CountUp[2] , SingleUp3 );
      CountLw[2]->Add( CountLw[2] , SingleLw1 );
      CountLw[2]->Add( CountLw[2] , SingleLw2 );
      CountLw[2]->Add( CountLw[2] , SingleLw3 );
    }    

    RatePl[site]->Divide(CountUpPl[site],TimePl[site],1,0.0001);
    RateAd[site]->Divide(CountUpAd[site],TimeAd[site],1,0.0001);
    RateSh[site]->Divide(CountUpSh[site],TimeSh[site],1,0.0001);
    Rate[site]  ->Divide(CountUp[site]  ,Time[site]  ,1,0.0001);

    cout<< " Pl muon, up:lw  "<<CountUpPl[site]->Integral() <<" "<< CountLwPl[site]->Integral() 
	<< "  diff = "<<(CountUpPl[site]->Integral()-CountLwPl[site]->Integral())/(CountUpPl[site]->Integral()+CountLwPl[site]->Integral()) <<endl;
    cout<< " Ad muon, up:lw  "<<CountUpAd[site]->Integral() <<" "<< CountLwAd[site]->Integral()
        << "  diff = "<<(CountUpAd[site]->Integral()-CountLwAd[site]->Integral())/(CountUpAd[site]->Integral()+CountLwAd[site]->Integral()) <<endl;
    cout<< " Sh muon, up:lw  "<<CountUpSh[site]->Integral() <<" "<< CountLwSh[site]->Integral()
        << "  diff = "<<(CountUpSh[site]->Integral()-CountLwSh[site]->Integral())/(CountUpSh[site]->Integral()+CountLwSh[site]->Integral()) <<endl;
    cout<< " All muon, up:lw "<<CountUp[site]->Integral() <<" "<< CountLw[site]->Integral()
        << "  diff = "<<(CountUp[site]->Integral()-CountLw[site]->Integral())/(CountUp[site]->Integral()+CountLw[site]->Integral()) <<endl;
    

    TCanvas * c = new TCanvas;
    
    RateSh[site]->Draw();
    RateAd[site]->Draw("same");
    //RateAd[site]->GetXaxis()->SetRangeUser(0,0.07);
    RateAd[site]->GetXaxis()->SetTitle("Time [second]");
    //RateAd[site]->GetYaxis()->SetRangeUser(20,27);
    RateAd[site]->GetYaxis()->SetTitle("Single Rate [Hz]");
    RateAd[site]->SetLineColor(3);
    RatePl[site]->Draw("same");
    RatePl[site]->SetLineColor(4);
    Rate[site]->Draw("same");
    Rate[site]->SetLineColor(2);
    
  }

  /// Accidental background rate calculation
  cout<<RSS_DYB(200, 0, 400e-6)<<endl;
  for( int site=0; site<3; site++ ) {
    int nAD;
    if( site==0 ) nAD = 2;
    if( site==1 ) nAD = 1;
    if( site==2 ) nAD = 3;

    cout<<"Processing "<<SiteName[site]<<endl;

    double TotalTime = Time[site]->Integral() * (timeEnd-timeStart)/timebins;
    double AllUp     = CountUp[site]->Integral();
    double AveRate   = AllUp/TotalTime;
    cout<<"Average rate "<<AveRate<<endl;
    double AccBkgRate = RSS_DYB( AveRate, 0, 400e-6 );
    double AccBkg = AccBkgRate * TotalTime;
    cout<<"TotalTime = "<<TotalTime<<"  AccBkgRate = "<<AccBkgRate<<"  AccBkg = "<<AccBkg<<endl;

    TH1F* tmpTime, *tmpCount;
    double TotalAccBkg = 0;
    for( int muon=0; muon<3; muon++ ) {
      cout<<"Processing muon type "<<name[muon]<<endl;
      if( muon==0 ) {
	tmpTime  = TimePl[ site ];
	tmpCount = CountUpPl[ site ];
      }
      if( muon==1 ) {
	tmpTime  = TimeAd[ site ];
	tmpCount = CountUpAd[ site ];
      }
      if( muon==2 ) {
	tmpTime  = TimeSh[ site ];
	tmpCount = CountUpSh[ site ];
      }
      
      double DiffAccBkgSum = 0;
      double DiffTimeSum = 0;
      for( int bin=1; bin<=timebins; bin++ ) {
	double time =  tmpTime->GetBinContent( bin ) * (timeEnd-timeStart)/timebins;
	double count = tmpCount->GetBinContent( bin );
	double SingRate = count/time;
	DiffTimeSum   += time;
	//cout<<"  SingRate = "<<SingRate<<endl;
	if( SingRate <= 0 ) DiffAccBkgSum += 0;
	else DiffAccBkgSum += RSS_DYB( SingRate, 0, 400e-6 ) * time;
      }
      TotalAccBkg += DiffAccBkgSum;
      cout<<"  DiffTimeSum = "<<DiffTimeSum<<"  DiffAccBkgSum = "<<DiffAccBkgSum<<endl; 
    }
    cout<<"  TotalAccBkg = "<<TotalAccBkg<<endl;
    cout<<" TotalDiffAccBkg/TotalAveAccBkg = "<< TotalAccBkg/AccBkg 
	<<"  diff = "<<(TotalAccBkg-AccBkg)/(TotalAccBkg+AccBkg)<<endl;
  }

  /// coarse bin plotting
  for( int site=0; site<3; site++ ) {
    CountUpPl[site]->Rebin(10);
    TimePl[site] ->Rebin(10);

    CountUpAd[site]->Rebin(10);
    TimeAd[site] ->Rebin(10);

    CountUpSh[site]->Rebin(10);
    TimeSh[site] ->Rebin(10);
    
    CountUp[site]->Rebin(10);
    Time[site] ->Rebin(10);

    RatePlC[site]->Divide(CountUpPl[site],TimePl[site]);
    RateAdC[site]->Divide(CountUpAd[site],TimeAd[site]);
    RateShC[site]->Divide(CountUpSh[site],TimeSh[site]);
    RateC[site]->Divide(CountUp[site],Time[site]);

    TCanvas * cc = new TCanvas;

    //    RateShC[site]->Draw();
    RateAdC[site]->Draw("");
    RateAdC[site]->SetLineColor(3);
    RatePlC[site]->Draw("same");
    RatePlC[site]->SetLineColor(4);
    RateC[site]->Draw("same");
    RateC[site]->SetLineColor(2);
  }
}

  
