#ifndef __LI9_H__
#define __LI9_H__

#include "Spectrum.h"
#include "Tool/Tool.h"
#include "string"

class Li9 : public Spectrum
{
 public:
  Li9(int AdNo, int set)
    {
      m_AdNo = AdNo;
      m_dataset = set;
      std::string name = "Li9_";
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

#endif // __LI9_H__
