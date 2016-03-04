#ifndef __GETWEEKLYFLUX_H__
#define __GETWEEKLYFLUX_H__
#include "IGetFlux.h"
#include "TimeStamp.h"
#include "Flux.h"
#include <map>

class GetWeeklyFlux : public IGetFlux
{
 public:
  GetWeeklyFlux();

  double Get( TimeStamp Time, int RctNo, int BinIdx );

 private:
  std::map< TimeStamp /* Week */, Flux* > m_FluxSpecs[6];
};

R__EXTERN GetWeeklyFlux* gGetWeeklyFlux;

#endif // __WEEKLYFLUX_H__
