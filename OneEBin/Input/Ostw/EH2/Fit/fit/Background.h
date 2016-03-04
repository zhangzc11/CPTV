#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "Spectrum.h"
#include "Tool.h"
#include "string"

class Background : public Spectrum
{
 public:
  Background(int AdNo, int set)
    {
      m_AdNo = AdNo;
      std::string name = "Background";
      name += i2a(m_AdNo) + " " + i2a(set);
      SetNameTitle( name.c_str(), name.c_str() );

      SetupBkg();
    }

private:
  int SetupBkg();

 private:
  int m_AdNo;
  int m_dataset;
};

#endif // __BACKGROUND_H__
