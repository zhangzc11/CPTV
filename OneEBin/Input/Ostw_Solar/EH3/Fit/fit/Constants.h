/*
  A simple file contain all non-array constants. (length<10)
  
  Apr. 9, 2012
  Zhe Wang
*/

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "CLHEP/Units/SystemOfUnits.h"
#include "TVector3.h"
#include "TimeStamp.h"

namespace Binning
{
  /*
    Working on EPrompt
  */
  static const double BeginEnergy = 0  * CLHEP::MeV;
  static const double EndEnergy   = 10 * CLHEP::MeV;
  static const unsigned int NHistoBin = 100;
  static const unsigned int NFitBin   = 1;
};

namespace Basic
{
  static const bool GdFit = false;
  static const bool HFit  = true;

  static const bool DailyFlux = false;
  static const bool WeeklyFulx = ! DailyFlux;

  /*
    All Ad and Reactor numbers are counted from 0.
  */
  static const unsigned int NoAd = 6;
  static const unsigned int NoRct = 6;

  static const TimeStamp BeginTime(2011,9,20,0,0,0);
  //static const TimeStamp BeginTime(2011,12,24,0,0,0);
  //static const TimeStamp EndTime  (2011,12,25,0,0,0);
  static const TimeStamp EndTime(2012,02,17,0,0,0);
  // A day
  static const TimeStamp StepTime(24*60*60);
}

namespace Position
{
  /* DocDb 7560 */
  static const TVector3 Ad[8] = 
    { TVector3( 363.0177*CLHEP::m, 49.1021 *CLHEP::m, -70.8146*CLHEP::m ),
      TVector3( 359.0053*CLHEP::m, 53.5544 *CLHEP::m, -70.8107*CLHEP::m ),
      TVector3( 4.4758  *CLHEP::m, -873.507*CLHEP::m, -67.5209*CLHEP::m ),
      TVector3( 931.5798*CLHEP::m, -1422.41*CLHEP::m, -66.4819*CLHEP::m ),
      TVector3( 936.294 *CLHEP::m, -1418.72*CLHEP::m, -66.4935*CLHEP::m ),
      TVector3( 935.2752*CLHEP::m, -1427.15*CLHEP::m, -66.4933*CLHEP::m ),
      TVector3( 0*CLHEP::m, 0*CLHEP::m, 0*CLHEP::m ),   // unknown
      TVector3( 0*CLHEP::m, 0*CLHEP::m, 0*CLHEP::m ),   // unknown
    };

  static const TVector3 Rct[6] =
    { TVector3( 360.6984*CLHEP::m, 410.1788*CLHEP::m, -40.2281*CLHEP::m ),
      TVector3( 449.4947*CLHEP::m, 409.3679*CLHEP::m, -40.2367*CLHEP::m ),
      TVector3( -321.63 *CLHEP::m, -539.583*CLHEP::m, -39.7268*CLHEP::m ),
      TVector3( -268.767*CLHEP::m, -468.232*CLHEP::m, -39.7202*CLHEP::m ),
      TVector3( -546.752*CLHEP::m, -952.721*CLHEP::m, -39.7959*CLHEP::m ),
      TVector3( -493.898*CLHEP::m, -881.363*CLHEP::m, -39.7857*CLHEP::m ),
    };
  
  static const double BaselineUncertainty = 28 * CLHEP::mm;
}

namespace Reactor
{
  static const double NmlPower = 2.9e6 * CLHEP::watt;
  static const double NmlU235Frac  = 0.64;
  static const double NmlU238Frac  = 0.08;
  static const double NmlPu239Frac = 0.25;
  static const double NmlPu241Frac = 0.03;
}

namespace DataPath
{
  static const char * const WeeklyFluxData =    "../data/Flux.20110920-20120220.txt";
  static const char * const NProtonData    =    "../data/NProton.20110920-20120220.txt";
  static const char * const RunInfo        =    "../../data/Sample/08_P12b_CorrectLiveTime/RunInfo.OnlyP12b.txt";
  static const char * const EH1Root        =    "../../data/Sample/08_P12b_CorrectLiveTime/EH1.root";
  static const char * const EH2Root        =    "../../data/Sample/08_P12b_CorrectLiveTime/EH2.root";
  static const char * const EH3Root        =    "../../data/Sample/08_P12b_CorrectLiveTime/EH3.root";
}

namespace Phys
{
  // Enu = Eprompt_vis + 0.792 MeV
  static const double EnuToEprompt = 0.792 * CLHEP::MeV;
  
  // GdLs, Gd H capture ratio
  static const double GdLS_Gd_Cap_Frac = 0.8383;
  static const double GdLS_H_Cap_Frac  = 0.1504;

  // GdLs region
  static const double GdLS_Distance_eff = 0.713;

  //static const double 

  // Ls region
  static const double LowECut_eff = 0.65708;
  static const double En3sigma_eff = 0.905;
  static const double LS_Distance_eff = 0.65;

  // GdLs Capture time constant
  static const double GdLS_Cap_Lam = 34882.6 * (1/CLHEP::second);

  // Ls Capture time constant
  static const double LS_Cap_Lam = 4908.75 * (1/CLHEP::second);


  // Coincidence window size
  static const double Tc = 400e-6 * CLHEP::second;

  // Oscillation formula
  static const double delta_M31_2 = 2.32e-3 * CLHEP::eV * CLHEP::eV;
  static const double delta_M21_2 = 7.59e-5 * CLHEP::eV * CLHEP::eV;

  static const double s_2_2_12 = 0.861;
}

namespace Li9Bkg
{
  // 0 - for 8MeV study and 1 for 2.2MeV study
  static const double Daily_Yield[2][3]     = { {3.1, 1.8, 0.16},
						{3.1, 1.8, 0.16} };
  
  static const double Daily_Yield_Err[2][3] = { {1.6, 1.1, 0.11},
						{1.6, 1.1, 0.11} };

  /* Selection Efficiency and muon veto efficiency */
  static const double Efficiency[2] = { 0.9 * 6.7e-3,
					0.43 * 6.7e-3 };
}

/// Others
/* Parameters to fit */
/* Static version will cause each source file has an individual copy of this. Not good for fit. */
extern double s_2_2_13;
extern double UnknownEffi;

namespace Dataset{
  enum Dataset_t { GdCap = 0, 
		   HCap  = 1 };
}

#endif // __CONSTANTS_H__  
