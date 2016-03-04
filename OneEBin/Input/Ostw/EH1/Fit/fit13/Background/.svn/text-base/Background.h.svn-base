/* 
   Total background spectrum
*/
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "Spectrum.h"
#include "Tool/Tool.h"
#include "string"

class Background : public Spectrum
{
 public:
  Background(int AdNo, int set)
    {
      m_AdNo = AdNo;
      std::string name = "Background_";
      name += i2a(set) + i2a(m_AdNo);
      SetNameTitle( name.c_str(), name.c_str() );
      
      m_TotalErrSqr = 0;
    }

 public:
  int AddBkg( Spectrum* BkgSpec );
  double GetTotalEnt();
  double GetTotalErr();

 private:
  int m_AdNo;
  int m_dataset;

  double m_TotalErrSqr;
};

#endif // __BACKGROUND_H__
