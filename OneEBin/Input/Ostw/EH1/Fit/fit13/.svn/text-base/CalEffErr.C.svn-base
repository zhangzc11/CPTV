#include <iostream>
using namespace std;
//
// Not right! Energy cut efficiency uncertainty are all correlated.
// 
void CalEff()
{
  /* These are all average values, [kg] */
  double GdLSMass = 19950;
  double LSMass = 21600;  
  double AcMass = 2403;   
  
  /* Proton (H) density, [N/kg] */
  double GdLSPD = 7.169e25;
  double LSPD = 7.116e25;
  double AcPD = 4.78e25;
  
  /* P12E result */
  /* 0 - GdLS region, 1 - LS region; then 0 uncorrelated, 1 correlated */
  double Ee[2]={ 0.8864, 0.6330 }, Eee[2][2] = { {0.0098, 0.0045},{0.0073, 0.0032} };
  double Eo[2]={ 0.0391, 0.0008 }, Eoe[2][2] = { {0.0047, 0.0002},{0.0001, 0.0001} };
  double Et[2]={ 0.9889, 0.8466 }, Ete[2][2] = { {0,0},           {0.0075, 0.0014} };
  
  /* Before distance eff */
  double EGd, EGde[2];
  EGd = (Ee[0]+Eo[0])*Et[0];
  
  EGde[0] = sqrt( (Eee[0][0]*Eee[0][0]+Eoe[0][0]*Eoe[0][0])/((Ee[0]+Eo[0])*(Ee[0]+Eo[0])) + (Ete[0][0]*Ete[0][0])/(Et[0]*Et[0]) )*EGd;
  
  EGde[1] = sqrt( (Eee[0][1]*Eee[0][1]+Eoe[0][1]*Eoe[0][1])/((Ee[0]+Eo[0])*(Ee[0]+Eo[0])) + (Ete[0][1]*Ete[0][1])/(Et[0]*Et[0]) )*EGd;

  double ELS, ELSe[2];
  ELS = (Ee[1]+Eo[1])*Et[1];
  
  ELSe[0] = sqrt( (Eee[1][0]*Eee[1][0]+Eoe[1][0]*Eoe[1][0])/((Ee[1]+Eo[1])*(Ee[1]+Eo[1])) + (Ete[1][0]*Ete[1][0])/(Et[1]*Et[1]) )*ELS;

  ELSe[1] = sqrt( (Eee[1][1]*Eee[1][1]+Eoe[1][1]*Eoe[1][1])/((Ee[1]+Eo[1])*(Ee[1]+Eo[1])) + (Ete[1][1]*Ete[1][1])/(Et[1]*Et[1]) )*ELS;

  double Ea=0.0288, Eae[2] = { 0.0013,0 };

  cout<<"Gd region:   "<<EGd<<" +- "<<EGde[0]<<" +- "<<EGde[1]<<endl;
  cout<<"GdLS region: "<<ELS<<" +- "<<ELSe[0]<<" +- "<<ELSe[1]<<endl;
  cout<<"Ac region:   "<<Ea<<" +- "<<Eae[0]<<" +- "<<Eae[1]<<endl;
  
  /* Distance */
  double Ed=0.7527, Ede[2] = { 0.0035, 0.0030 };

  double N, Ne[2];
  
  N = ((GdLSMass * GdLSPD * EGd) + (LSMass * LSPD * ELS) + (AcMass * AcPD * Ea)) * Ed;
  
  Ne[0] = 
    sqrt (
	  ( pow((GdLSMass * GdLSPD * EGde[0]), 2) 
	    + pow((LSMass * LSPD * ELSe[0]), 2)
	    + pow((AcMass * AcPD * Eae[0]), 2) ) 
	  / 
	  ( ((GdLSMass * GdLSPD * EGd) + (LSMass * LSPD * ELS) + (AcMass * AcPD * Ea)) 
	    *((GdLSMass * GdLSPD * EGd) + (LSMass * LSPD * ELS) + (AcMass * AcPD * Ea)) )
	  
	  + (Ede[0]*Ede[0])/(Ed*Ed)
	  ) 
    * N;

  Ne[1] =
    sqrt (
	  ( pow((GdLSMass * GdLSPD * EGde[1]), 2)
	    + pow((LSMass * LSPD * ELSe[1]), 2)
	    + pow((AcMass * AcPD * Eae[1]), 2) )
	  /
	  ( ((GdLSMass * GdLSPD * EGd) + (LSMass * LSPD * ELS) + (AcMass * AcPD * Ea))
	    *((GdLSMass * GdLSPD * EGd) + (LSMass * LSPD * ELS) + (AcMass * AcPD * Ea)) )
	  
	  + (Ede[1]*Ede[1])/(Ed*Ed)
	  ) 
    * N;
  
  cout<<"N: "<<N<<" +- "<<Ne[0]<<" +- "<<Ne[1]<<endl;

  cout<<"Relative errors: "<<endl;
  cout<<"Gd region:   "<<EGd/EGd<<" +- "<<EGde[0]/EGd<<" +- "<<EGde[1]/EGd<<endl;
  cout<<"GdLS region: "<<ELS/ELS<<" +- "<<ELSe[0]/ELS<<" +- "<<ELSe[1]/ELS<<endl;
  cout<<"Ac region:   "<<Ea/Ea<<" +- "<<Eae[0]/Ea<<" +- "<<Eae[1]/Ea<<endl;
  cout<<"N: "<<N/N<<" +- "<<Ne[0]/N<<" +- "<<Ne[1]/N<<endl;
  
}

