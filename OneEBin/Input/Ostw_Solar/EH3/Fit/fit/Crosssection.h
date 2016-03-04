#ifndef __CROSSSECTION_H__
#define __CROSSSECTION_H__

#include "Constants.h"
#include "Spectrum.h"
#include "string"

class Crosssection : public Spectrum
{
 public:
  Crosssection()
    {
      std::string name = "Crosssection";
      SetNameTitle( name.c_str(), name.c_str() );
      
      SetupCrosssection();
    }

 private:
  int SetupCrosssection();

  int m_AdNo;

};

R__EXTERN Crosssection* gCrosssection;

#endif // __CROSSSECTION_H__
