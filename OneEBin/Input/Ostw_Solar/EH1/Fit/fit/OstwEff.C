///
/// Calculate the rate of a searching window starting with a single event
/// assuming the window width T and the single's rate Rs.
///
/// See my note book for March 25, 2012 and April 04, 2012
///
/// Rs  -- Singles rate
/// Rmu -- Muon rate
/// Tc  -- Length of coincident window
/// Eff_e  -- Efficiency to detect a positron
/// Eff_en -- Conditional efficiency to detect a neutron after finding a positron  
///
#include <iostream>
#include <math.h>

double PStart(double Rs, double Rmu, double Tc)
{
  /// Case a
  double Pa = Rmu / ( Rs + Rmu ) * ( 1 - exp( -(Rs + Rmu) * Tc ) );
  
  /// Case b
  double Pb = exp( -Rs * Tc ) * exp( -Rmu * Tc );

  /// Case c+d
  double Pcd = 
      Rs*exp(-Rmu*Tc)*1/(Rs+Rmu)*(1-exp(-(Rs+Rmu)*Tc))
    - Rs*exp(-Rmu*Tc)*1/(2*Rs+Rmu)*(1-exp(-(2*Rs+Rmu)*Tc));

  double Ptot = Pa + Pb + Pcd;

  return Ptot;
}

double PNStart(double Rs, double Rmu, double Tc, double Eff_n, double Eff_ne, int Type, double Lambda_1, double a )
{
  if (Type==1){
      /// Case a
      double Pna = Eff_n * Rmu * ( (1- Eff_ne) / ( Rmu + Rs ) *( 1 - exp( -( Rmu + Rs) *Tc)) + Eff_ne / ( Rs + Rmu + Lambda_1) *( 1 - exp( -(Rmu + Rs + Lambda_1 ) * Tc)) );
      
      /// Case b
      double Pnb = Eff_n * exp( - (Rmu + Rs) * Tc ) * ( 1 - Eff_ne + Eff_ne * exp(-Lambda_1 * Tc)) ;
      
      /// Case c
      double Pnc = Eff_n * Eff_ne * Rmu * Rs / (Lambda_1 + Rs) / ( Lambda_1 + Rmu) * (exp( -Rmu * Tc) - exp( -2* Rmu * Tc - Lambda_1 * Tc)) -  Eff_n * Eff_ne * Rmu * Rs  / (Lambda_1 + Rs) / (Lambda_1 * 2 + Rs + Rmu) * ( exp(-Rmu * Tc) - exp( -(Lambda_1 * 2 + Rs + Rmu) * Tc)) - Eff_n * Eff_ne * exp(-Lambda_1 * Tc) * (exp( -Rmu * Tc) - exp( -2* Rmu * Tc) ) + Eff_n * Eff_ne * Rmu * exp(-Lambda_1 * Tc ) / ( Rmu + Rs ) * ( exp( -Rmu * Tc) - exp( - ( 2* Rmu + Rs) * Tc) ) ;
      /// Case d
      double Pnd = Eff_n * Eff_ne /2 * exp(-2* Rmu * Tc) * ( ( 1 - exp( -Lambda_1 * Tc) ) - Lambda_1 / (Lambda_1 + 2 * Rs) * ( 1 - exp( - ( Lambda_1 + 2 * Rs) * Tc) ) );
      
      double Pntot = Pna + Pnb + Pnc + Pnd;
      
      return Pntot;
  }
}

double TimeEff(double t, int Type, double Lambda_1, double a )
{
  if (Type == 1) {  
    double TimeEff = 1 - exp( -Lambda_1 * t);
    return TimeEff;
  }
  if (Type == 2) {  
    double Lambda_2 = 20;
    double TimeEff = 1 - ( 1 + a) * exp( -Lambda_1 * t) + a * exp( -Lambda_2 * t);      
    return TimeEff;
  }
}

double RSStart(double Rs, double Rmu, double Tc)
{
  double RSStart = Rs * PStart( Rs, Rmu, Tc);
  return RSStart;
}

