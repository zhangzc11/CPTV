/*
  Unit: n/MeV
 */
#ifndef __RCTSPEC_H__
#define __RCTSPEC_H__
#include <string>
#include "PreciseSpec.h"
#include "Constants.h" 

class RctSpec : public PreciseSpec
{
 public:
  RctSpec( std::string DataFile, std::string Info ) 
    {
      std::string name  = Info;
      std::string title = Info;
      SetNameTitle( name.c_str(), title.c_str() );

      SetDataFile( DataFile );
    };

  void SetDataFile(std::string DataFile);

  void SetNameTitle(const char* name, const char* title);

  ///
  ~RctSpec()
    {};

 private:
  std::string mDataFile;
};

extern RctSpec* gU238 ;
extern RctSpec* gU235 ;
extern RctSpec* gPu239;
extern RctSpec* gPu241;

extern TH1F* gU238X ; 
extern TH1F* gU235X ;
extern TH1F* gPu239X;
extern TH1F* gPu241X;

#endif // __RCTSPEC_H__
