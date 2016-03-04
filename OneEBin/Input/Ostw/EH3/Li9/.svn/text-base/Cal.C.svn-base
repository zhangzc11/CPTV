#include <iostream>
using namespace std;

void Cal()
{
  /* 0, Gd; 1, H */
  double N[2][3]  = { 
    { 390.8, 159.3, 38.35 },
    { 357.4, 136.6, 58.08 } };

  double dN[2][3] = { 
    { 119.4, 70.9,  14.24 },
    { 77.6,  43.1,  10.30 } };

  double R500[2][3] = {
    { 0.62, 0.10, 0.044 },
    { 0, 0, 0 } };

  double err = 0.5;

  double Eff[2] = { 0.71*0.91*0.96*0.993*0.83,
		    0.661*0.7*0.8843*0.75*0.83 };

  double LT[2][3] = {
    { 158*2,    162.96, 186.87*3 },
    { 151.77*2, 158.13, 186.28*3 } };

  cout.precision(2);
  cout<<fixed;
  for( int set=0; set<=1; set++ )  {
    for( int hal=0; hal<=2; hal++ )  {
      if( set==0 ) {
	cout<< (N[set][hal])/Eff[set]/LT[set][hal]+R500[set][hal]
	    << "$\\pm$"
	    << (dN[set][hal])/Eff[set]/LT[set][hal]+R500[set][hal]*0.5
	    << "\t&";
      } else {
	double R  =  N[1][hal]/Eff[1]/LT[1][hal];
	double dR = dN[1][hal]/Eff[1]/LT[1][hal];

	double corr  = (R500[0][hal]+N[0][hal]/Eff[0]/LT[0][hal])
          /(N[0][hal]/Eff[0]/LT[0][hal]);
	double dcorr = (R500[0][hal]*0.5+N[0][hal]/Eff[0]/LT[0][hal])
          /(N[0][hal]/Eff[0]/LT[0][hal]);
	
	dcorr = corr-dcorr;

	double r  = R*corr;
	double dr = r * sqrt( pow(dR/R,2) + pow(dcorr/corr, 2));
	
	cout<< r
	    << "$\\pm$"
	    << dr
	    << "\t&";
      }
    }
    cout<<endl;
  }
	
  
}
