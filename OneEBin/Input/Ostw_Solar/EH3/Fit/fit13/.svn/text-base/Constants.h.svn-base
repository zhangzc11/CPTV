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
#include <string>

namespace Basic
{
  static const bool GdFit = false;
  static const bool HFit  = true;

  static const bool WeeklyFulx = true;
  static const bool DailyFlux = ! WeeklyFulx;

  /*
    All Ad and Reactor numbers are counted from 0.
  */
  static const unsigned int NoAd = 6;
  static const unsigned int NoRct = 6;

  // A day
  static const TimeStamp StepTime(24*60*60);
  
  /* P12b */
  //static const TimeStamp BeginTime(2011,12,24,0,0,0);
  //static const TimeStamp EndTime  (2012,02,15,2,0,0);
  /* P12b-all */
  //static const TimeStamp BeginTime(2011,12,24,0,0,0);
  //static const TimeStamp EndTime  (2012,05,07,9,0,0);
  /* P12e */
  static const TimeStamp BeginTime(2011,12,24,0,0,0);
  static const TimeStamp EndTime  (2012, 8,01,0,0,0);

  /* Scan */
  //static const TimeStamp BeginTime(2011,12,24,0,0,0);
  //static const TimeStamp EndTime  (2012,01,15,0,0,0);
}


namespace Binning
{
  /*
    Working on EPrompt
  */
  static const double BeginEnergy = 0  * CLHEP::MeV;
  static const double EndEnergy   = 12 * CLHEP::MeV;
  /* The program requires that each bin numbers can be divided by the smaller ones exactly. */
  static const unsigned int NPreciseBin  = 1200;  // For truth, crosssection, etc.
  static const unsigned int NHistoBin = 120;      // For data specturm
  static const unsigned int NFitBin   = 1;        // For Fit

  /* Candidate integral range due to limited flux prediction */
  static const double BgnStudyEnergy = 0  * CLHEP::MeV;
  static const double EndStudyEnergy = 12 * CLHEP::MeV;
  static const unsigned int BgnBin  = 1;
  static const unsigned int EndBin  = 120;
};

namespace Reactor
{
  static const bool DBFlux = true;

  // WW's flux
  static const char * const U238SpecFile =    "../data/FissionSpec2011/antiNeuFlux_U2382011.dat";
  static const char * const U235SpecFile =    "../data/FissionSpec2011/antiNeuFlux_U2352011.dat";
  static const char * const Pu239SpecFile =   "../data/FissionSpec2011/antiNeuFlux_Pu2392011.dat";
  static const char * const Pu241SpecFile =   "../data/FissionSpec2011/antiNeuFlux_Pu2412011.dat";

  static const char * const WeeklyFluxDataFile = "../data/Power/WeeklyAvg_CorrectedPower_20111224-20120511.dat";

  // Flux in database
  //static const char * const DBWeeklyFluxDataFile = "../data/Flux.20110920-20120220.txt";
  //static const char * const DBWeeklyFluxDataFile = "../data/Flux.20110920-20120601.txt";
  static const char * const DBWeeklyFluxDataFile = "../data/Flux_2011-09-20_2012-07-27_unblind_ZL.txt";

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
  static const char * const NProtonData    =    "../data/NProton.20110920-20120220.txt";

  /* P12e Gd */
  /* 6-10 MeV */
  /*
  static const char * const GdRunInfo      =    "../../data/Sample/P12e_1.5MeV/Gd/RunInfo.txt";
  static const char * const GdEH1Root      =    "../../data/Sample/P12e_1.5MeV/Gd/EH1.root";
  static const char * const GdEH2Root      =    "../../data/Sample/P12e_1.5MeV/Gd/EH2.root";
  static const char * const GdEH3Root      =    "../../data/Sample/P12e_1.5MeV/Gd/EH3.root";
  */
  /* 6-12 MeV */
  static const char * const GdRunInfo      =    "../../../../AccSubOutput/P12e_1.5MeV/Gd/Normal_Scaled/RunInfo.txt";
  static const char * const GdEH1Root      =    "../../../../AccSubOutput/P12e_1.5MeV/Gd/Normal_Scaled/EH1.root";   
  static const char * const GdEH2Root      =    "../../../../AccSubOutput/P12e_1.5MeV/Gd/Normal_Scaled/EH2.root";   
  static const char * const GdEH3Root      =    "../../../../AccSubOutput/P12e_1.5MeV/Gd/Normal_Scaled/EH3.root";   
  
