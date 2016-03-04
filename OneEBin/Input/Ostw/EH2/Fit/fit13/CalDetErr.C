#include <iostream>
using namespace std;

void CalDetErr()
{
  /* These are all average values, [kg] */
  /* GdLS, LS, Acrylic */
  double Mass[3] = {19950, 21600, 2768};
  double Emc     = 0.0047;
  double Emu[3]  = {0.0003, 0.0013, 0.005};
  
  /* Proton (H) density, [N/kg] */
  double PD[3] = {7.169e25, 7.116e25, 4.78e25};
  
  /* H capture fraction */
  double Frac[3] = {0.1563, 0.9563, 0.7820};

  /* P12E result */
  /* Ee+Eo */ /* 0,1,2 GdLS, LS, Acrylic */
  double EE[3]     = {0.8864+0.0391, 0.6330+0.0008, 0.0391};
  /* Error */ /* 0,1 Cor. Uncor. */
  double EEe[2]    = {0.011, 0.0051};

  /* Lifetime */
  double Et[3]     = {0.9889, 0.8466, 0.8740};
  double Ete[2]    = {0.0075, 0.0014};

  /* Distance */
  double Ed=0.7527;
  double Ede[2] = { 0.0046, 0.0040 };

  double A = 0;
  for( int i=0; i<3; i++ ) {
    A += Mass[i]*PD[i]*Frac[i]*EE[i]*Et[i]*Ed;
  }

  double e1 = A*sqrt(EEe[1]**2+Ete[1]**2+Ede[1]**2);

  double e2 = 0;
  for( int i=0; i<3; i++ ) {
    e2 += pow(Mass[i]*PD[i]*Frac[i]*EE[i]*Et[i]*Ed*Emu[i] , 2);
  }
  e2 = sqrt(e2);

  cout<< A  <<endl;
  cout<< e1 <<endl;
  cout<< e2 <<endl;

  cout<< sqrt(e1**2+e2**2)/A <<endl;

  cout<<"Eff = "<< A/(Mass[0]*PD[0]*Frac[0]+Mass[1]*PD[1]*Frac[1]+Mass[2]*PD[2]*Frac[2]) <<endl;
}

