/*
  Unit: in CLHEP units.
 */
#ifndef __GETFLUXXSEC_H__
#define __GETFLUXXSEC_H__
#include "IGetFluxXsec.h"
#include "TimeStamp.h"
#include "FluxXsec.h"
#include <map>

class GetFluxXsec : public IGetFluxXsec
{
 public:
  GetFluxXsec();

  double Get( TimeStamp time, int RctNo, int BinIdx );

 private:
  std::map< TimeStamp /* Week */, FluxXsec* > m_FluxXsecSpecs[6];

  /* For easy and fast query */
  TimeStamp mEarliest, mLatest;
  std::map< TimeStamp /* Week */, FluxXsec* >::iterator mLastQueryIt[6];


  FluxXsec* mDefaultFluxXsec;
};

extern GetFluxXsec* gGetFluxXsec;

#endif // __FLUXXSEC_H__