  /* P12e H */
  /*
  static const char * const HRunInfo      =     "../../data/Sample/P12e_1.5MeV/H/RunInfo.txt";
  static const char * const HEH1Root      =     "../../data/Sample/P12e_1.5MeV/H/EH1.root";
  static const char * const HEH2Root      =     "../../data/Sample/P12e_1.5MeV/H/EH2.root";
  static const char * const HEH3Root      =     "../../data/Sample/P12e_1.5MeV/H/EH3.root";
  */
  
  static const char * const HRunInfo      =     "../../../../AccSubOutput/P12e_1.5MeV_NoScaling_Sep24/H/Normal/RunInfo.txt";
  static const char * const HEH1Root      =     "../../../../AccSubOutput/P12e_1.5MeV_NoScaling_Sep24/H/Normal/EH1.root";   
  static const char * const HEH2Root      =     "../../../../AccSubOutput/P12e_1.5MeV_NoScaling_Sep24/H/Normal/EH2.root";   
  static const char * const HEH3Root      =     "../../../../AccSubOutput/P12e_1.5MeV_NoScaling_Sep24/H/Normal/EH3.root";   
  
   /* P12b Gd */
  //static const char * const GdRunInfo      =    "../../data/Sample/P12b/Gd/RunInfo.txt";
  //static const char * const GdEH1Root      =    "../../data/Sample/P12b/Gd/EH1.root";
  //static const char * const GdEH2Root      =    "../../data/Sample/P12b/Gd/EH2.root";
  //static const char * const GdEH3Root      =    "../../data/Sample/P12b/Gd/EH3.root";
    
  // /* P12b H */
  //static const char * const HRunInfo      =     "../../data/Sample/P12b/H/RunInfo.txt";
  //static const char * const HEH1Root      =     "../../data/Sample/P12b/H/EH1.root";	  
  //static const char * const HEH2Root      =     "../../data/Sample/P12b/H/EH2.root";	  
  //static const char * const HEH3Root      =     "../../data/Sample/P12b/H/EH3.root";   
  

  /* P12b ext Gd */
  //static const char * const GdRunInfo      =    "../../data/Sample/P12b-ext/Gd/RunInfo.txt";
  //static const char * const GdEH1Root      =    "../../data/Sample/P12b-ext/Gd/EH1.root";
  //static const char * const GdEH2Root      =    "../../data/Sample/P12b-ext/Gd/EH2.root";
  //static const char * const GdEH3Root      =    "../../data/Sample/P12b-ext/Gd/EH3.root";
    
  //    /* P12b ext H */
  //static const char * const HRunInfo      =     "../../data/Sample/P12b-ext/H/RunInfo.txt";
  //static const char * const HEH1Root      =     "../../data/Sample/P12b-ext/H/EH1.root";
  //static const char * const HEH2Root      =     "../../data/Sample/P12b-ext/H/EH2.root";
  //static const char * const HEH3Root      =     "../../data/Sample/P12b-ext/H/EH3.root";

  /* P12b all Gd */
  //static const char * const GdRunInfo      =    "../../data/Sample/P12b-all/Gd/RunInfo.txt";
  //static const char * const GdEH1Root      =    "../../data/Sample/P12b-all/Gd/EH1.root";
  //static const char * const GdEH2Root      =    "../../data/Sample/P12b-all/Gd/EH2.root";
  //static const char * const GdEH3Root      =    "../../data/Sample/P12b-all/Gd/EH3.root";
    
