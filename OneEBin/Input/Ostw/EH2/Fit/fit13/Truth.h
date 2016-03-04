#ifndef __TRUTH_H__
#define __TRUTH_H__

#include "Spectrum.h"
#include "Tool/Tool.h"
#include <string>
#include <iostream>

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

      for( unsigned int rct = 1; rct<=Basic::NoRct; rct++ ) {
	m_Omega_r[ rct-1 ] = 0;
      }

      init = false;
      SetupTruth();
      
      /*
      for( unsigned int rct = 1; rct<=Basic::NoRct; rct++ ) {
	std::cout<<set<<" "
		 <<m_AdNo<<" "
		 <<m_Omega_r[ rct-1 ]<<std::endl;
      }
      */
    }

  int SetupTruth();
  double GetTotalEnt();
  double Omega_r( int ReactorIdx );

 private:
  int m_AdNo;
  int m_dataset;
  double m_Omega_r[ Basic::NoRct ];
  bool init;
};

#endif // __TRUTH_H__
