#include "Baseline.h"
#include "Constants.h"
#include <iostream>

double Baseline( unsigned int RctNo, unsigned int AdNo)
{
  double length = ( Position::Rct[ RctNo ] - Position::Ad[ AdNo ]).Mag();
  return length;
}
