/*
  Base class for all spectrum-like data, Measurement and Truth.
  All H2D with a common binning schemem.
  
  Zhe Wang, June 2012
*/

#ifndef __SPECTRUM_H__
#define __SPECTRUM_H__
#include "TH1D.h"
#include "Constants.h"

class Spectrum : public TH1D
{
 public:
  Spectrum()
    {
      this->SetBins(Binning::NHistoBin, Binning::BeginEnergy, Binning::EndEnergy );
    };

  /// Everything will has the same binning and energy range
  void SetNameTitle(const char* name, const char* title)
    {
      this->SetName(name);
      this->SetTitle(title);
    };

  ///
  ~Spectrum()
    {};
};

#endif // __SPECTRUM_H__
