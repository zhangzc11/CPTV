#include "SurvProb.h"
#include "Constants.h"
#include <iostream>
#include <math.h>

using namespace CLHEP;

double SurvProb( double t13, double baseline, double Enu )
{
  double s_2_2_13 = t13;  /* sin^2(2theta13) */

  // First term
  double Pee = 1;
  
  // Second term
  double delta31 = 1.267 * (Phys::delta_M31_2/(eV*eV) * baseline/m) / (Enu/MeV) ;
  double second = - s_2_2_13 * sin( delta31 ) * sin( delta31 );

  // Third term
  double delta21 = 1.267 * (Phys::delta_M21_2/(eV*eV) * baseline/m) / (Enu/MeV) ;
  double c_1_2_13 = sqrt( 1 - s_2_2_13 );
  double c_4_1_13 = (c_1_2_13 + 1)/2 * (c_1_2_13 + 1)/2;
  
  double third = - c_4_1_13 * Phys::s_2_2_12 * sin( delta21 ) * sin( delta21 );
  
  //std::cout<<"In SurvProb "<<Pee<<" "<<second<<" "<<third<<std::endl;
  Pee = Pee + second + third;

  return Pee;
}
