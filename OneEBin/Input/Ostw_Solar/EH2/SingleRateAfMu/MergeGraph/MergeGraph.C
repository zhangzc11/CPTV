#include "TGraph.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TStyle.h"
#include "../../Common/OstwEff.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

int main( int argc, char **argv )
{
  string target;
  string source;
  vector<string> datafiles;

  if( argc!=3 ) {
    cout<<"MergeGraph target source.list"<<endl;
    return 0;
  } else {
    target = argv[1];
    source = argv[2];
  }
  cout<<"Target: "<<target<<endl;
  cout<<"Source: "<<source<<endl;

  ifstream inlist( source.c_str() );
  string line;
  while( getline( inlist, line ) ) {
    datafiles.push_back( line );
  }
  cout<<datafiles.size()<<" input files"<<endl;
  

  // Start merging
  const int    timebins = 1000;
  const double timeStart = 0;
  const double timeEnd   = 0.1;  /* second */
  double TimeX[timebins];

  for( int bin = 1; bin<=timebins; bin++ ) {
    double time = (timeEnd-timeStart)/timebins * (bin-0.5);
    TimeX[bin-1] = time;
  }

  double  CTimeAviPl [4][timebins];
  double  CSingleUpPl[4][timebins];
  double  CSingleLwPl[4][timebins];
  double  CRatePl    [4][timebins];
	  				  
  double  CTimeAviAd [4][timebins];
  double  CSingleUpAd[4][timebins];
  double  CSingleLwAd[4][timebins];
  double  CRateAd    [4][timebins];
	  				  
  double  CTimeAviSh [4][timebins];
  double  CSingleUpSh[4][timebins];
  double  CSingleLwSh[4][timebins];
  double  CRateSh    [4][timebins];
	  				  
  double  CTimeAvi   [4][timebins];
  double  CSingleUp  [4][timebins];
  double  CSingleLw  [4][timebins];
  double  CRate      [4][timebins];

  for( int bin = 1; bin<=timebins; bin++ ) {
    for( int Ad = 1; Ad<=4; Ad++ ) {
      CTimeAviPl [Ad-1][bin-1]  = 0;
      CSingleUpPl[Ad-1][bin-1]  = 0;
      CSingleLwPl[Ad-1][bin-1]  = 0;
      CRatePl    [Ad-1][bin-1]  = 0;

      CTimeAviAd [Ad-1][bin-1]  = 0;
      CSingleUpAd[Ad-1][bin-1]  = 0;
      CSingleLwAd[Ad-1][bin-1]  = 0;
      CRateAd    [Ad-1][bin-1]  = 0;

      CTimeAviSh [Ad-1][bin-1]  = 0;
      CSingleUpSh[Ad-1][bin-1]  = 0;
      CSingleLwSh[Ad-1][bin-1]  = 0;
      CRateSh    [Ad-1][bin-1]  = 0;

      CTimeAvi   [Ad-1][bin-1]  = 0;
      CSingleUp  [Ad-1][bin-1]  = 0;
      CSingleLw  [Ad-1][bin-1]  = 0;
      CRate      [Ad-1][bin-1]  = 0;
    }
  }

  Double_t*  TTimeAviPl [4];
  Double_t*  TSingleUpPl[4];
  Double_t*  TSingleLwPl[4];
  Double_t*  TRatePl    [4];

  Double_t*  TTimeAviAd [4];
  Double_t*  TSingleUpAd[4];
  Double_t*  TSingleLwAd[4];
  Double_t*  TRateAd    [4];

  Double_t*  TTimeAviSh [4];
  Double_t*  TSingleUpSh[4];
  Double_t*  TSingleLwSh[4];
  Double_t*  TRateSh    [4];

  Double_t*  TTimeAvi   [4];
  Double_t*  TSingleUp  [4];
  Double_t*  TSingleLw  [4];
  Double_t*  TRate      [4];

  map<int /* AD No. */, TGraph * /* Time available after a pool muon */ >  TimeAviPl;
  map<int /* AD No. */, TGraph * /* Single upper limit counting      */ >  SingleUpPl;
  map<int /* AD No. */, TGraph * /* Single lower limit counting      */ >  SingleLwPl;
  map<int /* AD No. */, TGraph * /* Average rate                     */ >  RatePl;

  map<int /* AD No. */, TGraph * /* Time available after a pool muon */ >  TimeAviAd;
  map<int /* AD No. */, TGraph * /* Single upper limit counting      */ >  SingleUpAd;
  map<int /* AD No. */, TGraph * /* Single lower limit counting      */ >  SingleLwAd;
  map<int /* AD No. */, TGraph * /* Average rate                     */ >  RateAd;

  map<int /* AD No. */, TGraph * /* Time available after a pool muon */ >  TimeAviSh;
  map<int /* AD No. */, TGraph * /* Single upper limit counting      */ >  SingleUpSh;
  map<int /* AD No. */, TGraph * /* Single lower limit counting      */ >  SingleLwSh;
  map<int /* AD No. */, TGraph * /* Average rate                     */ >  RateSh;

  map<int /* AD No. */, TGraph * /* Time available after a pool muon */ >  TimeAvi;
  map<int /* AD No. */, TGraph * /* Single upper limit counting      */ >  SingleUp;
  map<int /* AD No. */, TGraph * /* Single lower limit counting      */ >  SingleLw;
  map<int /* AD No. */, TGraph * /* Average rate                     */ >  Rate;

  string Names[4] = { "TimeAvi", "SingleUp", "SingleLw", "Rate" };
  string Types[3] = { "Pl", "Ad", "Sh" };
  string ADs[4] = { "1", "2", "3", "4" };

  for( unsigned int i=0; i<datafiles.size(); i++ ) {
    cout<<"Processing "<<datafiles[i]<<endl;
    TFile f( datafiles[i].c_str(), "READ" );
    
    for( int Ad=1; Ad<=4; Ad++ ) {
      TimeAviPl [Ad] = (TGraph*) f.Get( (Names[0]+Types[0]+ADs[Ad-1]).c_str() );
      SingleUpPl[Ad] = (TGraph*) f.Get( (Names[1]+Types[0]+ADs[Ad-1]).c_str() );
      SingleLwPl[Ad] = (TGraph*) f.Get( (Names[2]+Types[0]+ADs[Ad-1]).c_str() );
      RatePl    [Ad] = (TGraph*) f.Get( (Names[3]+Types[0]+ADs[Ad-1]).c_str() );
      		    
      TimeAviAd [Ad] = (TGraph*) f.Get( (Names[0]+Types[1]+ADs[Ad-1]).c_str() );
      SingleUpAd[Ad] = (TGraph*) f.Get( (Names[1]+Types[1]+ADs[Ad-1]).c_str() );
      SingleLwAd[Ad] = (TGraph*) f.Get( (Names[2]+Types[1]+ADs[Ad-1]).c_str() );
      RateAd    [Ad] = (TGraph*) f.Get( (Names[3]+Types[1]+ADs[Ad-1]).c_str() );
      		    
      TimeAviSh [Ad] = (TGraph*) f.Get( (Names[0]+Types[2]+ADs[Ad-1]).c_str() );
      SingleUpSh[Ad] = (TGraph*) f.Get( (Names[1]+Types[2]+ADs[Ad-1]).c_str() );
      SingleLwSh[Ad] = (TGraph*) f.Get( (Names[2]+Types[2]+ADs[Ad-1]).c_str() );
      RateSh    [Ad] = (TGraph*) f.Get( (Names[3]+Types[2]+ADs[Ad-1]).c_str() );
      		    
      TimeAvi   [Ad] = (TGraph*) f.Get( (Names[0]+ADs[Ad-1]).c_str() );
      SingleUp  [Ad] = (TGraph*) f.Get( (Names[1]+ADs[Ad-1]).c_str() );
      SingleLw  [Ad] = (TGraph*) f.Get( (Names[2]+ADs[Ad-1]).c_str() );
      Rate      [Ad] = (TGraph*) f.Get( (Names[3]+ADs[Ad-1]).c_str() );

      TTimeAviPl [Ad-1] = TimeAviPl [Ad]->GetY();
      TSingleUpPl[Ad-1] = SingleUpPl[Ad]->GetY();
      TSingleLwPl[Ad-1] = SingleLwPl[Ad]->GetY();
      TRatePl    [Ad-1] = RatePl    [Ad]->GetY();
      		       	  		    
      TTimeAviAd [Ad-1] = TimeAviAd [Ad]->GetY();
      TSingleUpAd[Ad-1] = SingleUpAd[Ad]->GetY();
      TSingleLwAd[Ad-1] = SingleLwAd[Ad]->GetY();
      TRateAd    [Ad-1] = RateAd    [Ad]->GetY();
      		       	  		    
      TTimeAviSh [Ad-1] = TimeAviSh [Ad]->GetY();
      TSingleUpSh[Ad-1] = SingleUpSh[Ad]->GetY();
      TSingleLwSh[Ad-1] = SingleLwSh[Ad]->GetY();
      TRateSh    [Ad-1] = RateSh    [Ad]->GetY();
      		       	  		    
      TTimeAvi   [Ad-1] = TimeAvi   [Ad]->GetY();
      TSingleUp  [Ad-1] = SingleUp  [Ad]->GetY();
      TSingleLw  [Ad-1] = SingleLw  [Ad]->GetY();
      TRate      [Ad-1] = Rate      [Ad]->GetY();

      for(int bin = 1; bin<=timebins; bin++ ) {
	
	CTimeAviPl [Ad-1][bin-1] += TTimeAviPl [Ad-1][bin-1] ;
	CSingleUpPl[Ad-1][bin-1] += TSingleUpPl[Ad-1][bin-1] ;
	CSingleLwPl[Ad-1][bin-1] += TSingleLwPl[Ad-1][bin-1] ;
	
	CTimeAviAd [Ad-1][bin-1] += TTimeAviAd [Ad-1][bin-1] ;
	CSingleUpAd[Ad-1][bin-1] += TSingleUpAd[Ad-1][bin-1] ;
	CSingleLwAd[Ad-1][bin-1] += TSingleLwAd[Ad-1][bin-1] ;
	
	CTimeAviSh [Ad-1][bin-1] += TTimeAviSh [Ad-1][bin-1] ;
	CSingleUpSh[Ad-1][bin-1] += TSingleUpSh[Ad-1][bin-1] ;
	CSingleLwSh[Ad-1][bin-1] += TSingleLwSh[Ad-1][bin-1] ;

	CTimeAvi   [Ad-1][bin-1] += TTimeAvi   [Ad-1][bin-1] ;
	CSingleUp  [Ad-1][bin-1] += TSingleUp  [Ad-1][bin-1] ;
	CSingleLw  [Ad-1][bin-1] += TSingleLw  [Ad-1][bin-1] ;
      }
    }
  }

  double wid = (timeEnd-timeStart)/timebins;
  for( int Ad = 1; Ad<=4; Ad++ ) {
    for( int bin=1; bin<=timebins; bin++ ) {
      if( CTimeAviPl [Ad-1][bin-1]>0 ) CRatePl[Ad-1][bin-1] = CSingleUpPl[Ad-1][bin-1] / (CTimeAviPl [Ad-1][bin-1] * wid);
      if( CTimeAviAd [Ad-1][bin-1]>0 ) CRateAd[Ad-1][bin-1] = CSingleUpAd[Ad-1][bin-1] / (CTimeAviAd [Ad-1][bin-1] * wid);
      if( CTimeAviSh [Ad-1][bin-1]>0 ) CRateSh[Ad-1][bin-1] = CSingleUpSh[Ad-1][bin-1] / (CTimeAviSh [Ad-1][bin-1] * wid);
      if( CTimeAvi   [Ad-1][bin-1]>0 ) CRate  [Ad-1][bin-1] = CSingleUp[Ad-1][bin-1]   / (CTimeAvi [Ad-1][bin-1]   * wid);
      if( bin%100 == 0 ) {
        cout<< CSingleUpPl[Ad-1][bin-1] <<" "<< CTimeAviPl [Ad-1][bin-1] <<" "<< CRatePl[Ad-1][bin-1] <<endl;
      }
    }
  }


  TFile Output(target.c_str(),"RECREATE");

  for( int Ad=1; Ad<=4; Ad++ ) {
    TimeAviPl [Ad] = new TGraph( timebins, TimeX, CTimeAviPl [Ad-1] );
    SingleUpPl[Ad] = new TGraph( timebins, TimeX, CSingleUpPl[Ad-1] );
    SingleLwPl[Ad] = new TGraph( timebins, TimeX, CSingleLwPl[Ad-1] );
    RatePl    [Ad] = new TGraph( timebins, TimeX, CRatePl    [Ad-1] );
    		  				       
    TimeAviAd [Ad] = new TGraph( timebins, TimeX, CTimeAviAd [Ad-1] );
    SingleUpAd[Ad] = new TGraph( timebins, TimeX, CSingleUpAd[Ad-1] );
    SingleLwAd[Ad] = new TGraph( timebins, TimeX, CSingleLwAd[Ad-1] );
    RateAd    [Ad] = new TGraph( timebins, TimeX, CRateAd    [Ad-1] );
    		  				       
    TimeAviSh [Ad] = new TGraph( timebins, TimeX, CTimeAviSh [Ad-1] );
    SingleUpSh[Ad] = new TGraph( timebins, TimeX, CSingleUpSh[Ad-1] );
    SingleLwSh[Ad] = new TGraph( timebins, TimeX, CSingleLwSh[Ad-1] );
    RateSh    [Ad] = new TGraph( timebins, TimeX, CRateSh    [Ad-1] );
    		  				       
    TimeAvi   [Ad] = new TGraph( timebins, TimeX, CTimeAvi   [Ad-1] );
    SingleUp  [Ad] = new TGraph( timebins, TimeX, CSingleUp  [Ad-1] );
    SingleLw  [Ad] = new TGraph( timebins, TimeX, CSingleLw  [Ad-1] );
    Rate      [Ad] = new TGraph( timebins, TimeX, CRate      [Ad-1] );

    TimeAviPl [Ad]->SetName( (Names[0]+Types[0]+ADs[Ad-1]).c_str() );
    SingleUpPl[Ad]->SetName( (Names[1]+Types[0]+ADs[Ad-1]).c_str() );
    SingleLwPl[Ad]->SetName( (Names[2]+Types[0]+ADs[Ad-1]).c_str() );
    RatePl    [Ad]->SetName( (Names[3]+Types[0]+ADs[Ad-1]).c_str() );

    TimeAviAd [Ad]->SetName( (Names[0]+Types[1]+ADs[Ad-1]).c_str() );
    SingleUpAd[Ad]->SetName( (Names[1]+Types[1]+ADs[Ad-1]).c_str() );
    SingleLwAd[Ad]->SetName( (Names[2]+Types[1]+ADs[Ad-1]).c_str() );
    RateAd    [Ad]->SetName( (Names[3]+Types[1]+ADs[Ad-1]).c_str() );

    TimeAviSh [Ad]->SetName( (Names[0]+Types[2]+ADs[Ad-1]).c_str() );
    SingleUpSh[Ad]->SetName( (Names[1]+Types[2]+ADs[Ad-1]).c_str() );
    SingleLwSh[Ad]->SetName( (Names[2]+Types[2]+ADs[Ad-1]).c_str() );
    RateSh    [Ad]->SetName( (Names[3]+Types[2]+ADs[Ad-1]).c_str() );

    TimeAvi   [Ad]->SetName( (Names[0]+ADs[Ad-1]).c_str() );
    SingleUp  [Ad]->SetName( (Names[1]+ADs[Ad-1]).c_str() );
    SingleLw  [Ad]->SetName( (Names[2]+ADs[Ad-1]).c_str() );
    Rate      [Ad]->SetName( (Names[3]+ADs[Ad-1]).c_str() );

    TimeAviPl [Ad] -> Write();
    SingleUpPl[Ad] -> Write();
    SingleLwPl[Ad] -> Write();
    RatePl    [Ad] -> Write();
    		  
    TimeAviAd [Ad] -> Write();
    SingleUpAd[Ad] -> Write();
    SingleLwAd[Ad] -> Write();
    RateAd    [Ad] -> Write();
    		  
    TimeAviSh [Ad] -> Write();
    SingleUpSh[Ad] -> Write();
    SingleLwSh[Ad] -> Write();
    RateSh    [Ad] -> Write();
    		  
    TimeAvi   [Ad] -> Write();
    SingleUp  [Ad] -> Write();
    SingleLw  [Ad] -> Write();
    Rate      [Ad] -> Write();
  }

  /// Make some summary plots for different sites
  double  SiteRatePl    [timebins];
  double  SiteRateAd    [timebins];
  double  SiteRateSh    [timebins];
  double  SiteRate      [timebins];

  TGraph*  GrRatePl;
  TGraph*  GrRateAd;
  TGraph*  GrRateSh;
  TGraph*  GrRate  ;

  int nAD = 0;
  if( CSingleUpPl[0][0]>0 ) nAD ++;
  if( CSingleUpPl[1][0]>0 ) nAD ++;
  if( CSingleUpPl[2][0]>0 ) nAD ++;
  if( CSingleUpPl[3][0]>0 ) nAD ++;
  cout<<nAD<<" ADs are involved"<<endl;
  
  double totalTime = 0;
  double totalCount= 0;
  double timePl[timebins], timeAd[timebins], timeSh[timebins], time[timebins];
  for( int bin=1; bin<=timebins; bin++ ) {
    timePl [bin-1] = 0;
    timeAd [bin-1] = 0;
    timeSh [bin-1] = 0;
    time   [bin-1] = 0;
  }

  for( int bin=1; bin<=timebins; bin++ ) {
    double countPl, countAd, countSh, count;    
    countPl=countAd=countSh=count=0;

    for( int ad=1; ad<=nAD; ad++ ) {      
      timePl [bin-1] += CTimeAviPl[ad-1][bin-1];
      timeAd [bin-1] += CTimeAviAd[ad-1][bin-1];
      timeSh [bin-1] += CTimeAviSh[ad-1][bin-1];
      time   [bin-1] += CTimeAvi  [ad-1][bin-1];

      countPl += CSingleUpPl[ad-1][bin-1];
      countAd += CSingleUpAd[ad-1][bin-1];
      countSh += CSingleUpSh[ad-1][bin-1];
      count   += CSingleUp  [ad-1][bin-1];
    }
    totalTime += time [bin-1];
    totalCount+= count;
    
    SiteRatePl [bin-1] = countPl / (timePl[bin-1] * wid);
    SiteRateAd [bin-1] = countAd / (timeAd[bin-1] * wid);
    SiteRateSh [bin-1] = countSh / (timeSh[bin-1] * wid);
    SiteRate   [bin-1] = count   / (time  [bin-1] * wid);

  }
    
  GrRatePl = new TGraph( timebins, TimeX, SiteRatePl);
  GrRateAd = new TGraph( timebins, TimeX, SiteRateAd);
  GrRateSh = new TGraph( timebins, TimeX, SiteRateSh);
  GrRate   = new TGraph( timebins, TimeX, SiteRate  );

  GrRatePl ->SetName( "GrRatePl" );
  GrRateAd ->SetName( "GrRateAd" );
  GrRateSh ->SetName( "GrRateSh" );
  GrRate   ->SetName( "GrRate  " );

  GrRatePl ->Write();
  GrRateAd ->Write();
  GrRateSh ->Write();
  GrRate   ->Write();

  gStyle->SetOptTitle(kFALSE);
  TCanvas * c = new TCanvas;

  GrRateAd ->Draw("apl");
  GrRateAd->GetXaxis()->SetRangeUser(0,0.07);
  GrRateAd->GetXaxis()->SetTitle("Time [second]");
  GrRateAd->GetYaxis()->SetRangeUser(20,23);
  GrRateAd->GetYaxis()->SetTitle("Single Rate [Hz]");
  GrRateAd ->Draw("apl");
  GrRateAd->SetLineColor(3);
  GrRatePl->Draw("same");
  GrRatePl->SetLineColor(4);
  GrRate->Draw("same");
  GrRate->SetLineColor(2);
  
  c->Print( "Summary.ps" );
  
  Output.Close();

  //// Calculate average event rate and differential rate sum
  double aveRate = totalCount/ (totalTime*wid);
  cout<<"Average singles rate: "<<aveRate<<endl;
  cout<<"Total AccBkg with ave. rate: "<< RSS_DYB( aveRate, 0, 400e-6 )*(totalTime*wid) <<endl;
  
  double TotalDiffPl = 0;
  double TotalDiffAd = 0;
  double TotalDiffSh = 0;
  double TotalDiff = 0;
  for( int bin=1; bin<=timebins; bin++ ) {
    if( SiteRatePl [bin-1] != 0 ) 
      TotalDiffPl += RSS_DYB( SiteRatePl [bin-1], 0, 400e-6 )* timePl [bin-1] * wid;
    if( SiteRateAd [bin-1] != 0 )
      TotalDiffAd += RSS_DYB( SiteRateAd [bin-1], 0, 400e-6 )* timeAd [bin-1] * wid;
    if( SiteRateSh [bin-1] != 0 )
      TotalDiffSh += RSS_DYB( SiteRateSh [bin-1], 0, 400e-6 )* timeSh [bin-1] * wid;
  }
  TotalDiff = TotalDiffPl+TotalDiffAd+TotalDiffSh;

  cout<<"Total Pl AccBkg with diff rate: "<< TotalDiffPl <<endl;
  cout<<"Total Ad AccBkg with diff rate: "<< TotalDiffAd <<endl;
  cout<<"Total Sh AccBkg with diff rate: "<< TotalDiffSh <<endl;
  cout<<"Total AccBkg with diff rate: "<< TotalDiff <<endl;

  return 1;
}
