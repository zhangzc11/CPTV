#include <iostream>
using namespace std;

/*
  All the following data is for P12b-all, i.e. CPC period.
  Zhe Wang
  Jul. 7, 2013
*/

double nu[6][6] = { /* Index: Ad, then Rct. */
  /* From nu_i output of Truth.C 
     = Flux * Cross section * Daq time * Nproton / (4 pi r^2)
  */
  /*
  { 35431.3,   47513.9,   6497.09,   8186.52,   3384.38,   3804.68},
  { 36274.4,   48339.5,   6494.87,   8186.35,   3378.42,   3797.98},
  { 2612.07,   3551.49,   24198.1,   22767  , 19899.6  , 24384.8},
  { 1247.5 ,  1810.43 ,  2233.34 ,  2298.3  , 2549.68  , 2592.25},
  { 1252.92,   1817.9 ,  2230.81 ,  2296.92 ,  2542.68 ,  2585.89},
  { 1239.5 ,  1799.12 ,  2215.99 ,  2280.12 ,  2532.34 ,  2573.74}
  */
  {52637.1, 71446.7, 10362.8, 12886.6, 5101.93, 4089.13},
  {53909.3, 72708.9, 10361.6, 12889.4, 5094.39, 4082.13},
  {3890.95, 5311.76, 38352.8, 35609.8, 29833.4, 26244.5},
  {1862.28, 2732.94, 3577.17, 3634.08, 3858.53, 2789.98},
  {1869.09, 2742.75, 3571.63, 3630.3, 3845.9, 2782.86},
  {1850.69, 2716.27, 3549.79, 3605.78, 3832.86, 2770.13}
};

double MuOsEff[6] = {0.8078,0.8046,0.8403,0.9616,0.9615,0.9610};

void CalWeight()
{
  double nutot[6];
  double conv[3][3]; /* Index: AD4,5,6, then AD1,2,3 */

  for( int ad = 1; ad<=6; ad++ ) {
    nutot[ad-1] = nu[ad-1][0]+nu[ad-1][1]+nu[ad-1][2]+nu[ad-1][3]+nu[ad-1][4]+nu[ad-1][5];
  }

  for( int far = 4; far<=6; far++ ) {
    for( int ner = 1; ner<=3; ner++ ) {
      conv[far-4][ner-1] 
	= nutot[far-1] / nutot[ner-1];
    }
  }
  
  cout<<"Conversion factors:statistic for each far detector"<<endl;
  for( int far = 4; far<=6; far++ ) {
    for( int ner = 1; ner<=3; ner++ ) {
      cout<< conv[far-4][ner-1]<<":"<<nutot[ner-1]*MuOsEff[ner-1]<<"   ";
    }
    cout<<endl;
  }

  cout<<"Conversion factors"<<endl;
  for( int far = 4; far<=6; far++ ) {
    for( int ner = 1; ner<=3; ner++ ) {
      cout<< conv[far-4][ner-1]<<"   ";
    }
    cout<<endl;
  }

  cout<<"weight for each far detector"<<endl;
  for( int far = 4; far<=6; far++ ) {
    for( int ner = 1; ner<=3; ner++ ) {
      cout<< 1/(nutot[ner-1]*MuOsEff[ner-1])<<"   ";
    }
    cout<<endl;
  }

}