  //    /* P12b all H */
  //static const char * const HRunInfo      =     "../../data/Sample/P12b-all/H/RunInfo.txt";
  //static const char * const HEH1Root      =     "../../data/Sample/P12b-all/H/EH1.root";
  //static const char * const HEH2Root      =     "../../data/Sample/P12b-all/H/EH2.root";
  //static const char * const HEH3Root      =     "../../data/Sample/P12b-all/H/EH3.root";
  
  /* Test area */
  /* P12b ext Gd */
  //static const char * const GdRunInfo      =    "/work/dayabay_work/wangzhe/AccSubOutput/P12b/Gd/RunInfo.txt";
  //static const char * const GdEH1Root      =    "/work/dayabay_work/wangzhe/AccSubOutput/P12b/Gd/EH1.root";
  //static const char * const GdEH2Root      =    "/work/dayabay_work/wangzhe/AccSubOutput/P12b/Gd/EH2.root";
  //static const char * const GdEH3Root      =    "/work/dayabay_work/wangzhe/AccSubOutput/P12b/Gd/EH3.root";
      
  // /* P12b ext H */
  //static const char * const HRunInfo      =     "../../data/Sample/P12e/H/RunInfo.txt";
  //static const char * const HEH1Root      =     "../../data/Sample/P12e/H/EH1.root";
  //static const char * const HEH2Root      =     "../../data/Sample/P12e/H/EH2.root";
  //static const char * const HEH3Root      =     "../../data/Sample/P12e/H/EH3.root";
  //static const char * const HRunInfo      =     "../../data/Sample/P12b-all_1.5MeV/H/RunInfo.txt";
  //static const char * const HEH1Root      =     "../../data/Sample/P12b-all_1.5MeV/H/EH1.root";
  //static const char * const HEH2Root      =     "../../data/Sample/P12b-all_1.5MeV/H/EH2.root";
  //static const char * const HEH3Root      =     "../../data/Sample/P12b-all_1.5MeV/H/EH3.root";

}

namespace Eff
{
  // For Gd capture
  static const double Flasher_8_eff  = 0.9998;  /* PRL */
  static const double Spill_in_8_eff = 1.0503;  /* PRL */
  static const double Time_8_eff = 0.9857;      /* PRL */

  static const double EffUncer[2] = { 0.002, 0.0065 }; /* Relative */

  static const double Eff15NoOsci = 0.96928;
  static const double Eff15[6][6] = {  /* [AD,RCT] */
    {0.969659,0.969677,0.970589,0.970514,0.969981,0.970238},
    {0.969651,0.969671,0.970589,0.970514,0.969979,0.970236},
    {0.970048,0.969967,0.969871,0.969917,0.970061,0.969938},
    {0.967709,0.967797,0.969305,0.969303,0.969228,0.969339},
    {0.967716,0.967805,0.969298,0.969297,0.969214,0.969326},
    {0.96769 ,0.967777,0.969281,0.969279,0.969207,0.969318}
  };

  static const double BestEpsilon[2] = { 2.37301e-02, 1.12219e-02 };  /* best scale factor from combined fits, i.e. epsilon */
}


namespace Phys
{
  // Enu = Eprompt_vis + 0.792 MeV
  static const double EnuToEprompt = 0.792 * CLHEP::MeV;
  
  // Prompt Efficiency
  static const double Gd_Cap_Pmpt_eff = 0.9988;   /* PRL */
  static const double Gd_Cap_Dlyd_eff = 0.9086;   /* PRL */

  // GdLs region
  /* -------- ======== EEEEEEEE ======== -------- */
  // GdLS, Gd H capture ratio
  static const double GdLS_Gd_Cap_Frac  = 0.8383;     /* PRL */
  static const double GdLS_Gd_Cap_D_eff = 1;

  //static const double GdLS_H_Cap_Frac  = 0.1563;      /* Beizhen */
  static const double GdLS_H_Cap_Frac  = 0.1502;
  static const double GdLS_H_Cap_E_Eff = 0.8864 + 0.0391;
  static const double GdLS_H_Cap_T_Eff = 0.9889;

  // Ls region
  /* -------- ======== EEEEEEEE ======== -------- */
  static const double LS_H_Cap_Frac    = 0.9580;
  static const double LS_H_Cap_E_Eff   = 0.6330 + 0.0008;
  static const double LS_H_Cap_T_Eff   = 0.8403;

