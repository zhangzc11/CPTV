#include "Baseline.h"
#include "Constants.h"
#include <iostream>

double Baseline( unsigned int RctNo, unsigned int AdNo)
{
  double length = ( Position::Rct[ RctNo-1 ] - Position::Ad[ AdNo-1 ]).Mag();
  return length;
}
