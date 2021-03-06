/// 
/// Cuts list
/// 
/// Zhe Wang, Nov. 12 2011
///

#ifndef _CUTS_H_
#define _CUTS_H_

#include "CLHEP/Units/SystemOfUnits.h"
using namespace CLHEP;

class Cuts
{  
 public:
  enum DataSet_t{
    Gd = 0,
    H  = 1 };

 public:
  Cuts( DataSet_t DataSet  )
    {
      /// Events fall into the first three catagories won't be considered.
      /// ================================================================
      /// 
      /// A general cuts
      MultiTrig = 0x10000100;
      ESumTrig  = 0x10001000;

      /// The same sub-event. 
      /// The Latency covers the relative delay between detectors and 
      /// retrigger delay DocDB 6756.
      Latency = 2 * microsecond;

      /// Retrigger window
      ReTrigWin = 10 * microsecond;
 
      /// Event type determination.
      /// =========================
      /// Muon idenfication
      NChnlIws  = 12;
      NChnlOws  = 15;
      QSumAD    = 20 * MeV;
      ShowerAD  = 2.5 * GeV;

      /// A general cuts for all AD for flashers
      /* Flasher cuts needs to be reevaluated. */
      /* 8Inch flasher */
      /*
      TRMS      = 15;
      QMaxToSumLow  = 0;
      QMaxToSumHigh = 0.3;
      */
      // Ellipse cut
      /* 2Inch flasher */ 
      /* ... */

      /// AD event select
      QSumLow   = DataSet == Gd ? 0.7 * MeV : 1.5 * MeV;
      QSumHigh  = 20  * MeV;

      /// Window decision
      PlMuVeto   = 400 * microsecond;
      AdMuVeto   = 800 * microsecond;
      ShMuVeto   = 1 * second;
      CoinDt     = DataSet == Gd ? 200 * microsecond : 400 * microsecond;

      /// Distance between the prompt and delayed signal
      D2First    = DataSet == Gd ? 50000 * mm : 500 * mm;

      /// Energy cut for 2.2 MeV signal
      /// Need a Crystal ball fit
      Mean[0]= 2.37057; Sigma[0]= 0.149178;
      Mean[1]= 2.37342; Sigma[1]= 0.150645;
      Mean[2]= 2.36558; Sigma[2]= 0.145425;
      Mean[3]= 2.36834; Sigma[3]= 0.152641;
      Mean[4]= 2.38882; Sigma[4]= 0.147328;
      Mean[5]= 2.36642; Sigma[5]= 0.158039;

      for( int ad=1; ad<=6; ad++ ) {
	E22Low[ad-1] = (Mean[ad-1] - 3*Sigma[ad-1]) * MeV;
	E22Hgh[ad-1] = (Mean[ad-1] + 3*Sigma[ad-1]) * MeV;
      }

      /// Energy cut for 8 MeV signal
      E8Low = 6.0 * MeV;
      E8Hgh = 10.0 * MeV;
    };

  ~Cuts() {}; 

 public:
  /// Latency
  double  Latency;

  /// A general cuts for all events
  int     MultiTrig; 
  int     ESumTrig;

  /// Use a simple window cut determine triggers
  /// Could be more complicated
  double  ReTrigWin;

  /// A general cuts for all AD events
  double  TRMS;
  double  QMaxToSumLow;
  double  QMaxToSumHigh;
  
  /// Muon idenfication 
  int     NChnlIws;
  int     NChnlOws;
  double  QSumAD;
  double  ShowerAD;

  /// AD event selection
  double  QSumLow;   
  double  QSumHigh;  

  /// The two critical cuts determine the
  /// muon spallation t and
  /// delay-coincident delta t
  double  PlMuVeto;
  double  AdMuVeto;
  double  ShMuVeto;
  double  CoinDt;

  /// Distance between the prompt and delayed signal
  double  D2First;

  /// Energy cut for 2.2 MeV signal
  double Mean[8], Sigma[8];
  double E22Low[8];
  double E22Hgh[8];

  /// Energy cut for 8 MeV signal
  double E8Low;
  double E8Hgh;
};

#endif // _CUTS_H_