double RNStart(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double a)
{
  double RNStart = RIBD * PNStart( Rs, Rmu, Tc, Eff_n, Eff_ne, Type, Lambda_1, a);
  return RNStart;
}

double REStart(double Rs, double Rmu, double Tc, double RIBD, double Eff_e)
{
  double REStart = RIBD * Eff_e * PStart( Rs, Rmu, Tc);
  return REStart;
}

double RSS(double Rs, double Rmu, double Tc)
{
  double RSS = RSStart( Rs, Rmu, Tc) * ( Rs*Tc *exp(-Rs*Tc) );
  return RSS;
}

double REN(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double a )
{
  double REN = REStart( Rs, Rmu, Tc, RIBD, Eff_e) * Eff_en * TimeEff( Tc, Type, Lambda_1, a );
  return REN;
}


double RS(double Rs, double Rmu, double Tc)
{
  double RS = RSStart( Rs, Rmu, Tc) *  exp( -Rs * Tc ) ;
  return RS;
}

double RE(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double a )
{
  double RE = REStart( Rs, Rmu, Tc, RIBD, Eff_e) * exp( -Rs*Tc ) *(1-Eff_en * TimeEff(Tc,Type,Lambda_1,a));
  return RE;
}
double RN(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double a )
{
  double RN = RNStart( Rs, Rmu, Tc, RIBD, Eff_n, Eff_ne, Type,Lambda_1, a) *  exp( -Rs*Tc ) ;
  return RN;
}

double P_S_E(double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double a)
{
  if (Type==1){ 
    double P_S_E = Eff_e * ( 1 - Eff_en) * (1 - exp(- RIBD * Tc)) +  Eff_e * Eff_en * RIBD / ( Lambda_1 - RIBD) * ( exp(-RIBD * Tc) - exp( -Lambda_1 * Tc) );
    return P_S_E;
  }
  /*  if Type==2{ 
      double P_S_E =RIBD * Eff_e (Tc - Eff_en(T-(1+a) / Lambda_1 * (1 - exp(-Lambda_1 * Tc)) + a / Lambda_2 * ( 1 - exp( -Lambda_2 * Tc)) )) ;
      }	*/

}

double RSE(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double a )
{
	 
  double RSE = RSStart( Rs, Rmu, Tc) * P_S_E(Tc, RIBD, Eff_e,  Eff_en, Type, Lambda_1, a) *  exp( -Rs*Tc );
  return RSE;
}

double RES(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double a )
{
  double RES = REStart( Rs, Rmu, Tc, RIBD, Eff_e) * ( Rs*Tc * exp( -Rs*Tc ) ) *(1-Eff_en * TimeEff(Tc,Type,Lambda_1,a));
  return RES;
}

double RNS(double Rs, double Rmu, double Tc, double RIBD, double Eff_n, double Eff_ne, int Type, double Lambda_1, double a )
{
  double RNS = RNStart( Rs, Rmu, Tc, RIBD, Eff_n, Eff_ne, Type,Lambda_1,a ) *  (Rs*Tc *exp( -Rs*Tc )) ;
  return RNS;
}

double P_S_EN( double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double a )
{  
    if (Type==1){ 
    double P_S_EN = Eff_e * Eff_en * ( 1 - exp(-RIBD * Tc )- RIBD / (Lambda_1 + RIBD) * ( exp( -RIBD * Tc ) - exp( -Lambda_1 * Tc)) ) ;
   return P_S_EN;
    }
  /* if (Type==2){ 
     double P_S_EN =RIBD * Eff_e * Eff_en * (T-(1+a) / Lambda_1 * (1 - exp(-Lambda_1 * Tc)) + a / Lambda_2 * ( 1 - exp( -Lambda_2 * Tc)) ) ;
   return P_S_EN;
     }	*/ 
}

double RSEN(double Rs, double Rmu, double Tc, double RIBD, double Eff_e, double Eff_en, int Type, double Lambda_1, double a)
{
  
  double RSEN = RSStart( Rs, Rmu, Tc) *  P_S_EN(Tc, RIBD, Eff_e,  Eff_en, Type, Lambda_1, a) *  exp( -Rs*Tc );
  return RSEN;
}

