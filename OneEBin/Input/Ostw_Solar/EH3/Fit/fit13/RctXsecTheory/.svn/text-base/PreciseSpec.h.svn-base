#ifndef __PRECISESPEC_H__
#define __PRECISESPEC_H__
#include "TH1D.h"
#include "Constants.h"

class PreciseSpec : public TH1D
{
 public:
  PreciseSpec()
    {
      this->SetBins(Binning::NPreciseBin, Binning::BeginEnergy, Binning::EndEnergy );
    };

  /// Everything will has the same binning and energy range
  void SetNameTitle(const char* name, const char* title)
    {
      this->SetName(name);
      this->SetTitle(title);
    };

  ///
  ~PreciseSpec()
    {};
};

#endif // __PRECISESPEC_H__
