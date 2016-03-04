/*
  Get run information, like live time, singles rate etc. and signal number and prompt spectrum  
  for each run and each AD from RunInfo.txt and corresponding root tree files.
  Zhe Wang, Jun. 2012
*/
#ifndef __ANALYZEDATA_H__
#define __ANALYZEDATA_H__
#include "TimeStamp.h"
#include "Constants.h"
#include <map>
#include "TH1F.h"
#include "TFile.h"

class RunBrief
{
 public:
  int RunNumber;
  int Dataset;
  int Site;
  TimeStamp StartTime;
  TimeStamp StopTime;
  double Fulltime;

  int nEffAd;
  double Livetime[4];  
  double NNet[4];
  double Rs[4];
  double Scale[4];
  TH1F*  h1dVtx[4];
  TH1F*  h1dAccBkg[4];
  TH1F*  h1dAcc[4];
  /* 
     Ostw efficiency for GdLS region and LS region. 
     Assuming both position efficiency and neutron efficiency = 1 
  */

  double OstwEff[4];

  double NSgUp[4];
  double NSgLw[4];
  double TwoFold[4];
  double ThreeFold[4];
  double NBVtx[4];
  double NAVtx[4];
  double NAEng[4];
  
  double NAcc[4];
};

class AnalyzeData
{
 public:
  AnalyzeData();
  
  std::vector< RunBrief* > &  GetRuns()  {
    return m_RunBrief;
  }

  double Fulltime( int dataset, int AdNo )  {
    return m_Fulltime[ dataset ][ AdNo-1 ];
  }
  
  double Livetime( int dataset, int AdNo ) {
    return m_Livetime[ dataset ][ AdNo-1 ];
  }

  double MuVeEff( int dataset, int AdNo ) {
    return m_MuVeEff[ dataset ][ AdNo-1 ];
  }

  double OstwEff( int dataset, int AdNo ) {
    return m_OstwEff[ dataset ][ AdNo-1 ];
  }
  
 private:
  std::vector< RunBrief* > m_RunBrief;
  TFile* m_HistFile[ 2 ][ 3 ];

 public:
  /* total fulltime, muon veto efficiency and average Ostw efficiency */
  double m_Fulltime[ 2 ][ Basic::NoAd ];
  double m_Livetime[ 2 ][ Basic::NoAd ];
  double m_MuVeEff [ 2 ][ Basic::NoAd ];
  double m_OstwEff [ 2 ][ Basic::NoAd ];

  double NNet[ 2 ][ Basic::NoAd ];
  double NSgUp[ 2 ][ Basic::NoAd ];
  double NSgLw[ 2 ][ Basic::NoAd ];
  double TwoFold[ 2 ][ Basic::NoAd ];
  double ThreeFold[ 2 ][ Basic::NoAd ];
  double NBVtx[ 2 ][ Basic::NoAd ];
  double NAVtx[ 2 ][ Basic::NoAd ];
  double NAEng[ 2 ][ Basic::NoAd ];
  double NAcc[ 2 ][ Basic::NoAd ];
};

extern AnalyzeData* gAnalyzeData;

#endif // __ANALYZEDATA_H__
