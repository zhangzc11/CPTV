/*
  A simple file contains all non-array constants. (length<10)
  Except in array index, all ADs and reactors count from 1.
  
  Apr. 9, 2012
  Zhe Wang
*/

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "CLHEP/Units/SystemOfUnits.h"
#include "TVector3.h"
#include "TimeStamp.h"

namespace Basic
{
  static const bool GdFit = true;
  static const bool HFit  = false;

  static const bool DailyFlux = false;
  static const bool WeeklyFulx = ! DailyFlux;

  /*
    All Ad and Reactor numbers are counted from 0.
  */
  static const unsigned int NoAd = 6;
  static const unsigned int NoRct = 6;

  // A day
  static const TimeStamp StepTime(24*60*60);
}


namespace Binning
{
  /*
    Working on EPrompt
  */
  static const double BeginEnergy = 0  * CLHEP::MeV;
  static const double EndEnergy   = 10 * CLHEP::MeV;
  /* The program requires that each bin numbers can be divided by the smaller ones exactly. */
  static const unsigned int NPreciseBin  = 1000;  // For truth, crosssection, etc.
  static const unsigned int NHistoBin = 100;      // For data specturm
  static const unsigned int NFitBin   = 1;        // For Fit
};

namespace Reactor
{
  static const char * const U238SpecFile =    "../data/FissionSpec2011/antiNeuFlux_U2382011.dat";
  static const char * const U235SpecFile =    "../data/FissionSpec2011/antiNeuFlux_U2352011.dat";
  static const char * const Pu239SpecFile =   "../data/FissionSpec2011/antiNeuFlux_Pu2392011.dat";
  static const char * const Pu241SpecFile =   "../data/FissionSpec2011/antiNeuFlux_Pu2412011.dat";

  static const char * const WeeklyAvg_CorrectedPower_P12AB = "../data/Power/WeeklyAvg_CorrectedPower_P12AB.dat";

  static const double NmlPowerBlind = 2.90e9 * CLHEP::watt;
  static const double NmlPowerUnbld = 2.85e9 * CLHEP::watt;

  static const double NmlU235Frac  = 0.64;
  static const double NmlU238Frac  = 0.08;
  static const double NmlPu239Frac = 0.25;
  static const double NmlPu241Frac = 0.03;

  static const double AveE_U235  = 201.92 * CLHEP::MeV;
  static const double AveE_U238  = 205.52 * CLHEP::MeV;
  static const double AveE_Pu239 = 209.99 * CLHEP::MeV;
  static const double AveE_Pu241 = 213.60 * CLHEP::MeV;
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

namespace DataPath
{
  static const char * const WeeklyFluxData =    "../data/Flux.20110920-20120220.txt";
  static const char * const NProtonData    =    "../data/NProton.20110920-20120220.txt";
  /* P12b Gd */
  static const char * const GdRunInfo      =    "../../data/Sample/16_P12b_AdScaled_PRL_like_cuts/Gd/RunInfo.txt";
  static const char * const GdEH1Root      =    "../../data/Sample/16_P12b_AdScaled_PRL_like_cuts/Gd/EH1.root";
  static const char * const GdEH2Root      =    "../../data/Sample/16_P12b_AdScaled_PRL_like_cuts/Gd/EH2.root";
  static const char * const GdEH3Root      =    "../../data/Sample/16_P12b_AdScaled_PRL_like_cuts/Gd/EH3.root";

  /* P12b H , Need to rerun AccSub for these */
  static const char * const HRunInfo      =    "../../data/Sample/16_P12b_AdScaled_PRL_like_cuts/Gd/RunInfo.txt";
  static const char * const HEH1Root      =    "../../data/Sample/16_P12b_AdScaled_PRL_like_cuts/Gd/EH1.root";
  static const char * const HEH2Root      =    "../../data/Sample/16_P12b_AdScaled_PRL_like_cuts/Gd/EH2.root";
  static const char * const HEH3Root      =    "../../data/Sample/16_P12b_AdScaled_PRL_like_cuts/Gd/EH3.root";

  /* P12b */
  /*
  static const char * const RunInfo        =    "../../data/Sample/16_P12b_AdScaled/FnNeutron/RunInfo.txt";
  static const char * const EH1Root        =    "../../data/Sample/16_P12b_AdScaled/FnNeutron/EH1.root";
  static const char * const EH2Root        =    "../../data/Sample/16_P12b_AdScaled/FnNeutron/EH2.root";
  static const char * const EH3Root        =    "../../data/Sample/16_P12b_AdScaled/FnNeutron/EH3.root";
  */
  /* P12b ext */
  /*
  static const char * const RunInfo        =    "../../data/Sample/17_P12b_ext_AdScaled/FnNeutron/RunInfo.txt";
  static const char * const EH1Root        =    "../../data/Sample/17_P12b_ext_AdScaled/FnNeutron/EH1.root";
  static const char * const EH2Root        =    "../../data/Sample/17_P12b_ext_AdScaled/FnNeutron/EH2.root";
  static const char * const EH3Root        =    "../../data/Sample/17_P12b_ext_AdScaled/FnNeutron/EH3.root";
  */
  /* P12b + P12b ext*/
  /*
  static const char * const RunInfo        =    "../../data/Sample/18_P12b_all/RunInfo.txt";
  static const char * const EH1Root        =    "../../data/Sample/18_P12b_all/EH1.root";
  static const char * const EH2Root        =    "../../data/Sample/18_P12b_all/EH2.root";
  static const char * const EH3Root        =    "../../data/Sample/18_P12b_all/EH3.root"; 
  */
}

namespace Eff
{
  // For Gd capture
  static const double Flasher_8_eff  = 0.9998;  /* PRL */
  static const double Spill_in_8_eff = 1.0503;  /* PRL */
  static const double Time_8_eff = 0.9857;      /* PRL */

