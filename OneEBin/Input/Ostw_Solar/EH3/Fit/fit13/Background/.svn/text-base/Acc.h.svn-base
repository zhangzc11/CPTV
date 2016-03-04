#ifndef __ACC_H__
#define __ACC_H__

#include "Spectrum.h"
#include "Tool/Tool.h"
#include "string"

class Acc : public Spectrum
{
 public:
  Acc(int AdNo, int set)
    {
      m_AdNo = AdNo;
      m_dataset = set;
      std::string name = "Acc_";
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
  int m_AdNo;
  int m_dataset;
  double m_TotalErr;
};

#endif // __ACC_H__
