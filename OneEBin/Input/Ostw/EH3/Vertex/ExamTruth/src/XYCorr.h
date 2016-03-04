/* 
   Return a correction factor for recontructed r^2 and Z
   Zhe Wang, June 26, 2012
*/

#ifndef XYCORR_H
#define XYCORR_H

#define XBin 50
#define YBin 50

class XYCorr
{
 public:
  XYCorr();
  ~XYCorr();
  
  int Correct(double recx, double recy, 
	      double& truex, double& truey);

 private:
  double XCorr[XBin][YBin];
  double YCorr[XBin][YBin];

  double max,min,step;
};

#endif // XYCORR_H