  // For H capture
  static const double Time_22_eff = 1;     /* Todo: ... */

}

namespace Phys
{
  // Enu = Eprompt_vis + 0.792 MeV
  static const double EnuToEprompt = 0.792 * CLHEP::MeV;
  
  // GdLs, Gd H capture ratio
  static const double GdLS_Gd_Cap_Frac = 0.8383;     /* PRL */
  static const double GdLS_H_Cap_Frac  = 0.1504;

  /* All need More Study!!! */
  // Prompt Efficiency
  static const double Gd_Cap_Pmpt_eff = 0.9988;   /* PRL */
  static const double Gd_Cap_Dlyd_eff = 0.9086;   /* PRL */
  
  static const double H_Cap_Pmpt_eff  = 0.98;   /* Todo: Positron efficiency need to measured. */

  // GdLs region
  /* -------- ======== EEEEEEEE ======== -------- */
  /* Need More Study!!! */
  static const double GdLS_Distance_8_eff  = 1;
  static const double GdLS_Distance_22_eff = 0.6935 * 1.1;

  // Ls region
  static const double LowECut_eff = 0.65708;
  static const double En3sigma_eff = 0.905;
  static const double LS_Distance_22_eff = 0.7645 * 1.04;

  // GdLs Capture time constant
  static const double GdLS_Cap_Lam = 34882.6 * (1/CLHEP::second);

  // Ls Capture time constant
  static const double LS_Cap_Lam = 4908.75 * (1/CLHEP::second);


  // Coincidence window size
  static const double Tc = 200e-6 * CLHEP::second;

  // Oscillation formula
  static const double delta_M31_2 = 2.32e-3 * CLHEP::eV * CLHEP::eV;
  static const double delta_M21_2 = 7.59e-5 * CLHEP::eV * CLHEP::eV;

  static const double s_2_2_12 = 0.861;

  // Proton number correction
  static const double mH  = 1.007825;
  static const double fH1 = 0.99985;
}

namespace Li9Bkg
{
  // 0 - for 8MeV study and 1 for 2.2MeV study
  static const double Daily_Yield[2][3]     = { {3.1, 1.8, 0.16},    /* PRL */
						{3.1, 1.8, 0.16} };
  
  static const double Daily_Yield_Err[2][3] = { {1.6, 1.1, 0.11},
						{1.6, 1.1, 0.11} };

}

namespace FastNBkg
{
  /* PRL, but measured for 0.7 - 12 MeV, need to rescale to 0.7 - 10 MeV for this fit. */
  static const double DailyRateGd[6]    = { 0.84, 0.84, 0.74, 0.04, 0.04, 0.04 };
  static const double DailyRateGdErr[6] = { 0.28, 0.28, 0.44, 0.04, 0.04, 0.04 };

  static const double DailyRateH[6]     = { 0,0,0,0,0,0 };  /* Todo: Wait for J XP's input */
  static const double DailyRateHErr[6]  = { 0,0,0,0,0,0 };  /* Todo: Wait for J XP's input */
}

/// Others
/* Parameters to fit */
/* Static version will cause each source file has an individual copy of this. Not good for fit. */
extern double s_2_2_13;

namespace Uncertainty
{
  static const double RctCorrErr = 0.02;
}

namespace Dataset{
  enum Dataset_t { GdCap = 0, 
		   HCap  = 1 };
}

static const bool RepeatPRL = true;
namespace RePRL{
  static const double NCandidate[6] = {28935,  28975,  22466,  3528,   3436,   3452  };
//static const double Background[6] = {556.19, 441,    358,    145,    148,    139   };
  static const double Background[6] = {557,    557,    432,    173.7,  175.6,  165.9 };
  static const double BkgrdError[6] = {65.07,  65.07,  50.5,   10.9,   10.9,   10.9  };
    
  static const double TotalPredi[6] = {44442,  45307,  33225,  4647.4, 4657.8, 4611.9};
  static const double MuonOstwEf[6] = {0.8019, 0.7989, 0.8363, 0.9547, 0.9543, 0.9538};
  static const double OthersEffi = 0.788;
  
  static const double Deficit_13[6] = {0.148,  0.145,  0.20,   0.77,   0.77,   0.77  };

  static const double Omega_d_r[6 /*AD*/][6 /*RT*/] = 
    { { 0.417562, 0.426367, 0.038357, 0.053902, 0.030029, 0.033784 },
      { 0.420337, 0.426393, 0.037682, 0.052973, 0.029466, 0.033150 },
      { 0.041160, 0.042576, 0.190634, 0.20044 , 0.235894, 0.289297 },
      { 0.140358, 0.154889, 0.125564, 0.143849, 0.215749, 0.219591 },
      { 0.140904, 0.155538, 0.12549 , 0.143828, 0.215173, 0.219068 },
      { 0.140465, 0.155011, 0.125454, 0.143706, 0.215798, 0.219566 } };

}

#endif // __CONSTANTS_H__  
