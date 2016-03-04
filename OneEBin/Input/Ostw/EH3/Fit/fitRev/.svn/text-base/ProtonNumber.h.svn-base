/* 
   Return proton number for an AD at a certain time.
*/
#ifndef __PROTONNUMBER_H__
#define __PROTONNUMBER_H__
#include "TimeStamp.h"
#include <map>

class NProton
{
 public:
  double NPGdLs;     
  double NPGdLs_RE;   /* Relative error */
  double NPGdLs_AE;   /* Absolute error */
  double NPLs;	    
  double NPLs_RE;     /* Relative error */
  double NPLs_AE;     /* Absolute error */
};

class ProtonNumber
{
 public:
  ProtonNumber();

  NProton Get( TimeStamp Time, int AdNo );

 private:
  /* Let's hold a map of 8 ADs proton number. */
  std::map < TimeStamp /* time */, NProton  /* NProton */ >  m_NProtonData[8];
  
  /* For easy and fast query */
  TimeStamp mEarliest, mLatest;
  std::map < TimeStamp /* time */, NProton  /* NProton */ >::iterator  mLastQueryIt[8];
  

  NProton mDefaultNP;
};

extern ProtonNumber* gProtonNumber;

#endif // __PROTONNUMBER_H__