  // common
  static const double H_Cap_D_eff   = 0.7527;
  
  // GdLs Capture time constant
  static const double GdLS_Cap_Lam = 34882.6 * (1/CLHEP::second);

  // Ls Capture time constant
  static const double LS_Cap_Lam = 4601.0 * (1/CLHEP::second);


  // Acrylic
  static const double AcMass = 2403 * CLHEP::kg;
  static const double AcPD = 4.78e25 * (1/CLHEP::kg);
  static const double Acry_H_Cap_Eff   = 0.0288;

  // Errors (rel.) The first three is the relative errors of (Ee+Eo)*Et
  static const double Hpred3mE = 0.0117;
  static const double Hpred4mE = 0.0141;
  static const double HpredAcE = 0.0451;
  static const double H_Cap_D_effE  = 0.0046;

  // Coincidence window size
  static const double Tc[2] = { 200e-6 * CLHEP::second,
				400e-6 * CLHEP::second };

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
  // PRL
  //static const double Daily_Yield[2][3]     = { {3.1, 1.8, 0.16},
  // CPC
  //static const double Daily_Yield[2][3]     = { {2.9, 2.0, 0.22},
  // Shape
  //static const double Daily_Yield[2][3]     = { {2.4, 1.2, 0.22},
  static const double Daily_Yield[2][3]     = { {3.0, 2.0, 0.18 },
						{5.81, 3.57, 0.54} };

  // PRL
  //static const double Daily_Yield_Err[2][3] = { {1.6, 1.1, 0.11},
  // CPC
  static const double Daily_Yield_Err[2][3] = { {1.5, 1.0, 0.09},
						{1.39, 1.13, 0.12} };  
}

namespace AmCBkg
{
  // 0 - for 8MeV study and 1 for 2.2MeV study
  // PRL
  static const double Daily_Yield[2][3]     = { {0.20, 0.20, 0.20},   
                                                {0.09, 0.09, 0.06} };
  //{3.1, 1.8, 0.16} };

  static const double Daily_Yield_Err[2][3] = { {0.20, 0.20, 0.20},
                                                {0.03, 0.03, 0.02} };  /* 50% */
  //{0.42, 0.81, 0.06} };  /* note */
  //{1.6, 1.1, 0.11} };
}

namespace FastNBkg
{
  /* PRL, but measured for 0.7 - 12 MeV, need to rescale to 0.7 - 10 MeV for this fit. */
  /* 0 for Gd and 1 for H */
  // PRL
  //static const double DailyRate[2][6]    = {{ 0.84, 0.84, 0.74, 0.04, 0.04, 0.04 },
  // CPC
  static const double DailyRate[2][6]    = {{ 0.77, 0.77, 0.58, 0.05, 0.05, 0.05 },
					    { 2.09, 2.09, 1.37, 0.10 ,0.10, 0.10 } };

  // PRL
  //static const double DailyRateErr[2][6] = {{ 0.28, 0.28, 0.44, 0.04, 0.04, 0.04 },
  // CPC
  static const double DailyRateErr[2][6] = {{ 0.39, 0.39, 0.29, 0.03, 0.03, 0.03 }, 
					    { 0.27, 0.27, 0.29, 0.04, 0.04, 0.04 } };
}

/// Others
/* Parameters to fit */
/* Static version will cause each source file has an individual copy of this. Not good for fit. */
extern double s_2_2_13;
extern double Epsilon_r[ Basic::NoRct ];

namespace Uncertainty
{
  static const double RctCorrErr = 0.02;
}

namespace Dataset{
  enum Dataset_t { GdCap = 0, 
		   HCap  = 1 };
  static std::string Name[2] = { "GdCap", "HCap" };
}

static const bool RepeatPRL = false;
static const bool UsePRLFlux = false;
namespace RePRL{
  static const double LiveTime [6] = {40.8112, 40.6421, 42.4581, 48.0685, 48.067, 48.0518 };

