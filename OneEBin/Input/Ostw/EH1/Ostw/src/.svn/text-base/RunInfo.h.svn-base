//
//  Run information
//
//  Mar. 15, 2011 Zhe Wang
//
#ifndef _RUN_INFO_H_
#define _RUN_INFO_H_ 1

#include "TimeStamp.h"
#include <map>
#include <vector>
#include <string>

class RunInfo
{
 public:
  RunInfo()
    { Reset(); };

  ~RunInfo()
    {  };
  
 public:
  int Reset()
  {
    /// Run information
    Run = -1;
    Site = -1;

    StartTime = TimeStamp::GetBOT();
    StopTime  = TimeStamp::GetBOT();
    FullTime  = TimeStamp::GetBOT();

    NMuon = 0;

    for( int Det = 1; Det<=4; Det++ )  {
      NPlMuon[Det] = 0;
      NAdMuon[Det] = 0;
      NShMuon[Det] = 0;
      NNetMuon[Det] = 0;
      
      VetoTime[Det] = TimeStamp(0,0);
      
      NSingleUp[Det]  = 0;
      NSingleLow[Det] = 0;
    }

    /// Current time, for programing                                                                                                                  
    TimeStamp CurrTime = TimeStamp::GetBOT();
    
    SkipTime = TimeStamp::GetBOT();
    Breaks.clear();

    return 1;
  };

  int Dump();
  
  int DumpToFile( std::string filename );

 public:
  /// Run information
  int    Run;
  int    Site;

  TimeStamp StartTime;
  TimeStamp StopTime;
  TimeStamp FullTime;

  int    NMuon;
  std::map<int /* Ad number */,int >     NPlMuon;
  std::map<int /* Ad number */,int >     NAdMuon;
  std::map<int /* Ad number */,int >     NShMuon;
  std::map<int /* Ad number */,int >     NNetMuon;
  
  std::map<int /* Ad number */,TimeStamp >  VetoTime;

  std::map<int /* Ad number */,int >     NSingleUp;
  std::map<int /* Ad number */,int >     NSingleLow;
  
  /* Record breaks in a run, for example bad files. 
     They come in pairs, for the break start and the stop. */
  TimeStamp SkipTime;  /* Some files are removed from the good run list. */
  std::vector< TimeStamp > Breaks;
  
  /// Current time, for programing
  TimeStamp CurrTime;
};

#endif // _RUN_INFO_H_
