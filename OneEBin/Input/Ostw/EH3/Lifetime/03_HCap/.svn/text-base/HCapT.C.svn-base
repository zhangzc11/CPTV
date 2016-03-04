double HCapT(double *x,double *par)
{
  double N     = par[0];
  double Alpha = par[1];
  double LCap  = par[2];
  double LGen  = par[3];
  double FlatB = par[4];
  
  double frac  = par[5];
  double Beta  = par[6];
  double LCapH = par[7];
  double LGenH = par[8];

  double t = x[0];

  double NDensity =
    N*( 
       (1-frac) * ((1+Alpha)*LCap*exp(-LCap*t)   - Alpha*LGen*exp(-LGen*t)) +
       frac *     ((1+Beta)* LCapH*exp(-LCapH*t) - Beta *LGenH*exp(-LGenH*t))
	)
    + FlatB;

  return NDensity;
}
