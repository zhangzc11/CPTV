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
  int Site;
  TimeStamp StartTime;
  TimeStamp StopTime;
  double Fulltime;

  int nEffAd;
  double Livetime[4];
  double Rnetmu[4];
  double Rs[4];  
  TH1F*  h1dAcc8[4];
  TH1F*  h1dAcc22[4];  
};

class AnalyzeData
{
 public:
  AnalyzeData();
  
  const std::map< int /* RunNumber */, RunBrief* > &  GetRuns()  {
    return m_RunBrief;
  }

  double Livetime( int AdNo )  {
    return m_Livetime[ AdNo ];
  }

 private:
  std::map< int /* RunNumber */, RunBrief* > m_RunBrief;
  TFile* m_HistFile[3];

  double m_Livetime[ Basic::NoAd ];
};

extern AnalyzeData* gAnalyzeData;

#endif // __ANALYZEDATA_H__
