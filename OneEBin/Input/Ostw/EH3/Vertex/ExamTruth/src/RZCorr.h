/* 
   Return a correction factor for recontructed r^2 and Z
   Zhe Wang, June 26, 2012
*/

#ifndef RZCORR_H
#define RZCORR_H

#define R2Bin 100
#define ZBin  100

class RZCorr
{
 public:
  RZCorr();
  ~RZCorr();
  
  int Correct(double recz, double recr2, 
	      double& truez, double& truer2);

 private:
  double R2Corr[R2Bin][ZBin];
  double ZCorr[R2Bin][ZBin];

  double r2max,r2min,r2step;
  double zmax,zmin,zstep;
};

#endif // RZCORR_H
