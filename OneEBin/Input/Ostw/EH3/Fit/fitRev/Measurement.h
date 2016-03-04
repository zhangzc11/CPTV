/*
  Measurement: Represent the measured IBD positron spectrum from each AD
  Zhe Wang 2012 June
*/

#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__

#include "Spectrum.h"
#include "Tool/Tool.h"
#include "string"

class Measurement : public Spectrum
{
 public:
  Measurement(int AdNo, int set)
    {
      m_AdNo = AdNo;
      m_dataset = set;
      std::string name = "Measurement_";
      name += i2a(m_dataset) + i2a(m_AdNo);
      SetNameTitle( name.c_str(), name.c_str() );

      SetupMeas();
    }

  int SetupMeas();

  double Integral();
  
  double GetTotalErr()  {
    return m_TotalErr;
  }

 private:
  int m_AdNo;
  int m_dataset;
  double m_TotalErr;
};

#endif // __MEASUREMENT_H__
