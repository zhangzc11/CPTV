#ifndef __PROTONNUMBER_H__
#define __PROTONNUMBER_H__
#include "TimeStamp.h"
#include <map>

class NProton
{
 public:
  double NPGdLs;     
  double NPGdLs_RE;
  double NPGdLs_AE;
  double NPLs;	    
  double NPLs_RE;  
  double NPLs_AE;  
};

class ProtonNumber
{
 public:
  ProtonNumber();

  NProton Get( TimeStamp Time, int AdNo );

 private:
  /* Let's hold a map of 8 ADs proton number. */
  std::map < TimeStamp /* time */, NProton  /* NProton */ >  m_NProtonData[8];
};

extern ProtonNumber* gProtonNumber;

#endif // __PROTONNUMBER_H__
