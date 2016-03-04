#ifndef __OSTWEFF_H__
#define __OSTWEFF_H__

double PStart(double Rs, double Rmu, double Tc);
double PNStart(double Rs, double Rmu, double Tc, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );

double TimeEff(double t, int Type, double Lambda_1, double Lambda_2, double a );

double RSStart(double Rs, double Rmu, double Tc);
double RNStart(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a);
double REStart(double Rs, double Rmu, double Tc, double RIBD, double Eff_e);

double RSS(double Rs, double Rmu, double Tc);
double RSS_DYB(double Rs, double Rmu, double Tc);
double REN(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double EffEN_DYB(double Rs, double Rmu, double Tc);

double RS(double Rs, double Rmu, double Tc);
double RE(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double RN(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );

double P_S_E(double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a);
double RSE(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double RES(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );

double RNS(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );

double P_S_EN( double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );

double RSEN(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a);
double RSSS(double Rs, double Rmu, double Tc);
double RESS(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double RNSS(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );
double RS_E_S(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );
double RS_N_S(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double Lambda_2, double a );
double RE_N_S(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double Lambda_2, double a );

#endif // __OSTWEFF_H__
