#ifndef __TRUTH_H__
#define __TRUTH_H__

#include "Spectrum.h"
#include "Tool.h"
#include <string>

class Truth : public Spectrum
{
 public:
  Truth(int AdNo, int set)
    {
      m_AdNo = AdNo;
      m_dataset = set;
      std::string name = "Truth_";
      name += i2a(m_dataset) + i2a(m_AdNo);
      SetNameTitle( name.c_str(), name.c_str() );
      
      SetupTruth();
      
    }

  int SetupTruth();

 private:
  int m_AdNo;
  int m_dataset;
};

#endif // __TRUTH_H__
