#ifndef __FLUX_H__
#define __FLUX_H__

#include "Spectrum.h"
#include "Tool.h"
#include "string"

class Flux : public Spectrum
{
 public:
  Flux(int RctNo, std::string Info)
    {
      m_RctNo = RctNo;
      std::string name = "Flux_";
      name += i2a(m_RctNo);
      name += "_";
      name += Info;
      SetNameTitle( name.c_str(), name.c_str() );
    }
  
  int GetRctNo()
  {
    return m_RctNo;
  }

 private:
  int m_RctNo;
};

#endif // __FLUX_H__