  static const double NCandidate[6] = {28935,  28975,  22466,  3528,   3436,   3452  };

  static const double IbdRate  [6] = {714.17, 717.86, 532.29, 71.78, 69.80, 70.39  };
  static const double EIbdRate [6] = {4.58,   4.60,   3.82,   1.29,  1.28,  1.28   };
  
  //static const double Background[6] = {556.19, 441,    358,    145,    148,    139   };
  static const double Accidental[6] = {9.82,   9.88,   7.67,   3.29,   3.33,   3.12  };
  static const double Background[6] = {556.3,  556.4,  432.2,  173.7,  175.6,  165.8 };
  static const double BkgrdError[6] = {65.07,  65.30,  51.8,   10.9,   10.9,   10.4  };
    
  static const double TotalPredi[6] = {28083, 28522, 21895, 3496.3, 3502.6, 3466.3}; /* DocDB 7610 */
  //static const double TotalPredi[6] = { 28647, 29096, 22335, 3566.5, 3573, 3535.9 }; /* PRL with best pull parameters*/
  //static const double TotalPredi[6] = {28024.4, 28455.5, 21858.2, 3533.75, 3535.85, 3502.81}; /* Chao's number PRL */
  //static const double TotalPredi[6] = {67131.1, 68091.4, 64853.1, 9816.11, 9827.25, 9729}; /* Chao's number CPC */

  static const double MuonOstwEf[6] = {0.8019, 0.7989, 0.8363, 0.9547, 0.9543, 0.9538};
  static const double OthersEffi = 0.788;
  
  // DocDb 7610 Table 10
  // static const double Deficit_13[6] = {0.148,  0.145,  0.20,   0.77,   0.77,   0.77  };
  // My calcution according to DocDB 7610 8 and 9
  static const double Deficit_13[6] = { 0.148022, 0.145422, 0.198063, 0.771456, 0.772082, 0.772646 };

  static const double Omega_d_r[6 /*AD*/][6 /*RT*/] = 
    { { 0.417562, 0.426367, 0.038357, 0.053902, 0.030029, 0.033784 },
      { 0.420337, 0.426393, 0.037682, 0.052973, 0.029466, 0.033150 },
      { 0.041160, 0.042576, 0.190634, 0.20044 , 0.235894, 0.289297 },
      { 0.140358, 0.154889, 0.125564, 0.143849, 0.215749, 0.219591 },
      { 0.140904, 0.155538, 0.12549 , 0.143828, 0.215173, 0.219068 },
      { 0.140465, 0.155011, 0.125454, 0.143706, 0.215798, 0.219566 } };

  static const double Delta_d_r[6 /*AD*/][6 /*RT*/] =
    { { 0.082625, 0.085519, 0.415679, 0.352319, 0.683062, 0.639695 },
      {	0.080693, 0.084050, 0.415596, 0.352140, 0.683346, 0.639996 },
      { 0.676348, 0.682713, 0.133883, 0.144174, 0.183527, 0.150169 },
      { 0.812616, 0.811365, 0.756031, 0.752377, 0.758721, 0.750827 },
      { 0.812625, 0.811305, 0.756570, 0.752820, 0.759727, 0.751819 },
      { 0.812577, 0.811492, 0.757804, 0.754208, 0.760193, 0.752464 } };

}

namespace ReCPC{
  static const double IbdRate  [6] = {662.47, 670.87, 613.53, 77.57, 76.62, 74.97};
  static const double EIbdRate [6] = {3.00,   3.01,   2.69,   0.85,  0.85,  0.84 };
}

namespace ShapePaper{
  static const double IbdRate  [6] = {653.30, 664.15, 581.97, 73.31, 73.03, 72.20};
  static const double EIbdRate [6] = {2.31,   2.33,   2.07,   0.66,  0.66,  0.66 };
}

namespace AccBkg{
  static const double ScaleE[3] = { 0.0018, 0.0016, 0.0005 };
}

namespace Un3sigma{
  static const double frac[6] = { 0, 0, 0, 0.0033, 0.0033, 0.0033 };
}

#endif // __CONSTANTS_H__  
