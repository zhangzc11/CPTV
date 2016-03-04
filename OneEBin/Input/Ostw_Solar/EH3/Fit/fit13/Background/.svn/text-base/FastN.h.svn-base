#ifndef __FASTN_H__
#define __FASTN_H__

#include "Spectrum.h"
#include "Tool/Tool.h"
#include "string"

class FastN : public Spectrum
{
 public:
  FastN(int AdNo, int set)
    {
      m_AdNo = AdNo;
      m_dataset = set;
      std::string name = "FastN_";
      name += i2a(set) + i2a(m_AdNo);
      SetNameTitle( name.c_str(), name.c_str() );

      SetupBkg();
    }

 private:
  int SetupBkg();

 public:
  double GetTotalErr() {
    return m_TotalErr;
  };

 private:
  double shape(double energy); // return entries in 0.1 MeV bin;  

  int m_AdNo;
  int m_dataset;
  double m_TotalErr;
};

#endif // __FASTN_H__
