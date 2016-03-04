/********************************************************************
 * Class to read reactor data tables from offline DB using DBI Interface.
 * Reduced from GuoFu's update on InverseBeta generator.
 ********************************************************************/

#ifndef __KRLREACTORFLUX_HH__
#define __KRLREACTORFLUX_HH__

#include "TObject.h"
#include "TMath.h"
#include "Context/Context.h"

class DbiResultKey;
class ServiceMode;

class KRLReactorFlux : public TObject {
public:
  Double_t fEPointsFlux[6][33]; //0-1 for dayabay site, 2-5 for la site, at 33 energy points.
  Double_t fTotalNumber[6];
public:
  KRLReactorFlux();
  ~KRLReactorFlux() {;}
  void SetTime(time_t time) { fTime = time; } 
  void SetContext();
private:
  int readReactorTable(const ServiceMode& serviceMode);

  Context fluxLastContext;
  const DbiResultKey* fluxLastResult;
  time_t fTime;
};
R__EXTERN KRLReactorFlux* gReactorFlux;

#endif
