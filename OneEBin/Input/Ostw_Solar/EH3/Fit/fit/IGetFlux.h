#ifndef __IGETFLUX_H__
#define __IGETFLUX_H__
#include "TimeStamp.h"

class IGetFlux
{
 public:
  virtual double Get( TimeStamp Time, int RctNo, int BinIdx ) = 0;
};

#endif // __GETFLUX_H__
