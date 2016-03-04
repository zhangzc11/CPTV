#ifndef __FLUXXSEC_H__
#define __FLUXXSEC_H__

#include "Spectrum.h"
#include "Tool/Tool.h"
#include "string"

class FluxXsec : public Spectrum
{
 public:
  FluxXsec(int RctNo, std::string Info)
    {
      m_RctNo = RctNo;
      std::string name = "FluxXsec_";
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

#endif // __FLUXXSEC_H__
