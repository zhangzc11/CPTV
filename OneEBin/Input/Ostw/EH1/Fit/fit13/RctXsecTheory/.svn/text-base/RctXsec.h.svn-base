/*
  1. Reactor spectrum x cross section
  2. Xaxis is turned Eprompt
  3. Project high-definition plot to low-definition plot
  
  unit: cm*cm / MeV
*/
#ifndef __RCTXSEC_H__
#define __RCTXSEC_H__
#include "Spectrum.h"
#include "RctSpec.h"
#include "Crosssection.h"
#include <string>

class RctXsec : public Spectrum
{
 public:
  RctXsec(std::string Info, Crosssection* xsec, RctSpec* rctSpec)
    {
      std::string name = Info;
      SetNameTitle( name.c_str(), name.c_str() );
      
      mCrosssection = xsec;
      mRctSpec = rctSpec;

      SetupRctXsec();
    }
  
  void SetupRctXsec();

 private:
  Crosssection* mCrosssection;
  RctSpec* mRctSpec;

};

extern RctXsec* gU238Xsec ;
extern RctXsec* gU235Xsec ;
extern RctXsec* gPu239Xsec;
extern RctXsec* gPu241Xsec;

#endif // __RCTXSEC_H__
